#include "GxHeatMapNode.h"

#include "GxGeoUtil.h"
#include <qmath.h>
#include <heatmap.h>
#include <lodepng.h>
#include <GxGradientPalette.h>
#include <QApplication>
#include <QUuid>
#include <QDebug>
#include <osg/ImageUtils>

heatmap_colorscheme_t *GxHeatMapNode::m_pColorScheme = nullptr;

GxHeatMapNode::GxHeatMapNode(double raduis, double interpo)
	: m_dRadius(raduis)
	, m_dInterpo(interpo)
{
	m_rpImageOverlay = new GxImageOverlay;
	this->addChild(m_rpImageOverlay);

	if (m_pColorScheme == nullptr)
	{
		static unsigned char mixed_exp_data[4100] = { 0 };

		QList<QColor> colors;
		QColor c1(180, 255, 122);
		c1.setAlphaF(0.0);
		colors.append(c1);

		QColor c2(180, 255, 122);
		c2.setAlphaF(0.4);
		colors.append(c2);

		QColor c3(223, 201, 34);
		c3.setAlphaF(0.8);
		colors.append(c3);

		QColor c4(255, 109, 41);
		c4.setAlphaF(1.0);
		colors.append(c4);

		GxGradientPalette gradientPalette(colors);

		for (int i = 0; i < 1025; ++i)
		{
			QColor color = gradientPalette.colorAt((double)i / 1024);
			mixed_exp_data[4 * i] = color.red();
			mixed_exp_data[4 * i + 1] = color.green();
			mixed_exp_data[4 * i + 2] = color.blue();
			mixed_exp_data[4 * i + 3] = color.alpha();
		}

		m_pColorScheme = new heatmap_colorscheme_t;
		m_pColorScheme->colors = mixed_exp_data;
		m_pColorScheme->ncolors = 1025;
	}
}

GxHeatMapNode::~GxHeatMapNode()
{
}

void GxHeatMapNode::setPoints(const QList<StHeatmapPoint> &points)
{
	if (points.size() == 0)
	{
		return;
	}

	m_points.clear();

	StHeatmapPoint firstPoint = points.first();
	osg::Vec3d firstXYZ;
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(firstPoint.lon, firstPoint.lat, 0.0), firstXYZ);
	osg::Vec4d firstXYZW(firstXYZ, firstPoint.weight);
	m_points.append(firstXYZW);

	// 计算热力图水平和垂直范围 begin
	double dHorMin = firstXYZ.x(), dHorMax = firstXYZ.x()
		, dVerMin = firstXYZ.y(), dVerMax = firstXYZ.y();

	for (int i = 1; i < points.size(); ++i)
	{
		StHeatmapPoint heatmapPoint = points[i];

		// 经纬高转世界坐标
		osg::Vec3d vecXYZ;
		GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(heatmapPoint.lon, heatmapPoint.lat, 0.0), vecXYZ);

		if (dHorMin > vecXYZ.x())
		{
			dHorMin = vecXYZ.x();
		}
		if (dHorMax < vecXYZ.x())
		{
			dHorMax = vecXYZ.x();
		}
		if (dVerMin > vecXYZ.y())
		{
			dVerMin = vecXYZ.y();
		}
		if (dVerMax < vecXYZ.y())
		{
			dVerMax = vecXYZ.y();
		}

		osg::Vec4d vecXYZW(vecXYZ, heatmapPoint.weight);
		m_points.append(vecXYZW);
	}

	// 四个方向延伸半径的长度
	dHorMin -= m_dRadius;
	dVerMin -= m_dRadius;
	dHorMax += m_dRadius;
	dVerMax += m_dRadius;
	// 计算热力图水平和垂直范围 end

	// 生成热力图 begin
	const size_t w = qCeil((dHorMax - dHorMin) / m_dInterpo);
	const size_t h = qCeil((dVerMax - dVerMin) / m_dInterpo);
	heatmap_t *hm = heatmap_new(w, h);
	const size_t r = m_dRadius / m_dInterpo;

	heatmap_stamp_t *stamp = heatmap_stamp_gen(r);
	for (int i = 0; i < m_points.size(); ++i)
	{
		osg::Vec4d vecXYZW = m_points[i];
		unsigned int x = (vecXYZW.x() - dHorMin) / m_dInterpo;
		unsigned int y = (vecXYZW.y() - dVerMin) / m_dInterpo;
		heatmap_add_weighted_point_with_stamp(hm, x, y, vecXYZW.w(), stamp);
	}
	heatmap_stamp_free(stamp);

	unsigned char* imageData = new unsigned char[w * h * 4];
	heatmap_render_to(hm, m_pColorScheme, imageData);
	// 生成热力图 end

	// 热力图渲染到二维场景中 begin
	osg::Image *pImage = new osg::Image;
	pImage->setImage(hm->w, hm->h, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, imageData, osg::Image::USE_NEW_DELETE);

	osg::Vec3d v1(dHorMin, dVerMin, 10);
	osg::Vec3d v11;
	GxGeoUtil::xyz2DegreeLLH(v1, v11);

	osg::Vec3d v2(dHorMax, dVerMax, 10);
	osg::Vec3d v22;
	GxGeoUtil::xyz2DegreeLLH(v2, v22);

	m_rpImageOverlay->setBounds(v11.x(), v22.y(), v22.x(), v11.y());

	m_rpImageOverlay->setImage(pImage);
	// 热力图渲染到二维场景中 end

	heatmap_free(hm);
}

void GxHeatMapNode::addPoint(double lon, double lat, double weight)
{
	osg::Vec3d newPointXYZ;
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(lon, lat, 0.0), newPointXYZ);
	osg::Vec4d newPointXYZW(newPointXYZ, weight);
	m_points.append(newPointXYZW);

	osg::Vec4d firstXYZW = m_points.first();

	// 计算热力图水平和垂直范围 begin
	double dHorMin = firstXYZW.x(), dHorMax = firstXYZW.x()
		, dVerMin = firstXYZW.y(), dVerMax = firstXYZW.y();

	for (int i = 1; i < m_points.size(); ++i)
	{
		// 经纬高转世界坐标
		osg::Vec4d vecXYZW = m_points[i];

		if (dHorMin > vecXYZW.x())
		{
			dHorMin = vecXYZW.x();
		}
		if (dHorMax < vecXYZW.x())
		{
			dHorMax = vecXYZW.x();
		}
		if (dVerMin > vecXYZW.y())
		{
			dVerMin = vecXYZW.y();
		}
		if (dVerMax < vecXYZW.y())
		{
			dVerMax = vecXYZW.y();
		}
	}

	// 四个方向延伸半径的长度
	dHorMin -= m_dRadius;
	dVerMin -= m_dRadius;
	dHorMax += m_dRadius;
	dVerMax += m_dRadius;
	// 计算热力图水平和垂直范围 end

	// 生成热力图 begin
	const size_t w = qCeil((dHorMax - dHorMin) / m_dInterpo);
	const size_t h = qCeil((dVerMax - dVerMin) / m_dInterpo);
	heatmap_t *hm = heatmap_new(w, h);
	const size_t r = m_dRadius / m_dInterpo;

	heatmap_stamp_t *stamp = heatmap_stamp_gen(r);
	for (int i = 0; i < m_points.size(); ++i)
	{
		osg::Vec4d vecXYZW = m_points[i];
		unsigned int x = (vecXYZW.x() - dHorMin) / m_dInterpo;
		unsigned int y = (vecXYZW.y() - dVerMin) / m_dInterpo;
		heatmap_add_weighted_point_with_stamp(hm, x, y, vecXYZW.w(), stamp);
	}
	heatmap_stamp_free(stamp);

	unsigned char* imageData = new unsigned char[w * h * 4];
	heatmap_render_to(hm, m_pColorScheme, imageData);
	// 生成热力图 end

	// 热力图渲染到二维场景中 begin
	osg::Image *pImage = new osg::Image;
	pImage->setImage(hm->w, hm->h, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, imageData, osg::Image::USE_NEW_DELETE);

	osg::Vec3d v1(dHorMin, dVerMin, 10);
	osg::Vec3d v11;
	GxGeoUtil::xyz2DegreeLLH(v1, v11);

	osg::Vec3d v2(dHorMax, dVerMax, 10);
	osg::Vec3d v22;
	GxGeoUtil::xyz2DegreeLLH(v2, v22);

	m_rpImageOverlay->setBounds(v11.x(), v22.y(), v22.x(), v11.y());

	m_rpImageOverlay->setImage(pImage);
	// 热力图渲染到二维场景中 end

	heatmap_free(hm);
}

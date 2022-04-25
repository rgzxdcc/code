#ifndef GX_HEATMAP_NODE_H
#define GX_HEATMAP_NODE_H

#include <QList>
#include <heatmap.h>
#include "GxImageOverlay.h"
#include "dckjgzgis_export.h"

// ����ͼ��
struct StHeatmapPoint
{
	double lon;		// ����
	double lat;		// γ��
	double weight;	// Ȩ�أ�Ĭ��Ϊ1��

	StHeatmapPoint() {
		lon = 0.0;
		lat = 0.0;
		weight = 1.0;
	}

	StHeatmapPoint(double lo, double la, double wei = 1.0) {
		lon = lo;
		lat = la;
		weight = wei;
	}
};

/**
* @class GxHeatMapNode
* @brief ����ͼ�ڵ�
* @note
**/
class DCKJGZGIS_EXPORT GxHeatMapNode : public GxAnnotationNode
{
public:
	/**
	* @brief ���캯��
	* @param raduis [in] �뾶����λ���ף�
	* @param interpo [in] ��ֵ�������λ���ף�
	*/
	GxHeatMapNode(double raduis = 2000.0 * 20, double interpo = 2000.0);
	~GxHeatMapNode();

	/**
	* @brief ��������ͼ����ɵ�
	* @param points [in] ���е�
	*/
	void setPoints(const QList<StHeatmapPoint> &points);

	/**
	* @brief �������ͼ��ɵ�
	* @param lon [in] ���ȣ���λ���ȣ�
	* @param lat [in] γ�ȣ���λ���ȣ�
	* @param weight [in] Ȩ�أ�Ĭ��Ϊ1.0��
	*/
	void addPoint(double lon, double lat, double weight = 1.0);

private:
	double m_dRadius;				// ����ͼ��Բ�뾶
	double m_dInterpo;				// ��ֵ���
	QList<osg::Vec4d> m_points;		// ��ɵ㣨ǰ3���������������꣬��4��������Ȩ�أ�
	static heatmap_colorscheme_t *m_pColorScheme;	// ��ɫ
	osg::ref_ptr<GxImageOverlay> m_rpImageOverlay;
};

#endif // !GX_HEATMAP_NODE_H

#ifndef GX_HEATMAP_NODE_H
#define GX_HEATMAP_NODE_H

#include <QList>
#include <heatmap.h>
#include "GxImageOverlay.h"
#include "dckjgzgis_export.h"

// 热力图点
struct StHeatmapPoint
{
	double lon;		// 经度
	double lat;		// 纬度
	double weight;	// 权重（默认为1）

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
* @brief 热力图节点
* @note
**/
class DCKJGZGIS_EXPORT GxHeatMapNode : public GxAnnotationNode
{
public:
	/**
	* @brief 构造函数
	* @param raduis [in] 半径（单位：米）
	* @param interpo [in] 插值间隔（单位：米）
	*/
	GxHeatMapNode(double raduis = 2000.0 * 20, double interpo = 2000.0);
	~GxHeatMapNode();

	/**
	* @brief 设置热力图的组成点
	* @param points [in] 所有点
	*/
	void setPoints(const QList<StHeatmapPoint> &points);

	/**
	* @brief 添加热力图组成点
	* @param lon [in] 经度（单位：度）
	* @param lat [in] 纬度（单位：度）
	* @param weight [in] 权重（默认为1.0）
	*/
	void addPoint(double lon, double lat, double weight = 1.0);

private:
	double m_dRadius;				// 热力图画圆半径
	double m_dInterpo;				// 插值间隔
	QList<osg::Vec4d> m_points;		// 组成点（前3个分量是世界坐标，第4个分量是权重）
	static heatmap_colorscheme_t *m_pColorScheme;	// 颜色
	osg::ref_ptr<GxImageOverlay> m_rpImageOverlay;
};

#endif // !GX_HEATMAP_NODE_H

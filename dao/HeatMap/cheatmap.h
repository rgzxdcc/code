#ifndef CHEATMAP_H
#define CHEATMAP_H

#include <QList>
#include <osg/Image>
#include <osgEarth/MapNode>
#include "heatmap.h"


// 热力图点
struct StHTPoint
{
    double lon;     // 经度
    double lat;     // 纬度
    double weight;  // 权重（默认为1）

    StHTPoint()
    {
        lon = 0.0;
        lat = 0.0;
        weight = 1.0;
    }

    StHTPoint(double dlon, double dlat, double dweight)
    {
        lon = dlon;
        lat = dlat;
        weight = dweight;
    }
};

// 热力图创建
class CHeatMap
{
public:
    CHeatMap(osgEarth::MapNode *mapNode);

    // 获取最终图片
    osg::Image *getImage() { return _image;}
    // 获取图片大小


    // 设置热力图的组成点
    void setPoints(const QList<StHTPoint> &points);


private:

    // LLH2XYZ
    osg::Vec3d getLLH2XYZ(const osg::Vec3d &llh);

private:

    osgEarth::MapNode * _mapNode;
    osg::Image *        _image;
    osg::Vec4dArray *   _points;

    static heatmap_colorscheme_t *_colorscheme;
};

#endif // CHEATMAP_H

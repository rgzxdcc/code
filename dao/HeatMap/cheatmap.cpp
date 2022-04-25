#include "cheatmap.h"
#include <qmath.h>

#include "GxGradientPalette.h"

const double C_RADIUS = 2000.0 * 1000;
const double C_INTERVAL = 2000.0;

heatmap_colorscheme_t * CHeatMap::_colorscheme = nullptr;
CHeatMap::CHeatMap(osgEarth::MapNode *mapNode)
    :_mapNode(mapNode),
     _image(NULL)
{
    _points = new osg::Vec4dArray;

    // 初始色标
    if (_colorscheme == nullptr)
    {
        static unsigned char mixed_exp_data[4100] = { 0 };

        QList<QColor> colors;
        QColor c1(180, 255, 122);
        c1.setAlphaF(0.0);
       // vecCS.push_back(qMakePair(0.0, c1));
        colors.append(c1);

        QColor c2(180, 255, 122);
        c2.setAlphaF(0.4);
        //vecCS.push_back(qMakePair(0.4, c2));
        colors.append(c2);

        QColor c3(223, 201, 34);
        c3.setAlphaF(0.8);
        //vecCS.push_back(qMakePair(0.8, c3));
        colors.append(c3);

        QColor c4(255, 109, 41);
        c4.setAlphaF(1.0);
        //vecCS.push_back(qMakePair(1.0, c4));
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

        _colorscheme = new heatmap_colorscheme_t;
        _colorscheme->colors = mixed_exp_data;
        _colorscheme->ncolors = 1025;
    }
}

void CHeatMap::setPoints(const QList<StHTPoint> &points)
{
    if(!points.size())
        return;

    _points->clear();

    double xmin, ymin, xmax, ymax;
    osg::Vec3d firstP = getLLH2XYZ(osg::Vec3d(points[0].lon, points[0].lat, 0.0));
    xmin = firstP.x();
    ymin = firstP.y();
    xmax = firstP.x();
    ymax = firstP.y();

    // 循环计算给出点的矩形边界
    foreach (StHTPoint p, points)
    {
         osg::Vec3d xyzP = getLLH2XYZ(osg::Vec3d(p.lon, p.lat, 0.0));
         if (xyzP.x() < xmin)
            xmin = xyzP.x();
         if (xyzP.x() > xmax)
            xmax = xyzP.x();
         if (xyzP.y() < ymin)
            ymin = xyzP.y();
         if (xyzP.y() > ymax)
            ymax = xyzP.y();

         osg::Vec4d xyzwP(xyzP, p.weight);
         _points->push_back(xyzwP);
    }


    // 四个方向延伸
    xmin -= C_RADIUS;
    xmax += C_RADIUS;
    ymin -= C_RADIUS;
    ymax += C_RADIUS;

    // 生成离散数据
    const size_t w = qCeil(xmax - xmin) / C_INTERVAL;
    const size_t h = qCeil(ymax - ymin) / C_INTERVAL;
    heatmap_t *hm = heatmap_new(w, h);
    const size_t r = C_RADIUS / C_INTERVAL;

    heatmap_stamp_t *stamp = heatmap_stamp_gen(r);
    for (int i = 0; i < _points->size(); i++)
    {
        osg::Vec4d xyzw = _points->at(i);
        unsigned int x = (xyzw.x() - xmin) / C_INTERVAL;
        unsigned int y = (xyzw.y() - ymin) / C_INTERVAL;
        heatmap_add_weighted_point_with_stamp(hm, x, y, xyzw.w(), stamp);
    }
    heatmap_stamp_free(stamp);

    unsigned char *imageData = new unsigned char[w * h * 4];
    heatmap_render_to(hm, _colorscheme, imageData);

    // 生成图片
    _image = new osg::Image;
    _image->setImage(hm->w, hm->h, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, imageData, osg::Image::USE_NEW_DELETE);
}

osg::Vec3d CHeatMap::getLLH2XYZ(const osg::Vec3d &llh)
{
    osg::Vec3d XYZ;
    _mapNode->getMapSRS()->getEllipsoid()->convertLatLongHeightToXYZ(llh.y(), llh.x(), llh.z(), XYZ.x(), XYZ.y(), XYZ.z());

    return XYZ;
}

#include "situationscene.h"

#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

#include "customenvelope.h"
#include <QDebug>

SituationScene::SituationScene(osg::Group *root)
    : _root(root),
      _mapNode(NULL),
      _radarEnv(NULL)
{
    InitScene();
    InitEnvelope();
}

void SituationScene::InitScene()
{
    std::string earthPath = "E:/dcc/test/test.earth";
    osg::Node *node = osgDB::readNodeFile(earthPath);
    if (!node)
        return;

    _mapNode = osgEarth::MapNode::findMapNode(node);
    if (!_mapNode)
        return;

    //_root->addChild(_mapNode);
}

void SituationScene::InitEnvelope()
{
    // radar
    RadarData rd;
    rd.lon = 55.306;
    rd.lat = 32.041;
    rd.alt = 200;
    rd.radius = 20000;
    _radarEnv = new CustomEnvelope(this, rd);

    // jam
    JamData jd;
    jd.lon = 54.306;
    jd.lat = 29.341;
    jd.alt = 10000;
    _radarEnv->AddJam(jd);
    JamData jd2;
    jd2.lon = 52.421;
    jd2.lat = 31.379;
    jd2.alt = 10000;
    _radarEnv->AddJam(jd2);

    // 渲染包络
     _radarEnv->UpdateEnv();

    // deploy envelope
    osg::MatrixTransform *mt = new osg::MatrixTransform;
    osg::Matrix localM = LLH2Matrix(osg::Vec3(rd.lon, rd.lat, rd.alt));
   // localM = osg::Matrix::rotate(osg::PI_2, osg::Vec3d(1.0, 0.0, 0.0));
    mt->setMatrix(localM);
    mt->addChild(_radarEnv);

    _root->addChild(mt);
}

void SituationScene::UpdateJams(const std::list<JamData> &jams)
{
    if (_radarEnv)
    {
        _radarEnv->SetJams(jams);
    }

}

osg::Vec3 SituationScene::LLH2XYZ(osg::Vec3 LLH)
{
    osg::Vec3d XYZ;
    if (_mapNode)
    {
        double rlon = osg::DegreesToRadians(LLH.x());
        double rlat = osg::DegreesToRadians(LLH.y());

        _mapNode->getMapSRS()->getEllipsoid()->convertLatLongHeightToXYZ(rlat, rlon, LLH.z(), XYZ.x(), XYZ.y(), XYZ.z());
    }

    return XYZ;
}

osg::Matrix SituationScene::LLH2Matrix(osg::Vec3 LLH)
{
    osg::Matrix m;
    if (_mapNode)
    {
        double rlon = osg::DegreesToRadians(LLH.x());
        double rlat = osg::DegreesToRadians(LLH.y());

        _mapNode->getMapSRS()->getEllipsoid()->computeLocalToWorldTransformFromLatLongHeight(rlat, rlon, LLH.z(), m);
    }

    return m;
}

double SituationScene::Distance(osg::Vec3 start, osg::Vec3 end)
{
    osg::Vec3 xyz1 = LLH2XYZ(start);
    osg::Vec3 xyz2 = LLH2XYZ(end);

    return (xyz1 - xyz2).length();
}

double SituationScene::GetAzi(osg::Vec3 start, osg::Vec3 end)
{
    double YawAngle = 0.0;

    osg::Vec3 xyz1 = LLH2XYZ(start);
    osg::Vec3 xyz2 = LLH2XYZ(end);

    osg::Vec3d SecondBottomXYZ(xyz2.x(), xyz2.y(), xyz1.z());
    osg::Vec3d threeXYZ(xyz1.x(), xyz2.y(), xyz1.z());

    double dDistance1 = (SecondBottomXYZ - xyz1).length();
    double dDistance2 = (xyz1 - threeXYZ).length();//FxCommonUtils::GetDis(FirstXYZ, threeXYZ);

    if (dDistance1>0.0)
    {
        YawAngle = acos(dDistance2 / dDistance1);
    }
    else
        YawAngle = 0.0;
    if (xyz2.y() < xyz1.y() )
    {
        YawAngle = -YawAngle;
    }

    return osg::RadiansToDegrees(YawAngle);
}

#include "customenvelope.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Depth>

#include "GxGradientPalette.h"
#include "situationscene.h"

#include <QDebug>


CustomEnvelope::CustomEnvelope(SituationScene *ss, const RadarData &radar)
    :_situateScene(ss),
      _radar(radar)
{
    Init();
}

void CustomEnvelope::AddJam(const JamData &jd)
{
    _jams.push_back(jd);
}

void CustomEnvelope::SetJams(const std::list<JamData>& jams)
{
    _jams.clear();
    foreach (JamData jd, jams)
    {
        _jams.push_back(jd);
    }

    // update envelop
    UpdateEnv();
}

void CustomEnvelope::UpdateEnv()
{
    // 删除之前节点
    while (getNumChildren())
    {
        removeChild(0, 1);
    }

    // create envelope
    osg::Geode * gd = new osg::Geode;
    gd->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
    gd->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    gd->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    addChild(gd);

    // organize points
    double step = 5.0;
    double ele  = 0;
    for (; ele < 90.0; ele+=step)
    {
        osg::Geometry *gm = new osg::Geometry;
        osg::Vec3Array *vertexArray = new osg::Vec3Array;
        osg::Vec4Array *colorArray = new osg::Vec4Array;

        double azi  = 0;
        for (; azi <= 360.0; azi += step)
        {
            double indis = GetDistance(azi, ele);
            double outdis = GetDistance(azi, ele + step);
            osg::Vec4f incolor = GetColor(indis);
            osg::Vec4f outcolor = GetColor(outdis);

            double razi = osg::DegreesToRadians(azi);
            double rinele = osg::DegreesToRadians(ele);
            double routele = osg::DegreesToRadians(ele + step);
            double inx = indis * cos(rinele) * cos(razi);
            double iny = indis * cos(rinele) * sin(razi);
            double inz = indis * sin(rinele);
            double outx = outdis * cos(routele) * cos(razi);
            double outy = outdis * cos(routele) * sin(razi);
            double outz = outdis * sin(routele);

            vertexArray->push_back(osg::Vec3(outx, outy, outz));
            vertexArray->push_back(osg::Vec3(inx, iny, inz));

            colorArray->push_back(outcolor);
            colorArray->push_back(incolor);
        }

        gm->setVertexArray(vertexArray);
        gm->setColorArray(colorArray, osg::Array::BIND_PER_VERTEX);

        int numPoints = (360 / step + 1) * 2;
        gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, numPoints));

        gm->getOrCreateStateSet()->setAttribute(new osg::Depth(osg::Depth::LESS,0.0, 1.0, false));
        gm->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
        gm->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF| osg::StateAttribute::PROTECTED);
        gm->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        gd->addDrawable(gm);
    }
}

void CustomEnvelope::Init()
{
    // init palette
    QList<QColor> colors;
    colors.append(QColor(0, 0, 255, 0.0 * 255));
    colors.append(QColor(0, 255, 0, 0.4 * 255));
    colors.append(QColor(255, 255, 0, 0.8 * 255));
    colors.append(QColor(255, 0, 0, 1.0 * 255));
    _colorPalette = new GxGradientPalette(colors);

    getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
    getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
}

double CustomEnvelope::Log2Linear(double value)
{
    return pow(10, value / 10);
}

double CustomEnvelope::GetDistance(double azi, double pitch)
{
    // 无干扰压制
    if (_jams.size() < 1)
    {
        double numerator = _radar.Pt * pow(_radar.Gt * _radar.λ, 2.0) * _radar.σ * pow(_radar.n, 0.5);
        double denominator = pow(4*osg::PI, 3.0) * _radar.k * _radar.T0 * _radar.Bn * _radar.Fn * _radar.SN;
        double maxdis = pow(numerator / denominator, 0.25);
        pitch = osg::DegreesToRadians(pitch);
        double elefactor = pow(fabs(sin(pitch)), 0.25) * pow(cos(pitch), 2.0);
        return maxdis * elefactor;
    }
    else
    {
        // 计算分子
        double numerator = _radar.Pt * pow(_radar.Gt, 2.0) * Kj * _radar.σ * pow(_radar.n, 0.5);

        // 计算分母
        double denominator = 0.0;

        osg::Vec3 radarPos(_radar.lon, _radar.lat, _radar.alt);
        foreach (JamData jd, _jams)
        {
            osg::Vec3 jamPos(jd.lon, jd.lat, jd.alt);
            // 相对方位角
            double angle = _situateScene->GetAzi(radarPos, jamPos);
            double dir = fabs(azi - angle);
            if (dir > 360.0)
            {
                dir -= 360;
            }
            else if (dir > 180)
            {
                dir = 360 - dir;
            }


            double θ = dir;

            double Gθ = 0.0;
            double linearGt = Log2Linear(_radar.Gt);
            if (θ <= θhalf / 2)
            {
                Gθ = linearGt;
            }
            else if (θhalf / 2 <= θ && θ <= 90)
            {
                Gθ = K * pow(θhalf/θ, 2) * linearGt;
            }
            else
            {
                Gθ = K * pow(θhalf/90, 2) * linearGt;
            }

            // 计算距离

            double Rj =_situateScene->Distance(radarPos, jamPos);
            double denm = jd.Pj * Log2Linear(jd.Gj) * Gθ * _radar.Bn * Log2Linear(-jd.γj) / pow(Rj, 2.0) / jd.Bj;
            denominator += denm;
        }
        denominator *= (4 * osg::PI);
        if (fabs(denominator) <= 1e-8)
        {
            qDebug() << "nan nan nan --------------------------------------------------------------------- ";
        }
        double maxdis = pow(numerator / denominator, 0.25);

        // 俯仰因素
        pitch = osg::DegreesToRadians(pitch);
        double elefactor = pow(fabs(sin(pitch)), 0.25) * pow(cos(pitch), 2);
        return maxdis * elefactor;
    }

}

osg::Vec4f CustomEnvelope::GetColor(double distance)
{
    double pos = distance / 12000.0;

    QColor color = _colorPalette->colorAt(pos);

    return osg::Vec4f(color.redF(), color.greenF(), color.blueF(), 0.6);
}

#ifndef SITUATIONSCENE_H
#define SITUATIONSCENE_H

#include <osgEarth/MapNode>
#include <QList>

#include "datadef.h"

class CustomEnvelope;

class SituationScene
{
public:
    SituationScene(osg::Group *root);

    // create earth
    void InitScene();

    // create envelope
    void InitEnvelope();

    // update jams
    void UpdateJams(const std::list<JamData> &jams);

    // convert LLH to XYZ
    osg::Vec3 LLH2XYZ(osg::Vec3 LLH);
    // convert LLH to matrix
    osg::Matrix LLH2Matrix(osg::Vec3 LLH);

    // calc dis
    double Distance(osg::Vec3 start, osg::Vec3 end);
    // calc angle
    double GetAzi(osg::Vec3 start, osg::Vec3 end);


private:

    osg::Group *            _root;
    osgEarth::MapNode *     _mapNode;

    CustomEnvelope *        _radarEnv;
};

#endif // SITUATIONSCENE_H

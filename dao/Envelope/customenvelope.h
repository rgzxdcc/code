#ifndef CUSTOMENVELOPE_H
#define CUSTOMENVELOPE_H

#include <list>
#include <osg/Group>
#include <QLinearGradient>

#include "datadef.h"

class GxGradientPalette;
class SituationScene;

// 常规包络
class CustomEnvelope : public osg::Group
{
public:
    CustomEnvelope(SituationScene * ss, const RadarData &radar);

    // 添加干扰机
    void AddJam(const JamData &jd );

    // 重置干扰机
    void SetJams(const std::list<JamData>& jams);

    // 更新包络
    void UpdateEnv();

private:

    // 初始化
    void Init();

    //
    double Log2Linear(double value);

    // 获取辐射距离
    double GetDistance(double azi, double pitch);

    // 根据辐射范围获取对应色标
    osg::Vec4f GetColor(double distance);


private:
    GxGradientPalette*      _colorPalette;      // 色标
    SituationScene *        _situateScene;      // 三维场景

    RadarData               _radar;     // 雷达属性

    std::list<JamData>      _jams;      // 干扰机

};

#endif // CUSTOMENVELOPE_H

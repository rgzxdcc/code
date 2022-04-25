#ifndef DATADEF_H
#define DATADEF_H

#pragma pack(push, 1)

const double K = 0.05;
const double θhalf = 20.0;
const double Kj = 2.0;


// 雷达属性
struct RadarData
{
    RadarData()
    {
        Pt = 1.0e6;
        Gt = 40.0;
        λ  = 0.056;
        n  = 16.0;
        σ  = 3.0;
        Bn = 1.6e6;
        Fn = 10.0;
        SN = 2.0;
        T0 = 290.0;
        k  = 1.38e-23;
    }

    double Pt;
    double Gt;
    double λ;
    double n;
    double σ;
    double Bn;
    double Fn;
    double SN;
    double T0;
    double k;

    double lon;
    double lat;
    double alt;

    double radius;
};


// 干扰机参数
struct JamData
{
    JamData()
    {
        Pj = 10.0;
        Gj = 10.0;
        γj = 0.5;
        Bj = 2.0e6;
    }

    JamData(const JamData& jd)
    {
        Pj = jd.Pj;
        Gj = jd.Gj;
        γj = jd.γj;
        Bj = jd.Bj;

        lon = jd.lon;
        lat = jd.lat;
        alt = jd.alt;
    }

    double Pj;
    double Gj;
    double γj;
    double Bj;

    double lon;
    double lat;
    double alt;
};

#pragma pack(pop)

#endif // DATADEF_H

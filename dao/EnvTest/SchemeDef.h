/*
* 想定动态数据结构定义
* d00019 20211227
*/
#ifndef SCENARIO_DEF
#define SCENARIO_DEF

#include "GlobalDef.h"

#include <vector>
#include <map>
using namespace std;

const unsigned int UNVALID_ID = 0xFFFFFFFF;

enum UNIT_LEVEL	// 能力数据层级
{
	UNIT_LEVEL_TOP,		// 所属机关/行动总队
	UNIT_LEVEL_SCD,		// 动员单位/行动单元
};

// 能力单元
struct AbilityUnit
{
	UNIT_LEVEL		level;	// 能力层级
	unsigned int	id;		// id
	unsigned int	upid;	// 所属id
	string			name;	// 名称

	string			info;	// 信息

	vector<AbilityUnit>	units;	// 下层节点
};

// 地理信息点
struct SimGeoPoint
{
	SimGeoPoint()
	{
		lng = 120.0;
		lat = 32.9;
		alt = 0.1;
	}
	SimGeoPoint(double dlng, double dlat, double dalt)
	{
		lng = dlng;
		lat = dlat;
		alt = dalt;
	}
	bool operator == (const SimGeoPoint &sgp) const
	{
		return fabs(lng-sgp.lng) < 0.0000001 && 
			fabs(lat - sgp.lat) < 0.0000001 &&
			fabs(alt - sgp.alt) < 0.0000001;
	}

	double lng;			// 经度：°
	double lat;			// 纬度：°
	double alt;			// 高度：m
};

// 单条轨迹数据
struct SinglePath
{
	bool operator == (const SinglePath &sp) const 
	{
		return !strcmp(sp.begin.c_str(), begin.c_str()) &&
			!strcmp(sp.end.c_str(), end.c_str()) &&
			sp.keypoints == keypoints;
	}
	string desc;			// 数据描述
	string begin;			// 开始时间
	string end;				// 结束时间

	vector<SimGeoPoint> keypoints;	// 关键点集
};

// 态势资源
struct SituationResc
{
	TASK_TYPE		task;	// 任务类型
	EnObjType		type;	// 实体类型
	unsigned int	id;		// id
	string			name;	// 名称
	int				lod;	// 层级

	SimGeoPoint		sgp;	// 位置
};

typedef std::map<EnObjType, vector<SituationResc> > Type2Resource;
typedef std::map<TASK_TYPE, vector<SituationResc> > Task2Resource;

// 方案数据
struct Scheme
{
	SCN_TYPE type;		// 方案类型
	unsigned int id;	// 方案ID
	string name;		// 方案名称
	string dir;			// 方案目录
	string desc;		// 方案描述
	string begin;		// 开始时间
	string end;			// 结束时间

	union DetailSchemeInfo	// 方案自相关信息
	{
		struct BJHLInfo		// 保交护路信息
		{
			char name[NAME_MAX_LEN];// 部队名称
			unsigned int militias;	// 部队数量
			unsigned int vehicles;	// 部队车辆
			unsigned int speed;		// 行军速度
			unsigned int oilType;   // 油料种类
		}bjhl;

		struct MBFWInfo		// 目标防卫信息
		{
			char name[NAME_MAX_LEN];// 保卫目标名称
		}mbfw;
	}dsi;
};

// 任务数据
struct Task
{
	bool operator != (const Task &t) const
	{
		return t.type != type ||
			t.rescid != rescid ||
			strcmp(t.begin.c_str(), begin.c_str()) ||
			strcmp(t.end.c_str(), end.c_str());
	}

	TASK_TYPE		type;	// 任务类型
	unsigned int	rescid;	// 任务地点
	
	string			begin;	// 开始时间
	string			end;	// 结束时间
};

// 静态目标
struct StaticTarget
{	
	unsigned int	id;			// 目标ID
	EnObjType		objtype;	// 目标类型
	TASK_TYPE		tasktype;	// 任务类型
	bool			common;		// 是否常显
	string			name;		// 目标名称
	string			begin;		// 开始时间
	string			end;		// 结束时间

	SimGeoPoint		geop;		// 位置
	double			head;		// 方位：° 正北顺时针
};


// 实体对象：动态目标
struct DynamicTarget 
{
	DynamicTarget()
	{
		id			= UNVALID_ID;
		bcid		= UNVALID_ID;
		locateid	= UNVALID_ID;
		taskptid	= UNVALID_ID;
		objtype		= OBJ_MILITIA;
		tasktype	= TASK_COUNT;
		begin		= "";
		end			= "";
	}
	unsigned int	id;			// 目标ID
	unsigned int	bcid;		// 编成ID
	unsigned int	locateid;	// 集结地id
	unsigned int	taskptid;	// 任务地id
	EnObjType		objtype;	// 目标类型
	TASK_TYPE		tasktype;	// 任务类型

	string			begin;		// 开始时间
	string			end;		// 结束时间
	
	vector<SinglePath> multipath;	// 多段轨迹
};

#endif //SCENARIO_DEF
/*
* 所有仿真引擎端数据结构定义
* d00019 20211008
*/
#ifndef GLOBAL_DEF
#define GLOBAL_DEF

#pragma pack(push,1)
#pragma execution_character_set("utf-8")

//#include <iostream>
#include <QString>

#define NAME_MAX_LEN 100
#define DESCRIPT_TXT_MAX_LEN 200


// 消息最大长度
#define MAX_MSG_LEN 1000

// 视点结构最大长度
#define MAX_VIEW_LEN 300

// 消息类型 
enum MsgType
{
	SimInfoMsg = 0,	// 想定信息	
	InitSimMsg,		// 仿真初始化
	TimeCommandMsg,	// 时间信息
	SimFinishMsg,	// 仿真结束

	EnventMsg,		// 事件信息
	ScreenWordMsg,	// 字幕消息	

	ViewMsg,		// 视点信息
	DestoryMsg,		// 销毁命令	

	NewEntityMsg,	// 新建实体	
	EntityStuMsg,	// 实体状态	
	DetecTargetMsg,	// 跟踪目标

	CommnMsg,		// 通信信息
	GuideMsg,		// 引导信息
	GuardMsg,		// 警戒信息
	TaskMsg,		// 任务信息
	// l00293
	BranchLineMsg,  // 民兵分支路线信息
	MeetingMsg,		// 会议信息
	ActMsg,			// 行动信息
	
	TroopMsg,		// 部队实时动态
	OilMsg,			// 加油实时信息
};

// 想定类型
enum SCN_TYPE
{
	SCN_BJHL = 0,		// 保交护路
	SCN_MBFH = 1,		// 目标防护
};

// 任务类型
enum TASK_TYPE
{
	TASK_PREPARE	= 0,// 准备
	TASK_TRAFFIC	= 1,// 交通
	TASK_OIL		= 2,// 加油
	TASK_MAINTAIN	= 3,// 维修
	TASK_HOSPITAL	= 4,// 医疗
	TASK_CAMP		= 5,// 宿营
	TASK_CONFORT	= 6,// 慰问
	TASK_FEED		= 7,// 饮食
	TASK_SUMMARY	= 8,// 复盘
	TASK_HIDE		= 9,// 隐藏
	TASK_ALL		= 10,// 总览
	TASK_COUNT,
};

// 场景对象
// 1-部队 2-民兵车队 3-站岗民兵 4-加油站 5-医疗点 6-宿营点 7-饮食点 8-车辆维修点 9-一级指挥所 10-二级指挥所
// 11-三级指挥所 12-爆炸点 13-引导民兵 14-维修车辆 15-维修车辆-拖车 16-出口 17-入口 18-桥梁
enum EnObjType
{
	OBJ_TROOP = 1,
	OBJ_MILITIA = 2,
	OBJ_SOLDIER = 3,
	OBJ_GASSTATION = 4,
	OBJ_HOSPITAL = 5,
	OBJ_CAMP = 6,
	OBJ_FEED = 7,
	OBJ_MAINTAIN = 8,
	OBJ_FIRST = 9,
	OBJ_SECOND = 10,
	OBJ_THIRD = 11,
	OBJ_BOOM = 12,
	OBJ_SOLDIER_DIRECTION = 13,
	OBJ_MILITIA_REPAIR = 14,
	OBJ_MILITIA_REPAIR_CAR = 15,
	OBJ_EXIT = 16,
	OBJ_ENTRY = 17,
	OBJ_BRIDGE = 18,
};

// 窗口类型
enum WINDOW_TYPE		
{
	MAINUI_SCNSELECT,	// 方案选择窗口：_planWgt
	MAINUI_SCNINFO,		// 想定信息窗口：_scenarioWgt
	MAINUI_TOP,			// 主界面上窗口：_topWidget
	MAINUI_BOTTOM,		// 主界面下窗口：_bottomWidget
	MAINUI_SCREEN,		// 顶部屏幕播报：_screenWordWgt
	MAINUI_TASKFLOW,	// 任务流程窗口：_taskflowWgt
	MAINUI_LEGEND,		// 左下图例窗口：_legengWgt
	MAINUI_BROADCAST,	// 任务信息播报：_periodTips
	MAINUI_TROOPINFO,	// 底部部队信息：_troopScrollWgt
	MAINUI_TEST,		// 调式测试窗口：_testWgt

	TRANSIT_PREPARE_HIGHWAY,	// 高速公路信息：_highwayInfo
	TRANSIT_PREPARE_RESOURCE,	// 动员资源信息：_preModelWgt
	TRANSIT_PREPARE_SURVEY,		// 过境调研信息：_preTroopsInfo
	TRANSIT_PREPARE_MILITIA,	// 民兵动员预案：_proTroopsInfo
	TRANSIT_PREPARE_TROOP,		// 过境部队信息：_troopsWgt
	TRANSIT_PREPARE_DECISION,	// 会议决议信息：_decesionTable
	TRANSIT_TRAFFIC_CONTROL,	// 交通管制窗口：_trafficControl
	TRANSIT_CATER_TASKINFO,		// 热食保障任务：_feedInfoWgt
	TRANSIT_CATER_PROCEED,		// 热食保障进行：_feedSelectedInfo
	TRANSIT_OIL_TASKINFO,		// 油料补给任务：_oilDemandWgt
	TRANSIT_OIL_PROCEED,		// 油料补给执行：_oilWgt
	TRANSIT_MAINTAIN_INFO,		// 车辆维修窗口：_maintenance
	TRANSIT_TREATMENT_INFO,		// 医疗救护窗口：_cillInfo
	TRANSIT_CAMP_TASKINFO,		// 宿营保障任务：_campingSite
	TRANSIT_CAMP_PROCEED,		// 宿营保障执行：_campingInfo
};

// 消息头
struct MsgHead
{
	// 消息类型
	MsgType type;
	// 数据区长度
	unsigned dataLen;
	// 
	double dTime;
};

// 消息结构
struct ComMsg
{
	MsgHead msgHead;
	char data[MAX_MSG_LEN];
};



// 想定信息
struct SimInfo
{
	SimInfo()
	{
		dTime = 0;
		// 参考时间
		dPreferTime = 0;
		// 仿真总共时长
		dSimTimeLen = 0;
		// 实际总共时长
		dRealTimeLen = 0;

		// 场景名称
		memset(chBattleName, 0, DESCRIPT_TXT_MAX_LEN);
	}

	~SimInfo() {}


	double dTime;
	// 参考时间
	double dPreferTime;
	// 仿真总共时长
	double dSimTimeLen;
	// 实际总共时长
	double dRealTimeLen;
	// 场景名称
	char chBattleName[DESCRIPT_TXT_MAX_LEN];
};

// 心跳包
struct TimeMsg
{
	double dTime;
};



// 新建实体
struct NewEntity
{
	NewEntity()
	{
		dTime = 0;
		// 上级ID 通信指挥关系
		parentId = 0;
		// 自身ID
		nEntityID = 0;
		// 实体名称
		memset(cName, 0, NAME_MAX_LEN);
		// 实体类型
		enobjType = EnObjType::OBJ_TROOP;
		// 静态对象
		bStatic = true;
		// 默认非常显
		bCommon = false;
		// 任务类型
		taskType = TASK_ALL;

		// 实体初始姿态
		// 偏航、俯仰、横滚
		dAzAngle = 0;
		dPicthAngle = 0;
		dRolAngle = 0;

		// 实体初始位置
		// 经纬高-度
		dLon = 0;
		dLat = 0;
		dAlt = 0;
	}

	~NewEntity() {}

	double dTime;
	
	int parentId;				// 上级ID 通信指挥关系	
	int nEntityID;				// 自身ID	
	char cName[NAME_MAX_LEN];	// 实体名称	
	bool bStatic;				// 是否为静态对象
	bool bCommon;				// 是否为常显对象
	EnObjType enobjType;		// 实体类型
	// l00293增加任务类型属性
	TASK_TYPE taskType;			// 任务类型

	// 实体初始姿态: 偏航、俯仰、横滚
	double dAzAngle;
	double dPicthAngle;
	double dRolAngle;

	// 实体初始位置:经纬高-度米
	double dLon;
	double dLat;
	double dAlt;
};


// 状态实时位置姿态
struct EntityStu
{
	EntityStu()
	{
		dTime = 0;
		// 实体ID
		nEntityID = 0;
		// 任务类型
		taskType = TASK_ALL;
		// 姿态
		dAzAngle = 0;
		dPicthAngle = 0;
		dRolAngle = 0;

		// 方位
		dLon = 0;
		dLat = 0;
		dAlt = 0;
	}

	~EntityStu() {}


	double dTime;

	// 实体ID
	int nEntityID;

	// 所属任务类型
	TASK_TYPE taskType;

	// 姿态
	double dAzAngle;

	double dPicthAngle;

	double dRolAngle;

	// 方位
	double dLon;

	double dLat;

	double dAlt;
};

// 销毁
// 同时支持实体闪烁开启关闭、高亮常态切换
// 0-删除实体 1-开启闪烁 2-关闭闪烁 3-开启高亮 4-关闭高亮
struct DestoryCommand
{
	DestoryCommand()
	{
		dTime = 0;
		nEntityID = 0;
		nmod = 0;
	}

	~DestoryCommand()
	{
		dTime = 0;
	}

	double dTime;
	int nEntityID;
	int nmod;
};

// 事件命令
struct EventCommand
{
	EventCommand()
	{
		dTime = 0;
		enType = TASK_COUNT;
		memset(chDescript, 0, DESCRIPT_TXT_MAX_LEN);
	}

	~EventCommand() {}

	double dTime;
	TASK_TYPE enType;
	int flowIndex;
	char chDescript[DESCRIPT_TXT_MAX_LEN];
	int	   messageType;
};

// 字幕消息
struct ScreenWordInfo
{
	ScreenWordInfo()
	{
		dTime = 0;
		memset(chMsg, 0, DESCRIPT_TXT_MAX_LEN);
	}

	~ScreenWordInfo() {}

	double dTime;
	char chMsg[DESCRIPT_TXT_MAX_LEN];
	TASK_TYPE type;
};


// 视点信息 
// 定位
struct ViewLocatCmd
{
	ViewLocatCmd()
	{
		dTimeLen = 0;
		// 参数focal_point：焦点（指向点），使用map的SRS或参数指定的SRC
		dFocalLon = 0;
		dFocalLat = 0;
		dFocalAlt = 0;

		// 航向角（Heading，顺时针方向，单位度)，相机相对于焦点所在的切平面
		dHeading = 0;
		// 俯仰角（Pitch，单位度 ），相机相对于焦点所在的切平面
		dPitch = 0;
		//从相机到指向点（焦点）的直线距离
		dRange = 0;
	}

	~ViewLocatCmd() {}

	// 参数focal_point：焦点（指向点），使用map的SRS或参数指定的SRC
	double dFocalLon;
	double dFocalLat;
	double dFocalAlt;

	// 航向角（Heading，顺时针方向，单位度)，相机相对于焦点所在的切平面
	double dHeading;
	// 俯仰角（Pitch，单位度 ），相机相对于焦点所在的切平面
	double dPitch;
	//从相机到指向点（焦点）的直线距离
	double dRange;

	// 时长-- s 
	double dTimeLen;
};

// 凝视
struct PeerView
{
	PeerView()
	{
		// 视点位置
		dFocalLon = 0;
		dFocalLat = 0;
		dFocalAlt = 0;

		// 凝视实体 
		nEntityId = 0;
	}

	// 视点位置
	double dFocalLon;
	double dFocalLat;
	double dFocalAlt;
	
	// 凝视实体 
	int nEntityId;
};

// 谁看谁
struct PeerE2TView
{
	PeerE2TView()
	{
		// 
		nEntitId = 0;
		// 
		nTargetId = 0;
	}
	 // 
	int nEntitId;
	// 
	int nTargetId;
};

// 跟踪类型
enum EnTrackType
{
	// 只跟踪位置 
	EN_TRACK_POSTION = 1,

	// 跟踪位置姿态
	EN_TRACK_POSTURE_POSTION = 2,

	// 跟踪速度
	EN_TRACK_SPEED = 3,

};

// 视点跟踪
struct TracView
{
	TracView()
	{
		// 只跟踪位置 位置姿态 速度跟踪
		enTrackType =EN_TRACK_POSTION;
		nTargetId = 0;
		// 俯仰角
		dPitch = 0;
		// 偏航
		dAngle = 0;
		// 距离
		dDis = 0;
	}

	// 只跟踪位置 位置姿态 速度跟踪
	EnTrackType enTrackType;
	int nTargetId;
	// 俯仰角
	double dPitch;
	// 偏航
	double dAngle;
	// 距离
	double dDis;
};

// 漫游视点
struct TraveView
{
	TraveView()
	{
		// 视点位置 // 单位均为度
		dFocalLon = 0;
		dFocalLat = 0;
		dFocalAlt = 0;
		dHeading = 0;
		dPitch = 0;
		dRoll = 0;

		dFocalLon1 = 0;
		dFocalLat1 = 0;
		dFocalAlt1 = 0;
		dHeading1 = 0;
		dPitch1 = 0;
		dRoll1 = 0;

		// 时长
		dLenTime = 0;
	}
	// 视点位置 // 单位均为度
	double dFocalLon;
	double dFocalLat;
	double dFocalAlt;
	double dHeading;
	double dPitch;
	double dRoll;

	double dFocalLon1;
	double dFocalLat1;
	double dFocalAlt1;
	double dHeading1;
	double dPitch1;
	double dRoll1;

	// 时长
	double dLenTime;
};

// 漫游视点
struct TraveTargetView
{
	TraveTargetView()
	{
		// 
		// 视点位置
		dFocalLon = 0;
		dFocalLat = 0;
		dFocalAlt = 0;

		dFocalLon1 = 0;
		dFocalLat1 = 0;
		dFocalAlt1 = 0;

		nTargetId = 0;
		// 时长
		dLenTime = 0; 
	}
	// 
	// 视点位置
	double dFocalLon;
	double dFocalLat;
	double dFocalAlt;

	double dFocalLon1;
	double dFocalLat1;
	double dFocalAlt1;

	int nTargetId;
	// 时长
	double dLenTime;
};

// 视点类型
enum EnViewType
{
	// 视点定位
	EN_LOCAT_VIEW = 1,
	// 视点凝视
	EN_PEER_VIEW = 2,
	// 对看视点
	EN_PEERE2T_VIEW = 3,
	// 视点跟踪
	EN_TRACK_VIEW = 4,
	// 漫游视点
	EN_TRAVE_VIEW = 5,
	// 漫游目标
	EN_TRAVETARGET_VIEW = 6

};

struct ViewInfoMsg
{

	ViewInfoMsg()
	{
		dTime = 0;
		enViewType = EN_LOCAT_VIEW;
		memset(chMsg,0,MAX_VIEW_LEN);
	}

	double dTime;

	EnViewType enViewType;

	TASK_TYPE taskType;

	bool sceneType;		// true-3d false-2d

	char chMsg[MAX_VIEW_LEN];

};


#pragma pack(pop)
#endif //GLOBAL_DEF

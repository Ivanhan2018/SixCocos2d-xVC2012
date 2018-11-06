#ifndef STRUCT_HEAD_FILE
#define STRUCT_HEAD_FILE

#include "Packet.h"

#pragma pack(1)

//////////////////////////////////////////////////////////////////////////////////
//游戏列表

//游戏类型
struct tagGameType
{
	_WORD_							wJoinID;							//挂接索引
	_WORD_							wSortID;							//排序索引
	_WORD_							wTypeID;							//类型索引
	_TCHAR_							szTypeName[LEN_TYPE];				//种类名字
};

//游戏种类
struct tagGameKind
{
	unsigned short							wTypeID;							//类型索引
	unsigned short							wJoinID;							//挂接索引
	unsigned short							wSortID;							//排序索引
	unsigned short							wKindID;							//类型索引
	unsigned short							wGameID;							//模块索引
	unsigned int							dwOnLineCount;						//在线人数
	unsigned int							dwFullCount;						//满员人数
	bool							bInsetShortCut;						//是否加入快捷入口
	unsigned char							cbMachineType;						//机器类型 0x01 pc 0x02 手机 0x04页游
    unsigned char                             persect1;                          //补充字符
    unsigned char                             persect2;                          //补充字符
    unsigned char                             persect3;                          //补充字符
	_TCHAR_							szKindName[LEN_KIND];				//游戏名字
	_TCHAR_							szProcessName[LEN_PROCESS];			//进程名字
};

//游戏节点
struct tagGameNode
{
	_WORD_							wKindID;							//名称索引
	_WORD_							wJoinID;							//挂接索引
	_WORD_							wSortID;							//排序索引
	_WORD_							wNodeID;							//节点索引
	_TCHAR_							szNodeName[LEN_NODE];				//节点名称
};

//定制类型
struct tagGamePage
{
	_WORD_							wPageID;							//页面索引
	_WORD_							wKindID;							//名称索引
	_WORD_							wNodeID;							//节点索引
	_WORD_							wSortID;							//排序索引
	_WORD_							wOperateType;						//控制类型
	_TCHAR_							szDisplayName[LEN_PAGE];			//显示名称
};

//游戏房间
struct tagGameServer
{
	_WORD_							wKindID;							//名称索引
	_WORD_							wNodeID;							//节点索引
	_WORD_							wSortID;							//排序索引
	_WORD_							wServerID;							//房间索引
	_WORD_							wServerPort;						//房间端口
	_D_WORD_							dwOnLineCount;						//在线人数
	_D_WORD_							dwFullCount;						//满员人数
	_TCHAR_							szServerAddr[LEN_SERVER];					//房间地址
	_TCHAR_							szServerName[LEN_SERVER];			//房间名称
};
// add by pys(比赛界面)
struct tagGameMatchBaseInfo
{
	_D_WORD_							dwServerID;							// 服务器ID
	_WORD_							wKindID;							// 游戏ID
	_TCHAR_							szServerName[32];					// 比赛名称
	_TCHAR_							szStartType[64];					// 开赛方式
	SCORE							lFeeScore;							// 报名金币
	_D_WORD_							dwFeeItemID;						// 报名物品ID
	_WORD_							wTypeBit;							// 比赛类型
	unsigned int						crTitle;							// 标题颜色
};
struct tagGameMatchSeverID
{
	_D_WORD_							dwServerID;							// 服务器ID
};
//add by xhg(比赛人数信息)
struct tagGameMatchViewInfo
{
	_D_WORD_							dwMatchID;							//比赛ID
	_D_WORD_							dwServerID;							//服务器ID
	_WORD_							wSignUpCount;						//报名人数
};
//获奖信息
struct tagGameMatchAward
{
	_TCHAR_							szNickInfo[64];						//获奖信息
};
// add by pys(快捷方式)
// 快捷方式
struct tagShortCutInfo
{
	_WORD_							wServerID;							// 房间ID
	_WORD_							wShortCutNum;						// 快捷号
	_BYTE_							bMatch;								// 是否为比赛
};

// add by pys（短信系统）
// 短信信息
struct tagShortMsgInfo
{
	_BYTE_							bState;								//短信状态
	_TCHAR_							strSenderName[50];					//发件人
	_TCHAR_							strInfo[100];						//内容
	_MY_SYSTEMTIME					tSendTime;							//发件时间
	_TCHAR_							UrlAddress[64];						//链接地址
	_TCHAR_							UrlName[32];						//链接名称
	_TCHAR_							MsgTitle[32];						//消息标题
	int								cbMsgId;							//消息ID
};

// 人数状态
struct tagUserCountState
{
	_D_WORD_							wServerID;							// 房间ID
	_WORD_							wRegion1;							// 区域1
	_WORD_							wRegion2;							// 区域2
	_WORD_							wRegion3;							// 区域3
};

//视频配置
struct tagAVServerOption
{
	_WORD_							wAVServerPort;						//视频端口
	_D_WORD_							dwAVServerAddr;						//视频地址
};

//在线信息
struct tagOnLineInfoKind
{
	_WORD_							wKindID;							//类型标识
	_D_WORD_							dwOnLineCount;						//在线人数
};

//在线信息
struct tagOnLineInfoServer
{
	_WORD_							wServerID;							//房间标识
	_D_WORD_							dwOnLineCount;						//在线人数
};

//////////////////////////////////////////////////////////////////////////////////
//用户信息

//桌子状态
struct tagTableStatus
{
	_BYTE_							cbTableLock;						//锁定标志
	_BYTE_							cbPlayStatus;						//游戏标志
	long							cbAddScore;							//桌子低分
};

//用户状态
struct tagUserStatus
{
	_WORD_							wTableID;							//桌子索引
	_WORD_							wChairID;							//椅子位置
	_BYTE_							cbUserStatus;						//用户状态
};

//用户属性
struct tagUserAttrib
{
	_BYTE_							cbCompanion;						//用户关系
};

//用户积分
struct tagUserScore
{
	//积分信息
	SCORE							lScore;								//用户分数
	SCORE							lGrade;								//用户成绩
	SCORE							lInsure;							//用户银行
	SCORE							lGameScore;							//游戏积分

	//输赢信息
	_D_WORD_							dwWinCount;							//胜利盘数
	_D_WORD_							dwLostCount;						//失败盘数
	_D_WORD_							dwDrawCount;						//和局盘数
	_D_WORD_							dwFleeCount;						//逃跑盘数

	//全局信息
	_D_WORD_							dwUserMedal;						//用户奖牌
	_D_WORD_							dwExperience;						//用户经验
	long							lLoveLiness;						//用户魅力
	
	//SCORE							lotherScore;						//另外的豆豆					
};

//用户积分
struct tagMobileUserScore
{
	//积分信息
	SCORE							lScore;								//用户分数

	//输赢信息
	_D_WORD_							dwWinCount;							//胜利盘数
	_D_WORD_							dwLostCount;						//失败盘数
	_D_WORD_							dwDrawCount;						//和局盘数
	_D_WORD_							dwFleeCount;						//逃跑盘数

	//全局信息
	_D_WORD_							dwExperience;						//用户经验
};


//道具使用
struct tagUsePropertyInfo
{
	_WORD_                            wPropertyCount;                     //道具数目
	_WORD_                            dwValidNum;						    //有效数字
	_D_WORD_                           dwEffectTime;                       //生效时间
};


//用户道具
struct tagUserProperty
{
	_WORD_                            wPropertyUseMark;                   //道具标示
	tagUsePropertyInfo              PropertyInfo[MAX_PT_MARK];			//使用信息   
};

//道具包裹
struct tagPropertyPackage
{
	_WORD_                            wTrumpetCount;                     //小喇叭数
	_WORD_                            wTyphonCount;                      //大喇叭数
};

//用户信息
struct tagUserInfo
{
	//基本属性
	unsigned int							dwUserID;							//用户 I D
	unsigned int							dwGameID;							//游戏 I D
	unsigned int							dwGroupID;							//社团 I D
	_TCHAR_							szNickName[LEN_NICKNAME];			//用户昵称
	_TCHAR_							szGroupName[LEN_GROUP_NAME];		//社团名字
	_TCHAR_							szUnderWrite[LEN_UNDER_WRITE];		//个性签名
    
	//头像信息
	unsigned short							wFaceID;							//头像索引
	unsigned int							dwCustomID;							//自定标识
    
	//用户资料
	unsigned char							cbGender;							//用户性别
	unsigned char							cbMemberOrder;						//会员等级
    unsigned char							cbMasterOrder;						//管理等级
	// add by pys (奖励系统)
	unsigned int							dwSpreaderID;						//推荐人ID
    
	//用户状态
	unsigned short							wTableID;							//桌子索引
	unsigned short							wChairID;							//椅子索引
	unsigned char							cbUserStatus;						//用户状态
    
	//积分信息
	SCORE							lScore;								//用户分数
	SCORE							lGrade;								//用户成绩
	SCORE							lInsure;							//用户银行
	SCORE							lGameScore;							//游戏积分
    
	//游戏信息
	unsigned int							dwWinCount;							//胜利盘数
	unsigned int							dwLostCount;						//失败盘数
	unsigned int							dwDrawCount;						//和局盘数
	unsigned int							dwFleeCount;						//逃跑盘数
	unsigned int							dwUserMedal;						//用户奖牌
	unsigned int							dwExperience;						//用户经验
	int							lLoveLiness;						//用户魅力
    
	SCORE							lOtherScore;						//用户另外携带的积分
	bool							bisneedconvert;						//是否需要兑换
    
};

struct tagUserMatchExInfo
{
	unsigned int							dwMatchNo;							//比赛编号
	unsigned int							dwGameCount;						//游戏次数
	unsigned int							dwPersonRank;						//个人排名
};

//用户信息
struct tagUserInfoHead
{
	//用户属性
	unsigned int							dwGameID;							//游戏 I D
	unsigned int							dwUserID;							//用户 I D
	unsigned int							dwGroupID;							//社团I D
    
	//头像信息
	unsigned short							wFaceID;							//头像索引
	unsigned int							dwCustomID;							//自定标识
    
	//用户属性
	unsigned char							cbGender;							//用户性别
	unsigned char							cbMemberOrder;						//会员等级
	unsigned char							cbMasterOrder;						//管理等级
    
	//用户状态
	unsigned short							wTableID;							//桌子索引
	unsigned short							wChairID;							//椅子索引
	unsigned char							cbUserStatus;						//用户状态
    
	//积分信息
	SCORE							lScore;								//用户分数
	SCORE							lGameScore;							//游戏积分
	SCORE							lGrade;                             //用户成绩
	SCORE							lInsure;							//用户银行
    
	//游戏信息
	unsigned int							dwWinCount;							//胜利盘数
	unsigned int							dwLostCount;						//失败盘数
	unsigned int							dwDrawCount;						//和局盘数
	unsigned int							dwFleeCount;						//逃跑盘数
	unsigned int							dwUserMedal;						//用户奖牌
	unsigned int							dwExperience;						//用户经验
	int							lLoveLiness;						//用户魅力
    
    int							lUserLoves;							//爱心值
	tagUserMatchExInfo				UserMatchExInfo;					//比赛属性
};


//头像信息
struct tagCustomFaceInfo
{
	_D_WORD_							dwDataSize;							//数据大小
	_D_WORD_							dwCustomFace[FACE_CX*FACE_CY];		//图片信息
};

//用户信息
struct tagUserRemoteInfo
{
	//用户信息
	_D_WORD_							dwUserID;							//用户标识
	_D_WORD_							dwGameID;							//游戏标识
	_TCHAR_                             szNickName[LEN_NICKNAME];			//用户昵称

	//等级信息
	_BYTE_                              cbGender;							//用户性别
	_BYTE_                              cbMemberOrder;						//会员等级
	_BYTE_                              cbMasterOrder;						//管理等级

	//位置信息
	_WORD_                              wKindID;							//类型标识
	_WORD_                              wServerID;							//房间标识
	_TCHAR_                             szGameServer[LEN_SERVER];			//房间位置
};

//////////////////////////////////////////////////////////////////////////////////

//广场子项
struct tagGamePlaza
{
	_WORD_                              wPlazaID;							//广场标识
	_TCHAR_                             szServerAddr[32];					//服务地址
	_TCHAR_                             szServerName[32];					//服务器名
};

//级别子项
struct tagLevelItem
{
	long                                lLevelScore;						//级别积分
	_TCHAR_                             szLevelName[16];					//级别描述
};

//会员子项
struct tagMemberItem
{
	_BYTE_                              cbMemberOrder;						//等级标识
	_TCHAR_                             szMemberName[16];					//等级名字
};

//管理子项
struct tagMasterItem
{
	_BYTE_							cbMasterOrder;						//等级标识
	_TCHAR_							szMasterName[16];					//等级名字
};

//列表子项
struct tagColumnItem
{
	_BYTE_							cbColumnWidth;						//列表宽度
	_BYTE_							cbDataDescribe;						//字段类型
	_TCHAR_							szColumnName[16];					//列表名字
};

//地址信息
struct tagAddressInfo
{
	_TCHAR_							szAddress[32];						//服务地址
};

//数据信息
struct tagDataBaseParameter
{
	_WORD_							wDataBasePort;						//数据库端口
	_TCHAR_							szDataBaseAddr[32];					//数据库地址
	_TCHAR_							szDataBaseUser[32];					//数据库用户
	_TCHAR_							szDataBasePass[32];					//数据库密码
	_TCHAR_							szDataBaseName[32];					//数据库名字
};

// 比赛报名信息
struct tagMatchSignUpInfo
{
	_D_WORD_							dwUserID;							// 用户ID
	_D_WORD_							dwMatchID;							// 比赛ID
	_WORD_							wServerID;							// 房间ID
	_MY_SYSTEMTIME						tMatchDate;							// 开赛时间
};


//房间配置
struct tagServerOptionInfo
{
	//挂接属性
	_WORD_							wKindID;							//挂接类型
	_WORD_							wNodeID;							//挂接节点
	_WORD_							wSortID;							//排列标识

	//税收配置
	_WORD_							wRevenueRatio;						//税收比例
	SCORE							lServiceScore;						//服务费用
	//add by pys(积分系统)
	_WORD_							wScoreRevenue;						//金币积分比率

	//房间配置
	SCORE							lRestrictScore;						//限制积分
	SCORE							lMinTableScore;						//最低积分
	SCORE							lMinEnterScore;						//最低积分
	SCORE							lMaxEnterScore;						//最高积分

	//会员限制
	_BYTE_							cbMinEnterMember;					//最低会员
	_BYTE_							cbMaxEnterMember;					//最高会员

	//房间属性
	_D_WORD_							dwServerRule;						//房间规则
	_TCHAR_							szServerName[LEN_SERVER];			//房间名称
};

//用户信息
struct tagMobileUserInfoHead
{
	//用户属性
	_D_WORD_							dwGameID;							//游戏 I D
	_D_WORD_							dwUserID;							//用户 I D

	//头像信息
	_WORD_							wFaceID;							//头像索引
	_D_WORD_							dwCustomID;							//自定标识

	//用户属性
	_BYTE_							cbGender;							//用户性别
	_BYTE_							cbMemberOrder;						//会员等级

	//用户状态
	_WORD_							wTableID;							//桌子索引
	_WORD_							wChairID;							//椅子索引
	_BYTE_							cbUserStatus;						//用户状态

	//积分信息
	SCORE							lScore;								//用户分数

	//游戏信息
	_D_WORD_							dwWinCount;							//胜利盘数
	_D_WORD_							dwLostCount;						//失败盘数
	_D_WORD_							dwDrawCount;						//和局盘数
	_D_WORD_							dwFleeCount;						//逃跑盘数
	_D_WORD_							dwExperience;						//用户经验
};
//////////////////////////////////////////////////////////////////////////////////




#pragma pack()

#endif
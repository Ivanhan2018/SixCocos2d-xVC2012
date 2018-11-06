//
//  CMD_LOGONSERVER.h
//  NetTest
//
//  Created by XXY on 13-8-10.
//
//

#ifndef NetTest_CMD_LOGONSERVER_h
#define NetTest_CMD_LOGONSERVER_h
#include "Define.h"
#include "Packet.h"
#include "Struct.h"
#pragma pack(1)

//////////////////////////////////////////////////////////////////////////////////
//登录命令

#define MDM_GP_LOGON				1									//广场登录

//登录模式
#define SUB_GP_LOGON_GAMEID			1									//I D 登录
#define SUB_GP_LOGON_ACCOUNTS		2									//帐号登录
#define SUB_GP_REGISTER_ACCOUNTS	3									//注册帐号

//登录结果
#define SUB_GP_LOGON_SUCCESS		100									//登录成功
#define SUB_GP_LOGON_FAILURE		101									//登录失败
#define SUB_GP_LOGON_FINISH			102									//登录完成
#define SUB_GP_VALIDATE_MBCARD      103                                 //登录失败
#define SUB_GP_SHOW_PERFECTDLG      104                                 //显示完善对话框

// add by pys(定时比赛系统)
#define SUB_GP_S_SIGNUP_INFO		150									//报名信息

#define SUB_GP_S_PLAYER_COUNT_STATE_INFO 151							//房间人数状态

#define SUB_GP_S_USERBAG_INFO		180									//背包信息
//升级提示
#define SUB_GP_UPDATE_NOTIFY		200									//升级提示
//防沉迷提示
#define SUB_GP_PREVENT_NOTIFY		201									//防沉迷提示
//////////////////////////////////////////////////////////////////////////////////

//


struct CMD_GP_LogonGameID
{
	//系统信息
	_D_WORD_							dwPlazaVersion;						//广场版本
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
    
	//登录信息
	_D_WORD_							dwGameID;							//游戏 I D
	_TCHAR_							szPassword[LEN_MD5];				//登录密码
	_BYTE_							cbNeeValidateMBCard;			    //密保校验
};


//帐号登录
struct CMD_GP_LogonAccounts
{
	//系统信息
	_D_WORD_						dwPlazaVersion;						//广场版本
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
    
	//登录信息
	_TCHAR_							szPassword[LEN_MD5];				//登录密码
	_TCHAR_							szAccounts[LEN_ACCOUNTS];			//登录帐号
	_BYTE_							cbNeeValidateMBCard;			    //密保校验
    _BYTE_                              persecet1;                        //补充字段
    _BYTE_                              persecet2;                        //补充字段
    _BYTE_						      cbLoginType;                       //登录类型（0 PC端， 1 手机端, 2 页游端）
};


//注册帐号
struct CMD_GP_RegisterAccounts
{
	//系统信息
	_D_WORD_							dwPlazaVersion;						//广场版本
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
    
	//密码变量
	_TCHAR_							szLogonPass[LEN_MD5];				//登录密码
	_TCHAR_							szInsurePass[LEN_MD5];				//银行密码
    
	//注册信息
	_WORD_							wFaceID;							//头像标识
	_BYTE_							cbGender;							//用户性别
	_TCHAR_							szAccounts[LEN_ACCOUNTS];			//登录帐号
	_TCHAR_							szNickName[LEN_NICKNAME];			//用户昵称
	_TCHAR_							szSpreader[LEN_ACCOUNTS];			//推荐帐号
	_TCHAR_							szPassPortID[LEN_PASS_PORT_ID];		//证件号码
	_TCHAR_							szCompellation[LEN_COMPELLATION];	//真实名字
};

//登录成功
struct CMD_GP_LogonSuccess
{
	//属性资料
	_WORD_							wFaceID;							//头像标识
	_DWORD_							dwUserID;							//用户 I D
	_DWORD_							dwGameID;							//游戏 I D
	_DWORD_							dwGroupID;							//社团标识
	_DWORD_							dwCustomID;							//自定标识
	_DWORD_							dwUserMedal;						//用户奖牌
	_DWORD_							dwExperience;						//经验数值
	_DWORD_							dwLoveLiness;						//用户魅力
    
	bool							bBankPassWrodIsNull;				//银行密码是否为空
    
	//用户成绩
	SCORE							lUserScore;							//用户金币
	SCORE                           lUserInsure;						//用户银行
    
	//用户信息
	_BYTE_							cbGender;							//用户性别
	_BYTE_							cbMoorMachine;						//锁定机器
	_TCHAR_							szAccounts[LEN_ACCOUNTS];			//登录帐号
	_TCHAR_							szNickName[LEN_ACCOUNTS];			//用户昵称
	_TCHAR_							szGroupName[LEN_GROUP_NAME];		//社团名字
	//配置信息
	_BYTE_                            cbShowServerStatus;                 //显示服务器状态
};

struct CMD_GP_UserPropertyInfo
{
	//背包信息
	tagUserPropertyInfoAttrib	    UserPropertyInfoAttrib[MAX_PROPERTY/2];
};
//登录失败
struct CMD_GP_LogonFailure
{
	long							lResultCode;						//错误代码
	_TCHAR_							szDescribeString[128];				//描述消息
};

struct CMD_GP_SignUpInfo
{
	_D_WORD_							dwServerID;						//房间ID
	//time_t							lTime;							//开赛时间
};


//登陆完成
struct CMD_GP_LogonFinish
{
	_WORD_							wIntermitTime;						//中断时间
	_WORD_							wOnLineCountTime;					//更新时间
	tagShortCutInfo					tagShorCutInfo[12];					//快捷方式
};

//登录失败
struct CMD_GP_ValidateMBCard
{
	_UINT_								uMBCardID;						//机器序列
};

//升级提示
struct CMD_GP_UpdateNotify
{
	_BYTE_							cbMustUpdate;						//强行升级
	_BYTE_							cbAdviceUpdate;						//建议升级
	_D_WORD_							dwCurrentVersion;					//当前版本
};

//////////////////////////////////////////////////////////////////////////////////
//携带信息 CMD_GP_LogonSuccess

#define DTP_GP_GROUP_INFO			1									//社团信息
#define DTP_GP_MEMBER_INFO			2									//会员信息
#define	DTP_GP_UNDER_WRITE			3									//个性签名
#define DTP_GP_STATION_URL			4									//主页信息

//社团信息
struct DTP_GP_GroupInfo
{
	_D_WORD_							dwGroupID;							//社团索引
	_TCHAR_							szGroupName[LEN_GROUP_NAME];		//社团名字
};

//会员信息
struct DTP_GP_MemberInfo
{
	_BYTE_							cbMemberOrder;						//会员等级
	_MY_SYSTEMTIME						MemberOverDate;						//到期时间
};

//////////////////////////////////////////////////////////////////////////////////
//列表命令

#define MDM_GP_SERVER_LIST			2									//列表信息

//获取命令
#define SUB_GP_GET_LIST				1									//获取列表
#define SUB_GP_GET_SERVER			2									//获取房间
#define SUB_GP_GET_ONLINE			3									//获取在线
#define SUB_GP_GET_COLLECTION		4									//获取收藏
#define SUB_GP_GET_SHORTCUT			5									//获取快捷

//列表信息
#define SUB_GP_LIST_TYPE			100									//类型列表
#define SUB_GP_LIST_KIND			101									//种类列表
#define SUB_GP_LIST_NODE			102									//节点列表
#define SUB_GP_LIST_PAGE			103									//定制列表
#define SUB_GP_LIST_SERVER			104									//房间列表
#define SUB_GP_VIDEO_OPTION			105									//视频配置
#define SUB_GP_MATCH_LIST			108									//比赛列表
//add by pys(快捷方式)
#define	SUB_GP_SHORTCUT				106									//快捷方式
#define SUB_GP_VIPGIFT				107									//VIP每日奖励

struct tagVipDailyGift
{
	bool							bInit;
	SCORE						    llScore;
	_TCHAR_							szMsg[128];
};


//完成信息
#define SUB_GP_LIST_FINISH			200									//发送完成
#define SUB_GP_SERVER_FINISH		201									//房间完成

//在线信息
#define SUB_GR_KINE_ONLINE			300									//类型在线
#define SUB_GR_SERVER_ONLINE		301									//房间在线

//////////////////////////////////////////////////////////////////////////////////

//获取在线
struct CMD_GP_GetOnline
{
	_WORD_							wServerCount;						//房间数目
	_WORD_							wOnLineServerID[MAX_SERVER];		//房间标识
};

//类型在线
struct CMD_GP_KindOnline
{
	_WORD_							wKindCount;							//类型数目
	tagOnLineInfoKind				OnLineInfoKind[MAX_KIND];			//类型在线
};

//房间在线
struct CMD_GP_ServerOnline
{
	_WORD_							wServerCount;						//房间数目
	tagOnLineInfoServer				OnLineInfoServer[MAX_SERVER];		//房间在线
};

//////////////////////////////////////////////////////////////////////////////////
//服务命令

#define MDM_GP_USER_SERVICE			3									//用户服务

//账号服务
#define SUB_GP_MODIFY_MACHINE		100									//修改机器
#define SUB_GP_MODIFY_LOGON_PASS	101									//修改密码
#define SUB_GP_MODIFY_INSURE_PASS	102									//修改密码
#define SUB_GP_MODIFY_UNDER_WRITE	103									//修改签名
#define SUB_GP_FIRST_SET_BANK_PASS_WORD 104								//首次设置银行密码
//修改头像
#define SUB_GP_USER_FACE_INFO		200									//头像信息
#define SUB_GP_SYSTEM_FACE_INFO		201									//系统头像
#define SUB_GP_CUSTOM_FACE_INFO		202									//自定头像

//个人资料
#define SUB_GP_USER_INDIVIDUAL		301									//个人资料
#define	SUB_GP_QUERY_INDIVIDUAL		302									//查询信息
#define SUB_GP_MODIFY_INDIVIDUAL	303									//修改资料
#define SUB_GP_QUERY_SHORTMSG		304									//查询短信
#define SUB_GP_USER_SHORTMSG		305									//短信信息
#define SUB_GP_DELTE_SHORTMSG		306									//删除短信
#define SUB_GP_USEPROPPHONECARD		307									//使用道具
//沉迷时间
#define SUB_GP_USERTIME				308									//时间增加
//银行服务
#define SUB_GP_USER_SAVE_SCORE		400									//存款操作
#define SUB_GP_USER_TAKE_SCORE		401									//取款操作
#define SUB_GP_USER_TRANSFER_SCORE	402									//转账操作
#define SUB_GP_USER_INSURE_INFO		403									//银行资料
#define SUB_GP_QUERY_INSURE_INFO	404									//查询银行
#define SUB_GP_USER_INSURE_SUCCESS	405									//银行成功
#define SUB_GP_USER_INSURE_FAILURE	406									//银行失败
#define SUB_GP_QUERY_USER_INFO_REQUEST	407								//查询用户
#define SUB_GP_QUERY_USER_INFO_RESULT	408								//用户信息
#define SUB_GP_DELTEMSG_OK				409								//删除成功
#define SUB_GP_USERPROP_OK				410								//使用成功
//防沉迷定时
#define SUB_GP_USERINDULG				411								//防沉迷定时
// 比赛列表
#define	SUB_GP_QUERY_MATCH_LIST_INFO	500								//比赛列表
#define	SUB_GP_QUERY_MATCH_LIST_COUNT	501								//比赛列表
#define SUB_GP_QUERY_MATCH_ARAWD_INFO	502								//获奖信息
#define SUB_GP_UPDATE_USER_MATCH_INFO	503								//人数信息
#define SUB_GP_UPDATE_FINSH				504								//发送完成
//操作结果
#define SUB_GP_OPERATE_SUCCESS		900									//操作成功
#define SUB_GP_OPERATE_FAILURE		901									//操作失败

//////////////////////////////////////////////////////////////////////////////////

//在线时间
struct CMD_GP_UserTime
{
	_D_WORD_						   dwUserId;							//用户ID
	int							   OnLineTime;							//在线时长
};
//修改密码
struct CMD_GP_ModifyLogonPass
{
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szDesPassword[LEN_PASSWORD];		//用户密码
	_TCHAR_							szScrPassword[LEN_PASSWORD];		//用户密码
};

//修改密码
struct CMD_GP_ModifyInsurePass
{
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szDesPassword[LEN_PASSWORD];		//用户密码
	_TCHAR_							szScrPassword[LEN_PASSWORD];		//用户密码
};

//修改签名
struct CMD_GP_ModifyUnderWrite
{
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szPassword[LEN_PASSWORD];			//用户密码
	_TCHAR_							szUnderWrite[LEN_UNDER_WRITE];		//个性签名
};

//////////////////////////////////////////////////////////////////////////////////

//用户头像
struct CMD_GP_UserFaceInfo
{
	_WORD_							wFaceID;							//头像标识
	_D_WORD_							dwCustomID;							//自定标识
};

//修改头像
struct CMD_GP_SystemFaceInfo
{
	_WORD_							wFaceID;							//头像标识
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szPassword[LEN_PASSWORD];			//用户密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//修改头像
struct CMD_GP_CustomFaceInfo
{
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szPassword[LEN_PASSWORD];			//用户密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
	_D_WORD_							dwCustomFace[FACE_CX*FACE_CY];		//图片信息
};

//////////////////////////////////////////////////////////////////////////////////

//绑定机器
struct CMD_GP_ModifyMachine
{
	_BYTE_							cbBind;								//绑定标志
	_D_WORD_							dwUserID;							//用户标识
	_TCHAR_							szPassword[LEN_PASSWORD];			//用户密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//////////////////////////////////////////////////////////////////////////////////
struct CMD_GP_OnLineTime
{
	int					IOnLineTime;									//在线时间
};
//个人资料
struct CMD_GP_UserIndividual
{
	_D_WORD_							dwUserID;							//用户 I D
};

//查询信息
struct CMD_GP_QueryIndividual
{
	_D_WORD_							dwUserID;							//用户 I D
};

//修改资料
struct CMD_GP_ModifyIndividual
{
	_BYTE_							cbGender;							//用户性别
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szPassword[LEN_PASSWORD];			//用户密码
};

// 查询短信
struct CMD_GP_QueryShortMsgInfo
{
	_D_WORD_							dwUserID;							//用户ID
};
// 删除短信
struct CMD_GP_DelteShortMsgInfo
{
	_D_WORD_							dwUserID;							//用户ID
	int								MsgID;								//消息ID
};
//使用电话卡
struct CMD_GP_UsePropPhoneCard
{
	_D_WORD_                           dwUserID;							//用户ID
	_WORD_							PropID;								//道具ID
	_WORD_							wUsePropCount;						//使用数目
	_TCHAR_							UserAddreIP[32];					//IP地址
};
//////////////////////////////////////////////////////////////////////////////////
//携带信息 CMD_GP_UserIndividual

#define DTP_GP_UI_NICKNAME			1									//用户昵称
#define DTP_GP_UI_USER_NOTE			2									//用户说明
#define DTP_GP_UI_UNDER_WRITE		3									//个性签名
#define DTP_GP_UI_QQ				4									//Q Q 号码
#define DTP_GP_UI_EMAIL				5									//电子邮件
#define DTP_GP_UI_SEAT_PHONE		6									//固定电话
#define DTP_GP_UI_MOBILE_PHONE		7									//移动电话
#define DTP_GP_UI_COMPELLATION		8									//真实名字
#define DTP_GP_UI_DWELLING_PLACE	9									//联系地址

//////////////////////////////////////////////////////////////////////////////////

//银行资料
struct CMD_GP_UserInsureInfo
{
	_WORD_							wRevenueTake;						//税收比例
	_WORD_							wRevenueTransfer;					//税收比例
	_WORD_							wServerID;							//房间标识
	SCORE							lUserScore;							//用户金币
	SCORE							lUserInsure;						//银行金币
	SCORE							lTransferPrerequisite;				//转账条件
};

//存入金币
struct CMD_GP_UserSaveScore
{
	_D_WORD_							dwUserID;							//用户 I D
	SCORE							lSaveScore;							//存入金币
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//提取金币
struct CMD_GP_UserTakeScore
{
	_D_WORD_							dwUserID;							//用户 I D
	SCORE							lTakeScore;							//提取金币
	_TCHAR_							szPassword[LEN_MD5];				//银行密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//转账金币
struct CMD_GP_UserTransferScore
{
	_D_WORD_							dwUserID;							//用户 I D
	_BYTE_                            cbByNickName;                       //昵称赠送
	SCORE							lTransferScore;						//转账金币
	_TCHAR_							szPassword[LEN_MD5];				//银行密码
	_TCHAR_							szNickName[LEN_NICKNAME];			//目标用户
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//银行成功
struct CMD_GP_UserInsureSuccess
{
	_D_WORD_							dwUserID;							//用户 I D
	SCORE							lUserScore;							//用户金币
	SCORE							lUserInsure;						//银行金币
	_TCHAR_							szDescribeString[128];				//描述消息
};


// 设置银行密码
struct CMD_GP_FIRST_SET_BANK_PASS_WORD
{
	_DWORD_							dwUserID;							//用户标识
	_TCHAR_							szPassword1[LEN_PASSWORD];			//用户密码
	_TCHAR_							szPassword2[LEN_PASSWORD];			//用户密码
	_TCHAR_							szPassword3[LEN_PASSWORD];			//用户密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//银行失败
struct CMD_GP_UserInsureFailure
{
	long							lResultCode;						//错误代码
	_TCHAR_							szDescribeString[128];				//描述消息
};

//提取结果
struct CMD_GP_UserTakeResult
{
	_D_WORD_							dwUserID;							//用户 I D
	SCORE							lUserScore;							//用户金币
	SCORE							lUserInsure;						//银行金币
};

//查询银行
struct CMD_GP_QueryInsureInfo
{
	_D_WORD_							dwUserID;							//用户 I D
};

//查询用户
struct CMD_GP_QueryUserInfoRequest
{
	_BYTE_                            cbByNickName;                       //昵称赠送
	_TCHAR_							szNickName[LEN_NICKNAME];			//目标用户
};

//用户信息
struct CMD_GP_UserTransferUserInfo
{
	_D_WORD_							dwTargetGameID;						//目标用户
	_TCHAR_							szNickName[LEN_NICKNAME];			//目标用户
};
//////////////////////////////////////////////////////////////////////////////////

//操作失败
struct CMD_GP_OperateFailure
{
	long							lResultCode;						//错误代码
	_TCHAR_							szDescribeString[128];				//描述消息
};

//操作成功
struct CMD_GP_OperateSuccess
{
	long							lResultCode;						//操作代码
	_TCHAR_							szDescribeString[128];				//成功消息
};

//////////////////////////////////////////////////////////////////////////////////
//远程服务

#define MDM_GP_REMOTE_SERVICE		4									//远程服务

//查找服务
#define SUB_GP_C_SEARCH_DATABASE	100									//数据查找
#define SUB_GP_C_SEARCH_CORRESPOND	101									//协调查找

//查找服务
#define SUB_GP_S_SEARCH_DATABASE	200									//数据查找
#define SUB_GP_S_SEARCH_CORRESPOND	201									//协调查找

//////////////////////////////////////////////////////////////////////////////////

//协调查找
struct CMD_GP_C_SearchCorrespond
{
	_D_WORD_							dwGameID;							//游戏标识
	_TCHAR_							szNickName[LEN_NICKNAME];			//用户昵称
};

//协调查找
struct CMD_GP_S_SearchCorrespond
{
	_WORD_							wUserCount;							//用户数目
	tagUserRemoteInfo				UserRemoteInfo[16];					//用户信息
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//登录命令
#define MDM_MB_LOGON				100									//广场登录

//登录模式
#define SUB_MB_LOGON_GAMEID			1									//I D 登录
#define SUB_MB_LOGON_ACCOUNTS		2									//帐号登录
#define SUB_MB_REGISTER_ACCOUNTS	3									//注册帐号

//登录结果
#define SUB_MB_LOGON_SUCCESS		100									//登录成功
#define SUB_MB_LOGON_FAILURE		101									//登录失败

//升级提示
#define SUB_MB_UPDATE_NOTIFY		200									//升级提示

//////////////////////////////////////////////////////////////////////////////////

//I D 登录
struct CMD_MB_LogonGameID
{
	//系统信息
	_WORD_							wModuleID;							//模块标识
	_D_WORD_							dwPlazaVersion;						//广场版本
	_BYTE_                            cbDeviceType;                       //设备类型
    
	//登录信息
	_D_WORD_							dwGameID;							//游戏 I D
	_TCHAR_							szPassword[LEN_MD5];				//登录密码
    
	//连接信息
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器标识
	_TCHAR_							szMobilePhone[LEN_MOBILE_PHONE];	//电话号码
};

//帐号登录
struct CMD_MB_LogonAccounts
{
	//系统信息
	_WORD_							wModuleID;							//模块标识
	_D_WORD_							dwPlazaVersion;						//广场版本
	_BYTE_                            cbDeviceType;                       //设备类型
    
	//登录信息
	_TCHAR_							szPassword[LEN_MD5];				//登录密码
	_TCHAR_							szAccounts[LEN_ACCOUNTS];			//登录帐号
    
	//连接信息
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器标识
	_TCHAR_							szMobilePhone[LEN_MOBILE_PHONE];	//电话号码
};

//注册帐号
struct CMD_MB_RegisterAccounts
{
	//系统信息
	_WORD_							wModuleID;							//模块标识
	_D_WORD_							dwPlazaVersion;						//广场版本
	_BYTE_                            cbDeviceType;                       //设备类型
    
	//密码变量
	_TCHAR_							szLogonPass[LEN_MD5];				//登录密码
	_TCHAR_							szInsurePass[LEN_MD5];				//银行密码
    
	//注册信息
	_WORD_							wFaceID;							//头像标识
	_BYTE_							cbGender;							//用户性别
	_TCHAR_							szAccounts[LEN_ACCOUNTS];			//登录帐号
	_TCHAR_							szNickName[LEN_NICKNAME];			//用户昵称
    
	//连接信息
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器标识
	_TCHAR_							szMobilePhone[LEN_MOBILE_PHONE];	//电话号码
};

//登录成功
struct CMD_MB_LogonSuccess
{
	_WORD_							wFaceID;							//头像标识
	_BYTE_							cbGender;							//用户性别
	_D_WORD_							dwUserID;							//用户 I D
	_D_WORD_							dwGameID;							//游戏 I D
	_D_WORD_							dwExperience;						//经验数值
	_D_WORD_							dwLoveLiness;						//用户魅力
	_TCHAR_							szNickName[LEN_NICKNAME];			//用户昵称
};

//登录(注册)失败
struct CMD_MB_LogonFailure
{
	long							lResultCode;						//错误代码
	_TCHAR_							szDescribeString[128];				//描述消息
};

//升级提示
struct CMD_MB_UpdateNotify
{
	_BYTE_							cbMustUpdate;						//强行升级
	_BYTE_							cbAdviceUpdate;						//建议升级
	_D_WORD_							dwCurrentVersion;					//当前版本
};

//////////////////////////////////////////////////////////////////////////////////
//列表命令

#define MDM_MB_SERVER_LIST			101									//列表信息

//列表信息
#define SUB_MB_LIST_KIND			100									//种类列表
#define SUB_MB_LIST_SERVER			101									//房间列表
#define SUB_MB_LIST_FINISH			200									//列表完成
#define SUB_MB_LIST_MATCH_BASE_INFO	201									//比赛信息
//////////////////////////////////////////////////////////////////////////////////

#pragma pack()




#endif

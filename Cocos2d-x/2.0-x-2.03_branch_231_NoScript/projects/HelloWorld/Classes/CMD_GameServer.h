#ifndef CMD_GAME_SERVER_HEAD_FILE
#define CMD_GAME_SERVER_HEAD_FILE

#include "Packet.h"
#include "Property.h"
#include "Define.h"
#include "Struct.h"

#pragma pack(1)

//////////////////////////////////////////////////////////////////////////////////
//登录命令

#define MDM_GR_LOGON				1									//登录信息

//登录模式
#define SUB_GR_LOGON_USERID			1									//I D 登录
#define SUB_GR_LOGON_MOBILE			2									//手机登录
#define SUB_GR_LOGON_ACCOUNTS		3									//帐户登录

//登录结果
#define SUB_GR_LOGON_SUCCESS		100									//登录成功
#define SUB_GR_LOGON_FAILURE		101									//登录失败
#define SUB_GR_LOGON_FINISH			102									//登录完成

//升级提示
#define SUB_GR_UPDATE_NOTIFY		200									//升级提示

//////////////////////////////////////////////////////////////////////////////////

//I D 登录
struct CMD_GR_LogonUserID
{
	//版本信息
	_D_WORD_							dwPlazaVersion;						//广场版本
	_D_WORD_							dwFrameVersion;						//框架版本
	_D_WORD_							dwProcessVersion;					//进程版本
    
	//登录信息
	_D_WORD_						dwUserID;							//用户 I D
	_TCHAR_							szPass_WORD_[LEN_MD5];				//登录密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//手机登录
struct CMD_GR_LogonMobile
{
	//版本信息
	_WORD_							wGameID;							//游戏标识
	_D_WORD_							dwProcessVersion;					//进程版本
    
	//桌子区域
	_BYTE_                            cbDeviceType;                       //设备类型
	_WORD_                            wBehaviorFlags;                     //行为标识
	_WORD_                            wPageTableCount;                    //分页桌数
    
	//登录信息
	_D_WORD_							dwUserID;							//用户 I D
	_TCHAR_							szPass_WORD_[LEN_MD5];				//登录密码
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器标识
};

//帐号登录
struct CMD_GR_LogonAccounts
{
	//版本信息
	_D_WORD_							dwPlazaVersion;						//广场版本
	_D_WORD_							dwFrameVersion;						//框架版本
	_D_WORD_							dwProcessVersion;					//进程版本
    
	//登录信息
	_TCHAR_							szPass_WORD_[LEN_MD5];				//登录密码
	_TCHAR_							szAccounts[LEN_ACCOUNTS];			//登录帐号
	_TCHAR_							szMachineID[LEN_MACHINE_ID];		//机器序列
};

//登录成功
struct CMD_GR_LogonSuccess
{
	_D_WORD_							dwUserRight;						//用户权限
	_D_WORD_							dwMasterRight;						//管理权限
};

//登录失败
struct CMD_GR_LogonFailure
{
	LONG							lErrorCode;							//错误代码
	_TCHAR_							szDescribeString[128];				//描述消息
};

//升级提示
struct CMD_GR_UpdateNotify
{
	//升级标志
	_BYTE_							cbMustUpdatePlaza;					//强行升级
	_BYTE_							cbMustUpdateClient;					//强行升级
	_BYTE_							cbAdviceUpdateClient;				//建议升级
    
	//当前版本
	_D_WORD_							dwCurrentPlazaVersion;				//当前版本
	_D_WORD_							dwCurrentFrameVersion;				//当前版本
	_D_WORD_							dwCurrentClientVersion;				//当前版本
};

//////////////////////////////////////////////////////////////////////////////////
//配置命令

#define MDM_GR_CONFIG				2									//配置信息

#define SUB_GR_CONFIG_COLUMN		100									//列表配置
#define SUB_GR_CONFIG_SERVER		101									//房间配置
#define SUB_GR_CONFIG_PROPERTY		102									//道具配置
#define SUB_GR_CONFIG_FINISH		103									//配置完成
#define SUB_GR_CONFIG_USER_RIGHT	104									//玩家权限

#define  SUB_GR_CONFIG_PROPERTYBACKPACK		105							//背包信息*
//////////////////////////////////////////////////////////////////////////////////

//列表配置
struct CMD_GR_ConfigColumn
{
	_BYTE_							cbColumnCount;						//列表数目
	tagColumnItem					ColumnItem[MAX_COLUMN];				//列表描述
};

//房间配置
struct CMD_GR_ConfigServer
{
	//房间属性
	_WORD_							wTableCount;						//桌子数目
	_WORD_							wChairCount;						//椅子数目
    
	//房间配置
	_WORD_							wServerType;						//房间类型
	_D_WORD_						dwServerRule;						//房间规则
    
	bool							wIsSetAddScore;						//设置底注
	bool							wIsSetChouMa;						//设置筹码
	int								iSetBeiNum;							//倍数设置
	LONG							lCellScore;							//最低设分
	LONG							lServiceScore;						//服务费用
};

//道具配置
struct CMD_GR_ConfigProperty
{
	_BYTE_							cbPropertyCount;					//道具数目
	tagPropertyInfo					PropertyInfo[MAX_PROPERTY];			//道具描述
};

//玩家权限
struct CMD_GR_ConfigUserRight
{
	_D_WORD_							dwUserRight;						//玩家权限
};
//////////////////////////////////////////////////////////////////////////////////
//用户命令

#define MDM_GR_USER					3									//用户信息

//用户动作
#define SUB_GR_USER_RULE			1									//用户规则
#define SUB_GR_USER_LOOKON			2									//旁观请求
#define SUB_GR_USER_SITDOWN			3									//坐下请求
#define SUB_GR_USER_STANDUP			4									//起立请求
#define SUB_GR_USER_INVITE			5									//用户邀请
#define SUB_GR_USER_INVITE_REQ		6									//邀请请求
#define SUB_GR_USER_REPULSE_SIT  	7									//拒绝玩家坐下
#define SUB_GR_USER_KICK_USER       8                                   //踢出用户
#define SUB_GR_USER_INFO_REQ        9                                   //请求用户信息
#define SUB_GR_USER_CHAIR_REQ       10                                  //请求更换位置
#define SUB_GR_USER_CHAIR_INFO_REQ  11                                  //请求椅子用户信息
#define SUB_GR_USER_SETDOWN			12									//玩家坐下
#define SUB_GR_USER_LOCKTABLE		13									//请求锁定座子

//用户状态
#define SUB_GR_USER_ENTER			100									//用户进入
#define SUB_GR_USER_SCORE			101									//用户分数
#define SUB_GR_USER_STATUS			102									//用户状态
#define SUB_GR_REQUEST_FAILURE		103									//请求失败
#define SUB_GR_REQUEST_FAILURE		103									//请求失败
#define SUB_GR_MATCH_SIGNUP			150									//比赛报名
#define SUB_GR_OTHERMONEY			151									//获取新的金钱

//聊天命令
#define SUB_GR_USER_CHAT			201									//聊天消息
#define SUB_GR_USER_EXPRESSION		202									//表情消息
#define SUB_GR_WISPER_CHAT			203									//私聊消息
#define SUB_GR_WISPER_EXPRESSION	204									//私聊表情
#define SUB_GR_COLLOQUY_CHAT		205									//会话消息
#define SUB_GR_COLLOQUY_EXPRESSION	206									//会话表情

//道具命令
#define SUB_GR_PROPERTY_BUY			300									//购买道具
#define SUB_GR_PROPERTY_SUCCESS		301									//道具成功
#define SUB_GR_PROPERTY_FAILURE		302									//道具失败
#define SUB_GR_PROPERTY_MESSAGE     303                                 //道具消息
#define SUB_GR_PROPERTY_EFFECT      304                                 //道具效应
#define SUB_GR_PROPERTY_TRUMPET		305                                 //喇叭消息
#define SUB_GR_PROPERTY_UPDATE		306									//更新物品

//////////////////////////////////////////////////////////////////////////////////

//旁观请求
struct CMD_GR_UserLookon
{
	_WORD_							wTableID;							//桌子位置
	_WORD_							wChairID;							//椅子位置
};

//坐下请求
struct CMD_GR_UserSitDown
{
	_WORD_							wTableID;							//桌子位置
	_WORD_							wChairID;							//椅子位置
	_TCHAR_							szPassword[LEN_PASSWORD];			//桌子密码
	LONG							wGmaeUserScore;						//游戏下注
	long long						lGetotherMoney;						//获得带入游戏的筹码
	_BYTE_							UseArticle;							//使用物品（1，物品报名；2，豆豆报名）
};

//起立请求
struct CMD_GR_UserStandUp
{
	_WORD_							wTableID;							//桌子位置
	_WORD_							wChairID;							//椅子位置
	_BYTE_							cbForceLeave;						//强行离开
};
//锁定桌子
struct CMD_GR_LOCKTABLE
{
	SCORE                           Money;
	_WORD_                          wCharid;
	_WORD_                          wTableid;
};
//用户金币
struct CMD_GR_MONEY
{
	_WORD_                           wTableID;                          //桌子号码
	_WORD_                           WCharid;                           //椅子号
	SCORE                            lMoney;                            //金钱信息
};
//邀请用户
struct CMD_GR_UserInvite
{
	_WORD_                            wTableID;							//桌子号码
	_D_WORD_                          dwUserID;							//用户 I D
};

//邀请用户请求
struct CMD_GR_UserInviteReq
{
	_WORD_                             wTableID;						//桌子号码
	_D_WORD_                           dwUserID;						//用户 I D
};

//用户分数
struct CMD_GR_UserScore
{
	_D_WORD_							dwUserID;							//用户标识
	tagUserScore					UserScore;							//积分信息
};

//用户分数
struct CMD_GR_MobileUserScore
{
	_D_WORD_							dwUserID;							//用户标识
	tagMobileUserScore				UserScore;							//积分信息
};

//用户状态
struct CMD_GR_UserStatus
{
	_D_WORD_							dwUserID;							//用户标识
	tagUserStatus					UserStatus;							//用户状态
};

//请求失败
struct CMD_GR_RequestFailure
{
	LONG							lErrorCode;							//错误代码
	_TCHAR_							szDescribeString[256];				//描述信息
};


//用户聊天
struct CMD_GR_C_UserChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwChatColor;						//信息颜色
	_D_WORD_							dwTargetUserID;						//目标用户
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};

//用户聊天
struct CMD_GR_S_UserChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwChatColor;						//信息颜色
	_D_WORD_							dwSendUserID;						//发送用户
	_D_WORD_							dwTargetUserID;						//目标用户
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};

//用户表情
struct CMD_GR_C_UserExpression
{
	_WORD_							wItemIndex;							//表情索引
	_D_WORD_							dwTargetUserID;						//目标用户
};

//用户表情
struct CMD_GR_S_UserExpression
{
	_WORD_							wItemIndex;							//表情索引
	_D_WORD_							dwSendUserID;						//发送用户
	_D_WORD_							dwTargetUserID;						//目标用户
};

//用户私聊
struct CMD_GR_C_WisperChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwChatColor;						//信息颜色
	_D_WORD_							dwTargetUserID;						//目标用户
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};

//用户私聊
struct CMD_GR_S_WisperChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwChatColor;						//信息颜色
	_D_WORD_							dwSendUserID;						//发送用户
	_D_WORD_							dwTargetUserID;						//目标用户
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};

//私聊表情
struct CMD_GR_C_WisperExpression
{
	_WORD_							wItemIndex;							//表情索引
	_D_WORD_							dwTargetUserID;						//目标用户
};

//私聊表情
struct CMD_GR_S_WisperExpression
{
	_WORD_							wItemIndex;							//表情索引
	_D_WORD_							dwSendUserID;						//发送用户
	_D_WORD_							dwTargetUserID;						//目标用户
};

//用户会话
struct CMD_GR_ColloquyChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwChatColor;						//信息颜色
	_D_WORD_							dwSendUserID;						//发送用户
	_D_WORD_							dwConversationID;					//会话标识
	_D_WORD_							dwTargetUserID[16];					//目标用户
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};

//邀请用户
struct CMD_GR_C_InviteUser
{
	_WORD_							wTableID;							//桌子号码
	_D_WORD_							dwSendUserID;						//发送用户
};

//邀请用户
struct CMD_GR_S_InviteUser
{
	_D_WORD_							dwTargetUserID;						//目标用户
};

//购买道具
struct CMD_GR_C_PropertyBuy
{
	_BYTE_                            cbRequestArea;						//请求范围
	_BYTE_							cbConsumeScore;						//积分消费
	_WORD_							wItemCount;							//购买数目
	_WORD_							wPropertyIndex;						//道具索引
	_D_WORD_							dwTargetUserID;						//使用对象
};

//道具成功
struct CMD_GR_S_PropertySuccess
{
	_BYTE_                            cbRequestArea;						//使用环境
	_WORD_							wItemCount;							//购买数目
	_WORD_							wPropertyIndex;						//道具索引
	_D_WORD_							dwSourceUserID;						//目标对象
	_D_WORD_							dwTargetUserID;						//使用对象
};
//背包获取
struct DBO_GP_UserPropertyInfo
{
	tagUserPropertyInfoAttrib	   UserPropertyInfoAttrib[MAX_PROPERTY/2];	//背包信息
};
//道具失败
struct CMD_GR_PropertyFailure
{
	_WORD_                            wRequestArea;                       //请求区域
	LONG							lErrorCode;							//错误代码
	_TCHAR_							szDescribeString[256];				//描述信息
};

//道具消息
struct CMD_GR_S_PropertyMessage
{
	//道具信息
	_WORD_                            wPropertyIndex;                     //道具索引
	_WORD_                            wPropertyCount;                     //道具数目
	_D_WORD_                           dwSourceUserID;                     //使用对象
	_D_WORD_                           dwTargerUserID;                     //目标对象
};


//道具效应
struct CMD_GR_S_PropertyEffect
{
	_D_WORD_                           wUserID;					        //用 户I D
	_BYTE_							cbMemberOrder;						//会员等级
};

//发送喇叭
struct CMD_GR_C_SendTrumpet
{
	_BYTE_                           cbRequestArea;                        //请求范围
	_WORD_                           wPropertyIndex;                      //道具索引
	_D_WORD_                          TrumpetColor;                        //喇叭颜色
	_TCHAR_                          szTrumpetContent[TRUMPET_MAX_CHAR];  //喇叭内容
};

//发送喇叭
struct CMD_GR_S_SendTrumpet
{
	_WORD_                           wPropertyIndex;                      //道具索引
	_D_WORD_                          dwSendUserID;                         //用户 I D
	_D_WORD_                          TrumpetColor;                        //喇叭颜色
	_TCHAR_                          szSendNickName[32];				    //玩家昵称
	_TCHAR_                          szTrumpetContent[TRUMPET_MAX_CHAR];  //喇叭内容
};


//用户拒绝黑名单坐下
struct CMD_GR_UserRepulseSit
{
	_WORD_							wTableID;							//桌子号码
	_WORD_							wChairID;							//椅子位置
	_D_WORD_							dwUserID;							//用户 I D
	_D_WORD_							dwRepulseUserID;					//用户 I D
};

//////////////////////////////////////////////////////////////////////////////////

//规则标志
#define UR_LIMIT_SAME_IP			0x01								//限制地址
#define UR_LIMIT_WIN_RATE			0x02								//限制胜率
#define UR_LIMIT_FLEE_RATE			0x04								//限制逃率
#define UR_LIMIT_GAME_SCORE			0x08								//限制积分

//用户规则
struct CMD_GR_UserRule
{
	_BYTE_							cbRuleMask;							//规则掩码
	_WORD_							wMinWinRate;						//最低胜率
	_WORD_							wMaxFleeRate;						//最高逃率
	LONG							lMaxGameScore;						//最高分数
	LONG							lMinGameScore;						//最低分数
};

//请求用户信息
struct CMD_GR_UserInfoReq
{
	_D_WORD_                           dwUserIDReq;                        //请求用户
	_WORD_							wTablePos;							//桌子位置
};

//请求用户信息
struct CMD_GR_ChairUserInfoReq
{
	_WORD_							wTableID;							//桌子号码
	_WORD_							wChairID;							//椅子位置
};
//////////////////////////////////////////////////////////////////////////////////
//状态命令

#define MDM_GR_STATUS				4									//状态信息

#define SUB_GR_TABLE_INFO			100									//桌子信息
#define SUB_GR_TABLE_STATUS			101									//桌子状态

//////////////////////////////////////////////////////////////////////////////////

//桌子信息
struct CMD_GR_TableInfo
{
	_WORD_							wTableCount;						//桌子数目
	tagTableStatus					TableStatusArray[512];				//桌子状态
};

//桌子状态
struct CMD_GR_TableStatus
{
	_WORD_							wTableID;							//桌子号码
	tagTableStatus					TableStatus;						//桌子状态
};

//////////////////////////////////////////////////////////////////////////////////
//银行命令

#define MDM_GR_INSURE				5									//用户信息

//银行命令
#define SUB_GR_QUERY_INSURE_INFO	1									//查询银行
#define SUB_GR_SAVE_SCORE_REQUEST	2									//存款操作
#define SUB_GR_TAKE_SCORE_REQUEST	3									//取款操作
#define SUB_GR_TRANSFER_SCORE_REQUEST	4								//取款操作
#define SUB_GR_QUERY_USER_INFO_REQUEST	5								//查询用户

#define SUB_GR_USER_INSURE_INFO		100									//银行资料
#define SUB_GR_USER_INSURE_SUCCESS	101									//银行成功
#define SUB_GR_USER_INSURE_FAILURE	102									//银行失败
#define SUB_GR_USER_TRANSFER_USER_INFO	103								//用户资料

//////////////////////////////////////////////////////////////////////////////////

//查询银行
struct CMD_GR_C_QueryInsureInfoRequest
{
	_BYTE_                            cbActivityGame;                     //游戏动作
};

//存款请求
struct CMD_GR_C_SaveScoreRequest
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	SCORE							lSaveScore;							//存款数目
};

//取款请求
struct CMD_GR_C_TakeScoreRequest
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	SCORE							lTakeScore;							//取款数目
	_TCHAR_							szInsurePass[LEN_PASSWORD];			//银行密码
};

//转账金币
struct CMD_GP_C_TransferScoreRequest
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	_BYTE_                            cbByNickName;                       //昵称赠送
	SCORE							lTransferScore;						//转账金币
	_TCHAR_							szNickName[LEN_NICKNAME];			//目标用户
	_TCHAR_							szInsurePass[LEN_PASSWORD];			//银行密码
};

//查询用户
struct CMD_GR_C_QueryUserInfoRequest
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	_BYTE_                            cbByNickName;                       //昵称赠送
	_TCHAR_							szNickName[LEN_NICKNAME];			//目标用户
};

//银行资料
struct CMD_GR_S_UserInsureInfo
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	_WORD_							wRevenueTake;						//税收比例
	_WORD_							wRevenueTransfer;					//税收比例
	_WORD_							wServerID;							//房间标识
	SCORE							lUserScore;							//用户金币
	SCORE							lUserInsure;						//银行金币
	SCORE							lTransferPrerequisite;				//转账条件
};

//银行成功
struct CMD_GR_S_UserInsureSuccess
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	SCORE							lUserScore;							//身上金币
	SCORE							lUserInsure;						//银行金币
	_TCHAR_							szDescribeString[128];				//描述消息
};

//银行失败
struct CMD_GR_S_UserInsureFailure
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	LONG							lErrorCode;							//错误代码
	_TCHAR_							szDescribeString[128];				//描述消息
};

//用户信息
struct CMD_GR_S_UserTransferUserInfo
{
	_BYTE_                            cbActivityGame;                     //游戏动作
	_D_WORD_							dwTargetGameID;						//目标用户
	_TCHAR_							szNickName[LEN_NICKNAME];			//目标用户
};
//////////////////////////////////////////////////////////////////////////////////
//管理命令

#define MDM_GR_MANAGE				6									//管理命令

#define SUB_GR_SEND_WARNING			1									//发送警告
#define SUB_GR_SEND_MESSAGE			2									//发送消息
#define SUB_GR_LOOK_USER_IP			3									//查看地址
#define SUB_GR_KILL_USER			4									//踢出用户
#define SUB_GR_LIMIT_ACCOUNS		5									//禁用帐户
#define SUB_GR_SET_USER_RIGHT		6									//权限设置

//房间设置
#define SUB_GR_QUERY_OPTION			7									//查询设置
#define SUB_GR_OPTION_SERVER		8									//房间设置
#define SUB_GR_OPTION_CURRENT		9									//当前设置

#define SUB_GR_LIMIT_USER_CHAT		10									//限制聊天

#define SUB_GR_KICK_ALL_USER		11									//踢出用户
#define SUB_GR_DISMISSGAME		    12									//解散游戏

//////////////////////////////////////////////////////////////////////////////////

//发送警告
struct CMD_GR_SendWarning
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwTargetUserID;						//目标用户
	_TCHAR_							szWarningMessage[LEN_USER_CHAT];	//警告消息
};

//系统消息
struct CMD_GR_SendMessage
{
	_BYTE_							cbGame;								//游戏消息
	_BYTE_							cbRoom;								//游戏消息
	_BYTE_							cbAllRoom;							//游戏消息
	_WORD_							wChatLength;						//信息长度
	_TCHAR_							szSystemMessage[LEN_USER_CHAT];		//系统消息
};

//查看地址
struct CMD_GR_LookUserIP
{
	_D_WORD_							dwTargetUserID;						//目标用户
};

//踢出用户
struct CMD_GR_KickUser
{
	_D_WORD_							dwTargetUserID;						//目标用户
};

//禁用帐户
struct CMD_GR_LimitAccounts
{
	_D_WORD_							dwTargetUserID;						//目标用户
};

//权限设置
struct CMD_GR_SetUserRight
{
	//目标用户
	_D_WORD_							dwTargetUserID;						//目标用户
    
	//绑定变量
	_BYTE_							cbGameRight;						//帐号权限
	_BYTE_							cbAccountsRight;					//帐号权限
    
	//权限变化
	_BYTE_							cbLimitRoomChat;					//大厅聊天
	_BYTE_							cbLimitGameChat;					//游戏聊天
	_BYTE_							cbLimitPlayGame;					//游戏权限
	_BYTE_							cbLimitSendWisper;					//发送消息
	_BYTE_							cbLimitLookonGame;					//旁观权限
};

//房间设置
struct CMD_GR_OptionCurrent
{
	_D_WORD_							dwRuleMask;							//规则掩码
	tagServerOptionInfo				ServerOptionInfo;					//房间配置
};

//房间设置
struct CMD_GR_ServerOption
{
	tagServerOptionInfo				ServerOptionInfo;					//房间配置
};

//踢出所有用户
struct CMD_GR_KickAllUser
{
	_TCHAR_							szKickMessage[LEN_USER_CHAT];		//踢出提示
};

//解散游戏
struct CMD_GR_DismissGame
{
	_WORD_							wDismissTableNum;		            //解散桌号
};
//////////////////////////////////////////////////////////////////////////////////

//设置标志
#define OSF_ROOM_CHAT				1									//大厅聊天
#define OSF_GAME_CHAT				2									//游戏聊天
#define OSF_ROOM_WISPER				3									//大厅私聊
#define OSF_ENTER_TABLE				4									//进入游戏
#define OSF_ENTER_SERVER			5									//进入房间
#define OSF_SEND_BUGLE				12									//发送喇叭

//房间设置
struct CMD_GR_OptionServer
{
	_BYTE_							cbOptionFlags;						//设置标志
	_BYTE_							cbOptionValue;						//设置标志
};

//限制聊天
struct CMD_GR_LimitUserChat
{
	_D_WORD_							dwTargetUserID;						//目标用户
	_BYTE_							cbLimitFlags;						//限制标志
	_BYTE_							cbLimitValue;						//限制与否
};
//////////////////////////////////////////////////////////////////////////////////
//比赛命令

#define MDM_GR_MATCH				7									//比赛命令

#define SUB_GR_MATCH_FEE			400									//报名费用
#define SUB_GR_MATCH_NUM			401									//等待人数
#define SUB_GR_LEAVE_MATCH			402									//退出比赛
#define SUB_GR_MATCH_INFO			403									//比赛信息
#define SUB_GR_MATCH_WAIT_TIP		404									//等待提示
#define SUB_GR_MATCH_RESULT			405									//比赛结果
#define SUB_GR_MATCH_STATUS			406									//比赛状态
#define SUB_GR_MATCH_USER_COUNT		407									//参赛人数
#define SUB_GR_MATCH_DESC			408									//比赛描述
#define SUB_GR_MATCH_DETAILS		409									//比赛详情
#define SUB_GR_MATCH_RANK			410									//比赛排名
#define SUB_GR_MATCH_USERLIST		411									//用户列表
#define SUB_GR_MATCH_FINISHEDROUND	412									//完成一轮
#define SUB_GR_MATCH_GAMEBEGIN		414									//游戏开始
#define SUB_GR_MATCH_GAMEEND		413									//游戏结束
#define SUB_GR_MATCH_PLAYING_TABLE	415									//游戏桌子
#define SUB_GR_MATCH_USER_ElIMINATE	416									//淘汰用户
#define SUB_GR_MATCH_ITEM_INFO		417									//奖励物品
#define SUB_GR_MATCH_PROPE			418									//物品报名
#define SUB_GR_MATCH_SIGN_LOST		419									//报名失败

#define MAX_MATCH_DESC				5									//最多描述

//游戏服务器命令
#define SUB_GR_MATCH_START			420									//比赛开始
//奖励物品
struct tagRewardItem
{
	_D_WORD_								dwItemTypeID;					//物品类型ID
	_WORD_								wItemCount;						//物品数量
	_TCHAR_								szItemName[32];					//物品名称
	_TCHAR_								szItemInfo[128];				//物品描述
};
//报名物品
struct tagFreeItem
{
	_TCHAR_								szItemName[32];					//物品名字
	_D_WORD_								dwPropeID;						//物品ID
};
//比赛奖励
struct tagMatchReward
{
	_WORD_								wReginStart;					//名次区域
	_WORD_								wReginEnd;						//名次区域
	_D_WORD_								dwGold;							//金币奖励
	_D_WORD_								dwExperience;					//经验奖励
	_WORD_								wItemTypeCount;					//物品个数
	tagRewardItem*						pRewardItem;					//奖励物品
};
//比赛描述
struct CMD_GR_MatchDesc
{
	_TCHAR_							szTitle[MAX_MATCH_DESC][16];		//信息标题
	_TCHAR_							szDescribe[MAX_MATCH_DESC][64];		//描述内容
	COLORREF						crTitleColor;						//标题颜色
	COLORREF						crDescribeColor;					//描述颜色
	SCORE							lFeeScore;							//报名金币
	_D_WORD_							dwFeeItemID;						//报名道具
	tagMatchReward					tagRewardArray[5];					//奖励说明
	//赛制详情
	_WORD_							wUserCout;							//剩余几人停止淘汰
	_WORD_							wRoundUserCount;					//进入复赛人数
	_BYTE_							cbSecGameCount;						//复赛局数
	_BYTE_							cbRoundCount;						//复赛局数
};
//比赛人数
struct CMD_GR_Match_Num
{
	_D_WORD_							dwServerID;							//房间ID
	_D_WORD_							dwWaitting;							//等待人数
	_D_WORD_							dwTotal;							//开赛人数
	_D_WORD_							dwMatchTotal;						//总人数
};
//物品信息
struct CMD_GR_Match_Item
{
	int								sItemCount;							//物品数目
	_D_WORD_							dwMatchRank;						//获得名次
	_TCHAR_							szItemName[32];						//物品名字
};
// 用户淘汰
struct CMD_GR_Match_UserEliminate
{
	_D_WORD_							dwUserID;							//淘汰用户
};

//赛事信息
struct CMD_GR_Match_Info
{
	_TCHAR_							szTitle[4][64];						//信息标题
    _WORD_							wGameCount;							//游戏局数
};

//提示信息
struct CMD_GR_Match_Wait_Tip
{
	SCORE							lScore;								//当前积分
	_WORD_							wRank;								//当前名次
	_WORD_							wCurTableRank;						//本桌名次
	_WORD_							wUserCount;							//当前人数
	_WORD_							wPlayingTable;						//游戏桌数
	_TCHAR_							szMatchName[LEN_SERVER];			//比赛名称
	bool							bFirst;								//是否初赛
};

// 游戏桌子
struct CMD_GR_Match_Playing_Table
{
	_WORD_							wPlayingTable;						//当前正在游戏的桌子
};


// 排名列表
struct CMD_GR_Match_Rank_List
{
	_D_WORD_							dwUserID;
	_WORD_							wRank;
};

// 比赛用户列表
struct CMD_GR_Match_User_List
{
	_D_WORD_							dwMatchNo;							//比赛编号
	_WORD_							wUserCount;							//比赛人数
};

//比赛结果
struct CMD_GR_MatchResult
{
	_TCHAR_							szDescribe[256];					//得奖描述
	_D_WORD_							dwGold;								//金币奖励
	_D_WORD_							dwExperience;						//经验奖励
	_WORD_							wRewardItemCount;					//物品种类数目
	tagRewardItem					RewardItemArray[5];					//物品奖励
};

// 比赛信息
struct CMD_GR_MatchInfomation
{
	_TCHAR_							szMatchName[LEN_SERVER];			//比赛名称
	_BYTE_							bMatchStatus;						//比赛状态
	_TCHAR_							szTypeName[64];						//比赛类型
	_WORD_							wGamersCount;						//参赛人数
	LONG							lTime;								//单局时间
	_WORD_							wSumRound;							//总轮数
	_WORD_							wSumGames;							//每轮局数
	_WORD_							wCurrentRound;						//当前轮数
	_WORD_							wCurrentGames;						//当前局数
	SCORE							lCurrentCell;						//当前底分
	_TCHAR_							szMatchElimination[64];				//淘汰说明
	_WORD_							wCurrentCount;						//当前总人数
	_D_WORD_							dwMatchNo;							//比赛NO
};

//////////////////////////////////////////////////////////////////////////////////
//框架命令

#define MDM_GF_FRAME				100									//框架命令

//////////////////////////////////////////////////////////////////////////////////
//框架命令

//用户命令
#define SUB_GF_GAME_OPTION			1									//游戏配置
#define SUB_GF_USER_READY			2									//用户准备
#define SUB_GF_LOOKON_CONFIG		3									//旁观配置

//聊天命令
#define SUB_GF_USER_CHAT			10									//用户聊天
#define SUB_GF_USER_EXPRESSION		11									//用户表情

//游戏信息
#define SUB_GF_GAME_STATUS			100									//游戏状态
#define SUB_GF_GAME_SCENE			101									//游戏场景
#define SUB_GF_LOOKON_STATUS		102									//旁观状态

//系统消息
#define SUB_GF_SYSTEM_MESSAGE		200									//系统消息
#define SUB_GF_ACTION_MESSAGE		201									//动作消息

//////////////////////////////////////////////////////////////////////////////////

//游戏配置
struct CMD_GF_GameOption
{
	_BYTE_							cbAllowLookon;						//旁观标志
	_D_WORD_							dwFrameVersion;						//框架版本
	_D_WORD_							dwClientVersion;					//游戏版本
};

//旁观配置
struct CMD_GF_LookonConfig
{
	_D_WORD_							dwUserID;							//用户标识
	_BYTE_							cbAllowLookon;						//允许旁观
};

//旁观状态
struct CMD_GF_LookonStatus
{
	_BYTE_							cbAllowLookon;						//允许旁观
};

//游戏环境
struct CMD_GF_GameStatus
{
	_BYTE_							cbGameStatus;						//游戏状态
	_BYTE_							cbAllowLookon;						//旁观标志
};

//用户聊天 （发送）
struct CMD_GF_C_UserChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_							dwChatColor;						//信息颜色
	_D_WORD_							dwTargetUserID;						//目标用户
	_WORD_							wType;								//聊天类型
	_WORD_							wCount;								//显示次数
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};



//用户聊天(接收)
struct CMD_GF_S_UserChat
{
	_WORD_							wChatLength;						//信息长度
	_D_WORD_						dwChatColor;						//信息颜色
	_D_WORD_						dwSendUserID;						//发送用户
	_D_WORD_						dwTargetUserID;						//目标用户
	_WORD_							wType;								//聊天类型
	_WORD_							wChairID;							//发送用户椅子
	_TCHAR_							szChatString[LEN_USER_CHAT];		//聊天信息
};

//用户表情
struct CMD_GF_C_UserExpression
{
	_WORD_							wItemIndex;							//表情索引
	_D_WORD_							dwTargetUserID;						//目标用户
};

//用户表情
struct CMD_GF_S_UserExpression
{
	_WORD_							wItemIndex;							//表情索引
	_D_WORD_							dwSendUserID;						//发送用户
	_D_WORD_							dwTargetUserID;						//目标用户
};

//////////////////////////////////////////////////////////////////////////////////
//游戏命令

#define MDM_GF_GAME					200									//游戏命令

//////////////////////////////////////////////////////////////////////////////////
//携带信息

//其他信息
#define DTP_GR_TABLE_PASS_WORD_		1									//桌子密码

//用户属性
#define DTP_GR_NICK_NAME			10									//用户昵称
#define DTP_GR_GROUP_NAME			11									//社团名字
#define DTP_GR_UNDER_WRITE			12									//个性签名

//附加信息
#define DTP_GR_USER_NOTE			20									//用户备注
#define DTP_GR_CUSTOM_FACE			21									//自定头像

//////////////////////////////////////////////////////////////////////////////////

//请求错误
#define REQUEST_FAILURE_NORMAL		0									//常规原因
#define REQUEST_FAILURE_NOGOLD		1									//金币不足
#define REQUEST_FAILURE_NOSCORE		2									//积分不足
#define REQUEST_FAILURE_PASS_WORD_	3									//密码错误

//////////////////////////////////////////////////////////////////////////////////

#pragma pack()

#endif
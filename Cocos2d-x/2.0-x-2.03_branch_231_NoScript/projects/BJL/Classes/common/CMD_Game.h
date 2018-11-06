#ifndef CMD_GAME_HEAD_FILE
#define CMD_GAME_HEAD_FILE
#pragma once
#include "Define.h"

//////////////////////////////////////////////////////////////////////////
//μ??o????∞???“?

#define MDM_GR_LOGON				1									//∑?o‰μ??o

//#define SUB_GR_LOGON_ACCOUNTS		1									//’?a?μ??o
//#define SUB_GR_LOGON_USERID			2									//I D μ??o
								//									

#define SUB_GR_LOGON_SUCCESS		100									//μ??o≥…π?
#define SUB_GR_LOGON_ERROR			101									//μ??o??∞?
#define SUB_GR_LOGON_FINISH			102									//μ??o?í≥…


//#define MDM_GF_GAME						100								//游戏消息
//#define MDM_GF_FRAME					101								//框架消息

//∑?o‰’?∫≈μ??o
struct CMD_GR_LogonByAccounts
{
	DWORD							dwPlazaVersion;						//π?≥°∞ê±?
	DWORD							dwProcessVersion;					//Ωˉ≥?∞ê±?
	unsigned char					szAccounts[NAME_LEN];				//μ??o’?∫≈
	unsigned char					szPassWord[PASS_LEN];				//μ??o√???
};

//∑?o‰ ID μ??o
struct CMD_GR_LogonByUserID
{
	DWORD							dwPlazaVersion;						//π?≥°∞ê±?
	DWORD							dwProcessVersion;					//Ωˉ≥?∞ê±?
	DWORD							dwUserID;							//”√a? I D
	unsigned char					szPassWord[PASS_LEN];				//μ??o√???
};

//μ??o≥…π????￠
/*struct CMD_GR_LogonSuccess
{
	DWORD							dwUserID;							//”√a? I D
	//WORD							wJoinMatch;							//≤???  
};*/

//μ??o??∞?
struct CMD_GR_LogonError
{
	LONG							lErrorCode;							//￥ì??￥˙??
	char							szErrorDescribe[128];				//￥ì?????￠
};

//√???
enum enEnterRoomType
{
	FIRST_LOGON  =0,                  //μ?“a￥?μ??o
	RECONNECT_LOGON =1,               //÷??¨μ??o
};

//////////////////////////////////////////////////////////////////////////
//”√a?????∞???“?

//#define MDM_GR_USER					2									//”√a?–≈?￠

#define SUB_GR_USER_SIT_REQ			1									//?ˉ??????
#define SUB_GR_USER_LOOKON_REQ		2									//≈‘π�????
#define SUB_GR_USER_STANDUP_REQ		3									//???￠????
#define SUB_GR_USER_LEFT_GAME_REQ	4									//????”??∑

#define SUB_GR_USER_COME			100									//”√a?Ωˉ??
//#define SUB_GR_USER_STATUS			101									//”√a??￥?¨
//#define SUB_GR_USER_SCORE			102									//”√a?∑÷??
#define SUB_GR_SIT_FAILED			103									//?ˉ????∞?
#define SUB_GR_USER_RIGHT			104									//”√a?????
#define SUB_GR_MEMBER_ORDER			105									//a·‘±μ?o?
#define SUB_GR_USER_SORT			106									//”√a?√?￥?
#define SUB_GR_USER_MATCH_SCORE     107                                 //±???”√a?√?￥? 20109.29 by gaoshan
#define SUB_GR_MATCH_USER_COM       108                                 //±???”√a?Ωˉ??2010.10.5 by gaoshan

//#define SUB_GR_USER_CHAT			200									//???????￠
#define SUB_GR_USER_WISPER			205									//àΩ”????￠
//#define SUB_GR_USER_RULE			202									//”√a?πê‘ú

//#define SUB_GR_USER_INVITE			300									//—??????￠
//#define SUB_GR_USER_INVITE_REQ		301									//—???????


#define SUB_GR_JOIN_MATCH			400									//≤?o”±???
//#define SUB_GR_JOIN_MATCH_REQ		401									//≤???????
#define SUB_GR_USER_START_QUEUE_REQ 401                                 //≈≈?”????           2010.9.13 by gaoshan add

#define SUB_GR_MODIFY_GOLD			402									//–?∏?Ω?±“
#define SUB_GR_GAME_MATCH_INFO_REQ	403									//”??∑±???–≈?￠????
#define SUB_GR_GAME_MATCH_INFO		404									//”??∑±???–≈?￠
#define SUB_GR_CLOSE_GAME_ROOM		405									//π?±’”??∑∑?o‰
#define SUB_GR_CLIENT_READY         406                               //??a??à“—?≠?ù???í±? 2010.9.14 by gaoshan add
#define SUB_GR_CLIENT_START_GAME    407                               //??a??à???o”??∑ 2010.9.14 by gaoshan add
//////////////////////////////////////////////?¨?”￡¨9.15
#define SUB_GR_SET_VIPROOM_RATE     408									//…?÷√VIP∑?o‰±??????￠
#define SUB_GR_OK_PASSWORD_REQ		409									//aòμ√√???
#define SUB_GR_ERROR_PASSWORD		410									//√???￥ì??
#define SUB_GR_START_GAME_INFO		411									//”??∑???o–≈?￠//?¨?”￡¨20110105
#define SUB_GR_END_GAME_INFO		412									//”??∑Ω·?ˉ–≈?￠//?¨?”￡¨20110105
#define SUB_GR_DRAW_VIPRATE			413									//aêa≠∑?o‰±???//?¨?”￡¨20110818

//a·‘±μ?o?
struct CMD_GR_MemberOrder
{
	DWORD							dwUserID;							//?????? ID
	BYTE							cbMemberOrder;						//a·‘±μ?o?
};

//???ò?μ?≥//?¨?”￡¨20110105
struct CMD_GR_TaskSystem
{
	WORD							wKindID;							//”??∑ID
	WORD							wProblemID;							//????ID
	WORD							wEggNumber;							//Ω?μ∞????
	bool							bDrawAnimation;						//??∑ò?‘????a≠
};
//”√a????ò≤??‘				
struct tagUserTaskParameter
{
	DWORD	dwTaskID;				//???òID
	DWORD	dwCondition;			//Ω±?ˉ??o?
	DWORD	dwRewardA;				//Ω±?ˉA
	DWORD	dwRewardB;				//Ω±?ˉB
	DWORD	dwTaskKind;				//???ò??–?￡¨0 –??÷ 1…?o?￡¨2?‘??μ?o??·???ú
	DWORD	dwFinish;				//?í≥…
	DWORD	dwDoingValue;			//???ò?í≥…??÷μ

	char	szTaskName[128];		//√?≥?
	char	szDescript[128];		//???ò√???
	char	szRewardContent[128];	//Ω±?ˉ
};

//”√a?????
struct CMD_GR_UserRight
{
	DWORD							dwUserID;							//?????? ID
	DWORD							dwUserRight;						//”√a?????
};

//”√a??￥?¨
//struct CMD_GR_UserStatus
//{
//	DWORD							dwUserID;							//?????? ID
//	WORD							wTableID;							//???”?a÷√
//	WORD							wChairID;							//“??”?a÷√
//	BYTE							cbUserStatus;						//”√a??￥?¨
//};

//”√a?∑÷??
struct CMD_GR_UserScore
{
	//LONG							lLoveliness;						//”√a?????
	LONG							lWeekWinCount;						//?÷??   2010-12-30 by zhanghua
	LONG							lWeekMingci;						//÷?≈≈√? 2010-12-30 by zhanghua
	DWORD							dwUserID;							//”√a? I D
	tagUserScore					UserScore;							//a?∑÷–≈?￠
};

//”√a?±???a?∑÷2010.9.29 by gaoshan
struct CMD_GR_UserMatchScore
{
	DWORD                           dwUserID;                          //”√a?ID
	LONG                            lMatchScore;                       //±???a?∑÷
};

//”√a?√?￥?
struct CMD_GR_UserSort
{
	DWORD								dwUserID;							//”√a? I D
	WORD								wSortID;							//≈≈√?
	EN_MatchStatus						enMatchStatus;						//±????￥?¨
};

struct CMD_GR_AddBlood_Gold
{
	DWORD                               dwUserID;                          //”√a?ID
	WORD                                wSubGold;
};

//?????ˉ??
struct CMD_GR_UserSitReq
{
	//WORD							wTeamID;							//–°?è∫≈??  2010.9.14 by gaoshan 
	WORD							wTableID;							//???”?a÷√
	WORD							wChairID;							//“??”?a÷√
	BYTE							cbPassLen;							//√???≥§??
	char							szTablePass[PASS_LEN];				//???”√???
};

//—???”√a? 
struct CMD_GR_UserInviteReq
{
	WORD							wTableID;							//???”∫≈??
	DWORD							dwUserID;							//”√a? I D
};

//?ˉ????∞?
struct CMD_GR_SitFailed
{
	char							szFailedDescribe[256];				//￥ì??√???
};

//????Ω·ππ 
struct CMD_GR_UserChat
{
	WORD							wChatLength;						//–≈?￠≥§??
	//COLORREF						crFontColor;						//–≈?￠—’…′
	DWORD							dwSendUserID;						//∑￠à?”√a?
	DWORD							dwTargetUserID;						//??±í”√a?
	char							szChatMessage[MAX_CHAT_LEN];		//????–≈?￠
};

//àΩ”?Ω·ππ 
struct CMD_GR_Wisper
{
	WORD							wChatLength;						//–≈?￠≥§??
	//COLORREF						crFontColor;						//–≈?￠—’…′
	DWORD							dwSendUserID;						//∑￠à?”√a?
	DWORD							dwTargetUserID;						//??±í”√a?
	char							szChatMessage[MAX_CHAT_LEN];		//????–≈?￠
};

//”√a?πê‘ú
struct CMD_GR_UserRule
{
	bool							bPassword;							//…?÷√√???
	bool							bLimitWin;							//??÷??§??
	bool							bLimitFlee;							//??÷?????
	bool							bLimitScore;						//??÷?∑÷??
	bool							bCheckSameIP;						//–?—èμ?÷∑
	WORD							wWinRate;							//??÷??§??
	WORD							wFleeRate;							//??÷??”≈?
	LONG							lMaxScore;							//?ó∏?∑÷?? 
	LONG							lLessScore;							//?óμ?∑÷??
	char							szPassword[PASS_LEN];				//???”√???
};

//—???”√a? 
struct CMD_GR_UserInvite
{
	WORD							wTableID;							//???”∫≈??
	DWORD							dwUserID;							//”√a? I D
	
};

//≤?o”±???
struct CMD_GR_JoinMatch
{
	WORD							wJoin;								//–≈?￠??
	char							szVIPPassWord[PASS_LEN];			//VIP∑?o‰√???///////////?¨?”￡¨9.21
	LONG							lCellScore;							//±???////////////?¨?”￡¨101004
};
/////////////////////////////////////////?¨?”￡¨9.15
struct CMD_GR_Draw_VIPRate
{
	LONG							nRate;								//VIP∑?o‰±???
	
};

struct CMD_GR_VIPRoom_PassWord
{
	char							szPassword[PASS_LEN];				//VIP∑?o‰√???
    LONG							lCellScore;							//±???
};
/////////////////////////////////////////?¨?”￡¨9.15

//”??∑±???–≈?￠
struct CMD_GR_GameMatchInfo
{
	WORD							wSignUpCount;						//±?√??à??	
	WORD							wJoinCount;							//≤????à??
	WORD							wPlayeCount;						//o§’Ω?à??
	DWORD                           dwUserID;                           //”√a?ID
	char							szMatchTime[24];					//’?￥?±????±o‰
	char							szMatchStatus[16];					//±????￥?¨
};
//////////////////////////////////////////////////////////////////////////
//≈‰÷√–≈?￠????∞?

#define MDM_GR_INFO					3									//≈‰÷√–≈?￠

#define SUB_GR_SERVER_INFO			100									//∑?o‰≈‰÷√
#define SUB_GR_ORDER_INFO			101									//μ?o?≈‰÷√
#define SUB_GR_MEMBER_INFO			102									//a·‘±≈‰÷√
#define SUB_GR_COLUMN_INFO			108									//?–±ì≈‰÷√
//#define SUB_GR_CONFIG_FINISH		104									//≈‰÷√?í≥…

//”??∑∑?o‰–≈?￠
struct CMD_GR_ServerInfo
{
	//∑?o‰?ù–‘
	WORD							wKindID;							//??–? I D
	WORD							wTableCount;						//???”????
	WORD							wChairCount;						//“??”????
	DWORD							dwVideoAddr;						//?”?μμ?÷∑

	//??’π≈‰÷√
	WORD							wGameGenre;							//”??∑??–?
	BYTE							cbHideUserInfo;						//“?≤?–≈?￠
	//WORD							wMatchType;							//±?????–? 2010.9.13 by gaoshan
	BYTE                            cbLimitDraw;                        //??∑ò??÷?±??? 2010.9.17 by gaoshan add                          
};

//∑÷??√???–≈?￠
struct CMD_GR_ScoreInfo
{
	WORD							wDescribeCount;						//√???????
	WORD							wDataDescribe[16];					//????±í÷?
};

//μ?o?√???Ω·ππ
struct tagOrderItem
{
	LONG							lScore;								//μ?o?a?∑÷
	WORD							wOrderDescribe[16];					//μ?o?√???
};

//μ?o?√???–≈?￠
struct CMD_GR_OrderInfo
{
	WORD							wOrderCount;						//μ?o?????
	tagOrderItem					OrderItem[128];						//μ?o?√???
};

//?–±ì?ó√???Ω·ππ
/*struct tagColumnItem
{
	WORD							wColumnWidth;						//?–±ì?ì??
	WORD							wDataDescribe;						//?÷????–?
	char							szColumnName[16];					//?–±ì√??÷
};*/

//?–±ì√???–≈?￠
struct CMD_GR_ColumnInfo
{
	WORD							wColumnCount;						//?–±ì????
	tagColumnItem					ColumnItem[32];						//?–±ì√???
};

//////////////////////////////////////////////////////////////////////////
//∑?o‰?￥?¨????∞?

#define MDM_GR_STATUS				4									//?￥?¨–≈?￠

#define SUB_GR_TABLE_INFO			100									//???”–≈?￠
#define SUB_GR_TABLE_STATUS			101									//???”?￥?¨


//???”?￥?¨Ω·ππ
/*struct tagTableStatus
{
	BYTE							bTableLock;							//àˉ???￥?¨
	BYTE							bPlayStatus;						//”??∑?￥?¨
};*/

//???”?￥?¨???è
struct CMD_GR_TableInfo
{
	WORD							wTableCount;						//???”????
	tagTableStatus					TableStatus[512];					//?￥?¨???è
};

//???”?￥?¨–≈?￠
/*struct CMD_GR_TableStatus
{
	WORD							wTableID;							//???”∫≈??
	BYTE							bTableLock;							//àˉ???￥?¨
	BYTE							bPlayStatus;						//”??∑?￥?¨
	LONG							lCellScore;							//???”±???
};*/

//////////////////////////////////////////////////////////////////////////
//π??ì????∞?

#define MDM_GR_MANAGER				5									//π??ì√??ó

#define SUB_GR_SEND_WARNING			1									//∑￠à???∏ê
#define SUB_GR_SEND_MESSAGE			2									//∑￠à????￠
#define SUB_GR_LOOK_USER_IP			3									//≤è?￥μ?÷∑
#define SUB_GR_KILL_USER			4									//??≥?”√a?
#define SUB_GR_LIMIT_ACCOUNS		5									//Ω?”√’?a?
#define SUB_GR_SET_USER_RIGHT		6									//????…?÷√
//#define SUB_GR_OPTION_SERVER		7									//∑?o‰…?÷√

//∑￠à???∏ê
struct CMD_GR_SendWarning
{
	WORD							wChatLength;						//–≈?￠≥§??
	DWORD							dwTargetUserID;						//??±í”√a?
	char							szWarningMessage[MAX_CHAT_LEN];		//??∏ê???￠
};

//?μ?≥???￠
struct CMD_GR_SendMessage
{
	BYTE							cbGame;								//”??∑???￠
	BYTE							cbRoom;								//”??∑???￠
	WORD							wChatLength;						//–≈?￠≥§??
	char							szSystemMessage[MAX_CHAT_LEN];		//?μ?≥???￠
};

//≤è?￥μ?÷∑
struct CMD_GR_LookUserIP
{
	DWORD							dwTargetUserID;						//??±í”√a?
};

//??≥?”√a?
struct CMD_GR_KillUser
{
	DWORD							dwTargetUserID;						//??±í”√a?
};

//Ω?”√’?a?
struct CMD_GR_LimitAccounts
{
	DWORD							dwTargetUserID;						//??±í”√a?
};

//????…?÷√
struct CMD_GR_SetUserRight
{
	//??±í”√a?
	DWORD							dwTargetUserID;						//??±í”√a?

	//∞???±‰??
	BYTE							cbGameRight;						//’?∫≈????
	BYTE							cbAccountsRight;					//’?∫≈????

	//????±‰a?
	BYTE							cbLimitRoomChat;					//￥???????
	BYTE							cbLimitGameChat;					//”??∑????
	BYTE							cbLimitPlayGame;					//”??∑????
	BYTE							cbLimitSendWisper;					//∑￠à????￠
	BYTE							cbLimitLookonGame;					//≈‘π�????
};

//–?∏?±???????
struct CMD_CS_MatchData
{
	DWORD								dwUserID;							//”√a? I D
	tagUserGold							UserGold;							//”√a?Ω?±“

};
//…?÷√±í÷?
#define OSF_ROOM_CHAT				1									//￥???????
#define OSF_GAME_CHAT				2									//”??∑????
#define OSF_ROOM_WISPER				3									//￥???àΩ??
#define OSF_ENTER_GAME				4									//Ωˉ??”??∑
#define OSF_ENTER_ROOM				5									//Ωˉ??∑?o‰
#define OSF_SHALL_CLOSE				6									//o￥Ω′π?±’

//∑?o‰…?÷√
struct CMD_GR_OptionServer
{
	BYTE							cbOptionFlags;						//…?÷√±í÷?
	BYTE							cbOptionValue;						//…?÷√±í÷?
};

//////////////////////////////////////////////////////////////////////////
//?μ?≥????∞?

#define MDM_GR_SYSTEM				10									//?μ?≥–≈?￠

#define SUB_GR_MESSAGE				100									//?μ?≥???￠

//???￠??–?
#define SMT_INFO					0x0001								//–≈?￠???￠
#define SMT_EJECT					0x0002								//μ?≥????￠
#define SMT_GLOBAL					0x0004								//?′?÷???￠

#define SMT_CONNECT_NEXT			0x0008								//??÷??¨Ω”??“a∏?∑??ò??
#define SMT_TABLE_ROLL				0x0010							   //”??∑??√êπ??????￠ 2009-12-9 hjw add
#define SMT_TABLE_FIX				0x0020							   //”??∑??√êπ??????￠ 2009-12-11 hjw add
#define SMT_TABLE_WINTIP			0x0040							   //￥?”?o“?·??
#define SMT_TABLE_ANI				0x0080							   //a∞∑—μ???a≠

#define SMT_CLOSE_ROOM				0x1000								//π?±’∑?o‰
#define SMT_INTERMIT_LINE			0x4000								//÷–???¨Ω”

//???￠????∞?
struct CMD_GR_Message
{
	WORD							wMessageType;						//???￠??–?
	WORD							wMessageLength;						//???￠≥§??
	char							szContent[1024];					//???￠????
};

////版本信息
//struct CMD_GF_Info
//{
//	BYTE								bAllowLookon;					//旁观标志
//};
//////////////////////////////////////////////////////////////////////////
//∑?o‰????∞?

#define MDM_GR_SERVER_INFO			11									//∑?o‰–≈?￠

#define SUB_GR_ONLINE_COUNT_INFO	100									//‘???–≈?￠

//?à??–≈?￠
struct tagOnLineCountInfo
{
	WORD							wKindID;							//??–?±í??
	DWORD							dwOnLineCount;						//‘????à??
};

/////////////////////////////////////////////////////////////////?¨?”￡¨9.21
//VIP???”–≈?￠
struct tagVIPTableInfo
{
	WORD							wTableID;							//???”∫≈
	char							szPassWord[PASS_LEN];				//???”√???
	bool							bTablePassWord;						//￥à???”??∑ò”–√???
	LONG							lCellScore;							//±???
};


//////////////////////////////////////////////////////////////////////////
//控制事件
struct NTY_ControlEvent
{
	WORD							wControlID;							//控制标识
};

//定时器事件
//struct NTY_TimerEvent
//{
//	DWORD							dwTimerID;							/标识
//	WPARAM							dwBindParameter;					//绑定参数
//};

//数据库事件
struct NTY_DataBaseEvent
{
	WORD							wRequestID;							//请求标识
	DWORD							dwContextID;						//对象标识
};

//读取事件
struct NTY_TCPSocketReadEvent
{
	WORD							wDataSize;							//数据大小
	WORD							wServiceID;							//服务标识
	CMD_Command						Command;							//命令信息
};

//关闭事件
struct NTY_TCPSocketCloseEvent
{
	WORD							wServiceID;							//服务标识
	BYTE							cbShutReason;						//关闭原因
};

//连接事件
struct NTY_TCPSocketConnectEvent
{
	int								nErrorCode;							//错误代码
	WORD							wServiceID;							//服务标识
};

//应答事件
struct NTY_TCPNetworkAcceptEvent
{
	DWORD							dwSocketID;							//网络标识
	DWORD							dwClientIP;							//连接地址
};

//读取事件
struct NTY_TCPNetworkReadEvent
{
	WORD							wDataSize;							//数据大小
	DWORD							dwSocketID;							//网络标识
	CMD_Command						Command;							//命令信息
};

//关闭事件
struct NTY_TCPNetworkCloseEvent
{
	DWORD							dwSocketID;							//网络标识
	DWORD							dwClientIP;							//连接地址
	DWORD							dwActiveTime;						//连接时间
};


#endif
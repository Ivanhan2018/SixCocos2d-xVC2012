
#ifndef __SDH__gameFrame__
#define __SDH__gameFrame__

#include <iostream>
#include "common/GlobalDef.h"
#include "common/CMD_Plaza.h"
#include "net/TcpNetwork.h"
#include "event/GBEvent.h"
#include "ans/BaseObject.h"
#include "globalUnits/GlobalUnits.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma comment(lib, "WS2_32.lib")
#endif

using namespace cocos2d;
// 数据分类
typedef enum
{
	CMD_Default     = 0,		// 默认
	CMD_Logon		= 1,		// 登录
	CMD_Room		= 2,		// 房间
	CMD_Game		= 3,		// 游戏
	CMD_End         = 10,		// 结束

}DataType;

class MsgDispatch : public BaseObject,cocos2d::CCObject
{
public:

	MsgDispatch();

	~MsgDispatch();

	bool init();

	//登陆消息读取
	bool onEventTcpLoginRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize);

	//房间信息读取			add by wangjun 2014-12-15
	bool  OnEventTcpRoomRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize);

	//游戏消息读取
	bool  OnEventTcpGameRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize);

	//void onDispatch(float dt);

	virtual void update(float dt);

	void onEventSocketRecv(GBEventConstArg& arg);

	void dispEntityMsg(CMD_Command* pCommand, void * pBuffer, WORD wDataSize,GBEVENT_ID eid);
	/******************************登陆服务器消息*******************************************/
	//登录消息
	bool			onSocketMainLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//列表消息
	bool			onSocketMainServerList(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//系统消息
	bool			onSocketMainSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//用户消息
	bool			onSocketMainUser(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);


	/******************************游戏服务器消息*******************************************/
	//登录消息
	bool			OnSocketGameLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//用户消息
	bool			OnSocketGameUser(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//配置信息
	bool			OnSocketGameInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//状态信息
	bool			OnSocketGameStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//系统消息
	bool            OnSocketGameSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//房间信息
	bool            OnSocketGameServerInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);

	/******************************游戏服务器用户消息*******************************************/

	//设置回调接口（用来区分消息类型）
	void setTcpSink(BaseObject* obj);

	//用户登陆
	void setUserLogin(string account,string password,bool bAnonymous = false);

	//用户注册
	void setUserRegister(string account,string password,int nfaceId,int nGender, int visiter);

	//匿名登陆
	void setAnonymous();

	//发送登陆包
	bool sendLoginPacket();

	//第三方支付
	void sendOrderInfo(const char* PayName,int chargeNum);

	//修改昵称
	void modifyNickName(const char* nickName);

	//修改头像
	void modifyTouxiang(int nHand,int nSex);

	//          卡
	void isLnadCardRecarge(const char* cardNum,const char* cardPass);

	//电话卡
	void phoneCardRechange(const char* cardType,const char* cardFree,const char* cardNum,const char* cardPass);

	//获得登陆奖励
	void getLoginAward();

	//得到版本
	void getVersion();

	//修改密码
	void modifyPassWord(string oldPassword,string newPassword);

	//领取每日奖励
	void getDarlyAward(int taskID);

	//获得下载奖励（情况）
	void getDownLoadAward(int gameID,int subcmd);

	//完善注册
	void overRegist(string newAccount,string newPassword);

	// 领取救济金
	void getRelieve(int nUserID);

	//发送赠送包
	void sendScoreGiftPacket(const char* szAccount,long lValue);

	//发送金币话费领取包
	void sendChargePacket(int ntype,const char* des);

	//找回密码
	void findPassword(const char* szAccount);

	//发送数据
	void sendSocketDate(WORD wMainCmdID,WORD wSubCmdID);

	//发送数据
	void sendSocketDate(WORD wMainCmdID,WORD wSubCmdID, void * pData, WORD wDataSize);

	void SendPacketWithCompilatio(int tag);
	//连接登陆服务器(是否直接登陆)
	bool connectLoginServer();

	//连接游戏服务器
	bool connectGameServer(int nGameKindId);
	//连接游戏服务器
	bool connectGameServerAdr(DWORD dwAdrIP, WORD wPort);

	//发送数据
	void sendSocketDate(WORD wSubCmdID, void * pData, WORD wDataSize);
	//发送表情、文字      add by wangjun 2014-12-10
	void sendFrameDate(WORD wSubCmdID, void * pData, WORD wDataSize);

	//发送数据
	void sendSocketDate(WORD wSubCmdID);

	//设置登陆状态
	void setLoginState(enLoginState state);

	//发送排队请求
	void sendQueuePacket(int cbQueueCell = 0);

	//获取服务器配置信息
	void sendGetConfigPacket(int nVersion);

	//获取登陆状态
	enLoginState getLoginState() { return m_loginState; }

	//关闭登陆连接
	void closeLoginSocket();

	//关闭游戏服务连接
	void closeGameSocket();

	//获取全服总人数
	DWORD getServerOnLineCount();

	//获取mac地址
	std::string& getMacaddress();

	//设置匿名登陆
	bool getAnonymous() { return m_bAnonymous; }
	void setAnonymous(bool bAnonymous) { m_bAnonymous = m_bAnonymous; }

	//设置注册登陆
	bool isRegLogin() 
	{
		return m_bRegLogin; 
	}
	void setRegLogin(bool bReg) 
	{ 
		m_bRegLogin = bReg; 
	}

	int getLevelbyScore(LONG lScore);
	int getBaseCell(int type,int nLevel);   //获取倍率

	void setGameStatus(bool bStatus);
	bool isGameStatuc() { return  m_bGameStatus; }
	bool isGameLinkOK(){return m_pClientGameSock->isConectServer();};

	//-----------主命令码分类-------------------
	//-------------大厅登录--------------
	//登录消息      add by wangjun 2014-12-10
	bool OnTCPNetworkMainMBLogon(int wSubCmdID, void *buffer, WORD size);		  				
	//列表消息		add by wangjun 2014-12-10
	bool OnTCPNetworkMainMBServerList(int wSubCmdID, void *buffer, WORD size);						
	//服务消息		add by wangjun 2014-12-10
	bool OnTCPNetworkMainMBIphoneUserService(int wSubCmdID, void *buffer, WORD size);	

	//---------------------大厅登录子命令码处理--------------------------
	//登录成功      add by wangjun 2014-12-10
	bool OnSocketSubLogonSuccess(void *buffer, WORD size);					
	//登录失败      add by wangjun 2014-12-10
	bool OnSocketSubLogonFailure(void *buffer, WORD size);				

	//---------------------列表处理子命令码处理--------------------------
	//列表获取      add by wangjun 2014-12-10
	bool OnSocketSubListKind(void *buffer, WORD size);					
	//房间列表      add by wangjun 2014-12-10
	bool OnSocketSubListServer(void *buffer, WORD size);				
	//列表完成      add by wangjun 2014-12-10
	bool OnSocketSubListFinish(void *buffer, WORD size);	

	//登陆房间      add by wangjun 2014-12-10
	bool connectGameServer();
	void SendPacketWithEnterRoomPageCount(WORD count);

	//设置和获取StartType      add by wangjun 2014-12-10
	bool getStartType(){return m_bStartType;};
	void setStartType(bool type){m_bStartType = type;};

	//设置BehaviorFlag      add by wangjun 2014-12-10
	WORD getBehaviorFlag(){return m_wBehaviorFlags;};
	void setBehaviorFlag(WORD flag){m_wBehaviorFlags = flag;};

	//发送游戏规则      add by wangjun 2014-12-10
	void SendPacketWithGameOption();

	//获取用户 或申请用户信息
	void SendPacketWithRequestUserInfo(DWORD dwUserID, WORD wTableID);
	void SendPacketWithRequestChairUserInfo(WORD wTableID, WORD wChairID);
	//请求发送自己桌子的用户信息
	void SendPacketWithRequestMyTableUserInfo(int playerNum);

	//发送换桌消息      add by wangjun 2014-12-22
	void SendPacketWithChangeTable();

	//发送用户状态      add by wangjun 2014-12-22
	void SendPacketWithUserStatus(BYTE status);

	//查询保险柜信息      add by wangjun 2014-12-22
	void SendPacketWithQueryBankInfo();

	//保险柜命令      add by wangjun 2014-12-22
	bool OnTCPNetworkBankInsure(WORD wSubCmdID, void* pBuffer, WORD wDataSize);			
	//保险柜信息      add by wangjun 2014-12-10
	bool OnSocketWithInsureInfo(void *buffer, WORD size);			
	//查询保险柜成功      add by wangjun 2014-12-10
	bool OnSocketWithBankSucceed(void *buffer, WORD size);			
	//查询保险柜失败      add by wangjun 2014-12-10
	bool OnSocketWithBankFailure(void *buffer, WORD size);	

	//发送存款消息      add by wangjun 2014-12-22
	void SendPacketWithDeposit(SCORE score);

	//发送取款消息      add by wangjun 2014-12-22
	void SendPacketWithWithdraw(SCORE score, string password);

	//发送赠送消息      add by wangjun 2014-12-22
	void SendPacketWithSendScore(string nickname, SCORE score, string password, BYTE byNickName);

	/*********用户请求**********/
	//请求起立
	void SendPacketWithPerformStandup(WORD wTableID = INVALID_TABLE, WORD wChairID = INVALID_CHAIR, BYTE cbForceLeave = 1);

public:
	LONG m_lUserLevel[7];             //用户等级
private:
	ClientSock*   m_pClientLoginSock;
	ClientSock*   m_pClientGameSock;
	bool         m_bAnonymous;      //是否匿名登陆
	bool         m_bRegLogin;       //是否注册登陆
private:
	int m_dwRecvPacketCount;

	WORD m_wRecvSize;
	BYTE m_cbRecvBuff[81920];

private:
	CServerListMgr m_ServerListMgr;
	typedef std::vector<CMD_GP_UserLevelResult> UserLevel;
	UserLevel m_UserLevelList;
	WORD userServiceSubCmd;
public:
	string m_szAccount;
	string m_szPassword; //密码保存
	enLoginState m_loginState;
	bool  m_bGameStatus;                                  //游戏标识（服务器多次发送切换场景消息 防止客户端多次切换）
	WORD m_wBehaviorFlags;
	DataType m_eDataType;
	bool m_bStartType;

	//用户信息			add by wangjun 2014-12-10
	string					m_pAccounts;					// 用户帐号
	string					m_pPassword;					// 用户密码
	string					m_pBankWord;					// 保险柜密码
	string					m_pNickname;					// 用户昵称
	string					m_pPhoneNum;					// 手机号码


	DWORD						m_dwUserID;						// 用户I D
	DWORD						m_dwGameID;						// 游戏I D
	DWORD						m_dwKindID;						// 类型I D
	WORD						m_wFaceID;						// 用户头像
	BYTE						m_cbGender;						// 用户性别
	SCORE                       m_dwGoldScore;                  // 用户拥有的豆豆
	DWORD                       m_dwExperience;                 // 经验值

	TCHART						m_pPassWordMD5[LEN_MD5];		// md5密码
	TCHART						m_pMachineMD5[LEN_MD5];			// 机器标识

	BYTE						m_cbDeviceType;					// 设备类型

	WORD						m_wTableID;						// 桌子号
	WORD						m_wChairID;						// 椅子号
	BYTE						m_cbStatus;						// 用户状态

	string						m_pSystemMsg;
	WORD                        m_wSystemMsgType;               // 系统类型消息

	//保险柜传回来数据
	WORD										m_wRevenueTake;				//税收
	WORD										m_wRevenueTransfer;			//税收
	WORD										m_wServerID;					//房间标识
	SCORE									m_dwlUserScore;				//用户豆豆
	SCORE									m_dwlUserInsure;				//保险柜豆豆
	SCORE									m_dwlTransferPrerequisite;		//转账条件
	char										szDescribeString[256];			//描述信息
};

#endif /* defined(__SDH__gameFrame__) */

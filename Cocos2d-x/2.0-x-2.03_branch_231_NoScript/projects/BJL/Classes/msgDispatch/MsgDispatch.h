
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
// ���ݷ���
typedef enum
{
	CMD_Default     = 0,		// Ĭ��
	CMD_Logon		= 1,		// ��¼
	CMD_Room		= 2,		// ����
	CMD_Game		= 3,		// ��Ϸ
	CMD_End         = 10,		// ����

}DataType;

class MsgDispatch : public BaseObject,cocos2d::CCObject
{
public:

	MsgDispatch();

	~MsgDispatch();

	bool init();

	//��½��Ϣ��ȡ
	bool onEventTcpLoginRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize);

	//������Ϣ��ȡ			add by wangjun 2014-12-15
	bool  OnEventTcpRoomRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize);

	//��Ϸ��Ϣ��ȡ
	bool  OnEventTcpGameRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize);

	//void onDispatch(float dt);

	virtual void update(float dt);

	void onEventSocketRecv(GBEventConstArg& arg);

	void dispEntityMsg(CMD_Command* pCommand, void * pBuffer, WORD wDataSize,GBEVENT_ID eid);
	/******************************��½��������Ϣ*******************************************/
	//��¼��Ϣ
	bool			onSocketMainLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�б���Ϣ
	bool			onSocketMainServerList(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool			onSocketMainSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool			onSocketMainUser(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);


	/******************************��Ϸ��������Ϣ*******************************************/
	//��¼��Ϣ
	bool			OnSocketGameLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool			OnSocketGameUser(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool			OnSocketGameInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//״̬��Ϣ
	bool			OnSocketGameStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool            OnSocketGameSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool            OnSocketGameServerInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);

	/******************************��Ϸ�������û���Ϣ*******************************************/

	//���ûص��ӿڣ�����������Ϣ���ͣ�
	void setTcpSink(BaseObject* obj);

	//�û���½
	void setUserLogin(string account,string password,bool bAnonymous = false);

	//�û�ע��
	void setUserRegister(string account,string password,int nfaceId,int nGender, int visiter);

	//������½
	void setAnonymous();

	//���͵�½��
	bool sendLoginPacket();

	//������֧��
	void sendOrderInfo(const char* PayName,int chargeNum);

	//�޸��ǳ�
	void modifyNickName(const char* nickName);

	//�޸�ͷ��
	void modifyTouxiang(int nHand,int nSex);

	//          ��
	void isLnadCardRecarge(const char* cardNum,const char* cardPass);

	//�绰��
	void phoneCardRechange(const char* cardType,const char* cardFree,const char* cardNum,const char* cardPass);

	//��õ�½����
	void getLoginAward();

	//�õ��汾
	void getVersion();

	//�޸�����
	void modifyPassWord(string oldPassword,string newPassword);

	//��ȡÿ�ս���
	void getDarlyAward(int taskID);

	//������ؽ����������
	void getDownLoadAward(int gameID,int subcmd);

	//����ע��
	void overRegist(string newAccount,string newPassword);

	// ��ȡ�ȼý�
	void getRelieve(int nUserID);

	//�������Ͱ�
	void sendScoreGiftPacket(const char* szAccount,long lValue);

	//���ͽ�һ�����ȡ��
	void sendChargePacket(int ntype,const char* des);

	//�һ�����
	void findPassword(const char* szAccount);

	//��������
	void sendSocketDate(WORD wMainCmdID,WORD wSubCmdID);

	//��������
	void sendSocketDate(WORD wMainCmdID,WORD wSubCmdID, void * pData, WORD wDataSize);

	void SendPacketWithCompilatio(int tag);
	//���ӵ�½������(�Ƿ�ֱ�ӵ�½)
	bool connectLoginServer();

	//������Ϸ������
	bool connectGameServer(int nGameKindId);
	//������Ϸ������
	bool connectGameServerAdr(DWORD dwAdrIP, WORD wPort);

	//��������
	void sendSocketDate(WORD wSubCmdID, void * pData, WORD wDataSize);
	//���ͱ��顢����      add by wangjun 2014-12-10
	void sendFrameDate(WORD wSubCmdID, void * pData, WORD wDataSize);

	//��������
	void sendSocketDate(WORD wSubCmdID);

	//���õ�½״̬
	void setLoginState(enLoginState state);

	//�����Ŷ�����
	void sendQueuePacket(int cbQueueCell = 0);

	//��ȡ������������Ϣ
	void sendGetConfigPacket(int nVersion);

	//��ȡ��½״̬
	enLoginState getLoginState() { return m_loginState; }

	//�رյ�½����
	void closeLoginSocket();

	//�ر���Ϸ��������
	void closeGameSocket();

	//��ȡȫ��������
	DWORD getServerOnLineCount();

	//��ȡmac��ַ
	std::string& getMacaddress();

	//����������½
	bool getAnonymous() { return m_bAnonymous; }
	void setAnonymous(bool bAnonymous) { m_bAnonymous = m_bAnonymous; }

	//����ע���½
	bool isRegLogin() 
	{
		return m_bRegLogin; 
	}
	void setRegLogin(bool bReg) 
	{ 
		m_bRegLogin = bReg; 
	}

	int getLevelbyScore(LONG lScore);
	int getBaseCell(int type,int nLevel);   //��ȡ����

	void setGameStatus(bool bStatus);
	bool isGameStatuc() { return  m_bGameStatus; }
	bool isGameLinkOK(){return m_pClientGameSock->isConectServer();};

	//-----------�����������-------------------
	//-------------������¼--------------
	//��¼��Ϣ      add by wangjun 2014-12-10
	bool OnTCPNetworkMainMBLogon(int wSubCmdID, void *buffer, WORD size);		  				
	//�б���Ϣ		add by wangjun 2014-12-10
	bool OnTCPNetworkMainMBServerList(int wSubCmdID, void *buffer, WORD size);						
	//������Ϣ		add by wangjun 2014-12-10
	bool OnTCPNetworkMainMBIphoneUserService(int wSubCmdID, void *buffer, WORD size);	

	//---------------------������¼�������봦��--------------------------
	//��¼�ɹ�      add by wangjun 2014-12-10
	bool OnSocketSubLogonSuccess(void *buffer, WORD size);					
	//��¼ʧ��      add by wangjun 2014-12-10
	bool OnSocketSubLogonFailure(void *buffer, WORD size);				

	//---------------------�б����������봦��--------------------------
	//�б��ȡ      add by wangjun 2014-12-10
	bool OnSocketSubListKind(void *buffer, WORD size);					
	//�����б�      add by wangjun 2014-12-10
	bool OnSocketSubListServer(void *buffer, WORD size);				
	//�б����      add by wangjun 2014-12-10
	bool OnSocketSubListFinish(void *buffer, WORD size);	

	//��½����      add by wangjun 2014-12-10
	bool connectGameServer();
	void SendPacketWithEnterRoomPageCount(WORD count);

	//���úͻ�ȡStartType      add by wangjun 2014-12-10
	bool getStartType(){return m_bStartType;};
	void setStartType(bool type){m_bStartType = type;};

	//����BehaviorFlag      add by wangjun 2014-12-10
	WORD getBehaviorFlag(){return m_wBehaviorFlags;};
	void setBehaviorFlag(WORD flag){m_wBehaviorFlags = flag;};

	//������Ϸ����      add by wangjun 2014-12-10
	void SendPacketWithGameOption();

	//��ȡ�û� �������û���Ϣ
	void SendPacketWithRequestUserInfo(DWORD dwUserID, WORD wTableID);
	void SendPacketWithRequestChairUserInfo(WORD wTableID, WORD wChairID);
	//�������Լ����ӵ��û���Ϣ
	void SendPacketWithRequestMyTableUserInfo(int playerNum);

	//���ͻ�����Ϣ      add by wangjun 2014-12-22
	void SendPacketWithChangeTable();

	//�����û�״̬      add by wangjun 2014-12-22
	void SendPacketWithUserStatus(BYTE status);

	//��ѯ���չ���Ϣ      add by wangjun 2014-12-22
	void SendPacketWithQueryBankInfo();

	//���չ�����      add by wangjun 2014-12-22
	bool OnTCPNetworkBankInsure(WORD wSubCmdID, void* pBuffer, WORD wDataSize);			
	//���չ���Ϣ      add by wangjun 2014-12-10
	bool OnSocketWithInsureInfo(void *buffer, WORD size);			
	//��ѯ���չ�ɹ�      add by wangjun 2014-12-10
	bool OnSocketWithBankSucceed(void *buffer, WORD size);			
	//��ѯ���չ�ʧ��      add by wangjun 2014-12-10
	bool OnSocketWithBankFailure(void *buffer, WORD size);	

	//���ʹ����Ϣ      add by wangjun 2014-12-22
	void SendPacketWithDeposit(SCORE score);

	//����ȡ����Ϣ      add by wangjun 2014-12-22
	void SendPacketWithWithdraw(SCORE score, string password);

	//����������Ϣ      add by wangjun 2014-12-22
	void SendPacketWithSendScore(string nickname, SCORE score, string password, BYTE byNickName);

	/*********�û�����**********/
	//��������
	void SendPacketWithPerformStandup(WORD wTableID = INVALID_TABLE, WORD wChairID = INVALID_CHAIR, BYTE cbForceLeave = 1);

public:
	LONG m_lUserLevel[7];             //�û��ȼ�
private:
	ClientSock*   m_pClientLoginSock;
	ClientSock*   m_pClientGameSock;
	bool         m_bAnonymous;      //�Ƿ�������½
	bool         m_bRegLogin;       //�Ƿ�ע���½
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
	string m_szPassword; //���뱣��
	enLoginState m_loginState;
	bool  m_bGameStatus;                                  //��Ϸ��ʶ����������η����л�������Ϣ ��ֹ�ͻ��˶���л���
	WORD m_wBehaviorFlags;
	DataType m_eDataType;
	bool m_bStartType;

	//�û���Ϣ			add by wangjun 2014-12-10
	string					m_pAccounts;					// �û��ʺ�
	string					m_pPassword;					// �û�����
	string					m_pBankWord;					// ���չ�����
	string					m_pNickname;					// �û��ǳ�
	string					m_pPhoneNum;					// �ֻ�����


	DWORD						m_dwUserID;						// �û�I D
	DWORD						m_dwGameID;						// ��ϷI D
	DWORD						m_dwKindID;						// ����I D
	WORD						m_wFaceID;						// �û�ͷ��
	BYTE						m_cbGender;						// �û��Ա�
	SCORE                       m_dwGoldScore;                  // �û�ӵ�еĶ���
	DWORD                       m_dwExperience;                 // ����ֵ

	TCHART						m_pPassWordMD5[LEN_MD5];		// md5����
	TCHART						m_pMachineMD5[LEN_MD5];			// ������ʶ

	BYTE						m_cbDeviceType;					// �豸����

	WORD						m_wTableID;						// ���Ӻ�
	WORD						m_wChairID;						// ���Ӻ�
	BYTE						m_cbStatus;						// �û�״̬

	string						m_pSystemMsg;
	WORD                        m_wSystemMsgType;               // ϵͳ������Ϣ

	//���չ񴫻�������
	WORD										m_wRevenueTake;				//˰��
	WORD										m_wRevenueTransfer;			//˰��
	WORD										m_wServerID;					//�����ʶ
	SCORE									m_dwlUserScore;				//�û�����
	SCORE									m_dwlUserInsure;				//���չ񶹶�
	SCORE									m_dwlTransferPrerequisite;		//ת������
	char										szDescribeString[256];			//������Ϣ
};

#endif /* defined(__SDH__gameFrame__) */


#ifndef FISH_CLIENT_H
#define FISH_CLIENT_H

#include "./CloseType.h"
#include "./BaseTableClient.h"
#include "./UserInfo.h"
#include "../GameMsg/CMD_SanGong.h"	//add by Ivan_han

struct SinglePlayer
{
	SinglePlayer()
	{
		Init();
	}
	void Init()
	{
		memset(this, 0, sizeof(*this));
	}
	//TChip	m_lGameScore;				//������Ϣ
	//TChip	m_lUserChipIn;				//��ע��Ϣ
	//TPlayStatus	m_cbPlayStatus;
	char m_szAccounts[32];//�������
	//TCardData m_cbUserCardData[3];		//�û��˿�
	//unsigned char m_cbUserFinish;//��ɱ�־
	//unsigned char m_cbUserBanker;//��ׯ��־={0,1}
	//unsigned char m_cbUserContinue;//������־
};

class CClientLogic : public IBaseTableClient
{
public:
	CClientLogic(void);
	~CClientLogic(void);

public:
	
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);
	virtual void OnCommError(char* pszError);
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnClose(CLOSE_TYPE iCloseType);

	// ������Ϣ
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

public:

	//--- ��Ϸ�߼����� ---------------------------------

	// ��������Ϣ
	void handle_room_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// �������漰д���ݿ����Ϣ
	void handle_write_db_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// ����������Ϣ
	void handle_table_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// �������Ա��Ϣ
	void handle_magager_msg(int iSubCode, const BYTE* pData, int iDataLen);

public:
	int ConnectRoom(string str[5]);
private:
	//vector<USER_INFO> vecUserInfo;	// �û��б�

public:
	//��Ϸ״̬
	e_GameState m_byGameState;

	SinglePlayer m_Players[GAME_PLAYER_COUNT];

	//��ǰ�ͻ��˵��û���Ϣ
	USER_INFO_SIM m_MeUserInfo;

	SERVER_ROOM_INFO_SIM m_roomInfo;

	//ׯ���û�,S:�û����»��յ���ׯ��Ϣʱ��д���������C:�յ�ׯ���û���Ϣ��Ϣʱ��д�������
	TChairID m_wBankerUser;

	//��Ϸ����
	unsigned short int	m_wDrawCount;

	//true�������û���false��ͨ�����û�
	bool m_IsAndroid;
};

#endif


#include "ConnectCenterServer.h"

#if _DEBUG	
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreClientShell64_d.lib") 
#else
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreClientShell64.lib") 
#endif

CConnectCenterServer::CConnectCenterServer(void)
{

}

CConnectCenterServer::~CConnectCenterServer(void)
{
	// ������Դ
}

// ��Ӧ���ӳɹ�
void CConnectCenterServer::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	COften::OutputInfo("�������ķ������ɹ�");
	CMD_GameServer_Register gameRegister;
	SetRegisterInfo(gameRegister);
	send_data(MAIN_GCG_GAME, SUB_GC_GAME_REGISTER, (BYTE*)(&gameRegister), sizeof(CMD_GameServer_Register));
}

// ��Ӧ����ʧ��
void CConnectCenterServer::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	COften::OutputError("�������ķ�����ʧ��");
}

// ��Ӧ���ͳɹ�
void CConnectCenterServer::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{

}

// ��Ӧ����ʧ�ܣ�
void CConnectCenterServer::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	COften::OutputError("������Ϣʧ��");
}

// ��Ӧ�رշ����
void CConnectCenterServer::OnClose(CLOSE_TYPE iCloseType)
{
	COften::OutputError("���ķ������Ѿ��Ͽ�");
}

// ��ӦͨѶ�������Ϣ
void CConnectCenterServer::OnCommError(char* pszError)
{

}

/* --------------------------------------------------------------------------
����˵������Ӧ�հ���Ϣ
���������
	pData		�յ�������
	iDataLen	�յ������ݵĳ���
--------------------------------------------------------------------------*/
void CConnectCenterServer::OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{

}

// ����ע����Ϣ
void CConnectCenterServer::SetRegisterInfo(CMD_GameServer_Register &gameRegister)
{
	gameRegister.lParentId = m_Config.lParentId;						// ���ڵ㣨�ؿ� 1:������;2:�м���....��..
	gameRegister.iGameID = m_Config.iGameId;							// ��ϷID(���磺1����; 2������; 3�齫...)
	gameRegister.iRoomType = m_Config.iRoomType;						// ��Ϸ����(1=���ַ��䡢2=�����Ϸ��3=������Ϸ)..
	gameRegister.iRoomId = m_Config.iRoomId;							// ����ID
	gameRegister.lRoomTeltComIp = m_Config.lRoomTeltComIp;				// ������й�����IP
	gameRegister.lRoomUnicomIp = m_Config.lRoomUnicomIp;				// ������й���ͨIP
	gameRegister.lRoomMobileIp = m_Config.lRoomMobileIp;				// ������й��ƶ�IP
	gameRegister.iRoomPort = m_Config.iRoomPort;						// ����˿�
	memcpy(m_Config.szRoomName, gameRegister.szRoomName, ROOM_NAME_LEN);// ��������
	gameRegister.bAutoSit = m_Config.bAutoSit;							// �Ƿ��Զ�����(0:���Զ�����Ҫ�ֶ������������ӽ���; 1:�Զ�����������Ҫ������Ӻ�)
	gameRegister.iBasePoint = m_Config.iBasePoint;						// ����..
	gameRegister.iDoorsill = m_Config.iDoorsill;						// �����ż�
	gameRegister.iMaxDoorsill = m_Config.iMaxDoorsill;					// ��߽����ż�
	gameRegister.iTables = m_Config.iTables;							// �������ӵ�����
	gameRegister.iSeatNum = m_Config.iSeatNum;							// ÿ����������ÿ������λ����

	gameRegister.iEnterTradeGold = m_Config.iEnterTradeGold;			// ������(���)
	gameRegister.iEnterTradePoint = m_Config.iEnterTradePoint;			// ������(����)
	gameRegister.iRewardGold1 = m_Config.iRewardGold1;					// ��һ������
	gameRegister.iRewardGold2 = m_Config.iRewardGold2;					// �ڶ�������
}
#ifndef CONNECT_CENTER_SERVER_H
#define CONNECT_CENTER_SERVER_H

#include "CoreClient.h"
#include "PublicHead.h"
#include "CMD_InnerServer.h"
#include "RoomInfo.h"

class CConnectCenterServer : public CCoreClient
{
public:
	CConnectCenterServer();

	~CConnectCenterServer();
	
public:
	//--- �ص����� -----------------------------------------------B--
	// ��Ӧ���ӳɹ�
	void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);

	// ��Ӧ����ʧ��
	void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);

	// ��Ӧ���ͳɹ�
	void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// ��Ӧ����ʧ�ܣ�
	void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// ��Ӧ�رշ����
	void OnClose(CLOSE_TYPE iCloseType);

	/* --------------------------------------------------------------------------
	����˵������Ӧ�հ���Ϣ
	���������
		pData		�յ�������
		iDataLen	�յ������ݵĳ���
	--------------------------------------------------------------------------*/
	void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// ��ӦͨѶ�������Ϣ
	void OnCommError(char* pszError);

private:
	void SetRegisterInfo(CMD_GameServer_Register &gameRegister);

public:
	SERVER_ROOM_INFO m_Config;		// ����������

};

#endif
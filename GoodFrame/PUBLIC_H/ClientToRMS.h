/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\ClientToRMS.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	ClientToRMS
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef CLIENT_TO_RMS_H
#define CLIENT_TO_RMS_H

#include "./CoreClient.h"
#include "./GameSkeletonID.h"

#include "./EasyDataTime.h"
#include "./RoomInfo.h"

#include <vector>
using std::vector;

class CGameServerSkeleton;

// �ͻ��ˣ�Ŀ�������ӷ��ܷ����� RMS��RoomMgrServer ��
class CClientToRMS : public CCoreClient	// ���õ���ģʽ������Ϊһ�������п����ж���ͻ��ˡ�
{
public:
	friend class CGameServerSkeleton;

public:
	CClientToRMS(void);
	~CClientToRMS(void);

protected:		
	//--- �ص����� ------------------------

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

public:
	// ������Ϸ����Ǽܵ�ָ��
	void set_truck_server(CGameServerSkeleton* pTrunkServer);

	// ���÷��������ļ��Ĳ���
	void set_room_config(const ROOM_CONFIG& roomConfig);

public:
	SERVER_ROOM_INFO	m_stServerRoomInfo;	// ������Ϣ
	ROOM_CONFIG			m_stRoomConfig;		// ���������ļ�
private:
	CGameServerSkeleton* m_pTrunkServer;

	LONGLONG	lConnTime;	// ���Ϸ��ܵ�ʱ��
};

#endif
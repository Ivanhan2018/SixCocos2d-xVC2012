
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:43
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\GameServerSkeleton.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	GameServerSkeleton
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef SAMPLE_SERVER_H
#define SAMPLE_SERVER_H

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN

#include "./CoreServer.h"	// �ں˷���˵�ͷ�ļ�
#include "./Singleton.h"

#include "./ClientToRMS.h"
#include "./LogicSkeleton.h"
#include "./DbSkeleton.h"

#include "./IRoomMgr.h"
#include "./IDbAnyGame.h"

class IBaseTable;

// ��Ϸ����Ǽ�
class __declspec(dllexport) CGameServerSkeleton  : public CCoreServer 
{
public:
	friend class CClientToRMS;
public:
	CGameServerSkeleton(void);
	~CGameServerSkeleton(void);

public:

	// ��÷�������
	ROOM_CONFIG get_room_config();

	/* --------------------------------------------------------------------------
	����˵�������÷��������ļ��Ĳ���
	���������
		roomConfig	�������ò������ο� RoomConfig.ini
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int set_room_config(const char *roomConfig="Config/RoomConfig.ini");

	// ��Ϸ����Ǽܵİ汾��
	int get_skeleton_ver(char* pszVerNo, int iLen);

	// ���ӷ��ܷ����� RMS��RoomMgrServer ��
	int create_client_to_rms(const CLIENT_TO_RMS_PARAM& rms);

	// �Ͽ����ܷ����� RMS��RoomMgrServer ��
	int destroy_client_to_rms();

	/* --------------------------------------------------------------------------
	����˵������ʼ���������� start ����֮ǰִ�б�����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10  ������Ϣ��ʧ��
	--------------------------------------------------------------------------*/
	virtual int init();

	// �ͷ���Դ�������� stop ����֮��ִ�б�����
	virtual int uninit();

	// ��ʼ�������� init  ����֮��ִ�б�����
	virtual int start();

	// ������������ uninit ����֮ǰִ�б�����
	virtual int stop();

	// �����������ӵ���Ϸ��ʼ�Ķ�ʱ��
	void destroy_game_start_timer();

	// ��÷�������ָ��
	IRoomMgr* CGameServerSkeleton::get_room_mgr();

public:
	//--- ����Ҫ�̳еĴ��麯�� -----------------------------------

	// ��������ʵ��
	virtual IRoomMgr* create_room_mgr(SERVER_ROOM_INFO serverRoomInfo) = 0;

	// ���ٷ���ʵ��
	virtual void destroy_room_mgr() = 0;

	// ��������Ⱥʵ��
	virtual int create_table() = 0;

	// ��������Ⱥʵ��
	virtual void destroy_table() = 0;

	// �������ݿ�ʵ��
	virtual IDbAnyGame*	create_db() = 0;

	// �������ݿ�ʵ��
	virtual void destroy_db() = 0;

	// ���ܷ�����Ϣ��ȡ���
	virtual int OnRoomMgrServerOk(SERVER_ROOM_INFO serverRoomInfo, ROOM_CONFIG roomConfig) = 0;

public:
	//--- �ص����� -----------------------------------------------

	// ��Ӧ�Զ��ѹر���
	virtual int OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType);

	// ��Ӧ���ͳɹ�
	virtual void OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// ��Ӧ����ʧ��
	virtual void OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// ��Ӧ���ӳɹ�
	virtual void OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr);	

	// ��Ӧ����ʧ��
	virtual void OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode);

	// ��ʱ����Ӧ
	virtual int OnTimer(LONGLONG iIDEvent);

	/* --------------------------------------------------------------------------
	����˵������Ӧ����������
	���������
		lChannelNo	������˶Ͽ���ͨ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int OnNoHeartbeatDie(LONGLONG lChannelNo);

	// ������Ϣ
	virtual int OnIsHeartbeat(long long lChannelNo);

	/* --------------------------------------------------------------------------
	����˵������Ӧ�հ���Ϣ
	���������
		lChannelNo
	����������
		pRecv		��Ϣ�飬�Ѿ���ԭ�Ӱ��ˡ�ע�⣺Ҫ�õײ��ܵĻ��ƹ��
	--------------------------------------------------------------------------*/
	virtual void OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv);

	/* --------------------------------------------------------------------------
	����˵������Ӧ����������������Ϣ
	���������
		pData		�յ�������
		iDataLen	�յ������ݵĳ���
	--------------------------------------------------------------------------*/
	virtual void OnSkeletonRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	


public:
	// ������Ϸ��ʼ�����ͣ�iType �ο� GAME_BEGIN_TYPE_AUTO ��
	void game_begin_type(int iType);

	// �����Ϸ��ʼ�����ͣ� ����ֵ�ο� GAME_BEGIN_TYPE_AUTO ��
	int game_begin_type();

public:

	CClientToRMS* m_pClientToRMS;
	

	CLogicSkeleton*		m_pLogic;		// �߼�
	CDbSkeleton*		m_pMyDB;		// ���ݿ�

	IRoomMgr*	m_pRoomMgr;		// �������
	IDbAnyGame*	m_pDbAnyGame;

private:
	ROOM_CONFIG			m_stRoomConfig;		// ���������ļ�

	int	m_iVerNo;	// �汾��
	int	m_iGameBeginType;	// ��Ϸ��ʼ�����ͣ��ο� GAME_BEGIN_TYPE_AUTO ��

	bool m_bStartFinish;	// �������
};

#endif
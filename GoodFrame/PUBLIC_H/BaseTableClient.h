
#ifndef BASE_DESK_CLIENT
#define BASE_DESK_CLIENT

#include "./CloseType.h"
#include "./UserInfo.h"
#include "./TableInfo.h"
#include "./RoomInfo.h"
#include "./GameSkeletonMsgCode.h"

class CGameClientTransfer;

#ifdef WIN32
class  __declspec(dllexport) IBaseTableClient
#else
class  IBaseTableClient
#endif
{
public:
	friend class CGameClientTransfer;

public:
	IBaseTableClient(void);
	~IBaseTableClient(void);

public:

	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect)=0;
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)=0;
	virtual void OnCommError(char* pszError)=0;
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;
	virtual void OnClose(CLOSE_TYPE iCloseType)=0;
	/* --------------------------------------------------------------------------
	����˵������Ӧ�հ���Ϣ
	���������
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���
	--------------------------------------------------------------------------*/
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	int init(const CLIENT_ROOM_INFO& vRoomClientInfo, const CLIENT_FRAME_PARAM& vFrameParam);

	int start();
	
	int stop();

	//// ��������
	//int send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);
	// Add by Cool.Cat
	int send_data(int iMainCode, int iSubCode, void *pData, int iDataLen);
	int send_data(int iMainCode, int iSubCode);

	/* --------------------------------------------------------------------------
	����˵�����رշ����
	���������
		bClientClose	TRUE��ʾ�ͻ��������رգ�FALSE��ʾ������˹رյ�
	����ֵ��
		�ɹ��򷵻� TRUE�����򷵻� FALSE ��
	--------------------------------------------------------------------------*/
	bool close(CLOSE_TYPE iCloseType);

	/* --------------------------------------------------------------------------
	����˵������¼����
	���������
		���ID
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int login_room();

	// �뿪����
	int leave_room();

	// ����
	int sit_down(int iTableNo, int iSeatNo);

	/* --------------------------------------------------------------------------
	����˵�����ܹ���ʼ��Ϸ�����º����Ϣ���ͻ���Ҫ�ȵ���ʼ����Ϻ󣬷�����Ϣ������˲ŷ���
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int raise_hand();

	// ����
	int leave_seat();

	// ���뷿���ڵ��û��б�
	int query_user_list();

	// д��
	int write_score(const CMD_WRITE_SCORE& score);

public:

	// ��һ������������뷿
	int tick_one_leave_seat(int iTableNo, int iSeatNo);

	// ��һ���������
	int tick_table_leave_seat(int iTableNo);

	// �������������������
	int tick_all_leave_seat();

	// ������뷿
	int tick_user_out_room(int iTableNo, int iSeatNo);

	// ��һ�������е�����뷿
	int tick_user_out_room(int iTableNo);

	// �����е�����뷿
	int tick_user_out_room();

	//add by Ivan_han 20130929
	void setUserID(LONGLONG lUserID);

public:
	LOGIN_ROOM_SUCC	m_stLoginSucc;	// ��¼�ɹ���һЩ��Ϣ

	CLIENT_ROOM_INFO GetRoomInfo();

private:
	CGameClientTransfer* m_pGameClientTransfer;

	CLIENT_ROOM_INFO	m_stRoomInfo;
	
	LONGLONG m_lUserID;	// �û�ID���ڷ����Ψһ�ĺϷ���ʶ��

};

#endif

#ifndef CORE_CLIENT_H
#define CORE_CLIENT_H

#include <WinSock2.h>

#include "./CloseType.h"
#include "./MemBlockPool.h"
#include "./Log.h"

class __declspec(dllexport)  CCommTcpClient;

#include <hash_map>
using std::hash_map;
using std::pair;

// ���಻���õ���ģʽ������Ϊһ�������п����ж���ͻ��ˡ�
class __declspec(dllexport) CCoreClient
{
public:
	CCoreClient(void);
	~CCoreClient(void);

	

public:
	
	// ������Ϣ��ĳ���
	void set_msg_block_size(int iMsgBlockSize=2048);

	// ������Ϣ�ص����Ԫ������
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	// ���÷��ͽ���ص����Ԫ������
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// ���ö��������ļ��ʱ�䣬��λms
	void set_reconnect_interval_time(int iAutoReConnectTime);

	// ��ö�������
	bool get_reconnect();

	// ���ö�������
	void set_reconnect(bool bAutoReConnect);

	// ��ùرշ�ʽ
	CLOSE_TYPE get_close_type();

	// ���ùرշ�ʽ
	void set_close_type(CLOSE_TYPE iCloseType);

	// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
	void set_shrink_pools_time(LONGLONG iShrinkPoolsTime);

	// ���÷�����������ʱ��
	void set_send_heartbeat_time(LONGLONG iSendHeartbeatTime);

	// ������־��·��
	int set_log_path(TCHAR* pszPathName);

	/* --------------------------------------------------------------------------
	����˵������ʼ��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10  ִ�� WSAStartup ʧ��
		20  ������Ϣ��ʧ��
		40  �������ͽ����ʧ��
		50  m_hConnection ִ�� WSASocket ʧ��
		60  CreateIoCompletionPort ʧ��
		70  ���� IOCP �Ĺ����߳�ʧ��
		90  ������ʱ�����߳�ʧ��
	--------------------------------------------------------------------------*/
	int init();

	// ����
	int start();

	// ֹͣ
	int stop();

	/* --------------------------------------------------------------------------
	����˵������������
	���������
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���
	--------------------------------------------------------------------------*/
	int send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	/* --------------------------------------------------------------------------
	����˵�������ʹ������ݣ����ڲ���
	���������
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���
	--------------------------------------------------------------------------*/
	int send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// �������ӵ�ַ
	void set_connect_addr(const char* szListenAddr);

	// �������Ӷ˿�
	void set_connect_port(unsigned int nPort);

	// ����С�������
	int OnRecvComplete(int iResult, const CMemBlock* pRecv);

	// �����رշ���ˣ�Ŀ�����÷������������ͻ��������ر�������
	int power_close();

	/* --------------------------------------------------------------------------
	����˵������ӡδ��أ��ڳ��⣩��Ԫ��
	����������
		vecOutPool	δ��أ��ڳ��⣩��Ԫ������
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	void display_out_pool(bool bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool);
		
	// ��ʾ���еĳ���Ϣ
	void display_all_pool();

	// ����������
	int send_heartbeat_packeg();

	/* --------------------------------------------------------------------------
	����˵����д����־���
	���������
		iType	���ͣ��ο� LOG_ERR_TYPE ö�٣�
					LOG_TYPE_PROMPT = 0,	// ��ʾ
					LOG_TYPE_WARING = 1,	// ����
					LOG_TYPE_ERR = 2,		// �������쳣

		pszSentence		��־���
		iSentenceLen	��־���ĳ���
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int write_log(int iType, TCHAR* pszSentence, int iSentenceLen);

	/* --------------------------------------------------------------------------
	����˵����д����־��䣬���� Debug ����Ч��Release �в�д�ģ�Ŀ���Ƿ����ڽű��е���
	���������
		iType	���ͣ��ο� LOG_ERR_TYPE ö�٣�
					LOG_TYPE_PROMPT = 0,	// ��ʾ
					LOG_TYPE_WARING = 1,	// ����
					LOG_TYPE_ERR = 2,		// �������쳣

		pszSentence		��־���
		iSentenceLen	��־���ĳ���
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int write_log_debug(int iType, TCHAR* pszSentence, int iSentenceLen);

public:		
	//--- �ص����� ------------------------

	/* --------------------------------------------------------------------------
	����˵������Ӧ���ӳɹ�
	���������
		bIsReconnect	�Ƿ�����
		addrConnect		SOCKET ��ַ
	--------------------------------------------------------------------------*/
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect) = 0;

	// ��Ӧ����ʧ��
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect) = 0;

	/* --------------------------------------------------------------------------
	����˵������Ӧ���ͳɹ�
	���������
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���
	--------------------------------------------------------------------------*/
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	/* --------------------------------------------------------------------------
	����˵������Ӧ����ʧ��
	���������
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���
	--------------------------------------------------------------------------*/
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;
	
	/* --------------------------------------------------------------------------
	����˵������Ӧ�رշ����
	���������
		bClientClose	�Ƿ�ͻ��˹ر�
	--------------------------------------------------------------------------*/
	virtual void OnClose(CLOSE_TYPE iCloseType) = 0;

	/* --------------------------------------------------------------------------
	����˵������Ӧ�հ���Ϣ
	���������
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���
	--------------------------------------------------------------------------*/
	virtual void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	// ��ӦͨѶ�������Ϣ
	virtual void OnCommError(char* pszError) = 0;

private:
	CCommTcpClient* m_pTcpClient;	// TCP ͨѶ�㣬�޷��� CCoreServer ������ֱ��ʹ�ã�����˵��δ����ı�����
									// ֻ��ͨ�� CCoreServer �ĺ�������װ CCommTcpServer �еĹ���

	wstring		m_strPath;		// ��־��·��
	CLog*		m_pLogPrompt;	// ��ʾ��־��
	CLog*		m_pLogWaring;	// ������־��
	CLog*		m_pLogErr;		// �������쳣��־


};

#endif
#ifndef SAMPLE_CLIENT_H
#define SAMPLE_CLIENT_H

#include "../PUBLIC_H/CoreClient.h"//CCoreClient
#include "../common/GerneralListen.h"//CGerneralSink

// �ͻ���ͨ���ࡣ���õ���ģʽ������Ϊһ�������п����ж���ͻ���ͨ����ʵ����
class CClientComm : public CGerneralSink, public CCoreClient
{
public:
	friend class CDataManageDlg;

public:
	CClientComm(void);
	~CClientComm(void);

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
	virtual void OnClose(CLOSE_TYPE iCloseType);

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
	// ����һ����Ϣ
	void test04();

	// д����־�ļ�
	void test11();

private:

};

#endif
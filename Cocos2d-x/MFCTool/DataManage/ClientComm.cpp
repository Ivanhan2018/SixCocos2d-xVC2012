#include "stdafx.h"
#include "./ClientComm.h"
#include "DataManage.h"
#include "DataManageDlg.h"

//// �����ں˿ͻ��˵� Lib
// 32λϵ��ϵͳ
#if _DEBUG	
#pragma comment(lib, "../PUBLIC_LIB/x32/CoreClientShell32_d.lib") 
#else
#pragma comment(lib, "../PUBLIC_LIB/x32/CoreClientShell32.lib") 
#endif




CClientComm::CClientComm(void)
{
	
}


CClientComm::~CClientComm(void)
{
	int a=0;
}

// ��Ӧ���ӳɹ�
void CClientComm::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	if(pDataManageDlg)
		pDataManageDlg->SetConnected(true);

	// ����һ����Ϣ
	test04();
	int a=0;
}

// ��Ӧ����ʧ��
void CClientComm::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	printf("����ʧ��");
	int a=0;
}

// ��Ӧ���ͳɹ�
void CClientComm::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	int a=0;
}

// ��Ӧ����ʧ�ܣ�
void CClientComm::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	int a=0;
}

// ��Ӧ�رշ����
void CClientComm::OnClose(CLOSE_TYPE iCloseType)
{
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	if(pDataManageDlg)
		pDataManageDlg->SetConnected(false);
	int a=0;
}

/* --------------------------------------------------------------------------
����˵������Ӧ�հ���Ϣ
���������
	pData		�յ�������
	iDataLen	�յ������ݵĳ���
--------------------------------------------------------------------------*/
void CClientComm::OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	if(pDataManageDlg)
		pDataManageDlg->OnRecv(iMainCode,iSubCode,pData,iDataLen);
	return;
}

// ��ӦͨѶ�������Ϣ
void CClientComm::OnCommError(char* pszError)
{
	int a=0;
}

// ����һ����Ϣ
void CClientComm::test04()
{
	static int iCount = 0;
#if 1
	// ��Ϣ����
	Req_TEST_USER_INFO userInof;
	//StringCchPrintf(userInof.szName, _countof(userInof.szName)-1, _T("��������"));
	wcscpy(userInof.szName,L"��������");
	userInof.iAge = iCount;

	iCount++;

	int iMainCode = MAIN_DMS;
	int iSubCode = REQ_TEST_USER_INFO;	// ��ʾ�û���Ϣ	

	send_data(iMainCode, iSubCode, (BYTE*)(&userInof), sizeof(userInof));
#endif

}

// д����־�ļ�
void CClientComm::test11()
{
#if 0
	wstring strPrompt = _T("�����Ӳ����������");	// ��ʾ
	wstring strWaring = _T("����·����ƾ���һ��");	// ����
	wstring strErrCatch = _T("�Ƽ����ΰ���");		// �������쳣

	for(int i=0; i<10; i++)
	{
		write_log(0, (TCHAR*)strPrompt.c_str(), strPrompt.length());
		write_log(1, (TCHAR*)strWaring.c_str(), strWaring.length());
		write_log(2, (TCHAR*)strErrCatch.c_str(), strErrCatch.length());
	}
#endif

}

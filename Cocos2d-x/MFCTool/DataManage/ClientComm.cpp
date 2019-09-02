#include "stdafx.h"
#include "./ClientComm.h"
#include "DataManage.h"
#include "DataManageDlg.h"

//// 加载内核客户端的 Lib
// 32位系作系统
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

// 响应连接成功
void CClientComm::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	if(pDataManageDlg)
		pDataManageDlg->SetConnected(true);

	// 发送一条信息
	test04();
	int a=0;
}

// 响应连接失败
void CClientComm::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	printf("连接失败");
	int a=0;
}

// 响应发送成功
void CClientComm::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	int a=0;
}

// 响应发送失败，
void CClientComm::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	int a=0;
}

// 响应关闭服务端
void CClientComm::OnClose(CLOSE_TYPE iCloseType)
{
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	if(pDataManageDlg)
		pDataManageDlg->SetConnected(false);
	int a=0;
}

/* --------------------------------------------------------------------------
函数说明：响应收包消息
传入参数：
	pData		收到的数据
	iDataLen	收到的数据的长度
--------------------------------------------------------------------------*/
void CClientComm::OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	if(pDataManageDlg)
		pDataManageDlg->OnRecv(iMainCode,iSubCode,pData,iDataLen);
	return;
}

// 响应通讯错误的消息
void CClientComm::OnCommError(char* pszError)
{
	int a=0;
}

// 发送一条信息
void CClientComm::test04()
{
	static int iCount = 0;
#if 1
	// 消息内容
	Req_TEST_USER_INFO userInof;
	//StringCchPrintf(userInof.szName, _countof(userInof.szName)-1, _T("天命玄鸟"));
	wcscpy(userInof.szName,L"天命玄鸟");
	userInof.iAge = iCount;

	iCount++;

	int iMainCode = MAIN_DMS;
	int iSubCode = REQ_TEST_USER_INFO;	// 显示用户信息	

	send_data(iMainCode, iSubCode, (BYTE*)(&userInof), sizeof(userInof));
#endif

}

// 写入日志文件
void CClientComm::test11()
{
#if 0
	wstring strPrompt = _T("这包子硬得能砸死狗");	// 提示
	wstring strWaring = _T("过马路闯红灯警告一次");	// 警告
	wstring strErrCatch = _T("酒驾坐牢半年");		// 错误与异常

	for(int i=0; i<10; i++)
	{
		write_log(0, (TCHAR*)strPrompt.c_str(), strPrompt.length());
		write_log(1, (TCHAR*)strWaring.c_str(), strWaring.length());
		write_log(2, (TCHAR*)strErrCatch.c_str(), strErrCatch.length());
	}
#endif

}

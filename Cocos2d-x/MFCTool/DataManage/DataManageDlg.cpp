
// DataManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "DataManageDlg.h"
#include "afxdialogex.h"

#include "UserDlg.h"
#include "UserRegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int __stdcall data_receiver(const char * buffer, unsigned int length, bool error)
{

	if(error)
	{
		//MSG
		//发送一个网络断开消息
		PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),NET_MSG_NET_DOWN,0,0);

		return 0;
	}
		
	OutputDebugStringA("将网络消息传送到客户端消息队列处理");

	//将网络消息传送到客户端消息队列处理
	char *myBuffer=NULL;
	if(length>0)
	{
		myBuffer=new char[length+1];
		memset(myBuffer,0,length);
		memcpy(myBuffer,buffer,length);
	}
	PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),NET_MSG_RECEIVE,(long)(char*)myBuffer,length);
	return 0;

	//请到UI\UINetDataProcess.cpp     NetDataProcess()中增加新的接收回调函数
}


//本地或服务端有数据异常时的回调
void __stdcall logic_exception(int code, int agent, int from, int to)
{

	char errMsg[MAX_PATH];

	sprintf(errMsg,"logic exception[request from:%d to:%d  agent:%d]",from, to, agent);

	string strErr=errMsg;
	OutputDebugStringA(strErr.c_str());
	//ServerError(strErr);

	//sprintf(errMsg,"message:%s]", errorcode::error_message(code));

	//strErr=errMsg;
	//ServerError(strErr);


}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDataManageDlg 对话框




CDataManageDlg::CDataManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataManageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(m_szIp, 0, sizeof(m_szIp));
	m_iPort = 0;
	m_pClientComm=NULL;
}

void CDataManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edUser);
	DDX_Control(pDX, IDC_EDIT2, m_edPassword);
	DDX_Control(pDX, ID_BTN_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_STATIC_INFO, m_csInfo);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipDBGIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_edDBGPort);
	DDX_Control(pDX, IDC_EDIT4, m_edPlayerID);
}

BEGIN_MESSAGE_MAP(CDataManageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_MESSAGE(NET_MSG_RECEIVE, OnNetMsgReceive)
	ON_MESSAGE(NET_MSG_NET_DOWN, OnNetMsgNetDown)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDataManageDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(ID_BTN_CONNECT, &CDataManageDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataManageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDataManageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDataManageDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDataManageDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDataManageDlg 消息处理程序

BOOL CDataManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ipDBGIP.SetWindowText(L"127.0.0.1");
	//m_ipDBGIP.SetWindowText(L"192.168.1.109");
	m_edDBGPort.SetWindowText(L"6900");
	m_bConnected = false;
	m_btnConnect.EnableWindow(FALSE);
	m_edUser.SetWindowText(L"Admin");
	m_edPassword.SetWindowText(L"123");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDataManageDlg::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	//if(m_pClientComm)
	//{
	//	if(m_bConnected)
	//		m_pClientComm->stop();
	//	delete m_pClientComm;
	//	m_pClientComm=0;
	//}
	if(m_pClientComm)
	{
		if(m_pClientComm->Connected())
		{
			m_pClientComm->Disconnect();
		}
		delete m_pClientComm;
		m_pClientComm=0;
	}
}

void CDataManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDataManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDataManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CDataManageDlg::OnNetMsgReceive(WPARAM wParam, LPARAM lParam)
{
	// TODO
	CORE_MSG_HEAD *buffer=(CORE_MSG_HEAD*)wParam;
	//_ASSERT(buffer);

	int iDataLen=lParam;
	int iMainCode=buffer->iMainCode;
	int iSubCode=buffer->iSubCode;

	OnRecv(iMainCode,iSubCode,(const BYTE *)buffer,iDataLen);

	if(buffer)
	{ 
		delete[] buffer;
		buffer=NULL;
	}

	return 0;
}

LRESULT CDataManageDlg::OnNetMsgNetDown(WPARAM wParam, LPARAM lParam)
{
	// TODO
	SetConnected(false);

	return 0;
}

// 接收器响应消息，往往是从发射器传来的消息
int CDataManageDlg::OnResponse(int iMainCode, int iSubCode, void* pData, int iDataLen)
{
	return 0;
}

void CDataManageDlg::OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	// 业务处理
	switch (iMainCode)
	{
		// 数据管理服消息
	case MAIN_DMS:
		{
			HandlePacketDMS(iSubCode,pData,iDataLen);
			break;
		}
	default:
		{
			char sz[100]={0};
			sprintf(sz,"OnResponse.MainCode[%d].Unknown!\n",iMainCode);
			OutputDebugStringA(sz);
			break;
		}
	}
	return;
}

void CDataManageDlg::HandlePacketDMS(int iSubCode,const BYTE* pData,int iDataLen)
{	
	switch (iSubCode)
	{
	case RSP_UPDATE_USER_DATA_SUC:
		{
			//Req_ModifyUserData * pModify = (Req_ModifyUserData *)pData;
			EXTRA_PACK_STRUCT(Req_ModifyUserData)
            Req_ModifyUserDataEx * pModify = (Req_ModifyUserDataEx *)pData;
			char sz[100]={0};
			sprintf(sz,"修改用户资料完成\niRet=%d lUserID=%lld lSyslogoid=%lld szNickName=%s\n",pModify->iRet,pModify->lUserID,pModify->lSyslogoid,pModify->szNickName);
			OutputDebugStringA(sz);
			::AfxMessageBox(PUBLIC::s2ws(sz).c_str());
			break;
		}
	//case RSP_TOTAL_REPORT_LIST:
	//	{
	//		Rsp_TotalReport_List * pRsp = (Rsp_TotalReport_List *)((char *)pData+sizeof(CORE_MSG_HEAD));
	//		if(pRsp)
	//		{
	//			char sz[100]={0};
	//			sprintf(sz,"RSP_TOTAL_REPORT_LIST\nnCount=%d nSendIndex=%d bListComplete=%d\n",pRsp->nCount,pRsp->nSendIndex,pRsp->bListComplete);
	//			OutputDebugStringA(sz);
	//			//::AfxMessageBox(PUBLIC::s2ws(sz).c_str());
	//		}
	//		break;
	//	}
	//case RSP_TOTAL_REPORT:
	//	{
	//		Rsp_TotalReport * pRsp = (Rsp_TotalReport *)((char *)pData+sizeof(CORE_MSG_HEAD));
	//		if(pRsp)
	//		{
	//			char sz[600]={0};
	//			int nCount=0;
	//			memcpy(&nCount,pRsp->szDate,sizeof(int));
	//			sprintf(sz,"RSP_TOTAL_REPORT\nnCount=%d iRegistCount=%d lpayMoney=%lf\n",nCount,pRsp->iRegistCount,pRsp->lpayMoney);
	//			OutputDebugStringA(sz);
	//			//::AfxMessageBox(PUBLIC::s2ws(sz).c_str());
	//		}
	//		break;
	//	}
	default:
		{
			char sz[100]={0};
			sprintf(sz,"OnResponse.iSubCode[%d].Unknown!\n",iSubCode);
			OutputDebugStringA(sz);
			break;
		}
	}
	return;
}

void CDataManageDlg::SetConnected(bool bConnected)
{
	if(bConnected)
	{
		m_btnConnect.SetWindowText(L"断开");
		m_bConnected = true;
	}
	else
	{
		m_btnConnect.SetWindowText(L"连接");
		m_bConnected = false;
	}
}

void CDataManageDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUser,strPwd;
	m_edUser.GetWindowText(strUser);
	m_edPassword.GetWindowText(strPwd);
	if (wcscmp(strUser,L"Admin")==0 && wcscmp(strPwd,L"123")==0)
	{
		m_btnConnect.EnableWindow(TRUE);
		m_edPassword.SetWindowText(L"");
		//m_csInfo.SetWindowText(L"用户名或密码正确");
	}
	else
	{
		m_csInfo.SetWindowText(L"用户名或密码错误，请重新输入！");
		m_edUser.SetFocus();
	}
}


void CDataManageDlg::OnBnClickedBtnConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bConnected)
	{
		//if(m_pClientComm)
		//{
		//	m_pClientComm->stop();
		//}

		if(m_pClientComm)
		{
			m_pClientComm->Disconnect();
			SetConnected(false);
		}

		//m_btnConnect.SetWindowText(L"连接");
		//m_bConnected = false;
		return;
	}
	CString strDBGIP,strDBGPort;
	m_ipDBGIP.GetWindowText(strDBGIP);
	m_edDBGPort.GetWindowText(strDBGPort);

	string strIP=PUBLIC::ws2s(wstring(strDBGIP.GetString()));
	string strPort=PUBLIC::ws2s(wstring(strDBGPort.GetString()));
	
	int iRes = 0;
	strcpy(m_szIp,strIP.c_str());
	m_iPort=atoi(strPort.c_str());

	{
		//// 设置通用接收器指针
		//m_pClientComm = new CClientComm;
		if(!m_pClientComm)
		{
			m_pClientComm = new ClientSocket;
		}
		if(!m_pClientComm)
		{
			AfxMessageBox(_T("m_pClientComm 是空值！"));
			return;
		}

		bool connected=m_pClientComm->Connect(m_szIp,m_iPort,data_receiver,logic_exception);
		SetConnected(connected);

		//// 设置通用接收器指针
		//m_pClientComm->set_gerneral_listen((CGerneralListen*)this);

		//// 设置消息块的长度
		//m_pClientComm->set_msg_block_size(2048);
		//m_pClientComm->set_reconnect(false);	// 设置断线不再重连
		//m_pClientComm->set_connect_addr(m_szIp);
		//m_pClientComm->set_connect_port(m_iPort);

		//iRes = m_pClientComm->init();
		//iRes = m_pClientComm->start();
	}

	//m_btnConnect.SetWindowText(L"断开");
	//m_bConnected = true;
}


void CDataManageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_csInfo.SetWindowText(L"");
	CString strPlayerID;
	m_edPlayerID.GetWindowText(strPlayerID);
	if(strPlayerID.IsEmpty())
	{
		m_csInfo.SetWindowText(L"请输入用户ID！");
		m_edPlayerID.SetFocus();
		return;
	}

	CUserDlg dlgPlayerOfficer;
	dlgPlayerOfficer.DoModal();
}


void CDataManageDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_csInfo.SetWindowText(L"");

	CUserRegisterDlg dlgUserRegister;
	dlgUserRegister.DoModal();
}


void CDataManageDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	//if(!pDataManageDlg||!pDataManageDlg->m_pClientComm)
	//	return;

	if(!pDataManageDlg->IsConnected())
	{
		::AfxMessageBox(L"请先连接数据管理服！");
		return;
	}

	//EXTRA_PACK_STRUCT(Req_TotalReport)
	//Req_TotalReportEx req;
	//strcpy(req.szBeginDate,"2013-12-10");
	//strcpy(req.szEndDate,"2013-12-17");
	//req.iMainCode=MAIN_DMS;
	//req.iSubCode=REQ_TOTAL_REPORT_LIST;
	//req.uFlag=0xaaaaaaaaaaaaaaaa;
	//req.SetTotalSize(sizeof(CORE_MSG_HEAD)+sizeof(Req_TotalReport));

	//pDataManageDlg->m_pClientComm->Send((const char*)&req,sizeof(req));
}


void CDataManageDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	//if(!pDataManageDlg||!pDataManageDlg->m_pClientComm)
	//	return;

	if(!pDataManageDlg->IsConnected())
	{
		::AfxMessageBox(L"请先连接数据管理服！");
		return;
	}

	//EXTRA_PACK_STRUCT(Rsp_TotalReport)
	//EXTRA_PACK_STRUCT(Rsp_TotalReport_List)
	//Rsp_TotalReportEx rsp1;
	//vector<Rsp_TotalReport> vec;
	//for(int i=0;i<70;i++)
	//	vec.push_back(Rsp_TotalReport());
	//int NoSendCount=vec.size();
	//memcpy(&rsp1.szDate,&NoSendCount,sizeof(int));
	//int SendCount=0;
	//int nSendIndex=0;
	//while(NoSendCount>0)
	//{
	//	if(NoSendCount>Rsp_TotalReport_List::MAX_SIZE)
	//	{
	//		Rsp_TotalReport_ListEx rsp;
	//		rsp.bListComplete=false;
	//		rsp.nCount=Rsp_TotalReport_List::MAX_SIZE;
	//		rsp.nSendIndex=nSendIndex;
	//		for(int i=SendCount;i<SendCount+Rsp_TotalReport_List::MAX_SIZE;i++)
	//		{
	//			memcpy(&rsp.m_TotalReports[i-SendCount],&vec[i],sizeof(Rsp_TotalReport));
	//			rsp1.iRegistCount+=vec[i].iRegistCount;
	//			rsp1.iLoginCount+=vec[i].iLoginCount;
	//			rsp1.lpayMoney+=vec[i].lpayMoney;
	//			rsp1.lGiveFriendMoney+=vec[i].lGiveFriendMoney;
	//			rsp1.lrevenue+=vec[i].lrevenue;
	//			rsp1.lGiveFriendTaxes+=vec[i].lGiveFriendTaxes;
	//			rsp1.lsysGiveGold+=vec[i].lsysGiveGold;
	//			rsp1.lHighGold+=vec[i].lHighGold;
	//			rsp1.lGoldamount+=vec[i].lGoldamount;
	//			rsp1.lGoldpayments+=vec[i].lGoldpayments;
	//		}
	//		NoSendCount-=Rsp_TotalReport_List::MAX_SIZE;
	//		SendCount+=Rsp_TotalReport_List::MAX_SIZE;

	//		rsp.iMainCode=MAIN_DMS;
	//		rsp.iSubCode=RSP_TOTAL_REPORT_LIST;
	//		rsp.uFlag=0xaaaaaaaaaaaaaaaa;
	//		rsp.SetTotalSize(sizeof(CORE_MSG_HEAD)+sizeof(Rsp_TotalReport_List));
	//		pDataManageDlg->m_pClientComm->Send((const char*)&rsp,sizeof(rsp));

	//		nSendIndex++;

	//	}
	//	else
	//	{
	//		Rsp_TotalReport_ListEx rsp;
	//		rsp.bListComplete=true;
	//		rsp.nCount=NoSendCount;
	//		rsp.nSendIndex=nSendIndex;
	//		for(int i=SendCount;i<vec.size();i++)
	//		{
	//			memcpy(&rsp.m_TotalReports[i-SendCount],&vec[i],sizeof(Rsp_TotalReport));
	//			rsp1.iRegistCount+=vec[i].iRegistCount;
	//			rsp1.iLoginCount+=vec[i].iLoginCount;
	//			rsp1.lpayMoney+=vec[i].lpayMoney;
	//			rsp1.lGiveFriendMoney+=vec[i].lGiveFriendMoney;
	//			rsp1.lrevenue+=vec[i].lrevenue;
	//			rsp1.lGiveFriendTaxes+=vec[i].lGiveFriendTaxes;
	//			rsp1.lsysGiveGold+=vec[i].lsysGiveGold;
	//			rsp1.lHighGold+=vec[i].lHighGold;
	//			rsp1.lGoldamount+=vec[i].lGoldamount;
	//			rsp1.lGoldpayments+=vec[i].lGoldpayments;
	//		}
	//		NoSendCount=0;
	//		SendCount+=NoSendCount;

	//		rsp.iMainCode=MAIN_DMS;
	//		rsp.iSubCode=RSP_TOTAL_REPORT_LIST;
	//		rsp.uFlag=0xaaaaaaaaaaaaaaaa;
	//		rsp.SetTotalSize(sizeof(CORE_MSG_HEAD)+sizeof(Rsp_TotalReport_List));
	//		pDataManageDlg->m_pClientComm->Send((const char*)&rsp,sizeof(rsp));

	//		nSendIndex++;
	//	}
	//}
	//rsp1.iMainCode=MAIN_DMS;
	//rsp1.iSubCode=RSP_TOTAL_REPORT;
	//rsp1.uFlag=0xaaaaaaaaaaaaaaaa;
	//rsp1.SetTotalSize(sizeof(CORE_MSG_HEAD)+sizeof(Rsp_TotalReport));
	//pDataManageDlg->m_pClientComm->Send((const char*)&rsp1,sizeof(rsp1));
}

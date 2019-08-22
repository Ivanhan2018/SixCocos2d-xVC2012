// GBCCovertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GBCCovert.h"
#include "GBCCovertDlg.h"

#include "ChrAsc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGBCCovertDlg 对话框




CGBCCovertDlg::CGBCCovertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGBCCovertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGBCCovertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edHZ);
	DDX_Control(pDX, IDC_EDIT2, m_edGBK10);
	DDX_Control(pDX, IDC_EDIT3, m_edGBK16);
	DDX_Control(pDX, IDC_EDIT4, m_edGBKHZ);
	DDX_Control(pDX, IDC_EDIT5, m_edUni10);
	DDX_Control(pDX, IDC_EDIT6, m_edUni16);
	DDX_Control(pDX, IDC_EDIT7, m_edUniHZ);
}

BEGIN_MESSAGE_MAP(CGBCCovertDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CGBCCovertDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGBCCovertDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CGBCCovertDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CGBCCovertDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGBCCovertDlg 消息处理程序

BOOL CGBCCovertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	m_edHZ.SetLimitText(2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGBCCovertDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGBCCovertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CGBCCovertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGBCCovertDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Str;
	m_edHZ.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("请输入要转换的汉字！");
		m_edHZ.SetFocus();
		return;
	}

	char  sz[200]={0};
	short int w=AscFromChr(Str.GetString());
	//sprintf(sz,"%d,%u,%hu,%hx",w,w,w,w);
	//AfxMessageBox(sz);
	sprintf(sz,"%hu",w);
	m_edGBK10.SetWindowTextA(sz);
	sprintf(sz,"%hx",w);
	m_edGBK16.SetWindowTextA(sz);
	m_edGBKHZ.SetWindowTextA(Str);
}


void CGBCCovertDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Str;
	m_edGBK10.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("请输入GBK内码！");
		m_edGBK10.SetFocus();
		return;
	}

	char  sz[200]={0};
	short int w=atoi(Str.GetString());
	sprintf(sz,"%hu",w);
	m_edGBK10.SetWindowTextA(sz);
	sprintf(sz,"%hx",w);
	m_edGBK16.SetWindowTextA(sz);

	const char *str=ChrFromAnsi(w);
	m_edGBKHZ.SetWindowTextA(str);
}

void CGBCCovertDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Str;
	m_edHZ.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("请输入要转换的汉字！");
		m_edHZ.SetFocus();
		return;
	}
	wstring wstr=StringToWstring(Str.GetString());

	char  sz[200]={0};
	short int w=wstr[0];
	sprintf(sz,"%hu",w);
	m_edUni10.SetWindowTextA(sz);
	sprintf(sz,"%hx",w);
	m_edUni16.SetWindowTextA(sz);
	m_edUniHZ.SetWindowTextA(Str);
}

void CGBCCovertDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Str;
	m_edUni10.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("请输入Unicode码！");
		m_edUni10.SetFocus();
		return;
	}

	char  sz[200]={0};
	short int w=atoi(Str.GetString());
	sprintf(sz,"%hu",w);
	m_edUni10.SetWindowTextA(sz);
	sprintf(sz,"%hx",w);
	m_edUni16.SetWindowTextA(sz);

	wstring wstr;
	wstr.push_back(w);
	string str=WstringToString(wstr);
	m_edUniHZ.SetWindowTextA(str.c_str());
}
// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "WHEncrypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_i = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_EDIT1, m_i);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTEST, OnBtest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("1"));
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 使用 Unicode 字符集或者使用多字节字符集均可正常编译运行
void CTestDlg::OnBtest() 
{
	UpdateData(true);
	if(m_i==0)
	{
		// 读取配置表中的密文
		TCHAR psz2[MAX_ENCRYPT_LEN]={0};
		LPCTSTR psz1=_T("000C003D002900184823481718BE1890678467B14AE14AD43D6C3D422CD62CE3000C003E002900074823481718BE18886784152A4AE123B33D6C62FC2CD63A9F");
		//LPCTSTR psz1=_T("20651BBE8125D50065B565B276D1C66B1ABA1BB68157D50065C465C876A3C6101ACC1BCA8120D57765B465C176D7C6651AC81BBD8125D50765C965C976D1C617");
		//DWORD dwReadCount=_tcslen(psz1);
		//LPCTSTR psz1=_T("073f29116b59d6e4ebd20736291b6b47d67febe8");

		// 解密得到明文
		CWHEncrypt WHEncrypt;
		bool ret=WHEncrypt.XorCrevasse(psz1,psz2,MAX_ENCRYPT_LEN);
		int a=0;
		AfxMessageBox(psz2);//114.55.52.46
	}
	else
	{
		typedef int(_cdecl *Connect)(int i);
		HINSTANCE hinstDLL=NULL; 
		hinstDLL=LoadLibrary(_T("dll.dll"));
		if (hinstDLL)
		{
			Connect Proc;
			Proc = (Connect)GetProcAddress (hinstDLL,"Test");
			int iValue = Proc(m_i);
			FreeLibrary(hinstDLL);

			_TCHAR sz[20]={0};
			wsprintf(sz,_T("%d"),iValue);
			AfxMessageBox(sz);
		}
		else
		{
			AfxMessageBox(_T("没找到dll"));
		}
	}
}

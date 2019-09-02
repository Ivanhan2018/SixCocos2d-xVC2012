// calculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "calculator.h"
#include "calculatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


double sum1,sum2,sum3;
double point=0;
double tmpdata;
CString signal="@";
CString signal2="@";
CString signal3="@";
CString signal4="@";//用于CE键
int datesize;//数位计

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempDlg dialog

CTempDlg::CTempDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTempDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTempDlg)
	m_edit = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTempDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTempDlg, CDialog)
	//{{AFX_MSG_MAP(CTempDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_0, On0)
	ON_BN_CLICKED(IDC_SIGN, OnSign)
	ON_BN_CLICKED(IDC_POINT, OnPoint)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EQUAL, OnEqual)
	ON_BN_CLICKED(IDC_1, On1)
	ON_BN_CLICKED(IDC_2, On2)
	ON_BN_CLICKED(IDC_3, On3)
	ON_BN_CLICKED(IDC_REDUCE, OnReduce)
	ON_BN_CLICKED(IDC_DAOSHU, OnDaoshu)
	ON_BN_CLICKED(IDC_4, On4)
	ON_BN_CLICKED(IDC_5, On5)
	ON_BN_CLICKED(IDC_6, On6)
	ON_BN_CLICKED(IDC_CHEN, OnChen)
	ON_BN_CLICKED(IDC_PERCENT, OnPercent)
	ON_BN_CLICKED(IDC_7, On7)
	ON_BN_CLICKED(IDC_8, On8)
	ON_BN_CLICKED(IDC_9, On9)
	ON_BN_CLICKED(IDC_DIVIDE, OnDivide)
	ON_BN_CLICKED(IDC_SQRT, OnSqrt)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_CE, OnCe)
	ON_BN_CLICKED(IDC_C, OnC)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempDlg message handlers

BOOL CTempDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_1.AutoLoad(IDC_1,this);
	m_2.AutoLoad(IDC_2,this);
	m_3.AutoLoad(IDC_3,this);
	m_4.AutoLoad(IDC_4,this);
	m_5.AutoLoad(IDC_5,this);
	m_6.AutoLoad(IDC_6,this);
	m_7.AutoLoad(IDC_7,this);
	m_8.AutoLoad(IDC_8,this);
	m_9.AutoLoad(IDC_9,this);
	m_0.AutoLoad(IDC_0,this);
	m_back.AutoLoad(IDC_BACK,this);
	m_ce.AutoLoad(IDC_CE,this);
	m_c.AutoLoad(IDC_C,this);
	m_divide.AutoLoad(IDC_DIVIDE,this);
	m_sqrt.AutoLoad(IDC_SQRT,this);
	m_chen.AutoLoad(IDC_CHEN,this);
	m_percent.AutoLoad(IDC_PERCENT,this);
	m_reduce.AutoLoad(IDC_REDUCE,this);
	m_daoshu.AutoLoad(IDC_DAOSHU,this);
	m_sign.AutoLoad(IDC_SIGN,this);
	m_add.AutoLoad(IDC_ADD,this);
	m_equal.AutoLoad(IDC_EQUAL,this);
	m_point.AutoLoad(IDC_POINT,this);  
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTempDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTempDlg::OnPaint() 
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
HCURSOR CTempDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTempDlg::On0() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(0);
}

void CTempDlg::OnSign() 
{
	// TODO: Add your control notification handler code here
	m_edit=0-m_edit;
	UpdateData(0);

}

void CTempDlg::OnPoint() 
{
	// TODO: Add your control notification handler code here
	if(!point)     //判断point是否已按下过
		point=0.1;
	
}

void CTempDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here

	DateSolve();
	signal="+";
	point=0;
	m_edit=0;
	datesize=0;
}

void CTempDlg::OnEqual() 
{
	// TODO: Add your control notification handler code here
	if(signal=="+"){
		m_edit=sum1+m_edit;
		sum1=0;
	}

	if(signal=="-"){
		m_edit=sum1-m_edit;
		sum1=0;
	}

	if(signal=="*"){
		sum2=sum2*m_edit;
		if(signal2=="+"){
			m_edit=sum1+sum2;
			UpdateData(0);
		}
		else if(signal2=="-"){
			m_edit=sum1-sum2;
			UpdateData(0);
		}
		else{
			m_edit=sum2;
			UpdateData(0);
		}
	}

	
	if(signal=="/"){
		if(m_edit==0){
			AfxMessageBox("除数不能为零!");
		}
		else{
			sum3=sum3/m_edit;
			if(signal3=="+"){
				m_edit=sum1=sum1+sum3;
				UpdateData(0);
			}
			else if(signal3=="-"){
					m_edit=sum1=sum1-sum3;
					UpdateData(0);
				}
			else{
				m_edit=sum3;
				UpdateData(0);
			}
		}
	}
	Cleardate();
}

void CTempDlg::On1() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(1);
}

void CTempDlg::On2() 
{
	// TODO: Add your control notification handler code here

	KeyDeal(2);
}

void CTempDlg::On3() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(3);
}

void CTempDlg::OnReduce() 
{
	// TODO: Add your control notification handler code here

	DateSolve();
	signal="-";
	point=0;
	m_edit=0;
	datesize=0;
}

void CTempDlg::OnDaoshu() 
{
	// TODO: Add your control notification handler code here
	if(m_edit){
	   m_edit=1/m_edit;
	   UpdateData(0);
	   }
}

void CTempDlg::On4() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(4);
}

void CTempDlg::On5() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(5);
}

void CTempDlg::On6() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(6);
}

void CTempDlg::OnChen() 
{
	// TODO: Add your control notification handler code here
	
	point=0;
	signal4=signal;
	if(signal=="@"||signal=="=")
		sum2=m_edit;
	if(signal=="+"||signal=="-"){
		sum2=m_edit;
		signal2=signal;
	}
	if(signal=="*"){
		sum2=sum2*m_edit;
		m_edit=sum2;
	}
	if(signal=="/"){
		if(m_edit==0){
			AfxMessageBox("除数不能为零!");
			return;
		}
		sum2=sum3/m_edit;
		m_edit=sum2;
	}
	signal="*";
	UpdateData(0);
	m_edit=0;
	datesize=0;
}

void CTempDlg::OnPercent() 
{
	// TODO: Add your control notification handler code here
	m_edit=m_edit/100;
	UpdateData(0);
}

void CTempDlg::On7() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(7);

}

void CTempDlg::On8() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(8);

}

void CTempDlg::On9() 
{
	// TODO: Add your control notification handler code here
	KeyDeal(9);

}

void CTempDlg::OnDivide() 
{
	// TODO: Add your control notification handler code here
	point=0;
	signal4=signal;//
	tmpdata=m_edit;//数据备份,为OnCe()作准备
	if(signal=="@"||signal=="=")
		sum3=m_edit;
	if(signal=="+"||signal=="-"){
		sum3=m_edit;
		signal3=signal;
	}
	if(signal=="/"){
		if(m_edit==0){
			AfxMessageBox("除数不能为零!");
			return;
		}
		sum3=sum3/m_edit;
		m_edit=sum3;
	}
	if(signal=="*"){
		sum3=sum2*m_edit;
		m_edit=sum3;
	}
	signal="/";
	UpdateData(0);
	m_edit=0;
	datesize=0;

}

void CTempDlg::OnSqrt() 
{
	// TODO: Add your control notification handler code here
	m_edit=m_edit*m_edit;
	UpdateData(0);
}

void CTempDlg::OnBack() 
{
	// TODO: Add your control notification handler code here
	int i=(int)m_edit;
	if(point==0)
		m_edit=(double)(int)(m_edit/10);
	else{
		point=point*10;
		m_edit=(double)((int)(m_edit*(0.1/point)))*(point*10);
		if(i==m_edit)
			point=0;
	}
	if(datesize)//判断数位是否已完全清除
		datesize--;
	UpdateData(0);

}

void CTempDlg::OnCe() 
{
	// TODO: Add your control notification handler code here
	signal="@";
	if(signal4=="+"||signal4=="-")
		m_edit=sum1;
	else if(signal4=="*")
		m_edit=sum2;
	else if(signal4=="/")
		m_edit=sum3;
	point=0;
	datesize=0;
	UpdateData(0);
}

void CTempDlg::OnC() 
{
	// TODO: Add your control notification handler code here
	m_edit=0;
	sum1=0;
	sum2=0;
	sum3=0;
	tmpdata=0;
	datesize=0;
	point=0;
	signal="@";
	signal2="@";
	signal3="@";
	signal4="@";
	UpdateData(0);
}

void CTempDlg::Cleardate()  //数据清零
{
	signal="=";
	point=0;
	sum1=0;
	sum2=0;
	sum3=0;
	tmpdata=0;
	datesize=0;
	signal2="@";
	signal3="@";
	signal4="@";
	UpdateData(0);

}

void CTempDlg::DateSolve()   //处理加减法
{
	signal4=signal;    //}
	tmpdata=m_edit;   // }备份,为OnCe()作准备
	if(signal=="+")
		sum1=sum1+m_edit;
	else if(signal=="-")
		sum1=sum1-m_edit;
	else if(signal=="*")
		sum1=sum2=sum2*m_edit;
	else if(signal=="/")
		sum1=sum3=sum3/m_edit;
	else 
		sum1=m_edit;
	m_edit=sum1;
	UpdateData(0);
}


void CTempDlg::KeyDeal(int a)  //处理数字按钮
{

	if(datesize<9){
		datesize++;
		if(signal=="="){
			m_edit=a;
			signal="@";
			UpdateData(0);
			return;
		}
		if(point){
			m_edit=m_edit+point*a;
			point=point/10;
		}
		else
			m_edit=m_edit*10+a;
		UpdateData(0);
	}

}

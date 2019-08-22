// GBCCovertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GBCCovert.h"
#include "GBCCovertDlg.h"

#include "ChrAsc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGBCCovertDlg �Ի���




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


// CGBCCovertDlg ��Ϣ�������

BOOL CGBCCovertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_edHZ.SetLimitText(2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGBCCovertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CGBCCovertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGBCCovertDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Str;
	m_edHZ.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("������Ҫת���ĺ��֣�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Str;
	m_edGBK10.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("������GBK���룡");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Str;
	m_edHZ.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("������Ҫת���ĺ��֣�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Str;
	m_edUni10.GetWindowText(Str);
	if(Str.IsEmpty())
	{
		AfxMessageBox("������Unicode�룡");
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
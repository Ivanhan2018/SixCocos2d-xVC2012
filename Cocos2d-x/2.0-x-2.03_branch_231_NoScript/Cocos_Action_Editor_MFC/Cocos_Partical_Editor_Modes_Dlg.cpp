#include "stdafx.h"
//#include "Cocos_Partical_Editor_MFC.h"
#include "Cocos_Partical_Editor_MFCDlg.h"
#include "afxdialogex.h"

CPartical_Detial_Dlg_ModeA::CPartical_Detial_Dlg_ModeA(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCocos_Partical_Editor_MFCDlg::IDD, pParent)

	, speed(0)
	, speedVar(0)
	, tangentialAccel(0)
	, tangentialAccelVar(0)
	, radialAccel(0)
	, radialAccelVar(0)
	, m_gx(0)
	, m_gy(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPartical_Detial_Dlg_ModeA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_speed);
	DDX_Control(pDX, IDC_EDIT3, m_speedVar);
	DDX_Control(pDX, IDC_EDIT11, m_tangentialAccel);
	DDX_Control(pDX, IDC_EDIT12, m_tangentialAccelVar);
	DDX_Control(pDX, IDC_EDIT13, m_radialAccel);
	DDX_Control(pDX, IDC_EDIT4, m_radialAccelVar);
	DDX_Text(pDX, IDC_EDIT1, speed);
	DDX_Text(pDX, IDC_EDIT3, speedVar);
	DDX_Text(pDX, IDC_EDIT11, tangentialAccel);
	DDX_Text(pDX, IDC_EDIT12, tangentialAccelVar);
	DDX_Text(pDX, IDC_EDIT13, radialAccel);
	DDX_Text(pDX, IDC_EDIT4, radialAccelVar);
	DDX_Control(pDX, IDC_EDIT14, m_Gravity_x);
	DDX_Control(pDX, IDC_EDIT2, m_Gravity_y);
	DDX_Text(pDX, IDC_EDIT14, m_gx);
	DDX_Text(pDX, IDC_EDIT2, m_gy);
}

BEGIN_MESSAGE_MAP(CPartical_Detial_Dlg_ModeA, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()



BOOL CPartical_Detial_Dlg_ModeA::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		



	return TRUE;  
}

void CPartical_Detial_Dlg_ModeA::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CPartical_Detial_Dlg_ModeA::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPartical_Detial_Dlg_ModeA::OnDestroy()
{

}

void CPartical_Detial_Dlg_ModeA::Load(cocos2d::CCParticleSystem* particals)
{
	speed = particals->getSpeed();
	speedVar = particals->getSpeedVar();
	tangentialAccel = particals->getTangentialAccel();
	tangentialAccelVar = particals->getTangentialAccelVar();
	radialAccel= particals->getRadialAccel();
	radialAccelVar= particals->getRadialAccelVar();
	cocos2d::CCPoint pt = particals->getGravity();
	m_gx = pt.x;
	m_gy = pt.y;
	UpdateData(FALSE);
}

void CPartical_Detial_Dlg_ModeA::Update(cocos2d::CCParticleSystem* particals)
{
	UpdateData(TRUE);
	particals->setSpeed(speed);
	particals->setSpeedVar(speedVar);
	particals->setTangentialAccel(tangentialAccel);
	particals->setTangentialAccelVar(tangentialAccelVar);
	particals->setRadialAccel(radialAccel);
	particals->setRadialAccelVar(radialAccelVar);
	cocos2d::CCPoint pt(m_gx,m_gy);
	particals->setGravity(pt);
}

CPartical_Detial_Dlg_ModeB::CPartical_Detial_Dlg_ModeB(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCocos_Partical_Editor_MFCDlg::IDD, pParent)
	, startRadius(0)
	, startRadiusVar(0)
	, endRadius(0)
	, endRadiusVar(0)
	, rotatePerSecond(0)
	, rotatePerSecondVar(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPartical_Detial_Dlg_ModeB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_startRadius);
	DDX_Control(pDX, IDC_EDIT2, m_startRdiusVar);
	DDX_Control(pDX, IDC_EDIT3, m_endRadius);
	DDX_Control(pDX, IDC_EDIT4, m_endRadiusVar);
	DDX_Control(pDX, IDC_EDIT11, m_rotatePerSecond);
	DDX_Control(pDX, IDC_EDIT12, m_rotatePerSecondVar);
	DDX_Text(pDX, IDC_EDIT1, startRadius);
	DDX_Text(pDX, IDC_EDIT2, startRadiusVar);
	DDX_Text(pDX, IDC_EDIT3, endRadius);
	DDX_Text(pDX, IDC_EDIT4, endRadiusVar);
	DDX_Text(pDX, IDC_EDIT11, rotatePerSecond);
	DDX_Text(pDX, IDC_EDIT12, rotatePerSecondVar);
}

BEGIN_MESSAGE_MAP(CPartical_Detial_Dlg_ModeB, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()



BOOL CPartical_Detial_Dlg_ModeB::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		



	return TRUE;  
}

void CPartical_Detial_Dlg_ModeB::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CPartical_Detial_Dlg_ModeB::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPartical_Detial_Dlg_ModeB::OnDestroy()
{

}

void CPartical_Detial_Dlg_ModeB::Load(cocos2d::CCParticleSystem* particals)
{
	startRadius = particals->getStartRadius();
	startRadiusVar = particals->getStartRadiusVar();
	endRadius = particals->getEndRadius();
	endRadiusVar = particals->getEndRadiusVar();
	rotatePerSecond = particals->getRotatePerSecond();
	rotatePerSecondVar = particals->getRotatePerSecondVar();
	UpdateData(FALSE);
}

void CPartical_Detial_Dlg_ModeB::Update(cocos2d::CCParticleSystem* particals)
{
	UpdateData(TRUE);
	particals->setStartRadius(startRadius);
	particals->setStartRadiusVar(startRadiusVar);
	particals->setEndRadius(endRadius);
	particals->setEndRadiusVar(endRadiusVar);
	particals->setRotatePerSecond(rotatePerSecond);
	particals->setRotatePerSecondVar(rotatePerSecondVar);
}
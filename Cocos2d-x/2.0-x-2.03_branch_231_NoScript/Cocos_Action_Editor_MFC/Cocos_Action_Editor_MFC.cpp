
// Cocos_Action_Editor_MFC.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Cocos_Action_Editor_MFC.h"
#include "MainFrm.h"

#include "Cocos_Action_Editor_MFCDoc.h"
#include "Cocos_Action_Editor_MFCView.h"

#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

USING_NS_CC;

// CCocos_Action_Editor_MFCApp

BEGIN_MESSAGE_MAP(CCocos_Action_Editor_MFCApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCocos_Action_Editor_MFCApp::OnAppAbout)
	//// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_OPEN_IMAGE, &CCocos_Action_Editor_MFCApp::OnOpenImage)
	ON_COMMAND(ID_OPEN, &CCocos_Action_Editor_MFCApp::OnOpen)
	ON_COMMAND(ID_SAVE, &CCocos_Action_Editor_MFCApp::OnSave)
	ON_COMMAND(ID_PARTICAL_CONTROL, &CCocos_Action_Editor_MFCApp::OnParticalControl)
END_MESSAGE_MAP()


// CCocos_Action_Editor_MFCApp ����

CCocos_Action_Editor_MFCApp::CCocos_Action_Editor_MFCApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Cocos_Action_Editor_MFC.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CCocos_Action_Editor_MFCApp ����

CCocos_Action_Editor_MFCApp theApp;


// CCocos_Action_Editor_MFCApp ��ʼ��

BOOL CCocos_Action_Editor_MFCApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	AfxOleInit();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCocos_Action_Editor_MFCDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CCocos_Action_Editor_MFCView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����

	m_pMainWnd->SetWindowText(L"�����༭�� v1.0");

	//_CrtSetBreakAlloc(29225);

	partDlg = new CCocos_Partical_Editor_MFCDlg();
	partEditor = new CCos_Partical_Editor;

	partDlg->Create(IDD_COCOS_PARTICAL_EDITOR_MFC_DIALOG);
	partDlg->MoveWindow(0,0,700,530);
	partDlg->CenterWindow();

	partEditor->Create(IDD_DLGCONFIG,partDlg);
	partEditor->MoveWindow(0,0,700,530);

	partDlg->ShowWindow(SW_HIDE);
	partEditor->ShowWindow(SW_SHOW);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CCocos_Action_Editor_MFCView * pView = (CCocos_Action_Editor_MFCView*)(((CFrameWnd *)m_pMainWnd)->GetActiveView());
	RECT rc;
	pView->GetWindowRect(&rc);

	AppDelegate app;
	eglView = CCEGLView::sharedOpenGLView();
	eglView->attachWindow(pView->GetSafeHwnd());
	eglView->setFrameSize(rc.right-rc.left,rc.bottom-rc.top);
	pView->IsInited = true;
	CCApplication::sharedApplication()->run();

	return TRUE;
}

int CCocos_Action_Editor_MFCApp::ExitInstance()
{
	if(eglView)
	{
		delete eglView;
	}

	if(partEditor)
	{
		partEditor->OnDestroy();
		delete partEditor;
		partEditor = 0;
	}
	if(partDlg)
	{
		delete partDlg;
		partDlg = 0;
	}
	CCDirector::sharedDirector()->end();
	return CWinApp::ExitInstance();
}


// CCocos_Action_Editor_MFCApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CCocos_Action_Editor_MFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCocos_Action_Editor_MFCApp �Զ������/���淽��

void CCocos_Action_Editor_MFCApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	//bNameValid = strName.LoadString(IDS_EDIT_MENU);
	//ASSERT(bNameValid);
	//GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CCocos_Action_Editor_MFCApp::LoadCustomState()
{
}

void CCocos_Action_Editor_MFCApp::SaveCustomState()
{
}

// CCocos_Action_Editor_MFCApp ��Ϣ�������

void CCocos_Action_Editor_MFCApp::OnOpenImage()
{
	// TODO: �ڴ���������������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	::PostMessage(pMainFrame->GetSafeHwnd(),WM_COMMAND,ID_OPEN_IMAGE,0);
}

void CCocos_Action_Editor_MFCApp::OnOpen()
{
	// TODO: �ڴ���������������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	::PostMessage(pMainFrame->GetSafeHwnd(),WM_COMMAND,ID_OPEN,0);
}


void CCocos_Action_Editor_MFCApp::OnSave()
{
	// TODO: �ڴ���������������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	::PostMessage(pMainFrame->GetSafeHwnd(),WM_COMMAND,ID_SAVE,0);
}


void CCocos_Action_Editor_MFCApp::OnParticalControl()
{
	// TODO: �ڴ���������������
	partDlg->ShowWindow(SW_SHOW);
	partDlg->CenterWindow();
	partEditor->RefreshRunTargetCMB();
}

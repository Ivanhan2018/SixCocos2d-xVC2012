
// Cocos_Action_Editor_MFC.cpp : 定义应用程序的类行为。
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
	//// 基于文件的标准文档命令
	ON_COMMAND(ID_OPEN_IMAGE, &CCocos_Action_Editor_MFCApp::OnOpenImage)
	ON_COMMAND(ID_OPEN, &CCocos_Action_Editor_MFCApp::OnOpen)
	ON_COMMAND(ID_SAVE, &CCocos_Action_Editor_MFCApp::OnSave)
	ON_COMMAND(ID_PARTICAL_CONTROL, &CCocos_Action_Editor_MFCApp::OnParticalControl)
END_MESSAGE_MAP()


// CCocos_Action_Editor_MFCApp 构造

CCocos_Action_Editor_MFCApp::CCocos_Action_Editor_MFCApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Cocos_Action_Editor_MFC.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CCocos_Action_Editor_MFCApp 对象

CCocos_Action_Editor_MFCApp theApp;


// CCocos_Action_Editor_MFCApp 初始化

BOOL CCocos_Action_Editor_MFCApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	AfxOleInit();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCocos_Action_Editor_MFCDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CCocos_Action_Editor_MFCView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生

	m_pMainWnd->SetWindowText(L"动作编辑器 v1.0");

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


// CCocos_Action_Editor_MFCApp 消息处理程序


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

// 用于运行对话框的应用程序命令
void CCocos_Action_Editor_MFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCocos_Action_Editor_MFCApp 自定义加载/保存方法

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

// CCocos_Action_Editor_MFCApp 消息处理程序

void CCocos_Action_Editor_MFCApp::OnOpenImage()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	::PostMessage(pMainFrame->GetSafeHwnd(),WM_COMMAND,ID_OPEN_IMAGE,0);
}

void CCocos_Action_Editor_MFCApp::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	::PostMessage(pMainFrame->GetSafeHwnd(),WM_COMMAND,ID_OPEN,0);
}


void CCocos_Action_Editor_MFCApp::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	::PostMessage(pMainFrame->GetSafeHwnd(),WM_COMMAND,ID_SAVE,0);
}


void CCocos_Action_Editor_MFCApp::OnParticalControl()
{
	// TODO: 在此添加命令处理程序代码
	partDlg->ShowWindow(SW_SHOW);
	partDlg->CenterWindow();
	partEditor->RefreshRunTargetCMB();
}

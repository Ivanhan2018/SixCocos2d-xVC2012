#include "stdafx.h"
#include "Cocos_Partical_Editor_MFC.h"
#include "AppDelegate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCocos_Partical_Editor_MFCApp

BEGIN_MESSAGE_MAP(CCocos_Partical_Editor_MFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

USING_NS_CC;

CCocos_Partical_Editor_MFCApp::CCocos_Partical_Editor_MFCApp()
	:dlg(NULL),editor(NULL)
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


CCocos_Partical_Editor_MFCApp theApp;

BOOL CCocos_Partical_Editor_MFCApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	HRESULT hr= OleInitialize(NULL);
	if(hr== S_FALSE) 
	{ 
		OleUninitialize(); 
	} 
	AfxEnableControlContainer(); 
	COleObjectFactory::RegisterAll();


	AfxEnableControlContainer();

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	dlg = new CCocos_Partical_Editor_MFCDlg;
	editor = new CCos_Partical_Editor;

	m_pMainWnd = dlg;
	dlg->Create(IDD_COCOS_PARTICAL_EDITOR_MFC_DIALOG);
	dlg->MoveWindow(0,0,1024,665);
	dlg->CenterWindow();

	editor->Create(IDD_DLGCONFIG,dlg);
	editor->MoveWindow(324,0,700,665);

	dlg->ShowWindow(SW_SHOW);
	editor->ShowWindow(SW_SHOW);

	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->attachWindow(dlg->m_hWnd);
	eglView->setFrameSize(324, 637);

	CCApplication::sharedApplication()->run();
	m_pMainWnd = NULL;


	CMFCVisualManager::DestroyInstance();

	return FALSE;
}

int CCocos_Partical_Editor_MFCApp::ExitInstance()
{
	if(eglView)
	{
		delete eglView;
	}

	if(editor)
	{
		editor->OnDestroy();
		delete editor;
		editor = NULL;
	}
	if(dlg)
	{
		delete dlg;
		dlg = NULL;
	}
	CCDirector::sharedDirector()->end();
	return CWinApp::ExitInstance();
}

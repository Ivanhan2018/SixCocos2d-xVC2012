
// Cocos_Action_Editor_MFC.h : Cocos_Action_Editor_MFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "CCEGLView.h"
#include "Cocos_Partical_Editor_MFCDlg.h"

// CCocos_Action_Editor_MFCApp:
// 有关此类的实现，请参阅 Cocos_Action_Editor_MFC.cpp
//

class CCocos_Action_Editor_MFCApp : public CWinAppEx
{
public:
	CCocos_Action_Editor_MFCApp();
	~CCocos_Action_Editor_MFCApp()
	{
		AfxOleTerm(FALSE);
		this->CleanState();
		CMFCVisualManager::DestroyInstance( TRUE );
	}

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnOpenImage();
	afx_msg void OnOpen();
	afx_msg void OnSave();
private:
	CCocos_Partical_Editor_MFCDlg* partDlg;
	CCos_Partical_Editor* partEditor;
	cocos2d::CCEGLView* eglView;
public:
	afx_msg void OnParticalControl();
};

extern CCocos_Action_Editor_MFCApp theApp;

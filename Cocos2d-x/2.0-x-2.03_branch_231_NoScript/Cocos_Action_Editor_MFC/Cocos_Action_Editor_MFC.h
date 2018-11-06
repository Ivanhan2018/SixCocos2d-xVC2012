
// Cocos_Action_Editor_MFC.h : Cocos_Action_Editor_MFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "CCEGLView.h"
#include "Cocos_Partical_Editor_MFCDlg.h"

// CCocos_Action_Editor_MFCApp:
// �йش����ʵ�֣������ Cocos_Action_Editor_MFC.cpp
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

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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


#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		

#include "Cocos_Partical_Editor_MFCDlg.h"
#include "CCEGLView.h"

class CCocos_Partical_Editor_MFCApp : public CWinApp
{
public:
	CCocos_Partical_Editor_MFCApp();


public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

private:
	CCocos_Partical_Editor_MFCDlg* dlg;
	CCos_Partical_Editor* editor;
	cocos2d::CCEGLView* eglView;
	DECLARE_MESSAGE_MAP()
};

extern CCocos_Partical_Editor_MFCApp theApp;
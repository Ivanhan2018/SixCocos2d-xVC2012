// GBCCovert.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGBCCovertApp:
// �йش����ʵ�֣������ GBCCovert.cpp
//

class CGBCCovertApp : public CWinApp
{
public:
	CGBCCovertApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGBCCovertApp theApp;
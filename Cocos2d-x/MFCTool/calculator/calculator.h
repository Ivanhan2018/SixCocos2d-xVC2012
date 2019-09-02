// calculator.h : main header file for the CALCULATOR application
//

#if !defined(AFX_CALCULATOR_H__31D0F212_54D5_4000_86D3_0F4B0BB0BCA0__INCLUDED_)
#define AFX_CALCULATOR_H__31D0F212_54D5_4000_86D3_0F4B0BB0BCA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTempApp:
// See calculator.cpp for the implementation of this class
//

class CTempApp : public CWinApp
{
public:
	CTempApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTempApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATOR_H__31D0F212_54D5_4000_86D3_0F4B0BB0BCA0__INCLUDED_)

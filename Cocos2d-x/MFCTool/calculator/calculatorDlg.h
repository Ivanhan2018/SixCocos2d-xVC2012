// calculatorDlg.h : header file
//

#if !defined(AFX_CALCULATORDLG_H__E9D25D32_6919_4C99_A48D_E3F63572F882__INCLUDED_)
#define AFX_CALCULATORDLG_H__E9D25D32_6919_4C99_A48D_E3F63572F882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




/////////////////////////////////////////////////////////////////////////////
// CTempDlg dialog

class CTempDlg : public CDialog
{
// Construction
public:
	void KeyDeal(int);
	void DateSolve();
	void Cleardate();
	CTempDlg(CWnd* pParent = NULL);  // standard constructor
	CBitmapButton m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9,m_0;
	CBitmapButton m_add,m_reduce,m_chen,m_divide;
	CBitmapButton m_sqrt,m_point,m_daoshu,m_percent,m_equal,m_back,m_ce,m_c,m_sign;	




// Dialog Data
	//{{AFX_DATA(CTempDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
	double	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTempDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void On0();
	afx_msg void OnSign();
	afx_msg void OnPoint();
	afx_msg void OnAdd();
	afx_msg void OnEqual();
	afx_msg void On1();
	afx_msg void On2();
	afx_msg void On3();
	afx_msg void OnReduce();
	afx_msg void OnDaoshu();
	afx_msg void On4();
	afx_msg void On5();
	afx_msg void On6();
	afx_msg void OnChen();
	afx_msg void OnPercent();
	afx_msg void On7();
	afx_msg void On8();
	afx_msg void On9();
	afx_msg void OnDivide();
	afx_msg void OnSqrt();
	afx_msg void OnBack();
	afx_msg void OnCe();
	afx_msg void OnC();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORDLG_H__E9D25D32_6919_4C99_A48D_E3F63572F882__INCLUDED_)

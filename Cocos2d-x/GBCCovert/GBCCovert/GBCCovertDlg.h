// GBCCovertDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CGBCCovertDlg �Ի���
class CGBCCovertDlg : public CDialog
{
// ����
public:
	CGBCCovertDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GBCCOVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_edHZ;
	CEdit m_edGBK10;
	CEdit m_edGBK16;
	CEdit m_edGBKHZ;
	CEdit m_edUni10;
	CEdit m_edUni16;
	CEdit m_edUniHZ;
};


#pragma once
#include "afxwin.h"


// CUserDlg �Ի���

class CUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USER_ATTRI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// ͷ��
	CEdit m_edLogoID;
	// �û��ǳ�
	CEdit m_edNickName;
};

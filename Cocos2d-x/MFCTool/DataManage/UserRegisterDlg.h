#pragma once


// CUserRegisterDlg �Ի���

class CUserRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserRegisterDlg)

public:
	CUserRegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserRegisterDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

#pragma once


// CUserRegisterDlg 对话框

class CUserRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserRegisterDlg)

public:
	CUserRegisterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserRegisterDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_USER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

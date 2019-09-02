// UserRegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "UserRegisterDlg.h"
#include "afxdialogex.h"


// CUserRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CUserRegisterDlg, CDialogEx)

CUserRegisterDlg::CUserRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserRegisterDlg::IDD, pParent)
{

}

CUserRegisterDlg::~CUserRegisterDlg()
{
}

void CUserRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserRegisterDlg, CDialogEx)
END_MESSAGE_MAP()


// CUserRegisterDlg 消息处理程序

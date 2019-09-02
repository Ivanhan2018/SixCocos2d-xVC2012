// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include "DataManageDlg.h"

// CUserDlg �Ի���

IMPLEMENT_DYNAMIC(CUserDlg, CDialogEx)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserDlg::IDD, pParent)
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edLogoID);
	DDX_Control(pDX, IDC_EDIT2, m_edNickName);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUserDlg ��Ϣ�������


void CUserDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDataManageDlg *pDataManageDlg=((CDataManageDlg *)theApp.m_pMainWnd);
	//if(!pDataManageDlg||!pDataManageDlg->m_pClientComm)
	//	return;

	if(!pDataManageDlg->IsConnected())
	{
		::AfxMessageBox(L"�����������ݹ������");
		return;
	}

	CString strPlayerID;
	pDataManageDlg->m_edPlayerID.GetWindowText(strPlayerID);

	CString strLogoID;
	m_edLogoID.GetWindowText(strLogoID);
	if(strLogoID.IsEmpty())
	{
		::AfxMessageBox(L"������ͷ��ID��");
		m_edLogoID.SetFocus();
		return;
	}


	CString strNickName;
	m_edNickName.GetWindowText(strNickName);
	if(strNickName.IsEmpty())
	{
		::AfxMessageBox(L"�������û��ǳƣ�");
		m_edNickName.SetFocus();
		return;
	}

	string str=PUBLIC::ws2s(strNickName.GetString());

	Req_ModifyUserData UserData;
	UserData.lUserID= _wtoi64(strPlayerID.GetString());
	UserData.lSyslogoid = _wtoi64(strLogoID.GetString());
	memcpy(UserData.szNickName,str.c_str(), sizeof(UserData.szNickName));
	//pDataManageDlg->m_pClientComm->send_data(MAIN_DMS,REQ_UPDATE_USER_DATA,(BYTE*)&UserData,sizeof(UserData));
	
	//���
	//struct Req_ModifyUserDataEx:public CORE_MSG_HEAD,Req_ModifyUserData
	//{

	//};
	EXTRA_PACK_STRUCT(Req_ModifyUserData)
	Req_ModifyUserDataEx req;
	//req.iOpType=3;
	req.lUserID= _wtoi64(strPlayerID.GetString());
	req.lSyslogoid = _wtoi64(strLogoID.GetString());
	memcpy(req.szNickName,str.c_str(), sizeof(req.szNickName));
	req.iMainCode=MAIN_DMS;
	req.iSubCode=REQ_UPDATE_USER_DATA;
	//req.set_heartbeat();
	req.uFlag=0xaaaaaaaaaaaaaaaa;
	req.SetTotalSize(sizeof(Req_ModifyUserDataEx));

	pDataManageDlg->m_pClientComm->Send((const char*)&req,sizeof(req));
}

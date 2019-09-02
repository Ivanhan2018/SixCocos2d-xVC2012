
// DataManageDlg.h : ͷ�ļ�
//
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Resource.h"
//#include "./ClientComm.h"
#include "ClientSocket.h"
//#include "./Often.h"


// CDataManageDlg �Ի���
class CDataManageDlg : public CDialogEx 
	           //, public CGerneralListen  // Ҫ���� public CDialogEx �ĺ���
{
// ����
public:
	CDataManageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DATAMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnNetMsgReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetMsgNetDown(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	void SetConnected(bool bConnected);
	bool IsConnected()const{return m_bConnected;}
public:
	// ��������Ӧ��Ϣ�������Ǵӷ�������������Ϣ
	virtual int OnResponse(int iMainCode, int iSubCode, void* pData, int iDataLen);

	void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	void HandlePacketDMS(int iSubCode,const BYTE* pData,int iDataLen);

public:
	//CClientComm* m_pClientComm;	// �ͻ���ͨѶ
	ClientSocket* m_pClientComm;	// �ͻ���ͨѶ
private:
	char m_szIp[32];
	int  m_iPort;
	bool m_bConnected;
public:
	
	afx_msg void OnBnClickedButtonLogin();
	// �û���
	CEdit m_edUser;
	// ����
	CEdit m_edPassword;
	// ����
	CButton m_btnConnect;
	// �����������״̬
	CStatic m_csInfo;
	afx_msg void OnBnClickedBtnConnect();
	// ��̨���ݹ��������IP
	CIPAddressCtrl m_ipDBGIP;
	// ��̨���ݿ������˿�
	CEdit m_edDBGPort;
	afx_msg void OnBnClickedButton1();
	// �û�ID
	CEdit m_edPlayerID;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

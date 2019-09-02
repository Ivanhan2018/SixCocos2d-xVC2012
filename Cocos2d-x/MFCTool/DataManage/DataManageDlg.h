
// DataManageDlg.h : 头文件
//
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Resource.h"
//#include "./ClientComm.h"
#include "ClientSocket.h"
//#include "./Often.h"


// CDataManageDlg 对话框
class CDataManageDlg : public CDialogEx 
	           //, public CGerneralListen  // 要放在 public CDialogEx 的后面
{
// 构造
public:
	CDataManageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DATAMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 接收器响应消息，往往是从发射器传来的消息
	virtual int OnResponse(int iMainCode, int iSubCode, void* pData, int iDataLen);

	void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	void HandlePacketDMS(int iSubCode,const BYTE* pData,int iDataLen);

public:
	//CClientComm* m_pClientComm;	// 客户端通讯
	ClientSocket* m_pClientComm;	// 客户端通讯
private:
	char m_szIp[32];
	int  m_iPort;
	bool m_bConnected;
public:
	
	afx_msg void OnBnClickedButtonLogin();
	// 用户名
	CEdit m_edUser;
	// 密码
	CEdit m_edPassword;
	// 连接
	CButton m_btnConnect;
	// 与服务器连接状态
	CStatic m_csInfo;
	afx_msg void OnBnClickedBtnConnect();
	// 后台数据管理服务器IP
	CIPAddressCtrl m_ipDBGIP;
	// 后台数据库管理服端口
	CEdit m_edDBGPort;
	afx_msg void OnBnClickedButton1();
	// 用户ID
	CEdit m_edPlayerID;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

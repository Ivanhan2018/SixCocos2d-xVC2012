#pragma once
#include "afxwin.h"
#include "resource.h"
#include "HelloWorldScene.h"
#include "numbericedit.h"
#include "cocos2d.h"
#include "afxcolorbutton.h"

class CCocos_Partical_Editor_MFCDlg : public CDialogEx
{
public:
	CCocos_Partical_Editor_MFCDlg(CWnd* pParent = NULL);	
	virtual ~CCocos_Partical_Editor_MFCDlg()
	{
		DestroyWindow();
	}
	enum { IDD = IDD_COCOS_PARTICAL_EDITOR_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

public:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();

protected:
	HICON m_hIcon;

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};

class CPartical_Detial_Dlg_ModeA:public CDialogEx
{
public:
	CPartical_Detial_Dlg_ModeA(CWnd* pParent = NULL);	
	virtual ~CPartical_Detial_Dlg_ModeA()
	{
		DestroyWindow();
	}
	enum { IDD = IDD_MODE_A };
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();

public:
	void Load(cocos2d::CCParticleSystem* particals);
	void Update(cocos2d::CCParticleSystem* particals);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

protected:
	HICON m_hIcon;

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CNumbericEdit m_speed;
	CNumbericEdit m_speedVar;
	CNumbericEdit m_tangentialAccel;
	CNumbericEdit m_tangentialAccelVar;
	CNumbericEdit m_radialAccel;
	CNumbericEdit m_radialAccelVar;
	CNumbericEdit m_Gravity_x;
	CNumbericEdit m_Gravity_y;

	float speed;
	float speedVar;
	float tangentialAccel;
	float tangentialAccelVar;
	float radialAccel;
	float radialAccelVar;
	float m_gx;
	float m_gy;
};

class CPartical_Detial_Dlg_ModeB:public CDialogEx
{
public:
	CPartical_Detial_Dlg_ModeB(CWnd* pParent = NULL);
	virtual ~CPartical_Detial_Dlg_ModeB()
	{
		DestroyWindow();
	}
	enum { IDD = IDD_MODE_B };

public:
	void Load(cocos2d::CCParticleSystem* particals);
	void Update(cocos2d::CCParticleSystem* particals);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CNumbericEdit m_startRadius;
	CNumbericEdit m_startRdiusVar;
	CNumbericEdit m_endRadius;
	CNumbericEdit m_endRadiusVar;
	CNumbericEdit m_rotatePerSecond;
	CNumbericEdit m_rotatePerSecondVar;

	float startRadius;
	float startRadiusVar;
	float endRadius;
	float endRadiusVar;
	float rotatePerSecond;
	float rotatePerSecondVar;
};

class CCos_Partical_Editor:public CDialogEx,public MFC_WND_Delegate
{
public:
	CCos_Partical_Editor(CWnd* pParent = NULL);	
	virtual ~CCos_Partical_Editor()
	{
		DestroyWindow();
	}
	enum { IDD = IDD_DLGCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

public:
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();

private:
	CPartical_Detial_Dlg_ModeA* dlg_modeA;
	CPartical_Detial_Dlg_ModeB* dlg_modeB;

protected:
	HICON m_hIcon;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void LoadTextruePreview();

public:
	afx_msg void OnBnClickedModeA();
	afx_msg void OnBnClickedModeB();

	afx_msg void OnBnClickedShow();
	afx_msg void OnBnClickedHide();

	virtual void Set();
	virtual void Load();
	virtual void LoadFile();
	void RefreshRunTargetCMB();

	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedBrowserTexture();

private:
	CNumbericEdit m_start;
	CNumbericEdit m_startvar;
	CNumbericEdit m_stop;
	CNumbericEdit m_stopvar;
	CNumbericEdit m_startspin;
	CNumbericEdit m_startspinvar;
	CNumbericEdit m_stopspin;
	CNumbericEdit m_stopspinvar;
	CNumbericEdit m_EmissionRate;
	CNumbericEdit m_startcolorAlpha;
	CNumbericEdit m_startcolorVarAlpha;
	CNumbericEdit m_EndColorAlpha;
	CNumbericEdit m_EndColorVarAlpha;
	CNumbericEdit m_Angle;
	CNumbericEdit m_AngleVar;
	CNumbericEdit m_life;
	CNumbericEdit m_LifeVar;
	CMFCColorButton m_startcolor;
	CMFCColorButton m_startcolorVar;
	CMFCColorButton m_endcolor;
	CMFCColorButton m_endcolorVar; 
	CComboBox m_blendCB_dst;
	CComboBox m_blendCB_src;
	CButton m_partTypeA;
	CButton m_partTypeB;
	CButton m_partShow;
	CButton m_partHide;
	CButton m_runTargetBg;
	CButton m_runTargetSpr;
	CComboBox m_runTargetSprCMB;
	CStatic m_textrue_preview;

	unsigned int  m_uTotalParticales;
	char		  m_tBlendFunc;

	int m_as;
	int m_asv;
	int m_ae;
	int m_aev;

	float m_fDuration;
	float m_fLife;
	float m_fLifeVar;
	float m_fAngle;
	float m_fAngleVar;
	float m_fStartSize;
	float m_fStartSizeVar;
	float m_fEndSize;
	float m_fEndSizeVar;
	float m_fStartSpin;
	float m_fStartSpinVar;
	float m_fEndSpin;
	float m_fEndSpinVar;
	CString m_StrPath;
	HBITMAP m_hTexture;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnCbnSelchangeCombo4();
};

#pragma once

#include "cocos2d.h"
#include "CCEGLView.h"
#include "Utility.h"
#include "FileView.h"

USING_NS_CC;

class MyProp:public CMFCPropertyGridCtrl
{
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// 构造
public:
	CPropertiesWnd();

	void AdjustLayout();

// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndSpritePropList.SetVSDotNetLook(bSet);
		m_wndSpritePropList.SetGroupNameFullWidth(bSet);
	}

	void OnSelectSprite(CCSprite*);
	void OnUpdateSpriteFramePos(CCSprite*,POINT_INFO*);
	void OnUpdateSceneBg();

	void runActionFinished(CCNode*);
	void UpdateSceneBg(CString &sceneBgImg);

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndScenePropList;
	MyProp m_wndSpritePropList;

// 实现
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnDropdown();
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	LRESULT OnScenePropertyChanged(CMFCPropertyGridProperty *);
	LRESULT OnSpritePropertyChanged(CMFCPropertyGridProperty *);
	void switchComonBox();

	DECLARE_MESSAGE_MAP()

	void InitScenePropList();
	void InitSpritePropList();

	void SetPropListFont();
};


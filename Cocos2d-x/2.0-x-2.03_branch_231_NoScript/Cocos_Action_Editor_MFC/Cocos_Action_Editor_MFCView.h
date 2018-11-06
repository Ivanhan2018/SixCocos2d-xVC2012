
// Cocos_Action_Editor_MFCView.h : CCocos_Action_Editor_MFCView 类的接口
//

#pragma once


class CCocos_Action_Editor_MFCView : public CView
{
protected: // 仅从序列化创建
	CCocos_Action_Editor_MFCView();
	DECLARE_DYNCREATE(CCocos_Action_Editor_MFCView)

// 特性
public:
	CCocos_Action_Editor_MFCDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CCocos_Action_Editor_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	bool IsInited;

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	LRESULT CC2DX_MSG(WPARAM,LPARAM);
	LRESULT CC2DX_MSG2(WPARAM,LPARAM);
	LRESULT CC2DX_MSG3(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Cocos_Action_Editor_MFCView.cpp 中的调试版本
inline CCocos_Action_Editor_MFCDoc* CCocos_Action_Editor_MFCView::GetDocument() const
   { return reinterpret_cast<CCocos_Action_Editor_MFCDoc*>(m_pDocument); }
#endif


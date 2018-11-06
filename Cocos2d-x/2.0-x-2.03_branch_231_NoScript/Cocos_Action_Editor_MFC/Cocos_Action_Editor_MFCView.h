
// Cocos_Action_Editor_MFCView.h : CCocos_Action_Editor_MFCView ��Ľӿ�
//

#pragma once


class CCocos_Action_Editor_MFCView : public CView
{
protected: // �������л�����
	CCocos_Action_Editor_MFCView();
	DECLARE_DYNCREATE(CCocos_Action_Editor_MFCView)

// ����
public:
	CCocos_Action_Editor_MFCDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CCocos_Action_Editor_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	bool IsInited;

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Cocos_Action_Editor_MFCView.cpp �еĵ��԰汾
inline CCocos_Action_Editor_MFCDoc* CCocos_Action_Editor_MFCView::GetDocument() const
   { return reinterpret_cast<CCocos_Action_Editor_MFCDoc*>(m_pDocument); }
#endif


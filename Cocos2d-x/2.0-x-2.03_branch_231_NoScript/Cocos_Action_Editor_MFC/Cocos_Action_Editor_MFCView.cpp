
// Cocos_Action_Editor_MFCView.cpp : CCocos_Action_Editor_MFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cocos_Action_Editor_MFC.h"
#endif

#include "Cocos_Action_Editor_MFCDoc.h"
#include "Cocos_Action_Editor_MFCView.h"
#include "MainFrm.h"

#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_PK	WM_USER + 110
#define WM_PK2	WM_USER	+ 111
#define WM_PK3	WM_USER	+ 112

USING_NS_CC;

// CCocos_Action_Editor_MFCView

IMPLEMENT_DYNCREATE(CCocos_Action_Editor_MFCView, CView)

BEGIN_MESSAGE_MAP(CCocos_Action_Editor_MFCView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_MESSAGE(WM_PK,CC2DX_MSG)
	ON_MESSAGE(WM_PK2,CC2DX_MSG2)
	ON_MESSAGE(WM_PK3,CC2DX_MSG3)
END_MESSAGE_MAP()

// CCocos_Action_Editor_MFCView ����/����

CCocos_Action_Editor_MFCView::CCocos_Action_Editor_MFCView()
{
	// TODO: �ڴ˴���ӹ������
	IsInited = false;
}

CCocos_Action_Editor_MFCView::~CCocos_Action_Editor_MFCView()
{
}

BOOL CCocos_Action_Editor_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCocos_Action_Editor_MFCView ����

void CCocos_Action_Editor_MFCView::OnDraw(CDC* /*pDC*/)
{
	CCocos_Action_Editor_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CCocos_Action_Editor_MFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CCocos_Action_Editor_MFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CCocos_Action_Editor_MFCView::OnSize(UINT nType,int cx,int cy)
{
	if (IsInited)
	{
		CCEGLView::sharedOpenGLView()->setFrameSize(cx,cy);
		CCEGLView::sharedOpenGLView()->resize(cx,cy);
	}
}

// CCocos_Action_Editor_MFCView ���

#ifdef _DEBUG
void CCocos_Action_Editor_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CCocos_Action_Editor_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCocos_Action_Editor_MFCDoc* CCocos_Action_Editor_MFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCocos_Action_Editor_MFCDoc)));
	return (CCocos_Action_Editor_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCocos_Action_Editor_MFCView ��Ϣ�������

LRESULT CCocos_Action_Editor_MFCView::CC2DX_MSG(WPARAM wParam,LPARAM lParam)
{
	// ˢ���������
	CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
	CCSprite *pSprite = (CCSprite*)wParam;
	pMainFrame->OnSelectSprite(pSprite);
	return 0;
}

LRESULT CCocos_Action_Editor_MFCView::CC2DX_MSG2(WPARAM wParam,LPARAM lParam)
{
	// ˢ���������
	CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
	CCSprite *pSprite = (CCSprite*)wParam;
	POINT_INFO *pPoint = (POINT_INFO*)lParam;
	pMainFrame->OnUpdateSpriteFramePos(pSprite,pPoint);
	return 0;
}

LRESULT CCocos_Action_Editor_MFCView::CC2DX_MSG3(WPARAM wParam,LPARAM lParam)
{
	// ˢ���������
	CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
	pMainFrame->OnUpdateSceneBg();
	return 0;
}
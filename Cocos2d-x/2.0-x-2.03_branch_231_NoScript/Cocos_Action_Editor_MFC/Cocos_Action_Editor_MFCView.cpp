
// Cocos_Action_Editor_MFCView.cpp : CCocos_Action_Editor_MFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CCocos_Action_Editor_MFCView 构造/析构

CCocos_Action_Editor_MFCView::CCocos_Action_Editor_MFCView()
{
	// TODO: 在此处添加构造代码
	IsInited = false;
}

CCocos_Action_Editor_MFCView::~CCocos_Action_Editor_MFCView()
{
}

BOOL CCocos_Action_Editor_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCocos_Action_Editor_MFCView 绘制

void CCocos_Action_Editor_MFCView::OnDraw(CDC* /*pDC*/)
{
	CCocos_Action_Editor_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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

// CCocos_Action_Editor_MFCView 诊断

#ifdef _DEBUG
void CCocos_Action_Editor_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CCocos_Action_Editor_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCocos_Action_Editor_MFCDoc* CCocos_Action_Editor_MFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCocos_Action_Editor_MFCDoc)));
	return (CCocos_Action_Editor_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCocos_Action_Editor_MFCView 消息处理程序

LRESULT CCocos_Action_Editor_MFCView::CC2DX_MSG(WPARAM wParam,LPARAM lParam)
{
	// 刷新属性面板
	CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
	CCSprite *pSprite = (CCSprite*)wParam;
	pMainFrame->OnSelectSprite(pSprite);
	return 0;
}

LRESULT CCocos_Action_Editor_MFCView::CC2DX_MSG2(WPARAM wParam,LPARAM lParam)
{
	// 刷新属性面板
	CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
	CCSprite *pSprite = (CCSprite*)wParam;
	POINT_INFO *pPoint = (POINT_INFO*)lParam;
	pMainFrame->OnUpdateSpriteFramePos(pSprite,pPoint);
	return 0;
}

LRESULT CCocos_Action_Editor_MFCView::CC2DX_MSG3(WPARAM wParam,LPARAM lParam)
{
	// 刷新属性面板
	CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
	pMainFrame->OnUpdateSceneBg();
	return 0;
}
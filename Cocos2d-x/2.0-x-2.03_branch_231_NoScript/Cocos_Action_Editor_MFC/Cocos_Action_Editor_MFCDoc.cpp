
// Cocos_Action_Editor_MFCDoc.cpp : CCocos_Action_Editor_MFCDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Cocos_Action_Editor_MFC.h"
#endif

#include "Cocos_Action_Editor_MFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCocos_Action_Editor_MFCDoc

IMPLEMENT_DYNCREATE(CCocos_Action_Editor_MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CCocos_Action_Editor_MFCDoc, CDocument)
END_MESSAGE_MAP()


// CCocos_Action_Editor_MFCDoc 构造/析构

CCocos_Action_Editor_MFCDoc::CCocos_Action_Editor_MFCDoc()
{
	// TODO: 在此添加一次性构造代码

}

CCocos_Action_Editor_MFCDoc::~CCocos_Action_Editor_MFCDoc()
{
}

BOOL CCocos_Action_Editor_MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCocos_Action_Editor_MFCDoc 序列化

void CCocos_Action_Editor_MFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCocos_Action_Editor_MFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCocos_Action_Editor_MFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCocos_Action_Editor_MFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCocos_Action_Editor_MFCDoc 诊断

#ifdef _DEBUG
void CCocos_Action_Editor_MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCocos_Action_Editor_MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCocos_Action_Editor_MFCDoc 命令


#include "stdafx.h"
#include "ViewTree.h"
#include "FileView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString gFrameName;
bool gIsFrame = false;
int gHitPoint = -1;
CCSprite *gSelectSprite = 0;

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}
	pScene->setBBoxDirty(false);

	gFrameName.Empty();
	gIsFrame = false;

	CPoint ptCurSel(0,0);
	TVHITTESTINFO HitTestInfo;
	// 通过鼠标在客户区中的位置
	GetCursorPos(&ptCurSel);
	this->ScreenToClient(&ptCurSel);
	HitTestInfo.pt = ptCurSel;
	HTREEITEM hSelect = this->HitTest(&HitTestInfo);
	if(hSelect)
	{
		// 设置该项为选中状态
		this->SelectItem(hSelect);
		// 取SpriteInfo
		SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)this->GetItemData(hSelect);
		if (pSpriteInfo)
		{
			//CString text;
			//text.Format(L"pSpriteInfo[0x%08X].idx[%u].imagePath[%s].ItemText[%s]",
			//	pSpriteInfo,
			//	pSpriteInfo->idx,
			//	pSpriteInfo->imagePath.GetString(),
			//	this->GetItemText(hSelect).GetString()
			//);
			//::AfxMessageBox(text);

			// 显示Sprite的BoundingBox
			// Add by Cool.Cat
			CCSprite *pChild = dynamic_cast<CCSprite*>(pScene->getChildByTag(pSpriteInfo->idx));
			if (!pChild)
			{
				AfxMessageBox(L"对象不存在！");
				return;
			}

			pChild->setBBoxDirty(true);

			// 刷新属性面板
			gFrameName.Append(this->GetItemText(hSelect).GetString());
			CMainFrame* pMainFrame = (CMainFrame*)(this->GetParentFrame());
			pMainFrame->OnSelectSprite(pChild);
			gSelectSprite = pChild;
		}
	}
	else
	{
	}
	*pResult = 0;
}
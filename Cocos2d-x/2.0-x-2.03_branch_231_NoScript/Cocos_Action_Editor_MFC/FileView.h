
#pragma once
#include "resource.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCEGLView.h"
#include "HelloWorldScene.h"
#include "Utility.h"
#include "tinyxml/tinyxml.h"
#include "SIX_XMLParser.h"

#include "ViewTree.h"
#include <map>
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

//typedef map<CString,HITBOX_MAP*> FHITBOX_MAP;
//typedef FHITBOX_MAP::iterator FHITBOX_ITER;

typedef struct tagSpriteInfo{
	unsigned int idx;
	CString imageName;
	CString imagePath;
	CArray<CString,CString&> imageFrameName;
	FHITBOX_MAP frameHBox;
	bool runAction;
	CCPoint runActionBeforePoint;

	tagSpriteInfo()
	{
		idx = 0;
		runAction = false;
		runActionBeforePoint = CCPoint(0,0);
	}
	~tagSpriteInfo()
	{
		for (FHITBOX_ITER fIter=frameHBox.begin();fIter!=frameHBox.end();)
		{
			HITBOX_MAP *pHitBox = fIter->second;
			frameHBox.erase(fIter++);
			for (HITBOX_ITER mIter=pHitBox->begin();mIter!=pHitBox->end();)
			{
				POINT_INFO *pPoint = mIter->second;
				pHitBox->erase(mIter++);
				CC_SAFE_DELETE(pPoint);
			}
			CC_SAFE_DELETE(pHitBox);
		}
	}
}SPRITE_INFO;

typedef map<unsigned int,SPRITE_INFO*> SPRITE_MAP;
typedef SPRITE_MAP::iterator SPRITE_ITER;

static unsigned int gSpriteIdx = 0;

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// 构造
public:
	CFileView();

	void AdjustLayout();
	//void OnChangeVisualStyle();

// 特性
protected:

	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	void FillFileView();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 实现
public:
	virtual ~CFileView();
	CString GetWorkDir();

	SPRITE_MAP m_SpriteMap;
	CString ChooseFolder();
	void SaveSpriteInfo2File(CString,SPRITE_INFO*);
	void LoadSpriteInfoFromFile(CString);
	int ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnOpenImage();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};



#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "Cocos_Action_Editor_MFC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define WM_PK3	WM_USER	+ 112

/////////////////////////////////////////////////////////////////////////////
// CFileView

CString gBackgroundImg;

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
	for (SPRITE_ITER iter=m_SpriteMap.begin();iter!=m_SpriteMap.end();)
	{
		SPRITE_INFO *pSprite = iter->second;
		m_SpriteMap.erase(iter++);
		CC_SAFE_DELETE(pSprite);
	}
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_SAVE, OnFileSave)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_OPEN_IMAGE, &CFileView::OnOpenImage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;
	}

	//m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	//m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE);

	//OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("属性...."));

}

CString CFileView::GetWorkDir()
{
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(1024),1023);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	return path.Left(pos);
}

// Add by Cool.Cat
void CFileView::OnOpenImage()
{
	LPCTSTR szFilter = L"PNG(*.PNG)|*.PNG|JPG(*.JPG)|*.JPG|BMP(*.BMP)|*.BMP||";
	CFileDialog oFileDlg(TRUE, L".PNG", NULL, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST, szFilter);
	oFileDlg.m_ofn.lpstrInitialDir = (BSTR)GetWorkDir().GetString();
	TCHAR szLargeBuf[4096]={0};
	memset(szLargeBuf,0,sizeof(szLargeBuf));
	oFileDlg.m_ofn.lpstrFile = szLargeBuf;
	oFileDlg.m_ofn.nMaxFile = 4096;

	if(oFileDlg.DoModal() == IDOK)
	{
		POSITION posFile=oFileDlg.GetStartPosition();
		if (posFile<0)
			return;

		SPRITE_INFO *pSpriteInfo = new SPRITE_INFO();
		//memset(pSpriteInfo,0,sizeof(pSpriteInfo));
		pSpriteInfo->idx = ++gSpriteIdx;
		pSpriteInfo->imagePath.Empty();
		pSpriteInfo->imagePath.Append(oFileDlg.GetFolderPath().GetString());
		pSpriteInfo->imageFrameName.RemoveAll();
		CString fullPath;
		while(posFile)
		{
			fullPath.Empty();
			fullPath.Append(oFileDlg.GetNextPathName(posFile));
			if (!PathFileExists(fullPath))
				break;

			CString frameName(fullPath.Right(fullPath.GetLength()-fullPath.ReverseFind('\\')-1));

			pSpriteInfo->imageFrameName.Add(frameName);

			//// add hitbox data element
			//// Cool.Cat
			//CCSet *pHitBox = new CCSet();
			//pSpriteInfo->hitBox.insert(HITBOX_MAP::value_type(frameName,pHitBox));
		}
		m_SpriteMap.insert(SPRITE_MAP::value_type(pSpriteInfo->idx,pSpriteInfo));

		FillFileView();
		AdjustLayout();

		//AfxGetApp()->OpenDocumentFile(fullPath);
	}
}

// Add by Cool.Cat
void CFileView::FillFileView()
{
	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}

	// remove all node first
	// Cool.Cat
	m_wndFileView.DeleteAllItems();

	CCSize viewSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	SPRITE_ITER mIter = m_SpriteMap.begin();
	for (;mIter!=m_SpriteMap.end();mIter++)
	{
		SPRITE_INFO *pSpriteInfo = mIter->second;
		if (pSpriteInfo)
		{
			CString nodeName;
			if (!pSpriteInfo->imageName.GetLength())
			{
				nodeName.Format(L"CCSprite-%04d",pSpriteInfo->idx);
				pSpriteInfo->imageName.Append(nodeName.GetString());
			}
			else
				nodeName.Format(L"%s",pSpriteInfo->imageName.GetString());

			HTREEITEM hRoot = m_wndFileView.InsertItem(nodeName.GetString(), 0, 0);
			m_wndFileView.SetItemData(hRoot,(DWORD_PTR)pSpriteInfo);
			m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

			bool NeedAdd = false;
			if (!pScene->getChildByTag(pSpriteInfo->idx))
				NeedAdd = true;

			CCArray *pArray = CCArray::create();
			for (int i=0;i<pSpriteInfo->imageFrameName.GetCount();i++)
			{
				CString fileName = pSpriteInfo->imageFrameName.GetAt(i).GetString();
				HTREEITEM hItem = m_wndFileView.InsertItem(fileName.GetString(), 1, 1, hRoot);
				m_wndFileView.SetItemData(hItem,(DWORD_PTR)pSpriteInfo);

				if (NeedAdd)
				{
					// 丢给CC2DX执行Action
					// Add by Cool.Cat
					CString fullPath;
					fullPath.Format(L"%s\\%s",pSpriteInfo->imagePath.GetString(),fileName.GetString());

					CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage(Utility::UnicodeToAnsi(fullPath).c_str());
					CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTex,CCRect(0,0,pTex->getContentSize().width,pTex->getContentSize().height));
					CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(pFrame,Utility::UnicodeToAnsi(fileName).c_str());

					pArray->addObject(pFrame);

					// 从FHITBOX_MAP导入数据
					FHITBOX_ITER fIter = pSpriteInfo->frameHBox.find(Utility::UnicodeToUtf8(fileName.GetString()));
					if (fIter!=pSpriteInfo->frameHBox.end())
					{
						HITBOX_MAP *pHBox = fIter->second;
						if (pHBox)
						{
							pFrame->getTexture()->setHitBox(pHBox);
						}
					}
					// 从图像帧导入，所以要初始化HBox
					else
					{
						HITBOX_MAP *pHBox = new HITBOX_MAP();
						for (int i=1;i<=MAX_VERTEX_COUNT;i++)
						{
							POINT_INFO *pPoint = new POINT_INFO(-1,-1);
							pHBox->insert(HITBOX_MAP::value_type(i,pPoint));
						}
						pFrame->getTexture()->setHitBox(pHBox);
					}

					//// ----------------------------------
					//// hitbox顶点测试
					//// Cool.Cat
					//// ----------------------------------
					//HITBOX_MAP *hitbox = new HITBOX_MAP();
					//for (int i=1;i<=MAX_VERTEX_COUNT;i++)
					//{
					//	if (i<=8)
					//	{
					//		POINT_INFO *pPoint = new POINT_INFO(i*10,(i%2)?i*5:i*10);
					//		hitbox->insert(HITBOX_MAP::value_type(i,pPoint));
					//	}
					//	else
					//	{
					//		POINT_INFO *pPoint = new POINT_INFO(-1,-1);
					//		hitbox->insert(HITBOX_MAP::value_type(i,pPoint));
					//	}
					//}
					//pFrame->getTexture()->setHitBox(hitbox);
				}
			}

			m_wndFileView.Expand(hRoot, TVE_EXPAND);

			if (NeedAdd)
			{
				CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames( pArray, 0.1f );
				CCAnimate *pAnimate = CCAnimate::create( pAnimation );
				CCRepeatForever *pRepeat = CCRepeatForever::create( pAnimate );
				pRepeat->setTag(0);

				CCSpriteFrame *pFrame = (CCSpriteFrame*)pArray->objectAtIndex(0);

				CCSprite *pSpr = CCSprite::createWithSpriteFrame(pFrame);
				pSpr->setAnchorPoint(ccp(0.5,0.5));
				pSpr->setPosition(ccp((viewSize.width-pSpr->getContentSize().width)/2,(viewSize.height-pSpr->getContentSize().height)/2));
				pSpr->setColor(ccc3(255,255,255));
				pSpr->setOpacity(255);
				pSpr->setTag(pSpriteInfo->idx);
				pSpr->setObjName(Utility::UnicodeToUtf8(nodeName.GetString()).c_str());
				pSpr->runAction(pRepeat);
				pScene->addChild(pSpr);
				pSpr->setUserData((void*)pSpriteInfo);
				//pSpriteInfo->pSpriteEnt = pSpr;

				CCLabelTTF *pTTF = dynamic_cast<CCLabelTTF*>(pScene->getChildByTag(100));
				if (pTTF)
				{
					pTTF->setString(Utility::UnicodeToUtf8(L"点击左侧精灵树可进行常规操作").c_str());
					pTTF->setColor(ccc3(255,255,0));
				}
			}
		}
	}
}

CString CFileView::ChooseFolder() 
{
    // TODO: Add your control notification handler code here
    CString m_path;
    TCHAR szDir[1024];
    BROWSEINFO bi;
    ITEMIDLIST *pidl;
    bi.hwndOwner=this->m_hWnd; // 指定父窗口，在对话框显示期间，父窗口将被禁用 
    bi.pidlRoot=NULL; // 如果指定NULL，就以“桌面”为根 
    bi.pszDisplayName=szDir;
    bi.lpszTitle=L"请选择目录"; // 这一行将显示在对话框的顶端 
    bi.ulFlags=BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
    bi.lpfn=NULL;
    bi.lParam=0;
    bi.iImage=0;
    pidl = SHBrowseForFolder(&bi);
    //pidl=SHBrowseForFolder(&amp;bi);
    if(pidl==NULL) 
        return L"";
    if(!SHGetPathFromIDList(pidl, szDir)) 
        return L"";
    else
        m_path=szDir;
    //SetDlgItemText(IDC_EDIT_PATH, m_path);
	return m_path;
}

void CFileView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	LPCTSTR szFilter = L"PCC(*.pcc)|*.pcc||";
	CFileDialog oFileDlg(TRUE, L".pcc", NULL, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST, szFilter);
	oFileDlg.m_ofn.lpstrInitialDir = (BSTR)GetWorkDir().GetString();
	TCHAR szLargeBuf[4096]={0};
	memset(szLargeBuf,0,sizeof(szLargeBuf));
	oFileDlg.m_ofn.lpstrFile = szLargeBuf;
	oFileDlg.m_ofn.nMaxFile = 4096;

	if(oFileDlg.DoModal() == IDOK)
	{
		POSITION posFile=oFileDlg.GetStartPosition();
		if (posFile<0)
			return;

		CString fullPath;
		while(posFile)
		{
			fullPath.Empty();
			fullPath.Append(oFileDlg.GetNextPathName(posFile));
			if (!PathFileExists(fullPath))
				break;

			LoadSpriteInfoFromFile(fullPath);
		}
	}
}

void CFileView::OnFileSave()
{
	CreateDirectory(_T("Output"),NULL);

	//LPCTSTR szFilter = L"PCC(*.pcc)|*.pcc||";
	//CFileDialog oFileDlg(FALSE, L".pcc", NULL, OFN_HIDEREADONLY, szFilter);
	//oFileDlg.m_ofn.lpstrInitialDir = (BSTR)GetWorkDir().GetString();
	//TCHAR szLargeBuf[4096]={0};
	//memset(szLargeBuf,0,sizeof(szLargeBuf));
	//oFileDlg.m_ofn.lpstrFile = szLargeBuf;
	//oFileDlg.m_ofn.nMaxFile = 4096;

	//if(oFileDlg.DoModal() != IDOK)
	//	return;

	//CString path(oFileDlg.GetPathName());
	CString path(ChooseFolder());

	if (!path.GetLength())
	{
		return;
	}

	// save it~
	for (SPRITE_ITER mIter = m_SpriteMap.begin();mIter!=m_SpriteMap.end();mIter++)
	{
		SPRITE_INFO *pSpriteInfo = mIter->second;

		SaveSpriteInfo2File(path,pSpriteInfo);
	}

	AfxMessageBox(L"导出完成！");
}

void CFileView::LoadSpriteInfoFromFile(CString fullPath)
{
	SIX_XMLParser *pXML = new SIX_XMLParser();

	int retv = pXML->LoadXMLFromFile(Utility::UnicodeToAnsi(fullPath.GetString()).c_str());
	if (retv==-1 || retv==-2)
	{
		AfxMessageBox(L"导入配置文件失败！");
		return;
	}

	ParseXML(pXML->GetXMLDataSet());

	pXML->ReleaseXMLDataSet();

	CC_SAFE_DELETE(pXML);

	FillFileView();
}

int CFileView::ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet)
{
	SIX_XmlDataSet *pDataSet = 0;

	//SIXLog("ParseXML.GetChildrenCount[%d]",pXmlDataSet->GetChildrenCount());
	CCARRAY_FOREACH_T(pXmlDataSet->GetChildren(),pDataSet,SIX_XmlDataSet*)
	{
		// 跳过Root和Comment
		if (pDataSet->getKey().compareIgnoreCase("Element"))
			continue;

		if (pDataSet->pDataElement)
		{
			if (!pDataSet->getValue().compareIgnoreCase("Scene"))
			{
				SIX_KV *pKVPcc = 0;
				CCARRAY_FOREACH_T(pDataSet->pDataElement->GetChildren(),pKVPcc,SIX_KV*)
				{
					if (!CString(pKVPcc->getKey().getCString()).CompareNoCase(L"bg"))
					{
						gBackgroundImg.Empty();
						gBackgroundImg.Append(Utility::Utf8ToUnicode(pKVPcc->getValue().getCString()).c_str());
						if (gBackgroundImg.GetLength())
							::PostMessage(CCEGLView::sharedOpenGLView()->getAttachWindow(),WM_PK3,0,0);
					}
				}
			}
			else if (!pDataSet->getValue().compareIgnoreCase("Sprite"))
			{
				SPRITE_INFO *pSpriteInfo = new SPRITE_INFO();
				pSpriteInfo->idx = ++gSpriteIdx;
				pSpriteInfo->imagePath.Empty();

				// save it~
				pair<SPRITE_ITER,bool> result = m_SpriteMap.insert(SPRITE_MAP::value_type(pSpriteInfo->idx,pSpriteInfo));
				if (!result.second)
					continue;

				// get frame
				SIX_XmlDataSet *pDataSetFrame = 0;
				CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pDataSetFrame,SIX_XmlDataSet*)
				{
					SIX_KV *pKVFrame = 0;
					CString frameName;
					CCARRAY_FOREACH_T(pDataSetFrame->pDataElement->GetChildren(),pKVFrame,SIX_KV*)
					{
						if (!pKVFrame->getKey().compareIgnoreCase("name"))
						{
							frameName.Format(L"%s",Utility::Utf8ToUnicode(pKVFrame->getValue().getCString()).c_str());
						}
						pSpriteInfo->imageFrameName.Add(CString(pKVFrame->getValue().getCString()));
					}

					// get pos
					SIX_XmlDataSet *pDataSetPos = 0;
					HITBOX_MAP *pHBox = new HITBOX_MAP();
					int posCount = 0;
					CCARRAY_FOREACH_T(pDataSetFrame->pNode->GetChildren(),pDataSetPos,SIX_XmlDataSet*)
					{
						unsigned int idx = -1;
						POINT_INFO *pPoint = new POINT_INFO();
						// 此处要做2次检测填充，否则CCArray::objectAtIndex(idx)当idx超过object子节点总数量时会引发CCAssert
						for (int i=0;i<min(pDataSetPos->pDataElement->GetChildrenCount(),MAX_VERTEX_COUNT);i++)
						{
							SIX_KV *pKV = pDataSetPos->pDataElement->Get(i);
							if (pKV)
							{
								if (!pKV->getKey().compareIgnoreCase("idx"))
									idx = atoi(pKV->getValue().getCString());
								else if (!pKV->getKey().compareIgnoreCase("x"))
									pPoint->x = (float)atof(pKV->getValue().getCString());
								else if (!pKV->getKey().compareIgnoreCase("y"))
									pPoint->y = (float)atof(pKV->getValue().getCString());
							}
						}
						pHBox->insert(HITBOX_MAP::value_type((idx==-1)?posCount++:idx,pPoint));
					}

					for (int i=posCount;i<MAX_VERTEX_COUNT;i++)
					{
						POINT_INFO *pPoint = new POINT_INFO(-1.0f,-1.0f);
						pHBox->insert(HITBOX_MAP::value_type(i+1,pPoint));
					}
					pSpriteInfo->frameHBox.insert(FHITBOX_MAP::value_type(Utility::UnicodeToUtf8(frameName.GetString()),pHBox));
				}

				// get sprite
				SIX_KV *pKVSprite = 0;
				CCARRAY_FOREACH_T(pDataSet->pDataElement->GetChildren(),pKVSprite,SIX_KV*)
				{
					if (!CString(pKVSprite->getKey().getCString()).CompareNoCase(L"name"))
					{
						pSpriteInfo->imageName.Append(CString(Utility::Utf8ToUnicode(pKVSprite->getValue().getCString()).c_str()));
					}
					else if (!CString(pKVSprite->getKey().getCString()).CompareNoCase(L"path"))
					{
						pSpriteInfo->imagePath.Append(CString(Utility::Utf8ToUnicode(pKVSprite->getValue().getCString()).c_str()));
					}
				}
			}
		}
	}

	return 0;
}

void CFileView::SaveSpriteInfo2File(CString folderPath,SPRITE_INFO *pSpriteInfo)
{
	if (!pSpriteInfo)
		return;

	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","UTF-8","");
	doc.LinkEndChild(decl);
	TiXmlElement *RootElement = new TiXmlElement("pcc");
	doc.LinkEndChild(RootElement);
	RootElement->SetDoubleAttribute("version",1.0f);

	// 场景
	TiXmlElement *SceneElement = new TiXmlElement("Scene");
	SceneElement->SetAttribute("bg",Utility::UnicodeToUtf8(gBackgroundImg.GetString()));
	RootElement->LinkEndChild(SceneElement);

	// 名称
	TiXmlElement *SpriteElement = new TiXmlElement("Sprite");
	SpriteElement->SetAttribute("name",Utility::UnicodeToUtf8(pSpriteInfo->imageName.GetString()).c_str());
	SpriteElement->SetAttribute("path",Utility::UnicodeToUtf8(pSpriteInfo->imagePath.GetString()).c_str());
	RootElement->LinkEndChild(SpriteElement);

	for (int i=0;i<pSpriteInfo->imageFrameName.GetCount();i++)
	{
		CString fileName = pSpriteInfo->imageFrameName.GetAt(i).GetString();

		// frame name
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Utility::UnicodeToAnsi(fileName.GetString()).c_str());
		if (!pFrame)
		{
			AfxMessageBox(L"精灵帧对象不存在！");
			return;
		}

		TiXmlElement* FramesElement = new TiXmlElement("Frames");
		FramesElement->SetAttribute("name",Utility::UnicodeToUtf8(fileName.GetString()).c_str());
		SpriteElement->LinkEndChild(FramesElement);

		HITBOX_MAP *pHitBox = pFrame->getTexture()->hitBox();

		for (HITBOX_ITER mIter=pHitBox->begin();mIter!=pHitBox->end();mIter++)
		{
			POINT_INFO *pPoint = mIter->second;

			// 只存储设置好的点，能精简就精简，否则导出的文件太大了。。。
			if (pPoint->x>=0.0f && pPoint->y>=0.0f)
			{
				TiXmlElement *PosElement = new TiXmlElement("Pos");
				PosElement->SetAttribute("idx",mIter->first);
				FramesElement->LinkEndChild(PosElement);

				CString value;
				value.Format(L"%.1f",pPoint->x);
				PosElement->SetAttribute("x",Utility::UnicodeToUtf8(value.GetString()).c_str());
				value.Empty();
				value.Format(L"%.1f",pPoint->y);
				PosElement->SetAttribute("y",Utility::UnicodeToUtf8(value.GetString()).c_str());
			}
		}
	}

	CString fullPath;
	SYSTEMTIME st;
	::GetLocalTime(&st);
	fullPath.Format(L"%s\\%s-%02d%02d%02d-%03d.pcc",
		folderPath.GetString(),
		pSpriteInfo->imageName.GetString(),
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds
		);
	doc.SaveFile(Utility::UnicodeToAnsi(fullPath.GetString()).c_str());
	doc.Clear();
}

void CFileView::OnEditCut()
{
}

void CFileView::OnEditCopy()
{
}

void CFileView::OnEditClear()
{
}

void CFileView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

//void CFileView::OnChangeVisualStyle()
//{
//	m_wndToolBar.CleanUpLockedImages();
//	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ????*/);
//
//	m_FileViewImages.DeleteImageList();
//
//	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;
//
//	CBitmap bmp;
//	if (!bmp.LoadBitmap(uiBmpId))
//	{
//		TRACE(_T("???????λ?: %x\n"), uiBmpId);
//		ASSERT(FALSE);
//		return;
//	}
//
//	BITMAP bmpObj;
//	bmp.GetBitmap(&bmpObj);
//
//	UINT nFlags = ILC_MASK;
//
//	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;
//
//	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
//	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));
//
//	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
//}

BOOL CFileView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

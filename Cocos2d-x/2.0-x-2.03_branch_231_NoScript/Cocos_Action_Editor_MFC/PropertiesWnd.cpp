
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Cocos_Action_Editor_MFC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString gBackgroundImg;
extern CString gFrameName;
extern bool gIsFrame;
extern int gHitPoint;

inline void UpdateProperty(CMFCPropertyGridProperty* Property, const char *Value)
{
	const COleVariant& Var = Property->GetValue();

	if (Var.vt != VT_EMPTY && Var.vt != VT_BSTR)
	{
		ASSERT(FALSE);
		return;
	}

	if (Var.pcVal != Value)
		Property->SetValue((_variant_t)Value);
}

inline void UpdateProperty(CMFCPropertyGridProperty* Property, float Value)
{
	const COleVariant& Var = Property->GetValue();

	if (Var.vt != VT_EMPTY && Var.vt != VT_R4)
	{
		ASSERT(FALSE);
		return;
	}

	if ((float)Var.fltVal != Value)
		Property->SetValue((_variant_t)Value);
}

inline void UpdateProperty(CMFCPropertyGridProperty* Property, int Value)
{
	const COleVariant& Var = Property->GetValue();

	if (Var.vt != VT_EMPTY && Var.vt != VT_INT)
	{
		ASSERT(FALSE);
		return;
	}

	if (Var.ulVal != Value)
		Property->SetValue((_variant_t)Value);
}

inline void UpdateProperty(CMFCPropertyGridProperty* Property, bool Value)
{
	const COleVariant& Var = Property->GetValue();

	if (Var.vt != VT_EMPTY && Var.vt != VT_BOOL)
	{
		ASSERT(FALSE);
		return;
	}

	if (Var.boolVal != (VARIANT_BOOL)Value)
		Property->SetValue((_variant_t)Value);
}

BEGIN_MESSAGE_MAP(MyProp, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void MyProp::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMFCPropertyGridCtrl::OnLButtonDown(nFlags,point);

	CMFCPropertyGridProperty::ClickArea clickArea;
	CMFCPropertyGridProperty* pHit = HitTest(point, &clickArea);
	if (!pHit)
		return;

	CString propName(pHit->GetName());

	CString splitStr(L"坐标点P-");
	int nPos = propName.Find(splitStr);
	if (nPos!=0)
		return;
	
	gHitPoint = atoi(Utility::UnicodeToUtf8(propName.Right(propName.GetLength() - splitStr.GetLength()).GetString()).c_str());
}

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	//ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	//ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	//ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	//ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_CBN_SELCHANGE(1,OnDropdown)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CPropertiesWnd::OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndScenePropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndSpritePropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

	m_wndObjectCombo.AddString(_T("场景设置"));
	m_wndObjectCombo.AddString(_T("精灵设置"));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndScenePropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitScenePropList();

	if (!m_wndSpritePropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 3))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitSpritePropList();

	SetPropListFont();

	m_wndScenePropList.ShowWindow(TRUE);
	m_wndSpritePropList.ShowWindow(FALSE);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	if (m_wndScenePropList.IsWindowVisible())
	{
		m_wndScenePropList.ExpandAll();
	}
	else if (m_wndSpritePropList.IsWindowVisible())
	{
		m_wndSpritePropList.ExpandAll();
	}
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	if (m_wndScenePropList.IsWindowVisible())
		m_wndScenePropList.SetAlphabeticMode(!m_wndScenePropList.IsAlphabeticMode());
	else if (m_wndSpritePropList.IsWindowVisible())
		m_wndSpritePropList.SetAlphabeticMode(!m_wndSpritePropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	if (m_wndScenePropList.IsWindowVisible())
		pCmdUI->SetCheck(m_wndScenePropList.IsAlphabeticMode());
	else if (m_wndSpritePropList.IsWindowVisible())
		pCmdUI->SetCheck(m_wndSpritePropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

// Add by Cool.Cat
void CPropertiesWnd::InitScenePropList()
{
	m_wndScenePropList.EnableHeaderCtrl(FALSE);
	m_wndScenePropList.EnableDescriptionArea();
	m_wndScenePropList.SetVSDotNetLook();
	m_wndScenePropList.MarkModifiedProperties();

	// 属性
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("属性"));
	pGroup1->Expand();

	// 背景
	CMFCPropertyGridFileProperty *pProp = new CMFCPropertyGridFileProperty(
		_T("背景"),
		TRUE,
		_T("C:\\"),
		_T("PNG"),
		0,
		_T("PNG(*.PNG)|*.PNG|JPG(*.JPG)|*.JPG|BMP(*.BMP)|*.BMP||"),
		_T("选择图片")
		);
	pProp->AllowEdit(0);
	pGroup1->AddSubItem(pProp);

	m_wndScenePropList.AddProperty(pGroup1);
}

void CPropertiesWnd::InitSpritePropList()
{
	m_wndSpritePropList.EnableHeaderCtrl(FALSE);
	m_wndSpritePropList.EnableDescriptionArea();
	m_wndSpritePropList.SetVSDotNetLook();
	m_wndSpritePropList.MarkModifiedProperties();

	//// 静态设置float/double精度有BUG，GetValue()取值浮点为0.0f
	//CMFCPropertyGridProperty::m_strFormatFloat = _T("%0.2f");
	//CMFCPropertyGridProperty::m_strFormatDouble = _T("%0.2f");

	// 属性
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("属性"));
	pGroup1->Expand();

	// 名称
	CMFCPropertyGridProperty *pProp = new CMFCPropertyGridProperty(_T("名称"), _T("精灵"));
	pProp->Enable(FALSE);
	pGroup1->AddSubItem(pProp);

	// 边框
	pProp = new CMFCPropertyGridProperty(_T("边框重绘"), _T("否"), _T("设置对象是否具重绘边框"));
	pProp->AddOption(_T("否"));
	pProp->AddOption(_T("是"));
	pProp->AllowEdit(0);
	pGroup1->AddSubItem(pProp);

	// 旋转
	CMFCPropertyGridProperty* pRotate = new CMFCPropertyGridProperty(_T("旋转"),(_variant_t)0.0f,_T("设置对象旋转角度"));
	UpdateProperty(pRotate,90.0f);
	pGroup1->AddSubItem(pRotate);

	// 拉伸
	CMFCPropertyGridProperty* pScale = new CMFCPropertyGridProperty(_T("拉伸"), (_variant_t)0.0f, _T("设置对象拉伸比率"));
	pScale->SetValue((_variant_t)0.0f);
	pGroup1->AddSubItem(pScale);

	// 倾斜
	CMFCPropertyGridProperty* pSkew = new CMFCPropertyGridProperty(_T("倾斜"), (_variant_t)0.0f, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("沿X轴倾斜"), (_variant_t) 0.0f, _T("设置对象X轴倾斜角度"));
	pSkew->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("沿Y轴倾斜"), (_variant_t) 0.0f, _T("设置对象Y轴倾斜角度"));
	pSkew->AddSubItem(pProp);
	pSkew->Expand();
	pGroup1->AddSubItem(pSkew);

	// 翻转
	CMFCPropertyGridProperty *pFlipX = new CMFCPropertyGridProperty(_T("沿X轴翻转"), _T("否"), _T("设置对象X轴翻转"));
	pFlipX->AddOption(_T("否"));
	pFlipX->AddOption(_T("是"));
	pFlipX->AllowEdit(0);
	pGroup1->AddSubItem(pFlipX);

	CMFCPropertyGridProperty *pFlipY = new CMFCPropertyGridProperty(_T("沿Y轴翻转"), _T("否"), _T("设置对象Y轴翻转"));
	pFlipY->AddOption(_T("否"));
	pFlipY->AddOption(_T("是"));
	pFlipY->AllowEdit(0);
	pGroup1->AddSubItem(pFlipY);

	// 描点
	CMFCPropertyGridProperty* pAnchorPoint = new CMFCPropertyGridProperty(_T("描点"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("描点X"), (_variant_t) 0.5f, _T("设置对象描点X坐标"));
	pAnchorPoint->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("描点Y"), (_variant_t) 0.5f, _T("设置对象描点Y坐标"));
	pAnchorPoint->AddSubItem(pProp);
	pAnchorPoint->Expand();
	pGroup1->AddSubItem(pAnchorPoint);

	// 大小
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("大小"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("高度"), (_variant_t) 0.0f, _T("指定对象的高度"));
	pSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("宽度"), (_variant_t) 0.0f, _T("指定对象的宽度"));
	pSize->AddSubItem(pProp);
	pSize->Expand();
	pGroup1->AddSubItem(pSize);

	// 坐标
	CMFCPropertyGridProperty* pPos = new CMFCPropertyGridProperty(_T("坐标"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("坐标X"), (_variant_t) 0.0f, _T("指定对象的X坐标"));
	pPos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("坐标Y"), (_variant_t) 0.0f, _T("指定对象的Y坐标"));
	pPos->AddSubItem(pProp);
	pPos->Expand();
	pGroup1->AddSubItem(pPos);

	// 延迟
	CMFCPropertyGridProperty* pFrameDelay = new CMFCPropertyGridProperty(_T("延迟"),(_variant_t)0.0f,_T("设置对象动作帧延迟间隔，单位为秒"));
	UpdateProperty(pFrameDelay,0.1f);
	pGroup1->AddSubItem(pFrameDelay);

	// bbox
	CMFCPropertyGridProperty *pBBoxDraw = new CMFCPropertyGridProperty(_T("BBox重绘"), _T("否"), _T("设置对象是否重绘BoundingBox"));
	pBBoxDraw->AddOption(_T("否"));
	pBBoxDraw->AddOption(_T("是"));
	pBBoxDraw->AllowEdit(0);
	pGroup1->AddSubItem(pBBoxDraw);

	// hbox
	CMFCPropertyGridProperty *pHBoxDraw = new CMFCPropertyGridProperty(_T("HBox重绘"), _T("否"), _T("设置对象是否重绘HitBox"));
	pHBoxDraw->AddOption(_T("否"));
	pHBoxDraw->AddOption(_T("是"));
	pHBoxDraw->AllowEdit(0);
	pGroup1->AddSubItem(pHBoxDraw);

	// hbox属性
	CMFCPropertyGridProperty *pHBoxSet = new CMFCPropertyGridProperty(_T("HBox属性"), 0 , TRUE);
	for (int i=0;i<MAX_VERTEX_COUNT;i++)
	{
		CString pointName;
		pointName.Format(L"坐标点P-%02d",i+1);
		CMFCPropertyGridProperty *pPoint = new CMFCPropertyGridProperty(pointName, _T(""), _T(""));
		pPoint->SetData((DWORD_PTR)(i+1));
		pHBoxSet->AddSubItem(pPoint);
	}
	pHBoxSet->Show(0);
	pHBoxSet->AllowEdit(0);
	pGroup1->AddSubItem(pHBoxSet);

	// 直线游动
	CMFCPropertyGridProperty *pRunAcion = new CMFCPropertyGridProperty(_T("直线游动"), _T("否"), _T("设置对象是否沿着直线循环游动"));
	pRunAcion->AddOption(_T("否"));
	pRunAcion->AddOption(_T("是"));
	pRunAcion->AllowEdit(0);
	pGroup1->AddSubItem(pRunAcion);

	// 颜色
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("颜色"), RGB(210, 192, 254), NULL, _T("指定对象的颜色"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGroup1->AddSubItem(pColorProp);

	m_wndSpritePropList.AddProperty(pGroup1);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	if (m_wndScenePropList.IsWindowVisible())
		m_wndScenePropList.SetFocus();
	else if (m_wndSpritePropList.IsWindowVisible())
		m_wndSpritePropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	if (m_wndScenePropList.IsWindowVisible())
		m_wndScenePropList.SetFont(&m_fntPropList);
	if (m_wndSpritePropList.IsWindowVisible())
		m_wndSpritePropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::OnDropdown()
 {
	switchComonBox();
 }

void CPropertiesWnd::switchComonBox()
{
	int nSel = m_wndObjectCombo.GetCurSel();
	switch (nSel)
	{
		// 场景设置
	case 0:
		{
			m_wndScenePropList.ShowWindow(TRUE);
			m_wndSpritePropList.ShowWindow(FALSE);
			break;
		}
		// 对象设置
	case 1:
		{
			m_wndScenePropList.ShowWindow(FALSE);
			m_wndSpritePropList.ShowWindow(TRUE);
			break;
		}
	}
}

LRESULT CPropertiesWnd::OnScenePropertyChanged(CMFCPropertyGridProperty *pProp)
{
	if (!pProp)
		return 0;

	CString propName;
	propName.Append(pProp->GetName());
	CString propValue(pProp->GetValue());

	if (!propName.CompareNoCase(L"背景"))
	{
		gBackgroundImg.Empty();
		gBackgroundImg.Append(propValue.GetString());
		UpdateSceneBg(propValue);
	}
	return 1;
}

void CPropertiesWnd::UpdateSceneBg(CString &sceneBgImg)
{
	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}

	CCSprite *pBackground = dynamic_cast<CCSprite*>(pScene->getChildByTag(0));
	if (!pBackground)
	{
		pBackground = CCSprite::create(Utility::UnicodeToAnsi(sceneBgImg.GetString()).c_str());
		if (!pBackground)
		{
			AfxMessageBox(L"创建背景精灵失败！");
			return;
		}
		pScene->addChild(pBackground,-1,0);
	}
	else
	{
		CCTexture2D *tex2D = CCTextureCache::sharedTextureCache()->addImage(Utility::UnicodeToAnsi(sceneBgImg.GetString()).c_str());
		if (!tex2D)
		{
			AfxMessageBox(L"加载背景纹理失败！");
			return;
		}
		pBackground->setTexture(tex2D);
		CCSize newSize = tex2D->getContentSizeInPixels();
		pBackground->setTextureRect(CCRect(0,0,newSize.width,newSize.height));
		//pBackground->setContentSize(newSize);
	}

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	pBackground->setAnchorPoint(ccp(0,0));
	pBackground->setPosition(ccp((frameSize.width-pBackground->getContentSize().width)/2,(frameSize.height-pBackground->getContentSize().height)/2));
}

LRESULT CPropertiesWnd::OnSpritePropertyChanged(CMFCPropertyGridProperty *pProp)
{
	if (!pProp)
		return 0;

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return 0;
	}

	//通过lParam可以得到你修改的项
	CMFCPropertyGridProperty *pPropName = m_wndSpritePropList.GetProperty(0)->GetSubItem(0);
	CString propName(pPropName->GetValue());
	if (!propName.CompareNoCase(L"精灵"))
	{
		AfxMessageBox(L"请先选择一个精灵对象！");
		return 0;
	}

	//int pos = propName.ReverseFind('-');
	//if (!pos)
	//{
	//	AfxMessageBox(L"对象ID格式错误！");
	//	return 0;
	//}

	//CString idxStr;
	//idxStr.Format(L"%s",propName.Right(propName.GetLength() - pos - 1));

	//unsigned int idx = atoi(Utility::UnicodeToUtf8(idxStr.GetString()).c_str());

	unsigned int idx = pPropName->GetData();

	CCSprite *pSpr = dynamic_cast<CCSprite*>(pScene->getChildByTag(idx));
	if (!pSpr)
	{
		AfxMessageBox(L"对象对象不存在！");
		return 0;
	}

	propName.Empty();
	propName.Append(pProp->GetName());
	CString propValue(pProp->GetValue());

	if (!propName.CompareNoCase(L"边框重绘"))
	{
		if (!propValue.CompareNoCase(L"是"))
			pSpr->setRectDirty(true);
		else
			pSpr->setRectDirty(false);
	}
	else if (!propName.CompareNoCase(L"旋转"))
	{
		pSpr->setRotation(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"拉伸"))
	{
		pSpr->setScale(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"倾斜"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		pSpr->setSkewX(atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()));

		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setSkewY(atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"沿X轴倾斜"))
	{
		pSpr->setSkewX(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));   
	}
	else if (!propName.CompareNoCase(L"沿Y轴倾斜"))
	{
		pSpr->setSkewY(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"沿X轴翻转"))
	{
		if (!propValue.CompareNoCase(L"是"))
			pSpr->setFlipX(true);
		else
			pSpr->setFlipX(false);
	}
	else if (!propName.CompareNoCase(L"沿Y轴翻转"))
	{
		if (!propValue.CompareNoCase(L"是"))
			pSpr->setFlipY(true);
		else
			pSpr->setFlipY(false);   
	}
	else if (!propName.CompareNoCase(L"描点"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setAnchorPoint(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"描点X"))
	{
		CString valueX(pProp->GetValue());
		CMFCPropertyGridProperty *pPropY = m_wndSpritePropList.GetProperty(0)->GetSubItem(7)->GetSubItem(1);
		CString valueY(pPropY->GetValue());
		pSpr->setAnchorPoint(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"描点Y"))
	{
		CMFCPropertyGridProperty *pPropX = m_wndSpritePropList.GetProperty(0)->GetSubItem(7)->GetSubItem(0);
		CString valueX(pPropX->GetValue());
		CString valueY(pProp->GetValue());
		pSpr->setAnchorPoint(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"大小"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setContentSize(CCSize(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"高度"))
	{
		CString valueX(pProp->GetValue());
		CMFCPropertyGridProperty *pPropY = m_wndSpritePropList.GetProperty(0)->GetSubItem(8)->GetSubItem(1);
		CString valueY(pPropY->GetValue());
		pSpr->setContentSize(CCSize(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"宽度"))
	{
		CMFCPropertyGridProperty *pPropX = m_wndSpritePropList.GetProperty(0)->GetSubItem(8)->GetSubItem(0);
		CString valueX(pPropX->GetValue());
		CString valueY(pProp->GetValue());
		pSpr->setContentSize(CCSize(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"坐标"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setPosition(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);   
	}
	else if (!propName.CompareNoCase(L"坐标X"))
	{
		pSpr->setPositionX(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"坐标Y"))
	{
		pSpr->setPositionY(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"延迟"))
	{
		// 先找到动作
		CCRepeatForever *pRepeat = dynamic_cast<CCRepeatForever*>(pSpr->getActionByTag(0));
		if (!pRepeat)
		{
			AfxMessageBox(L"动作不存在！");
			return 0;
		}
		CCAnimate *pAnimate = dynamic_cast<CCAnimate*>(pRepeat->getInnerAction());
		if (!pAnimate)
		{
			AfxMessageBox(L"动画不存在！");
			return 0;
		}
		CCAnimation *pAnimation = pAnimate->getAnimation();
		if (!pAnimation)
		{
			AfxMessageBox(L"动画帧不存在！");
			return 0;
		}
		// 取动作帧数组
		CCArray *pArray = CCArray::arrayWithArray(pAnimation->getFrames());
		// 然后停止动作
		pSpr->stopActionByTag(0);
		// 再重新创建动作
		//pAnimation = CCAnimation::createWithSpriteFrames( pArray, atof(CFileView::UnicodeToUtf8(propValue.GetString()).c_str()) );
		pAnimation = CCAnimation::animationWithAnimationFrames(pArray,atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()),-1);
		pAnimate = CCAnimate::actionWithAnimation( pAnimation );
		pRepeat = CCRepeatForever::actionWithAction( pAnimate );
		pRepeat->setTag(0);
		pSpr->runAction(pRepeat);
	}
	else if (!propName.CompareNoCase(L"BBox重绘"))
	{
		if (!propValue.CompareNoCase(L"是"))
			pSpr->setBBoxDirty(true);
		else
			pSpr->setBBoxDirty(false);
	}
	else if (!propName.CompareNoCase(L"HBox重绘"))
	{
		if (!propValue.CompareNoCase(L"是"))
			pSpr->setHBoxDirty(true);
		else
			pSpr->setHBoxDirty(false);
	}
	else if (!propName.CompareNoCase(L"直线游动"))
	{
		SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSpr->getUserData());

		if (!propValue.CompareNoCase(L"是"))
		{
			runActionFinished(pSpr);
		}
		else
		{
			pSpr->stopActionByTag(1);
			pSpriteInfo->runAction = false;
		}
	}
	else
	{
		// HBox数据
		CString splitStr(L"坐标点P-");
		int nPos = propName.Find(splitStr);
		if (nPos>=0)
		{
			float x = -1.0f;
			float y = -1.0f;
			int pos = propValue.Find('/');
			if (pos<0)
			{
				//AfxMessageBox(L"坐标点格式错误，应为：x/y");
				CString value;
				value.Format(L"%f/%f",x,y);
				UpdateProperty(pProp,Utility::UnicodeToUtf8(value.GetString()).c_str());
			}
			else
			{
				x = atof(Utility::UnicodeToUtf8(propValue.Left(pos)).c_str());
				y = atof(Utility::UnicodeToUtf8(propValue.Right(propValue.GetLength()-pos-1)).c_str());
			}

			int pIdx = pProp->GetData();

			SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSpr->getUserData());
			if (pSpriteInfo)
			{
				CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Utility::UnicodeToAnsi(gFrameName.GetString()).c_str());
				if (pFrame)
				{
					// 填充当前帧的HBox数据
					int count = pFrame->getTexture()->vertexCount;
					if (count>MAX_VERTEX_COUNT)
					{
						AfxMessageBox(L"当前帧HBox数量溢出！");
					}
					else
					{
						HITBOX_ITER mIter=pFrame->getTexture()->hitBox()->find(pIdx);
						if (mIter!=pFrame->getTexture()->hitBox()->end())
						{
							POINT_INFO *pPoint = mIter->second;
							if (pPoint)
							{
								pPoint->x = x;
								pPoint->y = y;
							}
						}
						else
						{
							POINT_INFO *pPoint = new POINT_INFO(x,y);
							pFrame->getTexture()->hitBox()->insert(HITBOX_MAP::value_type(pIdx,pPoint));
						}
						// refresh hitbox
						pFrame->getTexture()->flushHitBox();
					}
					return 1;
				}
			}
		}
		else
		{
			AfxMessageBox(L"暂未实现");
			return 0;
		}
	}
	return 0;
}

void CPropertiesWnd::runActionFinished(CCNode *pSpr)
{
	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}

	SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSpr->getUserData());
	if (!pSpriteInfo)
		return;

	// 先找到动作
	CCFiniteTimeAction *pSeq = dynamic_cast<CCFiniteTimeAction*>(pSpr->getActionByTag(1));
	if (!pSeq)
	{
		// 取精灵当前绝对坐标
		pSpriteInfo->runActionBeforePoint = pSpr->getPosition();

		float offset_x = pSpr->getPositionX();
		float offset_y = pSpr->getPositionY();
		float mid_x = pScene->getContentSize().width/2;
		float mid_y = pScene->getContentSize().height/2;
		if (offset_x<mid_x)
			offset_x = mid_x * 2;
		else
			offset_x = 0.0f;
		CCMoveTo *pMove = CCMoveTo::create(5.0,ccp(offset_x,offset_y));
		CCCallFuncN *callfunc = CCCallFuncN::create(pSpr,callfuncN_selector(CPropertiesWnd::runActionFinished));
		pSeq = CCSequence::create(pMove,callfunc,0);
		pSeq->setTag(1);
		pSpr->runAction(pSeq);
		pSpriteInfo->runAction = true;
	}
	else
	{
		pSpr->stopAction(pSeq);
		pSpr->setPosition(pSpriteInfo->runActionBeforePoint);
		runActionFinished(pSpr);
	}
}

LRESULT CPropertiesWnd::OnPropertyChanged (WPARAM wParam,LPARAM lParam)
{
	int selIdx = (int)wParam;
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lParam;
	if (selIdx==2)
		return OnScenePropertyChanged(pProp);
	else if (selIdx==3)
		return OnSpritePropertyChanged(pProp);
   return 0;
 }

void CPropertiesWnd::OnSelectSprite(CCSprite *pSprite)
{
	gHitPoint = -1;

	// 先切换到对象面板
	m_wndObjectCombo.SetCurSel(1);

	switchComonBox();

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}

	if (!m_wndSpritePropList.GetPropertyCount())
	{
		AfxMessageBox(L"属性面板无内容");
		return;
	}

	// 刷新面板数据
	CMFCPropertyGridProperty *pProp = m_wndSpritePropList.GetProperty(0);
	if (!pProp->GetSubItemsCount())
	{
		AfxMessageBox(L"属性面板无内容");
		return;
	}

	// 名称
	CMFCPropertyGridProperty *pSubItem = pProp->GetSubItem(0);
	UpdateProperty(pSubItem,pSprite->getObjName());
	SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSprite->getUserData());
	pSubItem->SetData((DWORD_PTR)pSpriteInfo->idx);

	// 边框
	pSubItem = pProp->GetSubItem(1);
	if (pSprite->getRectDirty())
		UpdateProperty(pSubItem,"是");
	else
		UpdateProperty(pSubItem,"否");

	// 旋转
	pSubItem = pProp->GetSubItem(2);
	UpdateProperty(pSubItem,pSprite->getRotation());

	// 拉伸
	pSubItem = pProp->GetSubItem(3);
	UpdateProperty(pSubItem,pSprite->getScale());

	// 倾斜
	pSubItem = pProp->GetSubItem(4);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getSkewX());
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getSkewY());

	// 翻转
	pSubItem = pProp->GetSubItem(5);
	if (pSprite->isFlipX())
		UpdateProperty(pSubItem,"是");
	else
		UpdateProperty(pSubItem,"否");

	pSubItem = pProp->GetSubItem(6);
	if (pSprite->isFlipY())
		UpdateProperty(pSubItem,"是");
	else
		UpdateProperty(pSubItem,"否");

	// 描点
	pSubItem = pProp->GetSubItem(7);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getAnchorPoint().x);
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getAnchorPoint().y);

	// 大小
	pSubItem = pProp->GetSubItem(8);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getContentSize().width);
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getContentSize().height);

	// 坐标
	pSubItem = pProp->GetSubItem(9);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getPositionX());
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getPositionY());

	// 延迟
	// 先找到动作
	CCRepeatForever *pRepeat = dynamic_cast<CCRepeatForever*>(pSprite->getActionByTag(0));
	if (!pRepeat)
	{
		AfxMessageBox(L"动作不存在！");
		return;
	}
	CCAnimate *pAnimate = dynamic_cast<CCAnimate*>(pRepeat->getInnerAction());
	if (!pAnimate)
	{
		AfxMessageBox(L"动画不存在！");
		return;
	}
	CCAnimation *pAnimation = pAnimate->getAnimation();
	if (!pAnimation)
	{
		AfxMessageBox(L"动画帧不存在！");
		return;
	}
	float delay = pAnimation->getDelayPerUnit();
	pSubItem = pProp->GetSubItem(10);
	UpdateProperty(pSubItem,delay);

	// BBox
	pSubItem = pProp->GetSubItem(11);
	if (pSprite->getBBoxDirty())
		UpdateProperty(pSubItem,"是");
	else
		UpdateProperty(pSubItem,"否");

	// HBox
	pSubItem = pProp->GetSubItem(12);
	if (pSprite->getHBoxDirty())
		UpdateProperty(pSubItem,"是");
	else
		UpdateProperty(pSubItem,"否");

	CCLabelTTF *pTTF = dynamic_cast<CCLabelTTF*>(pScene->getChildByTag(100));
	if (pTTF)
	{
		pTTF->setString(Utility::UnicodeToUtf8(L"点击左侧精灵下面的对象帧，可编辑对象帧的HBox数据点\n精灵可拖拽，对象帧不可拖拽").c_str());
		pTTF->setColor(ccc3(255,0,0));
	}

	CCLabelTTF *pTTFPos = dynamic_cast<CCLabelTTF*>(pScene->getChildByTag(99));
	if (pTTFPos)
	{
		pTTFPos->setVisible(false);
	}

	// HBox属性
	// 可以根据frameName从帧缓存中查找
	// 也可以根据frameName从hitBox中查找
	if (gFrameName.GetLength())
	{
		// 先填充导入的HBox坐标数据
		//SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSprite->getUserData());
		if (pSpriteInfo)
		{
			CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Utility::UnicodeToAnsi(gFrameName.GetString()).c_str());
			if (pFrame)
			{
				gIsFrame = true;

				if (pTTF)
				{
					pTTF->setString(Utility::UnicodeToUtf8(L"当前帧可编辑HBox数据点：\n在右侧[HBox属性]里设置数据\n鼠标位于选定的精灵范围内，坐标提示为红色；否则为白色").c_str());
					pTTF->setColor(ccc3(0,255,0));
				}

				if (pTTFPos)
				{
					pTTFPos->setVisible(true);
				}

				// 暂停动作先~
				pSprite->pauseSchedulerAndActions();

				// 切换到当前帧
				pSprite->setDisplayFrame(pFrame);

				// 显示HBox属性控件
				pSubItem = pProp->GetSubItem(13);
				pSubItem->Show(1);

				// 填充当前帧的HBox数据
				int count = pFrame->getTexture()->vertexCount;
				if (count>MAX_VERTEX_COUNT)
				{
					AfxMessageBox(L"当前帧HBox数量溢出！");
				}
				else
				{
					// 实时数据填充
					int i=0;
					HITBOX_ITER mIter=pFrame->getTexture()->hitBox()->begin();
					for (;mIter!=pFrame->getTexture()->hitBox()->end();mIter++)
					{
						CMFCPropertyGridProperty *pItem = pSubItem->GetSubItem(i);
						POINT_INFO *pt = (POINT_INFO*)(mIter->second);
						CString value;
						value.Format(L"%0.2f/%0.2f",pt->x,pt->y);
						UpdateProperty(pItem,Utility::UnicodeToUtf8(value.GetString()).c_str());
						i++;
					}
				}
			}
			else
			{
				// 恢复吧~
				pSprite->resumeSchedulerAndActions();

				// 隐藏HBox属性控件
				pSubItem = pProp->GetSubItem(13);
				pSubItem->Show(0);
			}
		}
	}

	// 直线游动
	pSubItem = pProp->GetSubItem(14);
	if (pSpriteInfo->runAction)
		UpdateProperty(pSubItem,"是");
	else
		UpdateProperty(pSubItem,"否");
}

void CPropertiesWnd::OnUpdateSpriteFramePos(CCSprite *pSprite,POINT_INFO *pPoint)
{
	// 先切换到对象面板
	m_wndObjectCombo.SetCurSel(1);

	switchComonBox();

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}

	if (!m_wndSpritePropList.GetPropertyCount())
	{
		AfxMessageBox(L"属性面板无内容");
		return;
	}

	// 刷新面板数据
	CMFCPropertyGridProperty *pProp = m_wndSpritePropList.GetProperty(0);
	if (!pProp->GetSubItemsCount())
	{
		AfxMessageBox(L"属性面板无内容");
		return;
	}

	// HBox属性
	// 可以根据frameName从帧缓存中查找
	// 也可以根据frameName从hitBox中查找
	if (gFrameName.GetLength())
	{
		// 先填充导入的HBox坐标数据
		CMFCPropertyGridProperty *pSubItem = pProp->GetSubItem(13);
		CMFCPropertyGridProperty *pItem = pSubItem->GetSubItem(gHitPoint-1);
		CString value;
		value.Format(L"%0.2f/%0.2f",pPoint->x,pPoint->y);
		UpdateProperty(pItem,Utility::UnicodeToUtf8(value.GetString()).c_str());
	}
}

void CPropertiesWnd::OnUpdateSceneBg()
{
	// 先切换到对象面板
	m_wndObjectCombo.SetCurSel(0);

	switchComonBox();

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"场景不存在！");
		return;
	}

	if (!m_wndScenePropList.GetPropertyCount())
	{
		AfxMessageBox(L"属性面板无内容");
		return;
	}

	// 刷新面板数据
	CMFCPropertyGridProperty *pRoot = m_wndScenePropList.GetProperty(0);
	if (!pRoot->GetSubItemsCount())
	{
		AfxMessageBox(L"属性面板无内容");
		return;
	}

	CMFCPropertyGridFileProperty *pProp = (CMFCPropertyGridFileProperty*)pRoot->GetSubItem(0);

	pProp->AllowEdit(1);
	UpdateProperty(pProp,Utility::UnicodeToUtf8(gBackgroundImg.GetString()).c_str());
	pProp->AllowEdit(0);

	UpdateSceneBg(gBackgroundImg);
}
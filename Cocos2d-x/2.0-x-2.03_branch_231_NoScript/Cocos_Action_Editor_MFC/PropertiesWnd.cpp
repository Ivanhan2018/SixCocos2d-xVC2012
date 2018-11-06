
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

	CString splitStr(L"�����P-");
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
// CResourceViewBar ��Ϣ�������

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

	// �������:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ���������� \n");
		return -1;      // δ�ܴ���
	}

	m_wndObjectCombo.AddString(_T("��������"));
	m_wndObjectCombo.AddString(_T("��������"));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndScenePropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	InitScenePropList();

	if (!m_wndSpritePropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 3))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	InitSpritePropList();

	SetPropListFont();

	m_wndScenePropList.ShowWindow(TRUE);
	m_wndSpritePropList.ShowWindow(FALSE);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ������*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ����*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
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
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

// Add by Cool.Cat
void CPropertiesWnd::InitScenePropList()
{
	m_wndScenePropList.EnableHeaderCtrl(FALSE);
	m_wndScenePropList.EnableDescriptionArea();
	m_wndScenePropList.SetVSDotNetLook();
	m_wndScenePropList.MarkModifiedProperties();

	// ����
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("����"));
	pGroup1->Expand();

	// ����
	CMFCPropertyGridFileProperty *pProp = new CMFCPropertyGridFileProperty(
		_T("����"),
		TRUE,
		_T("C:\\"),
		_T("PNG"),
		0,
		_T("PNG(*.PNG)|*.PNG|JPG(*.JPG)|*.JPG|BMP(*.BMP)|*.BMP||"),
		_T("ѡ��ͼƬ")
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

	//// ��̬����float/double������BUG��GetValue()ȡֵ����Ϊ0.0f
	//CMFCPropertyGridProperty::m_strFormatFloat = _T("%0.2f");
	//CMFCPropertyGridProperty::m_strFormatDouble = _T("%0.2f");

	// ����
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("����"));
	pGroup1->Expand();

	// ����
	CMFCPropertyGridProperty *pProp = new CMFCPropertyGridProperty(_T("����"), _T("����"));
	pProp->Enable(FALSE);
	pGroup1->AddSubItem(pProp);

	// �߿�
	pProp = new CMFCPropertyGridProperty(_T("�߿��ػ�"), _T("��"), _T("���ö����Ƿ���ػ�߿�"));
	pProp->AddOption(_T("��"));
	pProp->AddOption(_T("��"));
	pProp->AllowEdit(0);
	pGroup1->AddSubItem(pProp);

	// ��ת
	CMFCPropertyGridProperty* pRotate = new CMFCPropertyGridProperty(_T("��ת"),(_variant_t)0.0f,_T("���ö�����ת�Ƕ�"));
	UpdateProperty(pRotate,90.0f);
	pGroup1->AddSubItem(pRotate);

	// ����
	CMFCPropertyGridProperty* pScale = new CMFCPropertyGridProperty(_T("����"), (_variant_t)0.0f, _T("���ö����������"));
	pScale->SetValue((_variant_t)0.0f);
	pGroup1->AddSubItem(pScale);

	// ��б
	CMFCPropertyGridProperty* pSkew = new CMFCPropertyGridProperty(_T("��б"), (_variant_t)0.0f, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("��X����б"), (_variant_t) 0.0f, _T("���ö���X����б�Ƕ�"));
	pSkew->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("��Y����б"), (_variant_t) 0.0f, _T("���ö���Y����б�Ƕ�"));
	pSkew->AddSubItem(pProp);
	pSkew->Expand();
	pGroup1->AddSubItem(pSkew);

	// ��ת
	CMFCPropertyGridProperty *pFlipX = new CMFCPropertyGridProperty(_T("��X�ᷭת"), _T("��"), _T("���ö���X�ᷭת"));
	pFlipX->AddOption(_T("��"));
	pFlipX->AddOption(_T("��"));
	pFlipX->AllowEdit(0);
	pGroup1->AddSubItem(pFlipX);

	CMFCPropertyGridProperty *pFlipY = new CMFCPropertyGridProperty(_T("��Y�ᷭת"), _T("��"), _T("���ö���Y�ᷭת"));
	pFlipY->AddOption(_T("��"));
	pFlipY->AddOption(_T("��"));
	pFlipY->AllowEdit(0);
	pGroup1->AddSubItem(pFlipY);

	// ���
	CMFCPropertyGridProperty* pAnchorPoint = new CMFCPropertyGridProperty(_T("���"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("���X"), (_variant_t) 0.5f, _T("���ö������X����"));
	pAnchorPoint->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("���Y"), (_variant_t) 0.5f, _T("���ö������Y����"));
	pAnchorPoint->AddSubItem(pProp);
	pAnchorPoint->Expand();
	pGroup1->AddSubItem(pAnchorPoint);

	// ��С
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("��С"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 0.0f, _T("ָ������ĸ߶�"));
	pSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("���"), (_variant_t) 0.0f, _T("ָ������Ŀ��"));
	pSize->AddSubItem(pProp);
	pSize->Expand();
	pGroup1->AddSubItem(pSize);

	// ����
	CMFCPropertyGridProperty* pPos = new CMFCPropertyGridProperty(_T("����"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("����X"), (_variant_t) 0.0f, _T("ָ�������X����"));
	pPos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("����Y"), (_variant_t) 0.0f, _T("ָ�������Y����"));
	pPos->AddSubItem(pProp);
	pPos->Expand();
	pGroup1->AddSubItem(pPos);

	// �ӳ�
	CMFCPropertyGridProperty* pFrameDelay = new CMFCPropertyGridProperty(_T("�ӳ�"),(_variant_t)0.0f,_T("���ö�����֡�ӳټ������λΪ��"));
	UpdateProperty(pFrameDelay,0.1f);
	pGroup1->AddSubItem(pFrameDelay);

	// bbox
	CMFCPropertyGridProperty *pBBoxDraw = new CMFCPropertyGridProperty(_T("BBox�ػ�"), _T("��"), _T("���ö����Ƿ��ػ�BoundingBox"));
	pBBoxDraw->AddOption(_T("��"));
	pBBoxDraw->AddOption(_T("��"));
	pBBoxDraw->AllowEdit(0);
	pGroup1->AddSubItem(pBBoxDraw);

	// hbox
	CMFCPropertyGridProperty *pHBoxDraw = new CMFCPropertyGridProperty(_T("HBox�ػ�"), _T("��"), _T("���ö����Ƿ��ػ�HitBox"));
	pHBoxDraw->AddOption(_T("��"));
	pHBoxDraw->AddOption(_T("��"));
	pHBoxDraw->AllowEdit(0);
	pGroup1->AddSubItem(pHBoxDraw);

	// hbox����
	CMFCPropertyGridProperty *pHBoxSet = new CMFCPropertyGridProperty(_T("HBox����"), 0 , TRUE);
	for (int i=0;i<MAX_VERTEX_COUNT;i++)
	{
		CString pointName;
		pointName.Format(L"�����P-%02d",i+1);
		CMFCPropertyGridProperty *pPoint = new CMFCPropertyGridProperty(pointName, _T(""), _T(""));
		pPoint->SetData((DWORD_PTR)(i+1));
		pHBoxSet->AddSubItem(pPoint);
	}
	pHBoxSet->Show(0);
	pHBoxSet->AllowEdit(0);
	pGroup1->AddSubItem(pHBoxSet);

	// ֱ���ζ�
	CMFCPropertyGridProperty *pRunAcion = new CMFCPropertyGridProperty(_T("ֱ���ζ�"), _T("��"), _T("���ö����Ƿ�����ֱ��ѭ���ζ�"));
	pRunAcion->AddOption(_T("��"));
	pRunAcion->AddOption(_T("��"));
	pRunAcion->AllowEdit(0);
	pGroup1->AddSubItem(pRunAcion);

	// ��ɫ
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("��ɫ"), RGB(210, 192, 254), NULL, _T("ָ���������ɫ"));
	pColorProp->EnableOtherButton(_T("����..."));
	pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
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
		// ��������
	case 0:
		{
			m_wndScenePropList.ShowWindow(TRUE);
			m_wndSpritePropList.ShowWindow(FALSE);
			break;
		}
		// ��������
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

	if (!propName.CompareNoCase(L"����"))
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
		AfxMessageBox(L"���������ڣ�");
		return;
	}

	CCSprite *pBackground = dynamic_cast<CCSprite*>(pScene->getChildByTag(0));
	if (!pBackground)
	{
		pBackground = CCSprite::create(Utility::UnicodeToAnsi(sceneBgImg.GetString()).c_str());
		if (!pBackground)
		{
			AfxMessageBox(L"������������ʧ�ܣ�");
			return;
		}
		pScene->addChild(pBackground,-1,0);
	}
	else
	{
		CCTexture2D *tex2D = CCTextureCache::sharedTextureCache()->addImage(Utility::UnicodeToAnsi(sceneBgImg.GetString()).c_str());
		if (!tex2D)
		{
			AfxMessageBox(L"���ر�������ʧ�ܣ�");
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
		AfxMessageBox(L"���������ڣ�");
		return 0;
	}

	//ͨ��lParam���Եõ����޸ĵ���
	CMFCPropertyGridProperty *pPropName = m_wndSpritePropList.GetProperty(0)->GetSubItem(0);
	CString propName(pPropName->GetValue());
	if (!propName.CompareNoCase(L"����"))
	{
		AfxMessageBox(L"����ѡ��һ���������");
		return 0;
	}

	//int pos = propName.ReverseFind('-');
	//if (!pos)
	//{
	//	AfxMessageBox(L"����ID��ʽ����");
	//	return 0;
	//}

	//CString idxStr;
	//idxStr.Format(L"%s",propName.Right(propName.GetLength() - pos - 1));

	//unsigned int idx = atoi(Utility::UnicodeToUtf8(idxStr.GetString()).c_str());

	unsigned int idx = pPropName->GetData();

	CCSprite *pSpr = dynamic_cast<CCSprite*>(pScene->getChildByTag(idx));
	if (!pSpr)
	{
		AfxMessageBox(L"������󲻴��ڣ�");
		return 0;
	}

	propName.Empty();
	propName.Append(pProp->GetName());
	CString propValue(pProp->GetValue());

	if (!propName.CompareNoCase(L"�߿��ػ�"))
	{
		if (!propValue.CompareNoCase(L"��"))
			pSpr->setRectDirty(true);
		else
			pSpr->setRectDirty(false);
	}
	else if (!propName.CompareNoCase(L"��ת"))
	{
		pSpr->setRotation(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"����"))
	{
		pSpr->setScale(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"��б"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		pSpr->setSkewX(atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()));

		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setSkewY(atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"��X����б"))
	{
		pSpr->setSkewX(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));   
	}
	else if (!propName.CompareNoCase(L"��Y����б"))
	{
		pSpr->setSkewY(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"��X�ᷭת"))
	{
		if (!propValue.CompareNoCase(L"��"))
			pSpr->setFlipX(true);
		else
			pSpr->setFlipX(false);
	}
	else if (!propName.CompareNoCase(L"��Y�ᷭת"))
	{
		if (!propValue.CompareNoCase(L"��"))
			pSpr->setFlipY(true);
		else
			pSpr->setFlipY(false);   
	}
	else if (!propName.CompareNoCase(L"���"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setAnchorPoint(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"���X"))
	{
		CString valueX(pProp->GetValue());
		CMFCPropertyGridProperty *pPropY = m_wndSpritePropList.GetProperty(0)->GetSubItem(7)->GetSubItem(1);
		CString valueY(pPropY->GetValue());
		pSpr->setAnchorPoint(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"���Y"))
	{
		CMFCPropertyGridProperty *pPropX = m_wndSpritePropList.GetProperty(0)->GetSubItem(7)->GetSubItem(0);
		CString valueX(pPropX->GetValue());
		CString valueY(pProp->GetValue());
		pSpr->setAnchorPoint(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"��С"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setContentSize(CCSize(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"�߶�"))
	{
		CString valueX(pProp->GetValue());
		CMFCPropertyGridProperty *pPropY = m_wndSpritePropList.GetProperty(0)->GetSubItem(8)->GetSubItem(1);
		CString valueY(pPropY->GetValue());
		pSpr->setContentSize(CCSize(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"���"))
	{
		CMFCPropertyGridProperty *pPropX = m_wndSpritePropList.GetProperty(0)->GetSubItem(8)->GetSubItem(0);
		CString valueX(pPropX->GetValue());
		CString valueY(pProp->GetValue());
		pSpr->setContentSize(CCSize(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);
	}
	else if (!propName.CompareNoCase(L"����"))
	{
		CString valueX(pProp->GetSubItem(0)->GetValue());
		CString valueY(pProp->GetSubItem(1)->GetValue());
		pSpr->setPosition(ccp(
			atof(Utility::UnicodeToUtf8(valueX.GetString()).c_str()),
			atof(Utility::UnicodeToUtf8(valueY.GetString()).c_str()))
			);   
	}
	else if (!propName.CompareNoCase(L"����X"))
	{
		pSpr->setPositionX(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"����Y"))
	{
		pSpr->setPositionY(atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()));
	}
	else if (!propName.CompareNoCase(L"�ӳ�"))
	{
		// ���ҵ�����
		CCRepeatForever *pRepeat = dynamic_cast<CCRepeatForever*>(pSpr->getActionByTag(0));
		if (!pRepeat)
		{
			AfxMessageBox(L"���������ڣ�");
			return 0;
		}
		CCAnimate *pAnimate = dynamic_cast<CCAnimate*>(pRepeat->getInnerAction());
		if (!pAnimate)
		{
			AfxMessageBox(L"���������ڣ�");
			return 0;
		}
		CCAnimation *pAnimation = pAnimate->getAnimation();
		if (!pAnimation)
		{
			AfxMessageBox(L"����֡�����ڣ�");
			return 0;
		}
		// ȡ����֡����
		CCArray *pArray = CCArray::arrayWithArray(pAnimation->getFrames());
		// Ȼ��ֹͣ����
		pSpr->stopActionByTag(0);
		// �����´�������
		//pAnimation = CCAnimation::createWithSpriteFrames( pArray, atof(CFileView::UnicodeToUtf8(propValue.GetString()).c_str()) );
		pAnimation = CCAnimation::animationWithAnimationFrames(pArray,atof(Utility::UnicodeToUtf8(propValue.GetString()).c_str()),-1);
		pAnimate = CCAnimate::actionWithAnimation( pAnimation );
		pRepeat = CCRepeatForever::actionWithAction( pAnimate );
		pRepeat->setTag(0);
		pSpr->runAction(pRepeat);
	}
	else if (!propName.CompareNoCase(L"BBox�ػ�"))
	{
		if (!propValue.CompareNoCase(L"��"))
			pSpr->setBBoxDirty(true);
		else
			pSpr->setBBoxDirty(false);
	}
	else if (!propName.CompareNoCase(L"HBox�ػ�"))
	{
		if (!propValue.CompareNoCase(L"��"))
			pSpr->setHBoxDirty(true);
		else
			pSpr->setHBoxDirty(false);
	}
	else if (!propName.CompareNoCase(L"ֱ���ζ�"))
	{
		SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSpr->getUserData());

		if (!propValue.CompareNoCase(L"��"))
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
		// HBox����
		CString splitStr(L"�����P-");
		int nPos = propName.Find(splitStr);
		if (nPos>=0)
		{
			float x = -1.0f;
			float y = -1.0f;
			int pos = propValue.Find('/');
			if (pos<0)
			{
				//AfxMessageBox(L"������ʽ����ӦΪ��x/y");
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
					// ��䵱ǰ֡��HBox����
					int count = pFrame->getTexture()->vertexCount;
					if (count>MAX_VERTEX_COUNT)
					{
						AfxMessageBox(L"��ǰ֡HBox���������");
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
			AfxMessageBox(L"��δʵ��");
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
		AfxMessageBox(L"���������ڣ�");
		return;
	}

	SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSpr->getUserData());
	if (!pSpriteInfo)
		return;

	// ���ҵ�����
	CCFiniteTimeAction *pSeq = dynamic_cast<CCFiniteTimeAction*>(pSpr->getActionByTag(1));
	if (!pSeq)
	{
		// ȡ���鵱ǰ��������
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

	// ���л����������
	m_wndObjectCombo.SetCurSel(1);

	switchComonBox();

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"���������ڣ�");
		return;
	}

	if (!m_wndSpritePropList.GetPropertyCount())
	{
		AfxMessageBox(L"�������������");
		return;
	}

	// ˢ���������
	CMFCPropertyGridProperty *pProp = m_wndSpritePropList.GetProperty(0);
	if (!pProp->GetSubItemsCount())
	{
		AfxMessageBox(L"�������������");
		return;
	}

	// ����
	CMFCPropertyGridProperty *pSubItem = pProp->GetSubItem(0);
	UpdateProperty(pSubItem,pSprite->getObjName());
	SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSprite->getUserData());
	pSubItem->SetData((DWORD_PTR)pSpriteInfo->idx);

	// �߿�
	pSubItem = pProp->GetSubItem(1);
	if (pSprite->getRectDirty())
		UpdateProperty(pSubItem,"��");
	else
		UpdateProperty(pSubItem,"��");

	// ��ת
	pSubItem = pProp->GetSubItem(2);
	UpdateProperty(pSubItem,pSprite->getRotation());

	// ����
	pSubItem = pProp->GetSubItem(3);
	UpdateProperty(pSubItem,pSprite->getScale());

	// ��б
	pSubItem = pProp->GetSubItem(4);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getSkewX());
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getSkewY());

	// ��ת
	pSubItem = pProp->GetSubItem(5);
	if (pSprite->isFlipX())
		UpdateProperty(pSubItem,"��");
	else
		UpdateProperty(pSubItem,"��");

	pSubItem = pProp->GetSubItem(6);
	if (pSprite->isFlipY())
		UpdateProperty(pSubItem,"��");
	else
		UpdateProperty(pSubItem,"��");

	// ���
	pSubItem = pProp->GetSubItem(7);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getAnchorPoint().x);
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getAnchorPoint().y);

	// ��С
	pSubItem = pProp->GetSubItem(8);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getContentSize().width);
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getContentSize().height);

	// ����
	pSubItem = pProp->GetSubItem(9);
	UpdateProperty(pSubItem->GetSubItem(0),pSprite->getPositionX());
	UpdateProperty(pSubItem->GetSubItem(1),pSprite->getPositionY());

	// �ӳ�
	// ���ҵ�����
	CCRepeatForever *pRepeat = dynamic_cast<CCRepeatForever*>(pSprite->getActionByTag(0));
	if (!pRepeat)
	{
		AfxMessageBox(L"���������ڣ�");
		return;
	}
	CCAnimate *pAnimate = dynamic_cast<CCAnimate*>(pRepeat->getInnerAction());
	if (!pAnimate)
	{
		AfxMessageBox(L"���������ڣ�");
		return;
	}
	CCAnimation *pAnimation = pAnimate->getAnimation();
	if (!pAnimation)
	{
		AfxMessageBox(L"����֡�����ڣ�");
		return;
	}
	float delay = pAnimation->getDelayPerUnit();
	pSubItem = pProp->GetSubItem(10);
	UpdateProperty(pSubItem,delay);

	// BBox
	pSubItem = pProp->GetSubItem(11);
	if (pSprite->getBBoxDirty())
		UpdateProperty(pSubItem,"��");
	else
		UpdateProperty(pSubItem,"��");

	// HBox
	pSubItem = pProp->GetSubItem(12);
	if (pSprite->getHBoxDirty())
		UpdateProperty(pSubItem,"��");
	else
		UpdateProperty(pSubItem,"��");

	CCLabelTTF *pTTF = dynamic_cast<CCLabelTTF*>(pScene->getChildByTag(100));
	if (pTTF)
	{
		pTTF->setString(Utility::UnicodeToUtf8(L"�����ྫ������Ķ���֡���ɱ༭����֡��HBox���ݵ�\n�������ק������֡������ק").c_str());
		pTTF->setColor(ccc3(255,0,0));
	}

	CCLabelTTF *pTTFPos = dynamic_cast<CCLabelTTF*>(pScene->getChildByTag(99));
	if (pTTFPos)
	{
		pTTFPos->setVisible(false);
	}

	// HBox����
	// ���Ը���frameName��֡�����в���
	// Ҳ���Ը���frameName��hitBox�в���
	if (gFrameName.GetLength())
	{
		// ����䵼���HBox��������
		//SPRITE_INFO *pSpriteInfo = (SPRITE_INFO*)(pSprite->getUserData());
		if (pSpriteInfo)
		{
			CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Utility::UnicodeToAnsi(gFrameName.GetString()).c_str());
			if (pFrame)
			{
				gIsFrame = true;

				if (pTTF)
				{
					pTTF->setString(Utility::UnicodeToUtf8(L"��ǰ֡�ɱ༭HBox���ݵ㣺\n���Ҳ�[HBox����]����������\n���λ��ѡ���ľ��鷶Χ�ڣ�������ʾΪ��ɫ������Ϊ��ɫ").c_str());
					pTTF->setColor(ccc3(0,255,0));
				}

				if (pTTFPos)
				{
					pTTFPos->setVisible(true);
				}

				// ��ͣ������~
				pSprite->pauseSchedulerAndActions();

				// �л�����ǰ֡
				pSprite->setDisplayFrame(pFrame);

				// ��ʾHBox���Կؼ�
				pSubItem = pProp->GetSubItem(13);
				pSubItem->Show(1);

				// ��䵱ǰ֡��HBox����
				int count = pFrame->getTexture()->vertexCount;
				if (count>MAX_VERTEX_COUNT)
				{
					AfxMessageBox(L"��ǰ֡HBox���������");
				}
				else
				{
					// ʵʱ�������
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
				// �ָ���~
				pSprite->resumeSchedulerAndActions();

				// ����HBox���Կؼ�
				pSubItem = pProp->GetSubItem(13);
				pSubItem->Show(0);
			}
		}
	}

	// ֱ���ζ�
	pSubItem = pProp->GetSubItem(14);
	if (pSpriteInfo->runAction)
		UpdateProperty(pSubItem,"��");
	else
		UpdateProperty(pSubItem,"��");
}

void CPropertiesWnd::OnUpdateSpriteFramePos(CCSprite *pSprite,POINT_INFO *pPoint)
{
	// ���л����������
	m_wndObjectCombo.SetCurSel(1);

	switchComonBox();

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"���������ڣ�");
		return;
	}

	if (!m_wndSpritePropList.GetPropertyCount())
	{
		AfxMessageBox(L"�������������");
		return;
	}

	// ˢ���������
	CMFCPropertyGridProperty *pProp = m_wndSpritePropList.GetProperty(0);
	if (!pProp->GetSubItemsCount())
	{
		AfxMessageBox(L"�������������");
		return;
	}

	// HBox����
	// ���Ը���frameName��֡�����в���
	// Ҳ���Ը���frameName��hitBox�в���
	if (gFrameName.GetLength())
	{
		// ����䵼���HBox��������
		CMFCPropertyGridProperty *pSubItem = pProp->GetSubItem(13);
		CMFCPropertyGridProperty *pItem = pSubItem->GetSubItem(gHitPoint-1);
		CString value;
		value.Format(L"%0.2f/%0.2f",pPoint->x,pPoint->y);
		UpdateProperty(pItem,Utility::UnicodeToUtf8(value.GetString()).c_str());
	}
}

void CPropertiesWnd::OnUpdateSceneBg()
{
	// ���л����������
	m_wndObjectCombo.SetCurSel(0);

	switchComonBox();

	HelloWorld* pScene = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!pScene)
	{
		AfxMessageBox(L"���������ڣ�");
		return;
	}

	if (!m_wndScenePropList.GetPropertyCount())
	{
		AfxMessageBox(L"�������������");
		return;
	}

	// ˢ���������
	CMFCPropertyGridProperty *pRoot = m_wndScenePropList.GetProperty(0);
	if (!pRoot->GetSubItemsCount())
	{
		AfxMessageBox(L"�������������");
		return;
	}

	CMFCPropertyGridFileProperty *pProp = (CMFCPropertyGridFileProperty*)pRoot->GetSubItem(0);

	pProp->AllowEdit(1);
	UpdateProperty(pProp,Utility::UnicodeToUtf8(gBackgroundImg.GetString()).c_str());
	pProp->AllowEdit(0);

	UpdateSceneBg(gBackgroundImg);
}
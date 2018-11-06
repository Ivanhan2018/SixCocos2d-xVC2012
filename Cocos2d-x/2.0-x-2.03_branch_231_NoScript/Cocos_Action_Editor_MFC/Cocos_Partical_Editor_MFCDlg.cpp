
// Cocos_Partical_Editor_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "Cocos_Partical_Editor_MFC.h"
#include "Cocos_Partical_Editor_MFCDlg.h"
#include "cocos2d.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "HelloWorldScene.h"
#include "tinyxml/tinyxml.h"
#include "CBase64.h"
#include "platform/third_party/win32/zlib/zlib.h"
#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CCos_Partical_Editor* p_dlg = NULL;


MFC_WND_Delegate* EditorDlgPtr()
{
	return p_dlg;
}

CCocos_Partical_Editor_MFCDlg::CCocos_Partical_Editor_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCocos_Partical_Editor_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCocos_Partical_Editor_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCocos_Partical_Editor_MFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CCocos_Partical_Editor_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	return TRUE;  
}

void CCocos_Partical_Editor_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CCocos_Partical_Editor_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCocos_Partical_Editor_MFCDlg::OnDestroy()
{
	ASSERT(1);
}

void CCocos_Partical_Editor_MFCDlg::OnOK()
{

}

void CCocos_Partical_Editor_MFCDlg::OnCancel()
{
	this->ShowWindow(0);
}


CCos_Partical_Editor::CCos_Partical_Editor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCocos_Partical_Editor_MFCDlg::IDD, pParent)
	, m_StrPath(_T("")),m_hTexture(NULL)
	, m_fStartSize(0)
	, m_fStartSizeVar(0)
	, m_fEndSize(0)
	, m_fEndSizeVar(0)
	, m_fStartSpin(0)
	, m_fStartSpinVar(0)
	, m_fEndSpin(0)
	, m_fEndSpinVar(0)
	, m_uTotalParticales(0)
	, m_as(0)
	, m_asv(0)
	, m_ae(0)
	, m_aev(0)
	, m_fDuration(0)
	, m_fLife(0)
	, m_fLifeVar(0)
	, m_fAngle(0)
	, m_fAngleVar(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCos_Partical_Editor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_TEXTURE_PATH, m_StrPath);
	DDX_Control(pDX, ID_TEXTRUE_PREVIEW, m_textrue_preview);
	DDX_Control(pDX, IDC_EDIT1, m_start);
	DDX_Control(pDX, IDC_EDIT2, m_startvar);
	DDX_Control(pDX, IDC_EDIT3, m_stop);
	DDX_Control(pDX, IDC_EDIT4, m_stopvar);
	DDX_Control(pDX, IDC_EDIT5, m_startspin);
	DDX_Control(pDX, IDC_EDIT6, m_startspinvar);
	DDX_Control(pDX, IDC_EDIT7, m_stopspin);
	DDX_Control(pDX, IDC_EDIT8, m_stopspinvar);
	DDX_Control(pDX, IDC_EDIT10, m_EmissionRate);
	DDX_Text(pDX, IDC_EDIT1, m_fStartSize);
	DDX_Text(pDX, IDC_EDIT2, m_fStartSizeVar);
	DDX_Text(pDX, IDC_EDIT3, m_fEndSize);
	DDX_Text(pDX, IDC_EDIT4, m_fEndSizeVar);
	DDX_Text(pDX, IDC_EDIT5, m_fStartSpin);
	DDX_Text(pDX, IDC_EDIT6, m_fStartSpinVar);
	DDX_Text(pDX, IDC_EDIT7, m_fEndSpin);
	DDX_Text(pDX, IDC_EDIT8, m_fEndSpinVar);
	DDX_Text(pDX, IDC_EDIT9, m_uTotalParticales);
	DDX_Control(pDX, IDC_EDIT15, m_startcolorAlpha);
	DDX_Control(pDX, IDC_EDIT16, m_startcolorVarAlpha);
	DDX_Control(pDX, IDC_EDIT17, m_EndColorAlpha);
	DDX_Control(pDX, IDC_EDIT18, m_EndColorVarAlpha);
	DDX_Text(pDX, IDC_EDIT15, m_as);
	DDX_Text(pDX, IDC_EDIT16, m_asv);
	DDX_Text(pDX, IDC_EDIT17, m_ae);
	DDX_Text(pDX, IDC_EDIT18, m_aev);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_startcolor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_startcolorVar);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_endcolor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, m_endcolorVar);
	DDX_Text(pDX, IDC_EDIT10, m_fDuration);
	DDX_Control(pDX, IDC_EDIT19, m_life);
	DDX_Control(pDX, IDC_EDIT20, m_LifeVar);
	DDX_Text(pDX, IDC_EDIT19, m_fLife);
	DDX_Text(pDX, IDC_EDIT20, m_fLifeVar);
	DDX_Control(pDX, IDC_EDIT21, m_Angle);
	DDX_Control(pDX, IDC_EDIT22, m_AngleVar);
	DDX_Text(pDX, IDC_EDIT21, m_fAngle);
	DDX_Text(pDX, IDC_EDIT22, m_fAngleVar);
	DDX_Control(pDX, IDC_COMBO1, m_blendCB_src);
	DDX_Control(pDX, IDC_COMBO2, m_blendCB_dst);
	DDX_Control(pDX, IDC_COMBO4, m_runTargetSprCMB);
	DDX_Control(pDX, IDC_RADIO1, m_partTypeA);
	DDX_Control(pDX, IDC_RADIO2, m_partTypeB);
	DDX_Control(pDX, IDC_RADIO5, m_partShow);
	DDX_Control(pDX, IDC_RADIO6, m_partHide);
	DDX_Control(pDX, IDC_RADIO3, m_runTargetBg);
	DDX_Control(pDX, IDC_RADIO4, m_runTargetSpr);
}

BEGIN_MESSAGE_MAP(CCos_Partical_Editor, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CCos_Partical_Editor::OnBnClickedModeA)
	ON_BN_CLICKED(IDC_RADIO2, &CCos_Partical_Editor::OnBnClickedModeB)
	ON_BN_CLICKED(IDC_RADIO5, &CCos_Partical_Editor::OnBnClickedShow)
	ON_BN_CLICKED(IDC_RADIO6, &CCos_Partical_Editor::OnBnClickedHide)
	ON_BN_CLICKED(IDC_BUTTON1, &CCos_Partical_Editor::OnBnClickedBrowserTexture)
	ON_BN_CLICKED(IDC_BUTTON2, &CCos_Partical_Editor::OnBnClickedPreview)
	ON_BN_CLICKED(IDC_BUTTON4, &CCos_Partical_Editor::OnBnClickedLoad)
	ON_BN_CLICKED(IDOK, &CCos_Partical_Editor::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON3, &CCos_Partical_Editor::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO3, &CCos_Partical_Editor::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CCos_Partical_Editor::OnBnClickedRadio4)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CCos_Partical_Editor::OnCbnSelchangeCombo4)
END_MESSAGE_MAP()



BOOL CCos_Partical_Editor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	dlg_modeA = new CPartical_Detial_Dlg_ModeA;
	dlg_modeB = new CPartical_Detial_Dlg_ModeB;

	dlg_modeA->Create(IDD_MODE_A,this);
	dlg_modeB->Create(IDD_MODE_B,this);

	dlg_modeA->ShowWindow(SW_HIDE);
	dlg_modeB->ShowWindow(SW_HIDE);

	dlg_modeA->MoveWindow(0,305,700,95);
	dlg_modeB->MoveWindow(0,305,700,95);

	m_StrPath = _T("未指定贴图");
	UpdateData(FALSE);

	CheckDlgButton(IDC_RADIO1,1);
	m_blendCB_src.SetCurSel(0);
	m_blendCB_dst.SetCurSel(0);
	dlg_modeA->ShowWindow(SW_SHOW);

	p_dlg = this;

	RefreshRunTargetCMB();

	return TRUE;  
}

void CCos_Partical_Editor::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CCos_Partical_Editor::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCos_Partical_Editor::OnDestroy()
{
	if(dlg_modeA)
	{
		delete dlg_modeA;
		dlg_modeA = NULL;
	}
	if(dlg_modeB)
	{
		delete dlg_modeB;
		dlg_modeB = NULL;
	}
	if(m_hTexture)
	{
		DeleteObject(m_hTexture);
	}
}

void CCos_Partical_Editor::OnCancel()
{
	this->GetParent()->ShowWindow(SW_HIDE);
}


void CCos_Partical_Editor::OnBnClickedModeA()
{
	dlg_modeA->ShowWindow(SW_SHOW);
	dlg_modeB->ShowWindow(SW_HIDE);
	m_partTypeB.SetCheck(0);
}


void CCos_Partical_Editor::OnBnClickedModeB()
{
	dlg_modeA->ShowWindow(SW_HIDE);
	dlg_modeB->ShowWindow(SW_SHOW);
	m_partTypeA.SetCheck(0);
}

void CCos_Partical_Editor::OnBnClickedShow()
{
	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;

	CCParticleSystemQuad *particals = dynamic_cast<CCParticleSystemQuad*>(ptr->part);
	if (!particals)
		particals = dynamic_cast<CCParticleSystemQuad*>(ptr->MakeParticle(ptr));
	particals->setVisible(true);
	m_partHide.SetCheck(0);
	Load();
}

void CCos_Partical_Editor::OnBnClickedHide()
{
	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;

	CCParticleSystemQuad *particals = dynamic_cast<CCParticleSystemQuad*>(ptr->part);
	if (!particals)
		particals = dynamic_cast<CCParticleSystemQuad*>(ptr->MakeParticle(ptr));
	particals->setVisible(false);
	m_partShow.SetCheck(0);
}

void CCos_Partical_Editor::OnBnClickedBrowserTexture()
{
	CFileDialog fdlg(
		TRUE,
		_T("PNG图像(*.png)"),
		NULL,
		OFN_HIDEREADONLY ,
		_T("图像文件(*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp;)||"),
		NULL);
	fdlg.m_ofn.lpstrTitle=_T("请选择粒子贴图");
	if(fdlg.DoModal()==IDCANCEL)
	{

	}else 
	{
		m_StrPath = fdlg.GetPathName();
		LoadTextruePreview();
	}
	UpdateData(FALSE);
}


void CCos_Partical_Editor::LoadTextruePreview()
{
	if(m_hTexture)
		DeleteObject(m_hTexture);
	CImage image;
	if(FAILED(image.Load(m_StrPath)))
	{
		//AfxMessageBox(_T("未载入贴图"));
		return;
	}
	m_hTexture = image.Detach();
	if(!m_hTexture)
		return;
	HBITMAP oldbmp = m_textrue_preview.SetBitmap(m_hTexture);
	if(oldbmp)
	{
		DeleteObject(oldbmp);
	}
}

USING_NS_CC;

void CCos_Partical_Editor::OnBnClickedPreview()
{
	Set();
}

void CCos_Partical_Editor::Set()
{
	UpdateData(TRUE);
	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;

	CCParticleSystemQuad *particals = dynamic_cast<CCParticleSystemQuad*>(ptr->part);
	if (!particals)
		return;

	if(IsDlgButtonChecked(IDC_RADIO1))
	{
		particals->setEmitterMode(kCCParticleModeGravity);
		dlg_modeA->Update(particals);
	}
	else
	{
		particals->setEmitterMode(kCCParticleModeRadius);
		dlg_modeB->Update(particals);
	}

	particals->setStartSize(m_fStartSize);
	particals->setStartSizeVar(m_fStartSizeVar);
	particals->setEndSize(m_fEndSize);
	particals->setEndSizeVar(m_fEndSizeVar);
	particals->setStartSpin(m_fStartSpin);
	particals->setStartSpinVar(m_fStartSpinVar);
	particals->setEndSpin(m_fEndSpin);
	particals->setEndSpinVar(m_fEndSpinVar);
	particals->setTotalParticles(m_uTotalParticales);
	particals->setTexture(CCTextureCache::sharedTextureCache()->addImage(CStringA(m_StrPath)));
	particals->setDuration(m_fDuration);
	particals->setLife(m_fLife);
	particals->setLifeVar(m_fLifeVar);
	particals->setAngle(m_fAngle);
	particals->setAngleVar(m_fAngleVar);

	COLORREF aRef = m_startcolor.GetColor();
	cocos2d::ccColor4F aColor = {0};
	aColor.r = (float)GetRValue(aRef)/255;
	aColor.g = (float)GetGValue(aRef)/255;
	aColor.b = (float)GetBValue(aRef)/255;
	aColor.a = (float)m_as/255;
	particals->setStartColor(aColor);

	aRef = m_startcolorVar.GetColor();
	aColor.r = (float)GetRValue(aRef)/255;
	aColor.g = (float)GetGValue(aRef)/255;
	aColor.b = (float)GetBValue(aRef)/255;
	aColor.a = (float)m_asv/255;
	particals->setStartColorVar(aColor);

	aRef = m_endcolor.GetColor();
	aColor.r = (float)GetRValue(aRef)/255;
	aColor.g = (float)GetGValue(aRef)/255;
	aColor.b = (float)GetBValue(aRef)/255;
	aColor.a = (float)m_ae/255;
	particals->setEndColor(aColor);

	aRef = m_endcolorVar.GetColor();
	aColor.r = (float)GetRValue(aRef)/255;
	aColor.g = (float)GetGValue(aRef)/255;
	aColor.b = (float)GetBValue(aRef)/255;
	aColor.a = (float)m_aev/255;
	particals->setEndColorVar(aColor);

	int src = m_blendCB_src.GetCurSel();
	int dst = m_blendCB_dst.GetCurSel();

	switch(src)
	{
		case 0:src = GL_ZERO;break;
		case 1:src = GL_ONE;break;
		case 2:src = GL_DST_COLOR;break;
		case 3:src = GL_ONE_MINUS_DST_COLOR;break;
		case 4:src = GL_SRC_ALPHA;break;
		case 5:src = GL_ONE_MINUS_SRC_COLOR;break;
		case 6:src = GL_DST_ALPHA;break;
		case 7:src = GL_ONE_MINUS_DST_ALPHA;break;
		case 8:src = GL_SRC_ALPHA_SATURATE;break;
		default:AfxMessageBox(_T("Not vaild blendfunc!"));
	}

	switch(dst)
	{
		case 0:dst = GL_ZERO;break;
		case 1:dst = GL_ONE;break;
		case 2:dst = GL_SRC_COLOR;break;
		case 3:dst = GL_ONE_MINUS_SRC_COLOR;break;
		case 4:dst = GL_SRC_ALPHA;break;
		case 5:dst = GL_ONE_MINUS_SRC_ALPHA;break;
		case 6:dst = GL_DST_ALPHA;break;
		case 7:dst = GL_ONE_MINUS_DST_ALPHA;break;
		default:AfxMessageBox(_T("Not vaild blendfunc!"));
	}
	ccBlendFunc afunc = {src,dst};
	particals->setBlendFunc(afunc);
}

void CCos_Partical_Editor::Load()
{
	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;

	CCParticleSystemQuad *particals = dynamic_cast<CCParticleSystemQuad*>(ptr->part);
	if (!particals)
		return;

	if(particals->getEmitterMode()==kCCParticleModeGravity)
	{
		CheckDlgButton(IDC_RADIO1,1);
		dlg_modeA->Load(particals);
		dlg_modeB->ShowWindow(SW_HIDE);
		dlg_modeA->ShowWindow(SW_SHOW);
	}
	else
	{
		CheckDlgButton(IDC_RADIO2,1);
		dlg_modeB->Load(particals);
		dlg_modeA->ShowWindow(SW_HIDE);
		dlg_modeB->ShowWindow(SW_SHOW);
	}

	m_fStartSize = particals->getStartSize();
	m_fStartSizeVar = particals->getStartSizeVar();
	m_fEndSize = particals->getEndSize();
	m_fEndSizeVar = particals->getEndSizeVar();
	m_fStartSpin = particals->getStartSpin();
	m_fStartSpinVar = particals->getStartSpinVar();
	m_fEndSpin = particals->getEndSpin();
	m_fEndSpinVar = particals->getEndSpinVar();
	m_uTotalParticales = particals->getTotalParticles();
	m_fDuration = particals->getDuration();
	m_fLife = particals->getLife();
	m_fLifeVar = particals->getLifeVar();
	m_fAngle = particals->getAngle();
	m_fAngleVar = particals->getAngleVar();
 	VolatileTexture* data = VolatileTexture::find(particals->getTexture());
	if (strlen(data->GetFileName()))
		m_StrPath = data->GetFileName();

	cocos2d::ccColor4F aColor = particals->getStartColor();
	m_startcolor.SetColor(RGB(aColor.r*255,aColor.g*255,aColor.b*255));
	m_as = aColor.a*255;

	aColor = particals->getStartColorVar();
	m_startcolorVar.SetColor(RGB(aColor.r*255,aColor.g*255,aColor.b*255));
	m_asv = aColor.a*255;

	aColor = particals->getEndColor();
	m_endcolor.SetColor(RGB(aColor.r*255,aColor.g*255,aColor.b*255));
	m_ae = aColor.a*255;

	aColor = particals->getEndColorVar();
	m_endcolorVar.SetColor(RGB(aColor.r*255,aColor.g*255,aColor.b*255));
	m_aev = aColor.a*255;

	ccBlendFunc func = particals->getBlendFunc();
	int nIndex = 0;
	switch(func.src)
	{
		case GL_ZERO:nIndex = 0;break;
		case GL_ONE:nIndex = 1;break;
		case GL_DST_COLOR:nIndex = 2;break;
		case GL_ONE_MINUS_DST_COLOR:nIndex = 3;break;
		case GL_SRC_ALPHA:nIndex = 4;break;
		case GL_ONE_MINUS_SRC_COLOR:nIndex = 5;break;
		case GL_DST_ALPHA:nIndex = 6;break;
		case GL_ONE_MINUS_DST_ALPHA:nIndex = 7;break;
		case GL_SRC_ALPHA_SATURATE:nIndex = 8;break;
		default:AfxMessageBox(_T("Not vaild blendfunc!"));
	}
	m_blendCB_src.SetCurSel(nIndex);

	switch(func.dst)
	{
		case GL_ZERO:nIndex = 0;break;
		case GL_ONE:nIndex = 1;break;
		case GL_SRC_COLOR:nIndex = 2;break;
		case GL_ONE_MINUS_SRC_COLOR:nIndex = 3;break;
		case GL_SRC_ALPHA:nIndex = 4;break;
		case GL_ONE_MINUS_SRC_ALPHA:nIndex = 5;break;
		case GL_DST_ALPHA:nIndex = 6;break;
		case GL_ONE_MINUS_DST_ALPHA:nIndex = 7;break;
		default:AfxMessageBox(_T("Not vaild blendfunc!"));
	}
	m_blendCB_dst.SetCurSel(nIndex);

	CCObject *parent = (CCObject*)(particals->getParent());
	// 加载到场景
	if (parent->isEqual(ptr))
	{
		m_runTargetBg.SetCheck(1);
		m_runTargetSpr.SetCheck(0);
		m_runTargetSprCMB.EnableWindow(0);
	}
	// 加载到精灵
	else
	{
		m_runTargetBg.SetCheck(0);
		m_runTargetSpr.SetCheck(1);
		m_runTargetSprCMB.EnableWindow(1);
	}

	LoadTextruePreview();
	UpdateData(FALSE);
}

void CCos_Partical_Editor::LoadFile()
{
	CFileDialog fdlg(
		TRUE,
		_T("XML粒子存档文件(*.plist)"),
		NULL,
		OFN_HIDEREADONLY ,
		_T("XML文档(*.plist;*.xml;*.partical)|*.plist;*.xml;*.partical;)||"),
		NULL);
	fdlg.m_ofn.lpstrTitle=_T("请选择粒子存档");
	if(fdlg.DoModal()==IDCANCEL)
		return;
	CStringA path(fdlg.GetPathName());
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;
	
	ptr->MakeParticle(ptr,path);

	//CCParticleSystemQuad* particals = CCParticleSystemQuad::create(path);
	//if(!particals)
	//	return;
	//ptr->removeChildByTag(2,true);
	//particals->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));
	//ptr->addChild(particals,1,2);

	HBITMAP htmp = m_textrue_preview.SetBitmap(NULL);
	if(htmp)
		DeleteObject(htmp);
	Load();
}

void CCos_Partical_Editor::OnBnClickedLoad()
{
	LoadFile();
}

bool deflateData(LPBYTE& pbuf,int& bufSize)
{
	int err = Z_OK;
	uLongf outsize = bufSize*2+10;
	LPBYTE newbuf = new BYTE[outsize];
	ZeroMemory(newbuf,outsize);
	err = compress(newbuf,&outsize,pbuf,bufSize);
	if(err!=Z_OK)
		return false;
	delete[] pbuf;
	pbuf = newbuf;
	bufSize = outsize;
	return true;
}

void AddXMLContent(TiXmlElement* parent, int valuetype,LPCSTR name,float aValue)
{
	CStringA tmpstr;
	CStringA tmptype;
	switch (valuetype)
	{
	case 0://Integer
		tmpstr.Format("%d",(int)aValue);
		tmptype = "integer";
		break;
	case 1://real,float
		tmpstr.Format("%03f",aValue);
		tmptype = "real";
		break;
	case 2: //String
		{
			LPCSTR str = (LPCSTR)(int)aValue;
			tmpstr = str;
			tmptype = "string";
		}
		break;
	default: return;
	}

	TiXmlElement* key = new TiXmlElement("key");
	TiXmlText* text = new TiXmlText(name);
	key->LinkEndChild(text);
	parent->LinkEndChild(key);

	key = new TiXmlElement(tmptype);
	text = new TiXmlText(tmpstr);
	key->LinkEndChild(text);
	parent->LinkEndChild(key);
}

void CCos_Partical_Editor::OnBnClickedSave()
{
	UpdateData(TRUE);
	CreateDirectory(_T("Output"),NULL);
	TiXmlDocument doc;
	//pList
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","UTF-8","");
	doc.LinkEndChild(decl);
	TiXmlElement *RootElement = new TiXmlElement("plist");
	doc.LinkEndChild(RootElement);
	RootElement->SetDoubleAttribute("version",1.0f);

	//dict
	TiXmlElement* dictElement = new TiXmlElement("dict");
	RootElement->LinkEndChild(dictElement);

	//content
	CFileDialog fdlg(
		FALSE,
		_T("XML粒子存档文件(*.plist)"),
		NULL,
		OFN_HIDEREADONLY ,
		_T("XML文档(*.plist;*.xml;*.partical)|*.plist;*.xml;*.partical;)||"),
		NULL);
	fdlg.m_ofn.lpstrTitle=_T("请选择粒子存档");
	if(fdlg.DoModal()==IDCANCEL)
		return;
	CStringA path(fdlg.GetPathName());

	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;
	
	CCParticleSystemQuad *particals = dynamic_cast<CCParticleSystemQuad*>(ptr->part);
	if (!particals)
		return;

	AddXMLContent(dictElement,1,"angle",particals->getAngle());
	AddXMLContent(dictElement,1,"angleVariance",particals->getAngleVar());
	AddXMLContent(dictElement,0,"blendFuncDestination",particals->getBlendFunc().dst);
	AddXMLContent(dictElement,0,"blendFuncSource",particals->getBlendFunc().src);
	AddXMLContent(dictElement,1,"duration",particals->getDuration());
	AddXMLContent(dictElement,1,"emitterType",particals->getEmitterMode());

	AddXMLContent(dictElement,1,"startColorAlpha",particals->getStartColor().a);
	AddXMLContent(dictElement,1,"startColorBlue",particals->getStartColor().b);
	AddXMLContent(dictElement,1,"startColorGreen",particals->getStartColor().g);
	AddXMLContent(dictElement,1,"startColorRed",particals->getStartColor().r);

	AddXMLContent(dictElement,1,"startColorVarianceAlpha",particals->getStartColorVar().a);
	AddXMLContent(dictElement,1,"startColorVarianceBlue",particals->getStartColorVar().b);
	AddXMLContent(dictElement,1,"startColorVarianceGreen",particals->getStartColorVar().g);
	AddXMLContent(dictElement,1,"startColorVarianceRed",particals->getStartColorVar().r);

	AddXMLContent(dictElement,1,"finishColorAlpha",particals->getEndColor().a);
	AddXMLContent(dictElement,1,"finishColorBlue",particals->getEndColor().b);
	AddXMLContent(dictElement,1,"finishColorGreen",particals->getEndColor().g);
	AddXMLContent(dictElement,1,"finishColorRed",particals->getEndColor().r);

	AddXMLContent(dictElement,1,"finishColorVarianceAlpha",particals->getEndColorVar().a);
	AddXMLContent(dictElement,1,"finishColorVarianceBlue",particals->getEndColorVar().b);
	AddXMLContent(dictElement,1,"finishColorVarianceGreen",particals->getEndColorVar().g);
	AddXMLContent(dictElement,1,"finishColorVarianceRed",particals->getEndColorVar().r);

	AddXMLContent(dictElement,1,"startParticleSize",particals->getStartSize());
	AddXMLContent(dictElement,1,"startParticleSizeVariance",particals->getStartSizeVar());

	AddXMLContent(dictElement,1,"finishParticleSize",particals->getEndSize());
	AddXMLContent(dictElement,1,"finishParticleSizeVariance",particals->getEndSizeVar());

	AddXMLContent(dictElement,1,"rotationStart",particals->getStartSpin());
	AddXMLContent(dictElement,1,"rotationStartVariance",particals->getStartSpinVar());
	AddXMLContent(dictElement,1,"rotationEnd",particals->getEndSpin());
	AddXMLContent(dictElement,1,"rotationEndVariance",particals->getEndSpinVar());

	AddXMLContent(dictElement,1,"maxParticles",particals->getTotalParticles());

	AddXMLContent(dictElement,1,"particleLifespan",particals->getLife());
	AddXMLContent(dictElement,1,"particleLifespanVariance",particals->getLifeVar());

	AddXMLContent(dictElement,1,"sourcePositionx",particals->getPosition().x);
	AddXMLContent(dictElement,1,"sourcePositiony",particals->getPosition().y);
	AddXMLContent(dictElement,1,"sourcePositionVariancex",particals->getPosVar().x);
	AddXMLContent(dictElement,1,"sourcePositionVariancey",particals->getPosVar().y);

	if(particals->getEmitterMode() == kCCParticleModeGravity)
	{
		AddXMLContent(dictElement,1,"gravityx",particals->getGravity().x);
		AddXMLContent(dictElement,1,"gravityy",particals->getGravity().y);
		AddXMLContent(dictElement,1,"speed",particals->getSpeed());
		AddXMLContent(dictElement,1,"speedVariance",particals->getSpeedVar());
		AddXMLContent(dictElement,1,"radialAcceleration",particals->getRadialAccel());
		AddXMLContent(dictElement,1,"radialAccelVariance",particals->getRadialAccelVar());
		AddXMLContent(dictElement,1,"tangentialAcceleration",particals->getTangentialAccel());
		AddXMLContent(dictElement,1,"tangentialAccelVariance",particals->getTangentialAccelVar());
	}
	else
	{
		AddXMLContent(dictElement,1,"maxRadius",particals->getStartRadius());
		AddXMLContent(dictElement,1,"maxRadiusVariance",particals->getStartRadiusVar());
		AddXMLContent(dictElement,1,"minRadius",particals->getEndRadius());
		AddXMLContent(dictElement,1,"minRadiusVariance",particals->getEndRadiusVar());
		AddXMLContent(dictElement,1,"rotatePerSecond",particals->getRotatePerSecond());
		AddXMLContent(dictElement,1,"rotatePerSecondVariance",particals->getRotatePerSecondVar());
	}

	AddXMLContent(dictElement,2,"textureFileName",(float)(int)(LPCSTR)(Utility::UnicodeToUtf8(m_StrPath.GetString()).c_str()));

	//Texture data hash
	std::string aHash;
	while(1)
	{
		CFile file(m_StrPath,CFile::modeRead|CFile::typeBinary);
		int filesize = file.GetLength();
		if(!filesize)
			break;
		BYTE* pbuf = new BYTE[filesize+1];
		ZeroMemory(pbuf,filesize+1);
		if(FAILED(file.Read(pbuf,filesize)))
		{
			file.Close();
			break;
		}
		file.Close();

		if(!deflateData(pbuf,filesize))
			break;

		CBase64::Encode(pbuf,filesize,aHash);
		AddXMLContent(dictElement,2,"textureImageData",(float)(int)aHash.c_str());
		delete[] pbuf;
		break;
	}
	//aHash = "1234";


	doc.SaveFile(path);
	doc.Clear();
}


void CCos_Partical_Editor::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCos_Partical_Editor::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_runTargetSpr.SetCheck(0);
	m_runTargetSprCMB.EnableWindow(0);
	m_runTargetSprCMB.SetCurSel(-1);

	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(!ptr)
		return;

	ptr->MakeParticle(ptr);
}

void CCos_Partical_Editor::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_runTargetBg.SetCheck(0);
	m_runTargetSprCMB.EnableWindow(1);
}

void CCos_Partical_Editor::RefreshRunTargetCMB()
{
	// 先清掉所有项
	m_runTargetSprCMB.Clear();
	m_runTargetSprCMB.ResetContent();
	
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	SPRITE_MAP sprMap = pMainFrame->m_wndFileView.m_SpriteMap;

	int idx = 0;
	for (SPRITE_ITER iter=sprMap.begin();iter!=sprMap.end();iter++)
	{
		SPRITE_INFO *pSprInfo = iter->second;
		m_runTargetSprCMB.InsertString(idx,pSprInfo->imageName);
		idx++;
	}
	m_runTargetSprCMB.SetCurSel(-1);
}

void CCos_Partical_Editor::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_runTargetSprCMB.GetCurSel();
	if (nPos>=0)
	{
		HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
		if(!ptr)
			return;

		CCSprite *pFish = dynamic_cast<CCSprite*>(ptr->getChildByTag(nPos+1));
		if (!pFish)
			return;
		ptr->MakeParticle(pFish);
	}
}
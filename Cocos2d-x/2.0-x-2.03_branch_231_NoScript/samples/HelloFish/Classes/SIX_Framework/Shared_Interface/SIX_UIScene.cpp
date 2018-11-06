#include "SIX_UIScene.h"
//#include <SIX_ClientLogic.h>

//USING_NS_CC_EXT;

SIX_UIScene::~SIX_UIScene()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,NOTIFY_CLOSEWND_CLICKED);

	SIXLog("~SIX_UIScene[0x%08X].m_Scene[0x%08X].retainCount[%d]",this,m_Scene,m_Scene->retainCount());
	CC_SAFE_DELETE(m_UIManager);
}

void SIX_UIScene::InitUIMgr()
{
	SIXLog("场景初始化...");
	m_UIManager = new SIX_UIMgr();
	m_UIManager->SetParent(this);
	m_pFlashBox = 0;
	m_pCloseBox = 0;
	m_pLogic = 0;
	SIXLog("场景初始化...OK!");

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SIX_UIScene::OnNotifyCloseWndClicked),NOTIFY_CLOSEWND_CLICKED,0);
}

//SIX_ClientLogic *SIX_UIScene::GetClientLogic()
//{
//	return SIX_ClientLogic::GetInstance();
//}

void SIX_UIScene::ShowCloseBox(bool bShow)
{
	// 要检查是否在游戏场景
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return;
	if (!pScene->getChildren())
		return;
	CCObject *pObject = pScene->getChildren()->objectAtIndex(0);
	if (!pObject)
		return;

	if (!m_pCloseBox)
	{
		m_pCloseBox = SIX_DisconnectBox::Create(0.0,0.0,ccc4(0,0,0,0),409,254);
		m_pCloseBox->InitMask(ccc4(0,0,0,128));
	}

	if (bShow)
	{
		// 显示背景+确定按妞
		m_pCloseBox->backgroundWithFile("tipbox.png");
		m_pCloseBox->buttonSubmitWithFileCell("Common/Button/return.png",3);
		m_pCloseBox->GetBtnSubmit()->setPosition(ccp(270,35));
		// 显示文字提示
		m_pCloseBox->setTextAttribute(20,80,369,140,"宋体",12);
		m_pCloseBox->setString(SIX_Utility::GetInstance()->G2U("与服务器的连接已断开，请重新登录！").c_str());
		// 设置可拖拽
		m_pCloseBox->setAllowDragged(true);
	}
	else
	{
		m_pCloseBox->UnExec();
	}

	m_pCloseBox->Show(bShow);
}

void SIX_UIScene::ShowFlashBox(SIX_ClientBase *pLogic,bool bShow)
{
	// 要检查是否在游戏场景
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return;
	if (!pScene->getChildren())
		return;
	CCObject *pObject = pScene->getChildren()->objectAtIndex(0);
	if (!pObject)
		return;

	m_pLogic = pLogic;

	if (!m_pFlashBox)
	{
		m_pFlashBox = SIX_DisconnectBox::Create(0.0,0.0,ccc4(0,0,0,0),409,254);
		m_pFlashBox->InitMask(ccc4(0,0,0,128));
	}

	if (bShow)
	{
		// 显示Loading动画(30s)
		m_pFlashBox->setLoadingAttribute(140.0f,120.0f,30.0f,this,callfunc_selector(SIX_UIScene::onDisconnectCallback));
		// 显示文字提示
		m_pFlashBox->setTextAttribute(120,80,369,20,"宋体",12);
		m_pFlashBox->setString(SIX_Utility::GetInstance()->G2U("通讯中断，正在尝试重连...").c_str());
		// 设置不可拖拽
		m_pFlashBox->setAllowDragged(false);
	}
	else
	{
		m_pFlashBox->UnExec();
	}

	m_pFlashBox->Show(bShow);
}

void SIX_UIScene::onDisconnectCallback()
{
	if (m_pLogic)
		m_pLogic->setReconnect(false);
	//ShowCloseBox(true);
}
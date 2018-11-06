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
	SIXLog("������ʼ��...");
	m_UIManager = new SIX_UIMgr();
	m_UIManager->SetParent(this);
	m_pFlashBox = 0;
	m_pCloseBox = 0;
	m_pLogic = 0;
	SIXLog("������ʼ��...OK!");

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SIX_UIScene::OnNotifyCloseWndClicked),NOTIFY_CLOSEWND_CLICKED,0);
}

//SIX_ClientLogic *SIX_UIScene::GetClientLogic()
//{
//	return SIX_ClientLogic::GetInstance();
//}

void SIX_UIScene::ShowCloseBox(bool bShow)
{
	// Ҫ����Ƿ�����Ϸ����
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
		// ��ʾ����+ȷ�����
		m_pCloseBox->backgroundWithFile("tipbox.png");
		m_pCloseBox->buttonSubmitWithFileCell("Common/Button/return.png",3);
		m_pCloseBox->GetBtnSubmit()->setPosition(ccp(270,35));
		// ��ʾ������ʾ
		m_pCloseBox->setTextAttribute(20,80,369,140,"����",12);
		m_pCloseBox->setString(SIX_Utility::GetInstance()->G2U("��������������ѶϿ��������µ�¼��").c_str());
		// ���ÿ���ק
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
	// Ҫ����Ƿ�����Ϸ����
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
		// ��ʾLoading����(30s)
		m_pFlashBox->setLoadingAttribute(140.0f,120.0f,30.0f,this,callfunc_selector(SIX_UIScene::onDisconnectCallback));
		// ��ʾ������ʾ
		m_pFlashBox->setTextAttribute(120,80,369,20,"����",12);
		m_pFlashBox->setString(SIX_Utility::GetInstance()->G2U("ͨѶ�жϣ����ڳ�������...").c_str());
		// ���ò�����ק
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
#include "RegisterLayer.h"
#include "SkinControls.h"
#include "LoginLayer.h"

static int k_Account_Tag = 0;
static int k_password_1_Tag = 1;
static int k_password_2_Tag = 1;

USING_NS_CC;

RegisterLayer::RegisterLayer(void)
{
}


RegisterLayer::~RegisterLayer(void)
{
}

void RegisterLayer::onEnter()
{
	CCLayer::onEnter();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite * bg = CCSprite::create("bg/bg.jpg");
	bg->setPosition(ccp(size.width/2, size.height/2));
	addChild(bg);

	CCLabelTTF * loadPrompt = CCLabelTTF::create("REGISTER", "ËÎÌå", 40);
	loadPrompt->setPosition(ccp(size.width/2, size.height*8.5/10));
	addChild(loadPrompt);

	int nX = size.width/2;
	int nY = size.height*6/10;
	//TextFieldTTFDefaultTest * pAccount = EditBox::create(CCRect(nX, size.height*6/10, 200, 40));
	//TextFieldTTFActionTest * pPassword1 = EditBox::createAnimation(CCRect(nX, size.height*6.8/10, 200, 40));
	//TextFieldTTFActionTest * pPassword2 = EditBox::createAnimation(CCRect(nX, size.height*7.6/10, 200, 40));
	//this->addChild( pAccount, 1, k_Account_Tag );
	//this->addChild( pPassword1, 1, k_password_1_Tag );
	//this->addChild( pPassword2, 1, k_password_2_Tag );
	m_peditAccount = UI::createEditBox(this, CCRect(nX, size.height*7.6/10, 200, 40), "login/white_edit.png", "Name:", 8);
	addChild( m_peditAccount );
	m_peditPW = UI::createEditBox(this, CCRect(nX, size.height*6.8/10, 200, 40), "login/white_edit.png", "PW:", 8, "Î¢ÈíÑÅºÚ", 20, kEditBoxInputFlagPassword, kEditBoxInputModeSingleLine);
	addChild( m_peditPW );
	m_peditAgainPW = UI::createEditBox(this, CCRect(nX, size.height*6/10, 200, 40), "login/white_edit.png", "Again PW:", 8, "Î¢ÈíÑÅºÚ", 20, kEditBoxInputFlagPassword, kEditBoxInputModeSingleLine);
	addChild( m_peditAgainPW );

	CCLabelTTF *titleRegister = CCLabelTTF::create("Register", "Marker Felt", 30);
	//titleRegister->setColor(ccc3(159, 168, 176)); 
	addChild( UI::createButton(this, CCPoint(nX-65, nY - 100), cccontrol_selector(RegisterLayer::RegisterCallback), titleRegister, "login/Button1.png", "login/Button2.png", NULL, NULL) );

	CCLabelTTF *titleCancel = CCLabelTTF::create("Cancel", "Marker Felt", 30);
	//titleCancel->setColor(ccc3(159, 168, 176)); 
	addChild( UI::createButton(this, CCPoint(nX+65, nY - 100), cccontrol_selector(RegisterLayer::CancelCallback), titleCancel, "login/Button1.png", "login/Button2.png", NULL, NULL) );
}

void RegisterLayer::onExit()
{
	CCLayer::onExit();
}

void RegisterLayer::editBoxReturn(CCEditBox* editBox)
{
	;
}

void RegisterLayer::RegisterCallback(CCObject* pSender, cocos2d::extension::CCControlEvent controlEvent)
{
}

void RegisterLayer::CancelCallback(CCObject* pSender, cocos2d::extension::CCControlEvent controlEvent)
{
	CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.0f, LoginLayer::scene(), ccBLACK) );
}

CCScene * RegisterLayer::scene()
{
	CCScene * pScene = CCScene::create();
	RegisterLayer * pRegister = new RegisterLayer;
	pScene->addChild( pRegister );
	pRegister->release();
	return pScene;
}

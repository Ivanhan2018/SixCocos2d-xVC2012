#include "LoginLayer.h"
#include "SkinControls.h"
#include "LoadingLayer.h"
#include "RegisterLayer.h"
#include "HallLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
//static int k_Default_Tag = 0;
//static int k_Action_Tag = 1;

CCScene* LoginLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        LoginLayer *layer = LoginLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        CCSize size = CCDirector::sharedDirector()->getVisibleSize();

        CCSprite* pSprite = CCSprite::create("login/bg.jpg");
        CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(pSprite, 0);

		int nX = size.width*3/4;
		int nY = size.height*6/10;
		//TextFieldTTFDefaultTest * pDefaultInput = UI::createEditBox(CCRect(nX, size.height*5/10, 200, 40));
		//TextFieldTTFActionTest * pActionInput = EditBox::createAnimation(CCRect(nX, nY, 200, 40));
		//this->addChild( pDefaultInput, 1, k_Default_Tag );
		//this->addChild( pActionInput, 1, k_Action_Tag );

		m_peditAccount = UI::createEditBox(this, CCRect(nX, nY, 200, 40), "login/white_edit.png", "Name:", 8);
		addChild( m_peditAccount );
		m_peditPW = UI::createEditBox(this, CCRect(nX, size.height*5/10, 200, 40), "login/white_edit.png", "PW:", 8, "Î¢ÈíÑÅºÚ", 20, kEditBoxInputFlagPassword, kEditBoxInputModeSingleLine);
		addChild( m_peditPW );
			
		CCLabelTTF *titleButton = CCLabelTTF::create("Login", "Î¢ÈíÑÅºÚ", 20);
		//titleButton->setColor(ccc3(159, 168, 176));
		addChild( UI::createButton(this, CCPoint(nX-65, nY - 120), cccontrol_selector(LoginLayer::LogoinCallback), titleButton, "login/Button1.png", "login/Button2.png", NULL, NULL) );
		CCLabelTTF *titleRegister = CCLabelTTF::create("Register", "Î¢ÈíÑÅºÚ", 20);
		//titleRegister->setColor(ccc3(159, 168, 176)); 
		addChild( UI::createButton(this, CCPoint(nX+65, nY - 120), cccontrol_selector(LoginLayer::RegisterCallback), titleRegister, "login/Button1.png", "login/Button2.png", NULL, NULL) );

        bRet = true;
    } while (0);

    return bRet;
}

void LoginLayer::editBoxReturn(CCEditBox* editBox)
{
	;
}

void LoginLayer::RegisterCallback(CCObject* pSender, CCControlEvent controlEvent)
{
	CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.0f, RegisterLayer::scene(), ccBLACK) );
}

void LoginLayer::LogoinCallback(CCObject* pSender, CCControlEvent controlEvent)
{
	//TextFieldTTFDefaultTest * pDefault = (TextFieldTTFDefaultTest *)getChildByTag( k_Default_Tag );
	//TextFieldTTFActionTest * pAction = (TextFieldTTFActionTest *)getChildByTag( k_Action_Tag );
	//std::string strContent = pDefault->getAllContent();
	//std::string strContent1 = pAction->getAllContent();

	//LoadingLayer::scene();//tmp
	HallLayer::scene(); //del
}
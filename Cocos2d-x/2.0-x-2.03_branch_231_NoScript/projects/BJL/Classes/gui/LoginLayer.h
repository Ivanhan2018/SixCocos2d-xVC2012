#ifndef __LOGINLAYER_H__
#define __LOGINLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ans/BaseObject.h"
using namespace cocos2d::extension;

USING_NS_CC;
#define P_SCREEN								(CCDirector::sharedDirector()->getWinSize())
// add by mojunxin important
#define FRAME_CENTER_X       (P_SCREEN.width/2)
#define FRAME_CENTER_Y       (P_SCREEN.height/2)

#define GAP_X					30
#define GAP_Y					30

#define NOTICE_CENTER_X       (143+GAP_X)
#define NOTICE_CENTER_Y       (201+GAP_Y)
#define NOTICE_TEXT_CENTER_X       (50)
#define NOTICE_TEXT_UP       (340)

#define LOGIN_CENTER_X       (P_SCREEN.width-192-50)
#define LOGIN_CENTER_Y       (145+110)

//#define REMEMBER_CENTER_X       (FRAME_CENTER_X+52)
#define REMEMBER_CENTER_X       (LOGIN_CENTER_X-90)
#define REMEMBER_CENTER_Y       (LOGIN_CENTER_Y-10)
#define AUTOMATIC_CENTER_X       (REMEMBER_CENTER_X+186)
#define AUTOMATIC_CENTER_Y       (REMEMBER_CENTER_Y)

// �ʺ�
#define ACCOUNT_CENTER_X        (LOGIN_CENTER_X-180)
#define ACCOUNT_CENTER_Y        (LOGIN_CENTER_Y+105)
#define ACCOUNT_TEXT_CENTER_X   (ACCOUNT_CENTER_X+80)
#define ACCOUNT_TEXT_CENTER_Y   (ACCOUNT_CENTER_Y)
#define TABLE_CENTER_X          (ACCOUNT_CENTER_X-60)
#define TABLE_CENTER_Y          (ACCOUNT_CENTER_Y)

// list button
#define LIST_CENTER_X           (FRAME_CENTER_X+150)
#define LIST_CENTER_Y           (FRAME_CENTER_Y-33)
// ����
#define PASSWORD_CENTER_X       (ACCOUNT_CENTER_X)
#define PASSWORD_CENTER_Y       (289)
#define PASSWORD_TEXT_CENTER_X  (ACCOUNT_TEXT_CENTER_X)
#define PASSWORD_TEXT_CENTER_Y  (PASSWORD_CENTER_Y)

#define LOGON_CENTER_X          (LOGIN_CENTER_X)
#define LOGON_CENTER_Y          (LOGIN_CENTER_Y-75)
#define REGISTER_CENTER_X       (LOGON_CENTER_X+100)
#define REGISTER_CENTER_Y       (65)
#define GUEST_CENTER_X          (LOGON_CENTER_X-100)
#define GUEST_CENTER_Y          (REGISTER_CENTER_Y)

typedef enum
{
	//��
	FLTAG_Zero				= 0,				//default
	FLTAG_AccountsTex		= 1,				//�ʺſ�
	FLTAG_PassWordTex		= 2,				//�����
	FLTAG_TableView			= 3,				//�ʺ��б�table
	FLTAG_ClearAccountsBtn	= 4,				//�ʺŰ�ťx
	FLTAG_ClearPassWordBtn	= 5,				//���밴ťx
	FLTAG_ListBtn			= 6,				//�б�ť
	FLTAG_LogonBtn			= 7,				//��¼��ť
	FLTAG_RememberPW		= 8,				//��ס���밴ť
	FLTAG_RememberLogon		= 9,				//�Զ���¼��ť
	FLTAG_ACPWFont			= 10,				//��ס��������
	FLTAG_AUTOFont			= 11,				//�Զ���¼����
	FLTAG_RememberPWYES		= 12,				//��ס����yes
	FLTAG_RememberLogonYES	= 13,				//�Զ���¼yes
	
	//��
	FLTAG_Viewbg			= 20,				//��ǰ����
	FLTAG_Loadbg			= 21,				//��¼����
}FLTAG;

class LoginLayer : public CCLayer, public CCEditBoxDelegate
{
public:
    
    LoginLayer();
    ~LoginLayer();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init(bool bLogin);

    //virtual void onEnter();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::extension::CCEditBox * userInput;
    cocos2d::extension::CCEditBox * passwordInput;
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    //CREATE_FUNC(LoginLayer);
    void onLogin(CCObject* obj);								//��½
    void onRegist(CCObject * obj);								//ע��
    void GuestLogon(CCObject * obj);							//�һ�����
	void changePassWord(CCObject* obj);							//�޸�����
    void back(CCObject * obj);									//����
    void setIsfaildLogin(bool mIsFaildLogin);					//��½ʧ��
    void onAnsLoginFinish(CCObject* obj);						//��½���
    void onLoginFaild(CCObject* obj);							//��½ʧ��
    void onFindPassword(CCObject* obj);							//�����һ�
	void setLogin(bool loginBool);
	void toFreeLayer(CCObject* obj);
    //void setLogin(bool bLogin) { m_bLogin = bLogin; }  //�����Ƿ�ֱ�ӵ�½
    std::string createAccount();
	std::string createPassword();
    static LoginLayer* create(bool bLogin = true)
    {
        LoginLayer *pRet = new LoginLayer(); 
        if (pRet && pRet->init(bLogin)) 
        { 
            pRet->autorelease();
            return pRet; 
        } 
        else
        { 
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
	void setBoolFrom(bool b);

    virtual void editBoxEditingDidBegin(CCEditBox* editBox) {};
    virtual void editBoxEditingDidEnd(CCEditBox* editBox) {};
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text) {};
	virtual void editBoxReturn(CCEditBox* editBox){};
private:
    CCMenu* m_pLoginMenu;       //��½
    CCMenu* m_pRegisterMenu;    //ע��
	CCSize winSize;
	bool m_bLogin;
	bool m_from; //�ж��Ǵ��ĸ�������뵽�ĵ�½���棬����Ǵ���������л����룬�򷵻ص����ý��棬����ǴӲ˵�������룬�򷵻ص�������Ĭ��ΪFALSE�������ý�
	CCMenuItemSprite * m_pDengluItemSprite;
};

#endif // __HELLOWORLD_SCENE_H__

#ifndef __ModifyPassWord_SCENE_H__
#define __ModifyPassWord_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class ModifyPassWord : public CCLayer
{
public:
    
    ModifyPassWord();
    ~ModifyPassWord();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init(bool bLogin);

    //virtual void onEnter();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    
    cocos2d::extension::CCEditBox * orginPasswordInput;
    cocos2d::extension::CCEditBox * modifyPasswordInput;
	cocos2d::extension::CCEditBox * surePasswordInput;
   
    void clickButton(CCObject* obj);							//确定修改
	void rBack(CCObject* obj);									//返回

	void onChangePassWordResult(CCObject* obj);					//修改密码返回

	bool isLegal(string str);

	void toFreeLayer(CCObject *obj);

    
    static ModifyPassWord* create(bool bLogin = true)
    {
        ModifyPassWord *pRet = new ModifyPassWord(); 
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

	virtual void keyBackClicked(void);					//手机返回按钮

private:
    CCMenu* m_pLoginMenu;       //登陆
    CCMenu* m_pRegisterMenu;    //注册
};

#endif // __HELLOWORLD_SCENE_H__

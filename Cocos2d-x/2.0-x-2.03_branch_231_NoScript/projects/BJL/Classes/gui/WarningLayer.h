#ifndef __Game__WarningLayler__
#define __Game__WarningLayler__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include "gui/PromptBox.h"
#include <iostream>
#include "cocos2d.h"

class WarningLayer : public cocos2d::CCLayer
{
private:
	CCSize winSize;
	int signInDays;
	CCSprite *signInImage;
	CCArray *awardImage;
	CCMenu *signInMenu;
	PromptBox* promptBox;
	bool cancelOrNot;
private:
	/**保存是否点击到勾中**/

public:
	WarningLayer();
	~WarningLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(WarningLayer);
	void setSignInDays(int days);
	void requestSignInDays();					//网页查询签到天数
	void signIn();								//签到
	void cancelHttpRequest(CCObject *obj);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);//查询签到天数回到
	void onSignInCompleted(cocos2d::CCNode *sender, void *data);//签到回调
	virtual void keyBackClicked(void);					//手机返回按钮
public:
	void dismiss(cocos2d::CCObject *obj);
	void onGetTaskAward(CCObject* obj);
};
#endif  //__Game__WarningLayler__
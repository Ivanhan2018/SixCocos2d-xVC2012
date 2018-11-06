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
	/**�����Ƿ���������**/

public:
	WarningLayer();
	~WarningLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(WarningLayer);
	void setSignInDays(int days);
	void requestSignInDays();					//��ҳ��ѯǩ������
	void signIn();								//ǩ��
	void cancelHttpRequest(CCObject *obj);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);//��ѯǩ�������ص�
	void onSignInCompleted(cocos2d::CCNode *sender, void *data);//ǩ���ص�
	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
public:
	void dismiss(cocos2d::CCObject *obj);
	void onGetTaskAward(CCObject* obj);
};
#endif  //__Game__WarningLayler__
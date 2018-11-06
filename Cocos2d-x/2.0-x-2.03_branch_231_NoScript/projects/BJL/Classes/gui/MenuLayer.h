#ifndef __Game__MenuLayler__
#define __Game__MenuLayler__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"

#include "RegistLayer.h"
class MenuLayer : public cocos2d::CCLayer
{
private:
	CCMenuItemSprite *musicItem;
	CCMenuItemSprite *effectItem;
	bool hasEffect;
	bool hasMusic;
public:
	CCMenu *pButtonMenu;
public:
	MenuLayer();
	~MenuLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();

	CREATE_FUNC(MenuLayer);

public:
	void permitButtonClick();							//����ť��
	void forbidButtonClick();							//��ֹ��ť��
	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
	void pressMusicItem(CCObject* obj);					//��Ϸ��������
	void pressEffectItem(CCObject* obj);					//��Ϸ��������
};
#endif  //__Game__MenuLayler__
#ifndef __Game__ChoosePlayerPhotoLayer__
#define __Game__ChoosePlayerPhotoLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class ChoosePlayerPhotoLayer : public cocos2d::CCLayer
{

private:
	/**确定选择的标志**/
	CCSprite *m_choose_log;
public:
	ChoosePlayerPhotoLayer();
	~ChoosePlayerPhotoLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(ChoosePlayerPhotoLayer);
public:
	
	//void choose1(cocos2d::CCObject *obj);
	//void choose2(cocos2d::CCObject *obj);
	//void choose3(cocos2d::CCObject *obj);
	//void choose4(cocos2d::CCObject *obj);
	//void choose5(cocos2d::CCObject *obj);
	//void choose6(cocos2d::CCObject *obj);
	//void choose7(cocos2d::CCObject *obj);
	//void choose8(cocos2d::CCObject *obj);
	void dismiss(cocos2d::CCObject *obj);
	
};
#endif  //__Game__ChoosePlayerPhotoLayer__
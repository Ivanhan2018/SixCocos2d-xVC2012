#ifndef __Game__FreeLayer__
#define __Game__FreeLayer__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"

#include "common/GlobalDef.h"
#include "common/CMD_Plaza.h"

class FreeLayer : public cocos2d::CCLayer
{

public:
	FreeLayer();
	~FreeLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(FreeLayer);


	virtual void keyBackClicked(void);					//手机返回按钮

	void onGetDownData(CCObject* obj);
	void getDownAwardOver(CCObject* obj);
public:

	void dismiss(cocos2d::CCObject *obj);
	void downLoad(cocos2d::CCObject *obj);

	SDownloadGamePrize_Returnn returnData;

};
#endif  //__Game__FreeLayer__
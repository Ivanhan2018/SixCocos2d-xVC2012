//
//  PesentCoins.h
//  Game
//
//  Created by 罗敏 on 13-7-10.
//
//

#ifndef __Game__ExitLayer__
#define __Game__ExitLayer__

#include "cocos2d.h"
#include "common/CocosUnits.h"
#include "cocos-ext.h"
USING_NS_CC;

class ExitLayer : public CCLayer {
public:
    CREATE_FUNC(ExitLayer);
	virtual bool init();
    ExitLayer();
    ~ExitLayer();

	void onOverRegist(CCObject* obj);
	void onFreeGetCoins(CCObject* obj);

	void close(CCObject* obj);
public:
    void resumeGame(CCObject* obj);		//继续游戏
	void exitGame(CCObject* obj);		//退出游戏
private:

};

#endif /* defined(__Game__PesentCoins__) */

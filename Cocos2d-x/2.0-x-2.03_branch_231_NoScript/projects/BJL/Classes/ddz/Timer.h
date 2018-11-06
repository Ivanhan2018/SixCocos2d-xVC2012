//  [3/26/2014 xieyi]
#ifndef __TIMER__
#define __TIMER__

#include "cocos2d.h"
#include "DDZRes.h"
#include "SceneData.h"
USING_NS_CC;
using namespace cocos2d;
class CCtimeCallBack:public CCInteger
{
public:
	CCtimeCallBack(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCtimeCallBack);
	Game_State m_gameState;
	int				m_timeKey;
};
class Timer : public CCNode
{
public :
	Timer();
	~Timer();
	CREATE_FUNC(Timer);
	virtual bool init();
	void time_schedule(float t);		//时间回调
	int m_time;
	void start(int userId, int t,Game_State gameState,int key);	//运行计时器
	CCLabelAtlas * m_number;			//计时器数字
	Game_State m_gameState;				//游戏状态
	int				m_timeKey;
	int				m_UserID;
	CCSprite *m_nikeSprite;

	void AddObject();
	void RemoveObject();

	void setCCteefTag(CCObject *obj); //空闲
	void setCardTalayer(CCObject *obj); //开牌  
	void setPlaceScore(CCObject *obj);  //下注
private:
	CCNode * g_timerNode;
};

#endif
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
	void time_schedule(float t);		//ʱ��ص�
	int m_time;
	void start(int userId, int t,Game_State gameState,int key);	//���м�ʱ��
	CCLabelAtlas * m_number;			//��ʱ������
	Game_State m_gameState;				//��Ϸ״̬
	int				m_timeKey;
	int				m_UserID;
	CCSprite *m_nikeSprite;

	void AddObject();
	void RemoveObject();

	void setCCteefTag(CCObject *obj); //����
	void setCardTalayer(CCObject *obj); //����  
	void setPlaceScore(CCObject *obj);  //��ע
private:
	CCNode * g_timerNode;
};

#endif
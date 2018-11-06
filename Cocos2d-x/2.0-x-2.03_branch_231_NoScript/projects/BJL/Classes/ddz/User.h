//  [3/26/2014 xieyi]
#ifndef __USER__
#define __USER__

#include "cocos2d.h"
#include "DDZRes.h"
USING_NS_CC;

class User : public CCLayer
{
public:
	User();
	~User();
	virtual bool init();
	CREATE_FUNC(User);
	void setUserIcon(int gender);
	void setLordIcon(bool blord);
	void setIsOnline(bool isOnline);//设置是否在线
	void setUserInfor(char* name,int gold,char* huafeidian);
	void userIconCallBack(CCObject* obj);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

	void  eyeCallUp(CCObject* _obj);
	//void setSpt
private:
	CCSprite*					 m_userInfor;//玩家信息
	CCSprite*					 m_userEye;
	CC_SYNTHESIZE(CCSprite*,m_userIcon,userIcon);
	CC_SYNTHESIZE(CCPoint,m_pos,IconPos);
	CC_SYNTHESIZE(int ,m_gender,Gender);//玩家性别,1表示男
	CC_SYNTHESIZE(bool,m_isDiZhu,IsDiZhu);//是不是地主

	CC_SYNTHESIZE(int,m_userId,UserId);//用户Id；
	CC_SYNTHESIZE(int,m_score,Score);//用户分数（也就是金币）
	CC_SYNTHESIZE(int,m_goldEggs,GooldEggs);//话费点
	bool        m_isOnline;
	bool        m_isOut;
	int		  m_UserSptKey;				//12玩家男女，34 地主男女,56农民男女
};

#endif
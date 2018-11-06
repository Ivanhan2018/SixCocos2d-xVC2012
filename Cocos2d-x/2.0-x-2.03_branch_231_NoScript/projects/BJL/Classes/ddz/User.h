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
	void setIsOnline(bool isOnline);//�����Ƿ�����
	void setUserInfor(char* name,int gold,char* huafeidian);
	void userIconCallBack(CCObject* obj);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

	void  eyeCallUp(CCObject* _obj);
	//void setSpt
private:
	CCSprite*					 m_userInfor;//�����Ϣ
	CCSprite*					 m_userEye;
	CC_SYNTHESIZE(CCSprite*,m_userIcon,userIcon);
	CC_SYNTHESIZE(CCPoint,m_pos,IconPos);
	CC_SYNTHESIZE(int ,m_gender,Gender);//����Ա�,1��ʾ��
	CC_SYNTHESIZE(bool,m_isDiZhu,IsDiZhu);//�ǲ��ǵ���

	CC_SYNTHESIZE(int,m_userId,UserId);//�û�Id��
	CC_SYNTHESIZE(int,m_score,Score);//�û�������Ҳ���ǽ�ң�
	CC_SYNTHESIZE(int,m_goldEggs,GooldEggs);//���ѵ�
	bool        m_isOnline;
	bool        m_isOut;
	int		  m_UserSptKey;				//12�����Ů��34 ������Ů,56ũ����Ů
};

#endif
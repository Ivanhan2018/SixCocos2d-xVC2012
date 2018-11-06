#pragma once
#include "cocos2d.h"
#include "Global.h"
class GameScene;
USING_NS_CC;
class Poker : public CCSprite,public CCTouchDelegate
{
public:
	Poker();
	~Poker();
	static Poker* create(const char *pszFileName, const CCRect& rect);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	void showFront();//��ʾ����
	void showLast();//��ʾ����
	Poker* copy();//����
	void setTouchPriority(int num);
	void SelectPkLuTou();//���ѡ�����ƾ�¶��ͷ
	void SelectPkSuoTou();//���ѡ�����ƾ���ͷ
private:
	CC_SYNTHESIZE(bool,m_isSelect,Select);//�Ƿ���ѡ
	CC_SYNTHESIZE(GameScene*,m_gameMain,GameMain);
	CC_SYNTHESIZE(bool,m_isDianJi,DianJi);//�Ƿ��ܱ����
	CC_SYNTHESIZE(int,m_huaSe,HuaSe);//��ɫ
	CC_SYNTHESIZE(int,m_num,Num);//��ֵ
};

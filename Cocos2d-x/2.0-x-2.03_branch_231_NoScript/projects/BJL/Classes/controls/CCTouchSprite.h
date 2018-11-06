#ifndef __CCTOUCHSPRITE_H__
#define __CCTOUCHSPRITE_H__

#include "cocos2d.h"

class CCTouchSprite : public cocos2d::CCSprite ,public cocos2d::CCTouchDelegate
{
public:
	CCTouchSprite();
	~CCTouchSprite();

	static CCTouchSprite* createWithPic(const char *fileName, int row, int cell); //��̬�������ڴ��Զ��ͷţ�
	static CCTouchSprite* createWithPic(const char *fileName, int row, int cell, cocos2d::CCObject *rec, cocos2d::SEL_CallFuncN selector); //��̬�������ڴ��Զ��ͷţ�
	static CCTouchSprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame,int row, int cell, cocos2d::CCObject *rec,cocos2d::SEL_CallFuncN selector);  //��̬�������ڴ��Զ��ͷţ�

	//void myInit();//�Զ����ʼ������
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

	CC_SYNTHESIZE(int, rowIndex, RowIndex);//sprite�ڵڼ���
	
	CC_SYNTHESIZE(int, cellIndex, CellIndex);//sprite�ڵڼ���

private:
	//�ж��Ƿ�����ť
	bool isClickSprite(cocos2d::CCTouch* pTouch);
protected:
	cocos2d::SEL_CallFuncN c_pfnSelector;
	cocos2d::CCObject* m_pListener;
private:
	//�ж��Ƿ��ƶ�
	bool m_bMovedSprite;
	bool m_bDoubleClick;

};

#endif
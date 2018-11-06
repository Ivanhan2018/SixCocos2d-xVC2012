#ifndef __CCTOUCHSPRITE_H__
#define __CCTOUCHSPRITE_H__

#include "cocos2d.h"

class CCTouchSprite : public cocos2d::CCSprite ,public cocos2d::CCTouchDelegate
{
public:
	CCTouchSprite();
	~CCTouchSprite();

	static CCTouchSprite* createWithPic(const char *fileName, int row, int cell); //静态创建（内存自动释放）
	static CCTouchSprite* createWithPic(const char *fileName, int row, int cell, cocos2d::CCObject *rec, cocos2d::SEL_CallFuncN selector); //静态创建（内存自动释放）
	static CCTouchSprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame,int row, int cell, cocos2d::CCObject *rec,cocos2d::SEL_CallFuncN selector);  //静态创建（内存自动释放）

	//void myInit();//自定义初始化函数
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

	CC_SYNTHESIZE(int, rowIndex, RowIndex);//sprite在第几行
	
	CC_SYNTHESIZE(int, cellIndex, CellIndex);//sprite在第几列

private:
	//判断是否点击按钮
	bool isClickSprite(cocos2d::CCTouch* pTouch);
protected:
	cocos2d::SEL_CallFuncN c_pfnSelector;
	cocos2d::CCObject* m_pListener;
private:
	//判断是否移动
	bool m_bMovedSprite;
	bool m_bDoubleClick;

};

#endif
/***********************************************
Name：SIX_UILayer
Desc：继承CCLayerColor，实现了层级锁定，可以用于
	  拦截Touch事件。
Auth：Cool.Cat@2013-03-28
Reco：Cool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <GUI/CCControlExtension/CCControlExtensions.h>
#include <GUI/CCScrollView/CCScrollView.h>
#include <GUI/CCScrollView/CCTableView.h>
#include <GUI/CCEditBox/CCEditBox.h>
#include <SIX_Interface.h>
#include <SIX_EditBox.h>

USING_NS_CC;
//USING_NS_CC_EXT;

class SIX_EditBox;

class SIX_UILayer:public CCLayerColor
{
public:
	SIX_UILayer(bool bTouchThroughForbidden=false,int nPriority=0,bool bRedrawBorder=false,bool bScissor=false);
	virtual ~SIX_UILayer();
public:
    /** creates a CCLayer with color, width and height in Points */
    static SIX_UILayer * create(const ccColor4B& color, float width, float height,bool bTouchThroughForbidden=false,int nPriority=0,bool bRedrawBorder=false,bool bScissor=false);
    /** creates a CCLayer with color. Width and height are the window size. */
    static SIX_UILayer * create(const ccColor4B& color,bool bTouchThroughForbidden=false,int nPriority=0,bool bRedrawBorder=false,bool bScissor=false);

    virtual bool init();
    /** initializes a CCLayer with color, width and height in Points */
    virtual bool initWithColor(const ccColor4B& color, float width, float height);
    /** initializes a CCLayer with color. Width and height are the window size. */
    virtual bool initWithColor(const ccColor4B& color);
protected:
	virtual void draw();
	virtual void visit();
	void beforeDraw();
	void afterDraw();
public:
	virtual void registerWithTouchDispatcher();
 
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccWindowMSG(CCTouch *pTouch, CCEvent *pEvent, int nType);

	virtual int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);

	virtual bool onTextFieldAttachWithIME(SIX_EditBox * pSender){return true;};
	virtual bool onTextFieldDetachWithIME(SIX_EditBox * pSender){return true;};
public:
	void *GetInterface(const char *pstrName);

	// 设置优先级
	void setPriority(int Priority);
	// 获取优先级
	int getPriority();

	// 提升优先级
	void PriorityPromote();
	// 降低优先级
	void PriorityReduce();

	// 是否拦截触碰事件
	void setSwallowsTouches(bool bSwallowsTouches);
	bool getSwallowsTouches();

	// 是否响应触碰事件
	void setTouchEventPause(bool bPause);
	bool getTouchEventPause();
	
	bool getRedrawBorder();
	void setRedrawBorder(bool bRedrawBorder);

	ccColor4B getBorderColor();
	void setBorderColor(const ccColor4B& color);
protected:
	bool m_bScissor;
	bool m_RedrawBorder;
	ccColor4B m_BorderColor;
	bool m_ForbiddenTouch;
	int m_nPriority;
};
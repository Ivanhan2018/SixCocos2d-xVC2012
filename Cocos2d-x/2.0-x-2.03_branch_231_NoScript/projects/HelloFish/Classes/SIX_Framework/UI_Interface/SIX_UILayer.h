/***********************************************
Name��SIX_UILayer
Desc���̳�CCLayerColor��ʵ���˲㼶��������������
	  ����Touch�¼���
Auth��Cool.Cat@2013-03-28
Reco��Cool.Cat@2013-04-24
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

	// �������ȼ�
	void setPriority(int Priority);
	// ��ȡ���ȼ�
	int getPriority();

	// �������ȼ�
	void PriorityPromote();
	// �������ȼ�
	void PriorityReduce();

	// �Ƿ����ش����¼�
	void setSwallowsTouches(bool bSwallowsTouches);
	bool getSwallowsTouches();

	// �Ƿ���Ӧ�����¼�
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
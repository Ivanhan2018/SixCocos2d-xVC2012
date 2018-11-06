/***********************************************
Name：SIX_PopWnd
Desc：通用弹出框，包含确认、取消、关闭按钮及拖拽
Auth：Cool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "SIX_UILayer.h"
#include "SIX_Cursor.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PRIORITY_STEP		-10
#define ZORDER_STEP			10

enum BTN_TAG {
	BTN_SUBMIT = -10,
	BTN_CANCEL = -20,
	BTN_CLOSE = -30
};

class SIX_PopWnd:public SIX_UILayer
{
public:
	virtual ~SIX_PopWnd();
public:
	static SIX_PopWnd *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
	// 当前可见的弹出窗口数目
	static int GetPopWndCount();
	static void setPopWndCount(int nCount);
public:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	// 重写SIX_PopWnd消息响应优先级策略，用于多窗口层级消息遮罩响应。
	// Cool.Cat@2013-07-12
	virtual void onShow();
	virtual void onHide();
	virtual void onShowFinished(){};
	virtual void onHideFinished(){};

	// 背景九宫格
	void backgroundWithSpriteFrameName(const char *pszSpriteFrameName);
	void backgroundWithFile(const char *file);
	
	// 按钮九宫格
	// 从帧名加载
	void buttonSubmitWithSpriteFrameName(const char *pszSpriteFrameName);
	void buttonCancelWithSpriteFrameName(const char *pszSpriteFrameName);
	void buttonCloseWithSpriteFrameName(const char *pszSpriteFrameName);
	// 从文件加载
	void buttonSubmitWithFile(const char *file,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
	void buttonCancelWithFile(const char *file,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
	void buttonCloseWithFile(const char *file,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
	// 从文件加载并均分，实现四态按钮
	void buttonSubmitWithFileCell(const char *file,int cell,bool Hor=true);
	void buttonCancelWithFileCell(const char *file,int cell,bool Hor=true);
	void buttonCloseWithFileCell(const char *file,int cell,bool Hor=true);

	// 根据给与的间隔宽度自动计算底部Yes/No按钮位置
	void AutoCaclBtnPosWidthYesOrNo(float offsetX,float offsetY);

	// 窗口显示状态
	bool IsShow();

	// 遮罩层
	virtual void InitMask(const ccColor4B& color,int nPriority=-129,bool bRedrawBorder=false);
	virtual void CreateMask();
	virtual void ReleaseMask();
	// 设置弹出窗口大小
	virtual void setContentSize(CCSize size);
	// 显示/隐藏窗口
	virtual void Show(bool IsShow=true);

	void ShowActionCallBack(CCNode *node);

	// 设置可否拖拽
	void setAllowDragged(bool bAllowDragged);
	bool getAllowDragged();

	// 获取
	CCControlButton *GetBtnSubmit(){return pSubmit;}
	CCControlButton *GetBtnCancel(){return pCancel;}
	CCControlButton *GetBtnClose(){return pClose;}
public:
	virtual bool OnSubmit(){return true;};
	virtual bool OnCancel(){return true;};
	virtual bool OnClose(){return true;};
	virtual bool OnBtn(CCObject*,int tag){return true;}
public:
	CCControlButton *CreateButtonWithFrameName(const char *pszSpriteFrameName);
	CCControlButton *CreateButtonWithFile(const char *file,CCRect rc,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
	CCControlButton *CreateButtonWithFileCell(const char *file,int cell,bool Hor=true);
	void doEvents(CCObject* pSender, CCControlEvent event);
protected:
	void RedistributionAllChildren(CCNode *pRoot,bool IsHide=false);
	void Redistribution(CCLayer *pControl,bool IsHide=false);

	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);

    // default implements are used to call script callback if exist
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccWindowMSG(CCTouch *pTouch, CCEvent *pEvent, int nType);
protected:
	// 背景
	CCScale9Sprite *pBackground;
	// 确定
	CCControlButton *pSubmit;
	// 取消
	CCControlButton *pCancel;
	// 关闭
	CCControlButton *pClose;

	// 遮罩层
	SIX_UILayer *pBlock;
	ccColor4B m_MaskColor;
	int m_MaskPriority;
	bool m_MaskRedrawBorder;

	bool m_IsShow;
	bool m_ActDone;

	// 拖拽相关
	bool m_bAllowDragged;
	bool m_IsDragged;
	CCPoint m_LastHitPos;

	// 是否在关闭的时候销毁UI子控件
	bool m_bCloseThenCleanup;

	// 上一次的优先级
	int m_LastPriority;
	// 弹出窗口数目
	static int m_WndCount;

	static int GLOBAL_PRIORITY;
	static int GLOBAL_ZORDER;
};
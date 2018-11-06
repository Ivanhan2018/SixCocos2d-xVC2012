/***********************************************
Name：SIX_EditBox
Desc：SIX_EditBox
Auth：Cool.Cat@2013-04-23
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <CCLuaEngine.h>

#define FONT_NAME	"Helvetica"
#define FONT_SIZE	12

USING_NS_CC;

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
};

class SIX_EditBox : public KeyboardNotificationLayer, public CCTextFieldDelegate
{
public:
	SIX_EditBox();
    void callbackRemoveNodeWhenDidAction(CCNode * pNode);

    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);

    virtual bool attachWithIME();

    // CCLayer
    virtual void onEnter();
    virtual void onExit();

    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
	// Add by Cool.Cat
	virtual void onTextFieldChanged(CCTextFieldTTF * sender);
    virtual bool onDraw(CCTextFieldTTF * pSender);

	// 输入文字上限个数(多字节+2，单字节+1)
	int getInputTextMaxCount();
	void setInputTextMaxCount(int max);

	void InitCursor(long long color,int width,int height);

	CCTextFieldTTF *getTTF();
private:
	void UpdateCursorPos();
private:
	CCTextFieldTTF		*m_pTextField;
	int                 m_nCharLimit;
	CCSprite			*m_pCursorSprite;
	CCAction			*m_pCursorAction;
};
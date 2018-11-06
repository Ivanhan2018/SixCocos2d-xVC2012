//
//  PromptBox.h
//  Game
//
//  Created by 罗敏 on 13-6-27.
//
//

#ifndef __Game__PromptBox__
#define __Game__PromptBox__

#include "cocos2d.h"
#include "common/CocosUnits.h"
USING_NS_CC;


typedef enum
{
	mPromptTypeServerShut,              //网络异常
	mPromptTypeLoginFaild,              //登陆失败
	mPromptTypePasswordFind,              //密码找回
	mPromptTypeGeTCHARgeFaild,			//领取失败
	mPromptTypeErrorPhone,
	mPromptTypeTwoInputError,
	mPromptTypeErrorQQNumber,
	mPromptTypeErrorNickName,
	mPromptTypeSeverPasswordFaild,		//2次密码不一致
	mPromptTypeLoginLegal,				//密码非法
	mPromptTypeMakeSureModifyNickName,	//去顶修改昵称
	mPromptTypeNosever,					//没有服务器
	mPromptTypeGetError,				//领取失败
	mPromptTypeLackCoins,				//破产
	mPromptStartFaild,				//进入游戏失败
	mPromptVersionNew,              //版本为最新
	mPromptNickNameError,              //昵称非法
} mPromptType;

class  PromptBox : public CCLayer 
{
public:
	static PromptBox* PromptBoxWith(CCPoint pos , mPromptType type);

	bool initPromptBox(CCPoint pos,mPromptType type);
	PromptBox();
	~PromptBox();

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void closePromptBox(CCObject * obj);
	void setPromptText(const char* szDes);

	void okButton(CCObject* obj);
	void cannelButton(CCObject* obj);

	void setLevelAndX(int nLevel,int nXXX,bool isLack);
private:
	const char * getTheCharWithType(mPromptType type);

	CCLabelTTF* m_pAlartWord;
	CCMenu * m_pBackMenu;
	bool m_bBackMenu;
	CCMenu* m_pOkMenu;
	bool m_bOkMenu;
	mPromptType m_nTypes;
	int m_nLevel;
	int m_nXXX;
	bool m_bIsLack;
};


#endif /* defined(__Game__PromptBox__) */

//
//  PromptBox.h
//  Game
//
//  Created by ���� on 13-6-27.
//
//

#ifndef __Game__PromptBox__
#define __Game__PromptBox__

#include "cocos2d.h"
#include "common/CocosUnits.h"
USING_NS_CC;


typedef enum
{
	mPromptTypeServerShut,              //�����쳣
	mPromptTypeLoginFaild,              //��½ʧ��
	mPromptTypePasswordFind,              //�����һ�
	mPromptTypeGeTCHARgeFaild,			//��ȡʧ��
	mPromptTypeErrorPhone,
	mPromptTypeTwoInputError,
	mPromptTypeErrorQQNumber,
	mPromptTypeErrorNickName,
	mPromptTypeSeverPasswordFaild,		//2�����벻һ��
	mPromptTypeLoginLegal,				//����Ƿ�
	mPromptTypeMakeSureModifyNickName,	//ȥ���޸��ǳ�
	mPromptTypeNosever,					//û�з�����
	mPromptTypeGetError,				//��ȡʧ��
	mPromptTypeLackCoins,				//�Ʋ�
	mPromptStartFaild,				//������Ϸʧ��
	mPromptVersionNew,              //�汾Ϊ����
	mPromptNickNameError,              //�ǳƷǷ�
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

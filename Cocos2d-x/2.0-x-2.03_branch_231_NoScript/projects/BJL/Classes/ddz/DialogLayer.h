//  [4/8/2014 xieyi]
#ifndef __DIALOGLAYER__
#define __DIALOGLAYER__
#include "cocos2d.h"
#include "DDZRes.h"
#include <limits>
USING_NS_CC;

enum dialog_type
{
	dialog_hints = 1,//��������
	dialog_back,//����
	dialog_poChan,//�Ʋ�
	dialog_poChanSongCoin,//�Ʋ��ͽ��
	dialog_dismissTable,//��ɢ����
	dialog_roomLimitMin,//��������
	dialog_roomLimitMax,//��������
};


class DialogLayer : public CCLayer
{

public:
	DialogLayer(dialog_type type);
	~DialogLayer();
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

	static DialogLayer * create(dialog_type type);
	dialog_type m_type;
	virtual void onEnter();
	virtual void onExit();

private:
	void menuOkCallBack(CCObject * pSender);	//ȷ��
	void menuCancleCallBack(CCObject * pSender);//ȡ��
	void initTable(char* Name,int type);		//--1Ϊֻ��ȷ����2Ϊȷ����ȡ��
	CCLabelTTF * m_ttf;
};

#endif
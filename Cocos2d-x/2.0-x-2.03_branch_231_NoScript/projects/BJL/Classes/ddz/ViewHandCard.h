//  [3/25/2014 wucan]

#ifndef			__VIEW_HANDCARD__
#define			__VIEW_HANDCARD__
#include "cocos2d.h"
#include "ViewTask.h"
#include <cmath>
USING_NS_CC;
#define  CARD_SPACE  40
#define  SMALLCARD_SPACE 20

class ViewHandCard :public CCLayer
{
public:
	ViewHandCard();
	~ViewHandCard();
	CREATE_FUNC(ViewHandCard);
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

public:
	void setHardCard(WORD _charID,BYTE* _data,int _num,bool _effect,bool _open);	
	void setOutCard(WORD _charID,BYTE* _data,int _num,WORD BankUserID=1000);
	bool UserOutCard(bool isOut);				//--�û�����
	void UserAutoCard();																//--�Զ�����
	void showDiPai(BYTE * _data,int _num,int _lastTask,bool isNew=true);										//--��ʾ����
	void showDipaiEffect(CCNode* _node);
	void showDipaiSpt(CCNode* _node);
	bool setHintCard();																	//--������ʾ��
	bool isNoCardout();
	void setUnallowTouch();	//��Ϸ���������˿��Ʋ��ܱ�������
	void removeHintCard();	//�Ƴ����µ��˿���
	void setCardRecover();													//--���Ƹ�ԭ
	void setCardUp(BYTE * _data,int _num);						//--���Ƶ���
	void newRound();
private:
	void showMeUserHardCard(BYTE* _data,int _num,bool _open);		//��ʾ�Լ����е��˿���
	void showhardCardEffect(float deley);
	void showLeftUserHardCard(BYTE* _data,int _num);	//��ʾ�ϼ�����
	void showRightUserHardCard(BYTE* _data,int _num);	//��ʾ�¼�����
	void showLeftHintCard(int _num);					//��ʾ�ϼ��˿��Ƹ��ŵ�����
	void showRightHintCard(int _num);					//��ʾ�¼��˿��Ƹ��ŵ�����
	int m_leftCardNum[20];								//�����xλ��
	int m_rightCardNum[20];								//�ұ���xλ��


public:
	CCSprite* getCardSprite(char _data,int _type,bool isBigCard);
	int			getCardData(BYTE* _data);							//--�õ�����
	int			getCardUpData(BYTE* _data);						//--�õ�up��־����
	bool OnShunziWidom( BYTE cbCardData[], BYTE cbCardCount ,BYTE wisCard[], int& index );
	bool OnLianduiWidom( BYTE cbCardData[], BYTE cbCardCount,BYTE wisCard[], int& index  );
private:
	//����ѡ�������ж�
	//ͨ������ı仯�ж����ƣ����m_distance>m_maxDistance,��ʾ��ɢ�����ƣ���֮��Ϊ��������
	float m_distance; //ǰһ����x��ԭ��ľ���
	float m_maxDistance; //��һ����x��ԭ��ľ���  
	float m_origin;	//ԭ��xλ��
	bool m_isRay;			//�����Ƿ�Ϊ��ɢ
	bool m_isSelect;	//�Ƿ�ѡ�����˿���
// 	CCLabelAtlas * m_leftCardNumAtlas;//�������˿�������
// 	CCLabelAtlas * m_rightCardNumAtlas;//�ұ�����˿�������

	CCNode * m_handCardNode;		//�Լ�����node					--CCSpriteBatchNode��д�ֻ���֧��̫��
	CCSpriteBatchNode * m_leftCardNode;		//�ϼ�����node
	CCSpriteBatchNode * m_rightCardNode;		//�¼�����node
	CCNode * m_diPaiNode;			//�����ƣ����ƣ�node
	CCSpriteBatchNode * m_hintLeftCardNode;	//�ϼҸ��ŵ��˿���node
	CCSpriteBatchNode * m_hintRightCardNode; //�¼Ҹ��ŵ��˿���node
	int m_dt[20];					//�˿���ƫ����
	CCNode * m_outCardNodeL;		//�ϼҳ�����
	CCNode * m_outCardNodeR;		//�¼ҳ�����
	CCNode * m_outCardNodeM;		//�Լ�������
	ViewTask*				m_viewTask;
	//--����������
	BYTE		m_outCardData[20];
	WORD	m_outCardNum;
	//--����Ч�����
	int        m_effectNum;
	bool     m_isOpenCard;
	//--��������
	BYTE   m_BackData[3];
	int	  m_lastTaskKey;
	bool m_unallowToucn;		//��Ϸ�������˿��Ʋ�������
};

#endif
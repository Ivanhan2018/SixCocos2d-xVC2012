//  [3/26/2014 xieyi]
#ifndef __SETTLEMENT__
#define __SETTLEMENT__
#include "cocos2d.h"
#include "DDZRes.h"
#include "User.h"
#include "CMD_DDZ.h"
#include "CardTableLayer.h"
USING_NS_CC;

enum{
	tag_showcard = 1,	//����
	tag_jiabei,			//�ӱ�
	tag_qiangdizhu,		//������
	tag_bomb,			//ը��
	tag_spring,			//����
	tag_lowcardtype,	//��������
	tag_overcardtype,	//��������
	tag_basescore,		//�׷�
	tag_tableconsume,	//��������
	tag_total,			//�ܱ���
};

class Settlement : public CCNode
{
public:

	Settlement();
	~Settlement();
	virtual bool init();
	CREATE_FUNC(Settlement);
	void setUserMessage(CCInteger * obj);		//�����Ϣ
	void setTimesMessage(CMD_S_GameEnd* _gameEnd,WORD _userID);	//���ñ�����Ϣ
private:
	void addString(char* key,CCPoint point,_ccColor3B  color,int fontSize,int tag,int num);		//���Ҫ��ʾ���ַ���
	void addUserString(const char * res,float pointY,_ccColor3B color,int fontSize,long udpScore,const char * nikeName,bool isJiaBei,bool isDiZhu,bool isSelf);
	CCSprite * m_bgLeftSprite;	//����ͼƬ
	CCSpriteBatchNode * m_batchNode;	//
};

#endif
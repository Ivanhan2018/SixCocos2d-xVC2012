//
//  DDZLogic.h
//  �������߼���
//
//  Created by zhouwei on 13-6-20.
//
//

#ifndef __Game__DDZLogic__
#define __Game__DDZLogic__

#include "common/Define.h"

//
//#ifdef WIN32
//#include <windows.h>
//#else
//
//#endif

#include <iostream>



//////////////////////////////////////////////////////////////////////////
//���ܣ��߼��ж�

//��������
#define ST_ORDER					0									//��С����
#define ST_COUNT					1									//��Ŀ����

//////////////////////////////////////////////////////////////////////////
//��Ŀ����

#define MAX_COUNT					20									//�����Ŀ
#define FULL_COUNT					54									//ȫ����Ŀ
#define BACK_COUNT					3									//������Ŀ
#define NORMAL_COUNT				17									//������Ŀ

//////////////////////////////////////////////////////////////////////////

//��ֵ����
#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

//�˿�����
#define CT_ERROR					0									//��������
#define CT_SINGLE					1									//��������
#define CT_DOUBLE					2									//��������
#define CT_THREE					3									//��������
#define CT_SINGLE_LINE				4									//��������
#define CT_DOUBLE_LINE				5									//��������
#define CT_THREE_LINE				6									//��������
#define CT_THREE_LINE_TAKE_ONE		7									//����һ��
#define CT_THREE_LINE_TAKE_TWO		8									//����һ��
#define CT_FOUR_LINE_TAKE_ONE		9									//�Ĵ�����
#define CT_FOUR_LINE_TAKE_TWO		10									//�Ĵ�����
#define CT_BOMB_CARD				11									//ը������
#define CT_MISSILE_CARD				12									//�������


//����Ч����־
#define IDA_WARN                        200                             //��������
#define IDA_SMOKE                       201                             //������
#define IDA_GOLD                        202                             //�𵰶���
#define IDA_LAND_WIN                    203								//����ʤ��
#define IDA_LAND_FAIL                   204								//����ʧ��
#define IDA_FAR_WIN                     205								//ũ��ʤ��
#define IDA_FAR_FAIL                    206								//ũ��ʧ��
//////////////////////////////////////////////////////////////////////////

//�����ṹ
struct tagAnalyseResult
{
	unsigned char 							cbFourCount;						//������Ŀ
	unsigned char 							cbThreeCount;						//������Ŀ
	unsigned char 							cbDoubleCount;						//������Ŀ
	unsigned char							cbSignedCount;						//������Ŀ
	unsigned char							cbFourCardData[MAX_COUNT];			//�����˿�
	unsigned char							cbThreeCardData[MAX_COUNT];			//�����˿�
	unsigned char							cbDoubleCardData[MAX_COUNT];		//�����˿�
	unsigned char							cbSignedCardData[MAX_COUNT];		//�����˿�
};

//���ƽ��
struct tagOutCardResult
{
	unsigned char							cbCardCount;						//�˿���Ŀ
	unsigned char							cbResultCard[MAX_COUNT];			//����˿�
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ�߼���
class DDZLogic
{
	//��������
protected:
	static const unsigned char				m_cbCardData[FULL_COUNT];			//�˿�����
    
	//��������
public:
	//���캯��
	DDZLogic();
	//��������
	~DDZLogic();
    
	//���ͺ���
public:
	
    //��ȡ����
	unsigned char getCardType(const unsigned char cbCardData[], unsigned char cbCardCount);
	
    //��ȡ��ֵ
	unsigned char getCardValue(unsigned char cbCardData) { return cbCardData & MASK_VALUE; }
	
    //��ȡ��ɫ
	unsigned char getCardColor(unsigned char cbCardData) { return cbCardData & MASK_COLOR; }
   
    //��ȡͬ������
    unsigned char getSampleCount(unsigned char cbCardData[], unsigned char cbCardCount, unsigned char cbCard);
   
    //����ͬ��(�����ƣ�ƥ���ƣ������ƣ�������)
    bool searchSampleCard(unsigned char cbHandCardData[], unsigned char cbHandCardCount,unsigned char cbCardData[], unsigned char cbCardCount,unsigned char cbCard,tagOutCardResult & OutCardResult);
    
    unsigned char getCardCount(unsigned char cbCardData[], unsigned char cbCardCount,unsigned char cbCenterCard);
	//���ƺ���
public:
	
    //�����˿�
	void randCardList(unsigned char cbCardBuffer[], unsigned char cbBufferCount);
	
    //�����˿�
	void sortCardList(unsigned char cbCardData[], unsigned char cbCardCount, unsigned char cbSortType);
	
    //ɾ���˿�
	bool removeCard(const unsigned char cbRemoveCard[], unsigned char cbRemoveCount, unsigned char cbCardData[], unsigned char cbCardCount);
    
	//�߼�����
public:
	//��Ч�ж�
	bool isValidCard(unsigned char cbCardData);
    
    //�Ƿ�������
    bool islinkCard(unsigned char cbCardData[], unsigned char cbCardCount,tagOutCardResult& OutCardResult);
    
    //�Ƿ���˫��
    bool isDoublelinkCard(unsigned char cbCardData[], unsigned char cbCardCount,tagAnalyseResult& AnalyseResult);
    
    //�Ƿ�ӵ��������
    unsigned char isHasCardData(unsigned char cbCenterCardData,unsigned char cbCardData[], unsigned char cbCardCount);
    
	//�߼���ֵ
	unsigned char getCardLogicValue(unsigned char cbCardData);
	
    //�Ա��˿�
	bool compareCard(const unsigned char cbFirstCard[], const unsigned char cbNextCard[], unsigned char cbFirstCount, unsigned char cbNextCount);
	
    //��������
	bool searchOutCard(const unsigned char cbHandCardData[], unsigned char cbHandCardCount, const unsigned char cbTurnCardData[], unsigned char cbTurnCardCount, tagOutCardResult & OutCardResult);
    
	//�ڲ�����
public:
	//�����˿�
	void analysebCardData(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult & AnalyseResult,bool bFlag = false);
	//���������
    long getMaxScore(const long bGameScore[]);
		
	//  [4/1/2014 wucan]
public:
	unsigned char getBackbeiLv(unsigned char* _data,unsigned char _num);
	unsigned char getLastTask(unsigned char* _data,unsigned char _num,unsigned char _key);
	bool isWangZha(unsigned char cbCardData[], unsigned char cbCardCount);
};

//////////////////////////////////////////////////////////////////////////



#endif /* defined(__Game__DDZLogic__) */

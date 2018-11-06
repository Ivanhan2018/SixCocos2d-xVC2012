#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "../GameMsg/CMD_SanGong.h"

//////////////////////////////////////////////////////////////////////////
//�궨��
#define FULL_COUNT					54									//ȫ����Ŀ
#define MAX_COUNT					3									//�����Ŀ

//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

//�˿����ͣ�����>��ը>ը��>����>��ֵ��
#define CT_VALUES					1									//��ֵ���ͣ�9��>8��>7��>0-6��ɢ�ƣ�
//����:����������J�� Q�� K��С����������ɵ�����
#define CT_THREE_JQK				2									//��������
//ը��:����������ͬ����
#define CT_THREE_BOMB				4									//ը������
//��ը����С��������һ����
#define CT_JOKER_BOMB				5									//��ը����
//��������3��3��ɵ���
#define CT_THREE_333				6									//��������
//////////////////////////////////////////////////////////////////////////

//ʵ�ַ��ơ����ͼ���С�����ͱ��ʵ���Ϸ�߼���
class CGameLogic
{
	//��������
private:
	static TCardData						m_cbCardListData[FULL_COUNT];				//�˿˶���

	//��������
public:
	//���캯��
	CGameLogic();
	//��������
	virtual ~CGameLogic();

	//���Ժ���
public:
	//��ȡ��ֵ
	static unsigned char GetCardValue(TCardData cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//��ȡ��ɫ={0����,16÷��,32����,48����,64��}
	static unsigned char GetCardColor(TCardData cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//��Ч�ж�
	static bool IsValidCard(TCardData cbCardData);
	//������
	static const char * GetCardName(TCardData cbCardData);

	//���ͺ���
public:
	//��ȡ����
	static TCardType GetCardType(TCardData cbCardData[], unsigned char cbCardCount);
	//��ȡ����
	static TCardTypeMulti GetCardTimes(TCardData cbCardData[], unsigned char cbCardCount);
	//��ȡ����
	static TCardPoint GetCardPoint(TCardData cbCardData[], unsigned char cbCardCount);

	//���ƺ���
public:
	//�����˿ˣ����߼���ֵ��������
	static void SortCardList(TCardData cbCardData[], unsigned char cbCardCount);
	//�����˿�
	static void RandCardList(TCardData cbCardBuffer[], unsigned char cbBufferCount);

	//ȡ[nMin,nMax]֮����������
	static int GetRand(const int nMin,const int nMax);

	//���ݸ���ѡ�񣬷���true�ĸ���Ϊp
	static bool SelectBoolByProb(float p);

	//���ܺ���
public:
	//�߼���ֵ��54���˿��������У�A<2<3<4<5<6<7<8<9<����10<÷��10<����10<����10<J<Q<K<С��<����
	static unsigned char GetCardLogicValue(TCardData cbCardData);
	//�Ա��˿ˣ�ibankerflag={0,1,2}����0ֵ����0�����͵ıȽϣ�ibankerflag=1��ʾcbFirstData��Ӧ�����Ӯ��ibankerflag=2��ʾcbNextData��Ӧ�����Ӯ
	static bool CompareCard(TCardData cbFirstData[], TCardData cbNextData[],unsigned char cbCardCount,int ibankerflag=0);
};

//////////////////////////////////////////////////////////////////////////

#endif

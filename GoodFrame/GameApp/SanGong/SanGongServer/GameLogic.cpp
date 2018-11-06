#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "GameLogic.h"

//����ά��
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
typedef unsigned char BYTE;


//////////////////////////////////////////////////////////////////////////

//�˿�����
TCardData CGameLogic::m_cbCardListData[FULL_COUNT]=
{
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//���� A - K
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//÷�� A - K
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//���� A - K
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//���� A - K
	0x4E,0x4F,
};


//���ڱȽϵ��߼���ֵ����ԭ��
typedef unsigned char(*pLVFunc)(TCardData x);

//�ҳ�һά�����е����ֵ
TCardData FindMaxElement(TCardData *c,int size_c,pLVFunc LVFunc)
{
	TCardData max=*c;
	TCardData temp=0;
	for(int i=1;i<size_c;++i)
	{
		temp=*(c+i);
		if(LVFunc(temp)>LVFunc(max))
		{
			max=temp;
		}
	}
	return max;
}

//�ҳ�һά�����е���Сֵ
TCardData FindMinElement(TCardData *c,int size_c,pLVFunc LVFunc)
{
	TCardData min=*c;
	TCardData temp=0;
	for(int i=1;i<size_c;++i)
	{
		temp=*(c+i);
		if(LVFunc(temp)<LVFunc(min))
		{
			min=temp;;
		}
	}
	return min;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameLogic::CGameLogic()
{
}

//��������
CGameLogic::~CGameLogic()
{
}

//��Ч�ж�
bool CGameLogic::IsValidCard(TCardData cbCardData)
{
	//��ȡ����
	BYTE cbCardColor=GetCardColor(cbCardData);
	BYTE cbCardValue=GetCardValue(cbCardData);

	//��Ч�ж�
	if ((cbCardData==0x4E)||(cbCardData==0x4F)) return true;
	if ((cbCardColor<=0x30)&&(cbCardValue>=0x01)&&(cbCardValue<=0x0D)) return true;

	return false;
}

const char * CGameLogic::GetCardName(TCardData cbCardData)
{
	bool bLegal=IsValidCard(cbCardData);
	//assert(bLegal && "GetCardName�������������!");
	if(bLegal)
	{
		static const char * szCardName[5][15]={
			{"����A","����2","����3","����4","����5","����6","����7","����8","����9","����10","����J","����Q","����K","",""},
			{"÷��A","÷��2","÷��3","÷��4","÷��5","÷��6","÷��7","÷��8","÷��9","÷��10","÷��J","÷��Q","÷��K","",""},
			{"����A","����2","����3","����4","����5","����6","����7","����8","����9","����10","����J","����Q","����K","",""},
			{"����A","����2","����3","����4","����5","����6","����7","����8","����9","����10","����J","����Q","����K","",""},
			{"","","","","","","","","","","","","","С��","����"},
		};
		unsigned char nColorIndex=(cbCardData & 0xf0)>>4;
		unsigned char nValueIndex=(cbCardData & 0x0f)-1;
		return szCardName[nColorIndex][nValueIndex];
	}
	else
		return "";
}

//��ȡ����
TCardType CGameLogic::GetCardType(TCardData cbCardData[],unsigned char cbCardCount)
{
	//Ч������
	assert(cbCardCount==MAX_COUNT);
	if (cbCardCount!=MAX_COUNT) return 0;

	//��ȡ��ֵ
	unsigned char cbValueList[MAX_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) cbValueList[i]=GetCardValue(cbCardData[i]);

	//�����ж�
	if ((cbValueList[0]==cbValueList[1])&&(cbValueList[0]==cbValueList[2])&&(cbValueList[0]==3))return CT_THREE_333;
	//ը���ж�
	if ((cbValueList[0]==cbValueList[1])&&(cbValueList[0]==cbValueList[2]))	return CT_THREE_BOMB;
	//��ը�ж�
	if ((cbValueList[0]>=14)&&(cbValueList[1]>=14))	return CT_JOKER_BOMB;
	if ((cbValueList[0]>=14)&&(cbValueList[2]>=14))	return CT_JOKER_BOMB;
	if ((cbValueList[1]>=14)&&(cbValueList[2]>=14))	return CT_JOKER_BOMB;

	//�����ж�
	unsigned char i=0;
	for (i=0;i<cbCardCount;i++)
	{
		if (cbValueList[i]<=10) break;
	}
	if (i==cbCardCount) return CT_THREE_JQK;

	return CT_VALUES;
}

//��ȡ����
TCardTypeMulti CGameLogic::GetCardTimes(TCardData cbCardData[],unsigned char cbCardCount)
{
	//��ȡ����
	TCardType cbCardType=GetCardType(cbCardData,cbCardCount);

	//��ȡ����
	switch (cbCardType)
	{
	case CT_VALUES:			//��ֵ����
		{
			//��������
			unsigned char cbValueList=0;
			unsigned char cbValueCard=0;

			//��ȡ��ֵ
			for (unsigned char i=0;i<cbCardCount;i++)
			{
				cbValueCard=GetCardValue(cbCardData[i]);
				if (cbValueCard<10) cbValueList+=cbValueCard;
			}
			
			return ((cbValueList%10)-5>=2)?(cbValueList%10)-5:1;
		}
	case CT_THREE_JQK:		//��������
		{
			return 6;
		}
	case CT_THREE_BOMB:		//ը������
		{
			return 7;
		}
	case CT_JOKER_BOMB:		//��ը����
		{
			return 8;
		}
	case CT_THREE_333:		//��������
		{
			return 9;
		}
	}

	return 0;
}

//��ȡ����
TCardPoint CGameLogic::GetCardPoint(TCardData cbCardData[],unsigned char cbCardCount)
{
	//��������
	TCardPoint cbValueList=0;

	//�������
	for (unsigned char i=0;i<MAX_COUNT;i++)
	{
		unsigned char cbCardValue=GetCardValue(cbCardData[i]);
		if (cbCardValue<10) cbValueList=(cbValueList+cbCardValue)%10;
	}

	return cbValueList;
}

//�����˿�
void CGameLogic::SortCardList(TCardData cbCardData[],unsigned char cbCardCount)
{
	//Ч�����
	assert(cbCardCount==MAX_COUNT);
	if (cbCardCount!=MAX_COUNT) return;

	//ת����ֵ
	unsigned char cbLogicValue[MAX_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) cbLogicValue[i]=GetCardLogicValue(cbCardData[i]);

	//�������
	bool bSorted=true;
	BYTE cbTempData,bLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (unsigned char i=0;i<bLast;i++)
		{
			if ((cbLogicValue[i]<cbLogicValue[i+1])||
				((cbLogicValue[i]==cbLogicValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
			{
				//����λ��
				cbTempData=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbTempData;
				cbTempData=cbLogicValue[i];
				cbLogicValue[i]=cbLogicValue[i+1];
				cbLogicValue[i+1]=cbTempData;
				bSorted=false;
			}
		}
		bLast--;
	} while(bSorted==false);

	return;
}

//�����˿�
void CGameLogic::RandCardList(TCardData cbCardBuffer[],unsigned char cbBufferCount)
{
	//���Դ���
	//CopyMemory(cbCardBuffer,m_cbCardListData,cbBufferCount);
	//����׼��
	unsigned char cbCardData[CountArray(m_cbCardListData)];
	memcpy(cbCardData,m_cbCardListData,sizeof(m_cbCardListData));

	//�����˿�
	BYTE cbRandCount=0,cbPosition=0;
	do
	{
		cbPosition=rand()%(CountArray(m_cbCardListData)-cbRandCount);
		cbCardBuffer[cbRandCount++]=cbCardData[cbPosition];
		cbCardData[cbPosition]=cbCardData[CountArray(m_cbCardListData)-cbRandCount];
	} while (cbRandCount<cbBufferCount);

	return;
}

//ȡ[nMin,nMax]֮����������
int	CGameLogic::GetRand(const int nMin,const int nMax)
{
	if ( nMin > nMax)
		return nMin;
	return rand()%(nMax-nMin+1)+nMin;
}

//���ݸ���ѡ�񣬷���true�ĸ���Ϊp
bool CGameLogic::SelectBoolByProb(float p)
{
	if(p>=1)
		return true;
	if(p<=0)
		return false;
	int P=(int)(p*1000+0.5); 
	int randNum = GetRand(0,1000);
	if(randNum<P)
		return true;
	return false;
}

//�߼���ֵ
unsigned char CGameLogic::GetCardLogicValue(TCardData cbCardData)
{
	//�˿�����
	BYTE cbCardColor=GetCardColor(cbCardData);
	BYTE cbCardValue=GetCardValue(cbCardData);

	////���Ե���
	//if (cbCardValue==10) cbCardValue=0;

	//ת����ֵ
	return (cbCardValue*4)+(cbCardColor>>4);
}

//�Ա��˿�
bool CGameLogic::CompareCard(TCardData cbFirstData[], TCardData cbNextData[], unsigned char cbCardCount,int ibankerflag/*=0*/)
{
	//��ȡ����
	BYTE cbNextType=GetCardType(cbNextData,cbCardCount);
	BYTE cbFirstType=GetCardType(cbFirstData,cbCardCount);

	//�����ж�
	if (cbFirstType!=cbNextType) return (cbFirstType>cbNextType);

	//������
	switch(cbFirstType)
	{
	case CT_THREE_JQK:		//��������
		{
			//�����У���������Ƶ����Ƚϴ�С�������մ�����С����K��Q��J�Ĵ�С�жϣ����Ƶ���ͬ��Ƚϻ�ɫ�����պ���>����>÷��>���飻
			//11(����J)���߼�ֵ=44
			//27(÷��J)���߼�ֵ=45
			//43(����J)���߼�ֵ=46
			//59(����J)���߼�ֵ=47
			//12(����Q)���߼�ֵ=48
			//28(÷��Q)���߼�ֵ=49
			//44(����Q)���߼�ֵ=50
			//60(����Q)���߼�ֵ=51
			//13(����K)���߼�ֵ=52
			//29(÷��K)���߼�ֵ=53
			//45(����K)���߼�ֵ=54
			//61(����K)���߼�ֵ=55
			//78(С��)���߼�ֵ=60
			//79(����)���߼�ֵ=64
			//�Ա�ɢ��
			//BYTE cbNextLogicValue=GetCardLogicValue(cbNextData[0]);
			//BYTE cbFirstLogicValue=GetCardLogicValue(cbFirstData[0]);
			TCardData cbNextMaxData=FindMaxElement(cbNextData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextMaxData);
			TCardData cbFirstMaxData=FindMaxElement(cbFirstData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstMaxData);

			//�Ա�ɢ��
			return cbFirstLogicValue>cbNextLogicValue;
		}
	//case CT_THREE_KING:		//��������
	case CT_THREE_BOMB:		//ը������
		{
			//ը���У���С��������һ����Ϊ������ը��K��ը��Q��ը��J��ը��10��ը��9��ը��8��ը��7��ը��6��ը��5��ը��4��ը��3��ը��2��ը��A��

			//BYTE cbNextLogicValue=GetCardLogicValue(cbNextData[0]);
			//BYTE cbFirstLogicValue=GetCardLogicValue(cbFirstData[0]);
			TCardData cbNextMaxData=FindMaxElement(cbNextData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextMaxData);
			TCardData cbFirstMaxData=FindMaxElement(cbFirstData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstMaxData);

			//�Ա�ɢ��
			return cbFirstLogicValue>cbNextLogicValue;
		}
	case CT_VALUES:			//��ֵ����
		{
			//ɢ���У�6�㣾5�㣾4�㣾3�㣾2�㣾1�㣾0�㣻
		    //��ׯ�Һ��мҵ�����ͬ��0-9�㣩����������Ƶ����Ƚϴ�С�������մ���>С��>K>Q>J>10>9>8>7>6>5>4>3>2>A�Ĵ�С���жϣ����Ƶ���ͬ��Ƚϻ�ɫ�����պ���>����>÷��>���飻

			//��ȡ��ֵ
			BYTE cbNextValueList=0;
			BYTE cbFirstValueList=0;
			for (BYTE i=0;i<MAX_COUNT;i++)
			{
				BYTE cbNextCardValue=GetCardValue(cbNextData[i]);
				BYTE cbFirstCardValue=GetCardValue(cbFirstData[i]);
				if (cbNextCardValue<10) cbNextValueList=(cbNextValueList+cbNextCardValue)%10;
				if (cbFirstCardValue<10) cbFirstValueList=(cbFirstValueList+cbFirstCardValue)%10;
			}

			//��ֵ�Ա�
			if (cbFirstValueList!=cbNextValueList) return cbFirstValueList>cbNextValueList;

			//��ׯ�Һ��мҵ���ͬΪ0�㣬���ж�ׯ�����add by Ivan_han 20131031
			if(cbFirstValueList==0 && ibankerflag==1)
				return true;
			if(cbFirstValueList==0 && ibankerflag==2)
				return false;

			//��ȡ����
			BYTE cbNextCountJQK=0;
			BYTE cbFirstCountJQK=0;
			for (BYTE i=0;i<MAX_COUNT;i++)
			{
				if (GetCardValue(cbNextData[i])>10) cbNextCountJQK++;
				if (GetCardValue(cbFirstData[i])>10) cbFirstCountJQK++;
			}

			//�����Ա�
			if (cbFirstCountJQK!=cbNextCountJQK) return cbFirstCountJQK>cbNextCountJQK;

			//�Ա�ɢ��
			//BYTE cbNextLogicValue=GetCardLogicValue(cbNextData[0]);
			//BYTE cbFirstLogicValue=GetCardLogicValue(cbFirstData[0]);
			TCardData cbNextMaxData=FindMaxElement(cbNextData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextMaxData);
			TCardData cbFirstMaxData=FindMaxElement(cbFirstData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstMaxData);

			//�Ա�ɢ��
			return cbFirstLogicValue>cbNextLogicValue;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////

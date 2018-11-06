#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "GameLogic.h"

//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
typedef unsigned char BYTE;


//////////////////////////////////////////////////////////////////////////

//扑克数据
TCardData CGameLogic::m_cbCardListData[FULL_COUNT]=
{
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//方块 A - K
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//梅花 A - K
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//红桃 A - K
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//黑桃 A - K
	0x4E,0x4F,
};


//用于比较的逻辑数值函数原型
typedef unsigned char(*pLVFunc)(TCardData x);

//找出一维数组中的最大值
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

//找出一维数组中的最小值
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

//构造函数
CGameLogic::CGameLogic()
{
}

//析构函数
CGameLogic::~CGameLogic()
{
}

//有效判断
bool CGameLogic::IsValidCard(TCardData cbCardData)
{
	//获取属性
	BYTE cbCardColor=GetCardColor(cbCardData);
	BYTE cbCardValue=GetCardValue(cbCardData);

	//有效判断
	if ((cbCardData==0x4E)||(cbCardData==0x4F)) return true;
	if ((cbCardColor<=0x30)&&(cbCardValue>=0x01)&&(cbCardValue<=0x0D)) return true;

	return false;
}

const char * CGameLogic::GetCardName(TCardData cbCardData)
{
	bool bLegal=IsValidCard(cbCardData);
	//assert(bLegal && "GetCardName的输入参数有误!");
	if(bLegal)
	{
		static const char * szCardName[5][15]={
			{"方块A","方块2","方块3","方块4","方块5","方块6","方块7","方块8","方块9","方块10","方块J","方块Q","方块K","",""},
			{"梅花A","梅花2","梅花3","梅花4","梅花5","梅花6","梅花7","梅花8","梅花9","梅花10","梅花J","梅花Q","梅花K","",""},
			{"红桃A","红桃2","红桃3","红桃4","红桃5","红桃6","红桃7","红桃8","红桃9","红桃10","红桃J","红桃Q","红桃K","",""},
			{"黑桃A","黑桃2","黑桃3","黑桃4","黑桃5","黑桃6","黑桃7","黑桃8","黑桃9","黑桃10","黑桃J","黑桃Q","黑桃K","",""},
			{"","","","","","","","","","","","","","小王","大王"},
		};
		unsigned char nColorIndex=(cbCardData & 0xf0)>>4;
		unsigned char nValueIndex=(cbCardData & 0x0f)-1;
		return szCardName[nColorIndex][nValueIndex];
	}
	else
		return "";
}

//获取类型
TCardType CGameLogic::GetCardType(TCardData cbCardData[],unsigned char cbCardCount)
{
	//效验数据
	assert(cbCardCount==MAX_COUNT);
	if (cbCardCount!=MAX_COUNT) return 0;

	//获取数值
	unsigned char cbValueList[MAX_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) cbValueList[i]=GetCardValue(cbCardData[i]);

	//爆玖判断
	if ((cbValueList[0]==cbValueList[1])&&(cbValueList[0]==cbValueList[2])&&(cbValueList[0]==3))return CT_THREE_333;
	//炸弹判断
	if ((cbValueList[0]==cbValueList[1])&&(cbValueList[0]==cbValueList[2]))	return CT_THREE_BOMB;
	//王炸判断
	if ((cbValueList[0]>=14)&&(cbValueList[1]>=14))	return CT_JOKER_BOMB;
	if ((cbValueList[0]>=14)&&(cbValueList[2]>=14))	return CT_JOKER_BOMB;
	if ((cbValueList[1]>=14)&&(cbValueList[2]>=14))	return CT_JOKER_BOMB;

	//三公判断
	unsigned char i=0;
	for (i=0;i<cbCardCount;i++)
	{
		if (cbValueList[i]<=10) break;
	}
	if (i==cbCardCount) return CT_THREE_JQK;

	return CT_VALUES;
}

//获取倍数
TCardTypeMulti CGameLogic::GetCardTimes(TCardData cbCardData[],unsigned char cbCardCount)
{
	//获取类型
	TCardType cbCardType=GetCardType(cbCardData,cbCardCount);

	//获取倍数
	switch (cbCardType)
	{
	case CT_VALUES:			//点值类型
		{
			//变量定义
			unsigned char cbValueList=0;
			unsigned char cbValueCard=0;

			//获取数值
			for (unsigned char i=0;i<cbCardCount;i++)
			{
				cbValueCard=GetCardValue(cbCardData[i]);
				if (cbValueCard<10) cbValueList+=cbValueCard;
			}
			
			return ((cbValueList%10)-5>=2)?(cbValueList%10)-5:1;
		}
	case CT_THREE_JQK:		//三公类型
		{
			return 6;
		}
	case CT_THREE_BOMB:		//炸弹类型
		{
			return 7;
		}
	case CT_JOKER_BOMB:		//王炸类型
		{
			return 8;
		}
	case CT_THREE_333:		//爆玖类型
		{
			return 9;
		}
	}

	return 0;
}

//获取点数
TCardPoint CGameLogic::GetCardPoint(TCardData cbCardData[],unsigned char cbCardCount)
{
	//变量定义
	TCardPoint cbValueList=0;

	//计算点数
	for (unsigned char i=0;i<MAX_COUNT;i++)
	{
		unsigned char cbCardValue=GetCardValue(cbCardData[i]);
		if (cbCardValue<10) cbValueList=(cbValueList+cbCardValue)%10;
	}

	return cbValueList;
}

//排列扑克
void CGameLogic::SortCardList(TCardData cbCardData[],unsigned char cbCardCount)
{
	//效验参数
	assert(cbCardCount==MAX_COUNT);
	if (cbCardCount!=MAX_COUNT) return;

	//转换数值
	unsigned char cbLogicValue[MAX_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) cbLogicValue[i]=GetCardLogicValue(cbCardData[i]);

	//排序操作
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
				//交换位置
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

//混乱扑克
void CGameLogic::RandCardList(TCardData cbCardBuffer[],unsigned char cbBufferCount)
{
	//测试代码
	//CopyMemory(cbCardBuffer,m_cbCardListData,cbBufferCount);
	//混乱准备
	unsigned char cbCardData[CountArray(m_cbCardListData)];
	memcpy(cbCardData,m_cbCardListData,sizeof(m_cbCardListData));

	//混乱扑克
	BYTE cbRandCount=0,cbPosition=0;
	do
	{
		cbPosition=rand()%(CountArray(m_cbCardListData)-cbRandCount);
		cbCardBuffer[cbRandCount++]=cbCardData[cbPosition];
		cbCardData[cbPosition]=cbCardData[CountArray(m_cbCardListData)-cbRandCount];
	} while (cbRandCount<cbBufferCount);

	return;
}

//取[nMin,nMax]之间的随机整数
int	CGameLogic::GetRand(const int nMin,const int nMax)
{
	if ( nMin > nMax)
		return nMin;
	return rand()%(nMax-nMin+1)+nMin;
}

//根据概率选择，返回true的概率为p
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

//逻辑数值
unsigned char CGameLogic::GetCardLogicValue(TCardData cbCardData)
{
	//扑克属性
	BYTE cbCardColor=GetCardColor(cbCardData);
	BYTE cbCardValue=GetCardValue(cbCardData);

	////属性调整
	//if (cbCardValue==10) cbCardValue=0;

	//转换数值
	return (cbCardValue*4)+(cbCardColor>>4);
}

//对比扑克
bool CGameLogic::CompareCard(TCardData cbFirstData[], TCardData cbNextData[], unsigned char cbCardCount,int ibankerflag/*=0*/)
{
	//获取类型
	BYTE cbNextType=GetCardType(cbNextData,cbCardCount);
	BYTE cbFirstType=GetCardType(cbFirstData,cbCardCount);

	//类型判断
	if (cbFirstType!=cbNextType) return (cbFirstType>cbNextType);

	//简单类型
	switch(cbFirstType)
	{
	case CT_THREE_JQK:		//三公类型
		{
			//三公中，根据最大牌点来比较大小，即按照大王＞小王＞K＞Q＞J的大小判断，若牌点相同则比较花色，按照黑桃>红桃>梅花>方块；
			//11(方块J)的逻辑值=44
			//27(梅花J)的逻辑值=45
			//43(红桃J)的逻辑值=46
			//59(黑桃J)的逻辑值=47
			//12(方块Q)的逻辑值=48
			//28(梅花Q)的逻辑值=49
			//44(红桃Q)的逻辑值=50
			//60(黑桃Q)的逻辑值=51
			//13(方块K)的逻辑值=52
			//29(梅花K)的逻辑值=53
			//45(红桃K)的逻辑值=54
			//61(黑桃K)的逻辑值=55
			//78(小王)的逻辑值=60
			//79(大王)的逻辑值=64
			//对比散牌
			//BYTE cbNextLogicValue=GetCardLogicValue(cbNextData[0]);
			//BYTE cbFirstLogicValue=GetCardLogicValue(cbFirstData[0]);
			TCardData cbNextMaxData=FindMaxElement(cbNextData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextMaxData);
			TCardData cbFirstMaxData=FindMaxElement(cbFirstData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstMaxData);

			//对比散牌
			return cbFirstLogicValue>cbNextLogicValue;
		}
	//case CT_THREE_KING:		//三条类型
	case CT_THREE_BOMB:		//炸弹类型
		{
			//炸弹中，大小王加任意一张牌为最大，其次炸弹K＞炸弹Q＞炸弹J＞炸弹10＞炸弹9＞炸弹8＞炸弹7＞炸弹6＞炸弹5＞炸弹4＞炸弹3＞炸弹2＞炸弹A；

			//BYTE cbNextLogicValue=GetCardLogicValue(cbNextData[0]);
			//BYTE cbFirstLogicValue=GetCardLogicValue(cbFirstData[0]);
			TCardData cbNextMaxData=FindMaxElement(cbNextData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextMaxData);
			TCardData cbFirstMaxData=FindMaxElement(cbFirstData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstMaxData);

			//对比散牌
			return cbFirstLogicValue>cbNextLogicValue;
		}
	case CT_VALUES:			//点值类型
		{
			//散牌中，6点＞5点＞4点＞3点＞2点＞1点＞0点；
		    //若庄家和闲家点数相同（0-9点），根据最大牌点来比较大小，即按照大王>小王>K>Q>J>10>9>8>7>6>5>4>3>2>A的大小来判断，若牌点相同则比较花色，按照黑桃>红桃>梅花>方块；

			//获取数值
			BYTE cbNextValueList=0;
			BYTE cbFirstValueList=0;
			for (BYTE i=0;i<MAX_COUNT;i++)
			{
				BYTE cbNextCardValue=GetCardValue(cbNextData[i]);
				BYTE cbFirstCardValue=GetCardValue(cbFirstData[i]);
				if (cbNextCardValue<10) cbNextValueList=(cbNextValueList+cbNextCardValue)%10;
				if (cbFirstCardValue<10) cbFirstValueList=(cbFirstValueList+cbFirstCardValue)%10;
			}

			//点值对比
			if (cbFirstValueList!=cbNextValueList) return cbFirstValueList>cbNextValueList;

			//若庄家和闲家点数同为0点，则判定庄家最大，add by Ivan_han 20131031
			if(cbFirstValueList==0 && ibankerflag==1)
				return true;
			if(cbFirstValueList==0 && ibankerflag==2)
				return false;

			//获取公数
			BYTE cbNextCountJQK=0;
			BYTE cbFirstCountJQK=0;
			for (BYTE i=0;i<MAX_COUNT;i++)
			{
				if (GetCardValue(cbNextData[i])>10) cbNextCountJQK++;
				if (GetCardValue(cbFirstData[i])>10) cbFirstCountJQK++;
			}

			//公数对比
			if (cbFirstCountJQK!=cbNextCountJQK) return cbFirstCountJQK>cbNextCountJQK;

			//对比散牌
			//BYTE cbNextLogicValue=GetCardLogicValue(cbNextData[0]);
			//BYTE cbFirstLogicValue=GetCardLogicValue(cbFirstData[0]);
			TCardData cbNextMaxData=FindMaxElement(cbNextData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextMaxData);
			TCardData cbFirstMaxData=FindMaxElement(cbFirstData,cbCardCount,CGameLogic::GetCardLogicValue);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstMaxData);

			//对比散牌
			return cbFirstLogicValue>cbNextLogicValue;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////

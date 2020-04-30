#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include<fstream>
#include<iostream>

using namespace std;

typedef unsigned char TCardData;//单张扑克
typedef unsigned char TCardType;//牌型={1无牛,3-11牛一到牛九,14牛牛,15银牛，16金牛，17炸弹，18五小牛}

#define GAME_POSITION_COUNT 5
#define OX_MAX_COUNT   5          //最大数目
#define FULL_COUNT     54         //全牌数目
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))//数组元素个数

//数值掩码
#define MASK_COLOR     0xF0        //花色掩码
#define MASK_VALUE     0x0F        //数值掩码
//获取数值
unsigned char GetCardValue(TCardData cbCardData) { return cbCardData&MASK_VALUE; }
//获取花色
unsigned char GetCardColor(TCardData cbCardData) { return cbCardData&MASK_COLOR; }
//获取花色
unsigned char GetCardColor2(TCardData cbCardData) { return (cbCardData&MASK_COLOR)>>4; }

//扑克数据
const TCardData m_cbCardListData[FULL_COUNT]=
{
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D, //方块 A - K
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D, //梅花 A - K
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D, //红桃 A - K
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D, //黑桃 A - K
	0x4E,0x4F,
};



//混乱扑克
void RandCardList(TCardData cbCardBuffer[],unsigned char cbBufferCount)
{
	//混乱准备
	TCardData cbCardData[CountArray(m_cbCardListData)];
	memcpy(cbCardData,m_cbCardListData,sizeof(m_cbCardListData));

	//混乱扑克
	unsigned char bRandCount=0,bPosition=0;
	do
	{
		bPosition=rand()%(CountArray(m_cbCardListData)-bRandCount);
		cbCardBuffer[bRandCount++]=cbCardData[bPosition];
		cbCardData[bPosition]=cbCardData[CountArray(m_cbCardListData)-bRandCount];
	} while (bRandCount<cbBufferCount);

	return;
}

/*============================begin of GoodCard Function==========================*/
//取[0,nCount-1]之间除例外值之外的随机整数
static int GetRandIndex(int nCount,vector<int>& vecIndex);

//根据概率选择
static int SelectByProb(int arr[],int arrProb[],int count,int total=0);



/* ========================= end of GoodCard Function======================= */

unsigned char GetCardLogicValue2(TCardData cbCardData,bool bNo11/*=false*/)
{
	unsigned char cbValue=GetCardValue(cbCardData);

	//获取花色
	unsigned char cbColor=GetCardColor2(cbCardData);

	if(cbValue>10)
	{
		cbValue = 10;
	}
	if(cbColor==0x4 && !bNo11)
	{
		return 11;
	}
	return cbValue;
}

//取[nMin,nMax]之间的随机整数
int GetRand(const int nMin,const int nMax)
{
	if ( nMin > nMax)
		return nMin;
	return rand()%(nMax-nMin+1)+nMin;
}

//取[0,nCount-1]之间除例外值之外的随机整数
int GetRandIndex(int nCount,vector<int>& vecIndex)
{
	if(nCount<2)
		return -1;
	int nMaxRcount=10000;
	int nRCount=0;
	for(;;nRCount++)
	{
		int Index=GetRand(0,nCount-1);
		vector<int>::iterator p;
		p=std::find(vecIndex.begin(),vecIndex.end(),Index);
		if(p==vecIndex.end())
		{
			vecIndex.push_back(Index);
			return Index;
		}
		if(nRCount>=nMaxRcount)
			return -1;
	}
	return -1;
}



void shuffle(vector<TCardData>& the_vector)
{
	
}

int main()
{
	srand((unsigned int)time(NULL));
	
	//获取扑克
	TCardData bTempArray[FULL_COUNT]={0};
	RandCardList(bTempArray,sizeof(bTempArray));
	for(int i=0;i<FULL_COUNT;i++)
	{
		printf("%d\n",bTempArray[i]);
	}

	printf("第一次打乱后：\n");
	vector<TCardData>::iterator Iter;
	vector<TCardData> the_vector(bTempArray,bTempArray+FULL_COUNT);
	for(int i=0;i<FULL_COUNT;i++)
	{
		printf("%d\n",the_vector[i]);
	}
	//printf("第二次打乱后：\n");
	//random_shuffle(the_vector.begin(),the_vector.end());
	//for(int i=0;i<FULL_COUNT;i++)
	//{
	//	printf("%d\n",the_vector[i]);
	//}

	//扑克数据
	static TCardData cbCardData[22]=
	{
		0x01,0x02,0x03,0x04,0x05, //方块 A - 5
		0x11,0x12,0x13,0x14,0x15, //梅花 A - 5
		0x21,0x22,0x23,0x24,0x25, //红桃 A - 5
		0x31,0x32,0x33,0x34,0x35, //黑桃 A - 5
		0x4E,0x4F,
	};

	static unsigned char cbCardDataValue[22]=
	{
		1,2,3,4,5, //方块 A - 5
		1,2,3,4,5, //梅花 A - 5
		1,2,3,4,5, //红桃 A - 5
		1,2,3,4,5, //黑桃 A - 5
		0,0,
	};

	ofstream outf("NiuNiu.txt"); 
	outf<<"--------统计分析--------"<<endl;
	char szTemp[100]={0};
	int nCount=0;
	for(int i=0;i<22;i++)
		for(int j=i+1;j<22;j++)
			for(int k=j+1;k<22;k++)
				for(int m=k+1;m<22;m++)
					for(int n=m+1;n<22;n++)
		{
			//五小牛的判断
			if(cbCardDataValue[i]+cbCardDataValue[j]+cbCardDataValue[k]+cbCardDataValue[m]+cbCardDataValue[n]<11)
			{
				sprintf(szTemp,"{%d,%d,%d,%d,%d},\n",(int)cbCardData[i],(int)cbCardData[j],(int)cbCardData[k],(int)cbCardData[m],(int)cbCardData[n]);
				outf<<szTemp;
				nCount++;
			}
		}
    printf("五小牛牌型的组合数：%d\n",nCount);
	/*cout<<CountArray(m_cbFiveSmallCardListData)<<endl;

	vector<TCardData> v1;
	bool bret=PeekFIVESMALL(the_vector,v1);
	printf("bret=%d\n",bret);
	for(int i=0;i<v1.size();i++)
	{
		printf("%d\n",v1[i]);
	}*/
	return 0;
}
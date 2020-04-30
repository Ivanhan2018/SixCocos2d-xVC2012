#ifndef SINGLECARD1_H
#define SINGLECARD1_H
#include<time.h>
#include<stdlib.h>
#include<cassert>
#include<cstring>
using namespace std;

//数目定义
#define MAX_COUNT     20         //最大数目
#define FULL_COUNT     54         //全牌数目
#define GOOD_CARD_COUTN    38         //好牌数目
#define BACK_COUNT     3         //底牌数目
#define NORMAL_COUNT    17         //常规数目
typedef unsigned char BYTE;
const BYTE m_cbGoodcardData[GOOD_CARD_COUTN]=
{
 0x01,0x02,
  0x11,0x12,
  0x21,0x22,
  0x31,0x32,
  0x4E,0x4F,
  0x07,0x08,0x09,
  0x17,0x18,0x19,
  0x27,0x28,0x29,
  0x37,0x38,0x39,
  0x0A,0x0B,0x0C,0x0D,
  0x1A,0x1B,0x1C,0x1D,
  0x2A,0x2B,0x2C,0x2D,
  0x3A,0x3B,0x3C,0x3D
};
//扑克数据
const BYTE m_cbCardData[FULL_COUNT]=
{
 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D, //方块 A - K
  0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D, //梅花 A - K
  0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D, //红桃 A - K
  0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D, //黑桃 A - K
  0x4E,0x4F,
};
//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
//得到好牌
void GetGoodCardData(BYTE cbGoodCardData[NORMAL_COUNT])
{
 //混乱准备
 BYTE cbCardData[CountArray(m_cbGoodcardData)];
 BYTE cbCardBuffer[CountArray(m_cbGoodcardData)];
 memcpy(cbCardData,m_cbGoodcardData,sizeof(m_cbGoodcardData));
 //混乱扑克
 BYTE cbRandCount=0,cbPosition=0;
 BYTE cbBufferCount=CountArray(m_cbGoodcardData);
 do
 {
  cbPosition=rand()%(cbBufferCount-cbRandCount);
  cbCardBuffer[cbRandCount++]=cbCardData[cbPosition];
  cbCardData[cbPosition]=cbCardData[cbBufferCount-cbRandCount];
 } while (cbRandCount<cbBufferCount);
 //复制好牌
 memcpy(cbGoodCardData, cbCardBuffer, NORMAL_COUNT) ;
}
//扑克类型
#define CT_ERROR     0         //错误类型
#define CT_SINGLE     1         //单牌类型
#define CT_DOUBLE     2         //对牌类型
#define CT_THREE     3         //三条类型
#define CT_SINGLE_LINE    4         //单连类型
#define CT_DOUBLE_LINE    5         //对连类型
#define CT_THREE_LINE    6         //三连类型
#define CT_THREE_LINE_TAKE_ONE  7         //三带一单
#define CT_THREE_LINE_TAKE_TWO  8         //三带一对
#define CT_FOUR_LINE_TAKE_ONE  9         //四带两单
#define CT_FOUR_LINE_TAKE_TWO  10         //四带两对
#define CT_BOMB_CARD    11         //炸弹类型
#define CT_MISSILE_CARD    12         //火箭类型
//数值掩码
#define MASK_COLOR     0xF0        //花色掩码
#define MASK_VALUE     0x0F        //数值掩码
//获取数值
BYTE GetCardValue(BYTE cbCardData) { return cbCardData&MASK_VALUE; }
//获取花色
BYTE GetCardColor(BYTE cbCardData) { return cbCardData&MASK_COLOR; }
//逻辑数值（3-K,A,2,小王,大王分别为3-17）
BYTE GetCardLogicValue(BYTE cbCardData)
{
 //扑克属性
 BYTE cbCardColor=GetCardColor(cbCardData);
 BYTE cbCardValue=GetCardValue(cbCardData);
#ifdef _DEBUG
 if(cbCardValue<=0 || cbCardValue>(MASK_VALUE&0x4f))
  return 0 ;
#endif
 assert(cbCardValue>0 && cbCardValue<=(MASK_VALUE&0x4f)) ;
 //转换数值
 if (cbCardColor==0x40) return cbCardValue+2;
 return (cbCardValue<=2)?(cbCardValue+13):cbCardValue;
}
//分析结构
struct tagAnalyseResult
{
 BYTE        cbFourCount;      //四张数目
 BYTE        cbThreeCount;      //三张数目
 BYTE        cbDoubleCount;      //两张数目
 BYTE       cbSignedCount;      //单张数目
 BYTE       cbFourCardData[MAX_COUNT];   //四张扑克
 BYTE       cbThreeCardData[MAX_COUNT];   //三张扑克
 BYTE       cbDoubleCardData[MAX_COUNT];  //两张扑克
 BYTE       cbSignedCardData[MAX_COUNT];  //单张扑克
};
//分析扑克(调用前先要排序，火箭计入cbDoubleCount字段)
bool AnalysebCardData(const BYTE cbCardData[], BYTE cbCardCount, tagAnalyseResult & AnalyseResult)
{
 //设置结果
 memset(&AnalyseResult,0x0,sizeof(AnalyseResult));
 //扑克分析
 for (BYTE i=0;i<cbCardCount;i++)
 {
  //变量定义
  BYTE cbSameCount=1;
  BYTE cbLogicValue=GetCardLogicValue(cbCardData[i]);
  if(cbLogicValue<=0) 
   return false;
  //搜索同牌
  for (BYTE j=i+1;j<cbCardCount;j++)
  {
   //获取扑克
   if (GetCardLogicValue(cbCardData[j])!=cbLogicValue) break;
   //设置变量
   cbSameCount++;
  }
  //设置结果
  switch (cbSameCount)
  {
  case 1:  //单张
   {
    BYTE cbIndex=AnalyseResult.cbSignedCount++;
    AnalyseResult.cbSignedCardData[cbIndex*cbSameCount]=cbCardData[i];
    break;
   }
  case 2:  //两张
   {
    BYTE cbIndex=AnalyseResult.cbDoubleCount++;
    AnalyseResult.cbDoubleCardData[cbIndex*cbSameCount]=cbCardData[i];
    AnalyseResult.cbDoubleCardData[cbIndex*cbSameCount+1]=cbCardData[i+1];
    break;
   }
  case 3:  //三张
   {
    BYTE cbIndex=AnalyseResult.cbThreeCount++;
    AnalyseResult.cbThreeCardData[cbIndex*cbSameCount]=cbCardData[i];
    AnalyseResult.cbThreeCardData[cbIndex*cbSameCount+1]=cbCardData[i+1];
    AnalyseResult.cbThreeCardData[cbIndex*cbSameCount+2]=cbCardData[i+2];
    break;
   }
  case 4:  //四张
   {
    BYTE cbIndex=AnalyseResult.cbFourCount++;
    AnalyseResult.cbFourCardData[cbIndex*cbSameCount]=cbCardData[i];
    AnalyseResult.cbFourCardData[cbIndex*cbSameCount+1]=cbCardData[i+1];
    AnalyseResult.cbFourCardData[cbIndex*cbSameCount+2]=cbCardData[i+2];
    AnalyseResult.cbFourCardData[cbIndex*cbSameCount+3]=cbCardData[i+3];
    break;
   }
  }
  //设置索引
  i+=cbSameCount-1;
 }
 return true;
}
 
//获取类型
BYTE GetCardType(const BYTE cbCardData[], BYTE cbCardCount)
{
 //简单牌型
 switch (cbCardCount)
 {
 case 0: //空牌
  {
   return CT_ERROR;
  }
 case 1: //单牌
  {
   return CT_SINGLE;
  }
 case 2: //对牌火箭
  {
   //牌型判断
   if ((cbCardData[0]==0x4F)&&(cbCardData[1]==0x4E)) return CT_MISSILE_CARD;
   if (GetCardLogicValue(cbCardData[0])==GetCardLogicValue(cbCardData[1])) return CT_DOUBLE;
   return CT_ERROR;
  }
 }
 //分析扑克
 tagAnalyseResult AnalyseResult;
 if(!AnalysebCardData(cbCardData,cbCardCount,AnalyseResult)) 
  return CT_ERROR ;
 //四牌判断
 if (AnalyseResult.cbFourCount>0)
 {
  //牌型判断
  if ((AnalyseResult.cbFourCount==1)&&(cbCardCount==4)) return CT_BOMB_CARD;
  // if ((AnalyseResult.cbFourCount==1)&&(AnalyseResult.cbSignedCount==2)&&(cbCardCount==6)) return CT_FOUR_LINE_TAKE_ONE;
  if ((AnalyseResult.cbFourCount==1)&&(AnalyseResult.cbSignedCount==2)&&(cbCardCount==6)) return CT_FOUR_LINE_TAKE_ONE;
  if ((AnalyseResult.cbFourCount==1)&&(AnalyseResult.cbDoubleCount==2)&&(cbCardCount==8)) return CT_FOUR_LINE_TAKE_TWO;
  return CT_ERROR;
 }
 //三牌判断
 if (AnalyseResult.cbThreeCount>0)
 {
  //三条类型
  if(AnalyseResult.cbThreeCount==1 && cbCardCount==3) return CT_THREE ;
  //连牌判断
  if (AnalyseResult.cbThreeCount>1)
  {
   //变量定义
   BYTE cbCardData=AnalyseResult.cbThreeCardData[0];
   BYTE cbFirstLogicValue=GetCardLogicValue(cbCardData);
   //错误过虑
   if (cbFirstLogicValue>=15) return CT_ERROR;
   //连牌判断
   for (BYTE i=1;i<AnalyseResult.cbThreeCount;i++)
   {
    BYTE cbCardData=AnalyseResult.cbThreeCardData[i*3];
    if (cbFirstLogicValue!=(GetCardLogicValue(cbCardData)+i)) return CT_ERROR;
   }
  }
  //牌形判断
  if (AnalyseResult.cbThreeCount*3==cbCardCount) return CT_THREE_LINE;
  if (AnalyseResult.cbThreeCount*4==cbCardCount) return CT_THREE_LINE_TAKE_ONE;
  if ((AnalyseResult.cbThreeCount*5==cbCardCount)&&(AnalyseResult.cbDoubleCount==AnalyseResult.cbThreeCount)) return CT_THREE_LINE_TAKE_TWO;
  return CT_ERROR;
 }
 //两张类型
 if (AnalyseResult.cbDoubleCount>=3)
 {
  //变量定义
  BYTE cbCardData=AnalyseResult.cbDoubleCardData[0];
  BYTE cbFirstLogicValue=GetCardLogicValue(cbCardData);
  //错误过虑
  if (cbFirstLogicValue>=15) return CT_ERROR;
  //连牌判断
  for (BYTE i=1;i<AnalyseResult.cbDoubleCount;i++)
  {
   BYTE cbCardData=AnalyseResult.cbDoubleCardData[i*2];
   if (cbFirstLogicValue!=(GetCardLogicValue(cbCardData)+i)) return CT_ERROR;
  }
  //二连判断
  if ((AnalyseResult.cbDoubleCount*2)==cbCardCount) return CT_DOUBLE_LINE;
  return CT_ERROR;
 }
 //单张判断
 if ((AnalyseResult.cbSignedCount>=5)&&(AnalyseResult.cbSignedCount==cbCardCount))
 {
  //变量定义
  BYTE cbCardData=AnalyseResult.cbSignedCardData[0];
  BYTE cbFirstLogicValue=GetCardLogicValue(cbCardData);
  //错误过虑
  if (cbFirstLogicValue>=15) return CT_ERROR;
  //连牌判断
  for (BYTE i=1;i<AnalyseResult.cbSignedCount;i++)
  {
   BYTE cbCardData=AnalyseResult.cbSignedCardData[i];
   if (cbFirstLogicValue!=(GetCardLogicValue(cbCardData)+i)) return CT_ERROR;
  }
  return CT_SINGLE_LINE;
 }
 return CT_ERROR;
}
//扑克定义
class CSingleCard
{
public :
 //构造函数
 CSingleCard()
 {  
  m_cCardID=0;
  m_cColor=0;
  m_cValue=0;
  m_bLegal=false;
  strcpy(m_szCardName,"");
 }
 //构造函数
 CSingleCard(unsigned char nCardID)
 {  
  m_cCardID=nCardID;
  m_cColor=(nCardID & 0xf0)>>4;
  m_cValue=nCardID & 0x0f;
  m_bLegal=IsLegal(nCardID);
  strcpy(m_szCardName,GetCardName(nCardID));
 }
 // 重载"="
 void operator = (const CSingleCard& ob)  
 {  
  //memcpy(&this->m_cCardID,&ob.m_cCardID,sizeof(ob)); 
  memcpy(this,&ob,sizeof(ob));
 }
 static bool IsLegal(unsigned char nCardID)
 {
  unsigned char nColor=(nCardID & 0xf0)>>4;
  unsigned char nValue=nCardID & 0x0f;
  if(nCardID==0x4E||nCardID==0x4F||(nColor<4&&nColor>=0)&&(nValue<14&&nValue>0))
   return true;
  else
   return false;
 }
 static unsigned char GetCardID(unsigned char nColor,unsigned char nValue)
 {
  unsigned char nCardID=nColor*16+nValue;
  return nCardID;
 }
 static const char * GetCardName(unsigned char nCardID)
 {
  bool bLegal=IsLegal(nCardID);
  assert(bLegal && "GetCardName的输入参数有误!");
  if(bLegal)
  {
   static const char * szCardName[5][15]={
    {"方块A","方块2","方块3","方块4","方块5","方块6","方块7","方块8","方块9","方块10","方块J","方块Q","方块K","",""},
    {"梅花A","梅花2","梅花3","梅花4","梅花5","梅花6","梅花7","梅花8","梅花9","梅花10","梅花J","梅花Q","梅花K","",""},
    {"红桃A","红桃2","红桃3","红桃4","红桃5","红桃6","红桃7","红桃8","红桃9","红桃10","红桃J","红桃Q","红桃K","",""},
    {"黑桃A","黑桃2","黑桃3","黑桃4","黑桃5","黑桃6","黑桃7","黑桃8","黑桃9","黑桃10","黑桃J","黑桃Q","黑桃K","",""},
    {"","","","","","","","","","","","","","小王","大王"},
   };
   unsigned char nColorIndex=(nCardID & 0xf0)>>4;
   unsigned char nValueIndex=(nCardID & 0x0f)-1;
   return szCardName[nColorIndex][nValueIndex];
  }
  else
   return "";
 }
 //牌的实际大小，比如斗地主中2就比A大
 //3-10 J Q  K  A  2  Jo小 Jo大
 //1-8  9 10 11 12 13 14   15
 static unsigned char GetPowByCardValue(unsigned char nCardValue)
 {
  if(nCardValue>2&&nCardValue<14)
   return nCardValue-2;
  if(nCardValue==1||nCardValue==2)
   return nCardValue+11;
  if(nCardValue==14||nCardValue==15)
   return nCardValue;
  return 0;
 }
public:
 unsigned char m_cCardID;//54个值
 unsigned char m_cColor;//花色，0方块，1梅花，2红桃，3黑桃，4王//牌的类型 黑桃=0 红桃=1 梅花=2 方块=3
 unsigned char m_cValue;//数值，A-K是1-13，小王是14，大王是15//牌面数目 2-10 J=11 Q=12 K=13 A=1 Jok(小)=14 Jok(大)=15 大与15表示此牌不存在
 bool m_bLegal;//是否是合法的牌
 char m_szCardName[8];//牌名：方块/梅花/红桃/黑桃A-K,小王/大王
};
void SortCard(CSingleCard ca[])
{
 CSingleCard temp;
 for(int i=0;i<20 && ca[i].m_bLegal;i++)
 for(int j=i+1;j<20 && ca[j].m_bLegal<=15;j++)
 if(CSingleCard::GetPowByCardValue(ca[i].m_cValue)>CSingleCard::GetPowByCardValue(ca[j].m_cValue))
 {
  temp=ca[i];
  ca[i]=ca[j];
  ca[j]=temp;
 }
}
//排序类型
#define ST_ORDER     0         //大小排序,例如红桃2,梅花2,方块2,红桃A,梅花A,方块A,红桃K,梅花K,方块K
#define ST_COUNT     1         //数目排序
//排列扑克
void SortCardList(BYTE cbCardData[], BYTE cbCardCount, BYTE cbSortType)
{
 //数目过虑
 if (cbCardCount==0) return;
 //转换数值
 //BYTE cbSortValue[MAX_COUNT];
    BYTE cbSortValue[FULL_COUNT];
 for (BYTE i=0;i<cbCardCount;i++) cbSortValue[i]=GetCardLogicValue(cbCardData[i]); 
 //排序操作
 bool bSorted=true;
 BYTE cbThreeCount,cbLast=cbCardCount-1;
 do
 {
  bSorted=true;
  for (BYTE i=0;i<cbLast;i++)
  {
   if ((cbSortValue[i]<cbSortValue[i+1])||
    ((cbSortValue[i]==cbSortValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
   {
    //交换位置
    cbThreeCount=cbCardData[i];
    cbCardData[i]=cbCardData[i+1];
    cbCardData[i+1]=cbThreeCount;
    cbThreeCount=cbSortValue[i];
    cbSortValue[i]=cbSortValue[i+1];
    cbSortValue[i+1]=cbThreeCount;
    bSorted=false;
   } 
  }
  cbLast--;
 } while(bSorted==false);
 //数目排序
 if (cbSortType==ST_COUNT)
 {
  //分析扑克
  BYTE cbIndex=0;
  tagAnalyseResult AnalyseResult;
  AnalysebCardData(cbCardData,cbCardCount,AnalyseResult);
  //拷贝四牌
  memcpy(&cbCardData[cbIndex],AnalyseResult.cbFourCardData,sizeof(BYTE)*AnalyseResult.cbFourCount*4);
  cbIndex+=AnalyseResult.cbFourCount*4;
  //拷贝三牌
  memcpy(&cbCardData[cbIndex],AnalyseResult.cbThreeCardData,sizeof(BYTE)*AnalyseResult.cbThreeCount*3);
  cbIndex+=AnalyseResult.cbThreeCount*3;
  //拷贝对牌
  memcpy(&cbCardData[cbIndex],AnalyseResult.cbDoubleCardData,sizeof(BYTE)*AnalyseResult.cbDoubleCount*2);
  cbIndex+=AnalyseResult.cbDoubleCount*2;
  //拷贝单牌
  memcpy(&cbCardData[cbIndex],AnalyseResult.cbSignedCardData,sizeof(BYTE)*AnalyseResult.cbSignedCount);
  cbIndex+=AnalyseResult.cbSignedCount;
 }
 return;
}
//分析炸弹
void GetAllBomCard(BYTE const cbHandCardData[], BYTE const cbHandCardCount, BYTE cbBomCardData[], BYTE &cbBomCardCount)
{
 BYTE cbTmpCardData[MAX_COUNT] ;
 memcpy(cbTmpCardData, cbHandCardData, cbHandCardCount) ;
 //大小排序
 SortCardList(cbTmpCardData, cbHandCardCount, ST_ORDER);
 cbBomCardCount = 0 ;
 if(cbHandCardCount<2) return ;
 //双王炸弹
 if(0x4F==cbTmpCardData[0] && 0x4E==cbTmpCardData[1])
 {
  cbBomCardData[cbBomCardCount++] = cbTmpCardData[0] ;
  cbBomCardData[cbBomCardCount++] = cbTmpCardData[1] ;
 }
 //扑克分析
 for (BYTE i=0;i<cbHandCardCount;i++)
 {
  //变量定义
  BYTE cbSameCount=1;
  BYTE cbLogicValue=GetCardLogicValue(cbTmpCardData[i]);
  //搜索同牌
  for (BYTE j=i+1;j<cbHandCardCount;j++)
  {
   //获取扑克
   if (GetCardLogicValue(cbTmpCardData[j])!=cbLogicValue) break;
   //设置变量
   cbSameCount++;
  }
  if(4==cbSameCount)
  {
   cbBomCardData[cbBomCardCount++] = cbTmpCardData[i] ;
   cbBomCardData[cbBomCardCount++] = cbTmpCardData[i+1] ;
   cbBomCardData[cbBomCardCount++] = cbTmpCardData[i+2] ;
   cbBomCardData[cbBomCardCount++] = cbTmpCardData[i+3] ;
  }
  //设置索引
  i+=cbSameCount-1;
 }
}
//删除扑克
bool RemoveCard(const BYTE cbRemoveCard[], BYTE cbRemoveCount, BYTE cbCardData[], BYTE cbCardCount)
{
 //检验数据
 assert(cbRemoveCount<=cbCardCount);
 if(cbRemoveCount>cbCardCount)
  return false ;
 //定义变量
 BYTE cbDeleteCount=0,cbTempCardData[MAX_COUNT];
 if (cbCardCount>CountArray(cbTempCardData)) return false;
 memcpy(cbTempCardData,cbCardData,cbCardCount*sizeof(cbCardData[0]));
 //置零扑克
 for (BYTE i=0;i<cbRemoveCount;i++)
 {
  for (BYTE j=0;j<cbCardCount;j++)
  {
   if (cbRemoveCard[i]==cbTempCardData[j])
   {
    cbDeleteCount++;
    cbTempCardData[j]=0;
    break;
   }
  }
 }
 if (cbDeleteCount!=cbRemoveCount) return false;
 //清理扑克
 BYTE cbCardPos=0;
 for (BYTE i=0;i<cbCardCount;i++)
 {
  if (cbTempCardData[i]!=0) cbCardData[cbCardPos++]=cbTempCardData[i];
 }
 return true;
}
//分析顺子
void GetAllLineCard(BYTE const cbHandCardData[], BYTE const cbHandCardCount, BYTE cbLineCardData[], BYTE &cbLineCardCount)
{
 BYTE cbTmpCard[MAX_COUNT] ;
 memcpy(cbTmpCard, cbHandCardData, cbHandCardCount) ;
 //大小排序
 SortCardList(cbTmpCard, cbHandCardCount, ST_ORDER) ;
 cbLineCardCount = 0 ;
 //数据校验
 if(cbHandCardCount<5) return ;
 BYTE cbFirstCard = 0 ;
 //去除2和王
 for(BYTE i=0 ; i<cbHandCardCount ; ++i) if(GetCardLogicValue(cbTmpCard[i])<15) {cbFirstCard = i ; break ;}
 BYTE cbSingleLineCard[12] ;
 BYTE cbSingleLineCount=0 ;
 BYTE cbLeftCardCount = cbHandCardCount ;
 bool bFindSingleLine = true ;
 //连牌判断
 while (cbLeftCardCount>=5 && bFindSingleLine)
 {
  cbSingleLineCount=1 ;
  bFindSingleLine = false ;
  BYTE cbLastCard = cbTmpCard[cbFirstCard] ;
  cbSingleLineCard[cbSingleLineCount-1] = cbTmpCard[cbFirstCard] ;
  for (BYTE i=cbFirstCard+1; i<cbLeftCardCount; i++)
  {
   BYTE cbCardData=cbTmpCard[i];
   //连续判断
   if (1!=(GetCardLogicValue(cbLastCard)-GetCardLogicValue(cbCardData)) && GetCardValue(cbLastCard)!=GetCardValue(cbCardData)) 
   {
    cbLastCard = cbTmpCard[i] ;
    if(cbSingleLineCount<5) 
    {
     cbSingleLineCount = 1 ;
     cbSingleLineCard[cbSingleLineCount-1] = cbTmpCard[i] ;
     continue ;
    }
    else break ;
   }
   //同牌判断
   else if(GetCardValue(cbLastCard)!=GetCardValue(cbCardData))
   {
    cbLastCard = cbCardData ;
    cbSingleLineCard[cbSingleLineCount] = cbCardData ;
    ++cbSingleLineCount ;
   }     
  }
  //保存数据
  if(cbSingleLineCount>=5)
  {
   RemoveCard(cbSingleLineCard, cbSingleLineCount, cbTmpCard, cbLeftCardCount) ;
   memcpy(cbLineCardData+cbLineCardCount , cbSingleLineCard, sizeof(BYTE)*cbSingleLineCount) ;
   cbLineCardCount += cbSingleLineCount ;
   cbLeftCardCount -= cbSingleLineCount ;
   bFindSingleLine = true ;
  }
 }
}

/*
//分析三条
void GetAllThreeCard(BYTE const cbHandCardData[], BYTE const cbHandCardCount, BYTE cbThreeCardData[], BYTE &cbThreeCardCount)
{
……
}
//分析对子
void GetAllDoubleCard(BYTE const cbHandCardData[], BYTE const cbHandCardCount, BYTE cbDoubleCardData[], BYTE &cbDoubleCardCount)
{
 ……}
//分析单牌
void GetAllSingleCard(BYTE const cbHandCardData[], BYTE const cbHandCardCount, BYTE cbSingleCardData[], BYTE &cbSingleCardCount)
{
 ……}
//对比扑克
bool CompareCard(const BYTE cbFirstCard[], const BYTE cbNextCard[], BYTE cbFirstCount, BYTE cbNextCount)
{
 ……}
 
*/

#endif

 // //获取类型
 // BYTE cbNextType=GetCardType(cbCardData,9);
 // assert(cbNextType==CT_ERROR);
// /*  BYTE cbThreeCardData[MAX_COUNT];
 // BYTE cbThreeCardCount=0 ;
 // GetAllThreeCard(cbCardData, 9, cbThreeCardData, cbThreeCardCount) ; */
 // BYTE cbCardData2[5]={0x0a,0x0b,0x1c,0x3d,0x01};//{0x01,0x3d,0x1c,0x0b,0x0a};
    // SortCardList(cbCardData2,5, ST_ORDER);//加上去，否则得出的类型不正确
 // BYTE cbNextType2=GetCardType(cbCardData2,5);
 // assert(cbNextType2==CT_SINGLE_LINE);
// /*  BYTE cbLineCard2[MAX_COUNT] ;
 // BYTE cbLineCardCount2;
 // GetAllLineCard(cbCardData2, 5, cbLineCard2, cbLineCardCount2) ; */
 // BYTE cbCardData3[6]={0x0a,0x0b,0x1c,0x3d,0x01,0x08};//{0x01,0x3d,0x1c,0x0b,0x0a};
 // SortCardList(cbCardData3,6, ST_ORDER);
 // BYTE cbNextType3=GetCardType(cbCardData3,6);
 // assert(cbNextType3==CT_ERROR);
// /*  BYTE cbLineCard3[MAX_COUNT] ;
 // BYTE cbLineCardCount3;
 // GetAllLineCard(cbCardData3, 6, cbLineCard3, cbLineCardCount3) ; */
 // BYTE cbCardData4[9]={0x01,0x0c,0x11,0x1c,0x21,0x2c,0x0d,0x1d,0x2d};
 // SortCardList(cbCardData4,9, ST_ORDER);
 // BYTE cbNextType4=GetCardType(cbCardData4,9);
 // assert(cbNextType4==CT_THREE_LINE);
 // BYTE cbCardData5[11]={0x01,0x3d,0x11,0x1c,0x21,0x31,0x0d,0x1d,0x4f,0x2d,0x4e};
 // SortCardList(cbCardData5,11, ST_ORDER);
 // BYTE cbNextType5=GetCardType(cbCardData5,11);
 // assert(cbNextType5==CT_ERROR);
 // printf("\n-------\n");
 // for (int i = 0; i < 11; i++) 
 // {
  // printf("%s,",CSingleCard::GetCardName(cbCardData5[i]));
 // }
 // printf("\n-------\n");
 // //是否有炸
 // BYTE cbAllBombCardData[MAX_COUNT], cbAllBombCount=0 ;
 // GetAllBomCard(cbCardData5, 11, cbAllBombCardData, cbAllBombCount) ;//函数内部已调用了SortCardList，不需要调用SortCardList
 // //大王,小王,黑桃A,红桃A,梅花A,方块A,黑桃K,红桃K,梅花K,方块K,
 // for (int i = 0; i < cbAllBombCount; i++) 
 // {
  // printf("%s,",CSingleCard::GetCardName(cbAllBombCardData[i]));
 // }
 // printf("\n-------\n");
// /*  BYTE cbLineCard5[MAX_COUNT] ;
 // BYTE cbLineCardCount5;
 // GetAllLineCard(cbCardData5, 11, cbLineCard5, cbLineCardCount5); */
 // printf("\n-------\n");
// /*  BYTE cbThreeCardData5[MAX_COUNT];
 // BYTE cbThreeCardCount5=0 ;
 // GetAllThreeCard(cbCardData5, 11, cbThreeCardData5, cbThreeCardCount5) ; */
 // //黑桃A,红桃A,梅花A,黑桃K,红桃K,梅花K,
 // for (int i = 0; i < cbThreeCardCount5; i++) 
 // {
  // printf("%s,",CSingleCard::GetCardName(cbThreeCardData5[i]));
 // }
 // printf("\n-------\n");
// /*  BYTE cbDoubleCardData5[MAX_COUNT] ;
 // BYTE cbDoubleCardcount5=0; 
 // GetAllDoubleCard(cbCardData5,11, cbDoubleCardData5, cbDoubleCardcount5) ; */
 // //黑桃A,红桃A,黑桃K,红桃K,
 // for (int i = 0; i < cbDoubleCardcount5; i++) 
 // {
  // printf("%s,",CSingleCard::GetCardName(cbDoubleCardData5[i]));
 // }
 // printf("\n-------\n");
// /*  //计算单牌
 // BYTE cbSingleCard5[MAX_COUNT] ;
 // BYTE cbSingleCardCount5=0 ;
 // GetAllSingleCard(cbCardData5,11, cbSingleCard5, cbSingleCardCount5) ;
 // //大王,小王,梅花Q,
 // for (int i = 0; i < cbSingleCardCount5; i++) 
 // {
  // printf("%s,",CSingleCard::GetCardName(cbSingleCard5[i]));
 // } */
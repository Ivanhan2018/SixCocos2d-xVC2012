#ifndef SINGLECARD_H
#define SINGLECARD_H
#include<time.h>
#include<stdlib.h>
#include<cassert>
#include<cstring>
using namespace std;

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
#endif
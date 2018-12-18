// CSingleCard.h: interface for the CSingleCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CSingleCard_H)
#define CSingleCard_H
#include "Export.h"
#include<time.h>
#include<stdlib.h>
#include<cassert>
#include<cstring>
using namespace std;

//�˿˶���
class EXPORT_DLL CSingleCard
{
public :
 //���캯��
 CSingleCard()
 {  
  m_cCardID=0;
  m_cColor=0;
  m_cValue=0;
  m_bLegal=false;
  strcpy(m_szCardName,"");
 }
 //���캯��
 CSingleCard(unsigned char nCardID)
 {  
  m_cCardID=nCardID;
  m_cColor=(nCardID & 0xf0)>>4;
  m_cValue=nCardID & 0x0f;
  m_bLegal=IsLegal(nCardID);
  strcpy(m_szCardName,GetCardName(nCardID));
 }
 // ����"="
 void operator = (const CSingleCard& ob)  
 {  
  //memcpy(&this->m_cCardID,&ob.m_cCardID,sizeof(ob)); 
  memcpy(this,&ob,sizeof(ob));
 }
 static inline bool IsLegal(unsigned char nCardID)
 {
  unsigned char nColor=(nCardID & 0xf0)>>4;
  unsigned char nValue=nCardID & 0x0f;
  if(nCardID==0x4E||nCardID==0x4F||(nColor<4&&nColor>=0)&&(nValue<14&&nValue>0))
   return true;
  else
   return false;
 }
 static inline unsigned char GetCardID(unsigned char nColor,unsigned char nValue)
 {
  unsigned char nCardID=nColor*16+nValue;
  return nCardID;
 }
 static inline const char * GetCardName(unsigned char nCardID)
 {
  bool bLegal=IsLegal(nCardID);
  assert(bLegal && "GetCardName�������������!");
  if(bLegal)
  {
   static const char * szCardName[5][15]={
    {"����A","����2","����3","����4","����5","����6","����7","����8","����9","����10","����J","����Q","����K","",""},
    {"÷��A","÷��2","÷��3","÷��4","÷��5","÷��6","÷��7","÷��8","÷��9","÷��10","÷��J","÷��Q","÷��K","",""},
    {"����A","����2","����3","����4","����5","����6","����7","����8","����9","����10","����J","����Q","����K","",""},
    {"����A","����2","����3","����4","����5","����6","����7","����8","����9","����10","����J","����Q","����K","",""},
    {"","","","","","","","","","","","","","С��","����"},
   };
   unsigned char nColorIndex=(nCardID & 0xf0)>>4;
   unsigned char nValueIndex=(nCardID & 0x0f)-1;
   return szCardName[nColorIndex][nValueIndex];
  }
  else
   return "";
 }
 //�Ƶ�ʵ�ʴ�С�����綷������2�ͱ�A��
 //3-10 J Q  K  A  2  JoС Jo��
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
 unsigned char m_cCardID;//54��ֵ
 unsigned char m_cColor;//��ɫ��0���飬1÷����2���ң�3���ң�4��//�Ƶ����� ����=0 ����=1 ÷��=2 ����=3
 unsigned char m_cValue;//��ֵ��A-K��1-13��С����14��������15//������Ŀ 2-10 J=11 Q=12 K=13 A=1 Jok(С)=14 Jok(��)=15 ����15��ʾ���Ʋ�����
 bool m_bLegal;//�Ƿ��ǺϷ�����
 char m_szCardName[8];//����������/÷��/����/����A-K,С��/����
};
static inline void SortCard(CSingleCard ca[])
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

#endif // !defined(CSingleCard_H)

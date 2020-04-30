#include "singlecard1.h"
#include<stdio.h>
#include<vector>
using namespace std;

//数组维数
//#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
 
bool PeekCardDataVec(vector<BYTE>& the_vector,const BYTE v,const int vNum,vector<BYTE>& v1) 
{
 //取动态数组中的nNum个v
 //vector <BYTE> v1;
 //BYTE v=5;//15;//11;
 bool bret=false;
 //int vNum=4;
 assert(vNum>=1 && vNum<=4 && "断言失败提示");
 int vCount=0;
 for(int i=0;i<the_vector.size();i++)
 {
  if(GetCardValue(the_vector[i])==v)
  {
   v1.push_back(the_vector[i]);
   the_vector.erase(the_vector.begin()+i);
   i--;
   vCount++;
   if(vCount==vNum)
   {
    bret=true;
    break;
   }
  }
 }
 static const char*szTip[2]={"成功","失败"};
 static const char*szNum[4]={"单牌","一对","三张","炸弹"};
 printf("取%s%d%s\n",szNum[vNum-1],v,bret?szTip[0]:szTip[1]);
 int nv=v1.size();
 assert(nv>=0 && nv<=4 && "断言失败提示");
 if(!bret)
 {
  for(int i=0;i<vCount;i++)
  {
   the_vector.push_back(v1.back());
   v1.pop_back();//将最后一个成员移出v1
  }
 }
 nv=v1.size();
 assert(nv>=0 && nv<=4 && "断言失败提示");
 return bret;
}
bool PeekCardDataVec(vector<BYTE>& the_vector,const int nType,const BYTE v,const int N,vector<BYTE>& v1) 
{
 //nType=3：取动态数组中的以v开始的长为3N,N∈[2,2]的飞机
    //nType=2：取动态数组中的以v开始的长为2N,N∈[3,5]的连对
    //nType=1：取动态数组中的以v开始的长为N∈[5,10]{<=}[5,12]的顺子（v>=3，且v+N<=15）
 bool bret=false;
 //int N=2;
 int vCount=0;
 for(int j=v;j<v+N;j++)
 {
  for(int i=0;i<the_vector.size();i++)
  {
   if(GetCardLogicValue(the_vector[i])==j&&j<=14)
   {
    v1.push_back(the_vector[i]);
    the_vector.erase(the_vector.begin()+i);
    vCount++;
    if(vCount%nType==0)
    {
     break;
    }
   }
  }
  if(vCount!=(j-v+1)*nType)
  {
   bret=false;
   break;
  }
 }
 if(vCount==nType*N)
 {
  bret=true;
 }
 static const char*szTip[2]={"成功","失败"};
 //printf("取以%d开始的长为3N=%d的飞机%s\n",v,nType*N,bret?szTip[0]:szTip[1]);
    //printf("取以%d开始的长为2N=%d的连对%s\n",v,nType*N,bret?szTip[0]:szTip[1]);
 int nv=v1.size();
 assert(nv>=0 && nv<=nType*N && "断言失败提示");
 if(!bret)
 {
  for(int i=0;i<vCount;i++)
  {
   the_vector.push_back(v1.back());
   v1.pop_back();//将最后一个成员移出v1
  }
 }
 nv=v1.size();
 assert(nv>=0 && nv<=nType*N && "断言失败提示");
 return bret;
}
//取[nMin,nMax]之间的随机整数
int GetRand(const int nMin,const int nMax)
{
 //return (int)(rand()*(nMax-nMin)/RAND_MAX+nMin);
    return rand()%(nMax-nMin+1)+nMin;
}
//取{J=11,Q=12,K=13,A=1,2=2}之间的随机整数
int GetRandJQKA2(void)
{
    int nret=0; 
 for(;;)
 {
  nret=rand()%15+1;
  if(nret==11||nret==12||nret==13||nret==1||nret==2)
   break;
 }
 return nret;
}
//取{小王=14,大王=15}之间的随机整数
int GetRandMissile(void)
{
 int nret=rand()%2+14; 
 return nret;
}
//取{小王=14,大王=15}之外的随机整数
//int GetRandBomb(void)
int GetRandNoMissile(void)
{
 int nret=rand()%13+1; 
 return nret;
}
//取{J=11,Q=12,K=13,A=1,2=2,小王=14,大王=15}之间的随机整数
int GetRandJQKA2Missile(void)
{
 int nret=0; 
 for(;;)
 {
  nret=rand()%15+1;
  if(nret==11||nret==12||nret==13||nret==1||nret==2||nret==14||nret==15)
   break;
 }
 return nret;
}
bool PeekGoodCardType1(vector<BYTE>& the_vector,vector<BYTE>& V1)
{
 //牌型1(17张)：V---炸弹a1(4)-->V1  +  V---飞机e1(6)-->V1  +  V---对子di(6,i=1,2,3,di>=J)-->V1  +  V---单牌g1(1,g1>=J)
 //srand( (unsigned)time( NULL ) );
 //vector <BYTE> V1;
 int nRCount=0;
 int nMaxRcount=10000;
 for(;;nRCount++)
 {
  int a1=GetRandNoMissile();
  //取动态数组中的炸弹a1(4)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,a1,4,v0);
  if(bret)
  {
   V1.insert(V1.end(),v0.begin(),v0.end());
   //V1.swap(v0);
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 for(;;nRCount++)
 {
  int e1=GetRandNoMissile();
  //取动态数组中的飞机e1(6)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,3,e1,2,v0);
  if(bret)
  {
   V1.insert(V1.end(),v0.begin(),v0.end());
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 for(int i=0;i<3;i++)
 for(;;nRCount++)
 {
  int d=GetRandJQKA2();
  //取动态数组中的对子(2*3=6)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,d,2,v0);
  if(bret)
  {
   V1.insert(V1.end(),v0.begin(),v0.end());
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 for(;;nRCount++)
 {
  int g1=GetRandJQKA2Missile();
  //取动态数组中的单牌g1(1)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,g1,1,v0);
  if(bret)
  {
   V1.insert(V1.end(),v0.begin(),v0.end());
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 return true;
}
bool PeekGoodCardType2(vector<BYTE>& the_vector,vector<BYTE>& V2)
{
 //牌型2(17张)：V---炸弹a2(4)-->V2  +  V---飞机e2(6)-->V2  +  V---顺子b2(5)-->V2  +  V---单牌gi(2,i=1,2,gi>=J)-->V2
 //vector <BYTE> V2;
 int nRCount=0;
 int nMaxRcount=10000;
 for(;;nRCount++)
 {
  int a2=GetRandNoMissile();
  //取动态数组中的炸弹a2(4)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,a2,4,v0);
  if(bret)
  {
   V2.insert(V2.end(),v0.begin(),v0.end());
   //V2.swap(v0);
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 for(;;nRCount++)
 {
  int e2=GetRandNoMissile();
  //取动态数组中的飞机e2(6)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,3,e2,2,v0);
  if(bret)
  {
   V2.insert(V2.end(),v0.begin(),v0.end());
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 for(;;nRCount++)
 {
  int b2=GetRand(3,10);
  //取动态数组中的顺子e2(5)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,1,b2,5,v0);
  if(bret)
  {
   V2.insert(V2.end(),v0.begin(),v0.end());
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 for(int i=0;i<2;i++)
 for(;;nRCount++)
 {
  int g2=GetRandJQKA2();
  //取动态数组中的单牌(2*3=6)
  vector <BYTE> v0;
  bool bret=::PeekCardDataVec(the_vector,g2,1,v0);
  if(bret)
  {
   V2.insert(V2.end(),v0.begin(),v0.end());
   break;
  }
  if(nRCount>=nMaxRcount)return false;
 }
 nRCount=0;
 return true;
}
typedef bool(*pPeekFun)(vector<BYTE>& the_vector,vector<BYTE>& V1);
static pPeekFun PeekFun[2]={PeekGoodCardType1,PeekGoodCardType2};
//取出3张随机的底牌
bool PeekRandBackCard(vector<BYTE>& the_vector,vector<BYTE>& Vback)
{
 int nRCount=0;
 for(int i=0;i<3;i++)
  for(;;nRCount++)
  {
   int g=GetRand(1,15);
   //取动态数组中的单牌
   vector <BYTE> v0;
   bool bret=::PeekCardDataVec(the_vector,g,1,v0);
   if(bret)
   {
    Vback.insert(Vback.end(),v0.begin(),v0.end());
    break;
   }
  }
  nRCount=0;
  return true;
}

int main()
{ 
 printf("%d\n",sizeof(pPeekFun));//8
 printf("%d\n",sizeof(PeekFun));//16
 printf("%d\n",CountArray(PeekFun));//2

 BYTE       m_bBackCard[3];      //游戏底牌
 BYTE       m_bHandCardData[3][20]; //手上扑克
 BYTE       m_bCardCount[3];   //扑克数目
 //发送好牌
 vector<BYTE>::iterator   Iter;
 vector<BYTE> the_vector;
 for( int i = 0; i < 54; i++ )
 {
  the_vector.push_back(m_cbCardData[i]);
 }
 srand( (unsigned)time( NULL ) );
 vector <BYTE> V[3];
 vector<BYTE> Vback;
 int nRCount=0;
 int nMaxRcount=10000;
 for(int i=0;i<2;i++)
  for(;;nRCount++)
  {
   int PeekFunIndex=GetRand(0,1);
   vector <BYTE> v0;
   bool bret=PeekFun[PeekFunIndex](the_vector,V[i]);
   if(bret)
   {
    break;
   }
   //if(nRCount>=nMaxRcount)return false;
  }
  
  nRCount=0;
  bool bsucback=PeekRandBackCard(the_vector,Vback);
  V[2].insert(V[2].end(),the_vector.begin(),the_vector.end());
  //V[2].swap(the_vector);
  //将3个容器中的扑克分给3个椅子
  for(int i=0;i<3;i++)
   m_bCardCount[i]=17;
        int FirstChairId=GetRand(0,2);
        int SecondChairId=0;
  for(;;nRCount++)
  {
   SecondChairId=GetRand(0,2);
   if(SecondChairId!=FirstChairId)
   {
    break;
   }
  }
  int LastChairId=3-FirstChairId-SecondChairId;
  memcpy(&m_bHandCardData[FirstChairId][0],&V[0][0],17);
  memcpy(&m_bHandCardData[SecondChairId][0],&V[1][0],17);
  memcpy(&m_bHandCardData[LastChairId][0],&V[2][0],17);
  memcpy(&m_bBackCard[0],&V[2][0],3);
  printf("\n三张底牌：\n");
  for (int i = 0; i < 3; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bBackCard[i]));
  }
  SortCardList(m_bBackCard,3,ST_ORDER);
  printf("\n排序后的三张底牌：\n");
  for (int i = 0; i < 3; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bBackCard[i]));
  }
  //发完牌后。每家17张
  printf("\n第一个人的牌：\n");
  for (int i = 0; i < 17; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bHandCardData[0][i]));
  }
  printf("\n第二个人的牌：\n");
  for (int i = 0; i < 17; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bHandCardData[1][i]));
  }
  printf("\n第三个人的牌：\n");
  for (int i = 0; i < 17; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bHandCardData[2][i]));
  }
  //排序后
  printf("\n第一个人排序后的牌：\n");
  SortCardList(m_bHandCardData[0],17,ST_ORDER);
  for (int i = 0; i < 17; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bHandCardData[0][i]));
  }
  printf("\n第二个人排序后的牌：\n");
  SortCardList(m_bHandCardData[1],17,ST_ORDER);
  for (int i = 0; i < 17; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bHandCardData[1][i]));
  }
  printf("\n第三个人排序后的牌：\n");
  SortCardList(m_bHandCardData[2],17,ST_ORDER);
  for (int i = 0; i < 17; i++) {
   printf("%s,",CSingleCard::GetCardName(m_bHandCardData[2][i]));
  }
  fflush(stdin);
  printf("\n");
  return 0;
}
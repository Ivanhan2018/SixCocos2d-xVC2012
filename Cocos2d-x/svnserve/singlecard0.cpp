#include "singlecard.h"
#include<stdio.h>

int main()
{ 
 //printf("%s\n",CSingleCard::GetCardName(0x4e));
 //CSingleCard htQ(0x2c);
 //CSingleCard htQ2=htQ;
 //printf("%s\n",CSingleCard::GetCardName(htQ.m_cCardID));
 //printf("%s\n",CSingleCard::GetCardName(htQ2.m_cCardID));
 CSingleCard PlayCards[3][20];//最多20张牌
 CSingleCard OutCards[20];//走的牌，一次也最多出20张牌
 CSingleCard pk[54];
 //初始化(黑桃A-K红桃A-K梅花A-K方块A-K小王大王)
 for (int i = 0; i < 52; i++) 
 {
  if (i < 13) 
  {
   pk[i]=CSingleCard(CSingleCard::GetCardID(3,(i + 1) % 14));
  } 
  else if (i < 26) 
  {
   pk[i]=CSingleCard(CSingleCard::GetCardID(2,(i - 12) % 14));
  } 
  else if (i < 39) 
  {
   pk[i] =CSingleCard(CSingleCard::GetCardID(1,(i - 25) % 14));
  } 
  else 
  {
   pk[i] =CSingleCard(CSingleCard::GetCardID(0,(i - 38) % 14));
  }
 }
 pk[52] =CSingleCard(0x4e);
 pk[53] =CSingleCard(0x4f);
 //出厂时候的牌
 for (int i = 0; i < 54; i++) {
  printf("%s,",CSingleCard::GetCardName(pk[i].m_cCardID));
 }
 printf("\n开始洗牌\n");
 /* Seed the random-number generator */
 srand( (unsigned)time( NULL ) );
 for (int i = 0; i < 54; i++) {
  int r =rand() % 54;
  CSingleCard t = pk[i];
  pk[i] = pk[r];
  pk[r] = t;
  //memcpy(&pk[i],&pk[r],sizeof(CSingleCard));
  //memcpy(&pk[r],&t,sizeof(CSingleCard));
 }
 //随机洗牌后的牌
 for (int i = 0; i < 54; i++) {
  printf("%s,",CSingleCard::GetCardName(pk[i].m_cCardID));
 }
 // 斗地主发牌,由于每个人都可能摸牌，所以数组长度为20
 for (int i = 0; i < 51; i++) {
  if (i < 17) {
   PlayCards[0][i] = pk[i];
  }
  if (i >= 17 && i < 34) {
   PlayCards[1][i - 17] = pk[i];
  }
  if (i >= 34 && i < 51) {
   PlayCards[2][i - 34] = pk[i];
  }
 }
 //发完牌后。每家17张
 printf("\n第一个人的牌：\n");
 for (int i = 0; i < 17; i++) {
  printf("%s,",CSingleCard::GetCardName(PlayCards[0][i].m_cCardID));
 }
 printf("\n第二个人的牌：\n");
 for (int i = 0; i < 17; i++) {
  printf("%s,",CSingleCard::GetCardName(PlayCards[1][i].m_cCardID));
 }
 printf("\n第三个人的牌：\n");
 for (int i = 0; i < 17; i++) {
  printf("%s,",CSingleCard::GetCardName(PlayCards[2][i].m_cCardID));
 }
 printf("\n请输入地主：0 ? 1 ? 2 ?");
 int nDz;
 scanf("%d",&nDz);
 //地主拿牌啊
 if (nDz==0||nDz==1||nDz==2) 
 {
  PlayCards[nDz][17] = pk[51];
  PlayCards[nDz][18] = pk[52];
  PlayCards[nDz][19] = pk[53];
 }
 //地主摸牌之后，每个人的牌输出
 printf("\n第一个人的牌：\n");
 for (int i = 0; i < 20; i++) {
  if(CSingleCard::IsLegal(PlayCards[0][i].m_cCardID))
   printf("%s,",CSingleCard::GetCardName(PlayCards[0][i].m_cCardID));
 }
 printf("\n第二个人的牌：\n");
 for (int i = 0; i < 20; i++) {
  if(CSingleCard::IsLegal(PlayCards[1][i].m_cCardID))
   printf("%s,",CSingleCard::GetCardName(PlayCards[1][i].m_cCardID));
 }
 printf("\n第三个人的牌：\n");
 for (int i = 0; i < 20; i++) {
  if(CSingleCard::IsLegal(PlayCards[2][i].m_cCardID))
   printf("%s,",CSingleCard::GetCardName(PlayCards[2][i].m_cCardID));
 }
 //排序后
 printf("\n第一个人排序后的牌：\n");
 ::SortCard(PlayCards[0]);
 for (int i = 0; i < 20; i++) {
  if(CSingleCard::IsLegal(PlayCards[0][i].m_cCardID))
   printf("%s,",CSingleCard::GetCardName(PlayCards[0][i].m_cCardID));
 }
 fflush(stdin);
 printf("\n");
 return 0;
}

#include "singlecard1.h"
#include<stdio.h>

int main()
{ 
 //const BYTE m_cbGoodcardData[GOOD_CARD_COUTN]
 CSingleCard pk[GOOD_CARD_COUTN];
 for (int i = 0; i < GOOD_CARD_COUTN; i++) 
 {
  pk[i]=CSingleCard(m_cbGoodcardData[i]);
  printf("%s,",CSingleCard::GetCardName(pk[i].m_cCardID));
 }
 tagAnalyseResult AnalyseResult;
 bool bret=AnalysebCardData(m_cbGoodcardData, GOOD_CARD_COUTN,AnalyseResult);
 BYTE cbTmpCardData[GOOD_CARD_COUTN] ;
 memcpy(cbTmpCardData,m_cbGoodcardData,GOOD_CARD_COUTN) ;
 //大小排序
 SortCardList(cbTmpCardData,GOOD_CARD_COUTN, ST_ORDER);
 printf("\n排序后：\n");
 for (int i = 0; i < GOOD_CARD_COUTN; i++) 
 {
  printf("%s,",CSingleCard::GetCardName(cbTmpCardData[i]));
 }
 tagAnalyseResult AnalyseResult2;
 bool bret2=AnalysebCardData(cbTmpCardData, GOOD_CARD_COUTN,AnalyseResult2);
 printf("\n-------\n");
 BYTE cbCardData[9]={0x01,0x02,0x11,0x12,0x21,0x22,0x0d,0x1d,0x2d};
 //tagAnalyseResult AnalyseResult3;
 //bool bret3=AnalysebCardData(cbCardData,9,AnalyseResult3);//排序前调用，结果不正确
 //SortCardList(cbCardData,9, ST_ORDER);
 //for (int i = 0; i < 9; i++) 
 //{
 // printf("%s,",CSingleCard::GetCardName(cbCardData[i]));
 //}
 //bret3=AnalysebCardData(cbCardData,9,AnalyseResult3);//排序后调用，结果正确
 SortCardList(cbCardData,9, ST_ORDER);

 printf("\n-------\n");
 fflush(stdin);
 //getchar();
 return 0;
}
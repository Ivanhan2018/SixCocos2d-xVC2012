#include"matrix4.h"
#include<cstring>

int main(void)
{
   int i,j;
   static float A[4][4]=
   {
	   {1,2,3,4},
	   {5,6,7,8},
	   {9,10,11,12},
	   {13,14,15,16}
   };
   static float C[4][4],B[4][4]=
   {
	{1,1,3,4},
	{1,2,3,2},
	{2,4,1,3},
	{5,7,1,4}
   };
   cout<<"----实矩阵乘法----"<<endl;
   Brmul(&A[0][0],&B[0][0],4,4,4,&C[0][0]);
   MATRIX4 mtxA,mtxB,mtxC;
   memcpy(&mtxA,A,sizeof(A));
   memcpy(&mtxB,B,sizeof(B));
   memcpy(&mtxC,C,sizeof(C));
   cout<<mtxA<<endl;
   cout<<mtxB<<endl;
   cout<<mtxC<<endl;
   MATRIX4 mtxD=mtxA.inverse();
   cout<<"----实矩阵求逆----"<<endl;
   cout<<mtxD<<endl;
   cout<<mtxD.inverse()<<endl;
   cout<<"----实矩阵求行列式的值----"<<endl;
   cout<<mtxA.det()<<endl;
   //system("pause");
   return 0;
}
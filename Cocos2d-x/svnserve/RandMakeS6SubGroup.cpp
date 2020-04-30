// RandMakeS6SubGroup.exe
#include <time.h>
#include <string.h>
#include <fstream>
using namespace std;
    
static char *abcdef[] = { 
 "1,4,6,5,2,3", 
 "1,5,6,3,4,2", 
 "1,6,5,2,4,3", 
 "1,6,4,3,2,5", 
 "2,3,5,6,5,1", 
 "2,5,3,4,1,6", 
 "2,6,4,1,5,3", 
 "3,2,6,5,4,1", 
 "3,4,5,2,6,1", 
 "3,5,4,1,6,2", 
 "3,6,2,1,4,5", 
 "4,1,5,6,3,2", 
 "4,3,2,5,1,6", 
 "4,5,1,2,3,6", 
 "4,2,3,6,1,5", 
 "5,1,3,6,2,4",
 "5,2,4,3,6,1",
 "5,3,1,4,2,6",
 "5,4,2,1,6,3",
 "6,1,3,4,5,2",
 "6,1,2,5,3,4",
 "6,2,1,4,3,5",     
 "6,3,1,2,5,4" 
};

int GetRand(int a,int b){
 if(a>=b)
  return a;
 int iRet=rand()%(b-a+1)+a;
 return iRet;
}

int main() {
 srand(time(0));
 int n=sizeof(abcdef)/sizeof(abcdef[0]);
 int m=GetRand(2,4);
 int* p=new int[m];
 char sz[100]={0};
 sprintf(sz,"S6_%d_",m);
 for(int i=0;i<m;i++){
  p[i]=GetRand(0,n-1);
  char sz1[100]={0};
  sprintf(sz1,"%d.",p[i]);
  strcat(sz,sz1);
 }
 strcat(sz,"txt");
 ofstream fout(sz);
 fout << "0,0,0,0,0,0"<<endl;
 for(int i=0;i<m;i++){
  fout<<abcdef[p[i]]<<endl;
 }
 delete[] p;
 puts(sz);
 //system("pause");
 return 0;
}
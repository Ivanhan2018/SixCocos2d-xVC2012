#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

template<class T>
void Brmul(T *a,T *b,int m,int n,int k,T *c)
{ 
 int i,j,l,u;
 for (i=0; i<=m-1; i++)
  for (j=0; j<=k-1; j++)
  { 
   u=i*k+j; 
   c[u]=0.0;
   for(l=0; l<=n-1; l++)
    c[u]=c[u]+a[i*n+l]*b[l*k+j];
  }
  return;
}

class MATRIX4
{
public:
 MATRIX4()
 {
  memset(&m_val[0][0],0,16*sizeof(int));
 }
 //compare
 const bool operator==(const MATRIX4& m)const
 {
  for(int i=0;i<4;i++)
   for(int j=0;j<4;j++)
   {
    if(m_val[i][j]!=m.m_val[i][j])
     return false;
   }
  return true;
 }
 //MATRIX4 inverse() const
 //{
 //   MATRIX4 mtx=*this;
 //   int i=Brinv((int *)&mtx.m_val[0][0],4);
 //   if(i!=0)
 //    return mtx;
 //   return MATRIX4();
 //}
 const MATRIX4 operator*(const MATRIX4& m) const
 {
  MATRIX4 mtx;
  Brmul/*<int>*/((int *)&(this->m_val[0][0]),(int *)&(m.m_val[0][0]),4,4,4,(int *)&(mtx.m_val[0][0]));
  return mtx;
 }
 static MATRIX4 NameToS4E(const char*name);
 static const char* S4EToName(const MATRIX4 &m);
 friend ostream& operator<< (ostream& os,MATRIX4& mtx);
public:
 int m_val[4][4]; //column vectors，应该是行向量或列向量，对象占用4*16=64字节的内存空间，内存顺序与真数组的内存顺序是一致的
 static int *S4[24];
 static const char S4Name[24][100];
 static int a1234[4][4];
 static int a1243[4][4];
 static int a1324[4][4];
 static int a1342[4][4];
 static int a1423[4][4];
 static int a1432[4][4];
 static int a2134[4][4];
 static int a2143[4][4];
 static int a2314[4][4];
 static int a2341[4][4];
 static int a2413[4][4];
 static int a2431[4][4];
 static int a3124[4][4];
 static int a3142[4][4];
 static int a3214[4][4];
 static int a3241[4][4];
 static int a3412[4][4];
 static int a3421[4][4];
 static int a4123[4][4];
 static int a4132[4][4];
 static int a4213[4][4];
 static int a4231[4][4];
 static int a4312[4][4];
 static int a4321[4][4];
};
int MATRIX4::a1234[4][4]={ {1,0,0,0},
{0,1,0,0},
{0,0,1,0},
{0,0,0,1}};
int MATRIX4::a1243[4][4]={ {1,0,0,0},
{0,1,0,0},
{0,0,0,1},
{0,0,1,0}};
int MATRIX4::a1324[4][4]={ {1,0,0,0},
{0,0,1,0},
{0,1,0,0},
{0,0,0,1}};
int MATRIX4::a1342[4][4]={ {1,0,0,0},
{0,0,0,1},
{0,1,0,0},
{0,0,1,0}};
int MATRIX4::a1423[4][4]={ {1,0,0,0},
{0,0,1,0},
{0,0,0,1},
{0,1,0,0}};
int MATRIX4::a1432[4][4]={ {1,0,0,0},
{0,0,0,1},
{0,0,1,0},
{0,1,0,0}};
int MATRIX4::a2134[4][4]={ {0,1,0,0},
{1,0,0,0},
{0,0,1,0},
{0,0,0,1}};
int MATRIX4::a2143[4][4]={ {0,1,0,0},
{1,0,0,0},
{0,0,0,1},
{0,0,1,0}};
int MATRIX4::a2314[4][4]={ {0,0,1,0},
{1,0,0,0},
{0,1,0,0},
{0,0,0,1}};
int MATRIX4::a2341[4][4]={ {0,0,0,1},
{1,0,0,0},
{0,1,0,0},
{0,0,1,0}};
int MATRIX4::a2413[4][4]={ {0,0,1,0},
{1,0,0,0},
{0,0,0,1},
{0,1,0,0}};
int MATRIX4::a2431[4][4]={ {0,0,0,1},
{1,0,0,0},
{0,0,1,0},
{0,1,0,0}};
int MATRIX4::a3124[4][4]={ {0,1,0,0},
{0,0,1,0},
{1,0,0,0},
{0,0,0,1}};
int MATRIX4::a3142[4][4]={ {0,1,0,0},
{0,0,0,1},
{1,0,0,0},
{0,0,1,0}};
int MATRIX4::a3214[4][4]={ {0,0,1,0},
{0,1,0,0},
{1,0,0,0},
{0,0,0,1}};
int MATRIX4::a3241[4][4]={ {0,0,0,1},
{0,1,0,0},
{1,0,0,0},
{0,0,1,0}};
int MATRIX4::a3412[4][4]={ {0,0,1,0},
{0,0,0,1},
{1,0,0,0},
{0,1,0,0}};
int MATRIX4::a3421[4][4]={ {0,0,0,1},
{0,0,1,0},
{1,0,0,0},
{0,1,0,0}};
int MATRIX4::a4123[4][4]={ {0,1,0,0},
{0,0,1,0},
{0,0,0,1},
{1,0,0,0}};
int MATRIX4::a4132[4][4]={ {0,1,0,0},
{0,0,0,1},
{0,0,1,0},
{1,0,0,0}};
int MATRIX4::a4213[4][4]={ {0,0,1,0},
{0,1,0,0},
{0,0,0,1},
{1,0,0,0}};
int MATRIX4::a4231[4][4]={ {0,0,0,1},
{0,1,0,0},
{0,0,1,0},
{1,0,0,0}};
int MATRIX4::a4312[4][4]={ {0,0,1,0},
{0,0,0,1},
{0,1,0,0},
{1,0,0,0}};
int MATRIX4::a4321[4][4]={ {0,0,0,1},
{0,0,1,0},
{0,1,0,0},
{1,0,0,0}};
int *MATRIX4::S4[24]={(int *)a1234,(int *)a1243,(int *)a1324,(int *)a1342,(int *)a1423,(int *)a1432,(int *)a2134,(int *)a2143,(int *)a2314,(int *)a2341,(int *)a2413,(int *)a2431,(int *)a3124,(int *)a3142,(int *)a3214,(int *)a3241,(int *)a3412,(int *)a3421,(int *)a4123,(int *)a4132,(int *)a4213,(int *)a4231,(int *)a4312,(int *)a4321};
const char MATRIX4::S4Name[24][100]={"1234","1243","1324","1342","1423","1432","2134","2143","2314","2341","2413","2431","3124","3142","3214","3241","3412","3421","4123","4132","4213","4231","4312","4321"};
MATRIX4 MATRIX4::NameToS4E(const char*name)
{
//#define RETURN_MTX(mtxName) {memcpy(&mtx,a##mtxName##,sizeof(a##mtxName##));return mtx;}
#define RETURN_MTX(mtxName) {memcpy(&mtx,a##mtxName,sizeof(a##mtxName));return mtx;}
 MATRIX4 mtx;
 if(strcmp(name,"(1)")==0||strcmp(name,"(1,2,3,4)")==0)
 {
  memcpy(&mtx,a1234,sizeof(a1234));
  return mtx;//乘法单位元
 }
 if(strcmp(name,"(34)")==0||strcmp(name,"(1,2,4,3)")==0)
 {
  memcpy(&mtx,a1243,sizeof(a1243));
  return mtx;
 }
 if(strcmp(name,"(23)")==0||strcmp(name,"(1,3,2,4)")==0)
  RETURN_MTX(1324)
 if(strcmp(name,"(234)")==0||strcmp(name,"(1,3,4,2)")==0)
  RETURN_MTX(1342);
 if(strcmp(name,"(243)")==0||strcmp(name,"(1,4,2,3)")==0)
  RETURN_MTX(1423);
 if(strcmp(name,"(24)")==0||strcmp(name,"(1,4,3,2)")==0)
  RETURN_MTX(1432);
 if(strcmp(name,"(12)")==0||strcmp(name,"(2,1,3,4)")==0)
  RETURN_MTX(2134);
 if(strcmp(name,"(12)(34)")==0||strcmp(name,"(2,1,4,3)")==0)
  RETURN_MTX(2143);
 if(strcmp(name,"(123)")==0||strcmp(name,"(2,3,1,4)")==0)
  RETURN_MTX(2314);
 if(strcmp(name,"(1234)")==0||strcmp(name,"(2,3,4,1)")==0)
  RETURN_MTX(2341);
 if(strcmp(name,"(1243)")==0||strcmp(name,"(2,4,1,3)")==0)
  RETURN_MTX(2413);
 if(strcmp(name,"(124)")==0||strcmp(name,"(2,4,3,1)")==0)
  RETURN_MTX(2431);
 if(strcmp(name,"(132)")==0||strcmp(name,"(3,1,2,4)")==0)
  RETURN_MTX(3124);
 if(strcmp(name,"(1342)")==0||strcmp(name,"(3,1,4,2)")==0)
  RETURN_MTX(3142);
 if(strcmp(name,"(13)")==0||strcmp(name,"(3,2,1,4)")==0)
  RETURN_MTX(3214);
 if(strcmp(name,"(134)")==0||strcmp(name,"(3,2,4,1)")==0)
  RETURN_MTX(3241);
 if(strcmp(name,"(13)(24)")==0||strcmp(name,"(3,4,1,2)")==0)
  RETURN_MTX(3412);
 if(strcmp(name,"(1324)")==0||strcmp(name,"(3,4,2,1)")==0)
  RETURN_MTX(3421);
 if(strcmp(name,"(1432)")==0||strcmp(name,"(4,1,2,3)")==0)
  RETURN_MTX(4123);
 if(strcmp(name,"(142)")==0||strcmp(name,"(4,1,3,2)")==0)
  RETURN_MTX(4132);
 if(strcmp(name,"(143)")==0||strcmp(name,"(4,2,1,3)")==0)
  RETURN_MTX(4213);
 if(strcmp(name,"(14)")==0||strcmp(name,"(4,2,3,1)")==0)
  RETURN_MTX(4231);
 if(strcmp(name,"(1423)")==0||strcmp(name,"(4,3,1,2)")==0)
  RETURN_MTX(4312);
 if(strcmp(name,"(14)(23)")==0||strcmp(name,"(4,3,2,1)")==0)
  RETURN_MTX(4321);
#undef RETURN_MTX
 return MATRIX4();
}
const char* MATRIX4::S4EToName(const MATRIX4 &m)
{
 for(int i=0;i<24;i++)
 {
  MATRIX4 mtx;
  memcpy(&mtx,S4[i],sizeof(a1234));
  if(mtx==m)
  {
   int iName=atoi(S4Name[i]);
   static char sz[100]={0};
   sprintf(sz,"(%d,%d,%d,%d)",iName/1000,(iName%1000)/100,(iName%100)/10,iName%10);
      return sz;
  }
 }
 return "Error";
}
ostream& operator<< (ostream& os,MATRIX4& mtx)
{
 for(int i=0;i<=3;i++)
 {
  for(int j=0;j<=3;j++)
   os<<mtx.m_val[i][j]<<",";
  os<<endl;
 }
 return os;
}
struct S4Element
{
public:
 static S4Element g_Error;
 S4Element(int a1,int a2,int a3,int a4):m_a1(a1),m_a2(a2),m_a3(a3),m_a4(a4){}
 bool operator==(const S4Element & a)
 {
  return (m_a1==a.m_a1 && m_a2==a.m_a2 && m_a3==a.m_a3 && m_a4==a.m_a4);
 }
 //二十四阶非交换群S_4的乘法表
 S4Element operator*(const S4Element & a)
 {
  if(S4Element::g_Error==a||S4Element::g_Error==*this)
   return S4Element::g_Error;
  //if(S4Element(1,2,3,4)==*this)
  // return a;
  //if(S4Element(1,2,3,4)==a)
  // return *this;
  MATRIX4 retM=MATRIX4::NameToS4E(S4Element::S4EToName(*this))*MATRIX4::NameToS4E(S4Element::S4EToName(a));
  return S4Element::NameToS4E(MATRIX4::S4EToName(retM));
 }
    //乘法逆元
    S4Element InvMul()const
 {
   for(int i=0;i<24;i++)
  {
   MATRIX4 mtx;
   memcpy(&mtx,MATRIX4::S4[i],sizeof(MATRIX4::a1234));
   S4Element s4e=S4Element::NameToS4E(MATRIX4::S4EToName(mtx));
   if(s4e*(*this)==S4Element(1,2,3,4))
   {
    return s4e;
   }
  }
  return S4Element::g_Error;
 }
 ////是否是偶置换
 //bool IsOdd()const
 //{
 //    if(S3Element(1,2,3)==*this)
 //  return true;
 // if(S3Element(2,3,1)==*this)
 //  return true;
 //    if(S3Element(3,1,2)==*this)
 //  return true;
 // return false;
 //}
 static S4Element NameToS4E(const char*name)
 { 
#define RETURN_S4E(iName) {return S4Element(iName/1000,(iName%1000)/100,(iName%100)/10,iName%10);}
 if(strcmp(name,"(1)")==0||strcmp(name,"(1,2,3,4)")==0)
  return S4Element(1,2,3,4);//乘法单位元
 if(strcmp(name,"(34)")==0||strcmp(name,"(1,2,4,3)")==0)
  return S4Element(1,2,4,3);
 if(strcmp(name,"(23)")==0||strcmp(name,"(1,3,2,4)")==0)
  return S4Element(1,3,2,4);
 if(strcmp(name,"(234)")==0||strcmp(name,"(1,3,4,2)")==0)
  RETURN_S4E(1342);
 if(strcmp(name,"(243)")==0||strcmp(name,"(1,4,2,3)")==0)
  RETURN_S4E(1423);
 if(strcmp(name,"(24)")==0||strcmp(name,"(1,4,3,2)")==0)
  RETURN_S4E(1432);
 if(strcmp(name,"(12)")==0||strcmp(name,"(2,1,3,4)")==0)
  RETURN_S4E(2134);
 if(strcmp(name,"(12)(34)")==0||strcmp(name,"(2,1,4,3)")==0)
  RETURN_S4E(2143);
 if(strcmp(name,"(123)")==0||strcmp(name,"(2,3,1,4)")==0)
  RETURN_S4E(2314);
 if(strcmp(name,"(1234)")==0||strcmp(name,"(2,3,4,1)")==0)
  RETURN_S4E(2341);
 if(strcmp(name,"(1243)")==0||strcmp(name,"(2,4,1,3)")==0)
  RETURN_S4E(2413);
 if(strcmp(name,"(124)")==0||strcmp(name,"(2,4,3,1)")==0)
  RETURN_S4E(2431);
 if(strcmp(name,"(132)")==0||strcmp(name,"(3,1,2,4)")==0)
  RETURN_S4E(3124);
 if(strcmp(name,"(1342)")==0||strcmp(name,"(3,1,4,2)")==0)
  RETURN_S4E(3142);
 if(strcmp(name,"(13)")==0||strcmp(name,"(3,2,1,4)")==0)
  RETURN_S4E(3214);
 if(strcmp(name,"(134)")==0||strcmp(name,"(3,2,4,1)")==0)
  RETURN_S4E(3241);
 if(strcmp(name,"(13)(24)")==0||strcmp(name,"(3,4,1,2)")==0)
  RETURN_S4E(3412);
 if(strcmp(name,"(1324)")==0||strcmp(name,"(3,4,2,1)")==0)
  RETURN_S4E(3421);
 if(strcmp(name,"(1432)")==0||strcmp(name,"(4,1,2,3)")==0)
  RETURN_S4E(4123);
 if(strcmp(name,"(142)")==0||strcmp(name,"(4,1,3,2)")==0)
  RETURN_S4E(4132);
 if(strcmp(name,"(143)")==0||strcmp(name,"(4,2,1,3)")==0)
  RETURN_S4E(4213);
 if(strcmp(name,"(14)")==0||strcmp(name,"(4,2,3,1)")==0)
  RETURN_S4E(4231);
 if(strcmp(name,"(1423)")==0||strcmp(name,"(4,3,1,2)")==0)
  RETURN_S4E(4312);
 if(strcmp(name,"(14)(23)")==0||strcmp(name,"(4,3,2,1)")==0)
  RETURN_S4E(4321);
#undef RETURN_S4E
   return S4Element::g_Error;
 }
 static const char* S4EToName(const S4Element & a,int type=0)
 {
  if(type==0)
  {
   static char sz[100]={0};
   sprintf(sz,"(%d,%d,%d,%d)",a.m_a1,a.m_a2,a.m_a3,a.m_a4);
   return sz;
  }
  if(type==1)
  {
   static char sz[100]={0};
   strcpy(sz,MY_S4EToName(a));
   return sz;
  }
  return "Error";
 }
 /*
  //E=(1,2,3,4)
  //E1=(2,1,3,4)
  //E2=(1,2,4,3)
  //E3=(2,1,4,3)
  //E4=(3,4,1,2)
  //E5=(4,3,1,2)
  //E6=(3,4,2,1)
  //E7=(4,3,2,1)
 */
 static const char* MY_S4EToName(const S4Element & a)
 {
  if(S4Element::NameToS4E("(1)")==a)
   return "E";
  if(S4Element::NameToS4E("(12)")==a)
   return "E1";
  if(S4Element::NameToS4E("(34)")==a)
   return "E2";
  if(S4Element::NameToS4E("(12)(34)")==a)
   return "E3";
  if(S4Element::NameToS4E("(13)(24)")==a)
   return "E4";
  if(S4Element::NameToS4E("(1423)")==a)
   return "E5";
  if(S4Element::NameToS4E("(1324)")==a)
   return "E6";
  if(S4Element::NameToS4E("(14)(23)")==a)
   return "E7";
  return "UnKnown";
 }
 friend ostream& operator<< (ostream& os,S4Element& a);
public:
 int m_a1,m_a2,m_a3,m_a4;//双行置换表达式
};
S4Element S4Element::g_Error=S4Element(0,0,0,0);
ostream& operator<< (ostream& os,S4Element& a)
{
 cout<<S4Element::S4EToName(a,0);
 return os;
}
int main()
{
 //8个置换E=(1),E1=(12),E2=(34),E3=(12)(34),E4=(13)(24),E5=(1423),E6=(1324),E7=(14)(23)
 S4Element E=S4Element::NameToS4E("(1)");
 S4Element E1=S4Element::NameToS4E("(12)");
 S4Element E2=S4Element::NameToS4E("(34)");
 S4Element E3=S4Element::NameToS4E("(12)(34)");
 S4Element E4=S4Element::NameToS4E("(13)(24)");
 S4Element E5=S4Element::NameToS4E("(1423)");
 S4Element E6=S4Element::NameToS4E("(1324)");
 S4Element E7=S4Element::NameToS4E("(14)(23)");
 cout<<"E="<<E<<endl;
 cout<<"E1="<<E1<<endl;
 cout<<"E2="<<E2<<endl;
 cout<<"E3="<<E3<<endl;
 cout<<"E4="<<E4<<endl;
 cout<<"E5="<<E5<<endl;
 cout<<"E6="<<E6<<endl;
 cout<<"E7="<<E7<<endl;
 cout<<"1/E="<<S4Element::S4EToName(E.InvMul(),1)<<endl;
 cout<<"1/E1="<<S4Element::S4EToName(E1.InvMul(),1)<<endl;
 cout<<"1/E2="<<S4Element::S4EToName(E2.InvMul(),1)<<endl;
 cout<<"1/E3="<<S4Element::S4EToName(E3.InvMul(),1)<<endl;
 cout<<"1/E4="<<S4Element::S4EToName(E4.InvMul(),1)<<endl;
 cout<<"1/E5="<<S4Element::S4EToName(E5.InvMul(),1)<<endl;
 cout<<"1/E6="<<S4Element::S4EToName(E6.InvMul(),1)<<endl;
 cout<<"1/E7="<<S4Element::S4EToName(E7.InvMul(),1)<<endl;
    printf("----乘法运算表----\n");
  printf("E*E=%s ",S4Element::S4EToName(E*E,1));
 printf("E*E1=%s ",S4Element::S4EToName(E*E1,1));
 printf("E*E2=%s ",S4Element::S4EToName(E*E2,1));
 printf("E*E3=%s ",S4Element::S4EToName(E*E3,1));
 printf("E*E4=%s ",S4Element::S4EToName(E*E4,1));
 printf("E*E5=%s ",S4Element::S4EToName(E*E5,1));
 printf("E*E6=%s ",S4Element::S4EToName(E*E6,1));
 printf("E*E7=%s\n",S4Element::S4EToName(E*E7,1));
 printf("E1*E=%s ",S4Element::S4EToName(E1*E,1));
 printf("E1*E1=%s ",S4Element::S4EToName(E1*E1,1));
 printf("E1*E2=%s ",S4Element::S4EToName(E1*E2,1));
 printf("E1*E3=%s ",S4Element::S4EToName(E1*E3,1));
 printf("E1*E4=%s ",S4Element::S4EToName(E1*E4,1));
 printf("E1*E5=%s ",S4Element::S4EToName(E1*E5,1));
 printf("E1*E6=%s ",S4Element::S4EToName(E1*E6,1));
 printf("E1*E7=%s\n",S4Element::S4EToName(E1*E7,1));
 printf("E2*E=%s ",S4Element::S4EToName(E2*E,1));
 printf("E2*E1=%s ",S4Element::S4EToName(E2*E1,1));
 printf("E2*E2=%s ",S4Element::S4EToName(E2*E2,1));
 printf("E2*E3=%s ",S4Element::S4EToName(E2*E3,1));
 printf("E2*E4=%s ",S4Element::S4EToName(E2*E4,1));
 printf("E2*E5=%s ",S4Element::S4EToName(E2*E5,1));
 printf("E2*E6=%s ",S4Element::S4EToName(E2*E6,1));
 printf("E2*E7=%s\n",S4Element::S4EToName(E2*E7,1));
 printf("E3*E=%s ",S4Element::S4EToName(E3*E,1));
 printf("E3*E1=%s ",S4Element::S4EToName(E3*E1,1));
 printf("E3*E2=%s ",S4Element::S4EToName(E3*E2,1));
 printf("E3*E3=%s ",S4Element::S4EToName(E3*E3,1));
 printf("E3*E4=%s ",S4Element::S4EToName(E3*E4,1));
 printf("E3*E5=%s ",S4Element::S4EToName(E3*E5,1));
 printf("E3*E6=%s ",S4Element::S4EToName(E3*E6,1));
 printf("E3*E7=%s\n",S4Element::S4EToName(E3*E7,1));
 printf("E4*E=%s ",S4Element::S4EToName(E4*E,1));
 printf("E4*E1=%s ",S4Element::S4EToName(E4*E1,1));
 printf("E4*E2=%s ",S4Element::S4EToName(E4*E2,1));
 printf("E4*E3=%s ",S4Element::S4EToName(E4*E3,1));
 printf("E4*E4=%s ",S4Element::S4EToName(E4*E4,1));
 printf("E4*E5=%s ",S4Element::S4EToName(E4*E5,1));
 printf("E4*E6=%s ",S4Element::S4EToName(E4*E6,1));
 printf("E4*E7=%s\n",S4Element::S4EToName(E4*E7,1));
 printf("E5*E=%s ",S4Element::S4EToName(E5*E,1));
 printf("E5*E1=%s ",S4Element::S4EToName(E5*E1,1));
 printf("E5*E2=%s ",S4Element::S4EToName(E5*E2,1));
 printf("E5*E3=%s ",S4Element::S4EToName(E5*E3,1));
 printf("E5*E4=%s ",S4Element::S4EToName(E5*E4,1));
 printf("E5*E5=%s ",S4Element::S4EToName(E5*E5,1));
 printf("E5*E6=%s ",S4Element::S4EToName(E5*E6,1));
 printf("E5*E7=%s\n",S4Element::S4EToName(E5*E7,1));
 printf("E6*E=%s ",S4Element::S4EToName(E6*E,1));
 printf("E6*E1=%s ",S4Element::S4EToName(E6*E1,1));
 printf("E6*E2=%s ",S4Element::S4EToName(E6*E2,1));
 printf("E6*E3=%s ",S4Element::S4EToName(E6*E3,1));
 printf("E6*E4=%s ",S4Element::S4EToName(E6*E4,1));
 printf("E6*E5=%s ",S4Element::S4EToName(E6*E5,1));
 printf("E6*E6=%s ",S4Element::S4EToName(E6*E6,1));
 printf("E6*E7=%s\n",S4Element::S4EToName(E6*E7,1));
 printf("E7*E=%s ",S4Element::S4EToName(E7*E,1));
 printf("E7*E1=%s ",S4Element::S4EToName(E7*E1,1));
 printf("E7*E2=%s ",S4Element::S4EToName(E7*E2,1));
 printf("E7*E3=%s ",S4Element::S4EToName(E7*E3,1));
 printf("E7*E4=%s ",S4Element::S4EToName(E7*E4,1));
 printf("E7*E5=%s ",S4Element::S4EToName(E7*E5,1));
 printf("E7*E6=%s ",S4Element::S4EToName(E7*E6,1));
 printf("E7*E7=%s\n",S4Element::S4EToName(E7*E7,1));
 return 0;
}
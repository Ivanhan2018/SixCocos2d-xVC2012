#include<cstring>
#include<iostream>
#include<string.h>
using namespace std;

struct S3Element
{
public:
 static S3Element g_Error;
 S3Element(int a1,int a2,int a3):m_a1(a1),m_a2(a2),m_a3(a3){}
 bool operator==(const S3Element & a)
 {
  return (m_a1==a.m_a1 && m_a2==a.m_a2 && m_a3==a.m_a3);
 }
 //六阶非交换群{I,r,rr,f,fr,frr}的乘法表
 S3Element operator*(const S3Element & a)
 {
  if(S3Element::g_Error==a||S3Element::g_Error==*this)
   return S3Element::g_Error;
  if(S3Element(1,2,3)==*this)
   return a;
  if(S3Element(1,2,3)==a)
   return *this;
  static char sz[100]={0};
  strcpy(sz,S3Element::S3EToName(*this));
  strcat(sz,S3Element::S3EToName(a));
  return S3Element::NameToS3E(sz);
 }
    //乘法逆元
    S3Element InvMul()const
 {
  static S3Element S3EArr[6]={
   S3Element::NameToS3E("I"),S3Element::NameToS3E("r"),S3Element::NameToS3E("rr"),
   S3Element::NameToS3E("f"),S3Element::NameToS3E("fr"),S3Element::NameToS3E("frr")};
        for(int i=0;i<6;i++)
  {
     if(S3EArr[i]*(*this)==S3EArr[0])
      return S3EArr[i];
  }
  return S3Element::g_Error;
 }
 //是否是偶置换
 bool IsOdd()const
 {
     if(S3Element(1,2,3)==*this)
   return true;
  if(S3Element(2,3,1)==*this)
   return true;
     if(S3Element(3,1,2)==*this)
   return true;
  return false;
 }
 static S3Element NameToS3E(const char*name)
 {
   if(strcmp(name,"(1)")==0||strcmp(name,"I")==0||strcmp(name,"ff")==0||strcmp(name,"rrr")==0||strcmp(name,"rfrf")==0||strcmp(name,"frfr")==0)
    return S3Element(1,2,3);//乘法单位元
   if(strcmp(name,"(123)")==0||strcmp(name,"r")==0||strcmp(name,"frrf")==0||strcmp(name,"rff")==0||strcmp(name,"ffr")==0)
    return S3Element(2,3,1);//逆时针旋转120°
   if(strcmp(name,"(132)")==0||strcmp(name,"rr")==0||strcmp(name,"frf")==0)
    return S3Element(3,1,2);//逆时针旋转240°
   if(strcmp(name,"(13)")==0||strcmp(name,"f")==0||strcmp(name,"rfr")==0)
    return S3Element(3,2,1);//轴翻转
   if(strcmp(name,"(23)")==0||strcmp(name,"fr")==0||strcmp(name,"rrf")==0)
    return S3Element(1,3,2);//逆时针旋转120°后轴翻转
   if(strcmp(name,"(12)")==0||strcmp(name,"frr")==0||strcmp(name,"rf")==0||strcmp(name,"rrfr")==0)
    return S3Element(2,1,3);//逆时针旋转240°后轴翻转
   return S3Element::g_Error;
 }
 static const char* S3EToName(const S3Element & a,int type=0)
 {
  if(type==0)
  {
   if(S3Element(1,2,3)==a)
    return "I";
   if(S3Element(1,3,2)==a)
    return "fr";
   if(S3Element(2,1,3)==a)
    return "rf";
   if(S3Element(2,3,1)==a)
    return "r";
   if(S3Element(3,1,2)==a)
    return "rr";
   if(S3Element(3,2,1)==a)
    return "f";
  }
  if(type==1)
  {
   if(S3Element(1,2,3)==a)
    return "(1)";
   if(S3Element(1,3,2)==a)
    return "(23)";
   if(S3Element(2,1,3)==a)
    return "(12)";
   if(S3Element(2,3,1)==a)
    return "(123)";
   if(S3Element(3,1,2)==a)
    return "(132)";
   if(S3Element(3,2,1)==a)
    return "(13)";
  }
  return "Error";
 }
 friend ostream& operator<< (ostream& os,const S3Element& a);//第二个参数加const修饰
public:
 int m_a1,m_a2,m_a3;//双行置换表达式
};
S3Element S3Element::g_Error=S3Element(0,0,0);
ostream& operator<< (ostream& os,const S3Element& a)
{
 os<<S3Element::S3EToName(a,0)<<"="<<"("<<a.m_a1<<","<<a.m_a2<<","<<a.m_a3<<")="<<S3Element::S3EToName(a,1);
 return os;
}
int main()
{
 //S3Element f=S3Element::NameToS3E("(13)");
 //S3Element frr=S3Element::NameToS3E("(12)");
 //printf("%s=%s\n",S3Element::S3EToName(f),S3Element::S3EToName(f,1));
 //printf("ff=(13)(13)=%s=%s\n",S3Element::S3EToName(f*f),S3Element::S3EToName(f*f,1));
 //printf("(frr)f=(12)(13)=%s=%s\n",S3Element::S3EToName(frr*f),S3Element::S3EToName(frr*f,1));
 //printf("f(frr)=(13)(12)=%s=%s\n",S3Element::S3EToName(f*frr),S3Element::S3EToName(f*frr,1));
    S3Element I=S3Element::NameToS3E("I");
    S3Element r=S3Element::NameToS3E("r");
    S3Element rr=S3Element::NameToS3E("rr");
    S3Element f=S3Element::NameToS3E("f");
 S3Element fr=S3Element::NameToS3E("fr");
 S3Element frr=S3Element::NameToS3E("frr");
 cout<<"I="<<I<<endl;
 cout<<"r="<<r<<endl;
 cout<<"rr="<<rr<<endl;
 cout<<"f="<<f<<endl;
 cout<<"fr="<<fr<<endl;
 cout<<"frr="<<frr<<endl; 
 auto I1=I.InvMul();
 auto r1=r.InvMul();
 auto ff=f*f;
 cout<<"1/I="<<I1<<endl;
 cout<<"1/r="<<r1<<endl;
 cout<<"f*f="<<ff<<endl;
 cout<<"1/rr="<<rr.InvMul()<<endl;
 cout<<"1/f="<<f.InvMul()<<endl;
 cout<<"1/fr="<<fr.InvMul()<<endl;
 cout<<"1/frr="<<frr.InvMul()<<endl;  
 cout<<"frr*f="<<frr*f<<endl;
 cout<<"f*frr="<<f*frr<<endl;
 return 0;
}
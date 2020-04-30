#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

struct ZnElement
{
public:
 static ZnElement g_Error;
 ZnElement(int mod=0,int k=0):m_mod(mod),m_k(k){}
    //加法逆元
 ZnElement InvAdd()const
 {
  for(int i=0;i<this->m_mod;i++)
  {
   if(ZnElement(this->m_mod,i)+(*this)==ZnElement(this->m_mod,0))
    return ZnElement(this->m_mod,i);
  }
  return ZnElement::g_Error;
 }
    ZnElement operator-()
 {
  return (*this).InvAdd();
 }
    ZnElement operator-(const ZnElement &a)
 {
  return (*this)+a.InvAdd();
 }
#if 1
    //乘法逆元
 ZnElement InvMul()const
 {
  for(int i=0;i<this->m_mod;i++)
  {
   if(ZnElement(this->m_mod,i)*(*this)==ZnElement(this->m_mod,1))
    return ZnElement(this->m_mod,i);
  }
  return ZnElement::g_Error;
 }
    ZnElement operator/(const ZnElement &a)
 {
  if(ZnElement::g_Error==a)
   return ZnElement::g_Error;
  return (*this)*a.InvMul();
 }
#endif
    ZnElement operator+(const ZnElement &a)
 {
  ZnElement ret;
  ret.m_mod=m_mod;
  ret.m_k=(m_k+a.m_k)%m_mod;
  return ret;
 }
 //剩余类环中的乘法
    ZnElement operator*(const ZnElement &a)
 {
  ZnElement ret;
  ret.m_mod=m_mod;
  ret.m_k=(m_k*a.m_k)%m_mod;
  return ret;
 }
    bool operator==(const ZnElement & a)
 {
  return (m_mod==a.m_mod&&m_k==a.m_k);
 }
 static ZnElement NameToZnE(const char*name)
 {
    int k=0,mod=0;
  sscanf(name,"[%d]_%d",&k,&mod);
  return ZnElement(mod,k);
 }
 static const char* ZnEToName(const ZnElement & a,int type=0)
 {
  if(type==0)
  {
   static char sz[100]={0};
   sprintf(sz,"[%d]_%d",a.m_k,a.m_mod);
   return sz;
  }
  if(type==1)
  {
   static char sz[100]={0};
   strcpy(sz,MY_ZnEToName(a));
   return sz;
  }
  return "Error";
 }
 static const char* MY_ZnEToName(const ZnElement & a,int mod=2)
 {
  if(mod==2)
  {
   if(ZnElement::NameToZnE("[0]_2")==a)
    return "I";
   if(ZnElement::NameToZnE("[1]_2")==a)
    return "a";
  }
  return "UnKnown";
 }
 friend ostream& operator<< (ostream& os,ZnElement& a);
public:
 int m_mod,m_k;
};
ZnElement ZnElement::g_Error=ZnElement(0,0);
ostream& operator<< (ostream& os,ZnElement& a)
{
 cout<<ZnElement::ZnEToName(a,0);
 return os;
}
//域F上的2阶方阵
struct M2Element
{
public:
 static M2Element g_Error;
 static M2Element s_M2ElementArr[6];
 static const char *s_szArr[6];
 M2Element(ZnElement a11,ZnElement a12,ZnElement a21,ZnElement a22):m_a11(a11),m_a12(a12),m_a21(a21),m_a22(a22){}
 M2Element(int a11,int a12,int a21,int a22)
 {
      m_a11=F2IntToZnElement(a11);
      m_a12=F2IntToZnElement(a12);
      m_a21=F2IntToZnElement(a21);
      m_a22=F2IntToZnElement(a22);
 }
 static ZnElement F2IntToZnElement(int a)
 {
        if(a==0)
   return ZnElement(2,0);
        if(a==1)
   return ZnElement(2,1);
  return ZnElement::g_Error;
 }
 M2Element operator *(const M2Element &m)
 {
  return M2Element( m_a11 * m.m_a11+m_a12 * m.m_a21,m_a11 * m.m_a12+m_a12 * m.m_a22, m_a21 * m.m_a11+m_a22 * m.m_a21, m_a21 * m.m_a12+m_a22 * m.m_a22);
 }
    bool operator==(const M2Element & m)
 {
  return (m_a11==m.m_a11 && m_a12==m.m_a12 && m_a21==m.m_a21 && m_a22==m.m_a22);
 }
 ZnElement det()
 {
  ZnElement ret=m_a11 *m_a22-m_a12*m_a21;
  return ret;
 }
 M2Element inverse()
 {
    ZnElement d=this->det();
    if(d==ZnElement(d.m_mod,0))
     return M2Element::g_Error;
    return M2Element(m_a22/d,-m_a12/d,-m_a21/d,m_a11/d);
 }
 static M2Element NameToM2Element(const char*name)
 {
    for(int i=0;i<6;i++)
    {
     if(strcmp(name,s_szArr[i])==0)
      return s_M2ElementArr[i];
    }
    return M2Element::g_Error;
 }
 static const char* M2ElementToName(const M2Element & a)
 {
    for(int i=0;i<6;i++)
    {
     if(s_M2ElementArr[i]==a)
      return s_szArr[i];
    }
    return "Error";
 }
 //未知6阶群的群元的阶
 static int M2ElementToOrder(const M2Element &idx,const M2Element &m)
 {
  M2Element t=idx;
  for(int i=1;i<=6;i++)
  {
   t=t*m;
   if(t==idx)
    return i;
  }
  return -1;
 }
 friend ostream& operator<< (ostream& os,M2Element& mtx);
public:
 ZnElement m_a11,m_a12,m_a21,m_a22;
};
M2Element M2Element::g_Error=M2Element(ZnElement::g_Error,ZnElement::g_Error,ZnElement::g_Error,ZnElement::g_Error);
M2Element M2Element::s_M2ElementArr[6]={M2Element(1,0,0,1),M2Element(1,1,0,1),M2Element(1,0,1,1),M2Element(0,1,1,0),M2Element(1,1,1,0),M2Element(0,1,1,1)};
const char *M2Element::s_szArr[6]={"O","I","A","B","C","D"};

ostream& operator<< (ostream& os,M2Element& m)
{
 os<<"{{"<<ZnElement::ZnEToName(m.m_a11,0)<<","<<ZnElement::ZnEToName(m.m_a12,0)<<"},{"<<ZnElement::ZnEToName(m.m_a21,0)<<","<<ZnElement::ZnEToName(m.m_a22,0)<<"}}";
 return os;
}
int main()
{
    M2Element O=M2Element::NameToM2Element("O");
    M2Element I=M2Element::NameToM2Element("I");
    M2Element A=M2Element::NameToM2Element("A");
    M2Element B=M2Element::NameToM2Element("B");
    M2Element C=M2Element::NameToM2Element("C");
    M2Element D=M2Element::NameToM2Element("D");
 printf("----未知6阶群群元的阶----\n");
 for(int i=0;i<6;i++)
  printf("M2ElementToOrder(%s)=%d\n",M2Element::s_szArr[i],M2Element::M2ElementToOrder(M2Element::s_M2ElementArr[0],M2Element::s_M2ElementArr[i]));
 
 printf("----未知6阶群的乘法运算表----\n");
 printf("O*O=%s ",M2Element::M2ElementToName(O*O));
 printf("O*I=%s ",M2Element::M2ElementToName(O*I));
 printf("O*A=%s ",M2Element::M2ElementToName(O*A));
 printf("O*B=%s ",M2Element::M2ElementToName(O*B));
 printf("O*C=%s ",M2Element::M2ElementToName(O*C));
 printf("O*D=%s\n",M2Element::M2ElementToName(O*D));
 printf("I*O=%s ",M2Element::M2ElementToName(I*O));
 printf("I*I=%s ",M2Element::M2ElementToName(I*I));
 printf("I*A=%s ",M2Element::M2ElementToName(I*A));
 printf("I*B=%s ",M2Element::M2ElementToName(I*B));
 printf("I*C=%s ",M2Element::M2ElementToName(I*C));
 printf("I*D=%s\n",M2Element::M2ElementToName(I*D));
 printf("A*O=%s ",M2Element::M2ElementToName(A*O));
 printf("A*I=%s ",M2Element::M2ElementToName(A*I));
 printf("A*A=%s ",M2Element::M2ElementToName(A*A));
 printf("A*B=%s ",M2Element::M2ElementToName(A*B));
 printf("A*C=%s ",M2Element::M2ElementToName(A*C));
 printf("A*D=%s\n",M2Element::M2ElementToName(A*D));
 printf("B*O=%s ",M2Element::M2ElementToName(B*O));
 printf("B*I=%s ",M2Element::M2ElementToName(B*I));
 printf("B*A=%s ",M2Element::M2ElementToName(B*A));
 printf("B*B=%s ",M2Element::M2ElementToName(B*B));
 printf("B*C=%s ",M2Element::M2ElementToName(B*C));
 printf("B*D=%s\n",M2Element::M2ElementToName(B*D));
 printf("C*O=%s ",M2Element::M2ElementToName(C*O));
 printf("C*I=%s ",M2Element::M2ElementToName(C*I));
 printf("C*A=%s ",M2Element::M2ElementToName(C*A));
 printf("C*B=%s ",M2Element::M2ElementToName(C*B));
 printf("C*C=%s ",M2Element::M2ElementToName(C*C));
 printf("C*D=%s\n",M2Element::M2ElementToName(C*D));
 printf("D*O=%s ",M2Element::M2ElementToName(D*O));
 printf("D*I=%s ",M2Element::M2ElementToName(D*I));
 printf("D*A=%s ",M2Element::M2ElementToName(D*A));
 printf("D*B=%s ",M2Element::M2ElementToName(D*B));
 printf("D*C=%s ",M2Element::M2ElementToName(D*C));
 printf("D*D=%s\n",M2Element::M2ElementToName(D*D));
 return 0;
}
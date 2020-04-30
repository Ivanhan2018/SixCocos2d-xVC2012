#include<stdio.h>
#include<string.h>

struct VElement
{
public:
 static VElement g_Error;
 VElement(int b1=0,int b2=0)
 {
  m_bVal[0]=b1;
  m_bVal[1]=b2;
 }
    //加法逆元
    VElement InvAdd()const//const加上去，否则会出现error C2662: "VElement::InvAdd": 不能将"this"指针从"const VElement"转换为"VElement &"
 {
     VElement ret;
  ret.m_bVal[0]=(2-m_bVal[0])%2;
  ret.m_bVal[1]=(2-m_bVal[1])%2;
  return ret;
 }
    //乘法逆元
    VElement InvMul()const
 {
  if(VElement(1,1)==*this)
   return VElement(1,1);
        if(VElement(1,0)==*this)
   return VElement(0,1);
        if(VElement(0,1)==*this)
   return VElement(1,0);
  return VElement::g_Error;
 }
    VElement operator-(const VElement &a)
 {
  return (*this)+a.InvAdd();
 }
    VElement operator/(const VElement &a)
 {
  return (*this)*a.InvMul();
 }
 /*
 + O=(0,0),I=(1,1),A=(0,1),B=(1,0)
 O O         I         A          B
 I  I          O        B          A
 A A         B         O          I
 B B         A         I           O
 */
    VElement operator+(const VElement &a)
 {
  VElement ret;
  //0^0=0, 1^0=1, 0^1=1, 1^1=0<=>0+0=0, 1+0=1, 0+1=1, 1+1=0
  ret.m_bVal[0]=m_bVal[0]^a.m_bVal[0];
  ret.m_bVal[1]=m_bVal[1]^a.m_bVal[1];
  ////0+0=0, 1+0=1, 0+1=1, 1+1=0
  //ret.m_bVal[0]=(m_bVal[0]+a.m_bVal[0])%2;
  //ret.m_bVal[1]=(m_bVal[1]+a.m_bVal[1])%2;
  return ret;
 }
 /*
 * O=(0,0),I=(1,1),A=(0,1),B=(1,0)
 O O         O         O          O
 I  O         I        A          B
 A O         A         B          I
 B O         B         I           A
 I,A,B构成一个C_3群=>A*A=B,B*B=A,A*B=B*A=I
 */
    VElement operator*(const VElement &a)
 {
     VElement ret;
  ////错误的：0*0=0, 1*0=0, 0*1=0, 1*1=1
  //ret.m_bVal[0]=m_bVal[0]*a.m_bVal[0];
  //ret.m_bVal[1]=m_bVal[1]*a.m_bVal[1];
  //正确的：
  if(VElement::g_Error==a||VElement::g_Error==*this)
   return VElement::g_Error;
        if(VElement(0,1)==a&&VElement(0,1)==*this)
   return VElement(1,0);
        if(VElement(1,0)==a&&VElement(1,0)==*this)
   return VElement(0,1);
        if(VElement(0,1)==a&&VElement(1,0)==*this)
   return VElement(1,1);
        if(VElement(1,0)==a&&VElement(0,1)==*this)
   return VElement(1,1);
  ret.m_bVal[0]=m_bVal[0]*a.m_bVal[0];
  ret.m_bVal[1]=m_bVal[1]*a.m_bVal[1];
  return ret;
 }
    bool operator==(const VElement & a)
 {
  return (m_bVal[0]==a.m_bVal[0]&&m_bVal[1]==a.m_bVal[1]);
 }
 static VElement NameToVE(const char*name)
 {
    if(strcmp(name,"O")==0)
     return VElement(0,0);
    if(strcmp(name,"I")==0)
     return VElement(1,1);
    if(strcmp(name,"A")==0)
     return VElement(0,1);
    if(strcmp(name,"B")==0)
     return VElement(1,0);
    return VElement::g_Error;
 }
 static const char* VEToName(const VElement & a)
 {
    if(VElement(0,0)==a)
     return "O";
    if(VElement(1,1)==a)
     return "I";
    if(VElement(0,1)==a)
     return "A";
    if(VElement(1,0)==a)
     return "B";
    return "Error";
 }
public:
 int m_bVal[2];
};
VElement VElement::g_Error=VElement(-1,-1);
int main()
{
 //const char* ret1=VElement::VEToName(VElement::NameToVE("A")+VElement::NameToVE("B"));
 //printf("A+B=%s\n",ret1);
 //const char* ret2=VElement::VEToName(VElement::NameToVE("A")*VElement::NameToVE("B"));
 //printf("A*B=%s\n",ret2);
    VElement O,I,A,B;
    O=VElement::NameToVE("O");
    I=VElement::NameToVE("I");
    A=VElement::NameToVE("A");
    B=VElement::NameToVE("B");
    printf("----加法运算表----\n");
 printf("O+O=%s ",VElement::VEToName(O+O));
 printf("O+I=%s ",VElement::VEToName(O+I));
 printf("O+A=%s ",VElement::VEToName(O+A));
 printf("O+B=%s\n",VElement::VEToName(O+B));
 printf("I+O=%s ",VElement::VEToName(I+O));
 printf("I+I=%s ",VElement::VEToName(I+I));
 printf("I+A=%s ",VElement::VEToName(I+A));
 printf("I+B=%s\n",VElement::VEToName(I+B));
 printf("A+O=%s ",VElement::VEToName(A+O));
 printf("A+I=%s ",VElement::VEToName(A+I));
 printf("A+A=%s ",VElement::VEToName(A+A));
 printf("A+B=%s\n",VElement::VEToName(A+B));
 printf("B+O=%s ",VElement::VEToName(B+O));
 printf("B+I=%s ",VElement::VEToName(B+I));
 printf("B+A=%s ",VElement::VEToName(B+A));
 printf("B+B=%s\n",VElement::VEToName(B+B));
    printf("----乘法运算表----\n");
 printf("O*O=%s ",VElement::VEToName(O*O));
 printf("O*I=%s ",VElement::VEToName(O*I));
 printf("O*A=%s ",VElement::VEToName(O*A));
 printf("O*B=%s\n",VElement::VEToName(O*B));
 printf("I*O=%s ",VElement::VEToName(I*O));
 printf("I*I=%s ",VElement::VEToName(I*I));
 printf("I*A=%s ",VElement::VEToName(I*A));
 printf("I*B=%s\n",VElement::VEToName(I*B));
 printf("A*O=%s ",VElement::VEToName(A*O));
 printf("A*I=%s ",VElement::VEToName(A*I));
 printf("A*A=%s ",VElement::VEToName(A*A));
 printf("A*B=%s\n",VElement::VEToName(A*B));
 printf("B*O=%s ",VElement::VEToName(B*O));
 printf("B*I=%s ",VElement::VEToName(B*I));
 printf("B*A=%s ",VElement::VEToName(B*A));
 printf("B*B=%s\n",VElement::VEToName(B*B));
    printf("----减法运算表----\n");
 printf("O-O=%s ",VElement::VEToName(O-O));
 printf("O-I=%s ",VElement::VEToName(O-I));
 printf("O-A=%s ",VElement::VEToName(O-A));
 printf("O-B=%s\n",VElement::VEToName(O-B));
 printf("I-O=%s ",VElement::VEToName(I-O));
 printf("I-I=%s ",VElement::VEToName(I-I));
 printf("I-A=%s ",VElement::VEToName(I-A));
 printf("I-B=%s\n",VElement::VEToName(I-B));
 printf("A-O=%s ",VElement::VEToName(A-O));
 printf("A-I=%s ",VElement::VEToName(A-I));
 printf("A-A=%s ",VElement::VEToName(A-A));
 printf("A-B=%s\n",VElement::VEToName(A-B));
 printf("B-O=%s ",VElement::VEToName(B-O));
 printf("B-I=%s ",VElement::VEToName(B-I));
 printf("B-A=%s ",VElement::VEToName(B-A));
 printf("B-B=%s\n",VElement::VEToName(B-B));
    printf("----除法运算表----\n");
 printf("O/O=%s ",VElement::VEToName(O/O));
 printf("O/I=%s ",VElement::VEToName(O/I));
 printf("O/A=%s ",VElement::VEToName(O/A));
 printf("O/B=%s\n",VElement::VEToName(O/B));
 printf("I/O=%s ",VElement::VEToName(I/O));
 printf("I/I=%s ",VElement::VEToName(I/I));
 printf("I/A=%s ",VElement::VEToName(I/A));
 printf("I/B=%s\n",VElement::VEToName(I/B));
 printf("A/O=%s ",VElement::VEToName(A/O));
 printf("A/I=%s ",VElement::VEToName(A/I));
 printf("A/A=%s ",VElement::VEToName(A/A));
 printf("A/B=%s\n",VElement::VEToName(A/B));
 printf("B/O=%s ",VElement::VEToName(B/O));
 printf("B/I=%s ",VElement::VEToName(B/I));
 printf("B/A=%s ",VElement::VEToName(B/A));
 printf("B/B=%s\n",VElement::VEToName(B/B));
 return 0;
}

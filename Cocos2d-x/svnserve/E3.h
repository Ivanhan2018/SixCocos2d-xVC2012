#ifndef E3_H
#define E3_H

// 求一元三次方程的实根
#include<cmath>
#include<complex>
/*
 x^3+px+q=0：
 x甲=((-q+sqrt(q^2+4p^3/27))/2)^(1/3)+((-q-sqrt(q^2+4p^3/27))/2)^(1/3)
 x乙=(-x甲+sqrt(-3x甲^2-4p))/2
 x丙=(-x甲-sqrt(-3x甲^2-4p))/2
*/
//typedef float Real;
template <class Real>struct E3
{
public:
 E3(Real p,Real q):m_p(p),m_q(q){}
 Real DeltOfE3()
 {
  Real ret=m_q*m_q+4*m_p*m_p*m_p/27;
  return ret;
 }
 Real cube(Real a)
 {
  if(a==0)
   return 0;
  if(a>0)
   return expf(1.0*logf(a)/3.0);
  else
   return -expf(1.0*logf(-a)/3.0);
 }
 std::complex<Real> cube(std::complex<Real> a)
 {
  return exp(std::complex<Real>(1.0/3.0,0)*log(a));
 }
 //与牛顿切线法求得的实根值是一致的
 Real xOfE3()
 {
  Real delt=DeltOfE3();
  if(delt>=0)
  {
   Real ret1=cube((-m_q+sqrtf(delt))*0.5);
   Real ret2=cube((-m_q-sqrtf(delt))*0.5);
   return ret1+ret2;
  }
  else
  {
   std::complex<Real> ret1=cube((-m_q+sqrt(std::complex<Real>(delt,0)))*std::complex<Real>(0.5,0));
   std::complex<Real> ret2=cube((-m_q-sqrt(std::complex<Real>(delt,0)))*std::complex<Real>(0.5,0));
   return (ret1+ret2).real();
  }
 }
 //返回true表示有三个实根，返回false表示只有一个实根
 //即初中笔记中的跳板公式
 bool x2x3OfE3(Real &x2,Real &x3)
 {
  Real x1=xOfE3();
  Real delt1=-3*x1*x1-4*m_p;
  if(delt1>=0)
  {
   x2=(-x1+sqrtf(delt1))*0.5;
   x3=(-x1-sqrtf(delt1))*0.5;
   return true;
  }
  else
   return false;//即另外两根为虚根或伪虚根
 }
public:
   Real m_p;
   Real m_q;
};

/*
魏尔斯特拉斯方程EC1:y^2+a_1xy+a_3y=x^3+a_2x^2+a_4x+a_6
表示一个椭圆曲线时有一个不为0的不变量△
*/
template <class real>struct EC1
{
public:
 EC1(real a1,real a3,real a2,real a4,real a6):m_a1(a1),m_a3(a3),m_a2(a2),m_a4(a4),m_a6(a6){}
 real b2OfEC()
 {
  return m_a1*m_a1+4*m_a2;
 }
 real b4OfEC()
 {
  return m_a1*m_a3+2*m_a4;
 }
 real b6OfEC()
 {
  return m_a3*m_a3+4*m_a6;
 }
 real b8OfEC()
 {
  return (b2OfEC()*b6OfEC()-b4OfEC())/4;
 }
 real c4OfEC()
 {
  return b2OfEC()*b2OfEC()-24*b4OfEC();
 }
 real c6OfEC()
 {
  return -b2OfEC()*b2OfEC()*b2OfEC()+36*b2OfEC()*b4OfEC()-216*b6OfEC();
 }
 real DeltOfEC()
 {
  //错误的：
  //return (c4OfEC()*c4OfEC()*c4OfEC()-c6OfEC()*c6OfEC())/35831808;
  //real c4=c4OfEC();
  //real c6=c6OfEC();
  //return (c4*c4*c4-c6*c6)/35831808;
  //正确的：
  real b2=b2OfEC();
  real b4=b4OfEC();
  real b6=b6OfEC();
  real b8=b8OfEC();
  return -b2*b2*b8-8*b4*b4*b4-27*b6*b6+9*b2*b4*b6;
 }
 real jOfEC()
 {
  return c4OfEC()*c4OfEC()*c4OfEC()/DeltOfEC();
 }
public:
 real m_a1;
 real m_a3;
 real m_a2;
 real m_a4;
 real m_a6;
};

/*
复分析中的魏尔斯特拉斯标准型EC2:y^2=4x^3-g_2x+g_3
可以用P（花体）函数参数化：x=P(z),y=P'(z)
*/
template <class real>struct EC2
{
public:
 EC2(real g2,real g3):m_g2(g2),m_g3(g3){}
 real DeltOfEC()
 {
  return m_g2*m_g2*m_g2-27*m_g3*m_g3;
 }
 real jOfEC()
 {
  return 1728*m_g2*m_g2*m_g2/DeltOfEC();
 }
public:
 real m_g2;
 real m_g3;
};

/*
数论和算术中常用的形式EC3:y^2=x^3+ax+b
*/
template <class real>struct EC3
{
public:
 EC3(real a,real b):m_a(a),m_b(b){}
 real b2OfEC()
 {
  return 0;
 }
 real b4OfEC()
 {
  return 2*m_a;
 }
 real b6OfEC()
 {
  return 4*m_b;
 }
 real b8OfEC()
 {
  return (b2OfEC()*b6OfEC()-b4OfEC())/4;
 }
 real c4OfEC()
 {
  return b2OfEC()*b2OfEC()-24*b4OfEC();
 }
 real c6OfEC()
 {
  return -b2OfEC()*b2OfEC()*b2OfEC()+36*b2OfEC()*b4OfEC()-216*b6OfEC();
 }
 real DeltOfEC()
 {
  return -16*(4*m_a*m_a*m_a+27*m_b*m_b);//不要把27写成26
 }
 real jOfEC()
 {
  //return c4OfEC()*c4OfEC()*c4OfEC()/DeltOfEC();//正确的
  return -1728*64*m_a*m_a*m_a/DeltOfEC();//加一个负号
 }
public:
 real m_a;
 real m_b;
};

#endif

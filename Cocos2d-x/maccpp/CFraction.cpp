//#include "stdafx.h"
#include "CFraction.h"
#include <cmath>
//辗转相除法求最大公约数
int Function(int& a,int& b)
{
	int r=a%b;
	while(r)
	{
		a=b;
		b=r;
		r=a%b;
	}
	return b;
}
ostream& operator<<(ostream& os,CFraction& f)
{
	f.Simplification();
	if(f.m_IsNegative)//负数
		os<<"  -"<<f.m_molecular<<"/"<<f.m_denomilator<<endl;
	else//正数
		os<<"   "<<f.m_molecular<<"/"<<f.m_denomilator<<endl;
	return os;
}
CFraction::CFraction(int a, int b):m_IsNegative(false)
{//默认分数为正1
	while(b==0)
	{
		cout<<"分母不能为0，请重新输入分母:"<<endl;
		cin>>b;
	}
	this->m_molecular=abs(a);
	this->m_denomilator=abs(b);
	if(a<0&&b<0)
		this->m_IsNegative=false;
	else if(a<0||b<0)
		this->m_IsNegative=true;
	else
		this->m_IsNegative=false;
	this->Simplification();
}
float CFraction::GetValue()const
{
	return this->m_molecular/(float)m_denomilator;
}
void CFraction::Simplification()
{
	int a=m_molecular,b=m_denomilator;
	int ret=Function(a,b);
	m_molecular/=ret;
	m_denomilator/=ret;
}
CFraction CFraction::operator +(const CFraction &f)const
{
	CFraction temp;
	if(m_IsNegative==f.m_IsNegative)//同号相加
	{
		temp.m_molecular=m_molecular*f.m_denomilator+m_denomilator*f.m_molecular;
		temp.m_denomilator=m_denomilator*f.m_denomilator;
		temp.m_IsNegative=m_IsNegative;
	}
	else// 不同号
	{
		temp.m_molecular=abs(m_molecular*f.m_denomilator-m_denomilator*f.m_molecular);
		temp.m_denomilator=abs(m_denomilator*f.m_denomilator);
		if(this->GetValue()>f.GetValue())
			temp.m_IsNegative=m_IsNegative;
		else
			temp.m_IsNegative=f.m_IsNegative;
	}
	return temp;
}
void CFraction::Show()
{
	cout<<*this;
}
CFraction CFraction::operator -(const CFraction &f) const
{
	CFraction temp;
	if(m_IsNegative==f.m_IsNegative)//同号相减
	{
		temp.m_molecular=abs(m_molecular*f.m_denomilator-m_denomilator*f.m_molecular);
		temp.m_denomilator=m_denomilator*f.m_denomilator;
		if(GetValue()>=f.GetValue())
			temp.m_IsNegative=false;
		else
			temp.m_IsNegative=true;
	}
	else//异号相减
	{
		temp.m_molecular=m_molecular*f.m_denomilator+m_denomilator*f.m_molecular;
		temp.m_denomilator=m_denomilator*f.m_denomilator;
		temp.m_IsNegative=m_IsNegative;
	}
	return temp;
}
CFraction CFraction::operator *(const CFraction &f) const
{
	CFraction temp;
	temp.m_molecular=m_molecular*f.m_molecular;
	temp.m_denomilator=m_denomilator*f.m_denomilator;
	//接下来确定符号
	if(m_IsNegative==f.m_IsNegative)//同号相乘符号为正
		temp.m_IsNegative=false;
	else
		temp.m_IsNegative=true;
	return temp;

}
CFraction CFraction::operator /(CFraction &f) const
{
	CFraction temp,r;
	r=f.GetReciprocal();
	temp=*this*r;
	return temp;
}
CFraction CFraction::GetReciprocal()
{
	CFraction temp;
	temp.m_denomilator=m_molecular;
	temp.m_molecular=m_denomilator;
	temp.m_IsNegative=m_IsNegative;
	return temp;
}
bool CFraction::operator ==(const CFraction &f) const
{
	if(m_IsNegative!=f.m_IsNegative)//不同号肯定不相等
		return false;
	if(GetValue()==f.GetValue())
		return true;
	else
		return false;
}
bool CFraction::operator <(const CFraction &f) const
{
	if(m_IsNegative==f.m_IsNegative)//同号比较大小
	{
		if(GetValue()<f.GetValue())
		{
			if(m_IsNegative)
				return false;
			else
				return true;
		}
		else if(GetValue()>f.GetValue())
		{
			if(m_IsNegative)
				return true;
			else
				return false;
		}
		else//相等的分数
			return false;
	}
	else if(m_IsNegative)//左负友正
		return true;
	else// 左正右负
		return false;
}
bool CFraction::operator >(const CFraction& f)const//大于号小于号刚好相反
{
	return (f<*this);
}
void CFraction::ChangeValue(int a,int b)
{
	*this=CFraction(a,b);
}
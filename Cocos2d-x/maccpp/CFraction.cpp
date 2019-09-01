//#include "stdafx.h"
#include "CFraction.h"
#include <cmath>
//շת����������Լ��
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
	if(f.m_IsNegative)//����
		os<<"  -"<<f.m_molecular<<"/"<<f.m_denomilator<<endl;
	else//����
		os<<"   "<<f.m_molecular<<"/"<<f.m_denomilator<<endl;
	return os;
}
CFraction::CFraction(int a, int b):m_IsNegative(false)
{//Ĭ�Ϸ���Ϊ��1
	while(b==0)
	{
		cout<<"��ĸ����Ϊ0�������������ĸ:"<<endl;
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
	if(m_IsNegative==f.m_IsNegative)//ͬ�����
	{
		temp.m_molecular=m_molecular*f.m_denomilator+m_denomilator*f.m_molecular;
		temp.m_denomilator=m_denomilator*f.m_denomilator;
		temp.m_IsNegative=m_IsNegative;
	}
	else// ��ͬ��
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
	if(m_IsNegative==f.m_IsNegative)//ͬ�����
	{
		temp.m_molecular=abs(m_molecular*f.m_denomilator-m_denomilator*f.m_molecular);
		temp.m_denomilator=m_denomilator*f.m_denomilator;
		if(GetValue()>=f.GetValue())
			temp.m_IsNegative=false;
		else
			temp.m_IsNegative=true;
	}
	else//������
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
	//������ȷ������
	if(m_IsNegative==f.m_IsNegative)//ͬ����˷���Ϊ��
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
	if(m_IsNegative!=f.m_IsNegative)//��ͬ�ſ϶������
		return false;
	if(GetValue()==f.GetValue())
		return true;
	else
		return false;
}
bool CFraction::operator <(const CFraction &f) const
{
	if(m_IsNegative==f.m_IsNegative)//ͬ�űȽϴ�С
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
		else//��ȵķ���
			return false;
	}
	else if(m_IsNegative)//������
		return true;
	else// �����Ҹ�
		return false;
}
bool CFraction::operator >(const CFraction& f)const//���ں�С�ںŸպ��෴
{
	return (f<*this);
}
void CFraction::ChangeValue(int a,int b)
{
	*this=CFraction(a,b);
}
#ifndef CFRACTION_H_
#define CFRACTION_H_
#include <iostream>
using  namespace std;
class CFraction
{
public:
	CFraction(int a=1,int b=1);
	virtual ~CFraction(){};
	float GetValue()const;//获取分数值
	void Simplification();//化简
	void Show();//显示分数
	friend ostream& operator<<(ostream& os,CFraction& f);
	//重载四则运算操作符
	CFraction operator +(const CFraction& f)const;
	CFraction operator -(const CFraction& f)const;
	CFraction operator *(const CFraction& f)const;
	CFraction operator /(CFraction& f)const;
	//重载比较操作符
	bool operator ==(const CFraction& f)const;
	bool operator >(const CFraction& f)const;
	bool operator <(const CFraction& f)const;
	CFraction GetReciprocal();//获取分数的倒数
	void ChangeValue(int a,int b);//改变当前分数分子和分母
private:
	int m_molecular;//分子
	int m_denomilator;//分母
	bool m_IsNegative;//是否为负数 
};
#endif
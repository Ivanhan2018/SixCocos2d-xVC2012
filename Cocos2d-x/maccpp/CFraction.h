#ifndef CFRACTION_H_
#define CFRACTION_H_
#include <iostream>
using  namespace std;
class CFraction
{
public:
	CFraction(int a=1,int b=1);
	virtual ~CFraction(){};
	float GetValue()const;//��ȡ����ֵ
	void Simplification();//����
	void Show();//��ʾ����
	friend ostream& operator<<(ostream& os,CFraction& f);
	//�����������������
	CFraction operator +(const CFraction& f)const;
	CFraction operator -(const CFraction& f)const;
	CFraction operator *(const CFraction& f)const;
	CFraction operator /(CFraction& f)const;
	//���رȽϲ�����
	bool operator ==(const CFraction& f)const;
	bool operator >(const CFraction& f)const;
	bool operator <(const CFraction& f)const;
	CFraction GetReciprocal();//��ȡ�����ĵ���
	void ChangeValue(int a,int b);//�ı䵱ǰ�������Ӻͷ�ĸ
private:
	int m_molecular;//����
	int m_denomilator;//��ĸ
	bool m_IsNegative;//�Ƿ�Ϊ���� 
};
#endif
#include<iostream>
#include<complex>
#include<vector>
#include<algorithm>
using namespace std;

/*
��ɭ˹̹������ŷ�������Ǿ���������ʽ�ĸ�����z=a+b�أ�����a��b���������Ҧ�=-1/2+sqrt(3)i/2=e^(2pii/3)�Ǳ�ԭ����ʵ�������ε�λ����
��ɭ˹̹�����ڸ�ƽ�����γ���һ�������ε��󡣸�˹�������γ���һ�������ε���
��ɭ˹̹�������еĿ���ԪȺ���Ǹ�ƽ�������ε�λ������ɵ�ѭ��Ⱥ�������ǣ�{��1,����,����^2}�������Ƿ���Ϊ1�İ�ɭ˹̹������
��x��y�ǰ�ɭ˹̹�������������ĳ����ɭ˹̹����z��ʹ��y=zx��������˵x������y��
����������������������졣�������Ҳ�������������ĸ��һ���ǿ���Ԫ�İ�ɭ˹̹����x�ǰ�ɭ˹̹�����������Ψһ��������ux����ʽ������u�����ε�λ�����κ�һ����
���ǿ���֤�����κ�һ����3����1��������������ʽx^2+-xy+y^2����˿��Էֽ�Ϊ(x+��y)(x+��^2y)����Ϊ���������ڰ�ɭ˹̹�����в�����������3����2���������ֽܷ�Ϊ������ʽ���������Ҳ�ǰ�ɭ˹̹������
�κ�һ����ɭ˹̹����a+b�أ�ֻҪ����a^2-ab+b^2Ϊ��������ô����һ����ɭ˹̹������ʵ���ϣ��κ�һ����ɭ˹̹����Ҫô����������ʽ��Ҫô����һ������Ԫ��һ����3����2�������ĳ˻���
��ɭ˹̹�������γ���һ��ŷ��������䷶��N�����µĹ�ʽ������
N(a+b��)=a^2-ab+b^2=|a+b��|^2----ע�ⲻҪ�������������еķ�������������еķ���
*/
bool IsPrime(unsigned int N)
{
	if(N==0||N==1)
		return false;
	int up=sqrt((float)N);
	for(int i=2;i<=up;i++)
	{
		if(N%i==0)
			return false;
	}
	return true;
}

class eint
{
public:
	eint(long a,long b)
	{
		m_a=a;
		m_b=b;
	}

	/*
		��ɭ˹̹����a+b�����������ҽ�����
		An Eisenstein integer z = a + b�� is an Eisenstein prime if and only if either of the following (mutually exclusive) conditions hold:
		z is equal to the product of a unit and a natural prime of the form 3n - 1, 
		|z|2 = a2 + ab + b2 is a natural prime (necessarily congruent to 0 or 1 modulo 3). 
		It follows that the absolute value squared of every Eisenstein prime is a natural prime or the square of a natural prime.
		3 = ?(1 + 2��)2 
		7 = (3 + ��)(2 ? ��). 
		2 + ��, 3 + ��, 4 + ��, 5 + 2��, 6 + ��, 7 + ��, 7 + 3��. 
	*/
	static bool IsPrime(eint N)
	{
#if 1
		// a+b�ص�6�����Ԫ��a+b��,-a-b�أ�-b+(a-b)�أ�b+(b-a)�أ�(b-a)-a�أ�(a-b)+a�أ���������a^-ab+b^2
		int norm=N.m_a*N.m_a+N.m_b*N.m_b-N.m_a*N.m_b;
		// a,-a��a�أ�-a�أ�-a-a�أ�a+a��
		if(N.m_a>0 && (N.m_a+1)%3==0 && N.m_b==0)
			return true;
		if(N.m_a<0 && (-N.m_a+1)%3==0 && N.m_b==0)
			return true;
		if(N.m_b>0 && (N.m_b+1)%3==0 && N.m_a==0)
			return true;
		if(N.m_b<0 && (-N.m_b+1)%3==0 && N.m_a==0)
			return true;
		if(N.m_a>0 && (N.m_a+1)%3==0 && N.m_b==N.m_a)
			return true;
		if(N.m_a<0 && (-N.m_a+1)%3==0 && N.m_b==N.m_a)
			return true;
		if(::IsPrime(norm))
			return true;
		return false;
#endif
#if 0
		//��2,1������1,2������-1,1������-2,-1�����ǰ�ɭ˹̹����
		//��2,0������2,2������0,2������-2,0������-2,-2������0,-2�����ǰ�ɭ˹̹����
		//int a1=abs(N.m_a);
		//int b1=abs(N.m_b);		
		//if(N.m_a==1 && N.m_b==-1)
		//	return true;
		//if(N.m_b==0 && (a1+1)%3==0)
		//	return true;
		int norm=N.m_a*N.m_a+N.m_b*N.m_b-N.m_a*N.m_b;
		if(::IsPrime(norm)/* && (abs(norm)+2)%3==0*/)
			return true;
		return false;
#endif
	}

	// �������ͷ�����ֵ��С��������˳��
	bool operator < (const eint &m)const 
	{
		int norm1=m_a*m_a+m_b*m_b-m_a*m_b;
		int norm2=m.m_a*m.m_a+m.m_b*m.m_b-m.m_a*m.m_b;
		float arg1=atan2f(m_b,m_a);
		float arg2=atan2f(m.m_b,m.m_a);
		float pi=atan2f(0,-1);
		if(arg1<0)
			arg1+=2*pi;
		if(arg2<0)
			arg2+=2*pi;
		if(norm1!=norm2)
			return norm1<norm2;
		else
			return arg1<arg2;
	}

	friend ostream& operator<< (ostream& os,const eint& N);
public:
	long m_a;
	long m_b;
};

ostream& operator<< (ostream& os,const eint& N)
{
	string strDes=(eint::IsPrime(N)?"�ǰ�ɭ˹̹����":"���ǰ�ɭ˹̹����");
	float pi=atan2f(0,-1);
	complex<float> zeta3=std::exp(complex<float>(0,2*pi/3));
	complex<float> z=complex<float>(N.m_a,0)+zeta3*complex<float>(N.m_b,0);
	cout<<N.m_a<<"+"<<N.m_b<<"��"<<"="<<z<<strDes<<" ";
	int norm1=N.m_a*N.m_a+N.m_b*N.m_b-N.m_a*N.m_b;
	cout<<"����ģ��"<<std::abs(z)<<"����:"<<norm1;
#if 0
	cout<<"    ";
	complex<float> z1=complex<float>(N.m_a,0)+zeta3*zeta3*complex<float>(N.m_b,0);
	cout<<N.m_a<<"+"<<N.m_b<<"��^2"<<"="<<z1;
#endif
	return os;
}

int main(void)
{
#if 0
	cout<<eint(1,0)<<endl;
	cout<<eint(-1,0)<<endl;
	cout<<eint(0,1)<<endl;
	cout<<eint(0,-1)<<endl;
	cout<<eint(1,1)<<endl;
	cout<<eint(1,-1)<<endl;
	cout<<eint(4,3)<<endl;
	cout<<eint(5,4)<<endl;
	cout<<eint(0,0)<<endl;
#endif

#if 1
	int n=4;
	int Norm=n*n*3;
	float pi=atan2f(0,-1);
	complex<float> zeta3=std::exp(complex<float>(0,2*pi/3));
	complex<float> z=complex<float>(n,0)+zeta3*complex<float>(-n,0);
	float r=std::abs(z);
	vector<eint> veint;
	for(int i=-n;i<=n;i++)
		for(int j=-n;j<=n;j++)
		{
			eint a(i,j);  
			veint.push_back(a);
			//cout<<a<<endl;
		}
		cout<<"����ģ������"<<r<<"�ҷ���������"<<Norm<<"�İ�ɭ˹̹��������"<<veint.size()<<"����"<<endl;
		sort(veint.begin(), veint.end(),less<eint>());
		for(int j=0;j<veint.size();j++)
		{
			cout<<"��"<<j<<"����ɭ˹̹������"<<veint[j]<<endl;
			if(j>0 && j%297==0)
			{
				//system("pause");
			}
		}
#endif

	//system("pause");
	return 0;
}


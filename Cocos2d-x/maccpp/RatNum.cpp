//c++����������
#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#include <stdio.h>
#include <tchar.h>
#include<iostream>
using namespace std;

class RatNum                                     //����һ����������RatNum 
{
public:
      int fz;
      int fm;
      public:
      RatNum(){}     //���캯�� 
      ~RatNum(){}    //�������� 
      RatNum(int z,int m){fz=z;fm=m;cout<<"������Ϊ��"<<fz<<"/"<<fm<<endl;}//�������Ĺ��캯���Ķ��壬���ڳ�ʼ�������Ա��ֵ 
      void set_Rat(int z,int m){fz=z;fm=m;}        //�Զ����е����ݳ�Ա��ֵ������ 
      int get_Ratz();                                //��ȡ���ӵ�ֵ 
      int get_Ratm();                               //��ȡ��ĸ��ֵ 
      int common();                              //���ź���������������Լ�������� 
      RatNum& operator +(RatNum &R);   //���������������+������������������Ϊ�����������ͣ� 
      RatNum& operator -(RatNum &R);    //���������������-������������������Ϊ�����������ͣ�
      RatNum& operator *(RatNum &R);    //���������������*������������������Ϊ�����������ͣ�
      RatNum& operator /(RatNum &R);    //���������������/������������������Ϊ�����������ͣ�
      RatNum& operator ==(RatNum &R);    //���������������==���������������ж������������Ƿ���ȣ�
      double real();                    //ת��ʵ�������������� 
};

ostream &operator<<(ostream &s,const RatNum &r)            //����<<�ĺ�������������������һ����cout��һ������Ķ������� 
{                                                          //cout��ostream�Ķ���ֻ�ܷ�����Ĺ������ݳ�Ա���������ȫ�����غ��� 
     s<<r.fz;
     s<<"/";    
     s<<r.fm;
     return s;
}

istream &operator>>(istream &s,RatNum &r)//����>>�ĺ���������Ϊȫ�ֺ�����cin��istream�Ķ���ֻ�ܷ�����Ĺ������ݳ�Ա 
{
    s>>r.fz;
    s>>r.fm;
    return s;
} 
int RatNum::get_Ratz()
{  
    return fz;  
}
int  RatNum::get_Ratm()
{
     return fm;
}
int RatNum::common()    //�������Ż���������ȡ���Լ���������¸�ֵ�����ӷ�ĸ 
{
    int temp,a,b,i;
    a=fm;
    b=fz;
    if(fz<fm)
    {
         temp=fm;          //�����������temp�����ڽ������ӷ�ĸ��ֵ�������ӱȷ�ĸСʱ�� 
         fm=fz;
         fz=temp;
         a=fz;
         b=fm;
    }
    i=fz%fm;
    while(i!=0)             //��ȡ���Լ������i������ʱ������ѭ�������ص���fm��fm����Ҫ�����Լ�� 
    {
               fz=fm;
               fm=i;
               i=fz%fm;
    } 
   
    cout<<"����������������Ϊ��"<<b/fm<<"/"<<a/fm<<endl;
    fz=b/fm;            //����Լ�ֵĽ�����¸�ֵ������
    fm=a/fm;            //��ĸԼ�ֵĽ�����¸�ֵ����ĸ
    return 0; 
    
} 
RatNum &RatNum:: operator +(RatNum &R)               
{
       
       fz=fz*R.fm+fm*R.fz;
       fm=fm*R.fm;
       return *this;       //����thisָ�룬����ָ���Ա���������ط��ӷ�ĸ��ֵ 
}
RatNum &RatNum:: operator -(RatNum &R)
{
       fz=fz*R.fm-fm*R.fz;
       fm=fm*R.fm;
       return *this;  
}
RatNum &RatNum:: operator *(RatNum &R)
{
       fz=fz*R.fz;
       fm=fm*R.fm;
       return *this;
}
RatNum &RatNum:: operator /(RatNum &R)
{
      fz=fz*R.fm;
      fm=fm*R.fz;
     return *this;
       
        
}
RatNum& RatNum:: operator ==(RatNum &R)
{
        R.common();
        if(fz==R.fz&&fm==R.fm)
        cout<<"���������������"<<endl;
        else
        cout<<"�����������������"<<endl;
        return *this; 
}
double RatNum::real()                        //ת��ʵ������real�����Ķ��壻 
{
       return double(fz/fm);
}

void pause()
{
#ifdef _MSC_VER
	system("pause");
#endif
}

int main()
{
    RatNum A(5,6);
    A.common();
    cout<<A;
    cout<<endl<<endl;
    cout<<"��������Ӻͷ�ĸ�����ӷ�ĸ�м��ÿո�ָ���"<<endl; 
    RatNum B;
    cin>>B;
    cout<<"���������Ϊ��"<<B<<endl;
    B.common(); 
   // system("cls");                            //������������� 
    cout<<endl<<endl;
    cout<<"����ִ����һ��䣺"<<endl;
    pause();                           //�������ʱ��ͣ�� 
    RatNum R1(3,4);                           //�������� 
    R1.common();                             //�Ż�����������������ʹ������Լȥ����ĸ
    RatNum R2;
    cout<<"������R2�ķ��Ӻͷ�ĸ���Կո�ָ����Ӻͷ�ĸ��"<<endl;
    cin>>R2;
    cout<<"���������Ϊ��"<<R2<<endl;
    R2.common();
    pause();
    system("cls");                          //ִ�г������������ 
    cout<<"����ִ������������"<<endl;
    cout<<endl<<endl;
    cout<<"����ʣ��Ľ���ǣ�"<<endl;
    pause();                          //������ͣ 
    RatNum R3;
    R3.set_Rat(4,5);
    cout<<"������Ϊ��"<<R3.get_Ratz()<<"/"<<R3.get_Ratm()<<endl;
    R3.common();
    RatNum R4(2,5);
    R4.operator +(R1);
    cout<<"��������Ӻ�Ľ��Ϊ��"<<R4.get_Ratz()<<"/"<<R4.get_Ratm(); 
    R4.common();
    pause();
    cout<<endl<<endl;
    RatNum R5(5,6);
    R5.operator -(R1);
    cout<<"�����������Ľ��Ϊ��"<<R5.get_Ratz()<<"/"<<R5.get_Ratm();
    R5.common();
    pause();
    cout<<endl<<endl;
    RatNum R6(1,3);
    R6.operator *(R1);
    cout<<"��������˺�Ľ��Ϊ��"<<R6.get_Ratz()<<"/"<<R6.get_Ratm();
    R6.common();
    pause();
    cout<<endl<<endl; 
    RatNum R7(1,2);
    R7.operator /(R1);
    cout<<"�����������Ľ��Ϊ��"<<R7.get_Ratz()<<"/"<<R7.get_Ratm();
    R7.common();
    pause();
    cout<<endl<<endl;
    RatNum R8(4,6);
    R8.common(); 
    RatNum R9(2,3);
    R8.operator==(R9);
    cout<<"��������ȵ�������Ϊ��"<<R8.get_Ratz()<<"/"<<R8.get_Ratm();
    pause(); 
    cout<<endl<<endl;
    RatNum R10(1,6);
    RatNum R0(4,9);
    R10.common();
    R10.operator==(R0);
    cout<<endl<<endl;
    RatNum R11(8,7);                            //������󲢳�ʼ�����ӷ�ĸ�����ó�Ա����real����ת��Ϊʵ���� 
    cout<<"ת��Ϊʵ����Ϊ��"<<R11.real()<<endl; 
    pause();
    return 0; 
} 

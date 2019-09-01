//c++有理数程序
#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#include <stdio.h>
#include <tchar.h>
#include<iostream>
using namespace std;

class RatNum                                     //定义一个有理数类RatNum 
{
public:
      int fz;
      int fm;
      public:
      RatNum(){}     //构造函数 
      ~RatNum(){}    //析构函数 
      RatNum(int z,int m){fz=z;fm=m;cout<<"有理数为："<<fz<<"/"<<fm<<endl;}//带参数的构造函数的定义，用于初始化对象成员的值 
      void set_Rat(int z,int m){fz=z;fm=m;}        //对对象中的数据成员的值的设置 
      int get_Ratz();                                //获取分子的值 
      int get_Ratm();                               //获取分母的值 
      int common();                              //最优函数的声明，用于约分有理数 
      RatNum& operator +(RatNum &R);   //重载运算符函数“+”的声明；返回类型为有理数类类型； 
      RatNum& operator -(RatNum &R);    //重载运算符函数“-”的声明；返回类型为有理数类类型；
      RatNum& operator *(RatNum &R);    //重载运算符函数“*”的声明；返回类型为有理数类类型；
      RatNum& operator /(RatNum &R);    //重载运算符函数“/”的声明；返回类型为有理数类类型；
      RatNum& operator ==(RatNum &R);    //重载运算符函数“==”的声明；用于判断两个有理数是否相等；
      double real();                    //转换实数函数的声明； 
};

ostream &operator<<(ostream &s,const RatNum &r)            //重载<<的函数，接受两个参数，一个是cout，一个是类的对象名； 
{                                                          //cout是ostream的对象，只能访问类的公有数据成员，定义的是全局重载函数 
     s<<r.fz;
     s<<"/";    
     s<<r.fm;
     return s;
}

istream &operator>>(istream &s,RatNum &r)//重载>>的函数。定义为全局函数，cin是istream的对象，只能访问类的公有数据成员 
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
int RatNum::common()    //创建的优化函数，提取最大公约数；并重新赋值给分子分母 
{
    int temp,a,b,i;
    a=fm;
    b=fz;
    if(fz<fm)
    {
         temp=fm;          //定义随机变量temp，用于交换分子分母的值，当分子比分母小时。 
         fm=fz;
         fz=temp;
         a=fz;
         b=fm;
    }
    i=fz%fm;
    while(i!=0)             //求取最大公约数，当i等于零时，跳出循环，返回的是fm，fm是所要的最大公约数 
    {
               fz=fm;
               fm=i;
               i=fz%fm;
    } 
   
    cout<<"化简后的有理数分数为："<<b/fm<<"/"<<a/fm<<endl;
    fz=b/fm;            //分子约分的结果重新赋值给分子
    fm=a/fm;            //分母约分的结果重新赋值给分母
    return 0; 
    
} 
RatNum &RatNum:: operator +(RatNum &R)               
{
       
       fz=fz*R.fm+fm*R.fz;
       fm=fm*R.fm;
       return *this;       //返回this指针，用于指向成员函数，返回分子分母的值 
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
        cout<<"这两个有理数相等"<<endl;
        else
        cout<<"这两个有理数不相等"<<endl;
        return *this; 
}
double RatNum::real()                        //转换实数函数real（）的定义； 
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
    cout<<"请输入分子和分母，分子分母中间用空格分隔："<<endl; 
    RatNum B;
    cin>>B;
    cout<<"您输入的数为："<<B<<endl;
    B.common(); 
   // system("cls");                            //程序的清屏处理 
    cout<<endl<<endl;
    cout<<"程序执行下一语句："<<endl;
    pause();                           //程序的暂时暂停； 
    RatNum R1(3,4);                           //创建对象 
    R1.common();                             //优化函数，它的作用是使有理数约去公分母
    RatNum R2;
    cout<<"请输入R2的分子和分母，以空格分隔分子和分母："<<endl;
    cin>>R2;
    cout<<"您输入的数为："<<R2<<endl;
    R2.common();
    pause();
    system("cls");                          //执行程序的清屏处理 
    cout<<"程序执行清屏操作："<<endl;
    cout<<endl<<endl;
    cout<<"程序剩余的结果是："<<endl;
    pause();                          //程序暂停 
    RatNum R3;
    R3.set_Rat(4,5);
    cout<<"有理数为："<<R3.get_Ratz()<<"/"<<R3.get_Ratm()<<endl;
    R3.common();
    RatNum R4(2,5);
    R4.operator +(R1);
    cout<<"有理数相加后的结果为："<<R4.get_Ratz()<<"/"<<R4.get_Ratm(); 
    R4.common();
    pause();
    cout<<endl<<endl;
    RatNum R5(5,6);
    R5.operator -(R1);
    cout<<"有理数相减后的结果为："<<R5.get_Ratz()<<"/"<<R5.get_Ratm();
    R5.common();
    pause();
    cout<<endl<<endl;
    RatNum R6(1,3);
    R6.operator *(R1);
    cout<<"有理数相乘后的结果为："<<R6.get_Ratz()<<"/"<<R6.get_Ratm();
    R6.common();
    pause();
    cout<<endl<<endl; 
    RatNum R7(1,2);
    R7.operator /(R1);
    cout<<"有理数相除后的结果为："<<R7.get_Ratz()<<"/"<<R7.get_Ratm();
    R7.common();
    pause();
    cout<<endl<<endl;
    RatNum R8(4,6);
    R8.common(); 
    RatNum R9(2,3);
    R8.operator==(R9);
    cout<<"这两个相等的有理数为："<<R8.get_Ratz()<<"/"<<R8.get_Ratm();
    pause(); 
    cout<<endl<<endl;
    RatNum R10(1,6);
    RatNum R0(4,9);
    R10.common();
    R10.operator==(R0);
    cout<<endl<<endl;
    RatNum R11(8,7);                            //定义对象并初始化分子分母，调用成员函数real（）转换为实数。 
    cout<<"转换为实数后为："<<R11.real()<<endl; 
    pause();
    return 0; 
} 

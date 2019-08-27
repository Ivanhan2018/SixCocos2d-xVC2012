//#include<stdio.h>
//#include<stdlib.h>
#include<assert.h>

//#include<typeinfo.h>
// 大整数类的声明
#include<iostream>
#include<math.h>
#include<stdlib.h>
//#include<conio.h>
#include<string.h>
using namespace std;

const unsigned long MaxSize = 100; //大整数最大长度400*4个10进制位

class Verylong
{
public:
	Verylong();
	Verylong(int inttype);
	Verylong(long l);
	Verylong(unsigned long l);
	Verylong(const Verylong &v);
	Verylong(long _signal,long _size,long* _data);//测试时用
	~Verylong(){};

	friend Verylong operator + (const Verylong &v1,const Verylong &v2);
    friend Verylong operator - (const Verylong &v1,const Verylong &v2);
    friend Verylong operator * (const Verylong &v1,const Verylong &v2);
    friend Verylong operator / (const Verylong &v1,const Verylong &v2);
	friend Verylong operator % (const Verylong &v1,const Verylong &v2);
    friend Verylong operator - (const Verylong &v1);
	Verylong operator = (const Verylong &v1);
	bool operator !();

    friend bool operator > (const Verylong &v1,const Verylong &v2);
	friend bool operator <= (const Verylong &v1,const Verylong &v2);
	friend bool operator == (const Verylong &v1,const Verylong &v2); 
	friend bool operator >= (const Verylong &v1,const Verylong &v2);	
	friend bool operator < (const Verylong &v1,const Verylong &v2);	
	friend bool operator != (const Verylong &v1,const Verylong &v2);

	Verylong operator ++();  //++i
	Verylong operator ++(int);  //i++
	Verylong operator --();	
	Verylong operator --(int);  //i--
	Verylong operator += (const Verylong &v1);
	Verylong operator -= (const Verylong &v1);
	Verylong operator *= (const Verylong &v1);
	Verylong operator /= (const Verylong &v1);
	Verylong operator %= (const Verylong &v1);

	Verylong operator <<(long i);  //左移
	Verylong operator >>(long i);  //右移	
	Verylong operator <<= (long i);  //左移
	Verylong operator >>= (long i);  //右移

	Verylong rshiftr(long i);		//右移移出部分
	unsigned long toUlong();

	friend Verylong operator & (const Verylong &v1,const Verylong &v2);
	friend Verylong operator | (const Verylong &v1,const Verylong &v2);
	friend Verylong operator ^ (const Verylong &v1,const Verylong &v2);
	Verylong operator ~ ();

	friend Verylong power(const Verylong &v1,const Verylong &v2);
	friend Verylong power(const Verylong &v1,const Verylong &v2,const Verylong &v3);
	friend void matrixpower(Verylong *x,long n,const Verylong &yy,const Verylong &pp,Verylong *fw);
	friend Verylong mod(const Verylong &v1,const Verylong &v2);
	friend istream& operator >>(istream &in,Verylong &v);
	friend ostream& operator <<(ostream &out,const Verylong &v);

	long getSignal(){return signal;}

protected:
	void assign(const Verylong &v2);//赋值
	Verylong quotRem (const Verylong &v2,Verylong &re) const;  //带余除法

	Verylong vpower(const Verylong &v2) const;  //指数为Verylong类型
	Verylong lpower(long lo) const; //指数为long类型
	Verylong vpower(const Verylong &v2,const Verylong &v3) const;
	Verylong lpower(long l2,const Verylong &v3) const;
	Verylong str2very(const char instr[4*MaxSize+1]); //将数字串转化成Verylong数据
	Verylong bit2very(const unsigned long lo[]) const;
	void very2str(char str[4*MaxSize+1]) const; ///将Verylong数据转化成数字串
	void very2bit(unsigned long lo[]) const; //3.33 = log(2,10)
	
	Verylong rshift(long i,unsigned long r[]) const; //右移,返回移位结果及移出部分

protected:
	long data[MaxSize];
	long size;
	long signal; //1,0,-1
};

Verylong::Verylong()
{
	memset(data,0,MaxSize*sizeof(long));
	size=1;
	signal=0;
}

//测试大整数时用
Verylong::Verylong(long _signal,long _size,long* _data)
{
    size=_size;

    for(long i=size-1;i>=0;i--)
		data[i]=_data[i];

    for(long i=size;i<MaxSize;i++)
        data[i]=0;

    signal=_signal;
}


Verylong::Verylong(int inttype)
{
	if(inttype==0)
		signal=0;
	else if(inttype<0)
	{
		signal=-1;
		inttype*=-1;
	}
	else
		signal=1;
		
	data[0]=inttype%10000;
	data[1]=0;
	size=1;
	if(inttype>=10000)
	{
		data[1]=inttype/10000;
		size++;
	}
	memset(data+2,0,(MaxSize-2)*sizeof(long));
}

Verylong::Verylong(long l)
{
	if(l==0)
		signal=0;
	else if(l<0)
	{
		signal=-1;
		l=-l;
	}
	else
		signal=1;
	data[0]=l%10000;
	data[1]=data[2]=0;
	size=1;
	if(l>=10000)
	{
		data[1]=(l/10000)%10000;
		size++;
	}
	if(l>=100000000)
	{
		data[2]=l/100000000;
		size++;
	}
	memset(data+3,0,(MaxSize-3)*sizeof(long));
}

Verylong::Verylong(unsigned long l)
{
	if(l==0)
		signal=0;
	else
		signal=1;
	data[0]=l%10000;
	data[1]=data[2]=0;
	size=1;
	if(l>=10000)
	{
		data[1]=(l/10000)%10000;
		size++;
	}
	if(l>=100000000)
	{
		data[2]=l/100000000;
		size++;
	}
	memset(data+3,0,(MaxSize-3)*sizeof(long));
}

Verylong::Verylong(const Verylong &v)
{
	this->assign(v);
}

void Verylong::assign(const Verylong &v)  //赋值
{
	size=v.size;
	for(int i=size-1;i>=0;i--)
		data[i]=v.data[i];
	for(int i=size;i<MaxSize;i++)
		data[i]=0;
	signal=v.signal;
}

Verylong Verylong::operator =(const Verylong &v1)
{	
	this->assign(v1);
	return *this;
}

//大整数类的实现
#define VERYLONG_CPP  verylong_cpp

#ifndef INF 
#define INF -1    //错误标记
#endif

const double lo2g10 = 3.33; // log(2,10)

Verylong operator + (const Verylong &v1,const Verylong &v2)
{
	if(v1==0)
		return v2;
	if(v2==0)
		return v1;
	Verylong v;
	int i=0;
	while(i<v1.size&&i<v2.size)
	{
		v.data[i]+=v1.signal*v1.data[i]+v2.signal*v2.data[i];

		if(v.data[i]>=10000)
		{
			v.data[i]-=10000;
			v.data[i+1]++;
		}
		if(v.data[i]<=-10000)
		{
			v.data[i]+=10000;
			v.data[i+1]--;
		}
		i++;
	}
	while(i<v1.size)
	{
		v.data[i]+=v1.signal*v1.data[i];
		i++;
	}
	while(i<v2.size)
	{
		v.data[i]+=v2.signal*v2.data[i];
		i++;
	}
	for(;i>=0;i--)
		if(v.data[i]!=0)
			break;
	if(i<0)
		v.size=1;
	else
		v.size=i+1;

    if(v.data[v.size-1]<0)
	{
		v.signal=-1;
		v.data[v.size-1]*=-1;
		for(int i=v.size-2;i>=0;i--)
		{
			if(v.data[i]>0)
			{
				v.data[i]-=10000;
				v.data[i+1]--;   //已经转换成对应的相反数
			}
			v.data[i]*=-1;
		}
	}
	else if(v.data[v.size-1]>0)     // 也可能是等于0的
	{
		v.signal=1;
		for(i=v.size-2;i>=0;i--)
			if(v.data[i]<0)
			{
				v.data[i]+=10000;
				v.data[i+1]--;
			}
	}
	while(v.data[v.size-1]==0&&v.size!=1)
	{
		v.size--;
	}
	if(v.size==1&&v.data[0]==0)
		v.signal=0;
	return v;
}

Verylong operator -(const Verylong &v1)
{
	Verylong v=v1;
	v.signal=-v1.signal;
	return v;
}

Verylong operator -(const Verylong &v1,const Verylong &v2)
{
	return v1+(-v2);
}

Verylong operator * (const Verylong &v1,const Verylong &v2)
{
	Verylong v;
	long n;
	int i,j;
	v.signal=v1.signal*v2.signal;
	if(v1.size+v2.size>MaxSize)
	{
		cout<<"计算溢出!"<<endl;
		return -1;
	}
	for(i=0;i<v1.size;i++)
		for(j=0;j<v2.size;j++)
		{
			v.data[i+j]+=v1.data[i]*v2.data[j];
			if(v.data[i+j]>=10000)
			{
				n=long(v.data[i+j]/10000);
				v.data[i+j+1]+=n;
				v.data[i+j]-=n*10000;
			}
		}

	i=i+j+1;
	for(;i>=0;i--)
		if(v.data[i]!=0)
			break;
	if(i<0)
		v.size=1;
	else
		v.size=i+1;
	return v;
}

Verylong Verylong::quotRem(const Verylong &v2,Verylong &re) const //向下取整 这里有问题
{
	Verylong shang=0,temp=0;
	Verylong vv,rre;  //下一个结果
	long current;
	int j;//记数
	if(v2==0) 
	{
		cerr<<"error! 0 can not be divided!";
		return INF;
	}

	if(*this==0)
	{
		re=0;
		return 0;
	}
	if(*this==v2)
	{
		re=0;
		return 1;
	}

	Verylong v,v3=*this,v4=v2;
 
	short sign1=1,sign2=1;
	if(v3<0) // 化为正数计算
    {
		sign1*=-1;
	    v3=-v3;
    }
	if(v4<0)  //
    {
		sign2*=-1;
		v4=-v4;
	}
	if(v3<v4)
	{
		re=*this;
		return 0;
	}
  
    long vv3=v3.data[v3.size-1];
	long vv4=v4.data[v4.size-1];
	shang.size=v3.size-v4.size;
	shang.signal=1;
	if(vv3>=vv4)
		shang.size++;
	if(shang.size==0)
		shang.size=1;
	long sign=1;
	while(v3>=v4)
	{
		temp=0;	
		if(vv3>=vv4)
			temp.size=v3.size-v4.size+1;
		else
		{
			temp.size=v3.size-v4.size;   //不够,后移一位
			vv3=vv3*10000+v3.data[v3.size-2];
		}
		current=(long)(vv3/vv4);
		temp.data[temp.size-1]=current;
		temp.signal=1;
		shang.data[temp.size-1]+=sign*current;
	    v3=v3-v4*temp;	
	 
		if(v3<0)
		{
			v3=-v3;
			sign*=-1;
		}
		vv3=v3.data[v3.size-1];
	}
	if(sign==1 || v3.signal==0)
		rre=v3;
	else
	{
		shang--;
		rre=v4-v3;
	}

	for(j=0;j<shang.size-1;j++)
	{
		if(shang.data[j]<0)  //标准化
		{
			shang.data[j]+=10000;
			shang.data[j+1]--;
		}
	}
    while(shang.data[shang.size-1]==0&&shang.size!=1)
		shang.size--;
    if(rre.signal==0 || (sign1>0 && sign2 >0))
	{
		re=rre;
		return shang;
	}
	else if(sign1<0 && sign2<0)  //符号判定,向零取整
	{
	    re=-rre;
	    return shang;
	}
	else if(sign1<0 && sign2>0)
	{
		re=-rre;
		return -shang;
	}
	else
	{
		re=rre;
		return -shang;	
	}
}

Verylong operator /(const Verylong &v1,const Verylong &v2)
{
	Verylong re;
	return v1.quotRem(v2,re);  //带余除法
}

Verylong operator %(const Verylong &v1,const Verylong &v2)
{
	Verylong re;
	v1.quotRem(v2,re);
	return re;
}

bool Verylong::operator !()
{
	return *this!=0;
}

bool operator >(const Verylong &v1,const Verylong &v2)  //基本函数
{
	bool temp=true;
	if(v1.signal>0 && v2.signal<=0)
		return true;
	if(v1.signal<0 && v2.signal>=0)
		return false;
	if(v1.signal<0)
		temp=false;

	if(v1.size>v2.size)
		return temp;

	if(v1.size<v2.size)
		return !temp;

	for(int i=v1.size-1;i>=0;i--)
		if(v1.data[i]>v2.data[i])
			return temp;
		else if(v1.data[i]<v2.data[i])
			return !temp;

	return !temp;
}

bool operator <=(const Verylong &v1,const Verylong &v2)
{
	return !(v1>v2);
}

bool operator ==(const Verylong &v1,const Verylong &v2)
{
	if(v1.signal!=v2.signal || v1.size!=v2.size)
		return false;

	for(int i=0;i<v1.size;i++)
		if(v1.data[i]!=v2.data[i])
			return false;

	return true;
}

bool operator >=(const Verylong &v1,const Verylong &v2)
{
	return (v1>v2)||(v1==v2);
}

bool operator <(const Verylong &v1,const Verylong &v2)
{
	return !(v1>=v2);
}

bool operator !=(const Verylong &v1,const Verylong &v2)
{
	return !(v1==v2);
}

Verylong Verylong::operator ++() //++i
{
	*this=*this+1;
	return *this;
}

Verylong Verylong::operator ++(int) //i++
{
	Verylong temp=*this;
	*this=*this+1;
	return temp;
}

Verylong Verylong::operator --()
{
	*this=*this-1;
	return *this;
}

Verylong Verylong::operator --(int) //i--
{
	Verylong temp=*this;
	*this=*this-1;
	return temp;
}

Verylong Verylong::operator +=(const Verylong &v1)
{
	*this=*this+v1;
	return *this;
}

Verylong Verylong::operator -=(const Verylong &v1)
{
	*this=*this-v1;
	return *this;
}

Verylong Verylong::operator *=(const Verylong &v1)
{
	*this=(*this)*v1;
	return *this;
}

Verylong Verylong::operator /=( const Verylong &v1)
{
	*this=(*this)/v1;
	return *this;
}

Verylong Verylong::operator %=( const Verylong &v1)
{
	*this=(*this)%v1;
	return *this;
}

Verylong Verylong::str2very(const char str[4*MaxSize+1])
{
	char instr[4*MaxSize+1];
	int inint[4*MaxSize];
	int instrsize;
	int i;
	Verylong v;
	instrsize=strlen(str);
	if(str[0]=='-')
	{
		v.signal=-1;
		for(i=0;i<instrsize;i++)
			instr[i]=str[i+1];
		instrsize--;
	}
	else if(str[0]<'0'||str[0]>'9')
	{
		cout<<"参数错误!!\n";
		exit(0);
	}
	else
	{
		v.signal=1;
		for(i=0;i<instrsize;i++)
			instr[i]=str[i];
	}

	for(i=0;i<instrsize;i++)
	{
		if(instr[i]<'0'||instr[i]>'9')
		{
			cout<<"参数错误!!\n";
			exit(0);
		}
	}

	i=instrsize-1;
	for(;i>=0;i--)
	{
		inint[i]=instr[i]-'0';
	}

	int j=0;
	i=instrsize-1;
	while(i>=0)
	{
		int step=0;
		while(step!=4&&i>=0)
		{
			v.data[j]+=long(inint[i])*long(pow((float)10,step));
			step++;
			i--;
		}
		j++;
	}
   v.size=j;
   if(v.data[0]==0&&v.size==1)
	   v.signal=0;
   return v;
}

void Verylong::very2str(char str[4*MaxSize+1]) const
{
	int k=0;
	long nbit;
	long ndata=this->data[this->size-1];
	long sign=1;
	if(this->signal==-1)
		str[k++]='-';
	if(ndata==0)
		str[k++]='0';
    else
	{
		if(ndata<0)
		{
			sign=-1;
			str[k++]='-';
		}
		int j=0;
		nbit=1000;
		while(j<4&&ndata/nbit==0)
		{
			nbit/=10;
			j++;
		}
		for(;j<4;j++)
		{
			str[k++]=(long)(sign*ndata)/nbit+'0';
			ndata%=nbit;
			nbit/=10;
		}	
		for(int i=this->size-2;i>=0;i--)
		{
			nbit=1000;
			ndata=this->data[i];
			for(int j=0;j<4;j++)
			{
				str[k++]=(long)(sign*ndata)/nbit+'0';
				ndata%=nbit;
				nbit/=10;
			}
		}
	}
	str[k++]='\0';
	int alen=4*MaxSize+1;
    memset(str+k,0,alen-k);
	return;
}

istream& operator >>(istream &in,Verylong &v)
{
	char instr[4*MaxSize+1];
	in>>instr;
	v=v.str2very(instr);
    return in;
}

ostream& operator <<(ostream &out,const Verylong &v)
{
	char str[MaxSize*4+1];
	v.very2str(str);
	out<<str;
	return out;
}

Verylong Verylong::lpower(long lo) const //指数为long类型  v1^lo
{
	Verylong one=Verylong(1);
	Verylong fw=one;
	int length = sizeof(long)*8;
	if(lo==0)
		return one;
	if(*this==one)
		return one;
	else   
	{
		int i=0;
		unsigned long nbit=0x1<<(length-1);
		while(i<length)
		{
			fw=fw*fw;
			if((lo & nbit)==nbit)        //依次取yy的每一位
				fw=fw*(*this);
			i++;
			nbit>>=1;
		}
	}	
	return fw;
}

Verylong Verylong::vpower(const Verylong &v2) const  // v1^v2
{
	if(v2<Verylong(0))
	{
		cout<<"错误的参数v2";
		return INF;
	}
	Verylong one=Verylong(1),zero=Verylong(0);
	Verylong fw=one;	//fw 求值
	int i;

	if(v2==zero)
		return one;
	else   
	{
		for(i=v2.size-1;i>=0;i--)
		{
			fw=fw.lpower(10000);
			fw=fw*this->lpower(v2.data[i]);
		}
	}	
	return fw;
}

Verylong power(const Verylong &v1,const Verylong &v2) 
{
	return v1.vpower(v2);
}

Verylong Verylong::lpower(long l2,const Verylong &v3) const //指数为long类型
{
	if(v3<0)
	{
		cout<<"参数错误!"<<endl;
		return -1;
	}
	Verylong one=Verylong(1);
	Verylong fw=one;
	int length = sizeof(long)*8;
	if(l2==0)
		return one;
	if(*this==one)
		return one;
	else   
	{
		int i=0;
		unsigned long nbit=0x1<<(length-1);
		while(i<length)
		{
			fw=(fw*fw)%v3;
			if((l2 & nbit)==nbit)        //依次取yy的每一位
				fw=(fw*(*this))%v3;
			i++;
			nbit>>=1;
		}
	}
    return mod(fw,v3);
}

Verylong Verylong::vpower(const Verylong &v0,const Verylong &v3) const
{ 
	Verylong v1=mod(*this,v3);
	Verylong v2=v0;
	if(v2<0||v3<0)
	{
		cout<<"错误的参数!"<<endl;
		return INF;
	}
	Verylong fw=1;	//fw 求值
	int i;
   
	if(v2==0)
		return 1;
	else   
	{
		for(i=v2.size-1;i>=0;i--)
		{
			fw=fw.lpower(10000,v3)%v3;
			fw=(fw*v1.lpower(v2.data[i],v3))%v3;
		}
	}	
	return mod(fw,v3);
}

Verylong power(const Verylong &v1,const Verylong &v2,const Verylong &v3) //v1^v2 mod v3
{
	return v1.vpower(v2,v3);
}

Verylong Verylong::operator <<(long i)
{
	Verylong v=(*this);
	int sign=v.signal;
	if(sign==-1)
		v=-v;

	long j;
	while(i>=16)
	{
		for(j=0;j<v.size;j++)
			v.data[j]=v.data[j]<<16;
	
		j=0;
		while(v.data[j]>=10000 ||j<v.size)
		{
			v.data[j+1]+=long(v.data[j]/10000);
			v.data[j]%=10000;
			j++;
		}
		if(v.data[j]>0)
			v.size=j+1;
		else 
			v.size=j;
		i-=16;
	}

	for(j=0;j<v.size;j++)
		v.data[j]=v.data[j]<<i;
	j=0;	
	while(v.data[j]>=10000 || j<v.size)
	{
			v.data[j+1]+=long(v.data[j]/10000);
			v.data[j]%=10000;	
			j++;
	}
	if(v.data[j]>0)
		v.size=j+1;
	else 
		v.size=j;
	if(sign==-1)
		v=-v;
	return v;
}

Verylong Verylong::operator <<= (long i)  //左移
{
	*this=*this<<i;
	return *this;
}

Verylong Verylong::rshift(long i,unsigned long r[]) const //右移,返回移位结果及移出部分
{
	Verylong v=(*this);
	int sign=v.signal;
	if(sign==-1)
		v=-v;

	long r1[MaxSize]; //保存2^16进制的数
	memset(r1,0,MaxSize*sizeof(long));
	memset(r,0,MaxSize*sizeof(long));
	long j,k=1;//循环变量
	long sizel = sizeof(long)/2; //sizeof(long)

	while(i>=16)
	{
		for(j=v.size-1;j>=1;j--)
		{
			v.data[j-1]+=(v.data[j]%65536)*10000;
			v.data[j]=v.data[j]>>16;	
		}
		r1[k++]=v.data[0]%65536;
		v.data[0]=v.data[0]>>16;
	
		while(v.data[v.size-1]==0 && v.size!=1)
			v.size--;
		
		i-=16;
	}

	long i2=1;
	j=i;
	while(j>0)
	{
		i2*=2;
		j--;
	}
	for(j=v.size-1;j>=1;j--)
	{
		v.data[j-1]+=(v.data[j]%i2)*10000;
		v.data[j]=v.data[j]>>i;
	}
	r1[k++]=v.data[0]%i2;
	v.data[0]=v.data[0]>>i;	
	while(r1[k]==0)
		k--;
	long sizer=1;
    for(j=1;j<=k;)
	{
		unsigned long nbit=1;
		for(long t=0;t<sizel;t++)  //压缩
		{
			r[sizer]+=r1[j++]*nbit; //65536=2^16
			nbit*=65536;
			if(j>k)
				break;
		}
		sizer++;
	}
	r[0]=sizer-1;
	while(v.data[v.size-1]==0 && v.size!=1)
		v.size--;
	if(sign==-1)
		v=-v;
	return v;
}

Verylong Verylong::rshiftr(long i) //右移移出部分
{
	unsigned long r[MaxSize];
	rshift(i,r);
	return this->bit2very(r);
}

Verylong Verylong::operator >>(long i)
{
	unsigned long r[MaxSize];
	return rshift(i,r);
}

Verylong Verylong::operator >>=(long i) //右移
{
	*this=*this>>i;
	return *this;
}

unsigned long Verylong::toUlong()  //截断转化成无符号长整型,负数不转换
{
	if(this->signal<0)
	{
		cout<<"负数不能转换!"<<endl;
		exit(0);
	}
	unsigned long v[MaxSize];
	long k=(long)(sizeof(long)*2/lo2g10); //3.33=log(2,10)
	if(size>k)
		rshift(8*sizeof(long),v);
	else
		rshift((long)(size*4*lo2g10),v);  //将所有位移入v中
	
	return v[1];
}

void Verylong::very2bit(unsigned long lo[]) const //转化成二进制串,lo[0]为串的大小及符号
{
	rshift((long)(size*4*lo2g10),lo); //3.33=log 2 10
}
											//二进制串转化成Verylong,lo[0]为串的大小及符号
Verylong Verylong::bit2very(const unsigned long lo[]) const
{
	long i;
	long sizel=sizeof(long)*4;
	unsigned long nbit=(1<<sizel);
	Verylong v2=nbit;
	v2*=v2;
	Verylong v=0;
	for(i=lo[0];i>=1;i--)
		v=v*v2+lo[i];			 //63353=2^32,sizeof(unsigned long)=32;
	return v;
}

Verylong operator & (const Verylong &v1,const Verylong &v2)
{
	unsigned long f1[MaxSize],f2[MaxSize],f[MaxSize];
	v1.very2bit(f1);
	v2.very2bit(f2);
	memset(f,0,MaxSize*sizeof(long));
	unsigned long i;
	for(i=1;i<=f1[0]&&i<=f2[0];i++)
	{
		f[i]=f1[i] & f2[i];
	}
	f[0]=i;
	return v1.bit2very(f);
}

Verylong operator | (const Verylong &v1,const Verylong &v2)
{
	unsigned long f1[MaxSize],f2[MaxSize],f[MaxSize];
	v1.very2bit(f1);
	v2.very2bit(f2);
	memset(f,0,MaxSize*sizeof(long));
	unsigned long i;
	for(i=1;i<=f1[0]&&i<=f2[0];i++)
	{
		f[i]=f1[i] | f2[i];
	}
	while(i<=f1[0])
	{
		f[i]=f1[i];
		i++;
	}
	while(i<=f2[0])
	{
		f[i]=f2[i];
		i++;
	}
	f[0]=i;
	return v1.bit2very(f);
}

Verylong operator ^ (const Verylong &v1,const Verylong &v2)
{
	unsigned long f1[MaxSize],f2[MaxSize],f[MaxSize];
	v1.very2bit(f1);
	v2.very2bit(f2);
	memset(f,0,MaxSize*sizeof(long));
	unsigned long i;
	for(i=1;i<=f1[0]&&i<=f2[0];i++)
	{
		f[i]=f1[i] ^ f2[i];
	}
	while(i<=f1[0])
	{
		f[i]=~f1[i];
		i++;
	}
	while(i<=f2[0])
	{
		f[i]=~f2[i];
		i++;
	}
	f[0]=i;
	return v1.bit2very(f);
}

Verylong Verylong::operator ~ ()  
{
	unsigned long f1[MaxSize],f[MaxSize];
	this->very2bit(f1);
	memset(f,0,MaxSize*sizeof(long));
	unsigned long i;
	for(i=1;i<=f1[0];i++)
	{
		f[i]=~f1[i];
	}
	f[0]=i;
	return this->bit2very(f);
}

Verylong mod(const Verylong &v1,const Verylong &v2)
{
	Verylong r=v1%v2;
	if(r.getSignal()>=0)
		return r;
	else 
		return r+v2;
}

// Verylong 的辅助函数
//实现向下兼容
Verylong mod(const Verylong &v1,const long &l2) //通过隐式类型转换,l2可以为int,short,long
{
	Verylong v2=l2;
	return mod(v1,v2);
}

Verylong mod(const long &l1,const Verylong &v2)	//通过隐式类型转换,l1可以为int,short,long
{
	Verylong v1=l1;
	return mod(v1,v2);
}

Verylong power(const Verylong &v1,const long &l2) //v1^l2
{
	Verylong v2=l2;
	return power(v1,v2);
}

Verylong power(const long &l1,const Verylong &v2)	
{
	Verylong v1=l1;
	return power(v1,v2);
}

Verylong power(const Verylong &v1,const Verylong &v2,const long &l3)
{
	Verylong v3=l3;
	return power(v1,v2,v3);
}

Verylong power(const Verylong &v1,const long &l2,const Verylong &v3)//通过隐式类型转换,l1可以为int,short,long
{
	Verylong v2=l2;
	return power(v1,v2,v3);
}

Verylong power(const long &l1,const Verylong &v2,const Verylong &v3)
{
	Verylong v1=l1;
	return power(v1,v2,v3);
}

Verylong power(const long &l1,const long &l2,const Verylong &v3)
{
	Verylong v1=l1,v2=l2;
	return power(v1,v2,v3);
}

Verylong power(const long &l1,const Verylong &v2,const long &l3)
{
	Verylong v1=l1,v3=l3;
	return power(v1,v2,v3);
}

Verylong power(const Verylong &v1,const const long &l2,const long &l3)
{
	Verylong v2=l2,v3=l3;
	return power(v1,v2,v3);
}


Verylong Mod(Verylong *x,long n,const Verylong &p)	//矩阵求模,矩阵以行优先存在向量x中,n为矩阵的阶
{
	for(long i=0;i<n;i++)
		for(long j=0;j<n;j++) 
			x[i*n+j]=mod(x[i*n+j],p);
	return 1;
}


void Multi(Verylong *x,Verylong *y,long n,const Verylong &p,Verylong *t)	//矩阵的乘法,结果保存在t中
{
	Verylong *g=new Verylong[n*n];
	Mod(x,n,p);
	Mod(y,n,p);
	long i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			g[i*n+j]=0;	
			for(k=0;k<n;k++)
				g[i*n+j]+=mod(x[i*n+k]*y[k*n+j],p);
			g[i*n+j]=mod(g[i*n+j],p);
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			t[i*n+j]=mod(g[i*n+j],p);
		}
	}
	delete []g;
	return;
}

//Verylong类型的模幕
void matrixpower(Verylong *x,long n,long v2,const Verylong &pp,Verylong *fw)
{
	long i,j;
	long length=sizeof(long)*8; //最大2^14=16384
	if(v2<10000)
		length=14;    //最大2^14-1=16383
	Verylong *tw=new Verylong[n*n];	//tw 为单位矩阵
	Verylong *xx=new Verylong[n*n];	
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
				tw[i*n+j]=1;
			else
				tw[i*n+j]=0;

			xx[i*n+j]=mod(x[i*n+j],pp);
		}
	}
	for(j=length-1;j>=0;j--)
	{
		Multi(tw,tw,n,pp,tw);
		if(v2 & (1<<j))				//依次取v2的每一位
			Multi(tw,xx,n,pp,tw);	
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			fw[i*n+j]=tw[i*n+j];
	}
	return;

}
void matrixpower(Verylong *x,long n,const Verylong &v2,const Verylong &pp,Verylong *fw)
{
	long i,j;
	Verylong *tw=new Verylong[n*n];	    //tw 为单位矩阵
    Verylong *rw=new Verylong[n*n];	    //rw 为单位矩阵
	Verylong *xx=new Verylong[n*n];	
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
				rw[i*n+j]=tw[i*n+j]=1;
			else
				rw[i*n+j]=tw[i*n+j]=0;

			xx[i*n+j]=mod(x[i*n+j],pp);
		}
	}

	for(i=v2.size-1;i>=0;i--)
	{
		matrixpower(tw,3,10000,pp,tw);
		matrixpower(xx,3,v2.data[i],pp,rw);
		Multi(tw,rw,n,pp,tw);
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			fw[i*n+j]=tw[i*n+j];
	}
	return;
}


//当n>=13时，计算结果溢出
unsigned int factorial(unsigned int n)  
{  
	unsigned int p;  
	if(n==0)
		p=1;  
	else  
		p=n*factorial(n-1);  
	return p;
}

//当n>=21时，计算结果溢出
unsigned long long factorial64(unsigned int n)  
{  
	unsigned long long p;  
	if(n==0)
		p=1;  
	else  
		p=n*factorial64(n-1);  
	return p;
}

//当n>=22时，计算的结果开始出现误差
//当n>=171时，计算结果溢出
double dfactorial(unsigned int n)  
{  
	double p;  
	if(n==0)
		p=1;  
	else  
		p=n*dfactorial(n-1);
	return p;
}

Verylong Verylongfactorial(unsigned long n)  
{  
	Verylong p;  
	if(n==0)
		p=1;  
	else  
		p=Verylong(n)*Verylongfactorial(n-1);
	return p;
}

Verylong Verylongfact(unsigned long n)  
{  
	Verylong p=1;  
	if(n==0||n==1)
		return p;  
	for(int i=1;i<=n;i++) 
	{
		p=p*Verylong(i);
	}
	return p;
}

int main()
{
 //   int a=(int)2.9f;
	//int b=(int)3.1f;
	//assert(a==2 && b==3);
	//printf("----factorial测试结果----\n");
	//printf("factorial(12)=%u\n",factorial(12));
	//printf("factorial(13)=%u\n",factorial(13));
	//printf("factorial(14)=%u\n",factorial(14));
	//printf("----factorial64测试结果----\n");
	//printf("factorial64(12)=%llu\n",factorial64(12));
	//for(int i=13;i<24;i++)
	//	printf("factorial64(%d)=%llu\n",i,factorial64(i));
	//printf("----dfactorial测试结果----\n");
	//printf("dfactorial(12)=%lf\n",dfactorial(12));
	//for(int i=13;i<24;i++)
	//	printf("dfactorial(%d)=%lf\n",i,dfactorial(i));
	//printf("dfactorial(170)=%lf\n",dfactorial(170));
	//printf("dfactorial(171)=%lf\n",dfactorial(171));
	//printf("----Verylongfactorial测试结果----\n");
	//cout<<"Verylongfactorial(12)="<<Verylongfactorial(12)<<endl;
	//for(int i=13;i<50;i++)
	//	cout<<"Verylongfactorial("<<i<<")="<<Verylongfactorial(i)<<endl;
	//cout<<"Verylongfactorial(170)="<<Verylongfactorial(170)<<endl;
	//cout<<"Verylongfactorial(171)="<<Verylongfactorial(171)<<endl;
	//cout<<"Verylongfactorial(1000)="<<Verylongfactorial(1000)<<endl;
    cout<<"Verylongfactorial(206)="<<Verylongfactorial(206)<<endl;
    cout<<"Verylongfact(206)="<<Verylongfact(206)<<endl;
	//for(int i=201;i<207;i++)
	//	cout<<"Verylongfactorial("<<i<<")="<<Verylongfactorial(i)<<endl;
	//system("pause");
	return 0;
}
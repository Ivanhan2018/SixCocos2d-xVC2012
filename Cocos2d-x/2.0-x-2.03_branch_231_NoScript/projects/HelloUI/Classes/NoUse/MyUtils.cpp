#include "MyUtils.h"

// 梯形法求定积分
// 或float integral(FPf fun,float a,float b,int n)
float TxIntf(float(*fun)(float x),float a,float b,int n)
{
	float s,h,y;
	s=(fun(a)+fun(b))/2; 
	h=(b-a)/n;// 积分步长 
	for(int i=1;i<n;i++) 
		s=s+fun(a+i*h); 
	y=s*h; 
	return y;
} 


unsigned int Add(unsigned int a,unsigned int b)
{
#ifdef WIN32
		unsigned int *c = &a;
		__asm
		{
			mov eax, c; //c中存储的a的地址->eax 
			mov eax, [eax]; //a的值->eax//注意直接mov eax, [c]是错误的
          	mov ebx, b; //可以像这样直接对ebx赋值
			lea eax, [eax+ebx];
			mov a, eax; //可以直接将eax的值->a
		}
		return a;
#else
        return a+b;
#endif
}

// 将一个数字转换成字符串
string NumberTostring(int Num)
{
	char buffer[100]={0};
	sprintf(buffer,"%d",Num);
	string strBuf=buffer;

	return strBuf;
}

// 返回形如"12,34,234,4,2"的字符串
string BytesToStr(unsigned char bt[],int nSize)
{
	string str="";
	int b;
	int n=0;
	for(int i=0;i<nSize;i++)
	{
		str+=NumberTostring(bt[i]);
		str+=",";
	}
	b=str.size();
	if(b>0&&str[b-1]==',')
		str.erase(str.begin()+b-1);
	return str;
}

/*
	access确定文件的访问权限
	0 检查文件是否存在
	1 检查文件是否可运行
	2 检查文件是否可以定访问
	4 检查是否可以读访问
	6 检查是否可以读/写访问
	当允许做指定的访问时，返回0否则返回-1
	mode=0，1，2，4，6，ret=0，-1
*/
bool file_exists(const char *filename)
{ 
   return (access(filename,0)==0); 
}

const char * GetResWithID(int ID)
{
	static const char *strArr[]={"未知资源","金钱","粮食","木材","皮料","铁","红宝石","黄宝石","绿宝石","黑铁"};
	if(ID>0&&ID<10)
	{
		return strArr[ID];
	}
	return strArr[0];
}

int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    iconv_t cd;

    const char *temp = inbuf;

    const char **pin = &temp;

    char **pout = &outbuf;

    memset(outbuf,0,outlen);

    cd = iconv_open(to_charset,from_charset);

    if(cd==0) 
		return -1;

    if(iconv(cd,pin,&inlen,pout,&outlen)==-1) 
		return -1;

    iconv_close(cd);

    return 0;

}

/*UTF8?GB2312*/
std::string U2G(const char *inbuf)
{
	size_t inlen = strlen(inbuf);

	char * outbuf = new char[inlen * 2 + 2];

	std::string strRet;

	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}

	delete [] outbuf;

	return strRet;
}

/*GB2312?UTF8*/
std::string G2U(const char *inbuf)
{
	size_t inlen = strlen(inbuf);

	char * outbuf = new char[inlen * 2 + 2];

	std::string strRet;

	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}

	delete [] outbuf;

	return strRet;
}
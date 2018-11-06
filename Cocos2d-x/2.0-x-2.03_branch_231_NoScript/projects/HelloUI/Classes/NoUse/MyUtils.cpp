#include "MyUtils.h"

// ���η��󶨻���
// ��float integral(FPf fun,float a,float b,int n)
float TxIntf(float(*fun)(float x),float a,float b,int n)
{
	float s,h,y;
	s=(fun(a)+fun(b))/2; 
	h=(b-a)/n;// ���ֲ��� 
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
			mov eax, c; //c�д洢��a�ĵ�ַ->eax 
			mov eax, [eax]; //a��ֵ->eax//ע��ֱ��mov eax, [c]�Ǵ����
          	mov ebx, b; //����������ֱ�Ӷ�ebx��ֵ
			lea eax, [eax+ebx];
			mov a, eax; //����ֱ�ӽ�eax��ֵ->a
		}
		return a;
#else
        return a+b;
#endif
}

// ��һ������ת�����ַ���
string NumberTostring(int Num)
{
	char buffer[100]={0};
	sprintf(buffer,"%d",Num);
	string strBuf=buffer;

	return strBuf;
}

// ��������"12,34,234,4,2"���ַ���
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
	accessȷ���ļ��ķ���Ȩ��
	0 ����ļ��Ƿ����
	1 ����ļ��Ƿ������
	2 ����ļ��Ƿ���Զ�����
	4 ����Ƿ���Զ�����
	6 ����Ƿ���Զ�/д����
	��������ָ���ķ���ʱ������0���򷵻�-1
	mode=0��1��2��4��6��ret=0��-1
*/
bool file_exists(const char *filename)
{ 
   return (access(filename,0)==0); 
}

const char * GetResWithID(int ID)
{
	static const char *strArr[]={"δ֪��Դ","��Ǯ","��ʳ","ľ��","Ƥ��","��","�챦ʯ","�Ʊ�ʯ","�̱�ʯ","����"};
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
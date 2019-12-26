#include <stdio.h> 
#include <iconv.h>
#include <string.h>
#include <string>
using namespace std;

// 编码转换
int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
iconv_t cd;
int rc;
char **pin = &inbuf;
char **pout = &outbuf;

cd = iconv_open(to_charset,from_charset);
if (cd==0) return -1;
if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
iconv_close(cd);
return 0;
}

// utf8码转为GB2312码
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

// GB2312码转为utf8
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}

// utf8转为gbk
string u2a(const char *inbuf)
{
int inlen=strlen(inbuf);
string strRet;
strRet.resize(inlen*2+2);
if(code_convert("utf-8","gbk",const_cast<char *>(inbuf),inlen,&strRet[0],strRet.size()))
return inbuf;
return strRet;
}

// gbk转为utf8
string a2u(const char *inbuf)
{
int inlen=strlen(inbuf);
string strRet;
strRet.resize(inlen*2+2);
if(code_convert("gbk","utf-8",const_cast<char *>(inbuf),inlen,&strRet[0],strRet.size()))
return inbuf;
return strRet;
}

#define OUTLEN 255
void test_u2g_g2u()
{
char *in1 = "我们aA";
char *in2 = "\xe6\x88\x91\xe4\xbb\xac\x61\x41";
printf("in1=%s,strlen(in1)=%d\n",in1,strlen(in1));
printf("in2=%s,strlen(in2)=%d\n",in2,strlen(in2));
for (int i=0;i<strlen(in1);i++) printf("%d ",in1[i]+0);
printf("\n");
for (int i=0;i<strlen(in1);i++) printf("%x ",in1[i]+0);
printf("\n");

char out[OUTLEN];
char out1[OUTLEN];
int rec = u2g(in1,strlen(in1),out,OUTLEN);
printf("rec=%d,strlen(out)=%d\n",rec,strlen(out));
for (int i=0;i<strlen(out);i++) printf("%d ",out[i]+0);
printf("\n");
for (int i=0;i<strlen(out);i++) printf("%x ",out[i]+0);
printf("\n");
int rec1 = g2u(out,strlen(out),out1,OUTLEN);
printf("rec1=%d,strlen(out1)=%d\n",rec1,strlen(out1));
for (int i=0;i<strlen(out1);i++) printf("%d ",out1[i]+0);
printf("\n");
for (int i=0;i<strlen(out1);i++) printf("%x ",out1[i]+0);
printf("\n");

string s1=u2a(in1);
string s2=a2u(s1.c_str());
printf("s1=%s,s1.size()=%d,%d\n",s1.c_str(),s1.size(),strlen(s1.c_str()));
printf("s2=%s,s2.size()=%d,%d\n",s2.c_str(),s2.size(),strlen(s2.c_str()));
}

/* 内码
Windows下：
aA
97 65
61 41
我们aA
-50 -46 -61 -57 97 65
ffffffce ffffffd2 ffffffc3 ffffffc7 61 41
汉字：我们aA
十六进制数：CE D2 C3 C7 61 41
Private Sub Command1_Click()
MsgBox Hex$(AscW("我")) '6211//windows大字符集
MsgBox Hex$(Asc("我")) 'ced2//国标的
End Sub
http://www.programfan.com/club/showpost.asp?id=24101
http://blog.csdn.net/black_dragon/archive/2005/05/25/380638.aspx 
Linux下：
root@dthero_cn:/home/yiyou/gopath/cpptest# ./testASC
我们aA
-26 -120 -111 -28 -69 -84 97 65 10 
ffffffe6 ffffff88 ffffff91 ffffffe4 ffffffbb ffffffac 61 41 a 
root@dthero_cn:/home/yiyou/gopath/cpptest# ./testASC
我
-26 -120 -111 10 
ffffffe6 ffffff88 ffffff91 a 
*/
int main()
{
test_u2g_g2u();
char s[80]={0};
int i=0,n=0;
//while (1){
fgets(s,100,stdin);
n=strlen(s);
//if (n==0) break;
for (i=0;i<n;i++) printf("%d ",s[i]+0);
printf("\n");
for (i=0;i<n;i++) printf("%x ",s[i]+0);
printf("\n");
//} 
//getchar();
return 0;
}
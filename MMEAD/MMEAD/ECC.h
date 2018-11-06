/****************************************************
Name：Elliptic Curve算法封装(ECC + ECDSA + ECDH)
Desc：EC生成及加解密、ECDSA数字签名及校验、ECDH密钥协商
Auth：Cool.Cat@2013-02-22
****************************************************
EC曲线采用国密2号标准：SM2-256(bits)
http://www.oscca.gov.cn/News/201012/News_1197.htm
****************************************************
【ECC流程】
****************************************************
初始化：
	1、生成椭圆曲线Ep(a,b)
	2、取Ep(a,b)一点作为基点G=point(x,y)
	3、取私钥k(k<n)，n是G的阶，并生成公钥K=kG
加密：Ep(a,b)、K、G
	1、将明文编码映射到Ep(a,b)上点M
	2、产生一个随机数因子r(r<n)
	3、计算点M1=M+rK，M2=rG
解密：k、M1、M2
	1、M1-kM2=M+rK-k(rG)=M+rkG-krG=M
	2、M解码得到明文
****************************************************
注意：m^n为m的n次方
	1、并不是所有的椭圆曲线都适合加密
	2、适用公式：y^2=x^3+ax+b(mod p)
	3、a、b、p可以确定EC=Ep(a,b)
	4、K、G都在Ep(a,b)上
	5、4a^3+27b^2≠0(mod p)
	6、明文M有可能无法映射到ECC上，所以不建议如此加密
	7、变形:
		加密(PriKey=私钥、PubKey=公钥、PubKey=PriKey*G)
		a、产生一个随机数因子r(r<n-1)
		b、R=r*PubKey，R点的x坐标=x(R)，如果x(R)=0，返回a
		c、计算点M1=明文M*x(R)
		d、计算点M2=r*G
		e、密文=(M1,M2)
		解密
		a、计算点R=PriKey*M2=PriKey*(r*G)=r*(PriKey*G)=r*PubKey=R
		c、计算明文M=M1*(x(R)^-1)=明文M*x(R)*(1/(x(R)))=M
****************************************************
安全：
	在加解密过程中，攻击者Z虽然可以窃取：
	①：Ep(a,b)、K、G
	②：M1、M2
	但是却无法通过①求得私钥k，也无法通过②求得因子r
	┌───────┐             ┌───────┐
	│       X      │		Z	   │       Y      │
	├───────┤      │     ├───────┤
	│   Ep(a,b)    │Ep(a,b),K,G  │   M1=M+rK    │
	│   K=kG       │──────>│   M2=rG      │
	├───────┤<──────│              │
	│   M=M1-M2    │    M1,M2    │              │
	└───────┘             └───────┘
****************************************************
【ECDSA流程】
****************************************************
签名：
	1、生成椭圆曲线Ep(a,b)
	2、取Ep(a,b)一点作为基点G=point(x,y)
	3、取私钥k(k<n)，n是G的阶，并生成公钥K=kG
	4、产生一个随机数因子r(r<n)，计算R=rG
	5、计算明文M的Hash=SHA(M,R.x,R.y)，M'=M(mod p)
	6、计算S=(Hash+M'*k)/r mod p
	7、如果R或S为0，则重新从step4开始
	8、对明文M签名，得到签名M(R,S)
验证：
	1、计算明文M的Hash=SHA(M,R.x,R.y)，M'=M(mod p)
	2、计算R'=(Hash*G+M'*K)/S
	3、验证R'=R
****************************************************
【ECDH流程】
****************************************************

****************************************************
参考：
	http://www.dkrypt.com/home/ecc
	http://www.imperialviolet.org/2010/12/04/ecc.html
	http://www.johannes-bauer.com/compsci/ecc/
	http://www.allopopo.cn/?p=306
	http://www.cnblogs.com/604608/archive/2011/09/13/2174890.html
	http://bbs.pediy.com/showthread.php?t=35745
	http://www.pediy.com/kssd/pediy06/pediy6014.htm
参数：
	http://www.shamus.ie/index.php?page=Shamus-Standard-Curves
****************************************************/
#pragma once
#include "EntityBase.h"

extern MMUtility *utility;

// {p,a,b,n,x,y}
class KEY_CONTEXT_ECC:public KEY_CONTEXT{
public:
	// G点
	ECn G;
	ECn W;

	// G点坐标
	Big x;
	Big y;

	Big p;
	Big a;
	Big b;

	// G点的阶
	Big n;

	int ep;
};

class ENCRYPT_CONTEXT_ECC:public ENCRYPT_CONTEXT{
public:
	// m1段
	ECn m1;
	// m2段
	ECn m2;
	// m段长度(bytes)
	unsigned int GetMLength(ECn m)
	{
		Big t=0;
		m.get(t);
		return bits(t)/8;
	}

	// x的补
	Big v;
};

class ECC:public EntityBase {
public:
	ECC()
	{
		time_t seed;
		time(&seed);
		irand((long)seed);
	}
	~ECC()
	{
		printf("~ECC\n");
	};
public:
	// 生成EC=Ep(a,b)，并通过x/y选取G点
	ERROR_INFO GenKeyToData(unsigned int keyLen,KEY_CONTEXT *key);
	// 输出密钥对上下文信息
	void Print(KEY_CONTEXT *key);
	// 通过密钥对加密数据
	ERROR_INFO EncodeDataByKey(KEY_CONTEXT *key,char *src,int slen,ENCRYPT_CONTEXT *enc);
	// 通过密钥对解密数据
	ERROR_INFO DecodeDataByKey(KEY_CONTEXT *key,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase=256);
	// 签名
	ERROR_INFO Signature(KEY_CONTEXT *key,char *src,int slen,char *dst,int *dlen,unsigned int signLen=160,unsigned int OutIoBase=16);
	// 校验
	ERROR_INFO Verify(KEY_CONTEXT *key,char *src,int slen,unsigned int InIoBase=16);
public:
	// 4a^3+27b^2≠0(mod p)，确保EC上不包含奇异点
	ERROR_INFO CheckPowmod(Big n,Big p);
	// (y^2)%p=(x^3+ax+b)%p
	ERROR_INFO CheckEqual(KEY_CONTEXT *key,Big x,Big y);
};
/****************************************************
Name：ElGamal算法封装
Desc：密钥生成、加解密、签名
Auth：Cool.Cat@2013-02-27
****************************************************
安全：
	1、ElGamal的安全性主要依赖于p和g
	2、由公钥y计算私钥x相当于求解离散对数，比较困难
缺点：
	3、密文是明文的2倍
****************************************************
初始化：
	1、生成大素数p，范围：512<=p<=1024(且p-1至少包含一个大素数因子q)，p是64的倍数
	2、取2个随机数g,x，满足1<g<p-1、1<x<p-1
	3、计算y=g^x(mod p)，则公钥=(y,g,p)，私钥=x
	4、选择明文M
****************************************************
【加解密流程】
****************************************************
加密：
	1、选择随机数k，且k/p-1互质
	2、计算a=g^k(mod p)
	3、计算b=y^kM(mod p)
	4、得到密文(a,b)
解密：
	1、计算M=b/a^x(mod p)
****************************************************
【签名流程】
****************************************************
签名：
	1、选择随机数k，且k/p-1互质
	2、计算r=g^k(mod p)
	3、计算k/p-1模逆k'=inverse(k,p-1)
	4、计算：
		s=((hash-xr)*ik)(mod p-1)			或
		s=((r-k*hash)*ik)(mod p-1)
	5、如果s<0，则加上p-1
	6、得到签名(r,s)，丢弃k
	7、如果s==0，重新生成
验证：
	1、检查：0<r<p，且0<s<p-1
	2、验证：
		(y^r*r^s) mod p = (g^hash) mod p	或
		(y^s*r^hash) mod p = (g^r) mod p
参考：
	http://en.wikipedia.org/wiki/ElGamal_signature_scheme
****************************************************/
#pragma once
#include "EntityBase.h"

// 小素数测试
//#define	TEST_SHORT_PRIME

#ifdef TEST_SHORT_PRIME
#define	P		"CE892335578D3F"
#define PK		"264D8D82C7AAB8"
#define	G		"473FE7D24CB6A6"
#define K		"889BADA83DDB7F"
#endif

extern MMUtility *utility;

class KEY_CONTEXT_ELGAMAL:public KEY_CONTEXT{
public:
	// 素数
	Big p;
	Big g;
};

class ElGamal:public EntityBase {
public:
	ElGamal()
	{
		time_t seed;
		time(&seed);
		irand((long)seed);
	};

	~ElGamal()
	{
		printf("~ElGamal\n");
	}
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
};
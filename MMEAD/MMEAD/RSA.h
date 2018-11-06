/****************************************************
Name：RSA算法封装(RSA + DSA)
Desc：RSA密钥对生成、加解密、签名校验。
Auth：Cool.Cat@2013-02-18
****************************************************/
#pragma once
#include "EntityBase.h"

extern MMUtility *utility;

class KEY_CONTEXT_RSA:public KEY_CONTEXT{
public:
	Big p;
	Big q;
	Big n;
	Big t;
};

class RSA:public EntityBase {
public:
	RSA()
	{
		Init(0);
	}
	// ----------------------------------------------
	// 【指定较小的公钥因子可以提高密钥对的生成速度，
	// 但是容易遭受攻击，所以还是建议公钥因子用大数】
	// Cool.Cat@2013-02-22
	// ----------------------------------------------
	RSA(unsigned int factor)
	{
		Init(factor);
	}
	~RSA()
	{
		printf("~RSA\n");
	};
private:
	void Init(unsigned int factor)
	{
		srand((unsigned int)time(0));
		m_factor = factor;
	}
public:
	// 生成密钥对
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
	void SetFactor(unsigned int factor){m_factor = factor;}
private:
	unsigned int m_factor;
};
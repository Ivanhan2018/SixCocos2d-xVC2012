/****************************************************
Name��ElGamal�㷨��װ
Desc����Կ���ɡ��ӽ��ܡ�ǩ��
Auth��Cool.Cat@2013-02-27
****************************************************
��ȫ��
	1��ElGamal�İ�ȫ����Ҫ������p��g
	2���ɹ�Կy����˽Կx�൱�������ɢ�������Ƚ�����
ȱ�㣺
	3�����������ĵ�2��
****************************************************
��ʼ����
	1�����ɴ�����p����Χ��512<=p<=1024(��p-1���ٰ���һ������������q)��p��64�ı���
	2��ȡ2�������g,x������1<g<p-1��1<x<p-1
	3������y=g^x(mod p)����Կ=(y,g,p)��˽Կ=x
	4��ѡ������M
****************************************************
���ӽ������̡�
****************************************************
���ܣ�
	1��ѡ�������k����k/p-1����
	2������a=g^k(mod p)
	3������b=y^kM(mod p)
	4���õ�����(a,b)
���ܣ�
	1������M=b/a^x(mod p)
****************************************************
��ǩ�����̡�
****************************************************
ǩ����
	1��ѡ�������k����k/p-1����
	2������r=g^k(mod p)
	3������k/p-1ģ��k'=inverse(k,p-1)
	4�����㣺
		s=((hash-xr)*ik)(mod p-1)			��
		s=((r-k*hash)*ik)(mod p-1)
	5�����s<0�������p-1
	6���õ�ǩ��(r,s)������k
	7�����s==0����������
��֤��
	1����飺0<r<p����0<s<p-1
	2����֤��
		(y^r*r^s) mod p = (g^hash) mod p	��
		(y^s*r^hash) mod p = (g^r) mod p
�ο���
	http://en.wikipedia.org/wiki/ElGamal_signature_scheme
****************************************************/
#pragma once
#include "EntityBase.h"

// С��������
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
	// ����
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
	// ����EC=Ep(a,b)����ͨ��x/yѡȡG��
	ERROR_INFO GenKeyToData(unsigned int keyLen,KEY_CONTEXT *key);
	// �����Կ����������Ϣ
	void Print(KEY_CONTEXT *key);
	// ͨ����Կ�Լ�������
	ERROR_INFO EncodeDataByKey(KEY_CONTEXT *key,char *src,int slen,ENCRYPT_CONTEXT *enc);
	// ͨ����Կ�Խ�������
	ERROR_INFO DecodeDataByKey(KEY_CONTEXT *key,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase=256);
	// ǩ��
	ERROR_INFO Signature(KEY_CONTEXT *key,char *src,int slen,char *dst,int *dlen,unsigned int signLen=160,unsigned int OutIoBase=16);
	// У��
	ERROR_INFO Verify(KEY_CONTEXT *key,char *src,int slen,unsigned int InIoBase=16);
};
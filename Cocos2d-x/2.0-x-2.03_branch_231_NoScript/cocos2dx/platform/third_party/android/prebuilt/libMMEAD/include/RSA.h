/****************************************************
Name��RSA�㷨��װ(RSA + DSA)
Desc��RSA��Կ�����ɡ��ӽ��ܡ�ǩ��У�顣
Auth��Cool.Cat@2013-02-18
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
	// ��ָ����С�Ĺ�Կ���ӿ��������Կ�Ե������ٶȣ�
	// �����������ܹ��������Ի��ǽ��鹫Կ�����ô�����
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
	// ������Կ��
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
public:
	void SetFactor(unsigned int factor){m_factor = factor;}
private:
	unsigned int m_factor;
};
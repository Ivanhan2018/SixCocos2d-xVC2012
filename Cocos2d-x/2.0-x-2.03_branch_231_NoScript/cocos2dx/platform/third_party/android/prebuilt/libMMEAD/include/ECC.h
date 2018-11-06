/****************************************************
Name��Elliptic Curve�㷨��װ(ECC + ECDSA + ECDH)
Desc��EC���ɼ��ӽ��ܡ�ECDSA����ǩ����У�顢ECDH��ԿЭ��
Auth��Cool.Cat@2013-02-22
****************************************************
EC���߲��ù���2�ű�׼��SM2-256(bits)
http://www.oscca.gov.cn/News/201012/News_1197.htm
****************************************************
��ECC���̡�
****************************************************
��ʼ����
	1��������Բ����Ep(a,b)
	2��ȡEp(a,b)һ����Ϊ����G=point(x,y)
	3��ȡ˽Կk(k<n)��n��G�Ľף������ɹ�ԿK=kG
���ܣ�Ep(a,b)��K��G
	1�������ı���ӳ�䵽Ep(a,b)�ϵ�M
	2������һ�����������r(r<n)
	3�������M1=M+rK��M2=rG
���ܣ�k��M1��M2
	1��M1-kM2=M+rK-k(rG)=M+rkG-krG=M
	2��M����õ�����
****************************************************
ע�⣺m^nΪm��n�η�
	1�����������е���Բ���߶��ʺϼ���
	2�����ù�ʽ��y^2=x^3+ax+b(mod p)
	3��a��b��p����ȷ��EC=Ep(a,b)
	4��K��G����Ep(a,b)��
	5��4a^3+27b^2��0(mod p)
	6������M�п����޷�ӳ�䵽ECC�ϣ����Բ�������˼���
	7������:
		����(PriKey=˽Կ��PubKey=��Կ��PubKey=PriKey*G)
		a������һ�����������r(r<n-1)
		b��R=r*PubKey��R���x����=x(R)�����x(R)=0������a
		c�������M1=����M*x(R)
		d�������M2=r*G
		e������=(M1,M2)
		����
		a�������R=PriKey*M2=PriKey*(r*G)=r*(PriKey*G)=r*PubKey=R
		c����������M=M1*(x(R)^-1)=����M*x(R)*(1/(x(R)))=M
****************************************************
��ȫ��
	�ڼӽ��ܹ����У�������Z��Ȼ������ȡ��
	�٣�Ep(a,b)��K��G
	�ڣ�M1��M2
	����ȴ�޷�ͨ�������˽Կk��Ҳ�޷�ͨ�����������r
	������������������             ������������������
	��       X      ��		Z	   ��       Y      ��
	������������������      ��     ������������������
	��   Ep(a,b)    ��Ep(a,b),K,G  ��   M1=M+rK    ��
	��   K=kG       ��������������>��   M2=rG      ��
	������������������<��������������              ��
	��   M=M1-M2    ��    M1,M2    ��              ��
	������������������             ������������������
****************************************************
��ECDSA���̡�
****************************************************
ǩ����
	1��������Բ����Ep(a,b)
	2��ȡEp(a,b)һ����Ϊ����G=point(x,y)
	3��ȡ˽Կk(k<n)��n��G�Ľף������ɹ�ԿK=kG
	4������һ�����������r(r<n)������R=rG
	5����������M��Hash=SHA(M,R.x,R.y)��M'=M(mod p)
	6������S=(Hash+M'*k)/r mod p
	7�����R��SΪ0�������´�step4��ʼ
	8��������Mǩ�����õ�ǩ��M(R,S)
��֤��
	1����������M��Hash=SHA(M,R.x,R.y)��M'=M(mod p)
	2������R'=(Hash*G+M'*K)/S
	3����֤R'=R
****************************************************
��ECDH���̡�
****************************************************

****************************************************
�ο���
	http://www.dkrypt.com/home/ecc
	http://www.imperialviolet.org/2010/12/04/ecc.html
	http://www.johannes-bauer.com/compsci/ecc/
	http://www.allopopo.cn/?p=306
	http://www.cnblogs.com/604608/archive/2011/09/13/2174890.html
	http://bbs.pediy.com/showthread.php?t=35745
	http://www.pediy.com/kssd/pediy06/pediy6014.htm
������
	http://www.shamus.ie/index.php?page=Shamus-Standard-Curves
****************************************************/
#pragma once
#include "EntityBase.h"

extern MMUtility *utility;

// {p,a,b,n,x,y}
class KEY_CONTEXT_ECC:public KEY_CONTEXT{
public:
	// G��
	ECn G;
	ECn W;

	// G������
	Big x;
	Big y;

	Big p;
	Big a;
	Big b;

	// G��Ľ�
	Big n;

	int ep;
};

class ENCRYPT_CONTEXT_ECC:public ENCRYPT_CONTEXT{
public:
	// m1��
	ECn m1;
	// m2��
	ECn m2;
	// m�γ���(bytes)
	unsigned int GetMLength(ECn m)
	{
		Big t=0;
		m.get(t);
		return bits(t)/8;
	}

	// x�Ĳ�
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
public:
	// 4a^3+27b^2��0(mod p)��ȷ��EC�ϲ����������
	ERROR_INFO CheckPowmod(Big n,Big p);
	// (y^2)%p=(x^3+ax+b)%p
	ERROR_INFO CheckEqual(KEY_CONTEXT *key,Big x,Big y);
};
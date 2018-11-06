/*********************************************************
Name���ӽ���ʵ�����
Desc����Կ����ͨ�ó���ײ�
Warn���ײ�Miracl��������̰߳�ȫ���ڶ��߳��е�����Կ���棬
��������mr_init_threading()��ʼ����mr_end_threading()����
Auth��Cool.Cat@2013-02-22
*********************************************************/
#pragma once
#include "MMEAD_Config.h"

#pragma pack(push)
#pragma pack(1)
// ��Կ��������
class KEY_CONTEXT{
public:
	KEY_CONTEXT(){keyLength=0;}
	virtual ~KEY_CONTEXT(){};
	// ��Կ
	Big PubKey;
	// ˽Կ
	Big PriKey;
	// ��Կ�Գ���(bytes)
	unsigned int keyLength;
	// ǩ��r
	Big r;
	// ǩ��s
	Big s;
};

// ����������
//			ECC			ElGamal/RSA
// ---+-----------+-------------------+-
//	����	m1			C
//			m2			-
// ---+-----------+-------------------+-
//	����	m1			M
//			m2			-
// ---+-----------+-------------------+-
class ENCRYPT_CONTEXT{
public:
	ENCRYPT_CONTEXT(){m1=m2=0;}
	virtual ~ENCRYPT_CONTEXT(){};

	Big m1;
	Big m2;

	unsigned int GetMLength(Big m){return bits(m)/8;}

#ifdef PRINT_ENCRYPT_CONTEXT
	void Print()
	{
		cout<<"m1.len["<<GetMLength(m1)<<"]="<<m1<<endl;
		cout<<"m2.len["<<GetMLength(m2)<<"]="<<m2<<endl;
	}
#endif
};

#pragma pack(pop)

class EntityBase {
public:
	EntityBase()
	{
		mir = new Miracl(100,0);
	};
	virtual ~EntityBase()
	{
		// Miraclʵ��ָ����Զ������������ֶ��ͷ�~
		//RP(mir);
		printf("~EntityBase\n");
	};

public:
	// ������Կ��
	virtual ERROR_INFO GenKeyToData(unsigned int keyLen,KEY_CONTEXT *key)=0;
	// �����Կ����������Ϣ
	virtual void Print(KEY_CONTEXT *key)=0;
	// ͨ����Կ�Լ������ݣ�����ǰ��slen���ܳ���keyLength��������Ҫ�ֶμ���
	virtual ERROR_INFO EncodeDataByKey(KEY_CONTEXT *key,char *src,int slen,ENCRYPT_CONTEXT *enc)=0;
	// ͨ����Կ�Խ������ݣ����ܺ��dlen���ܳ���keyLength��������Ҫ�ֶν���
	virtual ERROR_INFO DecodeDataByKey(KEY_CONTEXT *key,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase=256)=0;

	// ǩ��
	virtual ERROR_INFO Signature(KEY_CONTEXT *key,char *src,int slen,char *dst,int *dlen,unsigned int signLen=160,unsigned int OutIoBase=16)=0;
	// У��
	virtual ERROR_INFO Verify(KEY_CONTEXT *key,char *src,int slen,unsigned int InIoBase=16)=0;
public:
	// ȡmiraclʵ��ָ��
	miracl *GetMIP() {return &(*mir);};
	// ȡ��Կ�Եĳ���
	virtual unsigned int GetKeyLength(KEY_CONTEXT *key){return key->keyLength;};
	// ���ɴ�����p=2*r*pd+1=11 mod 12
	Big StrongPrime(unsigned int n,unsigned int seed1,unsigned int seed2)
	{
		Big p,pd,pl,ph;
		int r,r1,r2;
		irand(seed1);
		pd=rand(2*n/3,2);
		pd=nextprime(pd);
		ph=pow((Big)2,n-1)/pd;
		pl=pow((Big)2,n-2)/pd;
		ph-=pl;
		irand(seed2);
		ph=rand(ph);
		ph+=pl;
		r1=pd%12;
		r2=ph%12;
		r=0;
		while ((r1*(r2+r))%12!=5){r++;}
		ph+=r;
		do
		{
			p=2*ph*pd+1;
			ph+=12;
		} while (!prime(p));
		return p;
	}
	// SHA(160/256/384/512bit)
	ERROR_INFO Hash(Big *hash,const char*src,unsigned int slen,unsigned int bits=160)
	{
		switch (bits)
		{
			case 160:sha.Hash160(hash,src,slen);break;
			case 256:sha.Hash256(hash,src,slen);break;
			case 384:sha.Hash384(hash,src,slen);break;
			case 512:sha.Hash512(hash,src,slen);break;
			default:return ERROR_BITS_INVALID;
		}
		return ERROR_NONE;
	}
	// ͨ���������ȡ������Ϣ
	string GetErrorDesc(ERROR_INFO errCode)
	{
		switch (errCode)
		{
		case ERROR_NONE:return /*���쳣*/XorStr<0x31,7,0xFA912BB0>("\xFF\xEC\xE1\xD8\x86\x95"+0xFA912BB0).s;
		case ERROR_KEYLENGTH_INVALID:return /*Ҫ������Կ�Գ��ȳ�����Χ*/XorStr<0x9B,25,0x1878C2D4>("\x49\x36\x54\x64\x2C\x69\x62\x7E\x77\x1B\x13\x72\x14\x0C\x1F\x62\x18\x00\x1E\x58\x18\x06\x7F\x15"+0x1878C2D4).s;
		case ERROR_KEY_CONTEXT_NOTEXISTS:return /*��Կ�������Ĳ�����*/XorStr<0x84,19,0x4B96C827>("\x47\x59\x52\x38\x3E\x5D\x43\x44\x43\x4F\x40\x4B\x22\x2A\x26\x75\x40\x4F"+0x4B96C827).s;
		case ERROR_IOBASE_INVALID:return /*�ӽ��ܽ���ģʽֻ��Ϊ10/16/256*/XorStr<0xB4,30,0x6E950D0F>("\x08\x66\x0B\x55\x7B\x65\x07\x43\x6A\x7B\x7A\x1C\x0A\x7C\x14\x78\x00\x19\x08\x6D\xF9\xF9\xE5\xFA\xFA\xE2\xFC\xFA\xE6"+0x6E950D0F).s;
		case ERROR_SOURCELENGTH_TOO_MUCH:return /*����ǰԴ�����ȳ���n*/XorStr<0xFE,20,0x86EBB2A9>("\x42\x2C\xC3\xDD\xC5\xB3\xD0\xB1\xB2\xA9\xBB\xAD\xBC\xC3\xBF\xA1\xB7\xF2\x7E"+0x86EBB2A9).s;
		case ERROR_DESTLENGTH_TOO_MUCH:return /*���ܺ�Ŀ�괮���ȳ���n*/XorStr<0xD9,22,0x658B69D2>("\x64\x38\x18\x00\x67\x2D\x1B\x5F\x50\x08\x57\x4A\x56\x42\x51\x20\x5A\x46\x52\x11\x83"+0x658B69D2).s;
		case ERROR_NOT_RELATIVELY_PRIME:return /*RSA��e/t������*/XorStr<0x4F,15,0x8351D9D9>("\x1D\x03\x10\xF1\xE9\x31\x7A\x22\xE5\xE3\xE2\xFF\x8D\x96"+0x8351D9D9).s;

		case ERROR_NOT_PRIME:return /*ECC��p��Ϊ����*/XorStr<0x1D,15,0x627544B1>("\x58\x5D\x5C\x83\x9B\x52\x91\x9F\xEB\x8C\xEC\xF0\xE3\xD7"+0x627544B1).s;
		case ERROR_NOT_IN_EC:return /*ECC��point(x,y)����EC��*/XorStr<0xAC,24,0x25B09BE8>("\xE9\xEE\xED\x0C\x0A\xC1\xDD\xDA\xDA\xC1\x9E\xCF\x94\xC0\x93\x09\x07\x69\x64\xFA\x83\x08\x0D"+0x25B09BE8).s;
		case ERROR_NOT_ORDER_Q:return /*ECC��point(x,y)����q�Ľ�*/XorStr<0x12,25,0x20B13F84>("\x57\x50\x57\xB6\xAC\x67\x77\x70\x74\x6F\x34\x65\x32\x66\x09\x93\x99\xE9\xE3\x54\x93\xE3\x95\xFE"+0x20B13F84).s;
		case ERROR_SINGULARITY_EXISTS:return /*ECC��EC�ϰ��������*/XorStr<0x5A,20,0x09CA48FA>("\x1F\x18\x1F\xFE\xE4\x1A\x23\xA8\xAD\xD3\x98\xDF\xCA\xA1\x8E\xBB\x86\xDE\x8F"+0x09CA48FA).s;
		}
		return /*δ֪����*/XorStr<0xCD,9,0x43B2DF1C>("\x03\x7A\x19\x7A\x65\x3F\x1D\x27"+0x43B2DF1C).s;
	}
private:
	Miracl *mir;
	SHA sha;
};
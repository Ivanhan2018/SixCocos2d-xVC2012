#include "MMEAD.h"

MMUtility *utility = 0;

MMEAD::MMEAD()
{
	utility = new MMUtility();
	crc32 = new CRC32();
	md5 = new MD5();
	sha = new SHA();
	rsa = new RSA();
	ecc = new ECC();
	elgamal = new ElGamal();
	bf = new CBlowFish();
	tdea = new TDEA();
}

MMEAD::~MMEAD()
{
	RP(crc32);
	RP(md5);
	RP(sha);
	RP(rsa);
	RP(ecc);
	RP(elgamal);
	RP(utility);
	RP(bf);
	RP(tdea);
}

// 密钥对生成相关
void MMEAD::InitKeyByBlowFish(unsigned char *pKey,int keyLen)
{
	bf->Initialize(pKey,keyLen);
}

// 密钥对生成相关
void MMEAD::InitKeyByDES(unsigned char *pKey,int keyLen)
{
	tdea->InitKeySingle(pKey,keyLen);
	tdea->InitKeyDouble(pKey,keyLen);
	tdea->InitKeyTriple(pKey,keyLen);
}

unsigned long MMEAD::GetOutputLength(unsigned long len)
{
	return bf->GetOutputLength(len);
}

ERROR_INFO MMEAD::GenKeyToData(KEY_CONTEXT_RSA *pKey,unsigned int keyLen)
{
	return rsa->GenKeyToData(keyLen,pKey);
}

ERROR_INFO MMEAD::GenKeyToData(KEY_CONTEXT_ECC *pKey,unsigned int keyLen)
{
	return ecc->GenKeyToData(keyLen,pKey);
}

ERROR_INFO MMEAD::GenKeyToData(KEY_CONTEXT_ELGAMAL *pKey,unsigned int keyLen)
{
	return elgamal->GenKeyToData(keyLen,pKey);
}

void MMEAD::Print(KEY_CONTEXT_RSA *pKey)
{
	rsa->Print(pKey);
}

void MMEAD::Print(KEY_CONTEXT_ECC *pKey)
{
	ecc->Print(pKey);
}

void MMEAD::Print(KEY_CONTEXT_ELGAMAL *pKey)
{
	elgamal->Print(pKey);
}

// 加解密
// RSA
ERROR_INFO MMEAD::EncodeDataByKey(KEY_CONTEXT_RSA *pKey,char *src,int slen,ENCRYPT_CONTEXT *enc)
{
	return rsa->EncodeDataByKey(pKey,src,slen,enc);
}

// ECC
ERROR_INFO MMEAD::EncodeDataByKey(KEY_CONTEXT_ECC *pKey,char *src,int slen,ENCRYPT_CONTEXT *enc)
{
	return ecc->EncodeDataByKey(pKey,src,slen,enc);
}

// ELGAMAL
ERROR_INFO MMEAD::EncodeDataByKey(KEY_CONTEXT_ELGAMAL *pKey,char *src,int slen,ENCRYPT_CONTEXT *enc)
{
	return elgamal->EncodeDataByKey(pKey,src,slen,enc);
}

// BlowFish
ERROR_INFO MMEAD::EncodeDataByKey(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len<1)
		return ERROR_SOURCELENGTH_TOO_MUCH;

	bf->Encode(src,dst,len);

	return ERROR_NONE;
}

// DES Single
ERROR_INFO MMEAD::EncodeDataByDESSingle(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len%8)
		return ERROR_DESTLENGTH_NOT_BIT8;

	tdea->DES_Single(src,dst,len,true);
	return ERROR_NONE;
}

// DES Double
ERROR_INFO MMEAD::EncodeDataByDESDouble(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len%8)
		return ERROR_DESTLENGTH_NOT_BIT8;

	tdea->DES_Double(src,dst,len,true);
	return ERROR_NONE;
}

// DES Triple
ERROR_INFO MMEAD::EncodeDataByDESTriple(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len%8)
		return ERROR_DESTLENGTH_NOT_BIT8;

	tdea->DES_Triple(src,dst,len,true);
	return ERROR_NONE;
}

// 解密
// RSA
ERROR_INFO MMEAD::DecodeDataByKey(KEY_CONTEXT_RSA *pKey,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase)
{
	return rsa->DecodeDataByKey(pKey,enc,dst,dlen,OutIoBase);
}

// ECC
ERROR_INFO MMEAD::DecodeDataByKey(KEY_CONTEXT_ECC *pKey,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase)
{
	return ecc->DecodeDataByKey(pKey,enc,dst,dlen,OutIoBase);
}

// ELGAMAL
ERROR_INFO MMEAD::DecodeDataByKey(KEY_CONTEXT_ELGAMAL *pKey,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase)
{
	return elgamal->DecodeDataByKey(pKey,enc,dst,dlen,OutIoBase);
}

// BlowFish
ERROR_INFO MMEAD::DecodeDataByKey(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len<1)
		return ERROR_SOURCELENGTH_TOO_MUCH;

	bf->Decode(src,dst,len);

	return ERROR_NONE;
}

// DES Single
ERROR_INFO MMEAD::DecodeDataByDESSingle(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len%8)
		return ERROR_DESTLENGTH_NOT_BIT8;

	tdea->DES_Single(src,dst,len,false);
	return ERROR_NONE;
}

// DES Double
ERROR_INFO MMEAD::DecodeDataByDESDouble(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len%8)
		return ERROR_DESTLENGTH_NOT_BIT8;

	tdea->DES_Double(src,dst,len,false);
	return ERROR_NONE;
}

// DES Triple
ERROR_INFO MMEAD::DecodeDataByDESTriple(unsigned char *src,unsigned char *dst,int len)
{
	if (!src)
		return ERROR_SOURCE_INVALID;
	if (!dst)
		return ERROR_DEST_INVALID;
	if (len%8)
		return ERROR_DESTLENGTH_NOT_BIT8;

	tdea->DES_Triple(src,dst,len,false);
	return ERROR_NONE;
}

// 签名校验
ERROR_INFO MMEAD::Signature(KEY_CONTEXT_RSA *pKey,char *src,int slen,char *dst,int *dlen,unsigned int signLen,unsigned int OutIoBase)
{
	return rsa->Signature(pKey,src,slen,dst,dlen,signLen,OutIoBase);
}

ERROR_INFO MMEAD::Signature(KEY_CONTEXT_ECC *pKey,char *src,int slen,char *dst,int *dlen,unsigned int signLen,unsigned int OutIoBase)
{
	return ecc->Signature(pKey,src,slen,dst,dlen,signLen,OutIoBase);
}

ERROR_INFO MMEAD::Signature(KEY_CONTEXT_ELGAMAL *pKey,char *src,int slen,char *dst,int *dlen,unsigned int signLen,unsigned int OutIoBase)
{
	return elgamal->Signature(pKey,src,slen,dst,dlen,signLen,OutIoBase);
}

ERROR_INFO MMEAD::Verify(KEY_CONTEXT_RSA *pKey,char *src,int slen,unsigned int InIoBase)
{
	return rsa->Verify(pKey,src,slen,InIoBase);
}

ERROR_INFO MMEAD::Verify(KEY_CONTEXT_ECC *pKey,char *src,int slen,unsigned int InIoBase)
{
	return ecc->Verify(pKey,src,slen,InIoBase);
}

ERROR_INFO MMEAD::Verify(KEY_CONTEXT_ELGAMAL *pKey,char *src,int slen,unsigned int InIoBase)
{
	return elgamal->Verify(pKey,src,slen,InIoBase);
}

// Hash/对称及其他相关
unsigned int MMEAD::CRC_Stream(unsigned char *buffer, unsigned int size,unsigned int crc)
{
	if (!buffer || !size)
		return 0;

	return crc32->CRC_Stream(buffer,size,crc);
}

unsigned int MMEAD::CRC_File(const char *file)
{
	if (!file)
		return 0;

	return crc32->CRC_File(file);
}

ERROR_INFO MMEAD::HashByMD5(char *pSrc,unsigned sLen,char *pDst,bool upper,unsigned power,char *slot)
{
	if (!pSrc)
		return ERROR_SOURCE_INVALID;

	if (!pDst)
		return ERROR_DEST_INVALID;

	int p = power;
	if (p==0)
		p = 1;

	char *md5source = new char[33];
	memset(md5source,0,sizeof(md5source));

	// 先md5一次
	MakeMD5(pSrc,md5source,upper,1);

	// src + slot
	int slen2 = strlen(slot);
	if (slen2>0)
	{
		char *tmp = new char[32 + slen2 + 1];
		memset(tmp,0,sizeof(tmp));

		// 保存第一次MD5后的密文
		strcat(tmp,md5source);

		// 如果有slot则合并进来再加密一次
		strcat(tmp,slot);
		memset(md5source,0,sizeof(md5source));
		MakeMD5(tmp,md5source,upper,1);

		RP_ARRAY(tmp);
	}

	//p *= p;

	p--;

	if (p>0)
		MakeMD5(md5source,md5source,upper,p);

	memcpy(pDst,md5source,32);
	pDst[32] = 0;

	RP_ARRAY(md5source);

	return ERROR_NONE;
}

void MMEAD::MakeMD5(char *src,char *dst,bool upper,int repeat)
{
	int slen = strlen(src)+1;

	if (slen<33)
		slen = 33;

	char *md5source = new char[slen];
	memcpy(md5source,src,slen);

	for (int j=0;j<repeat;j++)
	{
		MD5 md5;
		md5.update((unsigned char *)md5source, strlen(md5source));
		md5.finalize();
		md5.hex_digest(md5source,upper);
	}

	memcpy(dst,md5source,32);
	dst[32] = 0;

	RP_ARRAY(md5source);
}

ERROR_INFO MMEAD::HashBySHA(Big *hash,const char *src,int slen,int bit)
{
	if (bit!=160 && bit!=256 && bit!=384 && bit!=512)
		return ERROR_HASH_BIT_OVERFLOW;

	switch (bit)
	{
	case 160:
		{
			sha->Hash160(hash,src,slen);
			break;
		}
	case 256:
		{
			sha->Hash256(hash,src,slen);
			break;
		}
	case 384:
		{
			sha->Hash384(hash,src,slen);
			break;
		}
	case 512:
		{
			sha->Hash512(hash,src,slen);
			break;
		}
	}

	return ERROR_NONE;
}
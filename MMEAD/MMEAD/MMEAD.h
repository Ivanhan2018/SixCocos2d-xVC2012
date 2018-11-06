/***********************************************
Name：MMEAD.h
Desc：My Micro Encryption And Decryption
	  MD5/SHA/RSA/ECC/ELGamal
Auth：Cool.Cat@2013-09-10
***********************************************/
#pragma once
#include "MMEAD_Config.h"
#include "RSA.h"
#include "ECC.h"
#include "ElGamal.h"
#include "TDEA.h"

class MMEAD {
public:
	MMEAD();
	virtual ~MMEAD();

	// 密钥对生成相关
public:
	ERROR_INFO GenKeyToData(KEY_CONTEXT_RSA *pKey,unsigned int keyLen=MIN_KEYLEN_RSA);
	ERROR_INFO GenKeyToData(KEY_CONTEXT_ECC *pKey,unsigned int keyLen=256);
	ERROR_INFO GenKeyToData(KEY_CONTEXT_ELGAMAL *pKey,unsigned int keyLen=MIN_KEYLEN_ELGAMAL);

	// BlowFish
	void InitKeyByBlowFish(unsigned char *pKey,int keyLen);
	unsigned long GetOutputLength(unsigned long len);

	// Des
	void InitKeyByDES(unsigned char *pKey,int keyLen);

	void Print(KEY_CONTEXT_RSA *pKey);
	void Print(KEY_CONTEXT_ECC *pKey);
	void Print(KEY_CONTEXT_ELGAMAL *pKey);

	// 加解密
public:
	// RSA
	ERROR_INFO EncodeDataByKey(KEY_CONTEXT_RSA *pKey,char *src,int slen,ENCRYPT_CONTEXT *enc);
	// ECC
	ERROR_INFO EncodeDataByKey(KEY_CONTEXT_ECC *pKey,char *src,int slen,ENCRYPT_CONTEXT *enc);
	// ELGAMAL
	ERROR_INFO EncodeDataByKey(KEY_CONTEXT_ELGAMAL *pKey,char *src,int slen,ENCRYPT_CONTEXT *enc);

	// BlowFish
	ERROR_INFO EncodeDataByKey(unsigned char *src,unsigned char *dst,int len);

	// DES Single
	ERROR_INFO EncodeDataByDESSingle(unsigned char *src,unsigned char *dst,int len);
	// DES Single
	ERROR_INFO EncodeDataByDESDouble(unsigned char *src,unsigned char *dst,int len);
	// DES Single
	ERROR_INFO EncodeDataByDESTriple(unsigned char *src,unsigned char *dst,int len);

	// RSA
	ERROR_INFO DecodeDataByKey(KEY_CONTEXT_RSA *pKey,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase=256);
	// ECC
	ERROR_INFO DecodeDataByKey(KEY_CONTEXT_ECC *pKey,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase=256);
	// ELGAMAL
	ERROR_INFO DecodeDataByKey(KEY_CONTEXT_ELGAMAL *pKey,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase=256);

	// BlowFish
	ERROR_INFO DecodeDataByKey(unsigned char *src,unsigned char *dst,int len);

	// DES Single
	ERROR_INFO DecodeDataByDESSingle(unsigned char *src,unsigned char *dst,int len);
	// DES Single
	ERROR_INFO DecodeDataByDESDouble(unsigned char *src,unsigned char *dst,int len);
	// DES Single
	ERROR_INFO DecodeDataByDESTriple(unsigned char *src,unsigned char *dst,int len);

	// 签名校验
public:
	ERROR_INFO Signature(KEY_CONTEXT_RSA *pKey,char *src,int slen,char *dst,int *dlen,unsigned int signLen=160,unsigned int OutIoBase=16);
	ERROR_INFO Signature(KEY_CONTEXT_ECC *pKey,char *src,int slen,char *dst,int *dlen,unsigned int signLen=160,unsigned int OutIoBase=16);
	ERROR_INFO Signature(KEY_CONTEXT_ELGAMAL *pKey,char *src,int slen,char *dst,int *dlen,unsigned int signLen=160,unsigned int OutIoBase=16);

	ERROR_INFO Verify(KEY_CONTEXT_RSA *pKey,char *src,int slen,unsigned int InIoBase=16);
	ERROR_INFO Verify(KEY_CONTEXT_ECC *pKey,char *src,int slen,unsigned int InIoBase=16);
	ERROR_INFO Verify(KEY_CONTEXT_ELGAMAL *pKey,char *src,int slen,unsigned int InIoBase=16);

	// Hash/对称及其他相关
public:
	// CRC32
	unsigned int CRC_Stream(unsigned char *buffer, unsigned int size,unsigned int crc=0xffffffff);
	unsigned int CRC_File(const char *file);
	// MD5
	ERROR_INFO HashByMD5(char *pSrc,unsigned sLen,char *pDst,bool upper=true,unsigned power=1,char *slot="");
	// SHA
	ERROR_INFO HashBySHA(Big *hash,const char *src,int slen,int bit=256);

private:
	void MakeMD5(char *src,char *dst,bool upper=true,int repeat=1);

private:
	CRC32 *crc32;
	MD5 *md5;
	SHA *sha;
	CBlowFish *bf;
	TDEA *tdea;
	RSA *rsa;
	ECC *ecc;
	ElGamal *elgamal;
};
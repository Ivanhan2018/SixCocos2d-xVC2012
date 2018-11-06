/***********************************************
Name£ºMMEAD.h
Desc£ºMy Micro Encryption And Decryption
	  MD5/SHA/RSA/ECC/ELGamal
Auth£ºCool.Cat@2013-09-10
***********************************************/
#pragma once
#include "MMEAD_Config.h"
#include "RSA.h"
#include "ECC.h"
#include "ElGamal.h"

class MMEAD {
public:
	MMEAD();
	virtual ~MMEAD();
public:
	// CRC32
	unsigned int CRC_Stream(unsigned char *buffer, unsigned int size,unsigned int crc=0xffffffff);
	unsigned int CRC_File(const char *file);

	// MD5
	//ERROR_INFO EncryptByMD5(char *pSrc,unsigned sLen,char *pDst,bool upper=true,unsigned power=1,char *slot="");
	ERROR_INFO HashByMD5(char *pSrc,unsigned sLen,char *pDst,bool upper=true,unsigned power=1,char *slot="");

	// SHA
	void EncryptBySHA();

	// RSA
	void EncryptByRSA();

	// ECC
	void EncryptByECC();

	// ElGamal
	void EncryptByElGamal();
private:
	void MakeMD5(char *src,char *dst,bool upper=true,int repeat=1);
private:
	CRC32 *crc32;
	MD5 *md5;
	SHA *sha;
	RSA *rsa;
	ECC *ecc;
	ElGamal *elgamal;
};
#ifndef ENCRYPT_HEAD_FILE
#define ENCRYPT_HEAD_FILE
#pragma once
#include "Define.h"


//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
#else
#endif
//MD5 ������
class CMD5Encrypt
{
	//��������
private:
	//���캯��
	CMD5Encrypt() {}

	//���ܺ���
public:
	//��������
	static void EncryptData(unsigned char * pszSrcData, char szMD5Result[33]);
};

//////////////////////////////////////////////////////////////////////////

//��������
class CXOREncrypt
{
	//��������
private:
	//���캯��
	CXOREncrypt() {}

	//���ܺ���
public:
	//��������
	static WORD EncryptData(unsigned char * pszSrcData, unsigned char* pszEncrypData, WORD wSize);
	//�⿪����
	static WORD CrevasseData(unsigned char * pszEncrypData, unsigned char* pszSrcData, WORD wSize);
};

//////////////////////////////////////////////////////////////////////////

#endif
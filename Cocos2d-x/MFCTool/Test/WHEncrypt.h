#ifndef WH_ENCRYPT_HEAD_FILE
#define WH_ENCRYPT_HEAD_FILE

#pragma once

//#include "ServiceCoreHead.h"
#define LEN_MD5						33									//��������
//����ά��
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
//////////////////////////////////////////////////////////////////////////////////

//�궨��
#define XOR_TIMES					8									//���ܱ���
#define MAX_SOURCE_LEN				64									//��󳤶�
#define MAX_ENCRYPT_LEN				(MAX_SOURCE_LEN*XOR_TIMES)			//��󳤶�

//////////////////////////////////////////////////////////////////////////////////

//�������
//class SERVICE_CORE_CLASS CWHEncrypt
class CWHEncrypt
{
	//��������
public:
	//���캯��
	CWHEncrypt();
	//��������
	virtual ~CWHEncrypt();

	//���ܺ���
public:
	//��������
	static bool MD5Encrypt(LPCTSTR pszSourceData, TCHAR szMD5Result[LEN_MD5]);

	//���ܺ���
public:
	//��������
	static bool XorEncrypt(LPCTSTR pszSourceData, LPTSTR pszEncrypData, WORD wMaxCount);
	//�⿪����
	static bool XorCrevasse(LPCTSTR pszEncrypData, LPTSTR pszSourceData, WORD wMaxCount);

	//���ܺ���
public:
	//��������
	static bool MapEncrypt(LPCTSTR pszSourceData, LPTSTR pszEncrypData, WORD wMaxCount);
	//�⿪����
	static bool MapCrevasse(LPCTSTR pszEncrypData, LPTSTR pszSourceData, WORD wMaxCount);
};

//////////////////////////////////////////////////////////////////////////////////

#endif

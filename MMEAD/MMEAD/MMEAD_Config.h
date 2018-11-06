#pragma once
#if !defined(WIN32)
#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "big.h"
#include "ecn.h"
#include "CRC32.h"
#include "MD5.h"
#include "SHA.h"
#include "blowfish.h"
#include "MMUtility.h"

/******************************
		��Կ�Գ���
******************************/
#define MIN_KEYLEN_ELGAMAL	512
#define MAX_KEYLEN_ELGAMAL	2048

#define MIN_KEYLEN_RSA		1024
#define MAX_KEYLEN_RSA		2048

#define RP(x)				if (x)\
							{\
								delete x;\
								x = 0;\
							}

#define RP_ARRAY(x)			if (x)\
							{\
								delete [] x;\
								x = 0;\
							}

typedef enum tagErrorInfo {
	// ���쳣
	ERROR_NONE								=	0,

	// Դ��������
	ERROR_SOURCE_INVALID,
	// Ŀ�괮������
	ERROR_DEST_INVALID,

	// Hashλ�����ȳ�����Χ
	ERROR_HASH_BIT_OVERFLOW,

	// Ҫ������Կ�Գ��ȳ�����Χ
	// ElGamal��512<=keyLen<=1024
	// RSA��	128<=keyLen<=2048
	// ECC��	keyLen=160/192/256
	ERROR_KEYLENGTH_INVALID					=	100,
	// ��Կ�������Ĳ�����
	ERROR_KEY_CONTEXT_NOTEXISTS,
	// ���������Ĳ�����
	ERROR_ENC_CONTEXT_NOTEXISTS,
	// �ӽ��ܽ��Ʋ�Ϊ10��16��256
	ERROR_IOBASE_INVALID,
	// ����ǰԴ�����ȳ���n
	ERROR_SOURCELENGTH_TOO_MUCH,
	// ���ܺ�Ŀ�괮���ȳ���n
	ERROR_DESTLENGTH_TOO_MUCH,
	// �ӽ���Ŀ�괮���Ȳ�Ϊ8�ı���
	ERROR_DESTLENGTH_NOT_BIT8,

	// RSA��e/t������
	ERROR_NOT_RELATIVELY_PRIME				=	200,
	// DSA��ǩ��r��һ��
	ERROR_DSA_VERIFY_NOMATCH,

	// ECC��p��Ϊ����
	ERROR_NOT_PRIME							=	300,
	// ECC��point(x,y)����EC��
	ERROR_NOT_IN_EC,
	// ECC��point(x,y)����q�Ľ�
	ERROR_NOT_ORDER_Q,
	// ECC��EC�ϰ��������
	ERROR_SINGULARITY_EXISTS,
	// ECC������ʧ��
	ERROR_ENCRYPT_FAILED,
	// ECC������ʧ��
	ERROR_DECRYPT_FAILED,
	// ECC��y^2!=x^3+ax+b(mod p)
	ERROR_NOT_INVALID_XY,

	// ECDSA��ǩ��rΪ0
	ERROR_SIGN_R_ISZERO						=	400,
	// ECDSA��ǩ��sΪ0
	ERROR_SIGN_S_ISZERO,
	// ECDSA��У��r/s/p������
	ERROR_VERIFY_RSP_NORELATIVELYPRIME,
	// ECCDSA/ELGAMAL��VR��һ��
	ERROR_VERIFY_VR_NOMATCH,

	// SHA��λ����Ϊ256/384/512
	ERROR_BITS_INVALID						=	500,

	// ElGamal������p��Χ����[512,1024]��
	ERROR_EL_BITS_P_INVALID					=	600
	
}ERROR_INFO;
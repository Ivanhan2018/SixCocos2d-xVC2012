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
		密钥对常量
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
	// 无异常
	ERROR_NONE								=	0,

	// 源串不存在
	ERROR_SOURCE_INVALID,
	// 目标串不存在
	ERROR_DEST_INVALID,

	// Hash位数长度超出范围
	ERROR_HASH_BIT_OVERFLOW,

	// 要生成密钥对长度超出范围
	// ElGamal：512<=keyLen<=1024
	// RSA：	128<=keyLen<=2048
	// ECC：	keyLen=160/192/256
	ERROR_KEYLENGTH_INVALID					=	100,
	// 密钥对上下文不存在
	ERROR_KEY_CONTEXT_NOTEXISTS,
	// 加密上下文不存在
	ERROR_ENC_CONTEXT_NOTEXISTS,
	// 加解密进制不为10、16、256
	ERROR_IOBASE_INVALID,
	// 加密前源串长度超过n
	ERROR_SOURCELENGTH_TOO_MUCH,
	// 解密后目标串长度超过n
	ERROR_DESTLENGTH_TOO_MUCH,
	// 加解密目标串长度不为8的倍数
	ERROR_DESTLENGTH_NOT_BIT8,

	// RSA：e/t不互质
	ERROR_NOT_RELATIVELY_PRIME				=	200,
	// DSA：签名r不一致
	ERROR_DSA_VERIFY_NOMATCH,

	// ECC：p不为素数
	ERROR_NOT_PRIME							=	300,
	// ECC：point(x,y)不在EC上
	ERROR_NOT_IN_EC,
	// ECC：point(x,y)不是q的阶
	ERROR_NOT_ORDER_Q,
	// ECC：EC上包含奇异点
	ERROR_SINGULARITY_EXISTS,
	// ECC：加密失败
	ERROR_ENCRYPT_FAILED,
	// ECC：解密失败
	ERROR_DECRYPT_FAILED,
	// ECC：y^2!=x^3+ax+b(mod p)
	ERROR_NOT_INVALID_XY,

	// ECDSA：签名r为0
	ERROR_SIGN_R_ISZERO						=	400,
	// ECDSA：签名s为0
	ERROR_SIGN_S_ISZERO,
	// ECDSA：校验r/s/p不互质
	ERROR_VERIFY_RSP_NORELATIVELYPRIME,
	// ECCDSA/ELGAMAL：VR不一致
	ERROR_VERIFY_VR_NOMATCH,

	// SHA：位数不为256/384/512
	ERROR_BITS_INVALID						=	500,

	// ElGamal：素数p范围不在[512,1024]间
	ERROR_EL_BITS_P_INVALID					=	600
	
}ERROR_INFO;
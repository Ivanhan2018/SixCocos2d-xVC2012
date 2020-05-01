// MD5.CC - source code for the C++/object oriented translation and 
//          modification of MD5.

// Translation and modification (c) 1995 by Mordechai T. Abzug 

// This translation/ modification is provided "as is," without express or 
// implied warranty of any kind.

// The translator/ modifier does not claim (1) that MD5 will do what you think 
// it does; (2) that this translation/ modification is accurate; or (3) that 
// this software is "merchantible."  (Language for this disclaimer partially 
// copied from the disclaimer below).

/* based on:

   MD5.H - header file for MD5C.C
   MDDRIVER.C - test driver for MD2, MD4 and MD5

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.

*/
#pragma once
//#include "MMEAD_Config.h"
#include <stdio.h>
//#include <fstream.h>
//#include <iostream.h>

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

// MD5
ERROR_INFO HashByMD5(char *pSrc,unsigned sLen,char *pDst,bool upper=true,unsigned power=1,char *slot="");

void MakeMD5(char *src,char *dst,bool upper=true,int repeat=1);

class MD5 {

public:
// methods for controlled operation:
  MD5              ();  // simple initializer
  void  update     (unsigned char *input, unsigned int input_length);
  void  update     (FILE *file);
  void  finalize   ();

// constructors for special circumstances.  All these constructors finalize
// the MD5 context.
  MD5              (unsigned char *string); // digest string, finalize
  MD5              (FILE *file);            // digest file, close, finalize

// methods to acquire finalized result
  unsigned char    *raw_digest ();  // digest as a 16-byte binary array
  char *            hex_digest ();  // digest as a 33-byte ascii-hex string
  char *			hex_digest (char buffer[33],bool upper=true); //same as above, passing buffer



private:

// first, some types:
  typedef unsigned       int uint4; // assumes integer is 4 words long
  typedef unsigned short int uint2; // assumes short integer is 2 words long
  typedef unsigned      char uint1; // assumes char is 1 word long

// next, the private data:
  uint4 state[4];
  uint4 count[2];     // number of *bits*, mod 2^64
  uint1 buffer[64];   // input buffer
  uint1 digest[16];
  uint1 finalized;

// last, the private methods, mostly static:
  void init             ();               // called by all constructors
  void transform        (uint1 *buffer);  // does the real update work.  Note 
                                          // that length is implied to be 64.

  static void encode    (uint1 *dest, uint4 *src, uint4 length);
  static void decode    (uint4 *dest, uint1 *src, uint4 length);
  static void memcpy    (uint1 *dest, uint1 *src, uint4 length);
  static void memset    (uint1 *start, uint1 val, uint4 length);

  static inline uint4  rotate_left (uint4 x, uint4 n);
  static inline uint4  F           (uint4 x, uint4 y, uint4 z);
  static inline uint4  G           (uint4 x, uint4 y, uint4 z);
  static inline uint4  H           (uint4 x, uint4 y, uint4 z);
  static inline uint4  I           (uint4 x, uint4 y, uint4 z);
  static inline void   FF  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
			    uint4 s, uint4 ac);
  static inline void   GG  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
			    uint4 s, uint4 ac);
  static inline void   HH  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
			    uint4 s, uint4 ac);
  static inline void   II  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
			    uint4 s, uint4 ac);

};
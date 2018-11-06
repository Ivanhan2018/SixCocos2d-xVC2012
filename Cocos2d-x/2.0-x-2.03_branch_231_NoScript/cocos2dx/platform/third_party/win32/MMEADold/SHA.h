/****************************************************
Name：SHA1/SHA2算法封装(160/256/384/512bit)
Desc：支持160、256、384、512bit
Auth：Cool.Cat@2013-02-27
****************************************************/
#pragma once
#include "MMEAD_Config.h"

class SHA{
public:
	SHA(){}
	~SHA(){}
public:
	void Hash160(Big *hash,const char *src,int slen);
	void Hash256(Big *hash,const char *src,int slen);
	void Hash384(Big *hash,const char *src,int slen);
	void Hash512(Big *hash,const char *src,int slen);
};
/****************************************************
Name：CRC32算法封装
Desc：冗余校验
Auth：Cool.Cat@2013-10-07
****************************************************/
#pragma once
#include "MMEAD_Config.h"

#define BUFSIZE		1024*4

class CRC32
{
public:
	CRC32();
	~CRC32();

	unsigned int CRC_Stream(unsigned char *buffer, unsigned int size,unsigned int crc=0xffffffff);
	unsigned int CRC_File(const char *file);
private:
	void MakeTable();
private:
	unsigned int crc_table[256];
};
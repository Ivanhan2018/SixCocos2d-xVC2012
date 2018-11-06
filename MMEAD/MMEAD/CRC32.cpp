#include "CRC32.h"

CRC32::CRC32()
{
	MakeTable();
}

CRC32::~CRC32()
{
}

/* 
**��ʼ��crc��,����32λ��С��crc�� 
**Ҳ����ֱ�Ӷ����crc��,ֱ�Ӳ��, 
**���ܹ���256��,�����ۻ�,�����ɵıȽϷ���. 
*/  
void CRC32::MakeTable()
{
	unsigned int c;
	unsigned int i, j;

	for (i=0;i<256;i++)
	{
		c = (unsigned int)i;
		for (j=0;j<8;j++)
		{
			if (c&1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[i] = c;
	}
}

unsigned int CRC32::CRC_Stream(unsigned char *buffer, unsigned int size,unsigned int crc)
{
	for (unsigned int i=0;i<size;i++)
		crc = (crc>>8)^crc_table[(crc&0xff)^buffer[i]];
	return ~crc;
}

unsigned int CRC32::CRC_File(const char *file)
{
	int readSize = 0;
	unsigned int crc = 0xffffffff;
	unsigned char buf[BUFSIZE] = {0};
	FILE *pf = fopen(file,"rb");
	if (!pf)
		return 0;

	while ((readSize=fread(buf,1,BUFSIZE,pf))>0)
	{
		crc = ~CRC_Stream(buf,readSize,crc);
	}

	crc = ~crc;

	fclose(pf);
	return crc;
}
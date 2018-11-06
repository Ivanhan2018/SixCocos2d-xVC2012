/***********************************************
Name：SIX_FileSystem.h
Desc：压缩/解压、加密/解密、文件读写
Auth：Cool.Cat@2013-05-03
***********************************************/
#pragma once
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#include <string>
#include <MMEAD.h>
#include <SIX_EntityMgr.h>

using namespace std;

USING_NS_CC;

class SIX_FileSystem:public SIX_EntityMgr,public TSingleton<SIX_FileSystem>
{
public:
	SIX_FileSystem();
	virtual ~SIX_FileSystem();
	virtual int ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet){return 0;}
	virtual int Run(){return 0;}
	virtual int Release(){return 0;}
public:
	bool CreateFolder(const char *folder);
	bool IsPathExists(const char *path="");

	bool ReadFromFile(char *pData,const char *file);
	bool WriteToFile(char *pData,const char *file);

	bool ZipFile(const char *pSrcFile,char *pDstFile);
	bool UnZipFile(const char *pSrcFile,char *pDstFile);

	bool Encrypt(const char *pSrc,int slen,char *pDst,int *dlen);
	bool Decrypt(const char *pSrc,int slen,char *pDst,int *dlen);

	bool EncryptFile(const char *pSrcFile,char *pDstFile);
	bool DecryptFile(const char *pSrcFile,char *pDstFile);

	MMEAD *GetMicroEncryptAndDecrypt(){return &(*pMMEAD);}
private:
	MMEAD *pMMEAD;
};
#include "SIX_FileSystem.h"

SIX_FileSystem::SIX_FileSystem()
{
	pMMEAD = new MMEAD();
}

SIX_FileSystem::~SIX_FileSystem()
{
	CC_SAFE_DELETE(pMMEAD);
}

bool SIX_FileSystem::CreateFolder(const char *folder)
{
	char msg[256]={0};

	if (IsPathExists(folder))
	{
		sprintf(msg,"CreateFolder.IsPathExists[%s].true",folder);
		SIXLog("msg=%s",msg);
		CCMessageBox(msg,0);
		return true;
	}

	sprintf(msg,"A.CreateFolder.folder[%s]",folder);
	SIXLog("msg=%s",msg);
	CCMessageBox(msg,0);

	string dataFolder = CCFileUtils::sharedFileUtils()->getWriteablePath();

	sprintf(msg,"B.CreateFolder.dataFolder[%s]",dataFolder.c_str());
	SIXLog("msg=%s",msg);
	CCMessageBox(msg,0);

	if (dataFolder=="" || !dataFolder.length())
		return true;

	dataFolder += folder;

	FILE *fp = fopen(dataFolder.c_str(),"w");

	sprintf(msg,"C.CreateFolder.dataFolder[%s].fp[0x%08X]",dataFolder.c_str(),fp);
	SIXLog("msg=%s",msg);
	CCMessageBox(msg,0);

	if(!fp)
		return false;
	fclose(fp);
	return true;
}

// 检查文件/目录是否已存在
bool SIX_FileSystem::IsPathExists(const char *path)
{
	string dataFolder = CCFileUtils::sharedFileUtils()->getWriteablePath();
	if (dataFolder=="" || !dataFolder.length())
		return false;

	dataFolder += path;

	return (access(dataFolder.c_str(),0)!=-1)?true:false;
}

bool SIX_FileSystem::LoadDataFromFile(char *pData,const char *file)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::SaveDataToFile(char *pData,const char *file)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::ZipFile(const char *pSrcFile,char *pDstFile)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::UnZipFile(const char *pSrcFile,char *pDstFile)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	// 检查目录是否已存在
	string dataFolder = CCFileUtils::sharedFileUtils()->getWriteablePath();
	if (dataFolder=="" || !dataFolder.length())
		if (!CreateFolder(dataFolder.c_str()))
			return false;

	return true;
#endif
}

bool SIX_FileSystem::Encrypt(const char *pSrc,int slen,char *pDst,int *dlen)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::Decrypt(const char *pSrc,int slen,char *pDst,int *dlen)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::EncryptFile(const char *pSrcFile,char *pDstFile)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::DecryptFile(const char *pSrcFile,char *pDstFile)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}
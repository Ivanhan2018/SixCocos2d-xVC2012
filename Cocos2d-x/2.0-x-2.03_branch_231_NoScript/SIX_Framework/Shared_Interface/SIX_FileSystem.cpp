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
	if (IsPathExists(folder))
		return true;

	string dataFolder = CCFileUtils::sharedFileUtils()->getWriteablePath();

	if (dataFolder=="" || !dataFolder.length())
		return true;

	dataFolder += folder;

#ifdef WIN32
	wstring ufolder(SIX_Utility::GetInstance()->Utf8ToUnicode(dataFolder.c_str()).c_str());
	BOOL retv = CreateDirectory(ufolder.c_str(),0);
	if (!retv/* && GetLastError()!=ERROR_ALREADY_EXISTS*/)
		return false;
#elif (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	int retv = mkdir(dataFolder.c_str(),S_IRWXU|S_IRWXG|S_IRWXO);
	if (retv/* && errno!=EEXIST*/)
		return false;
#endif

	return true;
}

// 检查文件/目录是否已存在
bool SIX_FileSystem::IsPathExists(const char *path)
{
	string dataFolder = CCFileUtils::sharedFileUtils()->getWriteablePath();
	if (dataFolder=="" || !dataFolder.length())
		return false;

	dataFolder += path;
	int retv = access(dataFolder.c_str(),0);
	//SIXLog("dataFolder[%s].retv[%d]",dataFolder.c_str(),retv);
	return (retv!=-1)?true:false;
}

bool SIX_FileSystem::ReadFromFile(char *pData,const char *file)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	return true;
#endif
}

bool SIX_FileSystem::WriteToFile(char *pData,const char *file)
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
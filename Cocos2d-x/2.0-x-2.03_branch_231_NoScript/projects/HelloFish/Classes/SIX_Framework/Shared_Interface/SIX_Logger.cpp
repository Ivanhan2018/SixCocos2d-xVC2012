#include <SIX_Logger.h>

SIX_Logger::SIX_Logger()
{
	bInited = false;
	mutex = new SIX_Mutex();

	buf = new char[1024*4];
	memset(buf,0,sizeof(buf));
}

SIX_Logger::~SIX_Logger()
{
	if (mLogFile.is_open())
	{
		mLogFile.close();
		mLogFile.clear();
	}

	CC_SAFE_DELETE(buf);
	CC_SAFE_DELETE(mutex);
}

void SIX_Logger::SetLogName(char *name)
{
	if (bInited)
		return;

	wchar_t tmp_path[1024]={0};
	memset(tmp_path,0,sizeof(tmp_path));

#ifdef WIN32
	wstring ufolder(SIX_Utility::GetInstance()->Utf8ToUnicode(SIX_Utility::GetInstance()->GetAppBasePath("Log")).c_str());
	CreateDirectory(ufolder.c_str(),0);

	SIX_Utility::GetInstance()->GetLocalTime(&st);

	wsprintf(tmp_path,L"%s%04d_%02d_%02d_%s.log",
		ufolder.c_str(),
		(int)st.wYear,
		(int)st.wMonth,
		(int)st.wDay,
		SIX_Utility::GetInstance()->Utf8ToUnicode(name).c_str()
		);

	SIX_Lock lock(mutex);
	{
		if (!mLogFile.is_open())
		{
			mLogFile.open(SIX_Utility::GetInstance()->UnicodeToAnsi(tmp_path).c_str(),std::ios_base::out | std::ios_base::app);
		}
	};

	bInited = true;
#endif
}

void SIX_Logger::WriteToFile(char *szBuff,...)
{
	if (!bInited)
		return;

	SIX_Lock lock(mutex);
	{
		va_list ap;

		memset(buf,0,sizeof(buf));
		va_start(ap, szBuff);
		vsprintf(buf,szBuff, ap);
		va_end(ap);

		SIX_Utility::GetInstance()->GetLocalTime(&st);

		char timeFormat[32]={0};
		memset(timeFormat,0,sizeof(timeFormat));
#ifdef WIN32
		sprintf_s(timeFormat,31,/*[%02d-%02d %02d:%02d:%02d %03d] */XorStr<0x7A,33,0x686F1950>("\x21\x5E\x4C\x4F\x1A\x52\xA5\xB1\xB0\xE7\xA4\xA0\xB6\xB5\xEC\xB3\xAF\xBB\xBE\xE9\xB4\xAA\xA0\xA3\xF6\xB3\xB1\xA5\xA5\xF3\xC5\xB9"+0x686F1950).s,
			st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
#else
		snprintf(timeFormat,31,/*[%02d-%02d %02d:%02d:%02d %03d] */XorStr<0x7A,33,0x686F1950>("\x21\x5E\x4C\x4F\x1A\x52\xA5\xB1\xB0\xE7\xA4\xA0\xB6\xB5\xEC\xB3\xAF\xBB\xBE\xE9\xB4\xAA\xA0\xA3\xF6\xB3\xB1\xA5\xA5\xF3\xC5\xB9"+0x686F1950).s,
			st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
#endif
		mLogFile << timeFormat << buf << std::endl;

		SIXLog("%s %s",timeFormat,buf);
	};
}

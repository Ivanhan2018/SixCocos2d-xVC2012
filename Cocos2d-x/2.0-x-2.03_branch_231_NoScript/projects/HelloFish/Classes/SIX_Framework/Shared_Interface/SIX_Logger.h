#pragma once
#ifdef WIN32
#include <windows.h>
#endif
#include <fstream>
#include <sstream>
#include <string>
#include <SIX_Lock.h>
using namespace std;

USING_NS_CC;

class SIX_Logger 
{
public:
	SIX_Logger();
	~SIX_Logger();

	void SetLogName(char *name);
	void WriteToFile(char *,...);
private:
	char* buf;
	SYSTEMTIME st;
	bool bInited;

	SIX_Mutex *mutex;

	std::ofstream mLogFile;
};

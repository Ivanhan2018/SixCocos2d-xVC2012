#include "SIX_Common.h"
#include "main.h"
#include "../Classes/SIX_World.h"
#include "CCEGLView.h"
#include "resource.h"
#include "MiniDumper.h"

USING_NS_CC;
CREATE_UTILITY;
//CREATE_GLOBALMGR;

CMiniDumper *pMiniDumper;

void onExit()
{
	int MemoryLeaked = _CrtDumpMemoryLeaks();
	CCAssert(MemoryLeaked==0,"Memory Leaked!");
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	ML_INIT(onExit);

	CCString *Name=0;
	CCString *Pass=0;
#ifdef WIN32
	pMiniDumper = new CMiniDumper();
	timeBeginPeriod(1);
#ifdef HALL_LOGIN
	// 读取大厅传过来的用户名与密码
	// 命令行格式："/modulefilename:Hall.exe /account:%s /pw:%s"
	wstring strCmdLine = lpCmdLine;
	wstring::size_type stStartIndex = strCmdLine.find(_T("/account:"));
	if (stStartIndex != strCmdLine.npos)
	{
		stStartIndex += lstrlen(_T("/account:"));
		wstring::size_type stEndIndex = strCmdLine.find(_T(" "), stStartIndex);
		wstring wAccount = strCmdLine.substr(stStartIndex, stEndIndex-stStartIndex);

		stStartIndex = strCmdLine.find(_T("/pw:"));
		stStartIndex += lstrlen(_T("/pw:"));
		stEndIndex = strCmdLine.find(_T(" "), stStartIndex);
		if (stStartIndex != strCmdLine.npos  && stEndIndex == strCmdLine.npos)
			stEndIndex = strCmdLine.length();
		wstring wPassword = strCmdLine.substr(stStartIndex, stEndIndex-stStartIndex);
	
		Name = CCString::create(SIX_Utility::GetInstance()->UnicodeToAnsi(wAccount.c_str()).c_str());
		Pass = CCString::create(SIX_Utility::GetInstance()->UnicodeToAnsi(wPassword.c_str()).c_str());
	}
#endif
#endif
	
    // create the application instance
    SIX_World app;
	app.setPlayerInfo(Name,Pass);
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(MAX_WIDTH, MAX_HEIGHT );
	int retv = CCApplication::sharedApplication()->run();

#ifdef WIN32
	timeEndPeriod(1);
#endif
    return retv;
}
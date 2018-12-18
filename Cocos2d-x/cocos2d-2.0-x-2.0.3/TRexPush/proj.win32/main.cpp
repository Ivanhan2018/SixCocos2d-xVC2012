#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include <iostream>
#include <fstream>
#include <string>

#include "XMLTesting.h"

USING_NS_CC;

using namespace std;


// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{




    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

	{
		ifstream input("xmlparams.txt", fstream::in);

		string s;

		input>>s;

		cout<<"Here is S: "<<s<<endl;

	if (s == "GO"){

		input >> s;
		xmlTests(s);

		system("pause");

		#ifdef USE_WIN32_CONSOLE
			FreeConsole();
		#endif

		return 0;
	}
	}


    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(480, 320);

    int ret = CCApplication::sharedApplication()->run();


#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}



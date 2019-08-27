/*
HsqtekiMac-2:maccpp Hsq$ g++ -fPIC -shared -o libmathlib.so mathlib.cpp
HsqtekiMac-2:maccpp Hsq$ g++ -o lgam10 lgam10.cpp -L. -lmathlib -ldl
HsqtekiMac-2:maccpp Hsq$ ./lgam10
计算实伽马函数Γ(x)，请输入x：
1
Γ(x=1.000000)=1.000010
HsqtekiMac-2:maccpp Hsq$ ./lgam10 4
Γ(x=4.000000)=6.000060
*/
#include <stdlib.h>
#include <stdio.h>
#if defined(_WIN32)||defined(_WIN64)
#include<windows.h>
#else
#include <dlfcn.h>
#endif

int main(int argc, char* argv[])
{
	typedef double(*pR)(double x);
	pR R;
#if defined(_WIN32)||defined(_WIN64)
	HINSTANCE hLib = LoadLibrary("MATHLIB72.DLL");
	if(!hLib) return 0;
	R=(pR)GetProcAddress(hLib,"_lgam1@8");//伽马函数
#else
        void* hLib = dlopen("./libmathlib.so", RTLD_LAZY);
        if(!hLib)
        {        
            printf("ERROR, Message(%s).\n", dlerror());
            return -1;
        }
        R=(pR)dlsym(hLib, "lgam1");
        char* szError = dlerror();
        if(szError != NULL)
        {
         printf("ERROR, Message(%s).\n", szError);
         dlclose(hLib);
         return -1;
        }
#endif

    if(argc>=2)
    {
        double x=atof(argv[1]);
        printf("Γ(x=%lf)=%lf\n",x,R(x));
    }
    else
    {
        double x;
	 printf("计算实伽马函数Γ(x)，请输入x：\n");
        scanf("%lf",&x);
        printf("Γ(x=%lf)=%lf\n",x,R(x));
    }
#if defined(_WIN32)||defined(_WIN64)
	FreeLibrary(hLib);
#else
    dlclose(hLib);
#endif
	getchar();
	return 0;
}
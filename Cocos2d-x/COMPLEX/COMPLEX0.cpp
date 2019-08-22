// COMPLEX0.cpp : 定义控制台应用程序的入口点。
//
#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。

//#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include<iostream> 
#include<complex>
#include<limits>
using namespace std;
typedef std::complex<double> dcomplex;
#define DC(z) dcomplex(z.re,z.im)

#pragma comment(lib,"COMPLEX.lib")

/*复数定义*/
typedef struct
{
	double re;
	double im;
}DCOMPLEX;
extern "C" 
{
	_declspec(dllexport)DCOMPLEX __stdcall CSin(const DCOMPLEX *c1);

	//不变量g_2,g_3的计算
	DCOMPLEX __stdcall g2(const DCOMPLEX *tau, const DCOMPLEX *w1);
	DCOMPLEX __stdcall g3(const DCOMPLEX *tau, const DCOMPLEX *w1);
};

/*
http://oeis.org/search?q=E_4&sort=&language=

g_2=60G_4
g_3=140G_6
*/

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout<<sizeof(dcomplex)<<std::endl;

	dcomplex tau(0,7.416195/8.626062);
	dcomplex w1(8.626062,0);
	DCOMPLEX ret=CSin((const DCOMPLEX *)&w1);
	cout<<DC(ret)<<endl;

	std::cout<<"g_2(实周期w_1=8.626062，虚周期w_2=7.416195i)="<<DC(g2((const DCOMPLEX *)&tau,(const DCOMPLEX *)&w1))<<std::endl;
	std::cout<<"g_3(实周期w_1=8.626062，虚周期w_2=7.416195i)="<<DC(g3((const DCOMPLEX *)&tau,(const DCOMPLEX *)&w1))<<std::endl;

	std::cin.get();
	return 0;
}


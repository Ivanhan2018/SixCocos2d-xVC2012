// COMPLEX0.cpp : �������̨Ӧ�ó������ڵ㡣
//
#pragma once

// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��

// ���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������
// WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��

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

/*��������*/
typedef struct
{
	double re;
	double im;
}DCOMPLEX;
extern "C" 
{
	_declspec(dllexport)DCOMPLEX __stdcall CSin(const DCOMPLEX *c1);

	//������g_2,g_3�ļ���
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

	std::cout<<"g_2(ʵ����w_1=8.626062��������w_2=7.416195i)="<<DC(g2((const DCOMPLEX *)&tau,(const DCOMPLEX *)&w1))<<std::endl;
	std::cout<<"g_3(ʵ����w_1=8.626062��������w_2=7.416195i)="<<DC(g3((const DCOMPLEX *)&tau,(const DCOMPLEX *)&w1))<<std::endl;

	std::cin.get();
	return 0;
}


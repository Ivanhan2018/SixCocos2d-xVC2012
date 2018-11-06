/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		侯国江
	
	purpose:  公共的宏，为了兼容 Unicode 与 Ansi 而设置，取代 stdafx.h 
*********************************************************************/



#ifndef PUBLIC_MACRO_H
#define PUBLIC_MACRO_H

// 屏蔽一些警告
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN

#include "Winsock2.h"	// 因为有了 WIN32_LEAN_AND_MEAN ，不再会与  <windows.h>中的<winsock.h> 起冲突了
#include <ws2tcpip.h>
#include <mswsock.h>

// TODO: 在此处引用程序需要的其他头文件
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdlib.h>
#include <locale.h>      // setlocale 所需头文件，让控制台输出 Unicode 的中文

#include <vector>
#include <list>
#include <map>
#include <hash_map>
using std::vector;
using std::list;
using std::map;
using std::hash_map;
using std::pair;

#include "Often.h"
#include "EasyDataTime.h"
							

#endif
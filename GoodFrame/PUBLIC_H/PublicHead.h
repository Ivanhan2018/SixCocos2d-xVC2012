/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		�����
	
	purpose:  �����ĺ꣬Ϊ�˼��� Unicode �� Ansi �����ã�ȡ�� stdafx.h 
*********************************************************************/



#ifndef PUBLIC_MACRO_H
#define PUBLIC_MACRO_H

// ����һЩ����
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN

#include "Winsock2.h"	// ��Ϊ���� WIN32_LEAN_AND_MEAN �����ٻ���  <windows.h>�е�<winsock.h> ���ͻ��
#include <ws2tcpip.h>
#include <mswsock.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdlib.h>
#include <locale.h>      // setlocale ����ͷ�ļ����ÿ���̨��� Unicode ������

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
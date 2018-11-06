/*
 *  packet.h
 *  test
 *
 *  Created by Aden on 14-11-20.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEFINE_PACKET_H
#define DEFINE_PACKET_H
#pragma once
#include "common/Define.h"
#pragma pack(1)

/////////////////////////////////////////////////////////////////////
//端口定义
#define MAX_CONTENT			512							//并发容量
#define PORT_AUTO_SELECT	((WORD)(0XFFFF))			//自动端口

//#define IP_LOGON			"login1.91zjd.com"
//#define PORT_TEMP			9001
//#define IP_LOGON			"121.40.208.243"
#define IP_LOGON			"121.41.82.116"
#define PORT_TEMP			8300
//#define IP_LOGON			"117.18.5.229"
//#define PORT_TEMP			36856

//#define PORT_LOGON			8100						//登陆端口  mojunxin
#define PORT_LOGON			8300						//登陆端口
#define PORT_CENTER			8310						//协调端口
#define PORT_8311			8311						//测试端口
#define PORT_MANAGER		8320						//管理端口

//#define DEFAULT_ACCOUNT		"phone"
//#define DEFAULT_PASSWORD	"hpkj12345!@#"
#define DEFAULT_ACCOUNT		"test009"
#define DEFAULT_PASSWORD	"123456"

/////////////////////////////////////////////////////////////////////
//网络定义

//数据类型
#define DK_MAPPED			0X01						//映射类型
#define DK_ENCRYPT			0X02						//加密类型
#define DK_COMPRESS			0X04						//压缩类型

//长度定义
#define SOCKET_TCP_BUFFER	16384									//网络缓冲
#define SOCKET_TCP_PACKET	(SOCKET_TCP_BUFFER-sizeof(TCP_Head))	//网络缓冲


#pragma mark 内核命令
#define MDM_KN_COMMAND			0						//内核命令
#define SUB_KN_DETECT_SOCKET	1						//检测命令
#define SUB_KN_VALIDATE_SOCKET	2						//验证命令
///////////////////////////////////////////////////////////////////////////
//结构定义
//网络验证
typedef struct
{
	TCHART				szValidateKey[64];							//验证字符
}TCP_Validate;

#pragma pack()

#endif

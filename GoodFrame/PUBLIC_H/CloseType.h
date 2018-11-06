/********************************************************************
	created:	2013/08/10
	created:	10:8:2013   11:47
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\CloseType.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	CloseType
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/


#ifndef CLOSE_TYPE_H
#define CLOSE_TYPE_H

enum CLOSE_TYPE	// 关闭方式
{
	CLOSE_TYPE_NO = 0,					// 初始是的无效值或者未知原因
	CLOSE_TYPE_CLIENT_CLOSE = 10,		// 客户端主动关闭
	CLOSE_TYPE_FLASH_CLOSE = 20,		// 闪断，例如手工禁用【本地连接】的方式模拟路由信号不稳定
	CLOSE_TYPE_SERVER_POWER_CLOSE = 30,	// 服务端主动关闭客户端
	CLOSE_TYPE_PACKAGE_ERR = 40,		// 通讯包出错

	//CLOSE_TYPE_WSARECV_ERR = 50,		// 反复读取失败，见 recv_data 函数
};

#endif
/********************************************************************
	created:	2013/01/01
	created:	1:1:2013   0:04
	filename: 	C:\GoodFrame\MemPoolTest\MemPoolTest\CoreHead.h
	file path:	C:\GoodFrame\MemPoolTest\MemPoolTest
	file base:	CoreHead
	file ext:	h
	author:		hgj
	
	purpose:	内核的结构、宏、枚举、
*********************************************************************/


#ifndef CORE_HEAD_H
#define CORE_HEAD_H

//#include <memory>
// 屏蔽一些警告
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define INVALID_CHANNEL_NO -1	// 无效的通道号
#define INVALID_MAIN_CODE  -1	// 无效的主码
#define INVALID_SUB_CODE   -1	// 无效的辅助码

#define WAIT_EXIT_TIME 60*1000	// 主要是为 WaitForSingleObject 等服务的

//--- 任务池的消息，TPM 是 TASK_POOL_MSG 的缩写 -------------------------------------------------------------------
#define TPM_CORE_NORMAL	 0	// 内核心的正常消息
#define TPM_CORE_EXIT	10	// 内核心的退出消息

//#include "./TaskMsgResult.h"

// 内核加密层
struct CORE_ENCRYPTION
{
	BYTE bySegment[16];	// 预留，暂时没做
};

// 内核消息的头
struct CORE_MSG_HEAD	
{
	CORE_MSG_HEAD()
	{
		uFlag = 0xaaaaaaaaaaaaaaaa;
		bIsHeartbeat = 0;
		lChannelNo = INVALID_CHANNEL_NO;	
		dwPeerIP = 0;	
		iMainCode = INVALID_MAIN_CODE;	// 无效的主码
		iSubCode = INVALID_SUB_CODE;	// 无效的辅助码

		iTotalSize = sizeof(CORE_MSG_HEAD);
	}

	void SetTotalSize(int iSize)
	{
		iTotalSize = iSize;
	}

	int GetTotalSize()
	{
		return iTotalSize;
	}

	// 在原长度基础上增加长度
	int RaiseTotalSize(int iRaiseSize)
	{
		iTotalSize += iRaiseSize;

		return iTotalSize;
	}

	ULONGLONG 		uFlag;			// 标志位，每个字节都应该是 0xaa ,其值应该是 0xaaaaaaaaaaaaaaaa  ;
    int				bIsHeartbeat;	// 0 表示非心跳包，1 表示心跳包
	int				iTotalSize;		// 整个消息的长度， sizeof(CORE_MSG) +  iBodyLen 
	LONGLONG		lChannelNo;		// 通道号，服务端专用
	unsigned int	dwPeerIP;		// 对端主机的IP
	int				iMainCode;
	int			    iSubCode;

	CORE_ENCRYPTION	encryption;
};



#endif
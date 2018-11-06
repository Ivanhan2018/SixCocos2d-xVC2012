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

#ifdef WIN32
// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#define INVALID_CHANNEL_NO -1	// 无效的通道号
#define INVALID_MAIN_CODE  -1	// 无效的主码
#define INVALID_SUB_CODE   -1	// 无效的辅助码

#define WAIT_EXIT_TIME 60*1000	// 主要是为 WaitForSingleObject 等服务的

//--- 任务池的消息，TPM 是 TASK_POOL_MSG 的缩写 -------------------------------------------------------------------
#define TPM_CORE_NORMAL	 0	// 内核心的正常消息
#define TPM_CORE_EXIT	10	// 内核心的退出消息

#include "PublicMacro.h"
#include "./TaskMsgResult.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

enum SERVER_HANDLE_ERR	// 对端专用的错误提示
{
	SHE_IS_POWER_CLOSED	= 5,	// 表示被对端主动关闭
	SHE_PackageNotOver	= 8,	// 包头若过来了，但包体还未发过来，就应该等到下一个包完整到达时才判断

	SHE_pCommTcpServerIsNull	= 1000,	// m_pCommTcpServer 是空值
	SHE_SmallPackegIsZero		= 1002,	// 收到包的长度是零
	SHE_Verify_Fail				= 1003,	// 校验包失败
	
	SHE_pAtomMsg_retrieve_Fail	= 1008,	// 原子包出池失败

	SHE_CoreHeadFlagFail = 2000,	// 标志位判断失败，非 0xaaaaaaaaaaaaaaaa
	SHE_PackageLenFail = 2001,		// 包的长度判断失败

	SHE_m_pCoreClientIsNull	= 3000,	// m_pCoreClient 是空值
	SHE_Verify_First_Fail	= 3004,	// 校验包失败，第一个包是无效的
	SHE_Verify_Other_Fail	= 3006,	// 校验包失败，第一个包之后出现无效包
}; 

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
		lCordState = 0;
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

	// 设置成心跳包
	void set_heartbeat()
	{
		lCordState = lCordState | 0x00000001;
	}
		
	// 设置主动关闭指定对端的指令
	void set_power_close_peer()
	{
		lCordState = lCordState | 0x00000002;
	}

	// 是否主动关闭指定对端的指令，返回true表示是，返回false表示否
	bool is_power_close_peer()
	{
		int iFlag = lCordState & 0x00000002;
		return (iFlag>0);
	}

	ULONGLONG 		uFlag;			// 标志位，每个字节都应该是 0xaa ,其值应该是 0xaaaaaaaaaaaaaaaa  ;
	long			lCordState;		// 内核指令的状态，是掩码，
									// 第0位是 0 表示非心跳包，1 表示心跳包
									// 第1位是 0 表示非主动关闭指令，1 表示主动关闭指令

	int				iTotalSize;		// 整个消息的长度， sizeof(CORE_MSG) +  iBodyLen 
	LONGLONG		lChannelNo;		// 通道号，服务端专用
	unsigned int	dwPeerIP;		// 对端主机的IP
	int				iMainCode;		// 主消息码
	int			    iSubCode;		// 辅助消息码

	CORE_ENCRYPTION	encryption;
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif
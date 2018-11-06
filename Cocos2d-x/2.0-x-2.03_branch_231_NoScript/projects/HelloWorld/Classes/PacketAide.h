//
//  PacketAide.h
//  XXDDZ
//
//  Created by Eldder on 13-10-17.
//
//

#ifndef PACKET_AIDE_HEAD_FILE
#define PACKET_AIDE_HEAD_FILE

#pragma once

#include "Packet.h"
#include "Define.h"
//#include "REC_GameController.h"
#pragma pack(1)



//存储长度
#ifdef _UNICODE
#define CountStringBuffer CountStringBufferW
#else
#define CountStringBuffer CountStringBufferA
#endif



//存储长度
//#define CountStringBufferA(String) ((UINT)((std::lstrlenA(String)+1)*sizeof(char)))
//#define CountStringBufferW(String) ((UINT)((std::wcslen(String)+1)*sizeof(_TCHAR_)))



//////////////////////////////////////////////////////////////////////////////////

//数据定义
//#define DTP_NULL					0								//无效数据

//数据描述
//struct tagDataDescribe
//{
//	_WORD_							wDataSize;						//数据大小
//	_WORD_							wDataDescribe;					//数据描述
//};

//////////////////////////////////////////////////////////////////////////////////

//发送辅助类
class CSendPacketHelper
{
	//变量定义
protected:
	_WORD_							m_wDataSize;					//数据大小
	_WORD_							m_wMaxBytes;					//缓冲大小
	LPBYTE							m_pcbBuffer;					//缓冲指针
    
	//函数定义
public:
	//构造函�?	
	inline CSendPacketHelper(void * pcbBuffer, _WORD_ wMaxBytes);
    
	//功能函数
public:
	//清理数据
	inline void CleanData() { m_wDataSize=0; }
	//获取大小
	inline _WORD_ GetDataSize() { return m_wDataSize; }
	//获取缓冲
	inline void * GetDataBuffer() { return m_pcbBuffer; }
    
	//功能函数
public:
	//插入字符
	inline bool AddPacket(LPCSTR pszString, _WORD_ wDataType);
	//插入字符
	inline bool AddPacket(LPCWSTR pszString, _WORD_ wDataType);
	//插入数据
	inline bool AddPacket(void * pData, _WORD_ wDataSize, _WORD_ wDataType);
};

//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

//构造函�?
CSendPacketHelper::CSendPacketHelper(void * pcbBuffer, _WORD_ wMaxBytes)
{
	//设置变量
	m_wDataSize=0;
	m_wMaxBytes=wMaxBytes;
	m_pcbBuffer=(_BYTE_ *)pcbBuffer;
    
	return;
}

////插入字符
//bool CSendPacketHelper::AddPacket(LPCSTR pszString, _WORD_ wDataType)
//{
//	//参数判断
//	CC_ASSERT(pszString!=NULL);
//	if (pszString[0]==0) return true;
//    
//	//插入数据
//	return AddPacket((void *)pszString,std::strlen(pszString),wDataType);
//}
//
////插入字符
//bool CSendPacketHelper::AddPacket(LPCWSTR pszString, _WORD_ wDataType)
//{
//	//参数判断
//	CC_ASSERT(pszString!=NULL);
//	if (pszString[0]==0) return true;
//    
//	//插入数据
//	//return AddPacket((void *)pszString,CountStringBufferW(pszString),wDataType);
//}

//插入数据
bool CSendPacketHelper::AddPacket(void * pData, _WORD_ wDataSize, _WORD_ wDataType)
{
	CC_ASSERT(wDataType!=DTP_NULL);
	CC_ASSERT((wDataSize+sizeof(tagDataDescribe)+m_wDataSize)<=m_wMaxBytes);
	if ((wDataSize+sizeof(tagDataDescribe)+m_wDataSize)>m_wMaxBytes) return false;
    
	//插入数据
	CC_ASSERT(m_pcbBuffer!=NULL);
	tagDataDescribe * pDataDescribe=(tagDataDescribe *)(m_pcbBuffer+m_wDataSize);
	pDataDescribe->wDataSize=wDataSize;
	pDataDescribe->wDataDescribe=wDataType;
    
	//插入数据
	if (wDataSize>0)
	{
		CC_ASSERT(pData!=NULL);
		
		memcpy(pDataDescribe+1 , pData , wDataSize);
	}
    
	//设置数据
	m_wDataSize+=sizeof(tagDataDescribe)+wDataSize;
    
	return true;}

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

#pragma pack()

#endif

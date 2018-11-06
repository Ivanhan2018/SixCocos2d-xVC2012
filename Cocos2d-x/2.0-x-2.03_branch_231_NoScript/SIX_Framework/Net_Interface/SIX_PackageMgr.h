/***********************************************
Name：SIX_PackageMgr
Desc：封包管理器负责拆包/组包
Auth：Cool.Cat@2013-04-18
***********************************************/
#pragma once
#include <SIX_Typedef.h>
#include <CoreHead.h>
#include <SIX_TRBuffer.h>

#define BUFFSIZE	1024*8
//#define BLOCKSIZE	1024*2

class SIX_ClientBase;

// 解包状态
typedef enum {
	// 完成包
	UNPACK_PACKET_SUCCESSED		=	0,
	// 空包
	UNPACK_PACKET_NIL			=	-1,
	// 错包
	UNPACK_PACKET_INVALID		=	-2,
	// 不完整包
	UNPACK_PACKET_NOCOMPLETED	=	-3,
	// RB里的数据不足一个包头
	UNPACK_PACKET_NOENOUGHHEAD	=	-4,
	// RB里没有可读的数据
	UNPACK_PACKET_NOBUFFER		=	-5,
	// 整包长度小于等于包头长度
	UNPACK_PACKET_LESSFULLPCK	=	-6,
	// 服务端主动关闭客户端
	UNPACK_PACKET_CLOSEPEER		=	-7,
} UNPACK_STATUS;

class MSG_INFO{
public:
	SIX_ClientBase		*m_pClient;
	int					m_MainCode;
	int					m_SubCode;
	unsigned char		*m_Data;
	unsigned int		m_DataLen;
	bool				m_bSetHeartBeat;
	bool				m_bSetPowerClosePeer;
	MSG_INFO()
	{
		m_pClient = 0;
		m_MainCode = m_SubCode = m_DataLen = 0;
		m_Data = 0;
		m_bSetHeartBeat = m_bSetPowerClosePeer = false;
	}
	~MSG_INFO()
	{
		CC_SAFE_DELETE_ARRAY(m_Data);
	}
	// 发送时调用
	void Create(int mainCode,int subCode,char *pData=0,unsigned int pDataLen=0,bool setHeartBeat=false,bool setPowerClosePeer=false)
	{
		m_pClient				= 0;
		m_MainCode				= mainCode;
		m_SubCode				= subCode;
		m_DataLen				= pDataLen;
		m_bSetHeartBeat			= setHeartBeat;
		m_bSetPowerClosePeer	= setPowerClosePeer;

		if (pDataLen>0)
		{
			m_Data = new unsigned char[m_DataLen+1];
			memcpy(m_Data,pData,m_DataLen);
			m_Data[m_DataLen] = 0;
		}	
	}
	// 收包时调用
	void Creae(SIX_ClientBase *pTarget,int mainCode,int subCode,char *pData=0,unsigned int pDataLen=0)
	{
		m_pClient				= pTarget;
		m_MainCode				= mainCode;
		m_SubCode				= subCode;
		m_DataLen				= pDataLen;
		m_bSetHeartBeat			= false;
		m_bSetPowerClosePeer	= false;

		if (pDataLen>0)
		{
			m_Data = new unsigned char[m_DataLen+1];
			memcpy(m_Data,pData,m_DataLen);
			m_Data[m_DataLen] = 0;
		}
	}
};

class SIX_PackageMgr
{
public:
	SIX_PackageMgr();
	~SIX_PackageMgr();
public:
	// 组包
	bool Pack(MSG_INFO *pMsg,char *pDst,unsigned int *pDstLen);
	// 拆包
	int UnPack(char *pSrc,unsigned int pSrcLen,MSG_INFO *pMsg);
	// 检验包
	int is_packeg_valid(char* pData, int iDataLen);
	// 尝试拆包
	int TryUnPack(MSG_INFO *pMsg);
	// 取包头长度
	unsigned int GetPackHeaderSize();
	// 写缓冲
	int WriteBuffer(char *pData,unsigned int writeLen);
	// 清空RBBuffer
	void ReleaseBuffer();
private:
	// 读缓冲
	SIX_TRBuffer<char> *m_recvList;
	// 包头长度
	unsigned int m_uHeadSize;
};
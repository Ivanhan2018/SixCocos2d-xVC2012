/***********************************************
Name：SIX_PackageMgr
Desc：封包管理器负责拆包/组包
Auth：Cool.Cat@2013-04-18
***********************************************/
#pragma once
#include <SIX_Typedef.h>
#include "CoreHead.h"

class MSG_INFO{
public:
	int				m_MainCode;
	int			    m_SubCode;
	char *			m_Data;
	unsigned int	m_DataLen;
	MSG_INFO()
	{
		m_MainCode = m_SubCode = m_DataLen = 0;
		m_Data = 0;
	}
	~MSG_INFO()
	{
		CC_SAFE_DELETE_ARRAY(m_Data);
	}
	void Creae(int mainCode,int subCode,char *pData,unsigned int pDataLen)
	{
		m_MainCode = mainCode;
		m_SubCode = subCode;
		m_DataLen = pDataLen;

		m_Data = new char[m_DataLen+1];
		memcpy(m_Data,pData,m_DataLen);
		m_Data[m_DataLen] = 0;
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
	bool UnPack(char *pSrc,unsigned int pSrcLen,MSG_INFO *pMsg);
};
#include "SIX_PackageMgr.h"

SIX_PackageMgr::SIX_PackageMgr()
{
}

SIX_PackageMgr::~SIX_PackageMgr()
{
}

// 组包
bool SIX_PackageMgr::Pack(MSG_INFO *pMsg,char *pDst,unsigned int *pDstLen)
{
	if(!pMsg || !pDst)
		return false;
	
	*pDstLen = 0;

	// 包头
	CORE_MSG_HEAD header;
	memset(&header,0,sizeof(header));
	header.RaiseTotalSize(pMsg->m_DataLen);
	header.iMainCode = pMsg->m_MainCode;
	header.iSubCode = pMsg->m_SubCode;

	*pDstLen = sizeof(header);
	memcpy(pDst,(const void*)&header,*pDstLen);
	memcpy(pDst+*pDstLen,pMsg->m_Data,pMsg->m_DataLen);
	*pDstLen += pMsg->m_DataLen;
	pDst[*pDstLen] = 0;

	return true;
}

// 拆包
bool SIX_PackageMgr::UnPack(char *pSrc,unsigned int pSrcLen,MSG_INFO *pMsg)
{
	if(!pMsg || !pSrc || !pSrcLen)
		return false;

	return true;
}
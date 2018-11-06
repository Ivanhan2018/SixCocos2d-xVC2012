#include "SIX_PackageMgr.h"
#include "SIX_GlobalMgr.h"

SIX_PackageMgr::SIX_PackageMgr()
{
	m_recvList = new SIX_TRBuffer<char>(BUFFSIZE);
	m_uHeadSize = sizeof(CORE_MSG_HEAD);
}

SIX_PackageMgr::~SIX_PackageMgr()
{
	CC_SAFE_DELETE(m_recvList);
}

// 组包
bool SIX_PackageMgr::Pack(MSG_INFO *pMsg,char *pDst,unsigned int *pDstLen)
{
	if(!pMsg || !pDst)
		return false;
	
	*pDstLen = 0;

	// 包头
	CORE_MSG_HEAD header;
	header.RaiseTotalSize(pMsg->m_DataLen);
	header.iMainCode = pMsg->m_MainCode;
	header.iSubCode = pMsg->m_SubCode;

	// 设置自己为心跳状态
	if (pMsg->m_bSetHeartBeat)
		header.set_heartbeat();
	// 设置自己为主动断开状态
	if (pMsg->m_bSetPowerClosePeer)
		header.set_power_close_peer();

	*pDstLen = this->GetPackHeaderSize();
	memcpy(pDst,(const void*)&header,*pDstLen);

	// 包体
	if (pMsg->m_DataLen>0)
	{
		memcpy(pDst+*pDstLen,pMsg->m_Data,pMsg->m_DataLen);
		*pDstLen += pMsg->m_DataLen;
		pDst[*pDstLen] = 0;
	}

	return true;
}

// 拆包
int SIX_PackageMgr::UnPack(char *pSrc,unsigned int pSrcLen,MSG_INFO *pMsg)
{
	if(!pMsg || !pSrc || !pSrcLen)
		return UNPACK_PACKET_NIL;

	memset(pMsg,0,sizeof(pMsg));

	if (is_packeg_valid(pSrc,pSrcLen)!=0)
		return UNPACK_PACKET_INVALID;

	const CORE_MSG_HEAD* pCoreHead = (CORE_MSG_HEAD*)pSrc;
	int bodyLen = pCoreHead->iTotalSize-this->GetPackHeaderSize();
	// 差值=本次数据长度-包体长度
	int leftLen = pSrcLen - this->GetPackHeaderSize() - bodyLen;

	// 差值小于0，说明包不完整，跳过本次处理，期待下一次拆包
	if (leftLen<0)
	{
		SIXLog("收到不完整包[%d]，期待下一次拆包!",leftLen);

		// 缓存本次数据包
		WriteBuffer(pSrc,pSrcLen);
		return UNPACK_PACKET_NOCOMPLETED;
	}
	// 差值大于0，说明完整包后还附带冗余数据，冗余数据要缓存起来
	else if (leftLen>0)
	{
		SIXLog("收到冗余包[%d]",leftLen);

		// 缓存冗余数据
		WriteBuffer(pSrc+this->GetPackHeaderSize()+bodyLen,leftLen);
	}

	// 差值等于0，说明本次接收到了完整包
	pMsg->m_MainCode = pCoreHead->iMainCode;
	pMsg->m_SubCode = pCoreHead->iSubCode;
	pMsg->m_DataLen = bodyLen;
	pMsg->m_Data = new unsigned char[bodyLen+1];
	memcpy(pMsg->m_Data,pSrc+this->GetPackHeaderSize(),bodyLen);
	pMsg->m_Data[bodyLen] = 0;
	return UNPACK_PACKET_SUCCESSED;
}

int SIX_PackageMgr::is_packeg_valid(char* pData, int iDataLen)
{
	if( 0 == pData || 0 == iDataLen)
	{
		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile(/*[PCK].pData[0x%08X][%d]*/XorStr<0x58,24,0xE877F911>("\x03\x09\x19\x10\x01\x73\x2E\x1B\x01\x15\x03\x38\x54\x1D\x43\x57\x50\x31\x37\x30\x49\x09\x33"+0xE877F911).s,
			pData,iDataLen);
		return -1;
	}

	const CORE_MSG_HEAD* pCoreHead = (CORE_MSG_HEAD*)pData;

	if(0xaaaaaaaaaaaaaaaa != pCoreHead->uFlag)	// 标志位判断
	{
		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile(/*[PCK].uFlag[0x%08X]*/XorStr<0x46,20,0x1B70A26D>("\x1D\x17\x0B\x02\x17\x65\x39\x0B\x22\x2E\x37\x0A\x62\x2B\x71\x65\x6E\x0F\x05"+0x1B70A26D).s,
			pCoreHead->uFlag);
		return -2;	// 标志位判断失败
	}

	//--- 长度判断 -----------------
	//if (pCoreHead->iTotalSize > 0 && pCoreHead->iTotalSize <= BUFFSIZE  && pCoreHead->iTotalSize <= iDataLen)
	if (pCoreHead->iTotalSize > 0 && pCoreHead->iTotalSize <= BUFFSIZE)
	{
	}
	else
	{
		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile(/*[PCK].Size[%d]*/XorStr<0xCE,15,0xC96463A3>("\x95\x9F\x93\x9A\x8F\xFD\x87\xBC\xAC\xB2\x83\xFC\xBE\x86"+0xC96463A3).s,
			pCoreHead->iTotalSize);
		return -3;	// 包的长度判断失败
	}

	// 加密层判断，待做 ???

	return 0;
}

int SIX_PackageMgr::TryUnPack(MSG_INFO *pMsg)
{
	int retv = UNPACK_PACKET_NIL;
	int mainCode = 0;
	int subCode = 0;
	unsigned int bodyLen = 0;
	CORE_MSG_HEAD *pHead = 0;
	char *pCoreHead = 0;

	if (!pMsg)
		goto clean;

	memset(pMsg,0,sizeof(pMsg));

	// RB里的数据长度不够一个完整包头
	if (m_recvList->GetCanReadSize()<this->GetPackHeaderSize())
	{
		retv = UNPACK_PACKET_NOENOUGHHEAD;
		goto clean;
	}

	// 先读包头(不擦除)
	pCoreHead = new char[this->GetPackHeaderSize()];
	memset(pCoreHead,0,this->GetPackHeaderSize());
	retv = m_recvList->ReadBuffer(pCoreHead,this->GetPackHeaderSize(),false);
	if (retv<=0)
	{
		CC_SAFE_DELETE(pCoreHead);
		retv = UNPACK_PACKET_NOBUFFER;
		goto clean;
	}

	// 计算包体长度
	pHead = (CORE_MSG_HEAD*)pCoreHead;

	// 验证是不是完整的头
	if (this->is_packeg_valid(pCoreHead,pHead->iTotalSize)!=0)
	{
		CC_SAFE_DELETE(pCoreHead);
		retv = UNPACK_PACKET_INVALID;
		goto clean;
	}

	// 判断是否是服务端主动关闭客户端
	if (pHead->is_power_close_peer())
	{
		CC_SAFE_DELETE(pCoreHead);
		retv = UNPACK_PACKET_CLOSEPEER;
		goto clean;
	}

	// 长度不对？
	if (pHead->iTotalSize<this->GetPackHeaderSize())
	{
		CC_SAFE_DELETE(pCoreHead);
		retv = UNPACK_PACKET_LESSFULLPCK;
		goto clean;
	}

	bodyLen = pHead->iTotalSize - this->GetPackHeaderSize();
	mainCode = pHead->iMainCode;
	subCode = pHead->iSubCode;
	//if (!bodyLen)
	//{
	//	CC_SAFE_DELETE(pCoreHead);
	//	retv = UNPACK_PACKET_LESSFULLPCK;
	//	goto clean;
	//}

	// 如果数据长度不够包体
	if (m_recvList->GetCanReadSize()<pHead->iTotalSize)
	{
		CC_SAFE_DELETE(pCoreHead);
		retv = UNPACK_PACKET_NOCOMPLETED;
		goto clean;
	}

	// 再读包头(擦除)
	retv = m_recvList->ReadBuffer(pCoreHead,this->GetPackHeaderSize());
	if (retv<=0)
	{
		CC_SAFE_DELETE(pCoreHead);
		retv = UNPACK_PACKET_NOBUFFER;
		goto clean;
	}

	// 读包体
	CC_SAFE_DELETE(pCoreHead);

	pMsg->m_MainCode = mainCode;
	pMsg->m_SubCode = subCode;
	pMsg->m_DataLen = bodyLen;

	if (bodyLen>0)
	{
		pCoreHead = new char[bodyLen+1];
		retv = m_recvList->ReadBuffer(pCoreHead,bodyLen);
		if (retv<=0)
		{
			CC_SAFE_DELETE(pCoreHead);
			retv = UNPACK_PACKET_NOBUFFER;
			goto clean;
		}

		pMsg->m_Data = new unsigned char[bodyLen+1];
		memcpy(pMsg->m_Data,pCoreHead,bodyLen);
		pMsg->m_Data[bodyLen] = 0;
	}

	CC_SAFE_DELETE(pCoreHead);
clean:
	return retv;
}

unsigned int SIX_PackageMgr::GetPackHeaderSize()
{
	return m_uHeadSize;
}

int SIX_PackageMgr::WriteBuffer(char *pData,unsigned int writeLen)
{
	return m_recvList->WriteBuffer(pData,writeLen);
}

void SIX_PackageMgr::ReleaseBuffer()
{
	m_recvList->Clean();
}
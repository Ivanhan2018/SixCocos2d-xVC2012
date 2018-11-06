/***********************************************
Name��SIX_PackageMgr
Desc�����������������/���
Auth��Cool.Cat@2013-04-18
***********************************************/
#pragma once
#include <SIX_Typedef.h>
#include <CoreHead.h>
#include <SIX_TRBuffer.h>

#define BUFFSIZE	1024*8
//#define BLOCKSIZE	1024*2

class SIX_ClientBase;

// ���״̬
typedef enum {
	// ��ɰ�
	UNPACK_PACKET_SUCCESSED		=	0,
	// �հ�
	UNPACK_PACKET_NIL			=	-1,
	// ���
	UNPACK_PACKET_INVALID		=	-2,
	// ��������
	UNPACK_PACKET_NOCOMPLETED	=	-3,
	// RB������ݲ���һ����ͷ
	UNPACK_PACKET_NOENOUGHHEAD	=	-4,
	// RB��û�пɶ�������
	UNPACK_PACKET_NOBUFFER		=	-5,
	// ��������С�ڵ��ڰ�ͷ����
	UNPACK_PACKET_LESSFULLPCK	=	-6,
	// ����������رտͻ���
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
	// ����ʱ����
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
	// �հ�ʱ����
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
	// ���
	bool Pack(MSG_INFO *pMsg,char *pDst,unsigned int *pDstLen);
	// ���
	int UnPack(char *pSrc,unsigned int pSrcLen,MSG_INFO *pMsg);
	// �����
	int is_packeg_valid(char* pData, int iDataLen);
	// ���Բ��
	int TryUnPack(MSG_INFO *pMsg);
	// ȡ��ͷ����
	unsigned int GetPackHeaderSize();
	// д����
	int WriteBuffer(char *pData,unsigned int writeLen);
	// ���RBBuffer
	void ReleaseBuffer();
private:
	// ������
	SIX_TRBuffer<char> *m_recvList;
	// ��ͷ����
	unsigned int m_uHeadSize;
};
/********************************************************************
	created:	2013/01/01
	created:	1:1:2013   0:04
	filename: 	C:\GoodFrame\MemPoolTest\MemPoolTest\CoreHead.h
	file path:	C:\GoodFrame\MemPoolTest\MemPoolTest
	file base:	CoreHead
	file ext:	h
	author:		hgj
	
	purpose:	�ں˵Ľṹ���ꡢö�١�
*********************************************************************/


#ifndef CORE_HEAD_H
#define CORE_HEAD_H

//#include <memory>
// ����һЩ����
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

#ifdef WIN32
// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#define INVALID_CHANNEL_NO -1	// ��Ч��ͨ����
#define INVALID_MAIN_CODE  -1	// ��Ч������
#define INVALID_SUB_CODE   -1	// ��Ч�ĸ�����

#define WAIT_EXIT_TIME 60*1000	// ��Ҫ��Ϊ WaitForSingleObject �ȷ����

//--- ����ص���Ϣ��TPM �� TASK_POOL_MSG ����д -------------------------------------------------------------------
#define TPM_CORE_NORMAL	 0	// �ں��ĵ�������Ϣ
#define TPM_CORE_EXIT	10	// �ں��ĵ��˳���Ϣ

#include "PublicMacro.h"
#include "./TaskMsgResult.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

enum SERVER_HANDLE_ERR	// �Զ�ר�õĴ�����ʾ
{
	SHE_IS_POWER_CLOSED	= 5,	// ��ʾ���Զ������ر�
	SHE_PackageNotOver	= 8,	// ��ͷ�������ˣ������廹δ����������Ӧ�õȵ���һ������������ʱ���ж�

	SHE_pCommTcpServerIsNull	= 1000,	// m_pCommTcpServer �ǿ�ֵ
	SHE_SmallPackegIsZero		= 1002,	// �յ����ĳ�������
	SHE_Verify_Fail				= 1003,	// У���ʧ��
	
	SHE_pAtomMsg_retrieve_Fail	= 1008,	// ԭ�Ӱ�����ʧ��

	SHE_CoreHeadFlagFail = 2000,	// ��־λ�ж�ʧ�ܣ��� 0xaaaaaaaaaaaaaaaa
	SHE_PackageLenFail = 2001,		// ���ĳ����ж�ʧ��

	SHE_m_pCoreClientIsNull	= 3000,	// m_pCoreClient �ǿ�ֵ
	SHE_Verify_First_Fail	= 3004,	// У���ʧ�ܣ���һ��������Ч��
	SHE_Verify_Other_Fail	= 3006,	// У���ʧ�ܣ���һ����֮�������Ч��
}; 

// �ں˼��ܲ�
struct CORE_ENCRYPTION
{
	BYTE bySegment[16];	// Ԥ������ʱû��
};

// �ں���Ϣ��ͷ
struct CORE_MSG_HEAD	
{
	CORE_MSG_HEAD()
	{
		uFlag = 0xaaaaaaaaaaaaaaaa;
		lCordState = 0;
		lChannelNo = INVALID_CHANNEL_NO;	
		dwPeerIP = 0;	
		iMainCode = INVALID_MAIN_CODE;	// ��Ч������
		iSubCode = INVALID_SUB_CODE;	// ��Ч�ĸ�����

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

	// ��ԭ���Ȼ��������ӳ���
	int RaiseTotalSize(int iRaiseSize)
	{
		iTotalSize += iRaiseSize;

		return iTotalSize;
	}

	// ���ó�������
	void set_heartbeat()
	{
		lCordState = lCordState | 0x00000001;
	}
		
	// ���������ر�ָ���Զ˵�ָ��
	void set_power_close_peer()
	{
		lCordState = lCordState | 0x00000002;
	}

	// �Ƿ������ر�ָ���Զ˵�ָ�����true��ʾ�ǣ�����false��ʾ��
	bool is_power_close_peer()
	{
		int iFlag = lCordState & 0x00000002;
		return (iFlag>0);
	}

	ULONGLONG 		uFlag;			// ��־λ��ÿ���ֽڶ�Ӧ���� 0xaa ,��ֵӦ���� 0xaaaaaaaaaaaaaaaa  ;
	long			lCordState;		// �ں�ָ���״̬�������룬
									// ��0λ�� 0 ��ʾ����������1 ��ʾ������
									// ��1λ�� 0 ��ʾ�������ر�ָ�1 ��ʾ�����ر�ָ��

	int				iTotalSize;		// ������Ϣ�ĳ��ȣ� sizeof(CORE_MSG) +  iBodyLen 
	LONGLONG		lChannelNo;		// ͨ���ţ������ר��
	unsigned int	dwPeerIP;		// �Զ�������IP
	int				iMainCode;		// ����Ϣ��
	int			    iSubCode;		// ������Ϣ��

	CORE_ENCRYPTION	encryption;
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif
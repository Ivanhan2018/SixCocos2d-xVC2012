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

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN
#ifdef WIN32
#include <windows.h>
#endif

#define INVALID_CHANNEL_NO -1	// ��Ч��ͨ����
#define INVALID_MAIN_CODE  -1	// ��Ч������
#define INVALID_SUB_CODE   -1	// ��Ч�ĸ�����

//--- ����ص���Ϣ��TPM �� TASK_POOL_MSG ����д -------------------------------------------------------------------
#define TPM_CORE_NORMAL	 0	// �ں��ĵ�������Ϣ
#define TPM_CORE_EXIT	10	// �ں��ĵ��˳���Ϣ

enum TASK_MSG_RESULT	// ������Ϣ���
{
	TMR_ERROR = 0,			// �������Ϣ���
	TMR_AUTO_RECYCLE = 1,	// ��ܻ��Զ����
	TMR_CONTINUE_PUT = 2,	// ����Ͷ�ݣ�Ӧ�ò㲻�����ֹ����
	
	TMR_SEND_TO_PEER = 3,	// �ط����Զˣ���ܻ��Զ���أ�Ӧ�ò㲻�����ֹ����
	TMR_CLOSE_PEER = 4,		// �رնԶˣ���ܻ��Զ���أ�Ӧ�ò㲻�����ֹ����
};

// �ں˼��ܲ�
struct CORE_ENCRYPTION
{
	unsigned char bySegment[16];	// Ԥ������ʱû��
};

// �ں���Ϣ��ͷ
struct CORE_MSG_HEAD	
{
	CORE_MSG_HEAD()
	{
		uFlag = 0xaaaaaaaaaaaaaaaa;
		bIsHeartbeat = 0;
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

	unsigned long long 		uFlag;			// ��־λ��ÿ���ֽڶ�Ӧ���� 0xaa ,��ֵӦ���� 0xaaaaaaaaaaaaaaaa  ;
    int				bIsHeartbeat;	// 0 ��ʾ����������1 ��ʾ������
	int				iTotalSize;		// ������Ϣ�ĳ��ȣ� sizeof(CORE_MSG) +  iBodyLen 
	long long		lChannelNo;		// ͨ���ţ������ר��
	unsigned int	dwPeerIP;		// �Զ�������IP
	int				iMainCode;
	int			    iSubCode;

	CORE_ENCRYPTION	encryption;
};



#endif
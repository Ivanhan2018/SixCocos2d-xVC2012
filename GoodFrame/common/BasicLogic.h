/********************************************************************
	created:	2013/02/08
	created:	8:2:2013   13:16
	filename: 	E:\SVN_2013\GoodFrame\common\BasicLogic.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	BasicLogic
	file ext:	h
	author:		�����
	
	purpose:	�����߼��࣬һ�������߼����Ա���Ϊ����
*********************************************************************/

#ifndef BASIC_LOGIC_H
#define BASIC_LOGIC_H

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN

#include "./SynchronyTaskEx.h"

class CCoreServer;

class __declspec(dllexport) CBasicLogic : public CSynchronyTaskExListener
{
public:
	friend class CCoreServer;

public:
	CBasicLogic(void);
	~CBasicLogic(void);

public:

	/* --------------------------------------------------------------------------
	����˵������Ӧ������Ϣ
	���������
		pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
	����������
		pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
	--------------------------------------------------------------------------*/
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock) = 0;

private:
	/* --------------------------------------------------------------------------
	����˵�����յ�Ͷ�ݵ�������Ϣ
	���������
		pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
	����������
		pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
	--------------------------------------------------------------------------*/
	virtual int OnConsumeTask(CMemBlock*& pMsgBlock);

public:
	void set_core_server(CCoreServer* pCoreServer);

	// ����������Ϣ�̵߳�����
	void set_thread_num(int iNum=1);

	// ������Ϣ�أ��������ⲿ���� CMemBlockPool ʵ����ָ��
	void set_mem_block_pool(CMemBlockPool* pMsgPool);

	// ��ʼ
	int start();

	// ֹͣ
	int stop();

public:

	// ���������Ϣ����Ҫ�ֹ����
	// bIsFront	TRUE ��ʾ�ӵ�˫����е�ͷ����FALSE ��ʾ�ӵ�˫����е�β��
	int put(CMemBlock*& pMemBlock, BOOL bIsFront=FALSE);

public:
	CSynchronyTaskEx m_stTaskSinkEx;	// ͬ�������������� OnConsumeTask ��������

	CCoreServer* m_pCoreServer;

protected:
	BOOL	m_bIsDB;	// �Ƿ����ݿ�
};

#endif
#include "./BasicLogic.h"
#include "./PublicHead.h"
#include "./CoreServer.h"

CBasicLogic::CBasicLogic(void)
{
	// ��ʽ�����ü���ģ��
	m_stTaskSinkEx.set_listen_module((CSynchronyTaskExListener*)this);

	m_pCoreServer = NULL;

	m_bIsDB = FALSE;	// �Ƿ�����
}

CBasicLogic::~CBasicLogic(void)
{
}

void CBasicLogic::set_core_server(CCoreServer* pCoreServer)
{
	m_pCoreServer = pCoreServer;
}

 // ����������Ϣ�̵߳�����
 void CBasicLogic::set_thread_num(int iNum)
 {
	m_stTaskSinkEx.set_thread_num(iNum);
 }
		
 // ������Ϣ�أ��������ⲿ���� CMemBlockPool ʵ����ָ��
 void CBasicLogic::set_mem_block_pool(CMemBlockPool* pMsgPool)
 {
	 assert(pMsgPool);
	m_stTaskSinkEx.set_mem_block_pool(pMsgPool);	
 }

 // ��ʼ
 int CBasicLogic::start()
 {
	 return m_stTaskSinkEx.start();
 }

 /* --------------------------------------------------------------------------
����˵����ֹͣ	
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CBasicLogic::stop()
{
	return m_stTaskSinkEx.stop();
}

/* --------------------------------------------------------------------------
����˵�������������Ϣ����Ҫ�ֹ����
���������
	pMemBlock	������Ϣ
����������
	pMemBlock	������Ϣ
����ֵ��
	�ɹ��򷵻� 0 ��
	ʧ�ܷ��� �����룬���£�
		10  TPM_CORE_EXIT ״̬
		20	��Ϣ�����ˣ������� set_message_len ���������ô�һ��
		30	�ڴ����ʧ��
--------------------------------------------------------------------------*/
int CBasicLogic::put(CMemBlock*& pMsgBlock, BOOL bIsFront)
{
	return m_stTaskSinkEx.put(pMsgBlock, bIsFront);
}

/* --------------------------------------------------------------------------
����˵�����յ�Ͷ�ݵ�������Ϣ
���������
	pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
����������
	pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
--------------------------------------------------------------------------*/
int CBasicLogic::OnConsumeTask(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = OnTask(pMsgBlock);

	switch(stTaskMsgResult)
	{
	case TMR_ERROR:	// ����
		{
			printf("Ͷ�ݵ�����ģ�鲻���� \n");

			// �Զ����
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// ���
			break;
		}
	case TMR_AUTO_RECYCLE:	// �Զ����
		{
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// ���
			break;
		}
	case TMR_CONTINUE_PUT:	// ����Ͷ�ݣ�Ӧ�ò㲻�����ֹ����
		{
			//printf("TMR_CONTINUE_PUT \n");	// ������

			break;
		}
	case TMR_SEND_TO_PEER:	// �ط����Զ�
		{
			LONGLONG lChannelNo;
			m_pCoreServer->m_pMsgPool->get_core_msg_channel(pMsgBlock, lChannelNo);
			m_pCoreServer->send_data(lChannelNo, pMsgBlock);
			break;
		}
	case TMR_CLOSE_PEER:	// �رնԶ�
		{
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// ���
			break;
		}
	default:
		{
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// ���
			break;
		}
	}

	return (int)stTaskMsgResult;
}
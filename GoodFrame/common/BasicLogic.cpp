#include "./BasicLogic.h"
#include "./PublicHead.h"
#include "./CoreServer.h"

CBasicLogic::CBasicLogic(void)
{
	// 定式，设置监听模块
	m_stTaskSinkEx.set_listen_module((CSynchronyTaskExListener*)this);

	m_pCoreServer = NULL;

	m_bIsDB = FALSE;	// 是否数据
}

CBasicLogic::~CBasicLogic(void)
{
}

void CBasicLogic::set_core_server(CCoreServer* pCoreServer)
{
	m_pCoreServer = pCoreServer;
}

 // 设置推送消息线程的数量
 void CBasicLogic::set_thread_num(int iNum)
 {
	m_stTaskSinkEx.set_thread_num(iNum);
 }
		
 // 设置消息池，必需由外部传入 CMemBlockPool 实例的指针
 void CBasicLogic::set_mem_block_pool(CMemBlockPool* pMsgPool)
 {
	 assert(pMsgPool);
	m_stTaskSinkEx.set_mem_block_pool(pMsgPool);	
 }

 // 开始
 int CBasicLogic::start()
 {
	 return m_stTaskSinkEx.start();
 }

 /* --------------------------------------------------------------------------
函数说明：停止	
返回值：
	成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CBasicLogic::stop()
{
	return m_stTaskSinkEx.stop();
}

/* --------------------------------------------------------------------------
函数说明：添加任务消息，需要手工归池
传入参数：
	pMemBlock	任务消息
传出参数：
	pMemBlock	任务消息
返回值：
	成功则返回 0 ；
	失败返回 错误码，如下：
		10  TPM_CORE_EXIT 状态
		20	消息超长了，可以用 set_message_len 将长度设置大一点
		30	内存出池失败
--------------------------------------------------------------------------*/
int CBasicLogic::put(CMemBlock*& pMsgBlock, BOOL bIsFront)
{
	return m_stTaskSinkEx.put(pMsgBlock, bIsFront);
}

/* --------------------------------------------------------------------------
函数说明：收到投递的任务消息
传入参数：
	pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
传出参数：
	pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
--------------------------------------------------------------------------*/
int CBasicLogic::OnConsumeTask(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = OnTask(pMsgBlock);

	switch(stTaskMsgResult)
	{
	case TMR_ERROR:	// 错误
		{
			printf("投递的任务模块不存在 \n");

			// 自动归池
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// 归池
			break;
		}
	case TMR_AUTO_RECYCLE:	// 自动归池
		{
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// 归池
			break;
		}
	case TMR_CONTINUE_PUT:	// 继续投递，应用层不允许手工归池
		{
			//printf("TMR_CONTINUE_PUT \n");	// 测试用

			break;
		}
	case TMR_SEND_TO_PEER:	// 回发给对端
		{
			LONGLONG lChannelNo;
			m_pCoreServer->m_pMsgPool->get_core_msg_channel(pMsgBlock, lChannelNo);
			m_pCoreServer->send_data(lChannelNo, pMsgBlock);
			break;
		}
	case TMR_CLOSE_PEER:	// 关闭对端
		{
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// 归池
			break;
		}
	default:
		{
			m_stTaskSinkEx.get_mem_block_pool()->recycle(pMsgBlock);	// 归池
			break;
		}
	}

	return (int)stTaskMsgResult;
}
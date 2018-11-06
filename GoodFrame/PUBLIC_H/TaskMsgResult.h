
#ifndef TASK_MSG_RESULT_H
#define TASK_MSG_RESULT_H

enum TASK_MSG_RESULT	// 任务消息结果
{
	TMR_ERROR = 0,			// 错误的消息结果
	TMR_AUTO_RECYCLE = 1,	// 框架会自动归池
	TMR_CONTINUE_PUT = 2,	// 继续投递，应用层不允许手工归池

	TMR_SEND_TO_PEER = 3,	// 回发给对端，框架会自动归池消息块，应用层不允许手工归池
	TMR_CLOSE_PEER = 4,		// 关闭对端，框架会自动归池，应用层不允许手工归池
};

#endif

#ifndef TASK_MSG_RESULT_H
#define TASK_MSG_RESULT_H

enum TASK_MSG_RESULT	// ������Ϣ���
{
	TMR_ERROR = 0,			// �������Ϣ���
	TMR_AUTO_RECYCLE = 1,	// ��ܻ��Զ����
	TMR_CONTINUE_PUT = 2,	// ����Ͷ�ݣ�Ӧ�ò㲻�����ֹ����

	TMR_SEND_TO_PEER = 3,	// �ط����Զˣ���ܻ��Զ������Ϣ�飬Ӧ�ò㲻�����ֹ����
	TMR_CLOSE_PEER = 4,		// �رնԶˣ���ܻ��Զ���أ�Ӧ�ò㲻�����ֹ����
};

#endif
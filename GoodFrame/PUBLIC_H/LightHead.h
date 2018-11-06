
/********************************************************************
	created:	2013/07/05
	created:	5:7:2013   20:36
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\LightHead.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	LightHead
	file ext:	h
	author:		�����ͷ�ļ�
	
	purpose:	����Ӧ���������ͻ���������Ľṹ
*********************************************************************/

#ifndef LIGHT_HEAD_H
#define LIGHT_HEAD_H

struct BASE_SERVER_CONFIG	// ����������ļ���Ϣ
{
	BASE_SERVER_CONFIG()
	{
		iServerPort=5150;
		sprintf(szDbIp, "127.0.0.1");
		iDbPort=3306;

		iTaskThreadNum = 6;
		iChannelBindThread = 0;	
		iIdleSpinUpLimit =  5;	
		iIdleSpinSleepTime = 1;	
	}

	int iServerPort;	// �������ļ����˿�
	char szDbIp[20];	// ���������ӵ����ݿ��Ip
	int iDbPort;	// ���������ӵ����ݿ�ļ����˿�

	int iTaskThreadNum;	// �����߳�����

	// true  ��ʾͨ���Ű��̣߳���һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݡ�
	// false ��ʾͨ���Ų����̣߳��߳���ͨ�����������Ӧ�ģ���һ��ͨ���ŵ����ݿ����ڶ���߳���ִ�У��޷���֤��ͨ���������ݵ��Ⱥ�˳�򣬻�����ȵ������ݻ���ִ�У��󵽵������Ѿ�ִ���������
	int iChannelBindThread;	

	int iIdleSpinUpLimit;	// ��ת���������ޣ�Ĭ��ֵ 5
	int iIdleSpinSleepTime;	// ��ת˯��ʱ�䣬�� ms Ϊ��λ��Ĭ��ֵ 1
};

struct BASE_CLIENT_CONFIG	// �ͻ��������ļ���Ϣ
{
	BASE_CLIENT_CONFIG()
	{
		sprintf(szServerIp, "127.0.0.1");
		iServerPort=5150;
	}

	char	szServerIp[20];		// Ҫ���ӵķ��������ӵ�Ip
	int		iServerPort;	// �ͻ���Ҫ���ӷ������Ķ˿�
};

#endif

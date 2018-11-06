
/********************************************************************
	created:	2013/07/05
	created:	5:7:2013   20:36
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\LightHead.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	LightHead
	file ext:	h
	author:		很轻的头文件
	
	purpose:	用于应付服务端与客户端最基本的结构
*********************************************************************/

#ifndef LIGHT_HEAD_H
#define LIGHT_HEAD_H

struct BASE_SERVER_CONFIG	// 服务端配置文件信息
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

	int iServerPort;	// 服务器的监听端口
	char szDbIp[20];	// 服务器连接的数据库的Ip
	int iDbPort;	// 服务器连接的数据库的监听端口

	int iTaskThreadNum;	// 任务线程数量

	// true  表示通道号绑定线程，即一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据。
	// false 表示通道号不绑定线程，线程与通道号是随机对应的，即一个通道号的数据可以在多个线程里执行，无法保证此通道号内数据的先后顺序，会出见先到的数据还在执行，后到的数据已经执行完毕啦。
	int iChannelBindThread;	

	int iIdleSpinUpLimit;	// 空转次数的上限，默认值 5
	int iIdleSpinSleepTime;	// 空转睡眠时间，以 ms 为单位，默认值 1
};

struct BASE_CLIENT_CONFIG	// 客户端配置文件信息
{
	BASE_CLIENT_CONFIG()
	{
		sprintf(szServerIp, "127.0.0.1");
		iServerPort=5150;
	}

	char	szServerIp[20];		// 要连接的服务器连接的Ip
	int		iServerPort;	// 客户端要连接服务器的端口
};

#endif

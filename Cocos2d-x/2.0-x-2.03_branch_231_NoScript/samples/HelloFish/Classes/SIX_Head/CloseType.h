/********************************************************************
	created:	2013/08/10
	created:	10:8:2013   11:47
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\CloseType.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	CloseType
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/


#ifndef CLOSE_TYPE_H
#define CLOSE_TYPE_H

enum CLOSE_TYPE	// �رշ�ʽ
{
	CLOSE_TYPE_NO = 0,					// ��ʼ�ǵ���Чֵ
	CLOSE_TYPE_CLIENT_CLOSE = 10,		// �ͻ��������ر�
	CLOSE_TYPE_FLASH_CLOSE = 20,		// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�
	CLOSE_TYPE_SERVER_POWER_CLOSE = 30,	// ����������رտͻ���
	CLOSE_TYPE_PACKAGE_ERR = 40,			// ͨѶ������
};

#endif
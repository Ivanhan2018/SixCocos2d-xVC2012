/*
 *  packet.h
 *  test
 *
 *  Created by Aden on 14-11-20.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEFINE_PACKET_H
#define DEFINE_PACKET_H
#pragma once
#include "common/Define.h"
#pragma pack(1)

/////////////////////////////////////////////////////////////////////
//�˿ڶ���
#define MAX_CONTENT			512							//��������
#define PORT_AUTO_SELECT	((WORD)(0XFFFF))			//�Զ��˿�

//#define IP_LOGON			"login1.91zjd.com"
//#define PORT_TEMP			9001
//#define IP_LOGON			"121.40.208.243"
#define IP_LOGON			"121.41.82.116"
#define PORT_TEMP			8300
//#define IP_LOGON			"117.18.5.229"
//#define PORT_TEMP			36856

//#define PORT_LOGON			8100						//��½�˿�  mojunxin
#define PORT_LOGON			8300						//��½�˿�
#define PORT_CENTER			8310						//Э���˿�
#define PORT_8311			8311						//���Զ˿�
#define PORT_MANAGER		8320						//����˿�

//#define DEFAULT_ACCOUNT		"phone"
//#define DEFAULT_PASSWORD	"hpkj12345!@#"
#define DEFAULT_ACCOUNT		"test009"
#define DEFAULT_PASSWORD	"123456"

/////////////////////////////////////////////////////////////////////
//���綨��

//��������
#define DK_MAPPED			0X01						//ӳ������
#define DK_ENCRYPT			0X02						//��������
#define DK_COMPRESS			0X04						//ѹ������

//���ȶ���
#define SOCKET_TCP_BUFFER	16384									//���绺��
#define SOCKET_TCP_PACKET	(SOCKET_TCP_BUFFER-sizeof(TCP_Head))	//���绺��


#pragma mark �ں�����
#define MDM_KN_COMMAND			0						//�ں�����
#define SUB_KN_DETECT_SOCKET	1						//�������
#define SUB_KN_VALIDATE_SOCKET	2						//��֤����
///////////////////////////////////////////////////////////////////////////
//�ṹ����
//������֤
typedef struct
{
	TCHART				szValidateKey[64];							//��֤�ַ�
}TCP_Validate;

#pragma pack()

#endif

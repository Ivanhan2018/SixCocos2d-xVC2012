#ifndef CMD_DATAMANAGE_H
#define CMD_DATAMANAGE_H


//#include "PublicMacro.h"
//#include <string.h>

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(1)



//////////////////////////////////////////////////////////////////////////
//��غ궨��

//////////////////////////////////////////////////////////////////////////////////
//��������������

///////////////////////////////////////////////////////////////////////////////

/**************************************************************************
//��̨���ݹ��������
**************************************************************************/
enum PROTOCOL_DATAMANAGE
{
	
	MAIN_DMS=20000,

	REQ_TEST_USER_INFO=400,//������
	REQ_TEST_USER_INFO_2,
    REQ_UPDATE_USER_DATA,// �޸��û�����
	
	RSP_TEST_USER_INFO=500,
	RSP_TEST_USER_INFO_2,
    RSP_UPDATE_USER_DATA_SUC,// �޸��û��������
	// Ϊ�˷�ֹ��ϢID�ظ�������ϢID��600��ʼ���ܴ��ڵ���2000 (��Ϊ��GameSkeletonMsgCode.h��Ҳ�õ���������Ϣ)
};

struct Req_TEST_USER_INFO	// ������
{
	Req_TEST_USER_INFO(){	memset(this, 0, sizeof(*this));	}
	int		iAge; 
	wchar_t	szName[128];
};

// �޸��û�����
struct Req_ModifyUserData
{
	Req_ModifyUserData()
	{
		memset(this,0,sizeof(*this));
	}
	int			iRet;									// ����ֵ(0��ȷ;!0����)
	long long	lUserID;								// �û�ID
	long long	lSyslogoid;								// ͷ��
	char			szNickName[33];						// �û��ǳ�
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
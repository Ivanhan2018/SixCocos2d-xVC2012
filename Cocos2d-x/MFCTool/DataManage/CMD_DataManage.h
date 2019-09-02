#ifndef CMD_DATAMANAGE_H
#define CMD_DATAMANAGE_H


//#include "PublicMacro.h"
//#include <string.h>

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(1)



//////////////////////////////////////////////////////////////////////////
//相关宏定义

//////////////////////////////////////////////////////////////////////////////////
//带语义数据类型

///////////////////////////////////////////////////////////////////////////////

/**************************************************************************
//后台数据管理服务器
**************************************************************************/
enum PROTOCOL_DATAMANAGE
{
	
	MAIN_DMS=20000,

	REQ_TEST_USER_INFO=400,//测试用
	REQ_TEST_USER_INFO_2,
    REQ_UPDATE_USER_DATA,// 修改用户资料
	
	RSP_TEST_USER_INFO=500,
	RSP_TEST_USER_INFO_2,
    RSP_UPDATE_USER_DATA_SUC,// 修改用户资料完成
	// 为了防止消息ID重复。此消息ID从600开始不能大于等于2000 (因为在GameSkeletonMsgCode.h中也用到了桌子消息)
};

struct Req_TEST_USER_INFO	// 测试用
{
	Req_TEST_USER_INFO(){	memset(this, 0, sizeof(*this));	}
	int		iAge; 
	wchar_t	szName[128];
};

// 修改用户资料
struct Req_ModifyUserData
{
	Req_ModifyUserData()
	{
		memset(this,0,sizeof(*this));
	}
	int			iRet;									// 返回值(0正确;!0错误)
	long long	lUserID;								// 用户ID
	long long	lSyslogoid;								// 头像
	char			szNickName[33];						// 用户昵称
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
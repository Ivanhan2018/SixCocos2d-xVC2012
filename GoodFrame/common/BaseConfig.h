/********************************************************************
	created:	2009/09/09
	created:	9:9:2009   9:33
	filename: 	e:\ACE_Program\Good_ACE\common\BaseConfig.h
	file path:	e:\ACE_Program\Good_ACE\common
	file base:	BaseConfig
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H


#include "./ace_head.h"
#include "./public_struct.h"

class CBaseConfig
{
public:
	CBaseConfig(void);
	~CBaseConfig(void);

	// 从客户端的配制文件中读取参数
	void read_client_config(char* szConfigName);

	// 从服务端的配制文件中读取参数
	void read_service_config(char* szConfigName);
public:
	BASE_CONFIG* GetBaseConfig();

private:
	BASE_CONFIG	m_BaseConfig;
};

#endif
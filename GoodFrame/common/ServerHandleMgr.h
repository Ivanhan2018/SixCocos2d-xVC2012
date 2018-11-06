
#ifndef SWRVICE_HANDLE_MGR_H
#define SWRVICE_HANDLE_MGR_H

#include "./ServerHandle.h"

// 通道（对端服务）管理
class __declspec(dllexport) CServerHandleMgr
{
public:
	CServerHandleMgr(void);
	~CServerHandleMgr(void);

public:
	// 增加一个对端服务
	LONGLONG add(CServerHandle* pServiceHandle);

	// 移除一个对端服务
	CServerHandle* remove_one(LONGLONG lChannelNo);

	// 移除所有的对端服务
	int remove_all(vector<CServerHandle*>& vecServiceHandle);

	// 由通道号获得对端服务指针
	CServerHandle* find(LONGLONG lChannelNo);

	// 指定的对端服务是否有效
	BOOL is_valid(LONGLONG lChannelNo);

private:
	typedef map<LONGLONG, CServerHandle*>	 MAP_TYPE;
	typedef pair <LONGLONG, CServerHandle*> PAIR_TYPE;	// 键值对

	MAP_TYPE	m_mapServiceHandle;	;

	CSRWLock	m_lock;		// 针对 m_mapServiceHandle 的锁

	LONGLONG volatile	m_lChannelNo;	// 通道号，映射对端服务，自增长，唯一的标识
};

#endif
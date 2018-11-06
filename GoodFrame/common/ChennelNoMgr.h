
/********************************************************************
	created:	2013/03/08
	created:	8:3:2013   13:21
	filename: 	E:\SVN_2013\GoodFrame\common\ChennelNoMgr.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	ChennelNoMgr
	file ext:	h
	author:		侯国江
	
	purpose:	通道号管理，在通讯中，通道号是唯一的64位长整数
*********************************************************************/

#ifndef CHENNEL_NO_MGR_H
#define CHENNEL_NO_MGR_H

#include "./ServerHandle.h"

// 通道号管理
class __declspec(dllexport) CChennelNoMgr
{
public:
	CChennelNoMgr(void);
	~CChennelNoMgr(void);

public:
	// 增加一个对端服务
	LONGLONG add(CServerHandle* pServerHandle);

	// 移除一个对端服务
	CServerHandle* remove_one(LONGLONG lChannelNo);

	// 移除一个对端服务
	int remove_one(CServerHandle* pServerHandle);

	// 移除所有的对端服务
	int remove_all(vector<CServerHandle*>& vecServerHandle);

	// 由通道号获得对端服务指针
	CServerHandle* find(LONGLONG lChannelNo);

	// 指定的对端服务是否有效
	BOOL is_valid(LONGLONG lChannelNo);

	// 获得所有有效的对端服务
	int get_all_valid(vector<CServerHandle*>& vecServerHandle);

	// 获得所有有效对端的通道号
	int get_all_valid(vector<LONGLONG>& vecChannelNo);

	// 增加一个主动关闭的对端
	int set_power_close_peer(LONGLONG lChannelNo);

	// 检查主动关闭对端超时
	int check_power_close_peer();

private:
	typedef hash_map<LONGLONG, CServerHandle*>	 MAP_TYPE;
	typedef pair <LONGLONG, CServerHandle*> PAIR_TYPE;	// 键值对

	MAP_TYPE	m_mapServerHandle;	

	CSRWLock	m_lock;		// 针对 m_mapServerHandle 的锁

	LONGLONG volatile	m_lChannelNo;	// 通道号，映射对端服务，自增长，唯一的标识
};

#endif
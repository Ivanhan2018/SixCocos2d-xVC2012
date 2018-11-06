
#ifndef SWRVICE_HANDLE_MGR_H
#define SWRVICE_HANDLE_MGR_H

#include "./ServerHandle.h"

// ͨ�����Զ˷��񣩹���
class __declspec(dllexport) CServerHandleMgr
{
public:
	CServerHandleMgr(void);
	~CServerHandleMgr(void);

public:
	// ����һ���Զ˷���
	LONGLONG add(CServerHandle* pServiceHandle);

	// �Ƴ�һ���Զ˷���
	CServerHandle* remove_one(LONGLONG lChannelNo);

	// �Ƴ����еĶԶ˷���
	int remove_all(vector<CServerHandle*>& vecServiceHandle);

	// ��ͨ���Ż�öԶ˷���ָ��
	CServerHandle* find(LONGLONG lChannelNo);

	// ָ���ĶԶ˷����Ƿ���Ч
	BOOL is_valid(LONGLONG lChannelNo);

private:
	typedef map<LONGLONG, CServerHandle*>	 MAP_TYPE;
	typedef pair <LONGLONG, CServerHandle*> PAIR_TYPE;	// ��ֵ��

	MAP_TYPE	m_mapServiceHandle;	;

	CSRWLock	m_lock;		// ��� m_mapServiceHandle ����

	LONGLONG volatile	m_lChannelNo;	// ͨ���ţ�ӳ��Զ˷�����������Ψһ�ı�ʶ
};

#endif
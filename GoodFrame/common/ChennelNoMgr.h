
/********************************************************************
	created:	2013/03/08
	created:	8:3:2013   13:21
	filename: 	E:\SVN_2013\GoodFrame\common\ChennelNoMgr.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	ChennelNoMgr
	file ext:	h
	author:		�����
	
	purpose:	ͨ���Ź�����ͨѶ�У�ͨ������Ψһ��64λ������
*********************************************************************/

#ifndef CHENNEL_NO_MGR_H
#define CHENNEL_NO_MGR_H

#include "./ServerHandle.h"

// ͨ���Ź���
class __declspec(dllexport) CChennelNoMgr
{
public:
	CChennelNoMgr(void);
	~CChennelNoMgr(void);

public:
	// ����һ���Զ˷���
	LONGLONG add(CServerHandle* pServerHandle);

	// �Ƴ�һ���Զ˷���
	CServerHandle* remove_one(LONGLONG lChannelNo);

	// �Ƴ�һ���Զ˷���
	int remove_one(CServerHandle* pServerHandle);

	// �Ƴ����еĶԶ˷���
	int remove_all(vector<CServerHandle*>& vecServerHandle);

	// ��ͨ���Ż�öԶ˷���ָ��
	CServerHandle* find(LONGLONG lChannelNo);

	// ָ���ĶԶ˷����Ƿ���Ч
	BOOL is_valid(LONGLONG lChannelNo);

	// ���������Ч�ĶԶ˷���
	int get_all_valid(vector<CServerHandle*>& vecServerHandle);

	// ���������Ч�Զ˵�ͨ����
	int get_all_valid(vector<LONGLONG>& vecChannelNo);

	// ����һ�������رյĶԶ�
	int set_power_close_peer(LONGLONG lChannelNo);

	// ��������رնԶ˳�ʱ
	int check_power_close_peer();

private:
	typedef hash_map<LONGLONG, CServerHandle*>	 MAP_TYPE;
	typedef pair <LONGLONG, CServerHandle*> PAIR_TYPE;	// ��ֵ��

	MAP_TYPE	m_mapServerHandle;	

	CSRWLock	m_lock;		// ��� m_mapServerHandle ����

	LONGLONG volatile	m_lChannelNo;	// ͨ���ţ�ӳ��Զ˷�����������Ψһ�ı�ʶ
};

#endif
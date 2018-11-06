#include "./PublicHead.h"
#include "./ServerHandleMgr.h"

CServerHandleMgr::CServerHandleMgr(void)
{
	m_lChannelNo = 0;
}

CServerHandleMgr::~CServerHandleMgr(void)
{
	CThreadGuardWrite guard(&m_lock);

	// �Ƴ����е�Ԫ��
	size_t sizeTmp = m_mapServiceHandle.size();

	m_mapServiceHandle.clear();
}

// ע�⣺����֮�䲻��Ƕ�ף���Ϊ CThreadGuardWrite ����Ƕ��

// �ܷ�� CServerHandle* �ĳ�������Ҳ�ŵ� CServerHandleMgr �������� ???

/* --------------------------------------------------------------------------
����˵��������һ���Զ˷���
���������
	pServiceHandle	�Զ˷���ָ��
����������
����ֵ��
    �ɹ��򷵻�ͨ���ţ����򷵻� INVALID_CHANNEL_NO ��
--------------------------------------------------------------------------*/
LONGLONG CServerHandleMgr::add(CServerHandle* pServiceHandle)
{
	CThreadGuardWrite guard(&m_lock);

	if(!pServiceHandle)
		return 10;

	::InterlockedIncrement64(&m_lChannelNo);	// ͨ���Զ��� 1 

	m_mapServiceHandle.insert(PAIR_TYPE(m_lChannelNo, pServiceHandle));

	return m_lChannelNo;
}

// �Ƴ�һ���Զ˷���
CServerHandle* CServerHandleMgr::remove_one(LONGLONG lChannelNo)
{
	CThreadGuardWrite guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServiceHandle = NULL;

	iter = m_mapServiceHandle.find(lChannelNo);

	if( iter != m_mapServiceHandle.end())	// �ҵ���
	{
		pServiceHandle = (CServerHandle*)(*iter).second;

		m_mapServiceHandle.erase(iter);	// �Ƴ�
	}

	return pServiceHandle;
}

/* --------------------------------------------------------------------------
����˵�����Ƴ����еĶԶ˷���
����������
	vecServiceHandle	���Ƴ��ĶԶ˷����б�
����ֵ��
    ���Ƴ��ĶԶ˷��������
--------------------------------------------------------------------------*/
int CServerHandleMgr::remove_all(vector<CServerHandle*>& vecServiceHandle)
{
	CThreadGuardWrite guard(&m_lock);

	CServerHandle* pServiceHandle = NULL;
	MAP_TYPE::iterator iter = m_mapServiceHandle.begin();
	int iCount = 0;

	// �Զ˷����б�ֵ
	for(; iter != m_mapServiceHandle.end(); iter++)
	{
		pServiceHandle = (CServerHandle*)(*iter).second;

		vecServiceHandle.push_back(pServiceHandle);

		iCount++;
	}

	return iCount;
}

// ��ͨ���Ż�öԶ˷���ָ��
CServerHandle* CServerHandleMgr::find(LONGLONG lChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServiceHandle = NULL;

	iter = m_mapServiceHandle.find(lChannelNo);

	if( iter != m_mapServiceHandle.end())	// �ҵ���
	{
		pServiceHandle = (CServerHandle*)(*iter).second;
	}

	return pServiceHandle;
}

// ָ���ĶԶ˷����Ƿ���Ч
BOOL CServerHandleMgr::is_valid(LONGLONG lChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServiceHandle = NULL;
	BOOL bValid = FALSE;

	iter = m_mapServiceHandle.find(lChannelNo);

	if( iter != m_mapServiceHandle.end())	// �ҵ���
	{
		pServiceHandle = (CServerHandle*)(*iter).second;
		bValid =  pServiceHandle->is_valid();
	}

	return bValid;
}
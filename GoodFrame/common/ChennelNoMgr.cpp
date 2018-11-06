#include "./PublicHead.h"
#include "./ChennelNoMgr.h"
#include "./CommTcpServer.h"

CChennelNoMgr::CChennelNoMgr(void)
{
	m_lChannelNo = 0;
}

CChennelNoMgr::~CChennelNoMgr(void)
{
	CThreadGuardWrite guard(&m_lock);

	// �Ƴ����е�Ԫ��
	size_t sizeTmp = m_mapServerHandle.size();

	m_mapServerHandle.clear();
}

// ע�⣺����֮�䲻��Ƕ�ף���Ϊ CThreadGuardWrite ����Ƕ��

// �ܷ�� CServerHandle* �ĳ�������Ҳ�ŵ� CChennelNoMgr �������� ???

/* --------------------------------------------------------------------------
����˵��������һ���Զ˷���
���������
	pServerHandle	�Զ˷���ָ��
����������
����ֵ��
    �ɹ��򷵻�ͨ���ţ����򷵻� INVALID_CHANNEL_NO ��
--------------------------------------------------------------------------*/
LONGLONG CChennelNoMgr::add(CServerHandle* pServerHandle)
{
	CThreadGuardWrite guard(&m_lock);

	if(!pServerHandle)
		return 10;

	::InterlockedIncrement64(&m_lChannelNo);	// ͨ���Զ��� 1 

	m_mapServerHandle.insert(PAIR_TYPE(m_lChannelNo, pServerHandle));

	return m_lChannelNo;
}

/* --------------------------------------------------------------------------
����˵�������������رյĶԶ�
���������
	pServerHandle	�Զ˷���ָ��
����������
����ֵ��
    �ɹ��򷵻�0�����򷵻ش����� ��
--------------------------------------------------------------------------*/
int CChennelNoMgr::set_power_close_peer(LONGLONG lChannelNo)
{
	CThreadGuardWrite guard(&m_lock);

	if(INVALID_CHANNEL_NO==lChannelNo)
		return 10;

	MAP_TYPE::iterator iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// �ҵ���
	{
		CServerHandle* pServerHandle = (CServerHandle*)(*iter).second;
		if(pServerHandle && pServerHandle->is_valid())
		{
			//printf("��Ҫɾ����ӡ:set_power_close_peer�˿ں� %d \n",lChannelNo);
			pServerHandle->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);	// ����������رտͻ���
			pServerHandle->m_iPowerClosePeerTime = ::GetTickCount64();
		}
	}

	return 0;
}

// ��������رնԶ˳�ʱ
int CChennelNoMgr::check_power_close_peer()
{
	vector<LONGLONG> vecOverTimePeer;	// ��ʱ�ĶԶ�����

	{
		CThreadGuardRead guard(&m_lock);	// ���á������ķ�ʽ�ҳ������رճ�ʱ�ĶԶˣ������ĺô����ٶȿ죬����������ġ�����

		LONGLONG lCurrent = GetTickCount64();	// ��ǰ��ʱ��
		CServerHandle* pServerHandle = NULL;

		MAP_TYPE::iterator iter = m_mapServerHandle.begin();

		for( ;  iter != m_mapServerHandle.end(); iter++ )
		{
			pServerHandle = (CServerHandle*)(*iter).second;

			if(pServerHandle->is_valid() &&					// �Զ���Ч
				pServerHandle->m_iPowerClosePeerTime>0 &&	// �����رնԶ˵�ʱ��Ϸ�
				lCurrent - pServerHandle->m_iPowerClosePeerTime > CCommTcpServer::INITIATIVE_CLOSE_PEER_OVER_TIME	// ��ʱ
				)	
			{
				LONGLONG lFirst = (*iter).first;

				vecOverTimePeer.push_back(lFirst);	// ���볬ʱ�ĶԶ�����
			}
		}
	}	// �������Զ����� m_lock

	{	// vecOverTimePeer.size() ������ĸ�����ʵ�ǲ���� 
		CThreadGuardWrite guard(&m_lock);
		int iSize = (int)vecOverTimePeer.size();
		if(iSize>0)
		{
			for(int i=0; i<iSize; i++)
			{
				LONGLONG lChannelNo = vecOverTimePeer[i];
				
				MAP_TYPE::iterator iter = m_mapServerHandle.find(lChannelNo);

				if( iter != m_mapServerHandle.end())	// �ҵ���
				{
					CServerHandle* pServerHandle = (CServerHandle*)(*iter).second;
					if(pServerHandle && pServerHandle->is_valid())
					{
						m_mapServerHandle.erase(iter);	// �Ƴ�

						//printf("��Ҫɾ����ӡ:check_power_close_peer�˿ں� %d \n",lChannelNo);
						pServerHandle->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
						pServerHandle->close(pServerHandle->get_close_type());			// ǿ�ƹر�
					}
				}
			}
		}
	}	// �������Զ����� m_lock


	return 0;
}

// �Ƴ�һ���Զ˷���
CServerHandle* CChennelNoMgr::remove_one(LONGLONG lChannelNo)
{
	CThreadGuardWrite guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServerHandle = NULL;

	iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// �ҵ���
	{
		pServerHandle = (CServerHandle*)(*iter).second;
		m_mapServerHandle.erase(iter);	// �Ƴ�
	}

	return pServerHandle;
}

// �Ƴ�һ���Զ˷���
int CChennelNoMgr::remove_one(CServerHandle* pServerHandle)
{
	CThreadGuardWrite guard(&m_lock);

	int iResult = 10;
	CServerHandle* pTmp = NULL;
	MAP_TYPE::iterator iter = m_mapServerHandle.begin();
	int iCount = 0;

	// �Զ˷����б�ֵ
	for(; iter != m_mapServerHandle.end(); iter++)
	{
		pTmp = (CServerHandle*)(*iter).second;

		if(pTmp == pServerHandle && pTmp->is_valid())
		{
			m_mapServerHandle.erase(iter);
			return 0;
		}
	}

	return iResult;
}

// ��ͨ���Ż�öԶ˷���ָ��
CServerHandle* CChennelNoMgr::find(LONGLONG lChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServerHandle = NULL;

	iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// �ҵ���
	{
		pServerHandle = (CServerHandle*)(*iter).second;
	}

	return pServerHandle;
}

// ָ���ĶԶ˷����Ƿ���Ч
BOOL CChennelNoMgr::is_valid(LONGLONG lChannelNo)
{
	if(INVALID_CHANNEL_NO==lChannelNo)
		return FALSE;

	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServerHandle = NULL;
	BOOL bValid = FALSE;

	iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// �ҵ���
	{
		pServerHandle = (CServerHandle*)(*iter).second;
		bValid =  pServerHandle->is_valid();
	}

	return bValid;
}

/* --------------------------------------------------------------------------
����˵�������������Ч�ĶԶ˷���
����������
	vecServerHandle	��Ч�ĶԶ˷�����б�
����ֵ��
    ��Ч�ĶԶ˷��������
--------------------------------------------------------------------------*/
int CChennelNoMgr::get_all_valid(vector<CServerHandle*>& vecServerHandle)
{
	CThreadGuardRead guard(&m_lock);

	CServerHandle* pServerHandle = NULL;
	MAP_TYPE::iterator iter = m_mapServerHandle.begin();
	int iCount = 0;

	// �Զ˷����б�ֵ
	for(; iter != m_mapServerHandle.end(); iter++)
	{
		pServerHandle = (CServerHandle*)(*iter).second;

		if(pServerHandle->is_valid())
		{
			vecServerHandle.push_back(pServerHandle);
			iCount++;
		}
	}

	return iCount;
}


/* --------------------------------------------------------------------------
����˵�������������Ч�Զ˵�ͨ����
����������
	vecChannelNo	��Ч�Զ˵�ͨ��������
����ֵ��
    ��Ч�ĶԶ˷��������
--------------------------------------------------------------------------*/
int CChennelNoMgr::get_all_valid(vector<LONGLONG>& vecChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	LONGLONG lChannelNo = INVALID_CHANNEL_NO;
	CServerHandle* pServerHandle = NULL;

	MAP_TYPE::iterator iter = m_mapServerHandle.begin();
	int iCount = 0;

	// �Զ˷����б�ֵ
	for(; iter != m_mapServerHandle.end(); iter++)
	{
		lChannelNo = (LONGLONG)(*iter).first;
		pServerHandle = (CServerHandle*)(*iter).second;

		if(pServerHandle->is_valid())
		{
			vecChannelNo.push_back(lChannelNo);
			iCount++;
		}
	}

	return iCount;
}

#include "PublicHead.h"
#include "FishTable.h"	// ����Ǳ����Ϸ����ĳ���Ӧ�����ּ���
#include "PartMgr.h"

CPartMgr::CPartMgr(void)
{
	m_pTable = NULL;
}

CPartMgr::~CPartMgr(void)
{
}

// ����
void CPartMgr::test()
{
	{
		// �������ڱ���������Ч���������ž��Զ�������
		CThreadGuardRead guard(&m_lock);	// ֻ������������Ŀ��ı�������ȡ
	}

	{
		// �������ڱ���������Ч���������ž��Զ�������
		CThreadGuardWrite guard(&m_lock);	// д����������Ŀ�������ɾ����
	}
}

// ��������ָ��
void CPartMgr::set_fish_table(CFishTable* pTable)
{
	m_pTable = pTable;
}

//��ȡ����ָ��
CFishTable* CPartMgr::get_fish_table()const
{
	return (CFishTable*)m_pTable;
}


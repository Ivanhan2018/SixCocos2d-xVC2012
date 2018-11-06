
#ifndef LITTLE_PART_H
#define LITTLE_PART_H

#include "./ThreadGuardEx.h"
class CFishTable;//add by Ivan_han 20130608

// С���������켣�����ࡢ�ӵ�������ĸ���
class CPartMgr
{
public:
	CPartMgr(void);
	~CPartMgr(void);

	// ����
	void test();

	// ��������ָ��
	void set_fish_table(CFishTable* pTable);

	//��ȡ����ָ��
	CFishTable* get_fish_table()const;

protected:
	CFishTable*		m_pTable;
	CSRWLock	m_lock;
};

#endif
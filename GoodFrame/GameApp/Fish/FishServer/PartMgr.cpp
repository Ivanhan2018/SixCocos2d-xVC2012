
#include "PublicHead.h"
#include "FishTable.h"	// 如果是别的游戏，则改成相应的名字即可
#include "PartMgr.h"

CPartMgr::CPartMgr(void)
{
	m_pTable = NULL;
}

CPartMgr::~CPartMgr(void)
{
}

// 测试
void CPartMgr::test()
{
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardRead guard(&m_lock);	// 只读锁，用于锁目标的遍历、读取
	}

	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
	}
}

// 设置桌子指针
void CPartMgr::set_fish_table(CFishTable* pTable)
{
	m_pTable = pTable;
}

//获取桌子指针
CFishTable* CPartMgr::get_fish_table()const
{
	return (CFishTable*)m_pTable;
}


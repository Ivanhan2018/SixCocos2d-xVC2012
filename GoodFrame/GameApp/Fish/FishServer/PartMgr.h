
#ifndef LITTLE_PART_H
#define LITTLE_PART_H

#include "./ThreadGuardEx.h"
class CFishTable;//add by Ivan_han 20130608

// 小零件，是鱼轨迹管理类、子弹管理类的父类
class CPartMgr
{
public:
	CPartMgr(void);
	~CPartMgr(void);

	// 测试
	void test();

	// 设置桌子指针
	void set_fish_table(CFishTable* pTable);

	//获取桌子指针
	CFishTable* get_fish_table()const;

protected:
	CFishTable*		m_pTable;
	CSRWLock	m_lock;
};

#endif
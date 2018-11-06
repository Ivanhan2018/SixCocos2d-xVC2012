/********************************************************************
	created:	2013/06/21
	created:	21:6:2013   15:49
	filename: 	E:\SixDivisions\GoodFRame\common\EndlessLoopGuard.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	EndlessLoopGuard
	file ext:	h
	author:		侯国江
	
	purpose:	死循环守护
*********************************************************************/

#ifndef ENDLESS_LOOP_GUARD_EX_H
#define ENDLESS_LOOP_GUARD_EX_H

// 1 表示开启死循环监测，0 表示禁止死循环监测
// 注意：开启死循环监测对性能的影响比较大，不到迫不得已时不要开启死循环监测
#define CHECK_ENDLESS_LOOP 1 

#include "./ThreadGuard.h"

#include <hash_map>
#include <vector>
#include <string>
using std::hash_map;
using std::pair;
using std::vector;
using std::string;

#include "./Singleton.h"

class __declspec(dllexport) CEndlessLoop;
class __declspec(dllexport) CEndlessLoopGuard;

struct ENDLESS_LOOP_INFO	// 死循环参数
{
	ENDLESS_LOOP_INFO()
	{
		lEnterTime = 0;
		lDisplayTime = 0;
		strSignName.empty();
	}

	long long lEnterTime;	// 进入守护的时间
	long long lDisplayTime;	// 列印所有的守护的时间
	string strSignName;		// 标记点的名称，可以用函数名或循环名作为标记点的名称
};

typedef	hash_map<CEndlessLoopGuard*, ENDLESS_LOOP_INFO>	MAP_ENDLESS_LOOP; 	// 
typedef pair <CEndlessLoopGuard*, ENDLESS_LOOP_INFO>		PAIR_ENDLESS_LOOP;	// 键值对

// 死循环
class __declspec(dllexport) CEndlessLoop : public CSingleton<CEndlessLoop>
{
public:
	friend class CEndlessLoopGuard;

public:
	CEndlessLoop();
	~CEndlessLoop();
	
	// 返回关键代码段
	inline CCriticalSpection*	get_lock();

	// 获得引用计数器的值，方便查询因嵌套而引发的死锁
	long long	get_count();

	// 列印所有的死循环、死锁
	int display_all_guard(bool bDiaplay, vector<ENDLESS_LOOP_INFO>& vecEndlessLoopInfo);

public:
	long long lCount;	// 引用计数器

private:
	CCriticalSpection	m_lock;	// 锁

	MAP_ENDLESS_LOOP	m_mapGuard;	// 所有的守护者
};

///////////////////////////////////////////////////////////////////////////////////

// 死循环守护
class __declspec(dllexport) CEndlessLoopGuard
{
public:

	CEndlessLoopGuard(CEndlessLoop* pLoop, char* pszSignName);

	~CEndlessLoopGuard(void);

public:
	int test();

protected:

	// 初始化与销毁都已在类中自动进行，优点：万一程序在解锁前return了或异常了，会通过析构自我解锁
	CEndlessLoop*	m_pEndlessLoop;

	bool		m_bEnterState;	// true  表示 m_pEndlessLoop 处于 进锁 状态，
								// false 表示 m_pEndlessLoop 处于 离锁 状态
};

#endif

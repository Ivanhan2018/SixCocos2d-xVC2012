/********************************************************************
	created:	2013/06/21
	created:	21:6:2013   15:49
	filename: 	E:\SixDivisions\GoodFRame\common\EndlessLoopGuard.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	EndlessLoopGuard
	file ext:	h
	author:		�����
	
	purpose:	��ѭ���ػ�
*********************************************************************/

#ifndef ENDLESS_LOOP_GUARD_EX_H
#define ENDLESS_LOOP_GUARD_EX_H

// 1 ��ʾ������ѭ����⣬0 ��ʾ��ֹ��ѭ�����
// ע�⣺������ѭ���������ܵ�Ӱ��Ƚϴ󣬲����Ȳ�����ʱ��Ҫ������ѭ�����
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

struct ENDLESS_LOOP_INFO	// ��ѭ������
{
	ENDLESS_LOOP_INFO()
	{
		lEnterTime = 0;
		lDisplayTime = 0;
		strSignName.empty();
	}

	long long lEnterTime;	// �����ػ���ʱ��
	long long lDisplayTime;	// ��ӡ���е��ػ���ʱ��
	string strSignName;		// ��ǵ�����ƣ������ú�������ѭ������Ϊ��ǵ������
};

typedef	hash_map<CEndlessLoopGuard*, ENDLESS_LOOP_INFO>	MAP_ENDLESS_LOOP; 	// 
typedef pair <CEndlessLoopGuard*, ENDLESS_LOOP_INFO>		PAIR_ENDLESS_LOOP;	// ��ֵ��

// ��ѭ��
class __declspec(dllexport) CEndlessLoop : public CSingleton<CEndlessLoop>
{
public:
	friend class CEndlessLoopGuard;

public:
	CEndlessLoop();
	~CEndlessLoop();
	
	// ���عؼ������
	inline CCriticalSpection*	get_lock();

	// ������ü�������ֵ�������ѯ��Ƕ�׶�����������
	long long	get_count();

	// ��ӡ���е���ѭ��������
	int display_all_guard(bool bDiaplay, vector<ENDLESS_LOOP_INFO>& vecEndlessLoopInfo);

public:
	long long lCount;	// ���ü�����

private:
	CCriticalSpection	m_lock;	// ��

	MAP_ENDLESS_LOOP	m_mapGuard;	// ���е��ػ���
};

///////////////////////////////////////////////////////////////////////////////////

// ��ѭ���ػ�
class __declspec(dllexport) CEndlessLoopGuard
{
public:

	CEndlessLoopGuard(CEndlessLoop* pLoop, char* pszSignName);

	~CEndlessLoopGuard(void);

public:
	int test();

protected:

	// ��ʼ�������ٶ����������Զ����У��ŵ㣺��һ�����ڽ���ǰreturn�˻��쳣�ˣ���ͨ���������ҽ���
	CEndlessLoop*	m_pEndlessLoop;

	bool		m_bEnterState;	// true  ��ʾ m_pEndlessLoop ���� ���� ״̬��
								// false ��ʾ m_pEndlessLoop ���� ���� ״̬
};

#endif

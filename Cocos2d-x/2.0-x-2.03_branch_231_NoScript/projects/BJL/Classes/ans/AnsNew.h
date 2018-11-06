/*
** overload new operator to trace the new and delete operation
** author: zhouwei
** date: 2012.10.22
*/

#ifndef __ANS_NEW_H__
#define __ANS_NEW_H__

#include <new>
#include <fstream>
#include "AnsDebug.h"

#if defined(_WIN32) && defined(__ANS_DEBUG)
namespace ans{
namespace debug{
// -----------------------------------------------------------------------
// inners
// -----------------------------------------------------------------------
void addNewTrack(void*, const char*, unsigned);
void removeNewTrack(void*);

// -------------------------------------------------------------
// ���û��ɾ���� new ������undbl ��ʾ������ظ���
void dumpUnfree(std::ofstream&, bool undbl=true);

// ���ַ�����ʽ����ûɾ�� new ������undbl ��ʾ��¼���ظ���
std::string getUnfreeInfo(bool undbl=true);

}}

// -----------------------------------------------------------------------
// overload new/delete and new[]/delete[] operator
// -----------------------------------------------------------------------
inline void* operator new(unsigned size, const char* file, unsigned line)
{
	void* p = (void*)malloc(size);
	ans::debug::addNewTrack(p, file, line);
	return p;
}

inline void operator delete(void* p, const char* file, unsigned line){}
inline void operator delete(void* p)
{
	if(p)
	{
		ans::debug::removeNewTrack(p);
		free(p);
	}
}

inline void* operator new[](unsigned size, const char* file, unsigned line)
{
	void* p = (void*)malloc(size);
	ans::debug::addNewTrack(p, file, line);
	return p;
}

inline void operator delete[](void* p, const char* file, unsigned line){}
inline void operator delete[](void* p)
{
	if(p)
	{
		ans::debug::removeNewTrack(p);
		free(p);
	}
}


#endif // __ANS_DEBUG
#endif // __ANS_NEW_H__
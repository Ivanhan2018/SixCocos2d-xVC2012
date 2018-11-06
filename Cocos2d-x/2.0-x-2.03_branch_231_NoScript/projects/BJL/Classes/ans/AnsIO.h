/*
** implement functions for io
** author: zhouwei
** date: 2012.10.25
*/

#ifndef __ANS_IO_H__
#define __ANS_IO_H__

#include <string>
using namespace std;

namespace ans{
namespace AnsIO{
	// -------------------------------------------------------------------
	// �����ļ��л��ļ�
	// ��� path Ϊ��aa/bb/cc/ ��ֻ����·������� path Ϊ��aa/bb/cc �򴴽��ļ� cc
	// ��������ɹ���·��/�ļ��Ѿ������򷵻� true
	// -------------------------------------------------------------------
	bool mkpath(const char* path, unsigned mode=0777);
	inline bool mkpath(const string& path, unsigned mode=0777){ return mkpath(path.c_str(), mode); }
}}

#endif
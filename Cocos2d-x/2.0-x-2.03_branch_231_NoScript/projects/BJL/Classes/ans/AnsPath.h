/*
** implement functions for path
** author: zhouwei
** date: 2012.10.15
*/

#ifndef __ANS_PATH_H__
#define __ANS_PATH_H__

#include <string>

using namespace std;

namespace ans{
namespace AnsPath{

	extern const char* PATH_SPLITTER;		// ·���ָ���
	extern const char* PATH_ANTI_SPLITTER;	// ����·���ָ���

	// -------------------------------------------------------------------
	// ����ļ�·�����ļ���
	// ������
	//     path    : ���·��
	//     pathSize: ���·�������С
	//     name    : ����ļ���
	//     nameSize: ����ļ��������С
	//     filePath: �����ļ�����·��
	// �磺aa\bb\cc\dd\ee.txt ���� split ��
	//     path == aa\bb\cc\dd 
	//     name == ee.txt
	// -------------------------------------------------------------------
	void split(char* path, size_t pathSize, char* name, size_t nameSize, const char* filePath);
	void split(string& path, string& name, const char* filePath);
	void split(string& path, string& name, const string& filePath);

	// -------------------------------------------------------------------
	// ��׼��һ��·��
	// ���� Windows ƽ̨��·����
	//     c:\abc\def\ghi/jkl\mno\..\\pqr///stu\vwx\ ��׼���󽫱�Ϊ��c:\abc\def\ghi\jkl\pqr\stu\vwx\
	//     ../aa/bb/cc//dd.txt ��׼����Ϊ��../aa/bb/cc/dd.txt 
	// -------------------------------------------------------------------
	string normalizePath(const string& path);
	string& normalizePath(string& path);

}
}

#endif
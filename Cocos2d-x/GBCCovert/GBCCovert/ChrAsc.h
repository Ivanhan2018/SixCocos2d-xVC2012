#if !defined(CHR_ASC_H)
#define CHR_ASC_H

#include <windows.h>
#include <string>
using namespace std;

/*
	�ַ������е�Asc��Chr��Ӧ���ֵ�GBK�루ע�����ֵΪ����������65536�ͺͺ�������鿴���е�GBK����һ���ˣ�
	�ַ������е�AscW��ChrW��Ӧ���ֵ�Unicode��

*/

//�����루�뺺�ֵ�GBK����һ�£����һ�ַ������һ����
const char * ChrFromAnsi(short CharCode);

//���ַ�������
short AscFromChr(const char *str);

//��wstring���͵��ַ�����ת����string
string WstringToString(wstring source);

//ת��string��wstring
wstring StringToWstring(string source);

#endif

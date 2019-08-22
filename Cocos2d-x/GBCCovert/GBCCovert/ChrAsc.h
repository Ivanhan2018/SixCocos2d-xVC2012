#if !defined(CHR_ASC_H)
#define CHR_ASC_H

#include <windows.h>
#include <string>
using namespace std;

/*
	字符编码中的Asc和Chr对应汉字的GBK码（注意编码值为负数，加上65536就和汉字内码查看器中的GBK内码一致了）
	字符编码中的AscW和ChrW对应汉字的Unicode码

*/

//由内码（与汉字的GBK内码一致）求得一字符，多对一函数
const char * ChrFromAnsi(short CharCode);

//求字符的内码
short AscFromChr(const char *str);

//将wstring类型的字符串，转换成string
string WstringToString(wstring source);

//转换string到wstring
wstring StringToWstring(string source);

#endif

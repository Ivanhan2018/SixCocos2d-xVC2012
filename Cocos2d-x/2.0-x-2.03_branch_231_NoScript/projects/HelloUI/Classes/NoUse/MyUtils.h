#if !defined(MyUtils_H)
#define MyUtils_H

#include <platform\third_party\win32\iconv\iconv.h>
#include <io.h>
#include <string>
using namespace std;

#ifdef WIN32
#pragma comment(lib,"libiconv.lib")
#endif

typedef float(*FPf)(float x);
float TxIntf(float(*fun)(float x),float a,float b,int n);

unsigned int Add(unsigned int a,unsigned int b);
string NumberTostring(int Num);
string BytesToStr(unsigned char bt[],int nSize);
bool file_exists(const char *filename);
const char * GetResWithID(int ID);

int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
std::string U2G(const char *inbuf);
std::string G2U(const char *inbuf);

#endif // !defined(MyUtils_H)

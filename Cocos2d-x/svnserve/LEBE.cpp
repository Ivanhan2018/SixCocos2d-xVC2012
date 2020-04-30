#include <iostream>
using namespace std;

int main()
{
	unsigned int i = 0x11112222;
	unsigned char * p = (unsigned char *)&i;
	if(*p == 0x22)
	{
		//Intel系列CPU采用Little Endian存储格式来存放基本类型变量
		printf("小端This is little endian system\n");
	}
	else
	{
		printf("大端This is big endian system\n");
	} 
	return 0;
}
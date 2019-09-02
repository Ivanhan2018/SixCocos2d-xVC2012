#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define D3DVS_VERSION(Major,Minor) (0xfffe0000|((Major)<<8)|(Minor))
#define D3DPS_VERSION(Major,Minor) (0xffff0000|((Major)<<8)|(Minor))

int main()
{
	unsigned long dwVSV=D3DVS_VERSION(2,0);
	assert(0xfffe0300>=dwVSV);
	unsigned long dwVSV1=D3DVS_VERSION(1,1);
	assert(0xfffe0300>=dwVSV1);
	unsigned long dwVSV2=D3DVS_VERSION(3,0);
	assert(0xfffe0300>=dwVSV2);

	unsigned long dwPSV=D3DPS_VERSION(2,0);
	assert(0xffff0300>=dwPSV);
	unsigned long dwPSV1=D3DPS_VERSION(1,4);
	assert(0xffff0300>=dwPSV1);

        printf("dwVSV=%u,dwVSV1=%u,dwVSV2=%u,dwPSV=%u,dwPSV1=%u\n",dwVSV,dwVSV1,dwVSV2,dwPSV,dwPSV1);

        printf("dwVSV=%d,dwVSV1=%d,dwVSV2=%d,dwPSV=%d,dwPSV1=%d\n",dwVSV,dwVSV1,dwVSV2,dwPSV,dwPSV1);

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}

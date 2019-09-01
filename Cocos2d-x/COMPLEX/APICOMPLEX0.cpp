#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#pragma comment(lib,"user32.lib")

int main(int argc, char* argv[])
{
	printf("����Complex.dll�����������API!\n");

	char sz[100]={0};
	char sz1[100]={0};
	char sz2[100]={0};
	if(argc<2)
	{
		printf("�����빦�ܺ�(1VC�⸴����ģ��2�Զ���⸴����ģ)��");
		scanf("%s",sz);
	}
	else
		strcpy(sz,argv[1]);
	if(argc<3)
	{
		printf("�������1��������ʵ����");
		scanf("%s",sz1);
	}
	else
		strcpy(sz1,argv[2]);
	if(argc<4)
	{
		printf("�������1���������鲿��");
		scanf("%s",sz2);
	}
	else
		strcpy(sz2,argv[3]);

	struct Complex
	{
		double x;
		double y;
	}cpxZ;

	cpxZ.x = atof(sz1);
	cpxZ.y = atof(sz2);

	int ifunc=atoi(sz);
	if(ifunc==1)
	{
		typedef double(*pR)(struct Complex);
		HINSTANCE hLib = LoadLibrary("MSVCRT.DLL");
		if(hLib)
		{
			pR R;
			R=(pR)GetProcAddress(hLib,"_cabs");
			printf("%f\n",R(cpxZ));
			FreeLibrary(hLib);
			::MessageBox(NULL,"����VC����㸴��ģ���", "", MB_OK) ;
		}
	}
	else if(ifunc==2)
	{
		//typedef double(*pR)(struct Complex *);
		typedef double(_stdcall *pR)(struct Complex *);
		HINSTANCE hLib = LoadLibrary("APIComplex.dll");
		if(hLib)
		{
			pR R;
			R=(pR)GetProcAddress(hLib,"_CAbs@4");
			printf("%f\n",R(&cpxZ));
			FreeLibrary(hLib);
			::MessageBox(NULL,"�����Զ������㸴��ģ���", "", MB_OK) ;
		}
	}

	system("pause");
	return 0;
}

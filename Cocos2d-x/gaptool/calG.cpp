#include "GroupUtil.h"

// 根据群的凯莱表分析其结构的小工具calG.exe


int main(int argc, char **argv)
{
	char sz[100]={0};
	char sz1[100]={0};
	char sz2[100]={0};
	if(argc<2)
	{
		printf("请输入群A凯莱表文件名：");
		scanf("%s",sz);
	}
	else
		strcpy(sz,argv[1]);
	if(argc<3)
	{
#if defined(_WIN32)||defined(_WIN64)
		_splitpath(sz,0,0,sz1,0);
#else
                //sscanf(sz,"./%s.txt",sz1);
                char *fn=GroupUtil::find_file_name(sz);
                strcpy(sz1,fn);
                printf("%s\n",sz1);
                GroupUtil::filter_ext_name(sz1);
                printf("%s\n",sz1);
#endif
		string strDes=sz;
		string strFn=sz1;
		strFn+="_ElementToOrder";
		strcpy(sz2,sz1);
		strDes.replace(strDes.find(sz1,0),strlen(sz1),strFn.c_str());
		strcpy(sz1,strDes.c_str());
	}
	else
		strcpy(sz1,argv[2]);

	char szFlag[100]={0};
        int iFlag=0;// 非0表示要计算群的最小生成元集、秩
	if(argc>=4)
	{
		strcpy(szFlag,argv[3]);
		iFlag=atoi(szFlag);
	}

	bool bret=GroupUtil::SaveGnEOrder(sz,sz1,sz2,iFlag);
	if(bret)
	{
		//MessageBoxA(NULL,"分析群的结构完毕！","提示",MB_OK);
                printf("分析群的结构完毕！\n");
	}

	//system("pause");
	return 0;
}
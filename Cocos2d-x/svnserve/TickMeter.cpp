#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class TickMeter
{
public:
	TickMeter(const char *szName);
	~TickMeter();
	// 微秒级的时钟周期
	clock_t getTimeElapsed();
private:
    clock_t  clockBegin, clockEnd;
	string strName;
};

TickMeter::TickMeter(const char *szName)
{
	clockBegin = clock();
    if(szName)strName=szName;	
}

TickMeter::~TickMeter()
{
	clockEnd = clock();
	printf("%s 用时 %d(%f秒)\n",strName.c_str(),(clockEnd - clockBegin),(clockEnd - clockBegin)*1.0/CLOCKS_PER_SEC); 
}

clock_t TickMeter::getTimeElapsed()
{
	clock_t	cur = clock();
	return (cur - clockBegin);
}

// n个整数冒泡升序排序
void pibub(int *p,int n)
{ 
	int m,k,j,i,d;
	k=0; m=n-1;
	while (k<m)
	{ 
		j=m-1; m=0;
		for (i=k; i<=j; i++)
		if (p[i]>p[i+1])
		{ 
			d=p[i]; 
			p[i]=p[i+1]; 
			p[i+1]=d; 
			m=i;
		}
		j=k+1; 
		k=0;
		for (i=m; i>=j; i--)
		if (p[i-1]>p[i])
		{ 
			d=p[i]; 
			p[i]=p[i-1]; 
			p[i-1]=d; 
			k=i;
		}
	}
	return;
}

void pibub(int *p,int n,int ascending)//ascending=1表示升序，0表示降序
{
	int temp,i,j;
	if(ascending)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<i;j++)
			{
				if(p[j]>p[i])//选择升序排序
				{
					temp=p[i];
					//插入
					for(int k=i;k>=j;k--)p[k]=p[k-1];
					p[j]=temp;
				}
			}
			// printf("\n");
			// printf("A[i=%d]=",i);
			// for(int k=0;k<n;k++) 
				// printf("%d",p[k]);
		}
	}
	else
	{
		for(i=0;i<n-1;i++)
		{
			for(j=0;j<n-1;j++)
				if(p[j]<p[j+1])//选择降序
				{
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
				}
		}
	}
}

void pibub1(int *p,int n)
{
	pibub(p,n,1);	
}


// 希尔排序
void pishl(int *p,int n)
{ 
	int k,j,i,t;
	k=n/2;
	while (k>0)
	{ 
		for (j=k; j<=n-1; j++)
		{ 
			t=p[j]; 
			i=j-k;
			while ((i>=0)&&(p[i]>t))
			{ 
				p[i+k]=p[i]; 
				i=i-k;
			}
			p[i+k]=t;
		}
		k=k/2;
	}
	return;
}

void stlsort(int *p,int n)
{
	//sort(p,p+n);//升序排列
	sort(p,p+n,less<int>());//升序排列
}

void quickSort(int *arr,int startPos, int endPos)  
{  
	int i,j;  
	int ch;  
	ch=arr[startPos];  
	i=startPos;  
	j=endPos;  
	while(i<j)  
	{  
		while(arr[j]>=ch && i<j)--j;  
		arr[i]=arr[j];  
		while(arr[i]<=ch && i<j)++i;  
		arr[j]=arr[i];  
	}  
	arr[i]=ch;  
	if(i-1>startPos) quickSort(arr,startPos,i-1);  
	if(endPos>i+1) quickSort(arr,i+1,endPos);  
}

void piqck(int *p,int n)
{
	quickSort(p,0,n-1);
}

vector<int> createInputArr(int n)
{
	vector<int> v(n);
	for(int i=0;i<n;i++)
		v[i]=rand();
	return v;
}

typedef void(*pR)(int *p,int n);
pR pFunc[]={pibub,pibub1,pishl,stlsort,piqck};
const char *szName[]={"冒泡排序","冒泡排序1","希尔排序","stl标准排序","快速排序"}; 

void Print(const char *szName,vector<int>& tlVect) 
{
    return;
    if(tlVect.size()>10)
		return;
	printf("%s容器中的元素为: ",szName);
	for (int i = 0; i < tlVect.size(); i++) {
		printf("%d,",tlVect[i]); 
	}

	printf("\n"); 
}

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		printf("Usage:  TickMeter n [-w][-g](eg:n=1000)\n");
		return 1;
	}
    printf("CLOCKS_PER_SEC=%d\n",CLOCKS_PER_SEC);	
	int n=atoi(argv[1]);
    int m=sizeof(pFunc)/sizeof(pFunc[0]);
	vector<int> v0=createInputArr(n);
	vector<int> vg=v0;	
	sort(vg.begin(),vg.end(),less<int>());//升序排列
	// 快速排序在完全逆序的情况下等价于冒泡排序，这时其他方法就比它快。
	vector<int> vw=v0;
	sort(vw.begin(),vw.end(),greater<int>());//降序排列	
	vector<int> *vArr[]={&v0,&vg,&vw};
	const char *szVName[]={"平均情况下","最好情况下","最坏情况下"}; 
	Print("v0",v0);
	Print("vg",vg);
	Print("vw",vw);	
	for(int j=0;j<3;j++)
    for(int i=0;i<m;i++)	
	{
		string str=szVName[j];
		str+=szName[i];
		TickMeter tm(str.c_str());
		vector<int> v=*vArr[j];
		pFunc[i](&v[0],n);
		clock_t s=tm.getTimeElapsed();
		Print(str.c_str(),v);
	}
    return 0;
}
	
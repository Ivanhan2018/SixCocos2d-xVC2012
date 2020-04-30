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

vector<int> createInputArr(int n)
{
	vector<int> v(n);
	for(int i=0;i<n;i++)
		v[i]=rand()%n;
	return v;
}

/*Try to find the max one in the list and return it*/
//求n个不同整数中的最大元算法,比较次数: N-1
int find_max(int * list, int n)
{
        int i = 1, max;
        max = list[0];
        while(i < n)
        {
                if(max < list[i])
                {
                        max = list[i];
                }
                i ++;
        }
        return max;
}

int stl_find_max(int * list, int n)
{
	int ret= *max_element(list, list + n);//最大元素
	return ret;
}

// find maximum of n numbers
template<class T>
T Max(T *a, int n)
{// Locate the largest element in a[0:n-1].
   int pos = 0;
   for (int i = 1; i < n; i++)
     if (a[pos] < a[i])
        pos = i;
   return a[pos];
}

typedef int(*pR)(int *p,int n);
pR pFunc[]={find_max,stl_find_max,Max<int>};
const char *szName[]={"求最大元素","stl泛型算法求最大元素","模板函数求最大元素"}; 

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
    int m=sizeof(szName)/sizeof(szName[0]);
	vector<int> v0=createInputArr(n);
	vector<int> *vArr[]={&v0};
	const char *szVName[]={"求最值元素的时间复杂度O(n)"}; 
	Print("v0",v0);
	for(int j=0;j<1;j++)
    for(int i=0;i<m;i++)	
	{
		string str=szVName[j];
		str+=szName[i];
		TickMeter tm(str.c_str());
		vector<int> v=*vArr[j];
		int ret=pFunc[i](&v[0],n);
		clock_t s=tm.getTimeElapsed();
		Print(str.c_str(),v);
		printf("ret=%d",ret);
	}
    return 0;
}
	
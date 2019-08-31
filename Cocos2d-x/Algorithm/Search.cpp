#include <iostream>
using namespace std;

// 顺序搜索算法
int SequentialSearch(int a[],const int &x,int n)
{
	int i;                             //顺序搜索数组中值为x的元素
	for(i=0;i<n&&a[i]!=x;i++);
	if(i==n)return -1;                 //返回-1表示没有找到元素x
	return i;
}

// 二分查找又称折半查找，它是一种效率较高的查找方法
template<class T>
int BinarySearch(T a[],const T &x,int n)
{
//在a[0]<=a[1]<=...<=a[n-1]中搜索x
//如果找到，则返回所在位置，否则返回-1
int left=0;int right=n-1;
while(left<=right){
int middle=(left+right)/2;
if(x==a[middle])return middle;
if(x>a[middle])left=middle+1;
else right=middle-1;
}
return -1;//未找到x
}

// 给定一个排好序的整数数组，要求二分搜索某个值的位置
int binary_search(int a[],const int &x,int n)
{
	const int* lo = a, *hi = a+n, *mid;
	while (lo != hi)
	{
		mid = lo+(hi-lo)/2;
		if (x == *mid)
			return mid-a;
		if (x < *mid)
			hi = mid;
		else
			lo = mid+1;
	}
	return -1;//没找到
}

int main()
{
#if 1
       //int a[10]={2,6,9,8,7,4,5,3,1,10},m=0,x=4;
        //int a[10]={2,6,9,18,27,34,35,43,51,100},m=0,x=43;
        //int a[10]={18,27,2,6,43,51,100,9,34,35},m=0,x=43;
        //int a[10]={18,27,2,6,34,51,100,9,43,35},m=0,x=43;
        int a[10]={18,27,2,34,100,51,6,9,43,35},m=0,x=43;
#else
	int a[10],m=0,x;
	cout <<"输入数组中的数"<<endl;
	for(int i=0;i<10;i++)
	{
		cin>>a[i];
	}
	cout <<"输入要找的数"<<endl;
	cin>>x;
#endif
	//m=SequentialSearch(a,x,10);
        //m=binary_search(a,x,10);
        m=BinarySearch(a,x,10);
	if(m!=-1)
		cout<<"元素"<<x<<"在数组中的第"<<m+1<<"个"<<endl;
	else
		cout <<"数组中没有"<<x<<"这个元素"<<endl;

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
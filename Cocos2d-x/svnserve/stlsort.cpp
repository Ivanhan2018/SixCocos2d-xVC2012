// g++ -std=c++11 -o stlsort stlsort.cpp
#include<algorithm>
#include<list>
#include<iostream>
using namespace std;

bool less_second(const int & m1, const int & m2) {
	return m1>m2;
}

template <typename T>
void printList1(T *a,int n)
{
 for(int i=0;i<n;i++)
  cout<<a[i]<<" ";
 cout<<endl;
}

template <typename T>
void printList(const list <T> &b)
{
  typename list<T>::const_iterator it;
  for(it=b.begin();it!=b.end();++it)
	cout<<*it<<" ";
  cout<<endl;	
}

template <typename T>
void BubbleSort(list<T> &L,bool ascending)
{
#if 1
	typename list<T>::iterator it1,it2; 	
	for (it1 = L.begin(); it1 != L.end();it1++)
	{
		for (it2 = it1; it2 != L.end();it2++)
		{
			//if ((*(it1)> *(it2))==ascending)
			if (ascending?(*(it1)> *(it2)):(*(it1)< *(it2)))	
			{
				//T t=*it1;*it1=*it2;*it2=t;
				//iter_swap(it1,it2);
				std::swap<T>(*it1,*it2);
			}
		}
	}
#else
	typename list<T>::reverse_iterator it1,it2;  	
	for (it1 = L.rbegin(); it1 != L.rend();++it1)
	{
		for (it2 = it1; it2 != L.rend();++it2)
		{
			if ((*(it1)< *(it2))==ascending)
			{
				//T t=*it1;*it1=*it2;*it2=t;
				iter_swap(it1,it2);
			}
		}
	} 
#endif
}

int main()
{
 int a[]={2,5,4,1,6,8,3,7,9,0};
 list <int> b;
 int n=sizeof(a)/sizeof(a[0]);
 for(int k=0;k<n;k++)
 {
  b.push_back(a[k]);
 }
 std::sort(a,a+n,less_second);//降序
 std::sort(a,a+n,[](const int & m1, const int & m2)->bool{return m1>m2;});//降序
 //b.sort();//升序
 b.sort(greater<int>());//降序
 BubbleSort(b,true);//升序
 //BubbleSort(b,false);//降序
 ////std::sort(b.begin(),b.end(),less_second);//不能编译通过
 printList1(a,n);
 printList(b);
 return 0;
}
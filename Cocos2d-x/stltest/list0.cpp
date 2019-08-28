#include<list>
#include<iostream>
#include<functional>
int main()
{
using namespace std;
list<int>::iterator Iter;
#if 1
list<int> the_list={3,4,6,2,1};//统一的初始化方法(VC2012不支持，VC2013支持)
#else
list<int> the_list;
int temp;
for( int i = 0; i < 5; i++ )
{
cin>>temp;
the_list.push_front(temp);
}
#endif
the_list.sort(less<int>());//升序排列
//the_list.sort(greater<int>());//降序排列
cout<<"the_list=";
for(Iter=the_list.begin();Iter!=the_list.end();Iter++)
cout<< " "<<*Iter;
cout<<endl;
}
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef vector<int> INTVECTOR;//自定义类型INTVECTOR

// 测试vector容器的功能
void Func1()
{
	//vec1对象初始为空
	INTVECTOR vec1;   
	//vec2对象最初有10个值为6的元素  
	INTVECTOR vec2(10,6);  
	//vec3对象最初有3个值为6的元素，拷贝构造
	INTVECTOR vec3(vec2.begin(),vec2.begin()+3);
	//声明一个名为i的双向迭代器      
#if _MSC_VER>=1700//VC2012
	auto i=vec1.begin();
#else
	INTVECTOR::iterator i;
#endif
	//从前向后显示vec1中的数据
	cout<<"vec1.begin()--vec1.end():"<<endl;
	for (i =vec1.begin(); i !=vec1.end(); ++i)
		cout << *i << " ";
	cout << endl;
	//从前向后显示vec2中的数据
	cout<<"vec2.begin()--vec2.end():"<<endl;
	for (i =vec2.begin(); i !=vec2.end(); ++i)
		cout << *i << " ";
	cout << endl;
	//从前向后显示vec3中的数据
	cout<<"vec3.begin()--vec3.end():"<<endl;
	for (i =vec3.begin(); i !=vec3.end(); ++i)
		cout << *i << " ";
	cout << endl;
	//测试添加和插入成员函数，vector不支持从前插入
	vec1.push_back(2);//从后面添加一个成员
	vec1.push_back(4);
	vec1.insert(vec1.begin()+1,5);//在vec1第一个的位置上插入成员5
	//从vec1第一的位置开始插入vec3的所有成员
	vec1.insert(vec1.begin()+1,vec3.begin(),vec3.end());
	cout<<"after push() and insert() now the vec1 is:" <<endl;
	for (i =vec1.begin(); i !=vec1.end(); ++i)
		cout << *i << " ";
	cout << endl;
	//测试赋值成员函数
	vec2.assign(8,1);   // 重新给vec2赋值，8个成员的初始值都为1
	cout<<"vec2.assign(8,1):" <<endl;
	for (i =vec2.begin(); i !=vec2.end(); ++i)
		cout << *i << " ";
	cout << endl;
	//测试引用类函数
	cout<<"vec1.front()="<<vec1.front()<<endl;//vec1第零个成员
	cout<<"vec1.back()="<<vec1.back()<<endl;//vec1的最后一个成员
	cout<<"vec1.at(4)="<<vec1.at(4)<<endl;//vec1的第五个成员
	cout<<"vec1[4]="<<vec1[4]<<endl;
	//测试移出和删除
	vec1.pop_back();//将最后一个成员移出vec1
	vec1.erase(vec1.begin()+1,vec1.end()-2);//删除成员
	cout<<"vec1.pop_back() and vec1.erase():" <<endl;
	for (i =vec1.begin(); i !=vec1.end(); ++i)
		cout << *i << " ";
	cout << endl;
	//显示序列的状态信息
	cout<<"vec1.size(): "<<vec1.size()<<endl;//打印成员个数
	cout<<"vec1.empty(): "<<vec1.empty()<<endl;//清空
}

void Func2()
{
	set<int> set1;
	for(int i=0; i<10; ++i)
		set1.insert(i);
#if _MSC_VER>=1700
	for(auto p=set1.begin();p!=set1.end();++p)
#else
	for(set<int>::iterator p=set1.begin();p!=set1.end();++p)
#endif
		cout<<*p<<"";
	if(set1.insert(3).second)//把3插入到set1中
		//插入成功则set1.insert(3).second返回1，否则返回0
		//此例中，集中已经有3这个元素了，所以插入将失败
		cout<<"set insert success";
	else
		cout<<"set insert failed"; 
	int a[] = {4, 1, 1, 1, 1, 1, 0, 5, 1, 0};
	multiset<int> A;
	A.insert(set1.begin(),set1.end());
	A.insert(a,a+10);
	cout<<endl;
#if _MSC_VER>=1700
	for(auto p=A.begin();p!=A.end();++p)
#else
	for(multiset<int>::iterator p=A.begin();p!=A.end();++p)
#endif
		cout<<*p<<" "; 
	cin.get();
}

int main(int argc, char **argv)
{
    cout<<"_MSC_VER: "<<_MSC_VER<<endl;  
    //Func1();
    Func2();
 
	system("pause");
	return 0;
}


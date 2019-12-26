// NodeLayout.cpp : 定义控制台应用程序的入口点。
/*
Error:运行时dynamic_cast的操作数必须包含多态类类型
error C2683: “dynamic_cast”:“Node”不是多态类型
IntelliSense: 运行时 dynamic_cast 的操作数必须包含多态类类型
error C2633: “Node”:“inline”是构造函数的唯一合法存储类
*/

//#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	Node(int tag)
	{
		m_tag=tag;
	}
	virtual ~Node()
	{
		m_tag=0;
	}
	int GetTag(){return m_tag;};
private:
	int m_tag;
};

class Layout:public Node {
public:
	Layout(int tag, int tag2):Node(tag)
	{
		m_tag2=tag2;
	}
	~Layout()
	{
	    m_tag2=0;
	}
private:
	int m_tag2;
};

Node * getChildByName(vector<Node*> v,int tag)
{
	for(int i=0,n=v.size();i<n;i++)
	{
	    if(v[i]->GetTag()==tag)
			return v[i];
	}
	return NULL;
}

int main()
{
	Node n1(10),n2(20);
	Layout n3(30,1),n4(40,2);
	Node* pNArr[]={&n1,&n2,&n3,&n4};
	vector<Node*> v(pNArr,pNArr+sizeof(pNArr)/sizeof(Node*));
	Layout *pn3 = dynamic_cast<Layout*>(getChildByName(v,30));//要求Node类有虚函数表才能编译通过，至于是析构还是一般成员函数是虚函数不重要
        cout<<"pn3="<<pn3<<endl;
	Layout *pN3 = (Layout*)(getChildByName(v,30));//不要求Node类有虚函数表就能编译通过
        cout<<"pN3="<<pN3<<endl;

	return 0;
}

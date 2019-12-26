// NodeLayout.cpp : �������̨Ӧ�ó������ڵ㡣
/*
Error:����ʱdynamic_cast�Ĳ��������������̬������
error C2683: ��dynamic_cast��:��Node�����Ƕ�̬����
IntelliSense: ����ʱ dynamic_cast �Ĳ��������������̬������
error C2633: ��Node��:��inline���ǹ��캯����Ψһ�Ϸ��洢��
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
	Layout *pn3 = dynamic_cast<Layout*>(getChildByName(v,30));//Ҫ��Node�����麯������ܱ���ͨ������������������һ���Ա�������麯������Ҫ
        cout<<"pn3="<<pn3<<endl;
	Layout *pN3 = (Layout*)(getChildByName(v,30));//��Ҫ��Node�����麯������ܱ���ͨ��
        cout<<"pN3="<<pN3<<endl;

	return 0;
}

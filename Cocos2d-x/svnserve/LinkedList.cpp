#ifdef USE_STL
#include <list>//STL 线性列表容器,list采用链表结构，不支持随机存取
#else
    
#endif
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;


#ifndef USE_STL

template <class T>
class Node//普通链表结点
{
	private:
		// next 为指向下一结点的指针
		Node<T> *next;
	public:
		// data 为公有成员
		T data;

		// 构造函数
		Node(const T& item, Node<T> *ptrnext = NULL);

		// 修改表的方法
		void InsertAfter(Node<T> *p);
		Node<T> *DeleteAfter(void);

		// 取得下一结点的指针
		Node<T> *NextNode(void) const;
};

// 构造函数。初始化数据及指针成员
template <class T>
Node<T>::Node(const T& item, Node<T> *ptrnext):
	          data(item), next(ptrnext)
{}

// 返回私有成员 next 的值
template <class T>
Node<T> *Node<T>::NextNode(void) const
{
	return next;
}

// 在当前结点之后插入结点 p
template <class T>
void Node<T>::InsertAfter(Node<T> *p)
{
	// p 指向当前结点的后继结点，然后将当前结点指向 p
	p->next = next;
	next = p;
}

// 删除当前结点的后继结点并返回其指针
template <class T>
Node<T> *Node<T>::DeleteAfter(void)
{
	// 若没有后继结点，返回 NULL
	if (next == NULL)
		return NULL;

	// 保存指向被删除结点的指针
	Node<T> *tempPtr = next;
	// 使当前结点指向 tempPtr 的后继结点
	next = tempPtr->next;
	// 返回被删除结点的指针
	return tempPtr;
}

template <class T>
class list //普通链表（可随机访问，但访问效率低）
{
	private:
		// 指向表头和表尾的指针
		Node<T> *front, *rear;

		// 用于数据访问、插入和删除的指针
		Node<T> *prevPtr, *currPtr;

		// 表中的元素个数
		int m_size;

		// 表中位置值，用于 Reset
		int position;

		// 将表 L 拷贝到当前表尾
		void CopyList(const list<T> &L);

	public:
		// 构造函数
		list(void);
		list(const list<T>& L);

		// 析构函数
		~list(void);

		// 赋值运算符
		list<T>& operator= (const list<T>& L);

		// 检查表状态的函数
		int size(void) const;               
		bool empty(void) const;

		// 遍历表的函数
		void Reset(int pos = 0);
		void Next(void);
		bool EndOfList(void) const;
		int CurrentPosition(void) const;

		// 插入函数
		void push_front(const T& item);
		void push_back(const T& item);
		void InsertAt(const T& item);
		void InsertAfter(const T& item);

		// 删除函数
		void DeleteFront(void);
		void DeleteAt(void);

		// 访问／修改数据
		T& Data(void);
		bool Find(const T& item);

		// 清空表的函数
		void clear(void);
public:
    //-------------------------------------------------------------
    //  list<T>::iterator
    //-------------------------------------------------------------
    class iterator{
        friend class list<T>; //因为在list中访问了protected成员
    protected:
        Node<T>* nodePtr;
        iterator (Node<T>* newPtr)
        {
            nodePtr = newPtr;
        }
    public:
        iterator()
        {
        }
        bool operator== (const iterator& itr) const
        {
            return nodePtr == itr.nodePtr;
        } // overloading ==
        bool operator!= (const iterator& itr) const
        {
            return nodePtr != itr.nodePtr;
        } // overloading !=
        T& operator*() const
        {
            return nodePtr -> data;
        } // overloading *
        iterator operator++(int)
        {
            iterator temp = *this;
            nodePtr = nodePtr -> NextNode();
            return temp;
        } // post-increment ++
        iterator& operator++()
        {
            nodePtr = nodePtr -> NextNode();
            return *this;
        } // pre-increment ++
        bool atEnd()
        {
            return (nodePtr == NULL);
        } 
    };
    //---------------------------------------------
    //  list类要添加begin, end方法
    //---------------------------------------------
    iterator begin()
    {
        return iterator(front);  //要访问Iterator的protected成员, 要把list添加为友元类.
    } 
    iterator end()
    {
        return iterator(NULL);  //要访问Iterator的protected成员, 要把list添加为友元类.
    } 	
    iterator insert(iterator pos, const T &val)
	{
	    Reset();
        list<int>::iterator Iter=begin();	
		for(;Iter!=end();Iter++)
		{
			if(Iter==pos)
			{
				InsertAt(val);
				break;
			}
			else
			{
				Next();
			}
		}
		return Iter;
	}
    void insert(iterator pos, int num, const T &val)
	{
	    Reset();
        list<int>::iterator Iter=begin();	
		for(;Iter!=end();Iter++)
		{
			if(Iter==pos)
			{
				for(int i=0;i<num;i++)
					InsertAt(val);
				break;
			}
			else
			{
				Next();
			}
		}
		return;
	}	
};

// 创建空表，使其指针指向 NULL，m_size 置为 0，position 置为 -1
template <class T>
list<T>::list(void): front(NULL), rear(NULL),
	prevPtr(NULL),currPtr(NULL), m_size(0), position(-1)
{}

// 将 L 拷贝到当前表尾
template <class T>
void list<T>::CopyList(const list<T> &L)
{
	// 用指针 P 遍历表
	Node<T> *p = L.front;

	// 往当前表的表尾插入 L 的每个元素
	while (p != NULL)
	{
		push_back(p->data);
		p = p->NextNode();
	}
}

template <class T>
list<T>::list(const list<T>& L)
{
	front = rear = prevPtr = currPtr = NULL;
	m_size = 0;
	position = -1;
	CopyList(L);
}

template <class T>
list<T>::~list(void)
{
	clear();
}

template <class T>
void list<T>::clear(void)
{
	Node<T> *currPos, *nextPos;
	currPos = front;
	while (currPos != NULL) 
	{
		// 取下一结点指针并删除当前结点
		nextPos = currPos->NextNode();
		delete currPos;
		currPos = nextPos;  //移到下一结点
	}
	front = rear = prevPtr = currPtr = NULL;
	m_size = 0;
	position = -1;
}

template <class T>
list<T>& list<T>::operator= (const list<T>& L)
{
	if (this == &L)      // 无法赋值给自身
		return *this;
	
	clear();
	CopyList(L);
	return *this;
}

template <class T>
int list<T>::size(void) const
{
	return m_size;
}

template <class T>
bool list<T>::empty(void) const
{
	return (m_size == 0);
}

// 将表位置设置到 pos
template <class T>
void list<T>::Reset(int pos)
{
	// 若表为空，则返回
	if (front == NULL)
		return;

	// 若位置非法，退出程序
	if (pos < 0 || pos > m_size - 1)
		throw "list::Reset: Invalid list position";
	
	prevPtr = NULL;
	currPtr = front;
	for (position = 0; position != pos; position++)
	{
		// 将两个指针右移
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
	}
}

// 将 prevPtr 和 currPtr 指针右移一个结点
template <class T>
void list<T>::Next(void)
{
	// 若已到表尾或表为空，返回
	if (currPtr !=  NULL)
	{
		// 将两个指针右移一个结点
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}
}

// 如果已到表尾，返回真
template <class T>
bool list<T>::EndOfList(void) const
{
	return (currPtr == NULL);
}

// 返回当前结点的位置
template <class T>
int list<T>::CurrentPosition(void) const
{
	return position;
}

// 往表头插入结点
template <class T>
void list<T>::push_front(const T& item)
{
	Reset();
	InsertAt(item);  // 往表头插入
}

// 在表尾插入结点
template <class T>
void list<T>::push_back(const T& item)
{
	prevPtr = rear;
	currPtr= NULL;
	position = m_size;

	InsertAt(item);
}

// 往表的当前位置插入结点
template <class T>
void list<T>::InsertAt(const T& item)
{
	Node<T> *newNode;

	// 两种情况：往表头或表中插入
	if (prevPtr == NULL)
	{
		// 往表头插入，包括往空表中插入
		newNode = new Node<T>(item, front);
		front = newNode;
	}
	else
	{
		// 往表中插入。在 prevPtr 后插入结点
		newNode = new Node<T>(item);
		prevPtr->InsertAfter(newNode);
	}

	// 若 currPtr == NULL，表示往空表中或非空表的表尾插入；应修改 rear 及 position 值
	if (currPtr == NULL)
	{
		rear = newNode;
		position = m_size;
	}

	// 改变 currPtr 及增加表的大小
	currPtr = newNode;
	m_size++;
}

// 在当前表位置后插入结点
template <class T>
void list<T>::InsertAfter(const T& item)
{
	Next();
	InsertAt(item);
}

// 删除表中第一个节点
template <class T>
void list<T>::DeleteFront(void)
{
   if (front == NULL)
      return;
	
   Reset();
   DeleteAt();
}

// 删除表中当前结点
template <class T>
void list<T>::DeleteAt(void)
{
	// 如果表为空或已到表尾，则出错退出
	if (currPtr == NULL)
		throw "list::DeleteAt: Invalid deletion!";
	
	Node<T> *p;

	// 被删除的必是头结点或表中结点
	if (prevPtr == NULL)
	{
		// 保存表头指针并取消其链接。如果这是最后结点，front 变为 NULL
		p = front;
		front = front->NextNode();
	}
	else
		// 取消链接 prevPtr 之后的中间结点，并保存其地址
		p = prevPtr->DeleteAfter();
	
	// 若表尾被删除，则 prevPtr 是新表尾且 position 减 1；否则，position 不变
	// 如果 p 是最后结点，rear = NULL 且 position = -1
	if (p == rear)
	{
		rear = prevPtr;
		position--;
	}
	
	// 将 currPtr 指向下一结点。若 p 为表中最后结点，则 currPtr 为 NULL
	currPtr = p->NextNode();
	
	// 释放结点并将表大小减 1
	delete p;
	m_size--;
}

// 返回当前结点的数据值
template <class T>
T& list<T>::Data(void)
{
	// 若表为空或已到表尾，则出错
	if (currPtr == NULL)
		throw "LinkedList::Data: invalid reference!";

	return currPtr->data;
}

// 查找链表中是否有某数据
template <class T>
bool list<T>::Find(const T& item)
{
	for (Reset(); !EndOfList(); Next())
		if (Data() == item)
			return true;

	return false;
}

#endif

int main()
{
int arr[]={1,4,2,8,5,7};
int n=sizeof(arr)/sizeof(arr[0]);
cout<<"1 4 2 8 5 7"<<endl;
list<int> L1,L2,L3;
for(int i=0;i<n;i++){
   L1.push_back(arr[i]);
   L2.push_front(arr[i]);
}
auto func1=[&]()->void{
		cout<<"n="<<L1.size()<<endl;
		if(L1.empty())
		cout<<"L1为空"<<endl;
		else
		cout<<"L1非空"<<endl;
	};
func1();

auto Iter1=L1.begin();
Iter1++;
L1.insert(Iter1,100);//在第一个元素之后插入100
auto Iter2=L2.begin();
Iter2++;
Iter2++;
L2.insert(Iter2,2,200);//在第二个元素之后插入两个200
cout<<"L1=";
for_each(L1.begin(),L1.end(),[](int& i)->void{cout<< " "<<i;});
cout<<endl;
cout<<"L2=";
for_each(L2.begin(),L2.end(),[](int& i){cout<< " "<<i;});
cout<<endl;
L3=L1;
L1.clear();
func1();
#ifdef USE_STL
L3.sort();//升序
//list不能用sort(L3.begin(),L3.end());
#endif
auto func2=[&]()->void{
		cout<<"L3=";
		for(list<int>::iterator Iter=L3.begin();Iter!=L3.end();Iter++)
		cout<< " "<<*Iter;
		cout<<endl;
	};
func2();
#ifdef USE_STL
L3.sort(greater<int>());//降序
//list不能用sort(L3.begin(),L3.end(),greater<int>());
#endif
func2();

return 0;
}
#include<iostream>
#ifdef USE_STL
#include <stack>//STL 堆栈容器
#else
	
#endif
#include <string>//字符串类
using namespace std;


#ifndef USE_STL
template <class T> class stack;
template <class T> class deque;
template <class T>
class Node {
	friend stack<T>;
	friend deque<T>;
private:
	T data;
	Node<T> *link;
};

template<class T>
class stack {
   public:
      stack() {m_top = 0;}
      ~stack();
      bool empty() const {return m_top == 0;}
      bool IsFull() const;
      T top() const;
      stack<T>& push(const T& x);
	  stack<T>& pop();
      stack<T>& Delete(T& x);
   private:
      Node<T> *m_top; // pointer to top node
};

template<class T>
stack<T>::~stack()
{// Stack destructor..
   Node<T> *next;
   while (m_top) {
      next = m_top->link;
      delete m_top;
      m_top = next;
      }
}

template<class T>
bool stack<T>::IsFull() const
{// Is the stack full?
   try {Node<T> *p = new Node<T>;
        delete p;
        return false;}
   catch (...) {return true;}
}

template<class T>
T stack<T>::top() const
{// Return top element.
   if (empty()) throw std::runtime_error("OutOfBounds();");
   return m_top->data;
}

template<class T>
stack<T>& stack<T>::push(const T& x)
{// Add x to stack.
   Node<T> *p = new Node<T>;
   p->data = x;
   p->link = m_top;
   m_top = p;
   return *this;
}

template<class T>
stack<T>& stack<T>::Delete(T& x)
{// Delete top element and put it in x.
   if (empty()) throw std::runtime_error("OutOfBounds();");
   x = m_top->data;
   Node<T> *p = m_top;
   m_top = m_top->link;
   delete p;
   return *this;
}

template<class T>
stack<T>& stack<T>::pop()
{
   T x;
   return Delete(x);
}

#endif

int main()
{	
	stack<int> a;
	a.push(5);
	cout<<a.top()<<endl;
	a.push(20);
	a.push(40);
	cout<<a.top()<<endl;

	stack<long> b;
	b.push(500000);
	cout<<b.top()<<endl;
	b.push(200000);
	b.push(400000);
	cout<<b.top()<<endl;

	stack<int> s;
	for( int i=0; i < 10; i++ )
	s.push(i);
	while(!s.empty())
	{
	cout<< " "<<s.top();
	s.pop();
	}// 9 8 7 6 5 4 3 2 1 0
	cout<<endl;

	stack<int> S;
	try {
	   S.push(1);
	   S.push(2);
	   S.push(3);
	   S.push(4);
	   }
	catch (...) {
	  cout << "Could not complete additions" << endl;
	  }
  
   cout << "Stack should be 1234" << endl;
   cout << "S top is " << S.top() << endl;
   try {
      S.pop();
      cout << "Stack top is " << S.top() << endl;
      S.pop();
      cout << "Stack top is " << S.top() << endl;
      S.pop();
      cout << "Stack top is " << S.top() << endl;
      S.pop();
	  if(!s.empty())
        cout << "Stack top is " << S.top() << endl;
      else
	    cout << "Stack top is empty" << endl;  
      }
   catch (...) {
      cout << "Last delete failed " << endl;
      }  
	return 0;
}
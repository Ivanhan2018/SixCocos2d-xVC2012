#include<iostream>
#ifdef USE_STL
#include<queue>//队列
#else
    
#endif
using namespace std;

#ifndef USE_STL
template <class T> class stack;
template <class T> class queue;

template <class T>
class Node {
	friend stack<T>;
	friend queue<T>;
private:
	T data;
	Node<T> *link;
};

template<class T>
class queue {
	// FIFO objects
public:
	queue() {m_front = m_rear = 0;} // constructor
	~queue(); // destructor
	bool empty() const
	{return ((m_front) ? false : true);}
	bool IsFull() const;
	T front() const; // return first element
	T back() const; // return last element
	queue<T>& push(const T& x);
	queue<T>& pop();
	queue<T>& Delete(T& x);
private:
	Node<T> *m_front;  // pointer to first node
	Node<T> *m_rear;   // pointer to last node
};

template<class T>
queue<T>::~queue()
{// Queue destructor.  Delete all nodes.
	Node<T> *next;
	while (m_front) {
		next = m_front->link; 
		delete m_front; 
		m_front = next;
	}
}

template<class T>
bool queue<T>::IsFull() const
{// Is the queue full?
	Node<T> *p;
	try {p = new Node<T>;
	delete p;
	return false;}
	catch (...) {return true;}
}

template<class T>
T queue<T>::front() const
{// Return first element of queue.  Throw
	// OutOfBounds exception if the queue is empty.
	if (empty()) throw std::runtime_error("OutOfBounds();");
	return m_front->data;
}

template<class T>
T queue<T>::back() const
{// Return last element of queue.  Throw
	// OutOfBounds exception if the queue is empty.
	if (empty()) throw std::runtime_error("OutOfBounds();");
	return m_rear->data;
}

template<class T>
queue<T>& queue<T>::push(const T& x)
{// Add x to rear of queue.  Do not catch
	// possible NoMem exception thrown by new.

	// create node for new element
	Node<T> *p = new Node<T>;
	p->data = x;
	p->link = 0;

	// add new node to rear of queue
	if (m_front) m_rear->link = p;  // queue not empty
	else m_front = p;             // queue empty
	m_rear = p;

	return *this;
}

template<class T>
queue<T>& queue<T>::Delete(T& x)
{// Delete first element and put it in x.  Throw
	// OutOfBounds exception if the queue is empty.

	if (empty()) throw std::runtime_error("OutOfBounds();");

	// save element in first node
	x = m_front->data;

	// delete first node
	Node<T> *p = m_front;
	m_front = m_front->link;
	delete p;

	return *this;
}

template<class T>
queue<T>& queue<T>::pop()
{
   T x;
   return Delete(x);
}

#endif

int main()
{
queue<int> q;
int arr[]={1,4,2,8,5,7};
int n=sizeof(arr)/sizeof(arr[0]);
cout<<"1 4 2 8 5 7"<<endl;
for(int i=0;i<n;i++){
   q.push(arr[i]);
}
while(!q.empty())
{
cout<<"front:"<<q.front()<<",back:"<<q.back()<<endl;
q.pop();
}

#ifdef USE_STL
//优先队列是从大到小的顺序8 7 5 4 2 1
priority_queue<int> Q;
cout<<"1 4 2 8 5 7"<<endl;
for(int i=0;i<n;i++){
   Q.push(arr[i]);
}
while(!Q.empty())
{
cout<<"top:"<<Q.top()<<endl;
Q.pop();
}
#endif
return 0;
}
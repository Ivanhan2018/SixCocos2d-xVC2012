#ifdef USE_STL
#include<vector>//STL 动态数组容器、向量(Vector)
#else
    
#endif
#include<iostream>
using namespace std;

#ifndef USE_STL
template<class T>
class vector {
public:
   vector(int size = 0);
   vector(const vector<T>& v); //copy constructor
   ~vector() {delete [] element;}
   T& operator[](int x) const;
   int size() {return size;}
   vector<T>& operator=(const vector<T>& v);
   vector<T> operator+() const; //unary +
   vector<T> operator+(const vector<T>& v) const;
   vector<T> operator-() const; //unary minus
   vector<T> operator-(const vector<T>& v) const;
   vector<T> operator*(const vector<T>& v) const;
   vector<T>& operator+=(const T& x);
   void Output(ostream& out) const;
private:
    int m_size;
    T *element; //array
};  

template<class T>
vector<T>::vector(int sz)
{//create
if (sz < 0) throw std::runtime_error(" BadInitializers();");
m_size = sz;
element = new T[sz];
}

template<class T>
vector<T>::vector(const vector<T>& v)
{//copy constructor
m_size = v.size;
element = new T[size];
for (int i = 0; i < m_size; i++)
   element[i] = v.element[i];
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{//overload assignment operator
if (this != &v) {//not self assignment
   delete [] element;
   m_size = v.m_size;
   element = new T[m_size];
   for (int i = 0; i < m_size; i++)
      element[i] = v.element[i];
   }
return *this;
}

template<class T>
T& vector<T>::operator[](int x) const
{//return reference to element x
if (x < 0 || x > m_size) throw std::runtime_error("OutOfBounds();");
return element[x];
}

template<class T>
vector<T> vector<T>::operator+(const vector<T>& v) const
{
if (m_size != v.m_size) throw std::runtime_error("SizeMismatch();");
vector<T> w(m_size);
for (int i = 0; i < m_size; i++)
    w.element[i] = element[i] + v.element[i];
return w;
}

template<class T>
vector<T> vector<T>::operator-(const vector<T>& v) const
{
if (m_size != v.size) throw std::runtime_error("SizeMismatch();");
vector<T> w(m_size);
for (int i = 0; i < m_size; i++)
    w.element[i] = element[i] - v.element[i];
return w;
}

template<class T>
vector<T> vector<T>::operator-() const
{//unary minus
vector<T> w(m_size);
for (int i = 0; i < m_size; i++)
    w.element[i] = -element[i];
return w;
}

template<class T>
vector<T> vector<T>::operator*(const vector<T>& v) const
{
if (m_size != v.size) throw std::runtime_error("SizeMismatch();");
vector<T> w(m_size);
for (int i = 0; i < m_size; i++)
    w.element[i] = element[i] * v.element[i];
return w;
}

template<class T>
vector<T>& vector<T>::operator+=(const T& x)
{
for (int i = 0; i < m_size; i++)
    element[i] += x;
return *this;
}

template<class T>
void vector<T>::Output(ostream& out) const
{// put the vector into the stream out
for (int i = 0; i < m_size; i++)
   out << element[i] << "  ";
}

//overload <<
template <class T>
ostream& operator<<(ostream& out, const vector<T>& x)
{
	x.Output(out); 
	return out;
}

#endif

int main()
{
	vector<int> X(10), Y, Z;
	try {
	   for (int i=0; i < 10; i++)
		  X[i] = i;
	   cout << "X[3] = " << X[3] << endl;
	   //cout << "X is " << X << endl;
	   Y = X;
	   //cout << "Y is " << Y << endl;
	   //X += 2;
	   //cout << "X incremented by 2 is " << X << endl;
	   //Z = (Y + X) * Y;
	   //cout << "(Y + X) * Y is " << Z << endl;
	   //cout << "-(Y + X) * Y is " << -Z << endl;
   }
   catch (...) {
	   cerr << "An exception has occurred" << endl;
   }
	//cin.get();	
	
	vector<int>::iterator Iter;
	vector<int> the_vector;
	int n=X.size();
	for(int i = 0; i < n; i++ )
	{
		the_vector.push_back(X[i]);//vector无push_front方法
	}
	//the_list.sort(greater<int>());
	cout<<"the_vector=";
	for(Iter=the_vector.begin();Iter!=the_vector.end();Iter++)
	cout<< " "<<*Iter;
	cout<<endl;
}
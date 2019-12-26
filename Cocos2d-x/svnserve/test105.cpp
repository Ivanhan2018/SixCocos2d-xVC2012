#include <iostream>
using namespace std; 

class CBase 
{ 
public: 
	CBase() 
	{ 
		data = new char[64]; 
	}; 
	~CBase() 
	{ 
		delete [] data; 
	}; 
	char *data; 
}; 

class CFunction 
{ 
public: 
	CFunction(){}; 
	~CFunction(){}; 
}; 

class CFunctionEx : public CFunction 
{ 
public: 
	CFunctionEx(){}; 
	~CFunctionEx(){}; 
private: 
	CBase m_cbase; 
}; 

int main() 
{ 
    // C++中析构函数为什么是虚函数会更好
	CFunction *pCFun = new CFunctionEx; 
	delete pCFun; 
	return 0;
} 


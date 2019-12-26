#include<iostream>
using namespace std;

class Class1 
{
public:
int mem_data1; 
int mem_data2;

Class1(){}//constructor 
void mem_func1()
{ 
cout<<"this is mem_func1"<<endl; 
this->mem_data1 =10;
} 

void virtual  mem_vfun1()
{ 
cout<<"this is mem_vfun1"<<endl;
this->mem_data2 =20;
} 
void virtual  mem_vfun2()
{ 
cout<<"this is mem_vfun2"<<endl;
this->mem_data2 =30;
} 
}; 

int main(int argc, char* argv[]) 
{
Class1 *ptemp=new Class1(); 
ptemp->mem_func1(); 
ptemp->mem_vfun1();
//this is mem_func1
//this is mem_vfun1
return 0; 
}  
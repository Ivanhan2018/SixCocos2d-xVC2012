#include <iostream>
using namespace std;
class product
{
public:
 virtual void produce(){};           //具体的实现交给子类的函数；
 virtual void sell(){};
 product(){};
 virtual ~product(){};
};
class conproduct1:public product
{
public:
 void produce()
 {cout<<"Pro conproduct1.."<<endl;}
 void sell()
 {cout<<"Sel conproduct1.."<<endl;}
};
class conproduct2:public product
{
public:
 void produce()
 {cout<<"Pro conproduct2.."<<endl;}
 void sell()
 {cout<<"Sel conproduct2.."<<endl;}
};
class Factory                      //具体的操作由factory控制选择
{
public:
 Factory(){}
 static product *Creatproduct(int a)
 {
  if(a==1) {return new conproduct1();}    //生成相对应的pro对象;
  if(a==2) {return new conproduct2();}
 }
};

class AbstractProductA
{
public:
     virtual ~AbstractProductA();
protected:
     AbstractProductA();
private:
};
class AbstractProductB
{
public:
     virtual ~AbstractProductB();
protected:
    AbstractProductB();
};
class ProductA1:public AbstractProductA
{
public:
     ProductA1();
     ~ProductA1();
protected:
};
class ProductA2:public AbstractProductA
{
public:
     ProductA2();
     ~ProductA2();
protected:
};
class ProductB1:public AbstractProductB
{
public:
     ProductB1();
     ~ProductB1();
protected:
private:
};
class ProductB2:public AbstractProductB
{
public: 
     ProductB2(); 
     ~ProductB2();
protected:
}; 

AbstractProductA::AbstractProductA() 
{      } 
AbstractProductA::~AbstractProductA() 
{      } 
AbstractProductB::AbstractProductB() 
{ 
} 
AbstractProductB::~AbstractProductB() 
{ 
} 
ProductA1::ProductA1() 
{ 
cout<<"ProductA1..."<<endl; 
} 
ProductA1::~ProductA1() 
{ 
} 
ProductA2::ProductA2() 
{ 
cout<<"ProductA2..."<<endl; 
} 
ProductA2::~ProductA2() 
{ 
} 
ProductB1::ProductB1() 
{ 
cout<<"ProductB1..."<<endl; 
} 
ProductB1::~ProductB1() 
{ 
} 
ProductB2::ProductB2() 
{ 
cout<<"ProductB2..."<<endl; 
} 
ProductB2::~ProductB2() 
{ 
}

 class AbstractFactory
 {
 public:
        virtual ~AbstractFactory();
        virtual AbstractProductA* CreateProductA() = 0;
        virtual AbstractProductB* CreateProductB() = 0;
 protected:
        AbstractFactory();
 private:
 };
 class ConcreteFactory1:public AbstractFactory
 {
 public:
        ConcreteFactory1();
        ~ConcreteFactory1();
        AbstractProductA* CreateProductA();
        AbstractProductB* CreateProductB();
 protected:
 private:
 };
 class ConcreteFactory2:public AbstractFactory
 {
 public:
        ConcreteFactory2();
        ~ConcreteFactory2();
        AbstractProductA* CreateProductA();
        AbstractProductB* CreateProductB();
 protected:
 private:
 };
 
AbstractFactory::AbstractFactory() 
{ 
} 
AbstractFactory::~AbstractFactory() 
{ 
} 
ConcreteFactory1::ConcreteFactory1() 
{ 
} 
ConcreteFactory1::~ConcreteFactory1() 
{ 
} 
AbstractProductA* ConcreteFactory1::CreateProductA() 
{ 
return new ProductA1(); 
} 
AbstractProductB* ConcreteFactory1::CreateProductB() 
{ 
return new ProductB1(); 
} 
ConcreteFactory2::ConcreteFactory2() 
{ 
} 
ConcreteFactory2::~ConcreteFactory2() 
{ 
} 
AbstractProductA* ConcreteFactory2::CreateProductA() 
{ 
return new ProductA2(); 
} 

AbstractProductB* ConcreteFactory2::CreateProductB() 
{ 
return new ProductB2(); 
}

// FACTORY模式(有内存泄露)
// AbstractFactory模式(有内存泄露)
int main()
{
	Factory *fac=new Factory();
	(fac->Creatproduct(2))->produce();
	
	AbstractFactory* cf1=new ConcreteFactory1(); 
	cf1->CreateProductA(); 
	cf1->CreateProductB(); 

	AbstractFactory* cf2=new ConcreteFactory2(); 
	cf2->CreateProductA(); 
	cf2->CreateProductB();
	
	cin.get();
	return 0 ;
}
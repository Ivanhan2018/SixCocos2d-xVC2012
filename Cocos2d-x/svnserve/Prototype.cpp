#include <iostream>
using namespace std;

class Prototype
{
public:
     virtual ~Prototype();
     virtual Prototype* Clone() const = 0;
protected:
     Prototype();
private:
};

class ConcretePrototype:public Prototype
{
public:
     ConcretePrototype();
     ConcretePrototype(const ConcretePrototype& cp);
     ~ConcretePrototype();
    Prototype* Clone() const;
protected: 
private: 
};

Prototype::Prototype() 
{ 
} 
Prototype::~Prototype() 
{ 
} 
Prototype* Prototype::Clone() const 
{ 
return 0; 
} 
ConcretePrototype::ConcretePrototype() 
{ 
} 
ConcretePrototype::~ConcretePrototype() 
{ 
} 
ConcretePrototype::ConcretePrototype(const ConcretePrototype& cp) 
{ 
cout<<"ConcretePrototype copy ..."<<endl; 
} 
Prototype* ConcretePrototype::Clone() const 
{ 
return new ConcretePrototype(*this); 
}

int main(int argc,char* argv[]) 
{ 
   Prototype* p = new ConcretePrototype(); 
   Prototype* p1 = p->Clone();
   cin.get();
   return 0; 
}
#include <iostream>
#include <memory>
using namespace std;

class AA
{
public:
	AA(int i, int j)
	{
		A=i; B=j;
		cout<<"构造函数"<<typeid(*this).name()<<"\n";
	}
	~AA()
	{ 
		cout<<"析构函数"<<typeid(*this).name()<<"\n";
	}
	void print();
private:
	int A, B;
};

void AA::print()
{
	cout<<A<<","<<B<<endl;
}

int main()
{
	//AA *a1;
	//AA *a2;
	//a1 = new AA(1, 2);
	//auto_ptr<AA> a1(new AA(1, 2));
	//unique_ptr<AA> a1(new AA(1, 2));
	shared_ptr<AA> a2(new AA(5, 6));
	weak_ptr<AA> a1(a2);
	if(!a1.expired()){
		shared_ptr<AA> a3=a1.lock();
		a3->print();
	}
	a2->print();
	//delete a1;
	//delete a2;
	return 0;
}
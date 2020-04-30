#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct transformTest01{
	int operator()(char val){
		return val + 100;
	}
};

int main()
{
        string   str="abcdadcdefdde!@234";
        string   str1;
	    str1.resize(str.size());
        //transform(str.begin(),str.end(),str1.begin(),::toupper);
		transform(str.begin(),str.end(),str1.begin(),transformTest01());
        cout<<str<<endl;
        cout<<str1<<endl;
        return   0;
}
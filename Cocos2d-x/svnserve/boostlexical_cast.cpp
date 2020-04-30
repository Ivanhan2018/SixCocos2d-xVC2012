#include <boost/lexical_cast.hpp> 
#include <iostream> 
using namespace std;

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o boostlexical_cast boostlexical_cast.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./boostlexical_cast
number: 123  123.012
string: 123  123.0123456789
bad lexical cast: source type value could not be interpreted as target


*/
//number: 123  123.012
//string: 123  123.0123456789
//bad lexical cast: source type value could not be interpreted as target
int main(int argc, char* argv[]) 
{ 
 using boost::lexical_cast; 
 int a=lexical_cast<int>("123"); 
 double b=lexical_cast<double>("123.0123456789"); 
 string s0=lexical_cast<string>(a); 
 string s1=lexical_cast<string>(b); 
 cout<<"number: "<<a<<"  "<<b<<endl; 
 cout<<"string: "<<s0<<"  "<<s1<<endl; 
 int c=0;
 try{ 
   c=lexical_cast<int>("abcd"); 
  }
 catch(boost::bad_lexical_cast& e){ 
   cout<<e.what()<<endl;
 }
  getchar();
  return 0; 
}
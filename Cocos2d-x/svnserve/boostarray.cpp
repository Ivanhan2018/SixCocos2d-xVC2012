#include <iostream>
#include <boost/array.hpp>
using namespace std;

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o boostarray boostarray.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./boostarray
hi1
*/
int main(){
  boost::array<int, 4> arr = {{1,2,3,4}};
  cout << "hi" << arr[0]<<endl;

  return 0;
}
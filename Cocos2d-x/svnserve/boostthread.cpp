#include <boost/thread/thread.hpp>
#include <iostream> 
using namespace std;

//1>LINK : fatal error LNK1104: 无法打开文件“libboost_thread-vc80-mt-sgd-1_35.lib”
/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o boostthread boostthread.cpp -lboost_thread -lboost_system
root@iZ14rcmneyrcltZ:~/cpptest# ./boostthread
Hello world, I'm a thread!
*/
void hello()
{
 std::cout <<"Hello world, I'm a thread!"<< std::endl;
}

int main(int argc, char* argv[])
{
 boost::thread thrd(&hello);
 thrd.join();
 //getchar();
 return 0;
}
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o lu lu.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./lu
解向量: [4](1,1,1,1)
*/
//LU分解
int main(int argc, char* argv[])
{
// 可不要与 std::vector 混在一起啊.
 // 可考虑 using namespace boost::numeric;
 // 然后用 ublas::vector
 using namespace boost::numeric::ublas;
 const int n = 4;
 permutation_matrix<double> P(n);
 matrix<double> m(n,n);
 vector<double> x(n); // 用来放解向量
 vector<double> v(n); // 常量向量

 v(0) = 5;
 v(1) = 3;
 v(2) = 2;
 v(3) = 2;
 m(0, 0) = 1;
 m(0, 1) = 2;
 m(0, 2) = 1;
 m(0, 3) = 1;
 m(1, 0) = 2;
 m(1, 1) = 1;
 m(1, 2) = 0;
 m(1, 3) = 0;
 m(2, 0) = 1;
 m(2, 1) = 0;
 m(2, 2) = 1;
 m(2, 3) = 0;
 m(3, 0) = 1;
 m(3, 1) = 0;
 m(3, 2) = 0;
 m(3, 3) = 1;

 try {

  lu_factorize(m,P);
  x = v;
  lu_substitute(m,P,x);
  std::cout << "解向量: " << x << std::endl;
 }
 catch(...) {
     std::cout << "奇异矩阵(无解或无穷解)." << std::endl;
 }

 //getchar();
 return 0;
}
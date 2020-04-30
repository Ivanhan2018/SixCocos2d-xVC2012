// REMEMBER to update "lu.hpp" header includes from boost-CVS
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <iostream>

namespace ublas = boost::numeric::ublas;

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o InvertMatrix InvertMatrix.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./InvertMatrix
mtxA矩阵[4,4]((0.2368,0.2471,0.2568,1.2671),(1.1161,0.1254,0.1397,0.149),(0.1582,1.1675,0.1768,0.1871),(0.1968,0.2071,1.2168,0.2271))
mtxA逆矩阵[4,4]((-0.0859208,0.937944,-0.0684372,-0.0796077),(-0.10559,-0.0885243,0.905983,-0.0991908),(-0.127073,-0.111351,-0.116967,0.878425),(0.851606,-0.135456,-0.140183,-0.143807))
mtxA逆矩阵的逆矩阵 [4,4]((0.2368,0.2471,0.2568,1.2671),(1.1161,0.1254,0.1397,0.149),(0.1582,1.1675,0.1768,0.1871),(0.1968,0.2071,1.2168,0.2271))
*/

//! \brief 求矩阵的逆
//! \param input[in] 被求矩阵
//! \param inverse[out] 逆矩阵
/* Matrix inversion routine.
Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
template<class T>
bool InvertMatrix (const ublas::matrix<T>& input, ublas::matrix<T>& inverse) {
       using namespace boost::numeric::ublas;
       typedef permutation_matrix<std::size_t> pmatrix;
       // create a working copy of the input
       matrix<T> A(input);
       // create a permutation matrix for the LU-factorization
       pmatrix pm(A.size1());

       // perform LU-factorization
       int res = lu_factorize(A,pm);
       if( res != 0 ) return false;

       // create identity matrix of "inverse"
       inverse.assign(ublas::identity_matrix<T>(A.size1()));

       // backsubstitute to get the inverse
       lu_substitute(A, pm, inverse);

       return true;
}


int main()
{
       namespace ublas = boost::numeric::ublas;
       ublas::matrix<double> mTmp(4,4);
/*
    ' 原矩阵
    mtxA(1, 1) = 0.2368:    mtxA(1, 2) = 0.2471:    mtxA(1, 3) = 0.2568:    mtxA(1, 4) = 1.2671
    mtxA(2, 1) = 1.1161:    mtxA(2, 2) = 0.1254:    mtxA(2, 3) = 0.1397:    mtxA(2, 4) = 0.149
    mtxA(3, 1) = 0.1582:    mtxA(3, 2) = 1.1675:    mtxA(3, 3) = 0.1768:    mtxA(3, 4) = 0.1871
    mtxA(4, 1) = 0.1968:    mtxA(4, 2) = 0.2071:    mtxA(4, 3) = 1.2168:    mtxA(4, 4) = 0.2271
*/

#if 1
        //! \brief 求逆矩阵
        ublas::matrix<double> mtxA(4,4), MAInv(4,4);       
		mtxA(0, 0) = 0.2368;    mtxA(0, 1) = 0.2471;    mtxA(0, 2) = 0.2568;    mtxA(0, 3) = 1.2671;
		mtxA(1, 0) = 1.1161;    mtxA(1, 1) = 0.1254;    mtxA(1, 2) = 0.1397;    mtxA(1, 3) = 0.149;
		mtxA(2, 0) = 0.1582;    mtxA(2, 1) = 1.1675;    mtxA(2, 2) = 0.1768;    mtxA(2, 3) = 0.1871;
		mtxA(3, 0) = 0.1968;    mtxA(3, 1) = 0.2071;    mtxA(3, 2) = 1.2168;    mtxA(3, 3) = 0.2271;
        std::cout <<"mtxA矩阵"<< mtxA <<std::endl;
       
       InvertMatrix(mtxA, MAInv);
       InvertMatrix(mtxA, mTmp);
       std::cout <<"mtxA逆矩阵"<< mTmp << std::endl;
       InvertMatrix(mTmp, mTmp);
       std::cout <<"mtxA逆矩阵的逆矩阵 " <<mTmp <<std::endl;
       std::cout <<"" <<std::endl;
#endif

#if 0
       //! \brief 三次Hermite矩阵
       ublas::matrix<double> MHermite(4,4), MHInverse(4,4);       
       MHermite(0,0) = 2;
       MHermite(0,1) = -2;
       MHermite(0,2) = 1;
       MHermite(0,3) = 1;
       MHermite(1,0) = -3;
       MHermite(1,1) = 3;
       MHermite(1,2) = -2;
       MHermite(1,3) = -1;
       MHermite(2,0) = 0;
       MHermite(2,1) = 0;
       MHermite(2,2) = 1;
       MHermite(2,3) = 0;
       MHermite(3,0) = 1;
       MHermite(3,1) = 0;
       MHermite(3,2) = 0;
       MHermite(3,3) = 0;
       std::cout <<"MHermit矩阵"<< MHermite <<std::endl;
       
       InvertMatrix(MHermite, MHInverse);
       InvertMatrix(MHermite, mTmp);
       std::cout <<"MHermit逆矩阵"<< mTmp << std::endl;
       InvertMatrix(mTmp, mTmp);
       std::cout <<"MHermite逆矩阵的逆矩阵 " <<mTmp <<std::endl;
       std::cout <<"" <<std::endl;
#endif

#if 0
       //! \brief 三次Bezier矩阵
       ublas::matrix<double> MBezier(4,4),MBInverse(4,4);
       MBezier(0,0) = -1;
       MBezier(0,1) = 3;
       MBezier(0,2) = -3;
       MBezier(0,3) = 1;
       MBezier(1,0) = 3;
       MBezier(1,1) = -6;
       MBezier(1,2) = 3;
       MBezier(1,3) = 0;
       MBezier(2,0)= -3;
       MBezier(2,1) = 3;
       MBezier(2,2) = 0;
       MBezier(2,3) = 0;
       MBezier(3,0) = 1;
       MBezier(3,1) = 0;
       MBezier(3,2) = 0;
       MBezier(3,3) = 0;
       std::cout <<"MBezier矩阵"<< MBezier<<std::endl;
       InvertMatrix(MBezier, MBInverse);
       InvertMatrix(MBezier, mTmp);
       std::cout <<"MBezier逆矩阵 " <<mTmp <<std::endl;
       InvertMatrix(mTmp, mTmp);
       std::cout <<"MBezier逆矩阵的逆矩阵 " <<mTmp <<std::endl;
       std::cout <<"" <<std::endl;
#endif

#if 0
       //! \brief 三次B样条矩阵
       ublas::matrix<double> MBSpline(4,4),MBSInverse(4,4);
       MBSpline(0,0) = -1;
       MBSpline(0,1) = 3;
       MBSpline(0,2) = -3;
       MBSpline(0,3) = 1;
       MBSpline(1,0) = 3;
       MBSpline(1,1) = -6;
       MBSpline(1,2) = 3;
       MBSpline(1,3) = 0;
       MBSpline(2,0) = -3;
       MBSpline(2,1) = 0;
       MBSpline(2,2) = 3;
       MBSpline(2,3) = 0;
       MBSpline(3,0) = 1;
       MBSpline(3,1) = 4;
       MBSpline(3,2) = 1;
       MBSpline(3,3) = 0;
       std::cout <<"MBSpline矩阵"<< MBSpline<<std::endl;
       InvertMatrix(MBSpline, MBSInverse);
       InvertMatrix(MBSpline, mTmp);
       std::cout <<"MBSpline逆矩阵 " <<MBSInverse <<std::endl;
       ublas::matrix<double> mTmp1(4,4);
       InvertMatrix(mTmp, mTmp);
       std::cout <<"MBSpline逆矩阵的逆矩阵 " <<mTmp <<std::endl;
       std::cout <<"" <<std::endl;
#endif

       //system("pause");
       return 0;
} 

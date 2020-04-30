#include <iostream>
#include "boost/multi_array.hpp"
using namespace std;

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o boostmulti_array boostmulti_array.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./boostmulti_array
matrix A
1 3 -2 0 4 
-2 -1 5 -7 2 
0 8 4 1 -5 
3 -3 2 -4 1 

*
matrix B
4 5 -1 
2 -2 6 
7 8 1 
0 3 -5 
9 8 -6 

=
matrix C
32 15 -9 
43 27 24 
-1 -21 77 
29 33 -5 


*/

typedef boost::multi_array<int, 2> matrix; 

matrix matrix_multiply(matrix& a,matrix& b)
{
    matrix::index row=a.shape()[0];
    matrix::index col=b.shape()[1];
    matrix c(boost::extents[row][col]);

    for (matrix::index i=0; i!=a.shape()[0]; ++i)
        for (matrix::index j=0; j!=b.shape()[1]; ++j)
            for (matrix::index k=0; k!=a.shape()[1]; ++k)
                c[i][j]+=a[i][k]*b[k][j];

    return c;
}

void print(const matrix& m)
{
    for (matrix::index i=0; i!=m.shape()[0]; cout<<endl,++i)
        for (matrix::index j=0; j!=m.shape()[1]; ++j)
                cout<<m[i][j]<<" ";    
}

int main() {   

    int valuesA[] = {   
        1, 3, -2,0,4,   
        -2,-1, 5,-7,2,
		0,8,4,1,-5,
		3,-3,2,-4,1
    };
    int valuesB[] = {   
        4, 5,-1,   
        2, -2,6,
		7,8,1,
		0,3,-5,
		9,8,-6
    }; 
    const int valuesA_size = 20; 
    const int valuesB_size = 15;  
    matrix A(boost::extents[4][5]);  
    matrix B(boost::extents[5][3]);
    A.assign(valuesA,valuesA + valuesA_size);
    B.assign(valuesB,valuesB + valuesB_size);

	/*
    Dim mtxA(4, 5) As Double
    Dim mtxB(5, 3) As Double
    Dim mtxC(4, 3) As Double
    
    mtxA(1, 1) = 1: mtxA(1, 2) = 3: mtxA(1, 3) = -2: mtxA(1, 4) = 0: mtxA(1, 5) = 4
    mtxA(2, 1) = -2: mtxA(2, 2) = -1: mtxA(2, 3) = 5: mtxA(2, 4) = -7: mtxA(2, 5) = 2
    mtxA(3, 1) = 0: mtxA(3, 2) = 8: mtxA(3, 3) = 4: mtxA(3, 4) = 1: mtxA(3, 5) = -5
    mtxA(4, 1) = 3: mtxA(4, 2) = -3: mtxA(4, 3) = 2: mtxA(4, 4) = -4: mtxA(4, 5) = 1

    mtxB(1, 1) = 4: mtxB(1, 2) = 5: mtxB(1, 3) = -1
    mtxB(2, 1) = 2: mtxB(2, 2) = -2: mtxB(2, 3) = 6
    mtxB(3, 1) = 7: mtxB(3, 2) = 8: mtxB(3, 3) = 1
    mtxB(4, 1) = 0: mtxB(4, 2) = 3: mtxB(4, 3) = -5
    mtxB(5, 1) = 9: mtxB(5, 2) = 8: mtxB(5, 3) = -6
	*/

    cout<<"matrix A"<<endl;
    print(A);   
    cout<<endl;cout<<"*"<<endl;cout<<"matrix B"<<endl;
    print(B);   
    cout<<endl;cout<<"="<<endl;cout<<"matrix C"<<endl;
    print(matrix_multiply(A,B));
    cout<<endl;

    //system("pause");
    return 0;
} 
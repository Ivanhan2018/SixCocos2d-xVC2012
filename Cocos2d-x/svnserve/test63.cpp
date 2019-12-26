//  Æ½¾ùÊý
#include <iostream>
double mean(double *array, size_t n)
{
    double m=0;
    for(size_t i=0; i<n; ++i){
        m += array[i];
    }
    return m/n;
}

int main(void)
{
    double a[] = {1, 2, 3, 4, 5};
    std::cout<<mean(a, 5)<<std::endl;    // will print 3
    return 0;
}

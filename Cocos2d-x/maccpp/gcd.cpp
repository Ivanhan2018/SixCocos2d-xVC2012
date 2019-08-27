// gcd.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>

template<typename T>
T gcd(T x, T y) {
  while ( y != 0 ) {
    T z = x % y;
    x = y;
    y = z;
  }
  return x;
}

int main() {
  int inputX, inputY;

  std::cout << "Please enter x: ";
  std::cin >> inputX;
  std::cout << "Please enter y: ";
  std::cin >> inputY;

  std::cout << "The GCD of " << inputX
            << " and " << inputY
            << " is " << gcd(inputX,inputY) << std::endl;

  //system("pause");
  return 0;
}

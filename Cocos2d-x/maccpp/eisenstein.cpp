#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;
//http://shell.deru.com/~gdt/c/code/numbers/eisenstein.cpp
/*
 * This C++ program checks to see if a number is an Eisenstein prime.
 * Eisenstein primes adhere for the form:  3n - 1, where n is an integer.
 * The STDC Library functions floor(n) and ceil(n) are used to test if
 * the expression (n + 1)/3 yields an integer.
 *
 * @creator gdt
 * @created 2009.04.07
 * @cavents Doesn't do any sanity checking on the input.
 * @notes This code was written during a CSC100 class at SCC.
 * @see http://www.research.att.com/~njas/sequences/A003627
 */
int main(int argc, char* argv[]) {
   bool isprime(int), iseisenstein(int);   // function prototypes

   int n; cout << "Enter a positive integer: "; cin >> n;
   if (isprime(n) && iseisenstein(n)) 
      cout << n << " is an Eisenstein prime" << endl;
   //system("pause");
   return 0; 
} 


// Return true if the input is prime.
bool isprime(int n) {  
   if (n == 2) return true;
   if (n <= 1 || n % 2 == 0) return false;
   int limit = (int)sqrt(double(n)) + 1;
   for (int i = 3; i < limit; i++)
      if (n % i == 0) return false;
   return true;
}

// Return true if input is an Eisenstein prime.
bool iseisenstein(int n) {  
   double x = (n + 1) / 3.0;
   return floor(x) == ceil(x);
}




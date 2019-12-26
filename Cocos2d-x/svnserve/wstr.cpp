//The strings s1 & s2 are equal.
#include <string>
#include <iostream>
using namespace std;//vc8编译成功
int main()
{
   
   // Equivalent ways to declare an object of type
   // basic_string <wchar_t>
   const basic_string <wchar_t> s1(L"abc");
   wstring s2(L"abc"),s3(L"Abc");   // Uses the typedef for wstring
    
   // Comparison between two objects of type basic_string <wchar_t>
   if ( s1 == s2 )
      cout << "The strings s1 & s2 are equal." << endl;
   else
      cout << "The strings s1 & s2 are not equal." << endl;

   if ( s1 != s3 )
      cout << "The strings s1 & s3 are not equal." << endl;
   else
      cout << "The strings s1 & s3 are equal." << endl;

   return 0;
}

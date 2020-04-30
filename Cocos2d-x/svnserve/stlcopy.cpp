#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int binary(char *p, char **pp, int n)
{ 
   int low=0,high=n-1,mid;

   while (low<=high)
   {  mid=(low+high)/2;
      if (strcmp(p,pp[mid])<0) low=mid+1;
      else  if (strcmp(p,pp[mid])<0)  low=mid+1;
      else  return (mid);

   }
   return (-1);
}

int main(void)
{  
   char *cpu[]={"PentiumMMX","Celeron500","Pentium II","PentiumIII","Coppermine"};
   char *p; 
   int  i,j;
   
   vector<char *> vec(&cpu[0], &cpu[5]);
   copy(vec.begin(), vec.end(), ostream_iterator<char *>(cout, " "));
   cout << endl;   
   
   for(i=0;i<5;i++)
   {
	   printf("%s\n",cpu[i]);
   }
    printf("%d\n",binary("PentiumIII",cpu,5));//2
	return 0;
}
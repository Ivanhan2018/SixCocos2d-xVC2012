//VC-Console
#include <iostream> 
using namespace std;
 
int main()  
{
int n=4;
int i,j,k,p;
for(i=1;i<=n;i++) 
for(j=1;j<=n;j++) 
if(i!=j) 
for(k=1;k<=n;k++) 
if((k!=i)&&(k!=j)) 
for(p=1;p<=n;p++) 
if((p!=i)&&(p!=j)&&(p!=k)) 
cout<<i<<j<<k<<p<<endl; 
getchar(); 
return 0;

}
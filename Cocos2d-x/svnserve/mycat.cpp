//VC-Console
#include <cstring>
#include <iostream> 
#include <fstream>
using namespace std;
 
int main(int argc, char **argv)
{
char szp[100]={0};
if(argc<2)
{
	strcpy(szp,"/etc/hosts");
}
else
	strcpy(szp,argv[1]);
	
ifstream OpenFile(szp);
char ch, aa;
while(!OpenFile.eof())
{
OpenFile>>ch;
cout<<ch<<","<<(int)ch<<endl;
}
//cin>>aa;
return 0;
}
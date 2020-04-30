#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iterator>
using namespace std;

int main(int argc, char *argv[])
{
char alpha[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
int max       = strlen(alpha);
cout << "共有" << max << "个字符：" <<endl;
cout << alpha << endl;
char group[5];

//取5个字符
for ( int i = 0; i < 5; i ++ )
{
      int index    = rand() * max / RAND_MAX;
      group[i]     = alpha[index];
      alpha[index] = alpha[max--];
}

//输出所有排列
cout<< "随机5个字符的组合队列为：" << endl;
sort( group, group + 5 );
do
{
      ostream_iterator <char> oit( cout,"," );
      copy( group,group + 5,oit );
      cout << endl;
}while( next_permutation( group,group + 5 ));

return EXIT_SUCCESS;
}
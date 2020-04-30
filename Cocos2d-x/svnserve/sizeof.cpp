#include<stdlib.h>
#include<stdio.h>

void Foo(char str[100])
{
 int a=sizeof(str);
 printf("a=%d\n",a);
}

int main()
{
 //Foo(NULL);
 char sz[100];
 Foo(sz);

 int c=sizeof(sz);
 printf("c=%d\n",c);

 void *p=malloc(100);
 int b=sizeof(p);
 printf("b=%d\n",b);
 
#ifdef WIN32
 system("pause");
#endif
 return 0;
}
#include <iostream>
using namespace std;

struct family
{
char *husband;
char *wife;
char *son;
char *daughter;
};

int main()
{
// 关键字struct被省略掉了
family Anderson={"John Anderson","Mary Anderson","Joey Anderson","Marla Anderson"};
Anderson.husband="John1 Anderson";
Anderson.wife="Mary1 Anderson";
Anderson.son="Joey1 Anderson";
Anderson.daughter="Marla1 Anderson";

family *ptr = &Anderson;
cout<<"husband is "<<ptr->husband<<endl<<"wife is "<<ptr->wife<<endl<<"son is "<<ptr->son<<endl<<"daughter is "<<ptr->daughter<<endl;

return 0;
}
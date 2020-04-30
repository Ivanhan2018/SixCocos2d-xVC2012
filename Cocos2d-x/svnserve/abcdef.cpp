// 生成n阶对称群群元集合的不稳定算法abcdef.exe
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> v6;
vector<string> s6;

// 整型转变为字符串
string itos(int i)
{
 stringstream s;
 s << i;
 return s.str();
}

int GetRand(int a,int b){
 if(a>=b)
  return a;
 int iRet=rand()%(b-a+1)+a;
 return iRet;
}

string GenS6Element()
{
    string str;
    vector<int> v6c=v6;

    while(v6c.size()>0)
    {
  int i=GetRand(0,v6c.size()-1);
  if(v6c.size()==v6.size())
   str=str+"\"";
        str=str+itos(v6c[i]);
  if(v6c.size()==1)
   str=str+"\"";
  str=str+",";
  v6c.erase(v6c.begin()+i);
    }
    return str;
}

bool GenS6()
{
    while(s6.size()<720)
    {
  string str=GenS6Element();
  vector<string>::iterator iter = find(s6.begin(),s6.end(),str);
  if(iter!=s6.end()){
   //找到了
  }
  else{
  //找不到
   s6.push_back(str);
  }
    }
    return true;
}

 

int main() {
 time_t now=time(0);
 srand(now);
 for(int i=0;i<6;i++)
  v6.push_back(i+1);
 bool bRet=GenS6();
 string fn="abcdef"+itos(now)+".txt";
 ofstream fout(fn);
 fout << "static char *abcdef[] = {"<<endl;
 for(int i=0;i<s6.size();i++){
  fout<<s6[i]<<endl;
 }
 fout<<"};"<<endl;
 cout<<"bRet="<<bRet<<endl;
 //system("pause");
 return 0;
}

#include<iostream>
#include<string>
#include<sstream>
using namespace std;

// 整型转变为字符串
string itos(int i)         
{
  stringstream s;
  s << i;
  return s.str();
}

enum eWorldPhyle // 种族 need lua regedit
{
	P_TERRAN	= 0, // 人型系
	P_BEAST		= 1, // 野兽系
	P_PLANTS	= 2, // 植物系
	P_FLY		= 3, // 飞行系
	P_INSECT	= 4, // 昆虫系
	P_DRAGON	= 5, // 龙系
	P_PROTOSS	= 6, // 神系
	P_UNDEAD	= 7, // 不死系
	PHYLE_MAX,
};

const char * gszWorldPhyle[PHYLE_MAX] = {"灵智系", "蛮荒系", "地脉系", "天羽系", "蜚廉系", "瑞兽系", "神巫系", "幽冥系"};
const char * getWorldPhyle(int Phyle)
{
   if(Phyle >= P_TERRAN && Phyle < PHYLE_MAX)
	return gszWorldPhyle[Phyle];
   else
        return "";
}

int main(int argc, char *argv[])
{
/* 	int i = 127;
	string ss = itos(i);
	const char* p = ss.c_str();
	cout << ss << " " << p << "\n"; */
	if( argc < 2 )
	{
		printf("Usage:  itos arg1\n");
		return 1;
	}	
	int Phyle=atoi(argv[1]);
	const char* p = getWorldPhyle(Phyle);
	cout << Phyle << "=>" << p << "\n";
	
	return 0;
}
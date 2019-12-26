#include<iostream>
using namespace std;

typedef enum : short int//int
{
	PType_Launcher = -1,         //关闭所有效果(-1)
	PType_Default  =0,           //默认箭阵效果
	PType_Blast    =1,          //爆炸
	PType_Magic    =2,          //魔法圈
	PType_MagicAttack=3,        //魔法攻击，一团粒子攻向目标，到达之后炸开
}FV_TYPE;

int main(int argc, char* argv[])
{
    cout<<sizeof(FV_TYPE)<<endl;
    return 0;
}
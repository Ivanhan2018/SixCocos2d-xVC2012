#include<complex>//复数
#include<iostream>
using namespace std;

/*
root@iZ14rcmneyrcltZ:~/cpptest/lua# g++ -o calccomplex calccomplex.cpp -I /usr/include/lua5.1/ -llua5.1
root@iZ14rcmneyrcltZ:~/cpptest/lua# ./calccomplex
5	53.130147231271
*/

//0.包含lua头文件
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

//C函数，做复数计算，输入实部，虚部。输出绝对值和角度
int calcComplex(lua_State *L)
{
    //从栈中读入实部，虚部
    double r = luaL_checknumber(L,1);
    double i = luaL_checknumber(L,2);
    complex<double> c(r,i);
    //存入绝对值
    lua_pushnumber(L,abs(c));
    //存入角度
    lua_pushnumber(L,arg(c)*180.0/3.14159);
    return 2;//两个结果
}

//5       53.130147231271
int main()
{
    char *szLua_code =
        "v,a = CalcComplex(3,4) "
        "print(v,a)";
 
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
   
    //放入C函数
    lua_pushcfunction(L, calcComplex);
    lua_setglobal(L, "CalcComplex");
   
    //执行
    bool err = luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0);
    if(err)
    {
        cerr << lua_tostring(L, -1);
        lua_pop(L, 1);
    }
 
    lua_close(L);
    //getchar();
    return 0;
}
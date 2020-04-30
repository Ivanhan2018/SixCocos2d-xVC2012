#include <stdio.h>
#include <math.h>
/*
root@iZ14rcmneyrcltZ:~/cpptest/lua# g++ -o luatest2 luatest2.cpp -I /usr/include/lua5.1/ -llua5.1
root@iZ14rcmneyrcltZ:~/cpptest/lua# ./luatest2
The sum is 21
luapythagorean(3,4)=5.000000
*/

//0.包含lua头文件
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

/* the Lua interpreter */
lua_State  * L;
int luaadd(int x,int y)
{
    int sum;
    //函数名
    lua_getglobal(L, "add");
    //第一个参数压栈
    lua_pushnumber(L, x);
    //第二个参数压栈
    lua_pushnumber(L, y);
    //调用函数
    lua_call(L, 2, 1);
    //得到返回值
    sum=(int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return sum;
}
double luapythagorean(double x,double y)
{
    double ret;
    //函数名
    lua_getglobal(L, "pythagorean");
    //第一个参数压栈
    lua_pushnumber(L, x);
    //第二个参数压栈
    lua_pushnumber(L, y);
    //调用函数
    lua_call(L, 2, 1);
    //得到返回值
    ret=(double)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}
double luafun(double x)
{
    double ret;
    //函数名
    lua_getglobal(L, "fun");
    //第一个参数压栈
    lua_pushnumber(L, x);
    //调用函数
    lua_call(L, 1, 1);
    //得到返回值
    ret=(double)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}
int main ( int argc, char *argv[] )
{
    int sum;
    double ret;
    //initialize Lua创建一个指向Lua解释器的指针。
    L=lua_open();
    //load Lua base libraries函数加载Lua库
    luaL_openlibs(L);
    //run the script加载脚本
    luaL_dofile(L,"test2.lua");
    //调用函数
    sum=luaadd(10, 11);
    ret=luapythagorean(3,4);
    // print the result
    printf("The sum is %d\n", sum);
    printf("luapythagorean(3,4)=%f\n",ret);

    //cleanup Lua关闭 释放资源
    lua_close(L);
    //getchar();
    return 0;
}
#include <stdio.h>

/*
root@iZ14rcmneyrcltZ:~/cpptest/lua# g++ -o luatest luatest.cpp -I /usr/include/lua5.1/ -llua5.1
root@iZ14rcmneyrcltZ:~/cpptest/lua# ./luatest
Hello, World!
*/

//0.包含lua头文件
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

/* C调用lua的函数 */
int helloAdd(lua_State* pL,int num1,int num2) {
    lua_getglobal(pL, "helloAdd");
    /* 把函数所需要的参数入栈 */
    lua_pushnumber(pL, num1);
    lua_pushnumber(pL, num2);
    /* 
        执行函数，第一个参数表示函数的参数个数，第二个参数表示函数返回值个数 ，
        Lua会先去堆栈取出参数，然后再取出函数对象，开始执行函数
    */
    lua_call(pL, 2, 1);
    int iResult = lua_tonumber(pL, -1);
	return iResult;
}

/* the Lua interpreter */
lua_State* L;
int main ( int argc, char *argv[] )
{
 /* initialize Lua */
 L = lua_open();
 /* load Lua base libraries */
 luaL_openlibs(L);
 //luaopen_base(pL);
 /* run the script */
 luaL_dofile(L, "test.lua");
 int num1=10;
 int num2=5;
 int sum=helloAdd(L,num1,num2);
 printf("%d+%d=%d\n",num1,num2,sum);
 /* cleanup Lua */
 lua_close(L);
 /* pause */
 printf( "Press enter to exit..." );
 //getchar();
 return 0;
}
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

/* the Lua interpreter */
lua_State* L;
int main (int argc, char *argv[])
{
    char *sz="test.lua";
	if( argc >= 2 )
	{
		sz=argv[1];
	}	

 /* initialize Lua */
 L = lua_open();
 /* load Lua base libraries */
 luaL_openlibs(L);
 
 /* run the script */
 luaL_dofile(L, sz);
 /* cleanup Lua */
 lua_close(L);
 /* pause */
 //printf( "Press enter to exit..." );
 //getchar();
 return 0;
}
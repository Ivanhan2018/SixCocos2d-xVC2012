#include <stdio.h>

/*
root@iZ14rcmneyrcltZ:~/cpptest/lua# g++ -o luatest3 luatest3.cpp -I /usr/include/lua5.1/ -llua5.1
root@iZ14rcmneyrcltZ:~/cpptest/lua# ./luatest3
true10nil'hello'
true10nil'hello'true
true10true'hello'
true10true'hello'nilnil
true10truenilnil
true
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

static void stackDump(lua_State* L) 
 {
     int top = lua_gettop(L);
     for (int i = 1; i <= top; ++i) {
        int t = lua_type(L,i);
         switch(t) {
         case LUA_TSTRING:
             printf("'%s'",lua_tostring(L,i));
             break;
         case LUA_TBOOLEAN:
             printf(lua_toboolean(L,i) ? "true" : "false");
            break;
         case LUA_TNUMBER:
             printf("%g",lua_tonumber(L,i));
             break;
         default:
             printf("%s",lua_typename(L,t));
             break;
         }
         printf("");
     }
     printf("\n");
 }

int main ( int argc, char *argv[] )
{
lua_State* L = luaL_newstate();
lua_pushboolean(L,1);
lua_pushnumber(L,10);
lua_pushnil(L);
lua_pushstring(L,"hello");
stackDump(L); //true 10 nil 'hello'

lua_pushvalue(L,-4);
stackDump(L); //true 10 nil 'hello' true

lua_replace(L,3);
stackDump(L); //true 10 true 'hello'

lua_settop(L,6);
stackDump(L); //true 10 true 'hello' nil nil

lua_remove(L,-3);
stackDump(L); //true 10 true nil nil

lua_settop(L,-5);
stackDump(L); //true

lua_close(L);
return 0;
}
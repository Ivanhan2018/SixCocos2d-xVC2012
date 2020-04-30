#include <iostream>
#include <stdio.h>
extern "C" 
{
 #include "lua.h"
 #include "lualib.h"
 #include "lauxlib.h"
}

//g++ -o DATE DATE.cpp -I /usr/include/lua5.1/ -llua5.1
class DATE
{
public:
	DATE() { month=day=year=0; }
	DATE( int m, int d, int y)
	{
		month=m;
		day=d;
		year=y;
	}
	void print()
	{
		std::cout<<"Month="<<month<<",Day="<<day<<",Year="<<year<<std::endl;
	}
private:
	int month, day, year;
};
 
void stackDump(lua_State *L)
{
	int i;
	int top = lua_gettop(L);
	printf("the size of stack is:%d\n",top);
	for ( i = 1;i <= top;i++ )
	{
		int type = lua_type(L, i);
		switch(type)
		{
		case LUA_TSTRING:
			{
				printf("%s",lua_tostring(L, i));
				break;
			}
 
		case LUA_TBOOLEAN:
			{
				printf(lua_toboolean(L, i)?"true":"false");
				break;
			}
		case LUA_TNUMBER:
			{
				printf("%g",lua_tonumber(L, i));
				break;
			}
		case LUA_TTABLE:
			{
				printf("this is a table!");
				break;
			}
		default:
			{
				printf("%s",lua_typename(L ,i));
				break;
			}
		}
		printf(" ");
	}
	printf("\n");
}
 
//获取lua文件中类型为表的变量
void loadConfigTable(lua_State *L,const char *fname, int *w, int *h)
{
	if ( luaL_loadfile(L, fname) || lua_pcall(L,0,0,0) )
		printf("error,can't run config file:%s:\n",lua_tostring(L,-1));
	stackDump(L);
	lua_getglobal(L, "MDY");	//获取lua文件中的表MDY，压入栈顶
	if ( !lua_istable(L, -1) ) 
		printf("error,MDY is not a table\n");
	stackDump(L);
	lua_getfield(L, -1, "Month");	//获取MDY表中key为Month的value。获取前MDY表位于栈顶
	if ( !lua_isnumber(L,-1) )
		printf("error,Month is not a number\n");
	stackDump(L);
	*w = lua_tointeger(L, -1);
	lua_pop(L, 1);				//从栈中弹出一个元素，即弹出栈顶值
	lua_getfield(L, -1, "Day");
	if ( !lua_isnumber(L, -1) )
		printf("error,Day is not a number\n");
	stackDump(L);
	*h = lua_tointeger(L, -1);
}
 
/* the Lua interpreter */
lua_State* L;
int main (int argc, char *argv[])
{
	DATE dates[] = { DATE(7, 22, 1998), DATE(7, 23, 1998), DATE(7, 24, 1998), DATE(7, 25, 1998), DATE(7, 26, 1998) };
	int n=sizeof(dates)/sizeof(dates[0]);
	for (int i=0; i<n; i++)
		dates[i].print();

	/* initialize Lua */
	L = lua_open();
	/* load Lua base libraries */
	luaL_openlibs(L);
	/* run the script */
    {	
		int i = 0;
		int j = 0;
		loadConfigTable(L, "DATE.lua", &i, &j);
		printf("the value of i,j is %d,%d\n",i,j);
    }
	/* cleanup Lua */
	lua_close(L);
	return 0;
}
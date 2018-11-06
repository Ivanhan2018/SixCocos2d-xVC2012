/*
** Lua binding: SIX_Proxy
** Generated automatically by tolua++-1.0.92 on 05/20/13 13:08:07.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_Proxy_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_Proxy (lua_State* tolua_S)
{
 SIX_Proxy* self = (SIX_Proxy*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_Proxy_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_Proxy");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"MSG_INFO");
 tolua_usertype(tolua_S,"TSingleton<SIX_Proxy>");
}

/* method: new of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_new00
static int tolua_SIX_Proxy_SIX_Proxy_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Proxy* tolua_ret = (SIX_Proxy*)  Mtolua_new((SIX_Proxy)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Proxy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_new00_local
static int tolua_SIX_Proxy_SIX_Proxy_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Proxy* tolua_ret = (SIX_Proxy*)  Mtolua_new((SIX_Proxy)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Proxy");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_delete00
static int tolua_SIX_Proxy_SIX_Proxy_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_GetInstance00
static int tolua_SIX_Proxy_SIX_Proxy_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Proxy* tolua_ret = (SIX_Proxy*)  SIX_Proxy::GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Proxy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PushEvent of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_PushEvent00
static int tolua_SIX_Proxy_SIX_Proxy_PushEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
  MSG_INFO* pEvent = ((MSG_INFO*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PushEvent'", NULL);
#endif
  {
   self->PushEvent(pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PushEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PopEvent of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_PopEvent00
static int tolua_SIX_Proxy_SIX_Proxy_PopEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PopEvent'", NULL);
#endif
  {
   MSG_INFO* tolua_ret = (MSG_INFO*)  self->PopEvent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MSG_INFO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PopEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FrontEvent of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_FrontEvent00
static int tolua_SIX_Proxy_SIX_Proxy_FrontEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FrontEvent'", NULL);
#endif
  {
   MSG_INFO* tolua_ret = (MSG_INFO*)  self->FrontEvent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MSG_INFO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FrontEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEventCount of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_GetEventCount00
static int tolua_SIX_Proxy_SIX_Proxy_GetEventCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEventCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetEventCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEventCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: WaitForExit of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_SIX_Proxy_SIX_Proxy_WaitForExit00
static int tolua_SIX_Proxy_SIX_Proxy_WaitForExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Proxy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'WaitForExit'", NULL);
#endif
  {
   self->WaitForExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'WaitForExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __TSingleton<SIX_Proxy>__ of class  SIX_Proxy */
#ifndef TOLUA_DISABLE_tolua_get_SIX_Proxy___TSingleton_SIX_Proxy___
static int tolua_get_SIX_Proxy___TSingleton_SIX_Proxy___(lua_State* tolua_S)
{
  SIX_Proxy* self = (SIX_Proxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__TSingleton<SIX_Proxy>__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<TSingleton<SIX_Proxy>*>(self), "TSingleton<SIX_Proxy>");
#else
   tolua_pushusertype(tolua_S,(void*)((TSingleton<SIX_Proxy>*)self), "TSingleton<SIX_Proxy>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_Proxy_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_Proxy_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_Proxy","SIX_Proxy","CCNode",tolua_collect_SIX_Proxy);
  #else
  tolua_cclass(tolua_S,"SIX_Proxy","SIX_Proxy","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_Proxy");
   tolua_function(tolua_S,"new",tolua_SIX_Proxy_SIX_Proxy_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Proxy_SIX_Proxy_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Proxy_SIX_Proxy_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Proxy_SIX_Proxy_delete00);
   tolua_function(tolua_S,"GetInstance",tolua_SIX_Proxy_SIX_Proxy_GetInstance00);
   tolua_function(tolua_S,"PushEvent",tolua_SIX_Proxy_SIX_Proxy_PushEvent00);
   tolua_function(tolua_S,"PopEvent",tolua_SIX_Proxy_SIX_Proxy_PopEvent00);
   tolua_function(tolua_S,"FrontEvent",tolua_SIX_Proxy_SIX_Proxy_FrontEvent00);
   tolua_function(tolua_S,"GetEventCount",tolua_SIX_Proxy_SIX_Proxy_GetEventCount00);
   tolua_function(tolua_S,"WaitForExit",tolua_SIX_Proxy_SIX_Proxy_WaitForExit00);
   tolua_variable(tolua_S,"__TSingleton_SIX_Proxy___",tolua_get_SIX_Proxy___TSingleton_SIX_Proxy___,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_Proxy (lua_State* tolua_S) {
 return tolua_SIX_Proxy_open(tolua_S);
};
#endif


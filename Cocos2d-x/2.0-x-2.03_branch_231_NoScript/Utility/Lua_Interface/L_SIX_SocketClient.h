/*
** Lua binding: SIX_SocketClient
** Generated automatically by tolua++-1.0.92 on 04/19/13 13:33:38.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_SocketClient_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_SocketClient (lua_State* tolua_S)
{
 SIX_SocketClient* self = (SIX_SocketClient*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_SocketClient_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_Socket");
 tolua_usertype(tolua_S,"SIX_Thread");
 tolua_usertype(tolua_S,"MSG_INFO");
 tolua_usertype(tolua_S,"SIX_SocketClient");
}

/* method: new of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_new00
static int tolua_SIX_SocketClient_SIX_SocketClient_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int protocol = ((int)  tolua_tonumber(tolua_S,2,TCP));
  {
   SIX_SocketClient* tolua_ret = (SIX_SocketClient*)  Mtolua_new((SIX_SocketClient)(protocol));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SocketClient");
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

/* method: new_local of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_new00_local
static int tolua_SIX_SocketClient_SIX_SocketClient_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int protocol = ((int)  tolua_tonumber(tolua_S,2,TCP));
  {
   SIX_SocketClient* tolua_ret = (SIX_SocketClient*)  Mtolua_new((SIX_SocketClient)(protocol));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SocketClient");
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

/* method: delete of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_delete00
static int tolua_SIX_SocketClient_SIX_SocketClient_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setJoinable of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_setJoinable00
static int tolua_SIX_SocketClient_SIX_SocketClient_setJoinable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_Thread",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
  SIX_Thread* pThread = ((SIX_Thread*)  tolua_tousertype(tolua_S,2,0));
  bool joinable = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setJoinable'", NULL);
#endif
  {
   self->setJoinable(pThread,joinable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setJoinable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsJoinable of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_IsJoinable00
static int tolua_SIX_SocketClient_SIX_SocketClient_IsJoinable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_Thread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
  SIX_Thread* pThread = ((SIX_Thread*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsJoinable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsJoinable(pThread);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsJoinable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PushMsg of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_PushMsg00
static int tolua_SIX_SocketClient_SIX_SocketClient_PushMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
  MSG_INFO* pMsg = ((MSG_INFO*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PushMsg'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PushMsg(pMsg);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PushMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PopMsg of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_PopMsg00
static int tolua_SIX_SocketClient_SIX_SocketClient_PopMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PopMsg'", NULL);
#endif
  {
   MSG_INFO* tolua_ret = (MSG_INFO*)  self->PopMsg();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MSG_INFO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PopMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FrontMsg of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_FrontMsg00
static int tolua_SIX_SocketClient_SIX_SocketClient_FrontMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FrontMsg'", NULL);
#endif
  {
   MSG_INFO* tolua_ret = (MSG_INFO*)  self->FrontMsg();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MSG_INFO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FrontMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CleanMsg of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_CleanMsg00
static int tolua_SIX_SocketClient_SIX_SocketClient_CleanMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CleanMsg'", NULL);
#endif
  {
   self->CleanMsg();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CleanMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMsgCount of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_GetMsgCount00
static int tolua_SIX_SocketClient_SIX_SocketClient_GetMsgCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMsgCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetMsgCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMsgCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStats of class  SIX_SocketClient */
#ifndef TOLUA_DISABLE_tolua_SIX_SocketClient_SIX_SocketClient_GetStats00
static int tolua_SIX_SocketClient_SIX_SocketClient_GetStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SocketClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SocketClient* self = (SIX_SocketClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStats'", NULL);
#endif
  {
   self->GetStats();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_SocketClient_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_SocketClient_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_SocketClient","SIX_SocketClient","SIX_Socket",tolua_collect_SIX_SocketClient);
  #else
  tolua_cclass(tolua_S,"SIX_SocketClient","SIX_SocketClient","SIX_Socket",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_SocketClient");
   tolua_function(tolua_S,"new",tolua_SIX_SocketClient_SIX_SocketClient_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_SocketClient_SIX_SocketClient_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_SocketClient_SIX_SocketClient_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_SocketClient_SIX_SocketClient_delete00);
   tolua_function(tolua_S,"setJoinable",tolua_SIX_SocketClient_SIX_SocketClient_setJoinable00);
   tolua_function(tolua_S,"IsJoinable",tolua_SIX_SocketClient_SIX_SocketClient_IsJoinable00);
   tolua_function(tolua_S,"PushMsg",tolua_SIX_SocketClient_SIX_SocketClient_PushMsg00);
   tolua_function(tolua_S,"PopMsg",tolua_SIX_SocketClient_SIX_SocketClient_PopMsg00);
   tolua_function(tolua_S,"FrontMsg",tolua_SIX_SocketClient_SIX_SocketClient_FrontMsg00);
   tolua_function(tolua_S,"CleanMsg",tolua_SIX_SocketClient_SIX_SocketClient_CleanMsg00);
   tolua_function(tolua_S,"GetMsgCount",tolua_SIX_SocketClient_SIX_SocketClient_GetMsgCount00);
   tolua_function(tolua_S,"GetStats",tolua_SIX_SocketClient_SIX_SocketClient_GetStats00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_SocketClient (lua_State* tolua_S) {
 return tolua_SIX_SocketClient_open(tolua_S);
};
#endif


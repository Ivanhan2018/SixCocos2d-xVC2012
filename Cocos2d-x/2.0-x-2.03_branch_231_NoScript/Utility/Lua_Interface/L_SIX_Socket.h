/*
** Lua binding: SIX_Socket
** Generated automatically by tolua++-1.0.92 on 04/19/13 12:06:34.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_Socket_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_Socket (lua_State* tolua_S)
{
 SIX_Socket* self = (SIX_Socket*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_Socket_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_Socket");
}

/* method: new of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_new00
static int tolua_SIX_Socket_SIX_Socket_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int protocol = ((int)  tolua_tonumber(tolua_S,2,TCP));
  {
   SIX_Socket* tolua_ret = (SIX_Socket*)  Mtolua_new((SIX_Socket)(protocol));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Socket");
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

/* method: new_local of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_new00_local
static int tolua_SIX_Socket_SIX_Socket_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int protocol = ((int)  tolua_tonumber(tolua_S,2,TCP));
  {
   SIX_Socket* tolua_ret = (SIX_Socket*)  Mtolua_new((SIX_Socket)(protocol));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Socket");
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

/* method: delete of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_delete00
static int tolua_SIX_Socket_SIX_Socket_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
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

/* method: OnRecv of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_OnRecv00
static int tolua_SIX_Socket_SIX_Socket_OnRecv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  const char* pData = ((const char*)  tolua_tostring(tolua_S,2,0));
  int pLen = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRecv'", NULL);
#endif
  {
   self->OnRecv(pData,pLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRecv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnClose of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_OnClose00
static int tolua_SIX_Socket_SIX_Socket_OnClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnClose'", NULL);
#endif
  {
   self->OnClose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_Init00
static int tolua_SIX_Socket_SIX_Socket_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
  {
   self->Init();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOPT of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_SetOPT00
static int tolua_SIX_Socket_SIX_Socket_SetOPT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  int optname = ((int)  tolua_tonumber(tolua_S,3,0));
  void* optval = ((void*)  tolua_touserdata(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOPT'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetOPT(level,optname,optval);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOPT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAsynMode of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_SetAsynMode00
static int tolua_SIX_Socket_SIX_Socket_SetAsynMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  bool isAsyn = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAsynMode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetAsynMode(isAsyn);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAsynMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_Connect00
static int tolua_SIX_Socket_SIX_Socket_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  const char* addr = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  int waitTime = ((int)  tolua_tonumber(tolua_S,4,5));
  bool Asyn = ((bool)  tolua_toboolean(tolua_S,5,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Connect(addr,port,waitTime,Asyn);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Recv of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_Recv00
static int tolua_SIX_Socket_SIX_Socket_Recv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  int flag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Recv'", NULL);
#endif
  {
   self->Recv(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Recv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Send of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_Send00
static int tolua_SIX_Socket_SIX_Socket_Send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  const char* buf = ((const char*)  tolua_tostring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  int flags = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Send'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Send(buf,len,flags);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_Close00
static int tolua_SIX_Socket_SIX_Socket_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Close();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetError of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_GetError00
static int tolua_SIX_Socket_SIX_Socket_GetError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetError'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetError();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsConnected of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_IsConnected00
static int tolua_SIX_Socket_SIX_Socket_IsConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsConnected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsConnected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConnected of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_SetConnected00
static int tolua_SIX_Socket_SIX_Socket_SetConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
  bool connected = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConnected'", NULL);
#endif
  {
   self->SetConnected(connected);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInvalid of class  SIX_Socket */
#ifndef TOLUA_DISABLE_tolua_SIX_Socket_SIX_Socket_IsInvalid00
static int tolua_SIX_Socket_SIX_Socket_IsInvalid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Socket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Socket* self = (SIX_Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInvalid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInvalid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInvalid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_Socket_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_Socket_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_Socket","SIX_Socket","",tolua_collect_SIX_Socket);
  #else
  tolua_cclass(tolua_S,"SIX_Socket","SIX_Socket","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_Socket");
   tolua_function(tolua_S,"new",tolua_SIX_Socket_SIX_Socket_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Socket_SIX_Socket_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Socket_SIX_Socket_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Socket_SIX_Socket_delete00);
   tolua_function(tolua_S,"OnRecv",tolua_SIX_Socket_SIX_Socket_OnRecv00);
   tolua_function(tolua_S,"OnClose",tolua_SIX_Socket_SIX_Socket_OnClose00);
   tolua_function(tolua_S,"Init",tolua_SIX_Socket_SIX_Socket_Init00);
   tolua_function(tolua_S,"SetOPT",tolua_SIX_Socket_SIX_Socket_SetOPT00);
   tolua_function(tolua_S,"SetAsynMode",tolua_SIX_Socket_SIX_Socket_SetAsynMode00);
   tolua_function(tolua_S,"Connect",tolua_SIX_Socket_SIX_Socket_Connect00);
   tolua_function(tolua_S,"Recv",tolua_SIX_Socket_SIX_Socket_Recv00);
   tolua_function(tolua_S,"Send",tolua_SIX_Socket_SIX_Socket_Send00);
   tolua_function(tolua_S,"Close",tolua_SIX_Socket_SIX_Socket_Close00);
   tolua_function(tolua_S,"GetError",tolua_SIX_Socket_SIX_Socket_GetError00);
   tolua_function(tolua_S,"IsConnected",tolua_SIX_Socket_SIX_Socket_IsConnected00);
   tolua_function(tolua_S,"SetConnected",tolua_SIX_Socket_SIX_Socket_SetConnected00);
   tolua_function(tolua_S,"IsInvalid",tolua_SIX_Socket_SIX_Socket_IsInvalid00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_Socket (lua_State* tolua_S) {
 return tolua_SIX_Socket_open(tolua_S);
};
#endif


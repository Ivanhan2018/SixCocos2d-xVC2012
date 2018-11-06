/*
** Lua binding: SIX_ClientLogic
** Generated automatically by tolua++-1.0.92 on 05/22/13 18:46:24.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_ClientLogic_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_ClientLogic (lua_State* tolua_S)
{
 SIX_ClientLogic* self = (SIX_ClientLogic*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_ClientLogic_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"BYTE");
 tolua_usertype(tolua_S,"SIX_ClientLogic");
 tolua_usertype(tolua_S,"sockaddr_in");
 tolua_usertype(tolua_S,"IBaseTableClient");
}

/* method: new of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_new00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_ClientLogic* tolua_ret = (SIX_ClientLogic*)  Mtolua_new((SIX_ClientLogic)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ClientLogic");
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

/* method: new_local of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_new00_local
static int tolua_SIX_ClientLogic_SIX_ClientLogic_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_ClientLogic* tolua_ret = (SIX_ClientLogic*)  Mtolua_new((SIX_ClientLogic)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ClientLogic");
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

/* method: delete of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_delete00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
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

/* method: OnConnect of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnConnect00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"sockaddr_in",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  bool bIsReconnect = ((bool)  tolua_toboolean(tolua_S,2,0));
  sockaddr_in addrConnect = *((sockaddr_in*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnConnect'", NULL);
#endif
  {
   self->OnConnect(bIsReconnect,addrConnect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnConnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnConnectFail of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnConnectFail00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnConnectFail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"sockaddr_in",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  bool bIsReconnect = ((bool)  tolua_toboolean(tolua_S,2,0));
  int iError = ((int)  tolua_tonumber(tolua_S,3,0));
  sockaddr_in addrConnect = *((sockaddr_in*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnConnectFail'", NULL);
#endif
  {
   self->OnConnectFail(bIsReconnect,iError,addrConnect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnConnectFail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnCommError of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnCommError00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnCommError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  char* pszError = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnCommError'", NULL);
#endif
  {
   self->OnCommError(pszError);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnCommError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSend of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnSend00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnSend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const BYTE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  const BYTE* pData = ((const BYTE*)  tolua_tousertype(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSend'", NULL);
#endif
  {
   self->OnSend(iMainCode,iSubCode,pData,iDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSendFailed of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnSendFailed00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnSendFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const BYTE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  const BYTE* pData = ((const BYTE*)  tolua_tousertype(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSendFailed'", NULL);
#endif
  {
   self->OnSendFailed(iMainCode,iSubCode,pData,iDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSendFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnClose of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnClose00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  bool bClientClose = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnClose'", NULL);
#endif
  {
   self->OnClose(bClientClose);
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

/* method: OnTableMsg of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_OnTableMsg00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_OnTableMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const BYTE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  const BYTE* pData = ((const BYTE*)  tolua_tousertype(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnTableMsg'", NULL);
#endif
  {
   self->OnTableMsg(iMainCode,iSubCode,pData,iDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnTableMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNeedExit of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_IsNeedExit00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_IsNeedExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNeedExit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNeedExit();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNeedExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_stop00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   int tolua_ret = (int)  self->stop();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: test of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_test00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'test'", NULL);
#endif
  {
   int tolua_ret = (int)  self->test();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fire of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_fire00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_fire00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fire'", NULL);
#endif
  {
   int tolua_ret = (int)  self->fire();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fire'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RandomUser of class  SIX_ClientLogic */
#ifndef TOLUA_DISABLE_tolua_SIX_ClientLogic_SIX_ClientLogic_RandomUser00
static int tolua_SIX_ClientLogic_SIX_ClientLogic_RandomUser00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ClientLogic",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ClientLogic* self = (SIX_ClientLogic*)  tolua_tousertype(tolua_S,1,0);
  char* pszName = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RandomUser'", NULL);
#endif
  {
   int tolua_ret = (int)  self->RandomUser(pszName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RandomUser'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_ClientLogic_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_ClientLogic_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_ClientLogic","SIX_ClientLogic","IBaseTableClient",tolua_collect_SIX_ClientLogic);
  #else
  tolua_cclass(tolua_S,"SIX_ClientLogic","SIX_ClientLogic","IBaseTableClient",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_ClientLogic");
   tolua_function(tolua_S,"new",tolua_SIX_ClientLogic_SIX_ClientLogic_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_ClientLogic_SIX_ClientLogic_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_ClientLogic_SIX_ClientLogic_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_ClientLogic_SIX_ClientLogic_delete00);
   tolua_function(tolua_S,"OnConnect",tolua_SIX_ClientLogic_SIX_ClientLogic_OnConnect00);
   tolua_function(tolua_S,"OnConnectFail",tolua_SIX_ClientLogic_SIX_ClientLogic_OnConnectFail00);
   tolua_function(tolua_S,"OnCommError",tolua_SIX_ClientLogic_SIX_ClientLogic_OnCommError00);
   tolua_function(tolua_S,"OnSend",tolua_SIX_ClientLogic_SIX_ClientLogic_OnSend00);
   tolua_function(tolua_S,"OnSendFailed",tolua_SIX_ClientLogic_SIX_ClientLogic_OnSendFailed00);
   tolua_function(tolua_S,"OnClose",tolua_SIX_ClientLogic_SIX_ClientLogic_OnClose00);
   tolua_function(tolua_S,"OnTableMsg",tolua_SIX_ClientLogic_SIX_ClientLogic_OnTableMsg00);
   tolua_function(tolua_S,"IsNeedExit",tolua_SIX_ClientLogic_SIX_ClientLogic_IsNeedExit00);
   tolua_function(tolua_S,"stop",tolua_SIX_ClientLogic_SIX_ClientLogic_stop00);
   tolua_function(tolua_S,"test",tolua_SIX_ClientLogic_SIX_ClientLogic_test00);
   tolua_function(tolua_S,"fire",tolua_SIX_ClientLogic_SIX_ClientLogic_fire00);
   tolua_function(tolua_S,"RandomUser",tolua_SIX_ClientLogic_SIX_ClientLogic_RandomUser00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_ClientLogic (lua_State* tolua_S) {
 return tolua_SIX_ClientLogic_open(tolua_S);
};
#endif


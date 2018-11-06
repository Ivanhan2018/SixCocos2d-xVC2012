/*
** Lua binding: UserInfo
** Generated automatically by tolua++-1.0.92 on 05/23/13 16:14:37.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_UserInfo_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_USER_INFO (lua_State* tolua_S)
{
 USER_INFO* self = (USER_INFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_UserInfo_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DATA_BASE<USER_INFO>");
 tolua_usertype(tolua_S,"USER_INFO");
 tolua_usertype(tolua_S,"EASY_DATA_TIME");
}

/* method: new of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_UserInfo_USER_INFO_new00
static int tolua_UserInfo_USER_INFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"USER_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   USER_INFO* tolua_ret = (USER_INFO*)  Mtolua_new((USER_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"USER_INFO");
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

/* method: new_local of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_UserInfo_USER_INFO_new00_local
static int tolua_UserInfo_USER_INFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"USER_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   USER_INFO* tolua_ret = (USER_INFO*)  Mtolua_new((USER_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"USER_INFO");
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

/* method: ClearServerInfo of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_UserInfo_USER_INFO_ClearServerInfo00
static int tolua_UserInfo_USER_INFO_ClearServerInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"USER_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearServerInfo'", NULL);
#endif
  {
   self->ClearServerInfo();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearServerInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lUserId of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_lUserId
static int tolua_get_USER_INFO_lUserId(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lUserId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lUserId of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_lUserId
static int tolua_set_USER_INFO_lUserId(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lUserId = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_szName
static int tolua_get_USER_INFO_szName(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_szName
static int tolua_set_USER_INFO_szName(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szName,(const char*)tolua_tostring(tolua_S,2,0),USER_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szPassword of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_szPassword
static int tolua_get_USER_INFO_szPassword(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szPassword'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szPassword);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szPassword of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_szPassword
static int tolua_set_USER_INFO_szPassword(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szPassword'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szPassword,(const char*)tolua_tostring(tolua_S,2,0),USER_PASSWORD_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szNickname of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_szNickname
static int tolua_get_USER_INFO_szNickname(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szNickname'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szNickname);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szNickname of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_szNickname
static int tolua_set_USER_INFO_szNickname(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szNickname'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szNickname,(const char*)tolua_tostring(tolua_S,2,0),USER_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stRegistTime of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_stRegistTime
static int tolua_get_USER_INFO_stRegistTime(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stRegistTime'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->stRegistTime,"EASY_DATA_TIME");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stRegistTime of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_stRegistTime
static int tolua_set_USER_INFO_stRegistTime(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stRegistTime'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"EASY_DATA_TIME",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stRegistTime = *((EASY_DATA_TIME*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stUserState of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_stUserState
static int tolua_get_USER_INFO_stUserState(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stUserState'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->stUserState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stUserState of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_stUserState
static int tolua_set_USER_INFO_stUserState(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stUserState'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stUserState = ((USER_STATE) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iTableNo of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_iTableNo
static int tolua_get_USER_INFO_iTableNo(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_iTableNo
static int tolua_set_USER_INFO_iTableNo(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iTableNo = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iSeatNo of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_iSeatNo
static int tolua_get_USER_INFO_iSeatNo(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_iSeatNo
static int tolua_set_USER_INFO_iSeatNo(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iSeatNo = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lScore of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_lScore
static int tolua_get_USER_INFO_lScore(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lScore'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lScore);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lScore of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_lScore
static int tolua_set_USER_INFO_lScore(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lScore'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lScore = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lChangeScore of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_get_USER_INFO_lChangeScore
static int tolua_get_USER_INFO_lChangeScore(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lChangeScore'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lChangeScore);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lChangeScore of class  USER_INFO */
#ifndef TOLUA_DISABLE_tolua_set_USER_INFO_lChangeScore
static int tolua_set_USER_INFO_lChangeScore(lua_State* tolua_S)
{
  USER_INFO* self = (USER_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lChangeScore'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lChangeScore = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_UserInfo_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_UserInfo_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"US_OFFLINE",US_OFFLINE);
  tolua_constant(tolua_S,"US_ONLINE_LEAVE_SIT",US_ONLINE_LEAVE_SIT);
  tolua_constant(tolua_S,"US_ONLINE_SITDOWN",US_ONLINE_SITDOWN);
  tolua_constant(tolua_S,"US_ONLINE_SITDOWN_RAISE",US_ONLINE_SITDOWN_RAISE);
  tolua_constant(tolua_S,"US_WAIT_RECONNECT",US_WAIT_RECONNECT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"USER_INFO","USER_INFO","DATA_BASE<USER_INFO>",tolua_collect_USER_INFO);
  #else
  tolua_cclass(tolua_S,"USER_INFO","USER_INFO","DATA_BASE<USER_INFO>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"USER_INFO");
   tolua_function(tolua_S,"new",tolua_UserInfo_USER_INFO_new00);
   tolua_function(tolua_S,"new_local",tolua_UserInfo_USER_INFO_new00_local);
   tolua_function(tolua_S,".call",tolua_UserInfo_USER_INFO_new00_local);
   tolua_function(tolua_S,"ClearServerInfo",tolua_UserInfo_USER_INFO_ClearServerInfo00);
   tolua_variable(tolua_S,"lUserId",tolua_get_USER_INFO_lUserId,tolua_set_USER_INFO_lUserId);
   tolua_variable(tolua_S,"szName",tolua_get_USER_INFO_szName,tolua_set_USER_INFO_szName);
   tolua_variable(tolua_S,"szPassword",tolua_get_USER_INFO_szPassword,tolua_set_USER_INFO_szPassword);
   tolua_variable(tolua_S,"szNickname",tolua_get_USER_INFO_szNickname,tolua_set_USER_INFO_szNickname);
   tolua_variable(tolua_S,"stRegistTime",tolua_get_USER_INFO_stRegistTime,tolua_set_USER_INFO_stRegistTime);
   tolua_variable(tolua_S,"stUserState",tolua_get_USER_INFO_stUserState,tolua_set_USER_INFO_stUserState);
   tolua_variable(tolua_S,"iTableNo",tolua_get_USER_INFO_iTableNo,tolua_set_USER_INFO_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_USER_INFO_iSeatNo,tolua_set_USER_INFO_iSeatNo);
   tolua_variable(tolua_S,"lScore",tolua_get_USER_INFO_lScore,tolua_set_USER_INFO_lScore);
   tolua_variable(tolua_S,"lChangeScore",tolua_get_USER_INFO_lChangeScore,tolua_set_USER_INFO_lChangeScore);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_UserInfo (lua_State* tolua_S) {
 return tolua_UserInfo_open(tolua_S);
};
#endif


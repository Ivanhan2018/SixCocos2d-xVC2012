/*
** Lua binding: RoomInfo
** Generated automatically by tolua++-1.0.92 on 05/23/13 16:14:31.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_RoomInfo_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_MANAGER_POWER_ERR (lua_State* tolua_S)
{
 MANAGER_POWER_ERR* self = (MANAGER_POWER_ERR*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SERVER_ROOM_INFO (lua_State* tolua_S)
{
 SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LOGIN_ROOM_SUCC (lua_State* tolua_S)
{
 LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LOGIN_ROOM (lua_State* tolua_S)
{
 LOGIN_ROOM* self = (LOGIN_ROOM*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_WRITE_SCORE_RESULT (lua_State* tolua_S)
{
 WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_WRITE_SCORE (lua_State* tolua_S)
{
 WRITE_SCORE* self = (WRITE_SCORE*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CLIENT_FRAME_PARAM (lua_State* tolua_S)
{
 CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_RECOME_AFTER_CUT (lua_State* tolua_S)
{
 RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TICK_USER_OUT_ROOM (lua_State* tolua_S)
{
 TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LOGIN_ROOM_FAIL (lua_State* tolua_S)
{
 LOGIN_ROOM_FAIL* self = (LOGIN_ROOM_FAIL*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LEAVE_ROOM_RESULT (lua_State* tolua_S)
{
 LEAVE_ROOM_RESULT* self = (LEAVE_ROOM_RESULT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CLIENT_ROOM_INFO (lua_State* tolua_S)
{
 CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CLIENT_TO_RMS_PARAM (lua_State* tolua_S)
{
 CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_RoomInfo_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MANAGER_POWER_ERR");
 tolua_usertype(tolua_S,"DATA_BASE<LOGIN_ROOM>");
 tolua_usertype(tolua_S,"DATA_BASE<LEAVE_ROOM_RESULT>");
 tolua_usertype(tolua_S,"SERVER_ROOM_INFO");
 tolua_usertype(tolua_S,"LOGIN_ROOM_SUCC");
 tolua_usertype(tolua_S,"USER_INFO");
 tolua_usertype(tolua_S,"DATA_BASE<MANAGER_POWER_ERR>");
 tolua_usertype(tolua_S,"WRITE_SCORE_RESULT");
 tolua_usertype(tolua_S,"DATA_BASE<TICK_USER_OUT_ROOM>");
 tolua_usertype(tolua_S,"LONGLONG");
 tolua_usertype(tolua_S,"RECOME_AFTER_CUT");
 tolua_usertype(tolua_S,"LEAVE_ROOM_RESULT");
 tolua_usertype(tolua_S,"DATA_BASE<CLIENT_TO_RMS_PARAM>");
 tolua_usertype(tolua_S,"WRITE_SCORE");
 tolua_usertype(tolua_S,"DATA_BASE<LOGIN_ROOM_FAIL>");
 tolua_usertype(tolua_S,"TICK_USER_OUT_ROOM");
 tolua_usertype(tolua_S,"DATA_BASE<WRITE_SCORE>");
 tolua_usertype(tolua_S,"DATA_BASE<SERVER_ROOM_INFO>");
 tolua_usertype(tolua_S,"MY_TEST");
 tolua_usertype(tolua_S,"LOGIN_ROOM_FAIL");
 tolua_usertype(tolua_S,"CLIENT_FRAME_PARAM");
 tolua_usertype(tolua_S,"CLIENT_TO_RMS_PARAM");
 tolua_usertype(tolua_S,"LOGIN_ROOM");
 tolua_usertype(tolua_S,"DATA_BASE<WRITE_SCORE_RESULT>");
 tolua_usertype(tolua_S,"DATA_BASE<CLIENT_FRAME_PARAM>");
 tolua_usertype(tolua_S,"CLIENT_ROOM_INFO");
 tolua_usertype(tolua_S,"DATA_BASE<CLIENT_ROOM_INFO>");
}

/* get function: a of class  MY_TEST */
#ifndef TOLUA_DISABLE_tolua_get_MY_TEST_a
static int tolua_get_MY_TEST_a(lua_State* tolua_S)
{
  MY_TEST* self = (MY_TEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->a);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  MY_TEST */
#ifndef TOLUA_DISABLE_tolua_set_MY_TEST_a
static int tolua_set_MY_TEST_a(lua_State* tolua_S)
{
  MY_TEST* self = (MY_TEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->a = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  MY_TEST */
#ifndef TOLUA_DISABLE_tolua_get_MY_TEST_b
static int tolua_get_MY_TEST_b(lua_State* tolua_S)
{
  MY_TEST* self = (MY_TEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->b);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  MY_TEST */
#ifndef TOLUA_DISABLE_tolua_set_MY_TEST_b
static int tolua_set_MY_TEST_b(lua_State* tolua_S)
{
  MY_TEST* self = (MY_TEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_CLIENT_FRAME_PARAM_new00
static int tolua_RoomInfo_CLIENT_FRAME_PARAM_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLIENT_FRAME_PARAM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CLIENT_FRAME_PARAM* tolua_ret = (CLIENT_FRAME_PARAM*)  Mtolua_new((CLIENT_FRAME_PARAM)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLIENT_FRAME_PARAM");
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

/* method: new_local of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_CLIENT_FRAME_PARAM_new00_local
static int tolua_RoomInfo_CLIENT_FRAME_PARAM_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLIENT_FRAME_PARAM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CLIENT_FRAME_PARAM* tolua_ret = (CLIENT_FRAME_PARAM*)  Mtolua_new((CLIENT_FRAME_PARAM)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLIENT_FRAME_PARAM");
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

/* get function: iMsgBlockSize of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_FRAME_PARAM_iMsgBlockSize
static int tolua_get_CLIENT_FRAME_PARAM_iMsgBlockSize(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iMsgBlockSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iMsgBlockSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iMsgBlockSize of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_FRAME_PARAM_iMsgBlockSize
static int tolua_set_CLIENT_FRAME_PARAM_iMsgBlockSize(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iMsgBlockSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iMsgBlockSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iSendHeartbeatTime of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_FRAME_PARAM_iSendHeartbeatTime
static int tolua_get_CLIENT_FRAME_PARAM_iSendHeartbeatTime(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSendHeartbeatTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSendHeartbeatTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSendHeartbeatTime of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_FRAME_PARAM_iSendHeartbeatTime
static int tolua_set_CLIENT_FRAME_PARAM_iSendHeartbeatTime(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSendHeartbeatTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iSendHeartbeatTime = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iShrinkPoolsTime of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_FRAME_PARAM_iShrinkPoolsTime
static int tolua_get_CLIENT_FRAME_PARAM_iShrinkPoolsTime(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iShrinkPoolsTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iShrinkPoolsTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iShrinkPoolsTime of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_FRAME_PARAM_iShrinkPoolsTime
static int tolua_set_CLIENT_FRAME_PARAM_iShrinkPoolsTime(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iShrinkPoolsTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iShrinkPoolsTime = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAutoReConnect of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_FRAME_PARAM_bAutoReConnect
static int tolua_get_CLIENT_FRAME_PARAM_bAutoReConnect(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoReConnect'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bAutoReConnect);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAutoReConnect of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_FRAME_PARAM_bAutoReConnect
static int tolua_set_CLIENT_FRAME_PARAM_bAutoReConnect(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoReConnect'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAutoReConnect = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iAutoReConnectTime of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_FRAME_PARAM_iAutoReConnectTime
static int tolua_get_CLIENT_FRAME_PARAM_iAutoReConnectTime(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iAutoReConnectTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iAutoReConnectTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iAutoReConnectTime of class  CLIENT_FRAME_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_FRAME_PARAM_iAutoReConnectTime
static int tolua_set_CLIENT_FRAME_PARAM_iAutoReConnectTime(lua_State* tolua_S)
{
  CLIENT_FRAME_PARAM* self = (CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iAutoReConnectTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iAutoReConnectTime = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00
static int tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLIENT_TO_RMS_PARAM",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* IP = ((char*)  tolua_tostring(tolua_S,2,"127.0.0.1"));
  int Port = ((int)  tolua_tonumber(tolua_S,3,6150));
  int MsgBlockSize = ((int)  tolua_tonumber(tolua_S,4,2048));
  int SendHeartbeatTime = ((int)  tolua_tonumber(tolua_S,5,30*1000));
  int ShrinkPoolsTime = ((int)  tolua_tonumber(tolua_S,6,3*60*1000));
  bool AutoReConnect = ((bool)  tolua_toboolean(tolua_S,7,true));
  int AutoReConnectTime = ((int)  tolua_tonumber(tolua_S,8,2*1000));
  {
   CLIENT_TO_RMS_PARAM* tolua_ret = (CLIENT_TO_RMS_PARAM*)  Mtolua_new((CLIENT_TO_RMS_PARAM)(IP,Port,MsgBlockSize,SendHeartbeatTime,ShrinkPoolsTime,AutoReConnect,AutoReConnectTime));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLIENT_TO_RMS_PARAM");
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

/* method: new_local of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00_local
static int tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLIENT_TO_RMS_PARAM",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* IP = ((char*)  tolua_tostring(tolua_S,2,"127.0.0.1"));
  int Port = ((int)  tolua_tonumber(tolua_S,3,6150));
  int MsgBlockSize = ((int)  tolua_tonumber(tolua_S,4,2048));
  int SendHeartbeatTime = ((int)  tolua_tonumber(tolua_S,5,30*1000));
  int ShrinkPoolsTime = ((int)  tolua_tonumber(tolua_S,6,3*60*1000));
  bool AutoReConnect = ((bool)  tolua_toboolean(tolua_S,7,true));
  int AutoReConnectTime = ((int)  tolua_tonumber(tolua_S,8,2*1000));
  {
   CLIENT_TO_RMS_PARAM* tolua_ret = (CLIENT_TO_RMS_PARAM*)  Mtolua_new((CLIENT_TO_RMS_PARAM)(IP,Port,MsgBlockSize,SendHeartbeatTime,ShrinkPoolsTime,AutoReConnect,AutoReConnectTime));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLIENT_TO_RMS_PARAM");
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

/* get function: szIP of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_szIP
static int tolua_get_CLIENT_TO_RMS_PARAM_szIP(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szIP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szIP of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_szIP
static int tolua_set_CLIENT_TO_RMS_PARAM_szIP(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szIP,(const char*)tolua_tostring(tolua_S,2,0),24-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iPort of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_iPort
static int tolua_get_CLIENT_TO_RMS_PARAM_iPort(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iPort);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iPort of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_iPort
static int tolua_set_CLIENT_TO_RMS_PARAM_iPort(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iPort = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iMsgBlockSize of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_iMsgBlockSize
static int tolua_get_CLIENT_TO_RMS_PARAM_iMsgBlockSize(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iMsgBlockSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iMsgBlockSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iMsgBlockSize of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_iMsgBlockSize
static int tolua_set_CLIENT_TO_RMS_PARAM_iMsgBlockSize(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iMsgBlockSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iMsgBlockSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iSendHeartbeatTime of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_iSendHeartbeatTime
static int tolua_get_CLIENT_TO_RMS_PARAM_iSendHeartbeatTime(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSendHeartbeatTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSendHeartbeatTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSendHeartbeatTime of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_iSendHeartbeatTime
static int tolua_set_CLIENT_TO_RMS_PARAM_iSendHeartbeatTime(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSendHeartbeatTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iSendHeartbeatTime = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iShrinkPoolsTime of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_iShrinkPoolsTime
static int tolua_get_CLIENT_TO_RMS_PARAM_iShrinkPoolsTime(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iShrinkPoolsTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iShrinkPoolsTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iShrinkPoolsTime of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_iShrinkPoolsTime
static int tolua_set_CLIENT_TO_RMS_PARAM_iShrinkPoolsTime(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iShrinkPoolsTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iShrinkPoolsTime = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAutoReConnect of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_bAutoReConnect
static int tolua_get_CLIENT_TO_RMS_PARAM_bAutoReConnect(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoReConnect'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bAutoReConnect);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAutoReConnect of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_bAutoReConnect
static int tolua_set_CLIENT_TO_RMS_PARAM_bAutoReConnect(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoReConnect'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAutoReConnect = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iAutoReConnectTime of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_TO_RMS_PARAM_iAutoReConnectTime
static int tolua_get_CLIENT_TO_RMS_PARAM_iAutoReConnectTime(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iAutoReConnectTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iAutoReConnectTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iAutoReConnectTime of class  CLIENT_TO_RMS_PARAM */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_TO_RMS_PARAM_iAutoReConnectTime
static int tolua_set_CLIENT_TO_RMS_PARAM_iAutoReConnectTime(lua_State* tolua_S)
{
  CLIENT_TO_RMS_PARAM* self = (CLIENT_TO_RMS_PARAM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iAutoReConnectTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iAutoReConnectTime = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_SERVER_ROOM_INFO_new00
static int tolua_RoomInfo_SERVER_ROOM_INFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SERVER_ROOM_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SERVER_ROOM_INFO* tolua_ret = (SERVER_ROOM_INFO*)  Mtolua_new((SERVER_ROOM_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SERVER_ROOM_INFO");
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

/* method: new_local of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_SERVER_ROOM_INFO_new00_local
static int tolua_RoomInfo_SERVER_ROOM_INFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SERVER_ROOM_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SERVER_ROOM_INFO* tolua_ret = (SERVER_ROOM_INFO*)  Mtolua_new((SERVER_ROOM_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SERVER_ROOM_INFO");
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

/* get function: uRoomID of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_unsigned_uRoomID
static int tolua_get_SERVER_ROOM_INFO_unsigned_uRoomID(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uRoomID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->uRoomID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uRoomID of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_unsigned_uRoomID
static int tolua_set_SERVER_ROOM_INFO_unsigned_uRoomID(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uRoomID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uRoomID = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szIP of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_szIP
static int tolua_get_SERVER_ROOM_INFO_szIP(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szIP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szIP of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_szIP
static int tolua_set_SERVER_ROOM_INFO_szIP(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szIP,(const char*)tolua_tostring(tolua_S,2,0),24-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iPort of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_iPort
static int tolua_get_SERVER_ROOM_INFO_iPort(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iPort);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iPort of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_iPort
static int tolua_set_SERVER_ROOM_INFO_iPort(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iPort = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iTables of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_iTables
static int tolua_get_SERVER_ROOM_INFO_iTables(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTables'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTables);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTables of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_iTables
static int tolua_set_SERVER_ROOM_INFO_iTables(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTables'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iTables = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iSeatNum of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_iSeatNum
static int tolua_get_SERVER_ROOM_INFO_iSeatNum(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNum of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_iSeatNum
static int tolua_set_SERVER_ROOM_INFO_iSeatNum(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iSeatNum = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iRoomPeopleCount of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_iRoomPeopleCount
static int tolua_get_SERVER_ROOM_INFO_iRoomPeopleCount(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRoomPeopleCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRoomPeopleCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRoomPeopleCount of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_iRoomPeopleCount
static int tolua_set_SERVER_ROOM_INFO_iRoomPeopleCount(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRoomPeopleCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iRoomPeopleCount = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szGameTable of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_szGameTable
static int tolua_get_SERVER_ROOM_INFO_szGameTable(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szGameTable'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szGameTable);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szGameTable of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_szGameTable
static int tolua_set_SERVER_ROOM_INFO_szGameTable(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szGameTable'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szGameTable,(const char*)tolua_tostring(tolua_S,2,0),GAME_TABLE_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lUserPower of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_lUserPower
static int tolua_get_SERVER_ROOM_INFO_lUserPower(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserPower'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lUserPower);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lUserPower of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_lUserPower
static int tolua_set_SERVER_ROOM_INFO_lUserPower(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserPower'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lUserPower = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iGameType of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_iGameType
static int tolua_get_SERVER_ROOM_INFO_iGameType(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iGameType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iGameType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iGameType of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_iGameType
static int tolua_set_SERVER_ROOM_INFO_iGameType(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iGameType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iGameType = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iMoneyPoint of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SERVER_ROOM_INFO_iMoneyPoint
static int tolua_get_SERVER_ROOM_INFO_iMoneyPoint(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iMoneyPoint'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iMoneyPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iMoneyPoint of class  SERVER_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SERVER_ROOM_INFO_iMoneyPoint
static int tolua_set_SERVER_ROOM_INFO_iMoneyPoint(lua_State* tolua_S)
{
  SERVER_ROOM_INFO* self = (SERVER_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iMoneyPoint'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iMoneyPoint = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_CLIENT_ROOM_INFO_new00
static int tolua_RoomInfo_CLIENT_ROOM_INFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLIENT_ROOM_INFO",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* IP = ((char*)  tolua_tostring(tolua_S,2,""));
  int Port = ((int)  tolua_tonumber(tolua_S,3,0));
  char* Name = ((char*)  tolua_tostring(tolua_S,4,""));
  char* Password = ((char*)  tolua_tostring(tolua_S,5,""));
  {
   CLIENT_ROOM_INFO* tolua_ret = (CLIENT_ROOM_INFO*)  Mtolua_new((CLIENT_ROOM_INFO)(IP,Port,Name,Password));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLIENT_ROOM_INFO");
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

/* method: new_local of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_CLIENT_ROOM_INFO_new00_local
static int tolua_RoomInfo_CLIENT_ROOM_INFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLIENT_ROOM_INFO",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* IP = ((char*)  tolua_tostring(tolua_S,2,""));
  int Port = ((int)  tolua_tonumber(tolua_S,3,0));
  char* Name = ((char*)  tolua_tostring(tolua_S,4,""));
  char* Password = ((char*)  tolua_tostring(tolua_S,5,""));
  {
   CLIENT_ROOM_INFO* tolua_ret = (CLIENT_ROOM_INFO*)  Mtolua_new((CLIENT_ROOM_INFO)(IP,Port,Name,Password));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLIENT_ROOM_INFO");
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

/* get function: szIP of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_ROOM_INFO_szIP
static int tolua_get_CLIENT_ROOM_INFO_szIP(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szIP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szIP of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_ROOM_INFO_szIP
static int tolua_set_CLIENT_ROOM_INFO_szIP(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szIP,(const char*)tolua_tostring(tolua_S,2,0),24-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iPort of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_ROOM_INFO_iPort
static int tolua_get_CLIENT_ROOM_INFO_iPort(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iPort);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iPort of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_ROOM_INFO_iPort
static int tolua_set_CLIENT_ROOM_INFO_iPort(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iPort = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_ROOM_INFO_szName
static int tolua_get_CLIENT_ROOM_INFO_szName(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_ROOM_INFO_szName
static int tolua_set_CLIENT_ROOM_INFO_szName(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: szPassword of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_get_CLIENT_ROOM_INFO_szPassword
static int tolua_get_CLIENT_ROOM_INFO_szPassword(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szPassword'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szPassword);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szPassword of class  CLIENT_ROOM_INFO */
#ifndef TOLUA_DISABLE_tolua_set_CLIENT_ROOM_INFO_szPassword
static int tolua_set_CLIENT_ROOM_INFO_szPassword(lua_State* tolua_S)
{
  CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  LOGIN_ROOM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LOGIN_ROOM_new00
static int tolua_RoomInfo_LOGIN_ROOM_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LOGIN_ROOM",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* pszName = ((char*)  tolua_tostring(tolua_S,2,0));
  char* pszPassword = ((char*)  tolua_tostring(tolua_S,3,0));
  {
   LOGIN_ROOM* tolua_ret = (LOGIN_ROOM*)  Mtolua_new((LOGIN_ROOM)(pszName,pszPassword));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LOGIN_ROOM");
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

/* method: new_local of class  LOGIN_ROOM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LOGIN_ROOM_new00_local
static int tolua_RoomInfo_LOGIN_ROOM_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LOGIN_ROOM",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* pszName = ((char*)  tolua_tostring(tolua_S,2,0));
  char* pszPassword = ((char*)  tolua_tostring(tolua_S,3,0));
  {
   LOGIN_ROOM* tolua_ret = (LOGIN_ROOM*)  Mtolua_new((LOGIN_ROOM)(pszName,pszPassword));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LOGIN_ROOM");
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

/* get function: szName of class  LOGIN_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_szName
static int tolua_get_LOGIN_ROOM_szName(lua_State* tolua_S)
{
  LOGIN_ROOM* self = (LOGIN_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  LOGIN_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_szName
static int tolua_set_LOGIN_ROOM_szName(lua_State* tolua_S)
{
  LOGIN_ROOM* self = (LOGIN_ROOM*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: szPassword of class  LOGIN_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_szPassword
static int tolua_get_LOGIN_ROOM_szPassword(lua_State* tolua_S)
{
  LOGIN_ROOM* self = (LOGIN_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szPassword'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szPassword);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szPassword of class  LOGIN_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_szPassword
static int tolua_set_LOGIN_ROOM_szPassword(lua_State* tolua_S)
{
  LOGIN_ROOM* self = (LOGIN_ROOM*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LOGIN_ROOM_SUCC_new00
static int tolua_RoomInfo_LOGIN_ROOM_SUCC_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LOGIN_ROOM_SUCC",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LOGIN_ROOM_SUCC* tolua_ret = (LOGIN_ROOM_SUCC*)  Mtolua_new((LOGIN_ROOM_SUCC)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LOGIN_ROOM_SUCC");
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

/* method: new_local of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LOGIN_ROOM_SUCC_new00_local
static int tolua_RoomInfo_LOGIN_ROOM_SUCC_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LOGIN_ROOM_SUCC",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LOGIN_ROOM_SUCC* tolua_ret = (LOGIN_ROOM_SUCC*)  Mtolua_new((LOGIN_ROOM_SUCC)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LOGIN_ROOM_SUCC");
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

/* get function: szIP of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_SUCC_szIP
static int tolua_get_LOGIN_ROOM_SUCC_szIP(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szIP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szIP of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_SUCC_szIP
static int tolua_set_LOGIN_ROOM_SUCC_szIP(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szIP,(const char*)tolua_tostring(tolua_S,2,0),24-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iPort of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_SUCC_iPort
static int tolua_get_LOGIN_ROOM_SUCC_iPort(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iPort);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iPort of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_SUCC_iPort
static int tolua_set_LOGIN_ROOM_SUCC_iPort(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iPort = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAlreadyInRoom of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_SUCC_bAlreadyInRoom
static int tolua_get_LOGIN_ROOM_SUCC_bAlreadyInRoom(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlreadyInRoom'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bAlreadyInRoom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAlreadyInRoom of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_SUCC_bAlreadyInRoom
static int tolua_set_LOGIN_ROOM_SUCC_bAlreadyInRoom(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlreadyInRoom'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAlreadyInRoom = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: userInfo of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_SUCC_userInfo
static int tolua_get_LOGIN_ROOM_SUCC_userInfo(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userInfo'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->userInfo,"USER_INFO");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: userInfo of class  LOGIN_ROOM_SUCC */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_SUCC_userInfo
static int tolua_set_LOGIN_ROOM_SUCC_userInfo(lua_State* tolua_S)
{
  LOGIN_ROOM_SUCC* self = (LOGIN_ROOM_SUCC*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userInfo'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"USER_INFO",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->userInfo = *((USER_INFO*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_RECOME_AFTER_CUT_new00
static int tolua_RoomInfo_RECOME_AFTER_CUT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RECOME_AFTER_CUT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RECOME_AFTER_CUT* tolua_ret = (RECOME_AFTER_CUT*)  Mtolua_new((RECOME_AFTER_CUT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RECOME_AFTER_CUT");
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

/* method: new_local of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_RECOME_AFTER_CUT_new00_local
static int tolua_RoomInfo_RECOME_AFTER_CUT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RECOME_AFTER_CUT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RECOME_AFTER_CUT* tolua_ret = (RECOME_AFTER_CUT*)  Mtolua_new((RECOME_AFTER_CUT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RECOME_AFTER_CUT");
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

/* get function: iErrCode of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_iErrCode
static int tolua_get_RECOME_AFTER_CUT_iErrCode(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iErrCode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iErrCode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iErrCode of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_iErrCode
static int tolua_set_RECOME_AFTER_CUT_iErrCode(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iErrCode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iErrCode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szIP of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_szIP
static int tolua_get_RECOME_AFTER_CUT_szIP(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szIP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szIP of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_szIP
static int tolua_set_RECOME_AFTER_CUT_szIP(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szIP'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szIP,(const char*)tolua_tostring(tolua_S,2,0),24-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iPort of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_iPort
static int tolua_get_RECOME_AFTER_CUT_iPort(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iPort);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iPort of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_iPort
static int tolua_set_RECOME_AFTER_CUT_iPort(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iPort'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iPort = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAlreadyInRoom of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_bAlreadyInRoom
static int tolua_get_RECOME_AFTER_CUT_bAlreadyInRoom(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlreadyInRoom'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bAlreadyInRoom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAlreadyInRoom of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_bAlreadyInRoom
static int tolua_set_RECOME_AFTER_CUT_bAlreadyInRoom(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlreadyInRoom'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAlreadyInRoom = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iTableNo of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_iTableNo
static int tolua_get_RECOME_AFTER_CUT_iTableNo(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_iTableNo
static int tolua_set_RECOME_AFTER_CUT_iTableNo(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNo of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_iSeatNo
static int tolua_get_RECOME_AFTER_CUT_iSeatNo(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_iSeatNo
static int tolua_set_RECOME_AFTER_CUT_iSeatNo(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: szName of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_get_RECOME_AFTER_CUT_szName
static int tolua_get_RECOME_AFTER_CUT_szName(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  RECOME_AFTER_CUT */
#ifndef TOLUA_DISABLE_tolua_set_RECOME_AFTER_CUT_szName
static int tolua_set_RECOME_AFTER_CUT_szName(lua_State* tolua_S)
{
  RECOME_AFTER_CUT* self = (RECOME_AFTER_CUT*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  LOGIN_ROOM_FAIL */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LOGIN_ROOM_FAIL_new00
static int tolua_RoomInfo_LOGIN_ROOM_FAIL_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LOGIN_ROOM_FAIL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LOGIN_ROOM_FAIL* tolua_ret = (LOGIN_ROOM_FAIL*)  Mtolua_new((LOGIN_ROOM_FAIL)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LOGIN_ROOM_FAIL");
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

/* method: new_local of class  LOGIN_ROOM_FAIL */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LOGIN_ROOM_FAIL_new00_local
static int tolua_RoomInfo_LOGIN_ROOM_FAIL_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LOGIN_ROOM_FAIL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LOGIN_ROOM_FAIL* tolua_ret = (LOGIN_ROOM_FAIL*)  Mtolua_new((LOGIN_ROOM_FAIL)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LOGIN_ROOM_FAIL");
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

/* get function: iErrCode of class  LOGIN_ROOM_FAIL */
#ifndef TOLUA_DISABLE_tolua_get_LOGIN_ROOM_FAIL_iErrCode
static int tolua_get_LOGIN_ROOM_FAIL_iErrCode(lua_State* tolua_S)
{
  LOGIN_ROOM_FAIL* self = (LOGIN_ROOM_FAIL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iErrCode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iErrCode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iErrCode of class  LOGIN_ROOM_FAIL */
#ifndef TOLUA_DISABLE_tolua_set_LOGIN_ROOM_FAIL_iErrCode
static int tolua_set_LOGIN_ROOM_FAIL_iErrCode(lua_State* tolua_S)
{
  LOGIN_ROOM_FAIL* self = (LOGIN_ROOM_FAIL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iErrCode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iErrCode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LEAVE_ROOM_RESULT */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LEAVE_ROOM_RESULT_new00
static int tolua_RoomInfo_LEAVE_ROOM_RESULT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LEAVE_ROOM_RESULT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LEAVE_ROOM_RESULT* tolua_ret = (LEAVE_ROOM_RESULT*)  Mtolua_new((LEAVE_ROOM_RESULT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LEAVE_ROOM_RESULT");
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

/* method: new_local of class  LEAVE_ROOM_RESULT */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_LEAVE_ROOM_RESULT_new00_local
static int tolua_RoomInfo_LEAVE_ROOM_RESULT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LEAVE_ROOM_RESULT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LEAVE_ROOM_RESULT* tolua_ret = (LEAVE_ROOM_RESULT*)  Mtolua_new((LEAVE_ROOM_RESULT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LEAVE_ROOM_RESULT");
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

/* get function: userInfo of class  LEAVE_ROOM_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_LEAVE_ROOM_RESULT_userInfo
static int tolua_get_LEAVE_ROOM_RESULT_userInfo(lua_State* tolua_S)
{
  LEAVE_ROOM_RESULT* self = (LEAVE_ROOM_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userInfo'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->userInfo,"USER_INFO");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: userInfo of class  LEAVE_ROOM_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_LEAVE_ROOM_RESULT_userInfo
static int tolua_set_LEAVE_ROOM_RESULT_userInfo(lua_State* tolua_S)
{
  LEAVE_ROOM_RESULT* self = (LEAVE_ROOM_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userInfo'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"USER_INFO",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->userInfo = *((USER_INFO*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iErrCode of class  LEAVE_ROOM_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_LEAVE_ROOM_RESULT_iErrCode
static int tolua_get_LEAVE_ROOM_RESULT_iErrCode(lua_State* tolua_S)
{
  LEAVE_ROOM_RESULT* self = (LEAVE_ROOM_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iErrCode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iErrCode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iErrCode of class  LEAVE_ROOM_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_LEAVE_ROOM_RESULT_iErrCode
static int tolua_set_LEAVE_ROOM_RESULT_iErrCode(lua_State* tolua_S)
{
  LEAVE_ROOM_RESULT* self = (LEAVE_ROOM_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iErrCode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iErrCode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MANAGER_POWER_ERR */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_MANAGER_POWER_ERR_new00
static int tolua_RoomInfo_MANAGER_POWER_ERR_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MANAGER_POWER_ERR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MANAGER_POWER_ERR* tolua_ret = (MANAGER_POWER_ERR*)  Mtolua_new((MANAGER_POWER_ERR)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MANAGER_POWER_ERR");
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

/* method: new_local of class  MANAGER_POWER_ERR */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_MANAGER_POWER_ERR_new00_local
static int tolua_RoomInfo_MANAGER_POWER_ERR_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MANAGER_POWER_ERR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MANAGER_POWER_ERR* tolua_ret = (MANAGER_POWER_ERR*)  Mtolua_new((MANAGER_POWER_ERR)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MANAGER_POWER_ERR");
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

/* get function: iWantPower of class  MANAGER_POWER_ERR */
#ifndef TOLUA_DISABLE_tolua_get_MANAGER_POWER_ERR_iWantPower
static int tolua_get_MANAGER_POWER_ERR_iWantPower(lua_State* tolua_S)
{
  MANAGER_POWER_ERR* self = (MANAGER_POWER_ERR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iWantPower'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iWantPower);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iWantPower of class  MANAGER_POWER_ERR */
#ifndef TOLUA_DISABLE_tolua_set_MANAGER_POWER_ERR_iWantPower
static int tolua_set_MANAGER_POWER_ERR_iWantPower(lua_State* tolua_S)
{
  MANAGER_POWER_ERR* self = (MANAGER_POWER_ERR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iWantPower'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iWantPower = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_TICK_USER_OUT_ROOM_new00
static int tolua_RoomInfo_TICK_USER_OUT_ROOM_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_USER_OUT_ROOM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_USER_OUT_ROOM* tolua_ret = (TICK_USER_OUT_ROOM*)  Mtolua_new((TICK_USER_OUT_ROOM)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_USER_OUT_ROOM");
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

/* method: new_local of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_TICK_USER_OUT_ROOM_new00_local
static int tolua_RoomInfo_TICK_USER_OUT_ROOM_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_USER_OUT_ROOM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_USER_OUT_ROOM* tolua_ret = (TICK_USER_OUT_ROOM*)  Mtolua_new((TICK_USER_OUT_ROOM)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_USER_OUT_ROOM");
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

/* get function: iRes of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_TICK_USER_OUT_ROOM_iRes
static int tolua_get_TICK_USER_OUT_ROOM_iRes(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_TICK_USER_OUT_ROOM_iRes
static int tolua_set_TICK_USER_OUT_ROOM_iRes(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iRes = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iTickMode of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_TICK_USER_OUT_ROOM_iTickMode
static int tolua_get_TICK_USER_OUT_ROOM_iTickMode(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTickMode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTickMode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTickMode of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_TICK_USER_OUT_ROOM_iTickMode
static int tolua_set_TICK_USER_OUT_ROOM_iTickMode(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTickMode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iTickMode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bWriteScore of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_TICK_USER_OUT_ROOM_bWriteScore
static int tolua_get_TICK_USER_OUT_ROOM_bWriteScore(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bWriteScore'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bWriteScore);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bWriteScore of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_TICK_USER_OUT_ROOM_bWriteScore
static int tolua_set_TICK_USER_OUT_ROOM_bWriteScore(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bWriteScore'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bWriteScore = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iTableNo of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_TICK_USER_OUT_ROOM_iTableNo
static int tolua_get_TICK_USER_OUT_ROOM_iTableNo(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_TICK_USER_OUT_ROOM_iTableNo
static int tolua_set_TICK_USER_OUT_ROOM_iTableNo(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNo of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_TICK_USER_OUT_ROOM_iSeatNo
static int tolua_get_TICK_USER_OUT_ROOM_iSeatNo(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_TICK_USER_OUT_ROOM_iSeatNo
static int tolua_set_TICK_USER_OUT_ROOM_iSeatNo(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: szName of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_get_TICK_USER_OUT_ROOM_szName
static int tolua_get_TICK_USER_OUT_ROOM_szName(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  TICK_USER_OUT_ROOM */
#ifndef TOLUA_DISABLE_tolua_set_TICK_USER_OUT_ROOM_szName
static int tolua_set_TICK_USER_OUT_ROOM_szName(lua_State* tolua_S)
{
  TICK_USER_OUT_ROOM* self = (TICK_USER_OUT_ROOM*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_WRITE_SCORE_new00
static int tolua_RoomInfo_WRITE_SCORE_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WRITE_SCORE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long ScoreChange = ((long long)  tolua_tonumber(tolua_S,2,0));
  int Type = ((int)  tolua_tonumber(tolua_S,3,0));
  long long UserId = ((long long)  tolua_tonumber(tolua_S,4,INVALID_USER_ID));
  long long ChannelNo = ((long long)  tolua_tonumber(tolua_S,5,INVALID_CHANNEL_NO));
  {
   WRITE_SCORE* tolua_ret = (WRITE_SCORE*)  Mtolua_new((WRITE_SCORE)(ScoreChange,Type,UserId,ChannelNo));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WRITE_SCORE");
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

/* method: new_local of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_WRITE_SCORE_new00_local
static int tolua_RoomInfo_WRITE_SCORE_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WRITE_SCORE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long ScoreChange = ((long long)  tolua_tonumber(tolua_S,2,0));
  int Type = ((int)  tolua_tonumber(tolua_S,3,0));
  long long UserId = ((long long)  tolua_tonumber(tolua_S,4,INVALID_USER_ID));
  long long ChannelNo = ((long long)  tolua_tonumber(tolua_S,5,INVALID_CHANNEL_NO));
  {
   WRITE_SCORE* tolua_ret = (WRITE_SCORE*)  Mtolua_new((WRITE_SCORE)(ScoreChange,Type,UserId,ChannelNo));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WRITE_SCORE");
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

/* get function: iType of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_iType
static int tolua_get_WRITE_SCORE_iType(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iType of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_iType
static int tolua_set_WRITE_SCORE_iType(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iType = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lUserId of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_lUserId
static int tolua_get_WRITE_SCORE_lUserId(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lUserId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lUserId of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_lUserId
static int tolua_set_WRITE_SCORE_lUserId(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: lChannelNo of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_lChannelNo
static int tolua_get_WRITE_SCORE_lChannelNo(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lChannelNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lChannelNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lChannelNo of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_lChannelNo
static int tolua_set_WRITE_SCORE_lChannelNo(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lChannelNo'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lChannelNo = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iScoreChange of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_iScoreChange
static int tolua_get_WRITE_SCORE_iScoreChange(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iScoreChange'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iScoreChange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iScoreChange of class  WRITE_SCORE */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_iScoreChange
static int tolua_set_WRITE_SCORE_iScoreChange(lua_State* tolua_S)
{
  WRITE_SCORE* self = (WRITE_SCORE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iScoreChange'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iScoreChange = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_WRITE_SCORE_RESULT_new00
static int tolua_RoomInfo_WRITE_SCORE_RESULT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WRITE_SCORE_RESULT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   WRITE_SCORE_RESULT* tolua_ret = (WRITE_SCORE_RESULT*)  Mtolua_new((WRITE_SCORE_RESULT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WRITE_SCORE_RESULT");
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

/* method: new_local of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_RoomInfo_WRITE_SCORE_RESULT_new00_local
static int tolua_RoomInfo_WRITE_SCORE_RESULT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WRITE_SCORE_RESULT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   WRITE_SCORE_RESULT* tolua_ret = (WRITE_SCORE_RESULT*)  Mtolua_new((WRITE_SCORE_RESULT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WRITE_SCORE_RESULT");
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

/* get function: iRes of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_RESULT_iRes
static int tolua_get_WRITE_SCORE_RESULT_iRes(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_RESULT_iRes
static int tolua_set_WRITE_SCORE_RESULT_iRes(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iRes = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lUserId of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_RESULT_lUserId
static int tolua_get_WRITE_SCORE_RESULT_lUserId(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->lUserId,"LONGLONG");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lUserId of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_RESULT_lUserId
static int tolua_set_WRITE_SCORE_RESULT_lUserId(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LONGLONG",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lUserId = *((LONGLONG*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lChannelNo of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_RESULT_lChannelNo
static int tolua_get_WRITE_SCORE_RESULT_lChannelNo(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lChannelNo'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->lChannelNo,"LONGLONG");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lChannelNo of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_RESULT_lChannelNo
static int tolua_set_WRITE_SCORE_RESULT_lChannelNo(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lChannelNo'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LONGLONG",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lChannelNo = *((LONGLONG*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lScore of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_WRITE_SCORE_RESULT_lScore
static int tolua_get_WRITE_SCORE_RESULT_lScore(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lScore'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->lScore,"LONGLONG");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lScore of class  WRITE_SCORE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_WRITE_SCORE_RESULT_lScore
static int tolua_set_WRITE_SCORE_RESULT_lScore(lua_State* tolua_S)
{
  WRITE_SCORE_RESULT* self = (WRITE_SCORE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lScore'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LONGLONG",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lScore = *((LONGLONG*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_RoomInfo_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_RoomInfo_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"RS_CAN_LOGIN",RS_CAN_LOGIN);
  tolua_constant(tolua_S,"RS_CAN_SIT",RS_CAN_SIT);
  tolua_cclass(tolua_S,"MY_TEST","MY_TEST","",NULL);
  tolua_beginmodule(tolua_S,"MY_TEST");
   tolua_variable(tolua_S,"a",tolua_get_MY_TEST_a,tolua_set_MY_TEST_a);
   tolua_variable(tolua_S,"b",tolua_get_MY_TEST_b,tolua_set_MY_TEST_b);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CLIENT_FRAME_PARAM","CLIENT_FRAME_PARAM","DATA_BASE<CLIENT_FRAME_PARAM>",tolua_collect_CLIENT_FRAME_PARAM);
  #else
  tolua_cclass(tolua_S,"CLIENT_FRAME_PARAM","CLIENT_FRAME_PARAM","DATA_BASE<CLIENT_FRAME_PARAM>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CLIENT_FRAME_PARAM");
   tolua_function(tolua_S,"new",tolua_RoomInfo_CLIENT_FRAME_PARAM_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_CLIENT_FRAME_PARAM_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_CLIENT_FRAME_PARAM_new00_local);
   tolua_variable(tolua_S,"iMsgBlockSize",tolua_get_CLIENT_FRAME_PARAM_iMsgBlockSize,tolua_set_CLIENT_FRAME_PARAM_iMsgBlockSize);
   tolua_variable(tolua_S,"iSendHeartbeatTime",tolua_get_CLIENT_FRAME_PARAM_iSendHeartbeatTime,tolua_set_CLIENT_FRAME_PARAM_iSendHeartbeatTime);
   tolua_variable(tolua_S,"iShrinkPoolsTime",tolua_get_CLIENT_FRAME_PARAM_iShrinkPoolsTime,tolua_set_CLIENT_FRAME_PARAM_iShrinkPoolsTime);
   tolua_variable(tolua_S,"bAutoReConnect",tolua_get_CLIENT_FRAME_PARAM_bAutoReConnect,tolua_set_CLIENT_FRAME_PARAM_bAutoReConnect);
   tolua_variable(tolua_S,"iAutoReConnectTime",tolua_get_CLIENT_FRAME_PARAM_iAutoReConnectTime,tolua_set_CLIENT_FRAME_PARAM_iAutoReConnectTime);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CLIENT_TO_RMS_PARAM","CLIENT_TO_RMS_PARAM","DATA_BASE<CLIENT_TO_RMS_PARAM>",tolua_collect_CLIENT_TO_RMS_PARAM);
  #else
  tolua_cclass(tolua_S,"CLIENT_TO_RMS_PARAM","CLIENT_TO_RMS_PARAM","DATA_BASE<CLIENT_TO_RMS_PARAM>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CLIENT_TO_RMS_PARAM");
   tolua_function(tolua_S,"new",tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_CLIENT_TO_RMS_PARAM_new00_local);
   tolua_variable(tolua_S,"szIP",tolua_get_CLIENT_TO_RMS_PARAM_szIP,tolua_set_CLIENT_TO_RMS_PARAM_szIP);
   tolua_variable(tolua_S,"iPort",tolua_get_CLIENT_TO_RMS_PARAM_iPort,tolua_set_CLIENT_TO_RMS_PARAM_iPort);
   tolua_variable(tolua_S,"iMsgBlockSize",tolua_get_CLIENT_TO_RMS_PARAM_iMsgBlockSize,tolua_set_CLIENT_TO_RMS_PARAM_iMsgBlockSize);
   tolua_variable(tolua_S,"iSendHeartbeatTime",tolua_get_CLIENT_TO_RMS_PARAM_iSendHeartbeatTime,tolua_set_CLIENT_TO_RMS_PARAM_iSendHeartbeatTime);
   tolua_variable(tolua_S,"iShrinkPoolsTime",tolua_get_CLIENT_TO_RMS_PARAM_iShrinkPoolsTime,tolua_set_CLIENT_TO_RMS_PARAM_iShrinkPoolsTime);
   tolua_variable(tolua_S,"bAutoReConnect",tolua_get_CLIENT_TO_RMS_PARAM_bAutoReConnect,tolua_set_CLIENT_TO_RMS_PARAM_bAutoReConnect);
   tolua_variable(tolua_S,"iAutoReConnectTime",tolua_get_CLIENT_TO_RMS_PARAM_iAutoReConnectTime,tolua_set_CLIENT_TO_RMS_PARAM_iAutoReConnectTime);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SERVER_ROOM_INFO","SERVER_ROOM_INFO","DATA_BASE<SERVER_ROOM_INFO>",tolua_collect_SERVER_ROOM_INFO);
  #else
  tolua_cclass(tolua_S,"SERVER_ROOM_INFO","SERVER_ROOM_INFO","DATA_BASE<SERVER_ROOM_INFO>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SERVER_ROOM_INFO");
   tolua_function(tolua_S,"new",tolua_RoomInfo_SERVER_ROOM_INFO_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_SERVER_ROOM_INFO_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_SERVER_ROOM_INFO_new00_local);
   tolua_variable(tolua_S,"uRoomID",tolua_get_SERVER_ROOM_INFO_unsigned_uRoomID,tolua_set_SERVER_ROOM_INFO_unsigned_uRoomID);
   tolua_variable(tolua_S,"szIP",tolua_get_SERVER_ROOM_INFO_szIP,tolua_set_SERVER_ROOM_INFO_szIP);
   tolua_variable(tolua_S,"iPort",tolua_get_SERVER_ROOM_INFO_iPort,tolua_set_SERVER_ROOM_INFO_iPort);
   tolua_variable(tolua_S,"iTables",tolua_get_SERVER_ROOM_INFO_iTables,tolua_set_SERVER_ROOM_INFO_iTables);
   tolua_variable(tolua_S,"iSeatNum",tolua_get_SERVER_ROOM_INFO_iSeatNum,tolua_set_SERVER_ROOM_INFO_iSeatNum);
   tolua_variable(tolua_S,"iRoomPeopleCount",tolua_get_SERVER_ROOM_INFO_iRoomPeopleCount,tolua_set_SERVER_ROOM_INFO_iRoomPeopleCount);
   tolua_variable(tolua_S,"szGameTable",tolua_get_SERVER_ROOM_INFO_szGameTable,tolua_set_SERVER_ROOM_INFO_szGameTable);
   tolua_variable(tolua_S,"lUserPower",tolua_get_SERVER_ROOM_INFO_lUserPower,tolua_set_SERVER_ROOM_INFO_lUserPower);
   tolua_variable(tolua_S,"iGameType",tolua_get_SERVER_ROOM_INFO_iGameType,tolua_set_SERVER_ROOM_INFO_iGameType);
   tolua_variable(tolua_S,"iMoneyPoint",tolua_get_SERVER_ROOM_INFO_iMoneyPoint,tolua_set_SERVER_ROOM_INFO_iMoneyPoint);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CLIENT_ROOM_INFO","CLIENT_ROOM_INFO","DATA_BASE<CLIENT_ROOM_INFO>",tolua_collect_CLIENT_ROOM_INFO);
  #else
  tolua_cclass(tolua_S,"CLIENT_ROOM_INFO","CLIENT_ROOM_INFO","DATA_BASE<CLIENT_ROOM_INFO>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CLIENT_ROOM_INFO");
   tolua_function(tolua_S,"new",tolua_RoomInfo_CLIENT_ROOM_INFO_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_CLIENT_ROOM_INFO_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_CLIENT_ROOM_INFO_new00_local);
   tolua_variable(tolua_S,"szIP",tolua_get_CLIENT_ROOM_INFO_szIP,tolua_set_CLIENT_ROOM_INFO_szIP);
   tolua_variable(tolua_S,"iPort",tolua_get_CLIENT_ROOM_INFO_iPort,tolua_set_CLIENT_ROOM_INFO_iPort);
   tolua_variable(tolua_S,"szName",tolua_get_CLIENT_ROOM_INFO_szName,tolua_set_CLIENT_ROOM_INFO_szName);
   tolua_variable(tolua_S,"szPassword",tolua_get_CLIENT_ROOM_INFO_szPassword,tolua_set_CLIENT_ROOM_INFO_szPassword);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LOGIN_ROOM","LOGIN_ROOM","DATA_BASE<LOGIN_ROOM>",tolua_collect_LOGIN_ROOM);
  #else
  tolua_cclass(tolua_S,"LOGIN_ROOM","LOGIN_ROOM","DATA_BASE<LOGIN_ROOM>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LOGIN_ROOM");
   tolua_function(tolua_S,"new",tolua_RoomInfo_LOGIN_ROOM_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_LOGIN_ROOM_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_LOGIN_ROOM_new00_local);
   tolua_variable(tolua_S,"szName",tolua_get_LOGIN_ROOM_szName,tolua_set_LOGIN_ROOM_szName);
   tolua_variable(tolua_S,"szPassword",tolua_get_LOGIN_ROOM_szPassword,tolua_set_LOGIN_ROOM_szPassword);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LOGIN_ROOM_SUCC","LOGIN_ROOM_SUCC","",tolua_collect_LOGIN_ROOM_SUCC);
  #else
  tolua_cclass(tolua_S,"LOGIN_ROOM_SUCC","LOGIN_ROOM_SUCC","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LOGIN_ROOM_SUCC");
   tolua_function(tolua_S,"new",tolua_RoomInfo_LOGIN_ROOM_SUCC_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_LOGIN_ROOM_SUCC_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_LOGIN_ROOM_SUCC_new00_local);
   tolua_variable(tolua_S,"szIP",tolua_get_LOGIN_ROOM_SUCC_szIP,tolua_set_LOGIN_ROOM_SUCC_szIP);
   tolua_variable(tolua_S,"iPort",tolua_get_LOGIN_ROOM_SUCC_iPort,tolua_set_LOGIN_ROOM_SUCC_iPort);
   tolua_variable(tolua_S,"bAlreadyInRoom",tolua_get_LOGIN_ROOM_SUCC_bAlreadyInRoom,tolua_set_LOGIN_ROOM_SUCC_bAlreadyInRoom);
   tolua_variable(tolua_S,"userInfo",tolua_get_LOGIN_ROOM_SUCC_userInfo,tolua_set_LOGIN_ROOM_SUCC_userInfo);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RECOME_AFTER_CUT","RECOME_AFTER_CUT","",tolua_collect_RECOME_AFTER_CUT);
  #else
  tolua_cclass(tolua_S,"RECOME_AFTER_CUT","RECOME_AFTER_CUT","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RECOME_AFTER_CUT");
   tolua_function(tolua_S,"new",tolua_RoomInfo_RECOME_AFTER_CUT_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_RECOME_AFTER_CUT_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_RECOME_AFTER_CUT_new00_local);
   tolua_variable(tolua_S,"iErrCode",tolua_get_RECOME_AFTER_CUT_iErrCode,tolua_set_RECOME_AFTER_CUT_iErrCode);
   tolua_variable(tolua_S,"szIP",tolua_get_RECOME_AFTER_CUT_szIP,tolua_set_RECOME_AFTER_CUT_szIP);
   tolua_variable(tolua_S,"iPort",tolua_get_RECOME_AFTER_CUT_iPort,tolua_set_RECOME_AFTER_CUT_iPort);
   tolua_variable(tolua_S,"bAlreadyInRoom",tolua_get_RECOME_AFTER_CUT_bAlreadyInRoom,tolua_set_RECOME_AFTER_CUT_bAlreadyInRoom);
   tolua_variable(tolua_S,"iTableNo",tolua_get_RECOME_AFTER_CUT_iTableNo,tolua_set_RECOME_AFTER_CUT_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_RECOME_AFTER_CUT_iSeatNo,tolua_set_RECOME_AFTER_CUT_iSeatNo);
   tolua_variable(tolua_S,"szName",tolua_get_RECOME_AFTER_CUT_szName,tolua_set_RECOME_AFTER_CUT_szName);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LOGIN_ROOM_FAIL","LOGIN_ROOM_FAIL","DATA_BASE<LOGIN_ROOM_FAIL>",tolua_collect_LOGIN_ROOM_FAIL);
  #else
  tolua_cclass(tolua_S,"LOGIN_ROOM_FAIL","LOGIN_ROOM_FAIL","DATA_BASE<LOGIN_ROOM_FAIL>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LOGIN_ROOM_FAIL");
   tolua_constant(tolua_S,"ERR_CAN_NOT_LOGIN",LOGIN_ROOM_FAIL::ERR_CAN_NOT_LOGIN);
   tolua_constant(tolua_S,"ERR_01",LOGIN_ROOM_FAIL::ERR_01);
   tolua_constant(tolua_S,"ERR_02",LOGIN_ROOM_FAIL::ERR_02);
   tolua_constant(tolua_S,"ERR_30",LOGIN_ROOM_FAIL::ERR_30);
   tolua_function(tolua_S,"new",tolua_RoomInfo_LOGIN_ROOM_FAIL_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_LOGIN_ROOM_FAIL_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_LOGIN_ROOM_FAIL_new00_local);
   tolua_variable(tolua_S,"iErrCode",tolua_get_LOGIN_ROOM_FAIL_iErrCode,tolua_set_LOGIN_ROOM_FAIL_iErrCode);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LEAVE_ROOM_RESULT","LEAVE_ROOM_RESULT","DATA_BASE<LEAVE_ROOM_RESULT>",tolua_collect_LEAVE_ROOM_RESULT);
  #else
  tolua_cclass(tolua_S,"LEAVE_ROOM_RESULT","LEAVE_ROOM_RESULT","DATA_BASE<LEAVE_ROOM_RESULT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LEAVE_ROOM_RESULT");
   tolua_function(tolua_S,"new",tolua_RoomInfo_LEAVE_ROOM_RESULT_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_LEAVE_ROOM_RESULT_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_LEAVE_ROOM_RESULT_new00_local);
   tolua_variable(tolua_S,"userInfo",tolua_get_LEAVE_ROOM_RESULT_userInfo,tolua_set_LEAVE_ROOM_RESULT_userInfo);
   tolua_variable(tolua_S,"iErrCode",tolua_get_LEAVE_ROOM_RESULT_iErrCode,tolua_set_LEAVE_ROOM_RESULT_iErrCode);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MANAGER_POWER_ERR","MANAGER_POWER_ERR","DATA_BASE<MANAGER_POWER_ERR>",tolua_collect_MANAGER_POWER_ERR);
  #else
  tolua_cclass(tolua_S,"MANAGER_POWER_ERR","MANAGER_POWER_ERR","DATA_BASE<MANAGER_POWER_ERR>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MANAGER_POWER_ERR");
   tolua_function(tolua_S,"new",tolua_RoomInfo_MANAGER_POWER_ERR_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_MANAGER_POWER_ERR_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_MANAGER_POWER_ERR_new00_local);
   tolua_variable(tolua_S,"iWantPower",tolua_get_MANAGER_POWER_ERR_iWantPower,tolua_set_MANAGER_POWER_ERR_iWantPower);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TICK_USER_OUT_ROOM","TICK_USER_OUT_ROOM","DATA_BASE<TICK_USER_OUT_ROOM>",tolua_collect_TICK_USER_OUT_ROOM);
  #else
  tolua_cclass(tolua_S,"TICK_USER_OUT_ROOM","TICK_USER_OUT_ROOM","DATA_BASE<TICK_USER_OUT_ROOM>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TICK_USER_OUT_ROOM");
   tolua_constant(tolua_S,"TUOR_NO_FIND",TICK_USER_OUT_ROOM::TUOR_NO_FIND);
   tolua_constant(tolua_S,"TUOR_TABLE_ERR",TICK_USER_OUT_ROOM::TUOR_TABLE_ERR);
   tolua_constant(tolua_S,"TUOR_SEAT_NO_USER",TICK_USER_OUT_ROOM::TUOR_SEAT_NO_USER);
   tolua_constant(tolua_S,"TICK_BY_TABLE_SEAT",TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT);
   tolua_constant(tolua_S,"TICK_BY_NAME",TICK_USER_OUT_ROOM::TICK_BY_NAME);
   tolua_constant(tolua_S,"TICK_BY_TABLE",TICK_USER_OUT_ROOM::TICK_BY_TABLE);
   tolua_constant(tolua_S,"TICK_BY_ALL",TICK_USER_OUT_ROOM::TICK_BY_ALL);
   tolua_function(tolua_S,"new",tolua_RoomInfo_TICK_USER_OUT_ROOM_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_TICK_USER_OUT_ROOM_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_TICK_USER_OUT_ROOM_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_TICK_USER_OUT_ROOM_iRes,tolua_set_TICK_USER_OUT_ROOM_iRes);
   tolua_variable(tolua_S,"iTickMode",tolua_get_TICK_USER_OUT_ROOM_iTickMode,tolua_set_TICK_USER_OUT_ROOM_iTickMode);
   tolua_variable(tolua_S,"bWriteScore",tolua_get_TICK_USER_OUT_ROOM_bWriteScore,tolua_set_TICK_USER_OUT_ROOM_bWriteScore);
   tolua_variable(tolua_S,"iTableNo",tolua_get_TICK_USER_OUT_ROOM_iTableNo,tolua_set_TICK_USER_OUT_ROOM_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_TICK_USER_OUT_ROOM_iSeatNo,tolua_set_TICK_USER_OUT_ROOM_iSeatNo);
   tolua_variable(tolua_S,"szName",tolua_get_TICK_USER_OUT_ROOM_szName,tolua_set_TICK_USER_OUT_ROOM_szName);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"WRITE_SCORE","WRITE_SCORE","DATA_BASE<WRITE_SCORE>",tolua_collect_WRITE_SCORE);
  #else
  tolua_cclass(tolua_S,"WRITE_SCORE","WRITE_SCORE","DATA_BASE<WRITE_SCORE>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"WRITE_SCORE");
   tolua_function(tolua_S,"new",tolua_RoomInfo_WRITE_SCORE_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_WRITE_SCORE_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_WRITE_SCORE_new00_local);
   tolua_variable(tolua_S,"iType",tolua_get_WRITE_SCORE_iType,tolua_set_WRITE_SCORE_iType);
   tolua_variable(tolua_S,"lUserId",tolua_get_WRITE_SCORE_lUserId,tolua_set_WRITE_SCORE_lUserId);
   tolua_variable(tolua_S,"lChannelNo",tolua_get_WRITE_SCORE_lChannelNo,tolua_set_WRITE_SCORE_lChannelNo);
   tolua_variable(tolua_S,"iScoreChange",tolua_get_WRITE_SCORE_iScoreChange,tolua_set_WRITE_SCORE_iScoreChange);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"WRITE_SCORE_RESULT","WRITE_SCORE_RESULT","DATA_BASE<WRITE_SCORE_RESULT>",tolua_collect_WRITE_SCORE_RESULT);
  #else
  tolua_cclass(tolua_S,"WRITE_SCORE_RESULT","WRITE_SCORE_RESULT","DATA_BASE<WRITE_SCORE_RESULT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"WRITE_SCORE_RESULT");
   tolua_function(tolua_S,"new",tolua_RoomInfo_WRITE_SCORE_RESULT_new00);
   tolua_function(tolua_S,"new_local",tolua_RoomInfo_WRITE_SCORE_RESULT_new00_local);
   tolua_function(tolua_S,".call",tolua_RoomInfo_WRITE_SCORE_RESULT_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_WRITE_SCORE_RESULT_iRes,tolua_set_WRITE_SCORE_RESULT_iRes);
   tolua_variable(tolua_S,"lUserId",tolua_get_WRITE_SCORE_RESULT_lUserId,tolua_set_WRITE_SCORE_RESULT_lUserId);
   tolua_variable(tolua_S,"lChannelNo",tolua_get_WRITE_SCORE_RESULT_lChannelNo,tolua_set_WRITE_SCORE_RESULT_lChannelNo);
   tolua_variable(tolua_S,"lScore",tolua_get_WRITE_SCORE_RESULT_lScore,tolua_set_WRITE_SCORE_RESULT_lScore);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_RoomInfo (lua_State* tolua_S) {
 return tolua_RoomInfo_open(tolua_S);
};
#endif


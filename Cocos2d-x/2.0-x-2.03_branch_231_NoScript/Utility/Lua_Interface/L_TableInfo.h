/*
** Lua binding: TableInfo
** Generated automatically by tolua++-1.0.92 on 05/23/13 16:14:35.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_TableInfo_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SEAT_INFO (lua_State* tolua_S)
{
 SEAT_INFO* self = (SEAT_INFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_RAISE_HAND (lua_State* tolua_S)
{
 RAISE_HAND* self = (RAISE_HAND*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TICK_ONE_LEAVE_SEAT (lua_State* tolua_S)
{
 TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LEAVE_SEAT (lua_State* tolua_S)
{
 LEAVE_SEAT* self = (LEAVE_SEAT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SHOT_FIRE_RESULT (lua_State* tolua_S)
{
 SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TABLE_INFO (lua_State* tolua_S)
{
 TABLE_INFO* self = (TABLE_INFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SHOT_FIRE (lua_State* tolua_S)
{
 SHOT_FIRE* self = (SHOT_FIRE*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SITDOWN (lua_State* tolua_S)
{
 SITDOWN* self = (SITDOWN*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TICK_TABLE_LEAVE_SEAT (lua_State* tolua_S)
{
 TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TICK_ALL_LEAVE_SEAT (lua_State* tolua_S)
{
 TICK_ALL_LEAVE_SEAT* self = (TICK_ALL_LEAVE_SEAT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_TableInfo_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DATA_BASE<SITDOWN>");
 tolua_usertype(tolua_S,"RAISE_HAND");
 tolua_usertype(tolua_S,"SHOT_FIRE");
 tolua_usertype(tolua_S,"DATA_BASE<LEAVE_SEAT>");
 tolua_usertype(tolua_S,"DATA_BASE<TICK_ONE_LEAVE_SEAT>");
 tolua_usertype(tolua_S,"DATA_BASE<TABLE_INFO>");
 tolua_usertype(tolua_S,"DATA_BASE<RAISE_HAND>");
 tolua_usertype(tolua_S,"TICK_TABLE_LEAVE_SEAT");
 tolua_usertype(tolua_S,"DATA_BASE<SHOT_FIRE>");
 tolua_usertype(tolua_S,"SEAT_INFO");
 tolua_usertype(tolua_S,"DATA_BASE<SHOT_FIRE_RESULT>");
 tolua_usertype(tolua_S,"SHOT_FIRE_RESULT");
 tolua_usertype(tolua_S,"TICK_ONE_LEAVE_SEAT");
 tolua_usertype(tolua_S,"LEAVE_SEAT");
 tolua_usertype(tolua_S,"DATA_BASE<TICK_TABLE_LEAVE_SEAT>");
 tolua_usertype(tolua_S,"CSingleUser");
 tolua_usertype(tolua_S,"TABLE_INFO");
 tolua_usertype(tolua_S,"DATA_BASE<SEAT_INFO>");
 tolua_usertype(tolua_S,"SITDOWN");
 tolua_usertype(tolua_S,"TICK_ALL_LEAVE_SEAT");
 tolua_usertype(tolua_S,"DATA_BASE<TICK_ALL_LEAVE_SEAT>");
}

/* method: new of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SEAT_INFO_new00
static int tolua_TableInfo_SEAT_INFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SEAT_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SEAT_INFO* tolua_ret = (SEAT_INFO*)  Mtolua_new((SEAT_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SEAT_INFO");
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

/* method: new_local of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SEAT_INFO_new00_local
static int tolua_TableInfo_SEAT_INFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SEAT_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SEAT_INFO* tolua_ret = (SEAT_INFO*)  Mtolua_new((SEAT_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SEAT_INFO");
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

/* get function: iSeatNo of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SEAT_INFO_iSeatNo
static int tolua_get_SEAT_INFO_iSeatNo(lua_State* tolua_S)
{
  SEAT_INFO* self = (SEAT_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SEAT_INFO_iSeatNo
static int tolua_set_SEAT_INFO_iSeatNo(lua_State* tolua_S)
{
  SEAT_INFO* self = (SEAT_INFO*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: bFreeSeat of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SEAT_INFO_bFreeSeat
static int tolua_get_SEAT_INFO_bFreeSeat(lua_State* tolua_S)
{
  SEAT_INFO* self = (SEAT_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFreeSeat'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bFreeSeat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bFreeSeat of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SEAT_INFO_bFreeSeat
static int tolua_set_SEAT_INFO_bFreeSeat(lua_State* tolua_S)
{
  SEAT_INFO* self = (SEAT_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFreeSeat'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bFreeSeat = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pSingleUser of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_get_SEAT_INFO_pSingleUser_ptr
static int tolua_get_SEAT_INFO_pSingleUser_ptr(lua_State* tolua_S)
{
  SEAT_INFO* self = (SEAT_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pSingleUser'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pSingleUser,"CSingleUser");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pSingleUser of class  SEAT_INFO */
#ifndef TOLUA_DISABLE_tolua_set_SEAT_INFO_pSingleUser_ptr
static int tolua_set_SEAT_INFO_pSingleUser_ptr(lua_State* tolua_S)
{
  SEAT_INFO* self = (SEAT_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pSingleUser'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CSingleUser",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pSingleUser = ((CSingleUser*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TABLE_INFO */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TABLE_INFO_new00
static int tolua_TableInfo_TABLE_INFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TABLE_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TABLE_INFO* tolua_ret = (TABLE_INFO*)  Mtolua_new((TABLE_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TABLE_INFO");
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

/* method: new_local of class  TABLE_INFO */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TABLE_INFO_new00_local
static int tolua_TableInfo_TABLE_INFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TABLE_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TABLE_INFO* tolua_ret = (TABLE_INFO*)  Mtolua_new((TABLE_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TABLE_INFO");
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

/* get function: iTableNo of class  TABLE_INFO */
#ifndef TOLUA_DISABLE_tolua_get_TABLE_INFO_iTableNo
static int tolua_get_TABLE_INFO_iTableNo(lua_State* tolua_S)
{
  TABLE_INFO* self = (TABLE_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  TABLE_INFO */
#ifndef TOLUA_DISABLE_tolua_set_TABLE_INFO_iTableNo
static int tolua_set_TABLE_INFO_iTableNo(lua_State* tolua_S)
{
  TABLE_INFO* self = (TABLE_INFO*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNum of class  TABLE_INFO */
#ifndef TOLUA_DISABLE_tolua_get_TABLE_INFO_iSeatNum
static int tolua_get_TABLE_INFO_iSeatNum(lua_State* tolua_S)
{
  TABLE_INFO* self = (TABLE_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNum of class  TABLE_INFO */
#ifndef TOLUA_DISABLE_tolua_set_TABLE_INFO_iSeatNum
static int tolua_set_TABLE_INFO_iSeatNum(lua_State* tolua_S)
{
  TABLE_INFO* self = (TABLE_INFO*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SITDOWN_new00
static int tolua_TableInfo_SITDOWN_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SITDOWN",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long UserId = ((long long)  tolua_tonumber(tolua_S,2,INVALID_USER_ID));
  int TableNo = ((int)  tolua_tonumber(tolua_S,3,INVAL_TABLE_NO));
  int SeatNo = ((int)  tolua_tonumber(tolua_S,4,INVAL_SEAT_NO));
  {
   SITDOWN* tolua_ret = (SITDOWN*)  Mtolua_new((SITDOWN)(UserId,TableNo,SeatNo));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SITDOWN");
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

/* method: new_local of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SITDOWN_new00_local
static int tolua_TableInfo_SITDOWN_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SITDOWN",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long UserId = ((long long)  tolua_tonumber(tolua_S,2,INVALID_USER_ID));
  int TableNo = ((int)  tolua_tonumber(tolua_S,3,INVAL_TABLE_NO));
  int SeatNo = ((int)  tolua_tonumber(tolua_S,4,INVAL_SEAT_NO));
  {
   SITDOWN* tolua_ret = (SITDOWN*)  Mtolua_new((SITDOWN)(UserId,TableNo,SeatNo));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SITDOWN");
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

/* get function: lUserId of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_get_SITDOWN_lUserId
static int tolua_get_SITDOWN_lUserId(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lUserId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lUserId of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_set_SITDOWN_lUserId
static int tolua_set_SITDOWN_lUserId(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iTableNo of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_get_SITDOWN_iTableNo
static int tolua_get_SITDOWN_iTableNo(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_set_SITDOWN_iTableNo
static int tolua_set_SITDOWN_iTableNo(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNo of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_get_SITDOWN_iSeatNo
static int tolua_get_SITDOWN_iSeatNo(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_set_SITDOWN_iSeatNo
static int tolua_set_SITDOWN_iSeatNo(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iRes of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_get_SITDOWN_iRes
static int tolua_get_SITDOWN_iRes(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  SITDOWN */
#ifndef TOLUA_DISABLE_tolua_set_SITDOWN_iRes
static int tolua_set_SITDOWN_iRes(lua_State* tolua_S)
{
  SITDOWN* self = (SITDOWN*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  RAISE_HAND */
#ifndef TOLUA_DISABLE_tolua_TableInfo_RAISE_HAND_new00
static int tolua_TableInfo_RAISE_HAND_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RAISE_HAND",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RAISE_HAND* tolua_ret = (RAISE_HAND*)  Mtolua_new((RAISE_HAND)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RAISE_HAND");
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

/* method: new_local of class  RAISE_HAND */
#ifndef TOLUA_DISABLE_tolua_TableInfo_RAISE_HAND_new00_local
static int tolua_TableInfo_RAISE_HAND_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RAISE_HAND",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RAISE_HAND* tolua_ret = (RAISE_HAND*)  Mtolua_new((RAISE_HAND)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RAISE_HAND");
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

/* get function: iRes of class  RAISE_HAND */
#ifndef TOLUA_DISABLE_tolua_get_RAISE_HAND_iRes
static int tolua_get_RAISE_HAND_iRes(lua_State* tolua_S)
{
  RAISE_HAND* self = (RAISE_HAND*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  RAISE_HAND */
#ifndef TOLUA_DISABLE_tolua_set_RAISE_HAND_iRes
static int tolua_set_RAISE_HAND_iRes(lua_State* tolua_S)
{
  RAISE_HAND* self = (RAISE_HAND*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_LEAVE_SEAT_new00
static int tolua_TableInfo_LEAVE_SEAT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long UserId = ((long long)  tolua_tonumber(tolua_S,2,INVALID_USER_ID));
  int TableNo = ((int)  tolua_tonumber(tolua_S,3,INVAL_TABLE_NO));
  int SeatNo = ((int)  tolua_tonumber(tolua_S,4,INVAL_SEAT_NO));
  {
   LEAVE_SEAT* tolua_ret = (LEAVE_SEAT*)  Mtolua_new((LEAVE_SEAT)(UserId,TableNo,SeatNo));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LEAVE_SEAT");
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

/* method: new_local of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_LEAVE_SEAT_new00_local
static int tolua_TableInfo_LEAVE_SEAT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long UserId = ((long long)  tolua_tonumber(tolua_S,2,INVALID_USER_ID));
  int TableNo = ((int)  tolua_tonumber(tolua_S,3,INVAL_TABLE_NO));
  int SeatNo = ((int)  tolua_tonumber(tolua_S,4,INVAL_SEAT_NO));
  {
   LEAVE_SEAT* tolua_ret = (LEAVE_SEAT*)  Mtolua_new((LEAVE_SEAT)(UserId,TableNo,SeatNo));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LEAVE_SEAT");
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

/* get function: lUserId of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_LEAVE_SEAT_lUserId
static int tolua_get_LEAVE_SEAT_lUserId(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lUserId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lUserId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lUserId of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_LEAVE_SEAT_lUserId
static int tolua_set_LEAVE_SEAT_lUserId(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iTableNo of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_LEAVE_SEAT_iTableNo
static int tolua_get_LEAVE_SEAT_iTableNo(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_LEAVE_SEAT_iTableNo
static int tolua_set_LEAVE_SEAT_iTableNo(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNo of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_LEAVE_SEAT_iSeatNo
static int tolua_get_LEAVE_SEAT_iSeatNo(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_LEAVE_SEAT_iSeatNo
static int tolua_set_LEAVE_SEAT_iSeatNo(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iRes of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_LEAVE_SEAT_iRes
static int tolua_get_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_LEAVE_SEAT_iRes
static int tolua_set_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  LEAVE_SEAT* self = (LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00
static int tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_ONE_LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_ONE_LEAVE_SEAT* tolua_ret = (TICK_ONE_LEAVE_SEAT*)  Mtolua_new((TICK_ONE_LEAVE_SEAT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_ONE_LEAVE_SEAT");
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

/* method: new_local of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00_local
static int tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_ONE_LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_ONE_LEAVE_SEAT* tolua_ret = (TICK_ONE_LEAVE_SEAT*)  Mtolua_new((TICK_ONE_LEAVE_SEAT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_ONE_LEAVE_SEAT");
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

/* get function: iRes of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_ONE_LEAVE_SEAT_iRes
static int tolua_get_TICK_ONE_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_ONE_LEAVE_SEAT_iRes
static int tolua_set_TICK_ONE_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iTableNo of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_ONE_LEAVE_SEAT_iTableNo
static int tolua_get_TICK_ONE_LEAVE_SEAT_iTableNo(lua_State* tolua_S)
{
  TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_ONE_LEAVE_SEAT_iTableNo
static int tolua_set_TICK_ONE_LEAVE_SEAT_iTableNo(lua_State* tolua_S)
{
  TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNo of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_ONE_LEAVE_SEAT_iSeatNo
static int tolua_get_TICK_ONE_LEAVE_SEAT_iSeatNo(lua_State* tolua_S)
{
  TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  TICK_ONE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_ONE_LEAVE_SEAT_iSeatNo
static int tolua_set_TICK_ONE_LEAVE_SEAT_iSeatNo(lua_State* tolua_S)
{
  TICK_ONE_LEAVE_SEAT* self = (TICK_ONE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00
static int tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_TABLE_LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_TABLE_LEAVE_SEAT* tolua_ret = (TICK_TABLE_LEAVE_SEAT*)  Mtolua_new((TICK_TABLE_LEAVE_SEAT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_TABLE_LEAVE_SEAT");
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

/* method: new_local of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00_local
static int tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_TABLE_LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_TABLE_LEAVE_SEAT* tolua_ret = (TICK_TABLE_LEAVE_SEAT*)  Mtolua_new((TICK_TABLE_LEAVE_SEAT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_TABLE_LEAVE_SEAT");
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

/* get function: iRes of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_TABLE_LEAVE_SEAT_iRes
static int tolua_get_TICK_TABLE_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_TABLE_LEAVE_SEAT_iRes
static int tolua_set_TICK_TABLE_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iTableNo of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_TABLE_LEAVE_SEAT_iTableNo
static int tolua_get_TICK_TABLE_LEAVE_SEAT_iTableNo(lua_State* tolua_S)
{
  TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_TABLE_LEAVE_SEAT_iTableNo
static int tolua_set_TICK_TABLE_LEAVE_SEAT_iTableNo(lua_State* tolua_S)
{
  TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: bWriteScore of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_TABLE_LEAVE_SEAT_bWriteScore
static int tolua_get_TICK_TABLE_LEAVE_SEAT_bWriteScore(lua_State* tolua_S)
{
  TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bWriteScore'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bWriteScore);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bWriteScore of class  TICK_TABLE_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_TABLE_LEAVE_SEAT_bWriteScore
static int tolua_set_TICK_TABLE_LEAVE_SEAT_bWriteScore(lua_State* tolua_S)
{
  TICK_TABLE_LEAVE_SEAT* self = (TICK_TABLE_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  TICK_ALL_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00
static int tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_ALL_LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_ALL_LEAVE_SEAT* tolua_ret = (TICK_ALL_LEAVE_SEAT*)  Mtolua_new((TICK_ALL_LEAVE_SEAT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_ALL_LEAVE_SEAT");
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

/* method: new_local of class  TICK_ALL_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00_local
static int tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TICK_ALL_LEAVE_SEAT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TICK_ALL_LEAVE_SEAT* tolua_ret = (TICK_ALL_LEAVE_SEAT*)  Mtolua_new((TICK_ALL_LEAVE_SEAT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TICK_ALL_LEAVE_SEAT");
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

/* get function: iRes of class  TICK_ALL_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_ALL_LEAVE_SEAT_iRes
static int tolua_get_TICK_ALL_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  TICK_ALL_LEAVE_SEAT* self = (TICK_ALL_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  TICK_ALL_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_ALL_LEAVE_SEAT_iRes
static int tolua_set_TICK_ALL_LEAVE_SEAT_iRes(lua_State* tolua_S)
{
  TICK_ALL_LEAVE_SEAT* self = (TICK_ALL_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: bWriteScore of class  TICK_ALL_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_get_TICK_ALL_LEAVE_SEAT_bWriteScore
static int tolua_get_TICK_ALL_LEAVE_SEAT_bWriteScore(lua_State* tolua_S)
{
  TICK_ALL_LEAVE_SEAT* self = (TICK_ALL_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bWriteScore'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bWriteScore);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bWriteScore of class  TICK_ALL_LEAVE_SEAT */
#ifndef TOLUA_DISABLE_tolua_set_TICK_ALL_LEAVE_SEAT_bWriteScore
static int tolua_set_TICK_ALL_LEAVE_SEAT_bWriteScore(lua_State* tolua_S)
{
  TICK_ALL_LEAVE_SEAT* self = (TICK_ALL_LEAVE_SEAT*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SHOT_FIRE_new00
static int tolua_TableInfo_SHOT_FIRE_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SHOT_FIRE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int TestNo = ((int)  tolua_tonumber(tolua_S,2,0));
  int BulletNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int Res = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   SHOT_FIRE* tolua_ret = (SHOT_FIRE*)  Mtolua_new((SHOT_FIRE)(TestNo,BulletNum,Res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SHOT_FIRE");
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

/* method: new_local of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SHOT_FIRE_new00_local
static int tolua_TableInfo_SHOT_FIRE_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SHOT_FIRE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int TestNo = ((int)  tolua_tonumber(tolua_S,2,0));
  int BulletNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int Res = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   SHOT_FIRE* tolua_ret = (SHOT_FIRE*)  Mtolua_new((SHOT_FIRE)(TestNo,BulletNum,Res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SHOT_FIRE");
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

/* get function: iTestNo of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_iTestNo
static int tolua_get_SHOT_FIRE_iTestNo(lua_State* tolua_S)
{
  SHOT_FIRE* self = (SHOT_FIRE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTestNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTestNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTestNo of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_iTestNo
static int tolua_set_SHOT_FIRE_iTestNo(lua_State* tolua_S)
{
  SHOT_FIRE* self = (SHOT_FIRE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTestNo'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iTestNo = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iBulletNum of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_iBulletNum
static int tolua_get_SHOT_FIRE_iBulletNum(lua_State* tolua_S)
{
  SHOT_FIRE* self = (SHOT_FIRE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iBulletNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iBulletNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iBulletNum of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_iBulletNum
static int tolua_set_SHOT_FIRE_iBulletNum(lua_State* tolua_S)
{
  SHOT_FIRE* self = (SHOT_FIRE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iBulletNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iBulletNum = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iRes of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_iRes
static int tolua_get_SHOT_FIRE_iRes(lua_State* tolua_S)
{
  SHOT_FIRE* self = (SHOT_FIRE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  SHOT_FIRE */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_iRes
static int tolua_set_SHOT_FIRE_iRes(lua_State* tolua_S)
{
  SHOT_FIRE* self = (SHOT_FIRE*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SHOT_FIRE_RESULT_new00
static int tolua_TableInfo_SHOT_FIRE_RESULT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SHOT_FIRE_RESULT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SHOT_FIRE_RESULT* tolua_ret = (SHOT_FIRE_RESULT*)  Mtolua_new((SHOT_FIRE_RESULT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SHOT_FIRE_RESULT");
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

/* method: new_local of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_TableInfo_SHOT_FIRE_RESULT_new00_local
static int tolua_TableInfo_SHOT_FIRE_RESULT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SHOT_FIRE_RESULT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SHOT_FIRE_RESULT* tolua_ret = (SHOT_FIRE_RESULT*)  Mtolua_new((SHOT_FIRE_RESULT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SHOT_FIRE_RESULT");
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

/* get function: szName of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_RESULT_szName
static int tolua_get_SHOT_FIRE_RESULT_szName(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_RESULT_szName
static int tolua_set_SHOT_FIRE_RESULT_szName(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iTableNo of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_RESULT_iTableNo
static int tolua_get_SHOT_FIRE_RESULT_iTableNo(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iTableNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iTableNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iTableNo of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_RESULT_iTableNo
static int tolua_set_SHOT_FIRE_RESULT_iTableNo(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iSeatNo of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_RESULT_iSeatNo
static int tolua_get_SHOT_FIRE_RESULT_iSeatNo(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iSeatNo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iSeatNo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iSeatNo of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_RESULT_iSeatNo
static int tolua_set_SHOT_FIRE_RESULT_iSeatNo(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: iBulletNum of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_RESULT_iBulletNum
static int tolua_get_SHOT_FIRE_RESULT_iBulletNum(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iBulletNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iBulletNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iBulletNum of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_RESULT_iBulletNum
static int tolua_set_SHOT_FIRE_RESULT_iBulletNum(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iBulletNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iBulletNum = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iRes of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_get_SHOT_FIRE_RESULT_iRes
static int tolua_get_SHOT_FIRE_RESULT_iRes(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  SHOT_FIRE_RESULT */
#ifndef TOLUA_DISABLE_tolua_set_SHOT_FIRE_RESULT_iRes
static int tolua_set_SHOT_FIRE_RESULT_iRes(lua_State* tolua_S)
{
  SHOT_FIRE_RESULT* self = (SHOT_FIRE_RESULT*)  tolua_tousertype(tolua_S,1,0);
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

/* Open function */
TOLUA_API int tolua_TableInfo_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_TableInfo_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"GAME_SYS_STATE_NO",GAME_SYS_STATE_NO);
  tolua_constant(tolua_S,"GAME_SYS_STATE_RUNING",GAME_SYS_STATE_RUNING);
  tolua_constant(tolua_S,"GAME_SYS_STATE_PAUSH",GAME_SYS_STATE_PAUSH);
  tolua_constant(tolua_S,"GAME_BEGIN_TYPE_AUTO",GAME_BEGIN_TYPE_AUTO);
  tolua_constant(tolua_S,"GAME_BEGIN_TYPE_ONLY_ONE",GAME_BEGIN_TYPE_ONLY_ONE);
  tolua_constant(tolua_S,"GAME_BEGIN_TYPE_ALL_SIT",GAME_BEGIN_TYPE_ALL_SIT);
  tolua_constant(tolua_S,"GAME_BEGIN_TYPE_ANY",GAME_BEGIN_TYPE_ANY);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SEAT_INFO","SEAT_INFO","DATA_BASE<SEAT_INFO>",tolua_collect_SEAT_INFO);
  #else
  tolua_cclass(tolua_S,"SEAT_INFO","SEAT_INFO","DATA_BASE<SEAT_INFO>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SEAT_INFO");
   tolua_function(tolua_S,"new",tolua_TableInfo_SEAT_INFO_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_SEAT_INFO_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_SEAT_INFO_new00_local);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_SEAT_INFO_iSeatNo,tolua_set_SEAT_INFO_iSeatNo);
   tolua_variable(tolua_S,"bFreeSeat",tolua_get_SEAT_INFO_bFreeSeat,tolua_set_SEAT_INFO_bFreeSeat);
   tolua_variable(tolua_S,"pSingleUser",tolua_get_SEAT_INFO_pSingleUser_ptr,tolua_set_SEAT_INFO_pSingleUser_ptr);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TABLE_INFO","TABLE_INFO","DATA_BASE<TABLE_INFO>",tolua_collect_TABLE_INFO);
  #else
  tolua_cclass(tolua_S,"TABLE_INFO","TABLE_INFO","DATA_BASE<TABLE_INFO>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TABLE_INFO");
   tolua_function(tolua_S,"new",tolua_TableInfo_TABLE_INFO_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_TABLE_INFO_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_TABLE_INFO_new00_local);
   tolua_variable(tolua_S,"iTableNo",tolua_get_TABLE_INFO_iTableNo,tolua_set_TABLE_INFO_iTableNo);
   tolua_variable(tolua_S,"iSeatNum",tolua_get_TABLE_INFO_iSeatNum,tolua_set_TABLE_INFO_iSeatNum);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SITDOWN","SITDOWN","DATA_BASE<SITDOWN>",tolua_collect_SITDOWN);
  #else
  tolua_cclass(tolua_S,"SITDOWN","SITDOWN","DATA_BASE<SITDOWN>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SITDOWN");
   tolua_constant(tolua_S,"ERR_CAN_NOT_BEGIN",SITDOWN::ERR_CAN_NOT_BEGIN);
   tolua_constant(tolua_S,"ERR_CAN_NOT_SIT_DOWN",SITDOWN::ERR_CAN_NOT_SIT_DOWN);
   tolua_function(tolua_S,"new",tolua_TableInfo_SITDOWN_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_SITDOWN_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_SITDOWN_new00_local);
   tolua_variable(tolua_S,"lUserId",tolua_get_SITDOWN_lUserId,tolua_set_SITDOWN_lUserId);
   tolua_variable(tolua_S,"iTableNo",tolua_get_SITDOWN_iTableNo,tolua_set_SITDOWN_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_SITDOWN_iSeatNo,tolua_set_SITDOWN_iSeatNo);
   tolua_variable(tolua_S,"iRes",tolua_get_SITDOWN_iRes,tolua_set_SITDOWN_iRes);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RAISE_HAND","RAISE_HAND","DATA_BASE<RAISE_HAND>",tolua_collect_RAISE_HAND);
  #else
  tolua_cclass(tolua_S,"RAISE_HAND","RAISE_HAND","DATA_BASE<RAISE_HAND>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RAISE_HAND");
   tolua_function(tolua_S,"new",tolua_TableInfo_RAISE_HAND_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_RAISE_HAND_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_RAISE_HAND_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_RAISE_HAND_iRes,tolua_set_RAISE_HAND_iRes);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LEAVE_SEAT","LEAVE_SEAT","DATA_BASE<LEAVE_SEAT>",tolua_collect_LEAVE_SEAT);
  #else
  tolua_cclass(tolua_S,"LEAVE_SEAT","LEAVE_SEAT","DATA_BASE<LEAVE_SEAT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LEAVE_SEAT");
   tolua_function(tolua_S,"new",tolua_TableInfo_LEAVE_SEAT_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_LEAVE_SEAT_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_LEAVE_SEAT_new00_local);
   tolua_variable(tolua_S,"lUserId",tolua_get_LEAVE_SEAT_lUserId,tolua_set_LEAVE_SEAT_lUserId);
   tolua_variable(tolua_S,"iTableNo",tolua_get_LEAVE_SEAT_iTableNo,tolua_set_LEAVE_SEAT_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_LEAVE_SEAT_iSeatNo,tolua_set_LEAVE_SEAT_iSeatNo);
   tolua_variable(tolua_S,"iRes",tolua_get_LEAVE_SEAT_iRes,tolua_set_LEAVE_SEAT_iRes);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TICK_ONE_LEAVE_SEAT","TICK_ONE_LEAVE_SEAT","DATA_BASE<TICK_ONE_LEAVE_SEAT>",tolua_collect_TICK_ONE_LEAVE_SEAT);
  #else
  tolua_cclass(tolua_S,"TICK_ONE_LEAVE_SEAT","TICK_ONE_LEAVE_SEAT","DATA_BASE<TICK_ONE_LEAVE_SEAT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TICK_ONE_LEAVE_SEAT");
   tolua_constant(tolua_S,"TFLS_MGR_ERR",TICK_ONE_LEAVE_SEAT::TFLS_MGR_ERR);
   tolua_constant(tolua_S,"TFLS_TABLE_ERR",TICK_ONE_LEAVE_SEAT::TFLS_TABLE_ERR);
   tolua_constant(tolua_S,"TFLS_SEAT_ERR",TICK_ONE_LEAVE_SEAT::TFLS_SEAT_ERR);
   tolua_function(tolua_S,"new",tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_TICK_ONE_LEAVE_SEAT_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_TICK_ONE_LEAVE_SEAT_iRes,tolua_set_TICK_ONE_LEAVE_SEAT_iRes);
   tolua_variable(tolua_S,"iTableNo",tolua_get_TICK_ONE_LEAVE_SEAT_iTableNo,tolua_set_TICK_ONE_LEAVE_SEAT_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_TICK_ONE_LEAVE_SEAT_iSeatNo,tolua_set_TICK_ONE_LEAVE_SEAT_iSeatNo);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TICK_TABLE_LEAVE_SEAT","TICK_TABLE_LEAVE_SEAT","DATA_BASE<TICK_TABLE_LEAVE_SEAT>",tolua_collect_TICK_TABLE_LEAVE_SEAT);
  #else
  tolua_cclass(tolua_S,"TICK_TABLE_LEAVE_SEAT","TICK_TABLE_LEAVE_SEAT","DATA_BASE<TICK_TABLE_LEAVE_SEAT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TICK_TABLE_LEAVE_SEAT");
   tolua_constant(tolua_S,"TFLS_MGR_ERR",TICK_TABLE_LEAVE_SEAT::TFLS_MGR_ERR);
   tolua_constant(tolua_S,"TFLS_TABLE_ERR",TICK_TABLE_LEAVE_SEAT::TFLS_TABLE_ERR);
   tolua_function(tolua_S,"new",tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_TICK_TABLE_LEAVE_SEAT_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_TICK_TABLE_LEAVE_SEAT_iRes,tolua_set_TICK_TABLE_LEAVE_SEAT_iRes);
   tolua_variable(tolua_S,"iTableNo",tolua_get_TICK_TABLE_LEAVE_SEAT_iTableNo,tolua_set_TICK_TABLE_LEAVE_SEAT_iTableNo);
   tolua_variable(tolua_S,"bWriteScore",tolua_get_TICK_TABLE_LEAVE_SEAT_bWriteScore,tolua_set_TICK_TABLE_LEAVE_SEAT_bWriteScore);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TICK_ALL_LEAVE_SEAT","TICK_ALL_LEAVE_SEAT","DATA_BASE<TICK_ALL_LEAVE_SEAT>",tolua_collect_TICK_ALL_LEAVE_SEAT);
  #else
  tolua_cclass(tolua_S,"TICK_ALL_LEAVE_SEAT","TICK_ALL_LEAVE_SEAT","DATA_BASE<TICK_ALL_LEAVE_SEAT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TICK_ALL_LEAVE_SEAT");
   tolua_constant(tolua_S,"TFLS_MGR_ERR",TICK_ALL_LEAVE_SEAT::TFLS_MGR_ERR);
   tolua_function(tolua_S,"new",tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_TICK_ALL_LEAVE_SEAT_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_TICK_ALL_LEAVE_SEAT_iRes,tolua_set_TICK_ALL_LEAVE_SEAT_iRes);
   tolua_variable(tolua_S,"bWriteScore",tolua_get_TICK_ALL_LEAVE_SEAT_bWriteScore,tolua_set_TICK_ALL_LEAVE_SEAT_bWriteScore);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SHOT_FIRE","SHOT_FIRE","DATA_BASE<SHOT_FIRE>",tolua_collect_SHOT_FIRE);
  #else
  tolua_cclass(tolua_S,"SHOT_FIRE","SHOT_FIRE","DATA_BASE<SHOT_FIRE>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SHOT_FIRE");
   tolua_function(tolua_S,"new",tolua_TableInfo_SHOT_FIRE_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_SHOT_FIRE_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_SHOT_FIRE_new00_local);
   tolua_variable(tolua_S,"iTestNo",tolua_get_SHOT_FIRE_iTestNo,tolua_set_SHOT_FIRE_iTestNo);
   tolua_variable(tolua_S,"iBulletNum",tolua_get_SHOT_FIRE_iBulletNum,tolua_set_SHOT_FIRE_iBulletNum);
   tolua_variable(tolua_S,"iRes",tolua_get_SHOT_FIRE_iRes,tolua_set_SHOT_FIRE_iRes);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SHOT_FIRE_RESULT","SHOT_FIRE_RESULT","DATA_BASE<SHOT_FIRE_RESULT>",tolua_collect_SHOT_FIRE_RESULT);
  #else
  tolua_cclass(tolua_S,"SHOT_FIRE_RESULT","SHOT_FIRE_RESULT","DATA_BASE<SHOT_FIRE_RESULT>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SHOT_FIRE_RESULT");
   tolua_function(tolua_S,"new",tolua_TableInfo_SHOT_FIRE_RESULT_new00);
   tolua_function(tolua_S,"new_local",tolua_TableInfo_SHOT_FIRE_RESULT_new00_local);
   tolua_function(tolua_S,".call",tolua_TableInfo_SHOT_FIRE_RESULT_new00_local);
   tolua_variable(tolua_S,"szName",tolua_get_SHOT_FIRE_RESULT_szName,tolua_set_SHOT_FIRE_RESULT_szName);
   tolua_variable(tolua_S,"iTableNo",tolua_get_SHOT_FIRE_RESULT_iTableNo,tolua_set_SHOT_FIRE_RESULT_iTableNo);
   tolua_variable(tolua_S,"iSeatNo",tolua_get_SHOT_FIRE_RESULT_iSeatNo,tolua_set_SHOT_FIRE_RESULT_iSeatNo);
   tolua_variable(tolua_S,"iBulletNum",tolua_get_SHOT_FIRE_RESULT_iBulletNum,tolua_set_SHOT_FIRE_RESULT_iBulletNum);
   tolua_variable(tolua_S,"iRes",tolua_get_SHOT_FIRE_RESULT_iRes,tolua_set_SHOT_FIRE_RESULT_iRes);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_TableInfo (lua_State* tolua_S) {
 return tolua_TableInfo_open(tolua_S);
};
#endif


/*
** Lua binding: ProFish
** Generated automatically by tolua++-1.0.92 on 05/19/13 17:51:13.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_ProFish_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Rsp_AddOneFish_List (lua_State* tolua_S)
{
 Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Req_UserShoot (lua_State* tolua_S)
{
 Req_UserShoot* self = (Req_UserShoot*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Rsp_CaptureFish (lua_State* tolua_S)
{
 Rsp_CaptureFish* self = (Rsp_CaptureFish*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Rsp_AddOneFish (lua_State* tolua_S)
{
 Rsp_AddOneFish* self = (Rsp_AddOneFish*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Req_HitFish (lua_State* tolua_S)
{
 Req_HitFish* self = (Req_HitFish*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Rsp_UserShoot (lua_State* tolua_S)
{
 Rsp_UserShoot* self = (Rsp_UserShoot*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_qcPoint (lua_State* tolua_S)
{
 qcPoint* self = (qcPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Rsp_AddOneFish_Arr (lua_State* tolua_S)
{
 Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_ProFish_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Rsp_AddOneFish_List");
 tolua_usertype(tolua_S,"Req_UserShoot");
 tolua_usertype(tolua_S,"Rsp_CaptureFish");
 tolua_usertype(tolua_S,"Rsp_AddOneFish");
 tolua_usertype(tolua_S,"Req_HitFish");
 tolua_usertype(tolua_S,"Rsp_UserShoot");
 tolua_usertype(tolua_S,"qcPoint");
 tolua_usertype(tolua_S,"Rsp_AddOneFish_Arr");
}

/* get function: x of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_get_qcPoint_x
static int tolua_get_qcPoint_x(lua_State* tolua_S)
{
  qcPoint* self = (qcPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_set_qcPoint_x
static int tolua_set_qcPoint_x(lua_State* tolua_S)
{
  qcPoint* self = (qcPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_get_qcPoint_y
static int tolua_get_qcPoint_y(lua_State* tolua_S)
{
  qcPoint* self = (qcPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_set_qcPoint_y
static int tolua_set_qcPoint_y(lua_State* tolua_S)
{
  qcPoint* self = (qcPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_ProFish_qcPoint_new00
static int tolua_ProFish_qcPoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"qcPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   qcPoint* tolua_ret = (qcPoint*)  Mtolua_new((qcPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"qcPoint");
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

/* method: new_local of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_ProFish_qcPoint_new00_local
static int tolua_ProFish_qcPoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"qcPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   qcPoint* tolua_ret = (qcPoint*)  Mtolua_new((qcPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"qcPoint");
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

/* method: new of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_ProFish_qcPoint_new01
static int tolua_ProFish_qcPoint_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"qcPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   qcPoint* tolua_ret = (qcPoint*)  Mtolua_new((qcPoint)(_x,_y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"qcPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ProFish_qcPoint_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  qcPoint */
#ifndef TOLUA_DISABLE_tolua_ProFish_qcPoint_new01_local
static int tolua_ProFish_qcPoint_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"qcPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   qcPoint* tolua_ret = (qcPoint*)  Mtolua_new((qcPoint)(_x,_y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"qcPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_ProFish_qcPoint_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_new00
static int tolua_ProFish_Rsp_AddOneFish_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_AddOneFish",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_AddOneFish* tolua_ret = (Rsp_AddOneFish*)  Mtolua_new((Rsp_AddOneFish)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_AddOneFish");
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

/* method: new_local of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_new00_local
static int tolua_ProFish_Rsp_AddOneFish_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_AddOneFish",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_AddOneFish* tolua_ret = (Rsp_AddOneFish*)  Mtolua_new((Rsp_AddOneFish)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_AddOneFish");
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

/* get function: TableID of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_unsigned_TableID
static int tolua_get_Rsp_AddOneFish_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->TableID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TableID of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_unsigned_TableID
static int tolua_set_Rsp_AddOneFish_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TableID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishKind of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_unsigned_FishKind
static int tolua_get_Rsp_AddOneFish_unsigned_FishKind(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishKind'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishKind);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishKind of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_unsigned_FishKind
static int tolua_set_Rsp_AddOneFish_unsigned_FishKind(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishKind'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishKind = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishPathType of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_unsigned_FishPathType
static int tolua_get_Rsp_AddOneFish_unsigned_FishPathType(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishPathType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishPathType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishPathType of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_unsigned_FishPathType
static int tolua_set_Rsp_AddOneFish_unsigned_FishPathType(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishPathType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishPathType = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishMoveSecs of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_unsigned_FishMoveSecs
static int tolua_get_Rsp_AddOneFish_unsigned_FishMoveSecs(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishMoveSecs'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishMoveSecs);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishMoveSecs of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_unsigned_FishMoveSecs
static int tolua_set_Rsp_AddOneFish_unsigned_FishMoveSecs(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishMoveSecs'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishMoveSecs = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishID of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_unsigned_FishID
static int tolua_get_Rsp_AddOneFish_unsigned_FishID(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishID of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_unsigned_FishID
static int tolua_set_Rsp_AddOneFish_unsigned_FishID(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: startP of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_startP
static int tolua_get_Rsp_AddOneFish_startP(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startP'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->startP,"qcPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: startP of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_startP
static int tolua_set_Rsp_AddOneFish_startP(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startP'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"qcPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->startP = *((  qcPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: arg1 of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_arg1
static int tolua_get_Rsp_AddOneFish_arg1(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg1'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->arg1,"qcPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: arg1 of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_arg1
static int tolua_set_Rsp_AddOneFish_arg1(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg1'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"qcPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->arg1 = *((  qcPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: arg2 of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_arg2
static int tolua_get_Rsp_AddOneFish_arg2(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg2'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->arg2,"qcPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: arg2 of class  Rsp_AddOneFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_arg2
static int tolua_set_Rsp_AddOneFish_arg2(lua_State* tolua_S)
{
  Rsp_AddOneFish* self = (Rsp_AddOneFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg2'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"qcPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->arg2 = *((  qcPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_Arr_new00
static int tolua_ProFish_Rsp_AddOneFish_Arr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_AddOneFish_Arr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_AddOneFish_Arr* tolua_ret = (Rsp_AddOneFish_Arr*)  Mtolua_new((Rsp_AddOneFish_Arr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_AddOneFish_Arr");
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

/* method: new_local of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_Arr_new00_local
static int tolua_ProFish_Rsp_AddOneFish_Arr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_AddOneFish_Arr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_AddOneFish_Arr* tolua_ret = (Rsp_AddOneFish_Arr*)  Mtolua_new((Rsp_AddOneFish_Arr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_AddOneFish_Arr");
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

/* get function: TableID of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_Arr_unsigned_TableID
static int tolua_get_Rsp_AddOneFish_Arr_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->TableID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TableID of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_Arr_unsigned_TableID
static int tolua_set_Rsp_AddOneFish_Arr_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TableID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishGroupType of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_Arr_unsigned_FishGroupType
static int tolua_get_Rsp_AddOneFish_Arr_unsigned_FishGroupType(lua_State* tolua_S)
{
  Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishGroupType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishGroupType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishGroupType of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_Arr_unsigned_FishGroupType
static int tolua_set_Rsp_AddOneFish_Arr_unsigned_FishGroupType(lua_State* tolua_S)
{
  Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishGroupType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishGroupType = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFishCount of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_Arr_unsigned_nFishCount
static int tolua_get_Rsp_AddOneFish_Arr_unsigned_nFishCount(lua_State* tolua_S)
{
  Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFishCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nFishCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFishCount of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_Arr_unsigned_nFishCount
static int tolua_set_Rsp_AddOneFish_Arr_unsigned_nFishCount(lua_State* tolua_S)
{
  Rsp_AddOneFish_Arr* self = (Rsp_AddOneFish_Arr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFishCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFishCount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Arr of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_get_ProFish_Rsp_AddOneFish_Arr_Arr
static int tolua_get_ProFish_Rsp_AddOneFish_Arr_Arr(lua_State* tolua_S)
{
 int tolua_index;
  Rsp_AddOneFish_Arr* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (Rsp_AddOneFish_Arr*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=20)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Arr[tolua_index],"Rsp_AddOneFish");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Arr of class  Rsp_AddOneFish_Arr */
#ifndef TOLUA_DISABLE_tolua_set_ProFish_Rsp_AddOneFish_Arr_Arr
static int tolua_set_ProFish_Rsp_AddOneFish_Arr_Arr(lua_State* tolua_S)
{
 int tolua_index;
  Rsp_AddOneFish_Arr* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (Rsp_AddOneFish_Arr*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=20)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->Arr[tolua_index] = *((Rsp_AddOneFish*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_List_new00
static int tolua_ProFish_Rsp_AddOneFish_List_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_AddOneFish_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_AddOneFish_List* tolua_ret = (Rsp_AddOneFish_List*)  Mtolua_new((Rsp_AddOneFish_List)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_AddOneFish_List");
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

/* method: new_local of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_List_new00_local
static int tolua_ProFish_Rsp_AddOneFish_List_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_AddOneFish_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_AddOneFish_List* tolua_ret = (Rsp_AddOneFish_List*)  Mtolua_new((Rsp_AddOneFish_List)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_AddOneFish_List");
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

/* get function: TableID of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_List_unsigned_TableID
static int tolua_get_Rsp_AddOneFish_List_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->TableID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TableID of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_List_unsigned_TableID
static int tolua_set_Rsp_AddOneFish_List_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TableID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishGroupType of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_List_unsigned_FishGroupType
static int tolua_get_Rsp_AddOneFish_List_unsigned_FishGroupType(lua_State* tolua_S)
{
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishGroupType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishGroupType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishGroupType of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_List_unsigned_FishGroupType
static int tolua_set_Rsp_AddOneFish_List_unsigned_FishGroupType(lua_State* tolua_S)
{
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishGroupType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishGroupType = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFishCount of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_AddOneFish_List_unsigned_nFishCount
static int tolua_get_Rsp_AddOneFish_List_unsigned_nFishCount(lua_State* tolua_S)
{
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFishCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nFishCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFishCount of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_AddOneFish_List_unsigned_nFishCount
static int tolua_set_Rsp_AddOneFish_List_unsigned_nFishCount(lua_State* tolua_S)
{
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFishCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFishCount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_List__seti00
static int tolua_ProFish_Rsp_AddOneFish_List__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Rsp_AddOneFish_List",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"Rsp_AddOneFish",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tolua_var_2 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  Rsp_AddOneFish tolua_value = *((Rsp_AddOneFish*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](tolua_var_2) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_List__geti00
static int tolua_ProFish_Rsp_AddOneFish_List__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Rsp_AddOneFish_List",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Rsp_AddOneFish_List* self = (Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tolua_var_1 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   Rsp_AddOneFish tolua_ret = (Rsp_AddOneFish)  self->operator[](tolua_var_1);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Rsp_AddOneFish)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Rsp_AddOneFish");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Rsp_AddOneFish));
     tolua_pushusertype(tolua_S,tolua_obj,"Rsp_AddOneFish");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLength of class  Rsp_AddOneFish_List */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_AddOneFish_List_getLength00
static int tolua_ProFish_Rsp_AddOneFish_List_getLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Rsp_AddOneFish_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Rsp_AddOneFish_List* self = (const Rsp_AddOneFish_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Req_UserShoot */
#ifndef TOLUA_DISABLE_tolua_ProFish_Req_UserShoot_new00
static int tolua_ProFish_Req_UserShoot_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Req_UserShoot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Req_UserShoot* tolua_ret = (Req_UserShoot*)  Mtolua_new((Req_UserShoot)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Req_UserShoot");
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

/* method: new_local of class  Req_UserShoot */
#ifndef TOLUA_DISABLE_tolua_ProFish_Req_UserShoot_new00_local
static int tolua_ProFish_Req_UserShoot_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Req_UserShoot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Req_UserShoot* tolua_ret = (Req_UserShoot*)  Mtolua_new((Req_UserShoot)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Req_UserShoot");
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

/* get function: Angle of class  Req_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Req_UserShoot_Angle
static int tolua_get_Req_UserShoot_Angle(lua_State* tolua_S)
{
  Req_UserShoot* self = (Req_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Angle'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Angle);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Angle of class  Req_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Req_UserShoot_Angle
static int tolua_set_Req_UserShoot_Angle(lua_State* tolua_S)
{
  Req_UserShoot* self = (Req_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Angle'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Angle = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: GunGrade of class  Req_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Req_UserShoot_unsigned_GunGrade
static int tolua_get_Req_UserShoot_unsigned_GunGrade(lua_State* tolua_S)
{
  Req_UserShoot* self = (Req_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GunGrade'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->GunGrade);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: GunGrade of class  Req_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Req_UserShoot_unsigned_GunGrade
static int tolua_set_Req_UserShoot_unsigned_GunGrade(lua_State* tolua_S)
{
  Req_UserShoot* self = (Req_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GunGrade'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->GunGrade = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_UserShoot_new00
static int tolua_ProFish_Rsp_UserShoot_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_UserShoot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_UserShoot* tolua_ret = (Rsp_UserShoot*)  Mtolua_new((Rsp_UserShoot)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_UserShoot");
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

/* method: new_local of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_UserShoot_new00_local
static int tolua_ProFish_Rsp_UserShoot_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_UserShoot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_UserShoot* tolua_ret = (Rsp_UserShoot*)  Mtolua_new((Rsp_UserShoot)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_UserShoot");
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

/* get function: iRes of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_UserShoot_iRes
static int tolua_get_Rsp_UserShoot_iRes(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iRes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iRes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iRes of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_UserShoot_iRes
static int tolua_set_Rsp_UserShoot_iRes(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: BulletID of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_UserShoot_unsigned_BulletID
static int tolua_get_Rsp_UserShoot_unsigned_BulletID(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BulletID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->BulletID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: BulletID of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_UserShoot_unsigned_BulletID
static int tolua_set_Rsp_UserShoot_unsigned_BulletID(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BulletID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->BulletID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TableID of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_UserShoot_unsigned_TableID
static int tolua_get_Rsp_UserShoot_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->TableID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TableID of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_UserShoot_unsigned_TableID
static int tolua_set_Rsp_UserShoot_unsigned_TableID(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TableID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TableID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ChairID of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_UserShoot_unsigned_ChairID
static int tolua_get_Rsp_UserShoot_unsigned_ChairID(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ChairID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ChairID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ChairID of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_UserShoot_unsigned_ChairID
static int tolua_set_Rsp_UserShoot_unsigned_ChairID(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ChairID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ChairID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_UserShoot_szName
static int tolua_get_Rsp_UserShoot_szName(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  Rsp_UserShoot */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_UserShoot_szName
static int tolua_set_Rsp_UserShoot_szName(lua_State* tolua_S)
{
  Rsp_UserShoot* self = (Rsp_UserShoot*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_ProFish_Req_HitFish_new00
static int tolua_ProFish_Req_HitFish_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Req_HitFish",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Req_HitFish* tolua_ret = (Req_HitFish*)  Mtolua_new((Req_HitFish)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Req_HitFish");
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

/* method: new_local of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_ProFish_Req_HitFish_new00_local
static int tolua_ProFish_Req_HitFish_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Req_HitFish",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Req_HitFish* tolua_ret = (Req_HitFish*)  Mtolua_new((Req_HitFish)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Req_HitFish");
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

/* get function: BulletID of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_get_Req_HitFish_unsigned_BulletID
static int tolua_get_Req_HitFish_unsigned_BulletID(lua_State* tolua_S)
{
  Req_HitFish* self = (Req_HitFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BulletID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->BulletID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: BulletID of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_set_Req_HitFish_unsigned_BulletID
static int tolua_set_Req_HitFish_unsigned_BulletID(lua_State* tolua_S)
{
  Req_HitFish* self = (Req_HitFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BulletID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->BulletID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFishCount of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_get_Req_HitFish_unsigned_nFishCount
static int tolua_get_Req_HitFish_unsigned_nFishCount(lua_State* tolua_S)
{
  Req_HitFish* self = (Req_HitFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFishCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nFishCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFishCount of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_set_Req_HitFish_unsigned_nFishCount
static int tolua_set_Req_HitFish_unsigned_nFishCount(lua_State* tolua_S)
{
  Req_HitFish* self = (Req_HitFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFishCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFishCount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishIDs of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_get_ProFish_Req_HitFish_FishIDs
static int tolua_get_ProFish_Req_HitFish_FishIDs(lua_State* tolua_S)
{
 int tolua_index;
  Req_HitFish* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (Req_HitFish*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_HIT_FISH_COUNT)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->FishIDs[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishIDs of class  Req_HitFish */
#ifndef TOLUA_DISABLE_tolua_set_ProFish_Req_HitFish_FishIDs
static int tolua_set_ProFish_Req_HitFish_FishIDs(lua_State* tolua_S)
{
 int tolua_index;
  Req_HitFish* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (Req_HitFish*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_HIT_FISH_COUNT)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->FishIDs[tolua_index] = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_CaptureFish_new00
static int tolua_ProFish_Rsp_CaptureFish_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_CaptureFish",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_CaptureFish* tolua_ret = (Rsp_CaptureFish*)  Mtolua_new((Rsp_CaptureFish)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_CaptureFish");
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

/* method: new_local of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_ProFish_Rsp_CaptureFish_new00_local
static int tolua_ProFish_Rsp_CaptureFish_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Rsp_CaptureFish",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Rsp_CaptureFish* tolua_ret = (Rsp_CaptureFish*)  Mtolua_new((Rsp_CaptureFish)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Rsp_CaptureFish");
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

/* get function: ChairID of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_CaptureFish_unsigned_ChairID
static int tolua_get_Rsp_CaptureFish_unsigned_ChairID(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ChairID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ChairID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ChairID of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_CaptureFish_unsigned_ChairID
static int tolua_set_Rsp_CaptureFish_unsigned_ChairID(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ChairID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ChairID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishID of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_CaptureFish_unsigned_FishID
static int tolua_get_Rsp_CaptureFish_unsigned_FishID(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishID of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_CaptureFish_unsigned_FishID
static int tolua_set_Rsp_CaptureFish_unsigned_FishID(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishKind of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_CaptureFish_unsigned_FishKind
static int tolua_get_Rsp_CaptureFish_unsigned_FishKind(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishKind'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishKind);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishKind of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_CaptureFish_unsigned_FishKind
static int tolua_set_Rsp_CaptureFish_unsigned_FishKind(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishKind'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishKind = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FishMulti of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_get_Rsp_CaptureFish_unsigned_FishMulti
static int tolua_get_Rsp_CaptureFish_unsigned_FishMulti(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishMulti'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->FishMulti);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FishMulti of class  Rsp_CaptureFish */
#ifndef TOLUA_DISABLE_tolua_set_Rsp_CaptureFish_unsigned_FishMulti
static int tolua_set_Rsp_CaptureFish_unsigned_FishMulti(lua_State* tolua_S)
{
  Rsp_CaptureFish* self = (Rsp_CaptureFish*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FishMulti'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FishMulti = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ProFish_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_ProFish_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"MAX_HIT_FISH_COUNT",MAX_HIT_FISH_COUNT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"qcPoint","qcPoint","",tolua_collect_qcPoint);
  #else
  tolua_cclass(tolua_S,"qcPoint","qcPoint","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"qcPoint");
   tolua_variable(tolua_S,"x",tolua_get_qcPoint_x,tolua_set_qcPoint_x);
   tolua_variable(tolua_S,"y",tolua_get_qcPoint_y,tolua_set_qcPoint_y);
   tolua_function(tolua_S,"new",tolua_ProFish_qcPoint_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_qcPoint_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_qcPoint_new00_local);
   tolua_function(tolua_S,"new",tolua_ProFish_qcPoint_new01);
   tolua_function(tolua_S,"new_local",tolua_ProFish_qcPoint_new01_local);
   tolua_function(tolua_S,".call",tolua_ProFish_qcPoint_new01_local);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"REQ_BUY_BULLET",REQ_BUY_BULLET);
  tolua_constant(tolua_S,"REQ_USER_SHOOT",REQ_USER_SHOOT);
  tolua_constant(tolua_S,"REQ_CAPTURE_FISH",REQ_CAPTURE_FISH);
  tolua_constant(tolua_S,"REQ_GET_SCORE_INFO",REQ_GET_SCORE_INFO);
  tolua_constant(tolua_S,"REQ_SET_PROPABILITY",REQ_SET_PROPABILITY);
  tolua_constant(tolua_S,"REQ_CALC_SCORE",REQ_CALC_SCORE);
  tolua_constant(tolua_S,"REQ_SET_CELL_SCORE",REQ_SET_CELL_SCORE);
  tolua_constant(tolua_S,"REQ_HIT_FISH",REQ_HIT_FISH);
  tolua_constant(tolua_S,"REQ_OPEN_BOSSBOX",REQ_OPEN_BOSSBOX);
  tolua_constant(tolua_S,"REQ_SHOOT_FORCECANNON",REQ_SHOOT_FORCECANNON);
  tolua_constant(tolua_S,"RSP_GAME_SCENE",RSP_GAME_SCENE);
  tolua_constant(tolua_S,"RSP_ADD_ONE_FISH",RSP_ADD_ONE_FISH);
  tolua_constant(tolua_S,"RSP_ADD_ONE_FISH_ARR",RSP_ADD_ONE_FISH_ARR);
  tolua_constant(tolua_S,"RSP_ADD_ONE_FISH_LIST",RSP_ADD_ONE_FISH_LIST);
  tolua_constant(tolua_S,"RSP_USER_SHOOT",RSP_USER_SHOOT);
  tolua_constant(tolua_S,"RSP_CAPTURE_FISH",RSP_CAPTURE_FISH);
  tolua_constant(tolua_S,"RSP_BULLET_COUNT",RSP_BULLET_COUNT);
  tolua_constant(tolua_S,"RSP_COIN_COUNT",RSP_COIN_COUNT);
  tolua_constant(tolua_S,"RSP_FISH_COUNT",RSP_FISH_COUNT);
  tolua_constant(tolua_S,"RSP_CHANGE_SCENE",RSP_CHANGE_SCENE);
  tolua_constant(tolua_S,"RSP_SCORE_INFO",RSP_SCORE_INFO);
  tolua_constant(tolua_S,"RSP_SET_CELL_SCORE",RSP_SET_CELL_SCORE);
  tolua_constant(tolua_S,"RSP_BONUS_INFO",RSP_BONUS_INFO);
  tolua_constant(tolua_S,"RSP_GAME_MESSAGE",RSP_GAME_MESSAGE);
  tolua_constant(tolua_S,"RSP_GET_PROP",RSP_GET_PROP);
  tolua_constant(tolua_S,"RSP_OPEN_BOSSBOX",RSP_OPEN_BOSSBOX);
  tolua_constant(tolua_S,"RSP_SHOOT_FORCECANNON",RSP_SHOOT_FORCECANNON);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Rsp_AddOneFish","Rsp_AddOneFish","",tolua_collect_Rsp_AddOneFish);
  #else
  tolua_cclass(tolua_S,"Rsp_AddOneFish","Rsp_AddOneFish","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Rsp_AddOneFish");
   tolua_function(tolua_S,"new",tolua_ProFish_Rsp_AddOneFish_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Rsp_AddOneFish_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Rsp_AddOneFish_new00_local);
   tolua_variable(tolua_S,"TableID",tolua_get_Rsp_AddOneFish_unsigned_TableID,tolua_set_Rsp_AddOneFish_unsigned_TableID);
   tolua_variable(tolua_S,"FishKind",tolua_get_Rsp_AddOneFish_unsigned_FishKind,tolua_set_Rsp_AddOneFish_unsigned_FishKind);
   tolua_variable(tolua_S,"FishPathType",tolua_get_Rsp_AddOneFish_unsigned_FishPathType,tolua_set_Rsp_AddOneFish_unsigned_FishPathType);
   tolua_variable(tolua_S,"FishMoveSecs",tolua_get_Rsp_AddOneFish_unsigned_FishMoveSecs,tolua_set_Rsp_AddOneFish_unsigned_FishMoveSecs);
   tolua_variable(tolua_S,"FishID",tolua_get_Rsp_AddOneFish_unsigned_FishID,tolua_set_Rsp_AddOneFish_unsigned_FishID);
   tolua_variable(tolua_S,"startP",tolua_get_Rsp_AddOneFish_startP,tolua_set_Rsp_AddOneFish_startP);
   tolua_variable(tolua_S,"arg1",tolua_get_Rsp_AddOneFish_arg1,tolua_set_Rsp_AddOneFish_arg1);
   tolua_variable(tolua_S,"arg2",tolua_get_Rsp_AddOneFish_arg2,tolua_set_Rsp_AddOneFish_arg2);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Rsp_AddOneFish_Arr","Rsp_AddOneFish_Arr","",tolua_collect_Rsp_AddOneFish_Arr);
  #else
  tolua_cclass(tolua_S,"Rsp_AddOneFish_Arr","Rsp_AddOneFish_Arr","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Rsp_AddOneFish_Arr");
   tolua_function(tolua_S,"new",tolua_ProFish_Rsp_AddOneFish_Arr_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Rsp_AddOneFish_Arr_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Rsp_AddOneFish_Arr_new00_local);
   tolua_variable(tolua_S,"TableID",tolua_get_Rsp_AddOneFish_Arr_unsigned_TableID,tolua_set_Rsp_AddOneFish_Arr_unsigned_TableID);
   tolua_variable(tolua_S,"FishGroupType",tolua_get_Rsp_AddOneFish_Arr_unsigned_FishGroupType,tolua_set_Rsp_AddOneFish_Arr_unsigned_FishGroupType);
   tolua_variable(tolua_S,"nFishCount",tolua_get_Rsp_AddOneFish_Arr_unsigned_nFishCount,tolua_set_Rsp_AddOneFish_Arr_unsigned_nFishCount);
   tolua_array(tolua_S,"Arr",tolua_get_ProFish_Rsp_AddOneFish_Arr_Arr,tolua_set_ProFish_Rsp_AddOneFish_Arr_Arr);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Rsp_AddOneFish_List","Rsp_AddOneFish_List","",tolua_collect_Rsp_AddOneFish_List);
  #else
  tolua_cclass(tolua_S,"Rsp_AddOneFish_List","Rsp_AddOneFish_List","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Rsp_AddOneFish_List");
   tolua_function(tolua_S,"new",tolua_ProFish_Rsp_AddOneFish_List_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Rsp_AddOneFish_List_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Rsp_AddOneFish_List_new00_local);
   tolua_variable(tolua_S,"TableID",tolua_get_Rsp_AddOneFish_List_unsigned_TableID,tolua_set_Rsp_AddOneFish_List_unsigned_TableID);
   tolua_variable(tolua_S,"FishGroupType",tolua_get_Rsp_AddOneFish_List_unsigned_FishGroupType,tolua_set_Rsp_AddOneFish_List_unsigned_FishGroupType);
   tolua_variable(tolua_S,"nFishCount",tolua_get_Rsp_AddOneFish_List_unsigned_nFishCount,tolua_set_Rsp_AddOneFish_List_unsigned_nFishCount);
   tolua_function(tolua_S,".seti",tolua_ProFish_Rsp_AddOneFish_List__seti00);
   tolua_function(tolua_S,".geti",tolua_ProFish_Rsp_AddOneFish_List__geti00);
   tolua_function(tolua_S,"getLength",tolua_ProFish_Rsp_AddOneFish_List_getLength00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Req_UserShoot","Req_UserShoot","",tolua_collect_Req_UserShoot);
  #else
  tolua_cclass(tolua_S,"Req_UserShoot","Req_UserShoot","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Req_UserShoot");
   tolua_function(tolua_S,"new",tolua_ProFish_Req_UserShoot_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Req_UserShoot_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Req_UserShoot_new00_local);
   tolua_variable(tolua_S,"Angle",tolua_get_Req_UserShoot_Angle,tolua_set_Req_UserShoot_Angle);
   tolua_variable(tolua_S,"GunGrade",tolua_get_Req_UserShoot_unsigned_GunGrade,tolua_set_Req_UserShoot_unsigned_GunGrade);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Rsp_UserShoot","Rsp_UserShoot","Req_UserShoot",tolua_collect_Rsp_UserShoot);
  #else
  tolua_cclass(tolua_S,"Rsp_UserShoot","Rsp_UserShoot","Req_UserShoot",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Rsp_UserShoot");
   tolua_function(tolua_S,"new",tolua_ProFish_Rsp_UserShoot_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Rsp_UserShoot_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Rsp_UserShoot_new00_local);
   tolua_variable(tolua_S,"iRes",tolua_get_Rsp_UserShoot_iRes,tolua_set_Rsp_UserShoot_iRes);
   tolua_variable(tolua_S,"BulletID",tolua_get_Rsp_UserShoot_unsigned_BulletID,tolua_set_Rsp_UserShoot_unsigned_BulletID);
   tolua_variable(tolua_S,"TableID",tolua_get_Rsp_UserShoot_unsigned_TableID,tolua_set_Rsp_UserShoot_unsigned_TableID);
   tolua_variable(tolua_S,"ChairID",tolua_get_Rsp_UserShoot_unsigned_ChairID,tolua_set_Rsp_UserShoot_unsigned_ChairID);
   tolua_variable(tolua_S,"szName",tolua_get_Rsp_UserShoot_szName,tolua_set_Rsp_UserShoot_szName);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Req_HitFish","Req_HitFish","",tolua_collect_Req_HitFish);
  #else
  tolua_cclass(tolua_S,"Req_HitFish","Req_HitFish","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Req_HitFish");
   tolua_function(tolua_S,"new",tolua_ProFish_Req_HitFish_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Req_HitFish_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Req_HitFish_new00_local);
   tolua_variable(tolua_S,"BulletID",tolua_get_Req_HitFish_unsigned_BulletID,tolua_set_Req_HitFish_unsigned_BulletID);
   tolua_variable(tolua_S,"nFishCount",tolua_get_Req_HitFish_unsigned_nFishCount,tolua_set_Req_HitFish_unsigned_nFishCount);
   tolua_array(tolua_S,"FishIDs",tolua_get_ProFish_Req_HitFish_FishIDs,tolua_set_ProFish_Req_HitFish_FishIDs);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Rsp_CaptureFish","Rsp_CaptureFish","",tolua_collect_Rsp_CaptureFish);
  #else
  tolua_cclass(tolua_S,"Rsp_CaptureFish","Rsp_CaptureFish","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Rsp_CaptureFish");
   tolua_function(tolua_S,"new",tolua_ProFish_Rsp_CaptureFish_new00);
   tolua_function(tolua_S,"new_local",tolua_ProFish_Rsp_CaptureFish_new00_local);
   tolua_function(tolua_S,".call",tolua_ProFish_Rsp_CaptureFish_new00_local);
   tolua_variable(tolua_S,"ChairID",tolua_get_Rsp_CaptureFish_unsigned_ChairID,tolua_set_Rsp_CaptureFish_unsigned_ChairID);
   tolua_variable(tolua_S,"FishID",tolua_get_Rsp_CaptureFish_unsigned_FishID,tolua_set_Rsp_CaptureFish_unsigned_FishID);
   tolua_variable(tolua_S,"FishKind",tolua_get_Rsp_CaptureFish_unsigned_FishKind,tolua_set_Rsp_CaptureFish_unsigned_FishKind);
   tolua_variable(tolua_S,"FishMulti",tolua_get_Rsp_CaptureFish_unsigned_FishMulti,tolua_set_Rsp_CaptureFish_unsigned_FishMulti);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ProFish (lua_State* tolua_S) {
 return tolua_ProFish_open(tolua_S);
};
#endif


/*
** Lua binding: CCIMEDelegate
** Generated automatically by tolua++-1.0.92 on 04/25/13 14:21:39.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCIMEDelegate_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCIMEDelegate (lua_State* tolua_S)
{
 CCIMEDelegate* self = (CCIMEDelegate*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCIMEDelegate_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCIMEKeyboardNotificationInfo");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"CCIMEDelegate");
}

/* get function: begin of class  CCIMEKeyboardNotificationInfo */
#ifndef TOLUA_DISABLE_tolua_get_CCIMEKeyboardNotificationInfo_begin
static int tolua_get_CCIMEKeyboardNotificationInfo_begin(lua_State* tolua_S)
{
  CCIMEKeyboardNotificationInfo* self = (CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'begin'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->begin,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: begin of class  CCIMEKeyboardNotificationInfo */
#ifndef TOLUA_DISABLE_tolua_set_CCIMEKeyboardNotificationInfo_begin
static int tolua_set_CCIMEKeyboardNotificationInfo_begin(lua_State* tolua_S)
{
  CCIMEKeyboardNotificationInfo* self = (CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'begin'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->begin = *((CCRect*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: end of class  CCIMEKeyboardNotificationInfo */
#ifndef TOLUA_DISABLE_tolua_get_CCIMEKeyboardNotificationInfo_end
static int tolua_get_CCIMEKeyboardNotificationInfo_end(lua_State* tolua_S)
{
  CCIMEKeyboardNotificationInfo* self = (CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'end'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->end,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: end of class  CCIMEKeyboardNotificationInfo */
#ifndef TOLUA_DISABLE_tolua_set_CCIMEKeyboardNotificationInfo_end
static int tolua_set_CCIMEKeyboardNotificationInfo_end(lua_State* tolua_S)
{
  CCIMEKeyboardNotificationInfo* self = (CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'end'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->end = *((CCRect*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: duration of class  CCIMEKeyboardNotificationInfo */
#ifndef TOLUA_DISABLE_tolua_get_CCIMEKeyboardNotificationInfo_duration
static int tolua_get_CCIMEKeyboardNotificationInfo_duration(lua_State* tolua_S)
{
  CCIMEKeyboardNotificationInfo* self = (CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'duration'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->duration);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: duration of class  CCIMEKeyboardNotificationInfo */
#ifndef TOLUA_DISABLE_tolua_set_CCIMEKeyboardNotificationInfo_duration
static int tolua_set_CCIMEKeyboardNotificationInfo_duration(lua_State* tolua_S)
{
  CCIMEKeyboardNotificationInfo* self = (CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'duration'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->duration = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCIMEDelegate */
#ifndef TOLUA_DISABLE_tolua_CCIMEDelegate_CCIMEDelegate_delete00
static int tolua_CCIMEDelegate_CCIMEDelegate_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCIMEDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCIMEDelegate* self = (CCIMEDelegate*)  tolua_tousertype(tolua_S,1,0);
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

/* method: attachWithIME of class  CCIMEDelegate */
#ifndef TOLUA_DISABLE_tolua_CCIMEDelegate_CCIMEDelegate_attachWithIME00
static int tolua_CCIMEDelegate_CCIMEDelegate_attachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCIMEDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCIMEDelegate* self = (CCIMEDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detachWithIME of class  CCIMEDelegate */
#ifndef TOLUA_DISABLE_tolua_CCIMEDelegate_CCIMEDelegate_detachWithIME00
static int tolua_CCIMEDelegate_CCIMEDelegate_detachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCIMEDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCIMEDelegate* self = (CCIMEDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->detachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCIMEDelegate_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCIMEDelegate_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCIMEKeyboardNotificationInfo","CCIMEKeyboardNotificationInfo","",NULL);
  tolua_beginmodule(tolua_S,"CCIMEKeyboardNotificationInfo");
   tolua_variable(tolua_S,"begin",tolua_get_CCIMEKeyboardNotificationInfo_begin,tolua_set_CCIMEKeyboardNotificationInfo_begin);
   tolua_variable(tolua_S,"end",tolua_get_CCIMEKeyboardNotificationInfo_end,tolua_set_CCIMEKeyboardNotificationInfo_end);
   tolua_variable(tolua_S,"duration",tolua_get_CCIMEKeyboardNotificationInfo_duration,tolua_set_CCIMEKeyboardNotificationInfo_duration);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCIMEDelegate","CCIMEDelegate","",tolua_collect_CCIMEDelegate);
  #else
  tolua_cclass(tolua_S,"CCIMEDelegate","CCIMEDelegate","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCIMEDelegate");
   tolua_function(tolua_S,"delete",tolua_CCIMEDelegate_CCIMEDelegate_delete00);
   tolua_function(tolua_S,"attachWithIME",tolua_CCIMEDelegate_CCIMEDelegate_attachWithIME00);
   tolua_function(tolua_S,"detachWithIME",tolua_CCIMEDelegate_CCIMEDelegate_detachWithIME00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCIMEDelegate (lua_State* tolua_S) {
 return tolua_CCIMEDelegate_open(tolua_S);
};
#endif


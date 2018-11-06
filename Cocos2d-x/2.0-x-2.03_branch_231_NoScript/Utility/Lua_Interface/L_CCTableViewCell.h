/*
** Lua binding: CCTableViewCell
** Generated automatically by tolua++-1.0.92 on 04/24/13 11:22:10.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCTableViewCell_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCTableViewCell (lua_State* tolua_S)
{
 CCTableViewCell* self = (CCTableViewCell*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCTableViewCell_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCSortableObject");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCTableViewCell");
}

/* method: new of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_new00
static int tolua_CCTableViewCell_CCTableViewCell_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTableViewCell* tolua_ret = (CCTableViewCell*)  Mtolua_new((CCTableViewCell)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewCell");
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

/* method: new_local of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_new00_local
static int tolua_CCTableViewCell_CCTableViewCell_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTableViewCell* tolua_ret = (CCTableViewCell*)  Mtolua_new((CCTableViewCell)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewCell");
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

/* method: getIdx of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_getIdx00
static int tolua_CCTableViewCell_CCTableViewCell_getIdx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewCell* self = (CCTableViewCell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIdx'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getIdx();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIdx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdx of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_setIdx00
static int tolua_CCTableViewCell_CCTableViewCell_setIdx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewCell* self = (CCTableViewCell*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uIdx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdx'", NULL);
#endif
  {
   self->setIdx(uIdx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_reset00
static int tolua_CCTableViewCell_CCTableViewCell_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewCell* self = (CCTableViewCell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'", NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setObjectID of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_setObjectID00
static int tolua_CCTableViewCell_CCTableViewCell_setObjectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewCell* self = (CCTableViewCell*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uIdx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setObjectID'", NULL);
#endif
  {
   self->setObjectID(uIdx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getObjectID of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_CCTableViewCell_CCTableViewCell_getObjectID00
static int tolua_CCTableViewCell_CCTableViewCell_getObjectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewCell* self = (CCTableViewCell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getObjectID'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getObjectID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCSortableObject__ of class  CCTableViewCell */
#ifndef TOLUA_DISABLE_tolua_get_CCTableViewCell___CCSortableObject__
static int tolua_get_CCTableViewCell___CCSortableObject__(lua_State* tolua_S)
{
  CCTableViewCell* self = (CCTableViewCell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCSortableObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCSortableObject*>(self), "CCSortableObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCSortableObject*)self), "CCSortableObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCTableViewCell_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCTableViewCell_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCTableViewCell","CCTableViewCell","CCNode",tolua_collect_CCTableViewCell);
  #else
  tolua_cclass(tolua_S,"CCTableViewCell","CCTableViewCell","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCTableViewCell");
   tolua_function(tolua_S,"new",tolua_CCTableViewCell_CCTableViewCell_new00);
   tolua_function(tolua_S,"new_local",tolua_CCTableViewCell_CCTableViewCell_new00_local);
   tolua_function(tolua_S,".call",tolua_CCTableViewCell_CCTableViewCell_new00_local);
   tolua_function(tolua_S,"getIdx",tolua_CCTableViewCell_CCTableViewCell_getIdx00);
   tolua_function(tolua_S,"setIdx",tolua_CCTableViewCell_CCTableViewCell_setIdx00);
   tolua_function(tolua_S,"reset",tolua_CCTableViewCell_CCTableViewCell_reset00);
   tolua_function(tolua_S,"setObjectID",tolua_CCTableViewCell_CCTableViewCell_setObjectID00);
   tolua_function(tolua_S,"getObjectID",tolua_CCTableViewCell_CCTableViewCell_getObjectID00);
   tolua_variable(tolua_S,"__CCSortableObject__",tolua_get_CCTableViewCell___CCSortableObject__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCTableViewCell (lua_State* tolua_S) {
 return tolua_CCTableViewCell_open(tolua_S);
};
#endif


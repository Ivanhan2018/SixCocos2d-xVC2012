/*
** Lua binding: SIX_ListViewCell
** Generated automatically by tolua++-1.0.92 on 05/11/13 15:01:23.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_ListViewCell_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_ListViewCell (lua_State* tolua_S)
{
 SIX_ListViewCell* self = (SIX_ListViewCell*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_ListViewCell_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_ListViewCell");
 tolua_usertype(tolua_S,"CCTableViewCell");
}

/* method: new of class  SIX_ListViewCell */
#ifndef TOLUA_DISABLE_tolua_SIX_ListViewCell_SIX_ListViewCell_new00
static int tolua_SIX_ListViewCell_SIX_ListViewCell_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_ListViewCell* tolua_ret = (SIX_ListViewCell*)  Mtolua_new((SIX_ListViewCell)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListViewCell");
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

/* method: new_local of class  SIX_ListViewCell */
#ifndef TOLUA_DISABLE_tolua_SIX_ListViewCell_SIX_ListViewCell_new00_local
static int tolua_SIX_ListViewCell_SIX_ListViewCell_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_ListViewCell* tolua_ret = (SIX_ListViewCell*)  Mtolua_new((SIX_ListViewCell)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListViewCell");
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

/* method: delete of class  SIX_ListViewCell */
#ifndef TOLUA_DISABLE_tolua_SIX_ListViewCell_SIX_ListViewCell_delete00
static int tolua_SIX_ListViewCell_SIX_ListViewCell_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListViewCell* self = (SIX_ListViewCell*)  tolua_tousertype(tolua_S,1,0);
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

/* method: draw of class  SIX_ListViewCell */
#ifndef TOLUA_DISABLE_tolua_SIX_ListViewCell_SIX_ListViewCell_draw00
static int tolua_SIX_ListViewCell_SIX_ListViewCell_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListViewCell* self = (SIX_ListViewCell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_ListViewCell_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_ListViewCell_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_ListViewCell","SIX_ListViewCell","CCTableViewCell",tolua_collect_SIX_ListViewCell);
  #else
  tolua_cclass(tolua_S,"SIX_ListViewCell","SIX_ListViewCell","CCTableViewCell",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_ListViewCell");
   tolua_function(tolua_S,"new",tolua_SIX_ListViewCell_SIX_ListViewCell_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_ListViewCell_SIX_ListViewCell_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_ListViewCell_SIX_ListViewCell_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_ListViewCell_SIX_ListViewCell_delete00);
   tolua_function(tolua_S,"draw",tolua_SIX_ListViewCell_SIX_ListViewCell_draw00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_ListViewCell (lua_State* tolua_S) {
 return tolua_SIX_ListViewCell_open(tolua_S);
};
#endif


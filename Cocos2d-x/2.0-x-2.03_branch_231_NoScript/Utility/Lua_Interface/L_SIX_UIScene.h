/*
** Lua binding: SIX_UIScene
** Generated automatically by tolua++-1.0.92 on 04/24/13 16:07:51.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_UIScene_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_UIScene (lua_State* tolua_S)
{
 SIX_UIScene* self = (SIX_UIScene*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_UIScene_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_UILayer");
 tolua_usertype(tolua_S,"CCScene");
 tolua_usertype(tolua_S,"SIX_UIMgr");
 tolua_usertype(tolua_S,"SIX_UIScene");
}

/* method: new of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_new00
static int tolua_SIX_UIScene_SIX_UIScene_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIScene* tolua_ret = (SIX_UIScene*)  Mtolua_new((SIX_UIScene)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIScene");
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

/* method: new_local of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_new00_local
static int tolua_SIX_UIScene_SIX_UIScene_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIScene* tolua_ret = (SIX_UIScene*)  Mtolua_new((SIX_UIScene)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIScene");
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

/* method: delete of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_delete00
static int tolua_SIX_UIScene_SIX_UIScene_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scene of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_scene00
static int tolua_SIX_UIScene_SIX_UIScene_scene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIScene* tolua_ret = (SIX_UIScene*)  SIX_UIScene::scene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIMgr of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_InitUIMgr00
static int tolua_SIX_UIScene_SIX_UIScene_InitUIMgr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIMgr'", NULL);
#endif
  {
   self->InitUIMgr();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIMgr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInterface of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_GetInterface00
static int tolua_SIX_UIScene_SIX_UIScene_GetInterface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInterface'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->GetInterface(pstrName);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInterface'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUIMgr of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_GetUIMgr00
static int tolua_SIX_UIScene_SIX_UIScene_GetUIMgr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUIMgr'", NULL);
#endif
  {
   SIX_UIMgr* tolua_ret = (SIX_UIMgr*)  self->GetUIMgr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUIMgr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_SIX_UIScene_SIX_UIScene_GetScene00
static int tolua_SIX_UIScene_SIX_UIScene_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
  {
   CCScene* tolua_ret = (CCScene*)  self->GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_UIManager of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIScene_m_UIManager_ptr
static int tolua_get_SIX_UIScene_m_UIManager_ptr(lua_State* tolua_S)
{
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_UIManager'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_UIManager,"SIX_UIMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_UIManager of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIScene_m_UIManager_ptr
static int tolua_set_SIX_UIScene_m_UIManager_ptr(lua_State* tolua_S)
{
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_UIManager'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_UIMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_UIManager = ((SIX_UIMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Scene of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIScene_m_Scene_ptr
static int tolua_get_SIX_UIScene_m_Scene_ptr(lua_State* tolua_S)
{
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Scene'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_Scene,"CCScene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Scene of class  SIX_UIScene */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIScene_m_Scene_ptr
static int tolua_set_SIX_UIScene_m_Scene_ptr(lua_State* tolua_S)
{
  SIX_UIScene* self = (SIX_UIScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Scene'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCScene",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Scene = ((CCScene*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_UIScene_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_UIScene_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_UIScene","SIX_UIScene","SIX_UILayer",tolua_collect_SIX_UIScene);
  #else
  tolua_cclass(tolua_S,"SIX_UIScene","SIX_UIScene","SIX_UILayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_UIScene");
   tolua_function(tolua_S,"new",tolua_SIX_UIScene_SIX_UIScene_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_UIScene_SIX_UIScene_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_UIScene_SIX_UIScene_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_UIScene_SIX_UIScene_delete00);
   tolua_function(tolua_S,"scene",tolua_SIX_UIScene_SIX_UIScene_scene00);
   tolua_function(tolua_S,"InitUIMgr",tolua_SIX_UIScene_SIX_UIScene_InitUIMgr00);
   tolua_function(tolua_S,"GetInterface",tolua_SIX_UIScene_SIX_UIScene_GetInterface00);
   tolua_function(tolua_S,"GetUIMgr",tolua_SIX_UIScene_SIX_UIScene_GetUIMgr00);
   tolua_function(tolua_S,"GetScene",tolua_SIX_UIScene_SIX_UIScene_GetScene00);
   tolua_variable(tolua_S,"m_UIManager",tolua_get_SIX_UIScene_m_UIManager_ptr,tolua_set_SIX_UIScene_m_UIManager_ptr);
   tolua_variable(tolua_S,"m_Scene",tolua_get_SIX_UIScene_m_Scene_ptr,tolua_set_SIX_UIScene_m_Scene_ptr);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_UIScene (lua_State* tolua_S) {
 return tolua_SIX_UIScene_open(tolua_S);
};
#endif


/*
** Lua binding: SIX_GlobalMgr
** Generated automatically by tolua++-1.0.92 on 05/03/13 18:05:05.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_GlobalMgr_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_GlobalMgr (lua_State* tolua_S)
{
 SIX_GlobalMgr* self = (SIX_GlobalMgr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_GlobalMgr_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_FileSystem");
 tolua_usertype(tolua_S,"SIX_GlobalMgr");
 tolua_usertype(tolua_S,"SIX_SceneMgr");
 tolua_usertype(tolua_S,"SIX_Proxy");
 tolua_usertype(tolua_S,"SIX_MusicMgr");
 tolua_usertype(tolua_S,"TSingleton<SIX_GlobalMgr>");
}

/* method: new of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_GlobalMgr* tolua_ret = (SIX_GlobalMgr*)  Mtolua_new((SIX_GlobalMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_GlobalMgr");
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

/* method: new_local of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00_local
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_GlobalMgr* tolua_ret = (SIX_GlobalMgr*)  Mtolua_new((SIX_GlobalMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_GlobalMgr");
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

/* method: delete of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_delete00
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetSceneMgr of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetSceneMgr00
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetSceneMgr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_GlobalMgr* self = (const SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneMgr'", NULL);
#endif
  {
   SIX_SceneMgr* tolua_ret = (SIX_SceneMgr*)  self->GetSceneMgr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SceneMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneMgr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMusicMgr of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetMusicMgr00
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetMusicMgr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_GlobalMgr* self = (const SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMusicMgr'", NULL);
#endif
  {
   SIX_MusicMgr* tolua_ret = (SIX_MusicMgr*)  self->GetMusicMgr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_MusicMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMusicMgr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProxy of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetProxy00
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetProxy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_GlobalMgr* self = (const SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProxy'", NULL);
#endif
  {
   SIX_Proxy* tolua_ret = (SIX_Proxy*)  self->GetProxy();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Proxy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProxy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFS of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetFS00
static int tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetFS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_GlobalMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_GlobalMgr* self = (const SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFS'", NULL);
#endif
  {
   SIX_FileSystem* tolua_ret = (SIX_FileSystem*)  self->GetFS();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_FileSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pSceneMgr of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_GlobalMgr_pSceneMgr_ptr
static int tolua_get_SIX_GlobalMgr_pSceneMgr_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pSceneMgr'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pSceneMgr,"SIX_SceneMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pSceneMgr of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_GlobalMgr_pSceneMgr_ptr
static int tolua_set_SIX_GlobalMgr_pSceneMgr_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pSceneMgr'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_SceneMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pSceneMgr = ((SIX_SceneMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pMusicMgr of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_GlobalMgr_pMusicMgr_ptr
static int tolua_get_SIX_GlobalMgr_pMusicMgr_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pMusicMgr'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pMusicMgr,"SIX_MusicMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pMusicMgr of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_GlobalMgr_pMusicMgr_ptr
static int tolua_set_SIX_GlobalMgr_pMusicMgr_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pMusicMgr'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_MusicMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pMusicMgr = ((SIX_MusicMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pProxy of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_GlobalMgr_pProxy_ptr
static int tolua_get_SIX_GlobalMgr_pProxy_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pProxy'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pProxy,"SIX_Proxy");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pProxy of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_GlobalMgr_pProxy_ptr
static int tolua_set_SIX_GlobalMgr_pProxy_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pProxy'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_Proxy",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pProxy = ((SIX_Proxy*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pFS of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_GlobalMgr_pFS_ptr
static int tolua_get_SIX_GlobalMgr_pFS_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pFS'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pFS,"SIX_FileSystem");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pFS of class  SIX_GlobalMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_GlobalMgr_pFS_ptr
static int tolua_set_SIX_GlobalMgr_pFS_ptr(lua_State* tolua_S)
{
  SIX_GlobalMgr* self = (SIX_GlobalMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pFS'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_FileSystem",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pFS = ((SIX_FileSystem*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_GlobalMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_GlobalMgr_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_GlobalMgr","SIX_GlobalMgr","TSingleton<SIX_GlobalMgr>",tolua_collect_SIX_GlobalMgr);
  #else
  tolua_cclass(tolua_S,"SIX_GlobalMgr","SIX_GlobalMgr","TSingleton<SIX_GlobalMgr>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_GlobalMgr");
   tolua_function(tolua_S,"new",tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_GlobalMgr_SIX_GlobalMgr_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_GlobalMgr_SIX_GlobalMgr_delete00);
   tolua_function(tolua_S,"GetSceneMgr",tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetSceneMgr00);
   tolua_function(tolua_S,"GetMusicMgr",tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetMusicMgr00);
   tolua_function(tolua_S,"GetProxy",tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetProxy00);
   tolua_function(tolua_S,"GetFS",tolua_SIX_GlobalMgr_SIX_GlobalMgr_GetFS00);
   tolua_variable(tolua_S,"pSceneMgr",tolua_get_SIX_GlobalMgr_pSceneMgr_ptr,tolua_set_SIX_GlobalMgr_pSceneMgr_ptr);
   tolua_variable(tolua_S,"pMusicMgr",tolua_get_SIX_GlobalMgr_pMusicMgr_ptr,tolua_set_SIX_GlobalMgr_pMusicMgr_ptr);
   tolua_variable(tolua_S,"pProxy",tolua_get_SIX_GlobalMgr_pProxy_ptr,tolua_set_SIX_GlobalMgr_pProxy_ptr);
   tolua_variable(tolua_S,"pFS",tolua_get_SIX_GlobalMgr_pFS_ptr,tolua_set_SIX_GlobalMgr_pFS_ptr);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_GlobalMgr (lua_State* tolua_S) {
 return tolua_SIX_GlobalMgr_open(tolua_S);
};
#endif


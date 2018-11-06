/*
** Lua binding: SIX_SceneMgr
** Generated automatically by tolua++-1.0.92 on 05/02/13 10:56:16.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_SceneMgr_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_SceneMgr (lua_State* tolua_S)
{
 SIX_SceneMgr* self = (SIX_SceneMgr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_SceneData (lua_State* tolua_S)
{
 SIX_SceneData* self = (SIX_SceneData*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

//static int tolua_collect_CCString (lua_State* tolua_S)
//{
// CCString* self = (CCString*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}
#endif


/* function to register type */
static void tolua_SIX_SceneMgr_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TSingleton<SIX_SceneMgr>");
 tolua_usertype(tolua_S,"CCString");
 tolua_usertype(tolua_S,"SIX_EntityMgr");
 tolua_usertype(tolua_S,"SIX_DSTPL<SIX_XmlDataSet>");
 tolua_usertype(tolua_S,"SIX_XmlDataSet");
 tolua_usertype(tolua_S,"SIX_SceneMgr");
 tolua_usertype(tolua_S,"SIX_Interface");
 tolua_usertype(tolua_S,"SIX_SceneData");
 tolua_usertype(tolua_S,"SIX_UIScene");
}

/* method: new of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_new00
static int tolua_SIX_SceneMgr_SIX_SceneData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_SceneData* tolua_ret = (SIX_SceneData*)  Mtolua_new((SIX_SceneData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SceneData");
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

/* method: new_local of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_new00_local
static int tolua_SIX_SceneMgr_SIX_SceneData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_SceneData* tolua_ret = (SIX_SceneData*)  Mtolua_new((SIX_SceneData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SceneData");
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

/* method: delete of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_delete00
static int tolua_SIX_SceneMgr_SIX_SceneData_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getId of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_getId00
static int tolua_SIX_SceneMgr_SIX_SceneData_getId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getId'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setId of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_setId00
static int tolua_SIX_SceneMgr_SIX_SceneData_setId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
  unsigned int Id = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setId'", NULL);
#endif
  {
   self->setId(Id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPath of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_getPath00
static int tolua_SIX_SceneMgr_SIX_SceneData_getPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPath'", NULL);
#endif
  {
   CCString tolua_ret = (CCString)  self->getPath();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCString));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPath of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_setPath00
static int tolua_SIX_SceneMgr_SIX_SceneData_setPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
  CCString Path = *((CCString*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPath'", NULL);
#endif
  {
   self->setPath(Path);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsPreload of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_getIsPreload00
static int tolua_SIX_SceneMgr_SIX_SceneData_getIsPreload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsPreload'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsPreload();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsPreload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsPreload of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_setIsPreload00
static int tolua_SIX_SceneMgr_SIX_SceneData_setIsPreload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
  bool IsPreload = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsPreload'", NULL);
#endif
  {
   self->setIsPreload(IsPreload);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsPreload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScenePtr of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_GetScenePtr00
static int tolua_SIX_SceneMgr_SIX_SceneData_GetScenePtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScenePtr'", NULL);
#endif
  {
   SIX_UIScene* tolua_ret = (SIX_UIScene*)  self->GetScenePtr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScenePtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadScene of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneData_LoadScene00
static int tolua_SIX_SceneMgr_SIX_SceneData_LoadScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadScene'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LoadScene();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Id of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneData_unsigned_m_Id
static int tolua_get_SIX_SceneData_unsigned_m_Id(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_Id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Id of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneData_unsigned_m_Id
static int tolua_set_SIX_SceneData_unsigned_m_Id(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Id = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Path of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneData_m_Path
static int tolua_get_SIX_SceneData_m_Path(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Path'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_Path,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Path of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneData_m_Path
static int tolua_set_SIX_SceneData_m_Path(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Path'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Path = *((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_IsPreload of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneData_m_IsPreload
static int tolua_get_SIX_SceneData_m_IsPreload(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_IsPreload'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_IsPreload);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_IsPreload of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneData_m_IsPreload
static int tolua_set_SIX_SceneData_m_IsPreload(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_IsPreload'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_IsPreload = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Scene of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneData_m_Scene_ptr
static int tolua_get_SIX_SceneData_m_Scene_ptr(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Scene'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_Scene,"SIX_UIScene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Scene of class  SIX_SceneData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneData_m_Scene_ptr
static int tolua_set_SIX_SceneData_m_Scene_ptr(lua_State* tolua_S)
{
  SIX_SceneData* self = (SIX_SceneData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Scene'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_UIScene",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Scene = ((SIX_UIScene*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_new00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_SceneMgr* tolua_ret = (SIX_SceneMgr*)  Mtolua_new((SIX_SceneMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SceneMgr");
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

/* method: new_local of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_new00_local
static int tolua_SIX_SceneMgr_SIX_SceneMgr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_SceneMgr* tolua_ret = (SIX_SceneMgr*)  Mtolua_new((SIX_SceneMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SceneMgr");
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

/* method: delete of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_delete00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ParseNode of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_ParseNode00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_ParseNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_XmlDataSet",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_XmlDataSet* pDataSet = ((SIX_XmlDataSet*)  tolua_tousertype(tolua_S,2,0));
  const char* nodeName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseNode'", NULL);
#endif
  {
   self->ParseNode(pDataSet,nodeName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseXML of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_ParseXML00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_ParseXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_XmlDataSet>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_DSTPL<SIX_XmlDataSet>* pXmlDataSet = ((SIX_DSTPL<SIX_XmlDataSet>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseXML'", NULL);
#endif
  {
   int tolua_ret = (int)  self->ParseXML(pXmlDataSet);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseXML'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_Run00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Run();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Release of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_Release00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Release'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Release();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSceneResourceFolder of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_SetSceneResourceFolder00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_SetSceneResourceFolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* folder = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSceneResourceFolder'", NULL);
#endif
  {
   self->SetSceneResourceFolder(folder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSceneResourceFolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalSceneCount of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_GetTotalSceneCount00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_GetTotalSceneCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalSceneCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetTotalSceneCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalSceneCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPreloadSceneCount of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_GetPreloadSceneCount00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_GetPreloadSceneCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPreloadSceneCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetPreloadSceneCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPreloadSceneCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentSceneIdx of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_GetCurrentSceneIdx00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_GetCurrentSceneIdx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentSceneIdx'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurrentSceneIdx();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentSceneIdx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadScene of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_unloadScene00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_unloadScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  int sceneIdx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadScene'", NULL);
#endif
  {
   self->unloadScene(sceneIdx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadScene of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_preloadScene00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_preloadScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_SceneData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_SceneData* pScene = ((SIX_SceneData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadScene'", NULL);
#endif
  {
   int tolua_ret = (int)  self->preloadScene(pScene);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeScene of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_changeScene00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_changeScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  int sceneIdx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeScene'", NULL);
#endif
  {
   SIX_UIScene* tolua_ret = (SIX_UIScene*)  self->changeScene(sceneIdx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScenePointer of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_SceneMgr_SIX_SceneMgr_GetScenePointer00
static int tolua_SIX_SceneMgr_SIX_SceneMgr_GetScenePointer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SceneMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
  int sceneIdx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScenePointer'", NULL);
#endif
  {
   SIX_SceneData* tolua_ret = (SIX_SceneData*)  self->GetScenePointer(sceneIdx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SceneData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScenePointer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_SceneBasePath of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneMgr_m_SceneBasePath_ptr
static int tolua_get_SIX_SceneMgr_m_SceneBasePath_ptr(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_SceneBasePath'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_SceneBasePath,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_SceneBasePath of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneMgr_m_SceneBasePath_ptr
static int tolua_set_SIX_SceneMgr_m_SceneBasePath_ptr(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_SceneBasePath'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_SceneBasePath = ((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_PreloadCount of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneMgr_unsigned_m_PreloadCount
static int tolua_get_SIX_SceneMgr_unsigned_m_PreloadCount(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_PreloadCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_PreloadCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_PreloadCount of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneMgr_unsigned_m_PreloadCount
static int tolua_set_SIX_SceneMgr_unsigned_m_PreloadCount(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_PreloadCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_PreloadCount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_CurrentSceneIdx of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneMgr_m_CurrentSceneIdx
static int tolua_get_SIX_SceneMgr_m_CurrentSceneIdx(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_CurrentSceneIdx'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_CurrentSceneIdx);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_CurrentSceneIdx of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SceneMgr_m_CurrentSceneIdx
static int tolua_set_SIX_SceneMgr_m_CurrentSceneIdx(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_CurrentSceneIdx'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_CurrentSceneIdx = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __TSingleton<SIX_SceneMgr>__ of class  SIX_SceneMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SceneMgr___TSingleton_SIX_SceneMgr___
static int tolua_get_SIX_SceneMgr___TSingleton_SIX_SceneMgr___(lua_State* tolua_S)
{
  SIX_SceneMgr* self = (SIX_SceneMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__TSingleton<SIX_SceneMgr>__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<TSingleton<SIX_SceneMgr>*>(self), "TSingleton<SIX_SceneMgr>");
#else
   tolua_pushusertype(tolua_S,(void*)((TSingleton<SIX_SceneMgr>*)self), "TSingleton<SIX_SceneMgr>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_SceneMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_SceneMgr_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_SceneData","SIX_SceneData","SIX_Interface",tolua_collect_SIX_SceneData);
  #else
  tolua_cclass(tolua_S,"SIX_SceneData","SIX_SceneData","SIX_Interface",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_SceneData");
   tolua_function(tolua_S,"new",tolua_SIX_SceneMgr_SIX_SceneData_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_SceneMgr_SIX_SceneData_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_SceneMgr_SIX_SceneData_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_SceneMgr_SIX_SceneData_delete00);
   tolua_function(tolua_S,"getId",tolua_SIX_SceneMgr_SIX_SceneData_getId00);
   tolua_function(tolua_S,"setId",tolua_SIX_SceneMgr_SIX_SceneData_setId00);
   tolua_function(tolua_S,"getPath",tolua_SIX_SceneMgr_SIX_SceneData_getPath00);
   tolua_function(tolua_S,"setPath",tolua_SIX_SceneMgr_SIX_SceneData_setPath00);
   tolua_function(tolua_S,"getIsPreload",tolua_SIX_SceneMgr_SIX_SceneData_getIsPreload00);
   tolua_function(tolua_S,"setIsPreload",tolua_SIX_SceneMgr_SIX_SceneData_setIsPreload00);
   tolua_function(tolua_S,"GetScenePtr",tolua_SIX_SceneMgr_SIX_SceneData_GetScenePtr00);
   tolua_function(tolua_S,"LoadScene",tolua_SIX_SceneMgr_SIX_SceneData_LoadScene00);
   tolua_variable(tolua_S,"m_Id",tolua_get_SIX_SceneData_unsigned_m_Id,tolua_set_SIX_SceneData_unsigned_m_Id);
   tolua_variable(tolua_S,"m_Path",tolua_get_SIX_SceneData_m_Path,tolua_set_SIX_SceneData_m_Path);
   tolua_variable(tolua_S,"m_IsPreload",tolua_get_SIX_SceneData_m_IsPreload,tolua_set_SIX_SceneData_m_IsPreload);
   tolua_variable(tolua_S,"m_Scene",tolua_get_SIX_SceneData_m_Scene_ptr,tolua_set_SIX_SceneData_m_Scene_ptr);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_SceneMgr","SIX_SceneMgr","SIX_EntityMgr",tolua_collect_SIX_SceneMgr);
  #else
  tolua_cclass(tolua_S,"SIX_SceneMgr","SIX_SceneMgr","SIX_EntityMgr",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_SceneMgr");
   tolua_function(tolua_S,"new",tolua_SIX_SceneMgr_SIX_SceneMgr_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_SceneMgr_SIX_SceneMgr_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_SceneMgr_SIX_SceneMgr_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_SceneMgr_SIX_SceneMgr_delete00);
   tolua_function(tolua_S,"ParseNode",tolua_SIX_SceneMgr_SIX_SceneMgr_ParseNode00);
   tolua_function(tolua_S,"ParseXML",tolua_SIX_SceneMgr_SIX_SceneMgr_ParseXML00);
   tolua_function(tolua_S,"Run",tolua_SIX_SceneMgr_SIX_SceneMgr_Run00);
   tolua_function(tolua_S,"Release",tolua_SIX_SceneMgr_SIX_SceneMgr_Release00);
   tolua_function(tolua_S,"SetSceneResourceFolder",tolua_SIX_SceneMgr_SIX_SceneMgr_SetSceneResourceFolder00);
   tolua_function(tolua_S,"GetTotalSceneCount",tolua_SIX_SceneMgr_SIX_SceneMgr_GetTotalSceneCount00);
   tolua_function(tolua_S,"GetPreloadSceneCount",tolua_SIX_SceneMgr_SIX_SceneMgr_GetPreloadSceneCount00);
   tolua_function(tolua_S,"GetCurrentSceneIdx",tolua_SIX_SceneMgr_SIX_SceneMgr_GetCurrentSceneIdx00);
   tolua_function(tolua_S,"unloadScene",tolua_SIX_SceneMgr_SIX_SceneMgr_unloadScene00);
   tolua_function(tolua_S,"preloadScene",tolua_SIX_SceneMgr_SIX_SceneMgr_preloadScene00);
   tolua_function(tolua_S,"changeScene",tolua_SIX_SceneMgr_SIX_SceneMgr_changeScene00);
   tolua_function(tolua_S,"GetScenePointer",tolua_SIX_SceneMgr_SIX_SceneMgr_GetScenePointer00);
   tolua_variable(tolua_S,"m_SceneBasePath",tolua_get_SIX_SceneMgr_m_SceneBasePath_ptr,tolua_set_SIX_SceneMgr_m_SceneBasePath_ptr);
   tolua_variable(tolua_S,"m_PreloadCount",tolua_get_SIX_SceneMgr_unsigned_m_PreloadCount,tolua_set_SIX_SceneMgr_unsigned_m_PreloadCount);
   tolua_variable(tolua_S,"m_CurrentSceneIdx",tolua_get_SIX_SceneMgr_m_CurrentSceneIdx,tolua_set_SIX_SceneMgr_m_CurrentSceneIdx);
   tolua_variable(tolua_S,"__TSingleton_SIX_SceneMgr___",tolua_get_SIX_SceneMgr___TSingleton_SIX_SceneMgr___,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_SceneMgr (lua_State* tolua_S) {
 return tolua_SIX_SceneMgr_open(tolua_S);
};
#endif


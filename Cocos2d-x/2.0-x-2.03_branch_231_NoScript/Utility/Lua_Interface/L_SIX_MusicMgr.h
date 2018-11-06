/*
** Lua binding: SIX_MusicMgr
** Generated automatically by tolua++-1.0.92 on 05/02/13 10:58:00.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_MusicMgr_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_SoundData (lua_State* tolua_S)
{
 SIX_SoundData* self = (SIX_SoundData*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_MusicMgr (lua_State* tolua_S)
{
 SIX_MusicMgr* self = (SIX_MusicMgr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCString (lua_State* tolua_S)
{
 CCString* self = (CCString*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_MusicMgr_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_Interface");
 tolua_usertype(tolua_S,"TSingleton<SIX_MusicMgr>");
 tolua_usertype(tolua_S,"SIX_SoundData");
 tolua_usertype(tolua_S,"SIX_EntityMgr");
 tolua_usertype(tolua_S,"SIX_DSTPL<SIX_XmlDataSet>");
 tolua_usertype(tolua_S,"SIX_XmlDataSet");
 tolua_usertype(tolua_S,"SIX_MusicMgr");
 tolua_usertype(tolua_S,"SimpleAudioEngine");
 tolua_usertype(tolua_S,"CCString");
}

/* method: new of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_new00
static int tolua_SIX_MusicMgr_SIX_SoundData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_SoundData* tolua_ret = (SIX_SoundData*)  Mtolua_new((SIX_SoundData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SoundData");
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

/* method: new_local of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_new00_local
static int tolua_SIX_MusicMgr_SIX_SoundData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_SoundData* tolua_ret = (SIX_SoundData*)  Mtolua_new((SIX_SoundData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_SoundData");
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

/* method: getId of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_getId00
static int tolua_SIX_MusicMgr_SIX_SoundData_getId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setId of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_setId00
static int tolua_SIX_MusicMgr_SIX_SoundData_setId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPath of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_getPath00
static int tolua_SIX_MusicMgr_SIX_SoundData_getPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPath of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_setPath00
static int tolua_SIX_MusicMgr_SIX_SoundData_setPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getType of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_getType00
static int tolua_SIX_MusicMgr_SIX_SoundData_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setType of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_setType00
static int tolua_SIX_MusicMgr_SIX_SoundData_setType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
  int Type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setType'", NULL);
#endif
  {
   self->setType(Type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsPreload of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_getIsPreload00
static int tolua_SIX_MusicMgr_SIX_SoundData_getIsPreload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setIsPreload of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_SoundData_setIsPreload00
static int tolua_SIX_MusicMgr_SIX_SoundData_setIsPreload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_SoundData",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_Id of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SoundData_unsigned_m_Id
static int tolua_get_SIX_SoundData_unsigned_m_Id(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_Id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Id of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SoundData_unsigned_m_Id
static int tolua_set_SIX_SoundData_unsigned_m_Id(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_Path of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SoundData_m_Path
static int tolua_get_SIX_SoundData_m_Path(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Path'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_Path,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Path of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SoundData_m_Path
static int tolua_set_SIX_SoundData_m_Path(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_Type of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SoundData_m_Type
static int tolua_get_SIX_SoundData_m_Type(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_Type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Type of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SoundData_m_Type
static int tolua_set_SIX_SoundData_m_Type(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Type = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_IsPreload of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_get_SIX_SoundData_m_IsPreload
static int tolua_get_SIX_SoundData_m_IsPreload(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_IsPreload'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_IsPreload);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_IsPreload of class  SIX_SoundData */
#ifndef TOLUA_DISABLE_tolua_set_SIX_SoundData_m_IsPreload
static int tolua_set_SIX_SoundData_m_IsPreload(lua_State* tolua_S)
{
  SIX_SoundData* self = (SIX_SoundData*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_new00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_MusicMgr* tolua_ret = (SIX_MusicMgr*)  Mtolua_new((SIX_MusicMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_MusicMgr");
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

/* method: new_local of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_new00_local
static int tolua_SIX_MusicMgr_SIX_MusicMgr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_MusicMgr* tolua_ret = (SIX_MusicMgr*)  Mtolua_new((SIX_MusicMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_MusicMgr");
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

/* method: delete of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_delete00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ParseNode of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_ParseNode00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_ParseNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_XmlDataSet",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ParseXML of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_ParseXML00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_ParseXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_XmlDataSet>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Run of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_Run00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Release of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_Release00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetSoundResourceFolder of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_SetSoundResourceFolder00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_SetSoundResourceFolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* folder = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSoundResourceFolder'", NULL);
#endif
  {
   self->SetSoundResourceFolder(folder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSoundResourceFolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalSoundCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_GetTotalSoundCount00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_GetTotalSoundCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalSoundCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetTotalSoundCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalSoundCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBgSoundCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_GetBgSoundCount00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_GetBgSoundCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBgSoundCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetBgSoundCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBgSoundCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffectSoundCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_GetEffectSoundCount00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_GetEffectSoundCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffectSoundCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetEffectSoundCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEffectSoundCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_preloadBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_preloadBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadBackgroundMusic'", NULL);
#endif
  {
   self->preloadBackgroundMusic(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playBackgroundMusic'", NULL);
#endif
  {
   self->playBackgroundMusic(nSoundId,bLoop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic01
static int tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playBackgroundMusic'", NULL);
#endif
  {
   self->playBackgroundMusic(nSoundId);
  }
 }
 return 0;
tolua_lerror:
 return tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  bool bReleaseData = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopBackgroundMusic'", NULL);
#endif
  {
   self->stopBackgroundMusic(bReleaseData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic01
static int tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopBackgroundMusic'", NULL);
#endif
  {
   self->stopBackgroundMusic();
  }
 }
 return 0;
tolua_lerror:
 return tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_pauseBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_pauseBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseBackgroundMusic'", NULL);
#endif
  {
   self->pauseBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_resumeBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_resumeBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeBackgroundMusic'", NULL);
#endif
  {
   self->resumeBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rewindBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_rewindBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_rewindBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rewindBackgroundMusic'", NULL);
#endif
  {
   self->rewindBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rewindBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: willPlayBackgroundMusic of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_willPlayBackgroundMusic00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_willPlayBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'willPlayBackgroundMusic'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->willPlayBackgroundMusic();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'willPlayBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBackgroundMusicPlaying of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_isBackgroundMusicPlaying00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_isBackgroundMusicPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBackgroundMusicPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBackgroundMusicPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBackgroundMusicPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundMusicVolume of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_getBackgroundMusicVolume00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_getBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundMusicVolume'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getBackgroundMusicVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundMusicVolume of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_setBackgroundMusicVolume00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_setBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundMusicVolume'", NULL);
#endif
  {
   self->setBackgroundMusicVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEffectsVolume of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_getEffectsVolume00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_getEffectsVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEffectsVolume'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getEffectsVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEffectsVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEffectsVolume of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_setEffectsVolume00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_setEffectsVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEffectsVolume'", NULL);
#endif
  {
   self->setEffectsVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEffectsVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->playEffect(nSoundId,bLoop);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect01
static int tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->playEffect(nSoundId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_pauseEffect00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_pauseEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseEffect'", NULL);
#endif
  {
   self->pauseEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseAllEffects of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_pauseAllEffects00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_pauseAllEffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseAllEffects'", NULL);
#endif
  {
   self->pauseAllEffects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseAllEffects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_resumeEffect00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_resumeEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeEffect'", NULL);
#endif
  {
   self->resumeEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeAllEffects of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_resumeAllEffects00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_resumeAllEffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeAllEffects'", NULL);
#endif
  {
   self->resumeAllEffects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeAllEffects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_stopEffect00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_stopEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopEffect'", NULL);
#endif
  {
   self->stopEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAllEffects of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_stopAllEffects00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_stopAllEffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAllEffects'", NULL);
#endif
  {
   self->stopAllEffects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAllEffects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_preloadEffect00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_preloadEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadEffect'", NULL);
#endif
  {
   self->preloadEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadEffect of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_MusicMgr_SIX_MusicMgr_unloadEffect00
static int tolua_SIX_MusicMgr_SIX_MusicMgr_unloadEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MusicMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool bDel = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadEffect'", NULL);
#endif
  {
   self->unloadEffect(nSoundId,bDel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_AudioEngine of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_MusicMgr_m_AudioEngine_ptr
static int tolua_get_SIX_MusicMgr_m_AudioEngine_ptr(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_AudioEngine'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_AudioEngine,"SimpleAudioEngine");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_AudioEngine of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_MusicMgr_m_AudioEngine_ptr
static int tolua_set_SIX_MusicMgr_m_AudioEngine_ptr(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_AudioEngine'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SimpleAudioEngine",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_AudioEngine = ((SimpleAudioEngine*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_SoundBasePath of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_MusicMgr_m_SoundBasePath_ptr
static int tolua_get_SIX_MusicMgr_m_SoundBasePath_ptr(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_SoundBasePath'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_SoundBasePath,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_SoundBasePath of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_MusicMgr_m_SoundBasePath_ptr
static int tolua_set_SIX_MusicMgr_m_SoundBasePath_ptr(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_SoundBasePath'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_SoundBasePath = ((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_BgCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_MusicMgr_unsigned_m_BgCount
static int tolua_get_SIX_MusicMgr_unsigned_m_BgCount(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_BgCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_BgCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_BgCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_MusicMgr_unsigned_m_BgCount
static int tolua_set_SIX_MusicMgr_unsigned_m_BgCount(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_BgCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_BgCount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_EffectCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_MusicMgr_unsigned_m_EffectCount
static int tolua_get_SIX_MusicMgr_unsigned_m_EffectCount(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_EffectCount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_EffectCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_EffectCount of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_MusicMgr_unsigned_m_EffectCount
static int tolua_set_SIX_MusicMgr_unsigned_m_EffectCount(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_EffectCount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_EffectCount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __TSingleton<SIX_MusicMgr>__ of class  SIX_MusicMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_MusicMgr___TSingleton_SIX_MusicMgr___
static int tolua_get_SIX_MusicMgr___TSingleton_SIX_MusicMgr___(lua_State* tolua_S)
{
  SIX_MusicMgr* self = (SIX_MusicMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__TSingleton<SIX_MusicMgr>__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<TSingleton<SIX_MusicMgr>*>(self), "TSingleton<SIX_MusicMgr>");
#else
   tolua_pushusertype(tolua_S,(void*)((TSingleton<SIX_MusicMgr>*)self), "TSingleton<SIX_MusicMgr>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_MusicMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_MusicMgr_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_SoundData","SIX_SoundData","SIX_Interface",tolua_collect_SIX_SoundData);
  #else
  tolua_cclass(tolua_S,"SIX_SoundData","SIX_SoundData","SIX_Interface",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_SoundData");
   tolua_function(tolua_S,"new",tolua_SIX_MusicMgr_SIX_SoundData_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_MusicMgr_SIX_SoundData_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_MusicMgr_SIX_SoundData_new00_local);
   tolua_function(tolua_S,"getId",tolua_SIX_MusicMgr_SIX_SoundData_getId00);
   tolua_function(tolua_S,"setId",tolua_SIX_MusicMgr_SIX_SoundData_setId00);
   tolua_function(tolua_S,"getPath",tolua_SIX_MusicMgr_SIX_SoundData_getPath00);
   tolua_function(tolua_S,"setPath",tolua_SIX_MusicMgr_SIX_SoundData_setPath00);
   tolua_function(tolua_S,"getType",tolua_SIX_MusicMgr_SIX_SoundData_getType00);
   tolua_function(tolua_S,"setType",tolua_SIX_MusicMgr_SIX_SoundData_setType00);
   tolua_function(tolua_S,"getIsPreload",tolua_SIX_MusicMgr_SIX_SoundData_getIsPreload00);
   tolua_function(tolua_S,"setIsPreload",tolua_SIX_MusicMgr_SIX_SoundData_setIsPreload00);
   tolua_variable(tolua_S,"m_Id",tolua_get_SIX_SoundData_unsigned_m_Id,tolua_set_SIX_SoundData_unsigned_m_Id);
   tolua_variable(tolua_S,"m_Path",tolua_get_SIX_SoundData_m_Path,tolua_set_SIX_SoundData_m_Path);
   tolua_variable(tolua_S,"m_Type",tolua_get_SIX_SoundData_m_Type,tolua_set_SIX_SoundData_m_Type);
   tolua_variable(tolua_S,"m_IsPreload",tolua_get_SIX_SoundData_m_IsPreload,tolua_set_SIX_SoundData_m_IsPreload);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_MusicMgr","SIX_MusicMgr","SIX_EntityMgr",tolua_collect_SIX_MusicMgr);
  #else
  tolua_cclass(tolua_S,"SIX_MusicMgr","SIX_MusicMgr","SIX_EntityMgr",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_MusicMgr");
   tolua_function(tolua_S,"new",tolua_SIX_MusicMgr_SIX_MusicMgr_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_MusicMgr_SIX_MusicMgr_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_MusicMgr_SIX_MusicMgr_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_MusicMgr_SIX_MusicMgr_delete00);
   tolua_function(tolua_S,"ParseNode",tolua_SIX_MusicMgr_SIX_MusicMgr_ParseNode00);
   tolua_function(tolua_S,"ParseXML",tolua_SIX_MusicMgr_SIX_MusicMgr_ParseXML00);
   tolua_function(tolua_S,"Run",tolua_SIX_MusicMgr_SIX_MusicMgr_Run00);
   tolua_function(tolua_S,"Release",tolua_SIX_MusicMgr_SIX_MusicMgr_Release00);
   tolua_function(tolua_S,"SetSoundResourceFolder",tolua_SIX_MusicMgr_SIX_MusicMgr_SetSoundResourceFolder00);
   tolua_function(tolua_S,"GetTotalSoundCount",tolua_SIX_MusicMgr_SIX_MusicMgr_GetTotalSoundCount00);
   tolua_function(tolua_S,"GetBgSoundCount",tolua_SIX_MusicMgr_SIX_MusicMgr_GetBgSoundCount00);
   tolua_function(tolua_S,"GetEffectSoundCount",tolua_SIX_MusicMgr_SIX_MusicMgr_GetEffectSoundCount00);
   tolua_function(tolua_S,"preloadBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_preloadBackgroundMusic00);
   tolua_function(tolua_S,"playBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic00);
   tolua_function(tolua_S,"playBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_playBackgroundMusic01);
   tolua_function(tolua_S,"stopBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic00);
   tolua_function(tolua_S,"stopBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_stopBackgroundMusic01);
   tolua_function(tolua_S,"pauseBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_pauseBackgroundMusic00);
   tolua_function(tolua_S,"resumeBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_resumeBackgroundMusic00);
   tolua_function(tolua_S,"rewindBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_rewindBackgroundMusic00);
   tolua_function(tolua_S,"willPlayBackgroundMusic",tolua_SIX_MusicMgr_SIX_MusicMgr_willPlayBackgroundMusic00);
   tolua_function(tolua_S,"isBackgroundMusicPlaying",tolua_SIX_MusicMgr_SIX_MusicMgr_isBackgroundMusicPlaying00);
   tolua_function(tolua_S,"getBackgroundMusicVolume",tolua_SIX_MusicMgr_SIX_MusicMgr_getBackgroundMusicVolume00);
   tolua_function(tolua_S,"setBackgroundMusicVolume",tolua_SIX_MusicMgr_SIX_MusicMgr_setBackgroundMusicVolume00);
   tolua_function(tolua_S,"getEffectsVolume",tolua_SIX_MusicMgr_SIX_MusicMgr_getEffectsVolume00);
   tolua_function(tolua_S,"setEffectsVolume",tolua_SIX_MusicMgr_SIX_MusicMgr_setEffectsVolume00);
   tolua_function(tolua_S,"playEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect00);
   tolua_function(tolua_S,"playEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_playEffect01);
   tolua_function(tolua_S,"pauseEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_pauseEffect00);
   tolua_function(tolua_S,"pauseAllEffects",tolua_SIX_MusicMgr_SIX_MusicMgr_pauseAllEffects00);
   tolua_function(tolua_S,"resumeEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_resumeEffect00);
   tolua_function(tolua_S,"resumeAllEffects",tolua_SIX_MusicMgr_SIX_MusicMgr_resumeAllEffects00);
   tolua_function(tolua_S,"stopEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_stopEffect00);
   tolua_function(tolua_S,"stopAllEffects",tolua_SIX_MusicMgr_SIX_MusicMgr_stopAllEffects00);
   tolua_function(tolua_S,"preloadEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_preloadEffect00);
   tolua_function(tolua_S,"unloadEffect",tolua_SIX_MusicMgr_SIX_MusicMgr_unloadEffect00);
   tolua_variable(tolua_S,"m_AudioEngine",tolua_get_SIX_MusicMgr_m_AudioEngine_ptr,tolua_set_SIX_MusicMgr_m_AudioEngine_ptr);
   tolua_variable(tolua_S,"m_SoundBasePath",tolua_get_SIX_MusicMgr_m_SoundBasePath_ptr,tolua_set_SIX_MusicMgr_m_SoundBasePath_ptr);
   tolua_variable(tolua_S,"m_BgCount",tolua_get_SIX_MusicMgr_unsigned_m_BgCount,tolua_set_SIX_MusicMgr_unsigned_m_BgCount);
   tolua_variable(tolua_S,"m_EffectCount",tolua_get_SIX_MusicMgr_unsigned_m_EffectCount,tolua_set_SIX_MusicMgr_unsigned_m_EffectCount);
   tolua_variable(tolua_S,"__TSingleton_SIX_MusicMgr___",tolua_get_SIX_MusicMgr___TSingleton_SIX_MusicMgr___,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_MusicMgr (lua_State* tolua_S) {
 return tolua_SIX_MusicMgr_open(tolua_S);
};
#endif


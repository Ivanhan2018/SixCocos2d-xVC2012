/*
** Lua binding: SIX_EntityMgr
** Generated automatically by tolua++-1.0.92 on 05/03/13 14:41:13.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_EntityMgr_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_EntityMgr (lua_State* tolua_S)
{
 SIX_EntityMgr* self = (SIX_EntityMgr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_EntityMgr_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_DSTPL<SIX_XmlDataSet>");
 tolua_usertype(tolua_S,"CCFileUtils");
 tolua_usertype(tolua_S,"SIX_XMLParser");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"SIX_EntityMgr");
 tolua_usertype(tolua_S,"SIX_Interface");
}

/* method: delete of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_delete00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: LoadXMLFromFile of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_LoadXMLFromFile00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_LoadXMLFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadXMLFromFile'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LoadXMLFromFile(file);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadXMLFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadXMLFromMemory of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_LoadXMLFromMemory00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_LoadXMLFromMemory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned char* stream = ((unsigned char*)  tolua_tostring(tolua_S,2,0));
  unsigned long len = ((unsigned long)  tolua_tonumber(tolua_S,3,0));
  int encoding = ((int)  tolua_tonumber(tolua_S,4,TIXML_DEFAULT_ENCODING));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadXMLFromMemory'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LoadXMLFromMemory(stream,len,encoding);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadXMLFromMemory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseXML of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_ReleaseXML00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_ReleaseXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseXML'", NULL);
#endif
  {
   self->ReleaseXML();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseXML'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseXML of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_ParseXML00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_ParseXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_XmlDataSet>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Run of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_Run00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Release of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_Release00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetFilePtr of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_GetFilePtr00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_GetFilePtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_EntityMgr* self = (const SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFilePtr'", NULL);
#endif
  {
   CCFileUtils* tolua_ret = (CCFileUtils*)  self->GetFilePtr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFileUtils");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFilePtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDictPtr of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_GetDictPtr00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_GetDictPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_EntityMgr* self = (const SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDictPtr'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->GetDictPtr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDictPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddObjToDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pValue = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  int idx = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddObjToDict'", NULL);
#endif
  {
   self->AddObjToDict(pValue,idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddObjToDict'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddObjToDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict01
static int tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pValue = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddObjToDict'", NULL);
#endif
  {
   self->AddObjToDict(pValue,key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjFromDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjFromDict'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->GetObjFromDict(idx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetObjFromDict'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjFromDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict01
static int tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjFromDict'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->GetObjFromDict(key);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 2;
tolua_lerror:
 return tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelObjFromDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelObjFromDict'", NULL);
#endif
  {
   self->DelObjFromDict(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelObjFromDict'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelObjFromDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict01
static int tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelObjFromDict'", NULL);
#endif
  {
   self->DelObjFromDict(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelAllObjFromDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_DelAllObjFromDict00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_DelAllObjFromDict00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelAllObjFromDict'", NULL);
#endif
  {
   self->DelAllObjFromDict();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelAllObjFromDict'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjCount of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjCount00
static int tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EntityMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetObjCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetObjCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pFileUtils of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_EntityMgr_pFileUtils_ptr
static int tolua_get_SIX_EntityMgr_pFileUtils_ptr(lua_State* tolua_S)
{
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pFileUtils'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pFileUtils,"CCFileUtils");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pFileUtils of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_EntityMgr_pFileUtils_ptr
static int tolua_set_SIX_EntityMgr_pFileUtils_ptr(lua_State* tolua_S)
{
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pFileUtils'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCFileUtils",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pFileUtils = ((CCFileUtils*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_EntityMgr_pDict_ptr
static int tolua_get_SIX_EntityMgr_pDict_ptr(lua_State* tolua_S)
{
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pDict'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pDict,"CCDictionary");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pDict of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_EntityMgr_pDict_ptr
static int tolua_set_SIX_EntityMgr_pDict_ptr(lua_State* tolua_S)
{
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pDict'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pDict = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pXML of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_EntityMgr_pXML_ptr
static int tolua_get_SIX_EntityMgr_pXML_ptr(lua_State* tolua_S)
{
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pXML'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->pXML,"SIX_XMLParser");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pXML of class  SIX_EntityMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_EntityMgr_pXML_ptr
static int tolua_set_SIX_EntityMgr_pXML_ptr(lua_State* tolua_S)
{
  SIX_EntityMgr* self = (SIX_EntityMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pXML'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_XMLParser",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pXML = ((SIX_XMLParser*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_EntityMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_EntityMgr_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_EntityMgr","SIX_EntityMgr","SIX_Interface",tolua_collect_SIX_EntityMgr);
  #else
  tolua_cclass(tolua_S,"SIX_EntityMgr","SIX_EntityMgr","SIX_Interface",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_EntityMgr");
   tolua_function(tolua_S,"delete",tolua_SIX_EntityMgr_SIX_EntityMgr_delete00);
   tolua_function(tolua_S,"LoadXMLFromFile",tolua_SIX_EntityMgr_SIX_EntityMgr_LoadXMLFromFile00);
   tolua_function(tolua_S,"LoadXMLFromMemory",tolua_SIX_EntityMgr_SIX_EntityMgr_LoadXMLFromMemory00);
   tolua_function(tolua_S,"ReleaseXML",tolua_SIX_EntityMgr_SIX_EntityMgr_ReleaseXML00);
   tolua_function(tolua_S,"ParseXML",tolua_SIX_EntityMgr_SIX_EntityMgr_ParseXML00);
   tolua_function(tolua_S,"Run",tolua_SIX_EntityMgr_SIX_EntityMgr_Run00);
   tolua_function(tolua_S,"Release",tolua_SIX_EntityMgr_SIX_EntityMgr_Release00);
   tolua_function(tolua_S,"GetFilePtr",tolua_SIX_EntityMgr_SIX_EntityMgr_GetFilePtr00);
   tolua_function(tolua_S,"GetDictPtr",tolua_SIX_EntityMgr_SIX_EntityMgr_GetDictPtr00);
   tolua_function(tolua_S,"AddObjToDict",tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict00);
   tolua_function(tolua_S,"AddObjToDict",tolua_SIX_EntityMgr_SIX_EntityMgr_AddObjToDict01);
   tolua_function(tolua_S,"GetObjFromDict",tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict00);
   tolua_function(tolua_S,"GetObjFromDict",tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjFromDict01);
   tolua_function(tolua_S,"DelObjFromDict",tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict00);
   tolua_function(tolua_S,"DelObjFromDict",tolua_SIX_EntityMgr_SIX_EntityMgr_DelObjFromDict01);
   tolua_function(tolua_S,"DelAllObjFromDict",tolua_SIX_EntityMgr_SIX_EntityMgr_DelAllObjFromDict00);
   tolua_function(tolua_S,"GetObjCount",tolua_SIX_EntityMgr_SIX_EntityMgr_GetObjCount00);
   tolua_variable(tolua_S,"pFileUtils",tolua_get_SIX_EntityMgr_pFileUtils_ptr,tolua_set_SIX_EntityMgr_pFileUtils_ptr);
   tolua_variable(tolua_S,"pDict",tolua_get_SIX_EntityMgr_pDict_ptr,tolua_set_SIX_EntityMgr_pDict_ptr);
   tolua_variable(tolua_S,"pXML",tolua_get_SIX_EntityMgr_pXML_ptr,tolua_set_SIX_EntityMgr_pXML_ptr);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_EntityMgr (lua_State* tolua_S) {
 return tolua_SIX_EntityMgr_open(tolua_S);
};
#endif


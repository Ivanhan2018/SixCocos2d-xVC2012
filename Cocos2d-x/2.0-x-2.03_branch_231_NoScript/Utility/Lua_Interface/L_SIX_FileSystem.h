/*
** Lua binding: SIX_FileSystem
** Generated automatically by tolua++-1.0.92 on 05/03/13 19:14:22.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_FileSystem_open (lua_State* tolua_S);


/* function to register type */
static void tolua_SIX_FileSystem_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_DSTPL<SIX_XmlDataSet>");
 tolua_usertype(tolua_S,"SIX_FileSystem");
 tolua_usertype(tolua_S,"SIX_EntityMgr");
 tolua_usertype(tolua_S,"TSingleton<SIX_FileSystem>");
}

/* method: ParseXML of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_ParseXML00
static int tolua_SIX_FileSystem_SIX_FileSystem_ParseXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_XmlDataSet>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Run of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_Run00
static int tolua_SIX_FileSystem_SIX_FileSystem_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Release of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_Release00
static int tolua_SIX_FileSystem_SIX_FileSystem_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: CreateFolder of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_CreateFolder00
static int tolua_SIX_FileSystem_SIX_FileSystem_CreateFolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* folder = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateFolder'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CreateFolder(folder);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateFolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPathExists of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_IsPathExists00
static int tolua_SIX_FileSystem_SIX_FileSystem_IsPathExists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPathExists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPathExists(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPathExists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadDataFromFile of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_LoadDataFromFile00
static int tolua_SIX_FileSystem_SIX_FileSystem_LoadDataFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  char* pData = ((char*)  tolua_tostring(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadDataFromFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadDataFromFile(pData,file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadDataFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveDataToFile of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_SaveDataToFile00
static int tolua_SIX_FileSystem_SIX_FileSystem_SaveDataToFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  char* pData = ((char*)  tolua_tostring(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveDataToFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SaveDataToFile(pData,file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveDataToFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ZipFile of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_ZipFile00
static int tolua_SIX_FileSystem_SIX_FileSystem_ZipFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pSrcFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  char* pDstFile = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ZipFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ZipFile(pSrcFile,pDstFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ZipFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnZipFile of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_UnZipFile00
static int tolua_SIX_FileSystem_SIX_FileSystem_UnZipFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pSrcFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  char* pDstFile = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnZipFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->UnZipFile(pSrcFile,pDstFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnZipFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Encrypt of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_Encrypt00
static int tolua_SIX_FileSystem_SIX_FileSystem_Encrypt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pSrc = ((const char*)  tolua_tostring(tolua_S,2,0));
  int slen = ((int)  tolua_tonumber(tolua_S,3,0));
  char* pDst = ((char*)  tolua_tostring(tolua_S,4,0));
  int dlen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Encrypt'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Encrypt(pSrc,slen,pDst,&dlen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)dlen);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Encrypt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Decrypt of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_Decrypt00
static int tolua_SIX_FileSystem_SIX_FileSystem_Decrypt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pSrc = ((const char*)  tolua_tostring(tolua_S,2,0));
  int slen = ((int)  tolua_tonumber(tolua_S,3,0));
  char* pDst = ((char*)  tolua_tostring(tolua_S,4,0));
  int dlen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Decrypt'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Decrypt(pSrc,slen,pDst,&dlen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)dlen);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Decrypt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EncryptFile of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_EncryptFile00
static int tolua_SIX_FileSystem_SIX_FileSystem_EncryptFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pSrcFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  char* pDstFile = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EncryptFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->EncryptFile(pSrcFile,pDstFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EncryptFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DecryptFile of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_SIX_FileSystem_SIX_FileSystem_DecryptFile00
static int tolua_SIX_FileSystem_SIX_FileSystem_DecryptFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_FileSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pSrcFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  char* pDstFile = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DecryptFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->DecryptFile(pSrcFile,pDstFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DecryptFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __TSingleton<SIX_FileSystem>__ of class  SIX_FileSystem */
#ifndef TOLUA_DISABLE_tolua_get_SIX_FileSystem___TSingleton_SIX_FileSystem___
static int tolua_get_SIX_FileSystem___TSingleton_SIX_FileSystem___(lua_State* tolua_S)
{
  SIX_FileSystem* self = (SIX_FileSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__TSingleton<SIX_FileSystem>__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<TSingleton<SIX_FileSystem>*>(self), "TSingleton<SIX_FileSystem>");
#else
   tolua_pushusertype(tolua_S,(void*)((TSingleton<SIX_FileSystem>*)self), "TSingleton<SIX_FileSystem>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_FileSystem_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_FileSystem_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"SIX_FileSystem","SIX_FileSystem","SIX_EntityMgr",NULL);
  tolua_beginmodule(tolua_S,"SIX_FileSystem");
   tolua_function(tolua_S,"ParseXML",tolua_SIX_FileSystem_SIX_FileSystem_ParseXML00);
   tolua_function(tolua_S,"Run",tolua_SIX_FileSystem_SIX_FileSystem_Run00);
   tolua_function(tolua_S,"Release",tolua_SIX_FileSystem_SIX_FileSystem_Release00);
   tolua_function(tolua_S,"CreateFolder",tolua_SIX_FileSystem_SIX_FileSystem_CreateFolder00);
   tolua_function(tolua_S,"IsPathExists",tolua_SIX_FileSystem_SIX_FileSystem_IsPathExists00);
   tolua_function(tolua_S,"LoadDataFromFile",tolua_SIX_FileSystem_SIX_FileSystem_LoadDataFromFile00);
   tolua_function(tolua_S,"SaveDataToFile",tolua_SIX_FileSystem_SIX_FileSystem_SaveDataToFile00);
   tolua_function(tolua_S,"ZipFile",tolua_SIX_FileSystem_SIX_FileSystem_ZipFile00);
   tolua_function(tolua_S,"UnZipFile",tolua_SIX_FileSystem_SIX_FileSystem_UnZipFile00);
   tolua_function(tolua_S,"Encrypt",tolua_SIX_FileSystem_SIX_FileSystem_Encrypt00);
   tolua_function(tolua_S,"Decrypt",tolua_SIX_FileSystem_SIX_FileSystem_Decrypt00);
   tolua_function(tolua_S,"EncryptFile",tolua_SIX_FileSystem_SIX_FileSystem_EncryptFile00);
   tolua_function(tolua_S,"DecryptFile",tolua_SIX_FileSystem_SIX_FileSystem_DecryptFile00);
   tolua_variable(tolua_S,"__TSingleton_SIX_FileSystem___",tolua_get_SIX_FileSystem___TSingleton_SIX_FileSystem___,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_FileSystem (lua_State* tolua_S) {
 return tolua_SIX_FileSystem_open(tolua_S);
};
#endif


/*
** Lua binding: SIX_PackageMgr
** Generated automatically by tolua++-1.0.92 on 05/08/13 15:07:59.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_PackageMgr_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_MSG_INFO (lua_State* tolua_S)
{
 MSG_INFO* self = (MSG_INFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_PackageMgr (lua_State* tolua_S)
{
 SIX_PackageMgr* self = (SIX_PackageMgr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_PackageMgr_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MSG_INFO");
 tolua_usertype(tolua_S,"SIX_PackageMgr");
}

/* get function: m_MainCode of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_get_MSG_INFO_m_MainCode
static int tolua_get_MSG_INFO_m_MainCode(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_MainCode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_MainCode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_MainCode of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_set_MSG_INFO_m_MainCode
static int tolua_set_MSG_INFO_m_MainCode(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_MainCode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_MainCode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_SubCode of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_get_MSG_INFO_m_SubCode
static int tolua_get_MSG_INFO_m_SubCode(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_SubCode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_SubCode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_SubCode of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_set_MSG_INFO_m_SubCode
static int tolua_set_MSG_INFO_m_SubCode(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_SubCode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_SubCode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Data of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_get_MSG_INFO_m_Data
static int tolua_get_MSG_INFO_m_Data(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Data'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_Data);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Data of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_set_MSG_INFO_m_Data
static int tolua_set_MSG_INFO_m_Data(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Data'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Data = ((char*)  tolua_tostring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_DataLen of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_get_MSG_INFO_unsigned_m_DataLen
static int tolua_get_MSG_INFO_unsigned_m_DataLen(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_DataLen'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_DataLen);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_DataLen of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_set_MSG_INFO_unsigned_m_DataLen
static int tolua_set_MSG_INFO_unsigned_m_DataLen(lua_State* tolua_S)
{
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_DataLen'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_DataLen = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_MSG_INFO_new00
static int tolua_SIX_PackageMgr_MSG_INFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MSG_INFO* tolua_ret = (MSG_INFO*)  Mtolua_new((MSG_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MSG_INFO");
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

/* method: new_local of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_MSG_INFO_new00_local
static int tolua_SIX_PackageMgr_MSG_INFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MSG_INFO* tolua_ret = (MSG_INFO*)  Mtolua_new((MSG_INFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MSG_INFO");
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

/* method: delete of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_MSG_INFO_delete00
static int tolua_SIX_PackageMgr_MSG_INFO_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Creae of class  MSG_INFO */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_MSG_INFO_Creae00
static int tolua_SIX_PackageMgr_MSG_INFO_Creae00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MSG_INFO* self = (MSG_INFO*)  tolua_tousertype(tolua_S,1,0);
  int mainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int subCode = ((int)  tolua_tonumber(tolua_S,3,0));
  char* pData = ((char*)  tolua_tostring(tolua_S,4,0));
  unsigned int pDataLen = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Creae'", NULL);
#endif
  {
   self->Creae(mainCode,subCode,pData,pDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Creae'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SIX_PackageMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_SIX_PackageMgr_new00
static int tolua_SIX_PackageMgr_SIX_PackageMgr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_PackageMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_PackageMgr* tolua_ret = (SIX_PackageMgr*)  Mtolua_new((SIX_PackageMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_PackageMgr");
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

/* method: new_local of class  SIX_PackageMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_SIX_PackageMgr_new00_local
static int tolua_SIX_PackageMgr_SIX_PackageMgr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_PackageMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_PackageMgr* tolua_ret = (SIX_PackageMgr*)  Mtolua_new((SIX_PackageMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_PackageMgr");
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

/* method: delete of class  SIX_PackageMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_SIX_PackageMgr_delete00
static int tolua_SIX_PackageMgr_SIX_PackageMgr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_PackageMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_PackageMgr* self = (SIX_PackageMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Pack of class  SIX_PackageMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_SIX_PackageMgr_Pack00
static int tolua_SIX_PackageMgr_SIX_PackageMgr_Pack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_PackageMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MSG_INFO",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_PackageMgr* self = (SIX_PackageMgr*)  tolua_tousertype(tolua_S,1,0);
  MSG_INFO* pMsg = ((MSG_INFO*)  tolua_tousertype(tolua_S,2,0));
  char* pDst = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int pDstLen = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pack'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Pack(pMsg,pDst,&pDstLen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)pDstLen);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Pack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnPack of class  SIX_PackageMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_PackageMgr_SIX_PackageMgr_UnPack00
static int tolua_SIX_PackageMgr_SIX_PackageMgr_UnPack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_PackageMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"MSG_INFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_PackageMgr* self = (SIX_PackageMgr*)  tolua_tousertype(tolua_S,1,0);
  char* pSrc = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned int pSrcLen = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  MSG_INFO* pMsg = ((MSG_INFO*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnPack'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->UnPack(pSrc,pSrcLen,pMsg);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnPack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_PackageMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_PackageMgr_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MSG_INFO","MSG_INFO","",tolua_collect_MSG_INFO);
  #else
  tolua_cclass(tolua_S,"MSG_INFO","MSG_INFO","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MSG_INFO");
   tolua_variable(tolua_S,"m_MainCode",tolua_get_MSG_INFO_m_MainCode,tolua_set_MSG_INFO_m_MainCode);
   tolua_variable(tolua_S,"m_SubCode",tolua_get_MSG_INFO_m_SubCode,tolua_set_MSG_INFO_m_SubCode);
   tolua_variable(tolua_S,"m_Data",tolua_get_MSG_INFO_m_Data,tolua_set_MSG_INFO_m_Data);
   tolua_variable(tolua_S,"m_DataLen",tolua_get_MSG_INFO_unsigned_m_DataLen,tolua_set_MSG_INFO_unsigned_m_DataLen);
   tolua_function(tolua_S,"new",tolua_SIX_PackageMgr_MSG_INFO_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_PackageMgr_MSG_INFO_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_PackageMgr_MSG_INFO_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_PackageMgr_MSG_INFO_delete00);
   tolua_function(tolua_S,"Creae",tolua_SIX_PackageMgr_MSG_INFO_Creae00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_PackageMgr","SIX_PackageMgr","",tolua_collect_SIX_PackageMgr);
  #else
  tolua_cclass(tolua_S,"SIX_PackageMgr","SIX_PackageMgr","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_PackageMgr");
   tolua_function(tolua_S,"new",tolua_SIX_PackageMgr_SIX_PackageMgr_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_PackageMgr_SIX_PackageMgr_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_PackageMgr_SIX_PackageMgr_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_PackageMgr_SIX_PackageMgr_delete00);
   tolua_function(tolua_S,"Pack",tolua_SIX_PackageMgr_SIX_PackageMgr_Pack00);
   tolua_function(tolua_S,"UnPack",tolua_SIX_PackageMgr_SIX_PackageMgr_UnPack00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_PackageMgr (lua_State* tolua_S) {
 return tolua_SIX_PackageMgr_open(tolua_S);
};
#endif


/*
** Lua binding: SIX_Utility
** Generated automatically by tolua++-1.0.92 on 05/09/13 15:53:32.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_Utility_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_MP (lua_State* tolua_S)
{
 SIX_MP* self = (SIX_MP*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_Utility (lua_State* tolua_S)
{
 SIX_Utility* self = (SIX_Utility*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_Utility_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SYSTEMTIME");
 tolua_usertype(tolua_S,"SIX_MP");
 tolua_usertype(tolua_S,"MP");
 tolua_usertype(tolua_S,"size_t");
 tolua_usertype(tolua_S,"SIX_Utility");
 tolua_usertype(tolua_S,"TSingleton<SIX_Utility>");
}

/* method: new of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_new00
static int tolua_SIX_Utility_SIX_MP_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_MP* tolua_ret = (SIX_MP*)  Mtolua_new((SIX_MP)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_MP");
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

/* method: new_local of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_new00_local
static int tolua_SIX_Utility_SIX_MP_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_MP* tolua_ret = (SIX_MP*)  Mtolua_new((SIX_MP)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_MP");
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

/* method: delete of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_delete00
static int tolua_SIX_Utility_SIX_MP_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MP* self = (SIX_MP*)  tolua_tousertype(tolua_S,1,0);
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

/* method: size of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_size00
static int tolua_SIX_Utility_SIX_MP_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MP* self = (SIX_MP*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_push_back00
static int tolua_SIX_Utility_SIX_MP_push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MP* self = (SIX_MP*)  tolua_tousertype(tolua_S,1,0);
  const char* val = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pop_back of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_pop_back00
static int tolua_SIX_Utility_SIX_MP_pop_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MP* self = (SIX_MP*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pop_back'", NULL);
#endif
  {
   self->pop_back();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pop_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: at of class  SIX_MP */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_MP_at00
static int tolua_SIX_Utility_SIX_MP_at00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_MP",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_MP* self = (SIX_MP*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'at'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->at(idx);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'at'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_new00
static int tolua_SIX_Utility_SIX_Utility_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Utility* tolua_ret = (SIX_Utility*)  Mtolua_new((SIX_Utility)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Utility");
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

/* method: new_local of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_new00_local
static int tolua_SIX_Utility_SIX_Utility_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Utility* tolua_ret = (SIX_Utility*)  Mtolua_new((SIX_Utility)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Utility");
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

/* method: GetInstance of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_GetInstance00
static int tolua_SIX_Utility_SIX_Utility_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Utility* tolua_ret = (SIX_Utility*)  SIX_Utility::GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Utility");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: REVE_DWORD of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_REVE_DWORD00
static int tolua_SIX_Utility_SIX_Utility_REVE_DWORD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  unsigned long x = ((unsigned long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'REVE_DWORD'", NULL);
#endif
  {
   unsigned long tolua_ret = (unsigned long)  self->REVE_DWORD(x);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'REVE_DWORD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentThreadId of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_GetCurrentThreadId00
static int tolua_SIX_Utility_SIX_Utility_GetCurrentThreadId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentThreadId'", NULL);
#endif
  {
   unsigned long tolua_ret = (unsigned long)  self->GetCurrentThreadId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentThreadId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RNDNUM of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_RNDNUM00
static int tolua_SIX_Utility_SIX_Utility_RNDNUM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  int min = ((int)  tolua_tonumber(tolua_S,2,0));
  int max = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RNDNUM'", NULL);
#endif
  {
   int tolua_ret = (int)  self->RNDNUM(min,max);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RNDNUM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: code_convert of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_code_convert00
static int tolua_SIX_Utility_SIX_Utility_code_convert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"size_t",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,7,&tolua_err) || !tolua_isusertype(tolua_S,7,"size_t",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  const char* from_charset = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* to_charset = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* inbuf = ((const char*)  tolua_tostring(tolua_S,4,0));
  size_t inlen = *((size_t*)  tolua_tousertype(tolua_S,5,0));
  char* outbuf = ((char*)  tolua_tostring(tolua_S,6,0));
  size_t outlen = *((size_t*)  tolua_tousertype(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'code_convert'", NULL);
#endif
  {
   int tolua_ret = (int)  self->code_convert(from_charset,to_charset,inbuf,inlen,outbuf,outlen);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'code_convert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U2G of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_U2G00
static int tolua_SIX_Utility_SIX_Utility_U2G00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  const char* inbuf = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'U2G'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->U2G(inbuf);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U2G'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: G2U of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_G2U00
static int tolua_SIX_Utility_SIX_Utility_G2U00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  const char* inbuf = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'G2U'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->G2U(inbuf);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'G2U'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Split of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_Split00
static int tolua_SIX_Utility_SIX_Utility_Split00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"MP",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  char* sp = ((char*)  tolua_tostring(tolua_S,2,0));
  char* src = ((char*)  tolua_tostring(tolua_S,3,0));
  MP* ptr = ((MP*)  tolua_tousertype(tolua_S,4,0));
  int SplitCount = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Split'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Split(sp,src,ptr,SplitCount);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Split'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Split of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_Split01
static int tolua_SIX_Utility_SIX_Utility_Split01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"SIX_MP",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  char* sp = ((char*)  tolua_tostring(tolua_S,2,0));
  char* src = ((char*)  tolua_tostring(tolua_S,3,0));
  SIX_MP* ptr = ((SIX_MP*)  tolua_tousertype(tolua_S,4,0));
  int SplitCount = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Split'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Split(sp,src,ptr,SplitCount);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_Utility_SIX_Utility_Split00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTickCount of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_GetTickCount00
static int tolua_SIX_Utility_SIX_Utility_GetTickCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTickCount'", NULL);
#endif
  {
   unsigned long tolua_ret = (unsigned long)  self->GetTickCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTickCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalTime of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_GetLocalTime00
static int tolua_SIX_Utility_SIX_Utility_GetLocalTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SYSTEMTIME",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  SYSTEMTIME st = *((SYSTEMTIME*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalTime'", NULL);
#endif
  {
   self->GetLocalTime(st);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimerStart of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_TimerStart00
static int tolua_SIX_Utility_SIX_Utility_TimerStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimerStart'", NULL);
#endif
  {
   self->TimerStart();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimerStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimerEnd of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_TimerEnd00
static int tolua_SIX_Utility_SIX_Utility_TimerEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimerEnd'", NULL);
#endif
  {
   self->TimerEnd();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimerEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMilliseconds of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_GetMilliseconds00
static int tolua_SIX_Utility_SIX_Utility_GetMilliseconds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMilliseconds'", NULL);
#endif
  {
   double tolua_ret = (double)  self->GetMilliseconds();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMilliseconds'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGlobalSecond of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_GetGlobalSecond00
static int tolua_SIX_Utility_SIX_Utility_GetGlobalSecond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGlobalSecond'", NULL);
#endif
  {
   double tolua_ret = (double)  self->GetGlobalSecond();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGlobalSecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Fixed of class  SIX_Utility */
#ifndef TOLUA_DISABLE_tolua_SIX_Utility_SIX_Utility_Fixed00
static int tolua_SIX_Utility_SIX_Utility_Fixed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Utility",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Utility* self = (SIX_Utility*)  tolua_tousertype(tolua_S,1,0);
  double tolua_var_1 = ((double)  tolua_tonumber(tolua_S,2,0));
  int tolua_var_2 = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Fixed'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Fixed(tolua_var_1,tolua_var_2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Fixed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_Utility_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_Utility_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_MP","SIX_MP","",tolua_collect_SIX_MP);
  #else
  tolua_cclass(tolua_S,"SIX_MP","SIX_MP","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_MP");
   tolua_function(tolua_S,"new",tolua_SIX_Utility_SIX_MP_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Utility_SIX_MP_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Utility_SIX_MP_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Utility_SIX_MP_delete00);
   tolua_function(tolua_S,"size",tolua_SIX_Utility_SIX_MP_size00);
   tolua_function(tolua_S,"push_back",tolua_SIX_Utility_SIX_MP_push_back00);
   tolua_function(tolua_S,"pop_back",tolua_SIX_Utility_SIX_MP_pop_back00);
   tolua_function(tolua_S,"at",tolua_SIX_Utility_SIX_MP_at00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_Utility","SIX_Utility","TSingleton<SIX_Utility>",tolua_collect_SIX_Utility);
  #else
  tolua_cclass(tolua_S,"SIX_Utility","SIX_Utility","TSingleton<SIX_Utility>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_Utility");
   tolua_function(tolua_S,"new",tolua_SIX_Utility_SIX_Utility_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Utility_SIX_Utility_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Utility_SIX_Utility_new00_local);
   tolua_function(tolua_S,"GetInstance",tolua_SIX_Utility_SIX_Utility_GetInstance00);
   tolua_function(tolua_S,"REVE_DWORD",tolua_SIX_Utility_SIX_Utility_REVE_DWORD00);
   tolua_function(tolua_S,"GetCurrentThreadId",tolua_SIX_Utility_SIX_Utility_GetCurrentThreadId00);
   tolua_function(tolua_S,"RNDNUM",tolua_SIX_Utility_SIX_Utility_RNDNUM00);
   tolua_function(tolua_S,"code_convert",tolua_SIX_Utility_SIX_Utility_code_convert00);
   tolua_function(tolua_S,"U2G",tolua_SIX_Utility_SIX_Utility_U2G00);
   tolua_function(tolua_S,"G2U",tolua_SIX_Utility_SIX_Utility_G2U00);
   tolua_function(tolua_S,"Split",tolua_SIX_Utility_SIX_Utility_Split00);
   tolua_function(tolua_S,"Split",tolua_SIX_Utility_SIX_Utility_Split01);
   tolua_function(tolua_S,"GetTickCount",tolua_SIX_Utility_SIX_Utility_GetTickCount00);
   tolua_function(tolua_S,"GetLocalTime",tolua_SIX_Utility_SIX_Utility_GetLocalTime00);
   tolua_function(tolua_S,"TimerStart",tolua_SIX_Utility_SIX_Utility_TimerStart00);
   tolua_function(tolua_S,"TimerEnd",tolua_SIX_Utility_SIX_Utility_TimerEnd00);
   tolua_function(tolua_S,"GetMilliseconds",tolua_SIX_Utility_SIX_Utility_GetMilliseconds00);
   tolua_function(tolua_S,"GetGlobalSecond",tolua_SIX_Utility_SIX_Utility_GetGlobalSecond00);
   tolua_function(tolua_S,"Fixed",tolua_SIX_Utility_SIX_Utility_Fixed00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_Utility (lua_State* tolua_S) {
 return tolua_SIX_Utility_open(tolua_S);
};
#endif


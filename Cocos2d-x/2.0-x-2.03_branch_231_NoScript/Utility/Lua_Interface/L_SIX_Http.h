/*
** Lua binding: SIX_Http
** Generated automatically by tolua++-1.0.92 on 04/03/13 10:54:39.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_Http_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_HTTP (lua_State* tolua_S)
{
 SIX_HTTP* self = (SIX_HTTP*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_Http_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"SIX_HTTP");
}

/* method: new of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_new00
static int tolua_SIX_Http_SIX_HTTP_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_HTTP* tolua_ret = (SIX_HTTP*)  Mtolua_new((SIX_HTTP)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_HTTP");
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

/* method: new_local of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_new00_local
static int tolua_SIX_Http_SIX_HTTP_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_HTTP* tolua_ret = (SIX_HTTP*)  Mtolua_new((SIX_HTTP)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_HTTP");
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

/* method: delete of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_delete00
static int tolua_SIX_Http_SIX_HTTP_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_HTTP* self = (SIX_HTTP*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Get of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_Get00
static int tolua_SIX_Http_SIX_HTTP_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_HTTP* self = (SIX_HTTP*)  tolua_tousertype(tolua_S,1,0);
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'", NULL);
#endif
  {
   self->Get(url);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Post of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_Post00
static int tolua_SIX_Http_SIX_HTTP_Post00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_HTTP* self = (SIX_HTTP*)  tolua_tousertype(tolua_S,1,0);
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Post'", NULL);
#endif
  {
   self->Post(url,data,len);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Post'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onHttpRequestCompleted of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_onHttpRequestCompleted00
static int tolua_SIX_Http_SIX_HTTP_onHttpRequestCompleted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_HTTP* self = (SIX_HTTP*)  tolua_tousertype(tolua_S,1,0);
  CCNode* sender = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  void* data = ((void*)  tolua_touserdata(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onHttpRequestCompleted'", NULL);
#endif
  {
   self->onHttpRequestCompleted(sender,data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onHttpRequestCompleted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: executeCallback of class  SIX_HTTP */
#ifndef TOLUA_DISABLE_tolua_SIX_Http_SIX_HTTP_executeCallback00
static int tolua_SIX_Http_SIX_HTTP_executeCallback00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_HTTP",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_HTTP* self = (SIX_HTTP*)  tolua_tousertype(tolua_S,1,0);
  int responseCode = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* resp = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  const char* cbName = ((const char*)  tolua_tostring(tolua_S,5,"onSuccessed"));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeCallback'", NULL);
#endif
  {
   self->executeCallback(responseCode,resp,len,cbName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_Http_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_Http_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_HTTP","SIX_HTTP","CCObject",tolua_collect_SIX_HTTP);
  #else
  tolua_cclass(tolua_S,"SIX_HTTP","SIX_HTTP","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_HTTP");
   tolua_function(tolua_S,"new",tolua_SIX_Http_SIX_HTTP_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Http_SIX_HTTP_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Http_SIX_HTTP_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Http_SIX_HTTP_delete00);
   tolua_function(tolua_S,"Get",tolua_SIX_Http_SIX_HTTP_Get00);
   tolua_function(tolua_S,"Post",tolua_SIX_Http_SIX_HTTP_Post00);
   tolua_function(tolua_S,"onHttpRequestCompleted",tolua_SIX_Http_SIX_HTTP_onHttpRequestCompleted00);
   tolua_function(tolua_S,"executeCallback",tolua_SIX_Http_SIX_HTTP_executeCallback00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_Http (lua_State* tolua_S) {
 return tolua_SIX_Http_open(tolua_S);
};
#endif


/*
** Lua binding: CCTextFieldTTF
** Generated automatically by tolua++-1.0.92 on 04/25/13 14:40:49.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCTextFieldTTF_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ccColor3B (lua_State* tolua_S)
{
 ccColor3B* self = (ccColor3B*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCTextFieldTTF_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCTextFieldTTF");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"CCLabelTTF");
 tolua_usertype(tolua_S,"CCTextAlignment");
 tolua_usertype(tolua_S,"ccColor3B");
}

/* method: attachWithIME of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_attachWithIME00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_attachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detachWithIME of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_detachWithIME00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_detachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->detachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCharCount of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_getCharCount00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_getCharCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCharCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCharCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCharCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColorSpaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_setColorSpaceHolder00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_setColorSpaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
  ccColor3B val = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColorSpaceHolder'", NULL);
#endif
  {
   self->setColorSpaceHolder(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColorSpaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColorSpaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_getColorSpaceHolder00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_getColorSpaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColorSpaceHolder'", NULL);
#endif
  {
   ccColor3B tolua_ret = (ccColor3B)  self->getColorSpaceHolder();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor3B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccColor3B));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColorSpaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setString of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_setString00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_setString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setString'", NULL);
#endif
  {
   self->setString(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getString of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_getString00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_getString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getString'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_setPlaceHolder00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_setPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceHolder'", NULL);
#endif
  {
   self->setPlaceHolder(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_getPlaceHolder00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_getPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlaceHolder'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPlaceHolder();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAttachWithIME of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_IsAttachWithIME00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_IsAttachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAttachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAttachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAttachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: textFieldWithPlaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder00
static int tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCTextAlignment",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* placeholder = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCSize dimensions = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  CCTextAlignment alignment = *((CCTextAlignment*)  tolua_tousertype(tolua_S,4,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,5,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,6,0));
  {
   CCTextFieldTTF* tolua_ret = (CCTextFieldTTF*)  CCTextFieldTTF::textFieldWithPlaceHolder(placeholder,dimensions,alignment,fontName,fontSize);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextFieldTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'textFieldWithPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: textFieldWithPlaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder01
static int tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* placeholder = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCTextFieldTTF* tolua_ret = (CCTextFieldTTF*)  CCTextFieldTTF::textFieldWithPlaceHolder(placeholder,fontName,fontSize);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextFieldTTF");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCTextFieldTTF_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCTextFieldTTF_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCTextFieldTTF","CCTextFieldTTF","CCLabelTTF",NULL);
  tolua_beginmodule(tolua_S,"CCTextFieldTTF");
   tolua_function(tolua_S,"attachWithIME",tolua_CCTextFieldTTF_CCTextFieldTTF_attachWithIME00);
   tolua_function(tolua_S,"detachWithIME",tolua_CCTextFieldTTF_CCTextFieldTTF_detachWithIME00);
   tolua_function(tolua_S,"getCharCount",tolua_CCTextFieldTTF_CCTextFieldTTF_getCharCount00);
   tolua_function(tolua_S,"setColorSpaceHolder",tolua_CCTextFieldTTF_CCTextFieldTTF_setColorSpaceHolder00);
   tolua_function(tolua_S,"getColorSpaceHolder",tolua_CCTextFieldTTF_CCTextFieldTTF_getColorSpaceHolder00);
   tolua_function(tolua_S,"setString",tolua_CCTextFieldTTF_CCTextFieldTTF_setString00);
   tolua_function(tolua_S,"getString",tolua_CCTextFieldTTF_CCTextFieldTTF_getString00);
   tolua_function(tolua_S,"setPlaceHolder",tolua_CCTextFieldTTF_CCTextFieldTTF_setPlaceHolder00);
   tolua_function(tolua_S,"getPlaceHolder",tolua_CCTextFieldTTF_CCTextFieldTTF_getPlaceHolder00);
   tolua_function(tolua_S,"IsAttachWithIME",tolua_CCTextFieldTTF_CCTextFieldTTF_IsAttachWithIME00);
   tolua_function(tolua_S,"textFieldWithPlaceHolder",tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder00);
   tolua_function(tolua_S,"textFieldWithPlaceHolder",tolua_CCTextFieldTTF_CCTextFieldTTF_textFieldWithPlaceHolder01);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCTextFieldTTF (lua_State* tolua_S) {
 return tolua_CCTextFieldTTF_open(tolua_S);
};
#endif


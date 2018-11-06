/*
** Lua binding: CCScale9Sprite
** Generated automatically by tolua++-1.0.92 on 05/21/13 21:31:50.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCScale9Sprite_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCScale9Sprite (lua_State* tolua_S)
{
 CCScale9Sprite* self = (CCScale9Sprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCSize (lua_State* tolua_S)
{
 CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCScale9Sprite_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCSpriteBatchNode");
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCSpriteFrame");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCRGBAProtocol");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCNode");
}

/* method: new of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_new00
static int tolua_CCScale9Sprite_CCScale9Sprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  Mtolua_new((CCScale9Sprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
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

/* method: new_local of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_new00_local
static int tolua_CCScale9Sprite_CCScale9Sprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  Mtolua_new((CCScale9Sprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
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

/* method: delete of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_delete00
static int tolua_CCScale9Sprite_CCScale9Sprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_originalSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_originalSize
static int tolua_get_CCScale9Sprite_m_originalSize(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_originalSize'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_originalSize,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_originalSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_originalSize
static int tolua_set_CCScale9Sprite_m_originalSize(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_originalSize'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_originalSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOriginalSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getOriginalSize00
static int tolua_CCScale9Sprite_CCScale9Sprite_getOriginalSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCScale9Sprite* self = (const CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOriginalSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getOriginalSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOriginalSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_preferredSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_preferredSize
static int tolua_get_CCScale9Sprite_m_preferredSize(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_preferredSize'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_preferredSize,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_preferredSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_preferredSize
static int tolua_set_CCScale9Sprite_m_preferredSize(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_preferredSize'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_preferredSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPreferredSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getPreferredSize00
static int tolua_CCScale9Sprite_CCScale9Sprite_getPreferredSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPreferredSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getPreferredSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPreferredSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPreferredSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setPreferredSize00
static int tolua_CCScale9Sprite_CCScale9Sprite_setPreferredSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSize var = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPreferredSize'", NULL);
#endif
  {
   self->setPreferredSize(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPreferredSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_capInsets of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_capInsets
static int tolua_get_CCScale9Sprite_m_capInsets(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_capInsets'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_capInsets,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_capInsets of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_capInsets
static int tolua_set_CCScale9Sprite_m_capInsets(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_capInsets'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_capInsets = *((CCRect*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCapInsets of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getCapInsets00
static int tolua_CCScale9Sprite_CCScale9Sprite_getCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCapInsets'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getCapInsets();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setCapInsets00
static int tolua_CCScale9Sprite_CCScale9Sprite_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCRect var = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsets'", NULL);
#endif
  {
   self->setCapInsets(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_insetLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_insetLeft
static int tolua_get_CCScale9Sprite_m_insetLeft(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetLeft'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_insetLeft);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_insetLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_insetLeft
static int tolua_set_CCScale9Sprite_m_insetLeft(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetLeft'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_insetLeft = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInsetLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getInsetLeft00
static int tolua_CCScale9Sprite_CCScale9Sprite_getInsetLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInsetLeft'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getInsetLeft();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInsetLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setInsetLeft00
static int tolua_CCScale9Sprite_CCScale9Sprite_setInsetLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetLeft'", NULL);
#endif
  {
   self->setInsetLeft(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_insetTop of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_insetTop
static int tolua_get_CCScale9Sprite_m_insetTop(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetTop'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_insetTop);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_insetTop of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_insetTop
static int tolua_set_CCScale9Sprite_m_insetTop(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetTop'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_insetTop = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInsetTop of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getInsetTop00
static int tolua_CCScale9Sprite_CCScale9Sprite_getInsetTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInsetTop'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getInsetTop();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInsetTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetTop of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setInsetTop00
static int tolua_CCScale9Sprite_CCScale9Sprite_setInsetTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetTop'", NULL);
#endif
  {
   self->setInsetTop(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_insetRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_insetRight
static int tolua_get_CCScale9Sprite_m_insetRight(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetRight'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_insetRight);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_insetRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_insetRight
static int tolua_set_CCScale9Sprite_m_insetRight(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetRight'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_insetRight = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInsetRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getInsetRight00
static int tolua_CCScale9Sprite_CCScale9Sprite_getInsetRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInsetRight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getInsetRight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInsetRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setInsetRight00
static int tolua_CCScale9Sprite_CCScale9Sprite_setInsetRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetRight'", NULL);
#endif
  {
   self->setInsetRight(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_insetBottom of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_insetBottom
static int tolua_get_CCScale9Sprite_m_insetBottom(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetBottom'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_insetBottom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_insetBottom of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_insetBottom
static int tolua_set_CCScale9Sprite_m_insetBottom(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_insetBottom'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_insetBottom = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInsetBottom of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getInsetBottom00
static int tolua_CCScale9Sprite_CCScale9Sprite_getInsetBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInsetBottom'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getInsetBottom();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInsetBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetBottom of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setInsetBottom00
static int tolua_CCScale9Sprite_CCScale9Sprite_setInsetBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetBottom'", NULL);
#endif
  {
   self->setInsetBottom(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_cOpacity of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_unsigned_m_cOpacity
static int tolua_get_CCScale9Sprite_unsigned_m_cOpacity(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_cOpacity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_cOpacity);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_cOpacity of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_unsigned_m_cOpacity
static int tolua_set_CCScale9Sprite_unsigned_m_cOpacity(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_cOpacity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_cOpacity = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getOpacity00
static int tolua_CCScale9Sprite_CCScale9Sprite_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   unsigned char tolua_ret = ( unsigned char)  self->getOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setOpacity00
static int tolua_CCScale9Sprite_CCScale9Sprite_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  unsigned char var = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_tColor of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_tColor
static int tolua_get_CCScale9Sprite_m_tColor(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_tColor'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_tColor,"ccColor3B");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_tColor of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_tColor
static int tolua_set_CCScale9Sprite_m_tColor(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_tColor'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_tColor = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_getColor00
static int tolua_CCScale9Sprite_CCScale9Sprite_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setColor00
static int tolua_CCScale9Sprite_CCScale9Sprite_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* var = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scale9Image of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_scale9Image_ptr
static int tolua_get_CCScale9Sprite_scale9Image_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale9Image'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->scale9Image,"CCSpriteBatchNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scale9Image of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_scale9Image_ptr
static int tolua_set_CCScale9Sprite_scale9Image_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale9Image'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSpriteBatchNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scale9Image = ((CCSpriteBatchNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bSpritesGenerated of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_bSpritesGenerated
static int tolua_get_CCScale9Sprite_m_bSpritesGenerated(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bSpritesGenerated'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bSpritesGenerated);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bSpritesGenerated of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_bSpritesGenerated
static int tolua_set_CCScale9Sprite_m_bSpritesGenerated(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bSpritesGenerated'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bSpritesGenerated = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_spriteRect of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_spriteRect
static int tolua_get_CCScale9Sprite_m_spriteRect(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteRect'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_spriteRect,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_spriteRect of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_spriteRect
static int tolua_set_CCScale9Sprite_m_spriteRect(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteRect'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_spriteRect = *((CCRect*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bSpriteFrameRotated of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_bSpriteFrameRotated
static int tolua_get_CCScale9Sprite_m_bSpriteFrameRotated(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bSpriteFrameRotated'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bSpriteFrameRotated);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bSpriteFrameRotated of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_bSpriteFrameRotated
static int tolua_set_CCScale9Sprite_m_bSpriteFrameRotated(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bSpriteFrameRotated'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bSpriteFrameRotated = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_capInsetsInternal of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_capInsetsInternal
static int tolua_get_CCScale9Sprite_m_capInsetsInternal(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_capInsetsInternal'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_capInsetsInternal,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_capInsetsInternal of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_capInsetsInternal
static int tolua_set_CCScale9Sprite_m_capInsetsInternal(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_capInsetsInternal'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_capInsetsInternal = *((CCRect*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_positionsAreDirty of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_positionsAreDirty
static int tolua_get_CCScale9Sprite_m_positionsAreDirty(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_positionsAreDirty'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_positionsAreDirty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_positionsAreDirty of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_positionsAreDirty
static int tolua_set_CCScale9Sprite_m_positionsAreDirty(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_positionsAreDirty'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_positionsAreDirty = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: topLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_topLeft_ptr
static int tolua_get_CCScale9Sprite_topLeft_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'topLeft'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->topLeft,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: topLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_topLeft_ptr
static int tolua_set_CCScale9Sprite_topLeft_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'topLeft'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->topLeft = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: top of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_top_ptr
static int tolua_get_CCScale9Sprite_top_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->top,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: top of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_top_ptr
static int tolua_set_CCScale9Sprite_top_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->top = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: topRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_topRight_ptr
static int tolua_get_CCScale9Sprite_topRight_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'topRight'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->topRight,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: topRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_topRight_ptr
static int tolua_set_CCScale9Sprite_topRight_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'topRight'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->topRight = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: left of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_left_ptr
static int tolua_get_CCScale9Sprite_left_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->left,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: left of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_left_ptr
static int tolua_set_CCScale9Sprite_left_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->left = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: centre of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_centre_ptr
static int tolua_get_CCScale9Sprite_centre_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'centre'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->centre,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: centre of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_centre_ptr
static int tolua_set_CCScale9Sprite_centre_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'centre'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->centre = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: right of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_right_ptr
static int tolua_get_CCScale9Sprite_right_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->right,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: right of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_right_ptr
static int tolua_set_CCScale9Sprite_right_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->right = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bottomLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_bottomLeft_ptr
static int tolua_get_CCScale9Sprite_bottomLeft_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottomLeft'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->bottomLeft,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bottomLeft of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_bottomLeft_ptr
static int tolua_set_CCScale9Sprite_bottomLeft_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottomLeft'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bottomLeft = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bottom of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_bottom_ptr
static int tolua_get_CCScale9Sprite_bottom_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->bottom,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bottom of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_bottom_ptr
static int tolua_set_CCScale9Sprite_bottom_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bottom = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bottomRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_bottomRight_ptr
static int tolua_get_CCScale9Sprite_bottomRight_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottomRight'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->bottomRight,"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bottomRight of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_bottomRight_ptr
static int tolua_set_CCScale9Sprite_bottomRight_ptr(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottomRight'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bottomRight = ((CCSprite*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sColorUnmodified of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_sColorUnmodified
static int tolua_get_CCScale9Sprite_m_sColorUnmodified(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sColorUnmodified'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_sColorUnmodified,"ccColor3B");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sColorUnmodified of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_sColorUnmodified
static int tolua_set_CCScale9Sprite_m_sColorUnmodified(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sColorUnmodified'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sColorUnmodified = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bIsOpacityModifyRGB of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite_m_bIsOpacityModifyRGB
static int tolua_get_CCScale9Sprite_m_bIsOpacityModifyRGB(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bIsOpacityModifyRGB'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bIsOpacityModifyRGB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bIsOpacityModifyRGB of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_set_CCScale9Sprite_m_bIsOpacityModifyRGB
static int tolua_set_CCScale9Sprite_m_bIsOpacityModifyRGB(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bIsOpacityModifyRGB'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bIsOpacityModifyRGB = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateCapInset of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_updateCapInset00
static int tolua_CCScale9Sprite_CCScale9Sprite_updateCapInset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateCapInset'", NULL);
#endif
  {
   self->updateCapInset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateCapInset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updatePositions of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_updatePositions00
static int tolua_CCScale9Sprite_CCScale9Sprite_updatePositions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updatePositions'", NULL);
#endif
  {
   self->updatePositions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updatePositions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setContentSize00
static int tolua_CCScale9Sprite_CCScale9Sprite_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
  {
   self->setContentSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_visit00
static int tolua_CCScale9Sprite_CCScale9Sprite_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'visit'", NULL);
#endif
  {
   self->visit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'visit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_init00
static int tolua_CCScale9Sprite_CCScale9Sprite_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithBatchNode of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode00
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteBatchNode* batchnode = ((CCSpriteBatchNode*)  tolua_tousertype(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  bool rotated = ((bool)  tolua_toboolean(tolua_S,4,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithBatchNode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithBatchNode(batchnode,rect,rotated,capInsets);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithBatchNode of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode01
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteBatchNode* batchnode = ((CCSpriteBatchNode*)  tolua_tousertype(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithBatchNode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithBatchNode(batchnode,rect,capInsets);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithFile00
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(file,rect,capInsets);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile00
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,4,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithFile(file,rect,capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'spriteWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_create00
static int tolua_CCScale9Sprite_CCScale9Sprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,4,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create(file,rect,capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithFile01
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithFile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(file,rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_initWithFile00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile01
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithFile(file,rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_create01
static int tolua_CCScale9Sprite_CCScale9Sprite_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create(file,rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithFile02
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithFile02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(capInsets,file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_initWithFile01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile02
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithFile(capInsets,file);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_create02
static int tolua_CCScale9Sprite_CCScale9Sprite_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create(capInsets,file);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithFile03
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithFile03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_initWithFile02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithFile of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile03
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithFile(file);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_create03
static int tolua_CCScale9Sprite_CCScale9Sprite_create03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create(file);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_create02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame00
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSpriteFrame'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSpriteFrame(spriteFrame,capInsets);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame00
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithSpriteFrame(spriteFrame,capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'spriteWithSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame00
static int tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::createWithSpriteFrame(spriteFrame,capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame01
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSpriteFrame'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSpriteFrame(spriteFrame);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame01
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithSpriteFrame(spriteFrame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame01
static int tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::createWithSpriteFrame(spriteFrame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName00
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSpriteFrameName'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSpriteFrameName(spriteFrameName,capInsets);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName00
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithSpriteFrameName(spriteFrameName,capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'spriteWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName00
static int tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::createWithSpriteFrameName(spriteFrameName,capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName01
static int tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSpriteFrameName'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSpriteFrameName(spriteFrameName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: spriteWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName01
static int tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::spriteWithSpriteFrameName(spriteFrameName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName01
static int tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::createWithSpriteFrameName(spriteFrameName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: resizableSpriteWithCapInsets of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_resizableSpriteWithCapInsets00
static int tolua_CCScale9Sprite_CCScale9Sprite_resizableSpriteWithCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resizableSpriteWithCapInsets'", NULL);
#endif
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  self->resizableSpriteWithCapInsets(capInsets);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resizableSpriteWithCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: node of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_node00
static int tolua_CCScale9Sprite_CCScale9Sprite_node00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::node();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'node'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_create04
static int tolua_CCScale9Sprite_CCScale9Sprite_create04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScale9Sprite_CCScale9Sprite_create03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacityModifyRGB of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setOpacityModifyRGB00
static int tolua_CCScale9Sprite_CCScale9Sprite_setOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  bool bValue = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacityModifyRGB'", NULL);
#endif
  {
   self->setOpacityModifyRGB(bValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpacityModifyRGB of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_isOpacityModifyRGB00
static int tolua_CCScale9Sprite_CCScale9Sprite_isOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpacityModifyRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpacityModifyRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateWithBatchNode of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_updateWithBatchNode00
static int tolua_CCScale9Sprite_CCScale9Sprite_updateWithBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteBatchNode* batchnode = ((CCSpriteBatchNode*)  tolua_tousertype(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  bool rotated = ((bool)  tolua_toboolean(tolua_S,4,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateWithBatchNode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->updateWithBatchNode(batchnode,rect,rotated,capInsets);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateWithBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_CCScale9Sprite_CCScale9Sprite_setSpriteFrame00
static int tolua_CCScale9Sprite_CCScale9Sprite_setSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpriteFrame'", NULL);
#endif
  {
   self->setSpriteFrame(spriteFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCRGBAProtocol__ of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_get_CCScale9Sprite___CCRGBAProtocol__
static int tolua_get_CCScale9Sprite___CCRGBAProtocol__(lua_State* tolua_S)
{
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCRGBAProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCRGBAProtocol*>(self), "CCRGBAProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCRGBAProtocol*)self), "CCRGBAProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCScale9Sprite_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCScale9Sprite_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCScale9Sprite","CCScale9Sprite","CCNode",tolua_collect_CCScale9Sprite);
  #else
  tolua_cclass(tolua_S,"CCScale9Sprite","CCScale9Sprite","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCScale9Sprite");
   tolua_function(tolua_S,"new",tolua_CCScale9Sprite_CCScale9Sprite_new00);
   tolua_function(tolua_S,"new_local",tolua_CCScale9Sprite_CCScale9Sprite_new00_local);
   tolua_function(tolua_S,".call",tolua_CCScale9Sprite_CCScale9Sprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCScale9Sprite_CCScale9Sprite_delete00);
   tolua_variable(tolua_S,"m_originalSize",tolua_get_CCScale9Sprite_m_originalSize,tolua_set_CCScale9Sprite_m_originalSize);
   tolua_function(tolua_S,"getOriginalSize",tolua_CCScale9Sprite_CCScale9Sprite_getOriginalSize00);
   tolua_variable(tolua_S,"m_preferredSize",tolua_get_CCScale9Sprite_m_preferredSize,tolua_set_CCScale9Sprite_m_preferredSize);
   tolua_function(tolua_S,"getPreferredSize",tolua_CCScale9Sprite_CCScale9Sprite_getPreferredSize00);
   tolua_function(tolua_S,"setPreferredSize",tolua_CCScale9Sprite_CCScale9Sprite_setPreferredSize00);
   tolua_variable(tolua_S,"m_capInsets",tolua_get_CCScale9Sprite_m_capInsets,tolua_set_CCScale9Sprite_m_capInsets);
   tolua_function(tolua_S,"getCapInsets",tolua_CCScale9Sprite_CCScale9Sprite_getCapInsets00);
   tolua_function(tolua_S,"setCapInsets",tolua_CCScale9Sprite_CCScale9Sprite_setCapInsets00);
   tolua_variable(tolua_S,"m_insetLeft",tolua_get_CCScale9Sprite_m_insetLeft,tolua_set_CCScale9Sprite_m_insetLeft);
   tolua_function(tolua_S,"getInsetLeft",tolua_CCScale9Sprite_CCScale9Sprite_getInsetLeft00);
   tolua_function(tolua_S,"setInsetLeft",tolua_CCScale9Sprite_CCScale9Sprite_setInsetLeft00);
   tolua_variable(tolua_S,"m_insetTop",tolua_get_CCScale9Sprite_m_insetTop,tolua_set_CCScale9Sprite_m_insetTop);
   tolua_function(tolua_S,"getInsetTop",tolua_CCScale9Sprite_CCScale9Sprite_getInsetTop00);
   tolua_function(tolua_S,"setInsetTop",tolua_CCScale9Sprite_CCScale9Sprite_setInsetTop00);
   tolua_variable(tolua_S,"m_insetRight",tolua_get_CCScale9Sprite_m_insetRight,tolua_set_CCScale9Sprite_m_insetRight);
   tolua_function(tolua_S,"getInsetRight",tolua_CCScale9Sprite_CCScale9Sprite_getInsetRight00);
   tolua_function(tolua_S,"setInsetRight",tolua_CCScale9Sprite_CCScale9Sprite_setInsetRight00);
   tolua_variable(tolua_S,"m_insetBottom",tolua_get_CCScale9Sprite_m_insetBottom,tolua_set_CCScale9Sprite_m_insetBottom);
   tolua_function(tolua_S,"getInsetBottom",tolua_CCScale9Sprite_CCScale9Sprite_getInsetBottom00);
   tolua_function(tolua_S,"setInsetBottom",tolua_CCScale9Sprite_CCScale9Sprite_setInsetBottom00);
   tolua_variable(tolua_S,"m_cOpacity",tolua_get_CCScale9Sprite_unsigned_m_cOpacity,tolua_set_CCScale9Sprite_unsigned_m_cOpacity);
   tolua_function(tolua_S,"getOpacity",tolua_CCScale9Sprite_CCScale9Sprite_getOpacity00);
   tolua_function(tolua_S,"setOpacity",tolua_CCScale9Sprite_CCScale9Sprite_setOpacity00);
   tolua_variable(tolua_S,"m_tColor",tolua_get_CCScale9Sprite_m_tColor,tolua_set_CCScale9Sprite_m_tColor);
   tolua_function(tolua_S,"getColor",tolua_CCScale9Sprite_CCScale9Sprite_getColor00);
   tolua_function(tolua_S,"setColor",tolua_CCScale9Sprite_CCScale9Sprite_setColor00);
   tolua_variable(tolua_S,"scale9Image",tolua_get_CCScale9Sprite_scale9Image_ptr,tolua_set_CCScale9Sprite_scale9Image_ptr);
   tolua_variable(tolua_S,"m_bSpritesGenerated",tolua_get_CCScale9Sprite_m_bSpritesGenerated,tolua_set_CCScale9Sprite_m_bSpritesGenerated);
   tolua_variable(tolua_S,"m_spriteRect",tolua_get_CCScale9Sprite_m_spriteRect,tolua_set_CCScale9Sprite_m_spriteRect);
   tolua_variable(tolua_S,"m_bSpriteFrameRotated",tolua_get_CCScale9Sprite_m_bSpriteFrameRotated,tolua_set_CCScale9Sprite_m_bSpriteFrameRotated);
   tolua_variable(tolua_S,"m_capInsetsInternal",tolua_get_CCScale9Sprite_m_capInsetsInternal,tolua_set_CCScale9Sprite_m_capInsetsInternal);
   tolua_variable(tolua_S,"m_positionsAreDirty",tolua_get_CCScale9Sprite_m_positionsAreDirty,tolua_set_CCScale9Sprite_m_positionsAreDirty);
   tolua_variable(tolua_S,"topLeft",tolua_get_CCScale9Sprite_topLeft_ptr,tolua_set_CCScale9Sprite_topLeft_ptr);
   tolua_variable(tolua_S,"top",tolua_get_CCScale9Sprite_top_ptr,tolua_set_CCScale9Sprite_top_ptr);
   tolua_variable(tolua_S,"topRight",tolua_get_CCScale9Sprite_topRight_ptr,tolua_set_CCScale9Sprite_topRight_ptr);
   tolua_variable(tolua_S,"left",tolua_get_CCScale9Sprite_left_ptr,tolua_set_CCScale9Sprite_left_ptr);
   tolua_variable(tolua_S,"centre",tolua_get_CCScale9Sprite_centre_ptr,tolua_set_CCScale9Sprite_centre_ptr);
   tolua_variable(tolua_S,"right",tolua_get_CCScale9Sprite_right_ptr,tolua_set_CCScale9Sprite_right_ptr);
   tolua_variable(tolua_S,"bottomLeft",tolua_get_CCScale9Sprite_bottomLeft_ptr,tolua_set_CCScale9Sprite_bottomLeft_ptr);
   tolua_variable(tolua_S,"bottom",tolua_get_CCScale9Sprite_bottom_ptr,tolua_set_CCScale9Sprite_bottom_ptr);
   tolua_variable(tolua_S,"bottomRight",tolua_get_CCScale9Sprite_bottomRight_ptr,tolua_set_CCScale9Sprite_bottomRight_ptr);
   tolua_variable(tolua_S,"m_sColorUnmodified",tolua_get_CCScale9Sprite_m_sColorUnmodified,tolua_set_CCScale9Sprite_m_sColorUnmodified);
   tolua_variable(tolua_S,"m_bIsOpacityModifyRGB",tolua_get_CCScale9Sprite_m_bIsOpacityModifyRGB,tolua_set_CCScale9Sprite_m_bIsOpacityModifyRGB);
   tolua_function(tolua_S,"updateCapInset",tolua_CCScale9Sprite_CCScale9Sprite_updateCapInset00);
   tolua_function(tolua_S,"updatePositions",tolua_CCScale9Sprite_CCScale9Sprite_updatePositions00);
   tolua_function(tolua_S,"setContentSize",tolua_CCScale9Sprite_CCScale9Sprite_setContentSize00);
   tolua_function(tolua_S,"visit",tolua_CCScale9Sprite_CCScale9Sprite_visit00);
   tolua_function(tolua_S,"init",tolua_CCScale9Sprite_CCScale9Sprite_init00);
   tolua_function(tolua_S,"initWithBatchNode",tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode00);
   tolua_function(tolua_S,"initWithBatchNode",tolua_CCScale9Sprite_CCScale9Sprite_initWithBatchNode01);
   tolua_function(tolua_S,"initWithFile",tolua_CCScale9Sprite_CCScale9Sprite_initWithFile00);
   tolua_function(tolua_S,"spriteWithFile",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile00);
   tolua_function(tolua_S,"create",tolua_CCScale9Sprite_CCScale9Sprite_create00);
   tolua_function(tolua_S,"initWithFile",tolua_CCScale9Sprite_CCScale9Sprite_initWithFile01);
   tolua_function(tolua_S,"spriteWithFile",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile01);
   tolua_function(tolua_S,"create",tolua_CCScale9Sprite_CCScale9Sprite_create01);
   tolua_function(tolua_S,"initWithFile",tolua_CCScale9Sprite_CCScale9Sprite_initWithFile02);
   tolua_function(tolua_S,"spriteWithFile",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile02);
   tolua_function(tolua_S,"create",tolua_CCScale9Sprite_CCScale9Sprite_create02);
   tolua_function(tolua_S,"initWithFile",tolua_CCScale9Sprite_CCScale9Sprite_initWithFile03);
   tolua_function(tolua_S,"spriteWithFile",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithFile03);
   tolua_function(tolua_S,"create",tolua_CCScale9Sprite_CCScale9Sprite_create03);
   tolua_function(tolua_S,"initWithSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame00);
   tolua_function(tolua_S,"spriteWithSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame00);
   tolua_function(tolua_S,"initWithSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrame01);
   tolua_function(tolua_S,"spriteWithSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrame01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrame01);
   tolua_function(tolua_S,"initWithSpriteFrameName",tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName00);
   tolua_function(tolua_S,"spriteWithSpriteFrameName",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName00);
   tolua_function(tolua_S,"initWithSpriteFrameName",tolua_CCScale9Sprite_CCScale9Sprite_initWithSpriteFrameName01);
   tolua_function(tolua_S,"spriteWithSpriteFrameName",tolua_CCScale9Sprite_CCScale9Sprite_spriteWithSpriteFrameName01);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_CCScale9Sprite_CCScale9Sprite_createWithSpriteFrameName01);
   tolua_function(tolua_S,"resizableSpriteWithCapInsets",tolua_CCScale9Sprite_CCScale9Sprite_resizableSpriteWithCapInsets00);
   tolua_function(tolua_S,"node",tolua_CCScale9Sprite_CCScale9Sprite_node00);
   tolua_function(tolua_S,"create",tolua_CCScale9Sprite_CCScale9Sprite_create04);
   tolua_function(tolua_S,"setOpacityModifyRGB",tolua_CCScale9Sprite_CCScale9Sprite_setOpacityModifyRGB00);
   tolua_function(tolua_S,"isOpacityModifyRGB",tolua_CCScale9Sprite_CCScale9Sprite_isOpacityModifyRGB00);
   tolua_function(tolua_S,"updateWithBatchNode",tolua_CCScale9Sprite_CCScale9Sprite_updateWithBatchNode00);
   tolua_function(tolua_S,"setSpriteFrame",tolua_CCScale9Sprite_CCScale9Sprite_setSpriteFrame00);
   tolua_variable(tolua_S,"__CCRGBAProtocol__",tolua_get_CCScale9Sprite___CCRGBAProtocol__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCScale9Sprite (lua_State* tolua_S) {
 return tolua_CCScale9Sprite_open(tolua_S);
};
#endif


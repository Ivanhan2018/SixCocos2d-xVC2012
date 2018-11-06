/*
** Lua binding: CCControlSlider
** Generated automatically by tolua++-1.0.92 on 04/28/13 13:04:06.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCControlSlider_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CCPoint (lua_State* tolua_S)
//{
// CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_CCControlSlider (lua_State* tolua_S)
{
 CCControlSlider* self = (CCControlSlider*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCControlSlider_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCControlSlider");
}

/* method: getValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getValue00
static int tolua_CCControlSlider_CCControlSlider_getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setValue00
static int tolua_CCControlSlider_CCControlSlider_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMinimumValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getMinimumValue00
static int tolua_CCControlSlider_CCControlSlider_getMinimumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinimumValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMinimumValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinimumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMinimumValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setMinimumValue00
static int tolua_CCControlSlider_CCControlSlider_setMinimumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinimumValue'", NULL);
#endif
  {
   self->setMinimumValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMinimumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaximumValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getMaximumValue00
static int tolua_CCControlSlider_CCControlSlider_getMaximumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaximumValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMaximumValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaximumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaximumValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setMaximumValue00
static int tolua_CCControlSlider_CCControlSlider_setMaximumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaximumValue'", NULL);
#endif
  {
   self->setMaximumValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaximumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setEnabled00
static int tolua_CCControlSlider_CCControlSlider_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchInside of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_isTouchInside00
static int tolua_CCControlSlider_CCControlSlider_isTouchInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchInside(touch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchInside'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: locationFromTouch of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_locationFromTouch00
static int tolua_CCControlSlider_CCControlSlider_locationFromTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'locationFromTouch'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->locationFromTouch(touch);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'locationFromTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMinimumAllowedValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getMinimumAllowedValue00
static int tolua_CCControlSlider_CCControlSlider_getMinimumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinimumAllowedValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMinimumAllowedValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinimumAllowedValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMinimumAllowedValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setMinimumAllowedValue00
static int tolua_CCControlSlider_CCControlSlider_setMinimumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinimumAllowedValue'", NULL);
#endif
  {
   self->setMinimumAllowedValue(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMinimumAllowedValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaximumAllowedValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getMaximumAllowedValue00
static int tolua_CCControlSlider_CCControlSlider_getMaximumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaximumAllowedValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMaximumAllowedValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaximumAllowedValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaximumAllowedValue of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setMaximumAllowedValue00
static int tolua_CCControlSlider_CCControlSlider_setMaximumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaximumAllowedValue'", NULL);
#endif
  {
   self->setMaximumAllowedValue(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaximumAllowedValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getThumbSprite of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getThumbSprite00
static int tolua_CCControlSlider_CCControlSlider_getThumbSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getThumbSprite'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getThumbSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getThumbSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setThumbSprite of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setThumbSprite00
static int tolua_CCControlSlider_CCControlSlider_setThumbSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* var = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setThumbSprite'", NULL);
#endif
  {
   self->setThumbSprite(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setThumbSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getProgressSprite of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getProgressSprite00
static int tolua_CCControlSlider_CCControlSlider_getProgressSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getProgressSprite'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getProgressSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getProgressSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setProgressSprite of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setProgressSprite00
static int tolua_CCControlSlider_CCControlSlider_setProgressSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* var = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProgressSprite'", NULL);
#endif
  {
   self->setProgressSprite(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProgressSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundSprite of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_getBackgroundSprite00
static int tolua_CCControlSlider_CCControlSlider_getBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlSlider* self = (const CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundSprite'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getBackgroundSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundSprite of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_setBackgroundSprite00
static int tolua_CCControlSlider_CCControlSlider_setBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* var = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundSprite'", NULL);
#endif
  {
   self->setBackgroundSprite(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_new00
static int tolua_CCControlSlider_CCControlSlider_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControlSlider* tolua_ret = (CCControlSlider*)  Mtolua_new((CCControlSlider)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlSlider");
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

/* method: new_local of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_new00_local
static int tolua_CCControlSlider_CCControlSlider_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControlSlider* tolua_ret = (CCControlSlider*)  Mtolua_new((CCControlSlider)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlSlider");
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

/* method: delete of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_delete00
static int tolua_CCControlSlider_CCControlSlider_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: initWithSprites of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_initWithSprites00
static int tolua_CCControlSlider_CCControlSlider_initWithSprites00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* backgroundSprite = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCSprite* progressSprite = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
  CCSprite* thumbSprite = ((CCSprite*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSprites'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSprites(backgroundSprite,progressSprite,thumbSprite);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithSprites'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sliderWithFiles of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_sliderWithFiles00
static int tolua_CCControlSlider_CCControlSlider_sliderWithFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* bgFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* progressFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* thumbFile = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   CCControlSlider* tolua_ret = (CCControlSlider*)  CCControlSlider::sliderWithFiles(bgFile,progressFile,thumbFile);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlSlider");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sliderWithFiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sliderWithSprites of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_sliderWithSprites00
static int tolua_CCControlSlider_CCControlSlider_sliderWithSprites00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSprite* backgroundSprite = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCSprite* pogressSprite = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
  CCSprite* thumbSprite = ((CCSprite*)  tolua_tousertype(tolua_S,4,0));
  {
   CCControlSlider* tolua_ret = (CCControlSlider*)  CCControlSlider::sliderWithSprites(backgroundSprite,pogressSprite,thumbSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlSlider");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sliderWithSprites'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_create00
static int tolua_CCControlSlider_CCControlSlider_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* bgFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* progressFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* thumbFile = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   CCControlSlider* tolua_ret = (CCControlSlider*)  CCControlSlider::create(bgFile,progressFile,thumbFile);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlSlider");
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

/* method: create of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_create01
static int tolua_CCControlSlider_CCControlSlider_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCSprite* backgroundSprite = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCSprite* pogressSprite = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
  CCSprite* thumbSprite = ((CCSprite*)  tolua_tousertype(tolua_S,4,0));
  {
   CCControlSlider* tolua_ret = (CCControlSlider*)  CCControlSlider::create(backgroundSprite,pogressSprite,thumbSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlSlider");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCControlSlider_CCControlSlider_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: needsLayout of class  CCControlSlider */
#ifndef TOLUA_DISABLE_tolua_CCControlSlider_CCControlSlider_needsLayout00
static int tolua_CCControlSlider_CCControlSlider_needsLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlSlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlSlider* self = (CCControlSlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'needsLayout'", NULL);
#endif
  {
   self->needsLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'needsLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCControlSlider_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCControlSlider_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCControlSlider","CCControlSlider","CCControl",tolua_collect_CCControlSlider);
  #else
  tolua_cclass(tolua_S,"CCControlSlider","CCControlSlider","CCControl",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCControlSlider");
   tolua_function(tolua_S,"getValue",tolua_CCControlSlider_CCControlSlider_getValue00);
   tolua_function(tolua_S,"setValue",tolua_CCControlSlider_CCControlSlider_setValue00);
   tolua_function(tolua_S,"getMinimumValue",tolua_CCControlSlider_CCControlSlider_getMinimumValue00);
   tolua_function(tolua_S,"setMinimumValue",tolua_CCControlSlider_CCControlSlider_setMinimumValue00);
   tolua_function(tolua_S,"getMaximumValue",tolua_CCControlSlider_CCControlSlider_getMaximumValue00);
   tolua_function(tolua_S,"setMaximumValue",tolua_CCControlSlider_CCControlSlider_setMaximumValue00);
   tolua_function(tolua_S,"setEnabled",tolua_CCControlSlider_CCControlSlider_setEnabled00);
   tolua_function(tolua_S,"isTouchInside",tolua_CCControlSlider_CCControlSlider_isTouchInside00);
   tolua_function(tolua_S,"locationFromTouch",tolua_CCControlSlider_CCControlSlider_locationFromTouch00);
   tolua_function(tolua_S,"getMinimumAllowedValue",tolua_CCControlSlider_CCControlSlider_getMinimumAllowedValue00);
   tolua_function(tolua_S,"setMinimumAllowedValue",tolua_CCControlSlider_CCControlSlider_setMinimumAllowedValue00);
   tolua_function(tolua_S,"getMaximumAllowedValue",tolua_CCControlSlider_CCControlSlider_getMaximumAllowedValue00);
   tolua_function(tolua_S,"setMaximumAllowedValue",tolua_CCControlSlider_CCControlSlider_setMaximumAllowedValue00);
   tolua_function(tolua_S,"getThumbSprite",tolua_CCControlSlider_CCControlSlider_getThumbSprite00);
   tolua_function(tolua_S,"setThumbSprite",tolua_CCControlSlider_CCControlSlider_setThumbSprite00);
   tolua_function(tolua_S,"getProgressSprite",tolua_CCControlSlider_CCControlSlider_getProgressSprite00);
   tolua_function(tolua_S,"setProgressSprite",tolua_CCControlSlider_CCControlSlider_setProgressSprite00);
   tolua_function(tolua_S,"getBackgroundSprite",tolua_CCControlSlider_CCControlSlider_getBackgroundSprite00);
   tolua_function(tolua_S,"setBackgroundSprite",tolua_CCControlSlider_CCControlSlider_setBackgroundSprite00);
   tolua_function(tolua_S,"new",tolua_CCControlSlider_CCControlSlider_new00);
   tolua_function(tolua_S,"new_local",tolua_CCControlSlider_CCControlSlider_new00_local);
   tolua_function(tolua_S,".call",tolua_CCControlSlider_CCControlSlider_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCControlSlider_CCControlSlider_delete00);
   tolua_function(tolua_S,"initWithSprites",tolua_CCControlSlider_CCControlSlider_initWithSprites00);
   tolua_function(tolua_S,"sliderWithFiles",tolua_CCControlSlider_CCControlSlider_sliderWithFiles00);
   tolua_function(tolua_S,"sliderWithSprites",tolua_CCControlSlider_CCControlSlider_sliderWithSprites00);
   tolua_function(tolua_S,"create",tolua_CCControlSlider_CCControlSlider_create00);
   tolua_function(tolua_S,"create",tolua_CCControlSlider_CCControlSlider_create01);
   tolua_function(tolua_S,"needsLayout",tolua_CCControlSlider_CCControlSlider_needsLayout00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCControlSlider (lua_State* tolua_S) {
 return tolua_CCControlSlider_open(tolua_S);
};
#endif


/*
** Lua binding: CCControl
** Generated automatically by tolua++-1.0.92 on 04/08/13 00:39:05.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCControl_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CCPoint (lua_State* tolua_S)
//{
// CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

//static int tolua_collect_GLubyte (lua_State* tolua_S)
//{
// GLubyte* self = (GLubyte*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_CCControl (lua_State* tolua_S)
{
 CCControl* self = (CCControl*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCControl_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"GLubyte");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"SEL_CCControlHandler");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCInvocation");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCRGBAProtocol");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCArray");
}

/* get function: m_cOpacity of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_cOpacity
static int tolua_get_CCControl_m_cOpacity(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_cOpacity'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_cOpacity,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_cOpacity of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_cOpacity
static int tolua_set_CCControl_m_cOpacity(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_cOpacity'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_cOpacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_getOpacity00
static int tolua_CCControl_CCControl_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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

/* method: setOpacity of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setOpacity00
static int tolua_CCControl_CCControl_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  GLubyte var = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
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

/* get function: m_tColor of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_tColor
static int tolua_get_CCControl_m_tColor(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_tColor'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_tColor,"ccColor3B");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_tColor of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_tColor
static int tolua_set_CCControl_m_tColor(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getColor of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_getColor00
static int tolua_CCControl_CCControl_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setColor of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setColor00
static int tolua_CCControl_CCControl_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_bIsOpacityModifyRGB of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_bIsOpacityModifyRGB
static int tolua_get_CCControl_m_bIsOpacityModifyRGB(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bIsOpacityModifyRGB'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bIsOpacityModifyRGB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bIsOpacityModifyRGB of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_bIsOpacityModifyRGB
static int tolua_set_CCControl_m_bIsOpacityModifyRGB(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isOpacityModifyRGB of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_isOpacityModifyRGB00
static int tolua_CCControl_CCControl_isOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setOpacityModifyRGB of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setOpacityModifyRGB00
static int tolua_CCControl_CCControl_setOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bOpacityModifyRGB = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacityModifyRGB'", NULL);
#endif
  {
   self->setOpacityModifyRGB(bOpacityModifyRGB);
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

/* get function: m_nDefaultTouchPriority of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_nDefaultTouchPriority
static int tolua_get_CCControl_m_nDefaultTouchPriority(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nDefaultTouchPriority'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_nDefaultTouchPriority);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nDefaultTouchPriority of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_nDefaultTouchPriority
static int tolua_set_CCControl_m_nDefaultTouchPriority(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nDefaultTouchPriority'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nDefaultTouchPriority = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefaultTouchPriority of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_getDefaultTouchPriority00
static int tolua_CCControl_CCControl_getDefaultTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControl* self = (const CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDefaultTouchPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDefaultTouchPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefaultTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultTouchPriority of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setDefaultTouchPriority00
static int tolua_CCControl_CCControl_setDefaultTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  int var = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultTouchPriority'", NULL);
#endif
  {
   self->setDefaultTouchPriority(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_eState of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_unsigned_m_eState
static int tolua_get_CCControl_unsigned_m_eState(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_eState'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_eState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_eState of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_unsigned_m_eState
static int tolua_set_CCControl_unsigned_m_eState(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_eState'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_eState = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getState of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_getState00
static int tolua_CCControl_CCControl_getState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControl* self = (const CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->getState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_hasVisibleParents of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_hasVisibleParents
static int tolua_get_CCControl_m_hasVisibleParents(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_hasVisibleParents'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_hasVisibleParents);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_hasVisibleParents of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_hasVisibleParents
static int tolua_set_CCControl_m_hasVisibleParents(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_hasVisibleParents'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_hasVisibleParents = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setEnabled00
static int tolua_CCControl_CCControl_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(bEnabled);
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

/* method: isEnabled of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_isEnabled00
static int tolua_CCControl_CCControl_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSelected of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setSelected00
static int tolua_CCControl_CCControl_setSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bSelected = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSelected'", NULL);
#endif
  {
   self->setSelected(bSelected);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isSelected of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_isSelected00
static int tolua_CCControl_CCControl_isSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSelected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isSelected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHighlighted of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_setHighlighted00
static int tolua_CCControl_CCControl_setHighlighted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bHighlighted = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHighlighted'", NULL);
#endif
  {
   self->setHighlighted(bHighlighted);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHighlighted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isHighlighted of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_isHighlighted00
static int tolua_CCControl_CCControl_isHighlighted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isHighlighted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isHighlighted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isHighlighted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasVisibleParents of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_hasVisibleParents00
static int tolua_CCControl_CCControl_hasVisibleParents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasVisibleParents'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasVisibleParents();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasVisibleParents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: needsLayout of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_needsLayout00
static int tolua_CCControl_CCControl_needsLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_bEnabled of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_bEnabled
static int tolua_get_CCControl_m_bEnabled(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bEnabled);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bEnabled of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_bEnabled
static int tolua_set_CCControl_m_bEnabled(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bEnabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bEnabled = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bSelected of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_bSelected
static int tolua_get_CCControl_m_bSelected(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bSelected'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bSelected);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bSelected of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_bSelected
static int tolua_set_CCControl_m_bSelected(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bSelected'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bSelected = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bHighlighted of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_bHighlighted
static int tolua_get_CCControl_m_bHighlighted(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bHighlighted'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bHighlighted);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bHighlighted of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_bHighlighted
static int tolua_set_CCControl_m_bHighlighted(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bHighlighted'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bHighlighted = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pDispatchTable of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl_m_pDispatchTable_ptr
static int tolua_get_CCControl_m_pDispatchTable_ptr(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pDispatchTable'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pDispatchTable,"CCDictionary");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pDispatchTable of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_set_CCControl_m_pDispatchTable_ptr
static int tolua_set_CCControl_m_pDispatchTable_ptr(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pDispatchTable'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pDispatchTable = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_new00
static int tolua_CCControl_CCControl_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControl* tolua_ret = (CCControl*)  Mtolua_new((CCControl)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControl");
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

/* method: new_local of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_new00_local
static int tolua_CCControl_CCControl_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControl* tolua_ret = (CCControl*)  Mtolua_new((CCControl)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControl");
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

/* method: init of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_init00
static int tolua_CCControl_CCControl_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: delete of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_delete00
static int tolua_CCControl_CCControl_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onEnter of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_onEnter00
static int tolua_CCControl_CCControl_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnter'", NULL);
#endif
  {
   self->onEnter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onExit of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_onExit00
static int tolua_CCControl_CCControl_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onExit'", NULL);
#endif
  {
   self->onExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_registerWithTouchDispatcher00
static int tolua_CCControl_CCControl_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendActionsForControlEvents of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_sendActionsForControlEvents00
static int tolua_CCControl_CCControl_sendActionsForControlEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  unsigned int controlEvents = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendActionsForControlEvents'", NULL);
#endif
  {
   self->sendActionsForControlEvents(controlEvents);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendActionsForControlEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTargetWithActionForControlEvents of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_addTargetWithActionForControlEvents00
static int tolua_CCControl_CCControl_addTargetWithActionForControlEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  unsigned int controlEvents = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTargetWithActionForControlEvents'", NULL);
#endif
  {
   self->addTargetWithActionForControlEvents(target,action,controlEvents);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTargetWithActionForControlEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTargetWithActionForControlEvents of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_removeTargetWithActionForControlEvents00
static int tolua_CCControl_CCControl_removeTargetWithActionForControlEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  unsigned int controlEvents = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTargetWithActionForControlEvents'", NULL);
#endif
  {
   self->removeTargetWithActionForControlEvents(target,action,controlEvents);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTargetWithActionForControlEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchLocation of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_getTouchLocation00
static int tolua_CCControl_CCControl_getTouchLocation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchLocation'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getTouchLocation(touch);
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
 tolua_error(tolua_S,"#ferror in function 'getTouchLocation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchInside of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_isTouchInside00
static int tolua_CCControl_CCControl_isTouchInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: invocationWithTargetAndActionForControlEvent of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_invocationWithTargetAndActionForControlEvent00
static int tolua_CCControl_CCControl_invocationWithTargetAndActionForControlEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  unsigned int controlEvent = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'invocationWithTargetAndActionForControlEvent'", NULL);
#endif
  {
   CCInvocation* tolua_ret = (CCInvocation*)  self->invocationWithTargetAndActionForControlEvent(target,action,controlEvent);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCInvocation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'invocationWithTargetAndActionForControlEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispatchListforControlEvent of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_dispatchListforControlEvent00
static int tolua_CCControl_CCControl_dispatchListforControlEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  unsigned int controlEvent = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispatchListforControlEvent'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->dispatchListforControlEvent(controlEvent);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispatchListforControlEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTargetWithActionForControlEvent of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_addTargetWithActionForControlEvent00
static int tolua_CCControl_CCControl_addTargetWithActionForControlEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  unsigned int controlEvent = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTargetWithActionForControlEvent'", NULL);
#endif
  {
   self->addTargetWithActionForControlEvent(target,action,controlEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTargetWithActionForControlEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTargetWithActionForControlEvent of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_removeTargetWithActionForControlEvent00
static int tolua_CCControl_CCControl_removeTargetWithActionForControlEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  unsigned int controlEvent = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTargetWithActionForControlEvent'", NULL);
#endif
  {
   self->removeTargetWithActionForControlEvent(target,action,controlEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTargetWithActionForControlEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_CCControl_CCControl_create00
static int tolua_CCControl_CCControl_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControl* tolua_ret = (CCControl*)  CCControl::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControl");
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

/* get function: __CCRGBAProtocol__ of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_get_CCControl___CCRGBAProtocol__
static int tolua_get_CCControl___CCRGBAProtocol__(lua_State* tolua_S)
{
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
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
TOLUA_API int tolua_CCControl_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCControl_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"kControlEventTotalNumber",kControlEventTotalNumber);
  tolua_constant(tolua_S,"CCControlEventTouchDown",CCControlEventTouchDown);
  tolua_constant(tolua_S,"CCControlEventTouchDragInside",CCControlEventTouchDragInside);
  tolua_constant(tolua_S,"CCControlEventTouchDragOutside",CCControlEventTouchDragOutside);
  tolua_constant(tolua_S,"CCControlEventTouchDragEnter",CCControlEventTouchDragEnter);
  tolua_constant(tolua_S,"CCControlEventTouchDragExit",CCControlEventTouchDragExit);
  tolua_constant(tolua_S,"CCControlEventTouchUpInside",CCControlEventTouchUpInside);
  tolua_constant(tolua_S,"CCControlEventTouchUpOutside",CCControlEventTouchUpOutside);
  tolua_constant(tolua_S,"CCControlEventTouchCancel",CCControlEventTouchCancel);
  tolua_constant(tolua_S,"CCControlEventValueChanged",CCControlEventValueChanged);
  tolua_constant(tolua_S,"CCControlStateNormal",CCControlStateNormal);
  tolua_constant(tolua_S,"CCControlStateHighlighted",CCControlStateHighlighted);
  tolua_constant(tolua_S,"CCControlStateDisabled",CCControlStateDisabled);
  tolua_constant(tolua_S,"CCControlStateSelected",CCControlStateSelected);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCControl","CCControl","CCLayer",tolua_collect_CCControl);
  #else
  tolua_cclass(tolua_S,"CCControl","CCControl","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCControl");
   tolua_variable(tolua_S,"m_cOpacity",tolua_get_CCControl_m_cOpacity,tolua_set_CCControl_m_cOpacity);
   tolua_function(tolua_S,"getOpacity",tolua_CCControl_CCControl_getOpacity00);
   tolua_function(tolua_S,"setOpacity",tolua_CCControl_CCControl_setOpacity00);
   tolua_variable(tolua_S,"m_tColor",tolua_get_CCControl_m_tColor,tolua_set_CCControl_m_tColor);
   tolua_function(tolua_S,"getColor",tolua_CCControl_CCControl_getColor00);
   tolua_function(tolua_S,"setColor",tolua_CCControl_CCControl_setColor00);
   tolua_variable(tolua_S,"m_bIsOpacityModifyRGB",tolua_get_CCControl_m_bIsOpacityModifyRGB,tolua_set_CCControl_m_bIsOpacityModifyRGB);
   tolua_function(tolua_S,"isOpacityModifyRGB",tolua_CCControl_CCControl_isOpacityModifyRGB00);
   tolua_function(tolua_S,"setOpacityModifyRGB",tolua_CCControl_CCControl_setOpacityModifyRGB00);
   tolua_variable(tolua_S,"m_nDefaultTouchPriority",tolua_get_CCControl_m_nDefaultTouchPriority,tolua_set_CCControl_m_nDefaultTouchPriority);
   tolua_function(tolua_S,"getDefaultTouchPriority",tolua_CCControl_CCControl_getDefaultTouchPriority00);
   tolua_function(tolua_S,"setDefaultTouchPriority",tolua_CCControl_CCControl_setDefaultTouchPriority00);
   tolua_variable(tolua_S,"m_eState",tolua_get_CCControl_unsigned_m_eState,tolua_set_CCControl_unsigned_m_eState);
   tolua_function(tolua_S,"getState",tolua_CCControl_CCControl_getState00);
   tolua_variable(tolua_S,"m_hasVisibleParents",tolua_get_CCControl_m_hasVisibleParents,tolua_set_CCControl_m_hasVisibleParents);
   tolua_function(tolua_S,"setEnabled",tolua_CCControl_CCControl_setEnabled00);
   tolua_function(tolua_S,"isEnabled",tolua_CCControl_CCControl_isEnabled00);
   tolua_function(tolua_S,"setSelected",tolua_CCControl_CCControl_setSelected00);
   tolua_function(tolua_S,"isSelected",tolua_CCControl_CCControl_isSelected00);
   tolua_function(tolua_S,"setHighlighted",tolua_CCControl_CCControl_setHighlighted00);
   tolua_function(tolua_S,"isHighlighted",tolua_CCControl_CCControl_isHighlighted00);
   tolua_function(tolua_S,"hasVisibleParents",tolua_CCControl_CCControl_hasVisibleParents00);
   tolua_function(tolua_S,"needsLayout",tolua_CCControl_CCControl_needsLayout00);
   tolua_variable(tolua_S,"m_bEnabled",tolua_get_CCControl_m_bEnabled,tolua_set_CCControl_m_bEnabled);
   tolua_variable(tolua_S,"m_bSelected",tolua_get_CCControl_m_bSelected,tolua_set_CCControl_m_bSelected);
   tolua_variable(tolua_S,"m_bHighlighted",tolua_get_CCControl_m_bHighlighted,tolua_set_CCControl_m_bHighlighted);
   tolua_variable(tolua_S,"m_pDispatchTable",tolua_get_CCControl_m_pDispatchTable_ptr,tolua_set_CCControl_m_pDispatchTable_ptr);
   tolua_function(tolua_S,"new",tolua_CCControl_CCControl_new00);
   tolua_function(tolua_S,"new_local",tolua_CCControl_CCControl_new00_local);
   tolua_function(tolua_S,".call",tolua_CCControl_CCControl_new00_local);
   tolua_function(tolua_S,"init",tolua_CCControl_CCControl_init00);
   tolua_function(tolua_S,"delete",tolua_CCControl_CCControl_delete00);
   tolua_function(tolua_S,"onEnter",tolua_CCControl_CCControl_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_CCControl_CCControl_onExit00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_CCControl_CCControl_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"sendActionsForControlEvents",tolua_CCControl_CCControl_sendActionsForControlEvents00);
   tolua_function(tolua_S,"addTargetWithActionForControlEvents",tolua_CCControl_CCControl_addTargetWithActionForControlEvents00);
   tolua_function(tolua_S,"removeTargetWithActionForControlEvents",tolua_CCControl_CCControl_removeTargetWithActionForControlEvents00);
   tolua_function(tolua_S,"getTouchLocation",tolua_CCControl_CCControl_getTouchLocation00);
   tolua_function(tolua_S,"isTouchInside",tolua_CCControl_CCControl_isTouchInside00);
   tolua_function(tolua_S,"invocationWithTargetAndActionForControlEvent",tolua_CCControl_CCControl_invocationWithTargetAndActionForControlEvent00);
   tolua_function(tolua_S,"dispatchListforControlEvent",tolua_CCControl_CCControl_dispatchListforControlEvent00);
   tolua_function(tolua_S,"addTargetWithActionForControlEvent",tolua_CCControl_CCControl_addTargetWithActionForControlEvent00);
   tolua_function(tolua_S,"removeTargetWithActionForControlEvent",tolua_CCControl_CCControl_removeTargetWithActionForControlEvent00);
   tolua_function(tolua_S,"create",tolua_CCControl_CCControl_create00);
   tolua_variable(tolua_S,"__CCRGBAProtocol__",tolua_get_CCControl___CCRGBAProtocol__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCControl (lua_State* tolua_S) {
 return tolua_CCControl_open(tolua_S);
};
#endif


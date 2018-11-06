/*
** Lua binding: SIX_UILayer
** Generated automatically by tolua++-1.0.92 on 05/14/13 14:38:37.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_UILayer_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ccColor4B (lua_State* tolua_S)
{
 ccColor4B* self = (ccColor4B*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_UILayer (lua_State* tolua_S)
{
 SIX_UILayer* self = (SIX_UILayer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_UILayer_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCLayerColor");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"ccColor4B");
 tolua_usertype(tolua_S,"SIX_UILayer");
}

/* method: new of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_new00
static int tolua_SIX_UILayer_SIX_UILayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool bTouchThroughForbidden = ((bool)  tolua_toboolean(tolua_S,2,false));
  int nPriority = ((int)  tolua_tonumber(tolua_S,3,0));
  bool bRedrawBorder = ((bool)  tolua_toboolean(tolua_S,4,false));
  {
   SIX_UILayer* tolua_ret = (SIX_UILayer*)  Mtolua_new((SIX_UILayer)(bTouchThroughForbidden,nPriority,bRedrawBorder));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UILayer");
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

/* method: new_local of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_new00_local
static int tolua_SIX_UILayer_SIX_UILayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool bTouchThroughForbidden = ((bool)  tolua_toboolean(tolua_S,2,false));
  int nPriority = ((int)  tolua_tonumber(tolua_S,3,0));
  bool bRedrawBorder = ((bool)  tolua_toboolean(tolua_S,4,false));
  {
   SIX_UILayer* tolua_ret = (SIX_UILayer*)  Mtolua_new((SIX_UILayer)(bTouchThroughForbidden,nPriority,bRedrawBorder));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UILayer");
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

/* method: delete of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_delete00
static int tolua_SIX_UILayer_SIX_UILayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_create00
static int tolua_SIX_UILayer_SIX_UILayer_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
  bool bTouchThroughForbidden = ((bool)  tolua_toboolean(tolua_S,5,false));
  int nPriority = ((int)  tolua_tonumber(tolua_S,6,0));
  bool bRedrawBorder = ((bool)  tolua_toboolean(tolua_S,7,false));
  {
   SIX_UILayer* tolua_ret = (SIX_UILayer*)  SIX_UILayer::create(*color,width,height,bTouchThroughForbidden,nPriority,bRedrawBorder);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UILayer");
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

/* method: create of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_create01
static int tolua_SIX_UILayer_SIX_UILayer_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  bool bTouchThroughForbidden = ((bool)  tolua_toboolean(tolua_S,3,false));
  int nPriority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool bRedrawBorder = ((bool)  tolua_toboolean(tolua_S,5,false));
  {
   SIX_UILayer* tolua_ret = (SIX_UILayer*)  SIX_UILayer::create(*color,bTouchThroughForbidden,nPriority,bRedrawBorder);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UILayer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UILayer_SIX_UILayer_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_init00
static int tolua_SIX_UILayer_SIX_UILayer_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: initWithColor of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_initWithColor00
static int tolua_SIX_UILayer_SIX_UILayer_initWithColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*color,width,height);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithColor of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_initWithColor01
static int tolua_SIX_UILayer_SIX_UILayer_initWithColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*color);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UILayer_SIX_UILayer_initWithColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_draw00
static int tolua_SIX_UILayer_SIX_UILayer_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_visit00
static int tolua_SIX_UILayer_SIX_UILayer_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: beforeDraw of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_beforeDraw00
static int tolua_SIX_UILayer_SIX_UILayer_beforeDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'beforeDraw'", NULL);
#endif
  {
   self->beforeDraw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beforeDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: afterDraw of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_afterDraw00
static int tolua_SIX_UILayer_SIX_UILayer_afterDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'afterDraw'", NULL);
#endif
  {
   self->afterDraw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'afterDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_registerWithTouchDispatcher00
static int tolua_SIX_UILayer_SIX_UILayer_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchBegan of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_ccTouchBegan00
static int tolua_SIX_UILayer_SIX_UILayer_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(pTouch,pEvent);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_ccTouchMoved00
static int tolua_SIX_UILayer_SIX_UILayer_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_ccTouchEnded00
static int tolua_SIX_UILayer_SIX_UILayer_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInterface of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_GetInterface00
static int tolua_SIX_UILayer_SIX_UILayer_GetInterface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInterface'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->GetInterface(pstrName);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInterface'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPriority of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_setPriority00
static int tolua_SIX_UILayer_SIX_UILayer_setPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  int Priority = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPriority'", NULL);
#endif
  {
   self->setPriority(Priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPriority of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_getPriority00
static int tolua_SIX_UILayer_SIX_UILayer_getPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PriorityPromote of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_PriorityPromote00
static int tolua_SIX_UILayer_SIX_UILayer_PriorityPromote00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PriorityPromote'", NULL);
#endif
  {
   self->PriorityPromote();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PriorityPromote'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PriorityReduce of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_PriorityReduce00
static int tolua_SIX_UILayer_SIX_UILayer_PriorityReduce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PriorityReduce'", NULL);
#endif
  {
   self->PriorityReduce();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PriorityReduce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSwallowsTouches of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_setSwallowsTouches00
static int tolua_SIX_UILayer_SIX_UILayer_setSwallowsTouches00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  bool bSwallowsTouches = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSwallowsTouches'", NULL);
#endif
  {
   self->setSwallowsTouches(bSwallowsTouches);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSwallowsTouches'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSwallowsTouches of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_getSwallowsTouches00
static int tolua_SIX_UILayer_SIX_UILayer_getSwallowsTouches00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSwallowsTouches'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getSwallowsTouches();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSwallowsTouches'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEventPause of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_setTouchEventPause00
static int tolua_SIX_UILayer_SIX_UILayer_setTouchEventPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  bool bPause = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEventPause'", NULL);
#endif
  {
   self->setTouchEventPause(bPause);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEventPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchEventPause of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_getTouchEventPause00
static int tolua_SIX_UILayer_SIX_UILayer_getTouchEventPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchEventPause'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getTouchEventPause();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchEventPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRedrawBorder of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_getRedrawBorder00
static int tolua_SIX_UILayer_SIX_UILayer_getRedrawBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRedrawBorder'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getRedrawBorder();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRedrawBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRedrawBorder of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_setRedrawBorder00
static int tolua_SIX_UILayer_SIX_UILayer_setRedrawBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  bool bRedrawBorder = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRedrawBorder'", NULL);
#endif
  {
   self->setRedrawBorder(bRedrawBorder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRedrawBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBorderColor of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_getBorderColor00
static int tolua_SIX_UILayer_SIX_UILayer_getBorderColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBorderColor'", NULL);
#endif
  {
   ccColor4B tolua_ret = (ccColor4B)  self->getBorderColor();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor4B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor4B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccColor4B));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor4B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBorderColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBorderColor of class  SIX_UILayer */
#ifndef TOLUA_DISABLE_tolua_SIX_UILayer_SIX_UILayer_setBorderColor00
static int tolua_SIX_UILayer_SIX_UILayer_setBorderColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UILayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UILayer* self = (SIX_UILayer*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBorderColor'", NULL);
#endif
  {
   self->setBorderColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBorderColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_UILayer_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_UILayer_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_UILayer","SIX_UILayer","CCLayerColor",tolua_collect_SIX_UILayer);
  #else
  tolua_cclass(tolua_S,"SIX_UILayer","SIX_UILayer","CCLayerColor",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_UILayer");
   tolua_function(tolua_S,"new",tolua_SIX_UILayer_SIX_UILayer_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_UILayer_SIX_UILayer_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_UILayer_SIX_UILayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_UILayer_SIX_UILayer_delete00);
   tolua_function(tolua_S,"create",tolua_SIX_UILayer_SIX_UILayer_create00);
   tolua_function(tolua_S,"create",tolua_SIX_UILayer_SIX_UILayer_create01);
   tolua_function(tolua_S,"init",tolua_SIX_UILayer_SIX_UILayer_init00);
   tolua_function(tolua_S,"initWithColor",tolua_SIX_UILayer_SIX_UILayer_initWithColor00);
   tolua_function(tolua_S,"initWithColor",tolua_SIX_UILayer_SIX_UILayer_initWithColor01);
   tolua_function(tolua_S,"draw",tolua_SIX_UILayer_SIX_UILayer_draw00);
   tolua_function(tolua_S,"visit",tolua_SIX_UILayer_SIX_UILayer_visit00);
   tolua_function(tolua_S,"beforeDraw",tolua_SIX_UILayer_SIX_UILayer_beforeDraw00);
   tolua_function(tolua_S,"afterDraw",tolua_SIX_UILayer_SIX_UILayer_afterDraw00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_SIX_UILayer_SIX_UILayer_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_SIX_UILayer_SIX_UILayer_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_SIX_UILayer_SIX_UILayer_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_SIX_UILayer_SIX_UILayer_ccTouchEnded00);
   tolua_function(tolua_S,"GetInterface",tolua_SIX_UILayer_SIX_UILayer_GetInterface00);
   tolua_function(tolua_S,"setPriority",tolua_SIX_UILayer_SIX_UILayer_setPriority00);
   tolua_function(tolua_S,"getPriority",tolua_SIX_UILayer_SIX_UILayer_getPriority00);
   tolua_function(tolua_S,"PriorityPromote",tolua_SIX_UILayer_SIX_UILayer_PriorityPromote00);
   tolua_function(tolua_S,"PriorityReduce",tolua_SIX_UILayer_SIX_UILayer_PriorityReduce00);
   tolua_function(tolua_S,"setSwallowsTouches",tolua_SIX_UILayer_SIX_UILayer_setSwallowsTouches00);
   tolua_function(tolua_S,"getSwallowsTouches",tolua_SIX_UILayer_SIX_UILayer_getSwallowsTouches00);
   tolua_function(tolua_S,"setTouchEventPause",tolua_SIX_UILayer_SIX_UILayer_setTouchEventPause00);
   tolua_function(tolua_S,"getTouchEventPause",tolua_SIX_UILayer_SIX_UILayer_getTouchEventPause00);
   tolua_function(tolua_S,"getRedrawBorder",tolua_SIX_UILayer_SIX_UILayer_getRedrawBorder00);
   tolua_function(tolua_S,"setRedrawBorder",tolua_SIX_UILayer_SIX_UILayer_setRedrawBorder00);
   tolua_function(tolua_S,"getBorderColor",tolua_SIX_UILayer_SIX_UILayer_getBorderColor00);
   tolua_function(tolua_S,"setBorderColor",tolua_SIX_UILayer_SIX_UILayer_setBorderColor00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_UILayer (lua_State* tolua_S) {
 return tolua_SIX_UILayer_open(tolua_S);
};
#endif


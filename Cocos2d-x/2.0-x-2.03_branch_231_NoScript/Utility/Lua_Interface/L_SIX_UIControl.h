/*
** Lua binding: SIX_UIControl
** Generated automatically by tolua++-1.0.92 on 04/03/13 13:38:46.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_UIControl_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CCString (lua_State* tolua_S)
//{
// CCString* self = (CCString*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_SIX_UIControl (lua_State* tolua_S)
{
 SIX_UIControl* self = (SIX_UIControl*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ccColor3B (lua_State* tolua_S)
{
 ccColor3B* self = (ccColor3B*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_RECT (lua_State* tolua_S)
{
 RECT* self = (RECT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UINT_PTR (lua_State* tolua_S)
{
 UINT_PTR* self = (UINT_PTR*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_UIControl_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCLayerColor");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCString");
 tolua_usertype(tolua_S,"RECT");
 tolua_usertype(tolua_S,"SIX_UIControl");
 tolua_usertype(tolua_S,"CCSet");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCAcceleration");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"UINT_PTR");
}

/* method: new of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_new00
static int tolua_SIX_UIControl_SIX_UIControl_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIControl* tolua_ret = (SIX_UIControl*)  Mtolua_new((SIX_UIControl)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIControl");
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

/* method: new_local of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_new00_local
static int tolua_SIX_UIControl_SIX_UIControl_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIControl* tolua_ret = (SIX_UIControl*)  Mtolua_new((SIX_UIControl)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIControl");
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

/* method: delete of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_delete00
static int tolua_SIX_UIControl_SIX_UIControl_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_init00
static int tolua_SIX_UIControl_SIX_UIControl_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onEnter of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_onEnter00
static int tolua_SIX_UIControl_SIX_UIControl_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onExit of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_onExit00
static int tolua_SIX_UIControl_SIX_UIControl_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onEnterTransitionDidFinish of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_onEnterTransitionDidFinish00
static int tolua_SIX_UIControl_SIX_UIControl_onEnterTransitionDidFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnterTransitionDidFinish'", NULL);
#endif
  {
   self->onEnterTransitionDidFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnterTransitionDidFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: didAccelerate of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_didAccelerate00
static int tolua_SIX_UIControl_SIX_UIControl_didAccelerate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAcceleration",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  CCAcceleration* pAccelerationValue = ((CCAcceleration*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'didAccelerate'", NULL);
#endif
  {
   self->didAccelerate(pAccelerationValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'didAccelerate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchBegan00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchMoved of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchMoved00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchEnded of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchEnded00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchCancelled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchCancelled00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
  {
   self->ccTouchCancelled(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchesBegan of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchesBegan00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchesBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  CCSet* pTouches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchesBegan'", NULL);
#endif
  {
   self->ccTouchesBegan(pTouches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchesBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchesMoved of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchesMoved00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchesMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  CCSet* pTouches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchesMoved'", NULL);
#endif
  {
   self->ccTouchesMoved(pTouches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchesMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchesEnded of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchesEnded00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchesEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  CCSet* pTouches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchesEnded'", NULL);
#endif
  {
   self->ccTouchesEnded(pTouches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchesEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchesCancelled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_ccTouchesCancelled00
static int tolua_SIX_UIControl_SIX_UIControl_ccTouchesCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  CCSet* pTouches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchesCancelled'", NULL);
#endif
  {
   self->ccTouchesCancelled(pTouches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchesCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInterface of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetInterface00
static int tolua_SIX_UIControl_SIX_UIControl_GetInterface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetClass of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetClass00
static int tolua_SIX_UIControl_SIX_UIControl_GetClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClass'", NULL);
#endif
  {
   CCString tolua_ret = (CCString)  self->GetClass();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCString));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetParent00
static int tolua_SIX_UIControl_SIX_UIControl_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   SIX_UIControl* tolua_ret = (SIX_UIControl*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIControl");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetWidth00
static int tolua_SIX_UIControl_SIX_UIControl_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetWidth00
static int tolua_SIX_UIControl_SIX_UIControl_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'", NULL);
#endif
  {
   self->SetWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetHeight00
static int tolua_SIX_UIControl_SIX_UIControl_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeight of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetHeight00
static int tolua_SIX_UIControl_SIX_UIControl_SetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  int height = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeight'", NULL);
#endif
  {
   self->SetHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetX of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetX00
static int tolua_SIX_UIControl_SIX_UIControl_GetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetX of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetX00
static int tolua_SIX_UIControl_SIX_UIControl_SetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetX'", NULL);
#endif
  {
   self->SetX(x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetY of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetY00
static int tolua_SIX_UIControl_SIX_UIControl_GetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetY'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetY of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetY00
static int tolua_SIX_UIControl_SIX_UIControl_SetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  int y = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetY'", NULL);
#endif
  {
   self->SetY(y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPadding of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetPadding00
static int tolua_SIX_UIControl_SIX_UIControl_GetPadding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPadding'", NULL);
#endif
  {
   RECT tolua_ret = (RECT)  self->GetPadding();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((RECT)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"RECT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(RECT));
     tolua_pushusertype(tolua_S,tolua_obj,"RECT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPadding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPadding of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetPadding00
static int tolua_SIX_UIControl_SIX_UIControl_SetPadding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  RECT rcPadding = *((RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPadding'", NULL);
#endif
  {
   self->SetPadding(rcPadding);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPadding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetName00
static int tolua_SIX_UIControl_SIX_UIControl_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   CCString* tolua_ret = (CCString*)  self->GetName();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCString");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetName00
static int tolua_SIX_UIControl_SIX_UIControl_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(pstrName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetText00
static int tolua_SIX_UIControl_SIX_UIControl_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'", NULL);
#endif
  {
   CCString tolua_ret = (CCString)  self->GetText();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCString));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetText00
static int tolua_SIX_UIControl_SIX_UIControl_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'", NULL);
#endif
  {
   self->SetText(pstrText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBorderSize of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetBorderSize00
static int tolua_SIX_UIControl_SIX_UIControl_GetBorderSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBorderSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetBorderSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBorderSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBorderSize of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetBorderSize00
static int tolua_SIX_UIControl_SIX_UIControl_SetBorderSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  int nSize = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBorderSize'", NULL);
#endif
  {
   self->SetBorderSize(nSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBorderSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBorderColor of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetBorderColor00
static int tolua_SIX_UIControl_SIX_UIControl_GetBorderColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBorderColor'", NULL);
#endif
  {
   ccColor3B tolua_ret = (ccColor3B)  self->GetBorderColor();
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
 tolua_error(tolua_S,"#ferror in function 'GetBorderColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBorderColor of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetBorderColor00
static int tolua_SIX_UIControl_SIX_UIControl_SetBorderColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  ccColor3B dwBorderColor = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBorderColor'", NULL);
#endif
  {
   self->SetBorderColor(dwBorderColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBorderColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisible of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsVisible00
static int tolua_SIX_UIControl_SIX_UIControl_IsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVisible of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetVisible00
static int tolua_SIX_UIControl_SIX_UIControl_SetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bVisible = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVisible'", NULL);
#endif
  {
   self->SetVisible(bVisible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsEnabled00
static int tolua_SIX_UIControl_SIX_UIControl_IsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetEnabled00
static int tolua_SIX_UIControl_SIX_UIControl_SetEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bEnable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnabled'", NULL);
#endif
  {
   self->SetEnabled(bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMouseEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsMouseEnabled00
static int tolua_SIX_UIControl_SIX_UIControl_IsMouseEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMouseEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMouseEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMouseEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMouseEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetMouseEnabled00
static int tolua_SIX_UIControl_SIX_UIControl_SetMouseEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bEnable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMouseEnabled'", NULL);
#endif
  {
   self->SetMouseEnabled(bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMouseEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFocused of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsFocused00
static int tolua_SIX_UIControl_SIX_UIControl_IsFocused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFocused'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFocused();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFocused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFocus of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetFocus00
static int tolua_SIX_UIControl_SIX_UIControl_SetFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFocus'", NULL);
#endif
  {
   self->SetFocus();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFloat of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsFloat00
static int tolua_SIX_UIControl_SIX_UIControl_IsFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFloat'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFloat();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFloat of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetFloat00
static int tolua_SIX_UIControl_SIX_UIControl_SetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bFloat = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFloat'", NULL);
#endif
  {
   self->SetFloat(bFloat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHyperLink of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetHyperLink00
static int tolua_SIX_UIControl_SIX_UIControl_GetHyperLink00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHyperLink'", NULL);
#endif
  {
   CCString tolua_ret = (CCString)  self->GetHyperLink();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCString));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHyperLink'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHyperLink of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetHyperLink00
static int tolua_SIX_UIControl_SIX_UIControl_SetHyperLink00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHyperLink'", NULL);
#endif
  {
   self->SetHyperLink(pstrText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHyperLink'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShowHtml of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsShowHtml00
static int tolua_SIX_UIControl_SIX_UIControl_IsShowHtml00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsShowHtml'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsShowHtml();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShowHtml'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShowHtml of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetShowHtml00
static int tolua_SIX_UIControl_SIX_UIControl_SetShowHtml00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bShowHtml = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowHtml'", NULL);
#endif
  {
   self->SetShowHtml(bShowHtml);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowHtml'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDraggable of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetDraggable00
static int tolua_SIX_UIControl_SIX_UIControl_GetDraggable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDraggable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetDraggable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDraggable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDraggable of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetDraggable00
static int tolua_SIX_UIControl_SIX_UIControl_SetDraggable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bDraggable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDraggable'", NULL);
#endif
  {
   self->SetDraggable(bDraggable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDraggable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDrawDirty of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_IsDrawDirty00
static int tolua_SIX_UIControl_SIX_UIControl_IsDrawDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDrawDirty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDrawDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDrawDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawDirty of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetDrawDirty00
static int tolua_SIX_UIControl_SIX_UIControl_SetDrawDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  bool bDrawDirty = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawDirty'", NULL);
#endif
  {
   self->SetDrawDirty(bDrawDirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetToolTip of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetToolTip00
static int tolua_SIX_UIControl_SIX_UIControl_GetToolTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetToolTip'", NULL);
#endif
  {
   CCString tolua_ret = (CCString)  self->GetToolTip();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCString));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetToolTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetToolTip of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetToolTip00
static int tolua_SIX_UIControl_SIX_UIControl_SetToolTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetToolTip'", NULL);
#endif
  {
   self->SetToolTip(pstrText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetToolTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserData of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetUserData00
static int tolua_SIX_UIControl_SIX_UIControl_GetUserData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUserData'", NULL);
#endif
  {
   CCString tolua_ret = (CCString)  self->GetUserData();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCString));
     tolua_pushusertype(tolua_S,tolua_obj,"CCString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUserData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUserData of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetUserData00
static int tolua_SIX_UIControl_SIX_UIControl_SetUserData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  const char* pstrText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUserData'", NULL);
#endif
  {
   self->SetUserData(pstrText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUserData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTag of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_GetTag00
static int tolua_SIX_UIControl_SIX_UIControl_GetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_UIControl* self = (const SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTag'", NULL);
#endif
  {
   UINT_PTR tolua_ret = (UINT_PTR)  self->GetTag();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((UINT_PTR)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"UINT_PTR");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(UINT_PTR));
     tolua_pushusertype(tolua_S,tolua_obj,"UINT_PTR");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTag of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_SetTag00
static int tolua_SIX_UIControl_SIX_UIControl_SetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UINT_PTR",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
  UINT_PTR pTag = *((UINT_PTR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTag'", NULL);
#endif
  {
   self->SetTag(pTag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pParent of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_pParent_ptr
static int tolua_get_SIX_UIControl_m_pParent_ptr(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pParent'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pParent,"SIX_UIControl");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pParent of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_pParent_ptr
static int tolua_set_SIX_UIControl_m_pParent_ptr(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pParent'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_UIControl",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pParent = ((SIX_UIControl*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_rcItem of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_rcItem
static int tolua_get_SIX_UIControl_m_rcItem(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_rcItem'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_rcItem,"RECT");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_rcItem of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_rcItem
static int tolua_set_SIX_UIControl_m_rcItem(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_rcItem'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_rcItem = *((RECT*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_rcPadding of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_rcPadding
static int tolua_get_SIX_UIControl_m_rcPadding(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_rcPadding'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_rcPadding,"RECT");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_rcPadding of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_rcPadding
static int tolua_set_SIX_UIControl_m_rcPadding(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_rcPadding'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_rcPadding = *((RECT*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sName of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_sName_ptr
static int tolua_get_SIX_UIControl_m_sName_ptr(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sName'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_sName,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sName of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_sName_ptr
static int tolua_set_SIX_UIControl_m_sName_ptr(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sName'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sName = ((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sText of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_sText
static int tolua_get_SIX_UIControl_m_sText(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sText'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_sText,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sText of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_sText
static int tolua_set_SIX_UIControl_m_sText(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sText'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sText = *((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nBorderSize of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_nBorderSize
static int tolua_get_SIX_UIControl_m_nBorderSize(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nBorderSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_nBorderSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nBorderSize of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_nBorderSize
static int tolua_set_SIX_UIControl_m_nBorderSize(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nBorderSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nBorderSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwBorderColor of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_dwBorderColor
static int tolua_get_SIX_UIControl_m_dwBorderColor(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwBorderColor'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_dwBorderColor,"ccColor3B");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwBorderColor of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_dwBorderColor
static int tolua_set_SIX_UIControl_m_dwBorderColor(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwBorderColor'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwBorderColor = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bVisible of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bVisible
static int tolua_get_SIX_UIControl_m_bVisible(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bVisible'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bVisible);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bVisible of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bVisible
static int tolua_set_SIX_UIControl_m_bVisible(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bVisible'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bVisible = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bEnabled
static int tolua_get_SIX_UIControl_m_bEnabled(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bEnabled);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bEnabled
static int tolua_set_SIX_UIControl_m_bEnabled(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_bMouseEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bMouseEnabled
static int tolua_get_SIX_UIControl_m_bMouseEnabled(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bMouseEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bMouseEnabled);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bMouseEnabled of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bMouseEnabled
static int tolua_set_SIX_UIControl_m_bMouseEnabled(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bMouseEnabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bMouseEnabled = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bFocused of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bFocused
static int tolua_get_SIX_UIControl_m_bFocused(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bFocused'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bFocused);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bFocused of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bFocused
static int tolua_set_SIX_UIControl_m_bFocused(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bFocused'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bFocused = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bFloat of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bFloat
static int tolua_get_SIX_UIControl_m_bFloat(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bFloat'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bFloat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bFloat of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bFloat
static int tolua_set_SIX_UIControl_m_bFloat(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bFloat'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bFloat = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sHyperLinkUrl of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_sHyperLinkUrl
static int tolua_get_SIX_UIControl_m_sHyperLinkUrl(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sHyperLinkUrl'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_sHyperLinkUrl,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sHyperLinkUrl of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_sHyperLinkUrl
static int tolua_set_SIX_UIControl_m_sHyperLinkUrl(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sHyperLinkUrl'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sHyperLinkUrl = *((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bShowHtml of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bShowHtml
static int tolua_get_SIX_UIControl_m_bShowHtml(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bShowHtml'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bShowHtml);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bShowHtml of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bShowHtml
static int tolua_set_SIX_UIControl_m_bShowHtml(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bShowHtml'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bShowHtml = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bDraggable of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bDraggable
static int tolua_get_SIX_UIControl_m_bDraggable(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bDraggable'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bDraggable);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bDraggable of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bDraggable
static int tolua_set_SIX_UIControl_m_bDraggable(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bDraggable'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bDraggable = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bDrawDirty of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_bDrawDirty
static int tolua_get_SIX_UIControl_m_bDrawDirty(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bDrawDirty'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bDrawDirty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bDrawDirty of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_bDrawDirty
static int tolua_set_SIX_UIControl_m_bDrawDirty(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bDrawDirty'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bDrawDirty = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sToolTip of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_sToolTip
static int tolua_get_SIX_UIControl_m_sToolTip(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sToolTip'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_sToolTip,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sToolTip of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_sToolTip
static int tolua_set_SIX_UIControl_m_sToolTip(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sToolTip'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sToolTip = *((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sUserData of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_sUserData
static int tolua_get_SIX_UIControl_m_sUserData(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sUserData'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_sUserData,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sUserData of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_sUserData
static int tolua_set_SIX_UIControl_m_sUserData(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sUserData'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sUserData = *((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pTag of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIControl_m_pTag
static int tolua_get_SIX_UIControl_m_pTag(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pTag'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_pTag,"UINT_PTR");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pTag of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIControl_m_pTag
static int tolua_set_SIX_UIControl_m_pTag(lua_State* tolua_S)
{
  SIX_UIControl* self = (SIX_UIControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pTag'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UINT_PTR",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pTag = *((UINT_PTR*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  SIX_UIControl */
#ifndef TOLUA_DISABLE_tolua_SIX_UIControl_SIX_UIControl_create00
static int tolua_SIX_UIControl_SIX_UIControl_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIControl* tolua_ret = (SIX_UIControl*)  SIX_UIControl::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIControl");
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

/* Open function */
TOLUA_API int tolua_SIX_UIControl_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_UIControl_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_UIControl","SIX_UIControl","CCLayerColor",tolua_collect_SIX_UIControl);
  #else
  tolua_cclass(tolua_S,"SIX_UIControl","SIX_UIControl","CCLayerColor",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_UIControl");
   tolua_function(tolua_S,"new",tolua_SIX_UIControl_SIX_UIControl_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_UIControl_SIX_UIControl_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_UIControl_SIX_UIControl_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_UIControl_SIX_UIControl_delete00);
   tolua_function(tolua_S,"init",tolua_SIX_UIControl_SIX_UIControl_init00);
   tolua_function(tolua_S,"onEnter",tolua_SIX_UIControl_SIX_UIControl_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_SIX_UIControl_SIX_UIControl_onExit00);
   tolua_function(tolua_S,"onEnterTransitionDidFinish",tolua_SIX_UIControl_SIX_UIControl_onEnterTransitionDidFinish00);
   tolua_function(tolua_S,"didAccelerate",tolua_SIX_UIControl_SIX_UIControl_didAccelerate00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_SIX_UIControl_SIX_UIControl_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_SIX_UIControl_SIX_UIControl_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_SIX_UIControl_SIX_UIControl_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_SIX_UIControl_SIX_UIControl_ccTouchCancelled00);
   tolua_function(tolua_S,"ccTouchesBegan",tolua_SIX_UIControl_SIX_UIControl_ccTouchesBegan00);
   tolua_function(tolua_S,"ccTouchesMoved",tolua_SIX_UIControl_SIX_UIControl_ccTouchesMoved00);
   tolua_function(tolua_S,"ccTouchesEnded",tolua_SIX_UIControl_SIX_UIControl_ccTouchesEnded00);
   tolua_function(tolua_S,"ccTouchesCancelled",tolua_SIX_UIControl_SIX_UIControl_ccTouchesCancelled00);
   tolua_function(tolua_S,"GetInterface",tolua_SIX_UIControl_SIX_UIControl_GetInterface00);
   tolua_function(tolua_S,"GetClass",tolua_SIX_UIControl_SIX_UIControl_GetClass00);
   tolua_function(tolua_S,"GetParent",tolua_SIX_UIControl_SIX_UIControl_GetParent00);
   tolua_function(tolua_S,"GetWidth",tolua_SIX_UIControl_SIX_UIControl_GetWidth00);
   tolua_function(tolua_S,"SetWidth",tolua_SIX_UIControl_SIX_UIControl_SetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_SIX_UIControl_SIX_UIControl_GetHeight00);
   tolua_function(tolua_S,"SetHeight",tolua_SIX_UIControl_SIX_UIControl_SetHeight00);
   tolua_function(tolua_S,"GetX",tolua_SIX_UIControl_SIX_UIControl_GetX00);
   tolua_function(tolua_S,"SetX",tolua_SIX_UIControl_SIX_UIControl_SetX00);
   tolua_function(tolua_S,"GetY",tolua_SIX_UIControl_SIX_UIControl_GetY00);
   tolua_function(tolua_S,"SetY",tolua_SIX_UIControl_SIX_UIControl_SetY00);
   tolua_function(tolua_S,"GetPadding",tolua_SIX_UIControl_SIX_UIControl_GetPadding00);
   tolua_function(tolua_S,"SetPadding",tolua_SIX_UIControl_SIX_UIControl_SetPadding00);
   tolua_function(tolua_S,"GetName",tolua_SIX_UIControl_SIX_UIControl_GetName00);
   tolua_function(tolua_S,"SetName",tolua_SIX_UIControl_SIX_UIControl_SetName00);
   tolua_function(tolua_S,"GetText",tolua_SIX_UIControl_SIX_UIControl_GetText00);
   tolua_function(tolua_S,"SetText",tolua_SIX_UIControl_SIX_UIControl_SetText00);
   tolua_function(tolua_S,"GetBorderSize",tolua_SIX_UIControl_SIX_UIControl_GetBorderSize00);
   tolua_function(tolua_S,"SetBorderSize",tolua_SIX_UIControl_SIX_UIControl_SetBorderSize00);
   tolua_function(tolua_S,"GetBorderColor",tolua_SIX_UIControl_SIX_UIControl_GetBorderColor00);
   tolua_function(tolua_S,"SetBorderColor",tolua_SIX_UIControl_SIX_UIControl_SetBorderColor00);
   tolua_function(tolua_S,"IsVisible",tolua_SIX_UIControl_SIX_UIControl_IsVisible00);
   tolua_function(tolua_S,"SetVisible",tolua_SIX_UIControl_SIX_UIControl_SetVisible00);
   tolua_function(tolua_S,"IsEnabled",tolua_SIX_UIControl_SIX_UIControl_IsEnabled00);
   tolua_function(tolua_S,"SetEnabled",tolua_SIX_UIControl_SIX_UIControl_SetEnabled00);
   tolua_function(tolua_S,"IsMouseEnabled",tolua_SIX_UIControl_SIX_UIControl_IsMouseEnabled00);
   tolua_function(tolua_S,"SetMouseEnabled",tolua_SIX_UIControl_SIX_UIControl_SetMouseEnabled00);
   tolua_function(tolua_S,"IsFocused",tolua_SIX_UIControl_SIX_UIControl_IsFocused00);
   tolua_function(tolua_S,"SetFocus",tolua_SIX_UIControl_SIX_UIControl_SetFocus00);
   tolua_function(tolua_S,"IsFloat",tolua_SIX_UIControl_SIX_UIControl_IsFloat00);
   tolua_function(tolua_S,"SetFloat",tolua_SIX_UIControl_SIX_UIControl_SetFloat00);
   tolua_function(tolua_S,"GetHyperLink",tolua_SIX_UIControl_SIX_UIControl_GetHyperLink00);
   tolua_function(tolua_S,"SetHyperLink",tolua_SIX_UIControl_SIX_UIControl_SetHyperLink00);
   tolua_function(tolua_S,"IsShowHtml",tolua_SIX_UIControl_SIX_UIControl_IsShowHtml00);
   tolua_function(tolua_S,"SetShowHtml",tolua_SIX_UIControl_SIX_UIControl_SetShowHtml00);
   tolua_function(tolua_S,"GetDraggable",tolua_SIX_UIControl_SIX_UIControl_GetDraggable00);
   tolua_function(tolua_S,"SetDraggable",tolua_SIX_UIControl_SIX_UIControl_SetDraggable00);
   tolua_function(tolua_S,"IsDrawDirty",tolua_SIX_UIControl_SIX_UIControl_IsDrawDirty00);
   tolua_function(tolua_S,"SetDrawDirty",tolua_SIX_UIControl_SIX_UIControl_SetDrawDirty00);
   tolua_function(tolua_S,"GetToolTip",tolua_SIX_UIControl_SIX_UIControl_GetToolTip00);
   tolua_function(tolua_S,"SetToolTip",tolua_SIX_UIControl_SIX_UIControl_SetToolTip00);
   tolua_function(tolua_S,"GetUserData",tolua_SIX_UIControl_SIX_UIControl_GetUserData00);
   tolua_function(tolua_S,"SetUserData",tolua_SIX_UIControl_SIX_UIControl_SetUserData00);
   tolua_function(tolua_S,"GetTag",tolua_SIX_UIControl_SIX_UIControl_GetTag00);
   tolua_function(tolua_S,"SetTag",tolua_SIX_UIControl_SIX_UIControl_SetTag00);
   tolua_variable(tolua_S,"m_pParent",tolua_get_SIX_UIControl_m_pParent_ptr,tolua_set_SIX_UIControl_m_pParent_ptr);
   tolua_variable(tolua_S,"m_rcItem",tolua_get_SIX_UIControl_m_rcItem,tolua_set_SIX_UIControl_m_rcItem);
   tolua_variable(tolua_S,"m_rcPadding",tolua_get_SIX_UIControl_m_rcPadding,tolua_set_SIX_UIControl_m_rcPadding);
   tolua_variable(tolua_S,"m_sName",tolua_get_SIX_UIControl_m_sName_ptr,tolua_set_SIX_UIControl_m_sName_ptr);
   tolua_variable(tolua_S,"m_sText",tolua_get_SIX_UIControl_m_sText,tolua_set_SIX_UIControl_m_sText);
   tolua_variable(tolua_S,"m_nBorderSize",tolua_get_SIX_UIControl_m_nBorderSize,tolua_set_SIX_UIControl_m_nBorderSize);
   tolua_variable(tolua_S,"m_dwBorderColor",tolua_get_SIX_UIControl_m_dwBorderColor,tolua_set_SIX_UIControl_m_dwBorderColor);
   tolua_variable(tolua_S,"m_bVisible",tolua_get_SIX_UIControl_m_bVisible,tolua_set_SIX_UIControl_m_bVisible);
   tolua_variable(tolua_S,"m_bEnabled",tolua_get_SIX_UIControl_m_bEnabled,tolua_set_SIX_UIControl_m_bEnabled);
   tolua_variable(tolua_S,"m_bMouseEnabled",tolua_get_SIX_UIControl_m_bMouseEnabled,tolua_set_SIX_UIControl_m_bMouseEnabled);
   tolua_variable(tolua_S,"m_bFocused",tolua_get_SIX_UIControl_m_bFocused,tolua_set_SIX_UIControl_m_bFocused);
   tolua_variable(tolua_S,"m_bFloat",tolua_get_SIX_UIControl_m_bFloat,tolua_set_SIX_UIControl_m_bFloat);
   tolua_variable(tolua_S,"m_sHyperLinkUrl",tolua_get_SIX_UIControl_m_sHyperLinkUrl,tolua_set_SIX_UIControl_m_sHyperLinkUrl);
   tolua_variable(tolua_S,"m_bShowHtml",tolua_get_SIX_UIControl_m_bShowHtml,tolua_set_SIX_UIControl_m_bShowHtml);
   tolua_variable(tolua_S,"m_bDraggable",tolua_get_SIX_UIControl_m_bDraggable,tolua_set_SIX_UIControl_m_bDraggable);
   tolua_variable(tolua_S,"m_bDrawDirty",tolua_get_SIX_UIControl_m_bDrawDirty,tolua_set_SIX_UIControl_m_bDrawDirty);
   tolua_variable(tolua_S,"m_sToolTip",tolua_get_SIX_UIControl_m_sToolTip,tolua_set_SIX_UIControl_m_sToolTip);
   tolua_variable(tolua_S,"m_sUserData",tolua_get_SIX_UIControl_m_sUserData,tolua_set_SIX_UIControl_m_sUserData);
   tolua_variable(tolua_S,"m_pTag",tolua_get_SIX_UIControl_m_pTag,tolua_set_SIX_UIControl_m_pTag);
   tolua_function(tolua_S,"create",tolua_SIX_UIControl_SIX_UIControl_create00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_UIControl (lua_State* tolua_S) {
 return tolua_SIX_UIControl_open(tolua_S);
};
#endif


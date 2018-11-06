/*
** Lua binding: CCTouchDispatcher
** Generated automatically by tolua++-1.0.92 on 04/28/13 02:12:21.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCTouchDispatcher_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCTouchDispatcher (lua_State* tolua_S)
{
 CCTouchDispatcher* self = (CCTouchDispatcher*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_EGLTouchDelegate (lua_State* tolua_S)
{
 EGLTouchDelegate* self = (EGLTouchDelegate*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCTouchDispatcher_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCTouchDelegate");
 tolua_usertype(tolua_S,"CCSet");
 tolua_usertype(tolua_S,"CCTouchHandler");
 tolua_usertype(tolua_S,"CCTouchDispatcher");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"ccTouchHandlerHelperData");
 tolua_usertype(tolua_S,"EGLTouchDelegate");
}

/* get function: m_type of class  ccTouchHandlerHelperData */
#ifndef TOLUA_DISABLE_tolua_get_ccTouchHandlerHelperData_m_type
static int tolua_get_ccTouchHandlerHelperData_m_type(lua_State* tolua_S)
{
  ccTouchHandlerHelperData* self = (ccTouchHandlerHelperData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_type of class  ccTouchHandlerHelperData */
#ifndef TOLUA_DISABLE_tolua_set_ccTouchHandlerHelperData_m_type
static int tolua_set_ccTouchHandlerHelperData_m_type(lua_State* tolua_S)
{
  ccTouchHandlerHelperData* self = (ccTouchHandlerHelperData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_type = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesBegan of class  EGLTouchDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_EGLTouchDelegate_touchesBegan00
static int tolua_CCTouchDispatcher_EGLTouchDelegate_touchesBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EGLTouchDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EGLTouchDelegate* self = (EGLTouchDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesBegan'", NULL);
#endif
  {
   self->touchesBegan(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesMoved of class  EGLTouchDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_EGLTouchDelegate_touchesMoved00
static int tolua_CCTouchDispatcher_EGLTouchDelegate_touchesMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EGLTouchDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EGLTouchDelegate* self = (EGLTouchDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesMoved'", NULL);
#endif
  {
   self->touchesMoved(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesEnded of class  EGLTouchDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_EGLTouchDelegate_touchesEnded00
static int tolua_CCTouchDispatcher_EGLTouchDelegate_touchesEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EGLTouchDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EGLTouchDelegate* self = (EGLTouchDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesEnded'", NULL);
#endif
  {
   self->touchesEnded(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesCancelled of class  EGLTouchDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_EGLTouchDelegate_touchesCancelled00
static int tolua_CCTouchDispatcher_EGLTouchDelegate_touchesCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EGLTouchDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EGLTouchDelegate* self = (EGLTouchDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesCancelled'", NULL);
#endif
  {
   self->touchesCancelled(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MouseMoveMoved of class  EGLTouchDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_EGLTouchDelegate_MouseMoveMoved00
static int tolua_CCTouchDispatcher_EGLTouchDelegate_MouseMoveMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EGLTouchDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EGLTouchDelegate* self = (EGLTouchDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MouseMoveMoved'", NULL);
#endif
  {
   self->MouseMoveMoved(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MouseMoveMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  EGLTouchDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_EGLTouchDelegate_delete00
static int tolua_CCTouchDispatcher_EGLTouchDelegate_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EGLTouchDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EGLTouchDelegate* self = (EGLTouchDelegate*)  tolua_tousertype(tolua_S,1,0);
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

/* method: delete of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_delete00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_init00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_new00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTouchDispatcher* tolua_ret = (CCTouchDispatcher*)  Mtolua_new((CCTouchDispatcher)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTouchDispatcher");
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

/* method: new_local of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_new00_local
static int tolua_CCTouchDispatcher_CCTouchDispatcher_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTouchDispatcher* tolua_ret = (CCTouchDispatcher*)  Mtolua_new((CCTouchDispatcher)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTouchDispatcher");
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

/* method: isDispatchEvents of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_isDispatchEvents00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_isDispatchEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDispatchEvents'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDispatchEvents();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDispatchEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDispatchEvents of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_setDispatchEvents00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_setDispatchEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  bool bDispatchEvents = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDispatchEvents'", NULL);
#endif
  {
   self->setDispatchEvents(bDispatchEvents);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDispatchEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addStandardDelegate of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_addStandardDelegate00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_addStandardDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouchDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCTouchDelegate* pDelegate = ((CCTouchDelegate*)  tolua_tousertype(tolua_S,2,0));
  int nPriority = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addStandardDelegate'", NULL);
#endif
  {
   self->addStandardDelegate(pDelegate,nPriority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addStandardDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTargetedDelegate of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_addTargetedDelegate00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_addTargetedDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouchDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCTouchDelegate* pDelegate = ((CCTouchDelegate*)  tolua_tousertype(tolua_S,2,0));
  int nPriority = ((int)  tolua_tonumber(tolua_S,3,0));
  bool bSwallowsTouches = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTargetedDelegate'", NULL);
#endif
  {
   self->addTargetedDelegate(pDelegate,nPriority,bSwallowsTouches);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTargetedDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeDelegate of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_removeDelegate00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_removeDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouchDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCTouchDelegate* pDelegate = ((CCTouchDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeDelegate'", NULL);
#endif
  {
   self->removeDelegate(pDelegate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllDelegates of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_removeAllDelegates00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_removeAllDelegates00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllDelegates'", NULL);
#endif
  {
   self->removeAllDelegates();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllDelegates'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPriority of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_setPriority00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_setPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCTouchDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  int nPriority = ((int)  tolua_tonumber(tolua_S,2,0));
  CCTouchDelegate* pDelegate = ((CCTouchDelegate*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPriority'", NULL);
#endif
  {
   self->setPriority(nPriority,pDelegate);
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

/* method: getPriority of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_getPriority00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_getPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouchDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCTouchDelegate* pDelegate = ((CCTouchDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPriority(pDelegate);
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

/* method: touches of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_touches00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_touches00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCSet* pTouches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
  unsigned int uIndex = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touches'", NULL);
#endif
  {
   self->touches(pTouches,pEvent,uIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touches'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesBegan of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_touchesBegan00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_touchesBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesBegan'", NULL);
#endif
  {
   self->touchesBegan(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesMoved of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_touchesMoved00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_touchesMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesMoved'", NULL);
#endif
  {
   self->touchesMoved(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesEnded of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_touchesEnded00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_touchesEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesEnded'", NULL);
#endif
  {
   self->touchesEnded(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchesCancelled of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_touchesCancelled00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_touchesCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchesCancelled'", NULL);
#endif
  {
   self->touchesCancelled(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchesCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MouseMoveMoved of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_MouseMoveMoved00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_MouseMoveMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCSet* touches = ((CCSet*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MouseMoveMoved'", NULL);
#endif
  {
   self->MouseMoveMoved(touches,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MouseMoveMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findHandler of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_CCTouchDispatcher_CCTouchDispatcher_findHandler00
static int tolua_CCTouchDispatcher_CCTouchDispatcher_findHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTouchDispatcher",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouchDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
  CCTouchDelegate* pDelegate = ((CCTouchDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findHandler'", NULL);
#endif
  {
   CCTouchHandler* tolua_ret = (CCTouchHandler*)  self->findHandler(pDelegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTouchHandler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __EGLTouchDelegate__ of class  CCTouchDispatcher */
#ifndef TOLUA_DISABLE_tolua_get_CCTouchDispatcher___EGLTouchDelegate__
static int tolua_get_CCTouchDispatcher___EGLTouchDelegate__(lua_State* tolua_S)
{
  CCTouchDispatcher* self = (CCTouchDispatcher*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__EGLTouchDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<EGLTouchDelegate*>(self), "EGLTouchDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((EGLTouchDelegate*)self), "EGLTouchDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCTouchDispatcher_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCTouchDispatcher_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"ccTouchSelectorBeganBit",ccTouchSelectorBeganBit);
  tolua_constant(tolua_S,"ccTouchSelectorMovedBit",ccTouchSelectorMovedBit);
  tolua_constant(tolua_S,"ccTouchSelectorEndedBit",ccTouchSelectorEndedBit);
  tolua_constant(tolua_S,"ccTouchSelectorCancelledBit",ccTouchSelectorCancelledBit);
  tolua_constant(tolua_S,"ccTouchSelectorAllBits",ccTouchSelectorAllBits);
  tolua_constant(tolua_S,"CCTOUCHBEGAN",CCTOUCHBEGAN);
  tolua_constant(tolua_S,"CCTOUCHMOVED",CCTOUCHMOVED);
  tolua_constant(tolua_S,"CCTOUCHENDED",CCTOUCHENDED);
  tolua_constant(tolua_S,"CCTOUCHCANCELLED",CCTOUCHCANCELLED);
  tolua_constant(tolua_S,"CCMOUSEMOVE",CCMOUSEMOVE);
  tolua_constant(tolua_S,"ccTouchMax",ccTouchMax);
  tolua_cclass(tolua_S,"ccTouchHandlerHelperData","ccTouchHandlerHelperData","",NULL);
  tolua_beginmodule(tolua_S,"ccTouchHandlerHelperData");
   tolua_variable(tolua_S,"m_type",tolua_get_ccTouchHandlerHelperData_m_type,tolua_set_ccTouchHandlerHelperData_m_type);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"EGLTouchDelegate","EGLTouchDelegate","",tolua_collect_EGLTouchDelegate);
  #else
  tolua_cclass(tolua_S,"EGLTouchDelegate","EGLTouchDelegate","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"EGLTouchDelegate");
   tolua_function(tolua_S,"touchesBegan",tolua_CCTouchDispatcher_EGLTouchDelegate_touchesBegan00);
   tolua_function(tolua_S,"touchesMoved",tolua_CCTouchDispatcher_EGLTouchDelegate_touchesMoved00);
   tolua_function(tolua_S,"touchesEnded",tolua_CCTouchDispatcher_EGLTouchDelegate_touchesEnded00);
   tolua_function(tolua_S,"touchesCancelled",tolua_CCTouchDispatcher_EGLTouchDelegate_touchesCancelled00);
   tolua_function(tolua_S,"MouseMoveMoved",tolua_CCTouchDispatcher_EGLTouchDelegate_MouseMoveMoved00);
   tolua_function(tolua_S,"delete",tolua_CCTouchDispatcher_EGLTouchDelegate_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCTouchDispatcher","CCTouchDispatcher","CCObject",tolua_collect_CCTouchDispatcher);
  #else
  tolua_cclass(tolua_S,"CCTouchDispatcher","CCTouchDispatcher","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCTouchDispatcher");
   tolua_function(tolua_S,"delete",tolua_CCTouchDispatcher_CCTouchDispatcher_delete00);
   tolua_function(tolua_S,"init",tolua_CCTouchDispatcher_CCTouchDispatcher_init00);
   tolua_function(tolua_S,"new",tolua_CCTouchDispatcher_CCTouchDispatcher_new00);
   tolua_function(tolua_S,"new_local",tolua_CCTouchDispatcher_CCTouchDispatcher_new00_local);
   tolua_function(tolua_S,".call",tolua_CCTouchDispatcher_CCTouchDispatcher_new00_local);
   tolua_function(tolua_S,"isDispatchEvents",tolua_CCTouchDispatcher_CCTouchDispatcher_isDispatchEvents00);
   tolua_function(tolua_S,"setDispatchEvents",tolua_CCTouchDispatcher_CCTouchDispatcher_setDispatchEvents00);
   tolua_function(tolua_S,"addStandardDelegate",tolua_CCTouchDispatcher_CCTouchDispatcher_addStandardDelegate00);
   tolua_function(tolua_S,"addTargetedDelegate",tolua_CCTouchDispatcher_CCTouchDispatcher_addTargetedDelegate00);
   tolua_function(tolua_S,"removeDelegate",tolua_CCTouchDispatcher_CCTouchDispatcher_removeDelegate00);
   tolua_function(tolua_S,"removeAllDelegates",tolua_CCTouchDispatcher_CCTouchDispatcher_removeAllDelegates00);
   tolua_function(tolua_S,"setPriority",tolua_CCTouchDispatcher_CCTouchDispatcher_setPriority00);
   tolua_function(tolua_S,"getPriority",tolua_CCTouchDispatcher_CCTouchDispatcher_getPriority00);
   tolua_function(tolua_S,"touches",tolua_CCTouchDispatcher_CCTouchDispatcher_touches00);
   tolua_function(tolua_S,"touchesBegan",tolua_CCTouchDispatcher_CCTouchDispatcher_touchesBegan00);
   tolua_function(tolua_S,"touchesMoved",tolua_CCTouchDispatcher_CCTouchDispatcher_touchesMoved00);
   tolua_function(tolua_S,"touchesEnded",tolua_CCTouchDispatcher_CCTouchDispatcher_touchesEnded00);
   tolua_function(tolua_S,"touchesCancelled",tolua_CCTouchDispatcher_CCTouchDispatcher_touchesCancelled00);
   tolua_function(tolua_S,"MouseMoveMoved",tolua_CCTouchDispatcher_CCTouchDispatcher_MouseMoveMoved00);
   tolua_function(tolua_S,"findHandler",tolua_CCTouchDispatcher_CCTouchDispatcher_findHandler00);
   tolua_variable(tolua_S,"__EGLTouchDelegate__",tolua_get_CCTouchDispatcher___EGLTouchDelegate__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCTouchDispatcher (lua_State* tolua_S) {
 return tolua_CCTouchDispatcher_open(tolua_S);
};
#endif


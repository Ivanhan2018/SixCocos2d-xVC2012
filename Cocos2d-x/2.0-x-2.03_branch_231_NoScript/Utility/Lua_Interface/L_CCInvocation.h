/*
** Lua binding: CCInvocation
** Generated automatically by tolua++-1.0.92 on 04/10/13 03:50:35.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCInvocation_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCInvocation (lua_State* tolua_S)
{
 CCInvocation* self = (CCInvocation*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCControlEvent (lua_State* tolua_S)
{
 CCControlEvent* self = (CCControlEvent*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SEL_CCControlHandler (lua_State* tolua_S)
{
 SEL_CCControlHandler* self = (SEL_CCControlHandler*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCInvocation_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCInvocation");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCControlEvent");
 tolua_usertype(tolua_S,"SEL_CCControlHandler");
}

/* get function: m_action of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_get_CCInvocation_m_action
static int tolua_get_CCInvocation_m_action(lua_State* tolua_S)
{
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_action'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_action,"SEL_CCControlHandler");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_action of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_set_CCInvocation_m_action
static int tolua_set_CCInvocation_m_action(lua_State* tolua_S)
{
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_action'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SEL_CCControlHandler",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAction of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_getAction00
static int tolua_CCInvocation_CCInvocation_getAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCInvocation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCInvocation* self = (const CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAction'", NULL);
#endif
  {
   SEL_CCControlHandler tolua_ret = (SEL_CCControlHandler)  self->getAction();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((SEL_CCControlHandler)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"SEL_CCControlHandler");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(SEL_CCControlHandler));
     tolua_pushusertype(tolua_S,tolua_obj,"SEL_CCControlHandler");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_target of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_get_CCInvocation_m_target_ptr
static int tolua_get_CCInvocation_m_target_ptr(lua_State* tolua_S)
{
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_target'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_target,"CCObject");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_target of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_set_CCInvocation_m_target_ptr
static int tolua_set_CCInvocation_m_target_ptr(lua_State* tolua_S)
{
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_target'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_target = ((CCObject*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTarget of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_getTarget00
static int tolua_CCInvocation_CCInvocation_getTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCInvocation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCInvocation* self = (const CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTarget'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->getTarget();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_controlEvent of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_get_CCInvocation_m_controlEvent
static int tolua_get_CCInvocation_m_controlEvent(lua_State* tolua_S)
{
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_controlEvent'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_controlEvent,"CCControlEvent");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_controlEvent of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_set_CCInvocation_m_controlEvent
static int tolua_set_CCInvocation_m_controlEvent(lua_State* tolua_S)
{
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_controlEvent'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlEvent",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_controlEvent = *((CCControlEvent*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getControlEvent of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_getControlEvent00
static int tolua_CCInvocation_CCInvocation_getControlEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCInvocation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCInvocation* self = (const CCInvocation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getControlEvent'", NULL);
#endif
  {
   CCControlEvent tolua_ret = (CCControlEvent)  self->getControlEvent();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCControlEvent)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCControlEvent");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCControlEvent));
     tolua_pushusertype(tolua_S,tolua_obj,"CCControlEvent");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getControlEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_create00
static int tolua_CCInvocation_CCInvocation_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCInvocation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCControlEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  CCControlEvent controlEvent = *((CCControlEvent*)  tolua_tousertype(tolua_S,4,0));
  {
   CCInvocation* tolua_ret = (CCInvocation*)  CCInvocation::create(target,action,controlEvent);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCInvocation");
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

/* method: new of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_new00
static int tolua_CCInvocation_CCInvocation_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCInvocation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCControlEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  CCControlEvent controlEvent = *((CCControlEvent*)  tolua_tousertype(tolua_S,4,0));
  {
   CCInvocation* tolua_ret = (CCInvocation*)  Mtolua_new((CCInvocation)(target,action,controlEvent));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCInvocation");
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

/* method: new_local of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_new00_local
static int tolua_CCInvocation_CCInvocation_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCInvocation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CCControlHandler",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCControlEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CCControlHandler action = *((SEL_CCControlHandler*)  tolua_tousertype(tolua_S,3,0));
  CCControlEvent controlEvent = *((CCControlEvent*)  tolua_tousertype(tolua_S,4,0));
  {
   CCInvocation* tolua_ret = (CCInvocation*)  Mtolua_new((CCInvocation)(target,action,controlEvent));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCInvocation");
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

/* method: invoke of class  CCInvocation */
#ifndef TOLUA_DISABLE_tolua_CCInvocation_CCInvocation_invoke00
static int tolua_CCInvocation_CCInvocation_invoke00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCInvocation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCInvocation* self = (CCInvocation*)  tolua_tousertype(tolua_S,1,0);
  CCObject* sender = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'invoke'", NULL);
#endif
  {
   self->invoke(sender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'invoke'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCInvocation_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCInvocation_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCInvocation","CCInvocation","CCObject",tolua_collect_CCInvocation);
  #else
  tolua_cclass(tolua_S,"CCInvocation","CCInvocation","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCInvocation");
   tolua_variable(tolua_S,"m_action",tolua_get_CCInvocation_m_action,tolua_set_CCInvocation_m_action);
   tolua_function(tolua_S,"getAction",tolua_CCInvocation_CCInvocation_getAction00);
   tolua_variable(tolua_S,"m_target",tolua_get_CCInvocation_m_target_ptr,tolua_set_CCInvocation_m_target_ptr);
   tolua_function(tolua_S,"getTarget",tolua_CCInvocation_CCInvocation_getTarget00);
   tolua_variable(tolua_S,"m_controlEvent",tolua_get_CCInvocation_m_controlEvent,tolua_set_CCInvocation_m_controlEvent);
   tolua_function(tolua_S,"getControlEvent",tolua_CCInvocation_CCInvocation_getControlEvent00);
   tolua_function(tolua_S,"create",tolua_CCInvocation_CCInvocation_create00);
   tolua_function(tolua_S,"new",tolua_CCInvocation_CCInvocation_new00);
   tolua_function(tolua_S,"new_local",tolua_CCInvocation_CCInvocation_new00_local);
   tolua_function(tolua_S,".call",tolua_CCInvocation_CCInvocation_new00_local);
   tolua_function(tolua_S,"invoke",tolua_CCInvocation_CCInvocation_invoke00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCInvocation (lua_State* tolua_S) {
 return tolua_CCInvocation_open(tolua_S);
};
#endif


/*
** Lua binding: CCEGLView
** Generated automatically by tolua++-1.0.92 on 05/20/13 11:09:57.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCEGLView_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCEGLView (lua_State* tolua_S)
{
 CCEGLView* self = (CCEGLView*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_HWND (lua_State* tolua_S)
{
 HWND* self = (HWND*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCEGLView_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCEGLViewProtocol");
 tolua_usertype(tolua_S,"HWND");
 tolua_usertype(tolua_S,"CCEGLView");
}

/* method: new of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_new00
static int tolua_CCEGLView_CCEGLView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCEGLView* tolua_ret = (CCEGLView*)  Mtolua_new((CCEGLView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEGLView");
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

/* method: new_local of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_new00_local
static int tolua_CCEGLView_CCEGLView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCEGLView* tolua_ret = (CCEGLView*)  Mtolua_new((CCEGLView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEGLView");
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

/* method: delete of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_delete00
static int tolua_CCEGLView_CCEGLView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isOpenGLReady of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_isOpenGLReady00
static int tolua_CCEGLView_CCEGLView_isOpenGLReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpenGLReady'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpenGLReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpenGLReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_end00
static int tolua_CCEGLView_CCEGLView_end00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   self->end();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'end'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFrameSize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_setFrameSize00
static int tolua_CCEGLView_CCEGLView_setFrameSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrameSize'", NULL);
#endif
  {
   self->setFrameSize(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFrameSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWindowIcon of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_setWindowIcon00
static int tolua_CCEGLView_CCEGLView_setWindowIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
  const char* tolua_var_1 = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWindowIcon'", NULL);
#endif
  {
   self->setWindowIcon(tolua_var_1);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWindowIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWindowTitle of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_setWindowTitle00
static int tolua_CCEGLView_CCEGLView_setWindowTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
  const char* tolua_var_2 = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWindowTitle'", NULL);
#endif
  {
   self->setWindowTitle(tolua_var_2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWindowTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHWnd of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_getHWnd00
static int tolua_CCEGLView_CCEGLView_getHWnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHWnd'", NULL);
#endif
  {
   HWND tolua_ret = (HWND)  self->getHWnd();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((HWND)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"HWND");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(HWND));
     tolua_pushusertype(tolua_S,tolua_obj,"HWND");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHWnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_resize00
static int tolua_CCEGLView_CCEGLView_resize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resize'", NULL);
#endif
  {
   self->resize(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: centerWindow of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_centerWindow00
static int tolua_CCEGLView_CCEGLView_centerWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'centerWindow'", NULL);
#endif
  {
   self->centerWindow();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'centerWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedOpenGLView of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_CCEGLView_CCEGLView_sharedOpenGLView00
static int tolua_CCEGLView_CCEGLView_sharedOpenGLView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEGLView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCEGLView* tolua_ret = (CCEGLView*)  CCEGLView::sharedOpenGLView();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEGLView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedOpenGLView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCEGLView_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCEGLView_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCEGLView","CCEGLView","CCEGLViewProtocol",tolua_collect_CCEGLView);
  #else
  tolua_cclass(tolua_S,"CCEGLView","CCEGLView","CCEGLViewProtocol",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCEGLView");
   tolua_function(tolua_S,"new",tolua_CCEGLView_CCEGLView_new00);
   tolua_function(tolua_S,"new_local",tolua_CCEGLView_CCEGLView_new00_local);
   tolua_function(tolua_S,".call",tolua_CCEGLView_CCEGLView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCEGLView_CCEGLView_delete00);
   tolua_function(tolua_S,"isOpenGLReady",tolua_CCEGLView_CCEGLView_isOpenGLReady00);
   tolua_function(tolua_S,"end",tolua_CCEGLView_CCEGLView_end00);
   tolua_function(tolua_S,"setFrameSize",tolua_CCEGLView_CCEGLView_setFrameSize00);
   tolua_function(tolua_S,"setWindowIcon",tolua_CCEGLView_CCEGLView_setWindowIcon00);
   tolua_function(tolua_S,"setWindowTitle",tolua_CCEGLView_CCEGLView_setWindowTitle00);
   tolua_function(tolua_S,"getHWnd",tolua_CCEGLView_CCEGLView_getHWnd00);
   tolua_function(tolua_S,"resize",tolua_CCEGLView_CCEGLView_resize00);
   tolua_function(tolua_S,"centerWindow",tolua_CCEGLView_CCEGLView_centerWindow00);
   tolua_function(tolua_S,"sharedOpenGLView",tolua_CCEGLView_CCEGLView_sharedOpenGLView00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCEGLView (lua_State* tolua_S) {
 return tolua_CCEGLView_open(tolua_S);
};
#endif


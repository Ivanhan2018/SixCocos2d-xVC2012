/*
** Lua binding: CCScrollView
** Generated automatically by tolua++-1.0.92 on 04/24/13 11:22:21.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCScrollView_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CCPoint (lua_State* tolua_S)
//{
// CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_CCScrollViewDelegate (lua_State* tolua_S)
{
 CCScrollViewDelegate* self = (CCScrollViewDelegate*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

//static int tolua_collect_CCSize (lua_State* tolua_S)
//{
// CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_CCScrollView (lua_State* tolua_S)
{
 CCScrollView* self = (CCScrollView*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCScrollView_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCScrollViewDelegate");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"CCScrollView");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCNode");
}

/* method: delete of class  CCScrollViewDelegate */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollViewDelegate_delete00
static int tolua_CCScrollView_CCScrollViewDelegate_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollViewDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollViewDelegate* self = (CCScrollViewDelegate*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollViewDidScroll of class  CCScrollViewDelegate */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollViewDelegate_scrollViewDidScroll00
static int tolua_CCScrollView_CCScrollViewDelegate_scrollViewDidScroll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollViewDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollViewDelegate* self = (CCScrollViewDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCScrollView* view = ((CCScrollView*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollViewDidScroll'", NULL);
#endif
  {
   self->scrollViewDidScroll(view);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollViewDidScroll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollViewDidZoom of class  CCScrollViewDelegate */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollViewDelegate_scrollViewDidZoom00
static int tolua_CCScrollView_CCScrollViewDelegate_scrollViewDidZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollViewDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollViewDelegate* self = (CCScrollViewDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCScrollView* view = ((CCScrollView*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollViewDidZoom'", NULL);
#endif
  {
   self->scrollViewDidZoom(view);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollViewDidZoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_new00
static int tolua_CCScrollView_CCScrollView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScrollView* tolua_ret = (CCScrollView*)  Mtolua_new((CCScrollView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollView");
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

/* method: new_local of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_new00_local
static int tolua_CCScrollView_CCScrollView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScrollView* tolua_ret = (CCScrollView*)  Mtolua_new((CCScrollView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollView");
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

/* method: delete of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_delete00
static int tolua_CCScrollView_CCScrollView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_init00
static int tolua_CCScrollView_CCScrollView_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: registerWithTouchDispatcher of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_registerWithTouchDispatcher00
static int tolua_CCScrollView_CCScrollView_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: viewWithViewSize of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_viewWithViewSize00
static int tolua_CCScrollView_CCScrollView_viewWithViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,3,NULL));
  {
   CCScrollView* tolua_ret = (CCScrollView*)  CCScrollView::viewWithViewSize(size,container);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'viewWithViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_create00
static int tolua_CCScrollView_CCScrollView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,3,NULL));
  {
   CCScrollView* tolua_ret = (CCScrollView*)  CCScrollView::create(size,container);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollView");
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

/* method: node of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_node00
static int tolua_CCScrollView_CCScrollView_node00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScrollView* tolua_ret = (CCScrollView*)  CCScrollView::node();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollView");
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

/* method: create of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_create01
static int tolua_CCScrollView_CCScrollView_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCScrollView* tolua_ret = (CCScrollView*)  CCScrollView::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollView");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCScrollView_CCScrollView_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithViewSize of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_initWithViewSize00
static int tolua_CCScrollView_CCScrollView_initWithViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithViewSize'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithViewSize(size,container);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentOffset of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setContentOffset00
static int tolua_CCScrollView_CCScrollView_setContentOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCPoint offset = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  bool animated = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentOffset'", NULL);
#endif
  {
   self->setContentOffset(offset,animated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentOffset of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getContentOffset00
static int tolua_CCScrollView_CCScrollView_getContentOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentOffset'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getContentOffset();
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
 tolua_error(tolua_S,"#ferror in function 'getContentOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentOffsetInDuration of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setContentOffsetInDuration00
static int tolua_CCScrollView_CCScrollView_setContentOffsetInDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCPoint offset = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  float dt = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentOffsetInDuration'", NULL);
#endif
  {
   self->setContentOffsetInDuration(offset,dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentOffsetInDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomScale of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setZoomScale00
static int tolua_CCScrollView_CCScrollView_setZoomScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomScale'", NULL);
#endif
  {
   self->setZoomScale(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoomScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomScale of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setZoomScale01
static int tolua_CCScrollView_CCScrollView_setZoomScale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
  bool animated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomScale'", NULL);
#endif
  {
   self->setZoomScale(s,animated);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCScrollView_CCScrollView_setZoomScale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZoomScale of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getZoomScale00
static int tolua_CCScrollView_CCScrollView_getZoomScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZoomScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getZoomScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZoomScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomScaleInDuration of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setZoomScaleInDuration00
static int tolua_CCScrollView_CCScrollView_setZoomScaleInDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
  float dt = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomScaleInDuration'", NULL);
#endif
  {
   self->setZoomScaleInDuration(s,dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoomScaleInDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: minContainerOffset of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_minContainerOffset00
static int tolua_CCScrollView_CCScrollView_minContainerOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'minContainerOffset'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->minContainerOffset();
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
 tolua_error(tolua_S,"#ferror in function 'minContainerOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: maxContainerOffset of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_maxContainerOffset00
static int tolua_CCScrollView_CCScrollView_maxContainerOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'maxContainerOffset'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->maxContainerOffset();
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
 tolua_error(tolua_S,"#ferror in function 'maxContainerOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isNodeVisible of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_isNodeVisible00
static int tolua_CCScrollView_CCScrollView_isNodeVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isNodeVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isNodeVisible(node);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isNodeVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_pause00
static int tolua_CCScrollView_CCScrollView_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCObject* sender = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause(sender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_resume00
static int tolua_CCScrollView_CCScrollView_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCObject* sender = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume(sender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDragging of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_isDragging00
static int tolua_CCScrollView_CCScrollView_isDragging00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDragging'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDragging();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDragging'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchMoved of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_isTouchMoved00
static int tolua_CCScrollView_CCScrollView_isTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchMoved'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchMoved();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBounceable of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_isBounceable00
static int tolua_CCScrollView_CCScrollView_isBounceable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBounceable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBounceable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBounceable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBounceable of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setBounceable00
static int tolua_CCScrollView_CCScrollView_setBounceable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool bBounceable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBounceable'", NULL);
#endif
  {
   self->setBounceable(bBounceable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBounceable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getViewSize of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getViewSize00
static int tolua_CCScrollView_CCScrollView_getViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getViewSize();
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
 tolua_error(tolua_S,"#ferror in function 'getViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewSize of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setViewSize00
static int tolua_CCScrollView_CCScrollView_setViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewSize'", NULL);
#endif
  {
   self->setViewSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainer of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getContainer00
static int tolua_CCScrollView_CCScrollView_getContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getContainer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContainer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContainer of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setContainer00
static int tolua_CCScrollView_CCScrollView_setContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pContainer = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContainer'", NULL);
#endif
  {
   self->setContainer(pContainer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContainer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDirection of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getDirection00
static int tolua_CCScrollView_CCScrollView_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDirection'", NULL);
#endif
  {
   CCScrollViewDirection tolua_ret = (CCScrollViewDirection)  self->getDirection();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDirection of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setDirection00
static int tolua_CCScrollView_CCScrollView_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCScrollViewDirection eDirection = ((CCScrollViewDirection) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirection'", NULL);
#endif
  {
   self->setDirection(eDirection);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDelegate of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getDelegate00
static int tolua_CCScrollView_CCScrollView_getDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDelegate'", NULL);
#endif
  {
   CCScrollViewDelegate* tolua_ret = (CCScrollViewDelegate*)  self->getDelegate();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScrollViewDelegate");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setDelegate00
static int tolua_CCScrollView_CCScrollView_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollViewDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCScrollViewDelegate* pDelegate = ((CCScrollViewDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
  {
   self->setDelegate(pDelegate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_ccTouchBegan00
static int tolua_CCScrollView_CCScrollView_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchMoved of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_ccTouchMoved00
static int tolua_CCScrollView_CCScrollView_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchEnded of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_ccTouchEnded00
static int tolua_CCScrollView_CCScrollView_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchCancelled of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_ccTouchCancelled00
static int tolua_CCScrollView_CCScrollView_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setContentSize of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setContentSize00
static int tolua_CCScrollView_CCScrollView_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_getContentSize00
static int tolua_CCScrollView_CCScrollView_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateInset of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_updateInset00
static int tolua_CCScrollView_CCScrollView_updateInset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateInset'", NULL);
#endif
  {
   self->updateInset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateInset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClippingToBounds of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_isClippingToBounds00
static int tolua_CCScrollView_CCScrollView_isClippingToBounds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClippingToBounds'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isClippingToBounds();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClippingToBounds'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setClippingToBounds of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setClippingToBounds00
static int tolua_CCScrollView_CCScrollView_setClippingToBounds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool bClippingToBounds = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClippingToBounds'", NULL);
#endif
  {
   self->setClippingToBounds(bClippingToBounds);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setClippingToBounds'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_visit00
static int tolua_CCScrollView_CCScrollView_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addChild of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_addChild00
static int tolua_CCScrollView_CCScrollView_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder,tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_addChild01
static int tolua_CCScrollView_CCScrollView_addChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCScrollView_CCScrollView_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_addChild02
static int tolua_CCScrollView_CCScrollView_addChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCScrollView_CCScrollView_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnabled of class  CCScrollView */
#ifndef TOLUA_DISABLE_tolua_CCScrollView_CCScrollView_setTouchEnabled00
static int tolua_CCScrollView_CCScrollView_setTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool e = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnabled'", NULL);
#endif
  {
   self->setTouchEnabled(e);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCScrollView_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCScrollView_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"kCCScrollViewDirectionNone",kCCScrollViewDirectionNone);
  tolua_constant(tolua_S,"kCCScrollViewDirectionHorizontal",kCCScrollViewDirectionHorizontal);
  tolua_constant(tolua_S,"kCCScrollViewDirectionVertical",kCCScrollViewDirectionVertical);
  tolua_constant(tolua_S,"kCCScrollViewDirectionBoth",kCCScrollViewDirectionBoth);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCScrollViewDelegate","CCScrollViewDelegate","",tolua_collect_CCScrollViewDelegate);
  #else
  tolua_cclass(tolua_S,"CCScrollViewDelegate","CCScrollViewDelegate","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCScrollViewDelegate");
   tolua_function(tolua_S,"delete",tolua_CCScrollView_CCScrollViewDelegate_delete00);
   tolua_function(tolua_S,"scrollViewDidScroll",tolua_CCScrollView_CCScrollViewDelegate_scrollViewDidScroll00);
   tolua_function(tolua_S,"scrollViewDidZoom",tolua_CCScrollView_CCScrollViewDelegate_scrollViewDidZoom00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCScrollView","CCScrollView","CCLayer",tolua_collect_CCScrollView);
  #else
  tolua_cclass(tolua_S,"CCScrollView","CCScrollView","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCScrollView");
   tolua_function(tolua_S,"new",tolua_CCScrollView_CCScrollView_new00);
   tolua_function(tolua_S,"new_local",tolua_CCScrollView_CCScrollView_new00_local);
   tolua_function(tolua_S,".call",tolua_CCScrollView_CCScrollView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCScrollView_CCScrollView_delete00);
   tolua_function(tolua_S,"init",tolua_CCScrollView_CCScrollView_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_CCScrollView_CCScrollView_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"viewWithViewSize",tolua_CCScrollView_CCScrollView_viewWithViewSize00);
   tolua_function(tolua_S,"create",tolua_CCScrollView_CCScrollView_create00);
   tolua_function(tolua_S,"node",tolua_CCScrollView_CCScrollView_node00);
   tolua_function(tolua_S,"create",tolua_CCScrollView_CCScrollView_create01);
   tolua_function(tolua_S,"initWithViewSize",tolua_CCScrollView_CCScrollView_initWithViewSize00);
   tolua_function(tolua_S,"setContentOffset",tolua_CCScrollView_CCScrollView_setContentOffset00);
   tolua_function(tolua_S,"getContentOffset",tolua_CCScrollView_CCScrollView_getContentOffset00);
   tolua_function(tolua_S,"setContentOffsetInDuration",tolua_CCScrollView_CCScrollView_setContentOffsetInDuration00);
   tolua_function(tolua_S,"setZoomScale",tolua_CCScrollView_CCScrollView_setZoomScale00);
   tolua_function(tolua_S,"setZoomScale",tolua_CCScrollView_CCScrollView_setZoomScale01);
   tolua_function(tolua_S,"getZoomScale",tolua_CCScrollView_CCScrollView_getZoomScale00);
   tolua_function(tolua_S,"setZoomScaleInDuration",tolua_CCScrollView_CCScrollView_setZoomScaleInDuration00);
   tolua_function(tolua_S,"minContainerOffset",tolua_CCScrollView_CCScrollView_minContainerOffset00);
   tolua_function(tolua_S,"maxContainerOffset",tolua_CCScrollView_CCScrollView_maxContainerOffset00);
   tolua_function(tolua_S,"isNodeVisible",tolua_CCScrollView_CCScrollView_isNodeVisible00);
   tolua_function(tolua_S,"pause",tolua_CCScrollView_CCScrollView_pause00);
   tolua_function(tolua_S,"resume",tolua_CCScrollView_CCScrollView_resume00);
   tolua_function(tolua_S,"isDragging",tolua_CCScrollView_CCScrollView_isDragging00);
   tolua_function(tolua_S,"isTouchMoved",tolua_CCScrollView_CCScrollView_isTouchMoved00);
   tolua_function(tolua_S,"isBounceable",tolua_CCScrollView_CCScrollView_isBounceable00);
   tolua_function(tolua_S,"setBounceable",tolua_CCScrollView_CCScrollView_setBounceable00);
   tolua_function(tolua_S,"getViewSize",tolua_CCScrollView_CCScrollView_getViewSize00);
   tolua_function(tolua_S,"setViewSize",tolua_CCScrollView_CCScrollView_setViewSize00);
   tolua_function(tolua_S,"getContainer",tolua_CCScrollView_CCScrollView_getContainer00);
   tolua_function(tolua_S,"setContainer",tolua_CCScrollView_CCScrollView_setContainer00);
   tolua_function(tolua_S,"getDirection",tolua_CCScrollView_CCScrollView_getDirection00);
   tolua_function(tolua_S,"setDirection",tolua_CCScrollView_CCScrollView_setDirection00);
   tolua_function(tolua_S,"getDelegate",tolua_CCScrollView_CCScrollView_getDelegate00);
   tolua_function(tolua_S,"setDelegate",tolua_CCScrollView_CCScrollView_setDelegate00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_CCScrollView_CCScrollView_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_CCScrollView_CCScrollView_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_CCScrollView_CCScrollView_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_CCScrollView_CCScrollView_ccTouchCancelled00);
   tolua_function(tolua_S,"setContentSize",tolua_CCScrollView_CCScrollView_setContentSize00);
   tolua_function(tolua_S,"getContentSize",tolua_CCScrollView_CCScrollView_getContentSize00);
   tolua_function(tolua_S,"updateInset",tolua_CCScrollView_CCScrollView_updateInset00);
   tolua_function(tolua_S,"isClippingToBounds",tolua_CCScrollView_CCScrollView_isClippingToBounds00);
   tolua_function(tolua_S,"setClippingToBounds",tolua_CCScrollView_CCScrollView_setClippingToBounds00);
   tolua_function(tolua_S,"visit",tolua_CCScrollView_CCScrollView_visit00);
   tolua_function(tolua_S,"addChild",tolua_CCScrollView_CCScrollView_addChild00);
   tolua_function(tolua_S,"addChild",tolua_CCScrollView_CCScrollView_addChild01);
   tolua_function(tolua_S,"addChild",tolua_CCScrollView_CCScrollView_addChild02);
   tolua_function(tolua_S,"setTouchEnabled",tolua_CCScrollView_CCScrollView_setTouchEnabled00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCScrollView (lua_State* tolua_S) {
 return tolua_CCScrollView_open(tolua_S);
};
#endif


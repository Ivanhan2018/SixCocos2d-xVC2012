/*
** Lua binding: SIX_ScrollBar
** Generated automatically by tolua++-1.0.92 on 05/15/13 19:11:03.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_ScrollBar_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
 CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

//static int tolua_collect_CCRect (lua_State* tolua_S)
//{
// CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_SIX_ScrollBar (lua_State* tolua_S)
{
 SIX_ScrollBar* self = (SIX_ScrollBar*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_ScrollBar_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"SIX_ScrollBar");
}

/* method: new of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_new00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_ScrollBar* tolua_ret = (SIX_ScrollBar*)  Mtolua_new((SIX_ScrollBar)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ScrollBar");
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

/* method: new_local of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_new00_local
static int tolua_SIX_ScrollBar_SIX_ScrollBar_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_ScrollBar* tolua_ret = (SIX_ScrollBar*)  Mtolua_new((SIX_ScrollBar)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ScrollBar");
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

/* method: delete of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_delete00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_create00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCRect",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"CCRect",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,7,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,8,&tolua_err) || !tolua_isusertype(tolua_S,8,"CCRect",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,9,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,10,&tolua_err) || !tolua_isusertype(tolua_S,10,"CCRect",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* backgroundFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect backgroundRect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCRect backgroundDstRect = *((CCRect*)  tolua_tousertype(tolua_S,4,0));
  const char* btnLTFile = ((const char*)  tolua_tostring(tolua_S,5,0));
  CCRect btnLTRect = *((CCRect*)  tolua_tousertype(tolua_S,6,0));
  const char* btnRBFile = ((const char*)  tolua_tostring(tolua_S,7,0));
  CCRect btnRBRect = *((CCRect*)  tolua_tousertype(tolua_S,8,0));
  const char* thumbFile = ((const char*)  tolua_tostring(tolua_S,9,0));
  CCRect thumbRect = *((CCRect*)  tolua_tousertype(tolua_S,10,0));
  bool bHorizontal = ((bool)  tolua_toboolean(tolua_S,11,true));
  {
   SIX_ScrollBar* tolua_ret = (SIX_ScrollBar*)  SIX_ScrollBar::create(backgroundFile,backgroundRect,backgroundDstRect,btnLTFile,btnLTRect,btnRBFile,btnRBRect,thumbFile,thumbRect,bHorizontal);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ScrollBar");
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

/* method: create of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_create01
static int tolua_SIX_ScrollBar_SIX_ScrollBar_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* background = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  CCRect backgroundDstRect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCSprite* btnLT = ((CCSprite*)  tolua_tousertype(tolua_S,4,0));
  CCSprite* btnRB = ((CCSprite*)  tolua_tousertype(tolua_S,5,0));
  CCScale9Sprite* thumb = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,6,0));
  bool bHorizontal = ((bool)  tolua_toboolean(tolua_S,7,true));
  {
   SIX_ScrollBar* tolua_ret = (SIX_ScrollBar*)  SIX_ScrollBar::create(background,backgroundDstRect,btnLT,btnRB,thumb,bHorizontal);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ScrollBar");
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_ScrollBar_SIX_ScrollBar_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithSprites of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_initWithSprites00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_initWithSprites00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* background = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  CCRect backgroundDstRect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCSprite* btnLT = ((CCSprite*)  tolua_tousertype(tolua_S,4,0));
  CCSprite* btnRB = ((CCSprite*)  tolua_tousertype(tolua_S,5,0));
  CCScale9Sprite* thumb = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSprites'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSprites(background,backgroundDstRect,btnLT,btnRB,thumb);
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

/* method: isTouchInside of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_isTouchInside00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_isTouchInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: locationFromTouch of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_locationFromTouch00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_locationFromTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: needsLayout of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_needsLayout00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_needsLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setBackground of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setBackground00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setBackground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* background = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackground'", NULL);
#endif
  {
   self->setBackground(background);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackground of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getBackground00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getBackground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_ScrollBar* self = (const SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackground'", NULL);
#endif
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  self->getBackground();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBtnLT of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setBtnLT00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setBtnLT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* btnLT = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBtnLT'", NULL);
#endif
  {
   self->setBtnLT(btnLT);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBtnLT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBtnLT of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getBtnLT00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getBtnLT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_ScrollBar* self = (const SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBtnLT'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getBtnLT();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBtnLT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBtnRB of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setBtnRB00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setBtnRB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* btnRB = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBtnRB'", NULL);
#endif
  {
   self->setBtnRB(btnRB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBtnRB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBtnRB of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getBtnRB00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getBtnRB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_ScrollBar* self = (const SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBtnRB'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getBtnRB();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBtnRB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setThumb of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setThumb00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setThumb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* thumb = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setThumb'", NULL);
#endif
  {
   self->setThumb(thumb);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setThumb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getThumb of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getThumb00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getThumb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SIX_ScrollBar* self = (const SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getThumb'", NULL);
#endif
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  self->getThumb();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getThumb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHorizontal of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setHorizontal00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setHorizontal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  bool bHorizontal = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHorizontal'", NULL);
#endif
  {
   self->setHorizontal(bHorizontal);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHorizontal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHorizontal of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getHorizontal00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getHorizontal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHorizontal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getHorizontal();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHorizontal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(value);
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

/* method: getValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setMinimumValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setMinimumValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setMinimumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float minimumValue = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinimumValue'", NULL);
#endif
  {
   self->setMinimumValue(minimumValue);
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

/* method: getMinimumValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getMinimumValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getMinimumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setMaximumValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setMaximumValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setMaximumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float maximumValue = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaximumValue'", NULL);
#endif
  {
   self->setMaximumValue(maximumValue);
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

/* method: getMaximumValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getMaximumValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getMaximumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setMinimumAllowedValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setMinimumAllowedValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setMinimumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float minimumAllowedValue = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinimumAllowedValue'", NULL);
#endif
  {
   self->setMinimumAllowedValue(minimumAllowedValue);
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

/* method: getMinimumAllowedValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getMinimumAllowedValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getMinimumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setMaximumAllowedValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setMaximumAllowedValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setMaximumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float maximumAllowedValue = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaximumAllowedValue'", NULL);
#endif
  {
   self->setMaximumAllowedValue(maximumAllowedValue);
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

/* method: getMaximumAllowedValue of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getMaximumAllowedValue00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getMaximumAllowedValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setThumbRect of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_setThumbRect00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_setThumbRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  CCRect rc = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setThumbRect'", NULL);
#endif
  {
   self->setThumbRect(rc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setThumbRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getThumbRect of class  SIX_ScrollBar */
#ifndef TOLUA_DISABLE_tolua_SIX_ScrollBar_SIX_ScrollBar_getThumbRect00
static int tolua_SIX_ScrollBar_SIX_ScrollBar_getThumbRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ScrollBar* self = (SIX_ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getThumbRect'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getThumbRect();
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
 tolua_error(tolua_S,"#ferror in function 'getThumbRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_ScrollBar_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_ScrollBar_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_ScrollBar","SIX_ScrollBar","CCControl",tolua_collect_SIX_ScrollBar);
  #else
  tolua_cclass(tolua_S,"SIX_ScrollBar","SIX_ScrollBar","CCControl",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_ScrollBar");
   tolua_function(tolua_S,"new",tolua_SIX_ScrollBar_SIX_ScrollBar_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_ScrollBar_SIX_ScrollBar_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_ScrollBar_SIX_ScrollBar_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_ScrollBar_SIX_ScrollBar_delete00);
   tolua_function(tolua_S,"create",tolua_SIX_ScrollBar_SIX_ScrollBar_create00);
   tolua_function(tolua_S,"create",tolua_SIX_ScrollBar_SIX_ScrollBar_create01);
   tolua_function(tolua_S,"initWithSprites",tolua_SIX_ScrollBar_SIX_ScrollBar_initWithSprites00);
   tolua_function(tolua_S,"isTouchInside",tolua_SIX_ScrollBar_SIX_ScrollBar_isTouchInside00);
   tolua_function(tolua_S,"locationFromTouch",tolua_SIX_ScrollBar_SIX_ScrollBar_locationFromTouch00);
   tolua_function(tolua_S,"needsLayout",tolua_SIX_ScrollBar_SIX_ScrollBar_needsLayout00);
   tolua_function(tolua_S,"setBackground",tolua_SIX_ScrollBar_SIX_ScrollBar_setBackground00);
   tolua_function(tolua_S,"getBackground",tolua_SIX_ScrollBar_SIX_ScrollBar_getBackground00);
   tolua_function(tolua_S,"setBtnLT",tolua_SIX_ScrollBar_SIX_ScrollBar_setBtnLT00);
   tolua_function(tolua_S,"getBtnLT",tolua_SIX_ScrollBar_SIX_ScrollBar_getBtnLT00);
   tolua_function(tolua_S,"setBtnRB",tolua_SIX_ScrollBar_SIX_ScrollBar_setBtnRB00);
   tolua_function(tolua_S,"getBtnRB",tolua_SIX_ScrollBar_SIX_ScrollBar_getBtnRB00);
   tolua_function(tolua_S,"setThumb",tolua_SIX_ScrollBar_SIX_ScrollBar_setThumb00);
   tolua_function(tolua_S,"getThumb",tolua_SIX_ScrollBar_SIX_ScrollBar_getThumb00);
   tolua_function(tolua_S,"setHorizontal",tolua_SIX_ScrollBar_SIX_ScrollBar_setHorizontal00);
   tolua_function(tolua_S,"getHorizontal",tolua_SIX_ScrollBar_SIX_ScrollBar_getHorizontal00);
   tolua_function(tolua_S,"setValue",tolua_SIX_ScrollBar_SIX_ScrollBar_setValue00);
   tolua_function(tolua_S,"getValue",tolua_SIX_ScrollBar_SIX_ScrollBar_getValue00);
   tolua_function(tolua_S,"setMinimumValue",tolua_SIX_ScrollBar_SIX_ScrollBar_setMinimumValue00);
   tolua_function(tolua_S,"getMinimumValue",tolua_SIX_ScrollBar_SIX_ScrollBar_getMinimumValue00);
   tolua_function(tolua_S,"setMaximumValue",tolua_SIX_ScrollBar_SIX_ScrollBar_setMaximumValue00);
   tolua_function(tolua_S,"getMaximumValue",tolua_SIX_ScrollBar_SIX_ScrollBar_getMaximumValue00);
   tolua_function(tolua_S,"setMinimumAllowedValue",tolua_SIX_ScrollBar_SIX_ScrollBar_setMinimumAllowedValue00);
   tolua_function(tolua_S,"getMinimumAllowedValue",tolua_SIX_ScrollBar_SIX_ScrollBar_getMinimumAllowedValue00);
   tolua_function(tolua_S,"setMaximumAllowedValue",tolua_SIX_ScrollBar_SIX_ScrollBar_setMaximumAllowedValue00);
   tolua_function(tolua_S,"getMaximumAllowedValue",tolua_SIX_ScrollBar_SIX_ScrollBar_getMaximumAllowedValue00);
   tolua_function(tolua_S,"setThumbRect",tolua_SIX_ScrollBar_SIX_ScrollBar_setThumbRect00);
   tolua_function(tolua_S,"getThumbRect",tolua_SIX_ScrollBar_SIX_ScrollBar_getThumbRect00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_ScrollBar (lua_State* tolua_S) {
 return tolua_SIX_ScrollBar_open(tolua_S);
};
#endif


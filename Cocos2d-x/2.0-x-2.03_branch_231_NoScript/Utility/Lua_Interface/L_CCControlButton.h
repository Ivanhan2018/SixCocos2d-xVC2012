/*
** Lua binding: CCControlButton
** Generated automatically by tolua++-1.0.92 on 04/09/13 18:51:14.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCControlButton_open (lua_State* tolua_S);


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

//static int tolua_collect_CCSize (lua_State* tolua_S)
//{
// CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}
//
//static int tolua_collect_ccColor3B (lua_State* tolua_S)
//{
// ccColor3B* self = (ccColor3B*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_CCControlButton (lua_State* tolua_S)
{
 CCControlButton* self = (CCControlButton*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCControlButton_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"GLubyte");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCString");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"CCControlButton");
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCSpriteFrame");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCControlState");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCTouch");
}

/* method: new of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_new00
static int tolua_CCControlButton_CCControlButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControlButton* tolua_ret = (CCControlButton*)  Mtolua_new((CCControlButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
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

/* method: new_local of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_new00_local
static int tolua_CCControlButton_CCControlButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControlButton* tolua_ret = (CCControlButton*)  Mtolua_new((CCControlButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
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

/* method: delete of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_delete00
static int tolua_CCControlButton_CCControlButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: needsLayout of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_needsLayout00
static int tolua_CCControlButton_CCControlButton_needsLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setEnabled of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setEnabled00
static int tolua_CCControlButton_CCControlButton_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSelected of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setSelected00
static int tolua_CCControlButton_CCControlButton_setSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSelected'", NULL);
#endif
  {
   self->setSelected(enabled);
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

/* method: setHighlighted of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setHighlighted00
static int tolua_CCControlButton_CCControlButton_setHighlighted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHighlighted'", NULL);
#endif
  {
   self->setHighlighted(enabled);
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

/* method: getCurrentTitle of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getCurrentTitle00
static int tolua_CCControlButton_CCControlButton_getCurrentTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentTitle'", NULL);
#endif
  {
   CCString* tolua_ret = (CCString*)  self->getCurrentTitle();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCString");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentTitleColor of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getCurrentTitleColor00
static int tolua_CCControlButton_CCControlButton_getCurrentTitleColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlButton* self = (const CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentTitleColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getCurrentTitleColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentTitleColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doesAdjustBackgroundImage of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_doesAdjustBackgroundImage00
static int tolua_CCControlButton_CCControlButton_doesAdjustBackgroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doesAdjustBackgroundImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->doesAdjustBackgroundImage();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doesAdjustBackgroundImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAdjustBackgroundImage of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setAdjustBackgroundImage00
static int tolua_CCControlButton_CCControlButton_setAdjustBackgroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  bool adjustBackgroundImage = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAdjustBackgroundImage'", NULL);
#endif
  {
   self->setAdjustBackgroundImage(adjustBackgroundImage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAdjustBackgroundImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_doesAdjustBackgroundImage of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_get_CCControlButton_m_doesAdjustBackgroundImage
static int tolua_get_CCControlButton_m_doesAdjustBackgroundImage(lua_State* tolua_S)
{
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_doesAdjustBackgroundImage'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_doesAdjustBackgroundImage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_doesAdjustBackgroundImage of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_set_CCControlButton_m_doesAdjustBackgroundImage
static int tolua_set_CCControlButton_m_doesAdjustBackgroundImage(lua_State* tolua_S)
{
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_doesAdjustBackgroundImage'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_doesAdjustBackgroundImage = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleLabel of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleLabel00
static int tolua_CCControlButton_CCControlButton_getTitleLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleLabel'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getTitleLabel();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleLabel of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleLabel00
static int tolua_CCControlButton_CCControlButton_setTitleLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCNode* var = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleLabel'", NULL);
#endif
  {
   self->setTitleLabel(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundSprite of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getBackgroundSprite00
static int tolua_CCControlButton_CCControlButton_getBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundSprite'", NULL);
#endif
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  self->getBackgroundSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
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

/* method: setBackgroundSprite of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setBackgroundSprite00
static int tolua_CCControlButton_CCControlButton_setBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* var = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
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

/* method: getPreferredSize of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getPreferredSize00
static int tolua_CCControlButton_CCControlButton_getPreferredSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPreferredSize of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setPreferredSize00
static int tolua_CCControlButton_CCControlButton_setPreferredSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getZoomOnTouchDown of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getZoomOnTouchDown00
static int tolua_CCControlButton_CCControlButton_getZoomOnTouchDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZoomOnTouchDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getZoomOnTouchDown();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZoomOnTouchDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomOnTouchDown of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setZoomOnTouchDown00
static int tolua_CCControlButton_CCControlButton_setZoomOnTouchDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  bool var = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomOnTouchDown'", NULL);
#endif
  {
   self->setZoomOnTouchDown(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoomOnTouchDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLabelAnchorPoint of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getLabelAnchorPoint00
static int tolua_CCControlButton_CCControlButton_getLabelAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLabelAnchorPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getLabelAnchorPoint();
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
 tolua_error(tolua_S,"#ferror in function 'getLabelAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLabelAnchorPoint of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setLabelAnchorPoint00
static int tolua_CCControlButton_CCControlButton_setLabelAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCPoint var = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLabelAnchorPoint'", NULL);
#endif
  {
   self->setLabelAnchorPoint(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLabelAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getOpacity00
static int tolua_CCControlButton_CCControlButton_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setOpacity of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setOpacity00
static int tolua_CCControlButton_CCControlButton_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isPushed of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_isPushed00
static int tolua_CCControlButton_CCControlButton_isPushed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPushed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPushed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPushed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleDispatchTable00
static int tolua_CCControlButton_CCControlButton_getTitleDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleDispatchTable'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->getTitleDispatchTable();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleDispatchTable00
static int tolua_CCControlButton_CCControlButton_setTitleDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCDictionary* var = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleDispatchTable'", NULL);
#endif
  {
   self->setTitleDispatchTable(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleColorDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleColorDispatchTable00
static int tolua_CCControlButton_CCControlButton_getTitleColorDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleColorDispatchTable'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->getTitleColorDispatchTable();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleColorDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleColorDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleColorDispatchTable00
static int tolua_CCControlButton_CCControlButton_setTitleColorDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCDictionary* var = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleColorDispatchTable'", NULL);
#endif
  {
   self->setTitleColorDispatchTable(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleColorDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleLabelDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleLabelDispatchTable00
static int tolua_CCControlButton_CCControlButton_getTitleLabelDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleLabelDispatchTable'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->getTitleLabelDispatchTable();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleLabelDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleLabelDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleLabelDispatchTable00
static int tolua_CCControlButton_CCControlButton_setTitleLabelDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCDictionary* var = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleLabelDispatchTable'", NULL);
#endif
  {
   self->setTitleLabelDispatchTable(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleLabelDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundSpriteDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getBackgroundSpriteDispatchTable00
static int tolua_CCControlButton_CCControlButton_getBackgroundSpriteDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundSpriteDispatchTable'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->getBackgroundSpriteDispatchTable();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundSpriteDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundSpriteDispatchTable of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setBackgroundSpriteDispatchTable00
static int tolua_CCControlButton_CCControlButton_setBackgroundSpriteDispatchTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCDictionary* var = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundSpriteDispatchTable'", NULL);
#endif
  {
   self->setBackgroundSpriteDispatchTable(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundSpriteDispatchTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVerticalMargin of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getVerticalMargin00
static int tolua_CCControlButton_CCControlButton_getVerticalMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCControlButton* self = (const CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVerticalMargin'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getVerticalMargin();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVerticalMargin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVerticalMargin of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getVerticalMargin01
static int tolua_CCControlButton_CCControlButton_getVerticalMargin01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CCControlButton* self = (const CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVerticalMargin'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getVerticalMargin();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCControlButton_CCControlButton_getVerticalMargin00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMargins of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setMargins00
static int tolua_CCControlButton_CCControlButton_setMargins00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  int marginH = ((int)  tolua_tonumber(tolua_S,2,0));
  int marginV = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMargins'", NULL);
#endif
  {
   self->setMargins(marginH,marginV);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMargins'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_init00
static int tolua_CCControlButton_CCControlButton_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: initWithLabelAndBackgroundSprite of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_initWithLabelAndBackgroundSprite00
static int tolua_CCControlButton_CCControlButton_initWithLabelAndBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCNode* label = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* backgroundSprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithLabelAndBackgroundSprite'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithLabelAndBackgroundSprite(label,backgroundSprite);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithLabelAndBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: buttonWithLabelAndBackgroundSprite of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_buttonWithLabelAndBackgroundSprite00
static int tolua_CCControlButton_CCControlButton_buttonWithLabelAndBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* label = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* backgroundSprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::buttonWithLabelAndBackgroundSprite(label,backgroundSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'buttonWithLabelAndBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_create00
static int tolua_CCControlButton_CCControlButton_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* label = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* backgroundSprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create(label,backgroundSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
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

/* method: initWithTitleAndFontNameAndFontSize of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_initWithTitleAndFontNameAndFontSize00
static int tolua_CCControlButton_CCControlButton_initWithTitleAndFontNameAndFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  std::string title = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithTitleAndFontNameAndFontSize'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithTitleAndFontNameAndFontSize(title,fontName,fontSize);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithTitleAndFontNameAndFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: buttonWithTitleAndFontNameAndFontSize of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_buttonWithTitleAndFontNameAndFontSize00
static int tolua_CCControlButton_CCControlButton_buttonWithTitleAndFontNameAndFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string title = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::buttonWithTitleAndFontNameAndFontSize(title,fontName,fontSize);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'buttonWithTitleAndFontNameAndFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_create01
static int tolua_CCControlButton_CCControlButton_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  std::string title = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create(title,fontName,fontSize);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCControlButton_CCControlButton_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithBackgroundSprite of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_initWithBackgroundSprite00
static int tolua_CCControlButton_CCControlButton_initWithBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* sprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithBackgroundSprite'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithBackgroundSprite(sprite);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: buttonWithBackgroundSprite of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_buttonWithBackgroundSprite00
static int tolua_CCControlButton_CCControlButton_buttonWithBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* sprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::buttonWithBackgroundSprite(sprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'buttonWithBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_create02
static int tolua_CCControlButton_CCControlButton_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* sprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create(sprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCControlButton_CCControlButton_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_ccTouchBegan00
static int tolua_CCControlButton_CCControlButton_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchMoved of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_ccTouchMoved00
static int tolua_CCControlButton_CCControlButton_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchEnded of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_ccTouchEnded00
static int tolua_CCControlButton_CCControlButton_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchCancelled of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_ccTouchCancelled00
static int tolua_CCControlButton_CCControlButton_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTitleForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleForState00
static int tolua_CCControlButton_CCControlButton_getTitleForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleForState'", NULL);
#endif
  {
   CCString* tolua_ret = (CCString*)  self->getTitleForState(state);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCString");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleForState00
static int tolua_CCControlButton_CCControlButton_setTitleForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCString* title = ((CCString*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleForState'", NULL);
#endif
  {
   self->setTitleForState(title,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleColorForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleColorForState00
static int tolua_CCControlButton_CCControlButton_getTitleColorForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleColorForState'", NULL);
#endif
  {
   const ccColor3B tolua_ret = (const ccColor3B)  self->getTitleColorForState(state);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor3B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const ccColor3B));
     tolua_pushusertype(tolua_S,tolua_obj,"const ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleColorForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleColorForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleColorForState00
static int tolua_CCControlButton_CCControlButton_setTitleColorForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleColorForState'", NULL);
#endif
  {
   self->setTitleColorForState(color,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleColorForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleLabelForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleLabelForState00
static int tolua_CCControlButton_CCControlButton_getTitleLabelForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleLabelForState'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getTitleLabelForState(state);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleLabelForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleLabelForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleLabelForState00
static int tolua_CCControlButton_CCControlButton_setTitleLabelForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCNode* label = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleLabelForState'", NULL);
#endif
  {
   self->setTitleLabelForState(label,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleLabelForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleTTFForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleTTFForState00
static int tolua_CCControlButton_CCControlButton_setTitleTTFForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* fntFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleTTFForState'", NULL);
#endif
  {
   self->setTitleTTFForState(fntFile,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleTTFForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleTTFForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleTTFForState00
static int tolua_CCControlButton_CCControlButton_getTitleTTFForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleTTFForState'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getTitleTTFForState(state);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleTTFForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleTTFSizeForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleTTFSizeForState00
static int tolua_CCControlButton_CCControlButton_setTitleTTFSizeForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleTTFSizeForState'", NULL);
#endif
  {
   self->setTitleTTFSizeForState(size,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleTTFSizeForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleTTFSizeForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleTTFSizeForState00
static int tolua_CCControlButton_CCControlButton_getTitleTTFSizeForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleTTFSizeForState'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTitleTTFSizeForState(state);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleTTFSizeForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleBMFontForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setTitleBMFontForState00
static int tolua_CCControlButton_CCControlButton_setTitleBMFontForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* fntFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleBMFontForState'", NULL);
#endif
  {
   self->setTitleBMFontForState(fntFile,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleBMFontForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleBMFontForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getTitleBMFontForState00
static int tolua_CCControlButton_CCControlButton_getTitleBMFontForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleBMFontForState'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getTitleBMFontForState(state);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleBMFontForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundSpriteForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getBackgroundSpriteForState00
static int tolua_CCControlButton_CCControlButton_getBackgroundSpriteForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundSpriteForState'", NULL);
#endif
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  self->getBackgroundSpriteForState(state);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundSpriteForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundSpriteForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setBackgroundSpriteForState00
static int tolua_CCControlButton_CCControlButton_setBackgroundSpriteForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) /*|| !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)*/) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* sprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = ((CCControlState)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundSpriteForState'", NULL);
#endif
  {
   self->setBackgroundSpriteForState(sprite,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundSpriteForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundSpriteFrameForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setBackgroundSpriteFrameForState00
static int tolua_CCControlButton_CCControlButton_setBackgroundSpriteFrameForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = *((CCControlState*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundSpriteFrameForState'", NULL);
#endif
  {
   self->setBackgroundSpriteFrameForState(spriteFrame,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundSpriteFrameForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZoomFactor of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getZoomFactor00
static int tolua_CCControlButton_CCControlButton_getZoomFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZoomFactor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getZoomFactor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZoomFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomFactor of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setZoomFactor00
static int tolua_CCControlButton_CCControlButton_setZoomFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  float ZoomFactor = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomFactor'", NULL);
#endif
  {
   self->setZoomFactor(ZoomFactor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoomFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZoomStep of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_getZoomStep00
static int tolua_CCControlButton_CCControlButton_getZoomStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZoomStep'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getZoomStep();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZoomStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomStep of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_setZoomStep00
static int tolua_CCControlButton_CCControlButton_setZoomStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  float ZoomStep = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomStep'", NULL);
#endif
  {
   self->setZoomStep(ZoomStep);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoomStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_ZoomFactor of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_get_CCControlButton_m_ZoomFactor
static int tolua_get_CCControlButton_m_ZoomFactor(lua_State* tolua_S)
{
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_ZoomFactor'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_ZoomFactor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_ZoomFactor of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_set_CCControlButton_m_ZoomFactor
static int tolua_set_CCControlButton_m_ZoomFactor(lua_State* tolua_S)
{
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_ZoomFactor'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_ZoomFactor = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_ZoomStep of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_get_CCControlButton_m_ZoomStep
static int tolua_get_CCControlButton_m_ZoomStep(lua_State* tolua_S)
{
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_ZoomStep'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_ZoomStep);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_ZoomStep of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_set_CCControlButton_m_ZoomStep
static int tolua_set_CCControlButton_m_ZoomStep(lua_State* tolua_S)
{
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_ZoomStep'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_ZoomStep = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: node of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_node00
static int tolua_CCControlButton_CCControlButton_node00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::node();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
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

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_CCControlButton_CCControlButton_create03
static int tolua_CCControlButton_CCControlButton_create03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCControlButton_CCControlButton_create02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCControlButton_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCControlButton_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCControlButton","CCControlButton","CCControl",tolua_collect_CCControlButton);
  #else
  tolua_cclass(tolua_S,"CCControlButton","CCControlButton","CCControl",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCControlButton");
   tolua_function(tolua_S,"new",tolua_CCControlButton_CCControlButton_new00);
   tolua_function(tolua_S,"new_local",tolua_CCControlButton_CCControlButton_new00_local);
   tolua_function(tolua_S,".call",tolua_CCControlButton_CCControlButton_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCControlButton_CCControlButton_delete00);
   tolua_function(tolua_S,"needsLayout",tolua_CCControlButton_CCControlButton_needsLayout00);
   tolua_function(tolua_S,"setEnabled",tolua_CCControlButton_CCControlButton_setEnabled00);
   tolua_function(tolua_S,"setSelected",tolua_CCControlButton_CCControlButton_setSelected00);
   tolua_function(tolua_S,"setHighlighted",tolua_CCControlButton_CCControlButton_setHighlighted00);
   tolua_function(tolua_S,"getCurrentTitle",tolua_CCControlButton_CCControlButton_getCurrentTitle00);
   tolua_function(tolua_S,"getCurrentTitleColor",tolua_CCControlButton_CCControlButton_getCurrentTitleColor00);
   tolua_function(tolua_S,"doesAdjustBackgroundImage",tolua_CCControlButton_CCControlButton_doesAdjustBackgroundImage00);
   tolua_function(tolua_S,"setAdjustBackgroundImage",tolua_CCControlButton_CCControlButton_setAdjustBackgroundImage00);
   tolua_variable(tolua_S,"m_doesAdjustBackgroundImage",tolua_get_CCControlButton_m_doesAdjustBackgroundImage,tolua_set_CCControlButton_m_doesAdjustBackgroundImage);
   tolua_function(tolua_S,"getTitleLabel",tolua_CCControlButton_CCControlButton_getTitleLabel00);
   tolua_function(tolua_S,"setTitleLabel",tolua_CCControlButton_CCControlButton_setTitleLabel00);
   tolua_function(tolua_S,"getBackgroundSprite",tolua_CCControlButton_CCControlButton_getBackgroundSprite00);
   tolua_function(tolua_S,"setBackgroundSprite",tolua_CCControlButton_CCControlButton_setBackgroundSprite00);
   tolua_function(tolua_S,"getPreferredSize",tolua_CCControlButton_CCControlButton_getPreferredSize00);
   tolua_function(tolua_S,"setPreferredSize",tolua_CCControlButton_CCControlButton_setPreferredSize00);
   tolua_function(tolua_S,"getZoomOnTouchDown",tolua_CCControlButton_CCControlButton_getZoomOnTouchDown00);
   tolua_function(tolua_S,"setZoomOnTouchDown",tolua_CCControlButton_CCControlButton_setZoomOnTouchDown00);
   tolua_function(tolua_S,"getLabelAnchorPoint",tolua_CCControlButton_CCControlButton_getLabelAnchorPoint00);
   tolua_function(tolua_S,"setLabelAnchorPoint",tolua_CCControlButton_CCControlButton_setLabelAnchorPoint00);
   tolua_function(tolua_S,"getOpacity",tolua_CCControlButton_CCControlButton_getOpacity00);
   tolua_function(tolua_S,"setOpacity",tolua_CCControlButton_CCControlButton_setOpacity00);
   tolua_function(tolua_S,"isPushed",tolua_CCControlButton_CCControlButton_isPushed00);
   tolua_function(tolua_S,"getTitleDispatchTable",tolua_CCControlButton_CCControlButton_getTitleDispatchTable00);
   tolua_function(tolua_S,"setTitleDispatchTable",tolua_CCControlButton_CCControlButton_setTitleDispatchTable00);
   tolua_function(tolua_S,"getTitleColorDispatchTable",tolua_CCControlButton_CCControlButton_getTitleColorDispatchTable00);
   tolua_function(tolua_S,"setTitleColorDispatchTable",tolua_CCControlButton_CCControlButton_setTitleColorDispatchTable00);
   tolua_function(tolua_S,"getTitleLabelDispatchTable",tolua_CCControlButton_CCControlButton_getTitleLabelDispatchTable00);
   tolua_function(tolua_S,"setTitleLabelDispatchTable",tolua_CCControlButton_CCControlButton_setTitleLabelDispatchTable00);
   tolua_function(tolua_S,"getBackgroundSpriteDispatchTable",tolua_CCControlButton_CCControlButton_getBackgroundSpriteDispatchTable00);
   tolua_function(tolua_S,"setBackgroundSpriteDispatchTable",tolua_CCControlButton_CCControlButton_setBackgroundSpriteDispatchTable00);
   tolua_function(tolua_S,"getVerticalMargin",tolua_CCControlButton_CCControlButton_getVerticalMargin00);
   tolua_function(tolua_S,"getVerticalMargin",tolua_CCControlButton_CCControlButton_getVerticalMargin01);
   tolua_function(tolua_S,"setMargins",tolua_CCControlButton_CCControlButton_setMargins00);
   tolua_function(tolua_S,"init",tolua_CCControlButton_CCControlButton_init00);
   tolua_function(tolua_S,"initWithLabelAndBackgroundSprite",tolua_CCControlButton_CCControlButton_initWithLabelAndBackgroundSprite00);
   tolua_function(tolua_S,"buttonWithLabelAndBackgroundSprite",tolua_CCControlButton_CCControlButton_buttonWithLabelAndBackgroundSprite00);
   tolua_function(tolua_S,"create",tolua_CCControlButton_CCControlButton_create00);
   tolua_function(tolua_S,"initWithTitleAndFontNameAndFontSize",tolua_CCControlButton_CCControlButton_initWithTitleAndFontNameAndFontSize00);
   tolua_function(tolua_S,"buttonWithTitleAndFontNameAndFontSize",tolua_CCControlButton_CCControlButton_buttonWithTitleAndFontNameAndFontSize00);
   tolua_function(tolua_S,"create",tolua_CCControlButton_CCControlButton_create01);
   tolua_function(tolua_S,"initWithBackgroundSprite",tolua_CCControlButton_CCControlButton_initWithBackgroundSprite00);
   tolua_function(tolua_S,"buttonWithBackgroundSprite",tolua_CCControlButton_CCControlButton_buttonWithBackgroundSprite00);
   tolua_function(tolua_S,"create",tolua_CCControlButton_CCControlButton_create02);
   tolua_function(tolua_S,"ccTouchBegan",tolua_CCControlButton_CCControlButton_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_CCControlButton_CCControlButton_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_CCControlButton_CCControlButton_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_CCControlButton_CCControlButton_ccTouchCancelled00);
   tolua_function(tolua_S,"getTitleForState",tolua_CCControlButton_CCControlButton_getTitleForState00);
   tolua_function(tolua_S,"setTitleForState",tolua_CCControlButton_CCControlButton_setTitleForState00);
   tolua_function(tolua_S,"getTitleColorForState",tolua_CCControlButton_CCControlButton_getTitleColorForState00);
   tolua_function(tolua_S,"setTitleColorForState",tolua_CCControlButton_CCControlButton_setTitleColorForState00);
   tolua_function(tolua_S,"getTitleLabelForState",tolua_CCControlButton_CCControlButton_getTitleLabelForState00);
   tolua_function(tolua_S,"setTitleLabelForState",tolua_CCControlButton_CCControlButton_setTitleLabelForState00);
   tolua_function(tolua_S,"setTitleTTFForState",tolua_CCControlButton_CCControlButton_setTitleTTFForState00);
   tolua_function(tolua_S,"getTitleTTFForState",tolua_CCControlButton_CCControlButton_getTitleTTFForState00);
   tolua_function(tolua_S,"setTitleTTFSizeForState",tolua_CCControlButton_CCControlButton_setTitleTTFSizeForState00);
   tolua_function(tolua_S,"getTitleTTFSizeForState",tolua_CCControlButton_CCControlButton_getTitleTTFSizeForState00);
   tolua_function(tolua_S,"setTitleBMFontForState",tolua_CCControlButton_CCControlButton_setTitleBMFontForState00);
   tolua_function(tolua_S,"getTitleBMFontForState",tolua_CCControlButton_CCControlButton_getTitleBMFontForState00);
   tolua_function(tolua_S,"getBackgroundSpriteForState",tolua_CCControlButton_CCControlButton_getBackgroundSpriteForState00);
   tolua_function(tolua_S,"setBackgroundSpriteForState",tolua_CCControlButton_CCControlButton_setBackgroundSpriteForState00);
   tolua_function(tolua_S,"setBackgroundSpriteFrameForState",tolua_CCControlButton_CCControlButton_setBackgroundSpriteFrameForState00);
   tolua_function(tolua_S,"getZoomFactor",tolua_CCControlButton_CCControlButton_getZoomFactor00);
   tolua_function(tolua_S,"setZoomFactor",tolua_CCControlButton_CCControlButton_setZoomFactor00);
   tolua_function(tolua_S,"getZoomStep",tolua_CCControlButton_CCControlButton_getZoomStep00);
   tolua_function(tolua_S,"setZoomStep",tolua_CCControlButton_CCControlButton_setZoomStep00);
   tolua_variable(tolua_S,"m_ZoomFactor",tolua_get_CCControlButton_m_ZoomFactor,tolua_set_CCControlButton_m_ZoomFactor);
   tolua_variable(tolua_S,"m_ZoomStep",tolua_get_CCControlButton_m_ZoomStep,tolua_set_CCControlButton_m_ZoomStep);
   tolua_function(tolua_S,"node",tolua_CCControlButton_CCControlButton_node00);
   tolua_function(tolua_S,"create",tolua_CCControlButton_CCControlButton_create03);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCControlButton (lua_State* tolua_S) {
 return tolua_CCControlButton_open(tolua_S);
};
#endif


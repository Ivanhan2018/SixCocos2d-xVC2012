/*
** Lua binding: SIX_EditBox
** Generated automatically by tolua++-1.0.92 on 04/25/13 14:51:52.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_EditBox_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_KeyboardNotificationLayer (lua_State* tolua_S)
{
 KeyboardNotificationLayer* self = (KeyboardNotificationLayer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_EditBox (lua_State* tolua_S)
{
 SIX_EditBox* self = (SIX_EditBox*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_EditBox_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCIMEKeyboardNotificationInfo");
 tolua_usertype(tolua_S,"SIX_EditBox");
 tolua_usertype(tolua_S,"CCIMEDelegate");
 tolua_usertype(tolua_S,"CCTextFieldDelegate");
 tolua_usertype(tolua_S,"CCTextFieldTTF");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"KeyboardNotificationLayer");
 tolua_usertype(tolua_S,"CCLayer");
}

/* method: subtitle of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_KeyboardNotificationLayer_subtitle00
static int tolua_SIX_EditBox_KeyboardNotificationLayer_subtitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyboardNotificationLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'subtitle'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->subtitle();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'subtitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onClickTrackNode of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_KeyboardNotificationLayer_onClickTrackNode00
static int tolua_SIX_EditBox_KeyboardNotificationLayer_onClickTrackNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyboardNotificationLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
  bool bClicked = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onClickTrackNode'", NULL);
#endif
  {
   self->onClickTrackNode(bClicked);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onClickTrackNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_KeyboardNotificationLayer_registerWithTouchDispatcher00
static int tolua_SIX_EditBox_KeyboardNotificationLayer_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyboardNotificationLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: keyboardWillShow of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_KeyboardNotificationLayer_keyboardWillShow00
static int tolua_SIX_EditBox_KeyboardNotificationLayer_keyboardWillShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyboardNotificationLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCIMEKeyboardNotificationInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
  CCIMEKeyboardNotificationInfo* info = ((CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'keyboardWillShow'", NULL);
#endif
  {
   self->keyboardWillShow(*info);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'keyboardWillShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_KeyboardNotificationLayer_ccTouchBegan00
static int tolua_SIX_EditBox_KeyboardNotificationLayer_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyboardNotificationLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchEnded of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_KeyboardNotificationLayer_ccTouchEnded00
static int tolua_SIX_EditBox_KeyboardNotificationLayer_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyboardNotificationLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: __CCIMEDelegate__ of class  KeyboardNotificationLayer */
#ifndef TOLUA_DISABLE_tolua_get_KeyboardNotificationLayer___CCIMEDelegate__
static int tolua_get_KeyboardNotificationLayer___CCIMEDelegate__(lua_State* tolua_S)
{
  KeyboardNotificationLayer* self = (KeyboardNotificationLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCIMEDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCIMEDelegate*>(self), "CCIMEDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCIMEDelegate*)self), "CCIMEDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_new00
static int tolua_SIX_EditBox_SIX_EditBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_EditBox* tolua_ret = (SIX_EditBox*)  Mtolua_new((SIX_EditBox)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_EditBox");
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

/* method: new_local of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_new00_local
static int tolua_SIX_EditBox_SIX_EditBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_EditBox* tolua_ret = (SIX_EditBox*)  Mtolua_new((SIX_EditBox)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_EditBox");
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

/* method: callbackRemoveNodeWhenDidAction of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_callbackRemoveNodeWhenDidAction00
static int tolua_SIX_EditBox_SIX_EditBox_callbackRemoveNodeWhenDidAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'callbackRemoveNodeWhenDidAction'", NULL);
#endif
  {
   self->callbackRemoveNodeWhenDidAction(pNode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'callbackRemoveNodeWhenDidAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: subtitle of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_subtitle00
static int tolua_SIX_EditBox_SIX_EditBox_subtitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'subtitle'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->subtitle();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'subtitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onClickTrackNode of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onClickTrackNode00
static int tolua_SIX_EditBox_SIX_EditBox_onClickTrackNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  bool bClicked = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onClickTrackNode'", NULL);
#endif
  {
   self->onClickTrackNode(bClicked);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onClickTrackNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachWithIME of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_attachWithIME00
static int tolua_SIX_EditBox_SIX_EditBox_attachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onEnter00
static int tolua_SIX_EditBox_SIX_EditBox_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onExit of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onExit00
static int tolua_SIX_EditBox_SIX_EditBox_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onTextFieldAttachWithIME of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onTextFieldAttachWithIME00
static int tolua_SIX_EditBox_SIX_EditBox_onTextFieldAttachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  CCTextFieldTTF* pSender = ((CCTextFieldTTF*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTextFieldAttachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTextFieldAttachWithIME(pSender);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTextFieldAttachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTextFieldDetachWithIME of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onTextFieldDetachWithIME00
static int tolua_SIX_EditBox_SIX_EditBox_onTextFieldDetachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  CCTextFieldTTF* pSender = ((CCTextFieldTTF*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTextFieldDetachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTextFieldDetachWithIME(pSender);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTextFieldDetachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTextFieldInsertText of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onTextFieldInsertText00
static int tolua_SIX_EditBox_SIX_EditBox_onTextFieldInsertText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  CCTextFieldTTF* pSender = ((CCTextFieldTTF*)  tolua_tousertype(tolua_S,2,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,3,0));
  int nLen = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTextFieldInsertText'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTextFieldInsertText(pSender,text,nLen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTextFieldInsertText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTextFieldDeleteBackward of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onTextFieldDeleteBackward00
static int tolua_SIX_EditBox_SIX_EditBox_onTextFieldDeleteBackward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  CCTextFieldTTF* pSender = ((CCTextFieldTTF*)  tolua_tousertype(tolua_S,2,0));
  const char* delText = ((const char*)  tolua_tostring(tolua_S,3,0));
  int nLen = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTextFieldDeleteBackward'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTextFieldDeleteBackward(pSender,delText,nLen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTextFieldDeleteBackward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onDraw of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_onDraw00
static int tolua_SIX_EditBox_SIX_EditBox_onDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  CCTextFieldTTF* pSender = ((CCTextFieldTTF*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onDraw'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onDraw(pSender);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInputTextMaxCount of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_getInputTextMaxCount00
static int tolua_SIX_EditBox_SIX_EditBox_getInputTextMaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInputTextMaxCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getInputTextMaxCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInputTextMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInputTextMaxCount of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_setInputTextMaxCount00
static int tolua_SIX_EditBox_SIX_EditBox_setInputTextMaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  int max = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInputTextMaxCount'", NULL);
#endif
  {
   self->setInputTextMaxCount(max);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInputTextMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitCursor of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_InitCursor00
static int tolua_SIX_EditBox_SIX_EditBox_InitCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
  long long color = ((long long)  tolua_tonumber(tolua_S,2,0));
  int width = ((int)  tolua_tonumber(tolua_S,3,0));
  int height = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitCursor'", NULL);
#endif
  {
   self->InitCursor(color,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTTF of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_SIX_EditBox_SIX_EditBox_getTTF00
static int tolua_SIX_EditBox_SIX_EditBox_getTTF00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_EditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTTF'", NULL);
#endif
  {
   CCTextFieldTTF* tolua_ret = (CCTextFieldTTF*)  self->getTTF();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextFieldTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTTF'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTextFieldDelegate__ of class  SIX_EditBox */
#ifndef TOLUA_DISABLE_tolua_get_SIX_EditBox___CCTextFieldDelegate__
static int tolua_get_SIX_EditBox___CCTextFieldDelegate__(lua_State* tolua_S)
{
  SIX_EditBox* self = (SIX_EditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTextFieldDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTextFieldDelegate*>(self), "CCTextFieldDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTextFieldDelegate*)self), "CCTextFieldDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_EditBox_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_EditBox_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"KeyboardNotificationLayer","KeyboardNotificationLayer","CCLayer",tolua_collect_KeyboardNotificationLayer);
  #else
  tolua_cclass(tolua_S,"KeyboardNotificationLayer","KeyboardNotificationLayer","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"KeyboardNotificationLayer");
   tolua_function(tolua_S,"subtitle",tolua_SIX_EditBox_KeyboardNotificationLayer_subtitle00);
   tolua_function(tolua_S,"onClickTrackNode",tolua_SIX_EditBox_KeyboardNotificationLayer_onClickTrackNode00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_SIX_EditBox_KeyboardNotificationLayer_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"keyboardWillShow",tolua_SIX_EditBox_KeyboardNotificationLayer_keyboardWillShow00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_SIX_EditBox_KeyboardNotificationLayer_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_SIX_EditBox_KeyboardNotificationLayer_ccTouchEnded00);
   tolua_variable(tolua_S,"__CCIMEDelegate__",tolua_get_KeyboardNotificationLayer___CCIMEDelegate__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_EditBox","SIX_EditBox","KeyboardNotificationLayer",tolua_collect_SIX_EditBox);
  #else
  tolua_cclass(tolua_S,"SIX_EditBox","SIX_EditBox","KeyboardNotificationLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_EditBox");
   tolua_function(tolua_S,"new",tolua_SIX_EditBox_SIX_EditBox_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_EditBox_SIX_EditBox_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_EditBox_SIX_EditBox_new00_local);
   tolua_function(tolua_S,"callbackRemoveNodeWhenDidAction",tolua_SIX_EditBox_SIX_EditBox_callbackRemoveNodeWhenDidAction00);
   tolua_function(tolua_S,"subtitle",tolua_SIX_EditBox_SIX_EditBox_subtitle00);
   tolua_function(tolua_S,"onClickTrackNode",tolua_SIX_EditBox_SIX_EditBox_onClickTrackNode00);
   tolua_function(tolua_S,"attachWithIME",tolua_SIX_EditBox_SIX_EditBox_attachWithIME00);
   tolua_function(tolua_S,"onEnter",tolua_SIX_EditBox_SIX_EditBox_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_SIX_EditBox_SIX_EditBox_onExit00);
   tolua_function(tolua_S,"onTextFieldAttachWithIME",tolua_SIX_EditBox_SIX_EditBox_onTextFieldAttachWithIME00);
   tolua_function(tolua_S,"onTextFieldDetachWithIME",tolua_SIX_EditBox_SIX_EditBox_onTextFieldDetachWithIME00);
   tolua_function(tolua_S,"onTextFieldInsertText",tolua_SIX_EditBox_SIX_EditBox_onTextFieldInsertText00);
   tolua_function(tolua_S,"onTextFieldDeleteBackward",tolua_SIX_EditBox_SIX_EditBox_onTextFieldDeleteBackward00);
   tolua_function(tolua_S,"onDraw",tolua_SIX_EditBox_SIX_EditBox_onDraw00);
   tolua_function(tolua_S,"getInputTextMaxCount",tolua_SIX_EditBox_SIX_EditBox_getInputTextMaxCount00);
   tolua_function(tolua_S,"setInputTextMaxCount",tolua_SIX_EditBox_SIX_EditBox_setInputTextMaxCount00);
   tolua_function(tolua_S,"InitCursor",tolua_SIX_EditBox_SIX_EditBox_InitCursor00);
   tolua_function(tolua_S,"getTTF",tolua_SIX_EditBox_SIX_EditBox_getTTF00);
   tolua_variable(tolua_S,"__CCTextFieldDelegate__",tolua_get_SIX_EditBox___CCTextFieldDelegate__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_EditBox (lua_State* tolua_S) {
 return tolua_SIX_EditBox_open(tolua_S);
};
#endif


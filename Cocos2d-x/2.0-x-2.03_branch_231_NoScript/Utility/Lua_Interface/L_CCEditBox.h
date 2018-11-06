/*
** Lua binding: CCEditBox
** Generated automatically by tolua++-1.0.92 on 04/20/13 15:48:17.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCEditBox_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCEditBox (lua_State* tolua_S)
{
 CCEditBox* self = (CCEditBox*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCEditBoxDelegate (lua_State* tolua_S)
{
 CCEditBoxDelegate* self = (CCEditBoxDelegate*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCEditBox_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCIMEKeyboardNotificationInfo");
 tolua_usertype(tolua_S,"CCEditBoxDelegate");
 tolua_usertype(tolua_S,"CCEditBox");
 tolua_usertype(tolua_S,"CCControlButton");
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCControlEvent");
 tolua_usertype(tolua_S,"CCIMEDelegate");
}

/* method: delete of class  CCEditBoxDelegate */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBoxDelegate_delete00
static int tolua_CCEditBox_CCEditBoxDelegate_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBoxDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBoxDelegate* self = (CCEditBoxDelegate*)  tolua_tousertype(tolua_S,1,0);
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

/* method: editBoxEditingDidBegin of class  CCEditBoxDelegate */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBoxDelegate_editBoxEditingDidBegin00
static int tolua_CCEditBox_CCEditBoxDelegate_editBoxEditingDidBegin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBoxDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBoxDelegate* self = (CCEditBoxDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCEditBox* editBox = ((CCEditBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'editBoxEditingDidBegin'", NULL);
#endif
  {
   self->editBoxEditingDidBegin(editBox);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'editBoxEditingDidBegin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: editBoxEditingDidEnd of class  CCEditBoxDelegate */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBoxDelegate_editBoxEditingDidEnd00
static int tolua_CCEditBox_CCEditBoxDelegate_editBoxEditingDidEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBoxDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBoxDelegate* self = (CCEditBoxDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCEditBox* editBox = ((CCEditBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'editBoxEditingDidEnd'", NULL);
#endif
  {
   self->editBoxEditingDidEnd(editBox);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'editBoxEditingDidEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: editBoxTextChanged of class  CCEditBoxDelegate */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBoxDelegate_editBoxTextChanged00
static int tolua_CCEditBox_CCEditBoxDelegate_editBoxTextChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBoxDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCEditBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBoxDelegate* self = (CCEditBoxDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCEditBox* editBox = ((CCEditBox*)  tolua_tousertype(tolua_S,2,0));
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'editBoxTextChanged'", NULL);
#endif
  {
   self->editBoxTextChanged(editBox,text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'editBoxTextChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: editBoxReturn of class  CCEditBoxDelegate */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBoxDelegate_editBoxReturn00
static int tolua_CCEditBox_CCEditBoxDelegate_editBoxReturn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBoxDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBoxDelegate* self = (CCEditBoxDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCEditBox* editBox = ((CCEditBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'editBoxReturn'", NULL);
#endif
  {
   self->editBoxReturn(editBox);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'editBoxReturn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_new00
static int tolua_CCEditBox_CCEditBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCEditBox* tolua_ret = (CCEditBox*)  Mtolua_new((CCEditBox)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEditBox");
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

/* method: new_local of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_new00_local
static int tolua_CCEditBox_CCEditBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCEditBox* tolua_ret = (CCEditBox*)  Mtolua_new((CCEditBox)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEditBox");
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

/* method: delete of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_delete00
static int tolua_CCEditBox_CCEditBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_create00
static int tolua_CCEditBox_CCEditBox_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCScale9Sprite",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCScale9Sprite",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* pNormal9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
  CCScale9Sprite* pPressed9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,4,NULL));
  CCScale9Sprite* pDisabled9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,5,NULL));
  {
   CCEditBox* tolua_ret = (CCEditBox*)  CCEditBox::create(*size,pNormal9SpriteBg,pPressed9SpriteBg,pDisabled9SpriteBg);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEditBox");
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

/* method: initWithSizeAndBackgroundSprite of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_initWithSizeAndBackgroundSprite00
static int tolua_CCEditBox_CCEditBox_initWithSizeAndBackgroundSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* pNormal9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSizeAndBackgroundSprite'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSizeAndBackgroundSprite(*size,pNormal9SpriteBg);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithSizeAndBackgroundSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setDelegate00
static int tolua_CCEditBox_CCEditBox_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCEditBoxDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  CCEditBoxDelegate* pDelegate = ((CCEditBoxDelegate*)  tolua_tousertype(tolua_S,2,0));
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

/* method: setText of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setText00
static int tolua_CCEditBox_CCEditBox_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const char* pText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(pText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getText of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_getText00
static int tolua_CCEditBox_CCEditBox_getText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getText'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getText();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontColor of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setFontColor00
static int tolua_CCEditBox_CCEditBox_setFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontColor'", NULL);
#endif
  {
   self->setFontColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceholderFontColor of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setPlaceholderFontColor00
static int tolua_CCEditBox_CCEditBox_setPlaceholderFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceholderFontColor'", NULL);
#endif
  {
   self->setPlaceholderFontColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceholderFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceHolder of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setPlaceHolder00
static int tolua_CCEditBox_CCEditBox_setPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const char* pText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceHolder'", NULL);
#endif
  {
   self->setPlaceHolder(pText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlaceHolder of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_getPlaceHolder00
static int tolua_CCEditBox_CCEditBox_getPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlaceHolder'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPlaceHolder();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInputMode of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setInputMode00
static int tolua_CCEditBox_CCEditBox_setInputMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  EditBoxInputMode inputMode = ((EditBoxInputMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInputMode'", NULL);
#endif
  {
   self->setInputMode(inputMode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInputMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxLength of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setMaxLength00
static int tolua_CCEditBox_CCEditBox_setMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  int maxLength = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxLength'", NULL);
#endif
  {
   self->setMaxLength(maxLength);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxLength of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_getMaxLength00
static int tolua_CCEditBox_CCEditBox_getMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInputFlag of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setInputFlag00
static int tolua_CCEditBox_CCEditBox_setInputFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  EditBoxInputFlag inputFlag = ((EditBoxInputFlag) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInputFlag'", NULL);
#endif
  {
   self->setInputFlag(inputFlag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInputFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setReturnType of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setReturnType00
static int tolua_CCEditBox_CCEditBox_setReturnType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  KeyboardReturnType returnType = ((KeyboardReturnType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setReturnType'", NULL);
#endif
  {
   self->setReturnType(returnType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setReturnType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setPosition00
static int tolua_CCEditBox_CCEditBox_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pos = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(*pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_setContentSize00
static int tolua_CCEditBox_CCEditBox_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: visit of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_visit00
static int tolua_CCEditBox_CCEditBox_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onExit of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_onExit00
static int tolua_CCEditBox_CCEditBox_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: keyboardWillShow of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_keyboardWillShow00
static int tolua_CCEditBox_CCEditBox_keyboardWillShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCIMEKeyboardNotificationInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: keyboardDidShow of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_keyboardDidShow00
static int tolua_CCEditBox_CCEditBox_keyboardDidShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCIMEKeyboardNotificationInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  CCIMEKeyboardNotificationInfo* info = ((CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'keyboardDidShow'", NULL);
#endif
  {
   self->keyboardDidShow(*info);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'keyboardDidShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: keyboardWillHide of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_keyboardWillHide00
static int tolua_CCEditBox_CCEditBox_keyboardWillHide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCIMEKeyboardNotificationInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  CCIMEKeyboardNotificationInfo* info = ((CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'keyboardWillHide'", NULL);
#endif
  {
   self->keyboardWillHide(*info);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'keyboardWillHide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: keyboardDidHide of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_keyboardDidHide00
static int tolua_CCEditBox_CCEditBox_keyboardDidHide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCIMEKeyboardNotificationInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  CCIMEKeyboardNotificationInfo* info = ((CCIMEKeyboardNotificationInfo*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'keyboardDidHide'", NULL);
#endif
  {
   self->keyboardDidHide(*info);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'keyboardDidHide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchDownAction of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_CCEditBox_CCEditBox_touchDownAction00
static int tolua_CCEditBox_CCEditBox_touchDownAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  CCObject* sender = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  CCControlEvent controlEvent = *((CCControlEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchDownAction'", NULL);
#endif
  {
   self->touchDownAction(sender,controlEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchDownAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCIMEDelegate__ of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_get_CCEditBox___CCIMEDelegate__
static int tolua_get_CCEditBox___CCIMEDelegate__(lua_State* tolua_S)
{
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
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

/* Open function */
TOLUA_API int tolua_CCEditBox_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCEditBox_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"kKeyboardReturnTypeDefault",kKeyboardReturnTypeDefault);
  tolua_constant(tolua_S,"kKeyboardReturnTypeDone",kKeyboardReturnTypeDone);
  tolua_constant(tolua_S,"kKeyboardReturnTypeSend",kKeyboardReturnTypeSend);
  tolua_constant(tolua_S,"kKeyboardReturnTypeSearch",kKeyboardReturnTypeSearch);
  tolua_constant(tolua_S,"kKeyboardReturnTypeGo",kKeyboardReturnTypeGo);
  tolua_constant(tolua_S,"kEditBoxInputModeAny",kEditBoxInputModeAny);
  tolua_constant(tolua_S,"kEditBoxInputModeEmailAddr",kEditBoxInputModeEmailAddr);
  tolua_constant(tolua_S,"kEditBoxInputModeNumeric",kEditBoxInputModeNumeric);
  tolua_constant(tolua_S,"kEditBoxInputModePhoneNumber",kEditBoxInputModePhoneNumber);
  tolua_constant(tolua_S,"kEditBoxInputModeUrl",kEditBoxInputModeUrl);
  tolua_constant(tolua_S,"kEditBoxInputModeDecimal",kEditBoxInputModeDecimal);
  tolua_constant(tolua_S,"kEditBoxInputModeSingleLine",kEditBoxInputModeSingleLine);
  tolua_constant(tolua_S,"kEditBoxInputFlagPassword",kEditBoxInputFlagPassword);
  tolua_constant(tolua_S,"kEditBoxInputFlagSensitive",kEditBoxInputFlagSensitive);
  tolua_constant(tolua_S,"kEditBoxInputFlagInitialCapsWord",kEditBoxInputFlagInitialCapsWord);
  tolua_constant(tolua_S,"kEditBoxInputFlagInitialCapsSentence",kEditBoxInputFlagInitialCapsSentence);
  tolua_constant(tolua_S,"kEditBoxInputFlagInitialCapsAllCharacters",kEditBoxInputFlagInitialCapsAllCharacters);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCEditBoxDelegate","CCEditBoxDelegate","",tolua_collect_CCEditBoxDelegate);
  #else
  tolua_cclass(tolua_S,"CCEditBoxDelegate","CCEditBoxDelegate","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCEditBoxDelegate");
   tolua_function(tolua_S,"delete",tolua_CCEditBox_CCEditBoxDelegate_delete00);
   tolua_function(tolua_S,"editBoxEditingDidBegin",tolua_CCEditBox_CCEditBoxDelegate_editBoxEditingDidBegin00);
   tolua_function(tolua_S,"editBoxEditingDidEnd",tolua_CCEditBox_CCEditBoxDelegate_editBoxEditingDidEnd00);
   tolua_function(tolua_S,"editBoxTextChanged",tolua_CCEditBox_CCEditBoxDelegate_editBoxTextChanged00);
   tolua_function(tolua_S,"editBoxReturn",tolua_CCEditBox_CCEditBoxDelegate_editBoxReturn00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCEditBox","CCEditBox","CCControlButton",tolua_collect_CCEditBox);
  #else
  tolua_cclass(tolua_S,"CCEditBox","CCEditBox","CCControlButton",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCEditBox");
   tolua_function(tolua_S,"new",tolua_CCEditBox_CCEditBox_new00);
   tolua_function(tolua_S,"new_local",tolua_CCEditBox_CCEditBox_new00_local);
   tolua_function(tolua_S,".call",tolua_CCEditBox_CCEditBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCEditBox_CCEditBox_delete00);
   tolua_function(tolua_S,"create",tolua_CCEditBox_CCEditBox_create00);
   tolua_function(tolua_S,"initWithSizeAndBackgroundSprite",tolua_CCEditBox_CCEditBox_initWithSizeAndBackgroundSprite00);
   tolua_function(tolua_S,"setDelegate",tolua_CCEditBox_CCEditBox_setDelegate00);
   tolua_function(tolua_S,"setText",tolua_CCEditBox_CCEditBox_setText00);
   tolua_function(tolua_S,"getText",tolua_CCEditBox_CCEditBox_getText00);
   tolua_function(tolua_S,"setFontColor",tolua_CCEditBox_CCEditBox_setFontColor00);
   tolua_function(tolua_S,"setPlaceholderFontColor",tolua_CCEditBox_CCEditBox_setPlaceholderFontColor00);
   tolua_function(tolua_S,"setPlaceHolder",tolua_CCEditBox_CCEditBox_setPlaceHolder00);
   tolua_function(tolua_S,"getPlaceHolder",tolua_CCEditBox_CCEditBox_getPlaceHolder00);
   tolua_function(tolua_S,"setInputMode",tolua_CCEditBox_CCEditBox_setInputMode00);
   tolua_function(tolua_S,"setMaxLength",tolua_CCEditBox_CCEditBox_setMaxLength00);
   tolua_function(tolua_S,"getMaxLength",tolua_CCEditBox_CCEditBox_getMaxLength00);
   tolua_function(tolua_S,"setInputFlag",tolua_CCEditBox_CCEditBox_setInputFlag00);
   tolua_function(tolua_S,"setReturnType",tolua_CCEditBox_CCEditBox_setReturnType00);
   tolua_function(tolua_S,"setPosition",tolua_CCEditBox_CCEditBox_setPosition00);
   tolua_function(tolua_S,"setContentSize",tolua_CCEditBox_CCEditBox_setContentSize00);
   tolua_function(tolua_S,"visit",tolua_CCEditBox_CCEditBox_visit00);
   tolua_function(tolua_S,"onExit",tolua_CCEditBox_CCEditBox_onExit00);
   tolua_function(tolua_S,"keyboardWillShow",tolua_CCEditBox_CCEditBox_keyboardWillShow00);
   tolua_function(tolua_S,"keyboardDidShow",tolua_CCEditBox_CCEditBox_keyboardDidShow00);
   tolua_function(tolua_S,"keyboardWillHide",tolua_CCEditBox_CCEditBox_keyboardWillHide00);
   tolua_function(tolua_S,"keyboardDidHide",tolua_CCEditBox_CCEditBox_keyboardDidHide00);
   tolua_function(tolua_S,"touchDownAction",tolua_CCEditBox_CCEditBox_touchDownAction00);
   tolua_variable(tolua_S,"__CCIMEDelegate__",tolua_get_CCEditBox___CCIMEDelegate__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCEditBox (lua_State* tolua_S) {
 return tolua_CCEditBox_open(tolua_S);
};
#endif


/*
** Lua binding: SIX_UIMgr
** Generated automatically by tolua++-1.0.92 on 05/11/13 18:50:43.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_UIMgr_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_UIMgr (lua_State* tolua_S)
{
 SIX_UIMgr* self = (SIX_UIMgr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_UIMgr_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"SIX_UIScene");
 tolua_usertype(tolua_S,"CCMenu");
 tolua_usertype(tolua_S,"CCAnimation");
 tolua_usertype(tolua_S,"SIX_UIMgr");
 tolua_usertype(tolua_S,"CCProgressTimer");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCLayerColor");
 tolua_usertype(tolua_S,"CCSpriteBatchNode");
 tolua_usertype(tolua_S,"SIX_ListView");
 tolua_usertype(tolua_S,"CCMenuItemAtlasFont");
 tolua_usertype(tolua_S,"SIX_XmlDataSet");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCMenuItemLabel");
 tolua_usertype(tolua_S,"SIX_DSTPL<SIX_KV>");
 tolua_usertype(tolua_S,"CCMenuItemImage");
 tolua_usertype(tolua_S,"SIX_EntityMgr");
 tolua_usertype(tolua_S,"CCLayerMultiplex");
 tolua_usertype(tolua_S,"SIX_DSTPL<SIX_XmlDataSet>");
 tolua_usertype(tolua_S,"vector<string>");
 tolua_usertype(tolua_S,"CCMenuItem");
 tolua_usertype(tolua_S,"SIX_KV");
 tolua_usertype(tolua_S,"CCLabelTTF");
 tolua_usertype(tolua_S,"CCControlEvent");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"SIX_ListViewCell");
 tolua_usertype(tolua_S,"CCControlButton");
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCLayerGradient");
 tolua_usertype(tolua_S,"CCMenuItemToggle");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCMenuItemSprite");
 tolua_usertype(tolua_S,"CCSpriteFrame");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCMenuItemFont");
}

/* method: new of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_new00
static int tolua_SIX_UIMgr_SIX_UIMgr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIMgr* tolua_ret = (SIX_UIMgr*)  Mtolua_new((SIX_UIMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIMgr");
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

/* method: new_local of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_new00_local
static int tolua_SIX_UIMgr_SIX_UIMgr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_UIMgr* tolua_ret = (SIX_UIMgr*)  Mtolua_new((SIX_UIMgr)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIMgr");
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

/* method: delete of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_delete00
static int tolua_SIX_UIMgr_SIX_UIMgr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ParseXML of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseXML00
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_XmlDataSet>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_DSTPL<SIX_XmlDataSet>* pXmlDataSet = ((SIX_DSTPL<SIX_XmlDataSet>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseXML'", NULL);
#endif
  {
   int tolua_ret = (int)  self->ParseXML(pXmlDataSet);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseXML'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_Run00
static int tolua_SIX_UIMgr_SIX_UIMgr_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Run();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Release of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_Release00
static int tolua_SIX_UIMgr_SIX_UIMgr_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Release'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Release();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetParent of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_SetParent00
static int tolua_SIX_UIMgr_SIX_UIMgr_SetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_UIScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_UIScene* pParnet = ((SIX_UIScene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetParent'", NULL);
#endif
  {
   self->SetParent(pParnet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_GetParent00
static int tolua_SIX_UIMgr_SIX_UIMgr_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   SIX_UIScene* tolua_ret = (SIX_UIScene*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_UIScene");
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

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute00
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute01
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteBatchNode* pControl = ((CCSpriteBatchNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute02
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* pControl = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute03
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCProgressTimer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCProgressTimer* pControl = ((CCProgressTimer*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute04
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* pControl = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute05
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCLabelTTF* pControl = ((CCLabelTTF*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute06
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute06(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItem* pControl = ((CCMenuItem*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute05(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute07
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute07(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItemToggle",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItemToggle* pControl = ((CCMenuItemToggle*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute06(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute08
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute08(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItemSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItemSprite* pControl = ((CCMenuItemSprite*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute07(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute09
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute09(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItemImage",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItemImage* pControl = ((CCMenuItemImage*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute08(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute10
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute10(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItemLabel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItemLabel* pControl = ((CCMenuItemLabel*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute09(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute11
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute11(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItemAtlasFont",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItemAtlasFont* pControl = ((CCMenuItemAtlasFont*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute10(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute12
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute12(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItemFont",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenuItemFont* pControl = ((CCMenuItemFont*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute11(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute13
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute13(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCLayer* pControl = ((CCLayer*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute12(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute14
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute14(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCMenu* pControl = ((CCMenu*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute13(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute15
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute15(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCLayerMultiplex* pControl = ((CCLayerMultiplex*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute14(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute16
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute16(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayerColor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCLayerColor* pControl = ((CCLayerColor*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute15(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute17
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute17(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCLayerGradient* pControl = ((CCLayerGradient*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute16(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute18
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute18(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCControl* pControl = ((CCControl*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute17(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseAttribute of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute19
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute19(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCControlButton* pControl = ((CCControlButton*)  tolua_tousertype(tolua_S,2,0));
  SIX_KV* pKV = ((SIX_KV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ParseAttribute(pControl,pKV);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute18(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAttributeSplit of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_GetAttributeSplit00
static int tolua_SIX_UIMgr_SIX_UIMgr_GetAttributeSplit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* src = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  string value = ((string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttributeSplit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAttributeSplit(src,name,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)value);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttributeSplit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAttributeAndPos of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_GetAttributeAndPos00
static int tolua_SIX_UIMgr_SIX_UIMgr_GetAttributeAndPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"SIX_KV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,2,0));
  const char* attribute = ((const char*)  tolua_tostring(tolua_S,3,0));
  SIX_KV* pResult = ((SIX_KV*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttributeAndPos'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetAttributeAndPos(pDataElement,attribute,pResult);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttributeAndPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseObject of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseObject00
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_XmlDataSet",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_XmlDataSet* pDataSet = ((SIX_XmlDataSet*)  tolua_tousertype(tolua_S,2,0));
  const char* nodeName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseObject'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->ParseObject(pDataSet,nodeName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ParseControl of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_ParseControl00
static int tolua_SIX_UIMgr_SIX_UIMgr_ParseControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_XmlDataSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_XmlDataSet* pDataSet = ((SIX_XmlDataSet*)  tolua_tousertype(tolua_S,2,0));
  CCNode* pRoot = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ParseControl'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->ParseControl(pDataSet,pRoot);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateAnimation of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateAnimation00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_XmlDataSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pObject = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SIX_XmlDataSet* pDataSet = ((SIX_XmlDataSet*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateAnimation'", NULL);
#endif
  {
   CCAnimation* tolua_ret = (CCAnimation*)  self->CreateAnimation(pObject,pDataSet);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateSpriteFrame of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateSpriteFrame00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pObject = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateSpriteFrame'", NULL);
#endif
  {
   CCSpriteFrame* tolua_ret = (CCSpriteFrame*)  self->CreateSpriteFrame(pObject,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSpriteFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateSprite of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateSprite00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateSprite'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->CreateSprite(pControl,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateButton of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateButton00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateButton'", NULL);
#endif
  {
   CCControlButton* tolua_ret = (CCControlButton*)  self->CreateButton(pControl,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateProgressTimer of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateProgressTimer00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateProgressTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateProgressTimer'", NULL);
#endif
  {
   CCProgressTimer* tolua_ret = (CCProgressTimer*)  self->CreateProgressTimer(pControl,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCProgressTimer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateProgressTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateSpriteBatchNode of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateSpriteBatchNode00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateSpriteBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateSpriteBatchNode'", NULL);
#endif
  {
   CCSpriteBatchNode* tolua_ret = (CCSpriteBatchNode*)  self->CreateSpriteBatchNode(pControl,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSpriteBatchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateSpriteBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateListView of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateListView00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateListView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateListView'", NULL);
#endif
  {
   SIX_ListView* tolua_ret = (SIX_ListView*)  self->CreateListView(pControl,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateListView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateListViewCell of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_CreateListViewCell00
static int tolua_SIX_UIMgr_SIX_UIMgr_CreateListViewCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pControl = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateListViewCell'", NULL);
#endif
  {
   SIX_ListViewCell* tolua_ret = (SIX_ListViewCell*)  self->CreateListViewCell(pControl,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListViewCell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateListViewCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SIX_UIMgr::ParseKV of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_SIX_UIMgr__ParseKV00
static int tolua_SIX_UIMgr_SIX_UIMgr_SIX_UIMgr__ParseKV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SIX_UIMgr::ParseKV'", NULL);
#endif
  {
   SIX_DSTPL<SIX_KV>* tolua_ret = (SIX_DSTPL<SIX_KV>*)  self->SIX_UIMgr::ParseKV(name,pDataElement);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_DSTPL<SIX_KV>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SIX_UIMgr__ParseKV'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadFrameCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_LoadFrameCache00
static int tolua_SIX_UIMgr_SIX_UIMgr_LoadFrameCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_DSTPL<SIX_KV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_DSTPL<SIX_KV>* pDataElement = ((SIX_DSTPL<SIX_KV>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFrameCache'", NULL);
#endif
  {
   self->LoadFrameCache(pDataElement);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFrameCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnloadFrameCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_UnloadFrameCache00
static int tolua_SIX_UIMgr_SIX_UIMgr_UnloadFrameCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnloadFrameCache'", NULL);
#endif
  {
   self->UnloadFrameCache();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnloadFrameCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrameCacheCount of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_GetFrameCacheCount00
static int tolua_SIX_UIMgr_SIX_UIMgr_GetFrameCacheCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrameCacheCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetFrameCacheCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrameCacheCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadAnimationCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_LoadAnimationCache00
static int tolua_SIX_UIMgr_SIX_UIMgr_LoadAnimationCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_XmlDataSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  SIX_XmlDataSet* pDataSet = ((SIX_XmlDataSet*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadAnimationCache'", NULL);
#endif
  {
   self->LoadAnimationCache(pDataSet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadAnimationCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationFromCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_GetAnimationFromCache00
static int tolua_SIX_UIMgr_SIX_UIMgr_GetAnimationFromCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationFromCache'", NULL);
#endif
  {
   CCAnimation* tolua_ret = (CCAnimation*)  self->GetAnimationFromCache(animationName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationFromCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnloadAnimationCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_UnloadAnimationCache00
static int tolua_SIX_UIMgr_SIX_UIMgr_UnloadAnimationCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnloadAnimationCache'", NULL);
#endif
  {
   self->UnloadAnimationCache();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnloadAnimationCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationCacheCount of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_GetAnimationCacheCount00
static int tolua_SIX_UIMgr_SIX_UIMgr_GetAnimationCacheCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationCacheCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetAnimationCacheCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationCacheCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addControlEvents of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_addControlEvents00
static int tolua_SIX_UIMgr_SIX_UIMgr_addControlEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCControl",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int controlEvents = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  CCControl* pContrl = ((CCControl*)  tolua_tousertype(tolua_S,3,0));
  CCObject* pTarget = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addControlEvents'", NULL);
#endif
  {
   self->addControlEvents(controlEvents,pContrl,pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addControlEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doEvents of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_doEvents00
static int tolua_SIX_UIMgr_SIX_UIMgr_doEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCControlEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pSender = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  CCControlEvent event = *((CCControlEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doEvents'", NULL);
#endif
  {
   self->doEvents(pSender,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAllDirty of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_setAllDirty00
static int tolua_SIX_UIMgr_SIX_UIMgr_setAllDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
  bool bDirty = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAllDirty'", NULL);
#endif
  {
   self->setAllDirty(bDirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAllDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAllDirty of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_SIX_UIMgr_SIX_UIMgr_getAllDirty00
static int tolua_SIX_UIMgr_SIX_UIMgr_getAllDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_UIMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAllDirty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getAllDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAllDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Parent of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIMgr_m_Parent_ptr
static int tolua_get_SIX_UIMgr_m_Parent_ptr(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Parent'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_Parent,"SIX_UIScene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Parent of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIMgr_m_Parent_ptr
static int tolua_set_SIX_UIMgr_m_Parent_ptr(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Parent'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SIX_UIScene",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Parent = ((SIX_UIScene*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_FrameCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIMgr_m_FrameCache
static int tolua_get_SIX_UIMgr_m_FrameCache(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_FrameCache'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_FrameCache,"vector<string>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_FrameCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIMgr_m_FrameCache
static int tolua_set_SIX_UIMgr_m_FrameCache(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_FrameCache'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<string>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_FrameCache = *((vector<string>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_AnimationCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIMgr_m_AnimationCache
static int tolua_get_SIX_UIMgr_m_AnimationCache(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_AnimationCache'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_AnimationCache,"CCDictionary");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_AnimationCache of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIMgr_m_AnimationCache
static int tolua_set_SIX_UIMgr_m_AnimationCache(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_AnimationCache'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_AnimationCache = *((CCDictionary*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bDirty of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_get_SIX_UIMgr_m_bDirty
static int tolua_get_SIX_UIMgr_m_bDirty(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bDirty'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bDirty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bDirty of class  SIX_UIMgr */
#ifndef TOLUA_DISABLE_tolua_set_SIX_UIMgr_m_bDirty
static int tolua_set_SIX_UIMgr_m_bDirty(lua_State* tolua_S)
{
  SIX_UIMgr* self = (SIX_UIMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bDirty'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bDirty = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_UIMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_UIMgr_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_UIMgr","SIX_UIMgr","SIX_EntityMgr",tolua_collect_SIX_UIMgr);
  #else
  tolua_cclass(tolua_S,"SIX_UIMgr","SIX_UIMgr","SIX_EntityMgr",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_UIMgr");
   tolua_function(tolua_S,"new",tolua_SIX_UIMgr_SIX_UIMgr_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_UIMgr_SIX_UIMgr_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_UIMgr_SIX_UIMgr_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_UIMgr_SIX_UIMgr_delete00);
   tolua_function(tolua_S,"ParseXML",tolua_SIX_UIMgr_SIX_UIMgr_ParseXML00);
   tolua_function(tolua_S,"Run",tolua_SIX_UIMgr_SIX_UIMgr_Run00);
   tolua_function(tolua_S,"Release",tolua_SIX_UIMgr_SIX_UIMgr_Release00);
   tolua_function(tolua_S,"SetParent",tolua_SIX_UIMgr_SIX_UIMgr_SetParent00);
   tolua_function(tolua_S,"GetParent",tolua_SIX_UIMgr_SIX_UIMgr_GetParent00);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute00);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute01);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute02);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute03);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute04);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute05);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute06);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute07);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute08);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute09);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute10);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute11);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute12);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute13);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute14);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute15);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute16);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute17);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute18);
   tolua_function(tolua_S,"ParseAttribute",tolua_SIX_UIMgr_SIX_UIMgr_ParseAttribute19);
   tolua_function(tolua_S,"GetAttributeSplit",tolua_SIX_UIMgr_SIX_UIMgr_GetAttributeSplit00);
   tolua_function(tolua_S,"GetAttributeAndPos",tolua_SIX_UIMgr_SIX_UIMgr_GetAttributeAndPos00);
   tolua_function(tolua_S,"ParseObject",tolua_SIX_UIMgr_SIX_UIMgr_ParseObject00);
   tolua_function(tolua_S,"ParseControl",tolua_SIX_UIMgr_SIX_UIMgr_ParseControl00);
   tolua_function(tolua_S,"CreateAnimation",tolua_SIX_UIMgr_SIX_UIMgr_CreateAnimation00);
   tolua_function(tolua_S,"CreateSpriteFrame",tolua_SIX_UIMgr_SIX_UIMgr_CreateSpriteFrame00);
   tolua_function(tolua_S,"CreateSprite",tolua_SIX_UIMgr_SIX_UIMgr_CreateSprite00);
   tolua_function(tolua_S,"CreateButton",tolua_SIX_UIMgr_SIX_UIMgr_CreateButton00);
   tolua_function(tolua_S,"CreateProgressTimer",tolua_SIX_UIMgr_SIX_UIMgr_CreateProgressTimer00);
   tolua_function(tolua_S,"CreateSpriteBatchNode",tolua_SIX_UIMgr_SIX_UIMgr_CreateSpriteBatchNode00);
   tolua_function(tolua_S,"CreateListView",tolua_SIX_UIMgr_SIX_UIMgr_CreateListView00);
   tolua_function(tolua_S,"CreateListViewCell",tolua_SIX_UIMgr_SIX_UIMgr_CreateListViewCell00);
   tolua_function(tolua_S,"SIX_UIMgr__ParseKV",tolua_SIX_UIMgr_SIX_UIMgr_SIX_UIMgr__ParseKV00);
   tolua_function(tolua_S,"LoadFrameCache",tolua_SIX_UIMgr_SIX_UIMgr_LoadFrameCache00);
   tolua_function(tolua_S,"UnloadFrameCache",tolua_SIX_UIMgr_SIX_UIMgr_UnloadFrameCache00);
   tolua_function(tolua_S,"GetFrameCacheCount",tolua_SIX_UIMgr_SIX_UIMgr_GetFrameCacheCount00);
   tolua_function(tolua_S,"LoadAnimationCache",tolua_SIX_UIMgr_SIX_UIMgr_LoadAnimationCache00);
   tolua_function(tolua_S,"GetAnimationFromCache",tolua_SIX_UIMgr_SIX_UIMgr_GetAnimationFromCache00);
   tolua_function(tolua_S,"UnloadAnimationCache",tolua_SIX_UIMgr_SIX_UIMgr_UnloadAnimationCache00);
   tolua_function(tolua_S,"GetAnimationCacheCount",tolua_SIX_UIMgr_SIX_UIMgr_GetAnimationCacheCount00);
   tolua_function(tolua_S,"addControlEvents",tolua_SIX_UIMgr_SIX_UIMgr_addControlEvents00);
   tolua_function(tolua_S,"doEvents",tolua_SIX_UIMgr_SIX_UIMgr_doEvents00);
   tolua_function(tolua_S,"setAllDirty",tolua_SIX_UIMgr_SIX_UIMgr_setAllDirty00);
   tolua_function(tolua_S,"getAllDirty",tolua_SIX_UIMgr_SIX_UIMgr_getAllDirty00);
   tolua_variable(tolua_S,"m_Parent",tolua_get_SIX_UIMgr_m_Parent_ptr,tolua_set_SIX_UIMgr_m_Parent_ptr);
   tolua_variable(tolua_S,"m_FrameCache",tolua_get_SIX_UIMgr_m_FrameCache,tolua_set_SIX_UIMgr_m_FrameCache);
   tolua_variable(tolua_S,"m_AnimationCache",tolua_get_SIX_UIMgr_m_AnimationCache,tolua_set_SIX_UIMgr_m_AnimationCache);
   tolua_variable(tolua_S,"m_bDirty",tolua_get_SIX_UIMgr_m_bDirty,tolua_set_SIX_UIMgr_m_bDirty);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_UIMgr (lua_State* tolua_S) {
 return tolua_SIX_UIMgr_open(tolua_S);
};
#endif


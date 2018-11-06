/*
** Lua binding: CCTableView
** Generated automatically by tolua++-1.0.92 on 04/24/13 11:22:14.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCTableView_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CCSize (lua_State* tolua_S)
//{
// CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_CCTableView (lua_State* tolua_S)
{
 CCTableView* self = (CCTableView*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCTableView_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCTableViewDelegate");
 tolua_usertype(tolua_S,"CCScrollViewDelegate");
 tolua_usertype(tolua_S,"CCTableViewDataSource");
 tolua_usertype(tolua_S,"CCScrollView");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCTableViewCell");
 tolua_usertype(tolua_S,"CCTableView");
}

/* method: tableCellTouched of class  CCTableViewDelegate */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableViewDelegate_tableCellTouched00
static int tolua_CCTableView_CCTableViewDelegate_tableCellTouched00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewDelegate* self = (CCTableViewDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
  CCTableViewCell* cell = ((CCTableViewCell*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tableCellTouched'", NULL);
#endif
  {
   self->tableCellTouched(table,cell);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tableCellTouched'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cellSizeForTable of class  CCTableViewDataSource */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableViewDataSource_cellSizeForTable00
static int tolua_CCTableView_CCTableViewDataSource_cellSizeForTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewDataSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewDataSource* self = (CCTableViewDataSource*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cellSizeForTable'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->cellSizeForTable(table);
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
 tolua_error(tolua_S,"#ferror in function 'cellSizeForTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tableCellAtIndex of class  CCTableViewDataSource */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableViewDataSource_tableCellAtIndex00
static int tolua_CCTableView_CCTableViewDataSource_tableCellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewDataSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewDataSource* self = (CCTableViewDataSource*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tableCellAtIndex'", NULL);
#endif
  {
   CCTableViewCell* tolua_ret = (CCTableViewCell*)  self->tableCellAtIndex(table,idx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewCell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tableCellAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: numberOfCellsInTableView of class  CCTableViewDataSource */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableViewDataSource_numberOfCellsInTableView00
static int tolua_CCTableView_CCTableViewDataSource_numberOfCellsInTableView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableViewDataSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewDataSource* self = (CCTableViewDataSource*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'numberOfCellsInTableView'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->numberOfCellsInTableView(table);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'numberOfCellsInTableView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_new00
static int tolua_CCTableView_CCTableView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTableView* tolua_ret = (CCTableView*)  Mtolua_new((CCTableView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableView");
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

/* method: new_local of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_new00_local
static int tolua_CCTableView_CCTableView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTableView* tolua_ret = (CCTableView*)  Mtolua_new((CCTableView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableView");
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

/* method: delete of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_delete00
static int tolua_CCTableView_CCTableView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_create00
static int tolua_CCTableView_CCTableView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableViewDataSource",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewDataSource* dataSource = ((CCTableViewDataSource*)  tolua_tousertype(tolua_S,2,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  {
   CCTableView* tolua_ret = (CCTableView*)  CCTableView::create(dataSource,size);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableView");
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

/* method: create of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_create01
static int tolua_CCTableView_CCTableView_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableViewDataSource",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTableViewDataSource* dataSource = ((CCTableViewDataSource*)  tolua_tousertype(tolua_S,2,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,4,0));
  {
   CCTableView* tolua_ret = (CCTableView*)  CCTableView::create(dataSource,size,container);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableView");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCTableView_CCTableView_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDataSource of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_getDataSource00
static int tolua_CCTableView_CCTableView_getDataSource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDataSource'", NULL);
#endif
  {
   CCTableViewDataSource* tolua_ret = (CCTableViewDataSource*)  self->getDataSource();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewDataSource");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDataSource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDataSource of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_setDataSource00
static int tolua_CCTableView_CCTableView_setDataSource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableViewDataSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  CCTableViewDataSource* source = ((CCTableViewDataSource*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDataSource'", NULL);
#endif
  {
   self->setDataSource(source);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDataSource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDelegate of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_getDelegate00
static int tolua_CCTableView_CCTableView_getDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDelegate'", NULL);
#endif
  {
   CCTableViewDelegate* tolua_ret = (CCTableViewDelegate*)  self->getDelegate();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewDelegate");
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

/* method: setDelegate of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_setDelegate00
static int tolua_CCTableView_CCTableView_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableViewDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  CCTableViewDelegate* pDelegate = ((CCTableViewDelegate*)  tolua_tousertype(tolua_S,2,0));
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

/* method: setVerticalFillOrder of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_setVerticalFillOrder00
static int tolua_CCTableView_CCTableView_setVerticalFillOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  CCTableViewVerticalFillOrder order = ((CCTableViewVerticalFillOrder) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVerticalFillOrder'", NULL);
#endif
  {
   self->setVerticalFillOrder(order);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVerticalFillOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVerticalFillOrder of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_getVerticalFillOrder00
static int tolua_CCTableView_CCTableView_getVerticalFillOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVerticalFillOrder'", NULL);
#endif
  {
   CCTableViewVerticalFillOrder tolua_ret = (CCTableViewVerticalFillOrder)  self->getVerticalFillOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVerticalFillOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithViewSize of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_initWithViewSize00
static int tolua_CCTableView_CCTableView_initWithViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: updateCellAtIndex of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_updateCellAtIndex00
static int tolua_CCTableView_CCTableView_updateCellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateCellAtIndex'", NULL);
#endif
  {
   self->updateCellAtIndex(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateCellAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insertCellAtIndex of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_insertCellAtIndex00
static int tolua_CCTableView_CCTableView_insertCellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertCellAtIndex'", NULL);
#endif
  {
   self->insertCellAtIndex(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertCellAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeCellAtIndex of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_removeCellAtIndex00
static int tolua_CCTableView_CCTableView_removeCellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeCellAtIndex'", NULL);
#endif
  {
   self->removeCellAtIndex(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeCellAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reloadData of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_reloadData00
static int tolua_CCTableView_CCTableView_reloadData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reloadData'", NULL);
#endif
  {
   self->reloadData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reloadData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dequeueCell of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_dequeueCell00
static int tolua_CCTableView_CCTableView_dequeueCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dequeueCell'", NULL);
#endif
  {
   CCTableViewCell* tolua_ret = (CCTableViewCell*)  self->dequeueCell();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewCell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dequeueCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cellAtIndex of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_cellAtIndex00
static int tolua_CCTableView_CCTableView_cellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cellAtIndex'", NULL);
#endif
  {
   CCTableViewCell* tolua_ret = (CCTableViewCell*)  self->cellAtIndex(idx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewCell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cellAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollViewDidScroll of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_scrollViewDidScroll00
static int tolua_CCTableView_CCTableView_scrollViewDidScroll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollViewDidZoom of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_scrollViewDidZoom00
static int tolua_CCTableView_CCTableView_scrollViewDidZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ccTouchEnded of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_CCTableView_CCTableView_ccTouchEnded00
static int tolua_CCTableView_CCTableView_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: __CCScrollViewDelegate__ of class  CCTableView */
#ifndef TOLUA_DISABLE_tolua_get_CCTableView___CCScrollViewDelegate__
static int tolua_get_CCTableView___CCScrollViewDelegate__(lua_State* tolua_S)
{
  CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCScrollViewDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCScrollViewDelegate*>(self), "CCScrollViewDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCScrollViewDelegate*)self), "CCScrollViewDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCTableView_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCTableView_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"kCCTableViewFillTopDown",kCCTableViewFillTopDown);
  tolua_constant(tolua_S,"kCCTableViewFillBottomUp",kCCTableViewFillBottomUp);
  tolua_cclass(tolua_S,"CCTableViewDelegate","CCTableViewDelegate","CCScrollViewDelegate",NULL);
  tolua_beginmodule(tolua_S,"CCTableViewDelegate");
   tolua_function(tolua_S,"tableCellTouched",tolua_CCTableView_CCTableViewDelegate_tableCellTouched00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTableViewDataSource","CCTableViewDataSource","",NULL);
  tolua_beginmodule(tolua_S,"CCTableViewDataSource");
   tolua_function(tolua_S,"cellSizeForTable",tolua_CCTableView_CCTableViewDataSource_cellSizeForTable00);
   tolua_function(tolua_S,"tableCellAtIndex",tolua_CCTableView_CCTableViewDataSource_tableCellAtIndex00);
   tolua_function(tolua_S,"numberOfCellsInTableView",tolua_CCTableView_CCTableViewDataSource_numberOfCellsInTableView00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCTableView","CCTableView","CCScrollView",tolua_collect_CCTableView);
  #else
  tolua_cclass(tolua_S,"CCTableView","CCTableView","CCScrollView",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCTableView");
   tolua_function(tolua_S,"new",tolua_CCTableView_CCTableView_new00);
   tolua_function(tolua_S,"new_local",tolua_CCTableView_CCTableView_new00_local);
   tolua_function(tolua_S,".call",tolua_CCTableView_CCTableView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CCTableView_CCTableView_delete00);
   tolua_function(tolua_S,"create",tolua_CCTableView_CCTableView_create00);
   tolua_function(tolua_S,"create",tolua_CCTableView_CCTableView_create01);
   tolua_function(tolua_S,"getDataSource",tolua_CCTableView_CCTableView_getDataSource00);
   tolua_function(tolua_S,"setDataSource",tolua_CCTableView_CCTableView_setDataSource00);
   tolua_function(tolua_S,"getDelegate",tolua_CCTableView_CCTableView_getDelegate00);
   tolua_function(tolua_S,"setDelegate",tolua_CCTableView_CCTableView_setDelegate00);
   tolua_function(tolua_S,"setVerticalFillOrder",tolua_CCTableView_CCTableView_setVerticalFillOrder00);
   tolua_function(tolua_S,"getVerticalFillOrder",tolua_CCTableView_CCTableView_getVerticalFillOrder00);
   tolua_function(tolua_S,"initWithViewSize",tolua_CCTableView_CCTableView_initWithViewSize00);
   tolua_function(tolua_S,"updateCellAtIndex",tolua_CCTableView_CCTableView_updateCellAtIndex00);
   tolua_function(tolua_S,"insertCellAtIndex",tolua_CCTableView_CCTableView_insertCellAtIndex00);
   tolua_function(tolua_S,"removeCellAtIndex",tolua_CCTableView_CCTableView_removeCellAtIndex00);
   tolua_function(tolua_S,"reloadData",tolua_CCTableView_CCTableView_reloadData00);
   tolua_function(tolua_S,"dequeueCell",tolua_CCTableView_CCTableView_dequeueCell00);
   tolua_function(tolua_S,"cellAtIndex",tolua_CCTableView_CCTableView_cellAtIndex00);
   tolua_function(tolua_S,"scrollViewDidScroll",tolua_CCTableView_CCTableView_scrollViewDidScroll00);
   tolua_function(tolua_S,"scrollViewDidZoom",tolua_CCTableView_CCTableView_scrollViewDidZoom00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_CCTableView_CCTableView_ccTouchEnded00);
   tolua_variable(tolua_S,"__CCScrollViewDelegate__",tolua_get_CCTableView___CCScrollViewDelegate__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCTableView (lua_State* tolua_S) {
 return tolua_CCTableView_open(tolua_S);
};
#endif


/*
** Lua binding: SIX_ListView
** Generated automatically by tolua++-1.0.92 on 05/21/13 19:13:47.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_ListView_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CCSize (lua_State* tolua_S)
//{
// CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_SIX_ListView (lua_State* tolua_S)
{
 SIX_ListView* self = (SIX_ListView*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_ListView_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCLayerColor");
 tolua_usertype(tolua_S,"SIX_ListView");
 tolua_usertype(tolua_S,"CCTableViewDelegate");
 tolua_usertype(tolua_S,"SIX_ScrollBar");
 tolua_usertype(tolua_S,"SIX_ListViewCell");
 tolua_usertype(tolua_S,"CCTableViewDataSource");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"CCScrollView");
 tolua_usertype(tolua_S,"ccColor4B");
 tolua_usertype(tolua_S,"SIX_UILayer");
 tolua_usertype(tolua_S,"CCTableViewCell");
 tolua_usertype(tolua_S,"CCTableView");
}

/* method: init of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_init00
static int tolua_SIX_ListView_SIX_ListView_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: initWithColor of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_initWithColor00
static int tolua_SIX_ListView_SIX_ListView_initWithColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*color,width,height);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_create00
static int tolua_SIX_ListView_SIX_ListView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"SIX_UILayer",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,8,"SIX_ScrollBar",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  CCPoint offset = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,4,0));
  CCSize cellSize = *((CCSize*)  tolua_tousertype(tolua_S,5,0));
  int pViewDirection = ((int)  tolua_tonumber(tolua_S,6,0));
  SIX_UILayer* pContainer = ((SIX_UILayer*)  tolua_tousertype(tolua_S,7,0));
  SIX_ScrollBar* pScrollBar = ((SIX_ScrollBar*)  tolua_tousertype(tolua_S,8,0));
  {
   SIX_ListView* tolua_ret = (SIX_ListView*)  SIX_ListView::create(*color,offset,size,cellSize,pViewDirection,pContainer,pScrollBar);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListView");
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

/* method: new of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_new00
static int tolua_SIX_ListView_SIX_ListView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"SIX_UILayer",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"SIX_ScrollBar",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint offset = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  CCSize cellSize = *((CCSize*)  tolua_tousertype(tolua_S,4,0));
  int pViewDirection = ((int)  tolua_tonumber(tolua_S,5,0));
  SIX_UILayer* pContainer = ((SIX_UILayer*)  tolua_tousertype(tolua_S,6,0));
  SIX_ScrollBar* pScrollBar = ((SIX_ScrollBar*)  tolua_tousertype(tolua_S,7,0));
  {
   SIX_ListView* tolua_ret = (SIX_ListView*)  Mtolua_new((SIX_ListView)(offset,size,cellSize,pViewDirection,pContainer,pScrollBar));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListView");
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

/* method: new_local of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_new00_local
static int tolua_SIX_ListView_SIX_ListView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"SIX_UILayer",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"SIX_ScrollBar",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint offset = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  CCSize cellSize = *((CCSize*)  tolua_tousertype(tolua_S,4,0));
  int pViewDirection = ((int)  tolua_tonumber(tolua_S,5,0));
  SIX_UILayer* pContainer = ((SIX_UILayer*)  tolua_tousertype(tolua_S,6,0));
  SIX_ScrollBar* pScrollBar = ((SIX_ScrollBar*)  tolua_tousertype(tolua_S,7,0));
  {
   SIX_ListView* tolua_ret = (SIX_ListView*)  Mtolua_new((SIX_ListView)(offset,size,cellSize,pViewDirection,pContainer,pScrollBar));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListView");
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

/* method: delete of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_delete00
static int tolua_SIX_ListView_SIX_ListView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: cellSizeForTable of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_cellSizeForTable00
static int tolua_SIX_ListView_SIX_ListView_cellSizeForTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: tableCellAtIndex of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_tableCellAtIndex00
static int tolua_SIX_ListView_SIX_ListView_tableCellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: numberOfCellsInTableView of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_numberOfCellsInTableView00
static int tolua_SIX_ListView_SIX_ListView_numberOfCellsInTableView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: tableCellTouched of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_tableCellTouched00
static int tolua_SIX_ListView_SIX_ListView_tableCellTouched00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCTableViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollViewDidScroll of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_scrollViewDidScroll00
static int tolua_SIX_ListView_SIX_ListView_scrollViewDidScroll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollViewDidZoom of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_scrollViewDidZoom00
static int tolua_SIX_ListView_SIX_ListView_scrollViewDidZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetCell of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_GetCell00
static int tolua_SIX_ListView_SIX_ListView_GetCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCell'", NULL);
#endif
  {
   SIX_ListViewCell* tolua_ret = (SIX_ListViewCell*)  self->GetCell(idx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_ListViewCell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AppendCell of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_AppendCell00
static int tolua_SIX_ListView_SIX_ListView_AppendCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
  SIX_ListViewCell* pItem = ((SIX_ListViewCell*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AppendCell'", NULL);
#endif
  {
   self->AppendCell(pItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AppendCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddCell of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_AddCell00
static int tolua_SIX_ListView_SIX_ListView_AddCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
  SIX_ListViewCell* pItem = ((SIX_ListViewCell*)  tolua_tousertype(tolua_S,2,0));
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddCell'", NULL);
#endif
  {
   self->AddCell(pItem,idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveCell of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_RemoveCell00
static int tolua_SIX_ListView_SIX_ListView_RemoveCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool bRelease = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveCell'", NULL);
#endif
  {
   self->RemoveCell(idx,bRelease);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveCell of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_RemoveCell01
static int tolua_SIX_ListView_SIX_ListView_RemoveCell01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_ListViewCell",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
  SIX_ListViewCell* pItem = ((SIX_ListViewCell*)  tolua_tousertype(tolua_S,2,0));
  bool bRelease = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveCell'", NULL);
#endif
  {
   self->RemoveCell(pItem,bRelease);
  }
 }
 return 0;
tolua_lerror:
 return tolua_SIX_ListView_SIX_ListView_RemoveCell00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveCellAll of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_RemoveCellAll00
static int tolua_SIX_ListView_SIX_ListView_RemoveCellAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveCellAll'", NULL);
#endif
  {
   self->RemoveCellAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveCellAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCellCount of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_GetCellCount00
static int tolua_SIX_ListView_SIX_ListView_GetCellCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCellCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetCellCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCellCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: refresh of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_refresh00
static int tolua_SIX_ListView_SIX_ListView_refresh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'refresh'", NULL);
#endif
  {
   self->refresh();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'refresh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainer of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_SIX_ListView_SIX_ListView_getContainer00
static int tolua_SIX_ListView_SIX_ListView_getContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainer'", NULL);
#endif
  {
   CCTableView* tolua_ret = (CCTableView*)  self->getContainer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableView");
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

/* get function: __CCTableViewDataSource__ of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_get_SIX_ListView___CCTableViewDataSource__
static int tolua_get_SIX_ListView___CCTableViewDataSource__(lua_State* tolua_S)
{
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTableViewDataSource__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTableViewDataSource*>(self), "CCTableViewDataSource");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTableViewDataSource*)self), "CCTableViewDataSource");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTableViewDelegate__ of class  SIX_ListView */
#ifndef TOLUA_DISABLE_tolua_get_SIX_ListView___CCTableViewDelegate__
static int tolua_get_SIX_ListView___CCTableViewDelegate__(lua_State* tolua_S)
{
  SIX_ListView* self = (SIX_ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTableViewDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTableViewDelegate*>(self), "CCTableViewDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTableViewDelegate*)self), "CCTableViewDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_ListView_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_ListView_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_ListView","SIX_ListView","CCLayerColor",tolua_collect_SIX_ListView);
  #else
  tolua_cclass(tolua_S,"SIX_ListView","SIX_ListView","CCLayerColor",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_ListView");
   tolua_function(tolua_S,"init",tolua_SIX_ListView_SIX_ListView_init00);
   tolua_function(tolua_S,"initWithColor",tolua_SIX_ListView_SIX_ListView_initWithColor00);
   tolua_function(tolua_S,"create",tolua_SIX_ListView_SIX_ListView_create00);
   tolua_function(tolua_S,"new",tolua_SIX_ListView_SIX_ListView_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_ListView_SIX_ListView_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_ListView_SIX_ListView_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_ListView_SIX_ListView_delete00);
   tolua_function(tolua_S,"cellSizeForTable",tolua_SIX_ListView_SIX_ListView_cellSizeForTable00);
   tolua_function(tolua_S,"tableCellAtIndex",tolua_SIX_ListView_SIX_ListView_tableCellAtIndex00);
   tolua_function(tolua_S,"numberOfCellsInTableView",tolua_SIX_ListView_SIX_ListView_numberOfCellsInTableView00);
   tolua_function(tolua_S,"tableCellTouched",tolua_SIX_ListView_SIX_ListView_tableCellTouched00);
   tolua_function(tolua_S,"scrollViewDidScroll",tolua_SIX_ListView_SIX_ListView_scrollViewDidScroll00);
   tolua_function(tolua_S,"scrollViewDidZoom",tolua_SIX_ListView_SIX_ListView_scrollViewDidZoom00);
   tolua_function(tolua_S,"GetCell",tolua_SIX_ListView_SIX_ListView_GetCell00);
   tolua_function(tolua_S,"AppendCell",tolua_SIX_ListView_SIX_ListView_AppendCell00);
   tolua_function(tolua_S,"AddCell",tolua_SIX_ListView_SIX_ListView_AddCell00);
   tolua_function(tolua_S,"RemoveCell",tolua_SIX_ListView_SIX_ListView_RemoveCell00);
   tolua_function(tolua_S,"RemoveCell",tolua_SIX_ListView_SIX_ListView_RemoveCell01);
   tolua_function(tolua_S,"RemoveCellAll",tolua_SIX_ListView_SIX_ListView_RemoveCellAll00);
   tolua_function(tolua_S,"GetCellCount",tolua_SIX_ListView_SIX_ListView_GetCellCount00);
   tolua_function(tolua_S,"refresh",tolua_SIX_ListView_SIX_ListView_refresh00);
   tolua_function(tolua_S,"getContainer",tolua_SIX_ListView_SIX_ListView_getContainer00);
   tolua_variable(tolua_S,"__CCTableViewDataSource__",tolua_get_SIX_ListView___CCTableViewDataSource__,NULL);
   tolua_variable(tolua_S,"__CCTableViewDelegate__",tolua_get_SIX_ListView___CCTableViewDelegate__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_ListView (lua_State* tolua_S) {
 return tolua_SIX_ListView_open(tolua_S);
};
#endif


/*
** Lua binding: CCSorting
** Generated automatically by tolua++-1.0.92 on 04/24/13 11:22:17.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCSorting_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCSortableObject (lua_State* tolua_S)
{
 CCSortableObject* self = (CCSortableObject*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCArrayForObjectSorting (lua_State* tolua_S)
{
 CCArrayForObjectSorting* self = (CCArrayForObjectSorting*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_CCSorting_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCArrayForObjectSorting");
 tolua_usertype(tolua_S,"CCSortableObject");
 tolua_usertype(tolua_S,"CCArray");
}

/* method: delete of class  CCSortableObject */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCSortableObject_delete00
static int tolua_CCSorting_CCSortableObject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSortableObject* self = (CCSortableObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setObjectID of class  CCSortableObject */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCSortableObject_setObjectID00
static int tolua_CCSorting_CCSortableObject_setObjectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSortableObject* self = (CCSortableObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned int objectID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setObjectID'", NULL);
#endif
  {
   self->setObjectID(objectID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getObjectID of class  CCSortableObject */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCSortableObject_getObjectID00
static int tolua_CCSorting_CCSortableObject_getObjectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSortableObject* self = (CCSortableObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getObjectID'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getObjectID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_new00
static int tolua_CCSorting_CCArrayForObjectSorting_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArrayForObjectSorting* tolua_ret = (CCArrayForObjectSorting*)  Mtolua_new((CCArrayForObjectSorting)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArrayForObjectSorting");
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

/* method: new_local of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_new00_local
static int tolua_CCSorting_CCArrayForObjectSorting_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArrayForObjectSorting* tolua_ret = (CCArrayForObjectSorting*)  Mtolua_new((CCArrayForObjectSorting)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArrayForObjectSorting");
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

/* method: insertSortedObject of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_insertSortedObject00
static int tolua_CCSorting_CCArrayForObjectSorting_insertSortedObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArrayForObjectSorting* self = (CCArrayForObjectSorting*)  tolua_tousertype(tolua_S,1,0);
  CCSortableObject* object = ((CCSortableObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertSortedObject'", NULL);
#endif
  {
   self->insertSortedObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertSortedObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSortedObject of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_removeSortedObject00
static int tolua_CCSorting_CCArrayForObjectSorting_removeSortedObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArrayForObjectSorting* self = (CCArrayForObjectSorting*)  tolua_tousertype(tolua_S,1,0);
  CCSortableObject* object = ((CCSortableObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSortedObject'", NULL);
#endif
  {
   self->removeSortedObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSortedObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setObjectID_ofSortedObject of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_setObjectID_ofSortedObject00
static int tolua_CCSorting_CCArrayForObjectSorting_setObjectID_ofSortedObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArrayForObjectSorting* self = (CCArrayForObjectSorting*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  CCSortableObject* object = ((CCSortableObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setObjectID_ofSortedObject'", NULL);
#endif
  {
   self->setObjectID_ofSortedObject(tag,object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setObjectID_ofSortedObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: objectWithObjectID of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_objectWithObjectID00
static int tolua_CCSorting_CCArrayForObjectSorting_objectWithObjectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArrayForObjectSorting* self = (CCArrayForObjectSorting*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'objectWithObjectID'", NULL);
#endif
  {
   CCSortableObject* tolua_ret = (CCSortableObject*)  self->objectWithObjectID(tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSortableObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'objectWithObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getObjectWithObjectID of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_getObjectWithObjectID00
static int tolua_CCSorting_CCArrayForObjectSorting_getObjectWithObjectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArrayForObjectSorting* self = (CCArrayForObjectSorting*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getObjectWithObjectID'", NULL);
#endif
  {
   CCSortableObject* tolua_ret = (CCSortableObject*)  self->getObjectWithObjectID(tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSortableObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getObjectWithObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: indexOfSortedObject of class  CCArrayForObjectSorting */
#ifndef TOLUA_DISABLE_tolua_CCSorting_CCArrayForObjectSorting_indexOfSortedObject00
static int tolua_CCSorting_CCArrayForObjectSorting_indexOfSortedObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArrayForObjectSorting",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSortableObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArrayForObjectSorting* self = (CCArrayForObjectSorting*)  tolua_tousertype(tolua_S,1,0);
  CCSortableObject* obj = ((CCSortableObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'indexOfSortedObject'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->indexOfSortedObject(obj);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'indexOfSortedObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCSorting_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCSorting_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCSortableObject","CCSortableObject","",tolua_collect_CCSortableObject);
  #else
  tolua_cclass(tolua_S,"CCSortableObject","CCSortableObject","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCSortableObject");
   tolua_function(tolua_S,"delete",tolua_CCSorting_CCSortableObject_delete00);
   tolua_function(tolua_S,"setObjectID",tolua_CCSorting_CCSortableObject_setObjectID00);
   tolua_function(tolua_S,"getObjectID",tolua_CCSorting_CCSortableObject_getObjectID00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCArrayForObjectSorting","CCArrayForObjectSorting","CCArray",tolua_collect_CCArrayForObjectSorting);
  #else
  tolua_cclass(tolua_S,"CCArrayForObjectSorting","CCArrayForObjectSorting","CCArray",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCArrayForObjectSorting");
   tolua_function(tolua_S,"new",tolua_CCSorting_CCArrayForObjectSorting_new00);
   tolua_function(tolua_S,"new_local",tolua_CCSorting_CCArrayForObjectSorting_new00_local);
   tolua_function(tolua_S,".call",tolua_CCSorting_CCArrayForObjectSorting_new00_local);
   tolua_function(tolua_S,"insertSortedObject",tolua_CCSorting_CCArrayForObjectSorting_insertSortedObject00);
   tolua_function(tolua_S,"removeSortedObject",tolua_CCSorting_CCArrayForObjectSorting_removeSortedObject00);
   tolua_function(tolua_S,"setObjectID_ofSortedObject",tolua_CCSorting_CCArrayForObjectSorting_setObjectID_ofSortedObject00);
   tolua_function(tolua_S,"objectWithObjectID",tolua_CCSorting_CCArrayForObjectSorting_objectWithObjectID00);
   tolua_function(tolua_S,"getObjectWithObjectID",tolua_CCSorting_CCArrayForObjectSorting_getObjectWithObjectID00);
   tolua_function(tolua_S,"indexOfSortedObject",tolua_CCSorting_CCArrayForObjectSorting_indexOfSortedObject00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCSorting (lua_State* tolua_S) {
 return tolua_CCSorting_open(tolua_S);
};
#endif


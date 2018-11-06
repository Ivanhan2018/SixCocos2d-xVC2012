/*
** Lua binding: SIX_Func
** Generated automatically by tolua++-1.0.92 on 05/19/13 12:59:47.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SIX_Func_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SIX_Func (lua_State* tolua_S)
{
 SIX_Func* self = (SIX_Func*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_LONGLONG (lua_State* tolua_S)
{
 SIX_LONGLONG* self = (SIX_LONGLONG*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LONGLONG (lua_State* tolua_S)
{
 LONGLONG* self = (LONGLONG*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SIX_Data (lua_State* tolua_S)
{
 SIX_Data* self = (SIX_Data*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_SIX_Func_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIX_LONGLONG");
 tolua_usertype(tolua_S,"LONGLONG");
 tolua_usertype(tolua_S,"CCString");
 tolua_usertype(tolua_S,"SIX_Func");
 tolua_usertype(tolua_S,"SIX_Data");
}

/* method: new of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_LONGLONG_new00
static int tolua_SIX_Func_SIX_LONGLONG_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_LONGLONG",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LONGLONG",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LONGLONG ll = *((LONGLONG*)  tolua_tousertype(tolua_S,2,0));
  {
   SIX_LONGLONG* tolua_ret = (SIX_LONGLONG*)  Mtolua_new((SIX_LONGLONG)(ll));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_LONGLONG");
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

/* method: new_local of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_LONGLONG_new00_local
static int tolua_SIX_Func_SIX_LONGLONG_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_LONGLONG",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LONGLONG",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LONGLONG ll = *((LONGLONG*)  tolua_tousertype(tolua_S,2,0));
  {
   SIX_LONGLONG* tolua_ret = (SIX_LONGLONG*)  Mtolua_new((SIX_LONGLONG)(ll));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_LONGLONG");
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

/* method: delete of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_LONGLONG_delete00
static int tolua_SIX_Func_SIX_LONGLONG_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_LONGLONG",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_LONGLONG* self = (SIX_LONGLONG*)  tolua_tousertype(tolua_S,1,0);
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

/* method: MakeLongLong of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_LONGLONG_MakeLongLong00
static int tolua_SIX_Func_SIX_LONGLONG_MakeLongLong00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_LONGLONG",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_LONGLONG* self = (SIX_LONGLONG*)  tolua_tousertype(tolua_S,1,0);
  unsigned int LO32 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int HI32 = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MakeLongLong'", NULL);
#endif
  {
   LONGLONG tolua_ret = (LONGLONG)  self->MakeLongLong(LO32,HI32);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LONGLONG)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LONGLONG");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LONGLONG));
     tolua_pushusertype(tolua_S,tolua_obj,"LONGLONG");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeLongLong'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LO32 of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_get_SIX_LONGLONG_unsigned_LO32
static int tolua_get_SIX_LONGLONG_unsigned_LO32(lua_State* tolua_S)
{
  SIX_LONGLONG* self = (SIX_LONGLONG*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LO32'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->LO32);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: LO32 of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_set_SIX_LONGLONG_unsigned_LO32
static int tolua_set_SIX_LONGLONG_unsigned_LO32(lua_State* tolua_S)
{
  SIX_LONGLONG* self = (SIX_LONGLONG*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LO32'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->LO32 = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HI32 of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_get_SIX_LONGLONG_unsigned_HI32
static int tolua_get_SIX_LONGLONG_unsigned_HI32(lua_State* tolua_S)
{
  SIX_LONGLONG* self = (SIX_LONGLONG*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HI32'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->HI32);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: HI32 of class  SIX_LONGLONG */
#ifndef TOLUA_DISABLE_tolua_set_SIX_LONGLONG_unsigned_HI32
static int tolua_set_SIX_LONGLONG_unsigned_HI32(lua_State* tolua_S)
{
  SIX_LONGLONG* self = (SIX_LONGLONG*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HI32'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->HI32 = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Data_new00
static int tolua_SIX_Func_SIX_Data_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Data",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Data* tolua_ret = (SIX_Data*)  Mtolua_new((SIX_Data)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Data");
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

/* method: new_local of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Data_new00_local
static int tolua_SIX_Func_SIX_Data_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Data",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Data* tolua_ret = (SIX_Data*)  Mtolua_new((SIX_Data)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Data");
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

/* method: delete of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Data_delete00
static int tolua_SIX_Func_SIX_Data_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Data",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: a of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_get_SIX_Data_a
static int tolua_get_SIX_Data_a(lua_State* tolua_S)
{
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->a);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_set_SIX_Data_a
static int tolua_set_SIX_Data_a(lua_State* tolua_S)
{
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->a = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_get_SIX_Data_b
static int tolua_get_SIX_Data_b(lua_State* tolua_S)
{
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->b);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_set_SIX_Data_b
static int tolua_set_SIX_Data_b(lua_State* tolua_S)
{
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: c of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_get_SIX_Data_c_ptr
static int tolua_get_SIX_Data_c_ptr(lua_State* tolua_S)
{
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'c'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->c,"CCString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: c of class  SIX_Data */
#ifndef TOLUA_DISABLE_tolua_set_SIX_Data_c_ptr
static int tolua_set_SIX_Data_c_ptr(lua_State* tolua_S)
{
  SIX_Data* self = (SIX_Data*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'c'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->c = ((CCString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SIX_Func */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Func_new00
static int tolua_SIX_Func_SIX_Func_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Func",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Func* tolua_ret = (SIX_Func*)  Mtolua_new((SIX_Func)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Func");
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

/* method: new_local of class  SIX_Func */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Func_new00_local
static int tolua_SIX_Func_SIX_Func_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SIX_Func",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SIX_Func* tolua_ret = (SIX_Func*)  Mtolua_new((SIX_Func)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Func");
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

/* method: delete of class  SIX_Func */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Func_delete00
static int tolua_SIX_Func_SIX_Func_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Func",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Func* self = (SIX_Func*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Sum of class  SIX_Func */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Func_Sum00
static int tolua_SIX_Func_SIX_Func_Sum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Func",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Func* self = (SIX_Func*)  tolua_tousertype(tolua_S,1,0);
  int a = ((int)  tolua_tonumber(tolua_S,2,0));
  int b = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Sum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Sum(a,b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetData of class  SIX_Func */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Func_GetData00
static int tolua_SIX_Func_SIX_Func_GetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Func",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Func* self = (SIX_Func*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetData'", NULL);
#endif
  {
   SIX_Data* tolua_ret = (SIX_Data*)  self->GetData();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SIX_Data");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendData of class  SIX_Func */
#ifndef TOLUA_DISABLE_tolua_SIX_Func_SIX_Func_SendData00
static int tolua_SIX_Func_SIX_Func_SendData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SIX_Func",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SIX_Data",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SIX_Func* self = (SIX_Func*)  tolua_tousertype(tolua_S,1,0);
  SIX_Data* pInfo = ((SIX_Data*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendData'", NULL);
#endif
  {
   int tolua_ret = (int)  self->SendData(pInfo);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SIX_Func_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_SIX_Func_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"TEST_COMMON",TEST_COMMON);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_LONGLONG","SIX_LONGLONG","",tolua_collect_SIX_LONGLONG);
  #else
  tolua_cclass(tolua_S,"SIX_LONGLONG","SIX_LONGLONG","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_LONGLONG");
   tolua_function(tolua_S,"new",tolua_SIX_Func_SIX_LONGLONG_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Func_SIX_LONGLONG_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Func_SIX_LONGLONG_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Func_SIX_LONGLONG_delete00);
   tolua_function(tolua_S,"MakeLongLong",tolua_SIX_Func_SIX_LONGLONG_MakeLongLong00);
   tolua_variable(tolua_S,"LO32",tolua_get_SIX_LONGLONG_unsigned_LO32,tolua_set_SIX_LONGLONG_unsigned_LO32);
   tolua_variable(tolua_S,"HI32",tolua_get_SIX_LONGLONG_unsigned_HI32,tolua_set_SIX_LONGLONG_unsigned_HI32);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_Data","SIX_Data","",tolua_collect_SIX_Data);
  #else
  tolua_cclass(tolua_S,"SIX_Data","SIX_Data","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_Data");
   tolua_function(tolua_S,"new",tolua_SIX_Func_SIX_Data_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Func_SIX_Data_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Func_SIX_Data_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Func_SIX_Data_delete00);
   tolua_variable(tolua_S,"a",tolua_get_SIX_Data_a,tolua_set_SIX_Data_a);
   tolua_variable(tolua_S,"b",tolua_get_SIX_Data_b,tolua_set_SIX_Data_b);
   tolua_variable(tolua_S,"c",tolua_get_SIX_Data_c_ptr,tolua_set_SIX_Data_c_ptr);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SIX_Func","SIX_Func","",tolua_collect_SIX_Func);
  #else
  tolua_cclass(tolua_S,"SIX_Func","SIX_Func","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SIX_Func");
   tolua_function(tolua_S,"new",tolua_SIX_Func_SIX_Func_new00);
   tolua_function(tolua_S,"new_local",tolua_SIX_Func_SIX_Func_new00_local);
   tolua_function(tolua_S,".call",tolua_SIX_Func_SIX_Func_new00_local);
   tolua_function(tolua_S,"delete",tolua_SIX_Func_SIX_Func_delete00);
   tolua_function(tolua_S,"Sum",tolua_SIX_Func_SIX_Func_Sum00);
   tolua_function(tolua_S,"GetData",tolua_SIX_Func_SIX_Func_GetData00);
   tolua_function(tolua_S,"SendData",tolua_SIX_Func_SIX_Func_SendData00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SIX_Func (lua_State* tolua_S) {
 return tolua_SIX_Func_open(tolua_S);
};
#endif


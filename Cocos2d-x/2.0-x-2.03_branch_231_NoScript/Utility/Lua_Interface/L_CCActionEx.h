/*
** Lua binding: CCActionEx
** Generated automatically by tolua++-1.0.92 on 04/28/13 11:18:09.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CCActionEx_open (lua_State* tolua_S);


/* function to register type */
static void tolua_CCActionEx_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CircleAction");
 tolua_usertype(tolua_S,"CCActionInterval");
 tolua_usertype(tolua_S,"myAction");
}

/* method: create of class  CircleAction */
#ifndef TOLUA_DISABLE_tolua_CCActionEx_CircleAction_create00
static int tolua_CCActionEx_CircleAction_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CircleAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  int direction = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   CircleAction* tolua_ret = (CircleAction*)  CircleAction::create(duration,*position,direction);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CircleAction");
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

/* method: create of class  myAction */
#ifndef TOLUA_DISABLE_tolua_CCActionEx_myAction_create00
static int tolua_CCActionEx_myAction_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"myAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   myAction* tolua_ret = (myAction*)  myAction::create(duration,func);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"myAction");
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

/* method: createCircle of class  myAction */
#ifndef TOLUA_DISABLE_tolua_CCActionEx_myAction_createCircle00
static int tolua_CCActionEx_myAction_createCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"myAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,3,0));
  const CCPoint* startP = ((const CCPoint*)  tolua_tousertype(tolua_S,4,0));
  const CCPoint* centerP = ((const CCPoint*)  tolua_tousertype(tolua_S,5,0));
  float direction = ((float)  tolua_tonumber(tolua_S,6,0));
  {
   myAction* tolua_ret = (myAction*)  myAction::createCircle(duration,func,*startP,*centerP,direction);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"myAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createCycloid of class  myAction */
#ifndef TOLUA_DISABLE_tolua_CCActionEx_myAction_createCycloid00
static int tolua_CCActionEx_myAction_createCycloid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"myAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,7,&tolua_err) || !tolua_isusertype(tolua_S,7,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,3,0));
  const CCPoint* startP = ((const CCPoint*)  tolua_tousertype(tolua_S,4,0));
  const CCPoint* rdeltArg = ((const CCPoint*)  tolua_tousertype(tolua_S,5,0));
  float direction = ((float)  tolua_tonumber(tolua_S,6,0));
  const CCPoint* reserved = ((const CCPoint*)  tolua_tousertype(tolua_S,7,0));
  {
   myAction* tolua_ret = (myAction*)  myAction::createCycloid(duration,func,*startP,*rdeltArg,direction,*reserved);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"myAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createCycloid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCActionEx_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_CCActionEx_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CircleAction","CircleAction","CCActionInterval",NULL);
  tolua_beginmodule(tolua_S,"CircleAction");
   tolua_function(tolua_S,"create",tolua_CCActionEx_CircleAction_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"myAction","myAction","CCActionInterval",NULL);
  tolua_beginmodule(tolua_S,"myAction");
   tolua_function(tolua_S,"create",tolua_CCActionEx_myAction_create00);
   tolua_function(tolua_S,"createCircle",tolua_CCActionEx_myAction_createCircle00);
   tolua_function(tolua_S,"createCycloid",tolua_CCActionEx_myAction_createCycloid00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCActionEx (lua_State* tolua_S) {
 return tolua_CCActionEx_open(tolua_S);
};
#endif


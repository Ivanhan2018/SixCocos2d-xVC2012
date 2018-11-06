/*
** Lua binding: GameSkeletonMsgCode
** Generated automatically by tolua++-1.0.92 on 05/23/13 16:14:28.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_GameSkeletonMsgCode_open (lua_State* tolua_S);


/* function to register type */
static void tolua_GameSkeletonMsgCode_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_GameSkeletonMsgCode_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_GameSkeletonMsgCode_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"ROOM_MAIN",ROOM_MAIN);
  tolua_constant(tolua_S,"ROOM_MAIN_DB",ROOM_MAIN_DB);
  tolua_constant(tolua_S,"MANAGER_MAIN",MANAGER_MAIN);
  tolua_constant(tolua_S,"MATCH_MAIN",MATCH_MAIN);
  tolua_constant(tolua_S,"TASK_MAIN",TASK_MAIN);
  tolua_constant(tolua_S,"PROP_MAIN",PROP_MAIN);
  tolua_constant(tolua_S,"TABLE_MAIN",TABLE_MAIN);
  tolua_constant(tolua_S,"ROOM_SUB_MY_TEST",ROOM_SUB_MY_TEST);
  tolua_constant(tolua_S,"ROOM_SUB_LOGIN",ROOM_SUB_LOGIN);
  tolua_constant(tolua_S,"ROOM_SUB_PASS_VERIFY",ROOM_SUB_PASS_VERIFY);
  tolua_constant(tolua_S,"ROOM_SUB_LOGIN_SUCC",ROOM_SUB_LOGIN_SUCC);
  tolua_constant(tolua_S,"ROOM_SUB_LOGIN_FAIL",ROOM_SUB_LOGIN_FAIL);
  tolua_constant(tolua_S,"ROOM_SUB_USER_INFO",ROOM_SUB_USER_INFO);
  tolua_constant(tolua_S,"ROOM_SUB_TABLE_LIST",ROOM_SUB_TABLE_LIST);
  tolua_constant(tolua_S,"ROOM_SUB_TABLE_LIST_OVER",ROOM_SUB_TABLE_LIST_OVER);
  tolua_constant(tolua_S,"ROOM_SUB_USER_LIST",ROOM_SUB_USER_LIST);
  tolua_constant(tolua_S,"ROOM_SUB_USER_LIST_OVER",ROOM_SUB_USER_LIST_OVER);
  tolua_constant(tolua_S,"ROOM_SUB_LEAVE_ROOM",ROOM_SUB_LEAVE_ROOM);
  tolua_constant(tolua_S,"ROOM_SUB_RECOME",ROOM_SUB_RECOME);
  tolua_constant(tolua_S,"ROOM_SUB_WRITE_SCORE",ROOM_SUB_WRITE_SCORE);
  tolua_constant(tolua_S,"ROOM_SUB_WRITE_SCORE_RESULT",ROOM_SUB_WRITE_SCORE_RESULT);
  tolua_constant(tolua_S,"MANAGER_SUB_POWER_ERR",MANAGER_SUB_POWER_ERR);
  tolua_constant(tolua_S,"MANAGER_SUB_SET_ROOM_STATE",MANAGER_SUB_SET_ROOM_STATE);
  tolua_constant(tolua_S,"MANAGER_SUB_TICK_ONE_LEAVE_SEAT",MANAGER_SUB_TICK_ONE_LEAVE_SEAT);
  tolua_constant(tolua_S,"MANAGER_SUB_TICK_TABLE_LEAVE_SEAT",MANAGER_SUB_TICK_TABLE_LEAVE_SEAT);
  tolua_constant(tolua_S,"MANAGER_SUB_TICK_ALL_LEAVE_SEAT",MANAGER_SUB_TICK_ALL_LEAVE_SEAT);
  tolua_constant(tolua_S,"MANAGER_SUB_TICK_USER_OUT_ROOM",MANAGER_SUB_TICK_USER_OUT_ROOM);
  tolua_constant(tolua_S,"MATCH_SUB_TEST",MATCH_SUB_TEST);
  tolua_constant(tolua_S,"TASK_SUB_TEST",TASK_SUB_TEST);
  tolua_constant(tolua_S,"PROP_SUB_TEST",PROP_SUB_TEST);
  tolua_constant(tolua_S,"TABLE_SUB_SITDOWN",TABLE_SUB_SITDOWN);
  tolua_constant(tolua_S,"TABLE_SUB_FIRE",TABLE_SUB_FIRE);
  tolua_constant(tolua_S,"TABLE_SUB_WRITE_SCORE",TABLE_SUB_WRITE_SCORE);
  tolua_constant(tolua_S,"TABLE_SUB_LEAVE_SEAT",TABLE_SUB_LEAVE_SEAT);
  tolua_constant(tolua_S,"TABLE_SUB_RAISE_HAND",TABLE_SUB_RAISE_HAND);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_GameSkeletonMsgCode (lua_State* tolua_S) {
 return tolua_GameSkeletonMsgCode_open(tolua_S);
};
#endif


/*
** Lua binding: PublicMacro
** Generated automatically by tolua++-1.0.92 on 12/24/17 11:12:19.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_PublicMacro_open (lua_State* tolua_S);


/* function to register type */
static void tolua_PublicMacro_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_PublicMacro_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_PublicMacro_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"DATA_SIZE_CONTRAST(size1_size2){",DATA_SIZE_CONTRAST(size1,size2){);
  tolua_constant(tolua_S,"INVALID_CHANNEL_NO",INVALID_CHANNEL_NO);
  tolua_constant(tolua_S,"TIMER_CHANNEL_NO",TIMER_CHANNEL_NO);
  tolua_constant(tolua_S,"PROFESSION_CHANNEL_NO",PROFESSION_CHANNEL_NO);
  tolua_constant(tolua_S,"INVALID_USER_ID",INVALID_USER_ID);
  tolua_constant(tolua_S,"INVAL_TABLE_NO",INVAL_TABLE_NO);
  tolua_constant(tolua_S,"INVAL_SEAT_NO",INVAL_SEAT_NO);
  tolua_constant(tolua_S,"IP_ADDRES_LEN",IP_ADDRES_LEN);
  tolua_constant(tolua_S,"USER_NAME_LEN",USER_NAME_LEN);
  tolua_constant(tolua_S,"USER_PASSWORD_LEN",USER_PASSWORD_LEN);
  tolua_constant(tolua_S,"USER_REAL_NAME_LEN",USER_REAL_NAME_LEN);
  tolua_constant(tolua_S,"USER_IDENTITY_CARD_LEN",USER_IDENTITY_CARD_LEN);
  tolua_constant(tolua_S,"USER_MOBILE_LEN",USER_MOBILE_LEN);
  tolua_constant(tolua_S,"DB_NAME_LEN",DB_NAME_LEN);
  tolua_constant(tolua_S,"DB_USER_NAME_LEN",DB_USER_NAME_LEN);
  tolua_constant(tolua_S,"DB_PASS_LEN",DB_PASS_LEN);
  tolua_constant(tolua_S,"ROOM_NAME_LEN",ROOM_NAME_LEN);
  tolua_constant(tolua_S,"FIGHT_TABLE_NAME_LEN",FIGHT_TABLE_NAME_LEN);
  tolua_constant(tolua_S,"ROOM_MESSAGE_LEN",ROOM_MESSAGE_LEN);
  tolua_constant(tolua_S,"GAME_MESSAGE_LEN",GAME_MESSAGE_LEN);
  tolua_constant(tolua_S,"PARAMETER_KEY_VALUE1_LEN",PARAMETER_KEY_VALUE1_LEN);
  tolua_constant(tolua_S,"GAME_NAME_LEN",GAME_NAME_LEN);
  tolua_constant(tolua_S,"PROGRESS_NAME_LEN",PROGRESS_NAME_LEN);
  tolua_constant(tolua_S,"REWARD_NAME_LEN",REWARD_NAME_LEN);
  tolua_constant(tolua_S,"ACCOUNTS_LEN",ACCOUNTS_LEN);
  tolua_constant(tolua_S,"CHAT_CONTENT_LEN",CHAT_CONTENT_LEN);
  tolua_constant(tolua_S,"MACHINE_CODE_LEN",MACHINE_CODE_LEN);
  tolua_constant(tolua_S,"GRADE_TITLE_LEN",GRADE_TITLE_LEN);
  tolua_constant(tolua_S,"TASK_NAME_LEN",TASK_NAME_LEN);
  tolua_constant(tolua_S,"FILE_NAME_LEN",FILE_NAME_LEN);
  tolua_constant(tolua_S,"ACTIVITY_NAME_LEN",ACTIVITY_NAME_LEN);
  tolua_constant(tolua_S,"ACTIVITY_TITLE_LEN",ACTIVITY_TITLE_LEN);
  tolua_constant(tolua_S,"DESCRIPTION_LEN",DESCRIPTION_LEN);
  tolua_constant(tolua_S,"TIME_LEN",TIME_LEN);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_PublicMacro (lua_State* tolua_S) {
 return tolua_PublicMacro_open(tolua_S);
};
#endif


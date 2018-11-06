/*
** Lua binding: BaseTableClient
** Generated automatically by tolua++-1.0.92 on 05/21/13 16:38:29.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_BaseTableClient_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

//static int tolua_collect_CLIENT_ROOM_INFO (lua_State* tolua_S)
//{
// CLIENT_ROOM_INFO* self = (CLIENT_ROOM_INFO*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}

static int tolua_collect_IBaseTableClient (lua_State* tolua_S)
{
 IBaseTableClient* self = (IBaseTableClient*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_BaseTableClient_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CLIENT_FRAME_PARAM");
 tolua_usertype(tolua_S,"sockaddr_in");
 tolua_usertype(tolua_S,"IBaseTableClient");
 tolua_usertype(tolua_S,"WRITE_SCORE");
 tolua_usertype(tolua_S,"BYTE");
 tolua_usertype(tolua_S,"CLIENT_ROOM_INFO");
}

/* method: delete of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_delete00
static int tolua_BaseTableClient_IBaseTableClient_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: OnConnect of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnConnect00
static int tolua_BaseTableClient_IBaseTableClient_OnConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"sockaddr_in",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  bool bIsReconnect = ((bool)  tolua_toboolean(tolua_S,2,0));
  sockaddr_in addrConnect = *((sockaddr_in*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnConnect'", NULL);
#endif
  {
   self->OnConnect(bIsReconnect,addrConnect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnConnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnConnectFail of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnConnectFail00
static int tolua_BaseTableClient_IBaseTableClient_OnConnectFail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"sockaddr_in",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  bool bIsReconnect = ((bool)  tolua_toboolean(tolua_S,2,0));
  int iError = ((int)  tolua_tonumber(tolua_S,3,0));
  sockaddr_in addrConnect = *((sockaddr_in*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnConnectFail'", NULL);
#endif
  {
   self->OnConnectFail(bIsReconnect,iError,addrConnect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnConnectFail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnCommError of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnCommError00
static int tolua_BaseTableClient_IBaseTableClient_OnCommError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  char* pszError = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnCommError'", NULL);
#endif
  {
   self->OnCommError(pszError);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnCommError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSend of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnSend00
static int tolua_BaseTableClient_IBaseTableClient_OnSend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const BYTE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  const BYTE* pData = ((const BYTE*)  tolua_tousertype(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSend'", NULL);
#endif
  {
   self->OnSend(iMainCode,iSubCode,pData,iDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSendFailed of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnSendFailed00
static int tolua_BaseTableClient_IBaseTableClient_OnSendFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const BYTE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  const BYTE* pData = ((const BYTE*)  tolua_tousertype(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSendFailed'", NULL);
#endif
  {
   self->OnSendFailed(iMainCode,iSubCode,pData,iDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSendFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnClose of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnClose00
static int tolua_BaseTableClient_IBaseTableClient_OnClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  bool bClientClose = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnClose'", NULL);
#endif
  {
   self->OnClose(bClientClose);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnTableMsg of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_OnTableMsg00
static int tolua_BaseTableClient_IBaseTableClient_OnTableMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const BYTE",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  const BYTE* pData = ((const BYTE*)  tolua_tousertype(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnTableMsg'", NULL);
#endif
  {
   self->OnTableMsg(iMainCode,iSubCode,pData,iDataLen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnTableMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_init00
static int tolua_BaseTableClient_IBaseTableClient_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CLIENT_ROOM_INFO",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CLIENT_FRAME_PARAM",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  const CLIENT_ROOM_INFO* vRoomClientInfo = ((const CLIENT_ROOM_INFO*)  tolua_tousertype(tolua_S,2,0));
  const CLIENT_FRAME_PARAM* vFrameParam = ((const CLIENT_FRAME_PARAM*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   int tolua_ret = (int)  self->init(*vRoomClientInfo,*vFrameParam);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: start of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_start00
static int tolua_BaseTableClient_IBaseTableClient_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   int tolua_ret = (int)  self->start();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_stop00
static int tolua_BaseTableClient_IBaseTableClient_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   int tolua_ret = (int)  self->stop();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send_data of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_send_data00
static int tolua_BaseTableClient_IBaseTableClient_send_data00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
  void* pData = ((void*)  tolua_touserdata(tolua_S,4,0));
  int iDataLen = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send_data'", NULL);
#endif
  {
   int tolua_ret = (int)  self->send_data(iMainCode,iSubCode,pData,iDataLen);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send_data'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send_data of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_send_data01
static int tolua_BaseTableClient_IBaseTableClient_send_data01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iMainCode = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSubCode = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send_data'", NULL);
#endif
  {
   int tolua_ret = (int)  self->send_data(iMainCode,iSubCode);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BaseTableClient_IBaseTableClient_send_data00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_close00
static int tolua_BaseTableClient_IBaseTableClient_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  bool bClientClose = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->close(bClientClose);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: login_room of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_login_room00
static int tolua_BaseTableClient_IBaseTableClient_login_room00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'login_room'", NULL);
#endif
  {
   int tolua_ret = (int)  self->login_room();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'login_room'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leave_room of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_leave_room00
static int tolua_BaseTableClient_IBaseTableClient_leave_room00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'leave_room'", NULL);
#endif
  {
   int tolua_ret = (int)  self->leave_room();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leave_room'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sit_down of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_sit_down00
static int tolua_BaseTableClient_IBaseTableClient_sit_down00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iTableNo = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSeatNo = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sit_down'", NULL);
#endif
  {
   int tolua_ret = (int)  self->sit_down(iTableNo,iSeatNo);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sit_down'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leave_seat of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_leave_seat00
static int tolua_BaseTableClient_IBaseTableClient_leave_seat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'leave_seat'", NULL);
#endif
  {
   int tolua_ret = (int)  self->leave_seat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leave_seat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: query_user_list of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_query_user_list00
static int tolua_BaseTableClient_IBaseTableClient_query_user_list00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'query_user_list'", NULL);
#endif
  {
   int tolua_ret = (int)  self->query_user_list();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'query_user_list'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: write_score of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_write_score00
static int tolua_BaseTableClient_IBaseTableClient_write_score00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const WRITE_SCORE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  const WRITE_SCORE* score = ((const WRITE_SCORE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'write_score'", NULL);
#endif
  {
   int tolua_ret = (int)  self->write_score(*score);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'write_score'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tick_one_leave_seat of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_tick_one_leave_seat00
static int tolua_BaseTableClient_IBaseTableClient_tick_one_leave_seat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iTableNo = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSeatNo = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tick_one_leave_seat'", NULL);
#endif
  {
   int tolua_ret = (int)  self->tick_one_leave_seat(iTableNo,iSeatNo);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tick_one_leave_seat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tick_table_leave_seat of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_tick_table_leave_seat00
static int tolua_BaseTableClient_IBaseTableClient_tick_table_leave_seat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iTableNo = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tick_table_leave_seat'", NULL);
#endif
  {
   int tolua_ret = (int)  self->tick_table_leave_seat(iTableNo);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tick_table_leave_seat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tick_all_leave_seat of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_tick_all_leave_seat00
static int tolua_BaseTableClient_IBaseTableClient_tick_all_leave_seat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tick_all_leave_seat'", NULL);
#endif
  {
   int tolua_ret = (int)  self->tick_all_leave_seat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tick_all_leave_seat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tick_user_out_room of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_tick_user_out_room00
static int tolua_BaseTableClient_IBaseTableClient_tick_user_out_room00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iTableNo = ((int)  tolua_tonumber(tolua_S,2,0));
  int iSeatNo = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tick_user_out_room'", NULL);
#endif
  {
   int tolua_ret = (int)  self->tick_user_out_room(iTableNo,iSeatNo);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tick_user_out_room'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tick_user_out_room of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_tick_user_out_room01
static int tolua_BaseTableClient_IBaseTableClient_tick_user_out_room01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
  int iTableNo = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tick_user_out_room'", NULL);
#endif
  {
   int tolua_ret = (int)  self->tick_user_out_room(iTableNo);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BaseTableClient_IBaseTableClient_tick_user_out_room00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: tick_user_out_room of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_tick_user_out_room02
static int tolua_BaseTableClient_IBaseTableClient_tick_user_out_room02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tick_user_out_room'", NULL);
#endif
  {
   int tolua_ret = (int)  self->tick_user_out_room();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BaseTableClient_IBaseTableClient_tick_user_out_room01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoomInfo of class  IBaseTableClient */
#ifndef TOLUA_DISABLE_tolua_BaseTableClient_IBaseTableClient_GetRoomInfo00
static int tolua_BaseTableClient_IBaseTableClient_GetRoomInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IBaseTableClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IBaseTableClient* self = (IBaseTableClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoomInfo'", NULL);
#endif
  {
   CLIENT_ROOM_INFO tolua_ret = (CLIENT_ROOM_INFO)  self->GetRoomInfo();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CLIENT_ROOM_INFO)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CLIENT_ROOM_INFO");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CLIENT_ROOM_INFO));
     tolua_pushusertype(tolua_S,tolua_obj,"CLIENT_ROOM_INFO");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoomInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_BaseTableClient_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_BaseTableClient_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"IBaseTableClient","IBaseTableClient","",tolua_collect_IBaseTableClient);
  #else
  tolua_cclass(tolua_S,"IBaseTableClient","IBaseTableClient","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"IBaseTableClient");
   tolua_function(tolua_S,"delete",tolua_BaseTableClient_IBaseTableClient_delete00);
   tolua_function(tolua_S,"OnConnect",tolua_BaseTableClient_IBaseTableClient_OnConnect00);
   tolua_function(tolua_S,"OnConnectFail",tolua_BaseTableClient_IBaseTableClient_OnConnectFail00);
   tolua_function(tolua_S,"OnCommError",tolua_BaseTableClient_IBaseTableClient_OnCommError00);
   tolua_function(tolua_S,"OnSend",tolua_BaseTableClient_IBaseTableClient_OnSend00);
   tolua_function(tolua_S,"OnSendFailed",tolua_BaseTableClient_IBaseTableClient_OnSendFailed00);
   tolua_function(tolua_S,"OnClose",tolua_BaseTableClient_IBaseTableClient_OnClose00);
   tolua_function(tolua_S,"OnTableMsg",tolua_BaseTableClient_IBaseTableClient_OnTableMsg00);
   tolua_function(tolua_S,"init",tolua_BaseTableClient_IBaseTableClient_init00);
   tolua_function(tolua_S,"start",tolua_BaseTableClient_IBaseTableClient_start00);
   tolua_function(tolua_S,"stop",tolua_BaseTableClient_IBaseTableClient_stop00);
   tolua_function(tolua_S,"send_data",tolua_BaseTableClient_IBaseTableClient_send_data00);
   tolua_function(tolua_S,"send_data",tolua_BaseTableClient_IBaseTableClient_send_data01);
   tolua_function(tolua_S,"close",tolua_BaseTableClient_IBaseTableClient_close00);
   tolua_function(tolua_S,"login_room",tolua_BaseTableClient_IBaseTableClient_login_room00);
   tolua_function(tolua_S,"leave_room",tolua_BaseTableClient_IBaseTableClient_leave_room00);
   tolua_function(tolua_S,"sit_down",tolua_BaseTableClient_IBaseTableClient_sit_down00);
   tolua_function(tolua_S,"leave_seat",tolua_BaseTableClient_IBaseTableClient_leave_seat00);
   tolua_function(tolua_S,"query_user_list",tolua_BaseTableClient_IBaseTableClient_query_user_list00);
   tolua_function(tolua_S,"write_score",tolua_BaseTableClient_IBaseTableClient_write_score00);
   tolua_function(tolua_S,"tick_one_leave_seat",tolua_BaseTableClient_IBaseTableClient_tick_one_leave_seat00);
   tolua_function(tolua_S,"tick_table_leave_seat",tolua_BaseTableClient_IBaseTableClient_tick_table_leave_seat00);
   tolua_function(tolua_S,"tick_all_leave_seat",tolua_BaseTableClient_IBaseTableClient_tick_all_leave_seat00);
   tolua_function(tolua_S,"tick_user_out_room",tolua_BaseTableClient_IBaseTableClient_tick_user_out_room00);
   tolua_function(tolua_S,"tick_user_out_room",tolua_BaseTableClient_IBaseTableClient_tick_user_out_room01);
   tolua_function(tolua_S,"tick_user_out_room",tolua_BaseTableClient_IBaseTableClient_tick_user_out_room02);
   tolua_function(tolua_S,"GetRoomInfo",tolua_BaseTableClient_IBaseTableClient_GetRoomInfo00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_BaseTableClient (lua_State* tolua_S) {
 return tolua_BaseTableClient_open(tolua_S);
};
#endif


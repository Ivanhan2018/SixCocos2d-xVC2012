/*
** Lua binding: collisionLib
** Generated automatically by tolua++-1.0.92 on 05/11/13 09:29:31.
** Lua template modified by Cool.Cat@2013/3/27 10:50:22
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_collisionLib_open (lua_State* tolua_S);


/* function to release collected object via destructor */
//#ifdef __cplusplus
//
//static int tolua_collect_CCPoint (lua_State* tolua_S)
//{
// CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
//	Mtolua_delete(self);
//	return 0;
//}
//#endif


/* function to register type */
static void tolua_collisionLib_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
}

/* function: segment_cross_Rect */
#ifndef TOLUA_DISABLE_tolua_collisionLib_segment_cross_Rect00
static int tolua_collisionLib_segment_cross_Rect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint v1 = *((CCPoint*)  tolua_tousertype(tolua_S,1,0));
  CCPoint v2 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint v3 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint v4 = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  CCPoint pt1 = *((CCPoint*)  tolua_tousertype(tolua_S,5,0));
  CCPoint pt2 = *((CCPoint*)  tolua_tousertype(tolua_S,6,0));
  float error = ((float)  tolua_tonumber(tolua_S,7,0));
  {
   CCPoint tolua_ret = (CCPoint)  segment_cross_Rect(v1,v2,v3,v4,pt1,pt2,error);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'segment_cross_Rect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: getReflex */
#ifndef TOLUA_DISABLE_tolua_collisionLib_getReflex00
static int tolua_collisionLib_getReflex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint v1 = *((CCPoint*)  tolua_tousertype(tolua_S,1,0));
  CCPoint v2 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint v3 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint v4 = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  CCPoint pt1 = *((CCPoint*)  tolua_tousertype(tolua_S,5,0));
  CCPoint pt2 = *((CCPoint*)  tolua_tousertype(tolua_S,6,0));
  float error = ((float)  tolua_tonumber(tolua_S,7,0));
  {
   CCPoint tolua_ret = (CCPoint)  getReflex(v1,v2,v3,v4,pt1,pt2,error);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReflex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_collisionLib_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_collisionLib_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_function(tolua_S,"segment_cross_Rect",tolua_collisionLib_segment_cross_Rect00);
  tolua_function(tolua_S,"getReflex",tolua_collisionLib_getReflex00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_collisionLib (lua_State* tolua_S) {
 return tolua_collisionLib_open(tolua_S);
};
#endif


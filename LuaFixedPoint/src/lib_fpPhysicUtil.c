#define CPhysicUtil_c
#define LUA_LIB


#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpStruct.h"
#include "lib_fpPhysicUtil.h"

//判断点是否在矩形内
//local b = CPhysicUtil.IsVInt3InRectXY(vInt3,rect)
static int PU_IsVInt3InRectXY(lua_State* L)
{
	const struct VInt3* vInt3 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(vInt3 != NULL);
	const struct CRect* rect = (struct CRect*)lua_touserdata(L, 2);
	ARGCHECK(rect != NULL);

	lua_pushboolean(L,IsVInt3InRectXY(vInt3,rect));
	return 1;
}

//判断两个圆是否相交
//local b = CPhysicUtil.IsCircleIntersectCircleXY(circle1,circle2)
static int PU_IsCircleIntersectCircleXY(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct CCircle* circle2 = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(circle2 != NULL);
	
	lua_pushboolean(L,IsCircleIntersectCircleXY(circle1,circle2));
	return 1;
}

//判断矩形和圆是否相交
//local b = CPhysicUtil.IsRectIntersectCircleXY(rect,circle)
static int PU_IsRectIntersectCircleXY(lua_State *L)
{
	const struct CRect* rect = (struct CRect*)lua_touserdata(L, 1);
	ARGCHECK(rect != NULL);
	const struct CCircle* circle = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(circle != NULL);
	
	lua_pushboolean(L,IsRectIntersectCircleXY(rect,circle));
	return 1;
}

static struct luaL_Reg vecMetaFunc[] =
{
   {NULL, NULL}
};

static struct luaL_Reg vecFunc[] =
{
	{"IsVInt3InRectXY",PU_IsVInt3InRectXY},
	{"IsCircleIntersectCircleXY",PU_IsCircleIntersectCircleXY},
	{"IsRectIntersectCircleXY",PU_IsRectIntersectCircleXY},
	{NULL, NULL}
};

LUALIB_API int luaopen_CPhysicUtil(lua_State *L)
{
	luaL_register(L, "CPhysicUtil", vecFunc);
	luaL_newmetatable(L, "CPhysicUtil");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	const luaL_Reg *lib;
	for (lib = vecMetaFunc; lib->func; lib++) {
		lua_pushstring(L, lib->name);
		lua_pushcfunction(L, lib->func);
		
		lua_settable(L, -3);
	}
	return 1;
}
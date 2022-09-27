#define CFixedPointUtil_c
#define LUA_LIB

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpIntCfg.h"

static int FixedPoint_Scale(lua_State* L)
{
	lua_pushnumber(L, IntScale);
	return 1;
}


static struct luaL_Reg vecMetaFunc[] =
{
    //{"__gc", Vec_32_gc},
	{NULL, NULL}
};

//暂时不需要_gc
//static int Vec_32_gc(lua_State *L) {
//	struct Vec_32 *pVec_32 = (struct Vec_32 *)lua_touserdata(L, 1);
//
//	return 1;
//}

static struct luaL_Reg vecFunc[] =
{
	{"Scale",FixedPoint_Scale},
	{NULL, NULL}
};

LUALIB_API int luaopen_CFixedPointUtil(lua_State *L)
{
	luaL_register(L, "CFixedPointUtil", vecFunc);
	luaL_newmetatable(L, "CFixedPointUtil");
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
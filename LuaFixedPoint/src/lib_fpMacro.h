#ifndef CFixedPointMacro_h
#define CFixedPointMacro_h

#include "lib_fpIntCfg.h"

//------一些工具宏--------------

//参数检测
#define ARGCHECK(cond) \
	luaL_argcheck(L, cond, 1,"Wrong Parameter");
	//luaL_argcheck(L, cond, 1,__FILE__+__LINE__+*"Wrong Parameter");

// 创建一个userdata数据
#define NEW_USERDATA(structType,argName) \
	size_t iBytes = sizeof(struct structType);\
	struct structType* argName;\
	argName = (struct structType*)lua_newuserdata(L, iBytes);

// 保留指定的小数的double类型值 (这不是一个准确的函数，如KEEP_DECIMAL(17.01) = 17.0100000002)
#define KEEP_DECIMAL(num) round(num*DoubleScale)/DoubleScale //用到这个宏的需要#include <math.h>

// 整数四舍五入
#define CINT_ROUND(num) (CINT)round(num)  //用到这个宏的需要#include <math.h>

//获取缩放的值
#define GET_SCALEVALUE(num) KEEP_DECIMAL(num/DoubleScale)

#define GETSET_METATABLE(tableNameStr) \
	luaL_getmetatable(L, tableNameStr);\
	lua_setmetatable(L, -2);

//获取函数调用的self
#define GETSELF(argType,argName)\
	struct argType* argName = (struct argType*)lua_touserdata(L, 1);

//绑定引用
#define LUA_REF(outRefIndex)\
	outRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);

//解绑引用
#define LUA_UNREF(refIndex)\
	luaL_unref(L,LUA_REGISTRYINDEX,refIndex);\
	refIndex = LUA_REFNIL;\

#endif
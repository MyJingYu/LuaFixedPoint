#ifndef CFixedPointMacro_h
#define CFixedPointMacro_h

#include "lib_fpIntCfg.h"

//------һЩ���ߺ�--------------

//�������
#define ARGCHECK(cond) \
	luaL_argcheck(L, cond, 1,"Wrong Parameter");
	//luaL_argcheck(L, cond, 1,__FILE__+__LINE__+*"Wrong Parameter");

// ����һ��userdata����
#define NEW_USERDATA(structType,argName) \
	size_t iBytes = sizeof(struct structType);\
	struct structType* argName;\
	argName = (struct structType*)lua_newuserdata(L, iBytes);

// ����ָ����С����double����ֵ (�ⲻ��һ��׼ȷ�ĺ�������KEEP_DECIMAL(17.01) = 17.0100000002)
#define KEEP_DECIMAL(num) round(num*DoubleScale)/DoubleScale //�õ���������Ҫ#include <math.h>

// ������������
#define CINT_ROUND(num) (CINT)round(num)  //�õ���������Ҫ#include <math.h>

//��ȡ���ŵ�ֵ
#define GET_SCALEVALUE(num) KEEP_DECIMAL(num/DoubleScale)

#define GETSET_METATABLE(tableNameStr) \
	luaL_getmetatable(L, tableNameStr);\
	lua_setmetatable(L, -2);

//��ȡ�������õ�self
#define GETSELF(argType,argName)\
	struct argType* argName = (struct argType*)lua_touserdata(L, 1);

//������
#define LUA_REF(outRefIndex)\
	outRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);

//�������
#define LUA_UNREF(refIndex)\
	luaL_unref(L,LUA_REGISTRYINDEX,refIndex);\
	refIndex = LUA_REFNIL;\

#endif
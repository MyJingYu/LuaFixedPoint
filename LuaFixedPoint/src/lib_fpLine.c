#define CLine_c
#define LUA_LIB


#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpIntCfg.h"
#include "lib_fpMacro.h"
#include "lib_fpVInt3.h"
#include "lib_fpStruct.h"


//lua new userdata
#define NEW_CLineUSERDATA(argName) \
	NEW_USERDATA(CLine,argName)

#define GETSET_CLineMETATABLE \
	GETSET_METATABLE("CLine")

//获取函数调用的self
#define GETSELF_CLine(argName)\
	GETSELF(CLine,argName)


//Line.new(p1,p2)
static int Line_new(lua_State *L)
{
	const struct VInt3* p1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(p1 != NULL);
	const struct VInt3* p2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(p2 != NULL);
	
	NEW_CLineUSERDATA(cLine);
	cLine->p1 = CVint3_new(L,p1->x,p1->y,p1->z,&cLine->_p1Index);
	cLine->p2 = CVint3_new(L,p2->x,p2->y,p2->z,&cLine->_p2Index);
	GETSET_CLineMETATABLE;
	return 1;
}
//CLine.newDefault()
static int Line_newDefault(lua_State *L)
{
	NEW_CLineUSERDATA(cLine);
	cLine->p1 = CVint3_new(L,0,0,0,&cLine->_p1Index);
	cLine->p2 = CVint3_new(L,0,0,0,&cLine->_p2Index);
	GETSET_CLineMETATABLE;
	return 1;
}
//CLine.Copy(copyLine)
static int Line_Copy(lua_State *L)
{
	GETSELF_CLine(copyLine);
	ARGCHECK(copyLine != NULL);
	
	NEW_CLineUSERDATA(cLine);
	cLine->p1 = CVint3_new(L,cLine->p1->x,cLine->p1->y,cLine->p1->z,&cLine->_p1Index);
	cLine->p2 = CVint3_new(L,cLine->p2->x,cLine->p2->y,cLine->p2->z,&cLine->_p2Index);
	GETSET_CLineMETATABLE;
	return 1;
}
// operator ==
static int Line__eq(lua_State *L)
{
	const struct CLine* line1 = (struct CLine*)lua_touserdata(L, 1);
	ARGCHECK(line1 != NULL)
	const struct CLine* line2 = (struct CLine*)lua_touserdata(L, 2);
	ARGCHECK(line2 != NULL)

	if ((CVint3_equel(line1->p1,line2->p1) == TRUE && CVint3_equel(line1->p2,line2->p2) == TRUE) ||
		(CVint3_equel(line1->p1,line2->p2) == TRUE && CVint3_equel(line1->p2,line2->p1) == TRUE))
		lua_pushboolean(L,TRUE);
	else
		lua_pushboolean(L,FALSE);
	return 1;
}
//cLine:copy(copyCLine)
static int Line_copy(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);
	const struct CLine* copyLine = (struct CLine*)lua_touserdata(L, 2);
	ARGCHECK(copyLine != NULL)
	
	CVint3_copy(line->p1,copyLine->p1);
	CVint3_copy(line->p2,copyLine->p2);
	lua_pop(L,1);
	return 1;
}
//cLine:ctor(p1,p2)
static int Line_ctor(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);
	
	const struct VInt3* p1 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(p1 != NULL);
	const struct VInt3* p2 = (struct VInt3*)lua_touserdata(L, 3);
	ARGCHECK(p2 != NULL);
	
	CVint3_copy(line->p1,p1);
	CVint3_copy(line->p2,p2);

	lua_pop(L,2);
	return 1;
}
//local p1,p2 = cLine:ps()
static int Line_ps(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);
	{
		NEW_USERDATA(VInt3,p1);
		CVint3_copy(p1,line->p1);
		GETSET_METATABLE("VInt3");
	}
	{
		NEW_USERDATA(VInt3,p2);
		CVint3_copy(p2,line->p2);
		GETSET_METATABLE("VInt3");
	}
	return 2;
}
//local p1Ref,p2Ref = cLine:ps()
// static int Line_psRef(lua_State *L)
// {
// 	GETSELF_CLine(line);
// 	ARGCHECK(line != NULL);
// 	luaC_pushuserdata(L,line->p1);
// 	luaC_pushuserdata(L,line->p2);
// 	return 2;
// }
//local p1 = cLine:p1()
static int Line_p1(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);
	NEW_USERDATA(VInt3,p1);
	CVint3_copy(p1,line->p1);
	GETSET_METATABLE("VInt3");
	return 1;
}
//local p1Ref = cLine:p1Ref()
// static int Line_p1Ref(lua_State *L)
// {
// 	GETSELF_CLine(line);
// 	ARGCHECK(line != NULL);
// 	luaC_pushuserdata(L,line->p1);
// 	return 1;
// }
//local p2 = cLine:p2()
static int Line_p2(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);
	NEW_USERDATA(VInt3,p2);
	CVint3_copy(p2,line->p2);
	GETSET_METATABLE("VInt3");
	return 1;
}
//local p2Ref = cLine:p2Ref()
// static int Line_p2Ref(lua_State *L)
// {
// 	GETSELF_CLine(line);
// 	ARGCHECK(line != NULL);
// 	luaC_pushuserdata(L,line->p2);
// 	return 1;
// }

static int Line__tostring(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);

	char buf[200]={0};
	sprintf(buf,"p1x:%.4f ,p1y:%.4f, p1z:%.4f , p2x:%.4f ,p2y:%.4f, p2z:%.4f",
			ScaleValue2Num(line->p1->x),ScaleValue2Num(line->p1->y),ScaleValue2Num(line->p1->z),
			ScaleValue2Num(line->p2->x),ScaleValue2Num(line->p2->y),ScaleValue2Num(line->p2->z));
	lua_pushstring(L,buf);
	return 1;
}

static int Line_gc(lua_State *L)
{
	GETSELF_CLine(line);
	ARGCHECK(line != NULL);
	LUA_UNREF(line->_p1Index)
	LUA_UNREF(line->_p2Index)
	return 1;
}

static struct luaL_Reg vecMetaFunc[] =
{
	{"ps", Line_ps},
	//{"psRef", Line_psRef},
	{"p1", Line_p1},
	//{"p1Ref", Line_p1Ref},
	{"p2", Line_p2},
	//{"p2Ref", Line_p2Ref},
 	{"ctor", Line_ctor},
 	{"copy", Line_copy},
	{"__eq",Line__eq},
	{"__tostring",Line__tostring},
    {"__gc", Line_gc},
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
	{"new", Line_new},
	{"newDefault", Line_newDefault},
	{"Copy", Line_Copy},
	{NULL, NULL}
};

LUALIB_API int luaopen_CLine(lua_State *L)
{
	luaL_register(L, "CLine", vecFunc);
	luaL_newmetatable(L, "CLine");
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
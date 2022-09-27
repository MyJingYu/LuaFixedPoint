#define CIntMath_c
#define LUA_LIB

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpIntCfg.h"
#include "lib_fpIntMathUtil.h"
#include <math.h>

//三角函数(弧度)
#define Trigonometric_FUN(funName)\
	static int math_##funName(lua_State *L){\
		const double radian = lua_tonumber(L, 1);\
		double result = funName##Int(radian);\
		lua_pushnumber(L,result);\
		return 1;\
	}
//三角函数(角度)
#define Trigonometric_Angle_FUN(funName)\
	static int math_##funName##Angle(lua_State *L){\
		const double angle = lua_tonumber(L, 1);\
		const double radian = Angle2Radian(angle);\
		double result = funName##Int(radian);\
		lua_pushnumber(L,result);\
		return 1;\
	}
//反三角函数(角度)
#define InverseTrigonometric_Angle_FUN(funName)\
	static int math_##funName##Angle(lua_State *L){\
    	const double v = lua_tonumber(L, 1);\
    	double radian = funName##Int(v);\
    	double angle = Radian2Angle(radian);\
    	lua_pushnumber(L,angle);\
    	return 1;\
    }


// 将数值进行定点数放大
static int math_num2ScaleValue(lua_State *L) {
	const double num = lua_tonumber(L, 1);
	const CINT value = Num2ScaleValue(num);
	lua_pushnumber(L, value);
	
	return 1;
}

// 将定点放大的数缩小成正常的值，保留两位小数
static int math_scaleValue2Num(lua_State *L) {
	const CINT num = lua_tonumber(L, 1);
	const double value = ScaleValue2Num(num);
	lua_pushnumber(L, value);
	
	return 1;
}
// 保留指定位的小数
static int math_KeepDecimal(lua_State *L) {
	double num = lua_tonumber(L, 1);
	num = KEEP_DECIMAL(num);
	lua_pushnumber(L, num);
	
	return 1;
}
// 开平方，并保留指定位的小数
static int math_Sqrt(lua_State *L) {
	double num = lua_tonumber(L, 1);
	num = KEEP_DECIMAL(sqrt(num));
	lua_pushnumber(L, num);
	
	return 1;
}


// local sinV = CIntMath.Sin(radian)
Trigonometric_FUN(Sin)
// local cosV = CIntMath.Cos(radian)
Trigonometric_FUN(Cos)
// local tanV = CIntMath.Tan(radian)
Trigonometric_FUN(Tan)
// local radian = CIntMath.ASin(sinV)
Trigonometric_FUN(ASin)
// local radian = CIntMath.ACos(cosV)
Trigonometric_FUN(ACos)
// local radian = CIntMath.ATan(tanV)
Trigonometric_FUN(ATan)
// local sinV = CIntMath.SinAngle(angle)
Trigonometric_Angle_FUN(Sin)
// local cosV = CIntMath.CosAngle(angle)
Trigonometric_Angle_FUN(Cos)
// local tanV = CIntMath.TanAngle(angle)
Trigonometric_Angle_FUN(Tan)
// local angle = CIntMath.ASinAngle(sinV)
InverseTrigonometric_Angle_FUN(ASin)
// local angle = CIntMath.ACosAngle(cosV)
InverseTrigonometric_Angle_FUN(ACos)
// local angle = CIntMath.ATanAngle(tanV)
InverseTrigonometric_Angle_FUN(ATan)

static int math_Round(lua_State *L) {
	const double num = lua_tonumber(L, 1);
	const CINT result = CINT_ROUND(num);
	lua_pushnumber(L, result);
	
	return 1;
}
static int math_Angle2Radian(lua_State *L) {
	const double angle = lua_tonumber(L, 1);
	const double radian = Angle2Radian(angle);
	lua_pushnumber(L, radian);
	return 1;
}
static int math_Radian2Angle(lua_State *L) {
	const double radian = lua_tonumber(L, 1);
	const double angle = Radian2Angle(radian);
	lua_pushnumber(L, angle);
	return 1;
}

static struct luaL_Reg vecMetaFunc[] =
{
	//{"__gc", Vec_32_gc},
	{NULL, NULL}
};

static struct luaL_Reg vecFunc[] =
{
	{"Num2ScaleValue", math_num2ScaleValue},
	{"ScaleValue2Num", math_scaleValue2Num},
	{"KeepDecimal", math_KeepDecimal},// 保留指定位的小数
	{"Sqrt", math_Sqrt},// 开平方，并保留指定位的小数
	{"Sin", math_Sin},
	{"Cos", math_Cos},
	{"Tan", math_Tan},
	{"ASin", math_ASin},
	{"ACos", math_ACos},
	{"ATan", math_ATan},
	{"SinAngle", math_SinAngle},
	{"CosAngle", math_CosAngle},
	{"TanAngle", math_TanAngle},
	{"ASinAngle", math_ASinAngle},
	{"ACosAngle", math_ACosAngle},
	{"ATanAngle", math_ATanAngle},
	{"Round", math_Round},
	{"Angle2Radian", math_Angle2Radian},
	{"Radian2Angle", math_Radian2Angle},
	{NULL, NULL}
};

LUALIB_API int luaopen_CIntMath(lua_State *L)
{
	luaL_register(L, "CIntMath", vecFunc);
	luaL_newmetatable(L, "CIntMath");
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
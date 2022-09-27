#define CVInt3_c
#define LUA_LIB

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpIntCfg.h"
#include "lib_fpIntMathUtil.h"
#include "lib_fpMacro.h"
#include "lib_fpVInt3.h"

//lua new userdata
#define NEW_VInt3USERDATA(argName) \
	NEW_USERDATA(VInt3,argName)

#define GETSET_VInt3METATABLE \
	GETSET_METATABLE("VInt3")

//获取函数调用的self
#define GETSELF_VInt3(argName)\
	GETSELF(VInt3,argName)

//获取lua堆栈指定index位置的值(VInt3或number类型)，并将xyz值（没有定点数放大）赋值给XArgName...
#define GET_VINT3_OR_NUM_PARAMS_TOXYZ(luaIndex,XArgName,YArgName,ZArgName)\
	{\
		const struct VInt3* vInt3 = (struct VInt3*)lua_touserdata(L, luaIndex);\
		if (vInt3 == NULL){\
			ARGCHECK(lua_type(L,luaIndex)==LUA_TNUMBER);\
			const double num = lua_tonumber(L, luaIndex);\
			XArgName = KEEP_DECIMAL(num);\
			YArgName = XArgName;\
			ZArgName = XArgName;\
		}\
		else{\
			XArgName = ScaleValue2Num(vInt3->x);\
			YArgName = ScaleValue2Num(vInt3->y);\
			ZArgName = ScaleValue2Num(vInt3->z);\
		}\
	}

//运算符重载函数获取参数宏(获取VInt3*，否则获取munber)
#define OPERATOR_OVERLOADING_FUN_GET_PARAMS\
	const struct VInt3* pVInt3_1 = (struct VInt3*)lua_touserdata(L, 1);\
	ARGCHECK(pVInt3_1 != NULL)\
	double x2,y2,z2;\
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x2,y2,z2)

//两个VInt3运算，将结果赋值给self
#define OPERATOR_2V_FUN(funName,op)\
	static int VInt3_##funName(lua_State *L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		double x1,x2,y1,y2,z1,z2;\
		GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);\
		GET_VINT3_OR_NUM_PARAMS_TOXYZ(3,x2,y2,z2);\
		vint3->x = Num2ScaleValue(x1 op x2);\
		vint3->y = Num2ScaleValue(y1 op y2);\
		vint3->z = Num2ScaleValue(z1 op z2);\
		lua_pop(L,2);\
		return 1;\
	}

//两个VInt3的XY运算，将结果赋值给self
#define OPERATOR_XY2V_FUN(funName,op)\
	static int VInt3_##funName(lua_State *L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		double x1,x2,y1,y2,z1,z2;\
		GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);\
		GET_VINT3_OR_NUM_PARAMS_TOXYZ(3,x2,y2,z2);\
		vint3->x = Num2ScaleValue(x1 op x2);\
		vint3->y = Num2ScaleValue(y1 op y2);\
		lua_pop(L,2);\
		return 1;\
		}

#define GET_ONE_VALVE(funName,argName)\
	static int VInt3_##funName(lua_State *L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		lua_pushnumber(L, GET_SCALEVALUE(vint3->argName));\
		return 1;\
	}

#define GET_ONE_VALUEREALE(funName,argName)\
	static int VInt3_##funName(lua_State* L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		lua_pushnumber(L, vint3->argName);\
		return 1;\
	}

#define GET_TWO_VALVE(funName,arg1Name,arg2Name)\
	static int VInt3_##funName(lua_State *L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		lua_pushnumber(L, GET_SCALEVALUE(vint3->arg1Name));\
		lua_pushnumber(L, GET_SCALEVALUE(vint3->arg2Name));\
		return 2;\
	}

#define GET_TWO_VALUEREALE(funName,arg1Name,arg2Name)\
	static int VInt3_##funName(lua_State* L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		lua_pushnumber(L, vint3->arg1Name);\
		lua_pushnumber(L, vint3->arg2Name);\
		return 2;\
	}

#define SET_ONE_VALUE(funName,argName)\
	static int VInt3_##funName(lua_State *L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		const double argName = lua_tonumber(L,2);\
		vint3->argName = CINT_ROUND(argName * IntScale);\
		lua_pop(L,1);\
		return 1;\
	}

#define SET_TWO_VALUE(funName,arg1Name,arg2Name)\
	static int VInt3_##funName(lua_State *L){\
		GETSELF_VInt3(vint3);\
		ARGCHECK(vint3 != NULL)\
		const double arg1Name = lua_tonumber(L,2);\
		const double arg2Name = lua_tonumber(L,3);\
		vint3->arg1Name = CINT_ROUND(arg1Name * IntScale);\
		vint3->arg2Name = CINT_ROUND(arg2Name * IntScale);\
		lua_pop(L,2);\
		return 2;\
	}
//-----------------------------------------------------------------------------------

static int VInt3_test(lua_State* L)
{
	//double a = 1701/DoubleScale; //会得到17.0100000x,但是lua返回时是17.01
	//double aa = KEEP_DECIMAL(a);
	// double a = KEEP_DECIMAL(1701);	//return 1701
	// double aa = KEEP_DECIMAL(17.01);//return 17.01000000002
	// lua_pushnumber(L, a);
	// lua_pushnumber(L, aa);
	
	size_t iBytes_VInt3 = sizeof(struct VInt3);
	size_t iBytes_CCircle = sizeof(struct CCircle);
	size_t iBytes_CLine = sizeof(struct CLine);
	size_t iBytes_CRect = sizeof(struct CRect);

	lua_pushnumber(L, 1);
	return 1;
}

// VInt3.new(x,y,z)
static int VInt3_new(lua_State* L)
{    
    double x = lua_tonumber(L, -3);
    double y = lua_tonumber(L, -2);
    double z = lua_tonumber(L, -1);
	
	NEW_VInt3USERDATA(vint3);
    vint3->x = CINT_ROUND(x * IntScale);
    vint3->y = CINT_ROUND(y * IntScale);
    vint3->z = CINT_ROUND(z * IntScale);
	
	GETSET_VInt3METATABLE;

    //生成table 性能较低
    //double x = lua_tonumber(L, -3);
    //double y = lua_tonumber(L, -2);
    //double z = lua_tonumber(L, -1);

    //lua_newtable(L);
    //lua_pushstring(L, "x");
    //lua_pushinteger(L, x);
    //lua_rawset(L, -3);

    //lua_pushstring(L, "y");
    //lua_pushinteger(L, y);
    //lua_rawset(L, -3);

    //lua_pushstring(L, "z");
    //lua_pushinteger(L, z);
    //lua_rawset(L, -3);

    //luaL_getmetatable(L, "VInt3");
    //lua_setmetatable(L, -2);

    return 1;
}

// VInt3.Copy(oneVInt3)
static int VInt3_Copy(lua_State* L)
{
	const struct VInt3* pVint3From = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(pVint3From != NULL);

	NEW_VInt3USERDATA(vint3);
	CVint3_copy(vint3,pVint3From);
	
	GETSET_VInt3METATABLE;
	return 1;
}

// thisVInt3:copy(oneVInt3)
static int VInt3_copy(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	CVint3_copy(vint3,pVInt3_2);
	
	lua_pop(L,1);
	return 1;
}
static int VInt3_copyXY(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	CVint3_copyXY(vint3,pVInt3_2);
	
	lua_pop(L,1);
	return 1;
}
static int VInt3_ctor(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	const double x = lua_tonumber(L, 2);
	const double y = lua_tonumber(L, 3);
	const double z = lua_tonumber(L, 4);
	CVint3_ctor(vint3,CINT_ROUND(x * IntScale),CINT_ROUND(y * IntScale),CINT_ROUND(z * IntScale));
	
	lua_pop(L,3);
	return 1;
}

static int VInt3_Scale(lua_State* L)
{
	lua_pushnumber(L, IntScale);
	return 1;
}

// operator ==
static int VInt3__eq(lua_State *L)
{
	const struct VInt3* pVInt3_1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(pVInt3_1 != NULL)
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	lua_pushboolean(L,CVint3_equel(pVInt3_1,pVInt3_2));
	return 1;
}
// vInt3_1:equalXY(vInt3_2)
static int VInt3_equalXY(lua_State *L)
{
	const struct VInt3* pVInt3_1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(pVInt3_1 != NULL)
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	lua_pushboolean(L,CVint3_equelXY(pVInt3_1,pVInt3_2));
	return 1;
}

// operator+
static int VInt3__add(lua_State *L)
{
	OPERATOR_OVERLOADING_FUN_GET_PARAMS;
	
	NEW_VInt3USERDATA(vint3);
	vint3->x = pVInt3_1->x + Num2ScaleValue(x2);
	vint3->y = pVInt3_1->y + Num2ScaleValue(y2);
	vint3->z = pVInt3_1->z + Num2ScaleValue(z2);
	
	GETSET_VInt3METATABLE;
	return 1;
}

// operator-
static int VInt3__sub(lua_State *L)
{
	OPERATOR_OVERLOADING_FUN_GET_PARAMS;
	NEW_VInt3USERDATA(vint3);
	vint3->x = pVInt3_1->x - Num2ScaleValue(x2);
	vint3->y = pVInt3_1->y - Num2ScaleValue(y2);
	vint3->z = pVInt3_1->z - Num2ScaleValue(z2);
	
	GETSET_VInt3METATABLE;
	return 1;
}

// operator*
static int VInt3__mul(lua_State *L)
{
	OPERATOR_OVERLOADING_FUN_GET_PARAMS;
	NEW_VInt3USERDATA(vint3);
	vint3->x = CINT_ROUND(pVInt3_1->x * x2);
	vint3->y = CINT_ROUND(pVInt3_1->y * y2);
	vint3->z = CINT_ROUND(pVInt3_1->z * z2);
	
	GETSET_VInt3METATABLE;
	return 1;
}

// operator/
static int VInt3__div(lua_State *L)
{
	OPERATOR_OVERLOADING_FUN_GET_PARAMS;
	ARGCHECK(x2 != 0 && y2 != 0 && z2 != 0)
	NEW_VInt3USERDATA(vint3);
	vint3->x = CINT_ROUND(pVInt3_1->x / x2);
	vint3->y = CINT_ROUND(pVInt3_1->y / y2);
	vint3->z = CINT_ROUND(pVInt3_1->z / z2);
	GETSET_VInt3METATABLE;
	return 1;
}

// VInt3:add(othervInt3)
// VInt3:add(num)
static int VInt3_add(lua_State *L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	double x1,y1,z1;
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);
	vint3->x += Num2ScaleValue(x1);
	vint3->y += Num2ScaleValue(y1);
	vint3->z += Num2ScaleValue(z1);

	lua_pop(L,1); //弹出一个元素(将addvInt3移除)
	return 1;
}

// VInt3:add2V(vInt3_1,vInt3_2)
// VInt3:add2V(num,vInt3_2)
// VInt3:add2V(vInt3_1,num)
OPERATOR_2V_FUN(add2V,+);
OPERATOR_XY2V_FUN(addXY2V,+);

// VInt3:sub(othervInt3)
// VInt3:sub(num)
static int VInt3_sub(lua_State *L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	double x1,y1,z1;
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);
	vint3->x -= Num2ScaleValue(x1);
	vint3->y -= Num2ScaleValue(y1);
	vint3->z -= Num2ScaleValue(z1);

	lua_pop(L,1); //弹出一个元素(将addvInt3移除)
	return 1;
}

// VInt3:sub2V(vInt3_1,vInt3_2)
// VInt3:sub2V(num,vInt3_2)
// VInt3:sub2V(vInt3_1,num)
OPERATOR_2V_FUN(sub2V,-);
OPERATOR_XY2V_FUN(subXY2V,-);

// VInt3:mul(othervInt3)
// VInt3:mul(num)
static int VInt3_mul(lua_State *L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	double x1,y1,z1; //没定点数放大的数
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);
	vint3->x = CINT_ROUND(vint3->x * x1);
	vint3->y = CINT_ROUND(vint3->y * y1);
	vint3->z = CINT_ROUND(vint3->z * z1);

	lua_pop(L,1); //弹出一个元素(将addvInt3移除)
	return 1;
}

// VInt3:mul2V(vInt3_1,vInt3_2)
// VInt3:mul2V(num,vInt3_2)
// VInt3:mul2V(vInt3_1,num)
OPERATOR_2V_FUN(mul2V,*);
OPERATOR_XY2V_FUN(mulXY2V,*);

// VInt3:div(othervInt3)
// VInt3:div(num)
static int VInt3_div(lua_State *L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	double x1,y1,z1; //没定点数放大的数
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);
	ARGCHECK(x1 != 0 && y1 != 0 && z1 != 0)
	
	vint3->x = CINT_ROUND(vint3->x / x1);
	vint3->y = CINT_ROUND(vint3->y / y1);
	vint3->z = CINT_ROUND(vint3->z / z1);

	lua_pop(L,1); //弹出一个元素(将addvInt3移除)
	return 1;
}

// VInt3:div2V(vInt3_1,vInt3_2)
// VInt3:div2V(num,vInt3_2)
// VInt3:div2V(vInt3_1,num)
static int VInt3_div2V(lua_State *L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	double x1,x2,y1,y2,z1,z2;
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(3,x2,y2,z2);
	ARGCHECK(x2 != 0 && y2 != 0 && z2 != 0)

	vint3->x = Num2ScaleValue(x1/x2);
	vint3->y = Num2ScaleValue(y1/y2);
	vint3->z = Num2ScaleValue(z1/z2);

	lua_pop(L,2);
	return 1;
}
static int VInt3_divXY2V(lua_State *L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	double x1,x2,y1,y2,z1,z2;
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(2,x1,y1,z1);
	GET_VINT3_OR_NUM_PARAMS_TOXYZ(3,x2,y2,z2);
	ARGCHECK(x2 != 0 && y2 != 0 && z2 != 0)

	vint3->x = Num2ScaleValue(x1/x2);
	vint3->y = Num2ScaleValue(y1/y2);

	lua_pop(L,2);
	return 1;
}

GET_ONE_VALVE(x,x);
GET_ONE_VALVE(y,y);
GET_ONE_VALVE(z,z);


GET_TWO_VALVE(xy,x,y);
GET_TWO_VALVE(xz,x,z);
GET_TWO_VALVE(yz,y,z);

static int VInt3_xyz(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)

	lua_pushnumber(L, GET_SCALEVALUE(vint3->x));
	lua_pushnumber(L, GET_SCALEVALUE(vint3->y));
	lua_pushnumber(L, GET_SCALEVALUE(vint3->z));
	return 3;
}

GET_ONE_VALUEREALE(xReal,x);
GET_ONE_VALUEREALE(yReal,y);
GET_ONE_VALUEREALE(zReal,z);

GET_TWO_VALUEREALE(xyReal,x,y);
GET_TWO_VALUEREALE(xzReal,x,z);
GET_TWO_VALUEREALE(yzReal,y,z);

static int VInt3_xyzReal(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)

	lua_pushnumber(L, vint3->x);
	lua_pushnumber(L, vint3->y);
	lua_pushnumber(L, vint3->z);
	return 3;
}

SET_ONE_VALUE(setX,x);
SET_ONE_VALUE(setY,y);
SET_ONE_VALUE(setZ,z);

SET_TWO_VALUE(setXY,x,y);
SET_TWO_VALUE(setXZ,x,z);
SET_TWO_VALUE(setYZ,y,z);

static int VInt3_length(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)

    double length = CVint3_length(vint3);

    lua_pushnumber(L, length);
    return 1;
}

static int VInt3_lengthSqu(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)

	double lengthSqu = CVint3_lengthSqu(vint3);

	lua_pushnumber(L, lengthSqu);
	return 1;
}

static int VInt3_lengthXY(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)

	double length = CVint3_lengthXY(vint3);

	lua_pushnumber(L, length);
	return 1;
}

static int VInt3_lengthXYSqu(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)

	double lengthSqu = CVint3_lengthXYSqu(vint3);

	lua_pushnumber(L, lengthSqu);
	return 1;
}

static int VInt3_distance(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	double length = CVint3_distance(vint3,pVInt3_2);

	lua_pushnumber(L, length);
	return 1;
}

static int VInt3_distanceSqu(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	double lengthSqu = CVint3_distanceSqu(vint3,pVInt3_2);

	lua_pushnumber(L, lengthSqu);
	return 1;
}

static int VInt3_distanceXY(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	double length = CVint3_distanceXY(vint3,pVInt3_2);

	lua_pushnumber(L, length);
	return 1;
}

static int VInt3_distanceXYSqu(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	
	const struct VInt3* pVInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(pVInt3_2 != NULL)

	double lengthSqu = CVint3_distanceXYSqu(vint3,pVInt3_2);

	lua_pushnumber(L, lengthSqu);
	return 1;
}

static int VInt3_normalize(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	CVInt3_normalize(vint3);
	return 1;
}

static int VInt3_normalizeXY(lua_State* L)
{
	GETSELF_VInt3(vint3);
	ARGCHECK(vint3 != NULL)
	CVInt3_normalizeXY(vint3);
	return 1;
}

//点乘
//local v = CVInt3.Dot(vInt3_1,vInt3_2)
static int VInt3_Dot(lua_State* L)
{
	const struct VInt3* vInt3_1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(vInt3_1 != NULL)
	const struct VInt3* vInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3_2 != NULL)

	const double v = vInt3_1->x*vInt3_2->x + vInt3_1->y*vInt3_2->y + vInt3_1->z*vInt3_2->z;
	const double result = KEEP_DECIMAL(v/(DoubleScale*DoubleScale));
	lua_pushnumber(L,result);
	return 1;
}

//点乘
//local v = CVInt3.DotXY(vInt3_1,vInt3_2)
static int VInt3_DotXY(lua_State* L)
{
	const struct VInt3* vInt3_1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(vInt3_1 != NULL)
	const struct VInt3* vInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3_2 != NULL)

	const double v = vInt3_1->x*vInt3_2->x + vInt3_1->y*vInt3_2->y;
	const double result = KEEP_DECIMAL(v/(DoubleScale*DoubleScale));
	lua_pushnumber(L,result);
	return 1;
}
//X乘
//local vInt3 = CVInt3.Cross(vInt3_1,vInt3_2)
static int VInt3_Cross(lua_State* L)
{
	const struct VInt3* vInt3_1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(vInt3_1 != NULL)
	const struct VInt3* vInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3_2 != NULL)

	NEW_VInt3USERDATA(vint3);
	vint3->x = vInt3_1->y * vInt3_2->z - vInt3_1->z * vInt3_2->y;
	vint3->y = vInt3_1->z * vInt3_2->x - vInt3_1->x * vInt3_2->z;
	vint3->z = vInt3_1->x * vInt3_2->y - vInt3_1->y * vInt3_2->x;
	GETSET_VInt3METATABLE;
	return 1;
}
//X乘 根据结果大于小于0判断vInt3_2 在vInt3_1的左右边（sin）
//local v = CVInt3.CrossXY(vInt3_1,vInt3_2)
static int VInt3_CrossXY(lua_State* L)
{
	const struct VInt3* vInt3_1 = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(vInt3_1 != NULL)
	const struct VInt3* vInt3_2 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3_2 != NULL)

	double  v = ScaleValue2Num((vInt3_1->x*vInt3_2->y - vInt3_1->y*vInt3_2->x)/DoubleScale);
	lua_pushnumber(L,v);
	return 1;
}
// 点绕点旋转(XY平面)
// VInt3Pos 点
// VInt3Center 中心点
// radian      旋转弧度
// @return 旋转后的向量 (1弧度=180/π≈57.3度)
static int VInt3_RotateXY(lua_State* L)
{
	const struct VInt3* VInt3Pos = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(VInt3Pos != NULL)
	const struct VInt3* VInt3Center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(VInt3Center != NULL)
	const double radian = lua_tonumber(L,3);

	double x = (VInt3Pos->x - VInt3Center->x)*CosInt(radian) - (VInt3Pos->y - VInt3Center->y)*SinInt(radian) + VInt3Center->x;
	double y = (VInt3Pos->x - VInt3Center->x)*SinInt(radian) + (VInt3Pos->y - VInt3Center->y)*CosInt(radian) + VInt3Center->y;
	NEW_VInt3USERDATA(vint3);
	vint3->x = CINT_ROUND(x);
	vint3->y = CINT_ROUND(y);
	vint3->z = VInt3Pos->z;
	GETSET_VInt3METATABLE;
	return 1;
}
// 该点绕点旋转(XY平面)
// VInt3Center 中心点
// radian      旋转弧度
static int VInt3_rotateXY(lua_State* L)
{
	GETSELF_VInt3(VInt3Pos)
	ARGCHECK(VInt3Pos != NULL)
	const struct VInt3* VInt3Center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(VInt3Center != NULL)
	const double radian = lua_tonumber(L,3);
	
	double x = (VInt3Pos->x - VInt3Center->x)*CosInt(radian) - (VInt3Pos->y - VInt3Center->y)*SinInt(radian) + VInt3Center->x;
	double y = (VInt3Pos->x - VInt3Center->x)*SinInt(radian) + (VInt3Pos->y - VInt3Center->y)*CosInt(radian) + VInt3Center->y;
	VInt3Pos->x = CINT_ROUND(x);
	VInt3Pos->y = CINT_ROUND(y);
	lua_pop(L,2);
	return 1;
}
static int VInt3_IsFront(lua_State* L)
{
	const struct VInt3* selfPos = (struct VInt3*)lua_touserdata(L, 1);
	ARGCHECK(selfPos != NULL)
	const struct VInt3* selfViewDir = (struct VInt3*)lua_touserdata(L, 2); //起始点方向的向量
	ARGCHECK(selfViewDir != NULL)
	const struct VInt3* targetPos = (struct VInt3*)lua_touserdata(L, 3);
	ARGCHECK(targetPos != NULL)
	
	struct VInt3 s2t = {targetPos->x-selfPos->x,targetPos->y-selfPos->y,targetPos->z-selfPos->z};
	double dot = s2t.x*selfViewDir->x + s2t.y*selfViewDir->y;   //点乘
	if (dot > 0)
	{
		lua_pushboolean(L,TRUE);
	}
	else
	{
		lua_pushboolean(L,FALSE);
	}
	return 1;
}

static int VInt3__tostring(lua_State *L)
{
	GETSELF_VInt3(vInt3);
	ARGCHECK(vInt3 != NULL);
	
	char buf[100]={0};
	sprintf(buf,"x:%.4f ,y:%.4f, z:%.4f",ScaleValue2Num(vInt3->x),ScaleValue2Num(vInt3->y),ScaleValue2Num(vInt3->z));//保留8位小数，不够补0
	lua_pushstring(L,buf);
	return 1;
}

static struct luaL_Reg vecMetaFunc[] =
{
	{"__add", VInt3__add},
	{"__sub", VInt3__sub},
	{"__mul", VInt3__mul},
	{"__div", VInt3__div},
	{"__eq",VInt3__eq},
	{"__tostring",VInt3__tostring},
	{"equalXY",VInt3_equalXY},
	{"ctor", VInt3_ctor},
	{"copy", VInt3_copy},
	{"copyXY", VInt3_copyXY},
	{"add", VInt3_add},
	{"add2V", VInt3_add2V},
	{"addXY2V", VInt3_addXY2V},
	{"sub", VInt3_sub},
	{"sub2V", VInt3_sub2V},
	{"subXY2V", VInt3_subXY2V},
	{"mul", VInt3_mul},
	{"mul2V", VInt3_mul2V},
	{"mulXY2V", VInt3_mulXY2V},
	{"div", VInt3_div},
	{"div2V", VInt3_div2V},
	{"divXY2V", VInt3_divXY2V},
    {"length",VInt3_length},
	{"lengthSqu",VInt3_lengthSqu},
	{"lengthXY",VInt3_lengthXY},
	{"lengthXYSqu",VInt3_lengthXYSqu},
	{"distance",VInt3_distance},
	{"distanceSqu",VInt3_distanceSqu},
	{"distanceXY",VInt3_distanceXY},
	{"distanceXYSqu",VInt3_distanceXYSqu},
	{"normalize",VInt3_normalize},
	{"normalizeXY",VInt3_normalizeXY},
    {"x",VInt3_x},	//取值xyz,存在消耗，不建议频繁使用
    {"y",VInt3_y},
	{"z",VInt3_z},
	{"xy",VInt3_xy},
	{"xz",VInt3_xz},
	{"yz",VInt3_yz},
	{"xyz",VInt3_xyz},
	{"xReal",VInt3_xReal},
	{"yReal",VInt3_yReal},
	{"zReal",VInt3_zReal},
	{"xyReal",VInt3_xyReal},
	{"xzReal",VInt3_xzReal},
	{"yzReal",VInt3_yzReal},
	{"xyzReal",VInt3_xyzReal},
	{"setX",VInt3_setX},	//设置xyz,存在消耗，不建议频繁使用
	{"setY",VInt3_setY},
	{"setZ",VInt3_setZ},
	{"setXY",VInt3_setXY},
	{"setXZ",VInt3_setXZ},
	{"setYZ",VInt3_setYZ},
	{"rotateXY",VInt3_rotateXY},

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
	{"new", VInt3_new},
	{"test", VInt3_test},
	{"Copy", VInt3_Copy},
	{"Scale",VInt3_Scale},
	{"Distance",VInt3_distance},
	{"DistanceSqu",VInt3_distanceSqu},
	{"DistanceXY",VInt3_distanceXY},
	{"DistanceXYSqu",VInt3_distanceXYSqu},
	{"Dot",VInt3_Dot},
	{"DotXY",VInt3_DotXY},
	{"Cross",VInt3_Cross},
	{"CrossXY",VInt3_CrossXY},
	{"RotateXY",VInt3_RotateXY},
	{"IsFront",VInt3_IsFront}, //判断点targetPos是否在selfPos的前面
	{NULL, NULL}
};

LUALIB_API int luaopen_VInt3(lua_State *L)
{
	luaL_register(L, "VInt3", vecFunc);
	luaL_newmetatable(L, "VInt3");
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
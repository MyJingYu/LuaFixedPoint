#define CCircle_c
#define LUA_LIB


#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpIntCfg.h"
#include "lib_fpIntMathUtil.h"
#include "lib_fpMacro.h"
#include "lib_fpVInt3.h"
#include "lib_fpStruct.h"
#include <math.h>


//lua new userdata
#define NEW_CCircleUSERDATA(argName) \
	NEW_USERDATA(CCircle,argName)

#define GETSET_CCircleMETATABLE \
	GETSET_METATABLE("CCircle")

//获取函数调用的self
#define GETSELF_CCircle(argName)\
	GETSELF(CCircle,argName)

#define SET_CENTER_XYZARG(circleName,luaIndex,argName)\
	{\
		const double num = lua_tonumber(L, luaIndex);\
		circleName->center->argName = Num2ScaleValue(num);\
	}

//CCircle.new(radius,center)
static int Circle_new(lua_State *L)
{
	const double radius = lua_tonumber(L,1);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(center != NULL);
	
	NEW_CCircleUSERDATA(circle);
	circle->radius = CINT_ROUND(radius * DoubleScale);
	circle->center = CVint3_new(L,center->x,center->y,center->z,&circle->_centerIndex);
	GETSET_CCircleMETATABLE;
	return 1;
}
//CCircle.newDefault()
static int Circle_newDefault(lua_State *L)
{
	NEW_CCircleUSERDATA(circle);
	circle->radius = 0;
	circle->center = CVint3_new(L,0,0,0,&circle->_centerIndex);
	GETSET_CCircleMETATABLE;
	return 1;
}
//CCircle.Copy(oneCCircle)
static int Circle_Copy(lua_State *L)
{
	GETSELF_CCircle(copyCircle);
	ARGCHECK(copyCircle != NULL);
	
	NEW_CCircleUSERDATA(circle);
	circle->radius = copyCircle->radius;
	circle->center = CVint3_new(L,copyCircle->center->x,copyCircle->center->y,copyCircle->center->z,&circle->_centerIndex);
	GETSET_CCircleMETATABLE;
	return 1;
}
// operator ==
static int Circle__eq(lua_State *L)
{
	const struct CCircle* c1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(c1 != NULL)
	const struct CCircle* c2 = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(c2 != NULL)

	if (Equal(c1->radius,c2->radius) == TRUE && CVint3_equel(c1->center,c2->center) == TRUE)
		lua_pushboolean(L,TRUE);
	else
		lua_pushboolean(L,FALSE);
	return 1;
}
//cCircle:copy(oneCCircle)
static int Circle_copy(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const struct CCircle* copyCircle = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(copyCircle != NULL);
	
	circle->radius = copyCircle->radius;
	CVint3_copy(circle->center,copyCircle->center);
	lua_pop(L,1);
	return 1;
}
static int Circle_copyCenter(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const struct CCircle* copyCircle = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(copyCircle != NULL);
	
	CVint3_copy(circle->center,copyCircle->center);
	lua_pop(L,1);
	return 1;
}
static int Circle_copyRadius(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const struct CCircle* copyCircle = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(copyCircle != NULL);
	
	circle->radius = copyCircle->radius;
	lua_pop(L,1);
	return 1;
}
//cCircle:ctor(radius,center)
static int Circle_ctor(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);

	const double radius = lua_tonumber(L,2);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 3);
	ARGCHECK(center != NULL);

	circle->radius = CINT_ROUND(radius * DoubleScale);
	CVint3_copy(circle->center,center);
	
	lua_pop(L,2);
	return 1;
}
static int Circle_radius(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	double radius = GET_SCALEVALUE(circle->radius);
	lua_pushnumber(L,radius);
	return 1;
}
//cCircle:setRadius(radius)
static int Circle_setRadius(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const double radius = lua_tonumber(L,2);
	circle->radius = CINT_ROUND(radius * DoubleScale);
	lua_pop(L,1);
	return 1;
}
static int Circle_center(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	NEW_USERDATA(VInt3,center);
	CVint3_copy(center,circle->center);
	GETSET_METATABLE("VInt3");
	return 1;
}
// static int Circle_centerRef(lua_State *L)
// {
// 	GETSELF_CCircle(circle);
// 	ARGCHECK(circle != NULL);
// 	luaC_pushuserdata(L,circle->center);
// 	return 1;
// }
static int Circle_setCenter(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(center != NULL);
	CVint3_copy(circle->center,center);
	lua_pop(L,1);
	return 1;
}
static int Circle_setCenterX(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	SET_CENTER_XYZARG(circle,2,x)
	lua_pop(L,1);
	return 1;
}
static int Circle_setCenterY(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	SET_CENTER_XYZARG(circle,2,y)
	lua_pop(L,1);
	return 1;
}
static int Circle_setCenterZ(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	SET_CENTER_XYZARG(circle,2,z)
	lua_pop(L,1);
	return 1;
}
static int Circle_setCenterXY(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	SET_CENTER_XYZARG(circle,2,x)
	SET_CENTER_XYZARG(circle,3,y)
	lua_pop(L,2);
	return 1;
}
static int Circle_setCenterXYZ(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	SET_CENTER_XYZARG(circle,2,x)
	SET_CENTER_XYZARG(circle,3,y)
	SET_CENTER_XYZARG(circle,4,z)
	lua_pop(L,3);
	return 1;
}
static int Circle_centerCopyXY(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(center != NULL);
	CVint3_copyXY(circle->center,center);
	lua_pop(L,1);
	return 1;
}
static int Circle_centerCopy(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(center != NULL);
	CVint3_copy(circle->center,center);
	lua_pop(L,1);
	return 1;
}
static int Circle_getCenterX(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	lua_pushnumber(L,ScaleValue2Num(circle->center->x));
	return 1;
}
static int Circle_getCenterY(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	lua_pushnumber(L,ScaleValue2Num(circle->center->y));
	return 1;
}
static int Circle_getCenterZ(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	lua_pushnumber(L,ScaleValue2Num(circle->center->z));
	return 1;
}
static int Circle_getCenterXY(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	lua_pushnumber(L,ScaleValue2Num(circle->center->x));
	lua_pushnumber(L,ScaleValue2Num(circle->center->y));
	return 2;
}
static int Circle_getCenterXYZ(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	lua_pushnumber(L,ScaleValue2Num(circle->center->x));
	lua_pushnumber(L,ScaleValue2Num(circle->center->y));
	lua_pushnumber(L,ScaleValue2Num(circle->center->z));
	return 3;
}

static int Circle_Distance(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct CCircle* circle2 = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(circle2 != NULL);
	double dis = CVint3_distance(circle1->center,circle2->center);
	lua_pushnumber(L,dis);
	return 1;
}
static int Circle_DistanceXY(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct CCircle* circle2 = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(circle2 != NULL);
	double dis = CVint3_distanceXY(circle1->center,circle2->center);
	lua_pushnumber(L,dis);
	return 1;
}
static int Circle_DistanceSqu(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct CCircle* circle2 = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(circle2 != NULL);
	double dis = CVint3_distanceSqu(circle1->center,circle2->center);
	lua_pushnumber(L,dis);
	return 1;
}
static int Circle_DistanceXYSqu(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct CCircle* circle2 = (struct CCircle*)lua_touserdata(L, 2);
	ARGCHECK(circle2 != NULL);
	double dis = CVint3_distanceXYSqu(circle1->center,circle2->center);
	lua_pushnumber(L,dis);
	return 1;
}

static int Circle_DistanceVInt3(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct VInt3* vInt3 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3 != NULL);
	double dis = CVint3_distance(circle1->center,vInt3);
	lua_pushnumber(L,dis);
	return 1;
}
static int Circle_DistanceXYVInt3(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct VInt3* vInt3 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3 != NULL);
	double dis = CVint3_distanceXY(circle1->center,vInt3);
	lua_pushnumber(L,dis);
	return 1;
}
static int Circle_DistanceSquVInt3(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct VInt3* vInt3 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3 != NULL);
	double dis = CVint3_distanceSqu(circle1->center,vInt3);
	lua_pushnumber(L,dis);
	return 1;
}
static int Circle_DistanceXYSquVInt3(lua_State *L)
{
	const struct CCircle* circle1 = (struct CCircle*)lua_touserdata(L, 1);
	ARGCHECK(circle1 != NULL);
	const struct VInt3* vInt3 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(vInt3 != NULL);
	double dis = CVint3_distanceXYSqu(circle1->center,vInt3);
	lua_pushnumber(L,dis);
	return 1;
}

static int Circle__tostring(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	
	char buf[100]={0};
	sprintf(buf,"radius:%.4f , x:%.4f ,y:%.4f, z:%.4f",ScaleValue2Num(circle->radius),
			ScaleValue2Num(circle->center->x),ScaleValue2Num(circle->center->y),ScaleValue2Num(circle->center->z));
	lua_pushstring(L,buf);
	return 1;
}

static int Circle_gc(lua_State *L)
{
	GETSELF_CCircle(circle);
	ARGCHECK(circle != NULL);
	LUA_UNREF(circle->_centerIndex);
	return 1;
}

static struct luaL_Reg vecMetaFunc[] =
{
 	{"radius", Circle_radius},
 	{"setRadius", Circle_setRadius},
 	{"center", Circle_center},
 	//{"centerRef", Circle_centerRef},
 	{"setCenter", Circle_setCenter},
 	{"setCenterX", Circle_setCenterX},
 	{"setCenterY", Circle_setCenterY},
	{"setCenterZ", Circle_setCenterZ},
	{"setCenterXY", Circle_setCenterXY},
	{"setCenterXYZ", Circle_setCenterXYZ},
	{"centerCopyXY", Circle_centerCopyXY},
	{"centerCopy", Circle_centerCopy},
	{"getCenterX", Circle_getCenterX},
	{"getCenterY", Circle_getCenterY},
	{"getCenterZ", Circle_getCenterZ},
	{"getCenterXY", Circle_getCenterXY},
	{"getCenterXYZ", Circle_getCenterXYZ},
 	{"ctor", Circle_ctor},
 	{"copy", Circle_copy},
 	{"copyCenter", Circle_copyCenter},
 	{"copyRadius", Circle_copyRadius},
	{"__eq",Circle__eq},
	{"__tostring",Circle__tostring},
    {"__gc", Circle_gc},
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
	{"new", Circle_new},
	{"newDefault", Circle_newDefault},
	{"Copy", Circle_Copy},
	{"Distance",Circle_Distance},
	{"DistanceSqu",Circle_DistanceSqu},
	{"DistanceXY",Circle_DistanceXY},
	{"DistanceXYSqu",Circle_DistanceXYSqu},
	{"DistanceVInt3",Circle_DistanceVInt3},
	{"DistanceSquVInt3",Circle_DistanceSquVInt3},
	{"DistanceXYVInt3",Circle_DistanceXYVInt3},
	{"DistanceXYSquVInt3",Circle_DistanceXYSquVInt3},
	{NULL, NULL}
};

LUALIB_API int luaopen_CCircle(lua_State *L)
{
	luaL_register(L, "CCircle", vecFunc);
	luaL_newmetatable(L, "CCircle");
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
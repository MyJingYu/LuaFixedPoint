#define CRect_c
#define LUA_LIB


#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lib_fpIntCfg.h"
#include "lib_fpIntMathUtil.h"
#include "lib_fpMacro.h"
#include "lib_fpRect.h"
#include "lib_fpVInt3.h"
#include <math.h>


//lua new userdata
#define NEW_CRectUSERDATA(argName) \
	NEW_USERDATA(CRect,argName)

#define GETSET_CRectMETATABLE \
	GETSET_METATABLE("CRect")

//获取函数调用的self
#define GETSELF_CRect(argName)\
	GETSELF(CRect,argName)

//返回rect的一个VInt3类型变量
//会建表，建议少用
#define GET_ONEPOS_FUN(funName,argName)\
	static int funName(lua_State *L){\
		GETSELF_CRect(rect);\
		ARGCHECK(rect != NULL);\
		NEW_USERDATA(VInt3,argName);\
		CVint3_copy(argName,rect->argName);\
		GETSET_METATABLE("VInt3")\
		return 1;}

//返回rect的一个VInt3类型变量引用
//谨慎修改返回值
//luaC_pushuserdata要求rect->xxx需要通过luaC_newuserdata创建
#define GET_ONEPOS_REF_FUN(funName,argName)\
	static int funName(lua_State *L){\
	GETSELF_CRect(rect);\
	ARGCHECK(rect != NULL);\
	lua_pushuserdata(L,rect->argName);\
	return 1;}

//center变化时四个顶点更新
#define UPDATE_POS_CENTERCHANGE(rect)\
	CVint3_ctor(rect->p1, rect->center->x-rect->halfLength, rect->center->y+rect->halfHeight, rect->center->z);\
	CVint3_ctor(rect->p2, rect->center->x+rect->halfLength, rect->center->y+rect->halfHeight, rect->center->z);\
	CVint3_ctor(rect->p3, rect->center->x+rect->halfLength, rect->center->y-rect->halfHeight, rect->center->z);\
	CVint3_ctor(rect->p4, rect->center->x-rect->halfLength, rect->center->y-rect->halfHeight, rect->center->z);

//radian变化时四个顶点更新
#define UPDATE_POS_RADIANCHANGE(rect)\
	CVint3_rotateVector3(rect->p1,rect->center,rect->radian);\
	CVint3_rotateVector3(rect->p2,rect->center,rect->radian);\
	CVint3_rotateVector3(rect->p3,rect->center,rect->radian);\
	CVint3_rotateVector3(rect->p4,rect->center,rect->radian);

//CRect.new(length,height,center)
static int Rect_new(lua_State *L)
{
	const double length = lua_tonumber(L,1);
	const double height = lua_tonumber(L,2);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 3);
	ARGCHECK(center != NULL);
	
	NEW_CRectUSERDATA(rect);
	rect->halfLength = CINT_ROUND(length * DoubleScale / 2);
	rect->halfHeight = CINT_ROUND(height * DoubleScale / 2);
	rect->radian = 0;
	rect->center = CVint3_new(L,center->x,center->y,center->z,&rect->_centerIndex);
	// p1---------p2
	//  |         |
	// p4---------p3
	rect->p1 = CVint3_new(L,center->x-rect->halfLength, center->y+rect->halfHeight, center->z,&rect->_p1Index);
	rect->p2 = CVint3_new(L,center->x+rect->halfLength, center->y+rect->halfHeight, center->z,&rect->_p2Index);
	rect->p3 = CVint3_new(L,center->x+rect->halfLength, center->y-rect->halfHeight, center->z,&rect->_p3Index);
	rect->p4 = CVint3_new(L,center->x-rect->halfLength, center->y-rect->halfHeight, center->z,&rect->_p4Index);
	GETSET_CRectMETATABLE;
	return 1;
}

//CRect.newDefault()
static int Rect_newDefault(lua_State *L)
{
	NEW_CRectUSERDATA(rect);
	rect->halfLength = 0;
	rect->halfHeight = 0;
	rect->radian = 0;
	rect->center = CVint3_new(L,0,0,0,&rect->_centerIndex);
	rect->p1 = CVint3_new(L,0,0,0,&rect->_p1Index);
	rect->p2 = CVint3_new(L,0,0,0,&rect->_p2Index);
	rect->p3 = CVint3_new(L,0,0,0,&rect->_p3Index);
	rect->p4 = CVint3_new(L,0,0,0,&rect->_p4Index);
	GETSET_CRectMETATABLE;
	return 1;
}
//CRect.Copy(oneCRect)
static int Rect_Copy(lua_State *L)
{
	GETSELF_CRect(copyRect);
	ARGCHECK(copyRect != NULL);
	
	NEW_CRectUSERDATA(rect);
	rect->halfLength = copyRect->halfLength;
	rect->halfHeight = copyRect->halfHeight;
	rect->radian = copyRect->radian;
	rect->center = CVint3_new(L,copyRect->center->x,copyRect->center->y,copyRect->center->z,&rect->_centerIndex);
	rect->p1 = CVint3_new(L,copyRect->p1->x,copyRect->p1->y,copyRect->p1->z,&rect->_p1Index);
	rect->p2 = CVint3_new(L,copyRect->p2->x,copyRect->p2->y,copyRect->p2->z,&rect->_p2Index);
	rect->p3 = CVint3_new(L,copyRect->p3->x,copyRect->p3->y,copyRect->p3->z,&rect->_p3Index);
	rect->p4 = CVint3_new(L,copyRect->p4->x,copyRect->p4->y,copyRect->p4->z,&rect->_p4Index);
	GETSET_CRectMETATABLE;
	return 1;
}
//cRect:copy(oneCRect)
static int Rect_copy(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	const struct CRect* copyRect = (struct CRect*)lua_touserdata(L, 2);
	ARGCHECK(copyRect != NULL);
	
	rect->halfLength = copyRect->halfLength;
	rect->halfHeight = copyRect->halfHeight;
	rect->radian = copyRect->radian;
	CVint3_copy(rect->center,copyRect->center);
	CVint3_ctor(rect->p1, rect->center->x-rect->halfLength, rect->center->y+rect->halfHeight, rect->center->z);
	CVint3_ctor(rect->p2, rect->center->x+rect->halfLength, rect->center->y+rect->halfHeight, rect->center->z);
	CVint3_ctor(rect->p3, rect->center->x+rect->halfLength, rect->center->y-rect->halfHeight, rect->center->z);
	CVint3_ctor(rect->p4, rect->center->x-rect->halfLength, rect->center->y-rect->halfHeight, rect->center->z);

	lua_pop(L,1);
	return 1;
}
//CRect:ctor(length,height,center)
static int Rect_ctor(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);

	const double length = lua_tonumber(L,2);
	const double height = lua_tonumber(L,3);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 4);
	ARGCHECK(center != NULL);

	rect->halfLength = CINT_ROUND(length * DoubleScale / 2);
	rect->halfHeight = CINT_ROUND(height * DoubleScale / 2);
	rect->radian = 0;
	CVint3_copy(rect->center,center);
	UPDATE_POS_CENTERCHANGE(rect);
	
	lua_pop(L,3);
	return 1;
}

static int Rect_halfLengthHeight(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL)
	double num1 = GET_SCALEVALUE(rect->halfLength);
	double num2 = GET_SCALEVALUE(rect->halfHeight);
	lua_pushnumber(L,num1);
	lua_pushnumber(L,num2);
	return 2;
}
static int Rect_radian(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	double num = GET_SCALEVALUE(rect->radian);
	lua_pushnumber(L,num);
	return 1;
}
GET_ONEPOS_FUN(Rect_center,center);

static int Rect_centerXYZ(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	lua_pushnumber(L,ScaleValue2Num(rect->center->x));
	lua_pushnumber(L,ScaleValue2Num(rect->center->y));
	lua_pushnumber(L,ScaleValue2Num(rect->center->z));
	return 3;
}
//GET_ONEPOS_REF_FUN(Rect_centerRef,center);
GET_ONEPOS_FUN(Rect_p1,p1);
//GET_ONEPOS_REF_FUN(Rect_p1Ref,p1);
GET_ONEPOS_FUN(Rect_p2,p2);
//GET_ONEPOS_REF_FUN(Rect_p2Ref,p2);
GET_ONEPOS_FUN(Rect_p3,p3);
//GET_ONEPOS_REF_FUN(Rect_p3Ref,p3);
GET_ONEPOS_FUN(Rect_p4,p4);
//GET_ONEPOS_REF_FUN(Rect_p4Ref,p4);
static int Rect_ps(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	{
		NEW_USERDATA(VInt3,p1);
		CVint3_copy(p1,rect->p1);
		GETSET_METATABLE("VInt3");
	}
	{
		NEW_USERDATA(VInt3,p2);
		CVint3_copy(p2,rect->p2);
		GETSET_METATABLE("VInt3");
	}
	{
		NEW_USERDATA(VInt3,p3);
		CVint3_copy(p3,rect->p3);
		GETSET_METATABLE("VInt3");
	}
	{
		NEW_USERDATA(VInt3,p4);
		CVint3_copy(p4,rect->p4);
		GETSET_METATABLE("VInt3");
	}
	return 4;
}
// static int Rect_psRef(lua_State *L)
// {
// 	GETSELF_CRect(rect);
// 	ARGCHECK(rect != NULL);
// 	luaC_pushuserdata(L,rect->p1);
// 	luaC_pushuserdata(L,rect->p2);
// 	luaC_pushuserdata(L,rect->p3);
// 	luaC_pushuserdata(L,rect->p4);
// 	return 4;
// }

//cRect:setCenter(vInt3)
static int Rect_setCenter(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(center != NULL);

	CVint3_copy(rect->center,center);
	UPDATE_POS_CENTERCHANGE(rect);
	UPDATE_POS_RADIANCHANGE(rect);

	lua_pop(L,1);
	return 1;
}
//矩形绕点旋转 cRect:rotate(center,radian)
static int Rect_rotate(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	const struct VInt3* center = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(center != NULL);
	const double radian = lua_tonumber(L,3);
	rect->radian = CINT_ROUND(radian*IntScale);
	UPDATE_POS_RADIANCHANGE(rect);

	lua_pop(L,2);
	return 1;
}
//朝某个方向移动一定距离 cRect:move(dirVint,distance)
static int Rect_move(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	const struct VInt3* dirVint = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(dirVint != NULL);
	const double distance = lua_tonumber(L,3);
	
	struct VInt3 morlDir = {dirVint->x,dirVint->y,dirVint->z};
	CVInt3_normalize(&morlDir);
	rect->center->x = rect->center->x + CINT_ROUND(morlDir.x*distance);
	rect->center->y = rect->center->y + CINT_ROUND(morlDir.y*distance);
	rect->center->z = rect->center->z + CINT_ROUND(morlDir.z*distance);
	UPDATE_POS_CENTERCHANGE(rect);
	UPDATE_POS_RADIANCHANGE(rect);

	lua_pop(L,2);
	return 1;
}
//rect:calPosByTwoPosAndHeight(startVInt3,endVInt3,iHeight,iStartDistanceEX,iEndDistanceEX)
//根据两个点和宽度计算矩形的四个顶点
//简单版本，只会更新矩形的四个顶点，不更新矩形的其他信息
//iHeight : 矩形宽度
//iStartDistanceEX ： 延长距离，根据开始点到结束点的方向，反向延长矩形的长度
//iEndDistanceEX ：   延长距离，根据开始点到结束点的方向，正向延长矩形的长度
static int Rect_calPosByTwoPosAndHeight(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	const struct VInt3* startVInt3 = (struct VInt3*)lua_touserdata(L, 2);
	ARGCHECK(startVInt3 != NULL);
	const struct VInt3* endVInt3 = (struct VInt3*)lua_touserdata(L, 3);
	ARGCHECK(endVInt3 != NULL);
	const double iHeight = lua_tonumber(L,4);
	const double iStartDistanceEX = lua_tonumber(L,5);
	const double iEndDistanceEX = lua_tonumber(L,6);

	struct VInt3 _startVInt3 = {startVInt3->x,startVInt3->y,startVInt3->z};
	struct VInt3 _endVInt3 = {endVInt3->x,endVInt3->y,endVInt3->z};
	struct VInt3 dir = {endVInt3->x-startVInt3->x,endVInt3->y-startVInt3->y,endVInt3->z-startVInt3->z};
	CVInt3_normalizeXY(&dir);

	if (Equal(iStartDistanceEX,1) == FALSE)
	{
		_startVInt3.x = _startVInt3.x +  CINT_ROUND((-dir.x) * iStartDistanceEX);
		_startVInt3.y = _startVInt3.y +  CINT_ROUND((-dir.y) * iStartDistanceEX);
	}
	if (Equal(iEndDistanceEX,1) == FALSE)
	{
		_endVInt3.x = _endVInt3.x +  CINT_ROUND(dir.x * iEndDistanceEX);
		_endVInt3.y = _endVInt3.y +  CINT_ROUND(dir.y * iEndDistanceEX);
	}
	
	struct VInt3 leftDir = {dir.x,dir.y,dir.z};
	struct VInt3 rightDir = {dir.x,dir.y,dir.z};
	CVint3_rotateVector3(&leftDir,&ZeroVInt3,Num2ScaleValue(1.57));//旋转90度
	CVint3_rotateVector3(&rightDir,&ZeroVInt3,Num2ScaleValue(1.57));//旋转90度

	// p1----------p2
	//  |          |   矩形图示
	// p4----------p3
	rect->p1->x = _startVInt3.x + leftDir.x * iHeight/2;
	rect->p1->y = _startVInt3.y + leftDir.y * iHeight/2;

	rect->p2->x = _endVInt3.x + leftDir.x * iHeight/2;
	rect->p2->y = _endVInt3.y + leftDir.y * iHeight/2;

	rect->p4->x = _startVInt3.x + rightDir.x * iHeight/2;
	rect->p4->y = _startVInt3.y + rightDir.y * iHeight/2;

	rect->p3->x = _endVInt3.x + rightDir.x * iHeight/2;
	rect->p3->y = _endVInt3.y + rightDir.x * iHeight/2;

	lua_pop(L,5);
	return 1;
}

static int Rect__tostring(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	
	char buf[400]={0};
	sprintf(buf,"halfLength:%.4f , halfHeight:%.4f , radian:%.4f , p1x:%.4f ,p1y:%.4f, p1z:%.4f , p2x:%.4f ,p2y:%.4f, p2z:%.4f , p3x:%.4f ,p3y:%.4f, p3z:%.4f , p4x:%.4f ,p4y:%.4f, p4z:%.4f",
		ScaleValue2Num(rect->halfLength),ScaleValue2Num(rect->halfHeight),ScaleValue2Num(rect->radian),
			ScaleValue2Num(rect->p1->x),ScaleValue2Num(rect->p1->y),ScaleValue2Num(rect->p1->z),
			ScaleValue2Num(rect->p2->x),ScaleValue2Num(rect->p2->y),ScaleValue2Num(rect->p2->z),
			ScaleValue2Num(rect->p3->x),ScaleValue2Num(rect->p3->y),ScaleValue2Num(rect->p3->z),
			ScaleValue2Num(rect->p4->x),ScaleValue2Num(rect->p4->y),ScaleValue2Num(rect->p4->z));
	// sprintf(buf,"halfLength:%d , halfHeight:%d , radian:%d , p1x:%d ,p1y:%d, p1z:%d , p2x:%d ,p2y:%d, p2z:%d , p3x:%d ,p3y:%d, p3z:%d , p4x:%d ,p4y:%d, p4z:%d",
	// 		rect->halfLength,rect->halfHeight,rect->radian,
	// 		rect->p1->x,rect->p1->y,rect->p1->z,
	// 		rect->p2->x,rect->p2->y,rect->p2->z,
	// 		rect->p3->x,rect->p3->y,rect->p3->z,
	// 		rect->p4->x,rect->p4->y,rect->p4->z);
	lua_pushstring(L,buf);
	return 1;
}

static int Rect_gc(lua_State *L)
{
	GETSELF_CRect(rect);
	ARGCHECK(rect != NULL);
	LUA_UNREF(rect->_centerIndex)
	LUA_UNREF(rect->_p1Index)
	LUA_UNREF(rect->_p2Index)
	LUA_UNREF(rect->_p3Index)
	LUA_UNREF(rect->_p4Index)
	return 1;
}
// static int Rect_test(lua_State *L)
// {
// 	lua_pushnumber(L,count);
// 	return 1;
// }

static struct luaL_Reg vecMetaFunc[] =
{
 	{"halfLengthHeight", Rect_halfLengthHeight},
 	{"radian", Rect_radian},
 	{"center", Rect_center},
 	{"centerXYZ", Rect_centerXYZ},
 	{"setCenter", Rect_setCenter},
 	//{"centerRef", Rect_centerRef},
 	{"p1", Rect_p1},
 	//{"p1Ref", Rect_p1Ref},
 	{"p2", Rect_p2},
 	//{"p2Ref", Rect_p2Ref},
 	{"p3", Rect_p3},
 	//{"p3Ref", Rect_p3Ref},
 	{"p4", Rect_p4},
 	//{"p4Ref", Rect_p4Ref},
	{"ps", Rect_ps},
	//{"psRef", Rect_psRef},
 	{"ctor", Rect_ctor},
 	{"copy", Rect_copy},
 	{"rotate", Rect_rotate},
 	{"move", Rect_move},
 	{"calPosByTwoPosAndHeight", Rect_calPosByTwoPosAndHeight},
 	{"__tostring", Rect__tostring},
    {"__gc", Rect_gc},
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
	{"new", Rect_new},
	{"newDefault", Rect_newDefault},
	{"Copy", Rect_Copy},
	//{"test", Rect_test},
	{NULL, NULL}
};

LUALIB_API int luaopen_CRect(lua_State *L)
{
	luaL_register(L, "CRect", vecFunc);
	luaL_newmetatable(L, "CRect");
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
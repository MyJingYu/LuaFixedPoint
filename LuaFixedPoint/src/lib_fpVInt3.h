#ifndef CVInt3_h
#define CVInt3_h

#include "lib_fpStruct.h"
#include "lib_fpIntCfg.h"
#include "lib_fpIntMathUtil.h"
#include "lua.h"
#include "lauxlib.h"

static struct VInt3 ZeroVInt3 = {0,0,0};

static BOOL CVint3_equel(const struct VInt3* v1, const struct VInt3* v2);
static BOOL CVint3_equelXY(const struct VInt3* v1, const struct VInt3* v2);
//
static struct VInt3* CVint3_new(lua_State *L,const CINT x, const CINT y, const CINT z, int* outRefIndex);
//将fromVint3 拷贝到toVInt3 中
static struct VInt3* CVint3_copy(struct VInt3* toVInt3, const struct VInt3* fromVint3);
static struct VInt3* CVint3_copyXY(struct VInt3* toVInt3, const struct VInt3* fromVint3);
//初始化toVInt3
static struct VInt3* CVint3_ctor(struct VInt3* toVInt3, const CINT x, const CINT y, const CINT z);
//坐标绕点(centerVInt3)旋转
static struct VInt3* CVint3_rotateVector3(struct VInt3* vInt3, const struct VInt3* centerVInt3, const CINT radian);

//返回的double是实际的值（不是放大的定点数）
static double CVint3_length(const struct VInt3* vInt3);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_lengthSqu(const struct VInt3* vInt3);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_lengthXY(const struct VInt3* vInt3);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_lengthXYSqu(const struct VInt3* vInt3);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_distance(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_distanceSqu(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_distanceXY(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2);
//返回的double是实际的值（不是放大的定点数）
static double CVint3_distanceXYSqu(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2);



static BOOL CVint3_equel(const struct VInt3* v1, const struct VInt3* v2)
{
	if (Equal(v1->x,v2->x) == TRUE && Equal(v1->y,v2->y) == TRUE && Equal(v1->z,v2->z) == TRUE)
		return TRUE;
	else
		return FALSE;
}

static BOOL CVint3_equelXY(const struct VInt3* v1, const struct VInt3* v2)
{
	if (Equal(v1->x,v2->x) == TRUE && Equal(v1->y,v2->y) == TRUE)
		return TRUE;
	else
		return FALSE;
}

static struct VInt3* CVint3_new(lua_State *L, const CINT x, const CINT y, const CINT z, int* outRefIndex)
{
	//size_t iBytes = sizeof(struct VInt3);
	//struct VInt3* pVint3 = (struct VInt3*)luaC_newuserdata(L, iBytes); //为了使这个userdata可以返回到lua层，使用luaC_ //不安全，会丢失
	//struct VInt3* pVint3 = (struct VInt3*)lua_newuserdata(L, iBytes); //为了使这个userdata可以返回到lua层，使用luaC_
	NEW_USERDATA(VInt3,pVint3);
	pVint3->x = x;
	pVint3->y = y;
	pVint3->z = z;
	GETSET_METATABLE("VInt3");
	*outRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);//会弹出栈顶对象
	//lua_pop(L,1); 
	
	return pVint3;
}

static struct VInt3* CVInt3_normalize(struct VInt3* vint3)
{
	CINT _lengthSqu = vint3->x * vint3->x + vint3->y* vint3->y + vint3->z* vint3->z;
	double length = KEEP_DECIMAL(sqrt(_lengthSqu)/DoubleScale);
	if ( FALSE == Equal(length,0) && FALSE == Equal(length,1))
	{
		vint3->x = CINT_ROUND(vint3->x / length);
		vint3->y = CINT_ROUND(vint3->y / length);
		vint3->z = CINT_ROUND(vint3->z / length);
	}
	return vint3;
}

static struct VInt3* CVInt3_normalizeXY(struct VInt3* vint3)
{
	CINT _lengthSqu = vint3->x * vint3->x + vint3->y* vint3->y;
	double length = KEEP_DECIMAL(sqrt(_lengthSqu)/DoubleScale);
	if ( FALSE == Equal(length,0) && FALSE == Equal(length,1))
	{
		vint3->x = CINT_ROUND(vint3->x / length);
		vint3->y = CINT_ROUND(vint3->y / length);
	}
	return vint3;
}

static struct VInt3* CVint3_copy(struct VInt3* toVInt3, const struct VInt3* fromVint3)
{
	toVInt3->x = fromVint3->x;
	toVInt3->y = fromVint3->y;
	toVInt3->z = fromVint3->z;
	return toVInt3;
}
static struct VInt3* CVint3_copyXY(struct VInt3* toVInt3, const struct VInt3* fromVint3)
{
	toVInt3->x = fromVint3->x;
	toVInt3->y = fromVint3->y;
	return toVInt3;
}

static struct VInt3* CVint3_ctor(struct VInt3* toVInt3, const CINT x, const CINT y, const CINT z)
{
	toVInt3->x = x;
	toVInt3->y = y;
	toVInt3->z = z;
	return toVInt3;
}

static struct VInt3* CVint3_rotateVector3(struct VInt3* vInt3, const struct VInt3* centerVInt3, const CINT radian)
{
	double _radian = GET_SCALEVALUE(radian);
	double sinV = SinInt(_radian);
	double cosV = CosInt(_radian);
	double scaleX = (vInt3->x - centerVInt3->x)*cosV - (vInt3->y - centerVInt3->y)*sinV + centerVInt3->x;
	double scaleY = (vInt3->x - centerVInt3->x)*sinV + (vInt3->y - centerVInt3->y)*cosV + centerVInt3->y;
	CVint3_ctor(vInt3,CINT_ROUND(scaleX),CINT_ROUND(scaleY),vInt3->z);
	return vInt3;
}

static double CVint3_length(const struct VInt3* vInt3)
{
    CINT _lengthSqu = vInt3->x*vInt3->x + vInt3->y*vInt3->y + vInt3->z*vInt3->z;
    double length = KEEP_DECIMAL(sqrt(_lengthSqu)/DoubleScale);
	return  length;
}
static double CVint3_lengthSqu(const struct VInt3* vInt3)
{
	CINT _lengthSqu = vInt3->x*vInt3->x + vInt3->y*vInt3->y + vInt3->z*vInt3->z;
	double lengthSqu = KEEP_DECIMAL(_lengthSqu/(DoubleScale*DoubleScale));
	return lengthSqu;
}
static double CVint3_lengthXY(const struct VInt3* vInt3)
{
	CINT _lengthSqu = vInt3->x*vInt3->x + vInt3->y*vInt3->y;
	double length = KEEP_DECIMAL(sqrt(_lengthSqu)/DoubleScale);
	return  length;
}
static double CVint3_lengthXYSqu(const struct VInt3* vInt3)
{
	CINT _lengthSqu = vInt3->x*vInt3->x + vInt3->y*vInt3->y;
	double lengthSqu = KEEP_DECIMAL(_lengthSqu/(DoubleScale*DoubleScale));
	return lengthSqu;
}
static double CVint3_distance(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2)
{
	CINT disX = vInt3_1->x - vInt3_2->x;
	CINT disY = vInt3_1->y - vInt3_2->y;
	CINT disZ = vInt3_1->z - vInt3_2->z;
	CINT _lengthSqu = disX*disX + disY*disY + disZ*disZ;
	double length = KEEP_DECIMAL(sqrt(_lengthSqu)/DoubleScale);
	return length;
}
static double CVint3_distanceSqu(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2)
{
	CINT disX = vInt3_1->x - vInt3_2->x;
	CINT disY = vInt3_1->y - vInt3_2->y;
	CINT disZ = vInt3_1->z - vInt3_2->z;
	CINT _lengthSqu = disX*disX + disY*disY + disZ*disZ;
	double lengthSqu = KEEP_DECIMAL(_lengthSqu/(DoubleScale*DoubleScale));
	return lengthSqu;
}
static double CVint3_distanceXY(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2)
{
	CINT disX = vInt3_1->x - vInt3_2->x;
	CINT disY = vInt3_1->y - vInt3_2->y;
	CINT _lengthSqu = disX*disX + disY*disY;
	double length = KEEP_DECIMAL(sqrt(_lengthSqu)/DoubleScale);
	return length;
}
static double CVint3_distanceXYSqu(const struct VInt3* vInt3_1, const struct VInt3* vInt3_2)
{
	CINT disX = vInt3_1->x - vInt3_2->x;
	CINT disY = vInt3_1->y - vInt3_2->y;
	CINT _lengthSqu = disX*disX + disY*disY;
	double lengthSqu = KEEP_DECIMAL(_lengthSqu/(DoubleScale*DoubleScale));
	return lengthSqu;
}

#endif
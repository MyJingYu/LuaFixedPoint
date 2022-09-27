#ifndef CPhysicUtil_h
#define CPhysicUtil_h

#include "lib_fpIntCfg.h"
#include "lib_fpStruct.h"
#include "lib_fpVInt3.h"
#include "lib_fpIntMathUtil.h"

//判断一个点是否在矩形内(XY平面)
static BOOL IsVInt3InRectXY(const struct VInt3* vInt3, const struct CRect* cRect);
//判断两个圆是否相交（XY平面）
static BOOL IsCircleIntersectCircle(const struct CCircle* circle1,const struct CCircle* circle2);
//判断矩形和圆是否相交（XY平面）
static BOOL IsRectIntersectCircleXY(const struct CRect* rect, const struct CCircle* circle);


// ==================================================

//计算|p1 p2| X |p1 p|
static double _getCross(const struct VInt3* p1,const struct VInt3* p2,const struct VInt3* p)
{
	double px = ScaleValue2Num(p->x);
	double py = ScaleValue2Num(p->y);
	double p1x = ScaleValue2Num(p1->x);
	double p1y = ScaleValue2Num(p1->y);
	double p2x = ScaleValue2Num(p2->x);
	double p2y = ScaleValue2Num(p2->y);
	return (p2x - p1x) * (py - p1y) -(px - p1x) * (p2y - p1y);
}

//判断一个点是否在矩形内(XY平面)
//https://blog.csdn.net/weixin_43619346/article/details/107513919
static BOOL IsVInt3InRectXY(const struct VInt3* vInt3, const struct CRect* rect)
{
	if (_getCross(rect->p1,rect->p2,vInt3)*_getCross(rect->p3,rect->p4,vInt3) >= 0 &&
		_getCross(rect->p2,rect->p3,vInt3)*_getCross(rect->p4,rect->p1,vInt3) >= 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//判断两个圆是否相交（XY平面）
static BOOL IsCircleIntersectCircleXY(const struct CCircle* circle1,const struct CCircle* circle2)
{
	double dis = CVint3_distanceXY(circle1->center,circle2->center);
	double radius = KEEP_DECIMAL((circle1->radius + circle2->radius)/DoubleScale);
	if (GreateEqual(radius,dis))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//判断矩形和圆是否相交（XY平面）
//https://leetcode-cn.com/problems/circle-and-rectangle-overlapping/solution/circle-and-rectangle-overlapping-by-ikaruga/
static BOOL IsRectIntersectCircleXY(const struct CRect* rect, const struct CCircle* circle)
{
	CINT v3CPos1TX,v3CPos1TY,v3RPos1TX,v3RPos1TY;
	double _radianR = ScaleValue2Num(rect->radian);//取真实的值
	if (FALSE == Equal(rect->radian,0))
	{
		double cosV = CosInt(_radianR);
		double sinV = SinInt(_radianR);

		v3CPos1TX = CINT_ROUND(cosV*circle->center->x - sinV*circle->center->y); //旋转变换
		v3CPos1TY = CINT_ROUND(sinV*circle->center->x + cosV*circle->center->y);
		v3RPos1TX = CINT_ROUND(cosV*rect->center->x - sinV*rect->center->y);
		v3RPos1TY = CINT_ROUND(sinV*rect->center->x + cosV*rect->center->y);
	}
	else
	{
		v3CPos1TX = circle->center->x;
		v3CPos1TY = circle->center->y;
		v3RPos1TX = rect->center->x;
		v3RPos1TY = rect->center->y;
	}

	CINT p1 = Abs(v3CPos1TX-v3RPos1TX);
	CINT p2 = Abs(v3CPos1TY-v3RPos1TY);
	double q1 = ScaleValue2Num(rect->halfHeight);
	double q2 = ScaleValue2Num(rect->halfHeight);
	double uu1 = Max(p1-q1,0);	//重点：为负说明有更短的距离，即垂直（旋转矩阵在这里就不适用了）
	double uu2 = Max(p2-q2,0);

	double dd = _radianR*_radianR;
    double uLength = uu1*uu1 + uu2*uu2;
	return  GreateEqual(dd,uLength);//根据向量长度和半径比较判断重叠
}


#endif
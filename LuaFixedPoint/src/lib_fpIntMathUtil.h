#ifndef CIntMathUtil_h
#define CIntMathUtil_h

#include "lib_fpMacro.h"
#include "lib_fpIntCfg.h"
#include <math.h>

static double pi = 3.141592657;
static double A2R = 57.2957795; //角度到弧度的换算系数

static CINT Abs(CINT v);
static double DoubleAbs(double v);
// 数值相等判断
static BOOL Equal(double v1, double v2);
// v1 > v2
static BOOL Greate(const double v1, const double v2);
// v1 >= v2
static BOOL GreateEqual(const double v1, const double v2);
// 将数值进行定点数放大
static CINT Num2ScaleValue(double num);
// 将定点放大的数缩小成正常的值，保留两位小数
static double ScaleValue2Num(CINT value);
static double SinInt(double radian);
static double CosInt(double radian);
static double TanInt(double radian);
static double ASinInt(double v);
static double ACosInt(double v);
static double ATanInt(double v);
static double Angle2Radian(double angle);
static double Radian2Angle(double radian);
static double Max(double v1, double v2);
static double Min(double v1, double v2);


// =======================================================

static CINT Abs(CINT v)
{
	if (v<0)
	{
		return v;
	}
	else
	{
		return  -v;
	}
}

static double DoubleAbs(double v)
{
	//return abs(v); @todo 可以直接这样吗
	if (v<0){
		return -v;
	}
	else{
		return v;
	}
}

// 数值相等判断
static BOOL Equal(double v1, double v2) //C 没有bool
{
	double dis = DoubleAbs(v1 - v2);
	return (dis < Equal_ErrorVlaue) ? TRUE : FALSE;
}

// v1 > v2
static BOOL Greate(const double v1, const double v2){
	double dis = DoubleAbs(v1 - v2);
	return  (~(dis < Equal_ErrorVlaue) && v1 >v2) ? TRUE : FALSE ;
};

// v1 >= v2
static BOOL GreateEqual(const double v1, const double v2){
	double dis = DoubleAbs(v1 - v2);
	return  ((dis < Equal_ErrorVlaue) || v1 >v2) ? TRUE : FALSE ;
};

// 将数值进行定点数放大
static CINT Num2ScaleValue(double num)
{
	num *= IntScale;
	num = CINT_ROUND(num);
	return num;
}

// 将定点放大的数缩小成正常的值，保留指定位小数
static double ScaleValue2Num(CINT value)
{
	double num = GET_SCALEVALUE(value);
	return num;
}

static double SinInt(double radian)
{
	double num = sin(radian);
	num = KEEP_DECIMAL(num);
	return num;
}
static double CosInt(double radian)
{
	double num = cos(radian);
	num = KEEP_DECIMAL(num);
	return num;
}
static double TanInt(double radian)
{
	double num = tan(radian);
	num = KEEP_DECIMAL(num);
	return num;
}
static double ASinInt(double v)
{
	double radian = asin(v);
	radian = KEEP_DECIMAL(radian);
	return radian;
}
static double ACosInt(double v)
{
	double radian = acos(v);
	radian = KEEP_DECIMAL(radian);
	return radian;
}
static double ATanInt(double v)
{
	double radian = atan(v);
	radian = KEEP_DECIMAL(radian);
	return radian;
}
static double Angle2Radian(double angle)
{
	double radian = KEEP_DECIMAL(angle/A2R);
	return radian;
}
static double Radian2Angle(double radian)
{
	double angle = KEEP_DECIMAL(radian*A2R);
	return angle;
}

static double Max(double v1, double v2)
{
	if (GreateEqual(v1,v2))
	{
		return v1;
	}
	else
	{
		return v2;
	}
}

static double Min(double v1, double v2)
{
	if (GreateEqual(v1,v2))
	{
		return v2;
	}
	else
	{
		return v1;
	}
}

#endif
#ifndef CFixedPointStruct_h
#define CFixedPointStruct_h

#include "lib_fpIntCfg.h"

//坐标
struct VInt3
{
	CINT x;
	CINT y;
	CINT z;
};


//矩形
struct CRect
{
	CINT halfLength;	//长度即x
	CINT halfHeight;	//宽度即y
	CINT radian;		//选择弧度
	struct VInt3* center;	//中心坐标
	int _centerIndex;		//中心点的userdata引用index (luaL_ref的返回值)（将center添加引用，避免释放）
	struct VInt3* p1;		//左上点
	int _p1Index;
	struct VInt3* p2;		//右上
	int _p2Index;
	struct VInt3* p3;		//左下
	int _p3Index;
	struct VInt3* p4;		//右下
	int _p4Index;
};

//圆
struct CCircle
{
	CINT radius;			//半径
	struct VInt3* center;	//中心坐标
	int _centerIndex;
};

//线段
struct CLine
{
	struct VInt3* p1;
	int _p1Index;
	struct VInt3* p2;
	int _p2Index;
};

#endif
#ifndef CFixedPointStruct_h
#define CFixedPointStruct_h

#include "lib_fpIntCfg.h"

//����
struct VInt3
{
	CINT x;
	CINT y;
	CINT z;
};


//����
struct CRect
{
	CINT halfLength;	//���ȼ�x
	CINT halfHeight;	//��ȼ�y
	CINT radian;		//ѡ�񻡶�
	struct VInt3* center;	//��������
	int _centerIndex;		//���ĵ��userdata����index (luaL_ref�ķ���ֵ)����center������ã������ͷţ�
	struct VInt3* p1;		//���ϵ�
	int _p1Index;
	struct VInt3* p2;		//����
	int _p2Index;
	struct VInt3* p3;		//����
	int _p3Index;
	struct VInt3* p4;		//����
	int _p4Index;
};

//Բ
struct CCircle
{
	CINT radius;			//�뾶
	struct VInt3* center;	//��������
	int _centerIndex;
};

//�߶�
struct CLine
{
	struct VInt3* p1;
	int _p1Index;
	struct VInt3* p2;
	int _p2Index;
};

#endif
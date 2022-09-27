#ifndef CIntCfg_h
#define CIntCfg_h

#define BOOL int
#define TRUE 1
#define FALSE 0

//ʹ��int32�洢������ʱ���Ե���
#define CINT long long
//#define CINT __int64
#define CFLOAT double

//�����������ţ�100 > ������λС���㣩
static const int IntScale = 1000;
static const float FloatScale = 1000.;
//���е��������double(��doubleʱ /FloatScale ��ȷ�Ȳ��� 1077/(float)100 = 10.77000005)
static const double DoubleScale = 1000.; 
//����С���Ĳ�ֵ�����������λС������Ϊ0.005,��λΪ0.0005
static const float KEEP_DECIMAL_VALUE = 0.0005;

static const double Equal_ErrorVlaue = 0.0000001;


#endif
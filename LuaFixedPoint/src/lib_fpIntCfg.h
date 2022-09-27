#ifndef CIntCfg_h
#define CIntCfg_h

#define BOOL int
#define TRUE 1
#define FALSE 0

//使用int32存储，不足时可以调整
#define CINT long long
//#define CINT __int64
#define CFLOAT double

//定点数的缩放（100 > 保留两位小数点）
static const int IntScale = 1000;
static const float FloatScale = 1000.;
//所有的相除请用double(非double时 /FloatScale 精确度不对 1077/(float)100 = 10.77000005)
static const double DoubleScale = 1000.; 
//保留小数的插值，如果保留两位小数，则为0.005,三位为0.0005
static const float KEEP_DECIMAL_VALUE = 0.0005;

static const double Equal_ErrorVlaue = 0.0000001;


#endif
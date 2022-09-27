--[[
    API:
        LIntMath.C.Num2ScaleValue(num)
        将数值num进行定点数放大

        LIntMath.C.ScaleValue2Num(scaleV)
        将定点放大的scaleV缩小成正常的值，保留规定位小数

        LIntMath.C.KeepDecimal(num)
        将数值num保留规定位小数
        
        LIntMath.C.Round(num)
        四色五入

        LIntMath.C.Sqrt(num)
        开平方，结果会保留规定位小数

        LIntMath.C.Sin(radian)
        三角函数计算，结果会保留规定位小数

        LIntMath.C.Cos(radian)
        三角函数计算，结果会保留规定位小数
        
        LIntMath.C.Tan(radian)
        三角函数计算，结果会保留规定位小数
        
        LIntMath.C.ASin(sinV)
        三角函数计算，返回弧度，结果会保留规定位小数
        
        LIntMath.C.ACos(cosV)
        三角函数计算，返回弧度，结果会保留规定位小数
        
        LIntMath.C.ATan(tanV)
        三角函数计算，返回弧度，结果会保留规定位小数
        
        LIntMath.C.SinAngle(angle)
        三角函数计算，结果会保留规定位小数
        
        LIntMath.C.CosAngle(angle)
        三角函数计算，结果会保留规定位小数
        
        LIntMath.C.TanAngle(angle)
        三角函数计算，结果会保留规定位小数
        
        LIntMath.C.ASinAngle(sinV)
        三角函数计算，返回角度，结果会保留规定位小数
        
        LIntMath.C.ACosAngle(cosV)
        三角函数计算，返回角度，结果会保留规定位小数
        
        LIntMath.C.ATanAngle(tanV)
        三角函数计算，返回角度，结果会保留规定位小数
        
        LIntMath.C.Angle2Radian(angle)
        角度转弧度，结果会保留规定位小数
        
        LIntMath.C.Radian2Angle(radian)
        弧度转角度，结果会保留规定位小数
]]


local LIntMath = {}

LIntMath.C = CIntMath; -- c层对象

return LIntMath;
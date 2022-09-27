--[[
    API:（tip：一些存在消耗的函数请避免频繁使用）

        LCircle.C.new(radius,vint3_center)
        根据半径，圆心创建circle对象【消耗大】

        LCircle.C.newDefault()
        创建一个circle对象，默认半径为0，圆心0,0,0【消耗大】

        LCircle.C.Copy(oneCircle)
        创建一个circle对象，并拷贝oneCircle数据给该对象【消耗大】

        LCircle.C.Distance(circle1,circle2)
        LCircle.C.DistanceSqu(circle1,circle2)
        LCircle.C.DistanceXY(circle1,circle2)
        LCircle.C.DistanceXYSqu(circle1,circle2)
        获取两个圆的距离，返回结果保留规定位小数

        LCircle.C.DistanceVInt3(circle,vint3)
        LCircle.C.DistanceSquVInt3(circle,vint3)
        LCircle.C.DistanceXYVInt3(circle,vint3)
        LCircle.C.DistanceXYSquVInt3(circle,vint3)
        获取圆和坐标的距离，返回结果保留规定位小数

        circle:ctor(radius,vint3_center)
        初始化圆的数据

        circle:copy(circle_copy)
        将circle_copy的数据拷贝给circle
        
        circle:copyCenter(circle_copy)
        将circle_copy的圆心的数据拷贝给circle
        
        circle:copyRadius(circle_copy)
        将circle_copy的半径的数据拷贝给circle

        circle:radius()
        获取圆的半径，返回结果保留规定位小数

        circle:setRadius(num)
        设置半径

        circle:center()
        获取圆心，返回一个新的vint对象，无法通过修改返回值来改变圆的数据【消耗大】

        circle:setCenter(vint3)
        设置圆心

        circle:setCenterX()、circle:setCenterY()、circle:setCenterZ()、circle:setCenterXY()、circle:setCenterXYZ()
        通过xyz值设置圆心数据

        circle:centerCopy(vint3)、circle:centerCopyXY(vint3)
        将vint3的数据拷贝给圆心

        circle:getCenterX()、circle:getCenterY()、circle:getCenterZ()、circle:getCenterXY()、circle:getCenterXYZ()
        获取圆心的XYZ，返回结果保留规定位小数

        operator ==
        circle1 == circle2
        判断两个圆是否相等
]]


local LVInt3 = require "LVInt3"

local LCircle = {}

LCircle.C = CCircle; -- c层对象

function LCircle.ToString(cRect)
    local radius = cRect:radius();
    local centerX,centerY,centerZ = cRect:centerXYZ();
    return "radius:"..radius.." center:"..centerX..", "..centerY..", "..centerZ;
end


return LCircle


--[[
    API:（tip：一些存在消耗的函数请避免频繁使用）

        LVInt3.VInt3.new()
        创建一个VInt3对象【消耗大】

        LVInt3.VInt3.Copy(vint3)
        创建一个VInt3对象并拷贝给定的数据【消耗大】

        LVInt3.VInt3.Distance(vint3_1,vint3_2)
        两个坐标的距离，结果保留规定位小数

        LVInt3.VInt3.DistanceSqu(vint3_1,vint3_2)
        两个坐标的距离的平方，结果保留规定位小数
        
        LVInt3.VInt3.DistanceXY(vint3_1,vint3_2)
        两个坐标XY平面的距离，结果保留规定位小数

        LVInt3.VInt3.DistanceXYSqu(vint3_1,vint3_2)
        两个坐标XY平面的距离的平方，结果保留规定位小数

        LVInt3.VInt3.Dot(vint3_1,vint3_2)
        点乘，结果保留规定位小数
        
        LVInt3.VInt3.DotXY(vint3_1,vint3_2)
        XY平面的点乘，结果保留规定位小数
        
        LVInt3.VInt3.Cross(vint3_1,vint3_2)
        叉乘，返回一个新的vint3对象【消耗大】
        
        LVInt3.VInt3.CrossXY(vint3_1,vint3_2)
        叉乘，结果保留规定位小数。根据结果大于小于0判断vInt3_2 在vInt3_1的左右边（sin）

        LVInt3.VInt3.RotateXY(vint3,vint3_center,radian)
        点vint3绕中心点vint3_center选择弧度radian，得到一个新的vint3对象【消耗大】

        LVInt3.VInt3.IsFront(vint3_selfPos,vint3_sewlfPosDir,vint3_targetPos)
        根据点selfPos和selfPos的朝向sewlfPosDir，判断targetPos是否在selfPos的前面

        operator +、-、*、/
        vint3_new = vint3_1 + vint3_2 or vint3_new = vint3_1 + num
        坐标的运算符计算，可同vint3或number计算，结果返回一个新的vint3对象【消耗大】

        operator ==
        vint3_1 == vint3_2
        判断两个坐标是否相等

        vint3:equalXY(vint3_1)
        判断vint3和vint3_1的XY是否相等

        vint3:ctor(x,y,z)
        设置vint3的xyz值

        vint3:copy(vint3_copy)
        拷贝vint3_copy的xyz值给vint3

        vint3:copyXY(vint3_copy)
        拷贝vint3_copy的xy值给vint3

        vint3:add(vint3_1)/vint3:add(num)
        vint3:sub(vint3_1)/vint3:sub(num)
        vint3:mul(vint3_1)/vint3:mul(num)
        vint3:div(vint3_1)/vint3:div(num)
        vint3加减乘除一个坐标或数值，会改变vint3

        vint3:Op##2V(vInt3_1,vInt3_2)/vint3:Op##2V(num,vInt3_2)/vint3:Op##2V(vInt3_1,num)
        vint3:Op##XY2V(vInt3_1,vInt3_2)/vint3:Op##XY2V(num,vInt3_2)/vint3:Op##XY2V(vInt3_1,num)
        Op:add、sub、mul、div
        将两个坐标或坐标和number加减乘除，并将结果赋值给vint3

        vint3:length()/vint3:lengthSqu()/vint3:lengthXY()/vint3:lengthXYSqu()
        计算向量vint3的长度，结果保留规定位小数

        vint3:distance(vint3_1)/vint3:distanceSqu(vint3_1)/vint3:distanceXY(vint3_1)/vint3:distanceXYSqu(vint3_1)
        坐标vint3到vint3_1的距离，结果保留规定位小数

        vint3:normalize()
        将vint3归一化

        vint3:normalizeXY()
        将vint3的XY归一化，Z不变

        vint3:x()/vint3:y()/vint3:z()/vint3:xy()/vint3:xz()/vint3:yz()/vint3:xyz()
        获取坐标的xyz,返回结果保留规定位小数【对比lua的直接访问变量，有一定消耗】

        vint3:xReal()/vint3:yReal()/vint3:zReal()/vint3:xyReal()/vint3:xzReal()/vint3:yzReal()/vint3:xyzReal()
        获取坐标的定点数发大的值，返回结果为整数【对比lua的直接访问变量，有一定消耗】

        vint3:setX()/vint3:setY()/vint3:setZ()/vint3:setXY()/vint3:setXZ()/vint3:setYZ()
        设置vint3的XYZ值【对比lua的直接赋值变量，有一定消耗】

        vint3:rotateXY(vint3_center,radian)
        点vint3绕vint3_center旋转弧度radian
]]


local Vector3 = require "GamePlay.Fight.Libs.Vector3"

-- lua层的VInt3,对c层的CVInt3做一些扩展支持
local LVInt3 = {}

LVInt3.VInt3 = VInt3; -- c层对象
LVInt3.VInt3Scale = VInt3.Scale();

LVInt3.zero = LVInt3.VInt3.new(0,0,0);
LVInt3.forward = LVInt3.VInt3.new(0,1,0);
LVInt3.forward_negative = LVInt3.VInt3.new(0,-1,0);
LVInt3.right = LVInt3.VInt3.new(1,0,0);
LVInt3.right_negative = LVInt3.VInt3.new(-1,0,0);
LVInt3.up = LVInt3.VInt3.new(0,0,1);
LVInt3.up_negative = LVInt3.VInt3.new(0,0,-1);

function LVInt3.ToString(cVInt3)
    local x,y,z = cVInt3:xyz();
    return table.concat({x,y,z},", ");
end

function LVInt3.RealValueToString(cVInt3)
    local x,y,z = cVInt3:xyz();
    local rx,ry,rz = cVInt3:xyzReal();
    return "ScaleValue: "..table.concat({x,y,z},", ").."    RealValue:"..table.concat({rx,ry,rz},", ");
end

function LVInt3.ToFVector(cVInt3)
    local x,y,z = cVInt3:xyz();
    return UE4.FVector(x,y,z);
end

function LVInt3.ToVector3(cVInt3)
    return Vector3.new(cVInt3:xyz())
end

return LVInt3;
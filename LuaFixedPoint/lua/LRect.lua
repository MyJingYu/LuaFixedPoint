--[[
    API:（tip：一些存在消耗的函数请避免频繁使用）

        LRect.C.new(length,height,vint3_center)
        根据长宽中心点创建rect对象【消耗大】

        LRect.C.newDefault()
        创建默认数据的rect对象，参数都为0【消耗大】

        LRect.C.Copy(oneRect)
        创建rect对象，并拷贝oneRect数据给该对象【消耗大】

        rect:ctor(length,height,vint3_center)
        初始化数据

        rect:copy(oneCRect)
        将oneCRect的数据拷贝给rect

        rect:rotate(vint3_center,radian)
        rect绕vint3_center旋转弧度radian，会更新四个顶点数据

        rect:move(vint3_dir,distance)
        rect朝某个方向移动一定距离,会更新四个顶点数据

        rect:halfLengthHeight()
        获取矩形的半长度宽度，返回结果保留规定位小数

        rect:radian()
        获取矩形旋转的弧度，返回结果保留规定位小数

        rect:center()
        获取rect的中心点，返回一个新的vint对象，无法通过修改返回值来改变矩形的数据【消耗大】

        rect:centerXYZ()
        获取rect中心点的xyz值，返回结果保留规定位小数

        rect:setCenter(vint3)
        设置rect的中心点，p1p2p3p4会跟着变化

        rect:p1()、rect:p2()、rect:p3()、rect:p4()、rect:ps()
        p1------p2
        |        |  矩形顶点示意图
        p4------p3
        获取矩形的四个顶点，返回一个新的vint对象，无法通过修改返回值来改变矩形的数据【消耗大】

        rect:calPosByTwoPosAndHeight(startVInt3,endVInt3,iHeight,iStartDistanceEX,iEndDistanceEX)
        特殊函数函数
        根据两个点和宽度计算矩形的四个顶点
        简单版本，只会更新矩形的四个顶点，不更新矩形的其他信息
        iHeight : 矩形宽度
        iStartDistanceEX ： 延长距离，根据开始点到结束点的方向，反向延长矩形的长度
        iEndDistanceEX ：   延长距离，根据开始点到结束点的方向，正向延长矩形的长度

]]


local LVInt3 = require "LVInt3"

local LRect = {}

LRect.C = CRect; -- c层对象

function LRect._posStr(x,y,z)
    return x..", ",y..", "..z
end

function LRect.ToString(cRect)
    -- local halfLength,halfHeight = cRect:halfLengthHeight();
    -- local radian = cRect:radian();
    -- local center = cRect:center();
    -- local p1,p2,p3,p4 = cRect:ps();
    -- return "halfLength:"..halfLength.." halfHeight:"..halfHeight.." radian:"..radian.." center:"..LVInt3.ToString(center).."\n\t"
    --         .."  p1:"..LVInt3.ToString(p1).."  p2:"..LVInt3.ToString(p2)
    --         .."  p3:"..LVInt3.ToString(p3).."  p4:"..LVInt3.ToString(p4);
    return tostring(cRect);
end

function LRect.PosToString(cRect)
    local p1,p2,p3,p4 = cRect:ps();
    return  "  p1:"..LVInt3.ToString(p1).."  p2:"..LVInt3.ToString(p2)
            .."  p3:"..LVInt3.ToString(p3).."  p4:"..LVInt3.ToString(p4);
end

return LRect


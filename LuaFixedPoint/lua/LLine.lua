--[[
    API:（tip：一些存在消耗的函数请避免频繁使用）

        LLine.C.new(vint3_p1,vint3_p2)
        创建line对象【消耗大】

        LLine.C.newDefault()
        创建line对象，两个顶点默认为0,0,0【消耗大】

        LLine.C.Copy(oneLine)
        创建line对象，并拷贝oneLine数据给该对象【消耗大】

        line:ctor(vint3_p1,vint3_p2)
        初始化线段的两个顶点

        line:copy(line_copy)
        将line_copy的数据拷贝给line

        operator ==
        line1 == line2
        判断两个线段是否相等

        line:ps()、line:p1()、line:p2()
        获取线段line的两个顶点，返回一个新的vint对象，无法通过修改返回值来改变线段的数据【消耗大】
]]


local LVInt3 = require "LVInt3"

local LLine = {}

LLine.C = CLine; -- c层对象

function LLine.ToString(cLine)
    local p1,p2 = cLine:ps();
    return "p1:"..LVInt3.ToString(p1).." p2:"..LVInt3.ToString(p2);
end


return LLine


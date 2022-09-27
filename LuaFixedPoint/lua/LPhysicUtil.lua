--[[
    API:
        LPhysicUtil.C.IsVInt3InRectXY(vInt3,rect)
        判断点是否在矩形内,只考虑XY平面

        LPhysicUtil.C.IsCircleIntersectCircleXY(circle1,circle2)
        判断两个圆是否相交,只考虑XY平面

        LPhysicUtil.C.IsRectIntersectCircleXY(rect,circle)
        判断矩形和圆是否相交,只考虑XY平面
]]


local LPhysicUtil = {}

LPhysicUtil.C = CPhysicUtil; -- c层对象

return LPhysicUtil;
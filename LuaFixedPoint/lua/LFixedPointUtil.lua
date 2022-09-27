--[[
    API:
        LFixedPointUtil.C.Scale()
        用于获取定点数的发大倍数
]]


local LFixedPointUtil = {}

LFixedPointUtil.C = CFixedPointUtil; -- c层对象

--定点数的缩放大小
LFixedPointUtil.Scale = LFixedPointUtil.C.Scale();

return LFixedPointUtil;
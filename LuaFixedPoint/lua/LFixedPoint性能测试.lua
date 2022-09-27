
local LVInt3 = require "LVInt3"
local LPhysicUtil = require "LPhysicUtil"
local LRect = require "LRect"
local LCircle = require "LCircle"
local LLine = require "LLine"

local LFixedPointTest = {}

function LFixedPointTest.test()
    LFixedPointTest.testGC()
end
function LFixedPointTest.testGC()
    -- gc 测试
    collectgarbage("collect") --先清空一次
	print("luaFP [gc 测试] 开始时内存占用:" .. (collectgarbage("count")/1024))

    local times = 1000000;
    for i = 1, times, 1 do
        local a = LRect.C.newDefault();
    end
	print("luaFP [gc 测试] 对象创建后内存占用:" .. (collectgarbage("count")/1024))
    collectgarbage("collect")
	print("luaFP [gc 测试] gc后内存占用:" .. (collectgarbage("count")/1024))
end

function LFixedPointTest.test1()
    -- 运算方式的消耗
    --[[
        LVInt3.VInt3.new(9,9,9) cost time:    2.1579999999999    
        cInt_2:copy(cInt_1) cost time:    0.23200000000008    
        VInt3:add(VInt3) cost time:    0.22400000000005    
        VInt3:add(Num) cost time:    0.38999999999999    
        (VInt3+VInt3) cost time:    2.001    
        (VInt3+Num) cost time:    2.177    
        VInt3:mul(VInt3) cost time:    0.553    
        VInt3:mul(Num) cost time:    0.77099999999996    
        (VInt3*VInt3) cost time:    2.317    
        (VInt3*Num) cost time:    2.4490000000001    
        lInt_1 == lInt_2 cost time:    0.23099999999999    b:    true    
        lInt_1 == lInt_3 cost time:    0.24200000000008    b:    false    
    ]]

    -- VInt3:add() 优于 运算符+ 【十倍+】
    local times = 10000000; --一千万
    if true then
        local cInt_1
        local lastTime = os.clock();
        for i = 1, times, 1 do
            cInt_1 = LVInt3.VInt3.new(9,9,9)
        end
        print("luaFP LVInt3.VInt3.new(9,9,9) cost time:",os.clock()-lastTime) --cost time:    2.1579999999999
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local cInt_2 = LVInt3.VInt3.new(0,0,0)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            cInt_2 = cInt_2:copy(cInt_1)
        end
        print("luaFP cInt_2:copy(cInt_1) cost time:",os.clock()-lastTime) --cost time:    0.23200000000008
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local cInt_2 = LVInt3.VInt3.new(1,2,3)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1:add(cInt_2);
        end
        print("luaFP VInt3:add(VInt3) cost time:",os.clock()-lastTime) --cost time:    0.22400000000005
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local num = 1
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1:add(num);
        end
        print("luaFP VInt3:add(Num) cost time:",os.clock()-lastTime) --cost time:    0.38999999999999
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local cInt_2 = LVInt3.VInt3.new(1,2,3)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1 + cInt_2
        end
        print("luaFP (VInt3+VInt3) cost time:",os.clock()-lastTime) --cost time:    2.001
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local num = 1
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1 + num
        end
        print("luaFP (VInt3+Num) cost time:",os.clock()-lastTime) --cost time:    2.177
    end

    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local cInt_2 = LVInt3.VInt3.new(1,2,3)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1:mul(cInt_2);
        end
        print("luaFP VInt3:mul(VInt3) cost time:",os.clock()-lastTime) --cost time:    0.553
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local num = 1
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1:mul(num);
        end
        print("luaFP VInt3:mul(Num) cost time:",os.clock()-lastTime) --cost time:    0.77099999999996
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local cInt_2 = LVInt3.VInt3.new(1,2,3)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1 * cInt_2
        end
        print("luaFP (VInt3*VInt3) cost time:",os.clock()-lastTime) --cost time:    2.317
    end
    if true then
        local cInt_1 = LVInt3.VInt3.new(9,9,9)
        local num = 1
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1 * num
        end
        print("luaFP (VInt3*Num) cost time:",os.clock()-lastTime) --cost time:    2.4490000000001
    end
    if true then
        local b
        local lInt_1 = LVInt3.VInt3.new(1,2,3)
        local lInt_2 = LVInt3.VInt3.new(1,2,3)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            b = lInt_1 == lInt_2;
        end
        print("luaFP lInt_1 == lInt_2 cost time:",os.clock()-lastTime,"b:",tostring(b)) --cost time:    0.23099999999999    b:    true
    end
    if true then
        local b
        local lInt_1 = LVInt3.VInt3.new(1,2,3)
        local lInt_3 = LVInt3.VInt3.new(1,2,3.2222)
        local lastTime = os.clock();
        for i = 1, times, 1 do
            b = lInt_1 == lInt_3;
        end
        print("luaFP lInt_1 == lInt_3 cost time:",os.clock()-lastTime,"b:",tostring(b)) --cost time:    0.24200000000008    b:    false
    end
end

function LFixedPointTest.test2()
    -- 计算测试

    local cInt_1 = LVInt3.VInt3.new(9.555,9.555,9.555)
    local cInt_2 = LVInt3.VInt3.new(1.222,2.222,3.222)
    local cInt_3 = LVInt3.VInt3.new(1.222,2.222,3.222)
    local num = 99.66666;
    -- +
    local result = cInt_1:add(cInt_2);
    print("luaFP cInt_1:add(cInt_2) = ",LVInt3.RealValueToString(result));
    result = result:add(num);
    print("luaFP result:add(num) = ",LVInt3.RealValueToString(result));
    result = result + cInt_2;
    print("luaFP result + cInt_2 = ",LVInt3.RealValueToString(result));
    result = result + num;
    print("luaFP result + num = ",LVInt3.RealValueToString(result));

    -- -
    result = result:sub(cInt_2);
    print("luaFP result:sub(cInt_2) = ",LVInt3.RealValueToString(result));
    result = result:sub(num);
    print("luaFP result:sub(num) = ",LVInt3.RealValueToString(result));
    result = result - cInt_2;
    print("luaFP result - cInt_2 = ",LVInt3.RealValueToString(result));
    result = result - num;
    print("luaFP result - num = ",LVInt3.RealValueToString(result));

    -- *
    result = result:mul(cInt_2);
    print("luaFP result:mul(cInt_2) = ",LVInt3.RealValueToString(result));
    result = result:mul(num);
    print("luaFP result:mul(num) = ",LVInt3.RealValueToString(result));
    result = result * cInt_2;
    print("luaFP result * cInt_2 = ",LVInt3.RealValueToString(result));
    result = result * num;
    print("luaFP result * num = ",LVInt3.RealValueToString(result));

    -- /
    result = result:div(cInt_2);
    print("luaFP result:div(cInt_2) = ",LVInt3.RealValueToString(result));
    result = result:div(num);
    print("luaFP result:div(num) = ",LVInt3.RealValueToString(result));
    result = result / cInt_2;
    print("luaFP result / cInt_2 = ",LVInt3.RealValueToString(result));
    result = result / num;
    print("luaFP result / num = ",LVInt3.RealValueToString(result));

    local b = cInt_1 == cInt_2
    print("luaFP cInt_1 == cInt_2: ",tostring(b));
    b = cInt_2 == cInt_3
    print("luaFP cInt_2 == cInt_3: ",tostring(b));
end

function LFixedPointTest.test3()
    -- 获取xyz性能测试
    -- 和运算差不多消耗，建议少用

    local times = 10000000; --一千万

    local cInt_1 = LVInt3.VInt3.new(9999.8888,98888.562654,966666.222223);

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local x = cInt_1:x()
        end
        print("luaFP VInt3:x() cost time:",os.clock()-lastTime) --cost time:    0.29600000000005
    end

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local x = cInt_1:yz()
        end
        print("luaFP VInt3:yz() cost time:",os.clock()-lastTime) --cost time:    0.39800000000002
    end

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local x = cInt_1:xyz()
        end
        print("luaFP VInt3:xyz() cost time:",os.clock()-lastTime) --cost time:    0.51999999999998
    end

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local x = cInt_1:xyzReal()
        end
        print("luaFP VInt3:xyzReal() cost time:",os.clock()-lastTime) --cost time:    0.22699999999998
    end
end

function LFixedPointTest.test4()
    -- 测试长度、距离计算
    -- 测试性能 （c层开平方相差不大）
    --[[
        cInt_1:length()                             cost time:    0.339
        cInt_1:lengthSqu()                          cost time:    0.31100000000001
        cInt_1:lengthXY()                           cost time:    0.33800000000002
        cInt_1:lengthSqu()                          cost time:    0.309
        cInt_1:distance(cInt_2)                     cost time:    0.375
        cInt_1:distanceSqu(cInt_2)                  cost time:    0.32600000000002
        cInt_1:distanceXY(cInt_2)                   cost time:    0.37299999999999
        cInt_1:distanceXYSqu(cInt_2)                cost time:    0.32599999999999
    ]]
    local cInt_1 = LVInt3.VInt3.new(3,4,5)
    local cInt_2 = LVInt3.VInt3.new(64,80,116)

    if false then
        local length = cInt_1:length();
        print("luaFP cInt_1:length() : ",length)

        local lengthSqu = cInt_1:lengthSqu();
        print("luaFP cInt_1:lengthSqu() : ",lengthSqu)

        local lengthXY = cInt_1:lengthXY();
        print("luaFP cInt_1:lengthXY() : ",lengthXY)

        local lengthXYSqu = cInt_1:lengthXYSqu();
        print("luaFP cInt_1:lengthXYSqu() : ",lengthXYSqu)

        local distance = cInt_1:distance(cInt_2);
        print("luaFP cInt_1:distance(cInt_2) : ",distance)

        local distanceSqu = cInt_1:distanceSqu(cInt_2);
        print("luaFP cInt_1:distanceSqu(cInt_2) : ",distanceSqu)

        local distanceXY = cInt_1:distanceXY(cInt_2);
        print("luaFP cInt_1:distanceXY(cInt_2) : ",distanceXY)

        local distanceXYSqu = cInt_1:distanceXYSqu(cInt_2);
        print("luaFP cInt_1:distanceXYSqu(cInt_2) : ",distanceXYSqu)

        local Distance = LVInt3.VInt3.Distance(cInt_1,cInt_2);
        print("luaFP VInt3.Distance(cInt_1,cInt_2) : ",Distance)

        local DistanceSqu = LVInt3.VInt3.DistanceSqu(cInt_1,cInt_2);
        print("luaFP VInt3.DistanceSqu(cInt_1,cInt_2) : ",DistanceSqu)

        local DistanceXY = LVInt3.VInt3.DistanceXY(cInt_1,cInt_2);
        print("luaFP VInt3.DistanceXY(cInt_1,cInt_2) : ",DistanceXY)

        local DistanceXYSqu = LVInt3.VInt3.DistanceXYSqu(cInt_1,cInt_2);
        print("luaFP VInt3.DistanceXYSqu(cInt_1,cInt_2) : ",DistanceXYSqu)

    end

    local times = 10000000; --一千万
    if true then
        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:length();
            end
            print("luaFP cInt_1:length() cost time:",os.clock()-lastTime) --cost time:    0.339
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:lengthSqu();
            end
            print("luaFP cInt_1:lengthSqu() cost time:",os.clock()-lastTime) --cost time:    0.31100000000001
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:lengthXY();
            end
            print("luaFP cInt_1:lengthXY() cost time:",os.clock()-lastTime) --cost time:    0.33800000000002
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:lengthXYSqu();
            end
            print("luaFP cInt_1:lengthSqu() cost time:",os.clock()-lastTime) --cost time:    0.309
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:distance(cInt_2);
            end
            print("luaFP cInt_1:distance(cInt_2) cost time:",os.clock()-lastTime) --cost time:    0.375
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:distanceSqu(cInt_2);
            end
            print("luaFP cInt_1:distanceSqu(cInt_2) cost time:",os.clock()-lastTime) --cost time:    0.32600000000002
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:distanceXY(cInt_2);
            end
            print("luaFP cInt_1:distanceXY(cInt_2) cost time:",os.clock()-lastTime) --cost time:    0.37299999999999
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local length = cInt_1:distanceXYSqu(cInt_2);
            end
            print("luaFP cInt_1:distanceXYSqu(cInt_2) cost time:",os.clock()-lastTime) --cost time:    0.32599999999999
        end
    end
end

function LFixedPointTest.test5()
    -- 归一化
    local cInt_1 = LVInt3.VInt3.new(3,4,5)
    local cInt_2 = LVInt3.VInt3.new(64,80,116)
    local cInt_3 = LVInt3.VInt3.Copy(cInt_1)
    local cInt_4 = LVInt3.VInt3.Copy(cInt_2)
    local cInt_5 = LVInt3.VInt3.new(1,1,1)
    local cInt_6 = LVInt3.VInt3.new(0,0,0)
    local cInt_7 = LVInt3.VInt3.new(0,0,0.02)

    if true then
        local a = cInt_1:normal();
        print("luaFP cInt_1:normal() :",LVInt3.RealValueToString(a));
    
        a = a:normal();
        print("luaFP a:normal() :",LVInt3.RealValueToString(a));
    
        a = a:normal();
        print("luaFP a:normal() :",LVInt3.RealValueToString(a));
        
        local length = a:length();
        print("luaFP a:length() :",length);
    end
    
    if true then
        local a = cInt_2:normal();
        print("luaFP cInt_2:normal() :",LVInt3.RealValueToString(a));
    
        a = a:normal();
        print("luaFP a:normal() :",LVInt3.RealValueToString(a));
    
        a = a:normal();
        print("luaFP a:normal() :",LVInt3.RealValueToString(a));
        
        local length = a:length();
        print("luaFP a:length() :",length);
    end
    
    if true then
        local a = cInt_3:normalXY();
        print("luaFP cInt_3:normalXY() :",LVInt3.RealValueToString(a));
    
        a = a:normalXY();
        print("luaFP a:normalXY() :",LVInt3.RealValueToString(a));
    
        a = a:normalXY();
        print("luaFP a:normalXY() :",LVInt3.RealValueToString(a));
        
        local length = a:lengthXY();
        print("luaFP a:lengthXY() :",length);
    end
    
    if true then
        local a = cInt_4:normalXY();
        print("luaFP cInt_4:normalXY() :",LVInt3.RealValueToString(a));
    
        a = a:normalXY();
        print("luaFP a:normalXY() :",LVInt3.RealValueToString(a));
    
        a = a:normalXY();
        print("luaFP a:normalXY() :",LVInt3.RealValueToString(a));
        
        local length = a:lengthXY();
        print("luaFP a:lengthXY() :",length);
    end
    
    if true then
        local a = cInt_5:normal();
        print("luaFP cInt_5:normal() :",LVInt3.RealValueToString(a));
    
        a = cInt_6:normal();
        print("luaFP cInt_6:normal() :",LVInt3.RealValueToString(a));
    
        a = cInt_7:normal();
        print("luaFP cInt_7:normal() :",LVInt3.RealValueToString(a));
    end
end

function LFixedPointTest.test6()
    -- 归一化性能
    --[[
        cInt_1:normal()     cost time:    0.82300000000001    
        cInt_2:normalXY()   cost time:    0.351    
        cInt_3:normal()     cost time:    0.768    
        cInt_4:normal()     cost time:    0.259    
        cInt_5:normal()     cost time:    0.357    
    ]]
    local cInt_1 = LVInt3.VInt3.new(64,80,116)
    local cInt_2 = LVInt3.VInt3.Copy(cInt_1)
    local cInt_3 = LVInt3.VInt3.new(1,1,1)
    local cInt_4 = LVInt3.VInt3.new(0,0,0)
    local cInt_5 = LVInt3.VInt3.new(0,0,0.02)

    local times = 10000000; --一千万
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_1:normal();
        end
        print("luaFP cInt_1:normal() cost time:",os.clock()-lastTime) --cost time:    0.82300000000001
    end
    
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_2:normalXY();
        end
        print("luaFP cInt_2:normalXY() cost time:",os.clock()-lastTime) --cost time:    0.351
    end

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_3:normal();
        end
        print("luaFP cInt_3:normal() cost time:",os.clock()-lastTime) --cost time:    0.768
    end
    
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_4:normal();
        end
        print("luaFP cInt_4:normal() cost time:",os.clock()-lastTime) --cost time:    0.259
    end
    
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local a = cInt_5:normal();
        end
        print("luaFP cInt_5:normal() cost time:",os.clock()-lastTime) --cost time:    0.357
    end
end

function LFixedPointTest.test7()
    -- 矩形计算测试
    local cInt_1 = LVInt3.VInt3.new(0,0,0)
    local cInt_2 = LVInt3.VInt3.new(99.155,88.555,77.666)
    local cInt_3 = LVInt3.VInt3.new(500,30.555,625.111)
    local length1 = 22.222
    local height1 = 55.555
    local length2 = 123.456
    local height2 = 98.654

    if true then
        local cRect1 = LRect.C.new(length1,height1,cInt_1);
        print("luaFP cRect1:",LRect.ToString(cRect1));

        -- local p1,p2,p3,p4 = cRect1:psRef();
        -- p1:add(p2);
        -- print("luaFP p1:add(p2):",LVInt3.ToString(p1));
        -- p3:add(p4);
        -- print("luaFP p3:add(p4):",LVInt3.ToString(p3));

        local p1,p2,p3,p4 = cRect1:ps();
        print("luaFP cRect1:ps() p1:",LVInt3.ToString(p1)," p3:",LVInt3.ToString(p1));
        print("luaFP cRect1:",LRect.ToString(cRect1));
    end
    
    if true then
        local cRect2 = LRect.C.new(length2,height2,cInt_2);
        print("luaFP cRect2:",LRect.ToString(cRect2));

        local r3 = LRect.C.Copy(cRect2);
        print("luaFP LRect.C.Copy(cRect2) :",LRect.ToString(r3));

        local r4 = LRect.C.newDefault();
        print("luaFP LRect.C.newDefault():",LRect.ToString(r4));

        r4 = r4:ctor(length1,height1,cInt_2);
        print("luaFP r4:ctor(length1,height1,cInt_2):",LRect.ToString(r4));
        
        r4 = r4:copy(r3);
        print("luaFP r4:copy(r3):",LRect.ToString(r4));
        
        r4 = r4:setCenter(cInt_3);
        print("luaFP r4:setCenter(cInt_3):",LRect.ToString(r4));

        r4 = r4:setCenter(cInt_1);
        print("luaFP r4:setCenter(cInt_1):",LRect.ToString(r4));

        r4 = r4:rotate(cInt_1,3.1415);--180度
        print("luaFP r4:rotate(cInt_1,3.1415):",LRect.ToString(r4));
        
        r4 = r4:setCenter(cInt_3);
        print("luaFP r4:setCenter(cInt_3):",LRect.ToString(r4));

        r4 = r4:rotate(cInt_3,3.1415);--180度
        print("luaFP r4:rotate(cInt_3,3.1415):",LRect.ToString(r4));

        r4 = r4:move(LVInt3.forward,1000);
        print("luaFP r4:move(LVInt3.forward,1000):",LRect.ToString(r4));

        r3 = r3:move(LVInt3.forward,1000);
        print("luaFP r3:move(LVInt3.forward,1000):",LRect.ToString(r3));
    end
end

function LFixedPointTest.test8()
    --矩形性能测试
    --[[
        创建新对象很耗；
        获取参数也挺耗时，获取引用优于获取参数；
        运算也挺耗的
        LRect.C.new(length1,height1,cInt_1)     cost time:    2.558    
        cRect1:p1()                             cost time:    0.20799999999997    
        cRect1:p1Ref()                          cost time:    0.057999999999993    
        cRect1:ps()                             cost time:    0.76900000000001    
        cRect1:psRef()                          cost time:    0.18000000000001    
        LRect.C.Copy(cRect2)                    cost time:    2.728    
        LRect.C.newDefault()                    cost time:    2.204    
        r4:ctor(length1,height1,cInt_2)         cost time:    0.053999999999974    
        4:copy(cRect2)                          cost time:    0.047000000000025    
        r4:setCenter(cInt_3)                    cost time:    0.22899999999998    
        r4:rotate(cInt_2,3.1415)                cost time:    0.38799999999998    
        r4:move(LVInt3.forward,1)               cost time:    0.416    
    ]]
    local cInt_1 = LVInt3.VInt3.new(0,0,0)
    local cInt_2 = LVInt3.VInt3.new(99.155,88.555,77.666)
    local cInt_3 = LVInt3.VInt3.new(500,30.555,625.111)
    local length1 = 22.222
    local height1 = 55.555
    local length2 = 123.456
    local height2 = 98.654

    local times = 1000000; --一百万
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cRect1 = LRect.C.new(length1,height1,cInt_1);
        end
        print("luaFP LRect.C.new(length1,height1,cInt_1) cost time:",os.clock()-lastTime) --cost time:    2.558
    end
    if true then
        local cRect1 = LRect.C.new(length1,height1,cInt_1);
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local p1 = cRect1:p1();
        end
        print("luaFP cRect1:p1() cost time:",os.clock()-lastTime) --cost time:    0.20799999999997

        -- lastTime = os.clock();
        -- for i = 1, times, 1 do
        --     local p1 = cRect1:p1Ref();
        -- end
        -- print("luaFP cRect1:p1Ref() cost time:",os.clock()-lastTime) --cost time:    0.057999999999993

        lastTime = os.clock();
        for i = 1, times, 1 do
            local p1,p2,p3,p4 = cRect1:ps();
        end
        print("luaFP cRect1:ps() cost time:",os.clock()-lastTime) --cost time:    0.76900000000001

        -- lastTime = os.clock();
        -- for i = 1, times, 1 do
        --     local p1,p2,p3,p4 = cRect1:psRef();
        -- end
        -- print("luaFP cRect1:psRef() cost time:",os.clock()-lastTime) --cost time:    0.18000000000001
    end
    
    local cRect2 = LRect.C.new(length2,height2,cInt_2);
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local r3 = LRect.C.Copy(cRect2);
        end
        print("luaFP LRect.C.Copy(cRect2) cost time:",os.clock()-lastTime) --cost time:    2.728

        lastTime = os.clock();
        for i = 1, times, 1 do
            local r3 = LRect.C.newDefault();
        end
        print("luaFP LRect.C.newDefault() cost time:",os.clock()-lastTime) --cost time:    2.204
    end
    
    if true then
        local r4 = LRect.C.newDefault();
        local lastTime = os.clock();
        for i = 1, times, 1 do
            r4 = r4:ctor(length1,height1,cInt_2);
        end
        print("luaFP r4:ctor(length1,height1,cInt_2) cost time:",os.clock()-lastTime) --cost time:    0.053999999999974

        lastTime = os.clock();
        for i = 1, times, 1 do
            r4 = r4:copy(cRect2);
        end
        print("luaFP r4:copy(cRect2) cost time:",os.clock()-lastTime) --cost time:    0.047000000000025
    end
    
    if true then
        local r4 = LRect.C.new(length2,height2,cInt_2);
        local lastTime = os.clock();
        for i = 1, times, 1 do
            r4 = r4:setCenter(cInt_3);
        end
        print("luaFP r4:setCenter(cInt_3) cost time:",os.clock()-lastTime) --cost time:    0.22899999999998

        lastTime = os.clock();
        for i = 1, times, 1 do
            r4 = r4:rotate(cInt_2,3.1415)
        end
        print("luaFP r4:rotate(cInt_2,3.1415) cost time:",os.clock()-lastTime) --cost time:    0.38799999999998

        lastTime = os.clock();
        for i = 1, times, 1 do
            r4 = r4:move(LVInt3.forward,1)
        end
        print("luaFP r4:move(LVInt3.forward,1) cost time:",os.clock()-lastTime) --cost time:    0.416
    end
end

function LFixedPointTest.test9()
    -- 圆形计算测试
    local cInt_1 = LVInt3.VInt3.new(0,0,0)
    local cInt_2 = LVInt3.VInt3.new(100,0,0)
    local cInt_3 = LVInt3.VInt3.new(0,95.33,0)
    local radius1 = 50
    local radius2 = 50
    local radius3 = 999.5699

    if true then
        local cCircle1 = LCircle.C.new(radius1,cInt_1);
        print("luaFP LCircle.C.new(radius1,cInt_1):",LCircle.ToString(cCircle1));

        local cCircle2 = LCircle.C.newDefault();
        print("luaFP LCircle.C.newDefault():",LCircle.ToString(cCircle2));

        local cCircle3 = LCircle.C.Copy(cCircle1);
        print("luaFP LCircle.C.Copy(cCircle1):",LCircle.ToString(cCircle3));
    end
    
    if true then
        local cCircle1 = LCircle.C.new(radius1,cInt_1);
        print("luaFP cCircle1 = LCircle.C.new(radius1,cInt_1):",LCircle.ToString(cCircle1));

        local cCircle2 = LCircle.C.new(radius2,cInt_2);
        print("luaFP cCircle2 = LCircle.C.new(radius2,cInt_2):",LCircle.ToString(cCircle2));
        
        local cCircle3 = LCircle.C.new(radius3,cInt_3);
        print("luaFP cCircle3 = LCircle.C.new(radius3,cInt_3):",LCircle.ToString(cCircle3));

        local cCircle4 = LCircle.C.Copy(cCircle1);
        print("luaFP cCircle4 = LCircle.C.Copy(cCircle1):",LCircle.ToString(cCircle3));

        local b = LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2)
        print("luaFP LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2):",tostring(b));

        cCircle2:setRadius(49.8888);
        print("luaFP cCircle2:setRadius(49.8888):",LCircle.ToString(cCircle2));

        b = LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2)
        print("luaFP LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2):",tostring(b));

        -- cCircle2:centerRef():ctor(-100,0,0);
        -- print("luaFP cCircle2:centerRef():ctor(-100,0,0):",LCircle.ToString(cCircle2));

        b = LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2);
        print("luaFP LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2):",tostring(b));

        cCircle4:copy(cCircle3);
        print("luaFP cCircle4:copy(cCircle3):",LCircle.ToString(cCircle4));

        b = cCircle4 == cCircle3
        print("luaFP cCircle4 == cCircle3:",tostring(b));

        b = cCircle4 == cCircle1
        print("luaFP cCircle4 == cCircle1:",tostring(b));

        cCircle4:ctor(radius1,cInt_3);
        print("luaFP cCircle4:ctor(radius1,cInt_3):",LCircle.ToString(cCircle4));
    end
end

function LFixedPointTest.test10()
    -- 圆形性能测试
    --[[
        LCircle.C.new(radius1,cInt_1)                   cost time:    0.60699999999997    
        LCircle.C.newDefault()                          cost time:    0.60899999999992    
        LCircle.C.Copy(cCircle1)                        cost time:    0.73199999999997    
        cCircle1:isIntersectCircle(cCircle2)            cost time:    0.050000000000182     b:    true    
        cCircle1:isIntersectCircle(cCircle2)            cost time:    0.052000000000135     b:    false    
        cCircle2:setRadius(49.8888)                     cost time:    0.032999999999902    
        cCircle2:radius()                               cost time:    0.028999999999996    
        cCircle2:center()                               cost time:    0.20800000000008    
        cCircle2:centerRef()                            cost time:    0.060999999999694    
        cCircle4:copy(cCircle3)                         cost time:    0.021999999999935    
        cCircle4 == cCircle3                            cost time:    0.023000000000138     b:    true    
        cCircle4 == cCircle1                            cost time:    0.021999999999935     b:    false     
        cCircle4:ctor(radius1,cInt_3)                   cost time:    0.034999999999854  
    ]]
    local cInt_1 = LVInt3.VInt3.new(0,0,0)
    local cInt_2 = LVInt3.VInt3.new(100,0,0)
    local cInt_3 = LVInt3.VInt3.new(0,95.33,0)
    local radius1 = 50
    local radius2 = 50
    local radius3 = 999.5699

    local times = 1000000; --一百万
    
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cCircle1 = LCircle.C.new(radius1,cInt_1);
        end
        print("luaFP LCircle.C.new(radius1,cInt_1) cost time:",os.clock()-lastTime) --cost time:    0.60699999999997
    end
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cCircle1 = LCircle.C.newDefault();
        end
        print("luaFP LCircle.C.newDefault() cost time:",os.clock()-lastTime) --cost time:    0.60899999999992
    end
    
    if true then
        local cCircle1 = LCircle.C.new(radius1,cInt_1);
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cCircle3 = LCircle.C.Copy(cCircle1);
        end
        print("luaFP LCircle.C.Copy(cCircle1) cost time:",os.clock()-lastTime) --cost time:    0.73199999999997
    end
    
    if true then
        local cCircle1 = LCircle.C.new(radius1,cInt_1);
        local cCircle2 = LCircle.C.new(radius2,cInt_2);
        local cCircle3 = LCircle.C.new(radius3,cInt_3);
        local cCircle4 = LCircle.C.Copy(cCircle1);

        if true then
            local b = nil;
            local lastTime = os.clock();
            for i = 1, times, 1 do
                b = LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2)
            end
            print("luaFP LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2) cost time:",os.clock()-lastTime," b:",tostring(b)) --cost time:    0.050000000000182
        end
        
        if true then
            local b = nil;
            cCircle2:setRadius(49.8888);
            local lastTime = os.clock();
            for i = 1, times, 1 do
                b = LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2)
            end
            print("luaFP LPhysicUtil.C.IsCircleIntersectCircleXY(cCircle1,cCircle2) cost time:",os.clock()-lastTime," b:",tostring(b)) --cost time:    0.052000000000135
        end
        
        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                cCircle2:setRadius(49.8888);
            end
            print("luaFP cCircle2:setRadius(49.8888) cost time:",os.clock()-lastTime) --cost time:    0.032999999999902
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local center = cCircle2:radius();
            end
            print("luaFP cCircle2:radius() cost time:",os.clock()-lastTime) --cost time:    0.028999999999996
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                local center = cCircle2:center();
            end
            print("luaFP cCircle2:center() cost time:",os.clock()-lastTime) --cost time:    0.20800000000008
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                cCircle4:copy(cCircle3);
            end
            print("luaFP cCircle4:copy(cCircle3) cost time:",os.clock()-lastTime) --cost time:    0.021999999999935
        end

        if true then
            local b = nil;
            local lastTime = os.clock();
            for i = 1, times, 1 do
                b = cCircle4 == cCircle3
            end
            print("luaFP cCircle4 == cCircle3 cost time:",os.clock()-lastTime," b:",tostring(b)) --cost time:    0.023000000000138
        end

        if true then
            local b = nil;
            local lastTime = os.clock();
            for i = 1, times, 1 do
                b = cCircle4 == cCircle1
            end
            print("luaFP cCircle4 == cCircle1 cost time:",os.clock()-lastTime," b:",tostring(b)) --cost time:    0.021999999999935
        end

        if true then
            local lastTime = os.clock();
            for i = 1, times, 1 do
                cCircle4:ctor(radius1,cInt_3);
            end
            print("luaFP cCircle4:ctor(radius1,cInt_3) cost time:",os.clock()-lastTime) --cost time:    0.034999999999854
        end
        
    end
end

function LFixedPointTest.test11()
    -- 线段计算测试
    local cInt_1 = LVInt3.VInt3.new(0,0,0)
    local cInt_2 = LVInt3.VInt3.new(100,0,0)
    local cInt_3 = LVInt3.VInt3.new(0,95.33,0)
    local cInt_4 = LVInt3.VInt3.new(-51.6523,56.222,0)

    if true then
        local cLine1 = LLine.C.new(cInt_1,cInt_2);
        print("luaFP LLine.C.new(cInt_1,cInt_2):",LLine.ToString(cLine1));

        local cLine2 = LLine.C.newDefault();
        print("luaFP LLine.C.newDefault():",LLine.ToString(cLine2));

        local cLine3 = LLine.C.Copy(cLine1);
        print("luaFP LLine.C.Copy(cLine1):",LLine.ToString(cLine3));
    end
    
    if true then
        local cLine1 = LLine.C.new(cInt_1,cInt_2);
        print("luaFP LLine.C.new(cInt_1,cInt_2):",LLine.ToString(cLine1));

        local cLine2 = LLine.C.new(cInt_3,cInt_4);
        print("luaFP LLine.C.new(cInt_3,cInt_4):",LLine.ToString(cLine2));
        
        local cLine3 = LLine.C.newDefault();
        print("luaFP LLine.C.newDefault():",LLine.ToString(cLine3));

        cLine3:copy(cLine2);
        print("luaFP cLine3:copy(cLine2):",LLine.ToString(cLine3));
        
        cLine3:ctor(cInt_2,cInt_4);
        print("luaFP cLine3:ctor(cInt_2,cInt_4):",LLine.ToString(cLine3));

        -- local p1Ref = cLine3:p1Ref();
        -- print("luaFP cLine3:p1Ref():",LVInt3.ToString(p1Ref));

        -- p1Ref:ctor(55.5555,66.6666,77.777);
        -- print("luaFP p1Ref:ctor(55.5555,66.6666,77.777):",LLine.ToString(cLine3));
    
        local p1 = cLine3:p1();
        print("luaFP cLine3:p1():",LVInt3.ToString(p1));
        
        -- local p2Ref = cLine3:p2Ref();
        -- print("luaFP cLine3:p2Ref():",LVInt3.ToString(p2Ref));

        p2Ref:ctor(1155.5555,1166.6666,1177.777);
        print("luaFP p2Ref:ctor(1155.5555,1166.6666,1177.777):",LLine.ToString(cLine3));

        local p2 = cLine3:p2();
        print("luaFP cLine3:p2():",LVInt3.ToString(p2));

        -- p1Ref,p2Ref = cLine3:psRef();
        -- p1Ref:ctor(-55.5555,-66.6666,-77.777);
        -- p2Ref:ctor(-1155.5555,-1166.6666,-1177.777);
        -- print("luaFP p1、p2Ref:ctor():",LLine.ToString(cLine3));

        p1,p2 = cLine3:ps();
        print("luaFP cLine3:ps(): p1:",LVInt3.ToString(p1),"p2:",LVInt3.ToString(p2));

        local b = cLine1 == cLine3
        print("luaFP cLine1 == cLine3:",tostring(b));

        cLine3:copy(cLine2);
        b = cLine2 == cLine3
        print("luaFP cLine2 == cLine3:",tostring(b));
    end
end

function LFixedPointTest.test12()
    -- 线段计算测试
    --[[
        LLine.C.new(cInt_1,cInt_2)  cost time:    1.009    
        LLine.C.newDefault()        cost time:    1.057    
        LLine.C.Copy(cLine1)        cost time:    1.1869999999999    
        cLine3:copy(cLine2)         cost time:    0.024000000000115    
        cLine3:ctor(cInt_2,cInt_4)  cost time:    0.025000000000091    
        cLine3:psRef()              cost time:    0.12199999999984    
        cLine3:ps()                 cost time:    0.39499999999998     
    ]]
    local cInt_1 = LVInt3.VInt3.new(0,0,0)
    local cInt_2 = LVInt3.VInt3.new(100,0,0)
    local cInt_3 = LVInt3.VInt3.new(0,95.33,0)
    local cInt_4 = LVInt3.VInt3.new(-51.6523,56.222,0)

    local times = 1000000; --一百万
    
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cLine1 = LLine.C.new(cInt_1,cInt_2);
        end
        print("luaFP LLine.C.new(cInt_1,cInt_2) cost time:",os.clock()-lastTime) --cost time:    1.009
    end

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cLine3 = LLine.C.newDefault();
        end
        print("luaFP LLine.C.newDefault() cost time:",os.clock()-lastTime) --cost time:    1.057
    end
    
    if true then
        local cLine1 = LLine.C.new(cInt_1,cInt_2);
        local lastTime = os.clock();
        for i = 1, times, 1 do
            local cLine3 = LLine.C.Copy(cLine1);
        end
        print("luaFP LLine.C.Copy(cLine1) cost time:",os.clock()-lastTime) --cost time:    1.1869999999999
    end

    local cLine1 = LLine.C.new(cInt_1,cInt_2);
    local cLine2 = LLine.C.new(cInt_3,cInt_4);
    local cLine3 = LLine.C.newDefault();

    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            cLine3:copy(cLine2);
        end
        print("luaFP cLine3:copy(cLine2) cost time:",os.clock()-lastTime) --cost time:    0.024000000000115
    end
    if true then
        local lastTime = os.clock();
        for i = 1, times, 1 do
            cLine3:ctor(cInt_2,cInt_4);
        end
        print("luaFP cLine3:ctor(cInt_2,cInt_4) cost time:",os.clock()-lastTime) --cost time:    0.025000000000091
    end
    -- if true then
    --     local p1Ref,p2Ref;
    --     local lastTime = os.clock();
    --     for i = 1, times, 1 do
    --         p1Ref,p2Ref = cLine3:psRef();
    --     end
    --     print("luaFP cLine3:psRef() cost time:",os.clock()-lastTime) --cost time:    0.12199999999984
    -- end
    if true then
        local p1,p2;
        local lastTime = os.clock();
        for i = 1, times, 1 do
            p1,p2 = cLine3:ps();
        end
        print("luaFP cLine3:ps() cost time:",os.clock()-lastTime) --cost time:    0.39499999999998
    end
end

return LFixedPointTest;

--Create an class.
function class(classname, super)
    local superType = type(super)
    local cls
    
    CCLuaLog("superType="..tostring(superType))

    if superType ~= "function" and superType ~= "table" then
        superType = nil
        super = nil
    end

    if superType == "function" or (super and super.__ctype == 1) then
        -- inherited from native C++ Object
        cls = {}

        if superType == "table" then
            -- copy fields from super
            for k,v in pairs(super) do cls[k] = v end
            cls.__create = super.__create
            cls.super    = super
        else
            cls.__create = super
        end

        cls.ctor    = function() end
        cls.__cname = classname
        cls.__ctype = 1

        function cls.new(...)
            local instance = cls.__create(...)
            -- copy fields from class to native object
            for k,v in pairs(cls) do instance[k] = v end
            instance.class = cls
            instance:ctor(...)
            return instance
        end

    else
        -- inherited from Lua Object
        if super then
            cls = clone(super)
            cls.super = super
        else
            cls = {ctor = function() end}
        end

        cls.__cname = classname
        cls.__ctype = 2 -- lua
        cls.__index = cls

        function cls.new(...)
            local instance = setmetatable({}, cls)
            instance.class = cls
            instance:ctor(...)
            return instance
        end
    end

    return cls
end

-- 重复执行
function schedule(node, callback, delay, withObject)
    local delay = CCDelayTime:create(delay)
    local callfunc = 0
    if (withObject==nil) then
    	withObject = false
    end
    if (withObject==true) then
    	callfunc = CCCallFuncN:create(callback)
    else
    	callfunc = CCCallFunc:create(callback)
    end
    local sequence = CCSequence:createWithTwoActions(delay, callfunc)
    sequence = tolua.cast(sequence,"CCActionInterval")
    local action = CCRepeatForever:create(sequence)
    node:runAction(action)
    return action
end

-- 执行一次
function performWithDelay(node, callback, delay, withObject)
    local delay = CCDelayTime:create(delay)
    if (withObject==nil) then
    	withObject = false
    end
    if (withObject==true) then
    	callfunc = CCCallFuncN:create(callback)
    else
    	callfunc = CCCallFunc:create(callback)
    end
    local sequence = CCSequence:createWithTwoActions(delay, callfunc)
    node:runAction(sequence)
    return sequence
end

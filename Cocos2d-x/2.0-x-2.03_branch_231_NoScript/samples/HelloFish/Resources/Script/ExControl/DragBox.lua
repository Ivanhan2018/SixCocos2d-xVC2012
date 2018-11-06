--[[
------------------------------------
下拉框控件
------------------------------------
Cool.Cat@2013/4/16 10:38:17
------------------------------------
]]

function CreateObj(var)
		CCLuaLog("var="..var)
    return CCSprite:create(var)
end

DragBox = class("DragBox", CreateObj)

DragBox.__index = DragBox

CCLuaLog("DragBox...................."..tostring(DragBox.__index))

function DragBox:createWithFile(fileName)
    if(fileName == nil) then
        CCLuaLog("DragBox.createWithFile.fileName.Nil!")
        return nil
    end

    local dragBox = DragBox.new(fileName)
    dragBox:autorelease()
    dragBox:retain()
    return dragBox
end

local function DoPrintWithOutObject()
	CCLuaLog("DoPrintWithOutObject")
end

local function DoPrintWithObject(node)
	CCLuaLog("DoPrintWithObject.node="..tostring(node))
end

function DragBox:DoAction()
  local delay = CCDelayTime:create(1.0)
  -- 不带self对象
  --local callfunc = CCCallFunc:create(DoPrintWithOutObject)
  -- 带self对象
  local callfunc = CCCallFuncN:create(DoPrintWithObject)
  local sequence = CCSequence:createWithTwoActions(delay, callfunc)
  sequence = tolua.cast(sequence,"CCActionInterval")
  local action = CCRepeatForever:create(sequence)
  self:runAction(action)
end
--[[
------------------------------------
弹出窗口
------------------------------------
Cool.Cat@2013/5/8 17:51:14
------------------------------------
]]

function CreateObj(w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
		return SIX_UILayer:create(ccc4(r,g,b,a),w,h,bTouchThroughForbidden,nPriority,bRedrawBorder)
end

PopWnd = class("PopWnd",CreateObj)

-- control
PopWnd.__index = PopWnd
PopWnd.__Progress= nil

function PopWndUpdate(pPopWnd)
	local UT = SIX_Utility:new()
	local value = UT:RNDNUM(0,100)	
	pPopWnd:updateProgress(value)	
end

function PopWnd:updateProgress(value)
	if (value>=100.0) then
		value = 100.0
	elseif (value<=0.0) then
		value = 0.0
	end

	-- 设置进度条百分比先~
	self.__Progress:setPercentage(value)
	
	-- 光标
	local curSpr = self.__Progress:getChildByTag(2)
	curSpr = tolua.cast(curSpr,"CCSprite")

	local m_tBarChangeRate = self.__Progress:getBarChangeRate()
	local m_tMidpoint = self.__Progress:getMidpoint()
	local offset_x = convertPercentageToMaxPostionX(value,m_tBarChangeRate,m_tMidpoint) * 100
	local offset_x_final = offset_x * self.__Progress:getContentSize().width / 100

	-- 在非规则区域要缩放
	if (offset_x_final<22.0) then
		curSpr:setScale(offset_x_final * (1/22))
	elseif (offset_x_final>596.0) then
		curSpr:setScale((22-(offset_x_final-596)) * (1/22))
	-- 在规则区域还原
	else
		curSpr:setScale(1.0)
	end
	curSpr:setPositionX(offset_x_final+self.__Progress:getPositionX())
end

-- true=拦截触碰
-- false=继续传递
function onPopWndTouch(e,x,y)
	CCLuaLog("onPopWndTouch.e.["..e.."].x["..x.."].y["..y.."]")
	return true
end

--[[
1、targeted优先级高于standard
2、Priority越小优先级越高
]]
function PopWnd:create(x,y,w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
	local pPopWnd = PopWnd.new(w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
	pPopWnd:setObjName("PopWnd")
	pPopWnd:setRectDirty(true)
	pPopWnd:setRedrawBorder(bRedrawBorder)
	pPopWnd:setBorderColor(ccc4(255,255,255,255))
	pPopWnd:setContentSize(CCSize(w,h))
	pPopWnd:setPosition(ccp(x,y))
	pPopWnd:InitProgress()
	--schedule(pPopWnd,PopWndUpdate,0.01,true)
	-- 触碰
	pPopWnd:setTouchEnabled(true)
	-- 单点触碰
	pPopWnd:registerScriptTouchHandler(onPopWndTouch,false)
	return pPopWnd
end

function PopWnd:InitProgress()
	if (self==nil) then
		return
	end
	
	-- 背景
	local bgSpr = CCSprite:create("Scene/Loading/progress_bg.png")
	bgSpr:getTexture():setAntiAliasTexParameters()
	bgSpr:setAnchorPoint(ccp(0,0))
	
	-- 边框
	local borderSpr = CCSprite:create("Scene/Loading/progress_border.png")
	borderSpr:getTexture():setAntiAliasTexParameters()
	borderSpr:setAnchorPoint(ccp(0,0))
	
	-- 比例
	local rateSpr = CCSprite:create("Scene/Loading/progress_rate.png")
	rateSpr:getTexture():setAntiAliasTexParameters()
	borderSpr:setAnchorPoint(ccp(0,0))
	
	local curSpr = CCSprite:create("Scene/Loading/halo.png")
	curSpr:getTexture():setAntiAliasTexParameters()
	curSpr:setAnchorPoint(ccp(0.5,0))
	curSpr:setTag(2)	
	
	self.__Progress = CCProgressTimer:create(rateSpr)
	self.__Progress:setAnchorPoint(ccp(0,0))
	self.__Progress:setPercentage(0.0)
	self.__Progress:setMidpoint(ccp(0,0))
	self.__Progress:setBarChangeRate(ccp(1,0))
	self.__Progress:setType(1)
	self.__Progress:setTag(1)
	
	local x = (self:getContentSize().width-self.__Progress:getContentSize().width)/2
	local y = (self:getContentSize().height-self.__Progress:getContentSize().height)/2
	self.__Progress:setPosition(ccp(x,y))
	bgSpr:setPosition(ccp(x,y))
	borderSpr:setPosition(ccp(x,y))

	self.__Progress:addChild(curSpr)

	self:addChild(bgSpr)
	self:addChild(borderSpr)	
	self:addChild(self.__Progress)
end

--function PopWnd:Show(IsShow,delay,pfnCallback)
function PopWnd:Show(IsShow)
	if (self==nil) then
		return
	end
	
--	local canDoAct = false
--	
--	-- 检测上个动作完成状态
--	-- Cool.Cat
--	local lastAct = self:getActionByTag(1)
--	if (lastAct~=nil) then
--		if (lastAct:isDone()) then
--			canDoAct = true
--		end
--	else
--		canDoAct = true
--	end
--	
--	-- 如果上个动作尚未完成，直接忽略本次操作
--	if (canDoAct==false) then
--		return
--	end
	
	local ScaleToAction,ScaleToActionReverse
	if (IsShow==true) then
		-- 吞掉触碰事件
		self:setSwallowsTouches(true)
		-- 继续当前Layer的touch处理
		self:setTouchEventPause(false)
		self:setScale(0.0)
		ScaleToAction = CCScaleTo:create(0.2,1.05)
		ScaleToActionReverse = CCScaleTo:create(0.1,1.0)
	elseif (IsShow==false) then
		-- 暂停当前Layer的touch处理
		self:setTouchEventPause(true)
		-- 继续传递触碰事件
		self:setSwallowsTouches(false)
		self:setScale(1.0)
		ScaleToAction = CCScaleTo:create(0.1,1.05)
		ScaleToActionReverse = CCScaleTo:create(0.2,0.0)
	end
	local act = CCSequence:createWithTwoActions(ScaleToAction, ScaleToActionReverse)
	act:setTag(1)
	self:runAction(act)
--	if (pfnCallback~=nil) then
--		performWithDelay(self,pfnCallback,delay,true)
--	end
end
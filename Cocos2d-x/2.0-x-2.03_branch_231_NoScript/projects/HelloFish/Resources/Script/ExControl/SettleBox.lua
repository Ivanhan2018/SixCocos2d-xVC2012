--[[
------------------------------------
结算窗口
------------------------------------
Cool.Cat@2013/5/23 16:39:18
------------------------------------
]]

function CreateSettleBox(w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
		return SIX_UILayer:create(ccc4(r,g,b,a),w,h,bTouchThroughForbidden,nPriority,bRedrawBorder)
end

SettleBox = class("SettleBox",CreateSettleBox)

-- control
SettleBox.__index = SettleBox
SettleBox.__ListView = nil
SettleBox.__Sumbit= nil
SettleBox.__Cancel= nil

function SettleBoxUpdate(pSettleBox)
end

-- true=拦截触碰
-- false=继续传递
function onSettleBoxTouch(e,x,y)
	CCLuaLog("onSettleBoxTouch.e.["..e.."].x["..x.."].y["..y.."]")
	return true
end

--[[
1、targeted优先级高于standard
2、Priority越小优先级越高
]]
function SettleBox:create(x,y,w,h,r,g,b,a,bTouchThroughForbidden,nPriority)
	local pSettleBox = SettleBox.new(w,h,r,g,b,a,bTouchThroughForbidden,nPriority)
	local pBackgroundSpr = CCSprite:create("scene/game/settle_bg.png")
	pBackgroundSpr:setAnchorPoint(ccp(0,0))
	pSettleBox:addChild(pBackgroundSpr)
	pSettleBox:setObjName("SettleBox")
	pSettleBox:setContentSize(CCSize(w,h))
	pSettleBox:setPosition(ccp(x,y))
	pSettleBox:InitListView()
	pSettleBox:InitButton()
	--schedule(pSettleBox,SettleBoxUpdate,0.01,true)
	-- 触碰
	pSettleBox:setTouchEnabled(true)
	-- 单点触碰
	pSettleBox:registerScriptTouchHandler(onSettleBoxTouch,false)
	return pSettleBox
end

function SettleBox:InitListView()
	if (self==nil) then
		return
	end

	local pContainer = SIX_UILayer:create(ccc4(0,0,0,0))
	pContainer:setContentSize(CCSize(self:getContentSize().width-20,self:getContentSize().height-20))
	pContainer:setPosition(ccp(10,10))
	
	local pScrollBar = SIX_ScrollBar:create(
				"extensions/scrollbar.png",CCRect(0,51,17,17),CCRect(17,0,self:getContentSize().height-20,17),
				"extensions/scrollbar.png",CCRect(0,0,17,17),
				"extensions/scrollbar.png",CCRect(0,17,17,17),
				"extensions/scrollbar.png",CCRect(0,34,17,17),
				false
			)
	pScrollBar:setAnchorPoint(ccp(0,0))
	pScrollBar:setMinimumValue(0)
	pScrollBar:setMaximumValue(100)
	pScrollBar:setValue(0)
	pScrollBar:setVisible(false)
	
	self.__ListView = SIX_ListView:create(ccc4(0,0,0,0),
																			ccp(30,70),
																		 	CCSize(self:getContentSize().width-60,self:getContentSize().height-100),
																		 	CCSize(self:getContentSize().width-20,18),
																		 	kCCScrollViewDirectionVertical,
																		 	pContainer,
																		 	pScrollBar
																			)
	self.__ListView:setObjName("SettleBoxList")
	
	-- 设置响应touch事件(create的时候已经设置好了，这里只是演示而已)
	self.__ListView:setTouchEnabled(true)
	
	-- 设置裁剪超出区域(create的时候默认设置为true，这里只是演示而已~)
	self.__ListView:getContainer():setClippingToBounds(true)
	-- 设置横竖方向(create的时候已经设置好了，这里只是演示而已~)
	self.__ListView:getContainer():setDirection(kCCScrollViewDirectionVertical)
	-- 设置自上而下滚动(create的时候已经设置好了，这里只是演示而已~)
	self.__ListView:getContainer():setVerticalFillOrder(kCCTableViewFillTopDown)
	-- 设置滑动效果
	self.__ListView:getContainer():setBounceable(false)
	self:addChild(self.__ListView)
end

function SettleBox:InitButton()
	if (self==nil) then
		return
	end
  
	self.__Submit = CCControlButton:create(CCScale9Sprite:create("scene/game/btnSettleNor.png"))
	self.__Submit:setPreferredSize(CCSize(82,28))
	self.__Submit:setZoomFactor(1.05)
	self.__Submit:setAnchorPoint(ccp(0.5,0.5))
	self.__Submit:setPosition(ccp(340+self.__Submit:getContentSize().width/2,12+self.__Submit:getContentSize().height/2))
	self.__Submit:setTag(-1)
	self.__Submit:setObjName("settleGoOn")
	self:addChild(self.__Submit)
	
	self.__Cancel = CCControlButton:create(CCScale9Sprite:create("scene/game/btnSettleNor.png"))
	self.__Cancel:setPreferredSize(CCSize(82,28))
	self.__Cancel:setZoomFactor(1.05)
	self.__Cancel:setAnchorPoint(ccp(0.5,0.5))
	self.__Cancel:setPosition(ccp(490+self.__Cancel:getContentSize().width/2,12+self.__Cancel:getContentSize().height/2))
	self.__Cancel:setObjName("settleExit")
	self.__Submit:setTag(-2)
	self:addChild(self.__Cancel)
	
	if (pScene~=nil) then
		pScene:GetUIMgr():addControlEvents(32,self.__Submit,pSettleBox)
		pScene:GetUIMgr():addControlEvents(32,self.__Cancel,pSettleBox)
	end
end

function SettleBox:clear()
	if (self==nil) then
		return
	end
	if (self.__ListView==nil) then
		return
	end
	
	self.__ListView:RemoveCellAll()
end

function SettleBox:setContent(text)
	if (self==nil) then
		return
	end
	if (self.__ListView==nil) then
		return
	end
	
	local pCell = SIX_ListViewCell:new()
	self.__ListView:AppendCell(pCell)	
	
	local pContent = CCLabelTTF:create()
	pContent:setString(text)
	pContent:setColor(ccc3(255,255,255))
	pContent:setOpacity(255)
	pContent:setAnchorPoint(ccp(0,0))
	pContent:setPosition(ccp(0,0))
	pContent:setContentSize(CCSize(self:getContentSize().width-20,self:getContentSize().height-20))
	pContent:getTexture():setAntiAliasTexParameters()
	pCell:addChild(pContent)
end

function SettleBox:Show(IsShow,delay,pfnCallback)
	if (self==nil) then
		return
	end
	
	local canDoAct = false
	
	-- 检测上个动作完成状态
	-- Cool.Cat
	local lastAct = self:getActionByTag(1)
	if (lastAct~=nil) then
		if (lastAct:isDone()) then
			canDoAct = true
		end
	else
		canDoAct = true
	end
	
	-- 如果上个动作尚未完成，直接忽略本次操作
	if (canDoAct==false) then
		return
	end
	
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
end
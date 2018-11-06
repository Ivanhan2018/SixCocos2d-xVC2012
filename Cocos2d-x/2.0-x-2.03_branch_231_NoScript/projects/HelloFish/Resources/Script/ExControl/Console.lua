--[[
------------------------------------
控制台
------------------------------------
Cool.Cat@2013/4/20 12:29:04
------------------------------------
]]

function CreateObj(w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
		return SIX_UILayer:create(ccc4(r,g,b,a),w,h,bTouchThroughForbidden,nPriority,bRedrawBorder)
end

Console = class("Console",CreateObj)

-- control
Console.__index = Console
Console.__TitleTTF = nil
Console.__RuntimeTTF = nil
Console.__EditBox = nil
Console.__Submit = nil
Console.__ListView = nil
-- attribute
Console.__EditBoxH = 30
Console.__PaddingLR = 5
Console.__PaddingT = 5
Console.__HeaderH = 15
Console.__SubmitW = 60

function ConsoleUpdate(pConsole)
	pConsole:setRuntime(GetFormatRuntime())
end

-- true=拦截触碰
-- false=继续传递
function onConsoleTouch(e,x,y)
	CCLuaLog("onConsoleTouch.e.["..e.."].x["..x.."].y["..y.."]")
	return false
end

-- 响应回车
function OnInputDone(pEditBox,text)
	pEditBox = tolua.cast(pEditBox,"SIX_EditBox")
	pEditBox:getTTF():setString("")
	local pConsole = pEditBox:getParent()
	pConsole:ProcessCommand(text)
end

--[[
1、targeted优先级高于standard
2、Priority越小优先级越高
]]
function Console:create(x,y,w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
	local pConsole = Console.new(w,h,r,g,b,a,bTouchThroughForbidden,nPriority,bRedrawBorder)
	pConsole:setObjName("Console")
	pConsole:setRectDirty(false)
	pConsole:setRedrawBorder(bRedrawBorder)
	pConsole:setBorderColor(ccc4(255,255,255,255))
	pConsole:setContentSize(CCSize(w,h))
	pConsole:setPosition(ccp(x,y))
	pConsole:InitTitle("Console")
	pConsole:InitRuntime("已经运行")
	--pConsole:InitContent(VersionFull())
	pConsole:InitListView()
	pConsole:InitEditBox()
	schedule(pConsole,ConsoleUpdate,0.1,true)
	-- 触碰
	pConsole:setTouchEnabled(true)
	-- 单点触碰
	pConsole:registerScriptTouchHandler(onConsoleTouch,false)
	return pConsole
end

function Console:DoEnter()
	if (self:isVisible()==false) then
		return
	end
	if (self.__EditBox~=nil) then
		self.__EditBox:attachWithIME()
	end
end

function Console:InitTitle(text)
	if (self==nil) then
		return
	end
	self.__TitleTTF = CCLabelTTF:create()
	self.__TitleTTF:setString(text)
	self.__TitleTTF:setColor(ccc3(255,255,255))
	self.__TitleTTF:setOpacity(255)
	self.__TitleTTF:setAnchorPoint(ccp(0,0))
	self.__TitleTTF:setPosition(ccp(self.__PaddingLR,self:getContentSize().height-self.__HeaderH-self.__PaddingT))
	self.__TitleTTF:getTexture():setAntiAliasTexParameters()
	self:addChild(self.__TitleTTF)
end

function Console:InitRuntime(text)
	if (self==nil) then
		return
	end
	self.__RuntimeTTF = CCLabelTTF:create()
	self.__RuntimeTTF:setString(text)
	self.__RuntimeTTF:setColor(ccc3(0,255,0))
	self.__RuntimeTTF:setOpacity(255)
	self.__RuntimeTTF:setAnchorPoint(ccp(0,0))
	self.__RuntimeTTF:setPosition(ccp(self:getContentSize().width-155,self:getContentSize().height-self.__HeaderH-self.__PaddingT))
	self.__RuntimeTTF:getTexture():setAntiAliasTexParameters()
	self.__RuntimeTTF:setContentSize(CCSize(150,self.__RuntimeTTF:getContentSize().height))
	-- 设置无效。。。
	self.__RuntimeTTF:setHorizontalAlignment(kCCTextAlignmentRight)	
	self:addChild(self.__RuntimeTTF)	
end

function Console:InitListView()
	if (self==nil) then
		return
	end

	local pContainer = SIX_UILayer:create(ccc4(0,0,0,0))
	pContainer:setContentSize(CCSize(self:getContentSize().width-self.__PaddingLR*2,self:getContentSize().height-self.__HeaderH-self.__EditBoxH-self.__PaddingT*4))
	pContainer:setPosition(ccp(self.__PaddingLR,self.__EditBoxH+self.__PaddingT*2))
	
	local pScrollBar = SIX_ScrollBar:create(
				"extensions/scrollbar.png",CCRect(0,51,17,17),CCRect(17,0,self:getContentSize().height-self.__HeaderH-self.__EditBoxH-self.__PaddingT*4-17*2,17),
				"extensions/scrollbar.png",CCRect(0,0,17,17),
				"extensions/scrollbar.png",CCRect(0,17,17,17),
				"extensions/scrollbar.png",CCRect(0,34,17,17),
				false
			)
	pScrollBar:setAnchorPoint(ccp(0,0))
	pScrollBar:setMinimumValue(0)
	pScrollBar:setMaximumValue(100)
	pScrollBar:setValue(0)
	--pScrollBar:setRotation(90)
	--pScrollBar:getBackground():setPreferredSize(CCSize(self:getContentSize().height-self.__HeaderH-self.__EditBoxH-self.__PaddingT*4-17,17))
	--pScrollBar:setContentSize(CCSize(self:getContentSize().height-self.__HeaderH-self.__EditBoxH-self.__PaddingT*4,17))
	
	self.__ListView = SIX_ListView:create(ccc4(0,0,0,0),
																			ccp(self.__PaddingLR,self.__EditBoxH+self.__PaddingT*2),
																		 	CCSize(self:getContentSize().width-self.__PaddingLR*2,self:getContentSize().height-self.__HeaderH-self.__EditBoxH-self.__PaddingT*4),
																		 	CCSize(self:getContentSize().width-self.__PaddingLR*2,18),
																		 	kCCScrollViewDirectionVertical,
																		 	pContainer,
																		 	pScrollBar
																			)
	self.__ListView:setObjName("ConsoleList")
	
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
	
--	-- 添加子节点到ListView
--	for i=0,19 do
--		local pCell = SIX_ListViewCell:new()
--		self.__ListView:AddCell(pCell,i)
--		
--		local sprite = CCScale9Sprite:create("extensions/tit.png");
--		sprite:setAnchorPoint(ccp(0,0));
--		sprite:setPosition(ccp(0,0));
--		sprite:setPreferredSize(CCSize(self:getContentSize().width-self.__PaddingLR*2,27));
--		pCell:addChild(sprite);
--	
--		local text = CCString:create(string.format("%02d",i));
--		local label = CCLabelTTF:create(text:getCString(), "Helvetica", 12.0);
--		label:setPosition(ccp(0,0));
--		label:setAnchorPoint(ccp(0,0));
--		label:setColor(ccc3(255,0,255));
--		label:setOpacity(255);
--		-- 抗锯齿
--		label:getTexture():setAntiAliasTexParameters();
--		label:setTag(123);
--		pCell:addChild(label);
--	end
	
	-- 手动刷新ListView(增删子节点会调用ListView内部方法自动刷新，这里只是演示而已~)
	--self.__ListView:refresh()
end

function Console:InitEditBox()
	if (self==nil) then
		return
	end
	self.__EditBox = SIX_EditBox:new()
	self.__EditBox:setPosition(ccp(self.__PaddingLR,self.__PaddingLR))
	self.__EditBox:setContentSize(CCSize(self:getContentSize().width-self.__PaddingLR*2-self.__SubmitW,self.__EditBoxH))
	-- 文字输入上限
	self.__EditBox:setInputTextMaxCount(80)
	self.__EditBox:getTTF():setPosition(ccp(5,5))
	self.__EditBox:getTTF():setFontSize(14)
	-- 默认提示文字
	self.__EditBox:getTTF():setPlaceHolder("CMD>")
	-- 提示文字颜色
	self.__EditBox:getTTF():setColorSpaceHolder(ccc3(0,255,255))
	-- 输入文字颜色
	self.__EditBox:getTTF():setColor(ccc3(0,255,255))
	self:addChild(self.__EditBox)
	
	-- 输入光标
	self.__EditBox:InitCursor(0xFFFFFFFF,2,16)
	
	-- 按钮
	local pNor = CCScale9Sprite:create("extensions/button.png")
	self.__Submit = CCControlButton:create(pNor)
	self.__Submit:setPreferredSize(CCSize(self.__SubmitW,self.__EditBoxH))
	self.__Submit:setZoomFactor(1.05)
	self.__Submit:setContentSize(CCSize(self.__SubmitW,self.__EditBoxH))
	self.__Submit:setAnchorPoint(ccp(0.5,0.5))
	self.__Submit:setPosition(ccp(self:getContentSize().width-self.__SubmitW/2-self.__PaddingLR,self.__PaddingLR + self.__EditBoxH/2))
	self:addChild(self.__Submit)
end

function Console:setTitle(text)
	if (self==nil) then
		return
	end
	if (self.__TitleTTF~=nil) then
		self.__TitleTTF:setString(text)
	end
end

function Console:setRuntime(text)
	if (self==nil) then
		return
	end
	if (self.__RuntimeTTF~=nil) then
		self.__RuntimeTTF:setString(text)
	end
end

function Console:setContent(text)
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
	pContent:setContentSize(CCSize(self:getContentSize().width-self.__PaddingLR*2,self:getContentSize().height-self.__HeaderH-self.__EditBoxH-self.__PaddingT*4))
	pContent:getTexture():setAntiAliasTexParameters()
	pCell:addChild(pContent)
end

function Console:Show(IsShow)
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
		-- 提高优先级
		--self:PriorityPromote()
		--self:setPriority(-1024)
		-- 吞掉触碰事件
		self:setSwallowsTouches(true)
		-- 继续当前Layer的touch处理
		self:setTouchEventPause(false)
		self:setScale(0.0)
		ScaleToAction = CCScaleTo:create(0.2,1.05)
		ScaleToActionReverse = CCScaleTo:create(0.1,1.0)
		self:DoEnter()
	elseif (IsShow==false) then
		-- 降低优先级
		--self:PriorityReduce()
		--self:setPriority(10)
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

function Console:ProcessCommand(cmd)
	if (self==nil) then
		return
	end

	local cmdCon = string.lower(cmd)
	
	if (cmdCon~="exit") then
		self:setContent(">"..cmd)
	end
	
	if (cmdCon=="version" or cmdCon=="ver") then
		self:setContent("---------------------------------------")
		self:setContent("版本："..VersionStr())
		self:setContent("日期："..VERSION.DATE)
		self:setContent("---------------------------------------")
	elseif (cmdCon=="stats") then
		self:setContent("version number："..VersionNum())
		if (pScene~=nil) then
			if (pScene:getObjName()=="SceneGame") then
				self:setContent("Bullet.Total="..CBulletAndNetManage.s_AllBullet:getChildrenCount())
			elseif (pScene:getObjName()=="SceneRoom") then
				if (pTableMgr~=nil) then
					self:setContent("房间在线人数="..pTableMgr.__PlayerCount)
					self:setContent("房间桌子总数="..pTableMgr.__TableCount.."/"..pTableMgr.__SeatCount)
				end
			end
		end
	elseif (cmdCon=="socket") then
		self:setContent("pSocket："..tostring(pSocket))
	elseif (cmdCon=="exit") then
		CCLuaLog("Sayonara!")
		-- 先停止通讯模块
		EndGameLogic()
		-- 给个退出标志位，在OnSocketRecv里收到断开消息后才真正退出
		NEEDEXIT=true
	elseif (cmdCon=="threadid") then
		self:setContent("CurrentThreadID："..string.format("0x%08X",(SIX_Utility:GetInstance():GetCurrentThreadId())))
	elseif (cmdCon=="login_room") then
		self:setContent("登录房间...")
		login_room()
	elseif (cmdCon=="leave_room") then
		self:setContent("离开房间...")
		leave_room()
	elseif (cmdCon=="leave_seat") then
		self:setContent("离开座位...")
		leave_seat()
	elseif (cmdCon=="fire") then
		self:setContent("开火...")
		fire()
	elseif (cmdCon=="query_user_list") then
		self:setContent("查询用户列表...")
		query_user_list()
	else
		local mp = SIX_MP:new()
		if (mp==nil) then
			self:setContent("Unknown.Command!")
			return
		end
		local value = SIX_Utility:GetInstance():Split(" ",cmd,mp)
		if (mp:size()==2) then
			local key = string.lower(mp:at(0))
			if (key=="write_score") then
				self:setContent("写分："..mp:at(1).."...")
				write_score(mp:at(1))
			elseif (key=="dirty") then
				local IsDirty = tonumber(mp:at(1))
				if (IsDirty==0) then
					self:getParent():setRectDirty(false)
				else
					self:getParent():setRectDirty(true)
				end
			elseif (key=="runscene") then
				local nextSceneIdx = tonumber(mp:at(1))
				CCLuaLog("nextSceneIdx="..nextSceneIdx)
				if (nextSceneIdx>=0) then
					runScene(nextSceneIdx,"CCFadeWhiteTransition",1.2)
				end
			else
				self:setContent("Unknown.Command!")
			end
		elseif (mp:size()==3) then
			local key = string.lower(mp:at(0))
			if (key=="sit_down") then
				self:setContent("坐下座位...")
				sit_down(mp:at(1),mp:at(2))
			else
				self:setContent("Unknown.Command!")
			end
		else
			self:setContent("Unknown.Command!")
		end
	end
end
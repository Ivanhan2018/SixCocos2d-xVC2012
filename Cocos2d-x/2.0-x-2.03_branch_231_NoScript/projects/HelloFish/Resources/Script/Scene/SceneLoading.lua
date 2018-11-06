--[[
------------------------------------
Loading场景脚本
------------------------------------
Cool.Cat@2013/4/2 16:12:05
------------------------------------
]]
--require "Script/Fish"--add by Ivan_han
changeScene = false
pPlayerInfoBox = 0

function main()
	-- 全局创建
	pScene = SIX_UIScene:scene()
	pScene:setObjName("SceneLoading")
	CCLuaLog("A")
	CCLuaLog("pScene="..tostring(pScene))
	CCLuaLog("pUIScene="..tostring(pScene:GetScene()))
	CCLuaLog("B")
	
	-- 触碰
	pScene:setTouchEnabled(true)
	-- 键盘
	pScene:setKeypadEnabled(true)
	-- 加速键
	pScene:setAccelerometerEnabled(true)

	-- 注册事件回调
	RegisterCallBack()
	
	return pScene
end

-- 单点触碰事件
function onSceneLoadingTouch(e,x,y)
	CCLuaLog("onSceneLoadingTouch.onTouch.e.["..e.."].x["..x.."].y["..y.."]")
	return true
end

--[[
多点触碰事件
原型：
enum {
    CCTOUCHBEGAN,
    CCTOUCHMOVED,
    CCTOUCHENDED,
    CCTOUCHCANCELLED,

    ccTouchMax,
};
]]
function onSceneLoadingMultiTouch(e,p)
	CCLuaLog("onSceneLoadingMultiTouch.onMultiTouch.e["..e.."]")
    for i = 1, #p, 2 do
        CCLuaLog("onSceneLoadingMultiTouch.onMultiTouch.x["..p[i].."].y["..p[i+1].."]")
    end
  CCLuaLog("--------------------------")
  return true
end

function eventListenerLoading(e)
	local type=e["name"]
	CCLuaLog("SceneLoading.type="..type)
	local pointer = e["pointer"]
	--pointer = tolua.cast(pointer,"SIX_UIScene")
	CCLuaLog("SceneLoading.type="..type..",pointer="..tostring(pointer))
	if type=="enter" then
		onLoadingEnter()
	elseif type=="exit" then
		onLoadingExit()
	elseif type=="ExitTransitionDidStart" then
		onLoadingExitTransitionDidStart()
	elseif type=="EnterTransitionDidFinish" then
		onLoadingEnterTransitionDidFinish()
	end
end

-- 注册事件回调
function RegisterCallBack()
	--[[
	注册触碰事件
	原型：
	funcID
	bIsMultiTouches=false
	nPriority=INT_MIN
	bSwallowsTouches=false
	]]
	-- 单点触碰
	pScene:registerScriptTouchHandler(onSceneLoadingTouch,false)
	-- 多点触碰
	--pScene:registerScriptTouchHandler(onSceneLoadingMultiTouch,true)
	
	-- 注册事件回调
	pScene:registerScriptHandler(eventListenerLoading)
end

-- 加载XML布局文件
function LoadXML()
	CCLuaLog("SceneLoading.LoadXML...SIX_UIScene["..tostring(pScene).."].Scene["..tostring(pScene:GetScene()).."]")
	if (pScene==nil) then
		CCLuaLog("SceneLoading.LoadXML.pScene.A="..tostring(pScene))
		return 0
	end

	CCFileUtils:sharedFileUtils():setResourceDirectory("iphonehd")
	local retv = pScene:GetUIMgr():LoadXMLFromFile("Loading.xml")
	pScene:GetUIMgr():ReleaseXML()
	if (retv~=0) then
		return 0
	end
	
	CCLuaLog("SceneLoading.LoadXML...OK!")
	return 1
end

function LoadUI()
	-- 取背景控件
	local bg = pScene:getChildren():objectAtIndex(0)
	bg = tolua.cast(bg,"CCLayerColor")
	CCLuaLog("bg="..tostring(bg)..",objName="..bg:getObjName())
	--add by Ivan_han
	--FishManage:Init(bg)	
--	-- 下拉框测试
--	pPlayerInfoBox = DragBox:createWithFile("Scene/Game/playerinfo_bg.png")
--	if (pPlayerInfoBox) then
--		pPlayerInfoBox:setPosition(ccp(100,100))
--		pPlayerInfoBox:DoAction()
--		bg:addChild(pPlayerInfoBox)
--	end
--	CCLuaLog("pPlayerInfoBox="..tostring(pPlayerInfoBox))	

--	-- 按钮背景	
--	local pSpr = CCScale9Sprite:create("Scene/Loading/BtnNormal.png")
--	CCLuaLog("pSpr="..tostring(pSpr))
--	-- 创建按钮
--	local pButton = CCControlButton:create(pSpr)
--	pButton:setObjName("wtf!!!")
--	CCLuaLog("pButton="..tostring(pButton)..",objName="..pButton:getObjName()..",type="..tolua.type(pButton))
--
--	pButton:setPreferredSize(CCSize(205,75))
--	pButton:setPosition(CCPoint(200,200))
--	bg:addChild(pButton)

--	-- 注册按钮回调事件
--	pScene:GetUIMgr():addControlEvents(67,pButton)

--		local pList = SIX_ListView:create(ccc4(0,0,0,0),0,0,ccp(600,100),CCSize(60,280),CCSize(60,60),kCCScrollViewDirectionVertical)
--		pList:setObjName("pList")
--		pList:setRectDirty(true)
--		pScene:addChild(pList)

	DEVELOPER_MODE = false
end

-- 进入场景时触发
function onLoadingEnter()
	CCLuaLog("SceneLoading.onLoadingEnter")
	
	-- 改成2D，默认是3D的。。。
	CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
	
	-- 可以直接解析XML文件加载UI
	LoadXML()
	
	-- 初始化UI
	LoadUI()
end

function Update(time)
	--CCLuaLog("Update.time="..time)
	
	local UT = SIX_Utility:new()
	local value = UT:RNDNUM(0,100)	
	updateProgress(value)	
end

function updateProgress(value)
	if (changeScene) then
		return
	end
	local bg = pScene:getChildByTag(0)
	bg = tolua.cast(bg,"CCLayerColor")
	
	-- 目前只有下面两种方式查找控件：
	-- 1)通过对象索引查找，如果要查找的节点之前又动态添加了新节点，则需要重新计算好索引才能找到
	--local pProgress = bg:getChildren():objectAtIndex(9)

	-- 2)通过tag查找，比第1种稍微方便些，不需要知道控件索引，但是一样需要先找到父节点才行
	local pProgress = bg:getChildByTag(1)
	
	pProgress = tolua.cast(pProgress,"CCProgressTimer")
	--CCLuaLog("pProgress.name="..pProgress:getObjName())	
	
	local v = pProgress:getPercentage()
	if (v>=100.0) then
		v = 0.0
	else
		v=v+0.5
	end

	-- 设置进度条百分比先~
	pProgress:setPercentage(v)
	
	-- 光标
	local halo = bg:getChildByTag(2)
	halo = tolua.cast(halo,"CCSprite")

	local m_tBarChangeRate = pProgress:getBarChangeRate()
	local m_tMidpoint = pProgress:getMidpoint()
	local offset_x = convertPercentageToMaxPostionX(v,m_tBarChangeRate,m_tMidpoint) * 100
	local offset_x_final = offset_x * pProgress:getContentSize().width / 100
	--CCLuaLog("halo="..tostring(halo)..",name="..halo:getObjName()..",value="..value..",getPositionX="..pProgress:getPositionX()..",v="..v..",offset_x="..offset_x..",offset_x_final="..offset_x_final..",halo:getPositionX()="..halo:getPositionX())

	-- 在非规则区域要缩放
	if (offset_x_final<22.0) then
		halo:setScale(offset_x_final * (1/22))
	elseif (offset_x_final>596.0) then
		halo:setScale((22-(offset_x_final-596)) * (1/22))
	-- 在规则区域还原
	else
		halo:setScale(1.0)
	end
	halo:setPositionX(offset_x_final+pProgress:getPositionX())
end

-- 场景切换完成时触发，位于onEnter之后
function onLoadingEnterTransitionDidFinish()
	CCLuaLog("SceneLoading.onLoadingEnterTransitionDidFinish")
	
	local pScheduler = CCDirector:sharedDirector():getScheduler();
	pScheduler:scheduleScriptFunc(Update, 0.01, false)	
end

-- 场景切换之前时触发，位于onExit之前
function onLoadingExitTransitionDidStart()
	CCLauLog("SceneLoading.onLoadingExitTransitionDidStart")
end

-- 退出场景时触发
function onLoadingExit()
	CCLuaLog("SceneLoading.onLoadingExit.A")
	
	-- 释放场景容器中对应的指针
	local pGlobalMgr = SIX_GlobalMgr:new()
	pGlobalMgr:GetSceneMgr():unloadScene(1)
	--add by Ivan_han
	--FishManage:Release()	
	CCLuaLog("SceneLoading.onLoadingExit.B")
end

-- 加速键处理？
-- 相应键：上、下、左、右、<、>
-- 传参(加速键信息)待实现
-- Cool.Cat@2013/4/2 16:36:52
local pConsole=nil
function AccelerometerKeyHook(MSG,wParam,lParam)
	--CCLuaLog("SceneRoom.AccelerometerKeyHook.MSG["..MSG.."].wParam["..wParam.."].lParam["..lParam.."]")
	
	if (MSG==Enum_KeyBord.WM_KEYUP) then
		if (wParam==KEY_WPARAM.VK_RETURN) then
			if (pConsole~=nil) then
				pConsole:DoEnter()
			end
		end	
	-- WM_CHAR
	elseif (MSG==Enum_KeyBord.WM_CHAR) then
		-- ESC
		if (wParam==KEY_WPARAM.VK_ESCAPE) then
			CCLuaLog("SceneRoom.KEY_WPARAM.VK_ESCAPE")
		-- ~
		elseif (wParam==KEY_WPARAM.VK_NUMPAD0) then
			ShowConsole()
			return 1
		-- balabala
		end
	end
	return 0
end

-- 控制台
function ShowConsole()
	if (GetRuntime()-DEVELOPER_LASTTIME>=0.05 or DEVELOPER_LASTTIME==0) then
		if (DEVELOPER_MODE==true) then
			DEVELOPER_MODE = false
			pScene:removeChildByTag(-1024,true)
		else
			DEVELOPER_MODE = true
			local pBlock = SIX_UILayer:create(ccc4(0,0,0,128),true,-129,false)
			pBlock:setTag(-1024)
			pScene:addChild(pBlock,99)
		end
		CCLuaLog("pConsole="..tostring(pConsole))
		DEVELOPER_LASTTIME = GetRuntime()
		
		if (pConsole==nil) then
			pConsole = Console:create(112,125,800,400,0,0,0,200,true,-1023,true)
			pConsole:setTag(-1025)
			pScene:addChild(pConsole,100)
		end
		if (pConsole) then
			pConsole:Show(DEVELOPER_MODE)
			if (DEVELOPER_MODE==true) then
				pScene:reorderChild(pConsole,100)
			end
		end
		CCLuaLog("Developer.Console.Show...["..os.time().."].DEVELOPER_MODE["..tostring(DEVELOPER_MODE).."].GetRuntime["..GetRuntime().."]")
	end
end

-- 控件拖拽
function onCCControlEventTouchDragInside(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragInside")
end

function onCCControlEventTouchDragOutside(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragOutside")
end

function onCCControlEventTouchDragEnter(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragEnter")
end

function onCCControlEventTouchDragExit(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragExit")
end

-- 控件按下
function onCCControlEventTouchDown(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDown")
end

-- 弹起(鼠标在控件区域内)
function onCCControlEventTouchUpInside(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchUpInside")
	pControl = tolua.cast(pSender,"CCControlButton")
	if (pControl==nil) then
		return
	end
	
	local btnName = pControl:getObjName()
	CCLuaLog("SceneLoading.btnName="..btnName)
	
	-- 切换场景
	if (btnName=="settings") then
		changeScene = true
		local retv = runScene(2,"CCFadeWhiteTransition",1.2)
		--add by Ivan_han
	    --FishManage:addOneFish(1)
	end
end

-- 弹起(鼠标在控件区域外)
function onCCControlEventTouchUpOutside(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchUpOutside")
end

-- 取消
function onCCControlEventTouchCancel(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchCancel")
end

-- 值改变
function onCCControlEventValueChanged(pSender,name)
	CCLuaLog("SceneLoading.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventValueChanged")
end

-- 主动调用函数并回显错误
xpcall(main, __G__TRACKBACK__)
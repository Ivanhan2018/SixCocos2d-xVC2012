--[[
------------------------------------
游戏场景
------------------------------------
Cool.Cat@2013/4/13 12:06:15
------------------------------------
--]]
require "Script/Fish"--add by Ivan_han
require "Script/BulletAndNet"
require "Script/Common/Variable"
require "Script/Ship"
require "Script/ExControl/SettleBox"


pPlayerInfoBox = 0
g_bInited = false
pSettleBox = nil

local l_LoadImageCount = 0
local l_LoadImageCountTotal = 31
local l_lastCollideCheckTime = SIX_Utility:new():GetTickCount()
local l_CollideIntervalTime = 100

function main()
	-- 全局创建
	pScene = SIX_UIScene:scene()
	pScene:setObjName("SceneGame")
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
function onTouch(e,x,y)
	CCLuaLog("onTouch.e.["..e.."].x["..x.."].y["..y.."]")
end

--[[
多点触碰事件
原型：
enum {
    CCTOUCHBEGAN,
    CCTOUCHMOVED,
    CCTOUCHENDED,
    CCTOUCHCANCELLED,
    CCMOUSEMOVE,
    ccTouchMax,
};
]]

function onMultiTouch(e,p)
	--CCLuaLog("SceneGame.onMultiTouch.e["..e.."]")
	if (g_bInited == false) then
		return
	end
	local PushMouseLeftButton = false
	local bWhirlGun = false
	local bShootBullet = false
	local bg = pScene:getChildren():objectAtIndex(0)
	local pushTime = 0
	
	for i = 1, #p, 2 do
		onUpdateMousePT( CCPoint(p[i], p[i+1]) )
		
		if 0==tonumber(e) then		
			PushMouseLeftButton = true
			pushTime = SIX_Utility:new():GetTickCount()
		elseif 1==tonumber(e) then
			bWhirlGun = true
		elseif 4==tonumber(e) then
			bWhirlGun = true
		elseif 2==tonumber(e) then
			if (pushTime+500 <= SIX_Utility:new():GetTickCount()) then
				bShootBullet = true
			end
			
			PushMouseLeftButton = false			
			getMySelfShip():onRepeatShootBullet( false )
		end
		
		if bWhirlGun or not getMySelfShip().m_gun.m_initGunPt then
			getMySelfShip().m_gun.m_initGunPt = true
			getMySelfShip():onWhirlGun( CCPoint(p[i], p[i+1]) )
		end
		
		if bShootBullet then
			getMySelfShip():onShootBullet( CCPoint(p[i], p[i+1]), false )
		elseif PushMouseLeftButton then
			getMySelfShip():onRepeatShootBullet( true )
		end
	end
	return true
end

function eventListenerGame(e)
	local type=e["name"]
	local pointer = e["pointer"]
	--CCLuaLog("SceneGame.type="..type..",pointer="..tostring(pointer))
	
	if type=="enter" then
		onGameEnter()
	elseif type=="exit" then
		onGameExit()
	elseif type=="ExitTransitionDidStart" then
		onGameExitTransitionDidStart()
	elseif type=="EnterTransitionDidFinish" then
		onGameEnterTransitionDidFinish()
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
	--pScene:registerScriptTouchHandler(onTouch,false)
	-- 多点触碰
	pScene:registerScriptTouchHandler(onMultiTouch,true)
	
	-- 注册事件回调
	pScene:registerScriptHandler(eventListenerGame)
end

-- 加载XML布局文件
function LoadXML()
	CCLuaLog("SceneGame.LoadXML...SIX_UIScene["..tostring(pScene).."].Scene["..tostring(pScene:GetScene()).."]")
	if (pScene==nil) then
		CCLuaLog("SceneGame.LoadXML.pScene.A="..tostring(pScene))
		return 0
	end

	CCFileUtils:sharedFileUtils():setResourceDirectory("iphonehd")
	local retv = pScene:GetUIMgr():LoadXMLFromFile("SceneGame.xml")
	pScene:GetUIMgr():ReleaseXML()
	if (retv~=0) then
		return 0
	end
	
	CCLuaLog("SceneGame.LoadXML...OK!")
	return 1
end

function LoadUI()
	-- 取背景控件
	local bg = pScene:getChildren():objectAtIndex(0)
	bg = tolua.cast(bg,"CCLayerColor")
	CCLuaLog("bg="..tostring(bg)..",objName="..bg:getObjName())
	
	-- 随机背景1-5
	local bgimage = bg:getChildren():objectAtIndex(0)
	bgimage = tolua.cast(bgimage,"CCSprite")
	if (bgimage~=nil) then
		local rnd = SIX_Utility:new():RNDNUM(1,5)
		local rndImage = "Scene/Game/Scene0"..rnd..".jpg"
		CCLuaLog(rndImage)
		local tex2D = CCTextureCache:sharedTextureCache():addImage(rndImage)
		if (tex2D~=nil)then
			tex2D = tolua.cast(tex2D,"CCTexture2D")
			bgimage:setTexture(tex2D)
		end
	end

--
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

	DEVELOPER_MODE = false
end

-- 进入场景时触发
function onGameEnter()
	CCLuaLog("SceneGame.onGameEnter")
	
	-- 改成2D，默认是3D的。。。
	CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
	
	-- 可以直接解析XML文件加载UI
	LoadXML()
	
	-- 初始化UI
	LoadUI()
end

function FishAndBulletCollide()
	if not g_bInited or SIX_Utility:new():GetTickCount() < l_lastCollideCheckTime+l_CollideIntervalTime then
		return
	end
	l_lastCollideCheckTime = SIX_Utility:new():GetTickCount()
	
	-- 子弹
	local allBullet = CBulletAndNetManage:sharedBullet():getChildren()
	local object = nil
	local UserID = nil
	local IsCatching = nil
	local lHaveCatchingFish = nil
	
	-- 子弹检测
	for index=0,allBullet:count()-1 do
		object = allBullet:objectAtIndex( index )
		object = tolua.cast(object, "CCSprite")
		UserID = CBulletAndNetManage.s_BulletData[object]["UserID"]
		IsCatching = CBulletAndNetManage.s_BulletData[object]["IsCatching"]
		lHaveCatchingFish = false
		
		if object and not IsCatching and UserID==getMySelfShip().m_UserID then
			for k,v in pairs( FishManage.mFishData ) do
				local spriteFishBomb = k
				spriteFishBomb = tolua.cast(spriteFishBomb, "CCSprite")
				
				local fishRect = spriteFishBomb:boundingBox()
				local fishWidth = fishRect.size.width*3/4
				local fishHeight = fishRect.size.height*3/4
				fishRect = CCRect(fishRect:getMidX()-fishWidth/2, fishRect:getMidY()-fishHeight/2, fishWidth, fishHeight)
			
				-- 先检测子弹位置有无碰撞鱼，再根据这个位置检测与鱼网区域相交的鱼 ( lHaveCatchingFish )
				if not FishManage.mFishData[spriteFishBomb]["isCatch"] then
					if lHaveCatchingFish then
						local netsizeaa = CBulletAndNetManage.l_NetSize
						local NetSize = CBulletAndNetManage:getNetSize()
						NetSize.width,NetSize.height = NetSize.width*3/4,NetSize.height*3/4 -- 图片的边空白区域需要忽略
						local NetRect = CCRect(object.x-NetSize.width/2,object.y-NetSize.height/2,NetSize.width,NetSize.height)
						
						if fishRect:intersectsRect( NetRect ) then
							FishManage.mFishData[spriteFishBomb]["isCatch"] = true
							DieAnimation( spriteFishBomb )
							--CCLuaLog(string.format("Fish 111 Rect(%d,%d,%d,%d),   bullet (%d,%d)",fishRect:getMinX(),fishRect:getMinY(),fishRect.size.width,fishRect.size.height,  object.x, object.y)) --del
						end						
					elseif fishRect:containsPoint(CCPoint(object.x,object.y)) then
						lHaveCatchingFish = true
						FishManage.mFishData[spriteFishBomb]["isCatch"] = true
						DieAnimation( spriteFishBomb )
						--CCLuaLog(string.format("Fish 222 Rect(%d,%d,%d,%d),   bullet (%d,%d)",fishRect:getMinX(),fishRect:getMinY(),fishRect.size.width,fishRect.size.height,  object.x, object.y)) --del
					end
					
					--CCLuaLog(string.format("Fish 333 Rect(%d,%d,%d,%d),   bullet (%d,%d)",fishRect:getMinX(),fishRect:getMinY(),fishRect.size.width,fishRect.size.height,  object.x, object.y)) --del
				end
			end -- end for
		end
		
		if lHaveCatchingFish then
			CBulletAndNetManage.s_BulletData[object]["IsCatching"] = true
			FinishAnimation( object )
		end
	end
    
	UpdateBullet()
end

function Update(time)
	if (changeScene==true) then
		changeScene = false
		g_bInited = false
		-- 切换到房间场景
		LAST_SCENE_IDX = 2
		runScene(0,"CCFadeWhiteTransition",1.2)
	else
		FishAndBulletCollide()
	end	
end

--local switchSceneID = 0

-- 场景切换完成时触发，位于onEnter之后
function onGameEnterTransitionDidFinish()
	CCLuaLog("SceneGame.onGameEnterTransitionDidFinish")
	
	local pScheduler = CCDirector:sharedDirector():getScheduler();
	pScheduler:scheduleScriptFunc(Update, 0.01, false)

	ShowPopWndLoading(true)
	
	-- 异步加载 .plist 文件
	pFishManage = FishManage.new()
	addSpriteFramesWithPlistAsync(string.format('Scene/Game/FishAndBomb/DeadBomb.plist'), pFishManage)
	
	addSpriteFramesWithPlistAsync(string.format('Scene/Game/GunBulletGold.plist'), pFishManage)
	
	local arr={1,2,3,4,5,6,7,8,9,10,12,15,18,20,25,30,40}
	for i=1,#arr do
		local fishType=arr[i]
		CCLuaLog("fishType.A["..i.."]="..fishType)
		local pStrBuffer1 = string.format('Scene/Game/FishAndBomb/Fish_%02d.plist', fishType)
		addSpriteFramesWithPlistAsync(pStrBuffer1,pFishManage)
	end
	
  local arr1={1,2,3,4,5,6,7,8,9,10,11,12}
	for i=1,#arr1 do
		local BombType=arr1[i]
		local pStrBuffer1 = string.format('Scene/Game/FishAndBomb/Bomb_%02d.plist', BombType)
		addSpriteFramesWithPlistAsync(pStrBuffer1,pFishManage)
	end
end

-- 另外还在回调中做以下3步处理：
-- Cool.Cat@2013/5/9 19:15:48
-- 1、pszPlist是xxx.png格式的，需要换成xxx.plist。。。
-- 2、CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithDictionary(dict,pTexture)
-- 3、CCSpriteFrameCache:sharedSpriteFrameCache():insertPlist(pszPlist)
function AddImageAsyncCallBack(pTexture,pszPlist)
	pTexture = tolua.cast(pTexture,"CCTexture2D")
	
	-- 判断下后缀，难道还有非png的。。。
	-- Cool.Cat
	pszPlist = string.lower(pszPlist)
	local suffix = string.sub(pszPlist,-4)
	if (suffix~=".png") then
		CCLuaLog("WTF!Are'u kidding me?")
		CCMessageBox("WTF!Are'u kidding me?",0)
	end
	
	-- 咔嚓掉
	local plist = string.gsub(pszPlist,".png",".plist")
	local pszPath = CCFileUtils:sharedFileUtils():fullPathFromRelativePath(plist)
	local dict = CCDictionary:createWithContentsOfFile(pszPath)
	CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithDictionary(dict,pTexture)
	CCSpriteFrameCache:sharedSpriteFrameCache():insertPlist(plist)
	dict:release()
	
	l_LoadImageCount = l_LoadImageCount+1
	CCLuaLog("AddImageAsyncCallBack.l_LoadImageCount="..l_LoadImageCount..".l_LoadImageCountTotal="..l_LoadImageCountTotal)

	-- 更新进度条	
	if (pPopWnd~=nil) then
		pPopWnd:updateProgress((l_LoadImageCount/l_LoadImageCountTotal)*100.0)
	end

	-- 计算是否全部加载完成
	if (l_LoadImageCount == l_LoadImageCountTotal) then
		CCLuaLog("AddImageAsyncCallBack.Done")
		
		-- 创建子弹管理
		local bg = pScene:getChildren():objectAtIndex(0)
		bg = tolua.cast(bg,"CCLayerColor")
		CCLuaLog("LoadResAsyncBegin.bg="..tostring(bg)..",name="..bg:getObjName())
		
		CBulletAndNetManage:Init(bg)
		CCLuaLog("LoadResAsyncBegin.CBulletAndNetManage.Inited")
		
		pFishManage:Init(bg)
		CCLuaLog("LoadResAsyncBegin.FishManage.Inited")
		
		-- 玩家
		local bg = pScene:getChildren():objectAtIndex(0)
		CShip:Enter(bg, 10035, true)
		
		ShowPopWndLoading(false)
		
		g_bInited = true
	end
end

--function LoadResAsyncBegin(node)
--	CCLuaLog("LoadResAsyncBegin.node="..tostring(node))
--end
--
--function LoadResAsyncEnd(node)
--	CCLuaLog("LoadResAsyncBeginEnd.node="..tostring(node))
--	
--	g_bInited = true
--end

-- 弹窗Loading
pPopWnd = nil
function ShowPopWndLoading(IsShow)
	if (IsShow==true) then
		local pBlock = SIX_UILayer:create(ccc4(0,0,0,128),true,-129,false)
		pBlock:setTag(-1024)
		pScene:addChild(pBlock,99)
	else
		pScene:removeChildByTag(-1024,true)
	end
	
	if (pPopWnd==nil) then
		pPopWnd = PopWnd:create(203,125,618,400,0,0,0,0,true,-1023,false)
		pPopWnd:setTag(-1025)
		pScene:addChild(pPopWnd,100)
	end
	
	CCLuaLog("ShowPopWndLoading.pPopWnd="..tostring(pPopWnd)..".IsShow="..tostring(IsShow))
	
	if (pPopWnd) then
		if (IsShow==true) then
			--pPopWnd:Show(IsShow,0.3,LoadResAsyncBegin)
			pScene:reorderChild(pPopWnd,100)
		else
			--pPopWnd:Show(IsShow,0.1,LoadResAsyncEnd)
		end
		pPopWnd:Show(IsShow)
	end
end

--function switchScene()
--	CCLuaLog("switchScene.switchSceneID="..switchSceneID)
--	
--	runScene(0,"CCFadeWhiteTransition",1.2)
--	
--	local pScheduler = CCDirector:sharedDirector():getScheduler();
--	pScheduler:unscheduleScriptEntry(switchSceneID)
--end

-- 场景切换之前时触发，位于onExit之前
function onGameExitTransitionDidStart()
	CCLauLog("SceneGame.onGameExitTransitionDidStart")
end

-- 退出场景时触发
function onGameExit()
	CCLuaLog("SceneGame.onGameExit.A")
	
	-- 释放场景容器中对应的指针
	local pGlobalMgr = SIX_GlobalMgr:new()
	pGlobalMgr:GetSceneMgr():unloadScene(2)
	
	-- 释放子弹管理
	CBulletAndNetManage:Release()
	
	--add by Ivan_han
	pFishManage:Release()
	CCLuaLog("SceneGame.onGameExit.B")
end

-- 加速键处理？
-- 相应键：上、下、左、右、<、>
-- 传参(加速键信息)待实现
-- Cool.Cat@2013/4/2 16:36:52
local pConsole=nil
function AccelerometerKeyHook(MSG,wParam,lParam)
	--CCLuaLog("SceneGame.AccelerometerKeyHook.MSG["..MSG.."].wParam["..wParam.."].lParam["..lParam.."]")
	
	if (g_bInited == false) then
		return
	end

	if (MSG==Enum_KeyBord.WM_KEYDOWN) then
		PRESS_KEY[wParam] = true
	elseif (MSG==Enum_KeyBord.WM_KEYUP) then
		PRESS_KEY[wParam] = nil
	end
			
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

	getMySelfShip():AccelerometerKeyHook(MSG,wParam,lParam)
	CBulletAndNetManage:AccelerometerKeyHook(MSG,wParam,lParam)
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
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragInside")
end

function onCCControlEventTouchDragOutside(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragOutside")
end

function onCCControlEventTouchDragEnter(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragEnter")
end

function onCCControlEventTouchDragExit(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragExit")
end

-- 控件按下
function onCCControlEventTouchDown(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDown")
end

-- 弹起(鼠标在控件区域内)
function onCCControlEventTouchUpInside(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchUpInside")
	--add by Ivan_han
  if name=="Help" then--¡¾°𐗺¡¿
	    FishManage:addOneFish(112,1,CCPoint(200,300),CCPoint(1500,0))
	elseif name=="Set" then--¡¾ʨ׃¡¿
        FishManage:addOneGroupFish(33)
	elseif name=="Supplement" then--¡¾³喵אф¡¿
	    --FishManage:addOneFish(1,2,ccp(500,300),ccp(350,300))
	    --FishManage:addOneGroupFish(21)
	    FishManage:addOneFish(2,2,ccp(500,300),ccp(350,300)) 
	elseif name=="MyDepot" then--¡¾ϒµĲֿ⡿
	    --FishManage:addOneFish(1,1,ccp(0,100))
	    FishManage:addOneGroupFish(12)	 
	elseif name=="Gam" then--¡¾ʧ½»¡¿
	    --FishManage:addOneFish(1,3,CCPoint(200,300),CCPoint(50,0),CCPoint(0,0))	
	    --FishManage:addOneGroupFish(31)
	    FishManage:addOneFish(107,2,ccp(0,300),ccp(150,300)) 
	elseif name=="Shop" then--¡¾ʌ³ǡ¿
	    FishManage:addOneFish(1,4)
	    --FishManage:addOneGroupFish(32) 
	elseif name=="Bullet" then--¡¾ؓµ¯¡¿
	    --FishManage:addOneFish(1,4)
	    FishManage:addOneFish(101,4)    
	elseif name=="Task" then--¡¾Ɏϱ¡¿
	    FishManage:addOneGroupFish(11)
	elseif name=="Exit" then
		ShowSettleBox(true)
	elseif name=="settleGoOn" then
		ShowSettleBox(false)
	elseif name=="settleExit" then
		-- 具体结算逻辑
		-- ...
		
		-- 再切换到房间场景
		changeScene = true
	else
	    FishManage:CaptureOneFish()--¡¾³ɾ͡¿¡¢¡¾½⌣΋³�
	end
end

-- 结算窗口
function ShowSettleBox(IsShow)
	if (pScene==nil) then
		return
	end

	if (IsShow==true) then
		local pBlock = SIX_UILayer:create(ccc4(0,0,0,128),true,-129,false)
		pBlock:setTag(-1024)
		pScene:addChild(pBlock,99)
	elseif (IsShow==false) then
		pScene:removeChildByTag(-1024,true)
	end
	
	if (pSettleBox==nil) then
		pSettleBox = SettleBox:create(213,67,597,515,0,0,0,0,true,-1023)
		pSettleBox:setTag(-1025)
		pScene:addChild(pSettleBox,100)
	end

	pSettleBox:Show(IsShow)
end

-- 弹起(鼠标在控件区域外)
function onCCControlEventTouchUpOutside(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchUpOutside")
end

-- 取消
function onCCControlEventTouchCancel(pSender,name)
	CCLuaLog("SceneGame.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchCancel")
end

-- 值改变
function onCCControlEventValueChanged(pSender,name)
	CCLuaLog("pSender["..tostring(pSender).."].name["..name.."].onCCControlEventValueChanged")
end

-- 主动调用函数并回显错误
xpcall(main, __G__TRACKBACK__)
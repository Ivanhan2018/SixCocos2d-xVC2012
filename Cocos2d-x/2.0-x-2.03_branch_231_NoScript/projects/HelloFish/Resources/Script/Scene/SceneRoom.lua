--[[
------------------------------------
Room场景脚本
------------------------------------
Cool.Cat@2013/5/10 13:09:18
------------------------------------
]]

require "Script/TableMgr"

pTableMgr = nil

changeScene = false
pPlayerInfoBox = 0

function main()
	-- 全局创建
	pScene = SIX_UIScene:scene()
	pScene:setObjName("SceneRoom")
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
function onSceneRoomTouch(e,x,y)
	CCLuaLog("onSceneRoomTouch.onTouch.e.["..e.."].x["..x.."].y["..y.."]")
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
function onSceneRoomMultiTouch(e,p)
--	CCLuaLog("onSceneRoomMultiTouch.onMultiTouch.e["..e.."]")
--    for i = 1, #p, 2 do
--        CCLuaLog("onSceneRoomMultiTouch.onMultiTouch.x["..p[i].."].y["..p[i+1].."]")
--    end
--  CCLuaLog("--------------------------")
end

function eventListenerRoom(e)
	local type=e["name"]
	CCLuaLog("SceneRoom.type="..type)
	local pointer = e["pointer"]
	--pointer = tolua.cast(pointer,"SIX_UIScene")
	CCLuaLog("SceneRoom.type="..type..",pointer="..tostring(pointer))
	if type=="enter" then
		onRoomEnter()
	elseif type=="exit" then
		onRoomExit()
	elseif type=="ExitTransitionDidStart" then
		onRoomExitTransitionDidStart()
	elseif type=="EnterTransitionDidFinish" then
		onRoomEnterTransitionDidFinish()
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
	--pScene:registerScriptTouchHandler(onSceneRoomTouch,false)
	-- 多点触碰
	pScene:registerScriptTouchHandler(onSceneRoomMultiTouch,true)
	
	-- 注册事件回调
	pScene:registerScriptHandler(eventListenerRoom)
end

-- 加载XML布局文件
function LoadXML()
	CCLuaLog("SceneRoom.LoadXML...SIX_UIScene["..tostring(pScene).."].Scene["..tostring(pScene:GetScene()).."]")
	if (pScene==nil) then
		CCLuaLog("SceneRoom.LoadXML.pScene.A="..tostring(pScene))
		return 0
	end

	CCFileUtils:sharedFileUtils():setResourceDirectory("iphonehd")
	local retv = pScene:GetUIMgr():LoadXMLFromFile("Room.xml")
	pScene:GetUIMgr():ReleaseXML()
	if (retv~=0) then
		return 0
	end
	
	CCLuaLog("SceneRoom.LoadXML...OK!")
	return 1
end

function LoadUI()
	DEVELOPER_MODE = false
end

-- 进入场景时触发
function onRoomEnter()
	CCLuaLog("SceneRoom.onRoomEnter")
	
	-- 改成2D，默认是3D的。。。
	CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
	
	-- 可以直接解析XML文件加载UI
	LoadXML()
	
	-- 初始化UI
	LoadUI()
end

function Update(time)
	if (changeScene==true) then
		local bg = pScene:getChildren():objectAtIndex(0)
		bg = tolua.cast(bg,"CCLayerColor")

		-- 桌子背景容器
		local pListView = bg:getChildByTag(1)
		if (pListView==nil) then
			CCMessageBox("WTF",0)
			return
		end

		pListView = tolua.cast(pListView,"SIX_ListView")
		if (pListView==nil) then
			return
		end

		pListView:setTouchEnabled(false)

		changeScene = false
			
		-- 切换到游戏场景
		LAST_SCENE_IDX = 0
		runScene(2,"CCFadeWhiteTransition",1.2)
	end
end

-- 场景切换完成时触发，位于onEnter之后
function onRoomEnterTransitionDidFinish()
	CCLuaLog("SceneRoom.onRoomEnterTransitionDidFinish")
	
	-- 初始化桌子逻辑管理器
	if (pTableMgr==nil) then
		local bg = pScene:getChildren():objectAtIndex(0)
		bg = tolua.cast(bg,"CCLayerColor")
	
		-- 桌子背景容器
		local pListView = bg:getChildByTag(1)
		if (pListView==nil) then
			CCMessageBox("WTF",0)
			return
		end
		
		pListView = tolua.cast(pListView,"SIX_ListView")
		if (pListView==nil) then
			return
		end
		
		pTableMgr = TableMgr:create(pListView)
	end
	
	local pScheduler = CCDirector:sharedDirector():getScheduler();
	pScheduler:scheduleScriptFunc(Update, 0.01, false)
	
	if (LAST_SCENE_IDX==2) then
		LAST_SCENE_IDX = -1
		-- 取桌子列表
		query_table_list()
		
		-- 取玩家列表
		query_user_list()
		
		-- 发送离座消息
		leave_seat()
	end
end

-- 场景切换之前时触发，位于onExit之前
function onRoomExitTransitionDidStart()
	CCLauLog("SceneRoom.onRoomExitTransitionDidStart")
end

-- 退出场景时触发
function onRoomExit()
	CCLuaLog("SceneRoom.onRoomExit.A")
	
	-- 释放场景容器中对应的指针
	local pGlobalMgr = SIX_GlobalMgr:new()
	pGlobalMgr:GetSceneMgr():unloadScene(0)
	--add by Ivan_han
	--FishManage:Release()	
	CCLuaLog("SceneRoom.onRoomExit.B")
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
	CCLuaLog("SceneRoompSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragInside")
end

function onCCControlEventTouchDragOutside(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragOutside")
end

function onCCControlEventTouchDragEnter(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragEnter")
end

function onCCControlEventTouchDragExit(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDragExit")
end

-- 控件按下
function onCCControlEventTouchDown(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchDown")
end

-- 弹起(鼠标在控件区域内)
function onCCControlEventTouchUpInside(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchUpInside")
	pControl = tolua.cast(pSender,"CCControlButton")
	if (pControl==nil) then
		return
	end

	local SeatTag = pControl:getTag()
	if (SeatTag==-1) then
		HideMessageBox()
	elseif (SeatTag==-2) then
		HideMessageBox()
	else
		-- 座位索引
		local SeatIdx = tonumber(string.sub(SeatTag,-1))
		-- 座子索引
		local TableIdx = tonumber(string.sub(SeatTag,3,-2))
		-- 第几行
		local CellRow = tonumber(string.sub(SeatTag,1,1)) - 1
		CCLuaLog("SeatTag="..SeatTag.." => CellRow="..CellRow..",TableIdx="..TableIdx..",SeatIdx="..SeatIdx)
		--CCMessageBox(SIX_Utility:GetInstance():U2G("行索引["..CellRow.."].桌子索引["..TableIdx.."].座位索引["..SeatIdx.."]"),0)
		
		sit_down(TableIdx,SeatIdx)
	end
end

-- 弹起(鼠标在控件区域外)
function onCCControlEventTouchUpOutside(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchUpOutside")
end

-- 取消
function onCCControlEventTouchCancel(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventTouchCancel")
end

-- 值改变
function onCCControlEventValueChanged(pSender,name)
	CCLuaLog("SceneRoom.pSender["..tostring(pSender).."].name["..name.."].onCCControlEventValueChanged")
end

-- 主动调用函数并回显错误
xpcall(main, __G__TRACKBACK__)
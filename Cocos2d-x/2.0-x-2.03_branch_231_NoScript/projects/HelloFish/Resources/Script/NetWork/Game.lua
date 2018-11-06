--[[
------------------------------------
客户端通讯业务逻辑脚本
------------------------------------
Cool.Cat@2013/5/7 16:44:38
------------------------------------
]]

frameParam = nil
clientRoomInfo = nil
pClientLogic = nil
pMsgBox = nil

pUserIdx=0

rndName = "张三"
seatIdx = 0


function setString(key,value)
	for i=0,#key do
		table.insert(key,value[i])
	end
end


function InitGameLogic(IP,Port,Name,Password)
	CCLuaLog("InitGameLogic...")

	-- 桌子的框架参数，构造函数里有默认值
	frameParam = CLIENT_FRAME_PARAM:new()
	-- 心跳周期(s)
	frameParam.iSendHeartbeatTime = 30*1000

	pClientLogic = SIX_ClientLogic:new()
	seatIdx = pClientLogic:RandomUser(rndName)
	CCLuaLog("rndName="..SIX_Utility:GetInstance():G2U(rndName)..",seatIdx="..seatIdx)
	
	-- 用户名要转GB2312
	local gbName = SIX_Utility:GetInstance():U2G(rndName)
		
	-- 房间信息
	clientRoomInfo = CLIENT_ROOM_INFO:new(IP,Port,rndName,Password)

	CCLuaLog("clientRoomInfo = {"..clientRoomInfo.szIP..","..clientRoomInfo.iPort..","..clientRoomInfo.szName..","..clientRoomInfo.szPassword.."} , gbName="..gbName)


	local bSuccessed = pClientLogic:init(clientRoomInfo,frameParam)
	CCLuaLog("SIX_ClientLogic.init.bSuccessed="..bSuccessed)
	bSuccessed = pClientLogic:start()
	CCLuaLog("SIX_ClientLogic.start.bSuccessed="..bSuccessed)
end

function EndGameLogic()
	if (pClientLogic~=nil) then
		pClientLogic:stop()
	end
end

-- 登录房间
function login_room()
	if (pClientLogic:IsNeedExit()) then
		return
	end
	--pClientLogic:login_room()
	local pData = LOGIN_ROOM:new(pClientLogic:GetRoomInfo().szName,pClientLogic:GetRoomInfo().szPassword)
	pClientLogic:send_data(ROOM_MAIN, ROOM_SUB_LOGIN, pData, pData:GetLen())
end

-- 离开房间
function leave_room()
	if (pClientLogic:IsNeedExit()) then
		return
	end
	--pClientLogic:leave_room()
	pClientLogic:send_data(ROOM_MAIN, ROOM_SUB_LEAVE_ROOM)
end

-- 坐座位
function sit_down(tableNo,seatNo)
	if (pClientLogic:IsNeedExit()) then
		return
	end
	--pClientLogic:sit_down(tableNo,seatNo)
	local pData = SITDOWN:new(pUserIdx, tableNo,seatNo)
	pClientLogic:send_data(TABLE_MAIN, TABLE_SUB_SITDOWN, pData, pData:GetLen())
end

-- 离开座位
function leave_seat()
	if (pClientLogic:IsNeedExit()) then
		return
	end
	--pClientLogic:leave_seat()
	pClientLogic:send_data(TABLE_MAIN, TABLE_SUB_LEAVE_SEAT)
end

-- 开火
function fire()
	if (pClientLogic:IsNeedExit()) then
		return
	end
	--pClientLogic:fire()
	local pData = SHOT_FIRE:new()
	pClientLogic:send_data(TABLE_MAIN, TABLE_SUB_FIRE, pData, pData:GetLen())
end
	
-- 写分
function write_score(scoreChange)
	if (pClientLogic:IsNeedExit()) then
		return
	end
	local pData = WRITE_SCORE:new(scoreChange)
	--pClientLogic:write_score(score)
	pClientLogic:send_data(TABLE_MAIN, TABLE_SUB_WRITE_SCORE, pData, pData:GetLen())
end

-- 桌子列表
function query_table_list()
	if (pClientLogic:IsNeedExit()) then
		return
	end
	pClientLogic:send_data(ROOM_MAIN, ROOM_SUB_TABLE_LIST)
end

-- 用户列表
function query_user_list()
	if (pClientLogic:IsNeedExit()) then
		return
	end
	--pClientLogic:query_user_list()
	pClientLogic:send_data(ROOM_MAIN, ROOM_SUB_USER_LIST)
end

-- 收到完成包进行业务及异常处理
function OnSocketRecv(proxy,maincode,subcode,data,len)
	CCLuaLog("OnSocketRecv.proxy["..tostring(proxy).."].maincode["..maincode.."].subcode["..subcode.."].data["..tostring(data).."].len["..len.."]")
	
	-- 各种异常
	if (maincode==0) then
		if (subcode==0) then
			CONNECTED = true
			CCLuaLog("连接成功")
			CCLuaLog("登录房间...")
			login_room()			
		else
			CONNECTED = false
			if (subcode==-1) then
				CCLuaLog("连接失败")
			elseif (subcode==-2) then
				CCLuaLog("网络连接已断开")
				if (NEEDEXIT==true) then
					CCDirector:sharedDirector():endToLua()
				end
			elseif (subcode==-3) then
				CCLuaLog("网络通讯异常")
			elseif (subcode==-4) then
				CCLuaLog("发送失败")
			else
				CCLuaLog("未知的通讯错误")
			end
			return
		end
	end
	
	-- 下面是各种业务处理
	--add by Ivan_han 20130519
	--房间消息
    if (maincode==ROOM_MAIN) then
        handle_room_msg(subcode,data,len)
        return
    end
	--桌子消息
    if (maincode==TABLE_MAIN) then
        handle_table_msg(subcode,data,len)
        return
    end    
end

-- 提示窗口
function MessageBox(...)
	if (pScene==nil) then
		return
	end

	local pBlock = SIX_UILayer:create(ccc4(0,0,0,128),true,-129,false)
	pBlock:setTag(-1024)
	pScene:addChild(pBlock,99)
	
	if (pMsgBox==nil) then
		pMsgBox = MsgBox:create(307,250,409,254,0,0,0,0,true,-1023)
		pMsgBox:setTag(-1025)
		pScene:addChild(pMsgBox,100)
	end

	pMsgBox:clear()
	for i=1,select('#',...) do
		local text = select(i, ...)
		pMsgBox:setContent(text)
	end
	pMsgBox:Show(true)
end

function HideMessageBox()
	if (pScene==nil) then
		return
	end
	pScene:removeChildByTag(-1024,true)
	pMsgBox:Show(false)
end

--处理房间消息
--[[
登录房间成功后收包顺序：
ROOM_SUB_USER_INFO				->
ROOM_SUB_TABLE_LIST				->
ROOM_SUB_TABLE_LIST_OVER	->
ROOM_SUB_USER_LIST				->
ROOM_SUB_USER_LIST_OVER 	->

]]
function handle_room_msg(subcode,data,len)
	if (subcode==ROOM_SUB_LOGIN_FAIL) then
		--printf("用户登录失败，错误码：%d  \n", pReal->iErrCode);
		data = tolua.cast(data,"LOGIN_ROOM_FAIL")
		CCLuaLog("用户登陆失败.iErrCode["..data.iErrCode.."]")
		-- 界面UI要给与提示！
		-- ...
	elseif (subcode==ROOM_SUB_LOGIN_SUCC) then
		CCLuaLog("登录成功...")
		data = tolua.cast(data,"LOGIN_ROOM_SUCC")
		data = tolua.cast(data.userInfo,"USER_INFO")
		pUserIdx=data.lUserId
    local szName=SIX_Utility:GetInstance():G2U(data.szName)
    local szNickname=SIX_Utility:GetInstance():G2U(data.szNickname)
    local iTableNo=data.iTableNo
    local iSeatNo=data.iSeatNo
    local lScore=data.lScore
    local stUserState = data.stUserState
		CCLuaLog("自己["..pUserIdx.."]：szName["..szName.."].szNickname["..szNickname.."].iTableNo["..iTableNo.."].iSeatNo["..iSeatNo.."].lScore["..lScore.."].stUserState["..stUserState.."]")
		
		local platform = CCApplication:sharedApplication():getTargetPlatform()
		if (platform==kTargetWindows) then
			local title = APPNAME.." ver:"..VersionStr() .. " "..szNickname.."["..szName.."]["..pUserIdx.."]"
			CCEGLView:sharedOpenGLView():setWindowTitle(SIX_Utility:GetInstance():U2G(title))
		end
		
		-- MsgBox
		MessageBox("登录成功！","+++ 你的个人数据 +++","用户ID："..pUserIdx,"用户名："..szName,"昵　称："..szNickname)
				
	elseif (subcode==ROOM_SUB_USER_INFO) then
		CCLuaLog("接收玩家信息...")
		data = tolua.cast(data,"USER_INFO")
		local lUserId=data.lUserId
    local szName=SIX_Utility:GetInstance():G2U(data.szName)
    local szNickname=SIX_Utility:GetInstance():G2U(data.szNickname)
    local iTableNo=data.iTableNo
    local iSeatNo=data.iSeatNo
    local lScore=data.lScore
    local stUserState = data.stUserState
		CCLuaLog("玩家["..lUserId.."]：szName["..szName.."].szNickname["..szNickname.."].iTableNo["..iTableNo.."].iSeatNo["..iSeatNo.."].lScore["..lScore.."].stUserState["..stUserState.."]")

	elseif (subcode==ROOM_SUB_TABLE_LIST) then
		CCLuaLog("接收桌子列表...")
		data = tolua.cast(data,"SERVER_ROOM_INFO")
		CCLuaLog("szGameTable["..data.szGameTable.."].iGameType["..data.iGameType.."].iMoneyPoint["..data.iMoneyPoint.."].iRoomPeopleCount["..data.iRoomPeopleCount.."].iTables["..data.iTables.."].iSeatNum["..data.iSeatNum.."]")
			
		-- 赋值
		pTableMgr:UpdateAttribute(data.iRoomPeopleCount,data.iTables,data.iSeatNum)
		-- 画桌子咯~
		pTableMgr:ShowTable(true)

	elseif (subcode==ROOM_SUB_TABLE_LIST_OVER) then
		CCLuaLog("接收桌子列表完成")
	elseif (subcode==ROOM_SUB_USER_LIST) then
		CCLuaLog("接收玩家列表...")
		data = tolua.cast(data,"USER_INFO")
		local lUserId=data.lUserId
    local szName=SIX_Utility:GetInstance():G2U(data.szName)
    local szNickname=SIX_Utility:GetInstance():G2U(data.szNickname)
    local iTableNo=data.iTableNo
    local iSeatNo=data.iSeatNo
    local lScore=data.lScore
    local stUserState = data.stUserState
    CCLuaLog("玩家["..lUserId.."]：szName["..szName.."].szNickname["..szNickname.."].iTableNo["..iTableNo.."].iSeatNo["..iSeatNo.."].lScore["..lScore.."].stUserState["..stUserState.."]")
    
    -- 玩家已经坐下的，绘制头像
    if (lUserId~=INVALID_USER_ID and iTableNo~=INVAL_TABLE_NO and iSeatNo~=INVAL_SEAT_NO) then
    	pTableMgr:SwitchSitDownOrLeaveSeat(lUserId,iTableNo,iSeatNo,true)
    end

	elseif (subcode==ROOM_SUB_USER_LIST_OVER) then
		CCLuaLog("接收玩家列表完成")

	elseif (subcode==ROOM_SUB_LEAVE_ROOM) then		
		data = tolua.cast(data,"LEAVE_ROOM_RESULT")	
		CCLuaLog("离房成功")
			
	else

	end
end

--处理桌子消息
function handle_table_msg(subcode,data,len)
	-- 坐座位
	if (subcode==TABLE_SUB_SITDOWN) then
		data = tolua.cast(data,"SITDOWN")
		if (0==data.iRes) then
				if (pTableMgr==nil or pScene==nil) then
					return
				end
				pTableMgr:SwitchSitDownOrLeaveSeat(data.lUserId,data.iTableNo,data.iSeatNo,true)
				if (data.lUserId==pUserIdx) then
					-- 给个标志位，在update里面去切换场景，这样看起来画面比较流畅
					changeScene = true
				end
				CCLuaLog(string.format("Sitdown，iTableNo=%d ,iSeatNo=%d ", data.iTableNo, data.iSeatNo));
		else
				CCLuaLog(string.format("Sitdown Fail，iTableNo=%d ,iSeatNo=%d , ErrorCode=%d ", data.iTableNo, data.iSeatNo, data.iRes));
				if (data.iRes==20) then
					MessageBox("坐下失败！","失败原因：该座位不存在！")
				elseif (data.iRes==30) then
					MessageBox("坐下失败！","失败原因：该座位已经有人啦！")
				end
		end
	-- 离开座位
	elseif (subcode==TABLE_SUB_LEAVE_SEAT) then
			data= tolua.cast(data,"LEAVE_SEAT")
			if(0==data.iRes)then
				CCLuaLog("leave.idx="..data.lUserId..",pUserIdx="..pUserIdx)
				pTableMgr:SwitchSitDownOrLeaveSeat(data.lUserId,data.iTableNo,data.iSeatNo,false)
				CCLuaLog(string.format("iTableNo=%d ,iSeatNo=%d，LeaveSeat ", data.iTableNo, data.iSeatNo));
			else
				CCLuaLog(string.format("LeaveSeat Fail,iTableNo=%d ,iSeatNo=%d，iRes=%d",data.iTableNo, data.iSeatNo,data.iRes));
				if (data.iRes==5 or data.iRes==10) then
					MessageBox("坐下失败！","失败原因：该座位不存在！")
				elseif (data.iRes==20) then
					MessageBox("坐下失败！","失败原因：该座位上还没有人坐呢！")
				end				
			end
	-- 开火
	elseif (subcode==TABLE_SUB_FIRE) then
		local pReal = tolua.cast(data,"SHOT_FIRE_RESULT")
			if(0==pReal.iRes)then
				CCLuaLog(string.format("%s Fire, iTableNo=%d ,iSeatNo=%d, iBulletNum=%d ",pReal.szName, pReal.iTableNo, pReal.iSeatNo, pReal.iBulletNum));
			else
				CCLuaLog(string.format("Fire Fail，ErrorCode=%d ", pReal.iRes));
			end
	-- 开火回复???
	elseif (subcode==RSP_USER_SHOOT) then
		local pReal = tolua.cast(data,"Rsp_UserShoot")
		if(0==pReal.iRes)then
			CCLuaLog(string.format("%s Fire, iTableNo=%d ,iSeatNo=%d, GunGrade=%d，BulletID=%d ",pReal.szName, pReal.TableID, pReal.ChairID, pReal.GunGrade,pReal.BulletID));
		else
			CCLuaLog(string.format("Fire Fail，ErrorCode=%d ", pReal.iRes));
		end

	elseif (subcode==RSP_ADD_ONE_FISH) then
		local pReal = tolua.cast(data,"Rsp_AddOneFish")
		CCLuaLog(string.format("鱼轨迹, 桌号%d 鱼种类%d，鱼标识%d，鱼轨迹类型%d ",pReal.TableID, pReal.FishKind, pReal.FishID,pReal.FishPathType))
		
		if not g_bInited then
			return
		end
		
		local StartPT = CCPoint(pReal.startP.x, pReal.startP.y)
		local arg1PT = CCPoint(pReal.arg1.x, pReal.arg1.y)
		local arg2PT = CCPoint(pReal.arg2.x, pReal.arg2.y)
		FishManage:addOneFish(pReal.FishKind, pReal.FishPathType, StartPT, arg1PT, arg2PT)
		
	elseif (subcode==RSP_ADD_ONE_FISH_ARR) then
		local pReal = tolua.cast(data,"Rsp_AddOneFish_Arr")
		CCLuaLog(string.format("鱼轨迹阵, 桌号%d 鱼轨迹阵类型%d，鱼数目%d ",pReal.TableID, pReal.FishGroupType,pReal.nFishCount))
		
		if not g_bInited then
			return
		end
		
		for i=0,pReal.nFishCount-1 do
			local StartPT = CCPoint(pReal.Arr[i].startP.x, pReal.Arr[i].startP.y)
			local arg1PT = CCPoint(pReal.Arr[i].arg1.x, pReal.Arr[i].arg1.y)
			local arg2PT = CCPoint(pReal.Arr[i].arg2.x, pReal.Arr[i].arg2.y)
			FishManage:addOneFish(pReal.Arr[i].FishKind, pReal.Arr[i].FishPathType, StartPT, arg1PT, arg2PT)
		end

	elseif (subcode==RSP_ADD_ONE_FISH_LIST) then
		local pReal = tolua.cast(data,"Rsp_AddOneFish_List")
		CCLuaLog(string.format("鱼轨迹阵, 桌号%d 鱼轨迹阵类型%d，鱼数目%d ",pReal.TableID, pReal.FishGroupType,pReal.nFishCount));		
		
		if not g_bInited then
			return
		end
		
		for i=0,pReal.nFishCount-1 do
			local StartPT = CCPoint(pReal.Arr[i].startP.x, pReal.Arr[i].startP.y)
			local arg1PT = CCPoint(pReal.Arr[i].arg1.x, pReal.Arr[i].arg1.y)
			local arg2PT = CCPoint(pReal.Arr[i].arg2.x, pReal.Arr[i].arg2.y)
			FishManage:addOneFish(pReal.Arr[i].FishKind, pReal.Arr[i].FishPathType, pReal.Arr[i].startP, pReal.Arr[i].arg1, pReal.Arr[i].arg2)
		end	
	else

	end
end

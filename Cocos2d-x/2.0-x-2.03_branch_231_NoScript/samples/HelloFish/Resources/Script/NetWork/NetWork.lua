--[[
------------------------------------
Socket业务逻辑脚本
------------------------------------
Cool.Cat@2013/4/18 16:58:01
------------------------------------
]]

pSocket = 0

function InitNetWork()
	CCLuaLog("InitNetWork...")
	pSocket = SIX_SocketClient:new(PROTOCOL.TCP)
	CCLuaLog("InitNetWork.pSocket="..tostring(pSocket))
	pSocket:Connect("110.76.47.206",80,5)
	CCLuaLog("InitNetWork...OK!")
	
--	-- test
--	local pMsg = MSG_INFO:new()
--	local text="你好"
--	pMsg:Creae(5,6,text,#text)
--	local pGlobalMgr = SIX_GlobalMgr:new()
--	pGlobalMgr:GetProxy():PushEvent(pMsg)
	
--	-- 登录请求
--	RequestLogin()
end

-- Send只负责new
-- 引擎内部会delete
function Send(mainCode,subCode,pData,pLen)
	local pMsg = MSG_INFO:new()
	pMsg:Creae(mainCode,subCode,pData,pLen)
	pSocket:PushMsg(pMsg)
end

-- 心跳
function HeartBeat()
	Send(NetEvent.MainCode.ONEWAY,NetEvent.SubCode.HEARTBEAT,0,0)
end

-- 登录
function RequestLogin()
	Send(NetEvent.MainCode.ONEWAY,NetEvent.SubCode.LOGIN,0,0)
end
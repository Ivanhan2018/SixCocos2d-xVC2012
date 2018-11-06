--[[
------------------------------------
 Lua<=>C++互调测试
------------------------------------
Cool.Cat@2013/3/26 17:54:09
------------------------------------
]]

function TestFunc()
	CCLuaLog("TestFunc...")
	
	local func = SIX_Func:new()
	CCLuaLog("Sum="..func:Sum(1,2))
	CCLuaLog("TEST_COMMON="..TEST_COMMON)
	
	local pInfo = SIX_Data:new()
	pInfo.a = 8
	pInfo.b = 123.456
	pInfo.c = CCString:create("你是：".."Cool.Cat?")
	
	-- 写
	local ret = func:SendData(pInfo)
	CCLuaLog("ret = "..ret)
	CCLuaLog("pInfo = {"..pInfo.a..","..pInfo.b..","..pInfo.c:getCString().."}")
	
	-- 读
	local pData = func:GetData()
	CCLuaLog("pData = {"..pData.a..","..pData.b..","..pData.c:getCString().."}")
	
	CCLuaLog("TestFunc...OK!")
end
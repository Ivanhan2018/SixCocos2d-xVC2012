--[[
------------------------------------
Http交互测试
------------------------------------
Cool.Cat@2013/4/2 16:46:12
------------------------------------
]]

function TestHttp()
	CCLuaLog("TestHttp...")

	local http = SIX_HTTP:new()
	http:Get("http://www.baidu.com")
	-- 如果要支持https协议，需重新编译Curl
	--http:Get("https://192.168.1.99:443/")
	
	CCLuaLog("TestHttp...OK!")
end

function onSuccessed(code,data,len)
	CCLuaLog("onSuccessed.code="..code..",data["..len.."]="..string.sub(data,0,MAX_LEN))
end

function onError(code,data,len)
	CCLuaLog("onError.code="..code..",data["..len.."]="..string.sub(data,0,MAX_LEN))
end
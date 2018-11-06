--[[
------------------------------------
场景管理器脚本
------------------------------------
Cool.Cat@2013/3/27 15:42:49
------------------------------------
]]

function LoadScene(folder,xmlPath)
	CCLuaLog("LoadScene...")
	
	local pGlobalMgr = SIX_GlobalMgr:new()
	pGlobalMgr:GetSceneMgr():SetSceneResourceFolder(folder)
	CCFileUtils:sharedFileUtils():setResourceDirectory(folder)
	pGlobalMgr:GetSceneMgr():LoadXMLFromFile(xmlPath)
	pGlobalMgr:GetSceneMgr():ReleaseXML()
	
	local total = pGlobalMgr:GetSceneMgr():GetTotalSceneCount()
	local preloadCount = pGlobalMgr:GetSceneMgr():GetPreloadSceneCount()
	CCLuaLog("Scene.Total["..total.."] , preload["..preloadCount.."]")
	
	-- 加载Loading场景
	if (initScene()==0) then
		CCLuaLog("LoadScene...Failed!")
		return 0
	end
	
	CCLuaLog("LoadScene...OK!")
end
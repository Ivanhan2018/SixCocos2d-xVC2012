--[[
------------------------------------
音乐管理器脚本
------------------------------------
Cool.Cat@2013/3/27 15:42:49
------------------------------------
]]

function LoadMusic(folder,xmlPath)
	CCLuaLog("LoadMusic...")
	
	local pGlobalMgr = SIX_GlobalMgr:new()
	pGlobalMgr:GetMusicMgr():SetSoundResourceFolder(folder)
	CCFileUtils:sharedFileUtils():setResourceDirectory(folder)
	pGlobalMgr:GetMusicMgr():LoadXMLFromFile(xmlPath)
	pGlobalMgr:GetMusicMgr():ReleaseXML()
	
	local total = pGlobalMgr:GetMusicMgr():GetTotalSoundCount()
	local soundCount = pGlobalMgr:GetMusicMgr():GetBgSoundCount()
	local effectCount = pGlobalMgr:GetMusicMgr():GetEffectSoundCount()
	CCLuaLog("Music.Total["..total.."] , BG["..soundCount.."] , Effect["..effectCount.."]")
	
	-- 随机背景音乐
	local maxbound = pGlobalMgr:GetMusicMgr():GetBgSoundCount()
	local UT = SIX_Utility:new()
	local rnd = UT:RNDNUM(0,maxbound-1)
	pGlobalMgr:GetMusicMgr():playBackgroundMusic(rnd,true);
	CCLuaLog("Using BG["..rnd.."] Now!")
	
	CCLuaLog("LoadMusic...OK!")
end
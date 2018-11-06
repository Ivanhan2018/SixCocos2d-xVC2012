--[[
----------------------------------
全局通用部分
------------------------------------
 Cool.Cat@2013/3/29 14:03:05
------------------------------------
]]

-- for CCLuaEngine traceback 输出绑定执行函数发生错误的信息  
function __G__TRACKBACK__(msg)
	CCLauLog("----------------------------------------")
	CCLauLog("LUA ERROR: " .. tostring(msg) .. "\n")
	CCLauLog(debug.traceback())
	CCLauLog("----------------------------------------")
end

function initScene()
	CCLuaLog("初始化场景...")
	
	local pGlobalMgr = SIX_GlobalMgr:new()
	CCFileUtils:sharedFileUtils():setResourceDirectory("Script")
	local pCurrentScene = pGlobalMgr:GetSceneMgr():changeScene(0)
	if (pCurrentScene==nil) then
		CCLuaLog("初始化场景...Failed!")
		return 0
	end
	
	local pDirector = CCDirector:sharedDirector();
	CCLuaLog("pCurrentScene["..tostring(pCurrentScene).."].runWithScene["..tostring(pCurrentScene:GetScene()).."]")
	pDirector:runWithScene(pCurrentScene:GetScene())
	
	CCLuaLog("初始化场景...OK!")
	return 1
end

function runScene(scendIdx,transitionScene,durTime)
	local errMsg = "scendIdx = "..scendIdx.." , transitionScene="..tostring(transitionScene).." , durTime = "..tostring(durTime)
	CCLuaLog(errMsg)
	
	local pGlobalMgr = SIX_GlobalMgr:new()
	CCFileUtils:sharedFileUtils():setResourceDirectory("Script")
	local pScene = pGlobalMgr:GetSceneMgr():changeScene(scendIdx)
	if (pScene==nil) then
		local errMsg = "runScene...Failed!"
		CCLuaLog(errMsg)
		return 0
	end

	-- 检查切换到的新场景是否存在
	-- Cool.Cat@2013/4/15 15:44:41
	if (pScene:GetScene()==nil) then
		CCLuaLog("pScene:GetScene().Nil!");
		return
	end
	
	local pDirector = CCDirector:sharedDirector();
	
	if (transitionScene=="CCTransitionJumpZoom") then
		pDirector:replaceScene( CCTransitionJumpZoom:create(durTime,pScene:GetScene()))
		
	elseif (transitionScene=="CCTransitionProgressRadialCCW") then
		pDirector:replaceScene( CCTransitionProgressRadialCCW:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionProgressRadialCW") then
		pDirector:replaceScene( CCTransitionProgressRadialCW:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionProgressHorizontal") then
		pDirector:replaceScene( CCTransitionProgressHorizontal:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionProgressVertical") then
		pDirector:replaceScene( CCTransitionProgressVertical:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionProgressInOut") then
		pDirector:replaceScene( CCTransitionProgressInOut:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionProgressOutIn") then
		pDirector:replaceScene( CCTransitionProgressOutIn:create(durTime,pScene:GetScene()))
		
	elseif (transitionScene=="CCTransitionCrossFade") then
		pDirector:replaceScene( CCTransitionCrossFade:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionPageForward") then
		pDirector:setDepthTest(true)
		pDirector:replaceScene( CCTransitionPageTurn:create(durTime,pScene:GetScene(),false))
	elseif (transitionScene=="CCTransitionPageBackward") then
		pDirector:setDepthTest(true)
		pDirector:replaceScene( CCTransitionPageTurn:create(durTime,pScene:GetScene(),true))	
	elseif (transitionScene=="CCTransitionFadeTR") then
		pDirector:replaceScene( CCTransitionFadeTR:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionFadeBL") then
		pDirector:replaceScene( CCTransitionFadeBL:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionFadeUp") then
		pDirector:replaceScene( CCTransitionFadeUp:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionFadeDown") then
		pDirector:replaceScene( CCTransitionFadeDown:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionTurnOffTiles") then
		pDirector:replaceScene( CCTransitionTurnOffTiles:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionSplitRows") then
		pDirector:replaceScene( CCTransitionSplitRows:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionSplitCols") then
		pDirector:replaceScene( CCTransitionSplitCols:create(durTime,pScene:GetScene()))
	
	elseif (transitionScene=="CCTransitionFade") then
		pDirector:replaceScene( CCTransitionFade:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCFadeWhiteTransition") then
		pDirector:replaceScene( CCTransitionFade:create(durTime,pScene:GetScene(),ccc3(255, 255, 255)))
	
	elseif (transitionScene=="CCFlipXLeftOver") then
		pDirector:replaceScene( CCTransitionFlipX:create(durTime,pScene:GetScene(),kOrientationLeftOver))
	elseif (transitionScene=="CCFlipXRightOver") then
		pDirector:replaceScene( CCTransitionFlipX:create(durTime,pScene:GetScene(),kOrientationRightOver))
	elseif (transitionScene=="CCFlipYUpOver") then
		pDirector:replaceScene( CCTransitionFlipY:create(durTime,pScene:GetScene(),kOrientationUpOver))
	elseif (transitionScene=="CCFlipYDownOver") then
		pDirector:replaceScene( CCTransitionFlipY:create(durTime,pScene:GetScene(),kOrientationDownOver))
	elseif (transitionScene=="CCFlipAngularLeftOver") then
		pDirector:replaceScene( CCTransitionFlipAngular:create(durTime,pScene:GetScene(),kOrientationLeftOver))
	elseif (transitionScene=="CCFlipAngularRightOver") then
		pDirector:replaceScene( CCTransitionFlipAngular:create(durTime,pScene:GetScene(),kOrientationRightOver))
	
	elseif (transitionScene=="CCZoomFlipXLeftOver") then
		pDirector:replaceScene( CCTransitionZoomFlipX:create(durTime,pScene:GetScene(),kOrientationLeftOver))
	elseif (transitionScene=="CCZoomFlipXRightOver") then
		pDirector:replaceScene( CCTransitionZoomFlipX:create(durTime,pScene:GetScene(),kOrientationRightOver))
	elseif (transitionScene=="CCZoomFlipYUpOver") then
		pDirector:replaceScene( CCTransitionZoomFlipY:create(durTime,pScene:GetScene(),kOrientationUpOver))
	elseif (transitionScene=="CCTransitionZoomFlipY") then
		pDirector:replaceScene( CCTransitionZoomFlipY:create(durTime,pScene:GetScene(),kOrientationDownOver))
	elseif (transitionScene=="CCZoomFlipAngularLeftOver") then
		pDirector:replaceScene( CCTransitionZoomFlipAngular:create(durTime,pScene:GetScene(),kOrientationLeftOver))
	elseif (transitionScene=="CCZoomFlipAngularRightOver") then
		pDirector:replaceScene( CCTransitionZoomFlipAngular:create(durTime,pScene:GetScene(),kOrientationRightOver))
	
	elseif (transitionScene=="CCTransitionShrinkGrow") then
		pDirector:replaceScene( CCTransitionShrinkGrow:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionRotoZoom") then
		pDirector:replaceScene( CCTransitionRotoZoom:create(durTime,pScene:GetScene()))
	
	elseif (transitionScene=="CCTransitionMoveInL") then
		pDirector:replaceScene( CCTransitionMoveInL:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionMoveInR") then
		pDirector:replaceScene( CCTransitionMoveInR:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionMoveInT") then
		pDirector:replaceScene( CCTransitionMoveInT:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionMoveInB") then
		pDirector:replaceScene( CCTransitionMoveInB:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionSlideInL") then
		pDirector:replaceScene( CCTransitionSlideInL:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionSlideInR") then
		pDirector:replaceScene( CCTransitionSlideInR:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionSlideInT") then
		pDirector:replaceScene( CCTransitionSlideInT:create(durTime,pScene:GetScene()))
	elseif (transitionScene=="CCTransitionSlideInB") then
		pDirector:replaceScene( CCTransitionSlideInB:create(durTime,pScene:GetScene()))
	end
	
	CCLuaLog("runScene...OK!")
	return 1
end
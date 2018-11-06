--[[
------------------------------------
金币 Class
------------------------------------
Cool.Cat@2013/4/2 16:46:12
------------------------------------
--]]

require "Script/Common/extern"

local l_Speed = 400							-- 金币移动速度

function Del(node)
	node:removeAllChildrenWithCleanup( true )
	node:removeFromParentAndCleanup( true )
end

function CountGold(goldValue)
	local gold = goldValue/100
	local silver = (goldValue - gold*100) / 10
	return gold,silver
end

function createOneGold(node, fishPT, PlayerPT, goldType, index, total)
	local pStrBuffer = string.format('gold_%02d_00000.png', goldType)
	local Sprite = CCSprite:createWithSpriteFrameName( pStrBuffer )
	local rcSize = Sprite:getContentSize()
	local Postion = CCPoint(fishPT.x - (rcSize.width-1)*total/2 + (rcSize.width-1)*index, fishPT.y - rcSize.height/2)
	-- 捕获鱼位置为中心点，横向排列，横向金币间距 -1
	Sprite:setPosition( Postion )
	
	local pArray = CCArray:create()
	for i=0,24 do
		local pStrBuffer = string.format('gold_%02d_%05d.png', goldType, i)
		local pSpriteFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( pStrBuffer )
		if not pSpriteFrame then
			break
		end
		pArray:addObject( pSpriteFrame )
	end
	Sprite:runAction( CCRepeatForever:create( CCAnimate:create( CCAnimation:createWithSpriteFrames( pArray, 0.09 ) ) ) )
	
	local JumpByAction = CCJumpBy:create(0.3, CCPointMake(0,150), 50, 1)
	local BounceOutMove = CCMoveTo:create( 0.9, CCPoint(Postion.x, Postion.y) )
	local BounceOut = CCEaseBounceOut:create(BounceOutMove)
	local fDistance = math.sqrt( math.pow(PlayerPT.x - fishPT.x,  2)  + math.pow(PlayerPT.y - fishPT.y,  2) ) -- 两点间距离
	local fTime = fDistance / l_Speed -- 金币动画需要的时间
	local pMove = CCMoveTo:create( fTime, PlayerPT )
	local pCallBack = CCCallFuncN:create(FinishAnimation)
	local ActionArray = CCArray:create()
	ActionArray:addObject(JumpByAction)
	ActionArray:addObject(BounceOut)
	ActionArray:addObject(pMove)
	ActionArray:addObject(pCallBack)
	ActionArray:addObject(CCCallFuncN:create( Del ))
	local SequenceRun = CCSequence:create(ActionArray)
	Sprite:runAction( SequenceRun )
	node:addChild( Sprite )
end

function showGold(goldValue, fishPT, PlayerPT)
	local node = pScene:getChildren():objectAtIndex(0)
	node = tolua.cast(node, "CCLayerColor")
	local gold,silver = CountGold( goldValue )
	
	for i=0,gold do
		createOneGold(node, fishPT, PlayerPT, 1, i, gold)
	end
	
	for i=0,silver do
		createOneGold(node, fishPT, PlayerPT, 2, i, silver)
	end
end
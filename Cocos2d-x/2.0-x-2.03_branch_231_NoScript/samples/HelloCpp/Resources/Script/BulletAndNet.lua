--[[
------------------------------------
子弹与网 Class
------------------------------------
Cool.Cat@2013/4/2 16:46:12
------------------------------------
--]]

require "Script/Common/extern"
require "Script/Gold" --tmp

local l_Bullet_Speed = 600			-- 子弹速度
local l_NetType = 1				-- 子弹类型
local l_NetSize = nil		-- 鱼网大小（宽，高）

function Stop(node)
	CBulletAndNetManage.s_BulletData[node] = nil
	node:removeAllChildrenWithCleanup( true )
	node:removeFromParentAndCleanup( true )
end

function FinishAnimation(node)
	node:stopAllActions()
	node:setVisible( false )

	-- 鱼网
	local pArray = CCArray:create()
	for i=0,24 do
		local strBuffer = string.format('FishNet_%02d_%05d.png',l_NetType, i)
		local pFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( strBuffer )
		if not pFrame then
			break
		end
		pArray:addObject( pFrame )
	end	
	local pAnimation = CCAnimation:createWithSpriteFrames( pArray, 0.05 )
	local pAnimate = CCAnimate:create( pAnimation )
	node:setAnchorPoint(CCPoint:new(0.5,0.5))

	-- 结束自己
	local BulletActionArray = CCArray:create()
	BulletActionArray:addObject(CCShow:create())
	BulletActionArray:addObject(pAnimate)
	BulletActionArray:addObject(CCCallFuncN:create( Stop ))
	node:runAction( CCSequence:create(BulletActionArray))
end

-- 获得两点外指定一个射程的坐标位置
function getRangePT(range, TouchPT, GunPT)
	local LocusAngle = math.atan2(TouchPT.y-GunPT.y, TouchPT.x-GunPT.x)
	local ptX = range*math.cos(LocusAngle)
	local ptY = range*math.sin(LocusAngle)
	return CCPoint(GunPT.x + ptX, ptY + GunPT.y)
end

function getRangePTEx(TouchPT, GunPT)
	local winSize = CCDirector:sharedDirector():getWinSize()
	local rangeLenght = math.sqrt(winSize.width*winSize.width + winSize.height * winSize.height) -- 取得斜角长度
	local RangePT = getRangePT(rangeLenght,TouchPT, GunPT)
		
	return RangePT
end

CBulletAndNet = class("CBulletAndNet", function(filename)
		return CCSprite:createWithSpriteFrameName( filename ) end)

CBulletAndNet.__index = CBulletAndNet

function CBulletAndNet:BulletAndNetWithTexture(filename)

    if(filename == nil) then
        cclog("in BulletAndNetWithTexture file == nil")
    end
    return CBulletAndNet.new(filename)
end


-- 子弹与墙壁碰撞刷新检测
function UpdateBullet()
	local winSize = CCDirector:sharedDirector():getWinSize()
	local allBullet = CBulletAndNetManage:sharedBullet():getChildren()
	local index = 0
	local object = nil
	
	while allBullet and index < allBullet:count() do
		object = allBullet:objectAtIndex( index )
		object = tolua.cast(object, "CCSprite")
		index = index + 1
		--CCLuaLog("UpdateBullet----------- "..tostring(object)..",time="..SIX_Utility:new():GetTickCount()..",x="..object.x..",y="..object.y)
		
		if object then
			local startPT = object:getUserData()	-- 子弹运动的起点
			startPT = tolua.cast(startPT, "CCPoint")

			if object.x < 0 or object.x >  winSize.width or object.y < 0 or object.y > winSize.height then
				-- 先计算边界碰撞点
				local collidePT = segment_cross_Rect(CCPoint(0,0), CCPoint(0,winSize.height),CCPoint(winSize.width,winSize.height),CCPoint(winSize.width,0),   CCPoint(startPT.x, startPT.y), CCPoint(object.x,object.y), 10)
				--计算法线向量
				local Direction=getReflex(CCPoint(0,0), CCPoint(0,winSize.height),CCPoint(winSize.width,winSize.height),CCPoint(winSize.width,0),   CCPoint(startPT.x, startPT.y), CCPoint(object.x,object.y), 10)
				--CCLuaLog("UpdateBullet----------- into pt startPT =("..startPT.x..","..startPT.y..") object =("..object.x..","..object.y..") collidePT =("..collidePT.x..","..collidePT.y..") Direction =("..Direction.x..","..Direction.y..")")--del

				-- 再计算下一个反射方向
				local newPT = CCPoint(0,0)
		        local v3 = 2 * math.atan2(Direction.y, Direction.x) - math.atan2(collidePT.y-startPT.y,collidePT.x-startPT.x)
		        if Direction.x==0 and Direction.y==0 then
		            collidePT.x=object.x
		            collidePT.y=object.y
		            if object.x < 0 then
		               collidePT.x=0
		            elseif object.x >  winSize.width then
		               collidePT.x=winSize.width
		            end

		            if object.y < 0 then
		               collidePT.y=0
		            elseif object.y > winSize.height then
		               collidePT.y=winSize.height
		            end
            		v3 =math.atan2(collidePT.y-startPT.y,collidePT.x-startPT.x)+math.pi                
				end
				newPT = CCPoint(10000*math.cos(v3), 10000*math.sin(v3))

				local fDistance =math.sqrt( math.pow(newPT.x,  2)  + math.pow(newPT.y,  2) ) 
				local fTime = fDistance / l_Bullet_Speed -- 子弹需要时间
				local pMove = CCMoveBy:create(fTime, newPT)
				local PlayUpDown = CBulletAndNetManage.s_BulletData[object]["Direction"]
				local Rotation = (math.pi*((0==PlayUpDown and 3) or 1)/2-math.atan2(newPT.y, newPT.x))*180/math.pi
				--CCLuaLog("UpdateBullet----------- into pt BulletID="..CBulletAndNetManage.s_BulletData[object]["BulletId"].."  newPT =("..newPT.x..","..newPT.y..") ; PlayUpDown = "..PlayUpDown)
				
				object:setPosition( collidePT )
				object:setUserData( CCPoint:new(collidePT.x, collidePT.y) )
				object:setRotation( Rotation )
				object:stopAllActions()
				object:runAction( pMove )
			end
		end
	end -- end while
end

--[[
---------------------------------------------------------------------------------------------------------
-- 子弹与网格管理类
--]]

CBulletAndNetManage = class("CBulletAndNetManage")
CBulletAndNetManage.__index = CBulletAndNetManage
CBulletAndNetManage.m_LastShootTime = 0				-- 上次发射时间
CBulletAndNetManage.m_Max_Shoot_Delay = 150		-- 子弹发射间隔
CBulletAndNetManage.s_AllBullet = nil -- CCSpriteBatchNode 类型 所有子弹
CBulletAndNetManage.s_BulletData = {} -- table 类型 子弹携带数据

function CBulletAndNetManage:Init(pNode)
	self.m_LastShootTime = SIX_Utility:new():GetTickCount()
	self.s_AllBullet = CCSpriteBatchNode:create( CCString:create( "Scene/Game/GunBulletGold.png" ):getCString() )
	pNode:addChild( self.s_AllBullet )
	
	self:setNetType( l_NetType )
end


function CBulletAndNetManage:Release()
	if (self.s_AllBullet~=nil) then
		self.s_AllBullet:removeAllChildrenWithCleanup( true )
	end
end

function CBulletAndNetManage:Shoot(UserID, BulletID, ptTouch, ptGun, fRotation, RepeatShoot, GunType)
	if NULL == self.s_AllBullet then
		CCLuaLog("请先调用 CBulletAndNetManage:Init(...) 函数！")
		return
	end
	
	-- 子弹间隔延迟控制
	local dwNow = SIX_Utility:new():GetTickCount()
	if not RepeatShoot and dwNow < CBulletAndNetManage.m_LastShootTime + self.m_Max_Shoot_Delay then
		return
	end
	CBulletAndNetManage.m_LastShootTime = dwNow

	local ptMuzzle = self:CountTwoPointOneCoordinate(ptTouch, ptGun, 120)	-- 计算枪口位置
	local BulletPath = string.format("bullet_%02d_00000.png", l_NetType)
	local pBullet = CBulletAndNet:BulletAndNetWithTexture( BulletPath )
	local RangePT = getRangePTEx(ptTouch, ptGun) -- 加上射程后的子弹目的地
	pBullet:setRotation( fRotation )
	pBullet:setAnchorPoint(CCPoint(0.5, 1.0))
	pBullet:setPosition( ptMuzzle )
	pBullet:setUserData( CCPoint:new(ptGun.x, ptGun.y) )
	
	CBulletAndNetManage.s_BulletData[pBullet] = {}
	CBulletAndNetManage.s_BulletData[pBullet]["BulletId"] = BulletID
	CBulletAndNetManage.s_BulletData[pBullet]["UserID"] = UserID
	CBulletAndNetManage.s_BulletData[pBullet]["Direction"] = getPlayerDirection( UserID )
	CBulletAndNetManage.s_BulletData[pBullet]["IsCatching"] = false
	
	if 0 == getPlayerDirection(UserID) then
		pBullet:setFlipY( true )
		pBullet:setAnchorPoint(CCPoint(0.5, 0.0))
	end
	
	local noRange = true -- 无射程
	if noRange then
		ptTouch = RangePT
	end
	
	local fDistance = math.sqrt( math.pow(ptTouch.x - ptMuzzle.x,  2)  + math.pow(ptTouch.y - ptMuzzle.y,  2) ) -- 两点间距离
	local fTime = fDistance / l_Bullet_Speed -- 子弹需要时间
	local pMove = CCMoveTo:create(fTime, ptTouch)
	--CCLuaLog("ptMuzzle="..ptMuzzle.x.."/"..ptMuzzle.y..",RangePT="..RangePT.x.."/"..RangePT.y)
	local BulletActionArray = CCArray:create()
	BulletActionArray:addObject(pMove)

	if noRange then
		local pCallBack = CCCallFuncN:create( FinishAnimation )
		BulletActionArray:addObject(pCallBack)
	end
	local pBulletRun = CCSequence:create(BulletActionArray)
	pBullet:runAction( pBulletRun )

	local pArray = CCArray:create()
	for i=0,24 do
		local pStrBuffer = string.format('bullet_%02d_%05d.png',l_NetType, i)
		local pSpriteFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( pStrBuffer )
		if not pSpriteFrame then
			break
		end
		pArray:addObject( pSpriteFrame )
	end
	
	if 1==GunType then
		pBullet:setScale(0.5)
	elseif 2==GunType then
		pBullet:setScale(0.6)
	elseif 3==GunType then
		pBullet:setScale(0.7)
	elseif 4==GunType then
		pBullet:setScale(0.9)
	elseif 5==GunType then
		pBullet:setScale(1.0)
	else
		pBullet:setScale(1.2)
	end
	
	pBullet:runAction( CCRepeatForever:create( CCAnimate:create( CCAnimation:createWithSpriteFrames( pArray, 0.5 ) ) ) )
	self.s_AllBullet:addChild( pBullet )
	
	--showGold(500, ptTouch, ptGun) --tmp
end

function CBulletAndNetManage:sharedBullet()
--	if nil == self.s_AllBullet then
--		CCLuaLog("请先调用 CBulletAndNetManage:Init(...) 函数！")
--		return nil
--	end

	return self.s_AllBullet;
end

function CBulletAndNetManage:CountTwoPointOneCoordinate(ptSrc, ptDes, fLenght)
	if (ptSrc.x == ptDes.x  and  ptSrc.y == ptDes.y) then
		return ptDes
	end

	local fDistance = math.sqrt( math.pow(ptSrc.x - ptDes.x,  2)  + math.pow(ptSrc.y - ptDes.y,  2) ) -- 两点间距离
	local fT = (fDistance - fLenght) / fDistance;
	local ptResult = CCPoint:new((1-fT) * ptSrc.x + fT * ptDes.x,  (1-fT) * ptSrc.y + fT * ptDes.y)
	
	return ptResult
end

function CBulletAndNetManage:AccelerometerKeyHook(MSG,wParam,lParam)
	if Enum_KeyBord.WM_KEYUP ~= MSG then
		return
	end
	
	local Key = tonumber(wParam)
	if PRESS_KEY[KEY_WPARAM.VK_CONTROL] then
		if 49<=Key and 54>=Key then
			Key = Key-49+1
		elseif KEY_WPARAM.VK_NUMPAD1<=Key and KEY_WPARAM.VK_NUMPAD6>=Key then
			Key = Key-KEY_WPARAM.VK_NUMPAD1+1
		end
		
		if 1==Key then
			self:setNetType( 1 )
		else
			self:setNetType( 2 )
		end
	end
end

function CBulletAndNetManage:setNetType(NetType)
	l_NetType = NetType
	
	local strBuffer = string.format('FishNet_%02d_00000.png',l_NetType)
	local pFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( strBuffer )
	local SpriteNet = CCSprite:createWithSpriteFrame( pFrame )
	SpriteNet = tolua.cast(SpriteNet, "CCNode")
	l_NetSize = SpriteNet:getContentSize()
end

function CBulletAndNetManage:getNetSize()
	return l_NetSize
end
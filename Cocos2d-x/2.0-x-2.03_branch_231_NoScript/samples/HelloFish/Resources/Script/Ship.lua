--[[
------------------------------------
船 Class
------------------------------------
Cool.Cat@2013/4/2 16:46:12
------------------------------------
--]]

require "Script/Common/extern"


local l_ShipTag={100,101,102,103}							-- xml中的船精灵，tag值
local l_PlayCount = 4													-- 玩家数目
local l_EmptySeat={false,false,false,false} 	-- 空座位
local l_TouchPT = CCPoint(0,0)								-- 鼠标位置(实时)
local l_MyUserID = -1													-- 玩家自己的ID


function getShipObject(Parent,shipIndex)
	return Parent:getChildByTag(l_ShipTag[shipIndex])
end

CShip = class("CShip", getShipObject)
CShip.__index = CShip
CShip.m_UserID = -1
CShip.m_seatIndex = 0
CShip.m_shipSprite = nil
CShip.m_gunSprite = nil

CShip.m_gun = {
m_gunOffestY = 19,											-- 炮Y轴相对船偏移 19 像素
m_curGunType = 3,												-- 当前炮类型
m_initGunPt = false,										-- 初始化炮位置
m_completeWhirlGun = true,							-- 旋转炮完成
m_unfinishedPT = CCPoint(0,0),					-- 旋转过程中未处理的坐标
}


function CShip:Enter(Parent, UserID, isMyself)
	local shipIndex = -1

	if isMyself then
		l_MyUserID = UserID
	end
	
	for k,v in ipairs(l_EmptySeat) do
		if not v and (not isMyself or (isMyself and k>l_PlayCount/2)) then
			shipIndex = k
			break
		end
	end
		
	if -1 == shipIndex then
		CCLuaLog("error no seats! -- CShip:Enter(),UserID = "..UserID)
		return
	end
	
	local newShip = CShip.new(Parent,shipIndex)
	local filePath = string.format("gun_03_00000.png")
	local SpriteFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( filePath )
	newShip.m_UserID = UserID
	newShip.m_seatIndex = shipIndex
	newShip.m_shipSprite = Parent:getChildByTag( l_ShipTag[newShip.m_seatIndex] )
	newShip.m_shipSprite = tolua.cast(newShip.m_shipSprite, "CCSprite")
	newShip.m_shipSprite:setVisible( true )	
	
	newShip.m_gunSprite = newShip.m_shipSprite:getChildByTag(10)
	newShip.m_gunSprite:setUserData(newShip)
	newShip.m_gunSprite = tolua.cast(newShip.m_gunSprite, "CCSprite")
	newShip.m_gunSprite:setDisplayFrame( SpriteFrame )
	
	l_EmptySeat[shipIndex] = newShip
end

function CShip:Leave( node, UserID )
	l_EmptySeat[self.m_seatIndex] = false
	self.m_shipSprite:setVisible( false )
end


-- 旋转炮管至指定坐标
function CShip:onWhirlGun(TouchPT)	
	self.m_gun.m_unfinishedPT = TouchPT
	if not self.m_gun.m_completeWhirlGun then
		return
	end

	if (self.m_shipSprite==nil) then
		return
	end
	self.m_shipSprite = tolua.cast(self.m_shipSprite, "CCSprite")
	self.m_gunSprite = tolua.cast(self.m_gunSprite, "CCSprite")
	-- 船 m_shipSprite 的宽高分别是 （99,184)，且锚点为(0.5,0.5) 见SceneGame.xml，炮管是船的子结点
	-- 因此先计算出船的起始点，再加上炮管的偏移位置 得出坐标系内炮管坐标
	local newGunX = self.m_shipSprite:getPositionX() - 99/2 + self.m_gunSprite:getPositionX()
	local newGunY = self.m_shipSprite:getPositionY() - 184/2 + self.m_gunSprite:getPositionY()
	
	-- Y轴固定，因此X轴没变化直接返回
	if TouchPT.x == newGunX then
		return
	end
	
	local angle = (TouchPT.y - newGunY)/(TouchPT.x - newGunX)
	angle = math.atan(angle)/math.pi*180
	
	
	--CCLuaLog("onMultiTouch.x-----start["..TouchPT.x.."].y["..TouchPT.y.."] angle["..angle.."] newGunX="..newGunX.."newGunY="..newGunY)
	if 2==getPlayerDirection(self.m_UserID) then		
		if 0==angle and TouchPT.x<newGunX then
			angle = -(90+angle)
		else
			angle = ((0>angle) and (-(90+angle))) or 90-angle
		end
		
		-- 单击炮水平线以下(下排玩家)，以上（上排玩家），旋转90，-90
		if TouchPT.y < newGunY then
			angle = ((TouchPT.x>= newGunX) and 90) or -90
			TouchPT.y = newGunY
		end
		
	else
	
		if 0==angle and TouchPT.x>newGunX then
			angle = -(90+angle)
		else
			angle = ((0>angle) and (-(90+angle))) or 90-angle
		end
		
		if TouchPT.y > newGunY then
			angle = ((TouchPT.x>= newGunX) and -90) or 90
			TouchPT.y = newGunY
		end
	end
		
	--CCLuaLog( string.format("edit onMultiTouch pt(%d,%d) angle=%d", TouchPT.x,TouchPT.y, angle) )
	local gun = self.m_gunSprite		
	gun = tolua.cast(gun, "CCSprite")
	local OldAngle = gun:getRotation()
	OldAngle = OldAngle-angle
	if 90 <= OldAngle or -90 >= OldAngle then
		local RotateAction = CCRotateTo:create(0.2, angle)
		self.m_gun.m_completeWhirlGun = false
		
		local CallAction = CCCallFuncN:create( onWhirlGunComplete )
		gun:runAction(CCSequence:createWithTwoActions(RotateAction, CallAction))
	else
		gun:setRotation( angle )
	end
end

-- 切换炮管
function CShip:AccelerometerKeyHook(MSG,wParam,lParam)
	if Enum_KeyBord.WM_KEYUP ~= MSG  or PRESS_KEY[KEY_WPARAM.VK_CONTROL] then
		return
	end
	
	local Key = tonumber(wParam)
	if 49<=Key and 54>=Key then
		Key = tonumber(wParam) - 49 + 1 -- 数字键 49《=》57（ASCII 十进制）开始
	elseif KEY_WPARAM.VK_NUMPAD1<=Key and KEY_WPARAM.VK_NUMPAD6>=Key then
		Key = tonumber(wParam) - 97 + 1 -- 小键盘数字键 97《=》105（ASCII 十进制）开始
	else
		return
	end
	
	local ImgPath = string.format("gun_%02d_00000.png",Key)
	local SpriteFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( ImgPath );
	local bg = pScene:getChildren():objectAtIndex(0)
	self.m_gunSprite:stopAllActions() -- 动画会阻止炮管修改属性
	self.m_gunSprite:setDisplayFrame(SpriteFrame)
	self.m_gun.m_curGunType = Key
	
	local ScaleToAction = CCScaleTo:create(0.2, 1.1)
	ScaleToAction = tolua.cast(ScaleToAction, "CCActionInterval")
	local ScaleToActionReverse = CCScaleTo:create(0.3, 1)
	self.m_gunSprite:runAction( CCSequence:createWithTwoActions(ScaleToAction, ScaleToActionReverse) )
end


-- 连续发射子弹
function CShip:onRepeatShootBullet( IsShoot )
	local bg = pScene:getChildren():objectAtIndex(0)
	bg = tolua.cast(bg, "CCLayerColor")
	
	if IsShoot then
		schedule(bg, onCallFucRepeatShootBullet, 0.2)
	else
		self.m_gunSprite:stopAllActions()
		bg:stopAllActions()
	end
end

-- 发射子弹
function CShip:onShootBullet( TouchPT, RepeatShoot )
	local ShootPT = TouchPT
	if self.m_UserID == l_MyUserID then
		ShootPT = l_TouchPT
	end
	
	if not self.m_gun.m_completeWhirlGun then
		return
	end
	
	-- 炮管的中心点：中心点 x轴等于船的中心点，y轴等于船中心点偏移 m_gunOffestY 像素
	-- CCSprite子结点的起点是(0,0),炮管与船都是精灵
	local gunPosition = CCPoint(self.m_shipSprite:getPositionX(), self.m_shipSprite:getPositionY())	
	if 0 == getPlayerDirection(self.m_UserID) then
		gunPosition.y = gunPosition.y - self.m_gun.m_gunOffestY
		
		if ShootPT.y > gunPosition.y then
			ShootPT.y = gunPosition.y
		end
	else
		gunPosition.y = gunPosition.y + self.m_gun.m_gunOffestY
		
		if ShootPT.y < gunPosition.y then
			ShootPT.y = gunPosition.y
		end
	end
	
	local gunAction = CCArray:create()
	for i=0,24 do
		local strPath = string.format("gun_%02d_%05d.png",self.m_gun.m_curGunType,i)
		local SpriteFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName(strPath)
		if not SpriteFrame then
			break
		end
		
		gunAction:addObject( SpriteFrame )
	end
	local GunAnimation = CCAnimation:createWithSpriteFrames(gunAction, 0.06)
	--GunAnimation:setRestoreOriginalFrame( true )
	self.m_gunSprite:runAction(CCAnimate:create(GunAnimation))
	
	CBulletAndNetManage:Shoot(self.m_UserID, 0, ShootPT, gunPosition, self.m_gunSprite:getRotation(), RepeatShoot, self.m_gun.m_curGunType)
end

------------------------------------
-- 公共的
--
-- 更新鼠标位置
function onUpdateMousePT( pt )
	l_TouchPT = pt
end
function getShip(UserID)
	for k,v in ipairs(l_EmptySeat) do
		repeat
		if not v then
			break
		end
		
		if v.m_UserID == UserID then
			return  l_EmptySeat[k]
		end
		until true
	end
end

-- 获取自己
function getMySelfShip()
	return getShip(l_MyUserID)
end

-- 获得玩家方向
function getPlayerDirection(UserID)
	local ship = getShip( UserID )
	
	-- 上右下左分别是0,1,2,3
	if 1==ship.m_seatIndex or 2==ship.m_seatIndex then
		return 0
	elseif 3==ship.m_seatIndex or 4==ship.m_seatIndex then
		return 2
	end
end

-- 连续子弹发射回调
function onCallFucRepeatShootBullet()
	getMySelfShip():onShootBullet(l_TouchPT, true)
end

-- 旋转炮管动画
function onWhirlGunComplete(gun)	
	local ship = gun:getUserData()
	ship = tolua.cast(ship, "CCNode")
	
	ship.m_gun.m_completeWhirlGun = true
	ship:onWhirlGun(ship.m_gun.m_unfinishedPT)
end
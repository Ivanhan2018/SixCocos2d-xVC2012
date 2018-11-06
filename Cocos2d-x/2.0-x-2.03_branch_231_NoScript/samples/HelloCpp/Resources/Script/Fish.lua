--[[
------------------------------------
一条鱼
------------------------------------
Ivan_han@2013/4/16 11:08:17
------------------------------------
]]
require "Script/Trace/Curve"

function CreateObj(pSpriteFrame)
    return CCSprite:createWithSpriteFrame(pSpriteFrame)
end

Fish = class("Fish", CreateObj)

Fish.__index = Fish
--Fish.fishType=1

CCLuaLog("Fish...................."..tostring(Fish.__index))

function Fish:spriteWithSpriteFrame(pSpriteFrame)
    local fish = Fish.new(pSpriteFrame)
    if (fish~=nil)then
		  fish:autorelease()
          fish:retain()
	end
	return fish
end

function Fish:spriteWithSpriteFrameName(pszSpriteFrameName)
    if(pszSpriteFrameName == nil) then
        CCLuaLog("Fish.spriteWithSpriteFrameName.pszSpriteFrameName.Nil!")
        return nil
    end
    local pFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName(pszSpriteFrameName)
    if (pFrame~=nil)then
		return self:spriteWithSpriteFrame(pFrame)
	end
end

function Fish:randomCatch(level)
	local rnd = SIX_Utility:new():RNDNUM(0,9)
	if(rand >= level) then
        return true
    end
    return false
end


--[[
三阶贝塞尔曲线（P_0,P_1,P_2,P_3）退化为二阶贝塞尔曲线（P_0,P_1,P_2，即抛物线：起点P_0=控制点P_1,控制点P_2,终点P_3）
参数说明：
startP----轨迹起点
endP----轨迹终点
startAngle----
endAngle----
time----动画时长
]]
function Fish:moveWithParabola(startP,endP,startAngle,endAngle,time)
	local sx = startP.x;
	local sy = startP.y; 
	local ex =endP.x;
	local ey =endP.y;

	local h = self:getContentSize().height * 0.5;
	local pos=CCPoint(sx,sy);
	self:setPosition(pos);
	self:setRotation(startAngle);

	-- 贝塞尔曲线
	local bezier=ccBezierConfig:new();
	-- 控制点1(起点)
	bezier.controlPoint_1 = ccp(sx, sy);
	-- 控制点2
	--bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5);
	bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+100);	
	-- 终点
	bezier.endPosition = ccp(endP.x, endP.y);

	local actionMove = CCBezierTo:create(time, bezier);
	local actionRotate = CCRotateTo:create(time, endAngle);
	local action = CCSpawn:createWithTwoActions(actionMove, actionRotate)
	local pcc=CCCallFuncN:create( SpriteRemoveCallBack )
	local sq = CCSequence:createWithTwoActions(action,pcc)
	self:runAction(sq);
end





--[[
具体的运动轨迹由轨迹类型、轨迹起点坐标、轨迹速度等相互独立的参数来控制
参数说明：
pathType--轨迹类型
1表示直线轨迹，额外参数arg1表示轨迹方向，例如pathType=1，arg1=ccp(1500,1500)表示右上角45度直线轨迹；pathType=1，arg1=ccp(1500,0)表示水平向右直线轨迹
2表示圆轨迹
3表示摆线轨迹，额外参数arg1代表半径和辐角主值增量，额外参数arg2代表摆线轨迹方向
arg1--第一个额外参数，直线轨迹、圆轨迹、摆线轨迹要用到
arg2--第二个额外参数，摆线轨迹要用到
]]
function Fish:addPath(pathType,arg1,arg2)
if(pathType==1)then
   --给定轨迹起点和恒定速度矢量（恒定速率和恒定方向）的匀速直线运动
   --对于直线轨迹，arg1代表直线轨迹方向，例如ccp(1500,1500)代表右上角45度直线轨迹，ccp(1500,0)代表水平向右直线轨迹
   if(arg1==nil)then
      arg1=CCPoint(1500,0);
  end
    --根据鱼帧资源中的鱼头部方向和鱼轨迹方向设置顺时针旋转角度（角度制）
    local angle=(qrArg(self:getTag())-math.atan2(arg1.y,arg1.x))*180/math.pi
    self:setRotation(angle);
	local actionMove = CCMoveBy:create(15.0,arg1);
    --在轨迹时长内，鱼精灵对象会删除自身
	local pcc=CCCallFuncN:create( SpriteRemoveCallBack )
	local sq = CCSequence:createWithTwoActions(actionMove, pcc)
	self:runAction(sq);
end
if(pathType==2)then
  local startP=CCPoint(self:getPositionX(),self:getPositionY());
  --对于圆轨迹，arg1代表圆心坐标
   if(arg1==nil)then
      arg1=CCPoint(self:getPositionX()-150,self:getPositionY());
  end    
  self:runAction(myAction:createCircle(60.0,"CircleTraceFunc",startP,arg1,20));
--[[
  local startP=CCPoint(self:getPositionX(),self:getPositionY());
  --对于圆轨迹，arg1代表圆心坐标
   if(arg1==nil)then
      arg1=CCPoint(self:getPositionX()+150,self:getPositionY());
  end 
  --对径点P
   local P=CCPoint(arg1.x*2-self:getPositionX(),arg1.y*2-self:getPositionY()); 
   local  actionBy = CircleAction:create(5.0,P,1);
   local  ac = CCRepeatForever:create(actionBy);
   self:runAction(ac);

   --圆顺时针运动轨迹，参数一为动画时长，参数二为当前圆上位置的对径点坐标，参数三为轨迹方向
   self:runAction(CircleAction:create(3.0, ccp(500,300),-1));  
]]   
end 
if(pathType==3)then
--[[
    --去掉了createMoveCircle，用createCycloid代替  
   local  actionBy =myAction:createCycloid(3.0,"CycloidTraceFunc",ccp(200,300),ccp(50,0),3,ccp(-50,math.pi*0.25));
   local  ac = CCRepeatForever:create(actionBy);
   self:runAction(ac);
   ]]
   local startP=CCPoint(self:getPositionX(),self:getPositionY());
  --对于摆线轨迹，arg1代表半径和辐角主值增量
    if(arg1==nil)then
       arg1=CCPoint(50,0);
   end
   --对于摆线轨迹，arg2.y代表摆线轨迹方向  
   if(arg2==nil)then
       arg2=ccp(0,math.pi);
   end  
    local angle=(qrArg(self:getTag())-arg2.y)*180/math.pi
    self:setRotation(angle);
	local actionMove = myAction:createCycloid(15.0,"CycloidTraceFunc",startP,arg1,3,arg2)
	local pcc=CCCallFuncN:create( SpriteRemoveCallBack )
	local sq = CCSequence:createWithTwoActions(actionMove,pcc)
	self:runAction(sq);   
end
if(pathType==4)then
   --自定义运动轨迹，参数一为动画时长，参数二为表示轨迹参数方程的LUA函数名
   --self:runAction(myAction:create(3.0,"SinTrace"));
   local angle=(qrArg(self:getTag())-0)*180/math.pi
   self:setRotation(angle);
    --创建一个先加速再减速的正弦曲线轨迹运动
   --local pAction=myAction:create(3.0,"SinTrace");
   --local pAction=myAction:create(3.0,"Trace_1_8_1");
   --local pAction=myAction:create(3.0,"Trace_1_8_2");  
   --local pAction=myAction:create(3.0,"Trace_1_8_3");
   --local pAction=myAction:create(3.0,"Trace_1_12_1");
   --local pAction=myAction:create(3.0,"Trace_1_12_2");  
   --local pAction=myAction:create(3.0,"Trace_1_12_3");
   --local pAction=myAction:create(3.0,"Trace_1_9_1");
   --local pAction=myAction:create(3.0,"Trace_1_9_2");
   --local pAction=myAction:create(3.0,"Trace_1_9_3");
   --local pAction=myAction:create(3.0,"Trace_9_1_1");
   --local pAction=myAction:create(3.0,"Trace_9_1_2");
   --local pAction=myAction:create(3.0,"Trace_9_1_3");
   --local pAction=myAction:create(3.0,"Trace_9_1_4");
   --local pAction=myAction:create(3.0,"Trace_9_16_1");
   --local pAction=myAction:create(3.0,"Trace_9_16_2");
   --local pAction=myAction:create(3.0,"Trace_9_16_3");
   local pAction=myAction:create(3.0,"Trace_9_16_4");   
   local move_ease_inout = CCEaseInOut:create(pAction,2);
   self:runAction(move_ease_inout);   
end
if(pathType==5)then
   self:moveWithParabola(ccp(200, 300), ccp(500, 300), 0.0, 20.0, 3.0);
end     
end

--[[
------------------------------------
鱼精灵对象用到的精灵帧的管理
------------------------------------
Ivan_han@2013/4/20 14:15:17
------------------------------------
]]
function CreateFishManage()
	return CCNode:create()
end

FishManage = class("FishManage",CreateFishManage)
FishManage.__index = FishManage
FishManage.__pNode = nil
FishManage.mFishData = {} -- 鱼携带数据
FishManage.s_AllFish ={[1]=nil,[2]=nil,[3]=nil,[4]=nil,[5]=nil,[6]=nil,[7]=nil,[8]=nil,[9]=nil,[10]=nil,[12]=nil,[15]=nil,[18]=nil,[20]=nil,[25]=nil,[30]=nil,[40]=nil}
--1-10号炸弹对应1-10号鱼，11号炸弹是全屏炸弹，12号炸弹是龙虾炸弹

FishManage.s_AllBomb ={[1]=nil,[2]=nil,[3]=nil,[4]=nil,[5]=nil,[6]=nil,[7]=nil,[8]=nil,[9]=nil,[10]=nil,[11]=nil,[12]=nil, ["Dead"]=nil}

--鱼的头部朝向
s_AllFishArg={[1]=math.pi,[2]=math.pi,[3]=math.pi,[4]=math.pi,[5]=math.pi,[6]=math.pi,[7]=math.pi,[8]=math.pi,[9]=math.pi,[10]=math.pi*0.5,[12]=math.pi,[15]=math.pi,[18]=math.pi,[20]=math.pi,[25]=math.pi,[30]=math.pi,[40]=math.pi}
--炸弹的头部朝向
s_AllBombArg={[1]=math.pi,[2]=math.pi,[3]=math.pi,[4]=math.pi,[5]=math.pi,[6]=math.pi,[7]=math.pi,[8]=math.pi,[9]=math.pi,[10]=math.pi,[11]=0,[12]=math.pi}


function FishManage:LoadBatchFish()
	local arr={1,2,3,4,5,6,7,8,9,10,12,15,18,20,25,30,40}
	for i=1,#arr do
		local fishType=arr[i]	
		local pStrBuffer = string.format('Scene/Game/FishAndBomb/Fish_%02d.png', fishType)	
		local pBatchName = CCString:create(pStrBuffer)
		self.s_AllFish[fishType] = CCSpriteBatchNode:create( pBatchName:getCString() )
		self.__pNode:addChild( self.s_AllFish[fishType]);
		pBatchName:release()
	end
end

function FishManage:LoadBatchBoom()
	-- 死亡炸弹
	FishManage.s_AllBomb["Dead"] = CCSpriteBatchNode:create( CCString:create("Scene/Game/FishAndBomb/DeadBomb.png"):getCString() )
	self.__pNode:addChild( FishManage.s_AllBomb["Dead"] )
	
  local arr1={1,2,3,4,5,6,7,8,9,10,11,12}
	for i=1,#arr1 do
		local BombType=arr1[i]
    local pStrBuffer = string.format('Scene/Game/FishAndBomb/Bomb_%02d.png', BombType)
    local pBatchName = CCString:create(pStrBuffer)
    self.s_AllBomb[BombType] = CCSpriteBatchNode:create( pBatchName:getCString() )
    self.__pNode:addChild( self.s_AllBomb[BombType] )
		pBatchName:release()
	end
end
	
function FishManage:Init(pNode)
	-- save parent node
	self.__pNode = pNode
	self:LoadBatchBoom()
	self:LoadBatchFish()
end

function FishManage:Release()
    local arr={1,2,3,4,5,6,7,8,9,10,12,15,18,20,25,30,40}
	for i=1,#arr do
		local fishType=arr[i]
	    local pStrBuffer1 = string.format('Scene/Game/FishAndBomb/Fish_%02d.plist', fishType)	
	    CCSpriteFrameCache:sharedSpriteFrameCache():removeSpriteFramesFromFile(pStrBuffer1)	
	    self.s_AllFish[fishType]:removeAllChildrenWithCleanup( true ) 
	end	
		
    local arr1={1,2,3,4,5,6,7,8,9,10,11,12}
	for i=1,#arr1 do
		local BombType=arr1[i]
	    local pStrBuffer1 = string.format('Scene/Game/FishAndBomb/Bomb_%02d.plist', BombType)
	    CCSpriteFrameCache:sharedSpriteFrameCache():removeSpriteFramesFromFile(pStrBuffer1)
	    self.s_AllBomb[BombType]:removeAllChildrenWithCleanup( true )
	end
	
	self.s_AllBomb["Dead"]:removeAllChildrenWithCleanup( true ) 
end


--[[
添加一个鱼阵
参数说明：
fishgroupType----鱼阵类型：1*表示直线轨迹阵，2*表示圆轨迹阵，3*表示摆线轨迹阵
鱼阵类型fishgroupType和轨迹类型pathType最好对应起来，增强LUA代码的可读性
pathType----轨迹类型：1表示直线轨迹，2表示圆轨迹，3表示摆线轨迹
]]
function FishManage:addOneGroupFish(fishgroupType)
--水平直线轨迹阵
if(fishgroupType==11)then
   FishManage:addOneFish(3,1,ccp(0,150),ccp(1500,0)); 
   FishManage:addOneFish(4,1,ccp(0,200),ccp(1500,0));
   FishManage:addOneFish(5,1,ccp(0,250),ccp(1500,0));
   FishManage:addOneFish(8,1,ccp(0,350),ccp(1500,0)); 
   FishManage:addOneFish(12,1,ccp(0,400),ccp(1500,0));
   FishManage:addOneFish(25,1,ccp(0,450),ccp(1500,0));
   FishManage:addOneFish(40,1,ccp(0,500),ccp(1500,0));    
end
--斜直线轨迹阵
if(fishgroupType==12)then
   FishManage:addOneFish(25,1,ccp(-120,-20),ccp(1500,1500))
   FishManage:addOneFish(3,1,ccp(-40,60),ccp(1500,1500))
   FishManage:addOneFish(1,1,ccp(0,100),ccp(1500,1500))
   FishManage:addOneFish(40,1,ccp(-80,20),ccp(1500,1500))   
end
--圆轨迹阵  
if(fishgroupType==21)then
    local startP=ccp(500,300)
    local centerP=ccp(350,300)   
	local deltArg=math.pi*0.2
	for i=1,10 do
		local startP=GetCirclePos(startP,centerP,deltArg*(i-1))
		FishManage:addOneFish(1,2,startP,centerP)
	end	 
end
--[[
--圆轨迹阵
if(fishgroupType==22)then
    local startP=ccp(0,300)
    local centerP=ccp(150,300)   
	local deltArg=math.pi*0.2
	for i=1,10 do
		local startP=GetCirclePos(startP,centerP,deltArg*(i-1))
		FishManage:addOneFish(7,2,startP,centerP)
	end	 
end
]] 
----水平摆线轨迹阵  
if(fishgroupType==31)then
    local startP=ccp(200,300)
    local rdeltArg=ccp(60,0)
    local arg2=ccp(0,math.pi)
	local deltArg=math.pi*0.2
	for i=1,10 do
		rdeltArg.y=deltArg*(i-1)
		FishManage:addOneFish(1,3,startP,rdeltArg,arg2)
	end	 
end
--斜摆线轨迹阵  
if(fishgroupType==32)then
    local startP=ccp(400,300)
    local rdeltArg=ccp(100,0)
    local arg2=ccp(0,math.pi*0.75)     
	local deltArg=math.pi*0.2
	for i=1,10 do
		rdeltArg.y=deltArg*(i-1)
		FishManage:addOneFish(6,3,startP,rdeltArg,arg2)
	end	 
end 
--垂直摆线轨迹阵  
if(fishgroupType==33)then
    local startP=ccp(400,300)
    local rdeltArg=ccp(60,0) 
    local arg2=ccp(0,math.pi*0.5)     
	local deltArg=math.pi*0.2
	for i=1,10 do
		rdeltArg.y=deltArg*(i-1)
		FishManage:addOneFish(2,3,startP,rdeltArg,arg2)
	end	
end  
end

--[[
添加一条鱼或一个炸弹
参数说明：
fishType----fishType/100=0时表示鱼，fishType%100表示几号鱼；fishType/100=1时表示炸弹，fishType%100表示几号炸弹；
]]
function FishManage:addOneFish(fishType,pathType,startP,arg1,arg2)
	-- 删除离开屏幕的鱼
	self:CaptureOneFish()
	
	if(startP==nil)then
	  startP=ccp(0,300)
	end	
	if(arg2==nil)then
	  arg2=ccp(0,math.pi)
	end
	
	--取商、取模
	local q=math.floor(fishType/100)--fishType/100
	local r=fishType-math.floor(fishType/100)*100--fishType%100,取模操作被定义为a%b==a-math.floor(a/b)*b
	local arr={[0]='Fish_%02d_%05d.png',[1]='Fish_%02d_00000.png',[2]='Bomb_%02d_%05d.png',[3]='Bomb_%02d_00000.png'}    
	local pArray = CCArray:create()
	
	for i=0,24 do
		local pStrBuffer = string.format(arr[2*q],r,i)
		local pSpriteFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( pStrBuffer )
		
		if not pSpriteFrame then
			break
		end
		pArray:addObject( pSpriteFrame )
	end
	
	-- 由帧缓存生成action，帧延迟0.1f
	local pAnimation =CCAnimation:createWithSpriteFrames(pArray,0.1)
	local fish_act = CCRepeatForever:create(CCAnimate:create(pAnimation))
	local Name=string.format(arr[2*q+1],r)	
	local pFish = Fish:spriteWithSpriteFrameName(Name)
	if (pFish) then
	  pFish:setScale(1.0)
	  pFish:setTag(fishType)
	  pFish:setPosition(startP)
	  pFish:runAction(fish_act)
	  pFish:addPath(pathType,arg1,arg2)
	  
	  FishManage.mFishData[pFish] = {}
	  FishManage.mFishData[pFish]["isCatch"] = false
	  
	  if 0 <= 2*q and 1 >= 2*q then
	  	FishManage.s_AllFish[r]:addChild( pFish )
	  else
	  	FishManage.s_AllBomb[r]:addChild( pFish )
	  end
	end
	CCLuaLog("pFish="..tostring(pFish))	
end

--[[
捕获屏幕外的鱼或炸弹
]]
function FishManage:CaptureOneFish()
	local winSize = CCDirector:sharedDirector():getWinSize()
	for k,v in pairs( FishManage.mFishData ) do
		local spriteFishBomb = k
		spriteFishBomb = tolua.cast(spriteFishBomb, "CCSprite")	
		local fishRect = spriteFishBomb:boundingBox()
	
		if not FishManage.mFishData[spriteFishBomb]["isCatch"] and not fishRect:intersectsRect(CCRect(0,0,winSize.width,winSize.height)) then
			lHaveCatchingFish = true
			FishManage.mFishData[spriteFishBomb]["isCatch"] = true
			SpriteRemoveCallBack( spriteFishBomb )
		end
	end
end

--取商、取模
function qr(fishType)
    local q=math.floor(fishType/100)
    local r=fishType-math.floor(fishType/100)*100
	return q,r
end

--鱼的头部朝向
--[[
fishType=1,2,40,……,——pi
fishType=3,——0
fishType=10,——pi*0.5
]]
function qrArg(fishType)
    local q,r=qr(fishType)
    if q==0 then
       --local Name=string.format('Fish_%02d',r)
       --return Name
       local arg=s_AllFishArg[r]
       return arg
	else
       local arg=s_AllBombArg[r]
       return arg
	end
end

function qrName(fishType)
    local q,r=qr(fishType)
    if q==0 then
       return 'Fish'
	else
       return 'Bomb'
	end
end

function SpriteRemoveCallBack(node)
	if FishManage.mFishData[node] then
		FishManage.mFishData[node] = nil
	end
	
	node:removeAllChildrenWithCleanup( true )
	node:removeFromParentAndCleanup( true )
end

function DieAnimation(node)
	node:stopAllActions()
	node:setVisible( false )
	node:setAnchorPoint(CCPoint:new(0.5,0.5))

	local pArray= CCArray:create();
	local q,r=qr(node:getTag())
	if(q==0)then
	  -- 死鱼
      for i=0,24,2 do
		local strBuffer = string.format('DeadFish_%02d_%05d.png', r, i)
		local pFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( strBuffer )
		if not pFrame then
			break
		end
		pArray:addObject( pFrame );
	  end
	  
	  -- 结束自己
		local pAnimation = CCAnimation:createWithSpriteFrames( pArray, 0.1 )
		local pAnimate = CCAnimate:create( pAnimation )
		local FishActionArray = CCArray:create()
		
		FishActionArray:addObject(CCShow:create())
		FishActionArray:addObject(pAnimate)
		FishActionArray:addObject(CCCallFuncN:create( SpriteRemoveCallBack ))
		node:runAction( CCSequence:create(FishActionArray))
	else
		-- 结束自己
		local FishActionArray = CCArray:create()
		FishActionArray:addObject(CCCallFuncN:create( SpriteRemoveCallBack ))
		local bombPT = node:getPositionLua()
		node:runAction( CCSequence:create(FishActionArray))
				
		--死炸弹
		for i=0,13 do 
			local strBuffer = string.format('DeadBomb_%05d.png',i)
			local pFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName(strBuffer)
			if not pFrame then
				break
			end
			
			pArray:addObject( pFrame )
		end
		
		local pAnimation = CCAnimation:createWithSpriteFrames( pArray, 0.1 )
		local pAnimate = CCAnimate:create( pAnimation )
		local DeadBombFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( "DeadBomb_00000.png" )
		local DeadSprite = CCSprite:createWithSpriteFrame( DeadBombFrame )
		local FishActionArray = CCArray:create()		
		FishActionArray:addObject(pAnimate)
		FishActionArray:addObject(CCCallFuncN:create( SpriteRemoveCallBack ))
		
		DeadSprite = tolua.cast(DeadSprite, "CCSprite")
		DeadSprite:setPosition( bombPT )
		DeadSprite:runAction( CCSequence:create( FishActionArray ) )
		FishManage.s_AllBomb["Dead"]:addChild( DeadSprite )
		
	end
end
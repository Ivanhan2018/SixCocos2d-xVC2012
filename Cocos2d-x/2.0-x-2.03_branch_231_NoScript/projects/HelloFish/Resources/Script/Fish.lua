--[[
------------------------------------
һ����
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
���ױ��������ߣ�P_0,P_1,P_2,P_3���˻�Ϊ���ױ��������ߣ�P_0,P_1,P_2���������ߣ����P_0=���Ƶ�P_1,���Ƶ�P_2,�յ�P_3��
����˵����
startP----�켣���
endP----�켣�յ�
startAngle----
endAngle----
time----����ʱ��
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

	-- ����������
	local bezier=ccBezierConfig:new();
	-- ���Ƶ�1(���)
	bezier.controlPoint_1 = ccp(sx, sy);
	-- ���Ƶ�2
	--bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5);
	bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+100);	
	-- �յ�
	bezier.endPosition = ccp(endP.x, endP.y);

	local actionMove = CCBezierTo:create(time, bezier);
	local actionRotate = CCRotateTo:create(time, endAngle);
	local action = CCSpawn:createWithTwoActions(actionMove, actionRotate)
	local pcc=CCCallFuncN:create( SpriteRemoveCallBack )
	local sq = CCSequence:createWithTwoActions(action,pcc)
	self:runAction(sq);
end





--[[
������˶��켣�ɹ켣���͡��켣������ꡢ�켣�ٶȵ��໥�����Ĳ���������
����˵����
pathType--�켣����
1��ʾֱ�߹켣���������arg1��ʾ�켣��������pathType=1��arg1=ccp(1500,1500)��ʾ���Ͻ�45��ֱ�߹켣��pathType=1��arg1=ccp(1500,0)��ʾˮƽ����ֱ�߹켣
2��ʾԲ�켣
3��ʾ���߹켣���������arg1����뾶�ͷ�����ֵ�������������arg2������߹켣����
arg1--��һ�����������ֱ�߹켣��Բ�켣�����߹켣Ҫ�õ�
arg2--�ڶ���������������߹켣Ҫ�õ�
]]
function Fish:addPath(pathType,arg1,arg2)
if(pathType==1)then
   --�����켣���ͺ㶨�ٶ�ʸ�����㶨���ʺͺ㶨���򣩵�����ֱ���˶�
   --����ֱ�߹켣��arg1����ֱ�߹켣��������ccp(1500,1500)�������Ͻ�45��ֱ�߹켣��ccp(1500,0)����ˮƽ����ֱ�߹켣
   if(arg1==nil)then
      arg1=CCPoint(1500,0);
  end
    --������֡��Դ�е���ͷ���������켣��������˳ʱ����ת�Ƕȣ��Ƕ��ƣ�
    local angle=(qrArg(self:getTag())-math.atan2(arg1.y,arg1.x))*180/math.pi
    self:setRotation(angle);
	local actionMove = CCMoveBy:create(15.0,arg1);
    --�ڹ켣ʱ���ڣ��㾫������ɾ������
	local pcc=CCCallFuncN:create( SpriteRemoveCallBack )
	local sq = CCSequence:createWithTwoActions(actionMove, pcc)
	self:runAction(sq);
end
if(pathType==2)then
  local startP=CCPoint(self:getPositionX(),self:getPositionY());
  --����Բ�켣��arg1����Բ������
   if(arg1==nil)then
      arg1=CCPoint(self:getPositionX()-150,self:getPositionY());
  end    
  self:runAction(myAction:createCircle(60.0,"CircleTraceFunc",startP,arg1,20));
--[[
  local startP=CCPoint(self:getPositionX(),self:getPositionY());
  --����Բ�켣��arg1����Բ������
   if(arg1==nil)then
      arg1=CCPoint(self:getPositionX()+150,self:getPositionY());
  end 
  --�Ծ���P
   local P=CCPoint(arg1.x*2-self:getPositionX(),arg1.y*2-self:getPositionY()); 
   local  actionBy = CircleAction:create(5.0,P,1);
   local  ac = CCRepeatForever:create(actionBy);
   self:runAction(ac);

   --Բ˳ʱ���˶��켣������һΪ����ʱ����������Ϊ��ǰԲ��λ�õĶԾ������꣬������Ϊ�켣����
   self:runAction(CircleAction:create(3.0, ccp(500,300),-1));  
]]   
end 
if(pathType==3)then
--[[
    --ȥ����createMoveCircle����createCycloid����  
   local  actionBy =myAction:createCycloid(3.0,"CycloidTraceFunc",ccp(200,300),ccp(50,0),3,ccp(-50,math.pi*0.25));
   local  ac = CCRepeatForever:create(actionBy);
   self:runAction(ac);
   ]]
   local startP=CCPoint(self:getPositionX(),self:getPositionY());
  --���ڰ��߹켣��arg1����뾶�ͷ�����ֵ����
    if(arg1==nil)then
       arg1=CCPoint(50,0);
   end
   --���ڰ��߹켣��arg2.y������߹켣����  
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
   --�Զ����˶��켣������һΪ����ʱ����������Ϊ��ʾ�켣�������̵�LUA������
   --self:runAction(myAction:create(3.0,"SinTrace"));
   local angle=(qrArg(self:getTag())-0)*180/math.pi
   self:setRotation(angle);
    --����һ���ȼ����ټ��ٵ��������߹켣�˶�
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
�㾫������õ��ľ���֡�Ĺ���
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
FishManage.mFishData = {} -- ��Я������
FishManage.s_AllFish ={[1]=nil,[2]=nil,[3]=nil,[4]=nil,[5]=nil,[6]=nil,[7]=nil,[8]=nil,[9]=nil,[10]=nil,[12]=nil,[15]=nil,[18]=nil,[20]=nil,[25]=nil,[30]=nil,[40]=nil}
--1-10��ը����Ӧ1-10���㣬11��ը����ȫ��ը����12��ը������Ϻը��

FishManage.s_AllBomb ={[1]=nil,[2]=nil,[3]=nil,[4]=nil,[5]=nil,[6]=nil,[7]=nil,[8]=nil,[9]=nil,[10]=nil,[11]=nil,[12]=nil, ["Dead"]=nil}

--���ͷ������
s_AllFishArg={[1]=math.pi,[2]=math.pi,[3]=math.pi,[4]=math.pi,[5]=math.pi,[6]=math.pi,[7]=math.pi,[8]=math.pi,[9]=math.pi,[10]=math.pi*0.5,[12]=math.pi,[15]=math.pi,[18]=math.pi,[20]=math.pi,[25]=math.pi,[30]=math.pi,[40]=math.pi}
--ը����ͷ������
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
	-- ����ը��
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
���һ������
����˵����
fishgroupType----�������ͣ�1*��ʾֱ�߹켣��2*��ʾԲ�켣��3*��ʾ���߹켣��
��������fishgroupType�͹켣����pathType��ö�Ӧ��������ǿLUA����Ŀɶ���
pathType----�켣���ͣ�1��ʾֱ�߹켣��2��ʾԲ�켣��3��ʾ���߹켣
]]
function FishManage:addOneGroupFish(fishgroupType)
--ˮƽֱ�߹켣��
if(fishgroupType==11)then
   FishManage:addOneFish(3,1,ccp(0,150),ccp(1500,0)); 
   FishManage:addOneFish(4,1,ccp(0,200),ccp(1500,0));
   FishManage:addOneFish(5,1,ccp(0,250),ccp(1500,0));
   FishManage:addOneFish(8,1,ccp(0,350),ccp(1500,0)); 
   FishManage:addOneFish(12,1,ccp(0,400),ccp(1500,0));
   FishManage:addOneFish(25,1,ccp(0,450),ccp(1500,0));
   FishManage:addOneFish(40,1,ccp(0,500),ccp(1500,0));    
end
--бֱ�߹켣��
if(fishgroupType==12)then
   FishManage:addOneFish(25,1,ccp(-120,-20),ccp(1500,1500))
   FishManage:addOneFish(3,1,ccp(-40,60),ccp(1500,1500))
   FishManage:addOneFish(1,1,ccp(0,100),ccp(1500,1500))
   FishManage:addOneFish(40,1,ccp(-80,20),ccp(1500,1500))   
end
--Բ�켣��  
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
--Բ�켣��
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
----ˮƽ���߹켣��  
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
--б���߹켣��  
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
--��ֱ���߹켣��  
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
���һ�����һ��ը��
����˵����
fishType----fishType/100=0ʱ��ʾ�㣬fishType%100��ʾ�����㣻fishType/100=1ʱ��ʾը����fishType%100��ʾ����ը����
]]
function FishManage:addOneFish(fishType,pathType,startP,arg1,arg2)
	-- ɾ���뿪��Ļ����
	self:CaptureOneFish()
	
	if(startP==nil)then
	  startP=ccp(0,300)
	end	
	if(arg2==nil)then
	  arg2=ccp(0,math.pi)
	end
	
	--ȡ�̡�ȡģ
	local q=math.floor(fishType/100)--fishType/100
	local r=fishType-math.floor(fishType/100)*100--fishType%100,ȡģ����������Ϊa%b==a-math.floor(a/b)*b
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
	
	-- ��֡��������action��֡�ӳ�0.1f
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
������Ļ������ը��
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

--ȡ�̡�ȡģ
function qr(fishType)
    local q=math.floor(fishType/100)
    local r=fishType-math.floor(fishType/100)*100
	return q,r
end

--���ͷ������
--[[
fishType=1,2,40,����,����pi
fishType=3,����0
fishType=10,����pi*0.5
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
	  -- ����
      for i=0,24,2 do
		local strBuffer = string.format('DeadFish_%02d_%05d.png', r, i)
		local pFrame = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName( strBuffer )
		if not pFrame then
			break
		end
		pArray:addObject( pFrame );
	  end
	  
	  -- �����Լ�
		local pAnimation = CCAnimation:createWithSpriteFrames( pArray, 0.1 )
		local pAnimate = CCAnimate:create( pAnimation )
		local FishActionArray = CCArray:create()
		
		FishActionArray:addObject(CCShow:create())
		FishActionArray:addObject(pAnimate)
		FishActionArray:addObject(CCCallFuncN:create( SpriteRemoveCallBack ))
		node:runAction( CCSequence:create(FishActionArray))
	else
		-- �����Լ�
		local FishActionArray = CCArray:create()
		FishActionArray:addObject(CCCallFuncN:create( SpriteRemoveCallBack ))
		local bombPT = node:getPositionLua()
		node:runAction( CCSequence:create(FishActionArray))
				
		--��ը��
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
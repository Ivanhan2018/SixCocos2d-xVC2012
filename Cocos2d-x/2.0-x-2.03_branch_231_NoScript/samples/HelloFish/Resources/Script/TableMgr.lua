--[[
------------------------------------
桌子逻辑管理器脚本
------------------------------------
Cool.Cat@2013/5/21 16:15:32
------------------------------------
]]

TableMgr = class("TableMgr")

-- attribute
TableMgr.__index						= TableMgr

-- 当前房间总人数
TableMgr.__PlayerCount			=	0
-- 桌子总数
TableMgr.__TableCount				= 0
-- 每个桌子包含的座位数
TableMgr.__SeatCount				= 0

-- 房间容器
TableMgr.__pListView				= 0
-- 每行桌子总数
TableMgr.__TableCountPerRow	=	3


-- method
function TableMgr:create(pListView)
	local pTableMgr = TableMgr:new()
	pTableMgr.__pListView = pListView
	return pTableMgr
end

function TableMgr:UpdateAttribute(iRoomPeopleCount,iTables,iSeatNum)
	if (self==nil) then
		return
	end
	self.__PlayerCount 	= iRoomPeopleCount
	self.__TableCount 	= iTables
	self.__SeatCount		= iSeatNum
end

function TableMgr:ShowTable(IsShow)
	self.__pListView:setVisible(IsShow)
	
	self.__pListView:RemoveCellAll()
	
	self:UpdateTableAll()
end

function TableMgr:UpdateTableAll()
	local rowCount = math.floor(self.__TableCount / self.__TableCountPerRow)
	local leftCount = self.__TableCount - self.__TableCountPerRow * rowCount
	CCLuaLog("rowCount = "..rowCount..".leftCount = "..leftCount)
	self:MakeRowTable(1,rowCount,self.__TableCountPerRow)
	self:MakeRowTable(rowCount+1,rowCount+1,leftCount)
end

function TableMgr:MakeRowTable(rowStart,rowCount,tableCount)
	if (tableCount<=0 or rowStart<=0) then
		return
	end
	for row=rowStart,rowCount do
		-- 动态创建第row行ListViewCell
		local CellRow = row
		local CellTag = CellRow * 100
		local pCell = SIX_ListViewCell:new()
		pCell:setObjName(string.format("TableCell-%02d",CellRow))
		pCell:setTag(CellTag)
		self.__pListView:AddCell(pCell,CellRow-1)
		CCLuaLog("row["..row.."].Cell["..pCell:getObjName().."].CellTag["..CellTag.."]")
		
		-- 动态创建第i行桌子
		for i=1,tableCount do
			--local TableTag = CellTag + i
			local TableTag = CellTag + (row-1)*self.__TableCountPerRow + i-1
			local pNode = CCNode:create()
			local TablePosX = i * 75 + (i-1) * 168
			pNode:setObjName(string.format("Table-%02d",TableTag))
			pNode:setTag(TableTag)
			pCell:addChild(pNode)
			CCLuaLog("row["..row.."].table["..pNode:getObjName().."].TableTag["..TableTag.."]")
			
			-- 桌子背景
			local pTable = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName("table.png")
			if (pTable==0) then
				return
			end
			
			local tableFrameContentSize = pTable:getOriginalSizeInPixels()
			
			pTable = CCScale9Sprite:createWithSpriteFrame(pTable);
			pTable:setAnchorPoint(ccp(0,0))
			pTable:setPreferredSize(CCSize(tableFrameContentSize.width,tableFrameContentSize.height))
			pTable:setPosition(ccp(TablePosX,95))
			pNode:addChild(pTable)
			
			-- 桌子座位
			for k=1,4 do
				local pSeat = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName("empty.png")
				if (pSeat==0) then
					return
				end
				local SeatTag = TableTag * 10 + k - 1
				CCLuaLog("row["..row.."].table["..i.."].seat["..(k-1).."].SeatTag["..SeatTag.."]")
				seatFrameContentSize = pSeat:getOriginalSizeInPixels()
				
				local SeatPosX=0
				if (k==1 or k==3) then
					SeatPosX = pTable:getPositionX() + seatFrameContentSize.width/2
				elseif (k==2 or k==4) then
					SeatPosX = pTable:getPositionX() + tableFrameContentSize.width - seatFrameContentSize.width/2
				end
	
				local SeatPosY=0
				if (k==1 or k==2) then
					SeatPosY = 225 + seatFrameContentSize.height/2
				elseif (k==3 or k==4) then
					SeatPosY = 10 + seatFrameContentSize.height/2
				end
				
				pSeat = CCScale9Sprite:createWithSpriteFrame(pSeat);
				pSeat = CCControlButton:create(pSeat)
				pSeat:setTag(SeatTag)
				pSeat:setPreferredSize(CCSize(seatFrameContentSize.width,seatFrameContentSize.height))
				pSeat:setPosition(ccp(SeatPosX,SeatPosY))
				if (k==3 or k==4) then
					pSeat:setRotation(180.0)
				end
				pScene:GetUIMgr():addControlEvents(32,pSeat)
				pNode:addChild(pSeat)
			end
		end
	end
end

function TableMgr:FindControlFromData(iTableNo,iSeatNo)
	if (self.__pListView==nil) then
		return nil
	end
	
	local cellTag = math.floor(iTableNo / self.__TableCountPerRow)
	local tableIdx = iTableNo - self.__TableCountPerRow * cellTag
	CCLuaLog("TableMgr:SitDown.cellTag = "..cellTag..".tableIdx = "..tableIdx)
	
	-- 查找对应的cell
	local pCell = self.__pListView:GetCell(cellTag)
	if (pCell==nil) then
		CCLuaLog("行标["..cellTag.."]不存在！")
		return nil
	end	
	
	-- 查找对应的table
	local tableTag = (cellTag+1)*100 + iTableNo
	local pTable = pCell:getChildByTag(tableTag)
	if (pTable==nil) then
		CCLuaLog("桌标["..tableTag.."]不存在！")
		return nil
	end		
	
	-- 查找对应的seat
	local seatTag = tableTag * 10 + iSeatNo
	local pSeat = pTable:getChildByTag(seatTag)
	if (pSeat==nil) then
		CCLuaLog("位号["..seatTag.."]不存在！")
		return nil
	end
	pSeat = tolua.cast(pSeat,"CCControlButton")
	return pSeat
end

function TableMgr:SwitchSitDownOrLeaveSeat(lUserId,iTableNo,iSeatNo,IsSitDown)
	CCLuaLog("TableMgr:SitDown.lUserId["..lUserId.."/"..pUserIdx.."].iTableNo["..iTableNo.."].iSeatNo["..iSeatNo.."]")

	-- 根据桌子ID和座位ID定位查找UI控件
	local pSeat = self:FindControlFromData(iTableNo,iSeatNo)
	if (pSeat==nil) then
		CCLuaLog("SitDown.FindControlFromData["..iTableNo.."]["..iSeatNo.."].Nil")
		return
	end
	
	-- 切换座位按钮的背景九宫格图片
	local pSprite = 0
	if (IsSitDown==true) then
		pSprite = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName("female.png")
	elseif (IsSitDown==false) then
		pSprite = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName("empty.png")
	end
	
	if (pSprite==0) then
		return
	end	
	
	
	local pBg = pSeat:getBackgroundSprite()
	-- 换图片前要先设置alpha
	pBg:setOpacity(255)
	pBg:setSpriteFrame(pSprite)
	if (IsSitDown==true) then
		CCLuaLog("SitDown.Done")
	elseif (IsSitDown==false) then
		CCLuaLog("LeaveSeat.Done")
	end
end
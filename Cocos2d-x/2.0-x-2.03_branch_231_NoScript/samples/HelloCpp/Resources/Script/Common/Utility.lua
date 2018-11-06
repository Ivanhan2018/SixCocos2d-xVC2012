--[[
----------------------------------
常用函数
------------------------------------
Cool.Cat@2013-4-8 1:01:20
------------------------------------
]]

function VersionStr()
	return 	VERSION.MAIN.."."..
					VERSION.CHILD.."."..
					VERSION.STAGE.."."..
					VERSION.BUILD.." ("..
					VERSION.DESC..")"
end

-- 1100405
function VersionNum()
	return 	VERSION.MAIN 	* 1000000 + 
					VERSION.CHILD * 100000	+
					VERSION.STAGE	*	10000		+
					VERSION.BUILD
end

function VersionFull()
	local split = "---------------------------------------\n"
	local versionFull = split
	versionFull = versionFull.."版本："..VersionStr().."\n"
	versionFull = versionFull.."日期："..VERSION.DATE.."\n"
	versionFull = versionFull..split.."\n"
	return versionFull
end

function pow(n,p)
	return n^p
end

function print_table(table)
  for i=1 ,#table do
		CCLuaLog("table["..i.."]="..table[i])
  end
end


function ENUM(tbl, index) 
    assert(type(tbl)=="table") 
    local enumtbl = {} 
    local enumindex = index or 0 
    for i, v in ipairs(tbl) do 
        enumtbl[v] = enumindex + i 
    end 
    return enumtbl 
end

-- 运行时间(s)
function GetRuntime()
	return SIX_Utility:GetInstance():GetGlobalSecond()
end

-- 保留小数点后p位
function Fixed(n,p)
	return SIX_Utility:GetInstance():Fixed(n,p)
end

function GetFormatRuntime()
	local sec = GetRuntime()
	
	local day = getIntPart(sec / 86400)
	sec = sec - day * 86400
	
	local hour = getIntPart(sec / 3600)
	sec = sec - hour * 3600
	
	local min = getIntPart(sec / 60)
	sec = sec - min * 60

	if (day==0) then
		return "已经运行："..string.format("%02d",hour)..":"..string.format("%02d",min)..":"..string.format("%05.2f",sec)
	end
	return "已经运行："..string.format("%02d",day).."(D)"..string.format("%02d",hour)..":"..string.format("%02d",min)..":"..string.format("%05.2f",sec)
end

function getIntPart(x)
    if (x <= 0) then
       return math.ceil(x);
    end

    if (math.ceil(x) == x) then
       x = math.ceil(x)
    else
       x = math.ceil(x) - 1
    end
    return x
end

-- 异步加载plist
-- 另外还在回调中做以下2步处理：
-- 1、CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithDictionary(dict,pTexture)
-- 2、CCSpriteFrameCache:sharedSpriteFrameCache():insertPlist(pszPlist)
function addSpriteFramesWithPlistAsync(pszPlist,target)
	-- 先获取全路径
	local pszPath = CCFileUtils:sharedFileUtils():fullPathFromRelativePath(pszPlist)
	--CCLuaLog("addSpriteFramesWithPlistAsync.pszPath["..pszPath.."]")
	
	-- 根据plist取得dict，非线程安全
	local dict = CCDictionary:createWithContentsOfFile(pszPath)
	--CCLuaLog("addSpriteFramesWithPlistAsync.dict["..tostring(dict).."]")
	
	-- 根据metadata取得textureFileName
	local metadataDict = dict:objectForKey("metadata")
	if (metadataDict==nil) then
		CCLuaLog("addSpriteFramesWithPlistAsync.metadataDict.Nil")
		dict:release()
		return
	end
	
	metadataDict = tolua.cast(metadataDict,"CCDictionary")
	
	--CCLuaLog("addSpriteFramesWithPlistAsync.metadataDict["..tostring(metadataDict).."]")
	
	local texturePath = metadataDict:valueForKey("textureFileName"):getCString()
	if (texturePath==nil) then
		CCLuaLog("addSpriteFramesWithPlistAsync.texturePath.A.Nil")
		dict:release()
		return
	end
	
	--CCLuaLog("addSpriteFramesWithPlistAsync.texturePath["..texturePath.."]")
	
	texturePath = CCFileUtils:sharedFileUtils():fullPathFromRelativeFile(texturePath,pszPath)
	if (texturePath==nil) then
		CCLuaLog("texturePath.B.Nil")
		dict:release()
		return
	end
	
	-- 异步加载
	CCTextureCache:sharedTextureCache():addImageAsync(texturePath,target)
	
	dict:release()
	
	CCLuaLog("addSpriteFramesWithPlistAsync.pszPlist["..pszPlist.."].Done")
end

-- 参考updateBar
-- 当横向m_tBarChangeRate.x=1 && m_tMidpoint.x=0 时，m_fPercentage就是真实的步进值，此时可以简化得到m_fPercentage=getPercentage()
-- 否则还是要调用此函数计算一下。。。
-- 目前只返回了横向步进值，如果是其他显示方式的进度条请自行改变返回值
-- Cool.Cat@2013/4/9 14:00:18
function convertPercentageToMaxPostionX(m_fPercentage,m_tBarChangeRate,m_tMidpoint)
  local alpha = m_fPercentage / 100.0;
  local alphaOffset = ccpMult(ccp(1.0 * (1.0 - m_tBarChangeRate.x) + alpha * m_tBarChangeRate.x, 1.0 * (1.0 - m_tBarChangeRate.y) + alpha * m_tBarChangeRate.y), 0.5);
  local min = ccpSub(m_tMidpoint, alphaOffset);
  local max = ccpAdd(m_tMidpoint, alphaOffset);

  if (min.x < 0) then
      max.x = max.x - min.x;
      min.x = 0;
  end

  if (max.x > 1) then
      min.x = min.x - (max.x - 1);
      max.x = 1;
  end

  if (min.y < 0) then
      max.y = max.y - min.y;
      min.y = 0;
  end

  if (max.y > 1) then
      min.y = min.y - (max.y - 1);
      max.y = 1;
  end
  
	--CCLuaLog("min="..min.x.."/"..min.y.." , max="..max.x.."/"..max.y)
 	return max.x
end
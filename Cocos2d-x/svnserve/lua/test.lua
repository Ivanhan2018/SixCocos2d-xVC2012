-- test.lua
print "Hello, World!"

myName = "beauty girl"  
helloTable = {name = "mutou", IQ = 125}  
  
function helloAdd(num1, num2)  
    return (num1 + num2)  
end;  

sum=helloAdd(10,30)
print("10+30="..sum)

gszWorldPhyle= {"灵智系", "蛮荒系", "地脉系", "天羽系", "蜚廉系", "瑞兽系", "神巫系", "幽冥系"}
--i 表示索引, v 表示值
for i,v in ipairs(gszWorldPhyle) do
   print(i, v)
end
PHYLE_MAX=#gszWorldPhyle
print("PHYLE_MAX="..PHYLE_MAX)

-- 填index=-1从0开始，填index=0或不填index从1开始,……
function CreateEnumTable(tbl, index) 
    local enumtbl = {} 
    local enumindex = index or 0 
    for i, v in ipairs(tbl) do 
        enumtbl[v] = enumindex + i 
    end 
    return enumtbl 
end
--[[
	种族= 0人型系,1野兽系,2植物系,3飞行系,4昆虫系,5龙系,6神系,7不死系
]]--
eWorldPhyle = CreateEnumTable({"P_TERRAN", "P_BEAST", "P_PLANTS", "P_FLY", "P_INSECT", "P_DRAGON", "P_PROTOSS", "P_UNDEAD", "PHYLE_MAX"},-1)
print("eWorldPhyle.P_TERRAN="..eWorldPhyle.P_TERRAN)
print("eWorldPhyle.PHYLE_MAX="..eWorldPhyle.PHYLE_MAX)

function getWorldPhyle(Phyle) 
    return gszWorldPhyle[Phyle+1]
end

for i=eWorldPhyle.P_TERRAN,eWorldPhyle.PHYLE_MAX-1,1 do
	local v=getWorldPhyle(i)
	print(i,v)
end

--正确的获取table的长度应该是遍历,而且要用pairs，不要用ipairs
local function get_len(tb)
  local len = 0
  for k,v in pairs(tb) do
    len= len+1
  end
return len
end

--[[
按定义计算二次剩余和二次非剩余
x=8,(13/17)=1
x=无解,(5/17)=-1
]]--
function Legendre(a,p)
    local x=0
	if(a%p==0) then
		return 0,x--是p的倍数
	end
	for i=1,p-1,1 do
	   if((i*i-a)%p==0) then
	   	   x=i
		   return 1,x--a是p的二次剩余
	   end
	end
    return -1,x--a是p的二次非剩余
end

local Ret17={[1]={}, [-1]={}, [0]={}}
for i=1,17,1 do
local ret,x=Legendre(i,17)
local str = string.format("(%d/17)=%d,x=%d",i,ret,x)
print(str)
--print(i,ret,x)
table.insert(Ret17[ret],i)
end
print(get_len(Ret17),#Ret17[1], #Ret17[-1], #Ret17[0])

function getRetStr(ret) 
    local strArr={"二次非剩余","整除","二次剩余"}
    return strArr[ret+2]
end

for k,v in pairs(Ret17) do
    io.write(k..getRetStr(k)..":[")
	for k1,v1 in pairs(v) do
		io.write(v1,",")
	end
	print("]")
end
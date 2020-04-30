--lua实现全排列

function printResult (a)
	for i = 1, #a do
		io.write(a[i], " ")
	end
	io.write("\n")
end

function Permute(a,k)
	local len = #a
	if(len == k) then
		printResult(a)
	else
		for i=k, len do
			a[i], a[k] = a[k], a[i]
			Permute(a,k+1)
			a[i], a[k] = a[k], a[i]
		end
	end
end

arr = {"a", "b", "c"}
--Permute(arr,1)

local function get_len(tb)
  local len = 0
  for k,v in pairs(tb) do
    len= len+1
  end
return len
end

function get_key(value, tbl)
    for k,v in ipairs(tbl) do
      if v == value then
          return k
      end
    end
    return -1
end

function is_equal(a, b)
	local na=get_len(a)
	local nb=get_len(b)	
	if(na~=nb) then
		return false
	end	
	for i=1,na,1 do
      if a[i] ~= b[i] then
          return false
      end
	end
	return true
end

function get_key2(value, tbl)
    for k,v in ipairs(tbl) do
      if is_equal(v, value) then
          return k
      end
    end
    return -1
end

function mul(a,b)
    local ret = {}
	local na=get_len(a)
	local nb=get_len(b)	
	if(na~=nb) then
		return nil
	end	
	for i=1,na,1 do
       ret[i]=a[b[i]]
	end
    return ret
end

local r={2,3,1}
local f={3,2,1}
local fr=mul(f,r)
local rf=mul(r,f)
local ff=mul(f,f)
local rr=mul(r,r)
local S3={ff,r,rr,f,fr,rf}
--[[
printResult(ff)
printResult(r)
printResult(rr)
printResult(f)
printResult(fr)
printResult(rf)
]]--
function printSet(G)
	for k,v in pairs(G) do
		local k1=get_key(v,G)
		io.write(k1, "->")
		printResult (v)
	end
end

function printTable(G)
	for ki,vi in pairs(G) do
		for kj,vj in pairs(G) do
			local ij=mul(vi,vj)
			local IJ=get_key2(ij,G)
			io.write(IJ, " ")
		end
		io.write("\n")
	end
end

print("S3=GAP4[6,1]:")
printSet(S3)
printTable(S3)

function FG(...)
    -- 把可变参数放在表类
    local args = { ... }
	local S={}	
	local I={}
	local n=get_len(args[1])
	for i=1,n,1 do
       I[i]=i
	end	
    table.insert(S,I)	
	for i,v in pairs(args) do
	    table.insert(S,v)
	end		
	local cnt=0
	local cnt1=get_len(S)
	
	while(cnt1>cnt)	do
		cnt=get_len(S)
		for ki,vi in pairs(S) do
			for kj,vj in pairs(S) do
				local ij=mul(vi,vj)
				local IJ=get_key2(ij,S)
				if(IJ==-1) then
					table.insert(S,ij)
				end	
			end
		end		
		cnt1=get_len(S)
	end	
    return S	
end

local A3=FG(r)
printSet(A3)
printTable(A3)

local D3=FG(r,f)
printSet(D3)
printTable(D3)

--E4={(1),(12)(34),(13)(24),(14)(23)}
print("克莱因四元群E4=GAP4[4,2]:")
local E4=FG({2,1,4,3},{3,4,1,2})
printSet(E4)
printTable(E4)

--A4={(1), (123), (132), (124), (142), (134), (143), (234), (243), (12)(34), (13)(24), (14)(23)}
print("A4=GAP4[12,3]:")
local A4=FG({2,1,4,3},{2,3,1,4})
printSet(A4)
printTable(A4)

--D_4={E=(1),E1=(12),E2=(34),E3=(12)(34),E4=(13)(24),E5=(1423),E6=(1324),E7=(14)(23)}
print("D4=GAP4[8,3]:")
local D4=FG({3,4,1,2},{2,1,3,4})
printSet(D4)
printTable(D4)

print("Rank=2的18阶群S_3×C_3=GAP4[18,3]:")
local S3C3=FG({1,2,3,4,6,5},{2,3,1,5,4,6})
printSet(S3C3)
printTable(S3C3)
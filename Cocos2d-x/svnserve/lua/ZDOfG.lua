local function get_len(tb)
  local len = 0
  for k,v in pairs(tb) do
    len= len+1
  end
return len
end

function VStr(a)
	local n=get_len(a)
    local s
	s="["
	for i=1,n,1 do
	    s=s..a[i]
		if i<n then
			s=s..","
		end		
	end
	s=s.."]"
	return s
end

local function VStr2(tb)
	local n=get_len(tb)
	local i=0
    local s
	s="["
	for k,v in pairs(tb) do
	    i=i+1
	    s=s..v
		if i<n then
			s=s..","
		end		
	end
	s=s.."]"
	return s
end

function MStr(a)
	local n=get_len(a)
    local s
	s="["
	for i=1,n,1 do
	    s=s.."["
		local ni=get_len(a[i])
		for j=1,ni,1 do
			s=s..a[i][j]
			if j<ni then
				s=s..","
			end
		end
		s=s.."]"
		if i<n then
			s=s..","
		end		
	end
	s=s.."]"
	return s
end

function TableStr(a)
	local n=get_len(a)
    local s="\n"
	for i=1,n,1 do 
		for j=1,n,1 do
			s=s..a[i][j].." "
		end
		if i<n then
			s=s.."\n"
		end
	end
	return s
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

--表中删掉相同的元素
function erase_unique(tbl)
	local exist = {}
	--把相同的元素进行覆盖掉
	for v, value in pairs(tbl) do
		exist[value] = true  --value进行保存 当成一个key
	end
	--重新排序表
	local newTable = {}
	for v, k in pairs(exist) do
		table.insert(newTable, v)--这里的v就相当于上面的value
	end
	return newTable --返回已经去重的表
end

function erase_unique2(tbl)
   local ret = {}
   for i,v in pairs(tbl) do   
    local k = get_key2(v,ret)        
     if k == -1 then  
      table.insert(ret,v)  
     end  
   end 
   return ret
end

local g_D3Mul=
{
 {1,2,3,4,5,6},
 {2,1,4,3,6,5},
 {3,5,1,6,2,4},
 {4,6,2,5,1,3},
 {5,3,6,1,4,2},
 {6,4,5,2,3,1}
}

local g_D4Mul=
{
 {1,2,3,4,5,6,7,8},
 {2,1,4,3,6,5,8,7},
 {3,4,1,2,7,8,5,6},
 {4,3,2,1,8,7,6,5},
 {5,7,6,8,1,3,2,4},
 {6,8,5,7,2,4,1,3},
 {7,5,8,6,3,1,4,2},
 {8,6,7,5,4,2,3,1}
}

local g_Q8Mul=
{
 {1,2,3,4,5,6,7,8},
 {2,1,4,3,6,5,8,7},
 {3,4,2,1,8,7,5,6},
 {4,3,1,2,7,8,6,5},
 {5,6,7,8,2,1,4,3},
 {6,5,8,7,1,2,3,4},
 {7,8,6,5,3,4,2,1},
 {8,7,5,6,4,3,1,2}
}

--非正规形式的凯莱表
local g_C9N=
{
{1,4,6,8,10,12,14,16,18},
{4,6,8,10,12,14,16,18,1},
{6,8,10,12,14,16,18,1,4},
{8,10,12,14,16,18,1,4,6},
{10,12,14,16,18,1,4,6,8},
{12,14,16,18,1,4,6,8,10},
{14,16,18,1,4,6,8,10,12},
{16,18,1,4,6,8,10,12,14},
{18,1,4,6,8,10,12,14,16}
}

function ToNormal(vvG)
	local N=get_len(vvG)
	local vM={}
	for i=1,N,1 do
		vM[vvG[1][i]]=i	
	end	
	local vvG1={}	
	for i=1,N,1 do
	    local vG1={}	
		for j=1,N,1 do
			table.insert(vG1,vM[vvG[i][j]])	
		end	
		table.insert(vvG1,vG1)
	end	
	return vvG1
end

function IsInCenterOfG(vvG,j)
 local N=get_len(vvG)
 for i=1,N,1 do
  local ij=vvG[i][j]
  local ji=vvG[j][i]
  if(ij~=ji)then
   return false
  end 
 end
 return true
end

function Center(vvG)
 local ret={}	
 local N=get_len(vvG)
 for i=1,N,1 do
  if(IsInCenterOfG(vvG,i))then
   table.insert(ret,i)
  end
 end
 return ret
end

function Inv(vvG,j)
 local N=get_len(vvG)
 for i=1,N,1 do
  local ij=vvG[i][j]
  if(ij==1)then
   return i
  end
 end
 return -1
end

function DerivedSubgroup(vvG)
 local ret={}
 table.insert(ret,1)
 local N=get_len(vvG)
 for i=1,N,1 do
  local I=Inv(vvG,i)
  for j=i+1,N,1 do
   local ij=vvG[i][j]
   local J=Inv(vvG,j)
   local IJ=vvG[I][J]
   local ijIJ=vvG[ij][IJ]
   table.insert(ret,ijIJ)
  end
 end
 table.sort(ret)
 local ret1=erase_unique(ret)
 return ret1
end

function IsLegalMtx(mtx)
	local ret={0,0,0}
	local illegal=-1
	ret[2]=get_len(mtx)
	if(ret[2]==0)then
		ret[1]=illegal--不是合法矩阵
		return ret
	end
	ret[3]=get_len(mtx[1])
	if(ret[3]==0)then
		ret[1]=illegal--不是合法矩阵
		return ret
	end
	for i=2,ret[2],1 do
		if(get_len(mtx[i])~=ret[3])then
			ret[1]=illegal--不是合法矩阵
			return ret
		end
	end
	ret[1]=0--是合法矩阵
	return ret
end

--未知n阶群的群元的阶
function getGnEOrder(A,a)
	local AFlag=IsLegalMtx(A)
	if(AFlag[1]==-1)then
		return -1
	end
	local n=AFlag[2]
	if(a<1 or a>n)then
		return -1
	end
	local t=1
	for i=1,n,1 do
		t=A[t][a]
		if(t==1)then
			return i
		end
	end
	return -1
end

function Factors(n)
	local ret={}
	if(n<1)then
		return ret
	end
	for i=1,n,1 do
		if(n%i==0)then
			table.insert(ret,i)
		end
	end
	return ret
end

--群元阶的分布
function calG(vvG)
	local AFlag=IsLegalMtx(vvG)
	if(AFlag[1]==-1 or AFlag[2]~=AFlag[3])then
		return nil
	end
	local vOrders=Factors(AFlag[2])
	local vCounts={}
	local n=get_len(vOrders)
	for i=1,n,1 do
		vCounts[vOrders[i]]=0
	end	
	local n1=get_len(vCounts)
	for i=1,AFlag[2],1 do
		local ord=getGnEOrder(vvG,i)
		vCounts[ord]=vCounts[ord]+1
		print(i,"->",ord)
	end
	return vCounts
end

--定义：给定群G，对G中的两个元a，b，若存在G中的某个元g，使得g^-1ag=b，就成元素a，b在G中共轭，记为a~b。
function IsConjugacy(vvG,a,b)
	local N=get_len(vvG)
	for i=1,N,1 do
		local ai=vvG[a][i]
		local ib=vvG[i][b]
		if(ai==ib)then
			return true
		end
	end
    return false
end

function ConjugacyClassesOfa(vvG,a)
    local ret={}
	local N=get_len(vvG)
	for i=1,N,1 do
        local bCon=IsConjugacy(vvG,a,i)
        if(bCon)then
            table.insert(ret,i)
	    end
    end
    return ret
end

function ConjugacyClasses(vvG)
    local vv={}
    local vv2={}	
	local N=get_len(vvG)
	for i=1,N,1 do
        local v=ConjugacyClassesOfa(vvG,i);
        table.insert(vv,v)
	end
	for i=1,N,1 do
        table.sort(vv[i])
	end	
    local vv1=erase_unique2(vv)
	local N1=get_len(vv1)
	print("N1=",N)
    for i=1,N1,1 do
        table.insert(vv2,get_len(vv1[i]))
	end
    table.sort(vv2)
    return vv1,vv2
end

local ZD3=Center(g_D3Mul)
local DD3=DerivedSubgroup(g_D3Mul)
local oD3=calG(g_D3Mul)
local C1D3,C2D3=ConjugacyClasses(g_D3Mul)
print("D3的中心Z(D_3):",VStr(ZD3))
print("D3的换位子群(D_3)':",VStr(DD3))
print("D3的群元阶的分布:",VStr2(oD3))
print("D3每个共轭类:",MStr(C1D3))
print("D3每个共轭类的长度:",VStr(C2D3))

local ZD4=Center(g_D4Mul)
local DD4=DerivedSubgroup(g_D4Mul)
local oD4=calG(g_D4Mul)
local C1D4,C2D4=ConjugacyClasses(g_D4Mul)
print("D4的中心Z(D_4):",VStr(ZD4))
print("D4的换位子群(D_4)':",VStr(DD4))
print("D4的群元阶的分布:",VStr2(oD4))
print("D4每个共轭类:",MStr(C1D4))
print("D4每个共轭类的长度:",VStr(C2D4))

local ZQ8=Center(g_Q8Mul)
local DQ8=DerivedSubgroup(g_Q8Mul)
local oQ8=calG(g_Q8Mul)
local C1Q8,C2Q8=ConjugacyClasses(g_Q8Mul)
print("Q8的中心Z(Q_8):",VStr(ZQ8))
print("Q8的换位子群(Q_8)':",VStr(DQ8))
print("Q8的群元阶的分布:",VStr2(oQ8))
print("Q8每个共轭类:",MStr(C1Q8))
print("Q8每个共轭类的长度:",VStr(C2Q8))

local g_C9=ToNormal(g_C9N)
print("C9的凯莱表:",TableStr(g_C9))
local ZC9=Center(g_C9)
local DC9=DerivedSubgroup(g_C9)
local oC9=calG(g_C9)
local C1C9,C2C9=ConjugacyClasses(g_C9)
print("C9的中心Z(C_9):",VStr(ZC9))
print("C9的换位子群(C_9)':",VStr(DC9))
print("C9的群元阶的分布:",VStr2(oC9))
print("C9每个共轭类:",MStr(C1C9))
print("C9每个共轭类的长度:",VStr(C2C9))

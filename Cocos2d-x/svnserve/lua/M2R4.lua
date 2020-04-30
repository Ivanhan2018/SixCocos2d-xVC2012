local function get_len(tb)
  local len = 0
  for k,v in pairs(tb) do
    len= len+1
  end
return len
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

function is_equalM(a, b)
	local na=get_len(a)
	local nb=get_len(b)	
	if(na~=nb) then
		return false
	end	
	for i=1,na,1 do
		local nai=get_len(a[i])
		local nbi=get_len(b[i])	
		if(nai~=nbi) then
			return false
		end		
		for j=1,nai,1 do
		  if a[i][j] ~= b[i][j] then
			  return false
		  end
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

function get_keyM(value, tbl)
    for k,v in ipairs(tbl) do
      if is_equalM(v, value) then
          return k
      end
    end
    return -1
end

function OpFunc(tbl,a,b)
local c=tbl[a+1][b+1]
return c
end

-- Returns a new table, recursively copied from the one given.
--
-- @param   table   table to be copied
-- @return  table
local function tbl_copy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == "table" then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[tbl_copy(orig_key)] = tbl_copy(orig_value)
        end
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

--两个nxn矩阵a和b相加得到c
function MAdd(a,b,Add)
	local na=get_len(a)
	local nb=get_len(b)	
	if(na~=nb) then
		return nil
	end	
	n=na
	c=tbl_copy(a)
	for i=1,n,1 do
		for j=1,n,1 do
			c[i][j]=OpFunc(Add,a[i][j],b[i][j])
		end
	end
	return c
end

--两个nxn矩阵a和b相乘得到c
function MMul(a,b,Add,Mul)
	local na=get_len(a)
	local nb=get_len(b)	
	if(na~=nb) then
		return nil
	end	
	n=na
	c=tbl_copy(a)
	for i=1,n,1 do
		for j=1,n,1 do
		local sum=0
		for k=1,n,1 do
			sum=OpFunc(Add,sum,OpFunc(Mul,a[i][k],b[k][j]))
		end
		c[i][j]=sum
		end
	end
	return c
end

function MStr(a)
	local n=get_len(a)
    local s
	s="["
	for i=1,n,1 do
	    s=s.."["
		for j=1,n,1 do
			s=s..a[i][j]
			if j<n then
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

function ZeroM(n)
	local I={}
	for i=1,n,1 do
	    local Ii={}
		for j=1,n,1 do
		   Ii[j]=0
		end
		I[i]=Ii
	end	
	return I
end

function FR(Add,Mul,...)
    -- 把可变参数放在表类
    local args = { ... }
	local S={}	
	local n=get_len(args[1])
    table.insert(S,ZeroM(n))	
	for i,v in pairs(args) do
	    table.insert(S,v)
	end		
	local cnt=0
	local cnt1=get_len(S)
	
	while(cnt1>cnt)	do
		cnt=get_len(S)
		for ki,vi in pairs(S) do
			for kj,vj in pairs(S) do
				local ij=MMul(vi,vj,Add,Mul)
				local IJ=get_keyM(ij,S)
				if(IJ==-1) then
					table.insert(S,ij)
				end	
				local ij1=MAdd(vi,vj,Add)
				local IJ1=get_keyM(ij1,S)
				if(IJ1==-1) then
					table.insert(S,ij1)
				end					
			end
		end		
		cnt1=get_len(S)
	end	
    return S	
end

function printMSet(G)
	for k,v in pairs(G) do
		--local k1=get_key(v,G)
		io.write(k, "->")
		io.write (MStr(v))
		io.write("\n")
	end
end

local g_F4Add={
{0,1,2,3},
{1,0,3,2},
{2,3,0,1},
{3,2,1,0}
}

--[[
local g_F4Mul={
{0,0,0,0},
{0,1,2,3},
{0,2,3,1},
{0,3,1,2}
}
]]
--与GAP4中的R4_11一致
local g_F4Mul={
{0,0,0,0},
{0,3,1,2},
{0,1,2,3},
{0,2,3,1}
}

local A={{0,2},{0,2}}
local B={{2,2},{0,0}}
local ABa=MAdd(A,B,g_F4Add)
local ABm=MMul(A,B,g_F4Add,g_F4Mul)
print("M_2(F_4)的子环:")
print("A=",MStr(A))
print("B=",MStr(B))
print("A+B=",MStr(ABa))
print("A*B=",MStr(ABm))

local R4_10=FR(g_F4Add,g_F4Mul,A,B)
print(get_len(R4_10))
printMSet(R4_10)

local E={{1,0},{0,1}}
local F4=FR(g_F4Add,g_F4Mul,E)
print(get_len(F4))
printMSet(F4)

local C={{1,0},{1,0}}
local D={{1,3},{1,3}}
local R16_381=FR(g_F4Add,g_F4Mul,C,D)
print(get_len(R16_381))
printMSet(R16_381)


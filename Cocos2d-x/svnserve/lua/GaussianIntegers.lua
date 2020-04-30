function gAdd(z1,z2)
local z3 = {}
z3[1]=z1[1]+z2[1]
z3[2]=z1[2]+z2[2]
return z3
end

function gSub(z1,z2)
local z3 = {}
z3[1]=z1[1]-z2[1]
z3[2]=z1[2]-z2[2]
return z3
end

function gMul(z1,z2)
local z3 = {}
z3[1]=z1[1]*z2[1]-z1[2]*z2[2]
z3[2]=z1[1]*z2[2]+z1[2]*z2[1]
return z3
end

function gStr(z)
local s
if z[2]>=0 then
s=z[1].."+"..z[2].."i"
else
s=z[1]..z[2].."i"
end
return s
end

function Norm(z)
 return (z[1]*z[1]+z[2]*z[2])
end

function ocdiv(a,b,c,d) 
    local e,f,p,q,s,w;
	p=a*c;
	q=-b*d;
	s=(a+b)*(c-d);
	w=c*c+d*d;
	if(w+1.0==1.0)then 
		e=1.0e+35*a/math.abs(a)
		f=1.0e+35*b/math.abs(b)
	else
		e=(p-q)/w
		f=(s-p-q)/w 
	end
	return e,f
end

--定义：设a,b∈M，若存在ε使b=ε(·)a，则称b是a的相伴数，记作b~a。
function IsAssociatedNumber(z1,z2)
   local E={{-1,0},{1,0},{0,1},{0,-1}}
    for k,v in ipairs(E) do
	  local b=gMul(v, z1)
      if b[1]==z2[1] and b[2]==z2[2] then
          return true
      end
    end 
    return false	
end

function Div(z1,z2)
 local c={}
 local c1,c2
 c1,c2=ocdiv(z1[1],z1[2],z2[1],z2[2])
 c[1]=math.floor(c1+0.5)
 c[2]=math.floor(c2+0.5)  
 return c
end

function divide(z1,z2)
  local q=Div(z1,z2)
  local r=gSub(z1,gMul(q,z2))
  local bRet=(r[1]==0 and r[2]==0)
  return bRet,q,r
end

function gMod(z1,z2)
  local q=Div(z1,z2)
  local r=gSub(z1,gMul(q,z2))
  return r
end

function gGcd(z1,z2)
 local x = z1
 local y = z2
 if(Norm(z1)<Norm(z2))then
	 x = z2
	 y = z1
 end
 while (y[1]~=0 or y[2]~=0) do
  local ret,q,r=divide(x,y)
  x = y
  y = r
 end 
 return x
end

function gGcdex(z1,z2)
 local swapped = false
 local x = z1
 local y = z2
 if(Norm(z1)<Norm(z2))then
	 x = z2
	 y = z1
	 swapped = true
 end
 local xx ={0,0}
 local lx = {1,0}
 local yy = {1,0}
 local ly = {0,0}
 while (y[1]~=0 or y[2]~=0) do
  bret,q,r=divide(x,y)
  x = y
  y = r
  local tx = gSub(lx,gMul(q,xx))
  lx = xx
  xx = tx
  local ty = gSub(ly,gMul(q,yy))
  ly = yy
  yy = ty
 end
 if swapped then
  lx,ly=ly,lx
 end
 return x,lx,ly
end

local z1={9,11}
local z2={56,3}
local z3=gAdd(z1,z2)
local z4=gSub(z1,z2)
local z5=gMul(z1,z2)
local z6=Div(z1,z2)
io.write("z1=",gStr(z1),"\n","z2=",gStr(z2),"\n")
io.write("z1+z2=",gStr(z3),"\n")
io.write("z1-z2=",gStr(z4),"\n")
io.write("z1*z2=",gStr(z5),"\n")
io.write("z1/z2=",gStr(z6),"\n")
-- print(math.floor(-4.2-0.5))
-- print(math.floor(-3.7-0.5))
-- print(math.floor(-0.5))
-- print(math.floor(0.5))
-- print(math.floor(4.2+0.5))
-- print(math.floor(3.7+0.5))
--求7+5i和18+5i的最大公因数：1=(9-i)(7+5i)+(-4-i)(18+5i)。
--求112+i和-57+79i的最大公因数：(112+i,-57+79i)=4+7i。
local ret,q,r=divide({7,5},{18,5})
print(ret,gStr(q),gStr(r))
local z7a=gGcd({7,5},{18,5})
local z7,x7,y7=gGcdex({7,5},{18,5})
print(gStr(z7a),gStr(z7),gStr(x7),gStr(y7))
local z8a=gGcd({112,1},{-57,79})
local z8,x8,y8=gGcdex({112,1},{-57,79})
print(gStr(z8a),gStr(z8),gStr(x8),gStr(y8))

function get_key(value, tbl)
    for k,v in ipairs(tbl) do
      if v == value then
          return k
      end
    end
    return -1
end

function genN(n)
	local gN={}
	for m=0,n,1 do 
		for n=0,n,1 do 
			local mn=m*m+n*n
			local k=get_key(mn, gN)
			if k==-1 then 
				table.insert(gN,mn)
			end
		end
	end
	table.sort(gN , function(a , b)
			return a < b
		end)
	for k,v in pairs(gN) do  
		io.write(v, ",")
	end
	io.write("\n")
end

--小于等于N的所有范数
function genMaxN(N)
	local gN={}
	local N1=math.ceil(math.sqrt(N))
	for m=0,N1,1 do 
		for n=0,N1,1 do 
			local mn=m*m+n*n
			local k=get_key(mn, gN)
			if k==-1 and mn<=N then 
				table.insert(gN,mn)
			end
		end
	end
	table.sort(gN , function(a , b)
			return a < b
		end)
	for k,v in pairs(gN) do  
		io.write(v, ",")
	end
	io.write("\n")
end
genN(10)
genMaxN(200)

--[[
Z[i]/(m+ni)是N(m+ni)=m^2+n^2阶有限环，完全剩余系是x_m,n=m+ni，m=0,1,…,N(m,n)/(a,b)-1，n=0,1,…,(a,b)-1。
非素理想的情形：
Z[i]/(3+6i)是45阶环={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,i,1+i,2+i,3+i,4+i,5+i,6+i,7+i,8+i,9+i,10+i,11+i,12+i,13+i,14+i,2+2i,3+2i,4+2i,5+2i,6+2i,7+2i,8+2i,9+2i,10+2i,11+2i,12+2i,13+2i,14+2i},乘法单位元群Z[i]/(3+6i)^*是φ(3+6i)=φ(3)φ(1+2i)=20阶群
Z[i]/(2+2i)是8阶环={0,1,2,3,i,1+i,2+i,3+i}
Z[i]/(2)是4阶环={0,1,i,1+i}
素理想的情形：
Z[i]/(1+i)是2阶环F_2={0,1}
Z[i]/(1+2i)是5阶环F_5={0,1,2,3,4},乘法单位元群Z[i]/(1+2i)^*是4阶群C_4={1,2,3,4}。
Z[i]/(3)是9阶环F_9={0,1,2,i,1+i,2+i,2i,1+2i,2+2i},乘法单位元群Z[i]/(3)^*是8阶群C_8={1,2,i,1+i,2+i,2i,1+2i,2+2i}。
Z[i]/(2+3i)是N(2+3i)=13阶环F_13={0,1,2,3,4,5,6,7,8,9,10,11,12},乘法单位元群Z[i]/(2+3i)^*是12阶群C_12={1,2,3,4,5,6,7,8,9,10,11,12}
]]
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

function get_key2(value, tbl)
    for k,v in ipairs(tbl) do
      if is_equal(v, value) then
          return k
      end
    end
    return -1
end

function printAddTable(G,z,Func)
	local nR=get_len(G)	
	local rG={}
	for i=1,nR,1 do
	   local r=gMod(G[i],z)
	   table.insert(rG,r)
	end	
	for i=1,nR,1 do
		for j=1,nR,1 do
		   local ij=gMod(Func(rG[i],rG[j]),z)
		   local IJ=get_key2(ij,rG)
		   io.write(IJ, " ")
		   --io.write(IJ,"->",gStr(ij), " ")
		end
		io.write("\n")
	end
end

function FRZi(z,...)
	local S={}	
	local r0=gMod({0,0},z)
	table.insert(S,r0)
    local args = { ... }
	for i,v in pairs(args) do
	    local r1=gMod(v,z)	
		table.insert(S,r1)
	end	    		
	local cnt=0
	local cnt1=get_len(S)
	
	while(cnt1>cnt)	do
		cnt=get_len(S)
		for ki,vi in pairs(S) do
			for kj,vj in pairs(S) do
				local ij=gMod(gMul(vi,vj),z)
				local IJ=get_key2(ij,S)
				if(IJ==-1) then
					table.insert(S,ij)
				end	
				local ij1=gMod(gAdd(vi,vj),z)
				local IJ1=get_key2(ij1,S)
				if(IJ1==-1) then
					table.insert(S,ij1)
				end					
			end
		end		
		cnt1=get_len(S)
	end	
    return S	
end

function ZimodnZObj(z1,z)
	local S=FRZi(z,z1)
    return S	
end

function printZiSet(G)
	for k,v in pairs(G) do
		io.write(k, "->")
		io.write (gStr(v))
		io.write("\n")
	end
end

function printZiTable(S,z)
    local n=get_len(S)
	local s1="[R"..n.."Add]"
	local s2="[R"..n.."Mul]"	
	print(s1)
	printAddTable(S,z,gAdd)
	print(s2)
	printAddTable(S,z,gMul)
end

--local rR4={{0,0},{-1,0},{0,-1},{-1,-1}}
--print("[R4Add]")
--printAddTable(rR4,{2,0},gAdd)
--[[
local R4={{0,0},{1,0},{0,1},{1,1}}
print("Z[i]/(2)是4阶环R4_9={0,1,i,1+i}:")
print("[R4Add]")
printAddTable(R4,{2,0},gAdd)
print("[R4Mul]")
printAddTable(R4,{2,0},gMul)
local R8={{0,0},{1,0},{2,0},{3,0},{0,1},{1,1},{2,1},{3,1}}
print("Z[i]/(2+2i)是8阶环R8_22={0,1,2,3,i,1+i,2+i,3+i}:")
print("[R8Add]")
printAddTable(R8,{2,2},gAdd)
print("[R8Mul]")
printAddTable(R8,{2,2},gMul)
local R45={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0},{12,0},{13,0},{14,0},{0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1},{9,1},{10,1},{11,1},{12,1},{13,1},{14,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},{9,2},{10,2},{11,2},{12,2},{13,2},{14,2}}
print("Z[i]/(3+6i)是45阶环={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,i,1+i,2+i,3+i,4+i,5+i,6+i,7+i,8+i,9+i,10+i,11+i,12+i,13+i,14+i,2+2i,3+2i,4+2i,5+2i,6+2i,7+2i,8+2i,9+2i,10+2i,11+2i,12+2i,13+2i,14+2i}:")
print("[R45Add]")
printAddTable(R45,{3,6},gAdd)
print("[R45Mul]")
printAddTable(R45,{3,6},gMul)

local R10_3={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0}}
print("Z[i]/(3+i)是10阶环R10_3={0,1,2,3,4,5,6,7,8,9}:")
print("[R10Add]")
printAddTable(R10_3,{3,1},gAdd)
print("[R10Mul]")
printAddTable(R10_3,{3,1},gMul)

local R10={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0}}
print("Z[i]/(1+3i)是10阶环R10={0,1,2,3,4,5,6,7,8,9}:")
print("[R10Add]")
printAddTable(R10,{1,3},gAdd)
print("[R10Mul]")
printAddTable(R10,{1,3},gMul)

local R16={{0,0},{1,0},{2,0},{3,0},{0,1},{1,1},{2,1},{3,1},{0,2},{1,2},{2,2},{3,2},{0,3},{1,3},{2,3},{3,3}}
print("Z[i]/(4)是16阶环R16_105={0,1,2,3,i,1+i,2+i,3+i,1+2i,2+2i,3+2i,1+3i,2+3i,3+3i}:")
print("[R16Add]")
printAddTable(R16,{4,0},gAdd)
print("[R16Mul]")
printAddTable(R16,{4,0},gMul)

local R18={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2}}
print("Z[i]/(3+3i)是18阶环R18_22=F_9×F_2={0,1,2,3,4,5,i,1+i,2+i,3+i,4+i,5+i,2i,1+2i,2+2i,3+2i,4+2i,5+2i}:")
print("[R18Add]")
printAddTable(R18,{3,3},gAdd)
print("[R18Mul]")
printAddTable(R18,{3,3},gMul)

local F17={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0},{12,0},{13,0},{14,0},{15,0},{16,0}}
print("Z[i]/(4+i)是17阶环F_17={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}:")
print("[R17Add]")
printAddTable(F17,{4,1},gAdd)
print("[R17Mul]")
printAddTable(F17,{4,1},gMul)

local F13={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0},{12,0}}
print("Z[i]/(2+3i)是13阶环F_13={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}:")
print("[R13Add]")
printAddTable(F13,{2,3},gAdd)
print("[R13Mul]")
printAddTable(F13,{2,3},gMul)
]]
--[[
--R8_24=ZimodnZObj(1+i,4)
print("R8_24=ZimodnZObj(1+i,4)")
local R8_24=ZimodnZObj({1,1},{4,0})
printZiSet(R8_24)
printZiTable(R8_24,{4,0})

print("R8_21=ZimodnZObj(1+2i,4)")
local R8_21=ZimodnZObj({1,2},{4,0})
printZiSet(R8_21)
printZiTable(R8_21,{4,0})

print("R16_105=Z[i]/(4)=ZimodnZObj(2+i,4)")
local R16_105=ZimodnZObj({2,1},{4,0})
printZiSet(R16_105)
printZiTable(R16_105,{4,0})

print("R4_3=ZimodnZObj(1,4)=Z/(3)")
local R4_3=ZimodnZObj({1,0},{4,0})
printZiSet(R4_3)
printZiTable(R4_3,{4,0})

print("R4_4={0,2,2i,2+2i}mod4")
local R4_4=FRZi({4,0},{2,0},{0,2})
printZiSet(R4_4)
printZiTable(R4_4,{4,0})

--local R8={{0,0},{1,0},{2,0},{3,0},{0,1},{1,1},{2,1},{3,1}}
--print("Z[i]/(2+2i)是8阶环R8_22={0,1,2,3,i,1+i,2+i,3+i}:")
print("R4_5=ZimodnZObj(1+i,2+2i)")
local R4_5=ZimodnZObj({1,1},{2,2})
printZiSet(R4_5)
printZiTable(R4_5,{2,2})

print("R8_22=Z[i]/(2+2i)=ZimodnZObj(2+i,2+2i)")
local R8_22=ZimodnZObj({2,1},{2,2})
printZiSet(R8_22)
printZiTable(R8_22,{2,2})

print("R8_23=ZimodnZObj(2i,8)")
local R8_23=ZimodnZObj({0,2},{8,0})
printZiSet(R8_23)
printZiTable(R8_23,{8,0})

print("R8_16={0,2,4,6,4i,2+4i,4+4i,6+4i}mod8")
local R8_16=FRZi({8,0},{2,4},{0,4},{4,0},{2,0},{6,4},{4,4},{6,0})
printZiSet(R8_16)
printZiTable(R8_16,{8,0})

print("R16_109=ZimodnZObj(1+i,4+4i)")
local R16_109=ZimodnZObj({1,1},{4,4})
printZiSet(R16_109)
printZiTable(R16_109,{4,4})

print("R16_7=ZimodnZObj(1+2i,4+4i)")
local R16_7=ZimodnZObj({1,2},{4,4})
printZiSet(R16_7)
printZiTable(R16_7,{4,4})

print("R8_22a=ZimodnZObj(2+i,2+6i)")
local R8_22a=ZimodnZObj({2,1},{2,6})
printZiSet(R8_22a)
printZiTable(R8_22a,{2,6})

print("R8_22b=ZimodnZObj(8+i,6+2i)")
local R8_22b=ZimodnZObj({8,1},{6,2})
printZiSet(R8_22b)
printZiTable(R8_22b,{6,2})
]]
--[[
for i=0,19,1 do
	for j=0,3,1 do
		for i1=0,19,1 do
			for j1=0,3,1 do
			    if i+j~=0 and i1+j1~=0 and (i~=i1 or j~=j1) then
					local R8_=FRZi({4,8},{i,j},{i1,j1})
					if get_len(R8_)==8 then
						print(i,j,i1,j1)
					end
				end
			end	
		end
	end	
end	
]]
print("R8_")
local R8_=FRZi({4,8},{15,0},{1,2})
printZiSet(R8_)
printZiTable(R8_,{4,8})

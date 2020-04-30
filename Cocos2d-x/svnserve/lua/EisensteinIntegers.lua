function eAdd(z1,z2)
local z3 = {}
z3[1]=z1[1]+z2[1]
z3[2]=z1[2]+z2[2]
return z3
end

function eSub(z1,z2)
local z3 = {}
z3[1]=z1[1]-z2[1]
z3[2]=z1[2]-z2[2]
return z3
end

function eMul(z1,z2)
local z3 = {}
z3[1]=z1[1]*z2[1]-z1[2]*z2[2]
z3[2]=z1[1]*z2[2]+z1[2]*z2[1]-z1[2]*z2[2]
return z3
end

function eStr(z)
local s
if z[2]>=0 then
s=z[1].."+"..z[2].."ω"
else
s=z[1]..z[2].."ω"
end
return s
end

--a+bω和a+bω^2的范数都为(a+bω)(a+bω^2)=a^2-ab+b^2
function eNorm(z)
 return (z[1]*z[1]-z[1]*z[2]+z[2]*z[2])
end

function gNorm(z)
 return (z[1]*z[1]+z[2]*z[2])
end

--a+bω=a-b-bω^2的共轭为a+bω^2=a+b(-1-ω)=a-b-bω
function eConj(z)
	local fz = {}
	fz[1]=z[1]-z[2]
	fz[2]=-z[2]
	return fz
end

--定义：设a,b∈M，若存在ε使b=ε(·)a，则称b是a的相伴数，记作b~a。
--a+bω的6个相伴元：a+bω,-a-bω，-b+(a-b)ω，b+(b-a)ω，(b-a)-aω，(a-b)+aω，范数都是a^2-ab+b^2
--艾森斯坦整数有六个单位数（N(ξ)=1）：±1,±ω,±ω2，
function eIsAssociatedNumber(z1,z2)
   local E={{-1,0},{1,0},{0,1},{0,-1},{-1,-1},{1,1}}
    for k,v in ipairs(E) do
	  local b=eMul(v, z1)
      if b[1]==z2[1] and b[2]==z2[2] then
          return true
      end
    end 
    return false	
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

function ediv(a,b,c,d) 
    local e,f
	w=c*c+d*d-c*d
	if(w+1.0==1.0)then 
		e=1.0e+35*a/math.abs(a)
		f=1.0e+35*b/math.abs(b)
	else
		e=(a*c+b*d)/w
		f=(b*d+b*c-a*d)/w 
	end
	return e,f
end

--转化为复数域上的点
function e2g(a,b) 
    local x=a-0.5*b
	local y=0.866025*b
	return x,y
end

function eDis(z1,z2)
local x1,y1=z1[1],z1[2]
local x2,y2=z2[1],z2[2]
return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)
end

--找出最小值序号及最小值
function minimum(a)
	local mi=1
	local m=a[mi]
	for i,val in ipairs(a) do
		if val < m then
			mi = i
			m = val
		end
	end
	return m, mi
end

--最接近复数域上点的艾森斯坦整数
function Eis(x,y) 
    local a=x+0.57735*y
	local b=1.1547*y
	local z={}
	local a1=math.floor(a+0.5)
	local a2=a1
	local b1=math.floor(b+0.5)
	local b2=b1
	local drr={eDis({a1,b1},{a,b}),eDis({a1,b2},{a,b}),eDis({a2,b1},{a,b}),eDis({a2,b2},{a,b})} 
	local m,mi=minimum(drr)
	if mi==1 then
	   z[1]=a1
	   z[2]=b1
	elseif mi==2 then
	   z[1]=a1
	   z[2]=b2	
	elseif mi==3 then
	   z[1]=a2
	   z[2]=b1		
	elseif mi==4 then
	   z[1]=a2
	   z[2]=b2	
	end
	return z
end

function eDiv0(z1,z2)
 local c={}
 local c1,c2
 local x1,y1=e2g(z1[1],z1[2])
 local x2,y2=e2g(z2[1],z2[2])
 local x3,y3=ocdiv(x1,y1,x2,y2)
 c=Eis(x3,y3)
 return c
end

function eDiv(z1,z2)
 local c={}
 local c1,c2
 c1,c2=ediv(z1[1],z1[2],z2[1],z2[2])
 c[1]=math.floor(c1+0.5)
 c[2]=math.floor(c2+0.5)  
 return c
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

function edivide(z1,z2)
  local q=eDiv(z1,z2)
  local r=eSub(z1,eMul(q,z2))
  local bRet=(r[1]==0 and r[2]==0)
  return bRet,q,r
end

function eMod(z1,z2)
  local q=eDiv(z1,z2)
  local r=eSub(z1,eMul(q,z2))
  return r
end

function eGcd(z1,z2)
 local x = z1
 local y = z2
 if(eNorm(z1)<eNorm(z2))then
	 x = z2
	 y = z1
 end
 while (y[1]~=0 or y[2]~=0) do
  local ret,q,r=edivide(x,y)
  --print(ret,eStr(q),eStr(r),eStr(x),eStr(y))
  x = y
  y = r
 end 
 return x
end

local z1={9,11}
local z2={56,3}
local z3=eAdd(z1,z2)
local z4=eSub(z1,z2)
local z5=eMul(z1,z2)
local z6=eDiv(z1,z2)--距离z1/z2最近的艾森斯坦整数
io.write("z1=",eStr(z1),"\n","z2=",eStr(z2),"\n")
io.write("z1+z2=",eStr(z3),"\n")
io.write("z1-z2=",eStr(z4),"\n")
io.write("z1*z2=",eStr(z5),"\n")
io.write("z1/z2=",eStr(z6),"\n")
local ret,q,r=edivide({471,610},{56,3})
print(ret,eStr(q),eStr(r))
local z7a=eGcd({7,5},{18,5})
print("(7+5ω,18+5ω)=",eStr(z7a))
local z8a=eGcd({112,1},{-57,79})
print("(112+ω,-57+79ω)=",eStr(z8a))

function get_key(value, tbl)
    for k,v in ipairs(tbl) do
      if v == value then
          return k
      end
    end
    return -1
end

function geneN(n)
	local gN={}
	for m=0,n,1 do 
		for n=0,n,1 do 
			local mn=m*m+n*n-m*n
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
function geneMaxN(N)
	local gN={}
	local N1=N
	for m=0,N1,1 do 
		for n=0,N1,1 do 
			local mn=m*m+n*n-m*n
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
--geneN(10)
geneMaxN(200)
print(eNorm({1,-1}))

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

function printTable(G,z,Func)
	local nR=get_len(G)	
	local rG={}
	for i=1,nR,1 do
	   local r=eMod(G[i],z)
	   table.insert(rG,r)
	end	
	for i=1,nR,1 do
		for j=1,nR,1 do
		   local ij=eMod(Func(rG[i],rG[j]),z)
		   local IJ=get_key2(ij,rG)
		   io.write(IJ, " ")
		end
		io.write("\n")
	end
end

function FREi(z,...)
	local S={}	
	local r0=eMod({0,0},z)
	table.insert(S,r0)
    local args = { ... }
	for i,v in pairs(args) do
	    local r1=eMod(v,z)	
		table.insert(S,r1)
	end	    		
	local cnt=0
	local cnt1=get_len(S)
	
	while(cnt1>cnt)	do
		cnt=get_len(S)
		for ki,vi in pairs(S) do
			for kj,vj in pairs(S) do
				local ij=eMod(eMul(vi,vj),z)
				local IJ=get_key2(ij,S)
				if(IJ==-1) then
					table.insert(S,ij)
				end	
				local ij1=eMod(eAdd(vi,vj),z)
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

function EimodnZObj(z1,z)
	local S=FREi(z,z1)
    return S	
end

function printEiSet(G)
	for k,v in pairs(G) do
		io.write(k, "->")
		io.write (eStr(v))
		io.write("\n")
	end
end

function printEiTable(S,z)
    local n=get_len(S)
	local s1="[R"..n.."Add]"
	local s2="[R"..n.."Mul]"	
	print(s1)
	printTable(S,z,eAdd)
	print(s2)
	printTable(S,z,eMul)
end

local R3={{0,0},{1,0},{2,0}}
print("R3_2=Z[ω]/(1-ω)={0,1,2}:")
print("[R3Add]")
printTable(R3,{1,-1},eAdd)
print("[R3Mul]")
printTable(R3,{1,-1},eMul)

--有问题
local R4={{0,0},{1,0},{0,1},{1,1}}
print("R4_11=Z[ω]/(2):")
print("[R4Add]")
printTable(R4,{2,0},eAdd)
print("[R4Mul]")
printTable(R4,{2,0},eMul)

local R9={{0,0},{1,0},{2,0},{0,1},{1,1},{2,1},{0,2},{1,2},{2,2}}
print("R9_9=Z[ω]/(3)={0,1,2,ω,1+ω,2+ω,2ω,1+2ω,2+2ω}:")
print("[R9Add]")
printTable(R9,{3,0},eAdd)
print("[R9Mul]")
printTable(R9,{3,0},eMul)

--有问题
local R16={{0,0},{1,0},{2,0},{3,0},{0,1},{1,1},{2,1},{3,1},{0,2},{1,2},{2,2},{3,2},{0,3},{1,3},{2,3},{3,3}}
print("Z[ω]/(4):")
print("[R16Add]")
printTable(R16,{4,0},eAdd)
print("[R16Mul]")
printTable(R16,{4,0},eMul)

--有问题
local R12={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{0,1},{1,1},{2,1},{3,1},{4,1},{5,1}}
print("Z[ω]/(4+2ω):")
print("[R12Add]")
printTable(R12,{4,2},eAdd)
print("[R12Mul]")
printTable(R12,{4,2},eMul)

print("R8_21")
local R8_21=FREi({4,0},{1,2})
printEiSet(R8_21)
printEiTable(R8_21,{4,0})

print("R16_8=ZE3modnZObj(6+12ω,16)")
local R16_8=FREi({16,0},{6,12})
printEiSet(R16_8)
printEiTable(R16_8,{16,0})
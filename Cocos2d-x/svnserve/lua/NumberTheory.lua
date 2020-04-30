function Factorial(n)
    if n==0 or n==1 then
        return 1
    else
        return n * Factorial(n-1)
    end
end

--print("Enter a number : ")
--i = io.read("*number")   
for i=5,12,1 do     
	io.write(i,"!=",Factorial(i),"\n")
end

--求2个整数的最大公约数
function GcdInt(a,b)
	if(a*b<0) then
		return -GcdInt(math.abs(a),math.abs(b))
	end
	if(a<b) then
		local temp=a
		a=b
		b=temp
	end
	if(a%b==0)then
		return b
	else
		return GcdInt(a%b,b)
	end
end

local ret=GcdInt(12,32)
local ret1=GcdInt(-12,32)
local ret2=GcdInt(12,-32)
print(ret,ret1,ret2)

function Iscoprime(a,b)
	local ret=0
	if(GcdInt(a,b)==1)then
		ret=1
	end
	return ret
end

--φ(n)表示不大于n且与n互素的正整数个数、n阶循环群中n阶元的个数、本原n次单位根（n次单位原根）的个数、整数模n乘法群（模n既约剩余类）(Z/p^nZ)^×中与n互素剩余类的个数
function Phi(n)
	local ret=0
	if(n==1)then
		return 1
	end
	for i=1,n-1,1 do     
		ret=ret+Iscoprime(n,i)
	end	
	return ret
end

--T(n)表示n的正因子的个数、n阶循环群子群的个数、Z/nZ理想的个数
function Sigma0(n)
	local ret=0
	for d=1,n,1 do 
		if(n%d==0)then
			ret=ret+1
		end
	end
	return ret
end

--totient(12)=4
--|S(C_12)|=T(12)=|{1,2,3,4,6,12}|=6
print(Phi(12),Sigma0(12))

local v36={37,57,63,74,76}
for i,v in pairs(v36) do
	io.write("totient(",v,")=",Phi(v),"\n")
end	

function Mod(ret,n)
	if(ret<0)then
		local ret1=ret+(-ret+1)*n
		return ret1%n
	end
	return ret%n
end

function mod(ret,n)
	local raw_mod=ret%n
	if (raw_mod==0) then
		return 0
	elseif (ret>= 0) then
		return raw_mod
	else
		return raw_mod+n
	end
end

function inverse_mod_p(u,p)
	for i=1,p-1,1 do 
		if (Mod(u * i, p ) == 1)then
			return i
		end		
	end
	return nil
--[[
    local t1 = 0
    local t3 = 0
    local q  = 0
    local u1 = 1
    local u3 = u
    local v1 = 0
    local v3 = p
    local inv_v = 0
	
    while( v3 ~= 0)	do
        q = u3 / v3
        t1 = u1 - v1 * q
        t3 = u3 - v3 * q
        u1 = v1
        u3 = v3
        v1 = t1
        v3 = t3
    end	
    inv_v=mod(u1,p)
    if (mod(u * inv_v, p ) ~= 1)then
		return 0
	end
    return inv_v
]]--
end

function PowerMod(a,k,p)
    if k<0 then
	    local a1=inverse_mod_p(a,p)
	    return PowerMod(a1,-k,p)
	end
	local ans=1
	for i=1,k,1 do 
		ans=ans*a%p
	end
	return ans
end

function OrderMod(a,p)
	local k=1
	while(k<=p)	do
		if(PowerMod(a,k,p)==1)then
		 break
		end
		k=k+1
	end
	return k
end

function LogMod(b,a,p)
	local k=1
	while(k<=p)	do
		if(PowerMod(a,k,p)==b)then
		 break
		end
		k=k+1
	end
	return k
end

print(LogMod(57, 3, 113))
print(inverse_mod_p(5,17))
local bArr={-2,-1,0,1,2,4,8,16}
for i,v in pairs(bArr) do
	io.write("PowerMod(5,",v,",17)=",PowerMod(5,v,17),"\n")
end	

function is_primitive_root(a,p)
	local k=OrderMod(a,p)
	return k==Phi(p)
end

--计算模n的最小原根
function PrimitiveRootMod(n)
	for a=1,n-1,1 do
		local ret=is_primitive_root(a,n)
		if(ret)then
			return a
		end
	end
	return nil
end

io.write("在前30个正整数中,")
for n=1,30,1 do 
	if PrimitiveRootMod(n)==nil then 
		io.write(n,",")
	end
end
io.write("没有原根\n")
for n=1,30,1 do 
    local ret=PrimitiveRootMod(n)
	if ret~=nil then 
		io.write("lprimroot(",n,")=",ret,",")
	end
end
io.write("有原根\n")
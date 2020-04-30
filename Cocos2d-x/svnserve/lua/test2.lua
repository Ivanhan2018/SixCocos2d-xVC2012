-- test2.lua

function add(x,y)
    return x+y
end

function pythagorean(a,b) 
local c2 = a^2 + b^2 
return math.sqrt(c2) 
end

function fun(x)
    return math.sqrt(math.sqrt(4*x*x+1)-x*x-1)
end

complex={
__add=function(op1,op2)
             op = {}
             op.x = op1.x + op2.x
             op.y = op1.y + op2.y
             setmetatable(op,complex)
             return op
           end,

__sub=function(op1,op2)
 op = {}
 op.x = op1.x - op2.x
 op.y = op1.y - op2.y
 setmetatable(op,complex)
 return op
end,

__mul=function(op1,op2)
 op = {}
 op.x = op1.x * op2.x-op1.y * op2.y
 op.y = op1.x* op2.y + op2.x* op1.y
 setmetatable(op,complex)
 return op
end,

__div=function(op1,op2)
 op = {}
 op.x = (op1.x * op2.x+op1.y * op2.y)/(op2.x * op2.x+op2.y * op2.y)
 op.y = (-op1.x* op2.y + op2.x* op1.y)/(op2.x * op2.x+op2.y * op2.y)
 setmetatable(op,complex)
 return op
end,

create=function(o)
 o = o or {}
 setmetatable(o,complex)
 return o
end             
}
	
a=complex.create{x=1,y=1}
b=complex.create{x=3,y=4}
c = a + b
print(c.x, c.y)  -- 输出 4，5
d = a - b
print(d.x, d.y)  -- 输出 -2，-3
e = a * b
print(e.x, e.y)  -- 输出 -1，7
f = a / b
print(f.x, f.y)  -- 输出 0.28，-0.04

meta={
__add=function(op1,op2)
             op = {}
             op.x = op1.x + op2.x
             op.y = op1.y + op2.y
             return op
end
    }
	
a={x=1,y=1}
setmetatable(a,meta)
b={x=3,y=4}
c = a + b
print("c:"..c.x, c.y) -- 输出 4，5
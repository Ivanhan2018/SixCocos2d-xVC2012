--[[
------------------------------------
平面曲线轨迹库
------------------------------------
Ivan_han@2013/5/20 16:37:17
------------------------------------
]]

function Trace_1_8_1(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_8(5w/6,0)=(853.3,0)的第一种轨迹
          local P_1=ccp(0,487.5)
          local a=854
          local x=a*t
          local y=11840/(x-877)+500
          return ccp(x,y)
end

function Trace_1_8_2(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_8(5w/6,0)=(853.3,0)的第二种轨迹
          --local P_1=ccp(0,487.5)
          local a=854
          local x=a*t
          local y=-0.00067*x*x+487.5
          return ccp(x,y)
end

function Trace_1_8_3(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_8(5w/6,0)=(853.3,0)的第三种轨迹
          --local P_1=ccp(0,487.5)
          local a=854
          local x=a*t
          local y=500*math.exp(-0.0043*x)-12.5
          return ccp(x,y)
end

function Trace_1_9_1(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第一种轨迹
          --local P_1=ccp(0,487.5)
          local a=1100
          local x=a*t
          local y=-0.31738*x+487.5
          return ccp(x,y)
end

function Trace_1_9_2(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第二种轨迹
          --local P_1=ccp(0,487.5)
          local a=400
          local y=487.5-a*t
          local x=0.00969*(y-487.5)*(y-487.5)
          return ccp(x,y)
end

function Trace_1_9_3(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第三种轨迹
          --local P_1=ccp(0,487.5)
          local a=400
          local y=487.5-a*t
          local x=-0.00485*y*y+1152.63
          return ccp(x,y)
end

--顶点在右边界上、开口向左的抛物线，暂时不采用该轨迹
function Trace_1_9_4(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第四种轨迹
          --local P_1=ccp(0,487.5)
          local a=400
          local y=487.5-a*t
          local x=-0.00969*(y-162.5)*(y-162.5)+1024
          return ccp(x,y)
end

function Trace_9_1_1(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第一种轨迹
          --local P_9=ccp(1024,162.5)
          local a=1100
          local x=1024-a*t--与Trace_1_9_1(t)不同的地方
          local y=-0.31738*x+487.5
          return ccp(x,y)
end

--顶点在左边界上、开口向右的抛物线，暂时不采用该轨迹
function Trace_9_1_2(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第二种轨迹
          --local P_9=ccp(1024,162.5)
          local a=400
          local y=162.5+a*t--与Trace_1_9_2(t)不同的地方
          local x=0.00969*(y-487.5)*(y-487.5)
          return ccp(x,y)
end

function Trace_9_1_3(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第三种轨迹
          --local P_1=ccp(0,487.5)
          local a=400
          local y=162.5+a*t--与Trace_1_9_3(t)不同的地方
          local x=-0.00485*y*y+1152.63
          return ccp(x,y)
end

--顶点在右边界上、开口向左的抛物线
function Trace_9_1_4(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第四种轨迹
          --local P_9=ccp(1024,162.5)
          local a=400
          local y=162.5+a*t--与Trace_1_9_4(t)不同的地方
          local x=-0.00969*(y-162.5)*(y-162.5)+1024
          return ccp(x,y)
end

function Trace_9_16_1(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第一种轨迹
          --local P_9=ccp(1024,162.5)
          local a=1100
          local x=1024-a*t
          local y=0.00047*(x-1200)*(x-1200)+147.94
          return ccp(x,y)
end

function Trace_9_16_2(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第二种轨迹
          --local P_9=ccp(1024,162.5)
          local a=1100
          local x=1024-a*t
          local y=-0.00048*x*x+663.986
          return ccp(x,y)
end

function Trace_9_16_3(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第三种轨迹
          local P_9=ccp(1024,162.5)
          local P_16=ccp(170.7,650)
          local tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x); 
          local tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y); 
          local r=math.sqrt(tempx+tempy);--r=nT=2npiA,n=1,1.5,2,2.5,……
          local A=r/(math.pi*2)--200
          local arg=math.atan2(P_16.y-P_9.y,P_16.x-P_9.x);        
          --轨迹起点为P_9=(350,300)，振幅为A，周期为T=2piA，“辐角为arg的反正弦波”曲线轨迹
          --将2调大为2.5
          local x=A*2.5*math.pi*t
          local y=A*math.sin(-2.5*math.pi*t)--+表示"正正弦波"，-表示“反正弦波”
          local Pt=ccp(x*math.cos(arg)-y*math.sin(arg),x*math.sin(arg)+y*math.cos(arg))--(x,y)逆时针旋转a=arg之后变为(xcosa-ysina,xsina+ycosa)
          return ccp(P_9.x+Pt.x,P_9.y+Pt.y)        
end

--实际上从上边界出来后又从上边界进来了，最后从左边界出来
function Trace_9_16_4(t)
          --轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第三种轨迹
          local P_9=ccp(1024,162.5)
          local P_16=ccp(170.7,650)
          local tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x); 
          local tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y); 
          local r=math.sqrt(tempx+tempy);--r=nT=2npiA,n=1,1.5,2,2.5,……
          local A=r/(math.pi*2)--200
          local arg=math.atan2(P_16.y-P_9.y,P_16.x-P_9.x);        
          --轨迹起点为P_9=(350,300)，振幅为A，周期为T=2piA，“辐角为arg的正正弦波”曲线轨迹
          --将2调大为2.5
          local x=A*2.5*math.pi*t
          local y=A*math.sin(2.5*math.pi*t)--+表示"正正弦波"，-表示“反正弦波”，与Trace_9_16_3不同的地方
          local Pt=ccp(x*math.cos(arg)-y*math.sin(arg),x*math.sin(arg)+y*math.cos(arg))--(x,y)逆时针旋转a=arg之后变为(xcosa-ysina,xsina+ycosa)
          return ccp(P_9.x+Pt.x,P_9.y+Pt.y)        
end

function Trace_1_12_1(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第一种轨迹
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.19044*x+487.5
          return ccp(x,y)
end

function Trace_1_12_2(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第二种轨迹
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.00075*(x-300)*(x-300)+420
          return ccp(x,y)
end

function Trace_1_12_3(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第三种轨迹
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.00204*(x-380)*(x-380)+192.924
          return ccp(x,y)
end

--与x轴有两个交点、开口向上的抛物线，暂时不采用该轨迹
function Trace_1_12_4(t)
          --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第四种轨迹
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.00357*(x-400)*(x-400)-83.7
          return ccp(x,y)
end

function CosTrace(t)
          --轨迹起点为(350,400)，振幅为150的余弦曲线轨迹
          local C=ccp(350,400)
          local a=150
          local x=a*2*math.pi*t
          local y=a*math.cos(2*math.pi*t)-a
          return ccp(C.x+x,C.y+y)
end

function CircleTrace(t)
          --圆中心为(350,300)，半径为150，轨迹起点为(500,300)的逆时针圆轨迹
          local x=150*math.cos(2*math.pi*t)
          local y=150*math.sin(2*math.pi*t)
          return ccp(350+x,300+y)
end

function EllipseTrace(t)
          --椭圆中心为(350,300)，长半径为150，短半径为120，轨迹起点为(500,300)，焦点F_1为(260,300)，焦点F_2为(440,300)的逆时针椭圆轨迹
          local C=ccp(350,300)
          local a=150
          local b=120
          local c=90
          local x=a*math.cos(2*math.pi*t)
          local y=b*math.sin(2*math.pi*t)
          return ccp(C.x+x,C.y+y)
end

function SinTrace(t)
          --轨迹起点为(350,300)，振幅为150的正弦曲线轨迹
          local C=ccp(350,300)
          local a=150
          local x=a*2*math.pi*t
          local y=a*math.sin(2*math.pi*t)
          return ccp(C.x+x,C.y+y)
end

--[[
获得圆上点的坐标
参数说明：
startP--轨迹起点坐标
centerP--圆心坐标
deltArg--相对于轨迹起点的辐角主值增量	
]]
function GetCirclePos(startP,centerP,deltArg)
          local startarg=math.atan2(startP.y-centerP.y,startP.x-centerP.x);--轨迹起点相对于圆心的辐角主值
          local tempx=(startP.x-centerP.x)*(startP.x-centerP.x); 
		  local tempy=(startP.y-centerP.y)*(startP.y-centerP.y); 
		  local r=math.sqrt(tempx+tempy);--圆的半径
          local x=r*math.cos(startarg+deltArg)--圆上点相对于圆心的X坐标偏移
          local y=r*math.sin(startarg+deltArg)--圆上点相对于圆心的Y坐标偏移
          return ccp(centerP.x+x,centerP.y+y) 
end

--[[
圆轨迹
参数说明：
t----轨迹参数方程中的参数
startP----轨迹起点坐标
centerP----圆心坐标
direction----取值浮点数，表示圈数，正、负圈数分别表示逆、顺时针旋转
]]
--function CircleTraceFunc(t,startP,centerP,direction)
function CircleTraceFunc(t,startPx,startPy,centerPx,centerPy,direction)
          local startP=ccp(startPx,startPy)
          local centerP=ccp(centerPx,centerPy)
          --圆中心为centerP，半径为r，轨迹起点为startP的direction弧度圆轨迹
          local startarg=math.atan2(startP.y-centerP.y,startP.x-centerP.x);--轨迹起点相对于圆心的辐角主值
          local tempx=(startP.x-centerP.x)*(startP.x-centerP.x); 
		  local tempy=(startP.y-centerP.y)*(startP.y-centerP.y); 
		  local r=math.sqrt(tempx+tempy);--圆的半径 
          local x=r*math.cos(startarg+2*math.pi*t*direction)
          local y=r*math.sin(startarg+2*math.pi*t*direction)
          --return ccp(centerP.x+x-startPx,centerP.y+y-startPy)--改为相对位置以支持CCRepeatForever无限次重复动画
          return ccp(centerP.x+x,centerP.y+y)
end


--[[
直线运动和匀速圆周运动合成的轨迹，我们称之为摆线
过原点startP=(0,0)、半径为r的摆线参数方程为
x=r(a-sina)
y=r(1-cosa)
在这里实参数a是在弧度之下，圆滚动的角度。对每一个给出的a ，圆心的坐标为(ra,r)。 
参数说明：
t----轨迹参数方程中的参数
]]
function CycloidTrace(t)
          local startP=ccp(200,300)--摆线轨迹起点
          local direction=3
		  local r=50;
          local a=2*math.pi*t*direction 
          local x=r*(a-math.sin(a))
          local y=r*(1-math.cos(a))
          return ccp(startP.x+x,startP.y+y)
end

--[[
摆线轨迹
参数说明：
t----轨迹参数方程中的参数
startP----轨迹起点坐标
r----圆的半径
deltArg----取值浮点数，相对于轨迹起点的辐角主值增量
direction----拱形的个数
reserved----保留参数，reservedx保留，reservedy摆线轨迹整体逆时针旋转弧度
]]
--function CycloidTraceFunc(t,startPx,startPy,r,deltArg,direction)
function CycloidTraceFunc(t,startPx,startPy,r,deltArg,direction,reservedx,reservedy)
          local a=2*math.pi*t*direction         
          local x=r*(a-math.sin(a))
          local y=r*(1-math.cos(a)) 
          local startPt=ccp(x,y)
          local centerPt=ccp(r*a,r)--圆心坐标
		  local retPt0=GetCirclePos(startPt,centerPt,deltArg)
		  local retPt=ccp(retPt0.x*math.cos(reservedy)-retPt0.y*math.sin(reservedy),retPt0.x*math.sin(reservedy)+retPt0.y*math.cos(reservedy))--(x,y)逆时针旋转a之后变为(xcosa-ysina,xsina+ycosa)
          local startP=ccp(startPx,startPy)--摆线轨迹起点deltArg=0 
          return ccp(startP.x+retPt.x,startP.y+retPt.y)      
end

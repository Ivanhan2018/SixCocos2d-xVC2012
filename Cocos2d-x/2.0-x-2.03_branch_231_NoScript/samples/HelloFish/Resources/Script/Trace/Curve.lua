--[[
------------------------------------
ƽ�����߹켣��
------------------------------------
Ivan_han@2013/5/20 16:37:17
------------------------------------
]]

function Trace_1_8_1(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_8(5w/6,0)=(853.3,0)�ĵ�һ�ֹ켣
          local P_1=ccp(0,487.5)
          local a=854
          local x=a*t
          local y=11840/(x-877)+500
          return ccp(x,y)
end

function Trace_1_8_2(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_8(5w/6,0)=(853.3,0)�ĵڶ��ֹ켣
          --local P_1=ccp(0,487.5)
          local a=854
          local x=a*t
          local y=-0.00067*x*x+487.5
          return ccp(x,y)
end

function Trace_1_8_3(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_8(5w/6,0)=(853.3,0)�ĵ����ֹ켣
          --local P_1=ccp(0,487.5)
          local a=854
          local x=a*t
          local y=500*math.exp(-0.0043*x)-12.5
          return ccp(x,y)
end

function Trace_1_9_1(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵ�һ�ֹ켣
          --local P_1=ccp(0,487.5)
          local a=1100
          local x=a*t
          local y=-0.31738*x+487.5
          return ccp(x,y)
end

function Trace_1_9_2(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵڶ��ֹ켣
          --local P_1=ccp(0,487.5)
          local a=400
          local y=487.5-a*t
          local x=0.00969*(y-487.5)*(y-487.5)
          return ccp(x,y)
end

function Trace_1_9_3(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵ����ֹ켣
          --local P_1=ccp(0,487.5)
          local a=400
          local y=487.5-a*t
          local x=-0.00485*y*y+1152.63
          return ccp(x,y)
end

--�������ұ߽��ϡ���������������ߣ���ʱ�����øù켣
function Trace_1_9_4(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵ����ֹ켣
          --local P_1=ccp(0,487.5)
          local a=400
          local y=487.5-a*t
          local x=-0.00969*(y-162.5)*(y-162.5)+1024
          return ccp(x,y)
end

function Trace_9_1_1(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵ�һ�ֹ켣
          --local P_9=ccp(1024,162.5)
          local a=1100
          local x=1024-a*t--��Trace_1_9_1(t)��ͬ�ĵط�
          local y=-0.31738*x+487.5
          return ccp(x,y)
end

--��������߽��ϡ��������ҵ������ߣ���ʱ�����øù켣
function Trace_9_1_2(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵڶ��ֹ켣
          --local P_9=ccp(1024,162.5)
          local a=400
          local y=162.5+a*t--��Trace_1_9_2(t)��ͬ�ĵط�
          local x=0.00969*(y-487.5)*(y-487.5)
          return ccp(x,y)
end

function Trace_9_1_3(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵ����ֹ켣
          --local P_1=ccp(0,487.5)
          local a=400
          local y=162.5+a*t--��Trace_1_9_3(t)��ͬ�ĵط�
          local x=-0.00485*y*y+1152.63
          return ccp(x,y)
end

--�������ұ߽��ϡ����������������
function Trace_9_1_4(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵ����ֹ켣
          --local P_9=ccp(1024,162.5)
          local a=400
          local y=162.5+a*t--��Trace_1_9_4(t)��ͬ�ĵط�
          local x=-0.00969*(y-162.5)*(y-162.5)+1024
          return ccp(x,y)
end

function Trace_9_16_1(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵ�һ�ֹ켣
          --local P_9=ccp(1024,162.5)
          local a=1100
          local x=1024-a*t
          local y=0.00047*(x-1200)*(x-1200)+147.94
          return ccp(x,y)
end

function Trace_9_16_2(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵڶ��ֹ켣
          --local P_9=ccp(1024,162.5)
          local a=1100
          local x=1024-a*t
          local y=-0.00048*x*x+663.986
          return ccp(x,y)
end

function Trace_9_16_3(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵ����ֹ켣
          local P_9=ccp(1024,162.5)
          local P_16=ccp(170.7,650)
          local tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x); 
          local tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y); 
          local r=math.sqrt(tempx+tempy);--r=nT=2npiA,n=1,1.5,2,2.5,����
          local A=r/(math.pi*2)--200
          local arg=math.atan2(P_16.y-P_9.y,P_16.x-P_9.x);        
          --�켣���ΪP_9=(350,300)�����ΪA������ΪT=2piA��������Ϊarg�ķ����Ҳ������߹켣
          --��2����Ϊ2.5
          local x=A*2.5*math.pi*t
          local y=A*math.sin(-2.5*math.pi*t)--+��ʾ"�����Ҳ�"��-��ʾ�������Ҳ���
          local Pt=ccp(x*math.cos(arg)-y*math.sin(arg),x*math.sin(arg)+y*math.cos(arg))--(x,y)��ʱ����תa=arg֮���Ϊ(xcosa-ysina,xsina+ycosa)
          return ccp(P_9.x+Pt.x,P_9.y+Pt.y)        
end

--ʵ���ϴ��ϱ߽�������ִ��ϱ߽�����ˣ�������߽����
function Trace_9_16_4(t)
          --�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵ����ֹ켣
          local P_9=ccp(1024,162.5)
          local P_16=ccp(170.7,650)
          local tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x); 
          local tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y); 
          local r=math.sqrt(tempx+tempy);--r=nT=2npiA,n=1,1.5,2,2.5,����
          local A=r/(math.pi*2)--200
          local arg=math.atan2(P_16.y-P_9.y,P_16.x-P_9.x);        
          --�켣���ΪP_9=(350,300)�����ΪA������ΪT=2piA��������Ϊarg�������Ҳ������߹켣
          --��2����Ϊ2.5
          local x=A*2.5*math.pi*t
          local y=A*math.sin(2.5*math.pi*t)--+��ʾ"�����Ҳ�"��-��ʾ�������Ҳ�������Trace_9_16_3��ͬ�ĵط�
          local Pt=ccp(x*math.cos(arg)-y*math.sin(arg),x*math.sin(arg)+y*math.cos(arg))--(x,y)��ʱ����תa=arg֮���Ϊ(xcosa-ysina,xsina+ycosa)
          return ccp(P_9.x+Pt.x,P_9.y+Pt.y)        
end

function Trace_1_12_1(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵ�һ�ֹ켣
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.19044*x+487.5
          return ccp(x,y)
end

function Trace_1_12_2(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵڶ��ֹ켣
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.00075*(x-300)*(x-300)+420
          return ccp(x,y)
end

function Trace_1_12_3(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵ����ֹ켣
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.00204*(x-380)*(x-380)+192.924
          return ccp(x,y)
end

--��x�����������㡢�������ϵ������ߣ���ʱ�����øù켣
function Trace_1_12_4(t)
          --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵ����ֹ켣
          --local P_1=ccp(0,487.5)
          local a=950
          local x=a*t
          local y=0.00357*(x-400)*(x-400)-83.7
          return ccp(x,y)
end

function CosTrace(t)
          --�켣���Ϊ(350,400)�����Ϊ150���������߹켣
          local C=ccp(350,400)
          local a=150
          local x=a*2*math.pi*t
          local y=a*math.cos(2*math.pi*t)-a
          return ccp(C.x+x,C.y+y)
end

function CircleTrace(t)
          --Բ����Ϊ(350,300)���뾶Ϊ150���켣���Ϊ(500,300)����ʱ��Բ�켣
          local x=150*math.cos(2*math.pi*t)
          local y=150*math.sin(2*math.pi*t)
          return ccp(350+x,300+y)
end

function EllipseTrace(t)
          --��Բ����Ϊ(350,300)�����뾶Ϊ150���̰뾶Ϊ120���켣���Ϊ(500,300)������F_1Ϊ(260,300)������F_2Ϊ(440,300)����ʱ����Բ�켣
          local C=ccp(350,300)
          local a=150
          local b=120
          local c=90
          local x=a*math.cos(2*math.pi*t)
          local y=b*math.sin(2*math.pi*t)
          return ccp(C.x+x,C.y+y)
end

function SinTrace(t)
          --�켣���Ϊ(350,300)�����Ϊ150���������߹켣
          local C=ccp(350,300)
          local a=150
          local x=a*2*math.pi*t
          local y=a*math.sin(2*math.pi*t)
          return ccp(C.x+x,C.y+y)
end

--[[
���Բ�ϵ������
����˵����
startP--�켣�������
centerP--Բ������
deltArg--����ڹ켣���ķ�����ֵ����	
]]
function GetCirclePos(startP,centerP,deltArg)
          local startarg=math.atan2(startP.y-centerP.y,startP.x-centerP.x);--�켣��������Բ�ĵķ�����ֵ
          local tempx=(startP.x-centerP.x)*(startP.x-centerP.x); 
		  local tempy=(startP.y-centerP.y)*(startP.y-centerP.y); 
		  local r=math.sqrt(tempx+tempy);--Բ�İ뾶
          local x=r*math.cos(startarg+deltArg)--Բ�ϵ������Բ�ĵ�X����ƫ��
          local y=r*math.sin(startarg+deltArg)--Բ�ϵ������Բ�ĵ�Y����ƫ��
          return ccp(centerP.x+x,centerP.y+y) 
end

--[[
Բ�켣
����˵����
t----�켣���������еĲ���
startP----�켣�������
centerP----Բ������
direction----ȡֵ����������ʾȦ����������Ȧ���ֱ��ʾ�桢˳ʱ����ת
]]
--function CircleTraceFunc(t,startP,centerP,direction)
function CircleTraceFunc(t,startPx,startPy,centerPx,centerPy,direction)
          local startP=ccp(startPx,startPy)
          local centerP=ccp(centerPx,centerPy)
          --Բ����ΪcenterP���뾶Ϊr���켣���ΪstartP��direction����Բ�켣
          local startarg=math.atan2(startP.y-centerP.y,startP.x-centerP.x);--�켣��������Բ�ĵķ�����ֵ
          local tempx=(startP.x-centerP.x)*(startP.x-centerP.x); 
		  local tempy=(startP.y-centerP.y)*(startP.y-centerP.y); 
		  local r=math.sqrt(tempx+tempy);--Բ�İ뾶 
          local x=r*math.cos(startarg+2*math.pi*t*direction)
          local y=r*math.sin(startarg+2*math.pi*t*direction)
          --return ccp(centerP.x+x-startPx,centerP.y+y-startPy)--��Ϊ���λ����֧��CCRepeatForever���޴��ظ�����
          return ccp(centerP.x+x,centerP.y+y)
end


--[[
ֱ���˶�������Բ���˶��ϳɵĹ켣�����ǳ�֮Ϊ����
��ԭ��startP=(0,0)���뾶Ϊr�İ��߲�������Ϊ
x=r(a-sina)
y=r(1-cosa)
������ʵ����a���ڻ���֮�£�Բ�����ĽǶȡ���ÿһ��������a ��Բ�ĵ�����Ϊ(ra,r)�� 
����˵����
t----�켣���������еĲ���
]]
function CycloidTrace(t)
          local startP=ccp(200,300)--���߹켣���
          local direction=3
		  local r=50;
          local a=2*math.pi*t*direction 
          local x=r*(a-math.sin(a))
          local y=r*(1-math.cos(a))
          return ccp(startP.x+x,startP.y+y)
end

--[[
���߹켣
����˵����
t----�켣���������еĲ���
startP----�켣�������
r----Բ�İ뾶
deltArg----ȡֵ������������ڹ켣���ķ�����ֵ����
direction----���εĸ���
reserved----����������reservedx������reservedy���߹켣������ʱ����ת����
]]
--function CycloidTraceFunc(t,startPx,startPy,r,deltArg,direction)
function CycloidTraceFunc(t,startPx,startPy,r,deltArg,direction,reservedx,reservedy)
          local a=2*math.pi*t*direction         
          local x=r*(a-math.sin(a))
          local y=r*(1-math.cos(a)) 
          local startPt=ccp(x,y)
          local centerPt=ccp(r*a,r)--Բ������
		  local retPt0=GetCirclePos(startPt,centerPt,deltArg)
		  local retPt=ccp(retPt0.x*math.cos(reservedy)-retPt0.y*math.sin(reservedy),retPt0.x*math.sin(reservedy)+retPt0.y*math.cos(reservedy))--(x,y)��ʱ����תa֮���Ϊ(xcosa-ysina,xsina+ycosa)
          local startP=ccp(startPx,startPy)--���߹켣���deltArg=0 
          return ccp(startP.x+retPt.x,startP.y+retPt.y)      
end

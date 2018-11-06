#include "Curve.h"
#include "Ship.h"//add by Ivan_han 20130617

CCPoint Curve::Trace_1_8_1(float t)
{
	// --轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_8(5w/6,0)=(853.3,0)的第一种轨迹
	CCPoint P_1=ccp(0,487.5);
	int a=854;
	float x=a*t;
	float y=11840/(x-877)+500;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_8_2(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_8(5w/6,0)=(853.3,0)的第二种轨迹
	//--local P_1=ccp(0,487.5)
	int a=854;
	float x=a*t;
	float y=-0.00067*x*x+487.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_8_3(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_8(5w/6,0)=(853.3,0)的第三种轨迹
	//--local P_1=ccp(0,487.5)
	int a=854;
	float x=a*t;
	float y=500*exp(-0.0043*x)-12.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_9_1(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第一种轨迹
	//--local P_1=ccp(0,487.5)
	int a=1100;
	float x=a*t;
	float y=-0.31738*x+487.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_9_2(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第二种轨迹
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=487.5-a*t;
	float x=0.00969*(y-487.5)*(y-487.5);
	return ccp(x,y);
}

CCPoint Curve::Trace_1_9_3(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第三种轨迹
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=487.5-a*t;
	float x=-0.00485*y*y+1152.63;
	return ccp(x,y);
}

//--顶点在右边界上、开口向左的抛物线，暂时不采用该轨迹
CCPoint Curve::Trace_1_9_4(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_9(w,0.25h)=(1024,162.5)的第四种轨迹
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=487.5-a*t;
	float x=-0.00969*(y-162.5)*(y-162.5)+1024;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_1_1(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第一种轨迹
	//--local P_9=ccp(1024,162.5)
	int a=1100;
	float x=1024-a*t;//--与Trace_1_9_1(t)不同的地方
	float y=-0.31738*x+487.5;
	return ccp(x,y);
}

//--顶点在左边界上、开口向右的抛物线，暂时不采用该轨迹
CCPoint Curve::Trace_9_1_2(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第二种轨迹
	//--local P_9=ccp(1024,162.5)
	int a=400;
	float y=162.5+a*t;//--与Trace_1_9_2(t)不同的地方
	float x=0.00969*(y-487.5)*(y-487.5);
	return ccp(x,y);
}

CCPoint Curve::Trace_9_1_3(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第三种轨迹
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=162.5+a*t;//--与Trace_1_9_3(t)不同的地方
	float x=-0.00485*y*y+1152.63;
	return ccp(x,y);
}

//--顶点在右边界上、开口向左的抛物线
CCPoint Curve::Trace_9_1_4(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_1(0,0.75h)=(0,487.5)的第四种轨迹
	//--local P_9=ccp(1024,162.5)
	int a=400;
	float y=162.5+a*t;//--与Trace_1_9_4(t)不同的地方
	float x=-0.00969*(y-162.5)*(y-162.5)+1024;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_16_1(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第一种轨迹
	//--local P_9=ccp(1024,162.5)
	int a=1100;
	float x=1024-a*t;
	float y=0.00047*(x-1200)*(x-1200)+147.94;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_16_2(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第二种轨迹
	//--local P_9=ccp(1024,162.5)
	int a=1100;
	float x=1024-a*t;
	float y=-0.00048*x*x+663.986;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_16_3(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第三种轨迹
	CCPoint P_9=ccp(1024,162.5);
	CCPoint P_16=ccp(170.7,650);
	float tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x);
	float tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y);
	float r=sqrt(tempx+tempy);//--r=nT=2npiA,n=1,1.5,2,2.5,……
	float A=r/(M_PI*2);//--200;
	float arg=atan2(P_16.y-P_9.y,P_16.x-P_9.x);        
	//--轨迹起点为P_9=(350,300)，振幅为A，周期为T=2piA，“辐角为arg的反正弦波”曲线轨迹
	//--将2调大为2.5
	float x=A*2.5*M_PI*t;
	float y=A*sin(-2.5*M_PI*t);//--+表示"正正弦波"，-表示“反正弦波”
	CCPoint Pt=ccp(x*cos(arg)-y*sin(arg),x*sin(arg)+y*cos(arg));//--(x,y)逆时针旋转a=arg之后变为(xcosa-ysina,xsina+ycosa)
	return ccp(P_9.x+Pt.x,P_9.y+Pt.y);
}

//--实际上从上边界出来后又从上边界进来了，最后从左边界出来
CCPoint Curve::Trace_9_16_4(float t)
{
	//--轨迹起点为P_9(w,0.25h)=(1024,162.5)，轨迹终点为P_16(w/6,h)=(170.7,650)的第三种轨迹
	CCPoint P_9=ccp(1024,162.5);
	CCPoint P_16=ccp(170.7,650);
	float tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x); 
	float tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y); 
	float r=sqrt(tempx+tempy);//--r=nT=2npiA,n=1,1.5,2,2.5,……
	float A=r/(M_PI*2);//--200
	float arg=atan2(P_16.y-P_9.y,P_16.x-P_9.x);
	//--轨迹起点为P_9=(350,300)，振幅为A，周期为T=2piA，“辐角为arg的正正弦波”曲线轨迹
	//--将2调大为2.5
	float x=A*2.5*M_PI*t;
	float y=A*sin(2.5*M_PI*t);//--+表示"正正弦波"，-表示“反正弦波”，与Trace_9_16_3不同的地方
	CCPoint Pt=ccp(x*cos(arg)-y*sin(arg),x*sin(arg)+y*cos(arg));//--(x,y)逆时针旋转a=arg之后变为(xcosa-ysina,xsina+ycosa)
	return ccp(P_9.x+Pt.x,P_9.y+Pt.y);
}

CCPoint Curve::Trace_1_12_1(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第一种轨迹
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.19044*x+487.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_12_2(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第二种轨迹
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.00075*(x-300)*(x-300)+420;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_12_3(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第三种轨迹
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.00204*(x-380)*(x-380)+192.924;
	return ccp(x,y);
}

//--与x轴有两个交点、开口向上的抛物线，暂时不采用该轨迹
CCPoint Curve::Trace_1_12_4(float t)
{
	//--轨迹起点为P_1(0,0.75h)=(0,487.5)，轨迹终点为P_12(5w/6,h)=(853.3,650)的第四种轨迹
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.00357*(x-400)*(x-400)-83.7;
	return ccp(x,y);
}

CCPoint Curve::Ellipse0Trace(float t)
{
	//--轨迹起点为(2,1)，半径为1的圆轨迹
	float t1=2*M_PI*t;
	CCPoint ret=ccp(1+cos(t1),1+sin(t1));
	//W=2,H=2,W1=1024,H1=650
	CCPoint ret1=CShipMgr::ScaleTrans(2,2,1024,650,ret);
	return ret1;
}

CCPoint Curve::CosTrace(float t)
{
	//--轨迹起点为(350,400)，振幅为150的余弦曲线轨迹
	CCPoint C=ccp(350,400);
	int a=150;
	float x=a*2*M_PI*t;
	float y=a*cos(2*M_PI*t)-a;
	return ccp(C.x+x,C.y+y);
}

CCPoint Curve::CircleTrace(float t)
{
	//--圆中心为(350,300)，半径为150，轨迹起点为(500,300)的逆时针圆轨迹
	float x=150*cos(2*M_PI*t);
	float y=150*sin(2*M_PI*t);
	return ccp(350+x,300+y);
}

CCPoint Curve::EllipseTrace(float t)
{
	//--椭圆中心为(350,300)，长半径为150，短半径为120，轨迹起点为(500,300)，焦点F_1为(260,300)，焦点F_2为(440,300)的逆时针椭圆轨迹
	CCPoint C=ccp(350,300);
	int a=150;
	int b=120;
	int c=90;
	float x=a*cos(2*M_PI*t);
	float y=b*sin(2*M_PI*t);
	return ccp(C.x+x,C.y+y);
}

CCPoint Curve::SinTrace(float t)
{
	//--轨迹起点为(350,300)，振幅为150的正弦曲线轨迹
	CCPoint C=ccp(350,300);
	int a=150;
	float x=a*2*M_PI*t;
	float y=a*sin(2*M_PI*t);
	return ccp(C.x+x,C.y+y);
}

CCPoint Curve::ArchimedesSpiralTrace(float t)
{
	int n=4;
	float arg=M_PI/2;
	t=2*M_PI*t*n+arg;
	//中心坐标及参数(x_0=0,y_0=200,a=20)
	int x_0=512;
	int y_0=325;
	int a=20;
	float x=(x_0+(a*t)*cos(t));
	float y=(y_0+(a*t)*sin(t));
	return CCPoint(x,y);
}

CCPoint Curve::ArchimedesSpiralTraceFunc(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy)
{
	t=2*M_PI*t*direction+deltArg;
	//中心坐标及参数(x_0=startPx=0,y_0=startPy=200,a=r=20)
	int x_0=startPx;
	int y_0=startPy;
	float x=(x_0+(r*t)*cos(t));
	float y=(y_0+(r*t)*sin(t));
	return CCPoint(x,y);
}

CCPoint Curve::ArchimedesSpiralTraceFunc1(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy)
{
	float t1=2*M_PI*t*direction+deltArg;
	float x=2*M_PI*direction*r*(cos(t1)-t1*sin(t1));
	float y=2*M_PI*direction*r*(sin(t1)+t1*cos(t1));
	return CCPoint(x,y);
}

CCPoint Curve::GoStopGoLineTrace(float t)
{
	//--轨迹起点为A(200,300)，停顿点B(600,300)和停顿时间为[0.3,0.7]，轨迹终点为C(1000,300)的走停走直线轨迹
	//CCPoint A=ccp(200,300);
	//CCPoint B=ccp(600,300);
	//CCPoint C=ccp(1000,300);
	if(t<0.3)
		return ccp(200+t*400/0.3,300);
	if(t>=0.3 && t<0.7)
		return ccp(600,300);
	if(t>0.7)
		return ccp(600+(t-0.7)*400/0.3,300);
	return ccp(0,0);
}

CCPoint Curve::GoStopGoLineTrace(float t,float Ax,float Ay,float Cx,float Cy,float Lambda,float tA,float tC)
{
	if(Lambda==-1||tA==0||tC==0)
		return ccp(0,0);
	float Bx=(Ax+Lambda*Cx)/(1+Lambda);
	float By=(Ay+Lambda*Cy)/(1+Lambda);
	if(t<tA)
		return ccp(Ax+t*(Bx-Ax)/tA,Ay+t*(By-Ay)/tA);
	if(t>=tA && t<tC)
		return ccp(Bx,By);
	if(t>tC)
		return ccp(Bx+(t-tA)*(Cx-Bx)/tC,By+(t-tA)*(Cy-By)/tC);
	return ccp(0,0);
}

//--[[
//获得圆上点的坐标
//参数说明：
//startP--轨迹起点坐标
//centerP--圆心坐标
//deltArg--相对于轨迹起点的辐角主值增量	
//]]
CCPoint Curve::GetCirclePos(CCPoint startP,CCPoint centerP,float deltArg)
{
	float startarg=atan2(startP.y-centerP.y,startP.x-centerP.x);//--轨迹起点相对于圆心的辐角主值
	float tempx=(startP.x-centerP.x)*(startP.x-centerP.x);
	float tempy=(startP.y-centerP.y)*(startP.y-centerP.y);
	float r=sqrt(tempx+tempy);//--圆的半径
	float x=r*cos(startarg+deltArg);//--圆上点相对于圆心的X坐标偏移
	float y=r*sin(startarg+deltArg);//圆上点相对于圆心的Y坐标偏移
	return ccp(centerP.x+x,centerP.y+y);
}

//--[[
//圆轨迹
//参数说明：
//t----轨迹参数方程中的参数
//startP----轨迹起点坐标
//centerP----圆心坐标
//direction----取值浮点数，表示圈数，正、负圈数分别表示逆、顺时针旋转
//]]
//--function CircleTraceFunc(t,startP,centerP,direction)
CCPoint Curve::CircleTraceFunc(float t,float startPx,float startPy,float centerPx,float centerPy,float direction)
{
          CCPoint startP=ccp(startPx,startPy);
          CCPoint centerP=ccp(centerPx,centerPy);
          //--圆中心为centerP，半径为r，轨迹起点为startP的direction弧度圆轨迹
          float startarg=atan2(startP.y-centerP.y,startP.x-centerP.x);//--轨迹起点相对于圆心的辐角主值
          float tempx=(startP.x-centerP.x)*(startP.x-centerP.x); 
		  float tempy=(startP.y-centerP.y)*(startP.y-centerP.y); 
		  float r=sqrt(tempx+tempy);//--圆的半径 
          float x=r*cos(startarg+2*M_PI*t*direction);
          float y=r*sin(startarg+2*M_PI*t*direction);
          //--return ccp(centerP.x+x-startPx,centerP.y+y-startPy)--改为相对位置以支持CCRepeatForever无限次重复动画
          return ccp(centerP.x+x,centerP.y+y);
}


//--[[
//直线运动和匀速圆周运动合成的轨迹，我们称之为摆线
//过原点startP=(0,0)、半径为r的摆线参数方程为
//x=r(a-sina)
//y=r(1-cosa)
//在这里实参数a是在弧度之下，圆滚动的角度。对每一个给出的a ，圆心的坐标为(ra,r)。 
//参数说明：
//t----轨迹参数方程中的参数
//]]
CCPoint Curve::CycloidTrace(float t)
{
	CCPoint startP=ccp(200,300);//--摆线轨迹起点
	int direction=3;
	int r=50;
	float a=2*M_PI*t*direction ;
	float x=r*(a-sin(a));
	float y=r*(1-cos(a));
	return ccp(startP.x+x,startP.y+y);
}

//--[[
//摆线轨迹
//参数说明：
//t----轨迹参数方程中的参数
//startP----轨迹起点坐标
//r----圆的半径
//deltArg----取值浮点数，相对于轨迹起点的辐角主值增量
//direction----拱形的个数
//reserved----保留参数，reservedx保留，reservedy摆线轨迹整体逆时针旋转弧度
//]]
//--function CycloidTraceFunc(t,startPx,startPy,r,deltArg,direction)
CCPoint Curve::CycloidTraceFunc(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy)
{
	float a=2*M_PI*t*direction;
	float x=r*(a-sin(a));
	float y=r*(1-cos(a));
	CCPoint startPt=ccp(x,y);
	CCPoint centerPt=ccp(r*a,r);//--圆心坐标
	CCPoint retPt0=GetCirclePos(startPt,centerPt,deltArg);
	CCPoint retPt=ccp(retPt0.x*cos(reservedy)-retPt0.y*sin(reservedy),retPt0.x*sin(reservedy)+retPt0.y*cos(reservedy));//--(x,y)逆时针旋转a之后变为(xcosa-ysina,xsina+ycosa)
	CCPoint startP=ccp(startPx,startPy);//--摆线轨迹起点deltArg=0
	return ccp(startP.x+retPt.x,startP.y+retPt.y);
}

//摆线CycloidTraceFunc的切向量
CCPoint Curve::CycloidTraceFunc1(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy)
{
	float a=2*M_PI*t*direction;
	float x=r*(1-cos(a))*2*M_PI*direction;
	float y=r*(sin(a))*2*M_PI*direction;
	//切向量(x,y)逆时针旋转deltArg+reservedy
	float Arg=atan2(y,x);
	Arg=Arg+deltArg+reservedy;
	return ccp(cos(Arg),sin(Arg));
}

CurveHelper::CurveHelper()
{
	//第CurveLibIndex=0种任意曲线轨迹库
	int CurveLibIndex=0;
	m_CurveLib.insert(make_pair(MakeLongLong(0,CurveLibIndex),Curve::Ellipse0Trace));
	//m_CurveLib.insert(make_pair(MakeLongLong(0,CurveLibIndex),Curve::CosTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(1,CurveLibIndex),Curve::CircleTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(2,CurveLibIndex),Curve::EllipseTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(3,CurveLibIndex),Curve::SinTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(4,CurveLibIndex),Curve::CycloidTrace));

	//第CurveLibIndex=1种任意曲线轨迹库，W=1024,H=650,W1=1280,H1=733
	CurveLibIndex=1;
	m_CurveLib.insert(make_pair(MakeLongLong(0,CurveLibIndex),Curve::Trace_1_8_1));
	m_CurveLib.insert(make_pair(MakeLongLong(1,CurveLibIndex),Curve::Trace_1_8_2));
	m_CurveLib.insert(make_pair(MakeLongLong(2,CurveLibIndex),Curve::Trace_1_8_3));
	m_CurveLib.insert(make_pair(MakeLongLong(3,CurveLibIndex),Curve::Trace_1_9_1));
	m_CurveLib.insert(make_pair(MakeLongLong(4,CurveLibIndex),Curve::Trace_1_9_2));
	m_CurveLib.insert(make_pair(MakeLongLong(5,CurveLibIndex),Curve::Trace_1_9_3));
	m_CurveLib.insert(make_pair(MakeLongLong(6,CurveLibIndex),Curve::Trace_1_9_4));
	m_CurveLib.insert(make_pair(MakeLongLong(7,CurveLibIndex),Curve::Trace_9_1_1));
	m_CurveLib.insert(make_pair(MakeLongLong(8,CurveLibIndex),Curve::Trace_9_1_2));
	m_CurveLib.insert(make_pair(MakeLongLong(9,CurveLibIndex),Curve::Trace_9_1_3));
	m_CurveLib.insert(make_pair(MakeLongLong(10,CurveLibIndex),Curve::Trace_9_1_4));
	m_CurveLib.insert(make_pair(MakeLongLong(11,CurveLibIndex),Curve::Trace_9_16_1));
	m_CurveLib.insert(make_pair(MakeLongLong(12,CurveLibIndex),Curve::Trace_9_16_2));
	m_CurveLib.insert(make_pair(MakeLongLong(13,CurveLibIndex),Curve::Trace_9_16_3));
	m_CurveLib.insert(make_pair(MakeLongLong(14,CurveLibIndex),Curve::Trace_9_16_4));
	m_CurveLib.insert(make_pair(MakeLongLong(15,CurveLibIndex),Curve::Trace_1_12_1));
	m_CurveLib.insert(make_pair(MakeLongLong(16,CurveLibIndex),Curve::Trace_1_12_2));
	m_CurveLib.insert(make_pair(MakeLongLong(17,CurveLibIndex),Curve::Trace_1_12_3));
	m_CurveLib.insert(make_pair(MakeLongLong(18,CurveLibIndex),Curve::Trace_1_12_4));
}
CurveHelper::~CurveHelper()
{
	m_CurveLib.clear();
}

long long CurveHelper::MakeLongLong(int LO32,int HI32)
{
	return LO32+(long long)HI32<<32;
}

CurveHelper& CurveHelper::Instance()
{
	static CurveHelper curveHelper;
	return curveHelper;
}

//轨迹索引->轨迹方程
pFuncTrace0 CurveHelper::GetCurve(long long Index)const
{
	map<long long,pFuncTrace0>::const_iterator iter = m_CurveLib.find( Index );
	if( iter != m_CurveLib.end() )
		return iter->second;
	return NULL;
}


pFuncTrace0 CurveHelper::GetCurve(int CurveLibIndex,int CurveIndex)const
{
	long long Index=MakeLongLong(CurveIndex,CurveLibIndex);
	return GetCurve(Index);
}

pFuncTrace0 CurveHelper::GetCurve(CCPoint arg1)const
{
	int CurveLibIndex=(int)arg1.x;
	int CurveIndex=(int)arg1.y;
	return GetCurve(CurveLibIndex,CurveIndex);
}




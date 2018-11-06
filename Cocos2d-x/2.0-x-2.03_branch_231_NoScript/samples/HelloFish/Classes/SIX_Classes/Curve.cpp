#include "Curve.h"
#include "Ship.h"//add by Ivan_han 20130617

CCPoint Curve::Trace_1_8_1(float t)
{
	// --�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_8(5w/6,0)=(853.3,0)�ĵ�һ�ֹ켣
	CCPoint P_1=ccp(0,487.5);
	int a=854;
	float x=a*t;
	float y=11840/(x-877)+500;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_8_2(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_8(5w/6,0)=(853.3,0)�ĵڶ��ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=854;
	float x=a*t;
	float y=-0.00067*x*x+487.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_8_3(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_8(5w/6,0)=(853.3,0)�ĵ����ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=854;
	float x=a*t;
	float y=500*exp(-0.0043*x)-12.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_9_1(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵ�һ�ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=1100;
	float x=a*t;
	float y=-0.31738*x+487.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_9_2(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵڶ��ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=487.5-a*t;
	float x=0.00969*(y-487.5)*(y-487.5);
	return ccp(x,y);
}

CCPoint Curve::Trace_1_9_3(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵ����ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=487.5-a*t;
	float x=-0.00485*y*y+1152.63;
	return ccp(x,y);
}

//--�������ұ߽��ϡ���������������ߣ���ʱ�����øù켣
CCPoint Curve::Trace_1_9_4(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_9(w,0.25h)=(1024,162.5)�ĵ����ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=487.5-a*t;
	float x=-0.00969*(y-162.5)*(y-162.5)+1024;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_1_1(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵ�һ�ֹ켣
	//--local P_9=ccp(1024,162.5)
	int a=1100;
	float x=1024-a*t;//--��Trace_1_9_1(t)��ͬ�ĵط�
	float y=-0.31738*x+487.5;
	return ccp(x,y);
}

//--��������߽��ϡ��������ҵ������ߣ���ʱ�����øù켣
CCPoint Curve::Trace_9_1_2(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵڶ��ֹ켣
	//--local P_9=ccp(1024,162.5)
	int a=400;
	float y=162.5+a*t;//--��Trace_1_9_2(t)��ͬ�ĵط�
	float x=0.00969*(y-487.5)*(y-487.5);
	return ccp(x,y);
}

CCPoint Curve::Trace_9_1_3(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵ����ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=400;
	float y=162.5+a*t;//--��Trace_1_9_3(t)��ͬ�ĵط�
	float x=-0.00485*y*y+1152.63;
	return ccp(x,y);
}

//--�������ұ߽��ϡ����������������
CCPoint Curve::Trace_9_1_4(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_1(0,0.75h)=(0,487.5)�ĵ����ֹ켣
	//--local P_9=ccp(1024,162.5)
	int a=400;
	float y=162.5+a*t;//--��Trace_1_9_4(t)��ͬ�ĵط�
	float x=-0.00969*(y-162.5)*(y-162.5)+1024;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_16_1(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵ�һ�ֹ켣
	//--local P_9=ccp(1024,162.5)
	int a=1100;
	float x=1024-a*t;
	float y=0.00047*(x-1200)*(x-1200)+147.94;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_16_2(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵڶ��ֹ켣
	//--local P_9=ccp(1024,162.5)
	int a=1100;
	float x=1024-a*t;
	float y=-0.00048*x*x+663.986;
	return ccp(x,y);
}

CCPoint Curve::Trace_9_16_3(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵ����ֹ켣
	CCPoint P_9=ccp(1024,162.5);
	CCPoint P_16=ccp(170.7,650);
	float tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x);
	float tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y);
	float r=sqrt(tempx+tempy);//--r=nT=2npiA,n=1,1.5,2,2.5,����
	float A=r/(M_PI*2);//--200;
	float arg=atan2(P_16.y-P_9.y,P_16.x-P_9.x);        
	//--�켣���ΪP_9=(350,300)�����ΪA������ΪT=2piA��������Ϊarg�ķ����Ҳ������߹켣
	//--��2����Ϊ2.5
	float x=A*2.5*M_PI*t;
	float y=A*sin(-2.5*M_PI*t);//--+��ʾ"�����Ҳ�"��-��ʾ�������Ҳ���
	CCPoint Pt=ccp(x*cos(arg)-y*sin(arg),x*sin(arg)+y*cos(arg));//--(x,y)��ʱ����תa=arg֮���Ϊ(xcosa-ysina,xsina+ycosa)
	return ccp(P_9.x+Pt.x,P_9.y+Pt.y);
}

//--ʵ���ϴ��ϱ߽�������ִ��ϱ߽�����ˣ�������߽����
CCPoint Curve::Trace_9_16_4(float t)
{
	//--�켣���ΪP_9(w,0.25h)=(1024,162.5)���켣�յ�ΪP_16(w/6,h)=(170.7,650)�ĵ����ֹ켣
	CCPoint P_9=ccp(1024,162.5);
	CCPoint P_16=ccp(170.7,650);
	float tempx=(P_9.x-P_16.x)*(P_9.x-P_16.x); 
	float tempy=(P_9.y-P_16.y)*(P_9.y-P_16.y); 
	float r=sqrt(tempx+tempy);//--r=nT=2npiA,n=1,1.5,2,2.5,����
	float A=r/(M_PI*2);//--200
	float arg=atan2(P_16.y-P_9.y,P_16.x-P_9.x);
	//--�켣���ΪP_9=(350,300)�����ΪA������ΪT=2piA��������Ϊarg�������Ҳ������߹켣
	//--��2����Ϊ2.5
	float x=A*2.5*M_PI*t;
	float y=A*sin(2.5*M_PI*t);//--+��ʾ"�����Ҳ�"��-��ʾ�������Ҳ�������Trace_9_16_3��ͬ�ĵط�
	CCPoint Pt=ccp(x*cos(arg)-y*sin(arg),x*sin(arg)+y*cos(arg));//--(x,y)��ʱ����תa=arg֮���Ϊ(xcosa-ysina,xsina+ycosa)
	return ccp(P_9.x+Pt.x,P_9.y+Pt.y);
}

CCPoint Curve::Trace_1_12_1(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵ�һ�ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.19044*x+487.5;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_12_2(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵڶ��ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.00075*(x-300)*(x-300)+420;
	return ccp(x,y);
}

CCPoint Curve::Trace_1_12_3(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵ����ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.00204*(x-380)*(x-380)+192.924;
	return ccp(x,y);
}

//--��x�����������㡢�������ϵ������ߣ���ʱ�����øù켣
CCPoint Curve::Trace_1_12_4(float t)
{
	//--�켣���ΪP_1(0,0.75h)=(0,487.5)���켣�յ�ΪP_12(5w/6,h)=(853.3,650)�ĵ����ֹ켣
	//--local P_1=ccp(0,487.5)
	int a=950;
	float x=a*t;
	float y=0.00357*(x-400)*(x-400)-83.7;
	return ccp(x,y);
}

CCPoint Curve::Ellipse0Trace(float t)
{
	//--�켣���Ϊ(2,1)���뾶Ϊ1��Բ�켣
	float t1=2*M_PI*t;
	CCPoint ret=ccp(1+cos(t1),1+sin(t1));
	//W=2,H=2,W1=1024,H1=650
	CCPoint ret1=CShipMgr::ScaleTrans(2,2,1024,650,ret);
	return ret1;
}

CCPoint Curve::CosTrace(float t)
{
	//--�켣���Ϊ(350,400)�����Ϊ150���������߹켣
	CCPoint C=ccp(350,400);
	int a=150;
	float x=a*2*M_PI*t;
	float y=a*cos(2*M_PI*t)-a;
	return ccp(C.x+x,C.y+y);
}

CCPoint Curve::CircleTrace(float t)
{
	//--Բ����Ϊ(350,300)���뾶Ϊ150���켣���Ϊ(500,300)����ʱ��Բ�켣
	float x=150*cos(2*M_PI*t);
	float y=150*sin(2*M_PI*t);
	return ccp(350+x,300+y);
}

CCPoint Curve::EllipseTrace(float t)
{
	//--��Բ����Ϊ(350,300)�����뾶Ϊ150���̰뾶Ϊ120���켣���Ϊ(500,300)������F_1Ϊ(260,300)������F_2Ϊ(440,300)����ʱ����Բ�켣
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
	//--�켣���Ϊ(350,300)�����Ϊ150���������߹켣
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
	//�������꼰����(x_0=0,y_0=200,a=20)
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
	//�������꼰����(x_0=startPx=0,y_0=startPy=200,a=r=20)
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
	//--�켣���ΪA(200,300)��ͣ�ٵ�B(600,300)��ͣ��ʱ��Ϊ[0.3,0.7]���켣�յ�ΪC(1000,300)����ͣ��ֱ�߹켣
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
//���Բ�ϵ������
//����˵����
//startP--�켣�������
//centerP--Բ������
//deltArg--����ڹ켣���ķ�����ֵ����	
//]]
CCPoint Curve::GetCirclePos(CCPoint startP,CCPoint centerP,float deltArg)
{
	float startarg=atan2(startP.y-centerP.y,startP.x-centerP.x);//--�켣��������Բ�ĵķ�����ֵ
	float tempx=(startP.x-centerP.x)*(startP.x-centerP.x);
	float tempy=(startP.y-centerP.y)*(startP.y-centerP.y);
	float r=sqrt(tempx+tempy);//--Բ�İ뾶
	float x=r*cos(startarg+deltArg);//--Բ�ϵ������Բ�ĵ�X����ƫ��
	float y=r*sin(startarg+deltArg);//Բ�ϵ������Բ�ĵ�Y����ƫ��
	return ccp(centerP.x+x,centerP.y+y);
}

//--[[
//Բ�켣
//����˵����
//t----�켣���������еĲ���
//startP----�켣�������
//centerP----Բ������
//direction----ȡֵ����������ʾȦ����������Ȧ���ֱ��ʾ�桢˳ʱ����ת
//]]
//--function CircleTraceFunc(t,startP,centerP,direction)
CCPoint Curve::CircleTraceFunc(float t,float startPx,float startPy,float centerPx,float centerPy,float direction)
{
          CCPoint startP=ccp(startPx,startPy);
          CCPoint centerP=ccp(centerPx,centerPy);
          //--Բ����ΪcenterP���뾶Ϊr���켣���ΪstartP��direction����Բ�켣
          float startarg=atan2(startP.y-centerP.y,startP.x-centerP.x);//--�켣��������Բ�ĵķ�����ֵ
          float tempx=(startP.x-centerP.x)*(startP.x-centerP.x); 
		  float tempy=(startP.y-centerP.y)*(startP.y-centerP.y); 
		  float r=sqrt(tempx+tempy);//--Բ�İ뾶 
          float x=r*cos(startarg+2*M_PI*t*direction);
          float y=r*sin(startarg+2*M_PI*t*direction);
          //--return ccp(centerP.x+x-startPx,centerP.y+y-startPy)--��Ϊ���λ����֧��CCRepeatForever���޴��ظ�����
          return ccp(centerP.x+x,centerP.y+y);
}


//--[[
//ֱ���˶�������Բ���˶��ϳɵĹ켣�����ǳ�֮Ϊ����
//��ԭ��startP=(0,0)���뾶Ϊr�İ��߲�������Ϊ
//x=r(a-sina)
//y=r(1-cosa)
//������ʵ����a���ڻ���֮�£�Բ�����ĽǶȡ���ÿһ��������a ��Բ�ĵ�����Ϊ(ra,r)�� 
//����˵����
//t----�켣���������еĲ���
//]]
CCPoint Curve::CycloidTrace(float t)
{
	CCPoint startP=ccp(200,300);//--���߹켣���
	int direction=3;
	int r=50;
	float a=2*M_PI*t*direction ;
	float x=r*(a-sin(a));
	float y=r*(1-cos(a));
	return ccp(startP.x+x,startP.y+y);
}

//--[[
//���߹켣
//����˵����
//t----�켣���������еĲ���
//startP----�켣�������
//r----Բ�İ뾶
//deltArg----ȡֵ������������ڹ켣���ķ�����ֵ����
//direction----���εĸ���
//reserved----����������reservedx������reservedy���߹켣������ʱ����ת����
//]]
//--function CycloidTraceFunc(t,startPx,startPy,r,deltArg,direction)
CCPoint Curve::CycloidTraceFunc(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy)
{
	float a=2*M_PI*t*direction;
	float x=r*(a-sin(a));
	float y=r*(1-cos(a));
	CCPoint startPt=ccp(x,y);
	CCPoint centerPt=ccp(r*a,r);//--Բ������
	CCPoint retPt0=GetCirclePos(startPt,centerPt,deltArg);
	CCPoint retPt=ccp(retPt0.x*cos(reservedy)-retPt0.y*sin(reservedy),retPt0.x*sin(reservedy)+retPt0.y*cos(reservedy));//--(x,y)��ʱ����תa֮���Ϊ(xcosa-ysina,xsina+ycosa)
	CCPoint startP=ccp(startPx,startPy);//--���߹켣���deltArg=0
	return ccp(startP.x+retPt.x,startP.y+retPt.y);
}

//����CycloidTraceFunc��������
CCPoint Curve::CycloidTraceFunc1(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy)
{
	float a=2*M_PI*t*direction;
	float x=r*(1-cos(a))*2*M_PI*direction;
	float y=r*(sin(a))*2*M_PI*direction;
	//������(x,y)��ʱ����תdeltArg+reservedy
	float Arg=atan2(y,x);
	Arg=Arg+deltArg+reservedy;
	return ccp(cos(Arg),sin(Arg));
}

CurveHelper::CurveHelper()
{
	//��CurveLibIndex=0���������߹켣��
	int CurveLibIndex=0;
	m_CurveLib.insert(make_pair(MakeLongLong(0,CurveLibIndex),Curve::Ellipse0Trace));
	//m_CurveLib.insert(make_pair(MakeLongLong(0,CurveLibIndex),Curve::CosTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(1,CurveLibIndex),Curve::CircleTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(2,CurveLibIndex),Curve::EllipseTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(3,CurveLibIndex),Curve::SinTrace));
	//m_CurveLib.insert(make_pair(MakeLongLong(4,CurveLibIndex),Curve::CycloidTrace));

	//��CurveLibIndex=1���������߹켣�⣬W=1024,H=650,W1=1280,H1=733
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

//�켣����->�켣����
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




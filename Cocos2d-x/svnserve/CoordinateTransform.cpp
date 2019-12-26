// CoordinateTransform.cpp : implementation file
//

//#include "stdafx.h"
#include "CoordinateTransform.h"

/////////////////////////////////////////////////////////////////////////////
// CCoordinateTransform
const double a80 = 6378140.000,f80 = 298.257;    //80
//const double a36 = 6378210.000,f36 = 298.600;    //54
const double a36 = 6378245.000,f36 = 298.300;    //54
const double a54 = 6378245.000,f54 = 298.300;
const double a83 = 6378136.000,f83 = 298.257;    //83
const double a84 = 6378137.000,f84 = 298.2572236;//WGS84参数
const double offset = 500000.000;

CCoordinateTransform::CCoordinateTransform()
{
	m_CentreLongitude = 117;
	m_BandNo	= 0;
}
 
CCoordinateTransform::~CCoordinateTransform()
{

}


double * CCoordinateTransform::gcc(double a,double f)
{
	static double ab[6];
	double a7,e2;
	int i;
	if(f<=0.5) return NULL;
	e2=2/f-1/f/f;
	ab[0]=pow(e2,5)*43659.0/65536.0+pow(e2,4)*11025.0/16384.0+1.0;
	ab[0]+=e2*e2*45.0/64.0+pow(e2,3)*175.0/256.0+e2*0.75;
	ab[1]=e2*0.75+e2*e2*15.0/16.0+pow(e2,3)*525.0/512.0;
	ab[1]+=pow(e2,4)*2205.0/2048.0+pow(e2,5)*72765.0/65536.0 ;
	ab[2]=e2*e2*15.0/64.0+pow(e2,3)*105.0/256.0;
	ab[2]+=pow(e2,4)*2205.0/4096.0+pow(e2,5)*10395.0/16384.0;
	ab[3]=pow(e2,3)*35.0/512.0+pow(e2,4)*315.0/2048.0;
	ab[3]+=pow(e2,5)*31185.0/131072.0;
	ab[4]=pow(e2,4)*315.0/16384.0+pow(e2,5)*3465.0/65536.0;
	ab[5]=pow(e2,5)*693.0/131072.0;
	a7=a*(-e2+1.0);
	ab[0]*=a7;
	for (i=1;i<6;i++)
	ab[i]*=pow(-1.0,i)*a7/(2.0*i);
	return ab;
}

double *GaussCalculte(double a,double f)
{  
	static double ab[6]; 
	double a7,e2; 
	int i; 
	if(f<=0.5) 
		return NULL; 
	e2=2/f-1/f/f; 
	ab[0]=pow(e2,5)*43659.0/65536.0+pow(e2,4)*11025.0/16384.0+1.0; 
	ab[0]+=e2*e2*45.0/64.0+pow(e2,3)*175.0/256.0+e2*0.75; 
	ab[1]=e2*0.75+e2*e2*15.0/16.0+pow(e2,3)*525.0/512.0; 
	ab[1]+=pow(e2,4)*2205.0/2048.0+pow(e2,5)*72765.0/65536.0 ; 
	ab[2]=e2*e2*15.0/64.0+pow(e2,3)*105.0/256.0; 
	ab[2]+=pow(e2,4)*2205.0/4096.0+pow(e2,5)*10395.0/16384.0; 
	ab[3]=pow(e2,3)*35.0/512.0+pow(e2,4)*315.0/2048.0; 
	ab[3]+=pow(e2,5)*31185.0/131072.0; 
	ab[4]=pow(e2,4)*315.0/16384.0+pow(e2,5)*3465.0/65536.0; 
	ab[5]=pow(e2,5)*693.0/131072.0; 
	a7=a*(-e2+1.0); 
	ab[0]*=a7; 
	for (i=1;i<6;i++)
		ab[i]*=pow(-1.0,i)*a7/(2.0*i); 
	return ab;
}

// 高斯投影转换
void GaussCalc(double L, double B, double& X, double& Y)
{
 // 椭球体短半轴 
 //double a = 6378245;     // 北京54
 //double b = 6356863.0188;    // 北京54
 double a = 6378140;     // 西安80
 double b = 6356755.2882;    // 西安80
 //double a = 6378137;      // WGS 84
 //double b = 6356752.3142;    // WGS 84
 double f = (a - b) / a;     // 扁率
 double e = 1 - (b / a) * (b / a);  // 第一偏心率平方
 double e2 = (a / b) * (a / b) - 1;  // 第二偏心率平方
 double dblPI = 3.1415926535898 / 180.0; // 角度弧度转换参数
 // 求经度所在带号
 int ZoneWide = 3; // 带宽 3度带或6度带
 int ZoneNumber;  // 带号
 double L0;   // 中央经度
 if (3 == ZoneWide)
 {// 3度带
  ZoneNumber = int(L - ZoneWide / 2) / ZoneWide + 1;
 }
 else// if (6 == ZoneWide)
 {// 6度带
  ZoneNumber = int(L) / ZoneWide + 1;
 }
 
 // 中央经度
 L0 = (ZoneNumber - 1) * ZoneWide + ZoneWide / 2;
 L0 = 120;
 // 角度转换成弧度
 double L1 = L * dblPI;
 double B1 = B * dblPI;
 L0 = L0 * dblPI;

 // 子午圈曲率半径
 double R = a * (1 - e) / sqrt((1 - e * sin(B1) * sin(B1)) * (1 - e * sin(B1) * sin(B1)) * (1 - e * sin(B1) * sin(B1)));
 double T = tan(B1) * tan(B1);
 double C = e2 * cos(B1) * cos(B1);
 double A = (L1 - L0) * cos(B1);
 // 子午线弧长
 double M = a * ((1 - e / 4 - 3 * e * e / 64 - 5 * e * e * e / 256) * B1
  - (3 * e / 8 + 3 * e * e / 32 + 45 * e * e * e / 1024) * sin(2 * B1)
  + (15 * e * e / 256 + 45 * e * e * e / 1024) * sin(4 * B1)
  - (35 * e * e * e / 3072) * sin(6 * B1));
 // 卯酉圈曲率半径
 double N = a / sqrt(1 - e * sin(B1) * sin(B1));
 // 东纬度偏移
 double FE = ZoneNumber * 1000000L + 500000L;
 // 高斯 - 克吕格投影比例因子
 double k0 = 1;

 // 根据投影公式计算点在投影坐标系中的位置
 X = FE + k0 * N * (A + (1 - T + C) * A * A * A / 6 + (5 - 18 * T + T * T + 14 * C - 58 * T * C) * A * A * A * A * A / 120);
 Y = k0 * (M + N * tan(B1) * (A * A / 2 + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24)
  + (61 - 58 * T + T * T + 270 * C - 330 * T * C) * A * A * A * A * A * A / 720);
}

#define RAD 57.295779 //rad = degree * 3.1415926 / 180 ;=>rad = degree / RAD
void Gauss2( double L , double B , double& x , double& y )
{
 // 椭球体
 //double a = 6378245;      // 北京54
 //double b = 6356863.0188;    // 北京54
 double a = 6378140;     // 西安80
 double b = 6356755.2882;    // 西安80
 //double a = 6378137;     // WGS 84
 //double b = 6356752.3142;    // WGS 84
 double f = (a - b) / a;     // 扁率
 double e = 1 - (b / a) * (b / a);  // 第一偏心率平方
 double e2 = (a / b) * (a / b) - 1;  // 第二偏心率平方

 // 求经度所在带号
 int ZoneWide = 3; // 带宽 3度带或6度带
 int ZoneNumber;  // 带号
 double L0;   // 中央经度
 if (3 == ZoneWide)
 {// 3度带
  ZoneNumber = int(L - ZoneWide / 2) / ZoneWide + 1;
  L0 = ZoneNumber * ZoneWide ;
 }
 else// if (6 == ZoneWide)
 {// 6度带
  ZoneNumber = int(L) / ZoneWide + 1;
  L0 = ZoneNumber*ZoneWide - 3;
 }
 
 //L、B转化成度
 L = int( L ) + (int( L*100 ) - int( L )*100)/double(60) + (L*10000 - int(L*100)*100)/3600;
 B = int( B ) + (int( B*100 ) - int( B )*100)/double(60) + (B*10000 - int(B*100)*100)/3600;
 
 double A = (L - L0)/RAD;
 double TB = tan( B/RAD );
 double TB2 = TB*TB;
 double CB = cos( B/RAD );
 double C = e2*CB*CB;
 double C2 = 1 + C;
 double N = (a*a/b) / sqrt( C2 );//卯酉曲率半径
 double P = A*A*CB*CB;
 double P2 = sin( B/RAD );
 double Q = P2*P2;
 double R = 32005.78006+Q*(133.92133+Q*0.7031);
 x = 6367558.49686*B/RAD - P2*CB*R + ( ( ( (TB2-58)*TB2 + 61)*P/30+(4*N+5)*C2-TB2)*P/12+1)*N*CB*P/2;
 y = 500000+( ( ( (TB2-18)*TB2-(58*TB2-14)*N+5)*P/20+C2-TB2)*P/6+1)*N*(A*CB);//为保证为正数，向西便偏移500公里，即＋500,000；
}

BOOL CCoordinateTransform::BlToGauss_84xy(double b,double l,double *x,double *y,GUASSTYPE GaussType,int BandNo,BOOL bAddBandNo)
{
	m_ProjectPara.a = a84;
	m_ProjectPara.f = f84;
	m_ProjectPara.offset = 500000.00;

	GetBandAndCentreLongitudeByBl(b,l,GaussType,BandNo);

	l = l -	m_CentreLongitude;
	BlToGaussxy(b,l,y,x);
	*x += m_ProjectPara.offset;

	if(bAddBandNo)
		*x += m_BandNo * 1.0E6;
	
	return TRUE;
}



BOOL CCoordinateTransform::BlToGaussxy(double b,double l,double *x,double *y)
{
	double t,n,g,m0,x0;
	static double a = m_ProjectPara.a;
	static double f = m_ProjectPara.f;
	static double e2=2./f-1/f/f;
	static double e1=e2/(-e2+1.0);
	static double* p1 = gcc(a,f);

//	if(f==0.)  return FALSE;  //  /0
	
	l *= DEGTORAD;
	b *= DEGTORAD;

	
	x0=*p1*b+*(p1+1)*sin(2.0*b)+*(p1+2)*sin(4.0*b);
	x0+=*(p1+3)*sin(6.0*b)+*(p1+4)*sin(8.0*b)+*(p1+5)*sin(10.0*b);
	t=tan(b);
	n=a/sqrt(1.0-e2*sin(b)*sin(b));
	g=e1*cos(b)*cos(b);
	m0=l*cos(b);
	*x=x0+n*t*m0*m0/2.0;
	*x+=(5.0-t*t+9.0*g+4.0*g*g)*n*t*pow(m0,4)/24.0;
	*x+=n*pow(m0,6)*t*(61.0-58.0*t*t+t*t*t*t)/720.0;
	*y=n*m0+n*pow(m0,3)*(1.0-t*t+g)/6.0;
	*y+=(5.0-18.0*t*t+t*t*t*t+14.0*g-58.0*g*t*t)*n*pow(m0,5)/120.0;

	return TRUE;
}

void CCoordinateTransform::GetBandAndCentreLongitudeByBl(double b,double l,GUASSTYPE GaussType,int BandNo)
{
	switch(GaussType)
	{
	case CCoordinateTransform::bandOneAndHalf:
		if(BandNo != CT_NONE)
			m_BandNo = BandNo ;
		else
			m_BandNo = 1 ;
//		m_CentreLongitude = 1;
		break;
	case CCoordinateTransform::bandThree:
		if(BandNo != CT_NONE)
			m_BandNo = BandNo ;
		else
			m_BandNo = (int)((l - 1.50)/3.0) + 1;
//		m_CentreLongitude = m_BandNo * 3.0;
		break;
	case CCoordinateTransform::bandSix:
		if(BandNo != CT_NONE)
			m_BandNo = BandNo ;
		else
			m_BandNo = (int)(l/6.0 + 1.0);
//		m_CentreLongitude = m_BandNo * 6.0 - 3.0;
		break;
	case CCoordinateTransform::bandNine:
		if(BandNo != CT_NONE)
			m_BandNo = BandNo ;
		else
			m_BandNo = 0;
//		m_CentreLongitude = 0;
		break;
	case CCoordinateTransform::bandNone:
		m_BandNo = 0;
		break;
	}
}

void CCoordinateTransform::SetCentreLongitude(double dCentreLongitude)
{
	m_CentreLongitude = dCentreLongitude;
}
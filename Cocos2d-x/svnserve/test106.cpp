#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include "CoordinateTransform.h"

// 引用测试
int Add(const int &n,const int &m)
{
  return n+m;
}

// 范围
typedef struct _GM_Rect
{
  double dMinX;
  double dMinY;
  double dMaxX;
  double dMaxY;
}GM_Rect;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

int main()
{
	CCoordinateTransform		coorTrans;
	coorTrans.SetCentreLongitude(117);

	double dx=0,dy=0;
    double	adfX=100;
    double	adfY=200;
	int		nVertices=10;
    double	dfXMin=100;
    double	dfYMin=200;
    double	dfXMax=600;
    double	dfYMax=700;

	double b=53.332649;
	double l=121.488441;
	//double b=27.000125543;
	//double l=115.195840802;
	double x=0,y=0;
	coorTrans.BlToGauss_84xy(b,l,&x,&y);
	printf("b=%f,l=%f—BlToGauss_84xy—>x=%f,y=%f\n",b,l,x,y);
	//coorTrans.BlToGauss_84xy(adfY,adfX,&dx,&dy);

	//GM_Rect m_pBound;
	//m_pBound.dMinX	= DBL_MAX;
	//m_pBound.dMaxX	= -DBL_MAX;
	//m_pBound.dMinY	= DBL_MAX;
	//m_pBound.dMaxY	= -DBL_MAX;

	//m_pBound.dMinX	= min(dx,m_pBound.dMinX);
	//m_pBound.dMinY	= min(dy,m_pBound.dMinY);
	//m_pBound.dMaxX	= max(dx,m_pBound.dMaxX);
	//m_pBound.dMaxY	= max(dy,m_pBound.dMaxY);	

	//coorTrans.BlToGauss_84xy(dfYMin,dfXMin,&dx,&dy);
	//dfXMin	= dx;
	//dfYMin	= dy;

	//coorTrans.BlToGauss_84xy(dfYMax,dfXMax,&dx,&dy);
	//dfXMax	= dx;
	//dfYMax	= dy;

	double d = 1049175.3061662777;
	char sz[100]={0};
	sprintf(sz, "%d米",(int)d);
	char sz1[100]={0};
	sprintf(sz1, "%d米",d);

	//system("pause");
	return 0;
}
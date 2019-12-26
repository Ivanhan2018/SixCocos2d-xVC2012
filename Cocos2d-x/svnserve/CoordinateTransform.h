// CoordinateTransform.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoordinateTransform window
#ifndef _COORDINATETRANSFORM
#define _COORDINATETRANSFORM
#define DEGTORAD  0.017453292519722

// add by Ivan_han 20141121
#define NULL 0
#define BOOL int
#define FALSE 0
#define TRUE 1

#include <math.h>


#define CT_NONE -1
typedef struct tagProjectPara
{
	double a;					//≥§∞Î÷·
	double f;					//±‚¬ :1/f	
	double offset;
}PROJECTPARA;


class CCoordinateTransform
{
// Construction
public:
	enum		GUASSTYPE{bandNone,bandOneAndHalf,bandThree,bandSix,bandNine};
	int			m_BandNo;
	double		m_CentreLongitude;
	PROJECTPARA m_ProjectPara;
public:
	CCoordinateTransform();

	BOOL BlToGauss_84xy(double b,double l,double *x,double *y,
	GUASSTYPE GaussType = CCoordinateTransform::bandThree,int BandNo = CT_NONE,BOOL bAddBandNo = FALSE);

	void SetCentreLongitude(double dCentreLongitude);

public:
//private:
	BOOL BlToGaussxy(double b,double l,double *x,double *y);
	double * gcc(double a,double f);
	void GetBandAndCentreLongitudeByBl(double b,double l,GUASSTYPE GaussType,int BandNo);
// Attributes
// Operations
public:
	
public:
	virtual ~CCoordinateTransform();

};
#endif
/////////////////////////////////////////////////////////////////////////////

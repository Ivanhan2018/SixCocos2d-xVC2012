#include "SIX_RippleGrid3D.h"
#include <SIX_Typedef.h>

SIX_RippleGrid3D* SIX_RippleGrid3D::create(const ccGridSize& gridSize)
{
	SIX_RippleGrid3D *pRet= new SIX_RippleGrid3D();
    
	if (pRet)
	{
		if (pRet->initWithSize(gridSize))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pRet);
		}
	}
	return pRet;
}

SIX_RippleGrid3D::SIX_RippleGrid3D()
: m_pBufNext(0)
, m_pBufLast(0)
, m_pBuf(0)
{
}

SIX_RippleGrid3D::~SIX_RippleGrid3D(void)
{
	CC_SAFE_FREE(m_pBuf);
}

bool SIX_RippleGrid3D::initWithSize(const ccGridSize &gridSize)
{
	if (CCGrid3D::initWithSize(gridSize))
	{
		m_width = gridSize.x+1;
		m_height = gridSize.y+1;
		unsigned int numOfPoints = m_width * m_height;
		m_pBuf = (float*)malloc(numOfPoints * sizeof(ccVertex3F));
		m_pBufLast = (ccVertex3F*)m_pVertices;
		m_pBufNext = (ccVertex3F*)m_pBuf;
		memcpy(m_pBufNext, m_pBufLast, numOfPoints * sizeof(ccVertex3F));

		return true;
	}
	return false;
}

void SIX_RippleGrid3D::update(float dt)
{
	int index = 0;
	for (int y = 1; y<m_height-1; y++) 
	{
		for (int x = 1; x<m_width-1; x++) 
		{
			index = x*m_height + y;

			float zu = m_pBufLast[index - 1].z;
			float zr = m_pBufLast[index + m_height].z;
			float zd = m_pBufLast[index + 1].z;
			float zl = m_pBufLast[index - m_height].z;

			float z = m_pBufLast[index].z;

			z = (zu+zr+zd+zl)/2-z;
			z -= z/64;
			m_pBufLast[index].z = z;
		}
	}
	m_pBufLast = m_pBufNext;
	m_pBufNext = (ccVertex3F*)m_pVertices;
	m_pVertices = m_pBufLast;
}

void SIX_RippleGrid3D::dropStone(int x, int y, int stoneSize, int stoneWeight)
{
	if ( x > m_width || y > m_height || x < 0 || y < 0)
		return;

	int radius = MIN(MIN(MIN(x, m_width-x-1), MIN(y,m_height-y-1)), stoneSize-1);

	int radius2 = radius*radius;
	float weight = -stoneWeight;

	for (int posx = x - stoneSize; posx < x + stoneSize; ++posx)
		for (int posy = y - stoneSize; posy < y + stoneSize; ++posy)
			if ((posx - x) * (posx - x) + (posy - y) * (posy - y) < radius2)
				m_pBufLast[(m_height * posx + posy)].z = weight;
}
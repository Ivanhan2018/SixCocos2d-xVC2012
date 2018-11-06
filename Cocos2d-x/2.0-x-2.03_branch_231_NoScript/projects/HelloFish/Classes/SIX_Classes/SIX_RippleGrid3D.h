#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define vertext_len 3

class SIX_RippleGrid3D:public CCGrid3D
{
public:
	SIX_RippleGrid3D();
	~SIX_RippleGrid3D();

	static SIX_RippleGrid3D* create(const ccGridSize& gridSize);
	virtual void update(float dt);

	bool initWithSize(const ccGridSize& gridSize);
	void dropStone(int x, int y, int stoneSize, int stoneWeight);
protected:
	ccVertex3F* m_pBufNext;
	ccVertex3F* m_pBufLast;
	float* m_pBuf;
	int m_width;
	int m_height;
};
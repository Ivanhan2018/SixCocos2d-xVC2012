#pragma once
#include "NumberSprite.h"

const int MAX_NUMBER_LENGTH = 12;

//对齐方式
enum ALIGN
{
	ALIGN_AT_LEFT,		//左对齐
	ALIGN_AT_CENTRE,	//中间对齐
	ALIGN_AT_RIGHT,		//右对齐
};

class Numbers
{
public:
	Numbers(CCTexture2D *pTexture, CCSize size, CCPoint position, float rotate, CCPoint hotspot, ALIGN align = ALIGN_AT_LEFT);
	~Numbers(void);
	void setValue(int v, bool isShow = true);
	void reset(CCPoint position, float rotate, CCPoint hotspot, ALIGN align = ALIGN_AT_LEFT);

public:
	NumberSprite *numberList[MAX_NUMBER_LENGTH];
	static int GetNumderLength(int number);

private:
	CCPoint position;
	CCPoint hotspot;
	ALIGN ali;
};

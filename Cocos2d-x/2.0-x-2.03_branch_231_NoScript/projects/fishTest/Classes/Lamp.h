#pragma once
#include "CCSprite.h"
using namespace cocos2d;

enum Result
{
	Result_YanZi = 0,
	Result_TuZi,
	Result_HouZi,
	Result_XiongMao,
	Result_ShiZi,
	Result_LaoYing,
	Result_KongQue,
	Result_GeZi,
	Result_LanSha,
	Result_YinSha,
	Result_JinSha,

	Result_End,
};

class Lamp :
	public cocos2d::CCSprite
{
public:
	Lamp(const char *pszFilename, Result r_type);
	~Lamp(void);
	virtual void draw(void);
public:
	Result r_type;
};

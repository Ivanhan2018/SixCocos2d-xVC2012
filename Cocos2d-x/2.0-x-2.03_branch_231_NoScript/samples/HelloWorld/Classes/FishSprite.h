#ifndef ____CFISH_H____
#define ____CFISH_H____

#include "cocos2d.h"

static int d_Fish_Max_Count = 100;				// 鱼最大数目

/// 鱼
class FishSprite : public cocos2d::CCSprite
{
	friend class CFashManage;
public:	
	bool randomCatch(int level);	
	void removeSelf();
	CC_SYNTHESIZE(bool, isCatching, IsCatching);

private:
	static FishSprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
	static FishSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
	void addPath();	
	void moveWithParabola(cocos2d::CCSprite* mSprite, cocos2d::CCPoint startP, cocos2d::CCPoint endP,
		float startAngle, float endAngle, float time);

public:
	enum Fish_Type
	{
		Fish_1,
		Fish_2,
		Fish_3,
		Fish_4,
		Fish_5,
		Fish_6,
		Fish_7,
		Fish_8,
		Fish_9,
		Fish_10,
		Fish_Type_Count
	};
};

class CFashManage
{
public:
	static void Init(cocos2d::CCNode * pNode);									///< 初始化鱼群（默认增加 d_Fish_Max_Count 条）
	static void Release();																		///< 释放鱼群
	static void addOneFish(FishSprite::Fish_Type eType=FishSprite::Fish_1);		///< 增加一条鱼
	static cocos2d::CCSpriteBatchNode * sharedFish();

private:
	static cocos2d::CCSpriteBatchNode * s_AllFish;
};
#endif
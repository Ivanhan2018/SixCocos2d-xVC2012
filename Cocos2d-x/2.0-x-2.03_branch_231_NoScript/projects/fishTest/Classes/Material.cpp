#include "Material.h"

Material::Material(void)
{
	animationCache.init();
}

Material::~Material(void)
{
}

void Material::load_00(void)
{

}

void Material::load_01(void)
{
	fishTexture = CCTextureCache::sharedTextureCache()->addImage("Image/fish.png");
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(9); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(165 + 136 * 0, 85, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(165 + 136 * 1, 85, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(165 + 136 * 2, 85, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(165 + 136 * 3, 85, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(165 + 136 * 4, 85, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(165 + 136 * 5, 85, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 136 * 0, 149, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 136 * 1, 149, 136, 64)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 136 * 2, 149, 136, 64)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.1f);

	animationCache.addAnimation(animation_01, "DengLongYu");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(11); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 0, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 1, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 2, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 3, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 4, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 5, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 6, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 7, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 8, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 9, 0, 64, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 64 * 10, 0, 64, 40)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, 0.1f);
	animationCache.addAnimation(animation_02, "BanYu");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(9); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 0, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 1, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 2, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 3, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 4, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 5, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 6, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 7, 152, 48, 48)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(408 + 48 * 8, 152, 48, 48)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, 0.1f);
	animationCache.addAnimation(animation_03, "HuDieYu");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_04 = new CCMutableArray<CCSpriteFrame*>(12); 
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(840, 152, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 0, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 1, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 2, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 3, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 4, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 5, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 6, 224, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 0, 296, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 1, 296, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 2, 296, 144, 72)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 3, 296, 144, 72)));
	CCAnimation *animation_04 = CCAnimation::animationWithFrames(animFrames_04, 0.1f);
	animationCache.addAnimation(animation_04, "JinSha");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_05 = new CCMutableArray<CCSpriteFrame*>(10); 
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 0, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 1, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 2, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 3, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 4, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 5, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(146 + 112 * 6, 526, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 112 * 0, 678, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 112 * 1, 678, 112, 152)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 112 * 2, 678, 112, 152)));
	CCAnimation *animation_05 = CCAnimation::animationWithFrames(animFrames_05, 0.12f);
	animationCache.addAnimation(animation_05, "MoGuiYu");
#endif
}

void Material::load_02(void)
{
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(580 + 80 * 0, 298, 80, 86)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(580 + 80 * 1, 298, 80, 86)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(580 + 80 * 2, 298, 80, 86)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(580 + 80 * 3, 298, 80, 86)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(580 + 80 * 4, 298, 80, 86)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.12f);
	animationCache.addAnimation(animation_01, "HaiGui");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(8); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 0, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 1, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 2, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 3, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 4, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 5, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 6, 382, 56, 40)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 56 * 7, 382, 56, 40)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, 0.1f);
	animationCache.addAnimation(animation_02, "CaiHuaYu");


	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(12); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(450 + 144 * 0, 382, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(449 + 144 * 1, 382, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(449 + 144 * 2, 382, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(449 + 144 * 3, 382, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 0, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 1, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 2, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 3, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 4, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 5, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 6, 454, 144, 72)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(0 + 144 * 0, 526, 144, 72)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, 0.1f);
	animationCache.addAnimation(animation_03, "YinSha");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_04 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(703 + 48 * 0, 0, 48, 32)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(703 + 48 * 1, 0, 48, 32)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(703 + 48 * 2, 0, 48, 32)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(703 + 48 * 3, 0, 48, 32)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(703 + 48 * 4, 0, 48, 32)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(703 + 48 * 5, 0, 48, 32)));
	CCAnimation *animation_04 = CCAnimation::animationWithFrames(animFrames_04, 0.1f);
	animationCache.addAnimation(animation_04, "QiPaoYuA");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_05 = new CCMutableArray<CCSpriteFrame*>(16); 
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 0, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 1, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 2, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 3, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 4, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 5, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 6, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 7, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 8, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 9, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 10, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 11, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 12, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 13, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 14, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 15, 64 + 48 * 0, 56, 48)));
	CCAnimation *animation_05 = CCAnimation::animationWithFrames(animFrames_05, 0.1f);
	animationCache.addAnimation(animation_05, "QiPaoYuB");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_06 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 15, 64 + 48 * 0, 56, 48)));
	CCAnimation *animation_06 = CCAnimation::animationWithFrames(animFrames_06, 0.1f);
	animationCache.addAnimation(animation_06, "QiPaoYuC");

	//-----------------------------------------------------------------------------------------------------------------

	CCMutableArray<CCSpriteFrame*> *animFrames_07 = new CCMutableArray<CCSpriteFrame*>(7);
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 15, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 16, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 17, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 18, 64 + 48 * 0, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 0, 64 + 48 * 1, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 1, 64 + 48 * 1, 56, 48)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(fishTexture, CCRectMake(56 * 2, 64 + 48 * 1, 56, 48)));
	CCAnimation *animation_07 = CCAnimation::animationWithFrames(animFrames_07, 0.1f);
	animationCache.addAnimation(animation_07, "QiPaoYuD");
#endif
}

void Material::load_03(void)
{
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(30); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_001.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_002.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_003.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_004.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_005.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_006.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_007.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_008.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_009.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_010.png"), CCRectMake(0, 0, 720, 450)));

	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_011.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_012.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_013.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_014.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_015.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_016.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_017.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_018.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_019.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_020.png"), CCRectMake(0, 0, 720, 450)));

	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_021.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_022.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_023.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_024.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_025.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_026.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_027.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_028.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_029.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Ashui720x450/Ashui_030.png"), CCRectMake(0, 0, 720, 450)));

	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.2f);

	animationCache.addAnimation(animation_01, "ShuiWen_1");
#endif
}

void Material::load_04(void)
{
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(30); 

	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_01.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_02.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_03.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_04.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_05.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_06.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_07.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_08.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_09.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_10.png"), CCRectMake(0, 0, 720, 450)));

	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_11.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_12.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_13.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_14.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_15.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_16.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_17.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_18.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_19.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_20.png"), CCRectMake(0, 0, 720, 450)));

	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_21.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_22.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_23.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_24.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_25.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_26.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_27.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_28.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_29.png"), CCRectMake(0, 0, 720, 450)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/wave/Bshui720x450/Bshui_30.png"), CCRectMake(0, 0, 720, 450)));

	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.2f);

	animationCache.addAnimation(animation_01, "ShuiWen_2");
#endif
}

void Material::load_05(void)
{
	shuiCaoTexture = CCTextureCache::sharedTextureCache()->addImage("Image/grass.png");
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(14); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(305 + 0 * 144, 289 + 0 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(305 + 1 * 144, 289 + 0 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(305 + 2 * 144, 289 + 0 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(305 + 3 * 144, 289 + 0 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(305 + 4 * 144, 289 + 0 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(2 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(3 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(4 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(5 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(6 * 144, 289 + 1 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 144, 289 + 2 * 160, 144, 160)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 144, 289 + 2 * 160, 144, 160)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.15f);
	animationCache.addAnimation(animation_01, "ShuiCao_01");

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(14); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(289 + 0 * 216, 610 + 0 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(289 + 1 * 216, 610 + 0 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(289 + 2 * 216, 610 + 0 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 216, 610 + 1 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 216, 610 + 1 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(2 * 216, 610 + 1 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(3 * 216, 610 + 1 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 216, 610 + 2 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 216, 610 + 2 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(2 * 216, 610 + 2 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(3 * 216, 610 + 2 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 216, 610 + 3 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 216, 610 + 3 * 256, 216, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(2 * 216, 610 + 3 * 256, 216, 256)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, 0.15f);
	animationCache.addAnimation(animation_02, "ShuiCao_02");

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(14); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 152, 0 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 152, 0 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(2 * 152, 0 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(3 * 152, 0 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(4 * 152, 0 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(5 * 152, 0 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 152, 1 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(1 * 152, 1 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(2 * 152, 1 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(3 * 152, 1 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(4 * 152, 1 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(5 * 152, 1 * 144, 152, 144)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(shuiCaoTexture, CCRectMake(0 * 152, 2 * 144, 152, 144)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, 0.15f);
	animationCache.addAnimation(animation_03, "ShuiCao_03");
#endif
}

void Material::load_06(void)
{
	/*
	historyTexture[0] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht00.png");
	historyTexture[1] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht01.png");
	historyTexture[2] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht02.png");
	historyTexture[3] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht03.png");
	historyTexture[4] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht04.png");
	historyTexture[5] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht05.png");
	historyTexture[6] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht06.png");
	historyTexture[7] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht07.png");
	historyTexture[8] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht08.png");
	historyTexture[9] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht09.png");
	historyTexture[10] = CCTextureCache::sharedTextureCache()->addImage("Image/history/ht10.png");
*/
	daoJiShiNumer = CCTextureCache::sharedTextureCache()->addImage("Image/daojishi.png");
	winerNumer = CCTextureCache::sharedTextureCache()->addImage("Image/beilv.png");
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang06.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang05.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang04.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang03.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang02.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang01.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang00.png"), CCRectMake(0, 0, 846, 168)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.06f);
	animationCache.addAnimation(animation_01, "Light_01");

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang00.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang01.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang02.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang03.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang04.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang05.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang06.png"), CCRectMake(0, 0, 846, 168)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, 0.06f);
	animationCache.addAnimation(animation_02, "Light_02");

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(2); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang00.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang01.png"), CCRectMake(0, 0, 846, 168)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, 0.1f);
	animationCache.addAnimation(animation_03, "Light_03");

	CCMutableArray<CCSpriteFrame*> *animFrames_04 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang01.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang02.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang03.png"), CCRectMake(0, 0, 846, 168)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang04.png"), CCRectMake(0, 0, 846, 168)));
	CCAnimation *animation_04 = CCAnimation::animationWithFrames(animFrames_04, 0.1f);
	animationCache.addAnimation(animation_04, "Light_04");
#endif
	light_0 = CCTextureCache::sharedTextureCache()->addImage("Image/light/baiguang00.png");
	light_1 = CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang00.png");
	light_2 = CCTextureCache::sharedTextureCache()->addImage("Image/light/caiguang01.png");
}

void Material::load_07(void)
{
	/*
	float t = 0.1f;
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt00.png"), CCRectMake(0, 0, 120, 188)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, t);
	lamp_Animatin_0.setObject(animation_01, 0);

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt01.png"), CCRectMake(0, 0, 120, 176)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, t);
	lamp_Animatin_0.setObject(animation_02, 1);

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt02.png"), CCRectMake(0, 0, 170, 180)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, t);
	lamp_Animatin_0.setObject(animation_03, 2);

	CCMutableArray<CCSpriteFrame*> *animFrames_04 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt03.png"), CCRectMake(0, 0, 128, 160)));
	CCAnimation *animation_04 = CCAnimation::animationWithFrames(animFrames_04, t);
	lamp_Animatin_0.setObject(animation_04, 3);

	CCMutableArray<CCSpriteFrame*> *animFrames_05 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt04.png"), CCRectMake(0, 0, 130, 180)));
	CCAnimation *animation_05 = CCAnimation::animationWithFrames(animFrames_05, t);
	lamp_Animatin_0.setObject(animation_05, 4);

	CCMutableArray<CCSpriteFrame*> *animFrames_06 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt05.png"), CCRectMake(0, 0, 130, 180)));
	CCAnimation *animation_06 = CCAnimation::animationWithFrames(animFrames_06, t);
	lamp_Animatin_0.setObject(animation_06, 5);

	CCMutableArray<CCSpriteFrame*> *animFrames_07 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt06.png"), CCRectMake(0, 0, 160, 160)));
	CCAnimation *animation_07 = CCAnimation::animationWithFrames(animFrames_07, t);
	lamp_Animatin_0.setObject(animation_07, 6);

	CCMutableArray<CCSpriteFrame*> *animFrames_08 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt07.png"), CCRectMake(0, 0, 110, 150)));
	CCAnimation *animation_08 = CCAnimation::animationWithFrames(animFrames_08, t);
	lamp_Animatin_0.setObject(animation_08, 7);

	CCMutableArray<CCSpriteFrame*> *animFrames_09 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt08.png"), CCRectMake(0, 0, 120, 150)));
	CCAnimation *animation_09 = CCAnimation::animationWithFrames(animFrames_09, t);
	lamp_Animatin_0.setObject(animation_09, 8);

	CCMutableArray<CCSpriteFrame*> *animFrames_10 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt09.png"), CCRectMake(0, 0, 120, 150)));
	CCAnimation *animation_10 = CCAnimation::animationWithFrames(animFrames_10, t);
	lamp_Animatin_0.setObject(animation_10, 9);

	CCMutableArray<CCSpriteFrame*> *animFrames_11 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_static/lt10.png"), CCRectMake(0, 0, 120, 150)));
	CCAnimation *animation_11 = CCAnimation::animationWithFrames(animFrames_11, t);
	lamp_Animatin_0.setObject(animation_11, 10);

	//============================================================================================================

	CCMutableArray<CCSpriteFrame*> *animFrames_12 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_12->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult00.png"), CCRectMake(0, 0, 128, 136)));
	CCAnimation *animation_12 = CCAnimation::animationWithFrames(animFrames_12, t);
	lamp_Animatin_1.setObject(animation_12, 0);

	CCMutableArray<CCSpriteFrame*> *animFrames_13 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_13->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult01.png"), CCRectMake(0, 0, 136, 208)));
	CCAnimation *animation_13 = CCAnimation::animationWithFrames(animFrames_13, t);
	lamp_Animatin_1.setObject(animation_13, 1);

	CCMutableArray<CCSpriteFrame*> *animFrames_14 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_14->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult02.png"), CCRectMake(0, 0, 128, 184)));
	CCAnimation *animation_14 = CCAnimation::animationWithFrames(animFrames_14, t);
	lamp_Animatin_1.setObject(animation_14, 2);

	CCMutableArray<CCSpriteFrame*> *animFrames_15 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_15->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult03.png"), CCRectMake(0, 0, 112, 176)));
	CCAnimation *animation_15 = CCAnimation::animationWithFrames(animFrames_15, t);
	lamp_Animatin_1.setObject(animation_15, 3);

	CCMutableArray<CCSpriteFrame*> *animFrames_16 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_16->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult04.png"), CCRectMake(0, 0, 128, 184)));
	CCAnimation *animation_16 = CCAnimation::animationWithFrames(animFrames_16, t);
	lamp_Animatin_1.setObject(animation_16, 4);

	CCMutableArray<CCSpriteFrame*> *animFrames_17 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_17->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult05.png"), CCRectMake(0, 0, 144, 160)));
	CCAnimation *animation_17 = CCAnimation::animationWithFrames(animFrames_17, t);
	lamp_Animatin_1.setObject(animation_17, 5);

	CCMutableArray<CCSpriteFrame*> *animFrames_18 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_18->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult06.png"), CCRectMake(0, 0, 120, 176)));
	CCAnimation *animation_18 = CCAnimation::animationWithFrames(animFrames_18, t);
	lamp_Animatin_1.setObject(animation_18, 6);

	CCMutableArray<CCSpriteFrame*> *animFrames_19 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_19->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult07.png"), CCRectMake(0, 0, 128, 160)));
	CCAnimation *animation_19 = CCAnimation::animationWithFrames(animFrames_19, t);
	lamp_Animatin_1.setObject(animation_19, 7);

	CCMutableArray<CCSpriteFrame*> *animFrames_20 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_20->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult08.png"), CCRectMake(0, 0, 136, 168)));
	CCAnimation *animation_20 = CCAnimation::animationWithFrames(animFrames_20, t);
	lamp_Animatin_1.setObject(animation_20, 8);

	CCMutableArray<CCSpriteFrame*> *animFrames_21 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_21->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult09.png"), CCRectMake(0, 0, 136, 168)));
	CCAnimation *animation_21 = CCAnimation::animationWithFrames(animFrames_21, t);
	lamp_Animatin_1.setObject(animation_21, 9);

	CCMutableArray<CCSpriteFrame*> *animFrames_22 = new CCMutableArray<CCSpriteFrame*>(1); 
	animFrames_22->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_under_light/ult10.png"), CCRectMake(0, 0, 136, 168)));
	CCAnimation *animation_22 = CCAnimation::animationWithFrames(animFrames_22, t);
	lamp_Animatin_1.setObject(animation_22, 10);
*/
}

void Material::load_08(void)
{
	float t = 0.12f;
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(7); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0001.png"), CCRectMake(0, 0, 120, 188)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0002.png"), CCRectMake(0, 0, 120, 188)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0003.png"), CCRectMake(0, 0, 120, 188)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0004.png"), CCRectMake(0, 0, 120, 188)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0005.png"), CCRectMake(0, 0, 120, 188)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0006.png"), CCRectMake(0, 0, 120, 188)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0007.png"), CCRectMake(0, 0, 120, 188)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, t);
	lamp_Animatin_2.setObject(animation_01, 0);

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(7); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0101.png"), CCRectMake(0, 0, 120, 176)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0102.png"), CCRectMake(0, 0, 120, 176)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0103.png"), CCRectMake(0, 0, 120, 176)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0104.png"), CCRectMake(0, 0, 120, 176)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0105.png"), CCRectMake(0, 0, 120, 176)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0106.png"), CCRectMake(0, 0, 120, 176)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0107.png"), CCRectMake(0, 0, 120, 176)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, t);
	lamp_Animatin_2.setObject(animation_02, 1);

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(5); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0201.png"), CCRectMake(0, 0, 120, 180)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0202.png"), CCRectMake(0, 0, 120, 180)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0203.png"), CCRectMake(0, 0, 120, 180)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0204.png"), CCRectMake(0, 0, 120, 180)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0205.png"), CCRectMake(0, 0, 120, 180)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, t);
	lamp_Animatin_2.setObject(animation_03, 2);

	CCMutableArray<CCSpriteFrame*> *animFrames_04 = new CCMutableArray<CCSpriteFrame*>(5); 
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0301.png"), CCRectMake(0, 0, 128, 160)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0302.png"), CCRectMake(0, 0, 128, 160)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0303.png"), CCRectMake(0, 0, 128, 160)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0304.png"), CCRectMake(0, 0, 128, 160)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0305.png"), CCRectMake(0, 0, 128, 160)));
	CCAnimation *animation_04 = CCAnimation::animationWithFrames(animFrames_04, t);
	lamp_Animatin_2.setObject(animation_04, 3);

	CCMutableArray<CCSpriteFrame*> *animFrames_05 = new CCMutableArray<CCSpriteFrame*>(5); 
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0401.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0402.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0403.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0404.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0405.png"), CCRectMake(0, 0, 130, 180)));
	CCAnimation *animation_05 = CCAnimation::animationWithFrames(animFrames_05, t);
	lamp_Animatin_2.setObject(animation_05, 4);

	CCMutableArray<CCSpriteFrame*> *animFrames_06 = new CCMutableArray<CCSpriteFrame*>(5); 
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0501.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0502.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0503.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0504.png"), CCRectMake(0, 0, 130, 180)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0505.png"), CCRectMake(0, 0, 130, 180)));
	CCAnimation *animation_06 = CCAnimation::animationWithFrames(animFrames_06, t);
	lamp_Animatin_2.setObject(animation_06, 5);

	CCMutableArray<CCSpriteFrame*> *animFrames_07 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0601.png"), CCRectMake(0, 0, 160, 160)));
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0602.png"), CCRectMake(0, 0, 160, 160)));
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0603.png"), CCRectMake(0, 0, 160, 160)));
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0604.png"), CCRectMake(0, 0, 160, 160)));
	CCAnimation *animation_07 = CCAnimation::animationWithFrames(animFrames_07, t);
	lamp_Animatin_2.setObject(animation_07, 6);

	CCMutableArray<CCSpriteFrame*> *animFrames_08 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0701.png"), CCRectMake(0, 0, 110, 150)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0702.png"), CCRectMake(0, 0, 110, 150)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0703.png"), CCRectMake(0, 0, 110, 150)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0704.png"), CCRectMake(0, 0, 110, 150)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0705.png"), CCRectMake(0, 0, 110, 150)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0706.png"), CCRectMake(0, 0, 110, 150)));
	CCAnimation *animation_08 = CCAnimation::animationWithFrames(animFrames_08, t);
	lamp_Animatin_2.setObject(animation_08, 7);

	CCMutableArray<CCSpriteFrame*> *animFrames_09 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0801.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0802.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0803.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0804.png"), CCRectMake(0, 0, 120, 150)));
	CCAnimation *animation_09 = CCAnimation::animationWithFrames(animFrames_09, t);
	lamp_Animatin_2.setObject(animation_09, 8);

	CCMutableArray<CCSpriteFrame*> *animFrames_10 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0901.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0902.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0903.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt0904.png"), CCRectMake(0, 0, 120, 150)));
	CCAnimation *animation_10 = CCAnimation::animationWithFrames(animFrames_10, t);
	lamp_Animatin_2.setObject(animation_10, 9);

	CCMutableArray<CCSpriteFrame*> *animFrames_11 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt1001.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt1002.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt1003.png"), CCRectMake(0, 0, 120, 150)));
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_b1/wlt1004.png"), CCRectMake(0, 0, 120, 150)));
	CCAnimation *animation_11 = CCAnimation::animationWithFrames(animFrames_11, t);
	lamp_Animatin_2.setObject(animation_11, 10);
#endif
}

void Material::load_09(void)
{
	float t = 0.1f;
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(8); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0001.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0002.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0003.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0004.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0005.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0006.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0007.png"), CCRectMake(0, 0, 256, 360)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0008.png"), CCRectMake(0, 0, 256, 360)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, t);
	winer_Animatin_0.setObject(animation_01, 0);

	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(7); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0101.png"), CCRectMake(0, 0, 220, 276)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0102.png"), CCRectMake(0, 0, 220, 276)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0103.png"), CCRectMake(0, 0, 220, 276)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0104.png"), CCRectMake(0, 0, 220, 276)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0105.png"), CCRectMake(0, 0, 220, 276)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0106.png"), CCRectMake(0, 0, 220, 276)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0107.png"), CCRectMake(0, 0, 220, 276)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, t);
	winer_Animatin_0.setObject(animation_02, 1);

	CCMutableArray<CCSpriteFrame*> *animFrames_03 = new CCMutableArray<CCSpriteFrame*>(5); 
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0201.png"), CCRectMake(0, 0, 280, 288)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0202.png"), CCRectMake(0, 0, 280, 288)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0203.png"), CCRectMake(0, 0, 280, 288)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0204.png"), CCRectMake(0, 0, 280, 288)));
	animFrames_03->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0205.png"), CCRectMake(0, 0, 280, 288)));
	CCAnimation *animation_03 = CCAnimation::animationWithFrames(animFrames_03, t);
	winer_Animatin_0.setObject(animation_03, 2);

	CCMutableArray<CCSpriteFrame*> *animFrames_04 = new CCMutableArray<CCSpriteFrame*>(7); 
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0301.png"), CCRectMake(0, 0, 200, 272)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0302.png"), CCRectMake(0, 0, 200, 272)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0303.png"), CCRectMake(0, 0, 200, 272)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0304.png"), CCRectMake(0, 0, 200, 272)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0305.png"), CCRectMake(0, 0, 200, 272)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0306.png"), CCRectMake(0, 0, 200, 272)));
	animFrames_04->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0307.png"), CCRectMake(0, 0, 200, 272)));
	CCAnimation *animation_04 = CCAnimation::animationWithFrames(animFrames_04, t);
	winer_Animatin_0.setObject(animation_04, 3);

	CCMutableArray<CCSpriteFrame*> *animFrames_05 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0401.png"), CCRectMake(0, 0, 224, 272)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0402.png"), CCRectMake(0, 0, 224, 272)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0403.png"), CCRectMake(0, 0, 224, 272)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0404.png"), CCRectMake(0, 0, 224, 272)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0405.png"), CCRectMake(0, 0, 224, 272)));
	animFrames_05->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0406.png"), CCRectMake(0, 0, 224, 272)));
	CCAnimation *animation_05 = CCAnimation::animationWithFrames(animFrames_05, t);
	winer_Animatin_0.setObject(animation_05, 4);

	CCMutableArray<CCSpriteFrame*> *animFrames_06 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0501.png"), CCRectMake(0, 0, 208, 288)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0502.png"), CCRectMake(0, 0, 208, 288)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0503.png"), CCRectMake(0, 0, 208, 288)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0504.png"), CCRectMake(0, 0, 208, 288)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0505.png"), CCRectMake(0, 0, 208, 288)));
	animFrames_06->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0506.png"), CCRectMake(0, 0, 208, 288)));
	CCAnimation *animation_06 = CCAnimation::animationWithFrames(animFrames_06, t);
	winer_Animatin_0.setObject(animation_06, 5);

	CCMutableArray<CCSpriteFrame*> *animFrames_07 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0601.png"), CCRectMake(0, 0, 320, 280)));
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0602.png"), CCRectMake(0, 0, 320, 280)));
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0603.png"), CCRectMake(0, 0, 320, 280)));
	animFrames_07->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0604.png"), CCRectMake(0, 0, 320, 280)));
	CCAnimation *animation_07 = CCAnimation::animationWithFrames(animFrames_07, t);
	winer_Animatin_0.setObject(animation_07, 6);

	CCMutableArray<CCSpriteFrame*> *animFrames_08 = new CCMutableArray<CCSpriteFrame*>(6); 
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0701.png"), CCRectMake(0, 0, 208, 296)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0702.png"), CCRectMake(0, 0, 208, 296)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0703.png"), CCRectMake(0, 0, 208, 296)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0704.png"), CCRectMake(0, 0, 208, 296)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0705.png"), CCRectMake(0, 0, 208, 296)));
	animFrames_08->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0706.png"), CCRectMake(0, 0, 208, 296)));
	CCAnimation *animation_08 = CCAnimation::animationWithFrames(animFrames_08, t);
	winer_Animatin_0.setObject(animation_08, 7);

	CCMutableArray<CCSpriteFrame*> *animFrames_09 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0801.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0802.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0803.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_09->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0804.png"), CCRectMake(0, 0, 264, 240)));
	CCAnimation *animation_09 = CCAnimation::animationWithFrames(animFrames_09, t);
	winer_Animatin_0.setObject(animation_09, 8);

	CCMutableArray<CCSpriteFrame*> *animFrames_10 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0901.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0902.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0903.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_10->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0904.png"), CCRectMake(0, 0, 264, 240)));
	CCAnimation *animation_10 = CCAnimation::animationWithFrames(animFrames_10, t);
	winer_Animatin_0.setObject(animation_10, 9);

	CCMutableArray<CCSpriteFrame*> *animFrames_11 = new CCMutableArray<CCSpriteFrame*>(4); 
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt1001.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt1002.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt1003.png"), CCRectMake(0, 0, 264, 240)));
	animFrames_11->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt1004.png"), CCRectMake(0, 0, 264, 240)));
	CCAnimation *animation_11 = CCAnimation::animationWithFrames(animFrames_11, t);
	winer_Animatin_0.setObject(animation_11, 10);
#endif
}

void Material::load_10(void)
{
	winer_Texture[0] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0001.png");
	winer_Texture[1] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0101.png");
	winer_Texture[2] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0201.png");
	winer_Texture[3] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0301.png");
	winer_Texture[4] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0401.png");
	winer_Texture[5] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0501.png");
	winer_Texture[6] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0601.png");
	winer_Texture[7] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0701.png");
	winer_Texture[8] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0801.png");
	winer_Texture[9] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt0901.png");
	winer_Texture[10] = CCTextureCache::sharedTextureCache()->addImage("Image/animal_winer_big/wlt1001.png");

	//CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(6); 
	//animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/frog/qingwa01.png"), CCRectMake(0, 0, 176, 176)));
	//animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/frog/qingwa02.png"), CCRectMake(0, 0, 176, 176)));
	//animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/frog/qingwa03.png"), CCRectMake(0, 0, 176, 176)));
	//animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/frog/qingwa04.png"), CCRectMake(0, 0, 176, 176)));
	//animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/frog/qingwa05.png"), CCRectMake(0, 0, 176, 176)));
	//animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/frog/qingwa06.png"), CCRectMake(0, 0, 176, 176)));
	//CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.12f);
	//animationCache.addAnimation(animation_01, "QingWaBianShen");
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(63); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua01.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua02.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua03.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua04.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua05.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua06.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua07.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua08.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua09.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua10.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua11.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua12.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua13.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua14.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua15.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua16.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua17.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua18.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua19.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua20.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua21.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua22.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua23.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua24.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua25.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua26.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua27.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua28.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua29.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua30.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua31.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Ayanhua/Ayanhua32.png"), CCRectMake(0, 0, 256, 256)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, 0.08f);
	animationCache.addAnimation(animation_02, "CaiJinParticle_A");
#endif
}

void Material::load_11(void)
{
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_02 = new CCMutableArray<CCSpriteFrame*>(63); 
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua01.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua02.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua03.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua04.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua05.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua06.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua07.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua08.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua09.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua10.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua11.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua12.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua13.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua14.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua15.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua16.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua17.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua18.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua19.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua20.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua21.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua22.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua23.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua24.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua25.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua26.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua27.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua28.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua29.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua30.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua31.png"), CCRectMake(0, 0, 256, 256)));
	animFrames_02->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua32.png"), CCRectMake(0, 0, 256, 256)));
	CCAnimation *animation_02 = CCAnimation::animationWithFrames(animFrames_02, 0.08f);
	animationCache.addAnimation(animation_02, "CaiJinParticle_B");
#endif
}

void Material::load_12(void)
{
#if 0
	CCMutableArray<CCSpriteFrame*> *animFrames_01 = new CCMutableArray<CCSpriteFrame*>(20); 
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow00.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow01.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow02.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow03.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow04.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow05.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow06.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow07.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow08.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow09.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow10.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow11.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow12.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow13.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow14.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow15.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow16.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow17.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow18.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow19.png"), CCRectMake(0, 0, 256,  128)));
	animFrames_01->addObject(CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow20.png"), CCRectMake(0, 0, 256,  128)));
	CCAnimation *animation_01 = CCAnimation::animationWithFrames(animFrames_01, 0.1f);
	animationCache.addAnimation(animation_01, "SharkShootParticle");
#endif
	sharkShootParticleTX = CCTextureCache::sharedTextureCache()->addImage("Image/sharkFireworks/tuow00.png");
	sharkFireParticleTX = CCTextureCache::sharedTextureCache()->addImage("Image/fireworks/Byanhua/Byanhua01.png");
}

void Material::load_13(void)
{

}

void Material::load_14(void)
{

}

void Material::load_15(void)
{

}

void Material::load_16(void)
{

}

void Material::load_17(void)
{

}

void Material::load_18(void)
{

}

void Material::load_19(void)
{

}

void Material::load_20(void)
{

}

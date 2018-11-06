#include "SceneTableInterfaceLayer.h"

SceneTableInterfaceLayer::SceneTableInterfaceLayer()
{

}

SceneTableInterfaceLayer::~SceneTableInterfaceLayer()
{

}

cocos2d::CCScene* SceneTableInterfaceLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create(); 
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		SceneTableInterfaceLayer *layer = SceneTableInterfaceLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool SceneTableInterfaceLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize WinSize = CCDirector::sharedDirector()->getWinSize();

	setKeypadEnabled(true);
	CCLayerColor* colorLayer = CCLayerColor::create(ccc4(166, 166, 166, 100), WinSize.width, WinSize.height);
	addChild(colorLayer);
	CCSprite *loadingTableInter = CCSprite::create("background/bg2.png");
	loadingTableInter->setPosition(ccp(WinSize.width/2,WinSize.height/2));
	addChild(loadingTableInter);
	return true;
}

void SceneTableInterfaceLayer::claosre( CCObject *obj )
{

}

void SceneTableInterfaceLayer::keyBackClicked( void )
{

}

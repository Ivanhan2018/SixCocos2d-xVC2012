//
//  GameLayer.cpp
//  TrexPush
//
//  Created by Nelson Andre on 12-10-01.
//
//

#include "GameLayer.h"
#include "GB2ShapeCache.h"
#include "Constants.h"
#include <vector>

CCScene* GameLayer::scene()
{
	
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        //HelloWorld *layer = HelloWorld::create();
        //CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        //scene->addChild(layer);
        
        GameLayer* gameLayer = new GameLayer();
        scene->addChild(gameLayer, 1);
        
        gameLayer->addNewSpriteAtPosition(ccp(100,100));

		//TODO: This is for testing only
		auto *dict = CCDictionary::dictionaryWithContentsOfFile("LevelData.plist");
		
		auto *stages  = (CCArray *)dict->objectForKey("STAGES");
		auto *stage1 = (CCDictionary *)stages->objectAtIndex(0);
		auto *levels = (CCArray *)stage1->objectForKey("LEVELS");
		auto *level1 = (CCDictionary *)levels->objectAtIndex(0);


		gameLayer->initializeLayerWithLevelData(level1);


    } while (0);
    
    // return the scene
    return scene;
}


CCScene* GameLayer::scene(int stage, int level){
	return NULL;
}

// Call this with the level sub-dictionary
void GameLayer::initializeLayerWithLevelData(CCDictionary *dict){

	// First, load the shape files
	auto *shapefiles = (CCArray *)dict->objectForKey("SHAPEFILES");
		
	for (int i = 0; i < shapefiles->count(); i++){
		SHAPE_CACHE->addShapesWithFile( ((CCString *)shapefiles->objectAtIndex(i))->getCString());
	}

	// We want the shapes key
	auto *shapesDict = dynamic_cast<CCArray*>(dict->objectForKey("SHAPES"));
	
	if (!shapesDict){
		return;
	}


	for (int i = 0; i < shapesDict->count(); i++){
		auto *obj = dynamic_cast<CCDictionary*>(shapesDict->objectAtIndex(i));

		auto keys = obj->allKeys();
		vector<std::string> v;
		for (int j = 0; j < keys->count(); j++){
			v.push_back(((CCString *)keys->objectAtIndex(j))->getCString());
		}

		auto pos_x = ((CCString*)(obj->objectForKey("POS_X")))->intValue();
		auto pos_y = ((CCString*)(obj->objectForKey("POS_Y")))->intValue();
		auto img = dynamic_cast<CCString*>(obj->objectForKey("IMAGE"));
		auto obj_id = dynamic_cast<CCString*>(obj->objectForKey("ID"));
		std::string str_id = obj_id->getCString();

		// TODO: We'll need a sprite here!
		this->addNewObjectAtPosition(str_id, CCPoint((float)pos_x, (float)pos_y));


	}
}
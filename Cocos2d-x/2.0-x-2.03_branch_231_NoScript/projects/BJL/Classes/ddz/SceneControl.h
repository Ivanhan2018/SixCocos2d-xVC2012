//  [3/19/2014 wucan]

#ifndef __DDZ__SceneControl__
#define __DDZ__SceneControl__

#include "cocos2d.h"
#include "SceneData.h"
USING_NS_CC;

class SceneControl
{
public:
	static SceneControl*		    sharedSceneControl();
	CCScene*						getScene(int index,bool bEffect,float t=0.4f);
};



#endif /* defined(__RunBeard__SceneControl__) */

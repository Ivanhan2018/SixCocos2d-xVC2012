
#ifndef _SceneTableInterfaceLayer_Game_
#define _SceneTableInterfaceLayer_Game_

#include "cocos2d.h"
#include "SceneData.h"
USING_NS_CC;

class SceneTableInterfaceLayer :public cocos2d::CCLayer
{
public:
		SceneTableInterfaceLayer();
		~SceneTableInterfaceLayer();
		CREATE_FUNC(SceneTableInterfaceLayer);
		virtual bool init();
		static cocos2d::CCScene* scene();
		void  claosre(CCObject *obj);        //����

		virtual void keyBackClicked(void);					//�ֻ����ذ�ť
};



#endif 

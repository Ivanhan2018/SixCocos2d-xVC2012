//  [2/28/2014 wucan]

#ifndef		__JNICONTROL_WUCAN__
#define		__JNICONTROL_WUCAN__
#include "cocos2d.h"
USING_NS_CC;

class JniControl:public CCObject
{
public:
	JniControl(void);
	~JniControl(void);
	static JniControl* sharedJniControl();

	void JniC_MsgToAndroid(CCObject* obj);
};

#endif
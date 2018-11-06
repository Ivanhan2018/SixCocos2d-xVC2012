#ifndef ____LOADING_H____
#define ____LOADING_H____

#include "cocos2d.h"
USING_NS_CC;

class LoadingLayer : public CCLayer
{
public:
	LoadingLayer(void);
	~LoadingLayer(void);

	/// ���ý������ٷֱ�
	void setProcessBar(float time, float fPercentage);
	/// װ�����
	void LoadComplete(float fTime);

	virtual void onEnter();
	virtual void onExit();

	static void scene();
};

#endif
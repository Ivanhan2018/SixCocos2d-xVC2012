#include "SmartRes.h"

USING_NS_CC;
SmartRes* SmartRes::s_sharedRes = NULL;

SmartRes* SmartRes::sharedRes(void)
{
	if (!s_sharedRes)
	{
		s_sharedRes = new SmartRes();
		s_sharedRes->init();
	}
	return s_sharedRes;
}

bool SmartRes::init(void)
{
	//const CCSize& winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
	//setVirtualScreenWidth(winSizeInPixels.width);

	m_designSize.width = 0.0f;
	m_designSize.height = 0.0f;
	m_screenSize.width = 0.0f;
	m_screenSize.height = 0.0f;
	return true;
}

void SmartRes::setVirtualScreenWidth(float width, float height)
{
	// 木有找到 2.0 里面怎么获取设备方向。。所以假定是横向了
	const CCSize& winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
	CCLog("Device.Screen[%.2fx%.2f]",winSizeInPixels.width,winSizeInPixels.height);

	m_scale = winSizeInPixels.width / width;

	m_designSize.width = width;
	m_designSize.height = height;
	m_screenSize.width = width;
	m_screenSize.height = winSizeInPixels.height / m_scale;

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(m_screenSize.width,m_screenSize.height, kResolutionNoBorder);
	//CCEGLView::sharedOpenGLView()->setContentScaleFactor(m_scale);
	CCSize size = CCEGLView::sharedOpenGLView()->getVisibleSize();

	CCLog("Virtual.Screen[%0.2fx%.2f].VisibleSize[%.2fx%.2f].scale[%0.2f](%.2f/%.2f)",
		m_screenSize.width, m_screenSize.height,
		size.width,size.height,
		m_scale,
		CCEGLView::sharedOpenGLView()->getScaleX(),
		CCEGLView::sharedOpenGLView()->getScaleY());

	//const CCSize& winSize = CCDirector::sharedDirector()->getWinSize();
	//m_center.x = winSize.width / 2;
	//m_center.y = winSize.height / 2;
	//m_left = 0;
	//m_right = m_screenSize.width - 1;
	//m_top = m_screenSize.height - 1;
	//m_bottom = 0;

	//CCLog("center x: %0.2f, center y: %0.2f", m_center.x, m_center.y);
	//CCLog("top: %0.2f, right: %0.2f, bottom: %0.2f, left: %0.2f", m_top, m_right, m_bottom, m_left);
}

//  [3/26/2014 xieyi]
#ifndef		__VIEW_MENU_LAYER__
#define		__VIEW_MENU_LAYER__
#include "cocos2d.h"
#include "DDZRes.h"
#include "SceneData.h"
#include "Timer.h"
USING_NS_CC;

class ViewMenuLayer : public CCLayer
{
public:
	CREATE_FUNC(ViewMenuLayer);
	virtual bool init();
	ViewMenuLayer();
	~ViewMenuLayer();
	bool m_isVisibleStart;	//是否明牌开始
	void setTimer(int userId,Game_State gameState,int t,bool visible,int key);

	void closeTimer();
	void SetTimeSprite();

	virtual void keyBackClicked(void);				//返回
	void setMenuNameTipsView(bool isVisible);
private:
								//添加按钮项
	void addMenuBarItem(const char * normal,const char * selected,const char * disable,
		CCObject * context,SEL_MenuHandler selector,CCPoint point,
		CCObject * pUserObject, int tag,bool visible);
	CCSprite* addMenuBarTips(const char * name,float delTime,CCPoint pt);
	void removeSelfCall(CCNode* _node);
private:
	CC_SYNTHESIZE(CCMenu *,m_menu,Menu);								//按钮
	CCMenu * m_menuBar;			//菜单栏
	CCNode * m_menuBarNode;		//菜单栏节点
	CCNode*  m_menuBarTips;
	bool m_menuBarIsShow;		//菜单栏是否显示
	CC_SYNTHESIZE(Timer*,m_timer,Timer);			//计时器
	float m_menuPositionY;
	bool m_isAutoHints;		//是否自动隐藏
};

#endif
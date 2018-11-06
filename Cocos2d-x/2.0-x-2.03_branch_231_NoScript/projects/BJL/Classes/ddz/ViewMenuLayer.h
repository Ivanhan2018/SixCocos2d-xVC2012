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
	bool m_isVisibleStart;	//�Ƿ����ƿ�ʼ
	void setTimer(int userId,Game_State gameState,int t,bool visible,int key);

	void closeTimer();
	void SetTimeSprite();

	virtual void keyBackClicked(void);				//����
	void setMenuNameTipsView(bool isVisible);
private:
								//��Ӱ�ť��
	void addMenuBarItem(const char * normal,const char * selected,const char * disable,
		CCObject * context,SEL_MenuHandler selector,CCPoint point,
		CCObject * pUserObject, int tag,bool visible);
	CCSprite* addMenuBarTips(const char * name,float delTime,CCPoint pt);
	void removeSelfCall(CCNode* _node);
private:
	CC_SYNTHESIZE(CCMenu *,m_menu,Menu);								//��ť
	CCMenu * m_menuBar;			//�˵���
	CCNode * m_menuBarNode;		//�˵����ڵ�
	CCNode*  m_menuBarTips;
	bool m_menuBarIsShow;		//�˵����Ƿ���ʾ
	CC_SYNTHESIZE(Timer*,m_timer,Timer);			//��ʱ��
	float m_menuPositionY;
	bool m_isAutoHints;		//�Ƿ��Զ�����
};

#endif
//  [4/4/2014 wucan]
#ifndef			__VOICE_FACE__
#define			__VOICE_FACE__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <limits>
USING_NS_CC;
USING_NS_CC_EXT;

#define TEXBACK_WIDTH			541
#define TEXBACK_HEIGHT		303

#define Voice_Width					1
#define Voice_Height				40

#define Face_W_Count				3
#define Face_H_Count				3


enum Vioce_Type
{
	Vioce_Type_1=0,
};

class CC_scrollView:public CCScrollViewDelegate ,public CCNode
{
public:
	CREATE_FUNC(CC_scrollView);
	virtual bool init();
	void addViewNode(CCNode* _Node,CCSize _size);								//--加入容器
	//--CCScrollViewDelegate
	virtual void scrollViewDidScroll(CCScrollView* view);			//--滑动
	virtual void scrollViewDidZoom(CCScrollView* view){};		//--缩放
public:
	CCScrollView*   m_scrollView;
};

class CC_listView: public CCTableViewDataSource, public CCTableViewDelegate,public CCNode
{
public:
	CREATE_FUNC(CC_listView);
	virtual bool init();
	//--CCTableViewDataSource
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	//--CCTableViewDelegate
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) ;
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){};

public:
	CCTableView*  m_tableView;

};




class VoiceAndFace:public CCLayer
{
public:
	CREATE_FUNC(VoiceAndFace);
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	//--控件
	void setFaceElement(int _type,const char * _name);
	void runOutOrIn(bool isVisible=true);
private:
	CC_listView*				m_VoiceNode;				//--语音控件
	CC_scrollView*				m_scrollView;
	CCNode*					m_FaceNode;				//--表情控件
	CCSprite*					m_VoiceSlide;
	CCSprite*					m_BackSpt;
	int			  m_faceCount;
	int			  m_voiceCount;
	CC_SYNTHESIZE(bool,m_isOut,IsOut);
	CCPoint     m_TouchBeganPos;
};

#endif
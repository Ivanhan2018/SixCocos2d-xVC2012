#ifndef __MOVELABEL_H__
#define __MOVELABEL_H__
#include "cocos2d.h"
using namespace cocos2d;


struct MoveLabel:public CCNode
{

	MoveLabel();
	~MoveLabel();
	void init(int x,int y,int width,int height);
	void initStr(char * pStr,char* fontName,int fontSize);

	virtual void draw(void);

	void touchDown(int x,int y);
	void touchMove(int x,int y);
	void touchUp(int x,int y);

	void setStr(char *pStr);
	char *getStr();

	void update();
	void drawStr();
	
	CCRect m_rect;
	CCRenderTexture *m_pRender;
	CCLabelTTF* m_pLabel;
	char *m_pStr;

	char* m_fontName;
	int m_fontSize;

	CCPoint m_p;
	CCPoint m_a;
	CCPoint m_v;
	int m_upBorder;
	int m_downBorder;

	CCPoint m_down;
	CCPoint m_up;
	CCPoint m_pre;
	CCPoint m_cur;
	int m_count;
	bool m_bTouch;
};






#endif
#include "moveLabel.h"

MoveLabel::MoveLabel()
{
	m_pStr = NULL;
	m_fontSize = 20;

	m_pRender = NULL;
	m_pLabel = NULL;

	m_pStr = NULL;

	m_fontName = NULL;
	m_fontSize = 20;


	m_v = ccp(0,0);
	m_a = ccp(0,0);
}
MoveLabel::~MoveLabel()
{
	if(m_pLabel)
	{
		m_pLabel->release();
		m_pLabel = NULL;
	}
	if(m_pRender)
	{
	    m_pRender->release();
	    m_pRender = NULL;
	}
	
}



void MoveLabel::init(int x,int y,int width,int height)
{
	if(m_pRender)
	{
		removeChild(m_pRender,false);
		m_pRender->release();
	}

	m_rect.setRect(x,y,width,height);
	m_pRender = CCRenderTexture::create(width, height, kCCTexture2DPixelFormat_RGBA8888);	
	m_pRender->retain();
	m_pRender->setPosition(ccp(x, y));
	addChild(m_pRender,0);

}
void MoveLabel::initStr(char * pStr,char* fontName,int fontSize)
{
	if(m_pLabel)
	{
		m_pLabel->release();
	}
	m_pStr = pStr;

	m_fontName = fontName;
	m_fontSize = fontSize;

	m_pLabel = CCLabelTTF::labelWithString(pStr,fontName, m_fontSize);

	m_pLabel->setPosition(ccp(0,0));
	m_pLabel->setColor(ccRED);
	m_pLabel->retain();

	m_p.x =  m_rect.size.width ;
	m_p.y =  m_rect.size.height;
}


void MoveLabel::touchDown(int x,int y)
{
	if(!m_rect.containsPoint(ccp(x+m_rect.size.width/2,y+m_rect.size.height/2)) || !this->isVisible())
		return;

	m_bTouch = true;
	m_down.x = x;
	m_down.y = y;
    m_pre = m_cur = m_down;
	m_count = 0;
	m_v = ccp(0,0);
	m_a = ccp(0,0);
}
void MoveLabel::touchMove(int x,int y)
{
	if(!m_bTouch)
		return;

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//m_pLabel->setScaleY(0.8);
	//m_p.y = s.height - y  - (m_pTarget->getPositionY() -  m_rect.size.height/2 ) -m_dimensions.height/2;
	int dy = m_cur.y - m_pre.y;
	m_pre = m_cur;
	m_cur = ccp(x,y);
	m_p.y -= dy;
	m_count++;
}
void MoveLabel::touchUp(int x,int y)
{
	if(!m_bTouch)
		return;

	m_bTouch = false;
	m_up.x = x;
	m_up.y = y;
	//m_count = 0;
}

void MoveLabel::setStr(char *pStr)
{
}

char *MoveLabel::getStr()
{
	return m_pStr;
}

void MoveLabel::draw()
{
	update();
	drawStr();
}

void MoveLabel::update()
{
	// Î´ÍÏ×§
	if(!m_bTouch)
	{
		if(m_count)
		{
			int len = m_up.y - m_down.y;
			int dy = len/m_count;
			if(dy > 10)
			{
				m_v.y = -40;
				m_a.y = 2;
			}
			else if(dy < -10)
			{
				m_v.y = 40;
				m_a.y = -2;
			}
			m_count = 0;
		}
	}

	m_v.y = m_v.y + m_a.y;

	if(m_v.y < 3 && m_v.y > -3)
	{
		m_v.y = 0;
	}
	m_p.y = m_p.y + m_v.y;

	if(m_p.y >=  m_upBorder && m_p.y <= m_downBorder)
	{
    	//m_pLabel->setPosition(m_p);
	}
	else if(m_p.y <  m_upBorder)
	{
		m_p.y =  m_upBorder;
	}
	else 
	{
		m_p.y  = m_downBorder;
	}
	if(m_upBorder > m_downBorder)
	{
		m_p.y =  m_upBorder;
	}
	m_pLabel->setPosition(m_p);
}

void MoveLabel::drawStr()
{
	if(m_pRender)
	{
	  m_pRender->clear(0,0,0,0.5);
	  m_pRender->begin();
	  m_pLabel->visit();
	  m_pRender->end();
	}
}
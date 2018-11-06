#include "SIX_Cursor.h"

SIX_Cursor::SIX_Cursor()
{
	m_pCursor = 0;
	m_bInited = false;
	m_bIngore = false;
}

SIX_Cursor::~SIX_Cursor()
{
	this->setInited(false);
	setShowSysCursor(TRUE);
	DoRelease();
}

bool SIX_Cursor::LoadCursorFromFile(const char *file)
{
#ifdef WIN32
	if (m_pCursor && this->getInited())
		return true;

	if (!file)
		return false;
	m_pCursor = CCSprite::create(file);
	if (!m_pCursor)
		return false;

	m_pCursor->retain();
	POINT pt;
	RECT rc;
	::GetCursorPos(&pt);
	::GetWindowRect(CCEGLView::sharedOpenGLView()->getHWnd(),&rc);
	if (::PtInRect(&rc,pt))
	{
		pt.x -= rc.left;
		pt.y -= rc.top;
		CCSet *pTouches = new CCSet();
		CCTouch *pTouch = new CCTouch();
		pTouch->setTouchInfo(0,pt.x,pt.y);
		pTouches->addObject(pTouch);
		//OnTouchLogic(pTouches,CCMOUSEMOVE);
		pTouch->release();
		pTouches->release();
	}
	this->setInited();
	return true;
#else
	return false;
#endif
}

void SIX_Cursor::DoRelease()
{
	CC_SAFE_RELEASE_NULL(m_pCursor);
}

void SIX_Cursor::setShowSysCursor(BOOL bShowSysCursor)
{
#ifdef WIN32
	// ref>=0	显示
	// ref==-1	隐藏
	::ShowCursor(TRUE);
	int ref = ::ShowCursor(FALSE);
	if (bShowSysCursor==TRUE)
	{
		if (ref==-1)
			::ShowCursor(TRUE);
	}
	else if (bShowSysCursor==FALSE)
	{
		while (ref>=0)
		{
			ref = ::ShowCursor(FALSE);
		}
	}
#endif
}

BOOL SIX_Cursor::getShowSysCursor()
{
#ifdef WIN32
	::ShowCursor(TRUE);
	int ref = ::ShowCursor(FALSE);
	if (ref==-1)
		return FALSE;
	return TRUE;
#else
	return false;
#endif
}

void SIX_Cursor::setShowOurCursor(bool bShowOurCursor)
{
	if (!m_pCursor)
		return;
	m_pCursor->setVisible(bShowOurCursor);
}

bool SIX_Cursor::getShowOurCursor()
{
	if (!m_pCursor)
		return false;
	return m_pCursor->isVisible();
}

void SIX_Cursor::setIngore(bool bIngore)
{
	m_bIngore = bIngore;
}

bool SIX_Cursor::getIngore()
{
	return m_bIngore;
}

void SIX_Cursor::setInited(bool bInited)
{
	m_bInited = bInited;
}

bool SIX_Cursor::getInited()
{
	return m_bInited;
}

CCSprite *SIX_Cursor::getCursor()
{
	return m_pCursor;
}

void SIX_Cursor::setCursor(CCSprite *cursor)
{
	m_pCursor = cursor;
}

void SIX_Cursor::OnTouchLogic(CCSet *pTouches,int pEvent)
{
#ifdef WIN32
	if (!m_pCursor)
		return;

	/*if (pEvent==CCNCMOUSEMOVE)
	{
		this->setShowOurCursor(false);
		this->setShowSysCursor(TRUE);
		return;
	}*/

	if (!this->getIngore())
	{
		this->setShowOurCursor(true);
		this->setShowSysCursor(FALSE);
	}

	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	CCSetIterator it;
	for( it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *pTouch = (CCTouch *)(*it);
		// 相对GL坐标系
		CCPoint pt = pTouch->getLocation();

		// reset pos
		m_pCursor->setPosition(ccp(pt.x,pt.y));

		switch (pEvent)
		{
		case CCTOUCHBEGAN:
			{
				break;
			}
		case CCTOUCHMOVED:
			{
				break;
			}
		case CCTOUCHENDED:
			{
				break;
			}
		case CCTOUCHCANCELLED:
			{
				break;
			}
		/*case CCMOUSEMOVE:
			{
				break;
			}*/
		}
	}
#endif
}
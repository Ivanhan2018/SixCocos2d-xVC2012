#include "SIX_Scissor.h"

SIX_Scissor::SIX_Scissor()
{
	m_bScissor = false;
	m_fOffsetX = m_fOffsetY = 0.0f;
}

SIX_Scissor::~SIX_Scissor()
{
}

SIX_Scissor* SIX_Scissor::create()
{
	SIX_Scissor *pScissor = new SIX_Scissor();
	if (pScissor && pScissor->init())
	{
		pScissor->autorelease();
		return pScissor;
	}
	CC_SAFE_DELETE(pScissor);
	return 0;
}

void SIX_Scissor::setScissorEnabled(bool IsScissor)
{
	m_bScissor = IsScissor;
}

bool SIX_Scissor::getScissorEnabled()
{
	return m_bScissor;
}

void SIX_Scissor::setScissorOffsetX(float offset)
{
	m_fOffsetX = offset;
}

float SIX_Scissor::getScissorOffsetX()
{
	return m_fOffsetX;
}

void SIX_Scissor::setScissorOffsetY(float offset)
{
	m_fOffsetY = offset;
}

float SIX_Scissor::getScissorOffsetY()
{
	return m_fOffsetY;
}

void SIX_Scissor::beforeDraw()
{
	CCPoint screenPos = this->getPosition();
	screenPos.x = this->getParent()->getPositionX() + m_fOffsetX;
	screenPos.y = this->getParent()->getPositionY() + m_fOffsetY;

    glEnable(GL_SCISSOR_TEST);
	float s = this->getScale();
	CCEGLView::sharedOpenGLView()->setScissorInPoints(screenPos.x*s, screenPos.y*s, getContentSize().width*s, getContentSize().height*s);
}

void SIX_Scissor::visit()
{
	if (!m_bScissor)
	{
		CCControl::visit();
		return;
	}

	if (!isVisible())
    {
		return;
    }

	kmGLPushMatrix();

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        this->transformAncestors();
    }

	this->transform();
	this->beforeDraw();

	if(m_pChildren)
    {
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}

		// this draw
		this->draw();
		
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}
	}
    else
    {
		this->draw();		
    }

	this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }

	kmGLPopMatrix();
}

void SIX_Scissor::afterDraw()
{
	if (m_bScissor)
		glDisable(GL_SCISSOR_TEST);
}
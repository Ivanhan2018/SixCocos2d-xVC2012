/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#include "CCObject.h"
#include "CCAutoreleasePool.h"
#include "ccMacros.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

CCObject* CCCopying::copyWithZone(CCZone *pZone)
{
    CC_UNUSED_PARAM(pZone);
    CCAssert(0, "not implement");
    return 0;
}

HITBOX_MAP *CCObject::hitBox()
{
	return m_hitBox;
}

void CCObject::setHitBox(HITBOX_MAP *hitBox)
{
	m_hitBox = hitBox;

	flushHitBox();
}

void CCObject::flushHitBox()
{
	vertexCount = m_hitBox->size();
	if (vertexCount>MAX_VERTEX_COUNT)
	{
		CCAssert(!(vertexCount>MAX_VERTEX_COUNT),0);
		return;
	}
	int i=0;
	for (HITBOX_ITER mIter=m_hitBox->begin();mIter!=m_hitBox->end();mIter++)
	{
		//if (i>=MAX_VERTEX_COUNT)
		//	break;
		POINT_INFO *pPoint = (POINT_INFO*)(mIter->second);
		if (pPoint->x>=0.0 && pPoint->y>=0.0)
		{
			verticesBuffer[i] = *pPoint;
			i++;
		}
	}
	vertexCount = i;
}

int CCObject::getHitBoxVertexCount()
{
	return m_hitBox->size();
}

CCObject::CCObject(void)
{
    static unsigned int uObjectCount = 0;

    m_uID = ++uObjectCount;
    m_nLuaID = 0;

    // when the object is created, the reference count of it is 1
    m_uReference = 1;
    m_bManaged = false;

	m_hitBox = new HITBOX_MAP();
	verticesBuffer = new POINT_INFO[MAX_VERTEX_COUNT];
	verticesBufferCopy = new POINT_INFO[MAX_VERTEX_COUNT];
	vertexCount = 0;
}

CCObject::~CCObject(void)
{
    // if the object is managed, we should remove it
    // from pool manager
    if (m_bManaged)
    {
        CCPoolManager::sharedPoolManager()->removeObject(this);
    }

	// do release obj here.
	// fixed memory leaks!
	// Cool.Cat
	if (m_hitBox)
	{
		for (HITBOX_ITER mIter=m_hitBox->begin();mIter!=m_hitBox->end();)
		{
			POINT_INFO *pPoint = mIter->second;
			m_hitBox->erase(mIter++);
			CC_SAFE_DELETE(pPoint);
		}
		CC_SAFE_DELETE(m_hitBox);
		CC_SAFE_DELETE_ARRAY(verticesBuffer);
		CC_SAFE_DELETE_ARRAY(verticesBufferCopy);
	}

	// Modifyied by Cool.Cat
	CCScriptEngineManager *pEngineManager = CCScriptEngineManager::sharedManager();
	if (!pEngineManager)
		return;

	CCScriptEngineProtocol* pEngine = pEngineManager->getScriptEngine();
	if (!pEngine)
		return;

    if (m_nLuaID)
    {
        pEngine->removeScriptObjectByCCObject(this);
    }
    else
    {
		if (pEngine->getScriptType() == kScriptTypeJavascript)
        {
            pEngine->removeScriptObjectByCCObject(this);
        }
    }
}

CCObject* CCObject::copy()
{
    return copyWithZone(0);
}

void CCObject::release(void)
{
    CCAssert(m_uReference > 0, "reference count should greater than 0");
    --m_uReference;

    if (m_uReference == 0)
    {
        delete this;
    }
}

void CCObject::retain(void)
{
    CCAssert(m_uReference > 0, "reference count should greater than 0");

    ++m_uReference;
}

CCObject* CCObject::autorelease(void)
{
    CCPoolManager::sharedPoolManager()->addObject(this);

    m_bManaged = true;
    return this;
}

bool CCObject::isSingleReference(void)
{
    return m_uReference == 1;
}

unsigned int CCObject::retainCount(void)
{
    return m_uReference;
}

bool CCObject::isEqual(const CCObject *pObject)
{
    return this == pObject;
}

NS_CC_END

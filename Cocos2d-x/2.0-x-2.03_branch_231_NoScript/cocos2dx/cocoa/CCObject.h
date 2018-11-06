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

#ifndef __CCOBJECT_H__
#define __CCOBJECT_H__

#include "platform/CCPlatformMacros.h"
#include <string>
#include <map>
using namespace std;

NS_CC_BEGIN

// Add by Cool.Cat
// ���㻺���������
#define MAX_VERTEX_COUNT	32

/**
 * @addtogroup base_nodes
 * @{
 */

class CCZone;
class CCObject;
class CCNode;
class CCEvent;

class CC_DLL CCCopying
{
public:
    virtual CCObject* copyWithZone(CCZone* pZone);
};

typedef struct tagPointInfo{
	float x;
	float y;
	tagPointInfo(float ix=-1.0f,float iy=-1.0f)
	{
		x = ix;
		y = iy;
	}
}POINT_INFO;

typedef map<unsigned int,POINT_INFO*> HITBOX_MAP;
typedef HITBOX_MAP::iterator HITBOX_ITER;

class CC_DLL CCObject : public CCCopying
{
public:
	// Add by Cool.Cat
	HITBOX_MAP *hitBox();
	void setHitBox(HITBOX_MAP *hitBox);
	void flushHitBox();
	int getHitBoxVertexCount();
	HITBOX_MAP *m_hitBox;
	// ���㻺��
	POINT_INFO *verticesBuffer;
	// ���㻺�帱��������CCSpriteBatchNode����
	POINT_INFO *verticesBufferCopy;
	int vertexCount;

    // object id, CCScriptSupport need public m_uID
    unsigned int        m_uID;//�౻ʵ�����ܸ���
    // Lua reference id
    int                 m_nLuaID;
protected:
    // ���ü���count of references
    unsigned int        m_uReference;
    // is the object autoreleased
    bool        m_bManaged;        
public:
    CCObject(void);//�������ü���Ϊ1
    virtual ~CCObject(void);
    
    void release(void);//�Ѷ���ļ�����1�������ü����½���0ʱ��ɾ��֮
    void retain(void);//���ü�����1
    CCObject* autorelease(void);
    CCObject* copy(void);
    bool isSingleReference(void);
    unsigned int retainCount(void);//���ü���
    virtual bool isEqual(const CCObject* pObject);

    virtual void update(float dt) {CC_UNUSED_PARAM(dt);};
    
    friend class CCAutoreleasePool;

	// Add by Cool.Cat
	void setObjName(const char *name)
	{
		m_Name.clear();
		m_Name.append(name);
	}
	const char *getObjName()
	{
		return m_Name.c_str();
	}
	std::string m_Name;
};


typedef void (CCObject::*SEL_SCHEDULE)(float);
typedef void (CCObject::*SEL_CallFunc)();
typedef void (CCObject::*SEL_CallFuncN)(CCNode*);
typedef void (CCObject::*SEL_CallFuncND)(CCNode*, void*);
typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
typedef void (CCObject::*SEL_MenuHandler)(CCObject*);
typedef void (CCObject::*SEL_EventHandler)(CCEvent*);
typedef int (CCObject::*SEL_Compare)(CCObject*);

#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)
#define callfuncN_selector(_SELECTOR) (SEL_CallFuncN)(&_SELECTOR)
#define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(&_SELECTOR)
#define callfuncO_selector(_SELECTOR) (SEL_CallFuncO)(&_SELECTOR)
#define menu_selector(_SELECTOR) (SEL_MenuHandler)(&_SELECTOR)
#define event_selector(_SELECTOR) (SEL_EventHandler)(&_SELECTOR)
#define compare_selector(_SELECTOR) (SEL_Compare)(&_SELECTOR)

// end of base_nodes group
/// @}

NS_CC_END

#endif // __CCOBJECT_H__

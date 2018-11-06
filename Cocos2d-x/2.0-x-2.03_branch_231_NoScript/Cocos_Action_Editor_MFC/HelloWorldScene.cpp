#include "HelloWorldScene.h"
#include "Utility.h"

USING_NS_CC;

#define WM_PK	WM_USER + 110
#define WM_PK2	WM_USER	+ 111

extern bool gIsFrame;
extern int gHitPoint;
extern CCSprite *gSelectSprite;

extern MFC_WND_Delegate* EditorDlgPtr();

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer,0,0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

	//// add "HelloWorld" splash screen"
	//CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	//// position the sprite on the center of the screen
	//pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//pSprite->setTag(0);
	//// add the sprite as a child to this layer
	//this->addChild(pSprite, 0,1);

	CCLabelTTF *pTTF = CCLabelTTF::create();
	pTTF->setString(Utility::UnicodeToUtf8(L"使用[文件]=>[导入]选择要导入的精灵帧").c_str());
	pTTF->setPosition(ccp(50,visibleSize.height-50));
	pTTF->setAnchorPoint(ccp(0,0));
	pTTF->setColor(ccc3(255,255,255));
	pTTF->setOpacity(255);
	pTTF->getTexture()->setAntiAliasTexParameters();
	pTTF->setTag(100);
	this->addChild(pTTF);

	pTTF = CCLabelTTF::create();
	pTTF->setString(Utility::UnicodeToUtf8(L"x/y = -/-").c_str());
	pTTF->setPosition(ccp(50,visibleSize.height-50));
	pTTF->setAnchorPoint(ccp(0,0));
	pTTF->setColor(ccc3(255,0,255));
	pTTF->setOpacity(255);
	pTTF->getTexture()->setAntiAliasTexParameters();
	pTTF->setVisible(false);
	this->addChild(pTTF,1,99);

	part = 0;
	//part = MakeParticle(this);
    
	m_SpriteDragged = 0;
	m_LastHitPos = ccp(0,0);
	m_LastRefreshTime = 0;
    // enable standard touch
    this->setTouchEnabled(true);
    return true;
}

CCParticleSystem *HelloWorld::MakeParticle(CCNode *pParent,const char *plist)
{
	if (part)
	{
		part->removeFromParentAndCleanup(true);
	}
	if (!plist)
	{
		part = CCParticleFire::create();
		part->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	}
	else
	{
		part = CCParticleSystemQuad::create(plist);
	}

	CCSize size = pParent->getContentSize();
	part->setPosition(ccp(size.width/2,size.height/2));
	part->setBlendAdditive(true);
	//part->setAutoRemoveOnFinish(true);
	pParent->addChild(part);
	return part;
}

void HelloWorld::onEnter()
{
	CCLayer::onEnter();
	EditorDlgPtr()->Load();
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHBEGAN);
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHENDED);
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHMOVED);
}

void HelloWorld::ccMousesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCMOUSEMOVE);
}

// 实现精灵拖动
// Cool.Cat
void HelloWorld::OnTouchLogic(CCSet *pTouches,int pEvent)
{
	CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
	// 相对GL坐标系
	CCPoint pos = pTouch->getLocation();

	switch (pEvent)
	{
	case CCTOUCHBEGAN:
		{
			CCLabelTTF *pTTF = dynamic_cast<CCLabelTTF*>(this->getChildByTag(99));

			if (gIsFrame)
			{
				if (gHitPoint!=-1 && gSelectSprite)
				{
					CCRect spriteRect = gSelectSprite->boundingBox();
					if (!spriteRect.containsPoint(pos))
						break;

					// update hitbox point data
					HITBOX_MAP *pHitBox = gSelectSprite->getTexture()->hitBox();
					if (!pHitBox)
						break;

					HITBOX_ITER iter = pHitBox->find(gHitPoint);
					if (iter==pHitBox->end())
						break;

					POINT_INFO *pPoint = iter->second;
					if (!pPoint)
						break;

					CCPoint newPos = gSelectSprite->convertToNodeSpace(pos);

					pPoint->x = newPos.x;
					pPoint->y = newPos.y;

					gSelectSprite->getTexture()->flushHitBox();

					::PostMessage(CCEGLView::sharedOpenGLView()->getAttachWindow(),WM_PK2,(WPARAM)gSelectSprite,(LPARAM)pPoint);
				}
			}
			else
			{
				CCNode *pParent = this->getParent();
				pParent->setBBoxDirty(false);
				// 用全局变量替代遍历查找
				if (gSelectSprite)
				{
					CCRect rc = gSelectSprite->boundingBox();
					if (rc.containsPoint(pos))
					{
						gSelectSprite->setBBoxDirty();
						m_SpriteDragged = gSelectSprite;
						m_LastHitPos = pos;

						// refresh properties
						::PostMessage(CCEGLView::sharedOpenGLView()->getAttachWindow(),WM_PK,(WPARAM)m_SpriteDragged,0);
					}
				}
				//for (int i=0;i<this->getChildrenCount();i++)
				//{
				//	CCSprite *pChild = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
				//	if (!pChild)
				//		continue;
				//	if (pChild->getTag()<=0)
				//		continue;
				//	CCRect rc = pChild->boundingBox();
				//	if (rc.containsPoint(pos))
				//	{
				//		pChild->setBBoxDirty();
				//		m_SpriteDragged = pChild;
				//		m_LastHitPos = pos;

				//		// refresh properties
				//		::PostMessage(CCEGLView::sharedOpenGLView()->getAttachWindow(),WM_PK,(WPARAM)m_SpriteDragged,0);
				//		break;
				//	}
				//}
			}
			break;
		}
	case CCMOUSEMOVE:
		{
			if (gIsFrame)
			{
				CCLabelTTF *pTTF = dynamic_cast<CCLabelTTF*>(this->getChildByTag(99));
				if (pTTF)
				{
					if (pos.y-50.0f<=0.0f)
						pTTF->setPosition(ccp(pos.x,pos.y));
					else
						pTTF->setPosition(ccp(pos.x,pos.y-50.0f));

					CCRect spriteRect = gSelectSprite->boundingBox();
					CCString *posStr;
					if (spriteRect.containsPoint(pos))
					{
						CCPoint newPos = gSelectSprite->convertToNodeSpace(pos);
						posStr = CCString::stringWithFormat("x = %.2f\ny = %.2f",newPos.x,newPos.y);
						pTTF->setColor(ccc3(255,0,255));
					}
					else
					{
						posStr = CCString::stringWithFormat("x = %.2f\ny = %.2f",pos.x,pos.y);
						pTTF->setColor(ccc3(255,255,255));
					}
					pTTF->setString(posStr->getCString());
				}
			}
			break;
		}
	case CCTOUCHMOVED:
		{
			if (gIsFrame)
				break;

			if (!m_SpriteDragged)
				break;

			CCPoint HitPos = CCPoint(pos.x - m_LastHitPos.x,pos.y - m_LastHitPos.y);

			float absPosX = m_SpriteDragged->getPositionX()+HitPos.x;
			float absPosY = m_SpriteDragged->getPositionY()+HitPos.y;

			float maxWidth = CCEGLView::sharedOpenGLView()->getFrameSize().width;
			float maxHeight = CCEGLView::sharedOpenGLView()->getFrameSize().height;

			if (absPosX<0.0)
				absPosX = 0.0;
			else if (absPosX+m_SpriteDragged->getContentSize().width>maxWidth)
				absPosX = maxWidth - m_SpriteDragged->getContentSize().width;

			if (absPosY<0.0)
				absPosY = 0.0;
			else if (absPosY+m_SpriteDragged->getContentSize().height>maxHeight)
				absPosY = maxHeight - m_SpriteDragged->getContentSize().height;

			// save it~
			m_LastHitPos = pos;

			m_SpriteDragged->setPosition(ccp(absPosX,absPosY));

			// refresh properties
			unsigned long long now = GetTickCount64();
			if (m_LastRefreshTime+1000<now)
			{
				m_LastRefreshTime = now;
				::PostMessage(CCEGLView::sharedOpenGLView()->getAttachWindow(),WM_PK,(WPARAM)m_SpriteDragged,0);
			}
			break;
		}
	default:
		{
			m_SpriteDragged = 0;
			break;
		}
	}
}

void HelloWorld::draw()
{
	if (gHitPoint!=-1 && gSelectSprite)
	{
		HITBOX_MAP *pHitBox = gSelectSprite->getTexture()->hitBox();
		if (!pHitBox)
			return;

		HITBOX_ITER iter = pHitBox->find(gHitPoint);
		if (iter==pHitBox->end())
			return;

		POINT_INFO *pPoint = iter->second;
		if (!pPoint)
			return;

		DrawPoint(ccc4(255,0,0,255),ccp(gSelectSprite->getPositionX()-gSelectSprite->getContentSize().width/2+pPoint->x,gSelectSprite->getPositionY()-gSelectSprite->getContentSize().height/2+pPoint->y));
	}
	CCLayer::draw();
}

void HelloWorld::DrawPoint(ccColor4B &color,CCPoint &pt)
{
	CCPoint vertices[4] = {
		ccp(pt.x-2,pt.y+2),
		ccp(pt.x-2,pt.y-2),
		ccp(pt.x+2,pt.y-2),
		ccp(pt.x+2,pt.y+2)
	};
	ccDrawColor4F(color.r,color.g,color.b,color.a);
	ccDrawPoly(vertices,4,true);
}
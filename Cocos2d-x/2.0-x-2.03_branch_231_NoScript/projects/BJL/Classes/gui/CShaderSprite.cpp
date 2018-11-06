#include "CShaderSprite.h"


CCShaderSprite::CCShaderSprite(void)
{
	m_uniformPos=0;
	m_uniformTime=0;
	m_RippleTime=0;
	m_RippleSpeed=10;
}


CCShaderSprite::~CCShaderSprite(void)
{
}

CCShaderSprite* CCShaderSprite::create( const char *pszFileName )
{
	CCShaderSprite *pobSprite = new CCShaderSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool CCShaderSprite::initWithFile( const char *pszFilename )
{
	bool ret=false;
	do 
	{
			CCSize winSize=CCDirector::sharedDirector()->getWinSize();
			m_haiouSpt=CCSprite::create(pszFilename);
			m_haiouSpt->setAnchorPoint(ccp(0,0.5f));
			m_haiouSpt->setPosition(CCPointMake(0, winSize.height * 0.5f));
			m_haiouSpt->getTexture()->setAntiAliasTexParameters();
			this->addChild(m_haiouSpt);

			CCSprite* spt=CCSprite::create(pszFilename);
			spt->setAnchorPoint(ccp(0,0));
			spt->setPosition(ccp(m_haiouSpt->getContentSize().width-1,0));
			spt->getTexture()->setAntiAliasTexParameters();
			m_haiouSpt->addChild(spt);
			//CCGLProgram* shader = new CCGLProgram();
			//shader->initWithVertexShaderFilename("example_Water.vsh","example_Water.fsh");
			//shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
			//shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
			//shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
			//shader->link();
			//shader->updateUniforms();
			
			//m_uniformPos					= glGetUniformLocation(shader->getProgram(), "f_point");
			//m_uniformTime				= glGetUniformLocation(shader->getProgram(), "f_time");
			//m_uniformMapHeight		= glGetUniformLocation(shader->getProgram(), "f_height");
			//m_uniformMapWidth		= glGetUniformLocation(shader->getProgram(), "f_width");
			//m_uniformMonsterTex		= glGetUniformLocation(shader->getProgram(), "CC_Texture1");

			//this->setShaderProgram(shader);
			//shader->release();
			//CHECK_GL_ERROR_DEBUG();

			scheduleUpdate();
			schedule(schedule_selector(CCShaderSprite::upHaiou),4.0f);

			ret=true;
			
	} while (0);
	return ret;
}

void CCShaderSprite::update( float delta )
{
	m_RippleTime+=delta*0.01f;
	if (m_RippleTime>=1.0)
	{
		m_RippleTime=0;
	}
}

void CCShaderSprite::draw( void )
{
	float y=m_haiouSpt->getPositionY();
	m_haiouSpt->setPosition(ccp(-m_RippleTime*m_haiouSpt->getContentSize().width,y));
	//--you can set Uniform in here
	//--you can set Uniform in here
	//CC_NODE_DRAW_SETUP();

	//getShaderProgram()->setUniformLocationWith1i(m_uniformMonsterTex,1);
	//getShaderProgram()->setUniformLocationWith1f(m_uniformMapHeight,sUniformMapHeight);
	//getShaderProgram()->setUniformLocationWith1f(m_uniformMapWidth,sUniformMapWidth);
	//getShaderProgram()->setUniformLocationWith2f(m_uniformPos,m_Pos.x,m_Pos.y);
	//getShaderProgram()->setUniformLocationWith1f(m_uniformTime,m_RippleTime);
	//ccGLBindTexture2DN(1,m_MonsterTexture->getName());

	CCNode::draw();
}

void CCShaderSprite::setTouchPos( float x,float y )
{
	CCSize size= CCDirector::sharedDirector()->getWinSize();

	m_Pos.x=x;
	m_Pos.y=y;
}

void CCShaderSprite::upHaiou(float ft)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	CCSpriteFrame * frame=NULL;
	CCAnimation* animation = CCAnimation::create();
	CCString* buf=CCString::createWithFormat("haiou%d.png",rand()%2);
	for(int i=0;i<3;i++)
	{
		CCSprite* sprite = CCSprite::create(buf->getCString());
		frame = CCSpriteFrame::createWithTexture(sprite->getTexture(),CCRectMake(43*i,0,43,32));
		//frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
		animation->addSpriteFrame(frame);
	}
	CCPoint ptStar=ccp(-50,rand()%sUniformMapHeight+winSize.height * 0.2f);
	CCPoint ptEnd=ccp(sUniformMapWidth+50,rand()%sUniformMapHeight+winSize.height * 0.2f);
	float    time=rand()%10+10;
	float   scal=time/20;
	animation->setDelayPerUnit(0.2f);

	CCSprite * HAIOUsPT=CCSprite::createWithSpriteFrame(frame);

	if (rand()%4==0)
	{
		ptStar=ccp(sUniformMapWidth+50,rand()%sUniformMapHeight);
		ptEnd=ccp(-50,rand()%sUniformMapHeight);
		//HAIOUsPT->setRotationY(180.0f);
	}
	HAIOUsPT->setPosition(ptStar);
	HAIOUsPT->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	HAIOUsPT->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(time,ptEnd),CCScaleTo::create(time,scal),NULL),
		CCCallFuncO::create(this,callfuncO_selector(CCShaderSprite::haiouCall),HAIOUsPT),NULL));

	this->addChild(HAIOUsPT);
}

void CCShaderSprite::haiouCall( CCObject* _obj )
{
	CCNode*node=(CCNode*)_obj;
	if(node)node->removeFromParentAndCleanup(true);
}

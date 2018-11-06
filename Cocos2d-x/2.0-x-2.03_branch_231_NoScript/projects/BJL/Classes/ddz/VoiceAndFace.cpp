#include "VoiceAndFace.h"
#include "DDZRes.h"
#include "cocos-ext.h"
#include "SceneData.h"
static VoiceAndFace* s_face=NULL;
/////////////////////////////////////////////////CC_scrollView
bool CC_scrollView::init()
{
	//   ��ʾ��ʾ������
	m_scrollView =CCScrollView::create(CCSizeMake(260,280),NULL);
	m_scrollView->setAnchorPoint(CCPointZero);
	m_scrollView->setPosition(CCPointZero);
	m_scrollView->setTouchEnabled(false);
	m_scrollView->setDirection(kCCScrollViewDirectionVertical);  //���ù����ķ��������ֿ���ѡ��
	m_scrollView->setBounceable(true);
	m_scrollView->setDelegate(this);
	this->addChild(m_scrollView);
	return true;
}

void CC_scrollView::addViewNode( CCNode* _Node,CCSize _size)
{
	m_scrollView->setContainer(_Node);
	m_scrollView->setContentSize(_size);
}

void CC_scrollView::scrollViewDidScroll( CCScrollView* view )
{

}



/////////////////////////////////////////////////CC_listView
bool CC_listView::init()
{
	do
	{
		//CC_BREAK_IF( !CCLayer::init() );
		CCSize size =CCDirector::sharedDirector()->getWinSize();
		m_tableView =CCTableView::create(this,CCSizeMake(220,280));
		m_tableView->setPosition(ccp(0,0));
		m_tableView->setDirection(kCCScrollViewDirectionVertical);


		m_tableView->setDelegate(this);  
		m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);  
		m_tableView->reloadData();// add  
		this->addChild(m_tableView, 1);  
		m_tableView->setTouchEnabled(false);
		//setTouchEnabled(false);
	} while (0);
	return true;
}

cocos2d::CCSize CC_listView::cellSizeForTable( CCTableView *table )
{
	return CCSizeMake(100,50);  
}

CCTableViewCell* CC_listView::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
	const char* buff=((CCString*)strings->objectForKey(CCString::createWithFormat("wav%d",idx)->getCString()))->getCString();
	CCTableViewCell *pCell = table->dequeueCell();
	if (!pCell) {
		pCell = new CCTableViewCell();
		pCell->autorelease();
		CCSprite *pSprite = CCSprite::createWithSpriteFrameName(texture_name::s_yyk);
		pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
		pCell->addChild(pSprite);
		pCell->setTag(idx);

		CCLabelTTF *pLabel = CCLabelTTF::create(buff, "", 14.0);
		pLabel->setAnchorPoint(ccp(0.5,0.5));
		pLabel->setPosition(ccp(pSprite->getContentSize().width*0.5,pSprite->getContentSize().height*0.5));
		pLabel->setTag(123);
		pCell->addChild(pLabel);
		pLabel->setColor(ccc3(173,118,0));
	}
	else
	{
		CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
		pLabel->setString(buff);
		pCell->setTag(idx);
	}

	return pCell; 
}

unsigned int CC_listView::numberOfCellsInTableView( CCTableView *table )
{
	return 6;
}

void CC_listView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("tableCellTouched\n"); 
	CCfaceAndVioce* _data = CCfaceAndVioce::create(msgToLogic_face);
	_data->m_Type =2;
	_data->m_KeyID = cell->getTag();
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,_data);
	if (s_face) s_face->runOutOrIn();
}


bool VoiceAndFace::init()
{
	bool ret =false;
	do 
	{
		CCSize WinSize =CCDirector::sharedDirector()->getWinSize();

		m_BackSpt =CCSprite::createWithSpriteFrameName(texture_name::s_faceBg);
		m_BackSpt->setPosition(ccp(WinSize.width*0.5,WinSize.height*0.5));
		this->addChild(m_BackSpt);
		
// 		m_VoiceSlide= CCSprite::createWithSpriteFrameName(texture_name::s_xlt);
// 		m_VoiceSlide->setPosition(ccp(TEXBACK_WIDTH*0.97,TEXBACK_HEIGHT*0.5));
// 		m_BackSpt->addChild(m_VoiceSlide);
				
		//--��������
		m_FaceNode =CCNode::create();
		m_faceCount=0;
		setFaceElement(0,texture_name::s_faceCool);
		setFaceElement(1,texture_name::s_faceHan);
		setFaceElement(2,texture_name::s_faceHanlen);
		setFaceElement(3,texture_name::s_faceKu);
		setFaceElement(4,texture_name::s_faceNu);
		setFaceElement(5,texture_name::s_faceNue);
		setFaceElement(6,texture_name::s_faceQiu);
		setFaceElement(7,texture_name::s_faceTu);
		setFaceElement(8,texture_name::s_faceXiao);
		setFaceElement(9,texture_name::s_faceYun);

		m_scrollView=CC_scrollView::create();
		m_scrollView->addViewNode(m_FaceNode,CCSizeMake(250,/*m_faceCount/Face_H_Count*68)*/360));			//--�˴���Ҫ���ǻ�ͼ�Ǵ������»����ؼ��Ų�����������
		m_scrollView->setPosition(0,10);
		m_BackSpt->addChild(m_scrollView);

		//--��������
		m_VoiceNode=CC_listView::create();
		m_VoiceNode->setPosition(ccp(TEXBACK_WIDTH*0.53,TEXBACK_HEIGHT*0.05));
		m_BackSpt->addChild(m_VoiceNode);

		//setTouchEnabled(true);
		//setTouchMode(kCCTouchesOneByOne);
		m_isOut =true;
		s_face=this;
		this->setPosition(ccp(this->getPositionX(),WinSize.height*1.0));
		ret =true;
	} while (0);
	return ret;
}

void VoiceAndFace::setFaceElement( int _type,const char * _name )
{
	CCSize size=CCSizeMake(TEXBACK_WIDTH,TEXBACK_HEIGHT);
	size.width=size.width*0.5;
	CCPoint basept =ccp(size.width*0.2,size.height*0.2);
	CCSprite * _spt=CCSprite::createWithSpriteFrameName(_name);
	_spt->setPosition(ccp((m_faceCount%Face_W_Count)*size.width*(0.9f/Face_W_Count)+basept.x,
	basept.y+(m_faceCount/Face_W_Count)*size.height*(0.9/Face_H_Count)));
	_spt->setTag(_type);
	m_FaceNode->addChild(_spt,_type);
	m_faceCount++;
}

bool VoiceAndFace::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pt =pTouch->getLocation();
	if (m_isOut==true)return false;

	if (!m_BackSpt->boundingBox().containsPoint(pt))
	{
		runOutOrIn();
		return true;
	}
	m_TouchBeganPos=pTouch->getLocation();
	m_VoiceNode->m_tableView->ccTouchBegan(pTouch,pEvent);
	m_scrollView->m_scrollView->ccTouchBegan(pTouch,pEvent);
	return true;
}

void VoiceAndFace::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	m_VoiceNode->m_tableView->ccTouchMoved(pTouch,pEvent);
	m_scrollView->m_scrollView->ccTouchMoved(pTouch,pEvent);
}

void VoiceAndFace::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCObject* pObj=NULL;
	CCPoint pt =pTouch->getLocation();
	m_VoiceNode->m_tableView->ccTouchEnded(pTouch,pEvent);
	m_scrollView->m_scrollView->ccTouchEnded(pTouch,pEvent);
	if(ccpLength(ccp(pt.x-m_TouchBeganPos.x,pt.y-m_TouchBeganPos.y))<=10)
	{
		//--�������
		CCARRAY_FOREACH(m_FaceNode->getChildren(),pObj)
		{
			CCSprite* pNode=(CCSprite*)pObj;
			CCPoint _Nodept=m_FaceNode->convertToNodeSpace(pt);
			if (pNode->boundingBox().containsPoint(_Nodept))
			{
				CCfaceAndVioce* _data = CCfaceAndVioce::create(msgToLogic_face);
				_data->m_Type =1;
				_data->m_KeyID = pNode->getTag();
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,_data);
				runOutOrIn();
				return ;
			}
		}
		//--���������list���洦��
	}
}

void VoiceAndFace::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void VoiceAndFace::runOutOrIn(bool isVisible)
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	m_isOut=!m_isOut; 
	this->stopAllActions();
	this->runAction(CCMoveTo::create(0.2f,m_isOut?ccp(this->getPositionX(),size.height*1.0):ccp(this->getPositionX(),size.height*0.00)));
}

void VoiceAndFace::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min)(),true);
	CCLayer::onEnter();
}

void VoiceAndFace::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


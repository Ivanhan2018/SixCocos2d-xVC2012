#include "Settlement.h"
#include "SceneData.h"
#include "SoundControl.h"

Settlement::Settlement()
{

}

Settlement::~Settlement()
{

}

bool Settlement::init()
{
	//if (!CCNode::init())
	//{
	//	return false;
	//}
	do 
	{
		m_bgLeftSprite = CCSprite::createWithSpriteFrameName(texture_name::s_settlementbg);
		m_bgLeftSprite->setAnchorPoint(ccp(1.0f,0.5f));
		m_bgLeftSprite->getTexture()->setAntiAliasTexParameters();
		m_bgLeftSprite->setPositionX(0.5f);
		this->addChild(m_bgLeftSprite);
		CCSprite * bgRightSprite = CCSprite::createWithSpriteFrameName(texture_name::s_settlementbg);
		bgRightSprite->setFlipX(true);
		bgRightSprite->setAnchorPoint(ccp(0,0.5f));
		bgRightSprite->getTexture()->setAntiAliasTexParameters();
		bgRightSprite->setPositionX(-0.5f);
		m_batchNode = CCSpriteBatchNode::create(texture_name::s_cardTable);
		this->addChild(bgRightSprite);
		this->addChild(m_batchNode);
	} while (0);
	return true;
}

void Settlement::addString(char* key,CCPoint point,_ccColor3B  color,int fontSize,int tag,int num)
{
	CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
	CCString str;
	str.initWithFormat("%s%d",((CCString*)strings->objectForKey(key))->getCString(),num);
	CCLabelTTF * pLableTTF = CCLabelTTF::create(str.getCString(),"Arial",fontSize);
	pLableTTF->setColor(color);
	pLableTTF->setPosition(point);
	this->addChild(pLableTTF,1,tag);
}

void Settlement::setUserMessage(CCInteger * obj)
{
	CCSettmentUserMessage * user = (CCSettmentUserMessage*)obj;
	_ccColor3B color = ccc3(161,84,32);
	switch(user->m_userId)
	{
	case 0:
		{
			if(1==SoundEffect::sharedSoundEffect()->m_leftUser.gender)
			{
				addUserString(texture_name::s_man_head_icon,50.0f,color,18,user->m_updScore,user->m_nikeName,user->m_isJiabei,user->m_userId==user->m_diZhuId?true:false,false);
			}
			else
			{
				addUserString(texture_name::s_woman_head_icon,50.0f,color,18,user->m_updScore,user->m_nikeName,user->m_isJiabei,user->m_userId==user->m_diZhuId?true:false,false);
			}
			
		}
		break;
	case 1:
		{
			if (1==SoundEffect::sharedSoundEffect()->m_self.gender)
			{
				addUserString(texture_name::s_man_head_icon,100.0f,color,18,user->m_updScore,user->m_nikeName,user->m_isJiabei,user->m_userId==user->m_diZhuId?true:false,true);
			}
			else
			{
				addUserString(texture_name::s_woman_head_icon,100.0f,color,18,user->m_updScore,user->m_nikeName,user->m_isJiabei,user->m_userId==user->m_diZhuId?true:false,true);
			}
			
		}
		break;
	case 2:
		{
			if (1==SoundEffect::sharedSoundEffect()->m_rightUser.gender)
			{
				addUserString(texture_name::s_man_head_icon,0,color,18,user->m_updScore,user->m_nikeName,user->m_isJiabei,user->m_userId==user->m_diZhuId?true:false,false);
			}
			else
			{
				addUserString(texture_name::s_woman_head_icon,0,color,18,user->m_updScore,user->m_nikeName,user->m_isJiabei,user->m_userId==user->m_diZhuId?true:false,false);
			}
		}
		break;
	}
}

void Settlement::setTimesMessage(CMD_S_GameEnd* _gameEnd,WORD _userID)
{
	float yPos1 = -50.0f;
	float yPos2 = -90.0f;
	float fontSize1 = 18;
	float fontSize2 = 20;
 	int NumData=0;
	_ccColor3B color = ccc3(161,84,32);
	//����
	//NumData=1;
	//for(int i=0;i<3;i++)
	//{
	//	if (_gameEnd->bOpenCard[i]>0)
	//	{
	//		NumData *=_gameEnd->bOpenCard[i];
	//	}
	//}
	//addString("showcard",ccp(-175.0f,-40.0f),color,14,tag_showcard,NumData>1?NumData:0);

	//�ӱ�
//  	NumData=1;
// 	for(int i=0;i<3;i++)
//// 	{
//// 		if (_gameEnd->bAdd[i])
//// 		{
//// 			NumData *=2;
//// 		}
//// 	}
//// 	addString("jiabei",ccp(-60.0f,-40.0f),color,14,tag_jiabei,NumData);
//
//	//������
//	NumData=0;
//	for(int i=0;i<3;i++)
//	{
//		if (_gameEnd->bLandLand[i]==4){
//			NumData +=2;
//		}else if(_gameEnd->bLandLand[i]>=2){
//			NumData +=1;
//		}else{
//		}
//	}
//	addString("qiangdizhu",/*ccp(60.0f,-40.0f)*/ccp(-113.0f,yPos1),color,fontSize1,tag_qiangdizhu,_gameEnd->bLandLand[0]);
//	//ը��
//	if (_gameEnd->wBombNum<=0)
//	{
//		addString("bomb",/*ccp(180.0f,-40.0f)*/ccp(0,yPos1),color,fontSize1,tag_bomb,0);
//	}else
//	{
//		addString("bomb",/*ccp(180.0f,-40.0f)*/ccp(0,yPos1),color,fontSize1,tag_bomb,_gameEnd->wBombNum);
//	}
//	
//	//����
//	addString("spring",/*ccp(-180.0f,-75.0f)*/ccp(113.0f,yPos1),color,fontSize1,tag_spring,_gameEnd->bSpring==true?2:0);
//	//��������
//	//addString("lowcardtype",/*ccp(-60.0f,-75.0f)*/ccp(-175.0f,-75.0f),color,14,tag_lowcardtype,_gameEnd->backType);
//	//��������
//	//addString("overcardtype",/*ccp(60.0f,-75.0f)*/ccp(-55.0f,-75.0f),color,14,tag_overcardtype,_gameEnd->taskType);
//	//�׷�
//	addString("basescore",/*ccp(180.0f,-75.0f)*/ccp(-75.0f,yPos2),color,fontSize2,tag_basescore,_gameEnd->lCellScore);
//	//�ܱ���
//	addString("total",ccp(75,yPos2),color,fontSize2,tag_total,_gameEnd->allBeillu[0]);
//	//˰��
//	//addString("tableconsume",ccp(-165.0f,-100.0f),color,14,tag_tableconsume,_gameEnd->lGameTax[_userID]);

}

void Settlement::addUserString(const char * res,float pointY,_ccColor3B color,int fontSize,long udpScore,const char * nikeName,bool isJiaBei,bool isDiZhu,bool isSelf)
{
 	CCSprite * userIcon = CCSprite::createWithSpriteFrameName(res);
 	userIcon->setPosition(ccp(-180.0f,pointY));
	userIcon->setScale(0.6f);
 	m_batchNode->addChild(userIcon);
	if (isJiaBei)
	{
		CCSprite * jiaBei = CCSprite::createWithSpriteFrameName(texture_name::s_jiaBeiTag);
		jiaBei->setPosition(ccp(40.0f,pointY));
		m_batchNode->addChild(jiaBei);
	}
	if (isSelf)
	{
		CCSprite * showSelf = CCSprite::createWithSpriteFrameName(texture_name::s_showSelf);
		showSelf->setPosition(ccp(0,pointY));
		m_batchNode->addChild(showSelf);
	}
	if (isDiZhu)
	{
		CCSprite * diZhuTag = CCSprite::createWithSpriteFrameName(texture_name::s_diZhuTag);
		diZhuTag->setPosition(ccp(-180.0f,pointY));
		m_batchNode->addChild(diZhuTag);
	}
	CCLabelTTF * nikeNameTTF = CCLabelTTF::create(nikeName,"Arial",fontSize);
	nikeNameTTF->setColor(color);
	nikeNameTTF->setPosition(ccp(-75.0f,pointY));
	this->addChild(nikeNameTTF);
	CCString str;
	if (udpScore>=0)
	{
		str.initWithFormat("+%ld",udpScore);
	}else
	{
		str.initWithFormat("%ld",udpScore);
	}
	
	CCLabelTTF * udpScoreTTF = CCLabelTTF::create(str.getCString(),"Arial",fontSize);
	udpScoreTTF->setColor(color);
	udpScoreTTF->setPosition(ccp(130.0f,pointY));
	this->addChild(udpScoreTTF);
	
}
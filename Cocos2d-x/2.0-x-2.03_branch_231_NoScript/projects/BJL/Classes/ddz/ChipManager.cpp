/***************************************
 筹码管理类
 ***************************************/
#include "ChipManager.h"
#include "CocosUnits.h"
#include "DDZRes.h"
using namespace cocos2d;

CCRect chipPosRect[8] = {
	CCRect(0,180,212,116),
	CCRect(225,180,350,80),
	CCRect(586,180,212,116),
	CCRect(0,120,200,60),
	CCRect(590,120,200,60),
	CCRect(217,108,367,68),
	CCRect(0,298,224,70),
	CCRect(576,298,224,70)
};

float chipWidth = 40;
float chipHeight = 35;

void addRandSeedTimeSprite()
{
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d(&psv, NULL);
	unsigned long int rand_seed = psv.tv_sec*1000+psv.tv_usec/1000;
	srand(rand_seed);
}

CCPoint randomPosInRect(int index)
{
	if(index<0||index>7)
	{
		return CCPoint(0,0);
	}
	addRandSeedTimeSprite();
	CCRect rect = chipPosRect[index];
	CCPoint pos;
	pos.x = rect.origin.x+rand()%((int)(rect.size.width-chipWidth));
	pos.y = rect.origin.y+rand()%((int)(rect.size.height-chipHeight));
	return pos;
}

ChipManager::ChipManager()
{

}

ChipManager::~ChipManager()
{
	if (ChipManagerArray != NULL)
	{
		ChipManagerArray->release();
		ChipManagerArray = NULL;
	}	
}

ChipManager *ChipManager::create(){
	ChipManager *chipManager = new ChipManager();
	if (chipManager&&chipManager->initTotalChipValue())
	{
		chipManager->autorelease();
		return chipManager;
	}	
	CC_SAFE_DELETE(chipManager);
	return NULL;
}

bool ChipManager::initTotalChipValue()
{
	bool bRet = false;
	do 
	{

		WinSize = CCDirector::sharedDirector()->getWinSize();
		for (int i = 0;i<8;i++)
		{
			m_pTotalChipValue[i] = CCLabelAtlas::create("0",texture_name::s_ChipMagerNumber,12,17,'0');
			m_pTotalChipValue[i]->setAnchorPoint(CCPointZero);
			m_pSpriteNunber[i] = CCSprite::createWithSpriteFrame(spriteFrame("SCORE_BACK.png"));
			m_pSpriteNunber[i]->setAnchorPoint(CCPointZero);

			switch (i)
			{
			case 0:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.1,WinSize.height*0.4));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.1-40,WinSize.height*0.4));
				}break;
			case 1:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.5,WinSize.height*0.4));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.5-40,WinSize.height*0.4));

				}break;
			case 2:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.8,WinSize.height*0.4));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.8-40,WinSize.height*0.4));
				}break;
			case 3:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.1,WinSize.height*0.25));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.1-40,WinSize.height*0.25));

				}break;
			case 4:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.8,WinSize.height*0.25));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.8-40,WinSize.height*0.25));

				}break;

			case 5:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.5,WinSize.height*0.25+10));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.5-40,WinSize.height*0.25+10));

				}break;
			case 6:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.1,WinSize.height*0.65));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.1-40,WinSize.height*0.65));

				}break;
			case 7:
				{
					m_pTotalChipValue[i]->setPosition(ccp(WinSize.width *0.8,WinSize.height*0.65));
					m_pSpriteNunber[i]->setPosition(ccp(WinSize.width*0.8-40,WinSize.height*0.65));

				}break;	
			default:
				break;
			}
			m_pTotalChipValue[i]->setVisible(false);
			m_pSpriteNunber[i]->setVisible(false);
		    addChild(m_pTotalChipValue[i],1);
			addChild(m_pSpriteNunber[i],1);
			ChipManagerArray = CCArray::create();
			ChipManagerArray->retain();
		}
		bRet = true;
	} while (0);

	return bRet;
}

void ChipManager::initGetChipManager()
{
	for (int i = 0; i < 8; i++)
	{
		m_pTotalChipValue[i]->setString(CCString::createWithFormat("%d",0)->getCString());
	}
}
void ChipManager::showTotalChipValue()
{
	for (int i = 0;i<8;i++)
	{
		m_pTotalChipValue[i]->setVisible(true);
		m_pSpriteNunber[i]->setVisible(true);
	}
}

void ChipManager::dissRemoveChuoValue()
{
	for (int i = 0;i<8;i++)
	{
		m_pTotalChipValue[i]->setVisible(false);
		m_pSpriteNunber[i]->setVisible(false);

	}
	//判断条件删除时,最好能够逆向遍历删除,这样不会漏掉任何元素
	for (int i = 0 ; i < ChipManagerArray->count() ; i++)
	{
		CCNode *node = (CCNode *)ChipManagerArray->objectAtIndex(i);
		node->removeFromParentAndCleanup(true);
	}
	CCLog("ChipManagerArray has %d element", ChipManagerArray->count());
	ChipManagerArray->removeAllObjects();
}
void ChipManager::showGetChipManager( BYTE cbBetArea,LONGLONG lBetScore )
{
	for (int i = 0; i < 8; i++)
	{	
		if (cbBetArea == i)
		{
			m_pTotalChipValue[i]->setVisible(true);
			m_pSpriteNunber[i]->setVisible(true);
			m_pTotalChipValue[i]->setString(CCString::createWithFormat("%I64d",lBetScore)->getCString());
		}
	}
}

void ChipManager::showChipManagerSprite( BYTE cbBetArea, LONGLONG lBetScore )
{
	CCSize	 WinthSize = CCDirector::sharedDirector()->getWinSize();
	char Stringing[150];
	LONGLONG m_lBetScore = 0;
	m_lBetScore =(lBetScore/100);
	int CiNumber=0;//次数
	sprintf(Stringing, "BJL_Cannger_%d.png",m_lBetScore);
	CCSprite *m_pSpriteChipValue = CCSprite::createWithSpriteFrame(spriteFrame(Stringing));
	m_pSpriteChipValue->setAnchorPoint(CCPointZero);
	m_pSpriteChipValue->setScale(0.5);
	//case 0:      //闲
	//case 1:    //平
	//case 2:    //庄
	//case 3:    //闲天王
	//case 4:    //庄天王 
	//case 5:    //同上平
	//case 6:    //闲对子
	//case 7:    //庄对子
	m_pSpriteChipValue->setPosition(randomPosInRect(cbBetArea));
	this->addChild(m_pSpriteChipValue);
	ChipManagerArray->addObject(m_pSpriteChipValue);

}


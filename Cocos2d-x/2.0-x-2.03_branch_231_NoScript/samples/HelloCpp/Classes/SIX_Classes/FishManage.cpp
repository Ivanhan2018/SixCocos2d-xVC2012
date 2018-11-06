#include "FishManage.h"
#include "CCActionEx.h"
#include "Curve.h"
#include "Gold.h"
#include "Ship.h"
#include "SIX_SceneGame.h"
#include "SIX_GlobalMgr.h"

CFishMgr *g_FishMgr = NULL;

// --���ͷ������
double *s_AllFishArg;
// --ը����ͷ������
double *s_AllBombArg;

int ARR_FISH[] = {1,2,3,4,5,6,7,8,9,10,12,15,18,20,25,30,40};
int ARR_FISH_COUNT = sizeof(ARR_FISH)/sizeof(int);

int ARR_BOMB[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,34,35,37,40,46,48};
int ARR_BOMB_COUNT = sizeof(ARR_BOMB)/sizeof(int);

const char ARR_FRAME_FMT[4][256] = {
	"Fish_%02d_%05d.png",
	"Fish_%02d_00000.png",
	"Bomb_%02d_%05d.png",
	"Bomb_%02d_00000.png"
};

int ARR_STARFISH_COUNT = 3;

// --ȡ�̡�ȡģ
void qr(int fishType,int *q,int *r)
{
    //*q=floor(fishType/100.0);
    //*r=fishType-(int)(floor(fishType/100.0)*100.0);
	*q=fishType/100;
	*r=fishType%100;
}

//--���ͷ������
//--[[
//fishType=1,2,40,����,����pi
//fishType=3,����0
//fishType=10,����pi*0.5
//]]
float qrArg(int fishType)
{
    int q=0;
	int r=0;
	qr(fishType,&q,&r);

    if (q==0)
	{
       int idx=CFishMgr::GetIndexFromArray(r,true);
       float arg=s_AllFishArg[idx];
       return arg;
	}
	else
	{
       int idx=CFishMgr::GetIndexFromArray(r,false);
	   float arg=s_AllBombArg[idx];
       return arg;
	}
}

const char *qrName(int fishType)
{
    int q=0;
	int r=0;
	qr(fishType,&q,&r);

    if (q==0)
       return "Fish";
	else
       return "Bomb";
}

// ---------------------------------------

CFish::CFish()
{
}

CFish::~CFish()
{
}

CFish *CFish::spriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	//CCSprite *pSprite = CCSprite::createWithSpriteFrame(pSpriteFrame);
 //   CFish *fish = (CFish*)pSprite;
	CFish *fish = new CFish();
    if (!fish)
		return 0;

	if (!fish->initWithSpriteFrame(pSpriteFrame))
	{
		CC_SAFE_DELETE(fish);
		return 0;
	}
	fish->autorelease();
	fish->retain();
	return fish;
}

CFish *CFish::spriteWithSpriteFrameName(const char *pszSpriteFrameName)
{
    if (!pszSpriteFrameName)
	{
        SIXLog("Fish.spriteWithSpriteFrameName.pszSpriteFrameName.Nil!");
        return 0;
	}
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    if (!pFrame)
		return 0;
	return spriteWithSpriteFrame(pFrame);
}

bool CFish::randomCatch(int level)
{
	int rnd = SIX_Utility::GetInstance()->RNDNUM(0,9);
	if (rnd >= level)
        return true;
    return false;
}

void CFish::SpriteRemoveCallBack(CCNode *node)
{
	CFish *pFish = (CFish *)(node);
	if (!pFish)
		return;

	//if (NULL != pFish)
	//{
	//	SIX_Lock lock(g_FishMgr->mutex);
	//	{
	//		FISH_MAP::iterator it = CFishMgr::GetInstance()->mFishData.find( pFish );
	//		if ( CFishMgr::GetInstance()->mFishData.end() != it)
	//		{
	//			FISH_DATA *pFishData = (FISH_DATA *)it->second;
	//			CFishMgr::GetInstance()->mFishData.erase( it );
	//			CC_SAFE_DELETE( pFishData );
	//		}
	//	}
	//}

	//pFish->removeAllChildrenWithCleanup( true );
	pFish->removeFromParentAndCleanup( true );

	// ��Ϊ���
	// Cool.Cat
	//SIX_Lock lock(g_FishMgr->mutex);
	//{
		FISH_MAP::iterator it = CFishMgr::GetInstance()->mFishData.find( pFish );
		if ( CFishMgr::GetInstance()->mFishData.end() != it)
		{
			FISH_DATA *pFishData = (FISH_DATA *)it->second;
			//CFishMgr::GetInstance()->mFishData.erase( it );
			//CC_SAFE_DELETE( pFishData );
			pFish->setVisible(false);
			pFishData->uld = 0;
			if (pFishData->pFishMgr->m_FishPool)
				pFishData->pFishMgr->m_FishPool->Push(pFish);
#ifdef USING_FISH_SHADOW
			pFishData->pShadow->setVisible(false);
			pFishData->pShadow->removeFromParentAndCleanup(true);
#endif
		}
	//}
}

//--[[
//���ױ��������ߣ�P_0,P_1,P_2,P_3���˻�Ϊ���ױ��������ߣ�P_0,P_1,P_2���������ߣ����P_0=���Ƶ�P_1,���Ƶ�P_2,�յ�P_3��
//����˵����
//startP----�켣���
//endP----�켣�յ�
//startAngle----
//endAngle----
//time----����ʱ��
//]]
void CFish::moveWithParabola(CCPoint startP,CCPoint endP,float startAngle,float endAngle,float time,TFishID uld/*=0*/)
{
	float sx = startP.x;
	float sy = startP.y; 
	float ex =endP.x;
	float ey =endP.y;

	float h = getContentSize().height * 0.5;
	CCPoint pos=CCPoint(sx,sy);
	setPosition(pos);
	setRotation(startAngle);

	// -- ����������
	ccBezierConfig bezier;
	// -- ���Ƶ�1(���)
	bezier.controlPoint_1 = ccp(sx, sy);
	// -- ���Ƶ�2
	//--bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5);
	bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+100);	
	// -- �յ�
	bezier.endPosition = ccp(endP.x, endP.y);

	CCBezierTo *actionMove = CCBezierTo::create(time, bezier);
	CCRotateTo *actionRotate = CCRotateTo::create(time, endAngle);
	CCSpawn *action = CCSpawn::createWithTwoActions(actionMove, actionRotate);
	CCCallFuncN *pcc=CCCallFuncN::create(this, callfuncN_selector(CFish::SpriteRemoveCallBack ));
	CCSequence *sq = CCSequence::createWithTwoActions(action,pcc);
	CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
	runAction(speed);
	speed->setTag(uld);
}

void CFish::moveWithBezier3(float duration,float InitElapsed,CCPoint p1,CCPoint p2,CCPoint p3,TFishID uld/*=0*/)
{
	//setPosition(p0);
	// -- 3�ױ���������
	ccBezierConfig bezier;
	// -- ���Ƶ�1
	bezier.controlPoint_1 = p1;
	// -- ���Ƶ�2
	bezier.controlPoint_2 = p2;	
	// -- �յ�
	bezier.endPosition = p3;

	CCBezierTo *actionMove = CCBezierTo::create(duration,bezier,InitElapsed);
	CCCallFuncN *pcc=CCCallFuncN::create(this, callfuncN_selector(CFish::SpriteRemoveCallBack ));
	CCSequence *sq = CCSequence::createWithTwoActions(actionMove,pcc);
	CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
	runAction(speed);
	speed->setTag(uld);
}

//--[[
//������˶��켣�ɹ켣���͡��켣������ꡢ�켣�ٶȵ��໥�����Ĳ���������
//����˵����
//uld--��ID������켣����ID
//pathType--�켣����
//1��ʾֱ�߹켣���������arg1��ʾ�켣��������pathType=1��arg1=ccp(1500,1500)��ʾ���Ͻ�45��ֱ�߹켣��pathType=1��arg1=ccp(1500,0)��ʾˮƽ����ֱ�߹켣
//2��ʾԲ�켣
//3��ʾ���߹켣���������arg1����뾶�ͷ�����ֵ�������������arg2.y������߹켣���򣬶������arg3.x����m_direction
//4��ʾ�������߹켣��(int)arg1.x�ĵ�(int)arg1.y���켣
//5��ʾ���ױ��������߹켣
//6��ʾ�����׵����߹켣��arg1����a=r�ͷ�����ֵ����=deltArg��arg3.x����m_direction(����������ʾ�桢˳ʱ�밢���׵¹켣)
//7��ʾ��ͣ��ֱ�߹켣��startP����켣���A��arg1����켣�յ�C��arg3.x=�˱�ʾ�켣ͣ�ٵ�B�������߶�AB���ɵıȣ�arg2.x=tA,arg2.y=tC��ʾͣ��ʱ��
//arg1--��һ�����������ֱ�߹켣��Բ�켣�����߹켣����ͣ��ֱ�߹켣�������׵����߹켣�����ױ��������߹켣���������߹켣Ҫ�õ�
//arg2--�ڶ���������������߹켣����ͣ��ֱ�߹켣�����ױ��������߹켣Ҫ�õ�
//arg3--������������������߹켣����ͣ��ֱ�߹켣�������׵����߹켣�����ױ��������߹켣Ҫ�õ�
//]]
void CFish::addPath(int pathType,float duration,float InitElapsed,CCPoint arg1,CCPoint arg2,CCPoint arg3,TFishID uld/*=0*/)
{
	if(pathType==1)
	{
		//--�����켣���ͺ㶨�ٶ�ʸ�����㶨���ʺͺ㶨���򣩵�����ֱ���˶�
		//--����ֱ�߹켣��arg1����ֱ�߹켣��������ccp(1500,1500)�������Ͻ�45��ֱ�߹켣��ccp(1500,0)����ˮƽ����ֱ�߹켣
		//--������֡��Դ�е���ͷ���������켣��������˳ʱ����ת�Ƕȣ��Ƕ��ƣ�
		float angle=(qrArg(getTag())-atan2(arg1.y,arg1.x))*180/M_PI;
		setRotation(angle);
		CCMoveBy *actionMove = CCMoveBy::create(duration,arg1,InitElapsed);

		//--�ڹ켣ʱ���ڣ��㾫������ɾ������
		CCCallFuncN *pcc=CCCallFuncN::create( this,callfuncN_selector(CFish::SpriteRemoveCallBack) );
		CCSequence *sq = CCSequence::createWithTwoActions(actionMove, pcc);
		CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
		runAction(speed);
		speed->setTag(uld);
	}
	if(pathType==2)
	{
		CCPoint startP=CCPoint(getPositionX(),getPositionY());
		// --����Բ�켣��arg1����Բ������
		myAction *actionMove = myAction::createTrace1(duration,InitElapsed,(pFuncTrace1)Curve::CircleTraceFunc,startP,arg1,20,CCPoint(0,0));
		CCCallFuncN *pcc=CCCallFuncN::create( this,callfuncN_selector(CFish::SpriteRemoveCallBack) );
		CCSequence *sq = CCSequence::createWithTwoActions(actionMove,pcc);
		CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
		runAction(speed);
		speed->setTag(uld);
	}
	if(pathType==3)
	{
		CCPoint startP=CCPoint(getPositionX(),getPositionY());
		//// --���ڰ��߹켣��arg1����뾶�ͷ�����ֵ����
		//float angle=(qrArg(getTag())-arg2.y)*180/M_PI;
		//setRotation(angle);
		if(arg3.x==0)
			arg3.x=3;
		myAction *actionMove = myAction::createTrace1(duration,InitElapsed,Curve::CycloidTraceFunc,startP,arg1,arg3.x,arg2);
		actionMove->setFunc1((pFuncVoid)Curve::CycloidTraceFunc1);
		CCCallFuncN *pcc=CCCallFuncN::create( this,callfuncN_selector(CFish::SpriteRemoveCallBack) );
		CCSequence *sq = CCSequence::createWithTwoActions(actionMove,pcc);
		CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
		runAction(speed);
		speed->setTag(uld);
	}
	if(pathType==4)
	{
		//--�Զ����˶��켣
		pFuncTrace0 Func=CurveHelper::Instance().GetCurve(arg1);
		if(Func==NULL)
			Func=Curve::Trace_9_16_4;
		myAction *pAction=myAction::createTrace0(duration,InitElapsed,Func);
		CCEaseInOut *move_ease_inout = CCEaseInOut::create(pAction,2);
		//runAction(move_ease_inout);
		CCCallFuncN *pcc=CCCallFuncN::create( this,callfuncN_selector(CFish::SpriteRemoveCallBack) );
		CCSequence *sq = CCSequence::createWithTwoActions(move_ease_inout,pcc);
		CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
		runAction(speed);
		speed->setTag(uld);
	}
	if(pathType==5)
	   //moveWithBezier3(ccp(260,743), ccp(307,187), ccp(383,-202), ccp(1110,307), 20.0);
	   moveWithBezier3(duration,InitElapsed,arg1,arg2,arg3,uld);
	if(pathType==6)
	{
		CCPoint startP=CCPoint(getPositionX(),getPositionY());
		// --���ڰ����׵����߹켣��arg1����a=r�ͷ�����ֵ����=deltArg
		if(arg3.x==0)
			arg3.x=3;
		myAction *actionMove = myAction::createTrace1(duration,InitElapsed,Curve::ArchimedesSpiralTraceFunc,startP,arg1,arg3.x,arg2);
		actionMove->setFunc1((pFuncVoid)Curve::ArchimedesSpiralTraceFunc1);
		CCCallFuncN *pcc=CCCallFuncN::create( this,callfuncN_selector(CFish::SpriteRemoveCallBack) );
		CCSequence *sq = CCSequence::createWithTwoActions(actionMove,pcc);
		CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
		runAction(speed);
		speed->setTag(uld);
	}
	if(pathType==7)
	{
		CCPoint startP=CCPoint(getPositionX(),getPositionY());
		float angle=(qrArg(getTag())-atan2(arg1.y-startP.y,arg1.x-startP.x))*180/M_PI;
		setRotation(angle);
		//--��ͣ��ֱ�߹켣
		//if(arg3.x==0)
		//	arg3.x=1;//��ʾB����AC���е�
		myAction *pAction=myAction::createTrace1(duration,InitElapsed,Curve::GoStopGoLineTrace,startP,arg1,arg3.x,arg2);
		CCCallFuncN *pcc=CCCallFuncN::create( this,callfuncN_selector(CFish::SpriteRemoveCallBack) );
		CCSequence *sq = CCSequence::createWithTwoActions(pAction,pcc);
		CCSpeed *speed= CCSpeed::actionWithAction(sq,1.0f);//1��������
		runAction(speed);
		speed->setTag(uld);
	}
	if(pathType==8)
		moveWithParabola(ccp(200, 300), ccp(500, 300), 0.0, 20.0, 3.0,uld);
}

void CFish::DieAnimation(const FISH_DATA * pFishData)
{
	stopAllActions();
	setVisible( false );
	setAnchorPoint(CCPoint(0.5,0.5));

	CCArray *pArray= CCArray::create();
	int q=0;
	int r=0;
	qr(getTag(), &q, &r);
	// ������Ч
	if (8 <= PlayerTreasureInfo::getFishMulti(pFishData->fishKind))
	{
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(r*100,false);
	}

	if(q==0)	//����
	{
		for (int i=0; i<=24; i+=2)
		{
			CCString *pStrBuffer = CCString::createWithFormat("DeadFish_%02d_%05d.png", r, i);
			CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrBuffer->getCString() );
			if ( NULL == pFrame)
				break;
			pArray->addObject( pFrame );
			pFrame->setObjName(pStrBuffer->getCString());
		}
		//SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("A.%s",this->getObjName());
		// �����Լ�
		CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames( pArray, 0.1f );
		CCActionInterval *pAnimate = CCAnimate::create( pAnimation );
		CCArray *FishActionArray = CCArray::create();
		FishActionArray->addObject( CCShow::create() );
		FishActionArray->addObject( pAnimate );
		FishActionArray->addObject( CCCallFuncN::create(this, callfuncN_selector(CFish::SpriteRemoveCallBack) ) );
		runAction( CCSequence::create( FishActionArray ));
		return;
	}
	else
	{
		//SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("B.%s",this->getObjName());
		 // �����Լ�
		CCArray *FishActionArray = CCArray::create();
		FishActionArray->addObject(CCCallFuncN::create(this, callfuncN_selector(CFish::SpriteRemoveCallBack) ) );
		CCPoint bombPT = getPositionLua();
		runAction( CCSequence::create(FishActionArray));

		//// ��ը��
		//for (int i=0; i<=13; i++)
		//{
		//	CCString *pStrBuffer = CCString::createWithFormat("DeadBomb_%05d.png", i);
		//	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrBuffer->getCString() );
		//	if ( NULL == pFrame)
		//		break;
		//	pArray->addObject( pFrame );
		//}
		//CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames( pArray, 0.1 );
		//CCActionInterval *pAnimate = CCAnimate::create( pAnimation );
		//CCSpriteFrame *pDeadBombFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "DeadBomb_00000.png" );
		//CCSprite *pDeadSprite = CCSprite::createWithSpriteFrame( pDeadBombFrame );
		//CCArray *pFishActionArray = CCArray::create();
		//pFishActionArray->addObject( pAnimate );
		//pFishActionArray->addObject( CCCallFuncN::create( this, callfuncN_selector( CFish::SpriteRemoveCallBack) ));
		//pDeadSprite->setPosition( bombPT );
		//pDeadSprite->runAction( CCSequence::create( pFishActionArray ) );
		//CFishMgr::GetInstance()->s_DeadBomb->addChild( pDeadSprite );
	}
}

// -------------------------------------------------
CFishMgr::CFishMgr()
{
	s_AllSeaGrass = 0;
	s_AllShell = 0;
	memset(s_AllStarFish,0,sizeof(s_AllStarFish));
	memset(s_AllFish, 0, sizeof(s_AllFish));
	memset(s_AllBomb, 0, sizeof(s_AllBomb));
	//s_DeadBomb = NULL;
	__pNode = NULL;
	//mutex = new SIX_Mutex();
	m_LoadHBoxProgress = -1;
	m_WaitForHBoxThread = false;
	m_NeedExitCheckThread = false;
	m_WaitForCheckThread = false;
	//mCheckThread = new SIX_Thread();
	//if (mCheckThread)
	//{
	//	int retv = mCheckThread->BeginThread(this,tc_thread_func(CFishMgr::CheckThreading),PTHREAD_CREATE_JOINABLE);
	//	if (retv!=0)
	//		m_WaitForCheckThread = false;
	//}
	m_FishPool = new SIX_TList<CFish*>;
	m_poolStep = 100;
}

CFishMgr::~CFishMgr()
{
	Release();
}

void CFishMgr::LoadSeaGrass()
{
	s_AllSeaGrass = CCSpriteBatchNode::create(CCString::create("Common/Effect/seagrass/seagrass.png")->getCString());
	__pNode->addChild(s_AllSeaGrass);
}

void CFishMgr::LoadShell()
{
	// ����Ҫ�����Ƹ���
	// Cool.Cat
	s_AllShell = CCSpriteBatchNode::create(CCString::create("Common/Effect/Shell/Shell.png")->getCString());
	__pNode->addChild(s_AllShell);
	//int zOrder = s_AllShell->getZOrder();
	//mScene->m_WaveSprite->_setZOrder(zOrder);
	//mScene->reorderChild(mScene->m_WaveSprite,zOrder);
}

void CFishMgr::LoadStarFish()
{
	for (int i=0;i<ARR_STARFISH_COUNT;i++)
	{
		s_AllStarFish[i] = CCSpriteBatchNode::create(CCString::createWithFormat("Common/Effect/StarFish/StarFish%02d.png",i+1)->getCString());
		__pNode->addChild(s_AllStarFish[i]);
	}
}

void CFishMgr::LoadBatchFish()
{
	for (int i=0;i<ARR_FISH_COUNT;i++)
	{
		int fishType=ARR_FISH[i];
		s_AllFish[i] = CCSpriteBatchNode::create( CCString::createWithFormat("Scene/Game/FishAndBomb/Fish_%02d.png",fishType)->getCString() );
		__pNode->addChild(s_AllFish[i]);
	}
}

void CFishMgr::LoadBatchBoom()
{
	for (int i=0;i<ARR_BOMB_COUNT;i++)
	{
		int BombType=ARR_BOMB[i];
		s_AllBomb[i] = CCSpriteBatchNode::create( CCString::createWithFormat("Scene/Game/FishAndBomb/Bomb_%02d.png",BombType)->getCString() );
		__pNode->addChild(s_AllBomb[i]);
	}

	////-- ����ը��
	//s_DeadBomb = CCSpriteBatchNode::create( CCString::create("Scene/Game/FishAndBomb/DeadBomb.png")->getCString() );
	//__pNode->addChild( s_DeadBomb );
}

int CFishMgr::LoadHitBoxCallBack(void *ptr)
{
	CFishMgr *pThis = static_cast<CFishMgr*>(ptr);
	SIX_Utility *pUtility = SIX_Utility::GetInstance();

	SIXLog("TID[0x%08X].LoadHitBoxCallBack.Begin",pUtility->GetCurrentThreadId());
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0001.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0002.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0003.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0004.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0005.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0006.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0007.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0008.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0009.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0010.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0012.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0015.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0018.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0020.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0025.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0030.pcc");
	pThis->m_LoadHBoxProgress++;
	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-0040.pcc");
	pThis->m_LoadHBoxProgress++;

	pUtility->LoadHitBoxFromFile("Scene/Game/FishAndBomb/CCSprite-bomb0034.pcc");
	pThis->m_LoadHBoxProgress++;

	for (int i=0;i<13;i++)
	{
		char fName[256] = {0};
#ifdef WIN32
		sprintf_s(fName,255,"Scene/Game/FishAndBomb/CCSprite-bomb%04d.pcc",i+1);
#else
		snprintf(fName,255,"Scene/Game/FishAndBomb/CCSprite-bomb%04d.pcc",i+1);
#endif
		pUtility->LoadHitBoxFromFile(fName);
		pThis->m_LoadHBoxProgress++;
	}
	SIXLog("TID[0x%08X].LoadHitBoxCallBack.Done",pUtility->GetCurrentThreadId());
	pThis->m_WaitForHBoxThread = false;
	return 0;
}

// ����HBox�����ļ��Ƚϴ����Ը�Ϊ�߳��첽���أ�����������
// Cool.Cat
void CFishMgr::LoadHitBox()
{
	SIXLog("LoadHitBox.A");
	SIX_Thread *pHBoxLoader = new SIX_Thread();
	if (!pHBoxLoader)
	{
		SIXLog("HBoxLoader.Init.Fault!");
		return;
	}

	m_LoadHBoxProgress = 0;
	m_WaitForHBoxThread = true;
	int retv = pHBoxLoader->BeginThread(this,tc_thread_func(CFishMgr::LoadHitBoxCallBack),PTHREAD_CREATE_JOINABLE);
	if (retv!=0)
		m_WaitForHBoxThread = false;
}

CCSpriteBatchNode *CFishMgr::sharedSeaGrass()
{
	return s_AllSeaGrass;
}

CCSpriteBatchNode *CFishMgr::sharedShell()
{
	return s_AllShell;
}

CCSpriteBatchNode **CFishMgr::sharedStarFish()
{
	return s_AllStarFish;
}

CCSpriteBatchNode **CFishMgr::sharedFish()
{
	return s_AllFish;
}

CCSpriteBatchNode **CFishMgr::sharedBomb()
{
	return s_AllBomb;
}
	
void CFishMgr::Init(SIX_SceneGame *pScene,CCNode *pNode,int poolStep)
{
	// -- save parent node
	mScene = pScene;
	__pNode = pNode;

	LoadSeaGrass();
	LoadStarFish();
	LoadShell();
	LoadBatchBoom();
	LoadBatchFish();

	// ��ʼ�������~
	m_poolStep = poolStep;
	FishPoolExpansion();
}

// �������
// Cool.Cat
void CFishMgr::FishPoolExpansion()
{
	if (!m_FishPool)
		return;

	if (m_poolStep<=0)
		m_poolStep = 100;

	unsigned int oldsize = m_FishPool->GetCount();
	for (int i=0;i<m_poolStep;i++)
	{
		CFish *pFish = CFish::spriteWithSpriteFrameName(CCString::createWithFormat(ARR_FRAME_FMT[1],1)->getCString());
		if (!pFish)
			continue;
		pFish->setVisible(false);

		FISH_DATA *pFishData = new FISH_DATA();
#ifdef USING_FISH_SHADOW
		pFishData->pShadow = CFish::spriteWithSpriteFrameName(CCString::createWithFormat(ARR_FRAME_FMT[1],1)->getCString());
		if (pFishData->pShadow)
			pFishData->pShadow->setVisible(false);
#endif
		pFishData->pFishMgr = this;
		pFishData->isCatch = false;
		pFishData->uld = 0;
		pFishData->FishMoveStatus = 0;
		pFishData->BuildTraceTime = 0;
		pFishData->Opacity = pFish->getOpacity();
		//SIX_Lock lock(g_FishMgr->mutex);
		//{
			pair<FISH_MAP::iterator,bool> status = mFishData.insert(FISH_MAP::value_type(pFish,pFishData));
			if (!status.second)
			{
				SIXLog("FishPoolExpansion[%u->%d][%u].Error!",oldsize,oldsize+m_poolStep,m_FishPool->GetCount());
				continue;
			}
		//}

		m_FishPool->Push(pFish);
	}
	SIXLog("FishPoolExpansion[%u->%d][%u].Done!",oldsize,oldsize+m_poolStep,m_FishPool->GetCount());
}

void CFishMgr::Release()
{
	m_NeedExitCheckThread = true;
	while (m_WaitForHBoxThread){}
	while (m_WaitForCheckThread){}

	if (s_AllSeaGrass)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::create("Common/Effect/seagrass/seagrass.plist")->getCString());
		s_AllSeaGrass->removeAllChildrenWithCleanup(true);
		s_AllSeaGrass->removeFromParentAndCleanup(true);
		s_AllSeaGrass = 0;
	}

	if (s_AllShell)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::create("Common/Effect/Shell/Shell.plist")->getCString());
		s_AllShell->removeAllChildrenWithCleanup(true);
		s_AllShell->removeFromParentAndCleanup(true);
		s_AllShell = 0;
	}

	for (int i=0;i<ARR_STARFISH_COUNT;i++)
	{
		if (s_AllStarFish[i])
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("Common/Effect/StarFish/StarFish%02d.plist",i+1)->getCString());
			s_AllStarFish[i]->removeAllChildrenWithCleanup(true);
			s_AllStarFish[i]->removeFromParentAndCleanup(true);
			s_AllStarFish[i] = 0;
		}
	}

	// ���ص���Ҫȫ�����
	// Cool.Cat
	int count = 0;
	for (int i=0;i<ARR_FISH_COUNT;i++)
	{
		int fishType=ARR_FISH[i];
		if (s_AllFish[i])
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("Scene/Game/FishAndBomb/Fish_%02d.plist",fishType)->getCString());
			count += s_AllFish[i]->getChildrenCount();
			//s_AllFish[i]->removeAllChildrenWithCleanup( true ) ;
			for (unsigned int j=0;j<s_AllFish[i]->getChildrenCount();j++)
			{
				CFish *pFish = dynamic_cast<CFish*>(s_AllFish[i]->getChildren()->objectAtIndex(j));
				if (!pFish)
					continue;
				pFish->SpriteRemoveCallBack(pFish);
			}
			s_AllFish[i]->removeFromParentAndCleanup(true);
			s_AllFish[i] = 0;
		}
	}

	for (int i=0;i<ARR_BOMB_COUNT;i++)
	{
		int BombType=ARR_BOMB[i];
		if (s_AllBomb[i])
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("Scene/Game/FishAndBomb/Bomb_%02d.plist",BombType)->getCString());
			count += s_AllBomb[i]->getChildrenCount();
			//s_AllBomb[i]->removeAllChildrenWithCleanup( true );
			for (unsigned int j=0;j<s_AllBomb[i]->getChildrenCount();j++)
			{
				CFish *pFish = dynamic_cast<CFish*>(s_AllBomb[i]->getChildren()->objectAtIndex(j));
				if (!pFish)
					continue;
				pFish->SpriteRemoveCallBack(pFish);
			}
			s_AllBomb[i]->removeFromParentAndCleanup(true);
			s_AllBomb[i] = 0;
		}
	}

	//if (NULL != s_DeadBomb)
	//	s_DeadBomb->removeAllChildrenWithCleanup( true );

	if (m_FishPool)
	{
		SIXLog("Release.Begin.m_FishPool.count[%d].count[%d]",m_FishPool->GetCount(),count);

		// ���ͷų���������
		while (m_FishPool->GetCount()>0)
		{
			CFish *pFish = m_FishPool->Pop();
			if (!pFish)
				continue;

			FISH_MAP::iterator it = CFishMgr::GetInstance()->mFishData.find( pFish );
			if ( CFishMgr::GetInstance()->mFishData.end() != it)
			{
				FISH_DATA *pFishData = (FISH_DATA *)it->second;
				CFishMgr::GetInstance()->mFishData.erase( it );
#ifdef USING_FISH_SHADOW
				CC_SAFE_RELEASE(pFishData->pShadow);
#endif
				CC_SAFE_DELETE( pFishData );
			}

			pFish->removeAllChildrenWithCleanup(true);
			pFish->removeFromParentAndCleanup(true);
			pFish->release();
		}

		SIXLog("Release.End.m_FishPool.count[%d]",m_FishPool->GetCount());

		CC_SAFE_DELETE(m_FishPool);
	}

	//CC_SAFE_DELETE(mutex);
}

//--[[
//���һ�����һ��ը��
//����˵����
//fishType----fishType/100=0ʱ��ʾ�㣬fishType%100��ʾ�����㣻fishType/100=1ʱ��ʾը����fishType%100��ʾ����ը����
//]]
void CFishMgr::addOneFish(TFishID uld,TFishKind fishType,TFishPathType pathType,float duration,TFishMoveStatus FishMoveStatus,float InitElapsed,TBuildTraceTime BuildTraceTime,CCPoint startP,CCPoint arg1,CCPoint arg2,CCPoint arg3)
{
	if (fishType<=0 || fishType>=200)
	{
		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("A.addOneFish.uld[%u].fishType[%d].pathType[%d].duration[%.4f]",uld,fishType,pathType,duration);
		return;
	}

	// --ȡ�̡�ȡģ
	int q = fishType/100;
	int r = fishType%100;

	// ���r�Ƿ���Ч����
	// Cool.Cat
	int validIdx = 0;
	if (0 <= 2*q && 1 >= 2*q)
		validIdx = GetIndexFromArray(r,true);
	else
		validIdx = GetIndexFromArray(r,false);
	if (validIdx==-1)
	{
		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("B.addOneFish.uld[%u].fishType[%d].pathType[%d].duration[%.4f].q[%d].r[%d]",uld,fishType,pathType,duration,q,r);
		return;
	}

	// ����ʽ����
	// Cool.Cat
	if (!m_FishPool)
	{
		SIXLog("��ز����ڣ�");
		return;
	}

	if (!m_FishPool->GetCount())
	{
		SIXLog("����û��������ʼ���� ...");
		FishPoolExpansion();
	}

	CCArray *pArray = CCArray::create();
	for (int i=0;i<64;i++)
	{
		CCString *fName = CCString::createWithFormat(ARR_FRAME_FMT[2*q],r,i);
		CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( fName->getCString() );

		if (!pSpriteFrame)
			break;
		pArray->addObject( pSpriteFrame );
		pSpriteFrame->setObjName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
	}

	// -- ��֡��������action��֡�ӳ�0.1f
	CCAnimation *pAnimation =CCAnimation::createWithSpriteFrames(pArray,0.1f);
	CC_SAFE_DELETE(pArray);
	pAnimation->setObjName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
	CCRepeatForever *fish_act = CCRepeatForever::create(CCAnimate::create(pAnimation));
	fish_act->setObjName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
	CFish *pFish = m_FishPool->Pop();
	if (!pFish)
	{
		SIXLog("�޿��ܽ�������Ŀ�~");
		return;
	}

	// ������������
	// Cool.Cat
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
	pFrame->setObjName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
	CCTexture2D *pTex = pFrame->getTexture();
	pTex->setObjName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
	pFish->setBatchNode(0);
	pFish->setTexture(pTex);
	pFish->setVisible(true);
	pFish->setOpacity(255);
	pFish->setScale(1.0f);
	pFish->setTag(fishType);
	pFish->setPosition(startP);
	pFish->setArg(qrArg(fishType));
	pFish->runAction(fish_act);
	pFish->addPath(pathType,duration,InitElapsed,arg1,arg2,arg3,uld);
	pFish->setObjName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());

	FISH_DATA *pFishData = 0;

	FISH_MAP::iterator it = CFishMgr::GetInstance()->mFishData.find( pFish );
	if ( CFishMgr::GetInstance()->mFishData.end() != it)
	{
		pFishData = (FISH_DATA *)it->second;
#ifdef USING_FISH_SHADOW
		CCSpriteFrame *pShadowFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(ARR_FRAME_FMT[2*q+1],r)->getCString());
		CCTexture2D *pShadowTex = pShadowFrame->getTexture();
		memset(&pFishData->pShadow->getQuad(), 0, sizeof(pFishData->pShadow->getQuad()));
		pFishData->pShadow->setBatchNode(0);
		pFishData->pShadow->setTexture(pShadowTex);
		pFishData->pShadow->setVisible(true);
		pFishData->pShadow->setColor(ccc3(0,0,0));
		pFishData->pShadow->setOpacity(128);
		pFishData->pShadow->setScale(FISH_SHADOW_RATIO);
		pFishData->pShadow->setTag(fishType);
		pFishData->pShadow->setArg(qrArg(fishType));
		// self action
		CCRepeatForever *shadow_act = (CCRepeatForever*)fish_act->copy()->autorelease();
		pFishData->pShadow->runAction(shadow_act);

		// ��Ӱƫ�ƴ���
		// Cool.Cat
		float center_offset = MAX_WIDTH/2;
		// ��߳��֣���Ӱλ�����·�
		if (startP.x<center_offset)
		{
			startP.x -= FISH_SHADOW_OFFSET;
			if (pathType==5)
				arg3.x -= FISH_SHADOW_OFFSET;
		}
		// �ұ߳��֣���Ӱλ�����·�
		else if (startP.x>center_offset)
		{
			startP.x += FISH_SHADOW_OFFSET;
			if (pathType==5)
				arg3.x += FISH_SHADOW_OFFSET;
		}

		startP.y -= FISH_SHADOW_OFFSET;

		if (pathType==5)
			arg3.y -= FISH_SHADOW_OFFSET;

		pFishData->pShadow->setPosition(startP);
		pFishData->pShadow->addPath(pathType,duration,InitElapsed,arg1,arg2,arg3,uld);
#endif
		pFishData->isCatch = false;
		pFishData->uld = uld;
		pFishData->fishKind = fishType;
		pFishData->FishMoveStatus = FishMoveStatus;
		pFishData->BuildTraceTime = BuildTraceTime;
		//��Ժ�����ӵ�����յ����ٵ���켣�����
		if(FishMoveStatus>0)
		{
			CCSpeed * pCCSpeed=(CCSpeed *)pFish->getActionByTag(uld);
			if(pCCSpeed!=NULL)
			{
				pCCSpeed->setSpeed(5.0f);
			}
		}
		pFishData->Opacity = pFish->getOpacity();
	}

	if (0 <= 2*q && 1 >= 2*q)
	{
#ifdef USING_FISH_SHADOW
			if (pFishData && pFishData->pShadow)
				s_AllFish[validIdx]->addChild(pFishData->pShadow);
#endif
		s_AllFish[validIdx]->addChild( pFish );
	}
	else
	{
#ifdef USING_FISH_SHADOW
			if (pFishData && pFishData->pShadow)
				s_AllBomb[validIdx]->addChild(pFishData->pShadow);
#endif
		s_AllBomb[validIdx]->addChild( pFish );
	}
}

int CFishMgr::GetIndexFromArray(int idx,bool IsFish)
{
	if (IsFish)
	{
		for (int i=0;i<ARR_FISH_COUNT;i++)
		{
			if (idx==ARR_FISH[i])
				return i;
		}
	}
	else
	{
		for (int i=0;i<ARR_BOMB_COUNT;i++)
		{
			if (idx==ARR_BOMB[i])
				return i;
		}	
	}
	return -1;
}

CFish *CFishMgr::GetFishFromMap(TFishID fishId,FISH_DATA **pFishDataDst)
{
	FISH_MAP::iterator mIter;
	//SIX_Lock lock(g_FishMgr->mutex);
	//{
		for (mIter=mFishData.begin(); mIter!=mFishData.end(); mIter++)
		{
			CFish *pFish = mIter->first;
			FISH_DATA *pFishData = mIter->second;
			if (!pFish || !pFishData || !pFishData->uld)
				continue;
			if (pFishData->uld==fishId)
			{
				*pFishDataDst = pFishData;
				return pFish;
			}
		}
	//}
	return 0;
}

void CFishMgr::CaptureFish(long long llUserID, long long llBulletID,const vector<TFishID> &vHitFishID,vector<TFishID> &vDeadFishID,TFallIntegral FallIntegral,TGunGrade GunGrade,TFishID DeadFullScreenBombFishID)
{
	CShip *pShip = g_pShipMgr->getShip( llUserID );
	if ( NULL == pShip )
		return;

	vector<TFishID> vFishID=vHitFishID;
	bool HasAddOneGoldDisc=false;

	// �ӵ�ײ�����Ķ���
	CCArray *allBullet = g_pBulletMgr->sharedBullet()->getChildren();
	CBulletAndNet *pBullet = NULL;
	bool IsMySelfBullet = false;
	if (llUserID==g_pShipMgr->getMySelfShip()->m_UserID)
		IsMySelfBullet = true;
	for (int index=0;index<(int)(allBullet->count());)
	{
		pBullet = dynamic_cast<CBulletAndNet*>( allBullet->objectAtIndex( index++ ) );
		if (NULL == pBullet  ||  llBulletID != pBullet->Data.BulletId || pBullet->Data.RemoveStatus!=0)
			continue;

		if (!pBullet->Data.IsCatching)
		{
			//SIXLog("BULLET---- capture fish %lld", pBullet->Data.BulletId);
			pBullet->Data.IsCatching = true;
			if (!IsMySelfBullet)
			{
				pBullet->FinishAnimation( pBullet );
				pBullet->setUserData((void*)1);
			}

			// �����������㣨���͸���ȣ�
			vector<TFishID>::iterator vIt = vFishID.begin();
			for (;vIt != vFishID.end();)
			{
				TFishID fishId = *vIt;
				FISH_DATA *pFishData = 0;
				CFish *pFish = this->GetFishFromMap(fishId,&pFishData);
				if (pFish && pFishData && pFishData->uld)
				{
					if ( pFishData->Opacity == pFish->getOpacity() )
					{
						pFishData->Opacity = pFish->getOpacity();
						pFish->setOpacity( 120 );
						CCDelayTime *pDelayTime = CCDelayTime::create(0.5);
						CCCallFuncN *pFishCallFun = CCCallFuncN::create(pFish, callfuncN_selector(CFishMgr::RestoreFish) );
						CCFiniteTimeAction *pSequence = CCSequence::create(pDelayTime, pFishCallFun, NULL);
						pFish->runAction( pSequence );
					}
				}
				else
				{
					//if (!pFish)
					//	SIXLog("vFishID[%u].pFish.nil",fishId);
					//if (!pFishData)
					//	SIXLog("vFishID[%u].pFishData.pFish.nil",fishId);
					//if (pFishData && !pFishData->uld)
					//	SIXLog("vFishID[%u].pFishData->uld.pFish.nil",fishId);
				}
				vIt = vFishID.erase(vIt);
			}

			// ը��������ת�̵�������Ҵ���λ�ø�����ʾ
			// Cool.Cat
			CCPoint PlayerPT = pShip->getGunPos();
			int nDirection = g_pShipMgr->getPlayerDirection( llUserID );
			PlayerPT.y = (0 == nDirection) ? MAX_HEIGHT-200 : 0+200;

			// �ȴ���ȫ��ը��
			// Cool.Cat
			// ������������������ȫ��ը��
			if(DeadFullScreenBombFishID>0)
			{
				FISH_DATA *pFishData = 0;
				CFish *pFish = this->GetFishFromMap(DeadFullScreenBombFishID,&pFishData);
				if (pFish && pFishData && pFishData->uld)
				{
						// let's do something~
						pFishData->isCatch = true;
						pFish->DieAnimation(pFishData);

						// ����������Ҷ���
						if (NULL != pShip  &&  NULL != g_pGold)
						{
							if(!HasAddOneGoldDisc && FallIntegral>0)
							{
								vector<TFishID>::const_iterator p=std::find(vHitFishID.begin(),vHitFishID.end(),pFishData->uld);
								if(p!=vHitFishID.end())
								{
									g_pGold->AddOneGoldDisc(FallIntegral, PlayerPT, pShip->m_UserID);
									HasAddOneGoldDisc=true;
								}
							}
						}

						// ��+����Ч��
						// Cool.Cat
						CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
						if (pScene && !STRCMP(pScene->getChildren()->objectAtIndex(0)->getObjName(),"SIX_SceneGame"))
						{
							CCActionInterval *pAction = CCLiquid::create(10,20,ccg(16,12),0.3f);
							pScene->runAction(pAction);

							// ���ӱ�ըЧ��
							CCParticleSystemQuad* part = CCParticleSystemQuad::create("Scene/Game/Particle/Bomb.plist");
							if(!part)
								return;

							part->setPosition(pFish->getPosition());
							part->setBlendAdditive(true);
							part->setAutoRemoveOnFinish(true);
							pScene->addChild(part);
						}
					}
			}

			// �㲶���Ķ��� (����ͬʱ���������)
			vector<TFishID>::iterator vItDead = vDeadFishID.begin();
			for (;vItDead != vDeadFishID.end();)
			{
				TFishID fishId = *vItDead;
				FISH_DATA *pFishData = 0;
				if(fishId==DeadFullScreenBombFishID)
				{
				   vItDead = vDeadFishID.erase(vItDead);
				   continue;
				}
				CFish *pFish = this->GetFishFromMap(fishId,&pFishData);
				if (pFish && pFishData && pFishData->uld)
				{
					pFishData->isCatch = true;
					pFish->DieAnimation(pFishData);
					// ����������Ҷ���
					if (NULL != pShip  &&  NULL != g_pGold)
					{
						if(pFishData->fishKind<12)
							g_pGold->showGold(GunGrade*PlayerTreasureInfo::getFishMulti(pFishData->fishKind),pFish->getPosition(), pShip->m_UserID);
						else
						{
							if(!HasAddOneGoldDisc && FallIntegral>0)
							{
								vector<TFishID>::const_iterator p=std::find(vHitFishID.begin(),vHitFishID.end(),pFishData->uld);
								if(p!=vHitFishID.end())
								{
									g_pGold->AddOneGoldDisc(FallIntegral, PlayerPT, pShip->m_UserID);
									HasAddOneGoldDisc=true;
								}
							}
							// ���û�г���ȫ��ը��
							if (DeadFullScreenBombFishID==0)
							{
								// ��Ч��
								// Cool.Cat
								CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
								if (pScene && !STRCMP(pScene->getChildren()->objectAtIndex(0)->getObjName(),"SIX_SceneGame"))
								{
									CCActionInterval *pAction = CCLiquid::create(10,20,ccg(16,12),0.3f);
									pScene->runAction(pAction);

									// ���ӱ�ըЧ��
									CCParticleSystemQuad* part = CCParticleSystemQuad::create("Scene/Game/Particle/Bomb.plist");
									if(!part)
										return;

									part->setPosition(pFish->getPosition());
									part->setBlendAdditive(true);
									part->setAutoRemoveOnFinish(true);
									pScene->addChild(part);
								}
							}
						}
					}
				}
				else
				{
					//if (!pFish)
					//	SIXLog("vDeadFishID[%u].pFish.nil",fishId);
					//if (!pFishData)
					//	SIXLog("vDeadFishID[%u].pFishData.pFish.nil",fishId);
					//if (pFishData && !pFishData->uld)
					//	SIXLog("vDeadFishID[%u].pFishData->uld.pFish.nil",fishId);
				}
				vItDead = vDeadFishID.erase(vItDead);
			}
			break;
		}
	}
}

void CFishMgr::RestoreFish(CCNode *node)
{
	CFish *pFish = (CFish *)node;
	if (NULL != pFish)
	{
		//SIX_Lock lock(g_FishMgr->mutex);
		//{
			FISH_MAP::iterator mIter = g_FishMgr->mFishData.find( pFish );
			if (g_FishMgr->mFishData.end() != mIter)
			{
				pFish->setOpacity( mIter->second->Opacity );
			}
		//}
	}
}

int CFishMgr::CheckThreading(void *ptr)
{
	CFishMgr *pThis = static_cast<CFishMgr*>(ptr);
	if (!pThis || !pThis->mScene)
		return 0;

	//while (!pThis->m_NeedExitCheckThread)
	//{
	//	pThis->mScene->FishAndBulletCollide();
	//	Sleep(1);
	//}

	pThis->m_WaitForCheckThread = false;
	return 0;
}

//��켣���٣�add by Ivan_han 20130621
void CFishMgr::SpeedUpOneFish(TFishID uld)
{
	//if(uld==0)
	//	return;

	FISH_MAP::iterator mIter;
	//SIX_Lock lock(g_FishMgr->mutex);
	//{
		for (mIter=mFishData.begin(); mIter!=mFishData.end(); mIter++)
		{
			CFish *pFish = mIter->first;
			FISH_DATA *pFishData = mIter->second;
			if (pFish!=NULL && pFishData!=NULL && pFishData->uld==uld)
			{
				CCSpeed * pCCSpeed=(CCSpeed *)pFish->getActionByTag(uld);
				if(pCCSpeed!=NULL)
				{
					pCCSpeed->setSpeed(5.0f);
					return;
				}
			}
		}
	//}
}

void CFishMgr::SpeedUpAllFish()
{
	FISH_MAP::iterator mIter;
	//SIX_Lock lock(g_FishMgr->mutex);
	//{
		for (mIter=mFishData.begin(); mIter!=mFishData.end(); mIter++)
		{
			CFish *pFish = mIter->first;
			FISH_DATA *pFishData = mIter->second;
			if (pFish!=NULL && pFishData!=NULL && pFishData->uld>0)
			{
				CCSpeed * pCCSpeed=(CCSpeed *)pFish->getActionByTag(pFishData->uld);
				if(pCCSpeed!=NULL)
				{
					pCCSpeed->setSpeed(5.0f);
				}
			}
		}
	//}
	return;
}

//���ڻָ�ʱͬ�������λ��
void CFishMgr::CheckAllFish()
{
	FISH_MAP::iterator mIter;
	//TBuildTraceTime ClientCheckTime=CEasyDataTime::get_current_time_diff_millitm_from_1970();
	TBuildTraceTime ClientCheckTime = SIX_Utility::GetInstance()->GetTickCount();
	//SIX_Lock lock(g_FishMgr->mutex);
	//{
		for (mIter=mFishData.begin(); mIter!=mFishData.end(); mIter++)
		{
			CFish *pFish = mIter->first;
			FISH_DATA *pFishData = mIter->second;
			if (pFish!=NULL && pFishData!=NULL && pFishData->uld>0)
			{
				CCSpeed * pCCSpeed=(CCSpeed *)pFish->getActionByTag(pFishData->uld);
				if(pCCSpeed!=NULL)
				{
					CCSequence* p=(CCSequence *)pCCSpeed->getInnerAction();
					if(p!=NULL)
					{
						//TBuildTraceTime ClientCheckTime=SIX_Proxy::GetTickCount64();
						long long llElapsed=ClientCheckTime-pFishData->BuildTraceTime+SIX_ClientRoom::GetInstance()->GetClientServerTimeInterval();
						float Elapsed =llElapsed * 0.001;
						p->setElapsed(Elapsed);
						//add by Ivan_han 20130715
						if(Elapsed>=p->getDuration())
						{
							pFish->setVisible(false);
#ifdef USING_FISH_SHADOW
							pFishData->pShadow->setVisible(false);
#endif
						}
					}
				}
			}
		}
	//}
	return;
}
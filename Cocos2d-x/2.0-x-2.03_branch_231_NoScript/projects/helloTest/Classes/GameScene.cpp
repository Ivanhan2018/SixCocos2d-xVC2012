///////////////////////////////////////////////
//������by:����   QQ:414755548
//���Ǹս���˾�Ĳ���,������кõ�˼·,��ӭΪС���ṩһЩ����ͽ���,лл!!
///////////////////////////////////////////////
#include "GameScene.h"
#include "Poker.h"
#include "Player.h"
#include "Tool.h"
#include "vector"
#include<algorithm>
#include <string>
#include <deque>
GameScene::GameScene():m_isSend(true),m_iSendPk(0),m_iState(0),
					   m_iCall(0),m_iCallTime(0),m_iOutCard(0),
					   m_type(ERROR_CARD),m_isChiBang(true){
	m_player = new Player();
	m_npcOne = new Player();
	m_npcTwo = new Player();
	m_Three = new Player();
	m_playerOut = new Player();
	m_npcOneOut = new Player();
	m_npcTwoOut = new Player();
	m_arrPlayerOut = CCArray::create();
	m_arrPlayerOut->retain();
	m_arrGenPk = CCArray::create();
	m_arrGenPk->retain();
	m_arrPokers = CCArray::create();
	m_arrPokers->retain();
	for(int i=0; i<3; ++i)
		m_bCall[i] = false;
	playerDiZhuLablePt = CCPointMake(100,100);
	npcOneDiZhuLablePt = CCPointMake(65+100,504);
	npcTwoDiZhuLablePt = CCPointMake(735-100,504);
}
GameScene::~GameScene(){
	CC_SAFE_DELETE(m_player);
	CC_SAFE_DELETE(m_npcOne);
	CC_SAFE_DELETE(m_npcTwo);
	CC_SAFE_DELETE(m_Three);
	CC_SAFE_DELETE(m_playerOut);
	CC_SAFE_DELETE(m_npcOneOut);
	CC_SAFE_DELETE(m_npcTwoOut);
	CC_SAFE_RELEASE(m_arrPokers);
	CC_SAFE_RELEASE(m_arrPlayerOut);
	CC_SAFE_RELEASE(m_arrGenPk);
}
CCScene* GameScene::scene(){
	CCScene* scene = CCScene::create();
	GameScene * gameLayer = GameScene::create();
	scene->addChild(gameLayer);
	return scene;
}
bool GameScene::init(){
	CCLayer::init();
	bool isRet = false;
	do 
	{
		srand((unsigned)time(NULL));//��ʼ���������
		CC_BREAK_IF(!initBackGround());
		CC_BREAK_IF(!createPokers());
		CC_BREAK_IF(!initPlayer());
		CC_BREAK_IF(!xiPai());
		CC_BREAK_IF(!initAnNiu());
		CC_BREAK_IF(!InitNpcBuChuLable());
		//������ǩ
		m_lableDiZhu = CCLabelTTF::create(a2u("����").c_str(),"Helvetica-BoldOblique",20);
		m_lableDiZhu->setPosition(ccp(100,100));
		this->addChild(m_lableDiZhu,1);
		m_lableDiZhu->setVisible(false);
		scheduleUpdate();

		isRet = true;
	} while (0);
	return isRet;
}
void GameScene::onEnter(){
	CCLayer::onEnter();
	
}
void GameScene::onExit(){
	CCLayer::onExit();
}
bool GameScene::initBackGround(){
	bool isRet = false;
	do 
	{	
		CCSprite* bk = CCSprite::create("bk.png");
		this->addChild(bk,0);
		bk->setAnchorPoint(ccp(0,0));
		isRet = true;
	} while (0);
	return isRet;
}
Poker* GameScene::selectPoker(int huaSe,int num){
	Poker* pk;
	if(huaSe != Gui)
		pk = Poker::create("poker.png",CCRect(num*pkWidth,huaSe*pkHeight,pkWidth,pkHeight));
	else
		pk = Poker::create("poker.png",CCRect((num-XiaoGui)*pkWidth,huaSe*pkHeight,pkWidth,pkHeight));
	pk->setHuaSe(huaSe);
	pk->setNum(num);
	pk->setGameMain(this);
	return pk;
}
bool GameScene::createPokers(){
	bool isRet = false;
	do 
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		Poker* pk;
		//����52����
		for (int i=0; i<4; ++i)
		{
			for (int j=0; j<13; ++j)
			{
				pk = selectPoker(i,j);
				pk->setPosition(ccp(size.width/2/*+j*20*/,size.height/2/*-i*20*/));
				pk->showLast();
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}
		}
		//����С��
		pk = selectPoker(Gui,XiaoGui);
		pk->setPosition(ccp(size.width/2,size.height/2/*-4*20*/));
		pk->showLast();
		this->addChild(pk);
		this->m_arrPokers->addObject(pk);
		//�������
		pk = selectPoker(Gui,DaGui);
		pk->setPosition(ccp(size.width/2/*+20*/,size.height/2/*-4*20*/));
		pk->showLast();
		this->addChild(pk);
		this->m_arrPokers->addObject(pk);
		isRet = true;
	} while (0);
	return isRet;
}
bool GameScene::xiPai(){
	bool isRet = false;
	do 
	{
		for(int i=0; i<54; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPokers->randomObject();
			Poker* pk2 = (Poker*)m_arrPokers->randomObject();
			m_arrPokers->exchangeObject(pk1,pk2);
		}
		isRet = true;
	} while (0);
	return isRet;
}
bool GameScene::initPlayer(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//��������ҵ�λ��
	m_player->setPoint(ccp(size.width/2,size.height/6));
	m_player->setPlayerClass(0);
	//���õ���1��λ��
	m_npcOne->setPoint(ccp(65,504));
	m_npcOne->setPlayerClass(1);
	//���õ���2��λ��
	m_npcTwo->setPoint(ccp(735,504));
	m_npcTwo->setPlayerClass(1);
	//���������Ƶ�λ��
	m_Three->setPoint(ccp(size.width/2,504));
	m_Three->setPlayerClass(2);
	//��������ҳ��Ƶ�λ��
	m_playerOut->setPoint(ccp(size.width/2,size.height/6+106));
	m_playerOut->setPlayerClass(3);
	//���õ���1��ҳ���λ��
	m_npcOneOut->setPoint(ccp(146,size.height/2+20));
	m_npcOneOut->setPlayerClass(4);
	//���õ���2��ҳ���λ��
	m_npcTwoOut->setPoint(ccp(654,size.height/2+20));
	m_npcTwoOut->setPlayerClass(5);
	return true;
}
void GameScene::SendPk(){
	Poker* pk;
	if(m_iSendPk<51 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		if(m_iSendPk%3 == 0)//����ҷ���
			MovePk(m_player,pk);
		else if(m_iSendPk%3 == 1)//������1����
			MovePk(m_npcOne,pk);
		else if(m_iSendPk%3 == 2)//������2����
			MovePk(m_npcTwo,pk);
		++m_iSendPk;
		m_isSend = false;
	}else if (m_iSendPk>50 && m_iSendPk<54 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		pk->showFront();
		MovePk(m_Three,pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if(m_iSendPk>53)
	{
		FenChaiNpcPai(m_npcOne);
		FenChaiNpcPai(m_npcTwo);
		m_iSendPk = 0;
		m_iState = 1;
	}
}
void GameScene::func(CCNode* pSender, void* pData){
	Player* play = (Player*)pData;
	play->updatePkWeiZhi();
	m_isSend = true;
}
void GameScene::MovePk(Player* play,Poker* pk)
{
	CCMoveTo* move;
	CCCallFuncND* func;
	float time = 0.05;
	play->getArrPk()->addObject(pk);
	move = CCMoveTo::create(time,play->getPoint());
	func = CCCallFuncND::create(this,callfuncND_selector(GameScene::func),play);
	CCSequence* sequence = (CCSequence*)CCSequence::create((CCFiniteTimeAction*)move,(CCFiniteTimeAction*)func,NULL);//by hxh
	pk->runAction(sequence);
}
void GameScene::update(float delta){
	switch (m_iState)
	{
	case 0:
		SendPk();
		break;
	case 1:
		schedule(schedule_selector(GameScene::Call),1);
		break;
	case 2:
		scheduleOnce(schedule_selector(GameScene::OutCard),0.5);
		break;
	case 3:
		IsShengLi();
		break;
	default:
		break;
	}
}
void GameScene::Call(float dt){
	//�Ƿ񶼽й�����
	if(!m_player->getCall() || !m_npcOne->getCall() || !m_npcTwo->getCall())
	{
		m_iCallTime%=3;
		switch (m_iCallTime)
		{
		case 0://���ѡ���������
			m_menu->setVisible(true);
			if (m_bCall[0])
			{
				CCMenuItemFont* itemFont = (CCMenuItemFont*)m_menu->getChildByTag(1);
				itemFont->setEnabled(false);
			}
			else
			{
				CCMenuItemFont* itemFont = (CCMenuItemFont*)m_menu->getChildByTag(1);
				itemFont->setEnabled(true);
			}
			if (m_bCall[1])
			{
				CCMenuItemFont* itemFont = (CCMenuItemFont*)m_menu->getChildByTag(2);
				itemFont->setEnabled(false);
			}
			else
			{
				CCMenuItemFont* itemFont = (CCMenuItemFont*)m_menu->getChildByTag(2);
				itemFont->setEnabled(true);
			}
			if (m_bCall[2])
			{
				CCMenuItemFont* itemFont = (CCMenuItemFont*)m_menu->getChildByTag(3);
				itemFont->setEnabled(false);
			}
			else
			{
				CCMenuItemFont* itemFont = (CCMenuItemFont*)m_menu->getChildByTag(3);
				itemFont->setEnabled(true);
			}
			break;
		case 1://����1ѡ���������
			++m_iCallTime;
			NpcCall(m_npcTwo,m_npcOne);
			ShowFenShu(ccp(m_npcTwo->getPoint().x-88,m_npcTwo->getPoint().y),m_npcTwo->getCallNum());
			break;
		case 2://����2ѡ���������
			++m_iCallTime;
			NpcCall(m_npcOne,m_npcTwo);
			ShowFenShu(ccp(m_npcOne->getPoint().x+88,m_npcOne->getPoint().y),m_npcOne->getCallNum());
			break;
		}
	}
	else//�ж�˭�ǵ������������Ƹ���
	{
		//�����û�е������ѵ�����һ��ʼѡ�����Ǹ�
		if(m_player->getCallNum() == 0 && m_npcOne->getCallNum() == 0 && m_npcTwo->getCallNum() == 0)
		{
			switch (m_iCall%3)
			{
			case 0:
				m_player->setCallNum(3);
				break;
			case 1:
				m_npcTwo->setCallNum(3);
				break;
			case 2:
				m_npcOne->setCallNum(3);
				break;
			default:
				break;
			}
		}
		//˭��ֵ��˭������
		CCObject* object;
		if(m_player->getCallNum() > m_npcOne->getCallNum() && m_player->getCallNum() > m_npcTwo->getCallNum()){
			CCArray* arrTem = CCArray::create();
			CCARRAY_FOREACH(m_Three->getArrPk(),object){
				Poker* pk = (Poker *)object;
				Poker* pkCopy = pk->copy();
				arrTem->addObject(pkCopy);
				addChild(pkCopy);
				m_player->getArrPk()->addObject(pk);
				m_player->setIsDiZhu(true);
				m_npcOne->setIsDiZhu(false);
				m_npcTwo->setIsDiZhu(false);
				m_iOutCard = 0;
			}
			m_Three->getArrPk()->removeAllObjects();
			m_Three->getArrPk()->addObjectsFromArray(arrTem);
			m_Three->updatePkWeiZhi();
			m_player->updatePkWeiZhi();
			//��ʾ������ǩ
			m_lableDiZhu->setPosition(playerDiZhuLablePt);
			m_lableDiZhu->setVisible(true);
		}
		if(m_npcOne->getCallNum() > m_player->getCallNum() && m_npcOne->getCallNum() > m_npcTwo->getCallNum()){
			
			CCArray* arrTem = CCArray::create();
			CCARRAY_FOREACH(m_Three->getArrPk(),object){
				Poker* pk = (Poker *)object;
				Poker* pkCopy = pk->copy();
				arrTem->addObject(pkCopy);
				addChild(pkCopy);
				m_npcOne->getArrPk()->addObject(pk);
				m_player->setIsDiZhu(false);
				m_npcOne->setIsDiZhu(true);
				m_npcTwo->setIsDiZhu(false);
				m_iOutCard = 2;
			}
			m_Three->getArrPk()->removeAllObjects();
			m_Three->getArrPk()->addObjectsFromArray(arrTem);
			m_Three->updatePkWeiZhi();
			//���·ֲ���
			m_npcOne->m_vecPX.clear();
			m_npcOne->updatePkWeiZhi();
			FenChaiNpcPai(m_npcOne);
			//��ʾ������ǩ
			m_lableDiZhu->setPosition(npcOneDiZhuLablePt);
			m_lableDiZhu->setVisible(true);
		}
		if(m_npcTwo->getCallNum() > m_npcOne->getCallNum() && m_npcTwo->getCallNum() > m_player->getCallNum()){
			CCArray* arrTem = CCArray::create();
			CCARRAY_FOREACH(m_Three->getArrPk(),object){
				Poker* pk = (Poker *)object;
				Poker* pkCopy = pk->copy();
				arrTem->addObject(pkCopy);
				addChild(pkCopy);
				m_npcTwo->getArrPk()->addObject(pk);
				m_player->setIsDiZhu(false);
				m_npcOne->setIsDiZhu(false);
				m_npcTwo->setIsDiZhu(true);
				m_iOutCard = 1;
			}
			m_Three->getArrPk()->removeAllObjects();
			m_Three->getArrPk()->addObjectsFromArray(arrTem);
			m_Three->updatePkWeiZhi();
			//���·ֲ���
			m_npcTwo->m_vecPX.clear();
			m_npcTwo->updatePkWeiZhi();
			FenChaiNpcPai(m_npcTwo);
			//��ʾ������ǩ
			m_lableDiZhu->setPosition(npcTwoDiZhuLablePt);
			m_lableDiZhu->setVisible(true);
		}
		m_iState = 2;
		++m_iCall;
		m_iCallTime = m_iCall;
		unschedule(schedule_selector(GameScene::Call));
		//ѡ����������ʾ������
		CCARRAY_FOREACH(m_Three->getArrPk(),object){
			Poker* pk = (Poker*)object;
			pk->showFront();
		}
		//�Ƴ��е�����������ʾ
		this->removeChildByTag(FenShu,true);//by hxh
		this->removeChildByTag(FenShu,true);//by hxh
		this->removeChildByTag(FenShu,true);//by hxh
		//ʹ����ҵ���Ϊ�ɵ��״̬
		CCARRAY_FOREACH(m_player->getArrPk(),object){
			Poker* pk = (Poker *)object;
			pk->setDianJi(true);
		}
	}
}

void GameScene::menuCallbackYi(CCObject* sender){
	m_player->setCallNum(1);
	m_player->setCall(true);
	m_bCall[0] = true;
	++m_iCallTime;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ShowFenShu(CCPoint(size.width/2,m_player->getPoint().y+88),1);
	//���ز˵�
	CCMenuItemFont* font = (CCMenuItemFont*) sender;
	font->getParent()->setVisible(false);
}
void GameScene::menuCallbackEr(CCObject* sender){
	m_player->setCallNum(2);
	m_player->setCall(true);
	m_bCall[1] = true;
	++m_iCallTime;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ShowFenShu(CCPoint(size.width/2,m_player->getPoint().y+88),2);
	CCMenuItemFont* font = (CCMenuItemFont*) sender;
	font->getParent()->setVisible(false);
}
void GameScene::menuCallbackSan(CCObject* sender)
{
	m_player->setCallNum(3);
	m_player->setCall(true);
	m_npcOne->setCall(true);
	m_npcTwo->setCall(true);
	m_bCall[2] = true;
	++m_iCallTime;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ShowFenShu(CCPoint(size.width/2,m_player->getPoint().y+88),3);
	CCMenuItemFont* font = (CCMenuItemFont*) sender;
	font->getParent()->setVisible(false);
}
void GameScene::menuCallbackBuJiao(CCObject* sender){
	m_player->setCallNum(0);
	m_player->setCall(true);
	++m_iCallTime;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ShowFenShu(CCPoint(size.width/2,m_player->getPoint().y+88),0);
	CCMenuItemFont* font = (CCMenuItemFont*) sender;
	font->getParent()->setVisible(false);
}
void GameScene::menuChuPai(CCObject* sender){
	//������һ�γ�����
	CCObject* object;
	CCARRAY_FOREACH(m_playerOut->getArrPk(),object){
		Poker* pk = (Poker*)object;
		pk->setVisible(false);
	}
	m_playerOut->getArrPk()->removeAllObjects();
	m_playerOut->getArrPk()->addObjectsFromArray(m_arrPlayerOut);
	m_arrGenPk->removeAllObjects();
	m_arrGenPk->addObjectsFromArray(m_arrPlayerOut);
	m_arrPlayerOut->removeAllObjects();
	m_playerOut->updatePkWeiZhi();
	m_player->setIsOutPk(true);
	CCARRAY_FOREACH(m_playerOut->getArrPk(),object){
		Poker* pk = (Poker *)object;
		pk->setDianJi(false);
		m_player->getArrPk()->removeObject(pk);
	}
	m_player->updatePkWeiZhi();
	m_type = m_typeTem;
	
	if(IsOutPkFinish())
		m_iState = 3;
	else
		++m_iOutCard;
	m_lastOut = m_player;
}
void GameScene::menuBuChu(CCObject* sender){
	++m_iOutCard;
	while(m_arrPlayerOut->count() > 0){
		Poker* pk = (Poker *)m_arrPlayerOut->objectAtIndex(0);
		if(pk->getSelect())
			pk->SelectPkSuoTou();
	}
	m_player->updatePkWeiZhi();
	m_player->setIsOutPk(false);
}
void GameScene::menuShengLi(CCObject* sender){
	ReStart();
}
void GameScene::menuShu(CCObject* sender){
	ReStart();
}
bool GameScene::initAnNiu(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//һ��
	CCMenuItemFont* yi = CCMenuItemFont::create(a2u("1��").c_str(),this,menu_selector(GameScene::menuCallbackYi));
	CCSize fontWidth = yi->getContentSize();
	int x = size.width/2 - (fontWidth.width*4 + 20 * 3)/2;
	int y = m_player->getPoint().y+88;
	yi->setAnchorPoint(ccp(0,0.5));
	yi->setPosition(ccp(x,y));
	//����
	CCMenuItemFont* er = CCMenuItemFont::create(a2u("2��").c_str(),this,menu_selector(GameScene::menuCallbackEr));
	er->setAnchorPoint(ccp(0,0.5));
	er->setPosition(ccp(x+fontWidth.width+20,y));
	//����
	CCMenuItemFont* san = CCMenuItemFont::create(a2u("3��").c_str(),this,menu_selector(GameScene::menuCallbackSan));
	san->setAnchorPoint(ccp(0,0.5));
	san->setPosition(ccp(x+fontWidth.width*2+40,y));
	//����
	CCMenuItemFont* buJiao = CCMenuItemFont::create(a2u("����").c_str(),this,menu_selector(GameScene::menuCallbackBuJiao));
	buJiao->setAnchorPoint(ccp(0,0.5));
	buJiao->setPosition(ccp(x+fontWidth.width*3+60,y));
	//�е����˵�
	m_menu = CCMenu::create();
	m_menu->addChild(yi,1,1);
	m_menu->addChild(er,1,2);
	m_menu->addChild(san,1,3);
	m_menu->addChild(buJiao,4);
	this->addChild(m_menu);
	m_menu->setPosition(CCPointZero);
	m_menu->setVisible(false);

	x = size.width/2 - (fontWidth.width*2 + 20 * 3)/2;
	y = m_player->getPoint().y+88;
	//����
	CCMenuItemFont* buChu = CCMenuItemFont::create(a2u("����").c_str(),this,menu_selector(GameScene::menuBuChu));
	buChu->setAnchorPoint(ccp(0,0.5));
	buChu->setPosition(ccp(x,y));
	//����
	CCMenuItemFont* chuPai = CCMenuItemFont::create(a2u("����").c_str(),this,menu_selector(GameScene::menuChuPai));
	chuPai->setAnchorPoint(ccp(0,0.5));
	chuPai->setPosition(ccp(x+fontWidth.width+20,y));
	//���Ʋ˵�
	m_chuPaiMenu = CCMenu::create();
	m_chuPaiMenu->addChild(buChu,2,0);
	m_chuPaiMenu->addChild(chuPai,2,1);
	m_chuPaiMenu->setPosition(CCPointZero);
	this->addChild(m_chuPaiMenu,1000);
	m_chuPaiMenu->setVisible(false);
	//��ʤ�˵İ�ť
	CCMenuItemFont* shengLi = CCMenuItemFont::create(a2u("��Ӯ��!!������¿�ʼ!!").c_str(),this,menu_selector(GameScene::menuShengLi));
	shengLi->setAnchorPoint(ccp(0.5,0.5));
	shengLi->setPosition(ccp(size.width/2,size.height/2));

	m_menuShengLi = CCMenu::create();
	m_menuShengLi->addChild(shengLi);
	m_menuShengLi->setPosition(CCPointZero);
	this->addChild(m_menuShengLi);
	m_menuShengLi->setVisible(false);
	//�����˵İ�ť
	CCMenuItemFont* shu = CCMenuItemFont::create(a2u("������!!!������¿�ʼ!!").c_str(),this,menu_selector(GameScene::menuShengLi));
	shu->setAnchorPoint(ccp(0.5,0.5));
	shu->setPosition(ccp(size.width/2,size.height/2));

	m_menuShu = CCMenu::create();
	m_menuShu->addChild(shu);
	m_menuShu->setPosition(CCPointZero);
	this->addChild(m_menuShu);
	m_menuShu->setVisible(false);
	return true;
}
void GameScene::NpcCall(Player* npc,Player* npc1){
	int i = rand()%4;
	if(i == 3)
	{
		npc->setCall(true);
		npc->setCallNum(0);
	}
	else
	{
		while (m_bCall[i] == true)	
			i = rand()%3;
		m_bCall[i] = true;
		npc->setCall(true);
		npc->setCallNum(i+1);
		//�����3�֣�������������ѽе���״̬
		if(i == 2)
		{
			m_player->setCall(true);
			npc1->setCall(true);
		}
	}
}

void GameScene::ShowFenShu(CCPoint pt,int num){
	CCString* str;
	if(num == 0)
		str = CCString::createWithFormat("����",num);
	else
		str = CCString::createWithFormat("%d��",num);
	CCLabelTTF* showFenShu = CCLabelTTF::create(a2u(str->getCString()).c_str(),"Helvetica-BoldOblique",20);
	showFenShu->setPosition(ccp(pt.x,pt.y));
	addChild(showFenShu,1,FenShu);
}
void GameScene::OutCard(float delta){
	switch (m_iOutCard%3)
	{
	case 0:
		m_chuPaiMenu->setVisible(true);
		m_typeTem = PaiDuanPaiXing();
		if(!m_npcOne->getIsOutPk() && !m_npcTwo->getIsOutPk())
			((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(0))->setEnabled(false);
		else
			((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(0))->setEnabled(true);
		//���ƻ����
		if(!m_npcOne->getIsOutPk() && !m_npcTwo->getIsOutPk())
		{
			//������г�����
			ClearOutPk();
			if (m_typeTem != ERROR_CARD)
				((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(1))->setEnabled(true);
			else
				((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(1))->setEnabled(false);
		}
		else
		{
			if(m_arrPlayerOut->count() != 0)
			{
				Poker* pk = (Poker*)m_arrGenPk->objectAtIndex(0);
				Poker* pk1 = (Poker*)m_arrPlayerOut->objectAtIndex(0);
				if(m_typeTem == m_type && pk1->getNum()>pk->getNum() || (m_typeTem==BOMB_CARD && m_type!=BOMB_CARD))
					((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(1))->setEnabled(true);
				else
					((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(1))->setEnabled(false);
			}
			else
				((CCMenuItemFont *)m_chuPaiMenu->getChildByTag(1))->setEnabled(false);
		}
		
		break;
	case 1:
		m_chuPaiMenu->setVisible(false);
		if(!m_player->getIsOutPk() && !m_npcOne->getIsOutPk())
		{
			//������г�����
			ClearOutPk();
			NpcOutPoker(m_npcTwo,m_arrGenPk,m_npcTwoOut);
		}
		else
			NpcGenPoker(m_npcTwo,m_arrGenPk ,m_npcTwoOut);
		PlayerOutPaiXu(m_arrGenPk);
		PlayerOutPaiXu(m_npcTwoOut->getArrPk());
		m_npcTwoOut->updatePkWeiZhi();
		m_npcTwo->updatePkWeiZhi();
		++m_iOutCard;
		if(IsOutPkFinish())
			m_iState = 3;
		break;
	case 2:
		if(!m_player->getIsOutPk() && !m_npcTwo->getIsOutPk())
		{
			//������г�����
			ClearOutPk();
			NpcOutPoker(m_npcOne,m_arrGenPk,m_npcOneOut);
		}
		else
			NpcGenPoker(m_npcOne,m_arrGenPk,m_npcOneOut);
		PlayerOutPaiXu(m_arrGenPk);
		PlayerOutPaiXu(m_npcTwoOut->getArrPk());
		m_npcOneOut->updatePkWeiZhi();
		m_npcOne->updatePkWeiZhi();
		++m_iOutCard;
		if(IsOutPkFinish())
			m_iState = 3;
		break;
	default:
		break;
	}
}
bool isShorter(const JiShu &js,const JiShu &js1){
	return js.num > js1.num;
}
int GameScene::PaiDuanPaiXing(){
	//�Գ����ƽ�������
	PlayerOutPaiXu(m_arrPlayerOut);
	//�����ж�
	int lengh = m_arrPlayerOut->count();
	PaiXing px;
	//�Ƶ���������5�������ж�
	if(lengh<5 && lengh>0){
		Poker* pk = (Poker *)m_arrPlayerOut->objectAtIndex(0);
		Poker* pk1 = (Poker *)m_arrPlayerOut->objectAtIndex(lengh-1);
		if(pk->getNum() == pk1->getNum())
			return lengh;
		//����һ
		pk1 = (Poker *)m_arrPlayerOut->objectAtIndex(lengh-2);
		if(pk->getNum() == pk1->getNum() && lengh == 4)
			return THREE_ONE_CARD;
		//˫��
		if(pk->getHuaSe()==Gui && pk1->getHuaSe()==Gui)
			return BOMB_CARD;
	}
	//�Ƶ��������ڵ���5�ŵ������ж�
	if(lengh>=5)
	{
		//�Ƿ�Ϊ��������
		if(IsLianPai())
			return CONNECT_CARD;
		if(IsLianDui())
			return COMPANY_CARD;
		//�жϷɻ�����
		return IsFeiJi();
	}
	return ERROR_CARD;
}
void GameScene::PlayerOutPaiXu(CCArray* m_arrPlayerOut){
	//�Գ����ƽ��з���
	std::vector<JiShu> vec;
	while(m_arrPlayerOut->count() > 0)
	{
		JiShu js;
		js.arr = CCArray::create();
		//ȡ����һ��
		Poker* pk = (Poker*)m_arrPlayerOut->objectAtIndex(0);
		m_arrPlayerOut->removeObjectAtIndex(0);
		js.num = 1;
		js.pkZhi = pk->getNum();
		js.arr->addObject(pk);
		//�ҳ����һ����ͬ����
		int i=0;
		while (i<m_arrPlayerOut->count())
		{
			Poker* pk1 = (Poker*)m_arrPlayerOut->objectAtIndex(i++);
			if(pk1->getNum() == pk->getNum())
			{
				++js.num;
				js.arr->addObject(pk1);
				m_arrPlayerOut->removeObject(pk1);
				--i;
			}
		}
		//��js�洢������������
		vec.push_back(js);
	}
	//��vec��������
	for(int i=0; i<vec.size()-1 && !vec.empty(); ++i){
		for(int j=0; j<vec.size()-i-1; ++j){
			if(vec[j].pkZhi > vec[j+1].pkZhi)
			{
				JiShu temp = vec[j];
				vec[j] = vec[j+1];
				vec[j+1] = temp;
			}
		}
	}
	stable_sort(vec.begin(),vec.end(),isShorter);
	//������õ������·���m_playerOut��
	for(std::vector<JiShu>::iterator it = vec.begin(); it!=vec.end(); ++it){
		m_arrPlayerOut->addObjectsFromArray(it->arr);
	}
}
bool GameScene::IsLianPai(){
	int lengh = m_arrPlayerOut->count();
	CCArray * arr = m_arrPlayerOut;
	//������ֵ����С��2
	CCObject* object;
#if 1
	for(int i=0;i<lengh;i++){
		if (((Poker *)arr->objectAtIndex(i))->getNum() >= 12)
			return false;
	}
#else
	CCARRAY_FOREACH(arr,object){
		if (((Poker *)object)->getNum() >= 12)
			return false;
	}
#endif
	//������������
	for(int i=0; i<lengh-1; ++i){
		Poker* pk = (Poker *)arr->objectAtIndex(i);
		Poker* pk1 = (Poker *)arr->objectAtIndex(i+1);
		if(pk->getNum()+1 != pk1->getNum())
			return false;
	}
	return true;
}
bool GameScene::IsLianDui(){
	int lengh = m_arrPlayerOut->count();
	CCArray * arr = m_arrPlayerOut;
	//������ֵ����С��2
	CCObject* object;
#if 1
	for(int i=0;i<lengh;i++){
		if (((Poker *)arr->objectAtIndex(i))->getNum() >= 12)
			return false;
	}
#else
	CCARRAY_FOREACH(arr,object){
		if (((Poker *)object)->getNum() >= 12)
			return false;
	}
#endif
	//���ڵ���6���Ʋ�������Ϊż��
	if(lengh < 6 && lengh%2 != 0)
		return false;
	//������������
	for(int i=0; i<lengh-2; i+=2){
		Poker* pk = (Poker *)arr->objectAtIndex(i);
		Poker* pk1 = (Poker *)arr->objectAtIndex(i+2);
		if(pk->getNum()+1 != pk1->getNum())
			return false;
	}
	return true;
}
int GameScene::IsFeiJi(){
	int lengh = m_arrPlayerOut->count();
	CRAD_INDEX card_index = FenXiFeiJi();
	//�ж�������
	if(card_index.three_index.size()*3+card_index.duble_index.size()*2==lengh && card_index.three_index.size()==1 && card_index.duble_index.size()==1)
		return THREE_TWO_CARD;
	//�жϷɻ�
	if(card_index.three_index.size()>1 && card_index.four_index.empty() && IsFeiJiLian(card_index.three_index)){
		//�ɻ�����
		if(card_index.three_index.size()*3 == lengh && card_index.duble_index.size()+card_index.single_index.size() == 0)
			return AIRCRAFT_CARD;
		//�ɻ�����
		if(card_index.three_index.size()*3+card_index.single_index.size() == lengh && card_index.duble_index.size() == 0)
			return AIRCRAFT_SINGLE_CARD;
		//�ɻ���˫
		if(card_index.three_index.size()*3+card_index.duble_index.size()*2 == lengh && card_index.single_index.size() == 0)
			return AIRCRAFT_DOBULE_CARD;
	}
	//�ж��Ĵ�
	if(card_index.three_index.empty() && !card_index.four_index.empty() && lengh%2 == 0)
	{
		//�Ĵ���
		if(card_index.four_index.size()*4+card_index.single_index.size() == lengh && card_index.four_index.size()==1 && card_index.single_index.size()==2)
			return BOMB_TWO_CARD;
		//�Ĵ���
		if(card_index.four_index.size()*4+card_index.duble_index.size()*2 == lengh && card_index.four_index.size()==1 && card_index.duble_index.size()==1)
			return BOMB_TWOOO_CARD;
	}
	return ERROR_CARD;
}
CRAD_INDEX GameScene::FenXiFeiJi(){
	//�������ͽṹ
	CCArray* arr = m_arrPlayerOut;
	//�ɻ�������
	CRAD_INDEX m_cardIndex; 
	for(int i=0; i<arr->count();)
	{
		int time = 0;//��ͬ�Ƶĸ���
		Poker* pk = (Poker *)arr->objectAtIndex(i);
		//�ҳ���ͬ��
		for(int j=i; j<arr->count(); ++j)
		{
			Poker* pk1 = (Poker *)arr->objectAtIndex(j);
			if(pk->getNum() == pk1->getNum()){
				++time;
				++i;
			}
		}
		//����
		if(time == 1)
			m_cardIndex.single_index.push_back(pk->getNum());
		else if(time == 2)
			m_cardIndex.duble_index.push_back(pk->getNum());
		else if(time == 3)
			m_cardIndex.three_index.push_back(pk->getNum());
		else if(time == 4)
			m_cardIndex.four_index.push_back(pk->getNum());
	}
	return m_cardIndex;
}
bool GameScene::IsFeiJiLian(std::vector<int> vec){
	for (int i=0; i<vec.size()-1; ++i)
	{
		if(vec[i]+1 != vec[i+1] || vec[i+1] >= 12)
			return false;
	}
	return true;
}
bool isShorter1(const PaiXing &px,const PaiXing &px1)//��С��������
{
	Poker* pk = px.vec.front();
	Poker* pk1 = px1.vec.front();
	return pk->getNum() < pk1->getNum();
}
void GameScene::FenChaiNpcPai(Player* npc){
	return;//�����˿��ƺ���
	/************************************************************************/
	/* 1.���ȷ��������Ƶ�����                                               */
	/************************************************************************/
	std::vector<PaiXing> vec;
	PaiXing xing;
	CCArray* arr = CCArray::create();//��ʱ����
	arr->addObjectsFromArray(npc->getArrPk());
	//��ȡ˫��
	Poker* pk = (Poker *)arr->objectAtIndex(0);
	Poker* pk1 = (Poker *)arr->objectAtIndex(1);
	if(pk->getHuaSe() == Gui && pk1->getHuaSe() == Gui){
		xing.type = BOMB_CARD;
		xing.vec.push_back(pk);
		xing.vec.push_back(pk1);
		arr->removeObject(pk);
		arr->removeObject(pk1);
		vec.push_back(xing);
	}
	//��������
	for(int i=0; i<arr->count();)
	{
		pk = (Poker*)arr->objectAtIndex(i);
		xing.vec.clear();//�������
		//�ҳ���pk��ͬ����
		for (int j=i; j<arr->count(); ++j)
		{
			pk1 = (Poker*)arr->objectAtIndex(j);
			if(pk->getNum() == pk1->getNum())
			{
				++i;
				xing.vec.push_back(pk1);
			}
			else
			{
				break;
			}
		}
		if(xing.vec.size() == 4)
			xing.type = BOMB_CARD;
		if(xing.vec.size() == 3)
			xing.type = THREE_CARD;
		if(xing.vec.size() == 2)
			xing.type = DOUBLE_CARD;
		if(xing.vec.size() == 1)
			xing.type = SINGLE_CARD;
		vec.push_back(xing);
	}
	/************************************************************************/
	/* 2.�����ȼ���ȡ���Ͳ��������ڳ��ƻ����                               */
	/************************************************************************/
	//��ȡը��
	for(std::vector<PaiXing>::iterator iter = vec.begin(); iter != vec.end(); )
	{
		if(iter->type == BOMB_CARD)
		{
			xing.type = BOMB_CARD;
			xing.vec.clear();
			xing.vec = iter->vec;
			npc->m_vecPX.push_back(xing);
			iter = vec.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//��ȡ�ɻ�
	TiQuFeiJi(npc,THREE_CARD,vec);
	//��ȡ����
	TiQuLianDui(npc,vec);
	//��ȡ����
	TiQuLianPai(npc,vec);
	//ʣ���������,����,���� ȫ������npc������
	for(std::vector<PaiXing>::iterator iter = vec.begin(); iter != vec.end();)
	{
		npc->m_vecPX.push_back(*iter);
		iter = vec.erase(iter);
	}
	//����
	stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
}
void GameScene::TiQuFeiJi(Player* npc,CARD_TYPE type,std::vector<PaiXing> &vec){
	Poker * pk = NULL;
	PaiXing xing;
	for (std::vector<PaiXing>::iterator iter=vec.begin(); iter != vec.end();)
	{
		if(pk == NULL && iter+1 == vec.end())
			break;
		if(pk == NULL && iter->type == type && (iter+1)->type == type)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk2 = (iter+1)->vec.front();
			if(pk1->getNum()-1 == pk2->getNum())
			{
				pk = pk2;
				xing.type = AIRCRAFT_CARD;
				xing.vec.clear();
				xing.vec = iter->vec;
				iter = vec.erase(iter);
				xing.vec.insert(xing.vec.end(),iter->vec.begin(),iter->vec.end());
				iter = vec.erase(iter);
			}
		}
		if(pk != NULL)
		{
			if(iter == vec.end())
			{
				npc->m_vecPX.push_back(xing);
				break;
			}
				
			Poker* pk1 = iter->vec.front();
			if(iter->type == type && pk->getNum()-1 == pk1->getNum())
			{
				pk = pk1;
				xing.vec.insert(xing.vec.end(),iter->vec.begin(),iter->vec.end());
				iter = vec.erase(iter);
				if(iter == vec.end())
				{
					npc->m_vecPX.push_back(xing);
					break;
				}
			}
			else
			{
				npc->m_vecPX.push_back(xing);
				pk = NULL;
			}
		}
		else
		{
			++iter;
		}
	}
}

bool isDaDaoXiao(const PaiXing &px,const PaiXing &px1)//�Ӵ�С����
{
	Poker* pk = px.vec.front();
	Poker* pk1 = px1.vec.front();
	return pk->getNum() > pk1->getNum();
}
void GameScene::TiQuLianDui(Player* npc,std::vector<PaiXing> &vec){
	std::vector<PaiXing> vecTem;//��ʱ����
	std::vector<PaiXing> vecFan;//���Ҫ���·���vec�����
	Poker* pk = NULL;
	for(std::vector<PaiXing>::iterator iter = vec.begin(); iter != vec.end();)
	{
		//���������Ƽ�����ʱ������
		Poker* pk1 = iter->vec.front();
		if((iter->type == THREE_CARD || iter->type == DOUBLE_CARD) && (pk == NULL || (pk->getNum()-1 == pk1->getNum() && pk->getNum() < Er)))
		{
			pk = pk1;
			vecTem.push_back(*iter);
			iter = vec.erase(iter);
		}
		else
		{
			if(pk == NULL)
				++iter;
			pk = NULL;
			if(vecTem.size() >= 3)
			{
				PaiXing xing;
				xing.type = COMPANY_CARD;
				for (int i=0; i<vecTem.size(); ++i)
				{
					if(vecTem[i].type == THREE_CARD)
					{
						//�������һ�ű��淵������vecFan��
						PaiXing xing1;
						xing1.type = SINGLE_CARD;
						xing1.vec.push_back(vecTem[i].vec.back());
						vecTem[i].vec.pop_back();
						vecFan.push_back(xing1);
						//��ʣ�����ű���xing��
						xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
					}
					if(vecTem[i].type == DOUBLE_CARD)
					{
						xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
					}
				}
				vecTem.clear();
				npc->m_vecPX.push_back(xing);
			}
			else if(!vecTem.empty())
			{
				vecFan.insert(vecFan.end(),vecTem.begin(),vecTem.end());
				vecTem.clear();
			}
		}
	}
	if(!vecTem.empty())
	{
		if(vecTem.size() >= 3)
			{
				PaiXing xing;
				xing.type = COMPANY_CARD;
				for (int i=0; i<vecTem.size(); ++i)
				{
					if(vecTem[i].type == THREE_CARD)
					{
						//�������һ�ű��淵������vecFan��
						PaiXing xing1;
						xing1.type = SINGLE_CARD;
						xing1.vec.push_back(vecTem[i].vec.back());
						vecTem[i].vec.pop_back();
						vecFan.push_back(xing1);
						//��ʣ�����ű���xing��
						xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
					}
					if(vecTem[i].type == DOUBLE_CARD)
					{
						xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
					}
				}
				vecTem.clear();
				npc->m_vecPX.push_back(xing);
			}
			else if(!vecTem.empty())
			{
				vecFan.insert(vecFan.end(),vecTem.begin(),vecTem.end());
				vecTem.clear();
			}
	}
	//��vecFan���ص�vec�����в��Ӵ�С����
	if(!vecFan.empty())
	{
		vec.insert(vec.end(),vecFan.begin(),vecFan.end());
		stable_sort(vec.begin(),vec.end(),isDaDaoXiao);
	}
}
void GameScene::TiQuLianPai(Player* npc,std::vector<PaiXing> &vec){
	std::vector<PaiXing> vecTem;//��ʱ����
	std::vector<PaiXing> vecFan;//���Ҫ���·���vec�����
	Poker* pk = NULL;
	for(std::vector<PaiXing>::iterator iter = vec.begin(); iter != vec.end();)
	{
		//���������Ƽ�����ʱ������
		Poker* pk1 = iter->vec.front();
		if((iter->type == THREE_CARD || iter->type == DOUBLE_CARD || iter->type == SINGLE_CARD) && (pk == NULL || (pk->getNum()-1 == pk1->getNum() && pk->getNum() < Er)))
		{
			pk = pk1;
			vecTem.push_back(*iter);
			iter = vec.erase(iter);
		}
		else
		{
			if(pk == NULL)
				++iter;
			pk = NULL;
			if(vecTem.size() >= 5)
			{
				PaiXing xing;
				xing.type = CONNECT_CARD;
				for (int i=0; i<vecTem.size(); ++i)
				{
					if(vecTem[i].type == THREE_CARD)
					{
						//����������ű��淵������vecFan��
						PaiXing xing1;
						xing1.type = DOUBLE_CARD;
						xing1.vec.push_back(vecTem[i].vec.back());
						vecTem[i].vec.pop_back();
						xing1.vec.push_back(vecTem[i].vec.back());
						vecTem[i].vec.pop_back();
						vecFan.push_back(xing1);
						//��ʣ��һ�ű���xing��
						xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
					}
					if(vecTem[i].type == DOUBLE_CARD)
					{
						//�������һ�ű��淵������vecFan��
						PaiXing xing1;
						xing1.type = SINGLE_CARD;
						xing1.vec.push_back(vecTem[i].vec.back());
						vecTem[i].vec.pop_back();
						vecFan.push_back(xing1);
						//��ʣ��һ�ű���xing��
						xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
					}
					if(vecTem[i].type == SINGLE_CARD)
						xing.vec.push_back(vecTem[i].vec.front());
				}
				vecTem.clear();
				npc->m_vecPX.push_back(xing);
			}
			else if(!vecTem.empty())
			{
				vecFan.insert(vecFan.end(),vecTem.begin(),vecTem.end());
				vecTem.clear();
			}
		}
	}
	if(!vecTem.empty())
	{
		if(vecTem.size() >= 5)
		{
			PaiXing xing;
			xing.type = CONNECT_CARD;
			for (int i=0; i<vecTem.size(); ++i)
			{
				if(vecTem[i].type == THREE_CARD)
				{
					//����������ű��淵������vecFan��
					PaiXing xing1;
					xing1.type = DOUBLE_CARD;
					xing1.vec.push_back(vecTem[i].vec.back());
					vecTem[i].vec.pop_back();
					xing1.vec.push_back(vecTem[i].vec.back());
					vecTem[i].vec.pop_back();
					vecFan.push_back(xing1);
					//��ʣ��һ�ű���xing��
					xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
				}
				if(vecTem[i].type == DOUBLE_CARD)
				{
					//�������һ�ű��淵������vecFan��
					PaiXing xing1;
					xing1.type = SINGLE_CARD;
					xing1.vec.push_back(vecTem[i].vec.back());
					vecTem[i].vec.pop_back();
					vecFan.push_back(xing1);
					//��ʣ��һ�ű���xing��
					xing.vec.insert(xing.vec.end(),vecTem[i].vec.begin(),vecTem[i].vec.end());
				}
				if(vecTem[i].type == SINGLE_CARD)
					xing.vec.push_back(vecTem[i].vec.front());
			}
			vecTem.clear();
			npc->m_vecPX.push_back(xing);
		}
		else if(!vecTem.empty())
		{
			vecFan.insert(vecFan.end(),vecTem.begin(),vecTem.end());
			vecTem.clear();
		}
	}
	//��vecFan���ص�vec�����в��Ӵ�С����
	if(!vecFan.empty())
	{
		vec.insert(vec.end(),vecFan.begin(),vecFan.end());
		stable_sort(vec.begin(),vec.end(),isShorter1);
	}
}
void GameScene::NpcOutPoker(Player* npc,CCArray* out,Player* out1){
	//������һ�γ�����
	CCObject* object;
	CCARRAY_FOREACH(out1->getArrPk(),object){
		Poker* pk = (Poker*)object;
		pk->setVisible(false);
	}
	out1->getArrPk()->removeAllObjects();
	if(npc->m_vecPX.size()==0)
		return;//by hxh
	//�����ֵ��С��һ������
	PaiXing px = npc->m_vecPX.front();
	out->removeAllObjects();
	//��������ԭ��
	if(px.type == THREE_CARD){
		stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
		m_type = THREE_CARD;
		//����
		for(std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin();iter!=npc->m_vecPX.end();++iter)
		{
			//����ֻʣ�����ƣ������ܴ�����2
			Poker* pk = iter->vec.front();
			if(pk->getNum() >= Er && npc->m_vecPX.size() != 1)
				break;
			if(iter->type == SINGLE_CARD)
			{
				out1->getArrPk()->addObject(iter->vec.front());
				out->addObject(iter->vec.front());
				npc->getArrPk()->removeObject(iter->vec.front());
				npc->m_vecPX.erase(iter);
				m_type = THREE_ONE_CARD;
				break;
			}
		}
		//��˫
		if(out1->getArrPk()->count() == 0)
		{
			for(std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin();iter!=npc->m_vecPX.end();++iter)
			{
				//����ֻʣ�����ƣ������ܴ�����2
				Poker* pk = iter->vec.front();
				if(pk->getNum() >= Er && npc->m_vecPX.size() != 1)
					break;
				if(iter->type == DOUBLE_CARD)
				{
					for(std::vector<Poker*>::iterator it=iter->vec.begin();it!=iter->vec.end();++it)
					{
						out1->getArrPk()->addObject(*it);
						out->addObject(*it);
						npc->getArrPk()->removeObject(*it);
					}
					npc->m_vecPX.erase(iter);
					m_type = THREE_TWO_CARD;
					break;
				}
			}
		}
	}
	//��˳����ԭ��
	if(px.type == AIRCRAFT_CARD){
		//���㹻�ĵ��ʹ���
		stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
		m_type = AIRCRAFT_CARD;
		if(GetNpcPxNum(npc,SINGLE_CARD) >= px.vec.size()/3)
		{
			int num=0;
			for (std::vector<PaiXing>::iterator it=npc->m_vecPX.begin(); it!=npc->m_vecPX.end()&&num<px.vec.size()/3;)
			{
				if(it->type == SINGLE_CARD)
				{
					++num;
					out1->getArrPk()->addObject(it->vec.front());
					out->addObject(it->vec.front());
					npc->getArrPk()->removeObject(it->vec.front());
					it = npc->m_vecPX.erase(it);
					m_type = AIRCRAFT_SINGLE_CARD;
				}
				else
					++it;
			}
		}
		//���㹻��˫�ʹ�˫
		if(GetNpcPxNum(npc,DOUBLE_CARD) >= px.vec.size()/3 && out1->getArrPk()->count() == 0)
		{
			int num=0;
			for (std::vector<PaiXing>::iterator it=npc->m_vecPX.begin(); it!=npc->m_vecPX.end()&&num<px.vec.size()/3;)
			{
				if(it->type == DOUBLE_CARD)
				{
					++num;
					for(std::vector<Poker*>::iterator ite=it->vec.begin(); ite!=it->vec.end(); ++ite)
					{
						out1->getArrPk()->addObject(*ite);
						out->addObject(*ite);
						npc->getArrPk()->removeObject(*ite);
						m_type = AIRCRAFT_DOBULE_CARD;
					}
					it = npc->m_vecPX.erase(it);
				}
				else
					++it;
			}
		}
	}
	//���Ƴ���ԭ��,ֱ�ӳ�����������
	if(px.type == CONNECT_CARD){
		m_type = CONNECT_CARD;
	}
	//˫˳����ԭ��ֱ�ӳ�����������
	if(px.type == COMPANY_CARD){
		m_type = COMPANY_CARD;
	}
	//���Ӻ͵��ӳ���ԭ��
	if(px.type == DOUBLE_CARD || px.type == SINGLE_CARD){
		int threeNum = GetNpcPxNum(npc,THREE_CARD)+GetNpcPxNum(npc,AIRCRAFT_CARD);
		int chiBangNum = GetNpcPxNum(npc,DOUBLE_CARD)+GetNpcPxNum(npc,SINGLE_CARD);
		//��������<=���ж���+���е���-2�������ӣ������������
		if(threeNum <= chiBangNum-2 || threeNum == 0)
		{
			if(px.type == DOUBLE_CARD)
				m_type = DOUBLE_CARD;
			if(px.type == SINGLE_CARD)
				m_type = SINGLE_CARD;
		}
		else
		{
			PaiXing px = npc->m_vecPX.front();
			std::vector<PaiXing>::iterator dle = npc->m_vecPX.begin();
			npc->m_vecPX.erase(dle);
			npc->m_vecPX.push_back(px);
			NpcOutPoker(npc,out,out1);
			return;
		}
	}
	for(std::vector<Poker*>::iterator iter=px.vec.begin(); iter!=px.vec.end(); ++iter)
	{
		out1->getArrPk()->addObject(*iter);
		out->addObject(*iter);
		npc->getArrPk()->removeObject(*iter);
		npc->setIsOutPk(true);
	}
	m_lastOut = npc;
	//��npc->m_vecPX���Ƴ�px
	for(std::vector<PaiXing>::iterator it=npc->m_vecPX.begin();it!=npc->m_vecPX.end();++it)
	{
		if(it->type == px.type && it->vec.front()->getNum() == px.vec.front()->getNum())
		{
			npc->m_vecPX.erase(it);
			break;
		}
	}
}

void GameScene::NpcGenPoker(Player* npc,CCArray* out ,Player* out1){
	
	//������һ�γ�����
	if(m_isChiBang)
	{
		CCObject* object;
		CCARRAY_FOREACH(out1->getArrPk(),object){
			Poker* pk = (Poker*)object;
			pk->setVisible(false);
		}
		out1->getArrPk()->removeAllObjects();
	}
	/************************************************************************/
	/*�ҳ���Ӧ���ͳ���                                                      */
	/************************************************************************/
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(m_type == iter->type)
		{
			//�Էɻ������ƽ����ж�
			if(m_type == AIRCRAFT_CARD || m_type == CONNECT_CARD || m_type == COMPANY_CARD)
				if(out->count() != iter->vec.size())
					continue;
			Poker* pk = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pk1 = iter->vec.front();
			//����Է����Լ��˴���2���Ʋ���
			if(!npc->getIsDiZhu() && !m_lastOut->getIsDiZhu())
			{
				if(pk1->getNum()>=Er || m_type == BOMB_CARD)
				{
					//pass
					if(npc == m_npcOne)
						this->getChildByTag(NpcOneBuChu)->setVisible(true);
					if(npc == m_npcTwo)
						this->getChildByTag(NpcTwoBuChu)->setVisible(true);
					npc->setIsOutPk(false);
					return;
				}
			}
			if(pk1->getNum() > pk->getNum())
			{
				out->removeAllObjects();
				for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
					out1->getArrPk()->addObject(*it);
					npc->getArrPk()->removeObject(*it);
					out->addObject(*it);
				}
				npc->m_vecPX.erase(iter);
				npc->setIsOutPk(true);
				m_lastOut = npc;
				return;
			}
		}
	}
	//����һ��������
	if(SanDaiYiOrEr(npc,out,out1))
		return;
	//�Ĵ������Ĵ�˫
	//�ɻ��������˫
	if(FeiJiDaiChiBang(npc,out,out1))
		return;
	/************************************************************************/
	/*�����ը����ʣһ����                                                  */
	/************************************************************************/
	if(npc->m_vecPX.size() == 2)
	{
		for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
		{
			if(iter->type == BOMB_CARD && m_type != BOMB_CARD)
			{
				out->removeAllObjects();
				for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
					out1->getArrPk()->addObject(*it);
					npc->getArrPk()->removeObject(*it);
					out->addObject(*it);
				}
				npc->m_vecPX.erase(iter);
				m_lastOut = npc;
				return;
			}
		}
	}
	/************************************************************************/
	/* ������Ʒ����Լ��˲����Ƹ�                                        */
	/************************************************************************/
	if(!npc->getIsDiZhu() && !m_lastOut->getIsDiZhu())
	{
		//pass
		if(npc == m_npcOne)
			this->getChildByTag(NpcOneBuChu)->setVisible(true);
		if(npc == m_npcTwo)
			this->getChildByTag(NpcTwoBuChu)->setVisible(true);
		npc->setIsOutPk(false);
		return;
	}
	/************************************************************************/
	/*�����Ƹ�֮                                                        */
	/************************************************************************/
	if(NpcChaiDan(npc,out,out1))
		return;
	/************************************************************************/
	/*��˫�Ƹ�֮                                                        */
	/************************************************************************/
	if(NpcChaiDui(npc,out,out1))
		return;
	/************************************************************************/
	/*�������Ƹ�֮                                                        */
	/************************************************************************/
	if(NpcChaiSan(npc,out,out1))
		return;
	/************************************************************************/
	/*��ɻ��Ƹ�֮                                                        */
	/************************************************************************/
	if(NpcChaiFeiJi(npc,out,out1))
		return;
	/************************************************************************/
	/*�����Ƹ�֮                                                        */
	/************************************************************************/
	if(NpcChaiLianPai(npc,out,out1))
		return;	
	/************************************************************************/
	/*��˫˳��֮                                                        */
	/************************************************************************/
	if(NpcChaiShuangShun(npc,out,out1))
		return;
	 //ը֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == BOMB_CARD)
		{
			//������Ʒ����Ĳ���ը����ը֮������Ƚϴ�Сը֮
			if(m_type != BOMB_CARD)
			{
				out->removeAllObjects();
				for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
					out1->getArrPk()->addObject(*it);
					npc->getArrPk()->removeObject(*it);
					out->addObject(*it);
				}
				npc->m_vecPX.erase(iter);
				m_type = BOMB_CARD;
				npc->setIsOutPk(true);
				m_lastOut = npc;
				return;
			}else
			{
				Poker* pk = (Poker*)out->objectAtIndex(0);
				Poker* pk1 = iter->vec.front();
				if(pk1->getNum()>pk->getNum())
				{
					out->removeAllObjects();
					for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
						out1->getArrPk()->addObject(*it);
						npc->getArrPk()->removeObject(*it);
						out->addObject(*it);
					}
					npc->m_vecPX.erase(iter);
					m_type = BOMB_CARD;
					npc->setIsOutPk(true);
					m_lastOut = npc;
					return;
				}
			}

		}
	}
	 //pass
	
	if(npc == m_npcOne)
	{
		this->getChildByTag(NpcOneBuChu)->setVisible(true);
	}
	if(npc == m_npcTwo)
	{
		this->getChildByTag(NpcTwoBuChu)->setVisible(true);
	}
	npc->setIsOutPk(false);
}
bool GameScene::SanDaiYiOrEr(Player* npc,CCArray* out,Player* out1){
	if((m_type == THREE_ONE_CARD || m_type == THREE_TWO_CARD) && m_isChiBang)
	{
		//�������һ����������4���򷵻�
		if(m_type == THREE_ONE_CARD && npc->getArrPk()->count()<4)
			return false;
		//������������������û�жԣ�������˫˳����˳�ͷ���
		if (m_type == THREE_TWO_CARD)
		{
			if(npc->getArrPk()->count()<5)
				return false;
			std::vector<PaiXing>::iterator iter;
			for (iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
			{
				if(iter->type == DOUBLE_CARD || iter->type == THREE_CARD || iter->type == COMPANY_CARD || iter->type == AIRCRAFT_CARD)
				{
					break;
				}
			}
			if(iter == npc->m_vecPX.end())
				return false;
		}
		m_count = out->count();
		//�ҳ�����
		for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
		{
			if(iter->type == THREE_CARD)
			{
				Poker* pk = (Poker*)out->objectAtIndex(0);
				Poker* pk1 = iter->vec.front();
				if(pk1->getNum() > pk->getNum())
				{
					out->removeAllObjects();
					for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
						out1->getArrPk()->addObject(*it);
						npc->getArrPk()->removeObject(*it);
						out->addObject(*it);
					}
					npc->m_vecPX.erase(iter);
					m_isChiBang = false;
					break;
				}
			}
		}
	}
	if (!m_isChiBang)
	{
		//���ϳ��
		for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
		{
			//����
			if(m_count == 4)
			{
				if(iter->type == SINGLE_CARD)
				{
					out1->getArrPk()->addObject(iter->vec.front());
					npc->getArrPk()->removeObject(iter->vec.front());
					out->addObject(iter->vec.front());
					npc->m_vecPX.erase(iter);
					m_isChiBang = true;
					npc->setIsOutPk(true);
					m_lastOut = npc;
					return true;
				}
			}
			//��˫
			if (m_count == 5)
			{
				if(iter->type == DOUBLE_CARD)
				{
					for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
						out1->getArrPk()->addObject(*it);
						npc->getArrPk()->removeObject(*it);
						out->addObject(*it);
					}
					npc->m_vecPX.erase(iter);
					m_isChiBang = true;
					npc->setIsOutPk(true);
					m_lastOut = npc;
					return true;
				}
			}
		}	
		if(m_count == 4)
		{
			NpcChaiDan(npc,out,out1);
			return true;
		}
		else if(m_count == 5)
		{
			NpcChaiDui(npc,out,out1);
			return true;
		}
	}
	return false;
}
bool GameScene::FeiJiDaiChiBang(Player* npc,CCArray* out,Player* out1){
	if((m_type == AIRCRAFT_SINGLE_CARD || m_type == AIRCRAFT_DOBULE_CARD) && m_isChiBang)
	{
		m_threeNum = 0;
		//�����м�������
		for(int i=0; i<out->count();)
		{
			int count = 0;
			Poker* pk = (Poker*)out->objectAtIndex(i);
			for (int j=i; j<out->count(); ++j)
			{
				Poker* pk1 = (Poker*)out->objectAtIndex(j);
				if(pk->getNum() == pk1->getNum())
				{
					count++;
					++i;
				}
				else
					break;
			}
			if(count == 3)
				m_threeNum++;
			else
				break;
		}
		//����ɻ������ƣ���������out.count���򷵻�
		if(m_type == AIRCRAFT_SINGLE_CARD && npc->getArrPk()->count()<out->count())
			return false;
		
		//����ɻ���˫���������û���㹻˫�ɴ��ͷ���
		if (m_type == AIRCRAFT_DOBULE_CARD)
		{
			if(npc->getArrPk()->count()<out->count())
				return false;
			//�����м���˫
			int doubleNum = 0;
			for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
				if(iter->type == DOUBLE_CARD || iter->type == THREE_CARD || iter->type == COMPANY_CARD || iter->type == AIRCRAFT_CARD)
					++doubleNum;
			//��������������ڶԵĸ����ͷ���false
			if(m_threeNum > doubleNum)
				return false;
		}
		//�ҳ��ɻ�
		for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
		{
			if(iter->type == AIRCRAFT_CARD)
			{
				if(m_threeNum != iter->vec.size()/3)
					continue;
				Poker* pk = (Poker*)out->objectAtIndex(m_threeNum*3);
				Poker* pk1 = iter->vec.front();
				if(pk1->getNum() > pk->getNum())
				{
					out->removeAllObjects();
					for(std::vector<Poker*>::iterator it = iter->vec.begin(); it!=iter->vec.end(); ++it){
						out1->getArrPk()->addObject(*it);
						npc->getArrPk()->removeObject(*it);
						out->addObject(*it);
					}
					npc->m_vecPX.erase(iter);
					m_isChiBang = false;
					break;
				}
			}
		}
	}
	if (!m_isChiBang)
	{
		//���ϳ��
		for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end();)
		{
			//����
			if(m_type == AIRCRAFT_SINGLE_CARD)
			{
				if(iter->type == SINGLE_CARD)
				{
					if(m_threeNum != 0)
					{
						out1->getArrPk()->addObject(iter->vec.front());
						npc->getArrPk()->removeObject(iter->vec.front());
						out->addObject(iter->vec.front());
						iter = npc->m_vecPX.erase(iter);
						--m_threeNum;
						if (m_threeNum == 0)
						{
							m_isChiBang = true;
							npc->setIsOutPk(true);
							m_lastOut = npc;
							return true;
						}
					}
				}
				else
					++iter;
			}
			//��˫
			if (m_type == AIRCRAFT_DOBULE_CARD)
			{
				if(iter->type == DOUBLE_CARD)
				{
					if(m_threeNum != 0)
					{
						for(int i=0; i<2; ++i)
						{
							out1->getArrPk()->addObject(iter->vec[i]);
							npc->getArrPk()->removeObject(iter->vec[i]);
							out->addObject(iter->vec[i]);
						}
						iter = npc->m_vecPX.erase(iter);
						--m_threeNum;
						if (m_threeNum == 0)
						{
							m_isChiBang = true;
							npc->setIsOutPk(true);
							m_lastOut = npc;
							return true;
						}
					}
				}
				else
					++iter;
			}
		}	
		if(m_type == AIRCRAFT_SINGLE_CARD)
		{
			NpcChaiDan(npc,out,out1);
			return true;
		}
		else if(m_type == AIRCRAFT_DOBULE_CARD)
		{
			NpcChaiDui(npc,out,out1);
			return true;
		}
	}
	return false;
}
bool GameScene::NpcChaiDan(Player* npc,CCArray* out ,Player* out1){
	if(m_type != SINGLE_CARD
	&& m_type != THREE_ONE_CARD 
	&& m_type != AIRCRAFT_SINGLE_CARD
	)
		return false;
	//1.��2��֮
	if(m_type == SINGLE_CARD)
	{
		for(std::vector<PaiXing>::iterator iter = npc->m_vecPX.begin(); iter != npc->m_vecPX.end(); ++iter)
		{
			Poker* pk = iter->vec.front();
			if(pk->getNum() == Er && iter->vec.size()>1)
			{
				//��һ�ŵ������ͼ��뵽npc->m_vecPX��
				PaiXing px;
				px.type = SINGLE_CARD;
				px.vec.push_back(iter->vec.back());
				iter->vec.pop_back();
				//�ı�ʣ�������
				if (iter->vec.size() == 3)
					iter->type = THREE_CARD;
				if(iter->vec.size() == 2)
					iter->type = DOUBLE_CARD;
				if(iter->vec.size() == 1)
					iter->type = SINGLE_CARD;
				if(iter->vec.size() == 0)
					npc->m_vecPX.erase(iter);
				//��npc->m_vecPX����
				npc->m_vecPX.push_back(px);
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}

	//2.��Ը�֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == DOUBLE_CARD)
		{
			Poker* pk = (Poker*)out->objectAtIndex(0);
			Poker* pk1 = iter->vec.front();
			if (pk1->getNum()>pk->getNum() 
			|| !m_isChiBang)
			{
				//��һ�����ͼ��뵽npc->m_vecPX��
				PaiXing px;
				px.type = SINGLE_CARD;
				px.vec.push_back(iter->vec.back());
				iter->vec.pop_back();
				//�ı�ʣ����������
				iter->type = SINGLE_CARD;
				//��������
				npc->m_vecPX.push_back(px);
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//3.��6�����ϵ�����֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == CONNECT_CARD && iter->vec.size()>=6)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk = (Poker*)out->objectAtIndex(0);
			if (pk1->getNum()>pk->getNum() 
				|| !m_isChiBang)
			{
				std::deque<Poker*> deqPx;
				deqPx.insert(deqPx.end(),iter->vec.begin(),iter->vec.end());
				//��һ�����ͼ��뵽npc->m_vecPX��
				PaiXing px;
				px.type = SINGLE_CARD;
				px.vec.push_back(deqPx.front());
				deqPx.pop_front();
				//�ı�ʣ����������
				iter->vec.clear();
				iter->vec.insert(iter->vec.end(),deqPx.begin(),deqPx.end());
				npc->m_vecPX.push_back(px);
				//��������
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}

		}
	}
	//4.��������֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == THREE_CARD)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk = (Poker*)out->objectAtIndex(0);
			if (pk1->getNum()>pk->getNum() 
				|| !m_isChiBang)
			{
				//��һ�����ͼ��뵽npc->m_vecPX��
				PaiXing px;
				px.type = SINGLE_CARD;
				px.vec.push_back(iter->vec.back());
				iter->vec.pop_back();
				//�ı�ʣ����������
				iter->type = DOUBLE_CARD;
				//��������
				npc->m_vecPX.push_back(px);
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//5.����˳��֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk = (Poker*)out->objectAtIndex(0);
			if (pk1->getNum()>pk->getNum() 
				|| !m_isChiBang)
			{
				std::deque<Poker*> deqPx;
				deqPx.insert(deqPx.end(),iter->vec.begin(),iter->vec.end());
				//��һ�����ͼ��뵽npc->m_vecPX��
				PaiXing px;
				px.type = THREE_CARD;
				for(int i=0; i<3; ++i)
				{
					px.vec.push_back(deqPx.front());
					deqPx.pop_front();
				}
				//�ı�ʣ����������
				if(iter->vec.size()/3 == 1)
					iter->type = THREE_CARD;
				iter->vec.clear();
				iter->vec.insert(iter->vec.end(),deqPx.begin(),deqPx.end());
				npc->m_vecPX.push_back(px);
				//��������
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//6.��5����˳��֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == CONNECT_CARD && iter->vec.size()>=5)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk = (Poker*)out->objectAtIndex(0);
			if (pk1->getNum()>pk->getNum() 
				|| !m_isChiBang)
			{
				std::vector<PaiXing> vecPx;
				//��ÿһ�����Ͳ�ֳɵ������ͼ��뵽npc->m_vecPX��
				for (std::vector<Poker*>::iterator it=iter->vec.begin(); it!=iter->vec.end(); ++it)
				{
					PaiXing px;
					px.type = SINGLE_CARD;
					px.vec.push_back(*it);
					vecPx.push_back(px);
				}
				//ɾ����������
				npc->m_vecPX.erase(iter);
				npc->m_vecPX.insert(npc->m_vecPX.end(),vecPx.begin(),vecPx.end());
				//��������
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//7.��˫˳��֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == COMPANY_CARD)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk = (Poker*)out->objectAtIndex(0);
			if (pk1->getNum()>pk->getNum() 
				|| !m_isChiBang)
			{
				std::vector<PaiXing> vecPx;
				std::deque<Poker*> deqPk;
				deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
				//С��4ȫ��ɡ��ԡ�����,�����һ���Ժ�һ������
				if(iter->vec.size()/2 < 4)
				{
					//�ֲ�ɶ���
					while (deqPk.size()!=0)
					{
						PaiXing px;
						px.type = DOUBLE_CARD;
						for (int i=0; i<2; ++i)
						{
							px.vec.push_back(deqPk.front());
							deqPk.pop_front();
						}
						vecPx.push_back(px);
					}
					//ɾ��������
					npc->m_vecPX.erase(iter);
					//���ֲ�Ķ��Ƽ���
					npc->m_vecPX.insert(npc->m_vecPX.end(),vecPx.begin(),vecPx.end());
				}else
				{
					//��һ�����ͼ��뵽npc->m_vecPX��
					PaiXing px;
					px.type = DOUBLE_CARD;
					for(int i=0; i<2; ++i)
					{
						px.vec.push_back(deqPk.front());
						deqPk.pop_front();
					}
					//�ı�ʣ����������
					iter->vec.clear();
					iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
					npc->m_vecPX.push_back(px);
				}

				//��������
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	return false;
}
bool GameScene::NpcChaiDui(Player* npc,CCArray* out,Player* out1){
	if(m_type != DOUBLE_CARD
	 && m_type != THREE_TWO_CARD
	 && m_type != AIRCRAFT_DOBULE_CARD)
		return false;
	//1.����������˫˳��֮
	for(std::vector<PaiXing>::iterator iter = npc->m_vecPX.begin(); iter != npc->m_vecPX.end(); ++iter){
		if(iter->type == COMPANY_CARD && iter->vec.size()/2 >= 4)
		{
			std::deque<Poker*> deqPk;
			deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
			//��һ����
			PaiXing px;
			px.type = DOUBLE_CARD;
			for(int i=0; i<2; ++i)
			{
				px.vec.push_back(deqPk.front());
				deqPk.pop_front();
			}
			//�ı�ʣ�������
			iter->vec.clear();
			iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
			//��px����npc->m_vecPX
			npc->m_vecPX.push_back(px);
			//��������
			stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
			//����
			NpcGenPoker(npc,out,out1);
			return true;
		}
	}
	//2.��������֮
	for(std::vector<PaiXing>::iterator iter = npc->m_vecPX.begin(); iter != npc->m_vecPX.end(); ++iter){
		if(iter->type == THREE_CARD)
		{
			std::deque<Poker*> deqPk;
			deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
			//��һ����
			PaiXing px;
			px.type = DOUBLE_CARD;
			for(int i=0; i<2; ++i)
			{
				px.vec.push_back(deqPk.front());
				deqPk.pop_front();
			}
			//�ı�ʣ�������
			iter->type = SINGLE_CARD;
			iter->vec.clear();
			iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
			//��px����npc->m_vecPX
			npc->m_vecPX.push_back(px);
			//��������
			stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
			//����
			NpcGenPoker(npc,out,out1);
			return true;
		}
	}
	//3.��˫˳��֮
	for(std::vector<PaiXing>::iterator iter = npc->m_vecPX.begin(); iter != npc->m_vecPX.end(); ++iter){
		if(iter->type == COMPANY_CARD)
		{
			std::deque<Poker*> deqPk;
			deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
			std::vector<PaiXing> vecPx;
			//������˫˳��ɶ���
			while (deqPk.size()!=0)
			{
				PaiXing px;
				px.type = DOUBLE_CARD;
				for(int i=0; i<2; ++i)
				{
					px.vec.push_back(deqPk.front());
					deqPk.pop_front();
				}
				vecPx.push_back(px);
			}
			
			//ɾ����������
			npc->m_vecPX.erase(iter);
			//��px����npc->m_vecPX
			npc->m_vecPX.insert(npc->m_vecPX.end(),vecPx.begin(),vecPx.end());
			//��������
			stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
			//����
			NpcGenPoker(npc,out,out1);
			return true;
		}
	}
	//4.����˳��֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD)
		{
			Poker* pk1 = iter->vec.front();
			Poker* pk = (Poker*)out->objectAtIndex(0);
			if(pk1->getNum()>pk->getNum())
			{
				std::vector<PaiXing> vecPx;
				std::deque<Poker*> deqPk;
				deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
				//С��2ȫ��ɡ�����������,�����һ��������һ����˳
				if(iter->vec.size()/3 <= 2)
				{
					//�ֲ�ɶ���
					while (deqPk.size()!=0)
					{
						PaiXing px;
						px.type = THREE_CARD;
						for (int i=0; i<3; ++i)
						{
							px.vec.push_back(deqPk.front());
							deqPk.pop_front();
						}
						vecPx.push_back(px);
					}
					//ɾ��������
					npc->m_vecPX.erase(iter);
					//���ֲ����������
					npc->m_vecPX.insert(npc->m_vecPX.end(),vecPx.begin(),vecPx.end());
				}else
				{
					//��һ���������ͼ��뵽npc->m_vecPX��
					PaiXing px;
					px.type = THREE_CARD;
					for(int i=0; i<3; ++i)
					{
						px.vec.push_back(deqPk.front());
						deqPk.pop_front();
					}
					//�ı�ʣ����������
					iter->vec.clear();
					iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
					npc->m_vecPX.push_back(px);
				}
				//��������
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//����
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	return false;
}
bool GameScene::NpcChaiSan(Player* npc,CCArray* out,Player* out1){
	if(m_type != THREE_CARD && m_type != THREE_ONE_CARD && m_type !=THREE_TWO_CARD)
		return false;
	//����˳��֮
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD)
		{
			Poker* pk = (Poker*)out->objectAtIndex(0);
			Poker* pk1 = iter->vec.front();
			if(pk1->getNum() > pk->getNum())
			{
				std::deque<Poker*> deqPk;
				deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
				//����������
				PaiXing px;
				px.type = THREE_CARD;
				for (int i=0; i<3; ++i)
				{
					px.vec.push_back(deqPk.front());
					deqPk.pop_front();
				}
				//�ı�ʣ�������
				if(deqPk.size()/3 == 1)
					iter->type = THREE_CARD;
				iter->vec.clear();
				iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
				//����
				npc->m_vecPX.push_back(px);
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		
		}
	}
	return false;
}
bool GameScene::NpcChaiFeiJi(Player* npc,CCArray* out,Player* out1){
	if(m_type != AIRCRAFT_CARD && m_type != AIRCRAFT_SINGLE_CARD && m_type != AIRCRAFT_DOBULE_CARD)
		return false;
	//��ɻ�����˳��
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD)
		{
			//�����м�������
			int threeNum = FenXiFeiJiNum(out);
			Poker* pk = (Poker*)out->objectAtIndex(threeNum*3);
			Poker* pk1 = iter->vec.front();

			
			int num = threeNum*3;
			int num1 = iter->vec.size();
			if(pk1->getNum() > pk->getNum() && num1 > num)
			{
				std::deque<Poker*> deqPk;
				deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
				//����������
				PaiXing px;
				px.type = AIRCRAFT_CARD;
				for (int i=0; i<num; ++i)
				{
					px.vec.push_back(deqPk.front());
					deqPk.pop_front();
				}
				//�ı�ʣ�������
				if(deqPk.size()/3 == 1)
					iter->type = THREE_CARD;
				iter->vec.clear();
				iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
				//����
				npc->m_vecPX.push_back(px);
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	return false;
}
bool GameScene::NpcChaiLianPai(Player* npc,CCArray* out,Player* out1){
	if(m_type != CONNECT_CARD)
		return false;
	//1.����ͬ����˫˳
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == COMPANY_CARD)
		{
			int outNum = out->count();
			int iterNum = iter->vec.size()/2;
			Poker* pk = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pk1 = iter->vec.front();
			if(pk1->getNum()>pk->getNum() && outNum==iterNum)
			{
				//����������
				PaiXing px;
				px.type = CONNECT_CARD;
				for(std::vector<Poker*>::iterator it=iter->vec.begin(); it!=iter->vec.end();++it)
				{
					px.vec.push_back(*it);
					it = iter->vec.erase(it);
				}
				//�ı�ʣ�������
				iter->type = CONNECT_CARD;
				//����
				npc->m_vecPX.push_back(px);
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//2.����ͬ������˳���ɻ���
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD)
		{
			int outNum = out->count();
			int iterNum = iter->vec.size()/3;
			Poker* pk = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pk1 = iter->vec.front();
			if(pk1->getNum()>pk->getNum() && outNum==iterNum)
			{
				//����������
				PaiXing px;
				px.type = CONNECT_CARD;
				for(std::vector<Poker*>::iterator it=iter->vec.begin(); it!=iter->vec.end();it+=2)
				{
					px.vec.push_back(*it);
					it = iter->vec.erase(it);
					
				}
				//�ı�ʣ�������
				iter->type = COMPANY_CARD;
				//����
				npc->m_vecPX.push_back(px);
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//3.��ͬ��������
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == CONNECT_CARD && iter->vec.size() > out->count())
		{
			Poker* pkFirst = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pkLast = (Poker*)out->objectAtIndex(0);
			//��iter->vec��ȡout->count()����
			std::vector<Poker*> vecPk;
			for(size_t i=0; i<out->count(); ++i)
				vecPk.push_back(iter->vec[i]);
			Poker* pk1First = vecPk.front();
			Poker* pk1Last = vecPk.back();
			if(pk1First > pkFirst && pk1Last > pkLast)
			{
				std::deque<Poker*> deqPk;
				deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
				//����������
				PaiXing px;
				px.type = CONNECT_CARD;
				for(int i=0; i<out->count(); ++i)
				{
					px.vec.push_back(deqPk.front());
					deqPk.pop_front();
				}
				iter->vec.clear();
				iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
				//�ı�ʣ�������
				std::vector<PaiXing> vecPx;
				if(iter->vec.size() < 5)
				{
					for (std::vector<Poker*>::iterator it=iter->vec.begin(); it!=iter->vec.end(); ++it)
					{
						PaiXing px;
						px.type = SINGLE_CARD;
						px.vec.push_back(*it);
						vecPx.push_back(px);
					}
					
				}
				npc->m_vecPX.erase(iter);
				//����
				npc->m_vecPX.push_back(px);
				npc->m_vecPX.insert(npc->m_vecPX.end(),vecPx.begin(),vecPx.end());
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//4.��ͬ����˫˳
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == COMPANY_CARD && iter->vec.size()/2 > out->count())
		{
			Poker* pkFirst = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pkLast = (Poker*)out->objectAtIndex(0);
			//��iter->vec��ȡout->count()����
			std::vector<Poker*> vecPk;
			for(size_t i=0; i<out->count(); ++i)
				vecPk.push_back(iter->vec[i*2]);
			Poker* pk1First = vecPk.front();
			Poker* pk1Last = vecPk.back();
			if(pk1First->getNum() > pkFirst->getNum() && pk1Last->getNum() > pkLast->getNum())
			{
				CCArray* arr = CCArray::create();
				for (std::vector<Poker*>::iterator it=iter->vec.begin();it!=iter->vec.end();++it)
					arr->addObject(*it);
				//����������
				PaiXing px;
				px.type = CONNECT_CARD;
				for(int i=0; i<out->count(); ++i)
					px.vec.push_back((Poker*)arr->objectAtIndex(i*2));
				for(std::vector<Poker*>::iterator it=px.vec.begin();it!=px.vec.end();++it)
					arr->removeObject(*it);
				npc->m_vecPX.erase(iter);
				//�ı�ʣ�������
				Player pl;
				CCObject* object;
#if 1
				for(int i=0;i<arr->count();i++){
					pl.getArrPk()->addObject(arr->objectAtIndex(i));
				}
#else
				CCARRAY_FOREACH(arr,object){
					pl.getArrPk()->addObject(object);
				}
#endif
				FenChaiNpcPai(&pl);
				//����
				npc->m_vecPX.insert(npc->m_vecPX.end(),pl.m_vecPX.begin(),pl.m_vecPX.end());
				npc->m_vecPX.push_back(px);
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//5.��ͬ������˳
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD && iter->vec.size()/3 > out->count())
		{
			Poker* pkFirst = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pkLast = (Poker*)out->objectAtIndex(0);
			//��iter->vec��ȡout->count()����
			std::vector<Poker*> vecPk;
			for(size_t i=0; i<out->count(); ++i)
				vecPk.push_back(iter->vec[i*3]);
			Poker* pk1First = vecPk.front();
			Poker* pk1Last = vecPk.back();
			if(pk1First->getNum() > pkFirst->getNum() && pk1Last->getNum() > pkLast->getNum())
			{
				CCArray* arr = CCArray::create();
				for (std::vector<Poker*>::iterator it=iter->vec.begin();it!=iter->vec.end();++it)
					arr->addObject(*it);
				//����������
				PaiXing px;
				px.type = CONNECT_CARD;
				for(int i=0; i<out->count(); ++i)
					px.vec.push_back((Poker*)arr->objectAtIndex(i*3));
				for(std::vector<Poker*>::iterator it=px.vec.begin();it!=px.vec.end();++it)
					arr->removeObject(*it);
				npc->m_vecPX.erase(iter);
				//�ı�ʣ�������
				Player pl;
				CCObject* object;
#if 1
				for(int i=0;i<arr->count();i++){
					pl.getArrPk()->addObject(arr->objectAtIndex(i));
				}
#else
				CCARRAY_FOREACH(arr,object){
					pl.getArrPk()->addObject(object);
				}
#endif
				FenChaiNpcPai(&pl);
				//����
				npc->m_vecPX.insert(npc->m_vecPX.end(),pl.m_vecPX.begin(),pl.m_vecPX.end());
				npc->m_vecPX.push_back(px);
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	return false;
}
int GameScene::FenXiFeiJiNum(CCArray* arr){
	int threeNum = 0;
	for(int i=0; i<arr->count();)
	{
		int count = 0;
		Poker* pk = (Poker*)arr->objectAtIndex(i);
		for (int j=i; j<arr->count(); ++j)
		{
			Poker* pk1 = (Poker*)arr->objectAtIndex(j);
			if(pk->getNum() == pk1->getNum())
			{
				count++;
				++i;
			}
			else
				break;
		}
		if(count == 3)
			threeNum++;
		else
			break;
	}
	return threeNum;
}
bool GameScene::NpcChaiShuangShun(Player* npc,CCArray* out,Player* out1){
	if(m_type != COMPANY_CARD)
		return false;
	//1.��ͬ������˫˳
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == COMPANY_CARD && iter->vec.size() > out->count())
		{
			Poker* pkFirst = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pkLast = (Poker*)out->objectAtIndex(0);
			//��iter->vec��ȡout->count()����
			std::vector<Poker*> vecPk;
			for(size_t i=0; i<out->count(); ++i)
				vecPk.push_back(iter->vec[i]);
			Poker* pk1First = vecPk.front();
			Poker* pk1Last = vecPk.back();
			if(pk1First > pkFirst && pk1Last > pkLast)
			{
				std::deque<Poker*> deqPk;
				deqPk.insert(deqPk.end(),iter->vec.begin(),iter->vec.end());
				//����������
				PaiXing px;
				px.type = CONNECT_CARD;
				for(int i=0; i<out->count(); ++i)
				{
					px.vec.push_back(deqPk.front());
					deqPk.pop_front();
				}
				iter->vec.clear();
				iter->vec.insert(iter->vec.end(),deqPk.begin(),deqPk.end());
				//�ı�ʣ�������
				std::vector<PaiXing> vecPx;
				if(iter->vec.size() < 6)
				{
					std::vector<Poker*>::iterator it=iter->vec.begin();
					for(int i=0; i<2; ++i)
					{
						PaiXing px1;
						px1.type = CONNECT_CARD;
						px1.vec.push_back(*it++);
						px1.vec.push_back(*it++);
						vecPx.push_back(px1);
					}
					npc->m_vecPX.erase(iter);
				}
				//����
				npc->m_vecPX.push_back(px);
				npc->m_vecPX.insert(npc->m_vecPX.end(),vecPx.begin(),vecPx.end());
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	//2.����ͬ��������˳
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == AIRCRAFT_CARD)
		{
			int outNum = out->count()/2;
			int iterNum = iter->vec.size()/3;
			Poker* pk = (Poker*)out->objectAtIndex(out->count()-1);
			Poker* pk1 = iter->vec.front();
			if(pk1->getNum()>pk->getNum() && iterNum>=outNum)
			{
				//��˫˳����
				PaiXing px;
				px.type = COMPANY_CARD;
				std::vector<Poker*> vecPk;
				for(size_t i=0; i<iter->vec.size(); ++i)
				{
					if((i%3 == 0 || i%3 == 1) && px.vec.size()<out->count())
						px.vec.push_back(iter->vec[i]);
					else 
						vecPk.push_back(iter->vec[i]);
				}
				npc->m_vecPX.erase(iter);
				//�ı�ʣ�������
				Player pl;
				for (std::vector<Poker*>::iterator it=vecPk.begin();it!=vecPk.end();++it)
					pl.getArrPk()->addObject(*it);
				FenChaiNpcPai(&pl);
				//����
				npc->m_vecPX.push_back(px);
				npc->m_vecPX.insert(npc->m_vecPX.end(),pl.m_vecPX.begin(),pl.m_vecPX.end());
				//��npc->m_vecPX����
				stable_sort(npc->m_vecPX.begin(),npc->m_vecPX.end(),isShorter1);
				//�ٴν��и���
				NpcGenPoker(npc,out,out1);
				return true;
			}
		}
	}
	return false;
}
int GameScene::GetNpcPxNum(Player* npc,CARD_TYPE cardType){
	int num = 0;
	for (std::vector<PaiXing>::iterator iter=npc->m_vecPX.begin(); iter!=npc->m_vecPX.end(); ++iter)
	{
		if(iter->type == cardType)
		{
			if(cardType == AIRCRAFT_CARD)
				num+=iter->vec.size()/3;
			else
				++num;
		}
	}
	return num;
}
bool GameScene::InitNpcBuChuLable(){
	//npctwo��ǩ
	CCLabelTTF* npcTwoBuChu = CCLabelTTF::create(a2u("����").c_str(),"Helvetica-BoldOblique",20);
	npcTwoBuChu->setPosition(m_npcTwoOut->getPoint());
	this->addChild(npcTwoBuChu,1,NpcTwoBuChu);
	npcTwoBuChu->setVisible(false);
	//npcone��ǩ
	CCLabelTTF* npcOneBuChu = CCLabelTTF::create(a2u("����").c_str(),"Helvetica-BoldOblique",20);
	npcOneBuChu->setPosition(m_npcOneOut->getPoint());
	this->addChild(npcOneBuChu,1,NpcOneBuChu);
	npcOneBuChu->setVisible(false);
	return true;
}
void GameScene::ClearOutPk()
{
	CCObject* object;
	CCARRAY_FOREACH(m_playerOut->getArrPk(),object){
		Poker* pk = (Poker*)object;
		pk->setVisible(false);
	}
	m_playerOut->getArrPk()->removeAllObjects();
	CCARRAY_FOREACH(m_npcTwoOut->getArrPk(),object){
		Poker* pk = (Poker*)object;
		pk->setVisible(false);
	}
	m_npcTwoOut->getArrPk()->removeAllObjects();
	CCARRAY_FOREACH(m_npcOneOut->getArrPk(),object){
		Poker* pk = (Poker*)object;
		pk->setVisible(false);
	}
	m_npcOneOut->getArrPk()->removeAllObjects();
	this->getChildByTag(NpcOneBuChu)->setVisible(false);
	this->getChildByTag(NpcTwoBuChu)->setVisible(false);
}
bool GameScene::IsOutPkFinish(){
	if(m_player->getArrPk()->count() == 0)
		return true;
	if(m_npcOne->getArrPk()->count() == 0)
		return true;
	if(m_npcTwo->getArrPk()->count() == 0)
		return true;
	return false;
}
void GameScene::IsShengLi(){
	//��ҳ�����
	if(m_player->getArrPk()->count() == 0)
		//ʤ��
		m_menuShengLi->setVisible(true);
	//����1������
	if(m_npcOne->getArrPk()->count() == 0)
	{
		if(m_npcOne->getIsDiZhu() || m_player->getIsDiZhu())
			m_menuShu->setVisible(true);
		if(m_npcTwo->getIsDiZhu())
			m_menuShengLi->setVisible(true);

	}
	//����2������
	if(m_npcTwo->getArrPk()->count() == 0)
	{
		if(m_npcTwo->getIsDiZhu() || m_player->getIsDiZhu())
			m_menuShu->setVisible(true);
		if(m_npcOne->getIsDiZhu())
			m_menuShengLi->setVisible(true);
	}
}
void GameScene::ReStart(){
	//��ʼ��
	m_iState = 0;
	m_isSend=true;
	m_iSendPk=0;
	m_iOutCard=0;
	m_type = ERROR_CARD;
	m_isChiBang = true;
	for(int i=0; i<3; ++i)
		m_bCall[i] = false;
	m_lableDiZhu->setVisible(false);
	this->getChildByTag(NpcTwoBuChu)->setVisible(false);
	this->getChildByTag(NpcOneBuChu)->setVisible(false);
	//�ָ������Ƶ�����
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCObject* object;
	CCARRAY_FOREACH(m_arrPokers,object){
		Poker* pk = (Poker*)object;
		pk->setPosition(ccp(size.width/2,size.height/2));
		pk->showLast();
		pk->setSelect(false);
		pk->setDianJi(false);
		pk->setVisible(true);
	}
	//�ָ��������
	m_player->setIsDiZhu(false);
	m_player->setCall(false);
	m_player->setCallNum(0);
	m_player->setIsOutPk(false);
	m_player->m_vecPX.clear();

	m_npcOne->setIsDiZhu(false);
	m_npcOne->setCall(false);
	m_npcOne->setCallNum(0);
	m_npcOne->setIsOutPk(false);
	m_npcOne->m_vecPX.clear();

	m_npcTwo->setIsDiZhu(false);
	m_npcTwo->setCall(false);
	m_npcTwo->setCallNum(0);
	m_npcTwo->setIsOutPk(false);
	m_npcTwo->m_vecPX.clear();
	//�������
	m_player->getArrPk()->removeAllObjects();
	m_playerOut->getArrPk()->removeAllObjects();
	m_npcOne->getArrPk()->removeAllObjects();
	m_npcOneOut->getArrPk()->removeAllObjects();
	m_npcTwo->getArrPk()->removeAllObjects();
	m_npcTwoOut->getArrPk()->removeAllObjects();
	CCARRAY_FOREACH(m_Three->getArrPk(),object)
	{
		Poker* pk = (Poker*)object;
		pk->removeFromParentAndCleanup(true);//removeFromParent();
	}
	m_Three->getArrPk()->removeAllObjects();
	m_menuShengLi->setVisible(false);
	m_menuShu->setVisible(false);
	m_chuPaiMenu->setVisible(false);
	//ϴ��
	xiPai();
}
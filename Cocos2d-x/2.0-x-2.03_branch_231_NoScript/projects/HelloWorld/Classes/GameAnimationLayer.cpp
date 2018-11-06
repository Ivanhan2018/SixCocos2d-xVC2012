//
//  GameAnimationLayer.cpp
//  XXDDZ
//
//  Created by ChengLin on 13-10-31.
//
//

#include "GameAnimationLayer.h"
//#include "GameMusicController.h"

// 当前类的对象
static GameAnimationLayer* gameAnimationLayer = NULL;

extern _BYTE_ UserSelfIndex;

int OUt_cardNUmbew;
// 1 L 2 R 3 S
#define AnimationPosition(A,B) (A / PROPERTY_POT + 2 - B)%3

// 道具坐标离中心点的偏�?
int offsetPosition[3][2] = {{380,120},{-380,120},{0,-200}};
// 文字显示坐标离中心点的偏�?
int offSetTextPostion[3][2] = {{0,-10},{200,60},{-200,60}};

// 构造函�?
GameAnimationLayer::GameAnimationLayer(){
    this->init();
}
// 析构函数
GameAnimationLayer::~GameAnimationLayer(){
    
}

bool GameAnimationLayer::init(){
    if(!CCLayer::init()){
        return false;
    }
    // 缓存道具图片资源1
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("symbol1.plist", "symbol1.png");
    // 缓存道具图片资源2
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("symbol2.plist", "symbol2.png");
    // 提示文字的资源初始化
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gametip.plist", "gametip.png");
    
    // 获取场景大小
    size = CCDirector::sharedDirector()->getWinSize();
    // 道具动画进入时长
    inTime = 1.5;
    // 道具动画消失时长
    outTime = 5;
    /////////////////// 指针初始�?//////////////
    // 洗牌动画对象
    dispatchCard_sprite = NULL;
    // 创建动画消息列表
    msgList = new list<GameAnimationMsg>();
    // 判断定时器是否已经启�?    
	timerIsRun = false;
    
    OUt_cardNUmbew = 0;
    CCTexture2D *textureCard = CCTextureCache::sharedTextureCache()->addImage("CardNew.png");
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 14; j++) {
            CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(j*90, i*120, 90, 120));
            char a[50];snprintf(a,50, "CardBig%d%d",i,j+1);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
        }
    }
    {//小王
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(0, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",4,14);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//大王
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(90, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",4,15);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    return true;
}



// 获取当前类的单例
GameAnimationLayer* GameAnimationLayer::shareGameAnimation(){
    if(!gameAnimationLayer){
        gameAnimationLayer = new GameAnimationLayer();
    }
    return gameAnimationLayer;
}
// 清除单例对象
void GameAnimationLayer::purgeShareGameAnimation(void){
    gameAnimationLayer = NULL;
}

// 播放动画
void GameAnimationLayer::playAnimationByID(GameAnimationMsg &msg){
    if(!msgList) return;
    // 将消息添加到列表
    msgList->push_back(msg);
    // 判断定时器是否已经启�?    
	if(!timerIsRun){
        //this->schedule(schedule_selector(GameAnimationLayer::timerCallBack), 0.1);
        // 设置定时器启动标志（开启）
        timerIsRun = true;
    }
}

// 定时器回�?
void GameAnimationLayer::timerCallBack(){
    if(msgList->empty()){
        // 停止定时�?        
		//this->unschedule(schedule_selector(GameAnimationLayer::timerCallBack));
        // 设置定时器启动标志（关闭�?        
		timerIsRun = false;
    }else{
        this->playAnimationByID(msgList->front().animationType);
        // 移除列表中的动画
        msgList->pop_front();
    }
}

// 播放动画
bool GameAnimationLayer::playAnimationByID(int animationType){
    // 播放游戏动画
    if(animationType < PROPERTY_POT){
        switch (animationType) {
            case AN_BOMB:
            {
                return explosion_Animation();
            }
            case AN_PLANE:
            {
                return plane_Animation();
            }
            case AN_ROCKET:
            {
                return rocket_Animation();
            }
            case AN_DISPATCH_CARD:
            {
                return dispatchCard_Animation();
            }
            default:
                CCLOG("没有对应项！");
                break;
        }
    }else{// 播放道具动画
        // 过滤出显示位�?左：1，右�?,中：3)
        int position = AnimationPosition(animationType, UserSelfIndex);
        switch(animationType % PROPERTY_POT){
            case PROPERTY_ID_CAR:
            {
                return car_Animation(position);
            }
            case PROPERTY_ID_EGG:
            {
                return egg_Animation(position);
            }
            case PROPERTY_ID_CLAP:
            {
                return clap_Animation(position);
            }
            case PROPERTY_ID_KISS:
            {
                return kiss_Animation(position);
            }
            case PROPERTY_ID_BEER:
            {
                return beer_Animation(position);
            }
            case PROPERTY_ID_CAKE:
            {
                return cake_Animation(position);
            }
            case PROPERTY_ID_RING:
            {
                return ring_Animation(position);
            }
            case PROPERTY_ID_BEAT:
            {
                return beat_Animation(position);
            }
            case PROPERTY_ID_BOMB:
            {
                return bomb_Animation(position);
            }
            case PROPERTY_ID_SMOKE:
            {
                return smoke_Animation(position);
            }
            case PROPERTY_ID_VILLA:
            {
                return villa_Animation(position);
            }
            case PROPERTY_ID_BRICK:
            {
                return brick_Animation(position);
            }
            case PROPERTY_ID_FLOWER:
            {
                return flower_Animation(position);
            }
            default:    // 文字动画
            {
                return textTips_Animation(position, animationType % PROPERTY_POT);
            }
                break;
        }
    }
    return true;
}
//////////////////////////// 游戏动画 ///////////////////////////////////
// 炸弹动画
bool GameAnimationLayer::explosion_Animation(){
    // 创建帧缓�?    
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("CARTOON_BOMB.png");
    //从桢缓存 创建帧框�?    
	CCArray *arr = CCArray::create();
    for(int i=0;i<6;i++){
        //从桢缓存 创建帧框�?        
		arr->addObject(CCSpriteFrame::createWithTexture(texture, CCRectMake(220*i, 0, 220, 517)));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    // 创建对象
    CCSprite *explosion_sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("CARTOON_BOMB.png",CCRectMake(0, 0, 220, 517)));
    explosion_sprite->setPosition(ccp(480,400));
    
    // 播放动画
    explosion_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCAnimate::create(animation), CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),explosion_sprite), NULL)));
    
    this->addChild(explosion_sprite,1);
    // 添加音效
    //GameMusicController::sharedGameMusic()->playEffect(VO_GL_BOMB);
    return true;
}

// 飞机效果
bool GameAnimationLayer::plane_Animation(){
    // 创建帧缓�?    
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("CARTOON_PLAN.png");
    //从桢缓存 创建帧框�?    
	CCArray *arr = CCArray::create();
    for(int i=0;i<3;i++){
        //从桢缓存 创建帧框�?        
		CCSpriteFrame *SitItem = CCSpriteFrame::createWithTexture(texture, CCRectMake(200*i, 0, 200, 134));
        arr->addObject(SitItem);
    }
    //创建�?    
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    // 创建对象
    CCSprite *plane_sprite = CCSprite::create("CARTOON_PLAN.png");
    plane_sprite->setPosition(ccp(1000,400));
    
    // 播放动画
    plane_sprite->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(CCAnimate::create(animation), NULL))));
    plane_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCMoveTo::create(1.8, CCPointMake(-150, 400)), CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),plane_sprite), NULL)));
    
    this->addChild(plane_sprite,1);
    // 添加音效
    //GameMusicController::sharedGameMusic()->playEffect(VO_GL_PLANE);
    return true;
}

// 火箭效果
bool GameAnimationLayer::rocket_Animation(){
    // 创建帧缓�?    
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("ROCKET.png");
    //从桢缓存 创建帧框�?    
	CCSpriteFrame *SitItem1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, 40, 180));
    //从桢缓存 创建帧框�?    
	CCSpriteFrame *SitItem2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(46, 0, 40, 180));
    //从桢缓存 创建帧框�?    
	CCSpriteFrame *SitItem3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(86, 0, 40, 180));
    //从桢缓存 创建帧框�?    
	CCSpriteFrame *SitItem4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(130, 0, 40, 180));
    //从桢缓存 创建帧框�?    
	CCSpriteFrame *SitItem5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(170, 0, 40, 180));
    //从桢缓存 创建帧框�?    
	CCSpriteFrame *SitItem6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(215, 0, 40, 180));
    
    //从桢缓存 创建帧框�?    
	CCArray *arr = CCArray::create(SitItem1,SitItem2, SitItem3,SitItem4, SitItem5,SitItem6, NULL);
    //创建�?    
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    // 创建对象
    CCSprite *rocket_sprite = CCSprite::create("ROCKET.png");
    rocket_sprite->setPosition(ccp(480,-200));
    
    // 播放动画
    rocket_sprite->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(CCAnimate::create(animation), NULL))));
    rocket_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCMoveTo::create(1.8, CCPointMake(480,840)), CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),rocket_sprite), NULL)));
    
    this->addChild(rocket_sprite,1);
    // 添加音效
    //GameMusicController::sharedGameMusic()->playEffect(VO_GL_BOMB);
    return true;
}


// 文字动画
bool GameAnimationLayer::textTips_Animation(int position,int textType){
    
    CCLog("显示位置�?d",position);
    
    // 创建精灵
    CCSprite *ccsprite = CCSprite::create();
    // 设置位置
    ccsprite->setPosition(ccp(size.width/2 + offSetTextPostion[position][0], size.height/2 + offSetTextPostion[position][1]));
    // 设置图像
    CCSpriteFrame *spriteFrame = NULL;
    switch(textType){
        case AN_TEXT_CALLBANKER:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_callbanker.png");
        }
            break;
        case AN_TEXT_NOTCALLBANKER:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_notcallbanker.png");
        }
            break;
        case AN_TEXT_RODBANKER:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_rodbanker.png");
        }
            break;
        case AN_TEXT_NOTRODBANKER:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_notrodbanker.png");
        }
            break;
        case AN_TEXT_DOUBLE:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_double.png");
        }
            break;
        case AN_TEXT_NOTDOUBLE:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_notdouble.png");
        }
            break;
        case AN_TEXT_MISS_CARD:
        {
            
        }
            break;
        case AN_TEXT_NOTOUTCARD:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_notoutcard.png");
        }
            break;
        case AN_TEXT_NOTCALL:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_notcall.png");
        }
            break;
        case AN_TEXT_YIFEN:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_yifen.png");
        }
            break;
        case AN_TEXT_ERFEN:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_erfen.png");
        }
            break;
        case AN_TEXT_SANFEN:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_sanfen.png");
        }
            break;
        case AN_TEXT_READY:
        {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_ready.png");
        }
            break;
    }
    
    // 设置图片
    if(spriteFrame){
        ccsprite->setDisplayFrame(spriteFrame);
    }
    // 创建动画
    CCArray *arrayOfActions = new CCArray();
    for (int i = 0; i < 3; i++) {
        CCRotateTo *rtoleft = CCRotateTo::create(0.3, 2);
        arrayOfActions->addObject(rtoleft);
        CCRotateTo *rtoright = CCRotateTo::create(0.3, -2);
        arrayOfActions->addObject(rtoright);
    }
    // 播放动画
    ccsprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCSequence::create(arrayOfActions),CCFadeOut::create(0.5),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),ccsprite),NULL)));
    
    this->addChild(ccsprite);
    
    return true;
}


// 洗牌动画
bool GameAnimationLayer::dispatchCard_Animation(){
    // 创建帧缓�?    
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("DISPATCH_CARD.png");
    CCArray *arr = CCArray::create();
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            //从桢缓存 创建帧框�?            
			CCSpriteFrame *SitItem = CCSpriteFrame::createWithTexture(texture, CCRectMake(j*257, i*167, 257, 167));
            arr->addObject(SitItem);
        }
    }
    // 创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.1);
    // 创建对象
    dispatchCard_sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("DISPATCH_CARD.png", CCRectMake(0, 0, 257, 167)));
    dispatchCard_sprite->setPosition(ccp(480,400));
    dispatchCard_sprite->setScale(0.9);
    // 播放动画
    dispatchCard_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCAnimate::create(animation), CCCallFunc::create(this, callfunc_selector(GameAnimationLayer::dispatchCard_AnimationCallBack)), NULL)));
    
    this->addChild(dispatchCard_sprite);
    return true;
}

//////////////////////////// 道具动画 ////////////////////////////
//汽车礼物
bool GameAnimationLayer::car_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 9;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "qc%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    for(int i=0;i<3;i++){
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("qc9.png"));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.25f);
    
    CCSprite *car_sprite = CCSprite::createWithSpriteFrameName("qc1.png");
    car_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    car_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),car_sprite),NULL)));
    
    this->addChild(car_sprite);
    return true;
}
//臭蛋礼物
bool GameAnimationLayer::egg_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 18;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "jd%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.1f);
    
    CCSprite* egg_sprite = CCSprite::createWithSpriteFrameName("jd1.png");
    egg_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    egg_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),egg_sprite),NULL)));
    
    this->addChild(egg_sprite);
    return true;
}
//鼓掌礼物
bool GameAnimationLayer::clap_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 35;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "gz%d.png",i%5+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.1f);
    
    CCSprite *clap_sprite = CCSprite::createWithSpriteFrameName("gz1.png");
    clap_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    clap_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),clap_sprite),NULL)));
    
    this->addChild(clap_sprite);
    return true;
}
//香吻礼物
bool GameAnimationLayer::kiss_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i = 0;i < 24 ;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "xw%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.15f);
    
    CCSprite *kiss_sprite = CCSprite::createWithSpriteFrameName("xw1.png");
    kiss_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    kiss_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),kiss_sprite),NULL)));
    
    this->addChild(kiss_sprite);
    return true;
}
//啤酒礼物
bool GameAnimationLayer::beer_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i = 0;i < 21 ;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "pj%d.png",i%7+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.15f);
    
    CCSprite *beer_sprite = CCSprite::createWithSpriteFrameName("pj1.png");
    beer_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    beer_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),beer_sprite),NULL)));
    
    this->addChild(beer_sprite);
    return true;
}
//蛋糕礼物
bool GameAnimationLayer::cake_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i = 0;i < 10 ;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "dg%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.15f);
    
    CCSprite *cake_sprite = CCSprite::createWithSpriteFrameName("dg1.png");
    cake_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    cake_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),cake_sprite),NULL)));
    
    this->addChild(cake_sprite);
    return true;
}
//钻戒礼物
bool GameAnimationLayer::ring_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i = 0;i < 19 ;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "zs%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.15f);
    
    CCSprite *ring_sprite = CCSprite::createWithSpriteFrameName("zs1.png");
    ring_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    ring_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),ring_sprite),NULL)));
    
    this->addChild(ring_sprite);
    return true;
}
//暴打礼物
bool GameAnimationLayer::beat_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 11;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "bd%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    CCSprite *beat_sprite = CCSprite::createWithSpriteFrameName("bd1.png");
    beat_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    beat_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),beat_sprite),NULL)));
    
    this->addChild(beat_sprite);
    return true;
}
//炸弹礼物
bool GameAnimationLayer::bomb_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 9;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "zd%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    CCSprite *bomb_sprite = CCSprite::createWithSpriteFrameName("zd1.png");
    bomb_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    bomb_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),bomb_sprite),NULL)));
    
    this->addChild(bomb_sprite);
    return true;
}
//香烟礼物
bool GameAnimationLayer::smoke_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i <16;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "xy%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    CCSprite *smoke_sprite = CCSprite::createWithSpriteFrameName("xy1.png");
    smoke_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    smoke_sprite->runAction(static_cast<CCSequence *>(CCSequence::create(CCFadeIn::create(inTime),CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),smoke_sprite),NULL)));
    
    this->addChild(smoke_sprite);
    return true;
}
//别墅礼物
bool GameAnimationLayer::villa_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 17;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "bs%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    CCSprite *villa_sprite = CCSprite::createWithSpriteFrameName("bs1.png");
    villa_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    villa_sprite->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCFadeIn::create(inTime),CCSequence::create(CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),villa_sprite),NULL))));
    
    this->addChild(villa_sprite);
    return true;
}
//砖头礼物
bool GameAnimationLayer::brick_Animation(int position){
    
    CCArray *arr = CCArray::create();
    for(int i=0;i < 15;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "zz%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    CCSprite *brick_sprite = CCSprite::createWithSpriteFrameName("zz1.png");
    brick_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    brick_sprite->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCFadeIn::create(inTime),CCSequence::create(CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),brick_sprite),NULL))));
    
    this->addChild(brick_sprite);
    return true;
}
//鲜花礼物
bool GameAnimationLayer::flower_Animation(int position){
    CCArray *arr = CCArray::create();
    for(int i=0;i < 22;i++){
        //从桢缓存 创建帧框�?        
		char img[50];snprintf(img,50, "xh%d.png",i+1);
        arr->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(img));
    }
    //创建动画
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,0.2f);
    
    CCSprite *flower_sprite = CCSprite::createWithSpriteFrameName("xh1.png");
    flower_sprite->setPosition(ccp(size.width/2 + offsetPosition[position][0], size.height/2 + offsetPosition[position][1]));
    
    flower_sprite->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCFadeIn::create(inTime),CCSequence::create(CCAnimate::create(animation),CCFadeOut::create(outTime),CCCallFuncO::create(this, callfuncO_selector(GameAnimationLayer::AnimationCallBack),flower_sprite),NULL))));
    
    this->addChild(flower_sprite);
    return true;
}

#define outCardCreat  320

#pragma mark 出牌动画
//出牌动画
bool GameAnimationLayer::outCard_Animation(BYTE cardNumbew, BYTE *cardData, cocos2d::CCPoint *cardPoint){
    
    OUt_cardNUmbew = cardNumbew;
    for(int i=0;i < cardNumbew;i++){
        // 初始化手牌数�?        
		_AnicardSprites[i] = CCSprite::create();
        _AnicardSprites[i]->setPosition(ccp(cardPoint[i].x, cardPoint[i].y));
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(cardData[i]/16),(cardData[i]%16));
        _AnicardSprites[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
       // _AnicardSprites[i]->runAction(CCSpawn::create(CCMoveTo::create(0.25,ccp(i*45 +480 - OUt_cardNUmbew/2*45,230)), CCScaleTo::create(0.25, 0.6), NULL));
        _AnicardSprites[i]->setVisible(true);
        this->addChild(_AnicardSprites[i] ,10);
    }
    for (int i = 0; i< cardNumbew; i++) {
        _AnicardSprites[i]->runAction(CCSpawn::create(CCMoveTo::create(0.25,ccp(i*30 +480 - OUt_cardNUmbew/2*30,230)), CCScaleTo::create(0.25, 0.6), NULL));
        //_AnicardSprites[i]->runAction(CCMoveTo::create(0.2,ccp(i*30 +480 - OUt_cardNUmbew/2*30,230)));
    }
    return true;
}


#pragma mark 销毁出牌动�?
void GameAnimationLayer::distoryoutcard_Animation(){
    //float xxxx = this->getChildByTag(outCardCreat)->getPositionX();
    CCLog("用户的出牌z_____________________%d" , OUt_cardNUmbew);
    if (OUt_cardNUmbew > 0) {
        for (int i = 0; i< OUt_cardNUmbew; i++) {
            _AnicardSprites[i]->removeAllChildrenWithCleanup(true);
            _AnicardSprites[i]->removeFromParentAndCleanup(true);
        }
    }
    
    OUt_cardNUmbew = 0;
    
}
///////////////////////////// 游戏动画回调函数 /////////////////////////////

// 洗牌动画回调函数
void GameAnimationLayer::dispatchCard_AnimationCallBack(){
    // 停止动画
    dispatchCard_sprite->stopAllActions();
    // 移除子项
    dispatchCard_sprite->removeAllChildrenWithCleanup(true);
    // 从父类中移除
    dispatchCard_sprite->removeFromParentAndCleanup(true);
}

//////////////////////////// 道具动画回调函数 ////////////////////////////

void GameAnimationLayer::AnimationCallBack(CCObject* pSender){
    CCSprite *sender = (CCSprite*)pSender;
    
    sender->stopAllActions();
    sender->removeFromParentAndCleanup(true);
}

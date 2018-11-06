//
//  GameAnimationLayer.h
//  XXDDZ
//  娓告垙鍔ㄧ敾鏁堟灉灞?//  Created by ChengLin on 13-10-31.
//
//

#ifndef __XXDDZ__GameAnimationLayer__
#define __XXDDZ__GameAnimationLayer__

#include "cocos2d.h"
#include "Property.h"

//USING_NS_CC;
using namespace cocos2d;
using namespace std;

#define AN_BOMB                     1
#define AN_PLANE                    2
#define AN_ROCKET                   3
#define AN_DISPATCH_CARD            4
#define PROPERTY_POT                100
#define AN_TEXT_CALLBANKER          40
#define AN_TEXT_NOTCALLBANKER       41
#define AN_TEXT_RODBANKER           50
#define AN_TEXT_NOTRODBANKER        51
#define AN_TEXT_DOUBLE              60
#define AN_TEXT_NOTDOUBLE           61
#define AN_TEXT_MISS_CARD          70
#define AN_TEXT_NOTOUTCARD          71
#define AN_TEXT_NOTCALL             80
#define AN_TEXT_YIFEN               81
#define AN_TEXT_ERFEN               82
#define AN_TEXT_SANFEN              83
#define AN_TEXT_READY               90

// 鍔ㄧ敾娑堟伅
struct GameAnimationMsg{
    int animationType;
};


class GameAnimationLayer :public CCLayer{
    
public:
    
    GameAnimationLayer();
    
    ~GameAnimationLayer();
    
    virtual bool init();
    
    // 鑾峰彇褰撳墠绫荤殑鍗曚緥
    static GameAnimationLayer* shareGameAnimation();
    // 娓呴櫎鍗曚緥瀵硅薄
    static void purgeShareGameAnimation(void);
    
    CREATE_FUNC(GameAnimationLayer);
private:
    // 鍦烘櫙澶у皬
    CCSize size;
    // 閬撳叿鍔ㄧ敾杩涘叆鏃堕暱
    float inTime;
    // 閬撳叿鍔ㄧ敾娑堝け鏃堕暱
    float outTime;
    CCSprite *_AnicardSprites[20];
    
    
    // 娲楃墝鍔ㄧ敾瀵硅薄
    CCSprite *dispatchCard_sprite;
    
    // 鍒ゆ柇瀹氭椂鍣ㄦ槸鍚﹀凡缁忓惎鍔?    
	bool timerIsRun;
    // 鍔ㄧ敾瀵瑰垪
    list<GameAnimationMsg> *msgList;
    
public:
    // 鎾斁鍔ㄧ敾
    void playAnimationByID(GameAnimationMsg &msg);
    // 鎾斁鍔ㄧ敾
    bool playAnimationByID(int animationType);
    
    bool outCard_Animation(BYTE cardNumbew , BYTE cardData[20] , CCPoint cardPoint[20]);
    
    void distoryoutcard_Animation();
    
private:
    // 瀹氭椂鍣ㄥ洖璋?    
	void timerCallBack();
    /////////// 娓告垙鍔ㄧ敾 ////////////
    // 鐐稿脊鍔ㄧ敾
    bool explosion_Animation();
    // 椋炴満鍔ㄧ敾
    bool plane_Animation();
    // 鐏鍔ㄧ敾
    bool rocket_Animation();
    // 娲楃墝鍔ㄧ敾
    bool dispatchCard_Animation();
    // 鏂囧瓧鍔ㄧ敾
    bool textTips_Animation(int position,int textType);
    
    
    /////////// 閬撳叿鍔ㄧ敾 ///////////
	//姹借溅绀肩墿
    bool car_Animation(int position);
	//鑷泲绀肩墿
    bool egg_Animation(int position);
	//榧撴帉绀肩墿
    bool clap_Animation(int position);
	//棣欏惢绀肩墿
    bool kiss_Animation(int position);
	//鍟ら厭绀肩墿
    bool beer_Animation(int position);
	//铔嬬硶绀肩墿
    bool cake_Animation(int position);
	//閽绘垝绀肩墿
    bool ring_Animation(int position);
	//鏆存墦绀肩墿
    bool beat_Animation(int position);
    //鐐稿脊绀肩墿
    bool bomb_Animation(int position);
	//棣欑儫绀肩墿
    bool smoke_Animation(int position);
	//鍒绀肩墿
    bool villa_Animation(int position);
	//鐮栧ご绀肩墿
    bool brick_Animation(int position);
	//椴滆姳绀肩墿
    bool flower_Animation(int position);
    
    //鍙戠墝鍔ㄧ敾
    
    
    
    
    // bool cardMOve_Animation( WORD cardCount ,BYTE _handCardsData[20]  , );
    
private:
    /////////// 娓告垙鍔ㄧ敾鍥炶皟鍑芥暟 ////////////
    
    
    
    
    // 娲楃墝鍔ㄧ敾鍥炶皟鍑芥暟
    void dispatchCard_AnimationCallBack();
    
    /////////// 閬撳叿鍔ㄧ敾鍥炶皟鍑芥暟 ///////////
    void AnimationCallBack(CCObject* pSender);
};

#endif /* defined(__XXDDZ__GameAnimationLayer__) */

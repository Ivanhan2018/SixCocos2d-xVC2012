//
//  GameMusicController.cpp
//  MyCocos2d
//
//  Created by ChengLin on 13-10-30.
//
//

#include "GameMusicController.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID //CC_PLATFORM_IOS //CC_PLATFORM_ANDROID//棰勭紪璇?鍒ゆ柇鏄惁鏄痑ndroid骞冲彴

// 鏄惁绂佺敤闊充箰
bool isMusicON = true;
// 鏄惁绂佺敤闊虫晥
bool isVoiceON = true;

static GameMusicController* s_pGameMusicController = NULL;

// 鑾峰彇褰撳墠绫荤殑鍗曚緥
GameMusicController* GameMusicController::sharedGameMusic(){
    if(! s_pGameMusicController){
        s_pGameMusicController = new GameMusicController();
    }
    return s_pGameMusicController;
}

GameMusicController::GameMusicController(void){
    s_pEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    // 缂撳瓨鑳屾櫙闊充箰
    preload();
    s_pEngine->setEffectsVolume(0.8);//璁剧疆闊虫晥澹伴煶
    
    s_pEngine->setBackgroundMusicVolume(0.3);//璁剧疆闊充箰澹伴煶
    
    // 鍒涘缓闊虫晥娑堟伅鍒楄〃
    musicList = new list<GameMusicMsg>();
    
    // 瀹氭椂鍣ㄥ紑鍚爣蹇?    timerIsRun = false;
}
// 娓呴櫎鍗曚緥瀵硅薄
void GameMusicController::purgeShareGameMusic(void){
    CC_SAFE_RELEASE_NULL(s_pGameMusicController);
}
// 璧勬簮缂撳瓨
void GameMusicController::preload(){
    s_pEngine->preloadBackgroundMusic(VO_BACKGROUND);
    s_pEngine->preloadEffect("BANKERINFO.mp3");
    s_pEngine->preloadEffect("COUNT_WARN.mp3");
    s_pEngine->preloadEffect("GAME_WARN.mp3");
    s_pEngine->preloadEffect("REVERSAL_CARD.mp3");
    s_pEngine->preloadEffect("DISPATCH_CARD.mp3");
    s_pEngine->preloadEffect("BOMB.mp3");
    s_pEngine->preloadEffect("PLANE.mp3");
    s_pEngine->preloadEffect("CONCLUDE.mp3");
    s_pEngine->preloadEffect("GAME_START.mp3");
    s_pEngine->preloadEffect("GAME_LOSE.mp3");
    s_pEngine->preloadEffect("GAME_WIN.mp3");
    s_pEngine->preloadEffect("BOMB_CARD_BOY.mp3");
    s_pEngine->preloadEffect("DOUBLE_LINE_BOY.mp3");
    s_pEngine->preloadEffect("DOUBLE_BOY.mp3");
    s_pEngine->preloadEffect("FOUR_TAKE_ONE_BOY.mp3");
    s_pEngine->preloadEffect("FOUR_TAKE_TWO_BOY.mp3");
    s_pEngine->preloadEffect("MISSILE_CARD_BOY.mp3");
    s_pEngine->preloadEffect("OUT_CARD_BOY.mp3");
    s_pEngine->preloadEffect("PASS_CARD_BOY.mp3");
    s_pEngine->preloadEffect("SCORE_1_BOY.mp3");
    s_pEngine->preloadEffect("SCORE_2_BOY.mp3");
    s_pEngine->preloadEffect("SCORE_3_BOY.mp3");
    s_pEngine->preloadEffect("SCORE_NONE_BOY.mp3");
    s_pEngine->preloadEffect("SINGLE_LINE_BOY.mp3");
    s_pEngine->preloadEffect("THREE_LINE_BOY.mp3");
    s_pEngine->preloadEffect("THREE_ONE_LINE_BOY.mp3");
    s_pEngine->preloadEffect("THREE_TAKE_ONE_BOY.mp3");
    s_pEngine->preloadEffect("THREE_TAKE_TWO_BOY.mp3");
    s_pEngine->preloadEffect("THREE_BOY.mp3");
    s_pEngine->preloadEffect("BOMB_CARD_GIRL.mp3");
    s_pEngine->preloadEffect("DOUBLE_LINE_GIRL.mp3");
    s_pEngine->preloadEffect("DOUBLE_GIRL.mp3");
    s_pEngine->preloadEffect("FOUR_TAKE_ONE_GIRL.mp3");
    s_pEngine->preloadEffect("FOUR_TAKE_TWO_GIRL.mp3");
    s_pEngine->preloadEffect("MISSILE_CARD_GIRL.mp3");
    s_pEngine->preloadEffect("OUT_CARD_GIRL.mp3");
    s_pEngine->preloadEffect("PASS_CARD_GIRL.mp3");
    s_pEngine->preloadEffect("SCORE_1_GIRL.mp3");
    s_pEngine->preloadEffect("SCORE_2_GIRL.mp3");
    s_pEngine->preloadEffect("SCORE_3_GIRL.mp3");
    s_pEngine->preloadEffect("SCORE_NONE_GIRL.mp3");
    s_pEngine->preloadEffect("THREE_LINE_GIRL.mp3");
    s_pEngine->preloadEffect("THREE_ONE_LINE_GIRL.mp3");
    s_pEngine->preloadEffect("THREE_TAKE_ONE_GIRL.mp3");
    s_pEngine->preloadEffect("THREE_TAKE_TWO_GIRL.mp3");
    s_pEngine->preloadEffect("THREE_GIRL.mp3");
    
    s_pEngine->preloadEffect("CALLBANKER_BOY.mp3");
    s_pEngine->preloadEffect("NOTCALLBANKER_BOY.mp3");
    s_pEngine->preloadEffect("RODBANKER_BOY.mp3");
    s_pEngine->preloadEffect("CALLBANKER_BOY.mp3");
    s_pEngine->preloadEffect("CALLDOUBLE_BOY.mp3");
    s_pEngine->preloadEffect("NOTCALLDOUBLE_BOY.mp3");
    
    s_pEngine->preloadEffect("CALLBANKER_GIRL.mp3");
    s_pEngine->preloadEffect("NOTCALLBANKER_GIRL.mp3");
    s_pEngine->preloadEffect("RODBANKER_GIRL.mp3");
    s_pEngine->preloadEffect("CALLBANKER_GIRL.mp3");
    s_pEngine->preloadEffect("CALLDOUBLE_GIRL.mp3");
    s_pEngine->preloadEffect("NOTCALLDOUBLE_GIRL.mp3");
    
    
    for (int i = 1; i <16; i++) {
        char asd[50];
        snprintf(asd, 50, "SINGLE_BOY_%d.mp3",i);
        s_pEngine->preloadEffect(asd);
    }
    
    for (int i = 1; i <16; i++) {
        char asd[50];
        snprintf(asd, 50, "SINGLE_GIRL_%d.mp3",i);
        s_pEngine->preloadEffect(asd);
    }
    
}

GameMusicController::~GameMusicController(void){
    
}

////////////// 闊虫晥闊充箰鍏ㄥ眬鎺у埗 //////////
// 璁剧疆绂佺敤闊充箰
bool GameMusicController::setMusic(bool on){
    isMusicON = on;
    if(on){// 寮€鍚煶涔?        playBackgroundMusic();
    }else{// 鍏抽棴闊充箰
        stopBackgroundMusic();
    }
    return true;
}

// 璁剧疆绂佺敤闊虫晥
bool GameMusicController::setVoice(bool on){
    isVoiceON = on;
    if(!on){// 鍏抽棴闊虫晥
        stopAllEffects();
    }
    return true;
}

// 鏌ヨ绂佺敤鐘舵€?void GameMusicController::getMusicAndVoiceState(bool &onMusic,bool &onVoice){
    onMusic = isMusicON;
    onVoice = isVoiceON;
};

// 绂佺敤闊充箰鍜岄煶鏁?bool GameMusicController::setMusicAndVoice(bool onMusice,bool onVoice){
    return setMusic(onMusice) && setVoice(onVoice);
}

// 鎻愬墠璁剧疆闊充箰鍜岄煶鏁?bool GameMusicController::setMusicAndVoiceAdvance(bool onMusice,bool onVoice){
    isMusicON = onMusice;
    isVoiceON = onVoice;
    return true;
}

////////////// 鑳屾櫙闊充箰鎺у埗 ////////////
// 鎾斁鑳屾櫙闊充箰
void GameMusicController::playBackgroundMusic(){
    // 鍒ゆ柇闊充箰鏄惁绂佺敤
    if(!isMusicON) return;
    // 鍒ゆ柇鑳屾櫙闊充箰鏄惁姝ｅ湪鎾彂
    if(s_pEngine->isBackgroundMusicPlaying()){
        s_pEngine->stopBackgroundMusic();
    }
    s_pEngine->playBackgroundMusic(VO_BACKGROUND, true);
}

// 鍋滄鑳屾櫙闊充箰
void GameMusicController::stopBackgroundMusic(){
    s_pEngine->stopBackgroundMusic();
}

// 鏆傚仠鑳屾櫙闊充箰
void GameMusicController::pauseBackgroundMusic(){
    s_pEngine->pauseBackgroundMusic();
}

// 缁х画鎾斁鑳屾櫙闊充箰
void GameMusicController::resumeBackgroundMusic(){
    s_pEngine->resumeBackgroundMusic();
}

////////////// 闊虫晥鎺у埗 ////////////////
// 鍋滄闊虫晥
void GameMusicController::stopEffectByID(int nSoundId){
    s_pEngine->stopEffect(nSoundId);
}

// 鍋滄鎵€鏈夐煶鏁?void GameMusicController::stopAllEffects(){
    
    s_pEngine->stopAllEffects();
}

// 鎾斁闊虫晥
void GameMusicController::playEffect(GameMusicMsg &msg){
    if(!musicList) return;
    // 灏嗘秷鎭坊鍔犲埌鍒楄〃涓?    musicList ->push_back(msg);
    // 鍒ゆ柇瀹氭椂鍣ㄦ槸鍚﹀紑鍚?    if(!timerIsRun){
        this->schedule(schedule_selector(GameMusicController::timerCallBack),0.1);
        // 璁剧疆瀹氭椂鍣ㄥ惎鍔ㄦ爣蹇楋紙寮€鍚級
        timerIsRun = true;
    }
}

// 瀹氭椂鍣ㄥ洖璋冨嚱鏁?void GameMusicController::timerCallBack(){
    if(musicList->empty()){
        // 鍋滄瀹氭椂鍣?        this->unschedule(schedule_selector(GameMusicController::timerCallBack));
        // 璁剧疆瀹氭椂鍣ㄥ惎鍔ㄦ爣蹇楋紙鍏抽棴锛?        timerIsRun = false;
    }else{
        if(musicList->front().distinguishSex){ // 鍖哄垎鎬у埆
            // 鍒ゆ柇鏄笉鏄崟寮犵被鍨?            if(musicList->front().musicType > 1000){
                this->playEffectSigleCard(musicList->front().sexType,musicList->front().musicType);
            }else{
                this->playEffect(musicList->front().sexType,musicList->front().musicType);
            }
        }else{ // 涓嶅尯鍒?            this->playEffect(musicList->front().musicType);
        }
        // 绉婚櫎鍒楄〃涓殑鏁版嵁
        musicList->pop_front();
    }
}

// 閫氱敤闊虫晥
int GameMusicController::playEffect(int effectType,bool bLoop){
    // 鍒ゆ柇鏄惁绂佺敤闊虫晥
    if(!isVoiceON) return 0;
    
    
    switch(effectType){
            // 閫氱敤闊虫晥瀹氫箟
        case VO_GL_BANKERINFO:
            s_pEngine->playEffect("BANKERINFO.mp3",bLoop);
            break;
        case VO_GL_COUNT_WARN:
            s_pEngine->playEffect("COUNT_WARN.mp3",bLoop);
            break;
        case VO_GL_GAME_WARN:
            s_pEngine->playEffect("GAME_WARN.mp3",bLoop);
            break;
        case VO_GL_REVERSAL_CARD:
            s_pEngine->playEffect("REVERSAL_CARD.mp3",bLoop);
            break;
        case VO_GL_DISPATCH_CARD:
            s_pEngine->playEffect("DISPATCH_CARD.mp3",bLoop);
            break;
        case VO_GL_BOMB:
            s_pEngine->playEffect("BOMB.mp3",bLoop);
            break;
        case VO_GL_PLANE:
            s_pEngine->playEffect("PLANE.mp3",bLoop);
            break;
        case VO_GL_CONCLUDE:
            s_pEngine->playEffect("CONCLUDE.mp3",bLoop);
            break;
        case VO_GL_GAME_START:
            s_pEngine->playEffect("GAME_START.mp3",bLoop);
            break;
        case VO_GL_GAME_LOSE:
            s_pEngine->playEffect("GAME_LOSE.mp3",bLoop);
            break;
        case VO_GL_GAME_WIN:
            s_pEngine->playEffect("GAME_WIN.mp3",bLoop);
            break;
        case VO_GL_STOPALL:
        {
            stopAllEffects();
            break;
        }
        default:
            CCLog("娌℃湁瀵瑰簲鐨勯煶鏁堬紒");
            break;
    }
    
    return 1;
}

// 鍖哄垎鎬у埆闊虫晥
int GameMusicController::playEffect(bool sexType,int effectType,bool bLoop){
    // 鍒ゆ柇鏄惁绂佺敤闊虫晥
    if(!isVoiceON) return 0;
    
    if(sexType){
        switch (effectType) {
            case VO_BOMB_CARD:
                s_pEngine->playEffect("BOMB_CARD_BOY.mp3",bLoop);
                break;
            case VO_DOUBLE_LINE:
                s_pEngine->playEffect("DOUBLE_LINE_BOY.mp3",bLoop);
                break;
            case VO_DOUBLE:
                s_pEngine->playEffect("DOUBLE_BOY.mp3",bLoop);
                break;
            case VO_FOUR_TAKE_ONE:
                s_pEngine->playEffect("FOUR_TAKE_ONE_BOY.mp3",bLoop);
                break;
            case VO_FOUR_TAKE_TWO:
                s_pEngine->playEffect("FOUR_TAKE_TWO_BOY.mp3",bLoop);
                break;
            case VO_MISSILE_CARD:
                s_pEngine->playEffect("MISSILE_CARD_BOY.mp3",bLoop);
                break;
            case VO_OUT_CARD:
                s_pEngine->playEffect("OUT_CARD_BOY.mp3",bLoop);
                break;
            case VO_PASS_CARD:
                s_pEngine->playEffect("PASS_CARD_BOY.mp3",bLoop);
                break;
            case VO_SCORE_1:
                s_pEngine->playEffect("SCORE_1_BOY.mp3",bLoop);
                break;
            case VO_SCORE_2:
                s_pEngine->playEffect("SCORE_2_BOY.mp3",bLoop);
                break;
            case VO_SCORE_3:
                s_pEngine->playEffect("SCORE_3_BOY.mp3",bLoop);
                break;
            case VO_SCORE_NONE:
                s_pEngine->playEffect("SCORE_NONE_BOY.mp3",bLoop);
                break;
            case VO_SINGLE_LINE:
                s_pEngine->playEffect("SINGLE_LINE_BOY.mp3",bLoop);
                break;
            case VO_THREE_LINE:
                s_pEngine->playEffect("THREE_LINE_BOY.mp3",bLoop);
                break;
            case VO_THREE_ONE_LINE:
                s_pEngine->playEffect("THREE_ONE_LINE_BOY.mp3",bLoop);
                break;
            case VO_THREE_TAKE_ONE:
                s_pEngine->playEffect("THREE_TAKE_ONE_BOY.mp3",bLoop);
                break;
            case VO_THREE_TAKE_TWO:
                s_pEngine->playEffect("THREE_TAKE_TWO_BOY.mp3",bLoop);
                break;
            case VO_THREE_TAKE_THREE:
                s_pEngine->playEffect("THREE_BOY.mp3",bLoop);
                break;
            case VO_CALLBANKER:
                s_pEngine->playEffect("CALLBANKER_BOY.mp3",bLoop);
                break;
            case VO_NOTCALLBANKER:
                s_pEngine->playEffect("NOTCALLBANKER_BOY.mp3",bLoop);
                break;
            case VO_RODBANKER:
                s_pEngine->playEffect("RODBANKER_BOY.mp3",bLoop);
                break;
            case VO_NOTRODBANKER:
#pragma mark (鏈疄鐜? 缂哄皯涓嶆灙鍦颁富闊虫晥                
               
                s_pEngine->playEffect("SCORE_NONE_BOY.mp3",bLoop);
                break;
            case VO_CALLDOUBLE:
                s_pEngine->playEffect("CALLDOUBLE_BOY.mp3",bLoop);
                break;
            case VO_NOTCALLDOUBLE:
                s_pEngine->playEffect("NOTCALLDOUBLE_BOY.mp3",bLoop);
                break;
            default:
                CCLog("娌℃湁瀵瑰簲鐨勯煶鏁堬紒%d", effectType);
                break;
        }
    }else{
        switch (effectType) {
            case VO_BOMB_CARD:
                s_pEngine->playEffect("BOMB_CARD_GIRL.mp3",bLoop);
                break;
            case VO_DOUBLE_LINE:
                s_pEngine->playEffect("DOUBLE_LINE_GIRL.mp3",bLoop);
                break;
            case VO_DOUBLE:
                s_pEngine->playEffect("DOUBLE_GIRL.mp3",bLoop);
                break;
            case VO_FOUR_TAKE_ONE:
                s_pEngine->playEffect("FOUR_TAKE_ONE_GIRL.mp3",bLoop);
                break;
            case VO_FOUR_TAKE_TWO:
                s_pEngine->playEffect("FOUR_TAKE_TWO_GIRL.mp3",bLoop);
                break;
            case VO_MISSILE_CARD:
                s_pEngine->playEffect("MISSILE_CARD_GIRL.mp3",bLoop);
                break;
            case VO_OUT_CARD:
                s_pEngine->playEffect("OUT_CARD_GIRL.mp3",bLoop);
                break;
            case VO_PASS_CARD:
                s_pEngine->playEffect("PASS_CARD_GIRL.mp3",bLoop);
                break;
            case VO_SCORE_1:
                s_pEngine->playEffect("SCORE_1_GIRL.mp3",bLoop);
                break;
            case VO_SCORE_2:
                s_pEngine->playEffect("SCORE_2_GIRL.mp3",bLoop);
                break;
            case VO_SCORE_3:
                s_pEngine->playEffect("SCORE_3_GIRL.mp3",bLoop);
                break;
            case VO_SCORE_NONE:
                s_pEngine->playEffect("SCORE_NONE_GIRL.mp3",bLoop);
                break;
            case VO_SINGLE_LINE:
                s_pEngine->playEffect("SINGLE_LINE_GIRL.mp3",bLoop);
                break;
            case VO_THREE_LINE:
                s_pEngine->playEffect("THREE_LINE_GIRL.mp3",bLoop);
                break;
            case VO_THREE_ONE_LINE:
                s_pEngine->playEffect("THREE_ONE_LINE_GIRL.mp3",bLoop);
                break;
            case VO_THREE_TAKE_ONE:
                s_pEngine->playEffect("THREE_TAKE_ONE_GIRL.mp3",bLoop);
                break;
            case VO_THREE_TAKE_TWO:
                s_pEngine->playEffect("THREE_TAKE_TWO_GIRL.mp3",bLoop);
                break;
            case VO_THREE_TAKE_THREE:
                s_pEngine->playEffect("THREE_GIRL.mp3",bLoop);
                break;
            case VO_CALLBANKER:
                s_pEngine->playEffect("CALLBANKER_GIRL.mp3",bLoop);
                break;
            case VO_NOTCALLBANKER:
                s_pEngine->playEffect("NOTCALLBANKER_GIRL.mp3",bLoop);
                break;
            case VO_RODBANKER:
                s_pEngine->playEffect("RODBANKER_GIRL.mp3",bLoop);
                break;
            case VO_NOTRODBANKER:
#pragma mark (鏈疄鐜? 缂哄皯涓嶆灙鍦颁富闊虫晥
                CCLog("缂哄皯涓嶆灙鍦颁富闊虫晥锛?);
                s_pEngine->playEffect("SCORE_NONE_GIRL.mp3",bLoop);
                break;
            case VO_CALLDOUBLE:
                s_pEngine->playEffect("CALLDOUBLE_GIRL.mp3",bLoop);
                break;
            case VO_NOTCALLDOUBLE:
                s_pEngine->playEffect("NOTCALLDOUBLE_GIRL.mp3",bLoop);
                break;
            default:
                CCLog("娌℃湁瀵瑰簲鐨勯煶鏁堬紒%d", effectType);
                break;
        }
    }
    
    return 1;
}

// 鍖哄垎鎬у埆闊虫晥(鎾斁鍗曞紶鐨勭墝)
int GameMusicController::playEffectSigleCard(bool sexType,int effectType,bool bLoop){
    // 鍒ゆ柇鏄惁绂佺敤闊虫晥
    if(!isVoiceON) return 0;
    // 璁＄畻鐗屽€?    int cardValue = effectType - VO_SINGLE_BASE;
    // 鏍￠獙鐗屽€?    if(cardValue < 1 || cardValue > 15) return 0;
    CCLog("cardValue = %d",cardValue);
    // 鑾峰彇璧勬簮
    char asd[50];
    
    if(sexType){ // 鐢?        snprintf(asd, 50, "SINGLE_BOY_%d.mp3",cardValue);
        s_pEngine->playEffect(asd,bLoop);
    }else{ // 濂?        snprintf(asd, 50, "SINGLE_GIRL_%d.mp3",cardValue);
        s_pEngine->playEffect(asd,bLoop);
    }
    return 1;
}

// 鐢ㄦ埛鍔犲€?void GameMusicController::playUserCallDouble(bool sexType,bool isDouble){
    // 鍒涘缓闊虫晥娑堟伅
    GameMusicMsg musicMsg;
    memset(&musicMsg, 0, sizeof(GameMusicMsg));
    musicMsg.distinguishSex = true;
    musicMsg.sexType = sexType;
    // 璁剧疆闊虫晥绫诲瀷
    if(isDouble){// 鍔犲€?        musicMsg.musicType = VO_CALLDOUBLE;
    }else{// 涓嶅姞鍊?        musicMsg.musicType = VO_NOTCALLDOUBLE;
    }
    // 鎾斁闊虫晥
    this->playEffect(musicMsg);
}

// 鐢ㄦ埛鍙湴涓?void GameMusicController::playUserCallBanker(bool sexType,BYTE cbCallInfo){
    // 鍒涘缓闊虫晥娑堟伅
    GameMusicMsg musicMsg;
    memset(&musicMsg, 0, sizeof(GameMusicMsg));
    musicMsg.distinguishSex = true;
    musicMsg.sexType = sexType;
    
    if(cbCallInfo == HLDDZ_CB_CALL_BENKER){// 鍙湴涓?        musicMsg.musicType = VO_CALLBANKER;
    }else if(cbCallInfo == HLDDZ_CB_NO_CALL_BENKER){ // 涓嶅彨鍦颁富
        musicMsg.musicType = VO_NOTCALLBANKER;
    }else{
        return;
    }
    // 鎾斁闊虫晥
    this->playEffect(musicMsg);
}

// 鐢ㄦ埛鎶㈠湴涓?void GameMusicController::playUserRodBanker(bool sexType,BYTE cbCallInfo){
    // 鍒涘缓闊虫晥娑堟伅
    GameMusicMsg musicMsg;
    memset(&musicMsg, 0, sizeof(GameMusicMsg));
    musicMsg.distinguishSex = true;
    musicMsg.sexType = sexType;
    
    // 鍒ゆ柇鏃舵姠鍦颁富杩樻椂鍙湴涓?    if(cbCallInfo == HLDDZ_CB_ROD_BANKER){// 鎶㈠湴涓?        musicMsg.musicType = VO_RODBANKER;
    }else if(cbCallInfo == HLDDZ_CB_NO_ROD_BANKER){// 涓嶆姠鍦颁富
        musicMsg.musicType = VO_NOTRODBANKER;
    }else{
        return;
    }
    // 鎾斁闊虫晥
    this->playEffect(musicMsg);
}

// 鐢ㄦ埛鍙垎
void GameMusicController::playUserCallScore(bool sexType,BYTE callScore){
    // 鍒涘缓闊虫晥娑堟伅
    GameMusicMsg musicMsg;
    memset(&musicMsg, 0, sizeof(GameMusicMsg));
    musicMsg.distinguishSex = true;
    musicMsg.sexType = sexType;
    // 璁剧疆闊虫晥绫诲瀷
    switch(callScore){
        case 0: // 涓嶅彨
            musicMsg.musicType = VO_SCORE_NONE;
            break;
        case 1: // 涓€鍒?            musicMsg.musicType = VO_SCORE_1;
            break;
        case 2: // 浜屽垎
            musicMsg.musicType = VO_SCORE_2;
            break;
        case 3: // 涓夊垎
            musicMsg.musicType = VO_SCORE_3;
            break;
    }
    // 鎾斁闊虫晥
    this->playEffect(musicMsg);
}

// 閫氳繃鍑虹殑鐗屾挱鏀句笉鍚岀殑闊虫晥
void GameMusicController::playOutCardEffect(bool sexType,BYTE cbCardCount,BYTE cbCardData[MAX_COUNT]){
    // 鍒ゆ柇鐗岀殑绫诲瀷
    CGameLogic gameLogic;
    BYTE outCardType = gameLogic.GetCardType(cbCardData, cbCardCount);
    // 鍒ゆ柇鐗屽瀷鏄惁姝ｇ‘
    if(outCardType==0) return;
    // 鏇村叿涓嶅悓鐨勭墝鍨嬫挱鏀鹃煶鏁?    switch(outCardType){
            // 椋炴満
        case CT_THREE_LINE:
        {
            if(cbCardCount >= 6){
                // 璋冪敤椋炴満闊虫晥
                GameMusicMsg musicMsg;
                memset(&musicMsg, 0, sizeof(GameMusicMsg));
                musicMsg.distinguishSex = true;
                musicMsg.musicType = VO_THREE_ONE_LINE;
                this->playEffect(musicMsg);
            }else{
                GameMusicMsg musicMsg;
                memset(&musicMsg, 0, sizeof(GameMusicMsg));
                musicMsg.distinguishSex = true;
                musicMsg.musicType = VO_OUT_BASE + CT_THREE_LINE;
                this->playEffect(musicMsg);
            }
        }
            break;
        case CT_THREE_TAKE_ONE:
        {
            if(cbCardCount >= 6){
                // 璋冪敤椋炴満闊虫晥
                GameMusicMsg musicMsg;
                memset(&musicMsg, 0, sizeof(GameMusicMsg));
                musicMsg.distinguishSex = true;
                musicMsg.musicType = VO_THREE_ONE_LINE;
                this->playEffect(musicMsg);
            }else{
                GameMusicMsg musicMsg;
                memset(&musicMsg, 0, sizeof(GameMusicMsg));
                musicMsg.distinguishSex = true;
                musicMsg.musicType = VO_OUT_BASE + CT_THREE_TAKE_ONE;
                this->playEffect(musicMsg);
            }
        }
            break;
        case CT_THREE_TAKE_TWO:
        {
            if(cbCardCount >= 6){
                // 璋冪敤椋炴満闊虫晥
                GameMusicMsg musicMsg;
                memset(&musicMsg, 0, sizeof(GameMusicMsg));
                musicMsg.distinguishSex = true;
                musicMsg.musicType = VO_THREE_ONE_LINE;
                this->playEffect(musicMsg);
            }else{
                GameMusicMsg musicMsg;
                memset(&musicMsg, 0, sizeof(GameMusicMsg));
                musicMsg.distinguishSex = true;
                musicMsg.musicType = VO_OUT_BASE + CT_THREE_TAKE_TWO;
                this->playEffect(musicMsg);
            }
        }
            break;
        case CT_SINGLE: // 鍗曟帓绫诲瀷
        {
            // 鍒涘缓闊虫晥娑堟伅
            GameMusicMsg musicMsg;
            memset(&musicMsg, 0, sizeof(GameMusicMsg));
            musicMsg.distinguishSex = true;
            musicMsg.sexType = sexType;
            musicMsg.musicType = VO_SINGLE_BASE + gameLogic.GetCardValue(cbCardData[0]);
            this->playEffect(musicMsg);
        }
            break;
        default:
        {
            // 鍒涘缓闊虫晥娑堟伅
            GameMusicMsg musicMsg;
            memset(&musicMsg, 0, sizeof(GameMusicMsg));
            musicMsg.distinguishSex = true;
            musicMsg.sexType = sexType;
            musicMsg.musicType = VO_OUT_BASE + outCardType;
            this->playEffect(musicMsg);
        }
            break;
    }
}

// 鎾斁缁撴潫闊虫晥
void GameMusicController::playGameEndEffect(bool isWin){
    // 鍒涘缓闊虫晥娑堟伅
    GameMusicMsg musicMsg;
    memset(&musicMsg, 0, sizeof(GameMusicMsg));
    musicMsg.distinguishSex = false;
    // 璁剧疆闊虫晥绫诲瀷
    if(isWin){
        musicMsg.musicType = VO_GL_GAME_WIN;
    }else{
        musicMsg.musicType = VO_GL_GAME_LOSE;
    }
    // 鎾斁
    playEffect(musicMsg);
}


void GameMusicController::PlaycommonEffect(bool iswarning){
    
    GameMusicMsg musicMsg;
    memset(&musicMsg, 0, sizeof(GameMusicMsg));
    musicMsg.distinguishSex = false;
    // 璁剧疆闊虫晥绫诲瀷
    if(iswarning){
        musicMsg.musicType = VO_GL_GAME_WARN;
    }else{
        musicMsg.musicType = VO_GL_GAME_WARN;
    }
    // 鎾斁
    playEffect(musicMsg);
}

#endif


//
//  GameMusicController.h
//  娓告垙闊虫晥鎺у埗绫?//  Created by ChengLin on 13-10-30.
//
//

#ifndef __MyCocos2d__GameMusicController__
#define __MyCocos2d__GameMusicController__

#include "cocos2d.h"
#include "Packet.h"
#include "GameLogic.h"
#include "CMD_Game.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

// 鑳屾櫙闊充箰
#define VO_BACKGROUND                       "BACK_MUSIC.mp3"            // 鑳屾櫙闊充箰

// 閫氱敤闊虫晥瀹氫箟
#define VO_GL_BANKERINFO					100							// 閾惰淇℃伅
#define VO_GL_COUNT_WARN                    101							// 鍓╀綑寮犳暟璀﹀憡
#define VO_GL_GAME_WARN                     102							// 鍊掕鏃惰鍛?
#define VO_GL_REVERSAL_CARD                 103							// 娲楃墝
#define VO_GL_DISPATCH_CARD                 104							// 鍙戠墝
#define VO_GL_BOMB                          105							// 鐐稿脊
#define VO_GL_PLANE                         106							// 椋炴満
#define VO_GL_CONCLUDE                      107							// 鏂畾
#define VO_GL_GAME_START                    108							// 娓告垙寮€濮?
#define VO_GL_GAME_LOSE                     109							// 杈?
#define VO_GL_GAME_WIN                      110							// 璧?
#define VO_GL_STOPALL                       111                         // 鍋滄鎵€鏈夐煶鏁?
// 娓告垙闊虫晥

#define VO_OUT_BASE                         200                         // 鍑虹墝鍛戒护鐨勫熀鏁?
#define VO_OUT_CARD                         201							// 鍗曠墝绫诲瀷
#define VO_SINGLE_BASE                      1000                        // 鍗曠墝鐨勫熀鏁?
#define VO_DOUBLE                           202							// 涓€瀵?
#define VO_THREE_TAKE_THREE                 203							// 涓夊紶
#define VO_SINGLE_LINE                      204							// 鍗曢『
#define VO_DOUBLE_LINE                      205							// 鍙岄『
#define VO_THREE_LINE                       206							// 涓夐『
#define VO_THREE_TAKE_ONE                   207							// 涓夊甫涓€
#define VO_THREE_TAKE_TWO                   208							// 涓夊甫涓€瀵?
#define VO_FOUR_TAKE_ONE                    209							// 鍥涘甫浜?
#define VO_FOUR_TAKE_TWO                    210							// 鍥涘甫浜屽
#define VO_BOMB_CARD                        211							// 鐐稿脊
#define VO_MISSILE_CARD                     212							// 鐜嬬偢
#define VO_THREE_ONE_LINE                   213							// 椋炴満(鐗规畩)

#define VO_PASS_CARD                        314							// 杩囷紙涓嶅嚭锛?
#define VO_SCORE_1                          315							// 1鍒?
#define VO_SCORE_2                          316							// 2鍒?
#define VO_SCORE_3                          317							// 3鍒?
#define VO_SCORE_NONE                       318							// 涓嶅彨

#define VO_CALLBANKER                       319                         // 鍙湴涓?
#define VO_NOTCALLBANKER                    320                         // 涓嶅彨鍦颁富

#define VO_RODBANKER                        321                         // 鎶㈠湴涓?
#define VO_NOTRODBANKER                     322                         // 涓嶆姠鍦颁富

#define VO_CALLDOUBLE                       323                         // 鍔犲€?
#define VO_NOTCALLDOUBLE                    324                         // 涓嶅姞鍊?

// 闊虫晥娑堟伅
struct GameMusicMsg{
    bool distinguishSex;            // 鏄惁鍖哄垎鎬у埆
    bool sexType;                   // 鎬у埆
    int musicType;                  // 闊虫晥绫诲瀷
};

class GameMusicController:public CCNode{
    
public:
    GameMusicController(void);
    ~GameMusicController(void);
    // 鑾峰彇褰撳墠绫荤殑鍗曚緥
    static GameMusicController* sharedGameMusic(void);
    // 娓呴櫎鍗曚緥瀵硅薄
    static void purgeShareGameMusic(void);
    // 璧勬簮缂撳瓨
    void preload();
    
private:
    // 澹伴煶寮曟搸
    SimpleAudioEngine *s_pEngine;
    // 闊虫晥娑堟伅鍒楄〃
    list<GameMusicMsg> *musicList;
    // 瀹氭椂鍣ㄦ槸鍚﹀紑鍚殑鏍囧織
    bool timerIsRun;
private:
    // 瀹氭椂鍣ㄥ洖璋冨嚱鏁?    
	void timerCallBack();
    
public:
    ////////////// 闊虫晥闊充箰鍏ㄥ眬鎺у埗 //////////
    // 璁剧疆绂佺敤闊充箰
    bool setMusic(bool on);
    // 璁剧疆绂佺敤闊虫晥
    bool setVoice(bool on);
    // 鏌ヨ绂佺敤鐘舵€?    
	static void getMusicAndVoiceState(bool &onMusic,bool &onVoice);
    // 鎻愬墠璁剧疆闊充箰鍜岄煶鏁?    
	static bool setMusicAndVoiceAdvance(bool onMusice,bool onVoice);
    // 璁剧疆闊充箰鍜岄煶鏁?    
	bool setMusicAndVoice(bool onMusice,bool onVoice);
    ////////////// 鑳屾櫙闊充箰鎺у埗 /////////////
    // 鎾斁鑳屾櫙闊充箰
    void playBackgroundMusic(void);
    // 鍋滄鑳屾櫙闊充箰
    void stopBackgroundMusic(void);
    // 鏆傚仠鑳屾櫙闊充箰
    void pauseBackgroundMusic(void);
    // 缁х画鎾斁鑳屾櫙闊充箰
    void resumeBackgroundMusic(void);
    
    ////////////// 闊虫晥鎺у埗 ////////////////
    // 鍋滄瀵瑰簲ID鐨勯煶鏁?    
	void stopEffectByID(int nSoundId);
    // 鍋滄鎵€鏈夐煶鏁?    
	void stopAllEffects(void);
    // 鎾斁闊虫晥
    void playEffect(GameMusicMsg &msg);
    // 閫氱敤闊虫晥
    int playEffect(int effectType,bool bLoop = false);
    // 鍖哄垎鎬у埆闊虫晥
    int playEffect(bool sexType,int effectType,bool bLoop = false);
    // 鍖哄垎鎬у埆闊虫晥(鎾斁鍗曞紶鐨勭墝)
    int playEffectSigleCard(bool sexType,int effectType,bool bLoop = false);
    
public:
    // 鐢ㄦ埛鍙湴涓?    
	void playUserCallBanker(bool sexType,BYTE cbCallInfo);
    // 鐢ㄦ埛鎶㈠湴涓?    
	void playUserRodBanker(bool sexType,BYTE cbCallInfo);
    // 鐢ㄦ埛鍙垎
    void playUserCallScore(bool sexType,BYTE cbDoubleScore);
    // 鐢ㄦ埛鍔犲€?    
	void playUserCallDouble(bool sexType,bool isDouble);
    // 閫氳繃鍑虹殑鐗屾挱鏀句笉鍚岀殑闊虫晥
    void playOutCardEffect(bool sexType,BYTE cbCardCount,BYTE cbCardData[MAX_COUNT]);
    // 鎾斁缁撴潫闊虫晥
    void playGameEndEffect(bool isWin);
    //閫氱敤闊虫晥
    void PlaycommonEffect(bool iswarning);
    
};

#endif /* defined(__MyCocos2d__GameMusicController__) */

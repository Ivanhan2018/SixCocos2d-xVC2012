//
//  cocosUnits.h
//  Game
//
//  Created by 罗敏 on 13-6-19.
//
//

#ifndef Game_CocosUnits_h
#define Game_CocosUnits_h
#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

inline  CCSpriteFrame* spriteFrame(std::string name)
{
	// 判断图片是否存在
    
	// 不存在 读取一张红色图片代替，并log不存在
    
	CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name.c_str());
	if (pFrame)
	{
		return pFrame;
	}
	CCSprite* sprite  = CCSprite::create(name.c_str());
	return sprite->displayFrame();
    //return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("all_error.png");
}

inline  void playButtonSound()
{
	bool hasEffect = CCUserDefault::sharedUserDefault()->getBoolForKey("hasEffect", true);
    if(hasEffect)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/button.mp3",false);
    }
}

inline unsigned int playSound(const char* str,bool isloop)
{
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("hasEffect", true))
    {
        return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(str, isloop);
    }
    else
    {
        return NULL;
    }
}

inline void stopSound(unsigned int ids)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(ids);
}

inline void playBGM(const char *str)
{
    if(str)
    {
        if(CCUserDefault::sharedUserDefault()->getBoolForKey("hasMusic"))
        {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(str,true);
        }
    }
}

inline void pauseBGM()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

inline void resumeBGM(const char* str)
{
    if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(str, true);
    }
}

inline void stopBGM()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

inline std::string addCommaToNumber(long number)
{
    if(number == 0)
    {
        return "0";
    }
    char t[256];
    std::string oldNumber;
    sprintf(t, "%ld",number);
    oldNumber = t;
    std::ostringstream newNumberString;
    bool isIntNumber = true;
    int Dot_Position = 0;
    for (int i =0; i < oldNumber.length(); i++)
    {
        std::ostringstream oldNumberChar;
        oldNumberChar<<oldNumber.at(i);
        if(strcmp(oldNumberChar.str().c_str(), ".") == 0)
        {
            isIntNumber = false;
            Dot_Position = i;
        }
    }
    if(isIntNumber == true)
    {
        std::vector<char> string;
        int Comma_Position = 0;
        for (int i = oldNumber.length() - 1; i >= 0; i--)
        {
            string.push_back(oldNumber.at(i));
            Comma_Position++;
            if(Comma_Position %3 == 0 && Comma_Position > 0 && i!= 0)
            {
                string.push_back(',');
            }
        }
        for (int i = string.size() - 1; i >= 0; i--)
        {
            newNumberString<<string.at(i);
        }
    }
    else
    {
        std::vector<char> string;
        int Comma_Position = 0;
        for (int i = oldNumber.length() - 1; i >= 0; i--)
        {
            Comma_Position++;
            int CommaBegan_Position = Comma_Position - (oldNumber.length() - Dot_Position - 1) - 1;
            string.push_back(oldNumber.at(i));
            if (CommaBegan_Position % 3 == 0 && CommaBegan_Position > 0 && i != 0)
            {
                string.push_back(',');
            }
        }
        for (int i = string.size() - 1; i >= 0; i--)
        {
            newNumberString<<string.at(i);
        }
    }
    return newNumberString.str().c_str();
}

inline std::string addCommaToNumber2(int number)
{
    char t[256];
    std::string oldNumber;
    sprintf(t, "%d",number);
    oldNumber = t;
    std::ostringstream newNumberString;
    bool isIntNumber = true;
    int Dot_Position = 0;
    for (int i =0; i < oldNumber.length(); i++)
    {
        std::ostringstream oldNumberChar;
        oldNumberChar<<oldNumber.at(i);
        if(strcmp(oldNumberChar.str().c_str(), ".") == 0)
        {
            isIntNumber = false;
            Dot_Position = i;
        }
    }
    if(isIntNumber == true)
    {
        std::vector<char> string;
        int Comma_Position = 0;
        for (int i = oldNumber.length() - 1; i >= 0; i--)
        {
            string.push_back(oldNumber.at(i));
            Comma_Position++;
            if(Comma_Position %3 == 0 && Comma_Position > 0 && i!= 0)
            {
                string.push_back('<');
            }
        }
        for (int i = string.size() - 1; i >= 0; i--)
        {
            newNumberString<<string.at(i);
        }
    }
    else
    {
        std::vector<char> string;
        int Comma_Position = 0;
        for (int i = oldNumber.length() - 1; i >= 0; i--)
        {
            Comma_Position++;
            int CommaBegan_Position = Comma_Position - (oldNumber.length() - Dot_Position - 1) - 1;
            string.push_back(oldNumber.at(i));
            if (CommaBegan_Position % 3 == 0 && CommaBegan_Position > 0 && i != 0)
            {
                string.push_back('<');
            }
        }
        for (int i = string.size() - 1; i >= 0; i--)
        {
            newNumberString<<string.at(i);
        }
    }
    return newNumberString.str().c_str();
}



#endif

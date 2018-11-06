//
//  RoomUserInfoText.h
//  Game
//
//  Created by ���� on 13-6-26.
//
//

#ifndef __Game__RoomUserInfoText__
#define __Game__RoomUserInfoText__

#include "cocos2d.h"
USING_NS_CC;

typedef enum
{
	GorupSpriteTypePhotoAndPhoto,		//ͼƬ��ͼƬ���
	GorupSpriteTypePhotoAndWord,		//ͼƬ���������
	GorupSpriteTypePhotoAndText0,        //��Դ������䳡�����ֳ�����ӳ���ͼƬ�����ֵ����
	GorupSpriteTypePhotoAndText1,        //��Դ������������м������߼�����ͼƬ�����ֵ����
}GorupSpriteType;

class GroupSprite : public CCSprite
{
public:
    GroupSprite();
    ~GroupSprite();
    static GroupSprite * GroupSpriteWith(const char* str1,const char* str2,GorupSpriteType type,int level = 0);
    bool initGroupSprite(const char* str1,const char* str2,GorupSpriteType type,int level);

	void setTextSize(int size);
	void setTextColor(int r,int g,int b);

	void showCoinsLight(float dt);

	void actionDownAndRemove(CCNode* node);
private:
	CCLabelTTF* labelWord;
};

#endif /* defined(__Game__RoomUserInfoText__) */

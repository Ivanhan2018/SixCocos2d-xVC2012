//
//  DDDMessageBox.h
//  XXDZPK
//
//  Created by XXY on 13-11-23.
//
//

#ifndef __XXDZPK__DDDMessageBox__
#define __XXDZPK__DDDMessageBox__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
	DDDRollDirectionNone = -1,//无类�? 默认方向 从右到左 
    DDDRollDirectionHorizontal = 0,  //水平  从右到左 
    DDDRollDirectionVertical, //竖直 从下到上 
}DDDLayerRollMessageDirection;


class DDDLayer : public CCLayer {
private:
    
    void DistoryMessageBox(float dt/*CCObject *pSender*/);
    
    void DistoryRollMessageBox(CCObject *pSender);
    
public:
    
    void ShowMessage(const wchar_t *tipMsg, float delay);

    void ShowAlert(const wchar_t *tipMsg);
    
    //void ShowAlert(const wchar_t *tipMsg, const wchar_t *tipTitle) = 0;
    
public:
    
    bool MessageOnRoll;
    
    int  MessageOnRoolCount;

    void ShowRollMessage(const wchar_t *tipMsg, DDDLayerRollMessageDirection eDirection = DDDRollDirectionNone);
    
    void ShowRollMessage(const wchar_t *tipSender, const wchar_t *tipMsg, DDDLayerRollMessageDirection eDirection = DDDRollDirectionNone);
    
    void ShowRollMessage(const wchar_t *tipSender, const wchar_t *tipTo, const wchar_t *tipMsg, DDDLayerRollMessageDirection eDirection = DDDRollDirectionNone);
    
    //比赛提示信息
    void showMatchMessaghe(const wchar_t *tipMSG);
    
    //比赛回调接口
    virtual void showMatchButtonOK(CCObject *pSender);
    
private:
    /**
     * 提示�?     */
    CCSprite *MsgBg;
    CCMenu *MsgBgCover;
    
    //显示滚动消息
    void DisplayRollMessage(CCSprite *MsgLayer, CCSize MsgSize, DDDLayerRollMessageDirection eDirection);
    //删除滚动消息
    void DistoryRollMessage(CCObject *pSender);
    
protected:
    
    virtual void AlertViewOKButtonClicked(CCObject *pSender);
    
    virtual void AlertViewCancelButtonClicked(CCObject *pSender);
    
    void CoverButtonClicked(CCObject *pSender);
};

class WaittingOtherPlayer {
private:
    
    CCSprite *DotWaitLayer;
    
public:
    void WaitOtherPlayerEnter(CCSprite *Layer);
    
    void DistoryDotWaitLayer();
    
    virtual void WaitOtherPlayerEnterStatusOff() = 0;
};

#endif /* defined(__XXDZPK__DDDMessageBox__) */

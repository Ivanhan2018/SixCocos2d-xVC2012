/***********************************************
Name：SIX_PopWndMessage
Desc：消息（系统消息，聊天消息，发送消息）
Auth：团长@2013-10-24
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "RoomInfo.h"
#include <deque>
using namespace std;

// 面板显示方式
typedef enum tagPannelShowStyle
{
	MIN_SHOW_RECEIVE_PANEL, // 最小显示接收面板
	NORMAL_SEND_AND_RECEIVE_PANEL, // 正常显示发送和接收面板
	MAX_SHOW_SEND_PANEL, // 最大显示发送面板
	MAX_SHOW_RECEIVE_PANEL,	// 最大显示接收面板
}pannelshowstyle;

// 聊天消息委托
class SIX_InformationDelegate
{
public:
	virtual void OnShowInformation(CMD_ChatContent *pChat) = 0;
};

class SIX_PopWndMessage : public SIX_EffectPopWnd, public CCTableViewDelegate
{
public:
	static SIX_PopWndMessage *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);
	virtual ~SIX_PopWndMessage(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void onShowFinished();
	virtual bool OnClose();
	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	void ReceiInformation(CMD_ChatContent *pContent);
	void setChangePanel(pannelshowstyle pannelStyle);
	void setInformationDelegate(SIX_InformationDelegate *pDelegate);
	void DoEnter();
	SIX_ListView *& getInformationListview(){ return m_pInformationListView; }
	bool getNextMsg();

private:
	void doEvents(CCObject* pSender, CCControlEvent event);
	void createListView(SIX_ListView *&pListView, int iTag, const CCRect &listViewRect, const CCSize &listViewCell);
	void createSendPanel();
	void setReceiveMsgToListView(bool bInsertAllData);
	void setDefaultChatContentToListView();

private:
	deque<CMD_ChatContent *> m_deChatContent;
	pannelshowstyle m_PannelShowStyle;

	bool m_bIsHaveShow;	// 当前是否显示聊天消息，只针对 MIN_SHOW_RECEIVE_PANEL
	SIX_InformationDelegate * m_InformationDelegate;

	SIX_ListView * m_pInformationListView;
	CCScale9Sprite * m_pSendPanel;
	SIX_EditBox * m_pChatContent;
};

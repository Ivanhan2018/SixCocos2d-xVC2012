/***********************************************
Name��SIX_PopWndMessage
Desc����Ϣ��ϵͳ��Ϣ��������Ϣ��������Ϣ��
Auth���ų�@2013-10-24
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "RoomInfo.h"
#include <deque>
using namespace std;

// �����ʾ��ʽ
typedef enum tagPannelShowStyle
{
	MIN_SHOW_RECEIVE_PANEL, // ��С��ʾ�������
	NORMAL_SEND_AND_RECEIVE_PANEL, // ������ʾ���ͺͽ������
	MAX_SHOW_SEND_PANEL, // �����ʾ�������
	MAX_SHOW_RECEIVE_PANEL,	// �����ʾ�������
}pannelshowstyle;

// ������Ϣί��
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

	bool m_bIsHaveShow;	// ��ǰ�Ƿ���ʾ������Ϣ��ֻ��� MIN_SHOW_RECEIVE_PANEL
	SIX_InformationDelegate * m_InformationDelegate;

	SIX_ListView * m_pInformationListView;
	CCScale9Sprite * m_pSendPanel;
	SIX_EditBox * m_pChatContent;
};

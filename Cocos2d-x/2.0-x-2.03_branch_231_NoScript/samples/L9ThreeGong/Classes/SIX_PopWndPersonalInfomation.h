/***********************************************
Name：SIX_PopWndPersonalInfomation
Desc：修改个人信息
Auth：团长@2013-10-22
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "CMD_Plaza.h"
#include "SIX_ControlButton.h"

enum panel_type
{
	PERSIONAL_INFO,
	EDIT_HEAD_PICTURE,
	ID_ATTEST,
	EDIT_PW,
};

class SIX_PopWndPersonalInfomation :	public SIX_EffectPopWnd,public CCTableViewDelegate
{
public:
	static SIX_PopWndPersonalInfomation *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);
	virtual ~SIX_PopWndPersonalInfomation(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual bool OnClose();
	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	void setFocus();
	void setEnter();

private:
	void doEvents(CCObject* pSender, CCControlEvent event);
	void CreateButtonWithFileCell(SIX_ControlButton ** pButton, const char *file,int cell,bool Hor=true);
	void showTips(const char*);

	void setEditNickNameIME(bool bAttach);
	void setDetachEditBoxIME();
	void setTouch(int iTag);
	void OnOkIDAttest();
	void OnOkModifyPW();
	
	void changePanel(panel_type pType);
	bool setRootNode(int iTag, CCNode *&pNode);
	CCNode *getRootNode(int iTag=-1);

	void setPersonalInfoPanel();
	void setEditHeadPicturePanel();
	void setIDAttestPanel();
	void setModifyPW();

private:
	map<int, CMD_SC_Award> m_mapAward;
	SIX_EditBox * m_pNickName;

	panel_type m_curPanelType;
	int m_iCurRootNode;

	long long m_llNoChangeLogoID;
	vector<long long>	m_vDefaultLogo;
};


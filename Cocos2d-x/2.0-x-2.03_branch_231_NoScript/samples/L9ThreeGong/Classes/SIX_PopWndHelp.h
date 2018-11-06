/***********************************************
Name£∫SIX_PopWndHelp
Desc£∫∞Ô÷˙
Auth£∫Õ≈≥§@2013-10-29
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"

class SIX_PopWndHelp :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndHelp *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndHelp(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();

private:
	void doEvents(CCObject* pSender, CCControlEvent event);
	void OnClickBtn(CCControlButton *pButton);
	
private:
	CCControlButton * m_pLastButton;
};
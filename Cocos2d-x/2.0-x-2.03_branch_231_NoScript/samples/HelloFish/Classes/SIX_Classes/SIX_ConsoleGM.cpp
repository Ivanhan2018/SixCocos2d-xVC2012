#include "SIX_ConsoleGM.h"
#include "SIX_ClientRoom.h"

SIX_ConsoleGM::SIX_ConsoleGM()
{

}

SIX_ConsoleGM::~SIX_ConsoleGM()
{

}

SIX_ConsoleGM *SIX_ConsoleGM::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_ConsoleGM *pConsole = new SIX_ConsoleGM();
	if (pConsole && pConsole->init())
	{
		pConsole->initWithColor(color,width,height);
		pConsole->setPosition(x,y);
		pConsole->setRedrawBorder(bRedrawBorder);
		pConsole->setTouchEnabled(true);
		pConsole->m_ForbiddenTouch = true;
		pConsole->m_bCloseThenCleanup = bCloseThenCleanup;
		pConsole->setObjName("SIX_Console");
	}
	return pConsole;
}

void SIX_ConsoleGM::OnInputDone(CCLayer *pLayer,const char *text)
{
	//SIX_Console::OnInputDone(pLayer,text);
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	if (!pFather)
		return;
	pThis->getTTF()->detachWithIME();
	this->OnProcessCommand(text);
	//pFather->OnProcessCommand(text);
	pThis->getTTF()->setString("");
	SIX_Utility::GetInstance()->FixedTexParameters(pThis->getTTF()->getTexture());
#endif
}

void SIX_ConsoleGM::OnProcessCommand(const char *cmd)
{
	string cmdCon(SIX_Utility::GetInstance()->U2G(cmd).c_str());
	std::transform(cmdCon.begin(),cmdCon.end(),cmdCon.begin(),::tolower);

	if(cmdCon=="rulist")
	{
		setContent("玩家ID,玩家账号,玩家昵称,用户状态,桌号,位置,登录时的金币值,登录时的积分");
		SIX_ClientRoom::GetInstance()->send_data(ROOM_MAIN, ROOM_SUB_USER_LIST);
	}

	if(cmdCon=="cls")
		pListView->RemoveCellAll();

}

void SIX_ConsoleGM::ON_ROOM_SUB_USER_LIST(long long	lUserId,const char *szName,const char *szNickname,int	stUserState,int iTableNo,int iSeatNo,long long lGoldLogin,long long lPointLogin)
{
	//用户状态
	static const char *szState[6]={"离线","在线离座","在座没举手","在座已举手","断线后等待重入","未知"};
	if(stUserState<0||stUserState>4)
		stUserState=5;
	//逻辑ID左上角顺时针方向顺序 -10132<->01243
	static const char *szSeat[6]={"离座","左上角","右上角","左下角","右下角","未知"};
	int iSeatNo1=iSeatNo+1;
	if(iSeatNo1<0||iSeatNo1>4)
		iSeatNo1=5;
	setContent("%I64d,%s,%s,%s,第%d桌,第%d个座位(%s),%d,%d",lUserId,szName,szNickname,szState[stUserState],iTableNo,iSeatNo,szSeat[iSeatNo1],lGoldLogin,lPointLogin);
}
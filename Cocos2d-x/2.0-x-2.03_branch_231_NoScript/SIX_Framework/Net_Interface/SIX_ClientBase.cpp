#include "SIX_ClientBase.h"

//SIX_ClientBase *SIX_ClientBase::m_pClientLogic = 0;

SIX_ClientBase::SIX_ClientBase()
{
	m_NeedExit = false;
}

SIX_ClientBase::~SIX_ClientBase()
{
	stop();
	SIXLog("~SIX_ClientBase");
}

// ------------------------
void SIX_ClientBase::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	//SIXLog("OnConnect.bIsReconnect[%d]",bIsReconnect);
	if (this->getNeedExit())
		return;
	MSG_INFO *pMsg = new MSG_INFO();
	bool bLastReconnect = false;
	if (this->getCloseType()==CLOSE_TYPE_FLASH_CLOSE)
		bLastReconnect = true;
	pMsg->Creae(this,0,bLastReconnect?RECONNECT_SUCCESSED:CONNECT_SUCCESSED,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientBase::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	//SIXLog("OnConnectFail.bIsReconnect[%d].iError[%d]",bIsReconnect,iError);
	if (this->getNeedExit())
		return;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(this,0,CONNECT_FAILED,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientBase::OnCommError(char* pszError)
{
	//SIXLog("OnCommError.pszError[%s]",pszError);
	if (this->getNeedExit())
		return;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(this,0,COMM_ERROR,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientBase::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	//SIXLog("OnSend.iMainCode[%d].iSubCode[%d].pData[0x%08X].iDataLen[%d]",iMainCode,iSubCode,pData,iDataLen);
}

void SIX_ClientBase::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	//SIXLog("OnSendFailed.iMainCode[%d].iSubCode[%d].pData[0x%08X].iDataLen[%d]",iMainCode,iSubCode,pData,iDataLen);
	if (this->getNeedExit())
		return;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(this,0,SEND_ERROR,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientBase::OnClose(CLOSE_TYPE iCloseType)
{
	//SIXLog("OnClose.bClientClose[%d]",bClientClose);
	if (this->getNeedExit())
		return;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(this,-1,iCloseType,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientBase::OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	//SIXLog("OnTableMsg.iMainCode[%d].iSubCode[%d].pData[0x%08X].iDataLen[%d]",iMainCode,iSubCode,pData,iDataLen);
	if (this->getNeedExit())
		return;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(this,iMainCode,iSubCode,(char*)pData,iDataLen);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

bool SIX_ClientBase::getNeedExit()
{
	return m_NeedExit;
}

void SIX_ClientBase::setNeedExit(bool needExit)
{
	m_NeedExit = needExit;
}

int SIX_ClientBase::init(char *ip,int port,char *name,char *pass,bool bReconnected,int iReconnectDelay)
{
	m_NeedExit = false;

	return ((SIX_SocketClient*)(this))->init(ip,port,name,pass,bReconnected,iReconnectDelay);
}

int SIX_ClientBase::start()
{
	if (m_NeedExit)
		return 0;
	return ((SIX_SocketClient*)(this))->start();
}

int SIX_ClientBase::stop()
{
	if (m_NeedExit)
		return 0;
	int retv = 0;
	retv = ((SIX_SocketClient*)(this))->stop();
	return retv;
}

// 获得客户端配置信息，主要用于调试，目的是调试时自动启用不同的用户名
#define USER_NUMBER 40
int SIX_ClientBase::RandomUser(char* pszName)
{
	int iUserNo = SIX_Utility::GetInstance()->RNDNUM(10,100);
	sprintf(pszName, "T%2d", iUserNo);
	return iUserNo % 4;

	//string strPathFile(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("FishClientConfig.ini"));

	//UINT iChangeNameNo = GetPrivateProfileIntA("NAME_NO", "ChangeNameNo", 1, strPathFile.c_str());	// 从配置文件中读取

	//UINT iNameNo = GetPrivateProfileIntA("NAME_NO", "NameNo", 0, strPathFile.c_str());	// 从配置文件中读取
	//SIXLog("iNameNo=%d",iNameNo);

	//int iUserNo = iNameNo%USER_NUMBER;
	//int iSeatNo = iUserNo%4;

	////int iSeatNo = SIX_Utility::GetInstance()->RNDNUM(0,9);
	//switch(iUserNo)
	//{
	//case 0:sprintf(pszName, "张三");break;
	//case 1:sprintf(pszName, "李四");break;
	//case 2:sprintf(pszName, "孙一");break;
	//case 3:sprintf(pszName, "杨二");break;
	//case 4:sprintf(pszName, "王五");break;
	//case 5:sprintf(pszName, "赵六");break;
	//case 6:sprintf(pszName, "孙七");break;
	//case 7:sprintf(pszName, "金八");break;
	//case 8:sprintf(pszName, "钱九");break;
	//case 9:sprintf(pszName, "懂毛");break;
	//default:
	//	{
	//		sprintf(pszName, "T%2d", iUserNo);
	//		break;
	//	}
	//}

	//if(iChangeNameNo>0)
	//{
	//	char szTmp[32] = {0};
	//	sprintf_s(szTmp, sizeof(szTmp)-1, "%d", iNameNo+1);
	//	WritePrivateProfileStringA("NAME_NO", "NameNo", szTmp, strPathFile.c_str());	// 写入配置文件
	//}

	//return iSeatNo % 4;
}
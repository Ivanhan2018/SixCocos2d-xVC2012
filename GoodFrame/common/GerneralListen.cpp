
//#include "StdAfx.h"
#include "./PublicHead.h"
#include "./GerneralListen.h"

/// 通用接收器 /////////////////////////////////////////////////////
CGerneralListen::CGerneralListen(void)
{
}


CGerneralListen::~CGerneralListen(void)
{
}

/// 通用发射器 /////////////////////////////////////////////////////

CGerneralSink::CGerneralSink(void)
{
	m_pGerneralListen = NULL;
}


CGerneralSink::~CGerneralSink(void)
{
}

// 设置通用接收器指针
void CGerneralSink::set_gerneral_listen(CGerneralListen* pGerneralListen)
{
	m_pGerneralListen = pGerneralListen;
}

// 发向接收器，是同步的，非异步，是要等待接收器 OnResponse 执行完毕的。
int CGerneralSink::send_to_listen(int iMainCode, int iSubCode, void* pData, int iDataLen)
{
	if(!m_pGerneralListen)
		return 10;

	if(!pData && iDataLen>0)
		return 20;

	if(NULL!=pData && iDataLen<=0)
		return 30;

	int iRes = 0;
	
	iRes = m_pGerneralListen->OnResponse(iMainCode, iSubCode, pData, iDataLen);
	return iRes;
}
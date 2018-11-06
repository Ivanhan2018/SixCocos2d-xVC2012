
//#include "StdAfx.h"
#include "./PublicHead.h"
#include "./GerneralListen.h"

/// ͨ�ý����� /////////////////////////////////////////////////////
CGerneralListen::CGerneralListen(void)
{
}


CGerneralListen::~CGerneralListen(void)
{
}

/// ͨ�÷����� /////////////////////////////////////////////////////

CGerneralSink::CGerneralSink(void)
{
	m_pGerneralListen = NULL;
}


CGerneralSink::~CGerneralSink(void)
{
}

// ����ͨ�ý�����ָ��
void CGerneralSink::set_gerneral_listen(CGerneralListen* pGerneralListen)
{
	m_pGerneralListen = pGerneralListen;
}

// �������������ͬ���ģ����첽����Ҫ�ȴ������� OnResponse ִ����ϵġ�
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
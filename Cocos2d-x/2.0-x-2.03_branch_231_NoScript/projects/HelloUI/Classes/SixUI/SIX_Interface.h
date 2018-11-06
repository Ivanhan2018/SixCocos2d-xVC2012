/*********************************************************
Name���ײ������
Desc��ʵ�ֽӿڶ���ͨ�����ԣ��ӿ��������ӿ������ӿ����ͣ�
Auth��Cool.Cat@2013-03-15
*********************************************************/
#pragma once
#include "SIX_IInterface.h"

INTERFACE_BEGIN_BASED(SIX_Interface,SIX_IInterface)
	CONSTRUCTOR(
		SIX_Interface,
		setInterfaceName("SIX_Interface");
	);
	DESTRUCTOR(
		SIX_Interface
	);
	// �ӿ�����(SHA-160)
	CC_SYNTHESIZE_READONLY(unsigned int,m_Idx,InterfaceIdx);
	// �ӿ�����
	CC_SYNTHESIZE_READONLY(CCString,m_Name,InterfaceName);
public:
	void setInterfaceIdx(unsigned int idx){m_Idx = idx;}
	void setInterfaceName(CCString name)
	{
		m_Name.initWithFormat(/*%s%s*/XorStr<0x8B,5,0x3CA9D42F>("\xAE\xFF\xA8\xFD"+0x3CA9D42F).s,INTERFACE_GLOBALNAME,name.getCString());
		//SIXLog("name=%s , m_Name=%s",name.getCString(),UT->G2U(m_Name.getCString()).c_str());
		// Miracl.SHA160(name)
		setInterfaceIdx(0);
	}
INTERFACE_END()
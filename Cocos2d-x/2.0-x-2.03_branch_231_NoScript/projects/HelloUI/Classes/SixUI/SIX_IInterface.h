/*********************************************************
Name���ײ�ӿ���
Desc������ӿ�
Auth��Cool.Cat@2013-03-15
*********************************************************/
#pragma once
#include "SIX_Typedef.h"

USING_NS_CC;

#define INTERFACE_BEGIN(__cls_name__)	class __cls_name__{
#define INTERFACE_BEGIN_BASED(__cls_name__,__based__)	class __cls_name__:public __based__ {
#define INTERFACE_END()	};

INTERFACE_BEGIN_BASED(SIX_IInterface,CCObject)
	DESTRUCTOR(SIX_IInterface)
	// �ӿ�����
	CC_PURE_VIRTUAL_FUNC(unsigned int,m_Idx,InterfaceIdx)
	// �ӿ�����
	CC_PURE_VIRTUAL_FUNC(CCString,m_Name,InterfaceName)
INTERFACE_END()
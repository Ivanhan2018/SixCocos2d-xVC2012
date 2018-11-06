#include "SIX_UIMgr.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <exception>
#include <cxxabi.h>
#endif

// ���Դ�Сд
extern int compareIgnoreCase(CCString str,const char * pStr);

//USING_NS_CC_EXT;

SIX_UIMgr::SIX_UIMgr()
{
	m_bDirty = false;
}
SIX_UIMgr::~SIX_UIMgr()
{
	UnloadFrameCache();
	UnloadAnimationCache();
}

template <typename T>
static bool ParseSingleAttribute(SIX_UIMgr *pThis,T *pObject,const char *attrName,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (!pThis || !pObject || !attrName || !pDataElement)
		return false;

	const char *typeName = 0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	typeName = typeid(pObject).name();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int status=0;
	const std::type_info &ti = typeid(pObject);
	typeName = abi::__cxa_demangle(ti.name(),0,0,&status);
#endif

	SIXLog("ParseSingleAttribute.typeid(pObject).name()=%s",typeName);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (!STRCMP(typeName,"struct cocos2d::_ccColor4B *"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!STRCMP(typeName,"cocos2d::_ccColor4B *"))
#endif
	{
		SIX_KV *pKV = new SIX_KV();
		int pos = pThis->GetAttributeAndPos(pDataElement,attrName,pKV);
		if (pos>=0)
		{
			MP *mp=new MP();
			int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
			if (count==3 || count==4)
			{
				((ccColor4B*)pObject)->r = (GLubyte)atoi(mp->at(0).c_str());
				((ccColor4B*)pObject)->g = (GLubyte)atoi(mp->at(1).c_str());
				((ccColor4B*)pObject)->b = (GLubyte)atoi(mp->at(2).c_str());

				if (count==4)
				{
					((ccColor4B*)pObject)->a = (GLubyte)atoi(mp->at(3).c_str());
				}
			}
	#ifdef WIN32
			mp->swap(MP());
	#endif
			mp->clear();
			CC_SAFE_DELETE(mp);

			// �Ƴ�ָ��������
			pDataElement->Del(pos);
		}
		CC_SAFE_DELETE(pKV);
		return true;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	else if (!STRCMP(typeName,"class cocos2d::CCPoint *"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	else if (!STRCMP(typeName,"cocos2d::CCPoint *"))
#endif
	{
		SIX_KV *pKV = new SIX_KV();
		int pos = pThis->GetAttributeAndPos(pDataElement,attrName,pKV);
		if (pos>=0)
		{
			MP *mp=new MP();
			int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
			if (count==2)
			{
				((CCPoint*)pObject)->setPoint(atof(mp->at(0).c_str()),atof(mp->at(1).c_str()));
			}
	#ifdef WIN32
			mp->swap(MP());
	#endif
			mp->clear();
			CC_SAFE_DELETE(mp);

			// �Ƴ�ָ��������
			pDataElement->Del(pos);
		}
		CC_SAFE_DELETE(pKV);
		return true;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	else if (!STRCMP(typeName,"class cocos2d::CCSize *"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	else if (!STRCMP(typeName,"cocos2d::CCSize *"))
#endif
	{
		SIX_KV *pKV = new SIX_KV();
		int pos = pThis->GetAttributeAndPos(pDataElement,attrName,pKV);
		if (pos>=0)
		{
			MP *mp=new MP();
			int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
			if (count==2)
			{
				((CCSize*)pObject)->setSize(atof(mp->at(0).c_str()),atof(mp->at(1).c_str()));
			}
	#ifdef WIN32
			mp->swap(MP());
	#endif
			mp->clear();
			CC_SAFE_DELETE(mp);

			// �Ƴ�ָ��������
			pDataElement->Del(pos);
		}
		CC_SAFE_DELETE(pKV);
		return true;
	}

	SIXLog("ParseSingleAttribute.typeid(pObject).name()=%s.Unknown!",typeName);
	return false;
}

template <typename T>
static bool LoadControl(SIX_UIMgr *pThis,T *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (!pThis || !pControl || !pDataElement)
		return false;

	// ��Щ�ؼ�����ʱҪ�ȳ�ʼ��ĳЩ���ԣ����磺AnchorPoint
	const char *typeName = 0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	typeName = typeid(pControl).name();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int status=0;
	const std::type_info &ti = typeid(pControl);
	typeName = abi::__cxa_demangle(ti.name(),0,0,&status);
#endif

	SIXLog("LoadControl.typeid(pControl).name()=%s",typeName);

	// ���¿ؼ����Ĭ��Ϊ(0,0)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (!STRCMP(typeName,"class cocos2d::CCLabelTTF *") ||
		!STRCMP(typeName,"class cocos2d::CCSprite *") ||
		!STRCMP(typeName,"class cocos2d::CCProgressTimer *")
	)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!STRCMP(typeName,"cocos2d::CCLabelTTF *") ||
		!STRCMP(typeName,"cocos2d::CCSprite *") ||
		!STRCMP(typeName,"cocos2d::CCProgressTimer *")
	)
#endif
	{
		// ���Ĭ��Ϊ(0,0)
		pControl->setAnchorPoint(ccp(0,0));
	}

	SIX_KV *pKV = 0;
	unsigned int j=0;
	CCARRAY_FOREACH_T(pDataElement->GetChildren(),pKV,SIX_KV*)
	{
		j++;
		SIXLog("SIX_UIMgr.pKV[%d].key[%s].value[%s]",j,pKV->getKey().getCString(),pKV->getValue().getCString());

		if (!pThis->ParseAttribute(pControl,pKV))
			return false;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (!STRCMP(typeName,"class cocos2d::CCLabelTTF *"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!STRCMP(typeName,"cocos2d::CCLabelTTF *"))
#endif
	{
		// �������
		((CCLabelTTF*)pControl)->getTexture()->setAntiAliasTexParameters();
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	else if (!STRCMP(typeName,"class cocos2d::CCSprite *"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	else if (!STRCMP(typeName,"cocos2d::CCSprite *"))
#endif
	{
		// �������
		((CCSprite*)pControl)->getTexture()->setAntiAliasTexParameters();
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	else if (!STRCMP(typeName,"class cocos2d::CCSpriteBatchNode *"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	else if (!STRCMP(typeName,"cocos2d::CCSpriteBatchNode *"))
#endif
	{
		// �������
		((CCSpriteBatchNode*)pControl)->getTexture()->setAntiAliasTexParameters();
	}

	return true;
}

// -----------------------------------------------------
// LoadControl��CreateControl����
// ���XML�ڵ�û��������ԣ�ֱ���ȴ����ؼ�������LoadControl
// �Ϳ��Խ����ˣ�����Layer�ȣ�������Ҫ��CreateControl�����
// ������ԣ��ؼ���CreateControl�ڲ�����������CCSprite�ȡ�
// -----------------------------------------------------
// Cool.Cat@2013-04-5
// -----------------------------------------------------
template <typename T>
static T *CreateControl(SIX_UIMgr *pThis,const char *name,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (!pThis)
		return 0;

	SIX_DSTPL<SIX_KV> *pDataElementKV = pThis->ParseKV(name,pDataElement);
	if (!pDataElementKV)
		return 0;

	T *pControl = 0;

	// ��Щ�ؼ�����ʱҪ�ȴ����������ԣ����磺file=''
	const char *typeName = 0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	typeName = typeid(T).name();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int status=0;
	const std::type_info &ti = typeid(T);
	typeName = abi::__cxa_demangle(ti.name(),0,0,&status);
#endif

	SIXLog("CreateControl.typeid(%s).name()=%s",name,typeName);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (!STRCMP(typeName,"class cocos2d::CCSprite") ||
		!STRCMP(typeName,"class cocos2d::extension::CCScale9Sprite")
	)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!STRCMP(typeName,"cocos2d::CCSprite") ||
		!STRCMP(typeName,"cocos2d::extension::CCScale9Sprite")
	)
#endif
	{
		// �ȼ���ͼƬ
		SIX_KV *pKVFile = new SIX_KV();
		int pos = pThis->GetAttributeAndPos(pDataElementKV,"file",pKVFile);
		if (pos<0)
		{
			pos = pThis->GetAttributeAndPos(pDataElementKV,"Frame",pKVFile);
			if (pos<0)
			{
				CC_SAFE_DELETE(pKVFile);
				CC_SAFE_DELETE(pDataElementKV);
				return 0;
			}
		}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if (!STRCMP(typeName,"class cocos2d::CCSprite"))
			pControl = (T*)CCSprite::create(pKVFile->getValue().getCString());
		else if (!STRCMP(typeName,"class cocos2d::extension::CCScale9Sprite"))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (!STRCMP(typeName,"cocos2d::CCSprite"))
			pControl = (T*)CCSprite::create(pKVFile->getValue().getCString());
		else if (!STRCMP(typeName,"cocos2d::extension::CCScale9Sprite"))
#endif
		{
			if (0 == compareIgnoreCase(pKVFile->getKey(),"file"))
				pControl = (T*)CCScale9Sprite::create(pKVFile->getValue().getCString());
			else
				pControl = (T*)CCScale9Sprite::createWithSpriteFrameName(pKVFile->getValue().getCString());
		}
		
		CC_SAFE_DELETE(pKVFile);

		// ȥ��file����
		pDataElementKV->Del(pos);
	}
	else
	{
		pControl = T::create();
	}

	if (!LoadControl<T>(pThis,pControl,pDataElementKV))
	{
		CC_SAFE_DELETE(pDataElementKV);
		CC_SAFE_RELEASE(pControl);
		return 0;
	}
	CC_SAFE_DELETE(pDataElementKV);
	return pControl;
}

// ��������ָ�����Բ���������ƫ��
// ����-1Ϊ���Բ�����
int SIX_UIMgr::GetAttributeAndPos(SIX_DSTPL<SIX_KV> *pDataElement,const char *attribute,SIX_KV *pResult)
{
	int pos=-1;
	SIX_KV *pKV = 0;
	unsigned int j=0;
	if (!attribute || !pDataElement || !pResult)
		goto clean;

	CCARRAY_FOREACH_T(pDataElement->GetChildren(),pKV,SIX_KV*)
	{
		if (!compareIgnoreCase(pKV->getKey(),attribute))
		{
			pResult->setKey(pKV->getKey().getCString());
			pResult->setValue(pKV->getValue().getCString());
			pos=j;
			goto clean;
		}
		j++;
	}
clean:
	return pos;
}

// CCNode����
bool SIX_UIMgr::ParseAttribute(CCNode *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"Name"))
	{
		//pControl->setObjName(pKV->getValue().getCString());
	}
	// �߿��ػ棬����ʱʹ��
	// ���ڵ����dirtyʱ��ֻӰ������͵�ǰ���е��ӽڵ�
	// ������ӵ��ӽڵ㣬ֻ������ʾ(����)ʱ�Ż�����ڵ�ͬ��
	// Cool.Cat
	else if (!compareIgnoreCase(pKV->getKey(),"dirty"))
	{
		//pControl->setRectDirty(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"zOrder"))
	{
		pControl->_setZOrder(pKV->getValue().intValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Tag"))
	{
		pControl->setTag(pKV->getValue().intValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"UserData"))
	{
		const char *userData = pKV->getValue().getCString();
		pControl->setUserData((void*)userData);
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Visible"))
	{
		pControl->setVisible(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Rotation"))
	{
		pControl->setRotation(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Scale"))
	{
		pControl->setScale(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"ScaleX"))
	{
		pControl->setScaleX(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"ScaleY"))
	{
		pControl->setScaleY(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"PositionX"))
	{
		pControl->setPositionX(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"PositionY"))
	{
		pControl->setPositionY(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"SkewX"))
	{
		pControl->setSkewX(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"SkewY"))
	{
		pControl->setSkewY(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Size") || 
			 !compareIgnoreCase(pKV->getKey(),"Pos")  ||
			 !compareIgnoreCase(pKV->getKey(),"AnchorPoint")
			)
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		switch (count)
		{
		case 2:
			{
				float x = atof(mp->at(0).c_str());
				float y = atof(mp->at(1).c_str());
				if (!compareIgnoreCase(pKV->getKey(),"Size"))
					pControl->setContentSize(CCSize(x,y));
				else if (!compareIgnoreCase(pKV->getKey(),"Pos"))
					pControl->setPosition(CCPoint(x,y));
				else if (!compareIgnoreCase(pKV->getKey(),"AnchorPoint"))
					pControl->setAnchorPoint(CCPoint(x,y));
				break;
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	// ���ض���
	else if (!compareIgnoreCase(pKV->getKey(),"Action"))
	{
		CCAnimation *pAnimation = GetAnimationFromCache(pKV->getValue().getCString());
		if (pAnimation)
		{
			CCAnimate *pAnimate = CCAnimate::actionWithAnimation(pAnimation);
			CCRepeatForever *pAction = CCRepeatForever::actionWithAction(pAnimate);
			pControl->runAction(pAction);
		}
	}
	//// �Զ��屳������
	//// ����sprite��ӵ����ڵ㣬�ᵼ�½ڵ������ӽڵ㲻������ң�ȥ����~
	//// Cool.Cat@2013-04-04
	//else if (!compareIgnoreCase(pKV->getKey(),"bkimage"))
	//{
	//	CCSprite* pSprite = 0;

	//	MP *mp=new MP();
	//	int count = SIX_Utility::GetInstance()->Split("=",(char*)pKV->getValue().getCString(),mp);
	//	switch (count)
	//	{
	//		// bkimage="filePath"
	//	case 0:
	//		{
	//			pSprite = CCSprite::create(pKV->getValue().getCString());
	//			CCAssert(pSprite,"A.wtf");
	//			pSprite->setAnchorPoint(ccp(0,0));
	//			break;
	//		}
	//		// bkimage="filePath=X,Y"
	//	case 2:
	//		{
	//			pSprite = CCSprite::create(mp->at(0).c_str());
	//			CCAssert(pSprite,"B.wtf");

	//			MP *child = new MP();
	//			count = SIX_Utility::GetInstance()->Split(",",(char*)mp->at(1).c_str(),child);
	//			if (count==2)
	//			{
	//				float x = atof(child->at(0).c_str());
	//				float y = atof(child->at(1).c_str());
	//				pSprite->setAnchorPoint(ccp(x,y));
	//			}
	//			child->swap(MP());
	//			child->clear();
	//			CC_SAFE_DELETE(child);
	//			break;
	//		}
	//	}
	//	mp->swap(MP());
	//	mp->clear();
	//	CC_SAFE_DELETE(mp);

	//	CCAssert(pSprite,"C.wtf");
	//	pControl->addChild(pSprite);
	//}
	else
	{
		SIXLog("Attribute[%s][%s].Unknown",pKV->getKey().getCString(),pKV->getValue().getCString());
		return false;
	}

	return true;
}

// CCSpriteBatchNode����
bool SIX_UIMgr::ParseAttribute(CCSpriteBatchNode *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	// alpha��Ϻ���
	if (!compareIgnoreCase(pKV->getKey(),"BlendFunc"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==2)
		{
			ccBlendFunc blendFunc = {0};
			blendFunc.src = (GLenum)atoi(mp->at(0).c_str());
			blendFunc.dst = (GLenum)atoi(mp->at(1).c_str());
			pControl->setBlendFunc(blendFunc);
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCNode*)pControl,pKV))
			return false;
	}
	return true;
}

// CCScale9Sprite����
bool SIX_UIMgr::ParseAttribute(CCScale9Sprite *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	// ������С
	if (!compareIgnoreCase(pKV->getKey(),"PreferredSize"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		switch (count)
		{
		case 2:
			{
				float x = atof(mp->at(0).c_str());
				float y = atof(mp->at(1).c_str());
				if (!compareIgnoreCase(pKV->getKey(),"PreferredSize"))
					pControl->setPreferredSize(CCSize(x,y));
				break;
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	// ���ڼ��
	else if (!compareIgnoreCase(pKV->getKey(),"InsetLeft"))
	{
		pControl->setInsetLeft(pKV->getValue().floatValue());
	}
	// ���ڼ��
	else if (!compareIgnoreCase(pKV->getKey(),"InsetTop"))
	{
		pControl->setInsetTop(pKV->getValue().floatValue());
	}
	// ���ڼ��
	else if (!compareIgnoreCase(pKV->getKey(),"InsetRight"))
	{
		pControl->setInsetRight(pKV->getValue().floatValue());
	}
	// ���ڼ��
	else if (!compareIgnoreCase(pKV->getKey(),"InsetBottom"))
	{
		pControl->setInsetBottom(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCNode*)pControl,pKV))
			return false;
	}

	return true;
}

// CCProgressTimer����
bool SIX_UIMgr::ParseAttribute(CCProgressTimer *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	// ��ǰ�ٷֱ�
	if (!compareIgnoreCase(pKV->getKey(),"Percentage"))
	{
		pControl->setPercentage(pKV->getValue().floatValue());
	}
	// 0=kCCProgressTimerTypeRadial	�״�����
	// 1=kCCProgressTimerTypeBar	��������
	else if (!compareIgnoreCase(pKV->getKey(),"Type"))
	{
		pControl->setType((CCProgressTimerType)pKV->getValue().intValue());
	}
	// �Ƿ��򲥷Ž��ȶ���
	else if (!compareIgnoreCase(pKV->getKey(),"ReverseProgress"))
	{
		pControl->setReverseProgress(pKV->getValue().boolValue());
	}
	// �Ƿ񰴷����򲥷Ŷ���
	else if (!compareIgnoreCase(pKV->getKey(),"ReverseDirection"))
	{
		pControl->setReverseDirection(pKV->getValue().boolValue());
	}
	// Alpha
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	// Alpha
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	// BarChangeRate��
	// (1,0)=����
	// (0,1)=����
	// Midpoint=�е�λ��
	// �������������ת�Ľ��ȶ��������������ģ�
	// ��������ζ�������������UV����ȱ仯����ʼλ�ã�
	// (0,y)=�������
	// (1,y)=�����ұ�
	// (x,0)=��������
	// (x,1)=��������
	// (0.5,0.5)��������
	else if (!compareIgnoreCase(pKV->getKey(),"BarChangeRate")||
				!compareIgnoreCase(pKV->getKey(),"Midpoint") ||
				!compareIgnoreCase(pKV->getKey(),"AnchorPoint")
			)
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==2)
		{
			double x = atof(mp->at(0).c_str());
			double y = atof(mp->at(1).c_str());
			if (!compareIgnoreCase(pKV->getKey(),"BarChangeRate"))
				pControl->setBarChangeRate(ccp(x,y));
			else if (!compareIgnoreCase(pKV->getKey(),"Midpoint"))
				pControl->setMidpoint(ccp(x,y));
			else if (!compareIgnoreCase(pKV->getKey(),"AnchorPoint"))
				pControl->setAnchorPoint(ccp(x,y));
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCNode*)pControl,pKV))
			return false;
	}

	return true;
}

// CCSprite����
bool SIX_UIMgr::ParseAttribute(CCSprite *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"AtlasIndex"))
	{
		pControl->setAtlasIndex(pKV->getValue().uintValue());
	}
	// Alpha
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	// Alpha
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	// �����Ӷ����ػ�
	else if (!compareIgnoreCase(pKV->getKey(),"DirtyRecursively"))
	{
		pControl->setDirtyRecursively(pKV->getValue().boolValue());
	}
	// X�ᷭת
	else if (!compareIgnoreCase(pKV->getKey(),"FlipX"))
	{
		pControl->setFlipX(pKV->getValue().boolValue());
	}
	// Y�ᷭת
	else if (!compareIgnoreCase(pKV->getKey(),"FlipY"))
	{
		pControl->setFlipY(pKV->getValue().boolValue());
	}
	// ��ת�Ƕ�
	else if (!compareIgnoreCase(pKV->getKey(),"Rotation"))
	{
		pControl->setRotation(pKV->getValue().floatValue());
	}
	// xy����
	else if (!compareIgnoreCase(pKV->getKey(),"Scale"))
	{
		pControl->setScale(pKV->getValue().floatValue());
	}
	// x����
	else if (!compareIgnoreCase(pKV->getKey(),"ScaleX"))
	{
		pControl->setScaleX(pKV->getValue().floatValue());
	}
	// y����
	else if (!compareIgnoreCase(pKV->getKey(),"ScaleY"))
	{
		pControl->setScaleY(pKV->getValue().floatValue());
	}
	// x��б
	else if (!compareIgnoreCase(pKV->getKey(),"SkewX"))
	{
		pControl->setSkewX(pKV->getValue().floatValue());
	}
	// y��б
	else if (!compareIgnoreCase(pKV->getKey(),"SkewY"))
	{
		pControl->setSkewY(pKV->getValue().floatValue());
	}
	// �Ƿ�ɼ�
	else if (!compareIgnoreCase(pKV->getKey(),"Visible"))
	{
		pControl->setVisible(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Pos")  ||
			 !compareIgnoreCase(pKV->getKey(),"AnchorPoint")
			)
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		switch (count)
		{
		case 2:
			{
				float x = atof(mp->at(0).c_str());
				float y = atof(mp->at(1).c_str());
				if (!compareIgnoreCase(pKV->getKey(),"Pos"))
					pControl->setPosition(CCPoint(x,y));
				else if (!compareIgnoreCase(pKV->getKey(),"AnchorPoint"))
					pControl->setAnchorPoint(CCPoint(x,y));
				break;
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCNode*)pControl,pKV))
			return false;
	}

	return true;
}

// CCLabelTTF����
bool SIX_UIMgr::ParseAttribute(CCLabelTTF *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	// �ı�
	if (!compareIgnoreCase(pKV->getKey(),"String"))
	{
		pControl->setString(pKV->getValue().getCString());
	}
	// ����
	else if (!compareIgnoreCase(pKV->getKey(),"fontName"))
	{
		pControl->setFontName(pKV->getValue().getCString());
	}
	// �����С
	else if (!compareIgnoreCase(pKV->getKey(),"fontSize"))
	{
		pControl->setFontSize(pKV->getValue().floatValue());
	}
	// �������
	else if (!compareIgnoreCase(pKV->getKey(),"HorizontalAlignment"))
	{
		pControl->setHorizontalAlignment((CCTextAlignment)pKV->getValue().intValue());
	}
	// �������
	else if (!compareIgnoreCase(pKV->getKey(),"VerticalAlignment"))
	{
		pControl->setVerticalAlignment((CCVerticalTextAlignment)pKV->getValue().intValue());
	}
	// ����ά��
	else if (!compareIgnoreCase(pKV->getKey(),"Dimensions"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==2)
		{
			float w = atof(mp->at(0).c_str());
			float h = atof(mp->at(1).c_str());
			pControl->setDimensions(CCSize(w,h));
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCSprite*)pControl,pKV))
			return false;
	}

	return true;
}

// CCMenuItem����
bool SIX_UIMgr::ParseAttribute(CCMenuItem *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else
	{
		if (!ParseAttribute((CCNode*)pControl,pKV))
			return false;
	}
	return true;
}

// CCMenuItemToggle����
bool SIX_UIMgr::ParseAttribute(CCMenuItemToggle *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCMenuItem*)pControl,pKV))
			return false;
	}
	return true;
}

// CCMenuItemSprite����
bool SIX_UIMgr::ParseAttribute(CCMenuItemSprite *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCMenuItem*)pControl,pKV))
			return false;
	}

	return true;
}

// CCMenuItemImage����
bool SIX_UIMgr::ParseAttribute(CCMenuItemImage *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!ParseAttribute((CCMenuItemSprite*)pControl,pKV))
		return false;

	return true;
}

// CCMenuItemLabel����
bool SIX_UIMgr::ParseAttribute(CCMenuItemLabel *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"String"))
	{
		pControl->setString(pKV->getValue().getCString());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color") ||
			 !compareIgnoreCase(pKV->getKey(),"DisabledColor")
			)
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			if (!compareIgnoreCase(pKV->getKey(),"Color"))
				pControl->setColor(ccc3(r,g,b));
			else if (!compareIgnoreCase(pKV->getKey(),"DisabledColor"))
				pControl->setDisabledColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCMenuItem*)pControl,pKV))
			return false;
	}
	return true;
}

// CCMenuItemAtlasFont����
bool SIX_UIMgr::ParseAttribute(CCMenuItemAtlasFont *pControl,SIX_KV *pKV)
{
	return ParseAttribute((CCMenuItemLabel*)pControl,pKV);
}

// CCMenuItemFont����
bool SIX_UIMgr::ParseAttribute(CCMenuItemFont *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"FontSize"))
	{
		pControl->setFontSize(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"FontName"))
	{
		pControl->setFontName(pKV->getValue().getCString());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"FontSizeObj"))
	{
		pControl->setFontSizeObj(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"FontNameObj"))
	{
		pControl->setFontNameObj(pKV->getValue().getCString());
	}
	else
	{
		if (!ParseAttribute((CCMenuItemLabel*)pControl,pKV))
			return false;
	}

	return true;
}

// CCLayer����
bool SIX_UIMgr::ParseAttribute(CCLayer *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"TouchEnabled"))
	{
		pControl->setTouchEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"KeypadEnabled"))
	{
		pControl->setKeypadEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"AccelerometerEnabled"))
	{
		pControl->setAccelerometerEnabled(pKV->getValue().boolValue());
	}
	else
	{
		if (!ParseAttribute((CCNode*)pControl,pKV))
			return false;
	}

	return true;
}

// CCMenu����
bool SIX_UIMgr::ParseAttribute(CCMenu *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"HandlerPriority"))
	{
		pControl->setHandlerPriority(pKV->getValue().intValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCLayer*)pControl,pKV))
			return false;
	}

	return true;
}

// CCLayerMultiplex����
bool SIX_UIMgr::ParseAttribute(CCLayerMultiplex *pControl,SIX_KV *pKV)
{
	return ParseAttribute((CCLayer*)pControl,pKV);
}

// CCLayerColor����
bool SIX_UIMgr::ParseAttribute(CCLayerColor *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"size"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==2)
		{
			double x = atof(mp->at(0).c_str());
			double y = atof(mp->at(1).c_str());
			pControl->setContentSize(CCSize(x,y));
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCLayer*)pControl,pKV))
			return false;
	}

	return true;
}

// CCLayerGradient����
bool SIX_UIMgr::ParseAttribute(CCLayerGradient *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"CompressedInterpolation"))
	{
		pControl->setCompressedInterpolation(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"StartOpacity"))
	{
		pControl->setStartOpacity(pKV->getValue().uintValue());
	}
	if (!compareIgnoreCase(pKV->getKey(),"EndOpacity"))
	{
		pControl->setEndOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"StartColor") ||
			 !compareIgnoreCase(pKV->getKey(),"EndColor"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());

			if (!compareIgnoreCase(pKV->getKey(),"StartColor"))
				pControl->setStartColor(ccc3(r,g,b));
			else if (!compareIgnoreCase(pKV->getKey(),"EndColor"))
				pControl->setEndColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				if (!compareIgnoreCase(pKV->getKey(),"StartColor"))
					pControl->setStartOpacity(a);
				else if (!compareIgnoreCase(pKV->getKey(),"EndColor"))
					pControl->setEndOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCLayerColor*)pControl,pKV))
			return false;	
	}

	return true;
}

// CCControl����
bool SIX_UIMgr::ParseAttribute(CCControl *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"DefaultTouchPriority"))
	{
		pControl->setDefaultTouchPriority(pKV->getValue().intValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Highlighted"))
	{
		pControl->setHighlighted(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Selected"))
	{
		pControl->setSelected(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			pControl->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	// �����¼�������
	else if (!compareIgnoreCase(pKV->getKey(),"Events"))
	{
		pControl->addTargetWithActionForControlEvents(pControl,cccontrol_selector(SIX_UIMgr::doEvents),pKV->getValue().intValue());
	}
	else
	{
		if (!ParseAttribute((CCLayer*)pControl,pKV))
			return false;
	}

	return true;
}

void SIX_UIMgr::addControlEvents(unsigned int controlEvents,CCControl *pContrl,CCObject *pTarget)
{
	if (!pContrl)
		return;

	if (!pTarget)
		pTarget = pContrl;

	pContrl->addTargetWithActionForControlEvents(pTarget,cccontrol_selector(SIX_UIMgr::doEvents),controlEvents);
}
// CCControlButton����
bool SIX_UIMgr::ParseAttribute(CCControlButton *pControl,SIX_KV *pKV)
{
	if (!pControl || !pKV)
		return false;

	if (!compareIgnoreCase(pKV->getKey(),"Enabled"))
	{
		pControl->setEnabled(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Selected"))
	{
		pControl->setSelected(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Highlighted"))
	{
		pControl->setHighlighted(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"PreferredSize"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		switch (count)
		{
		case 2:
			{
				float x = atof(mp->at(0).c_str());
				float y = atof(mp->at(1).c_str());
				if (!compareIgnoreCase(pKV->getKey(),"PreferredSize"))
					pControl->setPreferredSize(CCSize(x,y));
				break;
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else if (!compareIgnoreCase(pKV->getKey(),"ZoomOnTouchDown"))
	{
		pControl->setZoomOnTouchDown(pKV->getValue().boolValue());
	}
	// ������������
	else if (!compareIgnoreCase(pKV->getKey(),"ZoomFactor"))
	{
		//pControl->setZoomFactor(pKV->getValue().floatValue());
	}
	// �������Ų���
	else if (!compareIgnoreCase(pKV->getKey(),"ZoomStep"))
	{
		//pControl->setZoomStep(pKV->getValue().floatValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"AdjustBackgroundImage"))
	{
		pControl->setAdjustBackgroundImage(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Margins") ||
				!compareIgnoreCase(pKV->getKey(),"LabelAnchorPoint"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==2)
		{
			if (!compareIgnoreCase(pKV->getKey(),"Margins"))
			{
				int x = atoi(mp->at(0).c_str());
				int y = atoi(mp->at(1).c_str());
				pControl->setMargins(x,y);
			}
			else if (!compareIgnoreCase(pKV->getKey(),"LabelAnchorPoint"))
			{
				double x = atof(mp->at(0).c_str());
				double y = atof(mp->at(1).c_str());
				pControl->setLabelAnchorPoint(ccp(x,y));
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Opacity"))
	{
		pControl->setOpacity(pKV->getValue().uintValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"OpacityModifyRGB"))
	{
		pControl->setOpacityModifyRGB(pKV->getValue().boolValue());
	}
	else if (!compareIgnoreCase(pKV->getKey(),"Color"))
	{
		MP *mp=new MP();
		int count = SIX_Utility::GetInstance()->Split(",",(char*)pKV->getValue().getCString(),mp);
		if (count==3 || count==4)
		{
			GLubyte r = (GLubyte)atoi(mp->at(0).c_str());
			GLubyte g = (GLubyte)atoi(mp->at(1).c_str());
			GLubyte b = (GLubyte)atoi(mp->at(2).c_str());
			((CCControlButton *)pControl)->setColor(ccc3(r,g,b));

			if (count==4)
			{
				GLubyte a = (GLubyte)atoi(mp->at(3).c_str());
				pControl->setOpacity(a);
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
	}
	else
	{
		if (!ParseAttribute((CCControl*)pControl,pKV))
			return false;
	}

	return true;
}

bool SIX_UIMgr::GetAttributeSplit(const char *src,const char *name,string &value)
{
	if (!src || !name)
		return false;

	bool retv = false;
	MP *mp=new MP();
	int count = SIX_Utility::GetInstance()->Split("=",(char*)src,mp);
	if (count==2)
	{
		if (!STRCMP(mp->at(0).c_str(),name))
		{
			// name='value'
			int len = mp->at(1).length();
			if (len<2)
				goto clean;

			string x(mp->at(1).c_str(),1,mp->at(1).length()-2);
			value.append(x);
			retv = true;
		}
	}
clean:
#ifdef WIN32
	mp->swap(MP());
#endif
	mp->clear();
	CC_SAFE_DELETE(mp);
	return false;
}

SIX_DSTPL<SIX_KV> *SIX_UIMgr::ParseKV(const char *name,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (!name || !pDataElement)
		return 0;

	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,name,pKV);
	if (pos<0)
	{
		CC_SAFE_DELETE(pKV);
		return 0;
	}

	// format:string='xxx'\r\ncolor=''\r\n...
	SIX_DSTPL<SIX_KV> *pDataElementKV = new SIX_DSTPL<SIX_KV>;
	MP *mp=new MP();
	int count = SIX_Utility::GetInstance()->Split("\\r\\n",(char*)pKV->getValue().getCString(),mp);
	if (count==0)
	{
		MP *Arr = new MP();
		int countArr = SIX_Utility::GetInstance()->Split("=",(char*)pKV->getValue().getCString(),Arr);
		if (countArr==2)
		{
			int valueLen = Arr->at(1).length();
			// key='value'
			if (valueLen>2)
			{
				string valueFixed(Arr->at(1).c_str(),1,Arr->at(1).length()-2);
				SIX_KV *pKVAttr = new SIX_KV();
				pKVAttr->setKey(Arr->at(0).c_str());
				pKVAttr->setValue(valueFixed.c_str());
				pDataElementKV->Add(pKVAttr);
			}
		}
#ifdef WIN32
		Arr->swap(MP());
#endif
		Arr->clear();
		CC_SAFE_DELETE(Arr);
	}
	else
	{
		for (int i=0;i<count;i++)
		{
			MP *Arr = new MP();
			int countArr = SIX_Utility::GetInstance()->Split("=",(char*)mp->at(i).c_str(),Arr);
			if (countArr==2)
			{
				int valueLen = Arr->at(1).length();
				// key='value'
				if (valueLen>2)
				{
					string valueFixed(Arr->at(1).c_str(),1,Arr->at(1).length()-2);
					SIX_KV *pKVAttr = new SIX_KV();
					pKVAttr->setKey(Arr->at(0).c_str());
					pKVAttr->setValue(valueFixed.c_str());
					pDataElementKV->Add(pKVAttr);
				}
			}
#ifdef WIN32
			Arr->swap(MP());
#endif
			Arr->clear();
			CC_SAFE_DELETE(Arr);
		}
	}

	CC_SAFE_DELETE(pKV);

#ifdef WIN32
	mp->swap(MP());
#endif
	mp->clear();
	CC_SAFE_DELETE(mp);

	// �Ƴ�ָ��������
	pDataElement->Del(pos);

	return pDataElementKV;
}

void SIX_UIMgr::LoadAnimationCache(SIX_XmlDataSet *pDataSet)
{
	if (!pDataSet->pDataElement)
		return;

	int buflen = 0;
	char animationName[64] = {0};

	// Name
	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataSet->pDataElement,"Name",pKV);
	if (pos>=0)
	{
		buflen = pKV->getValue().length();
		memcpy(animationName,pKV->getValue().getCString(),buflen);
		animationName[buflen] = 0;
	}
	CC_SAFE_DELETE(pKV);
	pDataSet->pDataElement->Del(pos);

	// ��������֡
	CCAnimation *pAnimation = (CCAnimation*)ParseObject(pDataSet,"Animation");

	// save
	m_AnimationCache.setObject(pAnimation,animationName);
	SIXLog("LoadActionCache.pAnimation[0x%08X][%s]..OK!",pAnimation,animationName);
}

CCAnimation *SIX_UIMgr::GetAnimationFromCache(const char *animationName)
{
	return (CCAnimation*)m_AnimationCache.objectForKey(animationName);
}

void SIX_UIMgr::UnloadAnimationCache()
{
	m_AnimationCache.removeAllObjects();
}

void SIX_UIMgr::LoadFrameCache(SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (!pDataElement)
		return;

	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,"file",pKV);
	if (pos>=0)
	{
		SIXLog("m_FrameCache=%s...Loaded!",pKV->getValue().getCString());
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pKV->getValue().getCString());

		// save
		m_FrameCache.push_back(pKV->getValue().getCString());
	}

	CC_SAFE_DELETE(pKV);

	// ȥ��file����
	pDataElement->Del(pos);
}

void SIX_UIMgr::UnloadFrameCache()
{
	// remove from SpriteFrameCache
	int idx = 0;
	vector<string>::iterator m_iter = m_FrameCache.begin();
	for (m_iter;m_iter!=m_FrameCache.end();)
	{	
		SIXLog("m_FrameCache[%d]=%s...Removed!",idx,m_FrameCache.at(0).c_str());
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(m_FrameCache.at(0).c_str());
		m_iter = m_FrameCache.erase(m_iter);
		idx++;
	}

#ifdef WIN32
	m_FrameCache.swap(vector<string>());
#endif
	m_FrameCache.clear();
}

// Sprite֧���������ַ�ʽ����
// 1��File
// 2��SpriteFrame
CCSprite *SIX_UIMgr::CreateSprite(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	// ���Sprite�Ƿ��Ǵ�File����
	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,"File",pKV);
	if (pos>=0)
	{
		pControl = CCSprite::create(pKV->getValue().getCString());
		CC_SAFE_DELETE(pKV);
		// ȥ��File����
		pDataElement->Del(pos);
	}
	// ��SpriteFrame����
	else
	{
		CC_SAFE_DELETE(pKV);

		/*********************************************************
		����Ƿ��Ǵ�SpriteFrame����
		�������ԣ�Frame/Action����ָ��һ��
		*********************************************************/
		// Ĭ�ϳ�ʼ֡(Frame)
		pKV = new SIX_KV();
		pos = GetAttributeAndPos(pDataElement,"Frame",pKV);
		if (pos>=0)
		{
			// Frame���������SpriteFrameCache��
			CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pKV->getValue().getCString());
			if (!pSpriteFrame)
			{
				CC_SAFE_DELETE(pKV);
				SIXLog("CreateSprite.SpriteFrame[%s].Nil!",pKV->getValue().getCString());
				return 0;
			}

			pControl = CCSprite::createWithSpriteFrame(pSpriteFrame);
			if (!pControl)
			{
				CC_SAFE_DELETE(pKV);
				SIXLog("CreateSprite.SpriteFrame.Create.Failed!");
				return 0;
			}

			// ȥ��DefaultFrame����
			pDataElement->Del(pos);
		}
		CC_SAFE_DELETE(pKV);
	}

	// �ټ�������
	if (LoadControl<CCSprite>(this,(CCSprite*)pControl,pDataElement))
		return (CCSprite*)pControl;
	return 0;
}

CCScale9Sprite *SIX_UIMgr::CreateScale9Sprite(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	// ���Sprite�Ƿ��Ǵ�File����
	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,"File",pKV);
	if (pos>=0)
	{
		pControl = CCScale9Sprite::create(pKV->getValue().getCString());
		CC_SAFE_DELETE(pKV);
		// ȥ��File����
		pDataElement->Del(pos);
	}
	// ��SpriteFrame����
	else
	{
		CC_SAFE_DELETE(pKV);

		/*********************************************************
		����Ƿ��Ǵ�SpriteFrame����
		�������ԣ�Frame/Action����ָ��һ��
		*********************************************************/
		// Ĭ�ϳ�ʼ֡(Frame)
		pKV = new SIX_KV();
		pos = GetAttributeAndPos(pDataElement,"Frame",pKV);
		if (pos>=0)
		{
			// Frame���������SpriteFrameCache��
			CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pKV->getValue().getCString());
			if (!pSpriteFrame)
			{
				CC_SAFE_DELETE(pKV);
				SIXLog("CreateSprite.SpriteFrame[%s].Nil!",pKV->getValue().getCString());
				return 0;
			}

			pControl = CCScale9Sprite::createWithSpriteFrame(pSpriteFrame);
			if (!pControl)
			{
				CC_SAFE_DELETE(pKV);
				SIXLog("CreateSprite.SpriteFrame.Create.Failed!");
				return 0;
			}

			// ȥ��DefaultFrame����
			pDataElement->Del(pos);
		}
		CC_SAFE_DELETE(pKV);
	}

	if (LoadControl<CCScale9Sprite>(this,(CCScale9Sprite*)pControl,pDataElement))
		return (CCScale9Sprite*)pControl;
	return 0;
}

CCAnimation *SIX_UIMgr::CreateAnimation(CCObject *pObject,SIX_XmlDataSet *pDataSet)
{
	if (pObject || !pDataSet || !pDataSet->pDataElement)
		return 0;

	// ѭ������
	int Loops = 0;
	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataSet->pDataElement,"Loops",pKV);
	if (pos>=0)
		Loops = pKV->getValue().intValue();
	CC_SAFE_DELETE(pKV);

	// ֡���
	float DelayPerUnit = 0.0;
	pKV = new SIX_KV();
	pos = GetAttributeAndPos(pDataSet->pDataElement,"DelayPerUnit",pKV);
	if (pos>=0)
		DelayPerUnit = pKV->getValue().floatValue();
	CC_SAFE_DELETE(pKV);

	// �ָ���һ֡
	bool RestoreOriginalFrame = false;
	pKV = new SIX_KV();
	pos = GetAttributeAndPos(pDataSet->pDataElement,"RestoreOriginalFrame",pKV);
	if (pos>=0)
		RestoreOriginalFrame = pKV->getValue().boolValue();
	CC_SAFE_DELETE(pKV);

	// ��������֡����
	int frameCount = 0;
	CCArray *pArray = CCArray::array();
	SIX_XmlDataSet *pSpriteFrameDataSet = 0;
	CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pSpriteFrameDataSet,SIX_XmlDataSet*)
	{
		// ����֡����
		CCSpriteFrame *pSpriteFrame = (CCSpriteFrame*)ParseObject(pSpriteFrameDataSet,"SpriteFrame");
		if (pSpriteFrame)
		{
			pArray->addObject(pSpriteFrame);
			// ��֡������
			frameCount++;
		}
	}
	// ֡���������ݵĻ�
	if (pArray->count())
	{
		pObject = CCAnimation::animationWithSpriteFrames(pArray,DelayPerUnit/*,Loops*/);
		if (pObject)
			((CCAnimation*)pObject)->setRestoreOriginalFrame(RestoreOriginalFrame);
	}
	CC_SAFE_DELETE(pArray);

	return (CCAnimation*)pObject;
}

CCSpriteFrame *SIX_UIMgr::CreateSpriteFrame(CCObject *pObject,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pObject || !pDataElement)
		return 0;

	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,"name",pKV);
	if (pos<0)
	{
		CC_SAFE_DELETE(pKV);
		return 0;
	}

	pObject = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pKV->getValue().getCString());
		
	CC_SAFE_DELETE(pKV);

	// ȥ��file����
	pDataElement->Del(pos);

	return (CCSpriteFrame*)pObject;
}

// -------------------
// ��̬��ť
// -------------------
CCControlButton *SIX_UIMgr::CreateButton(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	// �Ź��񱳾�
	CCScale9Sprite *bgImageNormal = CreateControl<CCScale9Sprite>(this,"norScale9Sprite",pDataElement);
	// ���ٵ��и���̬�Ź��񱳾�
	if (!bgImageNormal)
		return 0;

	CCLabelTTF *pTTFNormal = CreateControl<CCLabelTTF>(this,"norLabelTTF",pDataElement);
	//// ���ٵ��и���̬ttf
	//if (!pTTFNormal)
	//{
	//	CC_SAFE_RELEASE(bgImageNormal);
	//	return 0;
	//}

	// ��һ��~
	if (pTTFNormal)
		pControl = CCControlButton::create(pTTFNormal,bgImageNormal);
	else
		pControl = CCControlButton::create(bgImageNormal);
	if (!pControl)
	{
		CC_SAFE_RELEASE(pTTFNormal);
		CC_SAFE_RELEASE(bgImageNormal);
		return 0;
	}

	// �ӹ�TTF
	CCLabelTTF *pTTFHover = CreateControl<CCLabelTTF>(this,"hovLabelTTF",pDataElement);
	if (pTTFHover)
		((CCControlButton*)pControl)->setTitleLabelForState(pTTFHover,CCControlStateHighlighted);
	// �ӹ��Ź��񱳾�
	CCScale9Sprite *bgImageHover = CreateControl<CCScale9Sprite>(this,"hovScale9Sprite",pDataElement);
	if (bgImageHover)
		((CCControlButton*)pControl)->setBackgroundSpriteForState(bgImageHover,CCControlStateHighlighted);

	// ���TTF
	CCLabelTTF *pTTFSelected = CreateControl<CCLabelTTF>(this,"selLabelTTF",pDataElement);
	if (pTTFSelected)
		((CCControlButton*)pControl)->setTitleLabelForState(pTTFSelected,CCControlStateSelected);
	// ����Ź��񱳾�
	CCScale9Sprite *bgImageSelected = CreateControl<CCScale9Sprite>(this,"selScale9Sprite",pDataElement);
	if (bgImageSelected)
		((CCControlButton*)pControl)->setBackgroundSpriteForState(bgImageSelected,CCControlStateSelected);

	// ����
	CCLabelTTF *pTTFDisabled = CreateControl<CCLabelTTF>(this,"disLabelTTF",pDataElement);
	if (pTTFDisabled)
		((CCControlButton*)pControl)->setTitleLabelForState(pTTFDisabled,CCControlStateDisabled);
	// ���þŹ��񱳾�
	CCScale9Sprite *bgImageDisabled = CreateControl<CCScale9Sprite>(this,"disScale9Sprite",pDataElement);
	if (bgImageDisabled)
		((CCControlButton*)pControl)->setBackgroundSpriteForState(bgImageDisabled,CCControlStateDisabled);

	// �ټ�������
	if (LoadControl<CCControlButton>(this,(CCControlButton*)pControl,pDataElement))
		return (CCControlButton*)pControl;
	return 0;
}

CCProgressTimer *SIX_UIMgr::CreateProgressTimer(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	CCSprite *spr = CreateControl<CCSprite>(this,"Sprite",pDataElement);
	if (!spr)
		return 0;

	pControl = CCProgressTimer::create(spr);
	if (!pControl)
	{
		CC_SAFE_RELEASE(spr);
		return 0;
	}

	// �ټ�������
	if (LoadControl<CCProgressTimer>(this,(CCProgressTimer*)pControl,pDataElement))
		return (CCProgressTimer*)pControl;
	return 0;
}

CCSpriteBatchNode *SIX_UIMgr::CreateSpriteBatchNode(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	// �ȼ���ͼƬ
	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,"file",pKV);
	if (pos<0)
	{
		CC_SAFE_DELETE(pKV);
		return 0;
	}

	pControl = CCSpriteBatchNode::batchNodeWithFile(pKV->getValue().getCString());

	CC_SAFE_DELETE(pKV);
	// ȥ��file����
	pDataElement->Del(pos);

	// �ټ�������
	if (LoadControl<CCSpriteBatchNode>(this,(CCSpriteBatchNode*)pControl,pDataElement))
		return (CCSpriteBatchNode*)pControl;
	return 0;
}

SIX_ListView *SIX_UIMgr::CreateListView(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	// ��������

	// ����������

	// ������������
	int pViewDirection = 0;
	SIX_KV *pKV = new SIX_KV();
	int pos = GetAttributeAndPos(pDataElement,"ViewDirection",pKV);
	if (pos>=0)
	{
		pViewDirection = atoi(pKV->getValue().getCString());
		// �Ƴ�ָ��������
		pDataElement->Del(pos);
	}
	CC_SAFE_DELETE(pKV);
	
	ccColor4B color;
	ParseSingleAttribute(this,&color,"color",pDataElement);

	CCPoint offset;
	ParseSingleAttribute(this,&offset,"offset",pDataElement);

	CCSize size;
	ParseSingleAttribute(this,&size,"size",pDataElement);

	CCSize cellSize;
	ParseSingleAttribute(this,&cellSize,"cellSize",pDataElement);

	pControl = SIX_ListView::create(color,offset,size,cellSize,pViewDirection);

	if (!pControl)
		return 0;

	// ��������
	if (!LoadControl<CCLayerColor>(this,(SIX_ListView*)pControl,pDataElement))
		return 0;

	return (SIX_ListView*)pControl;
}

SIX_ListViewCell *SIX_UIMgr::CreateListViewCell(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement)
{
	if (pControl || !pDataElement)
		return 0;

	pControl = new SIX_ListViewCell();

	if (!pControl)
		return 0;

	// ��������
	if (!LoadControl<CCNode>(this,(SIX_ListViewCell*)pControl,pDataElement))
		return 0;

	return (SIX_ListViewCell*)pControl;
}

CCObject *SIX_UIMgr::ParseObject(SIX_XmlDataSet *pDataSet,const char *nodeName)
{
	if (!pDataSet || !nodeName)
		return 0;

	// ����Root��Comment
	if (compareIgnoreCase(pDataSet->getKey(),"Element"))
		return 0;

	CCObject *pObject = 0;

	// ���������������ƥ��
	if (pDataSet->pDataElement && !compareIgnoreCase(pDataSet->getValue(),nodeName))
	{
		if (!compareIgnoreCase(pDataSet->getValue(),"Animation"))
		{
			pObject = CreateAnimation(pObject,pDataSet);
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"SpriteFrame"))
		{
			pObject = CreateSpriteFrame(pObject,pDataSet->pDataElement);
		}
		else
		{
			SIXLog("SIX_UIMgr.ParseObject.pObject[%s].NoSupported!",pDataSet->getValue().getCString());
			return 0;
		}
	}

	CCAssert(pObject!=0,"SIX_UIMgr.ParseObject.pObject.Nil");

	return pObject;
}

CCNode *SIX_UIMgr::ParseControl(SIX_XmlDataSet *pDataSet,CCNode *pRoot)
{
	if (!pDataSet)
		return 0;

	// ����Root��Comment
	if (compareIgnoreCase(pDataSet->getKey(),"Element"))
		return 0;

	CCNode *pControl = 0;
	// ������������
	bool ControlIsValid = false;

	// �������������
	if (pDataSet->pDataElement)
	{
		// ȫ�ֳ���ͨ��֡���黺��
		if (!compareIgnoreCase(pDataSet->getValue(),"SpriteFrameCache"))
		{
			 LoadFrameCache(pDataSet->pDataElement);
			 return 0;
		}
		// ��ǰ����ͨ�ö�����
		else if (!compareIgnoreCase(pDataSet->getValue(),"Animation"))
		{
			 LoadAnimationCache(pDataSet);
			 return 0;
		}
		// ����Ŀؼ���LoadControl����
		else if (!compareIgnoreCase(pDataSet->getValue(),"Node"))
		{
			pControl = CCNode::create();
			ControlIsValid = LoadControl<CCNode>(this,(CCNode*)pControl,pDataSet->pDataElement);
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"Control"))
		{
			pControl = new CCControl();
			((CCControl*)pControl)->init();
			ControlIsValid = LoadControl<CCControl>(this,(CCControl*)pControl,pDataSet->pDataElement);
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"Layer"))
		{
			pControl = CCLayer::create();
			ControlIsValid = LoadControl<CCLayer>(this,(CCLayer*)pControl,pDataSet->pDataElement);
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"LayerColor"))
		{
			pControl = CCLayerColor::create(ccc4(255,255,255,255));
			ControlIsValid = LoadControl<CCLayerColor>(this,(CCLayerColor*)pControl,pDataSet->pDataElement);
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"LabelTTF"))
		{
			pControl = CCLabelTTF::create();
			ControlIsValid = LoadControl<CCLabelTTF>(this,(CCLabelTTF*)pControl,pDataSet->pDataElement);
		}
		// ����Ŀؼ�Ҫ��CreateXXX����
		else if (!compareIgnoreCase(pDataSet->getValue(),"Sprite"))
		{
			// Sprite�����ӽڵ���CreateSprite�д������
			pControl = CreateSprite(pControl,pDataSet->pDataElement);
			if (pControl)
				ControlIsValid = true;
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"Scale9Sprite"))
		{
			pControl = CreateScale9Sprite(pControl,pDataSet->pDataElement);
			if (pControl)
				ControlIsValid = true;
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"Button"))
		{
			pControl = CreateButton(pControl,pDataSet->pDataElement);
			if (pControl)
				ControlIsValid = true;
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"ProgressTimer"))
		{
			pControl = CreateProgressTimer(pControl,pDataSet->pDataElement);
			if (pControl)
				ControlIsValid = true;
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"SpriteBatchNode"))
		{
			pControl = CreateSpriteBatchNode(pControl,pDataSet->pDataElement);
			if (pControl)
				ControlIsValid = true;
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"ListView"))
		{
			pControl = CreateListView(pControl,pDataSet->pDataElement);
			if (pControl)
				ControlIsValid = true;
		}
		else if (!compareIgnoreCase(pDataSet->getValue(),"ListViewCell"))
		{
			pControl = CreateListViewCell(pControl,pDataSet->pDataElement);
			if (pControl)
			{
				// ListViewCell�ĸ��ڵ������ListView
				SIX_ListView *pFather = dynamic_cast<SIX_ListView*>(pRoot);
				if (!pFather)
				{
					CC_SAFE_DELETE(pControl);
					SIXLog("SIX_UIMgr.ParseControl[%s].pFather.Nil",pDataSet->getValue().getCString());
					CCMessageBox(pDataSet->getValue().getCString(),"Error");
					CCAssert(pControl!=0,"SIX_UIMgr.ParseControl.pFather.Nil");
					return 0;
				}

				// ��AddCell��ʽ��ӵ�ListView
				unsigned int idx = pFather->GetCellCount();
				pFather->AddCell((SIX_ListViewCell*)pControl,idx);

				ControlIsValid = true;
			}
		}
		else
		{
			SIXLog("SIX_UIMgr.ParseControl.pControl[%s].NoSupported!",pDataSet->getValue().getCString());
			return 0;
		}
	}

	if (pControl==0)
	{
		SIXLog("SIX_UIMgr.ParseControl[%s].pControl.Nil",pDataSet->getValue().getCString());
		CCMessageBox(pDataSet->getValue().getCString(),"Error");
		CCAssert(pControl!=0,"SIX_UIMgr.ParseControl.pControl.Nil");
		return 0;
	}

	if (ControlIsValid)
	{
		// �ȼӵ����ڵ�
		if (pRoot)
		{
			// ��ListViewCell�ڵ��ʹ��addChild��ʽ
			if (compareIgnoreCase(pDataSet->getValue(),"ListViewCell"))
				pRoot->addChild(pControl);
		}

		// �ټ��������ӽڵ�
		if (pDataSet->pNode)
		{
			SIX_XmlDataSet *pChildDataSet = 0;
			CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pChildDataSet,SIX_XmlDataSet*)
			{
				ParseControl(pChildDataSet,pControl);
			}
		}
	}
	else
	{
		CC_SAFE_DELETE(pControl);
		SIXLog("SIX_UIMgr.ParseControl.KV[%s][%s].Failed!",
			pDataSet->getKey().getCString(),
			pDataSet->getValue().getCString()
		);
		return 0;
	}

	return pControl;
}

int SIX_UIMgr::ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet)
{
	SIXLog("SIX_UIMgr.Parse=%d",pXmlDataSet->GetChildrenCount());
	SIX_XmlDataSet *pDataSet = 0;
	unsigned int i=0;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();

	CCARRAY_FOREACH_T(pXmlDataSet->GetChildren(),pDataSet,SIX_XmlDataSet*)
	{
		ParseControl(pDataSet,GetParent());
	}

	return 0;
}

int SIX_UIMgr::Run()
{
	return 0;
}

int SIX_UIMgr::Release()
{
	return 0;
}

void SIX_UIMgr::doEvents(CCObject* pSender, CCControlEvent event)
{
	/*CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	lua_State* m_state = pEngine->getLuaState();
	lua_pushlightuserdata(m_state, pSender);
	::lua_pushstring(m_state,pSender->getObjName());
	switch (event)
	{
		case CCControlEventTouchDown:			pEngine->executeGlobalFunction("onCCControlEventTouchDown",2);break;
		case CCControlEventTouchDragInside:		pEngine->executeGlobalFunction("onCCControlEventTouchDragInside",2);break;
		case CCControlEventTouchDragOutside:	pEngine->executeGlobalFunction("onCCControlEventTouchDragOutside",2);break;
		case CCControlEventTouchDragEnter:		pEngine->executeGlobalFunction("onCCControlEventTouchDragEnter",2);break;
		case CCControlEventTouchDragExit:		pEngine->executeGlobalFunction("onCCControlEventTouchDragExit",2);break;
		case CCControlEventTouchUpInside:		pEngine->executeGlobalFunction("onCCControlEventTouchUpInside",2);break;
		case CCControlEventTouchUpOutside:		pEngine->executeGlobalFunction("onCCControlEventTouchUpOutside",2);break;
		case CCControlEventTouchCancel:			pEngine->executeGlobalFunction("onCCControlEventTouchCancel",2);break;
		case CCControlEventValueChanged:		pEngine->executeGlobalFunction("onCCControlEventValueChanged",2);break;
		default:SIXLog("doEvents.Unknown[%d]",event);break;
	}*/
}

void SIX_UIMgr::setAllDirty(bool bDirty)
{
	m_bDirty = bDirty;
}

bool SIX_UIMgr::getAllDirty()
{
	return m_bDirty;
}
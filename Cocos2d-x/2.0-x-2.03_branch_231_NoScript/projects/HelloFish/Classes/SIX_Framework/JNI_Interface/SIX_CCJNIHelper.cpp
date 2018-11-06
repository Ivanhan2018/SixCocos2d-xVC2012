#include "SIX_CCJNIHelper.h"

#define  CCJNIHLPER_NAME "com/sixdivisions/framework/CCJNIHelper"

SIX_CCJNIHelper::SIX_CCJNIHelper()
{
	m_iCPUCore = 0;
	memset(m_fCPUFrequency,0,sizeof(m_fCPUFrequency));
}

SIX_CCJNIHelper::~SIX_CCJNIHelper()
{
}

// C++=>JNI
void SIX_CCJNIHelper::showMsgBoxYesOrNoJNI(const char *message,const char *title)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jmi;
	if(JniHelper::getStaticMethodInfo(jmi,CCJNIHLPER_NAME,"showMsgBoxYesOrNo","([Ljava/lang/String;)V"))
	{
		jclass str_cls = jmi.env->FindClass("java/lang/String");

		jstring str1 = jmi.env->NewStringUTF(SIX_Utility::GetInstance()->G2U(title).c_str());
		jstring str2 = jmi.env->NewStringUTF(SIX_Utility::GetInstance()->G2U(message).c_str());

		jobjectArray arrs = jmi.env->NewObjectArray(2,str_cls,0);
		jmi.env->SetObjectArrayElement(arrs,0,str1);
		jmi.env->SetObjectArrayElement(arrs,1,str2);
		jmi.env->CallStaticVoidMethod(jmi.classID,jmi.methodID,arrs);
	}
#endif
	SIXLog("getPackageNameJNI[%s]",this->getPackageNameJNI());
	SIXLog("getCurrentLanguageJNI[%s]",this->getCurrentLanguageJNI());
	SIXLog("getVersionSDKJNI[%s]",this->getVersionSDKJNI());
	SIXLog("getVersionReleaseJNI[%s]",this->getVersionReleaseJNI());
	SIXLog("getVersionKernelJNI[%s]",this->getVersionKernelJNI());
	SIXLog("getDeviceModelJNI[%s]",this->getDeviceModelJNI());
	SIXLog("getSerialJNI[%s]",this->getSerialJNI());
	SIXLog("getCPUInfoJNI[%s]",this->getCPUInfoJNI());
	SIXLog("----------------------------");
	SIXLog("getCPUCore[%d]",this->getCPUCore());
	for (int i=0;i<this->getCPUCore();i++)
		SIXLog("getCPUFrequency[%d][%.2f]",i,this->getCPUFrequency(i));
	SIXLog("----------------------------");
	SIXLog("getCPUABIJNI[%s]",this->getCPUABIJNI());
	SIXLog("getCPUABI2JNI[%s]",this->getCPUABI2JNI());
	SIXLog("getDisplayMetricsJNI[%s]",this->getDisplayMetricsJNI());
	SIXLog("getMacAddressJNI[%s]",this->getMacAddressJNI());
	SIXLog("getIMSIJNI[%s]",this->getIMSIJNI());
	SIXLog("getIMEIJNI[%s]",this->getIMEIJNI());
	SIXLog("getIMEISVJNI[%s]",this->getIMEISVJNI());
	SIXLog("getPhoneNumberJNI[%s]",this->getPhoneNumberJNI());
	SIXLog("getPropertiesKVJNI[%s]",this->getPropertiesKVJNI());
	SIXLog("getAPKPath[%s]",this->getAPKPath().c_str());
}

void SIX_CCJNIHelper::killProcessJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "killProcess", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

const char *SIX_CCJNIHelper::getPackageNameJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getPackageName", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
	return 0;
}

const char* SIX_CCJNIHelper::getCurrentLanguageJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getCurrentLanguage", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getVersionSDKJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getVersionSDK", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getVersionReleaseJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getVersionRelease", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getVersionKernelJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getVersionKernel", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getDeviceModelJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getDeviceModel", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getSerialJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getSerial", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getCPUInfoJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getCPUInfo", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);
        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getCPUABIJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getCPUABI", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getCPUABI2JNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getCPUABI2", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getDisplayMetricsJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getDisplayMetrics", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getMacAddressJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getMacAddress", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getIMSIJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getIMSI", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getIMEIJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getIMEI", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getIMEISVJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getIMEISV", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getPhoneNumberJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getPhoneNumber", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

const char* SIX_CCJNIHelper::getPropertiesKVJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CCJNIHLPER_NAME, "getPropertiesKV", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        t.env->DeleteLocalRef(str);

        return ret->m_sString.c_str();
    }
#endif
    return 0;
}

void SIX_CCJNIHelper::setAPKPath(string path)
{
	m_sAPKPath = path;
}

string SIX_CCJNIHelper::getAPKPath()
{
	return m_sAPKPath;
}

void SIX_CCJNIHelper::setCPUCore(int core)
{
	m_iCPUCore = core;
}

int SIX_CCJNIHelper::getCPUCore()
{
	return m_iCPUCore;
}

void SIX_CCJNIHelper::setCPUFrequency(int core,float frequency)
{
	if (core>=32)
	{
		// impossible... 
		CCMessageBox(/*Hey man!are you from the future?*/XorStr<0xBC,33,0x36177688>("\xF4\xD8\xC7\x9F\xAD\xA0\xAC\xE2\xA5\xB7\xA3\xE7\xB1\xA6\xBF\xEB\xAA\xBF\xA1\xA2\xF0\xA5\xBA\xB6\xF4\xB3\xA3\xA3\xAD\xAB\xBF\xE4"+0x36177688).s,0);
		return;
	}
	m_fCPUFrequency[core] = frequency;
}

float SIX_CCJNIHelper::getCPUFrequency(int core)
{
	if (core>=32)
	{
		// impossible... 
		return 0.0f;
	}
	return m_fCPUFrequency[core];
}

// JNI==>C++
extern "C"
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void Java_com_sixdivisions_framework_CCJNIHelper_setAPKPath(JNIEnv*  env, jobject thiz, jstring apkPath)
	{
        SIX_CCJNIHelper::GetInstance()->setAPKPath(JniHelper::jstring2string(apkPath));
    }

	// 通过JNI从Android传递CPU频率数组回来处理
	// 以下3步即可完成JNI=>C++数据转换
	// Cool.Cat
	void Java_com_sixdivisions_framework_CCJNIHelper_setCPUFrequency(JNIEnv* env,jobject thiz,jfloatArray frequency)
	{
		int core = env->GetArrayLength(frequency);
		SIX_CCJNIHelper::GetInstance()->setCPUCore(core);
		// 1、把简单类型的数组(float)转化成本地类型的数组(jfloat)，并返回jfloat数组指针v
		jfloat *v = env->GetFloatArrayElements(frequency,0);
		// 2、再通过指针v进行数据拷贝处理
		for (int i=0;i<core;i++)
			SIX_CCJNIHelper::GetInstance()->setCPUFrequency(i,v[i]);
		// 3、当然拷贝完后还要记得释放之~
		env->ReleaseFloatArrayElements(frequency,v,0);
	}

	void Java_com_sixdivisions_framework_CCJNIHelper_SayEveryBodyHi()
	{
		CCLog(SIX_Utility::GetInstance()->G2U(/*山上的朋友你们好！*/XorStr<0x44,19,0x6E0108E0>("\x8D\xF8\x8F\x88\xFD\x8D\x8F\xB8\x9F\x9C\x8A\xAC\x93\x96\xE8\x90\xF7\xF4"+0x6E0108E0).s).c_str());
	}

	// 这里有个问题：jni/main.cpp中SIX_World是new出来的，同时CCApplication->run()直接跳出
	// 并不像win32下做循环，所以SIX_World会成为野指针，不会触发析构
	void Java_com_sixdivisions_framework_CCJNIHelper_ExitApplication()
	{
		CCLog(SIX_Utility::GetInstance()->G2U(/*ExitApplication!*/XorStr<0x4C,17,0x161B8F9C>("\x09\x35\x27\x3B\x11\x21\x22\x3F\x3D\x36\x37\x23\x31\x36\x34\x7A"+0x161B8F9C).s).c_str());
		// 卸载脚本引擎
		CCScriptEngineManager::purgeSharedManager();
		// 终结引擎主循环
		CCDirector::sharedDirector()->end();
		CCLog(SIX_Utility::GetInstance()->G2U(/*ExitApplication.Done!*/XorStr<0xCC,22,0xF283359D>("\x89\xB5\xA7\xBB\x91\xA1\xA2\xBF\xBD\xB6\xB7\xA3\xB1\xB6\xB4\xF5\x98\xB2\xB0\xBA\xC1"+0xF283359D).s).c_str());
	}
#endif
}
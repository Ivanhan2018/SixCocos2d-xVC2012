/*********************************************************
Name：SIX_CCJNIHelper
Desc：C++<=>JNI交互接口扩展，
      cc2dx原有扩展不要做改动，以后就在这里做文章了！
Auth：Cool.Cat@2013-09-25
**********************************************************
----------------------------------------------------------
Java类型	本地类型		描述
----------------------------------------------------------
boolean		jboolean		C/C++8位整型
byte		jbyte			C/C++带符号的8位整型
char		jchar			C/C++无符号的16位整型
short		jshort			C/C++带符号的16位整型
int			jint			C/C++带符号的32位整型
long		jlong			C/C++带符号的64位整型
float		jfloat			C/C++32位浮点型
double		jdouble			C/C++64位浮点型
Object		jobject			任何Java对象，或者没有对应java类型的对象
Class		jclass			Class对象
String		jstring			字符串对象
Object[]	jobjectArray	任何对象的数组
boolean[]	jbooleanArray	布尔型数组
byte[]		jbyteArray		比特型数组
char[]		jcharArray		字符型数组
short[]		jshortArray		短整型数组
int[]		jintArray		整型数组
long[]		jlongArray		长整型数组
float[]		jfloatArray		浮点型数组
double[]	jdoubleArray	双浮点型数组
----------------------------------------------------------
*********************************************************/
#pragma once
#include <SIX_Typedef.h>
#include <TSingleton.h>
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"
#include <android/log.h>
#include <jni.h>
#endif

class SIX_CCJNIHelper:public TSingleton<SIX_CCJNIHelper>{
public:
	SIX_CCJNIHelper();
	virtual ~SIX_CCJNIHelper();
public:
	void showMsgBoxYesOrNoJNI(const char*,const char*title="提示");
	void killProcessJNI();
	// 获取包名
	const char *getPackageNameJNI();
	// 获取当前语言
	const char *getCurrentLanguageJNI();
	// 获取SDK版本
	const char *getVersionSDKJNI();
	// 获取系统版本
	const char *getVersionReleaseJNI();
	// 获取内核版本
	const char *getVersionKernelJNI();
	// 获取设备型号
	const char *getDeviceModelJNI();
	// 获取设备序列号
	const char *getSerialJNI();
	// 获取CPU名称
	const char *getCPUInfoJNI();
	// 获取CPUABI
	const char *getCPUABIJNI();
	// 获取CPUABI2
	const char *getCPUABI2JNI();
	// 获取宽高信息
	const char *getDisplayMetricsJNI();
	// 获取mac地址
	const char *getMacAddressJNI();
	// 获取IMSI(International Mobile Subscriber Identification Number)，从SIM卡中获取
	const char *getIMSIJNI();
	// 获取IMEI(International Mobile Equipment Identification Number)，从设备中获取
	const char *getIMEIJNI();
	// 获取IMEI SV(International Mobile Equipment Identification Number Software Version)，通常似乎跟IMEI一致？
	const char *getIMEISVJNI();
	// 获取电话号码(国内用户基本都获取不到，国内运营商使用IMSI作为传输标识，所以通过SIM获取号码基本无法获取电话号码，可考虑用getIMEIJNI替代)
	const char *getPhoneNumberJNI();
	// 获取属性集值对
	const char *getPropertiesKVJNI();

public:
	void setAPKPath(string);
	string getAPKPath();

	void setCPUCore(int);
	int getCPUCore();

	void setCPUFrequency(int core,float frequency);
	float getCPUFrequency(int core);
private:
	// 包路径
	string m_sAPKPath;
	// CPU核心数量
	int m_iCPUCore;
	// CPU核心频率
	float m_fCPUFrequency[32];
};
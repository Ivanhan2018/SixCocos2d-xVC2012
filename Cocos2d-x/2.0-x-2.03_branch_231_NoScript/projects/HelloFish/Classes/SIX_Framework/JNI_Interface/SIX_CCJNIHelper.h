/*********************************************************
Name��SIX_CCJNIHelper
Desc��C++<=>JNI�����ӿ���չ��
      cc2dxԭ����չ��Ҫ���Ķ����Ժ���������������ˣ�
Auth��Cool.Cat@2013-09-25
**********************************************************
----------------------------------------------------------
Java����	��������		����
----------------------------------------------------------
boolean		jboolean		C/C++8λ����
byte		jbyte			C/C++�����ŵ�8λ����
char		jchar			C/C++�޷��ŵ�16λ����
short		jshort			C/C++�����ŵ�16λ����
int			jint			C/C++�����ŵ�32λ����
long		jlong			C/C++�����ŵ�64λ����
float		jfloat			C/C++32λ������
double		jdouble			C/C++64λ������
Object		jobject			�κ�Java���󣬻���û�ж�Ӧjava���͵Ķ���
Class		jclass			Class����
String		jstring			�ַ�������
Object[]	jobjectArray	�κζ��������
boolean[]	jbooleanArray	����������
byte[]		jbyteArray		����������
char[]		jcharArray		�ַ�������
short[]		jshortArray		����������
int[]		jintArray		��������
long[]		jlongArray		����������
float[]		jfloatArray		����������
double[]	jdoubleArray	˫����������
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
	void showMsgBoxYesOrNoJNI(const char*,const char*title="��ʾ");
	void killProcessJNI();
	// ��ȡ����
	const char *getPackageNameJNI();
	// ��ȡ��ǰ����
	const char *getCurrentLanguageJNI();
	// ��ȡSDK�汾
	const char *getVersionSDKJNI();
	// ��ȡϵͳ�汾
	const char *getVersionReleaseJNI();
	// ��ȡ�ں˰汾
	const char *getVersionKernelJNI();
	// ��ȡ�豸�ͺ�
	const char *getDeviceModelJNI();
	// ��ȡ�豸���к�
	const char *getSerialJNI();
	// ��ȡCPU����
	const char *getCPUInfoJNI();
	// ��ȡCPUABI
	const char *getCPUABIJNI();
	// ��ȡCPUABI2
	const char *getCPUABI2JNI();
	// ��ȡ�����Ϣ
	const char *getDisplayMetricsJNI();
	// ��ȡmac��ַ
	const char *getMacAddressJNI();
	// ��ȡIMSI(International Mobile Subscriber Identification Number)����SIM���л�ȡ
	const char *getIMSIJNI();
	// ��ȡIMEI(International Mobile Equipment Identification Number)�����豸�л�ȡ
	const char *getIMEIJNI();
	// ��ȡIMEI SV(International Mobile Equipment Identification Number Software Version)��ͨ���ƺ���IMEIһ�£�
	const char *getIMEISVJNI();
	// ��ȡ�绰����(�����û���������ȡ������������Ӫ��ʹ��IMSI��Ϊ�����ʶ������ͨ��SIM��ȡ��������޷���ȡ�绰���룬�ɿ�����getIMEIJNI���)
	const char *getPhoneNumberJNI();
	// ��ȡ���Լ�ֵ��
	const char *getPropertiesKVJNI();

public:
	void setAPKPath(string);
	string getAPKPath();

	void setCPUCore(int);
	int getCPUCore();

	void setCPUFrequency(int core,float frequency);
	float getCPUFrequency(int core);
private:
	// ��·��
	string m_sAPKPath;
	// CPU��������
	int m_iCPUCore;
	// CPU����Ƶ��
	float m_fCPUFrequency[32];
};
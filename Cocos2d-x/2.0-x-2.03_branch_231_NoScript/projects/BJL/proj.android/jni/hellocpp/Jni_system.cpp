#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "Jni_system.h"
#include "JniHelper.h"
#define  CLASS_NAME "game/com/zjdddz/yinghuafei/HelperAndroid"

using namespace cocos2d;

extern "C"
{
	//��JAVA�����ʾ��ֵ����
	void showRechageLayer(const char* userId,const char* userLevel,const char * dialogID)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"showRechangeDialog","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
		{
			jstring jUserID = t.env->NewStringUTF(userId); 
			jstring jUserLevel = t.env->NewStringUTF(userLevel); 
			jstring jDialogID = t.env->NewStringUTF(dialogID); 
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jUserID, jUserLevel,jDialogID); 
			t.env->DeleteLocalRef(jUserID); 
			t.env->DeleteLocalRef(jUserLevel); 
			t.env->DeleteLocalRef(jDialogID); 
		}
	}

	void showFeedBackLayer()
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"showFeedBackDialog","()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);  
		}
	}

	void checkUpdate()
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"checkVersionUpdate","()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);  
		}
	}

	void onLineServer()
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"toOnLineServer","()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);  
		}
	}

	void toUserProtion(const char* str)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"toUserProtion","(Ljava/lang/String;)V"))
		{
			jstring jstr = t.env->NewStringUTF(str); 
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr); 
			t.env->DeleteLocalRef(jstr); 
		}
	}

	void downloadAndriodGame(const char* gameId)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"downLoadGame","(Ljava/lang/String;)V"))
		{
			jstring jGameID = t.env->NewStringUTF(gameId); 
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jGameID); 
			t.env->DeleteLocalRef(jGameID); 
		}
	}

	int getGameExist(int gameID)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"isAvilible","(I)I"))
		{
			jint _int;
			_int = t.env->CallStaticIntMethod(t.classID, t.methodID,gameID);
			return _int;
		}
		return -1;
	}

	void openGame(const char* gameID)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"switchGame","(Ljava/lang/String;)V"))
		{
			jstring jGameID = t.env->NewStringUTF(gameID); 
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jGameID); 
			t.env->DeleteLocalRef(jGameID); 
		}
	}

	//���Ͷ���
	void sendOrderID(int _orderID)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"getOrderID","(I)V"))
		{
			t.env->CallStaticIntMethod(t.classID, t.methodID,_orderID);
		}
	}

	//�����쳣
	void networkAnomaly()
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"networkAnomaly","()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);  
		}
	}

	//�����Ƿ���� 1. ����ǿ�Ƹ��� 2. ������ǿ�Ƹ��� 3.���˸���
	void updateAndriodGame(const char* updateType,const char* packgeSize,const char* downLoadUrl)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t,CLASS_NAME,"updateGame","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
		{
			jstring jupdateType = t.env->NewStringUTF(updateType); 
			jstring jpackgeSize = t.env->NewStringUTF(packgeSize); 
			jstring jdownLoadUrl = t.env->NewStringUTF(downLoadUrl); 
			t.env->CallStaticVoidMethod(t.classID, t.methodID,jupdateType,jpackgeSize,jdownLoadUrl); 
			t.env->DeleteLocalRef(jupdateType); 
			t.env->DeleteLocalRef(jpackgeSize); 
			t.env->DeleteLocalRef(jdownLoadUrl); 
		}
	}

	//java����C++���� ��ֵ����ֵ
	void Java_game_com_zjdddz_yinghuafei_Helper_sendRechargeableCard(JNIEnv *env, jobject thiz, jstring type, jstring dwCardFee, jstring cardnum, jstring cardpassword)
	{
		const char *_cardType = env->GetStringUTFChars(type,NULL);
		const char *_cardFee = env->GetStringUTFChars(dwCardFee,NULL);
		const char *_cardNum = env->GetStringUTFChars(cardnum,NULL);
		const char *_cardPassword = env->GetStringUTFChars(cardpassword,NULL);
		RechargeableCard(_cardType,_cardFee,_cardNum,_cardPassword);
		env->ReleaseStringUTFChars(type, _cardType);
		env->ReleaseStringUTFChars(dwCardFee, _cardFee);
		env->ReleaseStringUTFChars(cardnum, _cardNum);
		env->ReleaseStringUTFChars(cardpassword, _cardPassword);
	}
	//java����C++���� �Ͻ𿨳�ֵ
	void Java_game_com_zjdddz_yinghuafei_Helper_sendPurpleGoldIslandCard(JNIEnv *env, jobject thiz, jstring cardnum, jstring cardpassword)
	{
		const char *_cardNum = env->GetStringUTFChars(cardnum,NULL);
		const char *_cardPassword = env->GetStringUTFChars(cardpassword,NULL);
		PurpleGoldIslandCard(_cardNum,_cardPassword);
		env->ReleaseStringUTFChars(cardnum, _cardNum);
		env->ReleaseStringUTFChars(cardpassword, _cardPassword);
	}

	void Java_game_com_zjdddz_yinghuafei_Helper_sendIMEI(JNIEnv *env, jobject thiz, jstring MacAddress)
	{
		const char *_MacAddress = env->GetStringUTFChars(MacAddress,NULL);
		IMEI(_MacAddress);
		env->ReleaseStringUTFChars(MacAddress, _MacAddress);
	}


	//Java����C++ ���ذٷֱ�
	void Java_game_com_zjdddz_yinghuafei_Helper_downloadPesent(JNIEnv *env, jobject thiz,jstring pesent,jstring gameID)
	{
		const char * _pesent = env->GetStringUTFChars(pesent,NULL);
		const char * _gameID = env->GetStringUTFChars(gameID,NULL);
		if(_pesent == NULL)
		{
			outInout("_pesent");
		}
		if(_gameID == NULL)
		{
			outInout("gameID");
		}
		downloadPesent(_pesent,_gameID);
		env->ReleaseStringUTFChars(pesent, _pesent);
		env->ReleaseStringUTFChars(gameID, _gameID);
	}

	//JAVA ����c++ ȡ������
	void Java_game_com_zjdddz_yinghuafei_Helper_cannelDowload(JNIEnv *env, jobject thiz)
	{
		CCLOG("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		cannelGameDownload();
	}

	//JAVA ����c++ ���ID
	void Java_game_com_zjdddz_yinghuafei_Helper_getOrderInfo(JNIEnv *env, jobject thiz,jstring PayName,jstring chargeNum)
	{
		const char * _PayName = env->GetStringUTFChars(PayName,NULL);
		const char * _chargeNum = env->GetStringUTFChars(chargeNum,NULL);
		getOrder(_PayName,_chargeNum);
		env->ReleaseStringUTFChars(PayName, _PayName);
		env->ReleaseStringUTFChars(chargeNum, _chargeNum);
	}
	//JAVA ����c++ ��ֵ�ɹ�
	void Java_game_com_zjdddz_yinghuafei_Helper_rechangerOver(JNIEnv *env, jobject thiz,jstring coinsNum)
	{
		const char * _coinsNum = env->GetStringUTFChars(coinsNum,NULL);
		//const char * _goldEggNum = env->GetStringUTFChars(goldEggNum,NULL);
		orderOver(_coinsNum/*,_goldEggNum*/);
		CCLog("coinsNum in jnisystem %d",coinsNum);
		env->ReleaseStringUTFChars(coinsNum, _coinsNum);
		//env->ReleaseStringUTFChars(goldEggNum, _goldEggNum);
	}

	//JAVA ����C++����������Ϣ
	void Java_game_com_zjdddz_yinghuafei_Helper_newMessage(JNIEnv *env, jobject thiz)
	{
		newUMMessage();
	}

	//JAVA ����c++ �Ʋ�ȡ����ֵ
	void Java_game_com_zjdddz_yinghuafei_Helper_cannelRechanger(JNIEnv *env, jobject thiz)
	{
		CCLog("######################################1111111#");
		cannelRechanger();
	}

	void Java_game_com_zjdddz_yinghuafei_Helper_sendChannel(JNIEnv *env, jobject thiz,jstring channelstr)
	{
		const char * _channelstr = env->GetStringUTFChars(channelstr,NULL);
		getChannl(_channelstr);
		env->ReleaseStringUTFChars(channelstr, _channelstr);
	}

	void Java_game_com_zjdddz_yinghuafei_Helper_sendVersionCode(JNIEnv *env, jobject thiz,jstring versionstr)
	{
		const char * _versionstr = env->GetStringUTFChars(versionstr,NULL);
		getVersion(_versionstr);
		env->ReleaseStringUTFChars(versionstr, _versionstr);
	}

	//void showTipDialog(const char *title, const char *msg) 
	//{ 
	//	JniMethodInfo t; 
	//	if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showTipDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) 
	//	{ 
	//		jstring jTitle = t.env->NewStringUTF(title); 
	//		jstring jMsg = t.env->NewStringUTF(msg); 
	//		t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle, jMsg); 
	//		t.env->DeleteLocalRef(jTitle); 
	//		t.env->DeleteLocalRef(jMsg); 
	//	} 
	//}
	//void Java_game_com_zjdddz_Helper_setPackageName(JNIEnv *env, jobject thiz, jstring packageName)
	//{
	//	const char *pkgName = env->GetStringUTFChars(packageName, NULL);
	//	setPackageName(pkgName);
	//	env->ReleaseStringUTFChars(packageName, pkgName);
	//}

	//void Java_game_com_zjdddz_Helper_setLogin(JNIEnv *env, jobject thiz, jstring jstr)
	//{
	//	const char *str = env->GetStringUTFChars(jstr, NULL);
	//	setLogin(str);
	//	env->ReleaseStringUTFChars(jstr, str);
	//}

	//void Java_game_com_zjdddz_Helper_setUserInfo(JNIEnv *env, jobject thiz, jstring jstr)
	//{
	//	const char *str = env->GetStringUTFChars(jstr, NULL);
	//	setUserInfo(str);
	//	env->ReleaseStringUTFChars(jstr, str);
	//}

	//void Java_game_com_zjdddz_Helper_setUserName(JNIEnv *env, jobject thiz, jstring jstr)
	//{
	//	const char *str = env->GetStringUTFChars(jstr, NULL);
	//	setUserName(str);
	//	env->ReleaseStringUTFChars(jstr, str);
	//}

	//void Java_game_com_zjdddz_Helper_setLevelStandart(JNIEnv *env, jobject thiz, jstring jstr)
	//{
	//	const char *str = env->GetStringUTFChars(jstr, NULL);
	//	setLevelStandart(str);
	//	env->ReleaseStringUTFChars(jstr, str);
	//}

	//void Java_game_com_zjdddz_Helper_setDangweiStandart(JNIEnv *env, jobject thiz, jstring jstr)
	//{
	//	const char *str = env->GetStringUTFChars(jstr, NULL);
	//	setDangweiStandart(str);
	//	env->ReleaseStringUTFChars(jstr, str);
	//}

	//void Java_game_com_zjdddz_Helper_setMusic(JNIEnv *env, jobject thiz, jstring jstr)
	//{
	//	const char *str = env->GetStringUTFChars(jstr, NULL);
	//	setMusic(str);
	//	env->ReleaseStringUTFChars(jstr, str);
	//}

	//void Java_game_com_zjdddz_Helper_exitView(JNIEnv *env, jobject thiz)
	//{
	//	exitView();
	//}

	//void gameEnd()
	//{
	//	  
	//	////��̬����ʾ��1.�޲������޷���ֵ---------------------------------$$$$$$-----------------------------
	//	JniMethodInfo minfo;//����Jni������Ϣ�ṹ��
	//	//getStaticMethodInfo �κ�������һ��boolֵ��ʾ�Ƿ��ҵ��˺���
	//	bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"testFun", "()V");

	//	if (!isHave) 
	//	{
	//		CCLog("testFunc: not exit");
	//	}else
	//	{
	//		CCLog("testFunc: exit");
	//		//���ô˺���
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	//	}
	//	CCLog("testFunc-java finish");
	//}

	//void updateServerOnBackground()
	//{
	//	JniMethodInfo minfo;
	//	bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"updateServerOnBackground", "()V");
	//	if (isHave)
	//	{
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	//	}

	//}

	//void initFinish()
	//{
	//	JniMethodInfo minfo;
	//	bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"initFinish", "()V");
	//	if (isHave)
	//	{
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	//	}
	//}

	//void setUserScore(const char* str)
	//{

	//	JniMethodInfo minfo;
	//	bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"playerSet_lscore", "(Ljava/lang/String;)V");

	//	if (!isHave) 
	//	{
	//		CCLog("setUserScore: not exit");
	//	}else
	//	{
	//		CCLog("setUserScore:  exit");
	//		jstring stringArg = minfo.env->NewStringUTF(str);
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);

	//		minfo.env->DeleteLocalRef(stringArg);
	//		minfo.env->DeleteLocalRef(minfo.classID);
	//	}
	//	CCLog("setUserScore-java finish");
	//}

	//void setUserEggs(const char* str)
	//{
	//	JniMethodInfo minfo;
	//	bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"playerSet_eggs", "(Ljava/lang/String;)V");

	//	if (!isHave) 
	//	{
	//		CCLog("setUserEggs: not exit");
	//	}else
	//	{
	//		CCLog("setUserEggs:  exit");
	//		jstring stringArg = minfo.env->NewStringUTF(str);
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);

	//		minfo.env->DeleteLocalRef(stringArg);
	//		minfo.env->DeleteLocalRef(minfo.classID);
	//	}
	//	CCLog("setUserEggs-java finish");
	//}

	////���õ�λ
	//void setParking(const char* str)
	//{
	//	JniMethodInfo minfo;
	//	bool bHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"setParking", "(Ljava/lang/String;)V");

	//	if (bHave) 
	//	{
	//		jstring stringArg = minfo.env->NewStringUTF(str);
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);

	//		minfo.env->DeleteLocalRef(stringArg);
	//		minfo.env->DeleteLocalRef(minfo.classID);
	//	}

	//	CCLOG("gameend setParking1");
	//}

	//void jniExitView()
	//{
	//	JniMethodInfo minfo;
	//	bool bHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"jniExitView", "()V");

	//	if (bHave) 
	//	{
	//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
//	}
//}

//void liantong_pay(const char* yuan)
//{
//	JniMethodInfo minfo;
//	bool bHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"liantong_pay", "(Ljava/lang/String;)V");
//	if (bHave) 
//	{
//		jstring stringArg = minfo.env->NewStringUTF(yuan);
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);
//		minfo.env->DeleteLocalRef(stringArg);
//		minfo.env->DeleteLocalRef(minfo.classID);
//
//	}
//}
//
//void openWebview()
//{
	//JniMethodInfo minfo;
	//bool isHave = JniHelper::getMethodInfo(minfo,"game/com/dt_zjh/Game","openWebview", "()V");
	//if (isHave)
	//{
	//	minfo.env->CallVoidMethod(minfo.classID, minfo.methodID);
	//}

	//JniMethodInfo minfo;  
	//getStaticMethodInfo���ж�Java��̬�����Ƿ���ڣ����Ұ���Ϣ���浽minfo��  
	//����1��JniMethodInfo  
	//����2��Java�����+����  
	//����3��Java��������  
	//����4�������������ͺͷ���ֵ����  
//	bool isHave = JniHelper::getStaticMethodInfo(minfo,"game/com/dt_zjh/Game","getInstance","()Lgame/com/dt_zjh/Game;");  
//	jobject jobj;//�����  
//	if (isHave) 
//	{  
//		//����ĵ���getInstance������Test��Ķ���  
//		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
//
//		isHave = JniHelper::getMethodInfo(minfo,"game/com/dt_zjh/Game","openWebview","()V");  
//		if (isHave) 
//		{  
//			//����openWebview, ����1��Test����   ����2������ID  
//			minfo.env->CallVoidMethod(jobj, minfo.methodID);  
//		}  
//	} 
//}

//void liantong_pay(int yuan)
//{
//	JniMethodInfo minfo;
//	bool bHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"liantong_pay", "(Ljava/lang/I;)V");
//	if (bHave) 
//	{
//		//jstring stringArg = minfo.env->NewStringUTF(yuan);
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, yuan);
//		//minfo.env->DeleteLocalRef(stringArg);
//		minfo.env->DeleteLocalRef(minfo.classID);

//	}
//}
}
#endif

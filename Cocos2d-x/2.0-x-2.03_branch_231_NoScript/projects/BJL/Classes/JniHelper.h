
#ifndef JNI_HELPER_H
#define JNI_HELPER_H

#include "cocos2d.h"
#include "entity/EntityMgr.h"
#include "ans/AnsString.h"
#include "common/Define.h"
#include "../proj.android/jni/hellocpp/Jni_system.h"
#include "globalUnits/GlobalUnits.h"
#include "gui/TaskInfo.h"
#include "configMgr/ConfigMgr.h"

using namespace cocos2d;

inline void showAndroidRechageLayer(const char* userId,const char* userLevel,const char* dialogID)
{
	//�͵ȼ� = 1 �еȼ� = 2 �ߵȼ� = 3 ��X = 1 ûX = 2
	showRechageLayer(userId,userLevel,dialogID);
}

inline void showAndroidFeedBackLayer()
{
	showFeedBackLayer();
}

inline void checkVersionToUpdate()
{
	checkUpdate();
}

inline void toPhoneSever()
{
	onLineServer();
}

inline void toAndridUserProtion(const char* str)
{
	toUserProtion(str);
}

inline void toSendAndroidOrder(int orderID)
{
	sendOrderID(orderID);
}

inline void toUpdateGame(std::string id,std::string str,const char* url)
{
	updateAndriodGame(id.c_str(),str.c_str(),url);
}

inline void IMEI(const char* address)
{
	CCLog("AAAAAAAAAAAmacaddress = %s",address);
	EntityMgr::instance()->setMacAddress(CCString::createWithFormat("%s%s","M",address)->getCString());
	CCLog("cccccccccccccccccccccccc%s",address);
}

inline void downloadGame(const char* gameID)
{
	downloadAndriodGame(gameID);
}

inline void RechargeableCard(const char* type, const char* dwCardFee, const char* cardnum, const char* cardpassword)
{
	CCLOG("type:%s,dwCardFee:%s,cardnum:%s,cardpassword:%s,",type,dwCardFee,cardnum,cardpassword);
	if(EntityMgr::instance()->getDispatch()->connectLoginServer())
	{
		EntityMgr::instance()->getDispatch()->phoneCardRechange(type,dwCardFee,cardnum,cardpassword);
	}
}

inline void PurpleGoldIslandCard(const char* cardnum, const char* cardpassword)
{
	CCLOG("cardnum:%s,cardpassword:%s,",cardnum,cardpassword);
	if(EntityMgr::instance()->getDispatch()->connectLoginServer())
	{
		EntityMgr::instance()->getDispatch()->isLnadCardRecarge(cardnum,cardpassword);
	}
}

inline void getOrder(const char* payName,const char* chargeNum)
{
	if (EntityMgr::instance()->getDispatch()->getLoginState() == enLogin_Server)
	{
		if(!EntityMgr::instance()->getDispatch()->connectLoginServer())
		{
			networkAnomaly();
			return;
		}
	}
	
	EntityMgr::instance()->getDispatch()->sendOrderInfo(payName,ans::AnsString::string2Int(chargeNum));
	CCLOG("payName = %s,string2Int(chargeNum) = %d",payName,ans::AnsString::string2Int(chargeNum));
	CCLOG("payName = %s,atoi(chargeNum) = %d",payName,atoi(chargeNum));
	
}

inline void orderOver(const char* coinsNum/*,const char* goldEggNum*/)
{
	g_GlobalUnits.getGolbalUserData()->lScore = ans::AnsString::string2Int(coinsNum);
	CCLOG("coinsNum in jnihelper  = %d",ans::AnsString::string2Int(coinsNum));
	//g_GlobalUnits.getGolbalUserData()->lGoldEggs = (int)goldEggNum;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_UPDATESCOREANDGOLDEGG,NULL);
}

inline void cannelRechanger()
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_CANNELRECHANGER,NULL);
}

inline void getChannl(const char* str)
{
	CCLog("*****************************channelstr = %s",str);
	
	ConfigMgr::instance()->m_Config.m_channelStr = str;
}

inline void getVersion(const char* str)
{
	CCLog("11111111111111111111version = %s",str);
	//�ֽ�汾 �õ��汾��

	int versionFix[3];
	versionFix[0] = 0;
	versionFix[1] = 0;
	versionFix[2] = 0;
	/* У��x_sVer */
	bool ret = true;
	if(str==NULL || strlen(str)<5)
	{
		ret = false;
		CCLog("version error size");
	}

	size_t iLen = strlen(str);
	int iCot = 0;

	for(size_t i=0; i<iLen; i++)
	{
		if(str[i]==0x2E)
		{
			iCot++;
		}
		else if(str[i]<0x30 || str[i]>0x39)
		{
			ret = false;
			CCLog("have error char");
		}
	}

	if(iCot!=2)
	{
		ret = false;
		CCLog("less point");
	}

	/* ��ȡ */
	if(ret)
	{
		sscanf(str, "%d.%d.%d", versionFix+0, versionFix+1, versionFix+2);
	}
	ConfigMgr::instance()->m_VersionInfo.m_nHighVersion = versionFix[0];
	ConfigMgr::instance()->m_VersionInfo.m_nMiddleVersion = versionFix[1];
	ConfigMgr::instance()->m_VersionInfo.m_nLowVersion = versionFix[2];
}

inline void downloadPesent(const char* pesent,const char* gameID)
{
	int _pesent = atoi(pesent);
	int _gameID = atoi(gameID);
	CCLOG("downloadgame gameID = %d,pesent = %d",_gameID,_pesent);

	if (EntityMgr::instance()->m_nDownLoadPe == _pesent)
	{
		return;
	}
	if(_pesent%2==0)
	{
		CCInteger* inter = CCInteger::create(_pesent);
		//EntityMgr::instance()->m_nDownLoadPe = _pesent;

		switch (_gameID)
		{
		case GameId_DDZ:
			{
				break;
			}
		case GameId_PHZ:
			{
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_RUNBREAD,inter);
				if (_pesent >= 100)
				{
					//EntityMgr::instance()->getDispatch()->connectLoginServer();
					//EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_PHZ,1);
					EntityMgr::instance()->m_nDownLoadPe = 1;
				}
				break;
			}
		case GameId_CSMJ:
			{
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_CHANGSHAMAJIADOWNLOAD,inter);
				if (_pesent >= 100)
				{
					//EntityMgr::instance()->getDispatch()->connectLoginServer();
					//EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_CSMJ,1);
					EntityMgr::instance()->m_nDownLoadPe = 1;
				}
				break;
			}
		case GameId_ZJH:
			{
				break;
			}
		case GameId_SDK:
			{
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_THREETOONE,inter);
				if (_pesent >= 100)
				{
					//EntityMgr::instance()->getDispatch()->connectLoginServer();
					//EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_SDH,1);
					EntityMgr::instance()->m_nDownLoadPe = 1;
				}
				break;
			}
		case GameId_PDK:
			{
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_RUNFASTDOWNLOAD,inter);
				if (_pesent >= 100)
				{
					//EntityMgr::instance()->getDispatch()->connectLoginServer();
					//EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_PDK,1);
					EntityMgr::instance()->m_nDownLoadPe = 1;
				}
				break;
			}

		default:
			{
				assert(false);
				return;
			}
		}
	}
}

inline int isGameExit(int gameID)
{
	CCLOG("GAMEID = %d,exist = %d",gameID,getGameExist(gameID));
	return getGameExist(gameID);
}

inline void openAndriodGame(const char* gameID)
{
	openGame(gameID);
}

inline void outInout(const char* str)
{
	CCLOG("%s  is null ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`",str);
}

inline void cannelGameDownload()
{
	CCLOG("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	EntityMgr::instance()->m_nDownLoadPe = 1;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_CANNELDOWNLOADGAME,NULL);
	CCLOG("cccccccccccccccccccccccccccccccccccccccccccccc");
}

inline void newUMMessage()
{
	TaskInfo* info = TaskInfo::ShareTaskInfo();
	info->m_nUMMessage++;
}

//void setPackageName(const char *packageName)
//{
//	CCLog("packageName: %s", packageName); 
//}
//
//void setLogin(const char* str)
//{
//
//	//CCDirector::sharedDirector()->end();
//	EntityMgr::instance()->setLogin(str);
//}
//
//void setUserInfo(const char* str)
//{
//	EntityMgr::instance()->setUserInfo(str);
//}
//
//void setUserName(const char* str)
//{
//	EntityMgr::instance()->setUserName(str);
//}
//
//void setLevelStandart(const char* str)
//{
//	EntityMgr::instance()->setLevelStandart(str);
//}
//
//void setDangweiStandart(const char* str)
//{
//	EntityMgr::instance()->setDangweiStandart(str);
//}
//
//void setMusic(const char* str)
//{
//	EntityMgr::instance()->setMusic(str);
//}
//
//void exitView()
//{
//	CCLog("exitView1");
//	tagSigOutObj tag;
//	tag.bSigOut = true;
//	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_SIGOUT,&tag);
//	CCLog("exitView2"); 
//}

#endif //JNI_HELPER_H

//
//  GlobalUnits.h
//
//  ����ļ�Ϊ�˸�pc�ı���һ�£���ʱ�������Ժ���ܻ�ɵ�
//  Created by zhouwei on 13-6-9.
//
//

#ifndef __GlobalUnits__
#define __GlobalUnits__

#include <iostream>
#include "common/Define.h"
#include "common/GlobalDef.h"
#include <vector>
#include "ans/AnsTaskPool.h"
#include "globalUnits/GlobalUnits.h"
#include "common/struct.h"
typedef std::vector<tagGameServer> GameServerList;
typedef std::vector<tagUserData*> GameUsrDateList;

//ȫ���û�����
struct tagGlobalUserData
{
	//��������
	//������Ϣ
	WORD								wFaceID;						//ͷ������
	DWORD								dwUserID;						//�û� I D
	DWORD								dwGameID;						//ͷ�� I D
	DWORD								dwGroupID;						//��������

	char								szAccounts[NAME_LEN];			//��¼�ʺ�
	char								szPassWord[PASS_LEN];			//��¼����
	char								szGroupName[GROUP_LEN];			//��������
	char								szNickName[NAME_LEN];			//����ǳ�
	DWORD								sdServerID;						//����������ID
	DWORD								sdKindID;						//��������ϷID
	LONG								lWeekMingci;					//�û���������
	LONG								lWeekWinCount;					//�û����ܾ���һ������

	//�û�����
	BYTE								cbGender;						//�û��Ա�
	BYTE								cbMember;						//��Ա�ȼ�
	BYTE								cbVisitor;						//�ο�����
	int									nKeepDays;						//������½����
	int									nCanGet;						//�Ƿ�����ȡ
	int									nTodayScore;					//������
	int									nTomorrowScore;					//������
	int									nRelieveCount;					//ʣ����ȡ�ȼý����


	//������Ϣ
	LONG								lScore;							//�û�����
	LONG								lStorage;
	LONG								lLostCount;						//�������
	LONG								lWinCount;						//Ӯ������
	LONG								lTotalCount;					//������
	LONG								lFleeCount;						//������Ŀ
	LONG								lExperience;					//�û�����
	LONG								lGoldEggs;						//�û���
	LONG								lWeiWang;						//�û����� 
	char                               szZipCode[ZIP_CODE_LEN];        //��������
	char                               szDwellingPlace[CITY_LEN];      //������Ϣ
	char								szDescribeString[DESCRIBE_LEN];	//������Ϣ

	tagGlobalUserData()
	{
		memset(this, 0, sizeof(*this));
	}
};

class CServerListMgr
{
public:
	CServerListMgr();
	~CServerListMgr();

	void sortItems();
	void insertItem(tagGameServer item[],unsigned int nCount);
	void removeItem(tagGameServer* pItem);
	void clearItem();

	//��ȡȫ��������
	DWORD getServerOnLineCount();

	tagGameServer getCurrentServer();    //��ȡ��ǰ������

	tagGameServer getGameServer(unsigned int nKind);

	tagGameServer getGameServerByIndex(int index);			//��ȡ�ڼ�������		add by wangjun
private:
	GameServerList m_GameServerList;      //�������б�
};

class CUserDateMgr
{
public:
	void insertItem(tagUserData* pItem);
	void removeItem(tagUserData* pItem);
private:
	GameUsrDateList m_GameUsrDateList;
};

//ȫ����Ϣ��
class CGlobalUnits
{
public:
	CGlobalUnits();
	~CGlobalUnits();
private:
	tagGlobalUserData*   m_GloblaUserData;
public:
	//CServerListMgr m_ServerListMgr;
	CUserDateMgr m_UserDateMgr;
public:
	void setGolbalUserData(tagGlobalUserData* tag);

	//��ȡ�û���Ϣ
	tagGlobalUserData* getGolbalUserData() { return m_GloblaUserData; }

public:
	unsigned int m_nGabalUserLevel;
	unsigned int m_nOnlineCount;
	bool m_bDownVisible;

	unsigned int m_nHighVer;        //��Ϸ�ͻ��˰汾
	unsigned int m_nLowVer;
	char m_szText[128];             //������Ϣ
	char m_szTextTips[128];         //������ʾ��Ϣ

};


class CGlobalMath
{
public:
	//��ȡ�û�ͷ��
	static string getUserFace(unsigned int faceID,unsigned int sex)
	{
		faceID -=1;
		char buf[50];
		if (faceID <= 7 && sex == 1)        //Ϊ��
		{
			sprintf(buf, "dtgb_touxiangnan%d.png.png",faceID + 1);
			return  buf;
		}

		faceID -= 20;

		sprintf(buf, "dtgb_touxiangnv%d.png",faceID % 8 + 1);
		return buf;
	}

	//��ȡ�û��ȼ�ͼƬ
	static string getUserLevel(int level)
	{
		std::string tmpStr;
		switch (level)
		{
		case 0:
			tmpStr = "dtgb_userlevel0.png";
			break;
		case 1:
			tmpStr = "dtgb_userlevel1.png";
			break;
		case 2:
			tmpStr = "dtgb_userlevel2.png";
			break;
		case 3:
			tmpStr = "dtgb_userlevel3.png";
			break;
		case 4:
			tmpStr = "dtgb_userlevel4.png";
			break;
		case 5:
			tmpStr = "dtgb_userlevel5.png";
			break;
		case 6:
			tmpStr = "dtgb_userlevel6.png";
			break;
		case 7:
			tmpStr = "dtgb_userlevel7.png";
			break;
		default:
			break;
		}
		return tmpStr;
	}
};

//ȫ����Ϣ
extern CGlobalUnits g_GlobalUnits;


//typedef ans::TaskPool<tagBuffer> TaskPool;
//extern TaskPool g_TaskPool;

#endif /* defined(__GlobalUnits__) */

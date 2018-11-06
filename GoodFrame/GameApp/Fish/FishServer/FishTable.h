
#ifndef FISH_TABLE_H
#define FISH_TABLE_H

#include "./ThreadGuard.h"

#include "./GameSkeletonID.h"
#include "./TaskMsgResult.h"
#include "./IBaseTable.h"
#include "../GameMsg/ProFish.h"//add by Ivan_han

#include "FishTraceMgr.h"
#include "BulletMgr.h"
#include "AwardPool.h"//add by Ivan_han

enum ENUM_GAME_PHASE
{
	ENUM_GAME_START,
	ENUM_GAME_END,
};

#define M_PI       3.14159265358979323846

#define USESLEEP 0	// 1 ��ʾģ��������������ʱ��ͬ����0 ��ʾ����������

//add by Ivan_han 20130624
//////////////////////////////////////////////////////////////////////////
#define VIEW_WIDTH  1280
#define VIEW_HEIGHT  733

#define IDI_BUILD_TRACE				1									//�����ڲ����������Ⱥ�켣
#define IDI_CLEAR_TRACE				2									//���ٹ켣
#define IDI_CHANGE_SCENE			3									//�л�����
#define IDI_REGULAR_FISH			4									//�����ڲ�������켣
#define IDI_BONUS					5									//�����ʽ�
#define IDI_SYS_MESSAGE				6									//ϵͳ��Ϣ
//#define IDI_REGULAR_READY			7									//����׼��
//#define IDI_REGULAR_END			    8									//�������
#define IDI_STATUS                  9                                   //���״̬
#define IDI_Adjust_Vh              10                                   //��⽱��״̬��������ˮλ�꣬add by Ivan_han 20130730
#define IDI_Adjust_Vl               11                                   //��⽱��״̬��������ˮλ�꣬add by Ivan_han 20130730
#define IDI_AWARD_POOL_SAVE         12                                   //���ش���
#define IDI_TestCommonPool              13                                   //������ͨ�ؼ��״̬
#define IDI_TestBonusPool               14                                  //����ʽ�ؼ��״̬
#define IDI_FIRE_OVERTIME			15									// ����ʱ add by cxf
#define IDI_GAME_END_TIMER			16									// ������Ϸ��ʱ��
#define IDI_BULLET_OVERTIME			17									// �ӵ���ʱ

#define TIMES_INFINITY     DWORD (-1)

#define TIME_BUILD_TRACE			2000								//�����ڲ����������Ⱥ�켣
#define TIME_CLEAR_TRACE			10000								//���ٹ켣
#define TIME_CHANGE_SCENE			30000								//�л�����
#define TIME_CAPTURE		        120000				                //�����ڳ���ʱ��
#define TIME_OFF		            60000					            //�����ڳ���ʱ��

//#define TIME_REGULAR_READY			10000								//10����׼��
#define TIME_REGULAR_FISH			10000							    //�����ڲ�������켣
//#define TIME_REGULAR_END			20000								//20��������Ⱥ����
#define TIME_SYS_MESSAGE			5*60								//ϵͳ��Ϣ
#define TIME_FIRE_OVERTIME			(10000)								// ����ʱʱ��
#define TIME_BULLET_OVERTIME		(10000)								// ����ӵ���ʱ���

#define FISH_ALIVE_TIME				20							//���ʱ��

#define MAX_FLOAT_NUM              4                                  //�ڸ�������������

#define FIER_OVERTIME_WARNING_TIME	40									// ����ʱ��ʾ
#define FIER_OVERTIME_TIME			60									// ����ʱʱ��
#define FIER_BULLET_OVERTIME		15									// �ӵ����ʱ��
//////////////////////////////////////////////////////////////////////////

class IRoomMgr;

class CFishTable : public IBaseTable
{
public:
	CFishTable(void);
	~CFishTable(void);

public:
	// ��ʼ��
	void OnInit();
	// ��ʼ����������
	void OnSitDownInit(int iSeatNo);
	// ��Ӧ������Ϣ
	void OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen);

public:
	//--- Ҫ�Ӹ���̳еĴ��麯�� --------------------------------

	// ����
	virtual int OnCut(LONGLONG lUserId);

	// ����������Ӧ�����������û����������¼����ʱ�Ż���Ӧ
	virtual int OnRecomeAfterCut(int iSeatNo);

	// ���Ӷ�ʱ����Ӧ
	virtual int OnTableTimer(int iTableNo, int iIDEvent);

	//��Ϸ��ʼ
	virtual int OnGameBegin();

	// ����
	virtual int OnRaiseHand(int iSeatNo);

	//��Ϸ����
	virtual int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	// ����֮ǰ
	virtual int OnLeaveSeatBefore(LONGLONG lUserId, int iSeatNo);

	// ����֮��
	virtual int OnLeaveSeatLast(int iSeatNo);

	// ��ȡ̨�� �������ӵ�
	virtual void TradeFee();

	// ����
	virtual int OnAccounts(int iSeatNo);

	// �û�����
	virtual void OnUserSitDown(int iSeatNo);

	//�������˷��������ʱ���ٵ���::GetTickCount64()��add by Ivan_han 20130627
	static unsigned long long GetTickCount64();

public:

	// ����
	int fire(int iSeatNo, SHOT_FIRE* pReal);
	/// �ӵ�����
	int BulletReflection(int iSeatNo, BULLET_REFLECTION* pReal);
	/// ������
	int CaptureFish(int iSeatNo, CAPTURE_FISH* pReal);
		
	TBulletID getNewBulletID();
	CFishTraceMgr& getFishTraceMgr();

	// �������/��Ϻը���Ų��Ҷ�Ӧ����������
	static int GetIndexFromArray(TFishKind fishType);

private:
	int Check(SEAT_INFO** pSeatInfo, int iSeatNo);

private:
	// �����ڵĵȼ�
	void UserSetGunGrade(int iSeatNo,Req_SetGunGrade * pReq);
	// �����ӵ�
	void UserBuyBullet(int iSeatNo, USER_BUY_BULLET * userBuyBullet);
	// ɾ�����ж�ʱ��
	void KillAllTimer();
	// ��鳬ʱ�˳�����
	void OnCheckOverTime();
	// ��������
	void OnMatchEnd();
	// ����û��ӵ�
	bool OnCheckAllUserBullet();
	// ����
	void SortMatch(CMD_GameUserInfo matchInfo[]);

protected:
	CFishTraceMgr	m_stFishTraceMgr;	// ��켣������
	CBulletMgr		m_stBulletMgr;		// �ӵ�����
	CAwardPool      m_stAwardPool;      //���ض���

private:
	// �����û���Ϣ
	CMD_GameUserInfo m_gameUserInfo[GAME_PLAYER_COUNT];
	// ����ʣ��ʱ��
	int m_iMatchCountDown;
	// ��Ϸ�׶�
	ENUM_GAME_PHASE m_eGamePhase;		//������Ϸ״̬

};

#endif
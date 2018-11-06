#ifndef CONFIG_H
#define CONFIG_H
#include "GameTable.h"

/*
	��ȡxml�ļ��еĶ�ʱ�����ʱ�����ò���,add by Ivan_han 20131018
	�������ļ����Ʒ��̶��ƣ����ڲ���,add by Ivan_han 20131102
*/
class SangongConfig
{
public:
	SangongConfig(const char *xmlFileName=0);
	static SangongConfig & Instance();
	int LoadData(const char *xmlFileName);

	int GetCallBankerTime()const;
	int GetCallBankerEndTime()const;
	int GetCallScoreTime()const;
	int GetCallScoreEndTime()const;
	int GetShowCardTime()const;
public:
	bool m_HasLoadOK;//�Ƿ���سɹ���
	/*
	<!-- ������Ϸ״̬��ʱ�����ʱ��(��λ:����)���ֱ��ӦTIME_CALL_BANKER�ꡢTIME_CALL_BANKER_END�ꡢTIME_CALL_SCORE�ꡢTIME_CALL_SCORE_END�ꡢTIME_SHOW_CARD��--> 
	<GameStateMgr CallBankerTime="5000" CallBankerEndTime="4000" CallScoreTime="5000" CallScoreEndTime="5000" ShowCardTime="10000" /> 
	*/
	int m_CallBankerTime;
	int m_CallBankerEndTime;
	int m_CallScoreTime;
	int m_CallScoreEndTime;
	int m_ShowCardTime;

	//û������ׯ������Ǯ������ׯ�ĸ���
	float m_BankerProb;

	/*
		<!--���̶��ƣ����ڲ���-->
		<FixCard Enable="1" Banker="0x31,0x26,0x01" NoBanker="0x03,0x1A,0x15"></FixCard>
	*/
	int m_Enable;
	TCardData m_cbBankerCardData[MAX_COUNT];
	TCardData m_cbNoBankerCardData[MAX_COUNT];
};

#endif


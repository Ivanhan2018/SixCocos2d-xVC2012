#ifndef CONFIG_H
#define CONFIG_H
#include "GameTable.h"

/*
	读取xml文件中的定时器间隔时间配置参数,add by Ivan_han 20131018
	由配置文件控制发固定牌，利于测试,add by Ivan_han 20131102
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
	bool m_HasLoadOK;//是否加载成功过
	/*
	<!-- 三公游戏状态定时器间隔时间(单位:毫秒)，分别对应TIME_CALL_BANKER宏、TIME_CALL_BANKER_END宏、TIME_CALL_SCORE宏、TIME_CALL_SCORE_END宏、TIME_SHOW_CARD宏--> 
	<GameStateMgr CallBankerTime="5000" CallBankerEndTime="4000" CallScoreTime="5000" CallScoreEndTime="5000" ShowCardTime="10000" /> 
	*/
	int m_CallBankerTime;
	int m_CallBankerEndTime;
	int m_CallScoreTime;
	int m_CallScoreEndTime;
	int m_ShowCardTime;

	//没有人抢庄，则安排钱多者作庄的概率
	float m_BankerProb;

	/*
		<!--发固定牌，用于测试-->
		<FixCard Enable="1" Banker="0x31,0x26,0x01" NoBanker="0x03,0x1A,0x15"></FixCard>
	*/
	int m_Enable;
	TCardData m_cbBankerCardData[MAX_COUNT];
	TCardData m_cbNoBankerCardData[MAX_COUNT];
};

#endif


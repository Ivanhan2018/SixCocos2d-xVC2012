#ifndef		 __CC_SCENEDATA_WUCAN__
#define		__CC_SCENEDATA_WUCAN__
#include "cocos2d.h"
USING_NS_CC;
#include "CMD_DDZ.h"
#include "CMD_DDZClient.h"
#include "DDZLogic.h"
#define CREATE_FUNC_MSG(__TYPE__) \
static __TYPE__* create(int v) \
{ \
	__TYPE__ *pRet = new __TYPE__(v); \
	pRet->autorelease(); \
	return pRet; \
}

enum Game_State
{
	Game_null=1,				//û��ʼ
	Game_Start,					//���ƿ�ʼ
	Game_landLord,			//������
	Game_Run,					//����
	Game_Over,				//��Ϸ����
};

enum
{
	msgToView_UserInfor=1,				//--����������Ϣ
	msgToView_start,					//--��Ϸ��ʼ
	msgToView_startView,				//--��ʼЧ������
	msgToView_addView,					//--�ӱ�����
	msgToView_sendCard,					//--����
	msgToView_backCard,					//--����
	msgToView_openCard,					//--����
	msgToView_landLord,					//--������
	msgToView_beiLv,							//--���ʱ仯
	msgToview_LordView,					//--�������ֱ仯
	msgToView_time,						
	msgToView_outCard,
	msgToView_passCard,
	msgToView_gameOver,							//--��Ϸ����
	msgToView_SettmentUser,					//--��Ϸ����������Ϣ
	msgToView_openCardNum,					//--viewHandCard����
	msgToview_TimeCallBack,						//--ʱ��ص�  Time ����
	msgToView_OnLine,								//--���������ʾ
	msgToView_Reconnect,						//--��������
	msgToView_socketoffConnect,				//--����Ͽ��Զ�����
	msgToView_socketoff,							//--����Ͽ������ش���
	msgToView_VoiceAndFace,					//--���������
	msgToView_huafeidian,							//--���ѵ�
	msgToView_Close,								//--ǿ�ƹر�
	msgToView_RoomLimit,						//--��������

	msgToLogic_openStart,
	magToLogc_gameStart,
	msgToLogc_openCard,
	msgToLogc_LandLord,
	msgToLogic_outCard,
	msgToLogic_passCard,
	msgToLogic_MoreGame,
	magToLogc_jiabei,							//--�ӱ�
	msgToLogic_face,								//--����
	msgToLogic_changeTable
};

//�����˵�ö��
enum
{
	menu_visibleStartMenuItem = 1,	//���ƿ�ʼ
	menu_startMenuItem,				//��ͨ��ʼ
//	menu_menuBarItem,				//�˵���
	menu_rechargemenuItem,			//���ٳ�ֵ
	menu_outCardMenuItem,			//����
	menu_passOutCardMenuItem,		//��Ҫ
	menu_hintMenuItem,				//��ʾ
	menu_jiaoDiZhuItem,				//�е���
	menu_buJiaoItem,				//����
	menu_qiangDiZhuItem,			//������
	menu_passQiangDiZhuItem,		//����
	menu_visibleCardItem,			//����X2
	menu_doubleItem,				//�ӱ�
	menu_unDoubleItem,				//���ӱ�
	menu_settlementDetial,			//��������
	menu_again,						//����һ��
	menu_menuBarTalkItem,			//�˵������찴ť
	menu_menuBarRobotItem,			//�˵����йܰ�ť
	menu_menuBarOptionsItem,		//�˵������ð�ť
	menu_menuBarTaskItem,			//�˵�������ť
	menu_menuBarBackItem,			//�˵������ذ�ť
	menu_MenuBarPullItem,			//�˵���������ť
	menu_visibleCardStartItem,		//���ƹ����е����ƿ�ʼ
	menu_number,					//���ƿ�ʼ��ť����
	menu_OutAgency,			//ȡ���й�
	menu_changeTable,	//���ƿ�ʼ
};

//--������Ϣ����
class CCuserInfor:public CCInteger
{
public:
	CCuserInfor(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCuserInfor);
	WORD		m_userInforID;		//�û�id
	LONG		m_score;			//����
	WORD		m_gender;			//�Ա�
	LONG		m_GoldEggs;			//���ѵ�
	char			m_PosName[32];		//����
	char          m_name[32];
};

//--���ƿ�ʼ��Ϣ
class CCopenStart:public CCInteger
{
public:
	CCopenStart(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCopenStart);
	WORD				m_bCurrentUser;                     //��ʼ�û� 
	bool					m_bOpenCard;							//���ƿ�ʼ
};

//--������Ϣ
class CCsendCard: public CCInteger
{
public:
	CCsendCard(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCsendCard);
	BYTE			m_handCardData[MAX_COUNT];
	WORD		m_handCardNum;
	bool			m_bOpen;
	bool			m_bEffect;
	WORD		m_userID;
};

//--������Ϣ
class CCopenCard: public CCInteger
{
public:
	CCopenCard(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCopenCard);
	WORD m_openID;
};

//--������
class CClandLord: public CCInteger
{
public:
	CClandLord(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CClandLord);
	WORD		m_landID;
	WORD		m_LandKey;
	bool			m_isLand;
};

//--��ʾʱ��
class CCtimeControl:public CCInteger
{
public:
	CCtimeControl(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCtimeControl);
	WORD		m_timeUserID;
	WORD		m_timeNum;
	Game_State	m_gameState;			//--Game_landLord <2 Ϊ�е��� >2Ϊ������
	WORD		m_timeKey;					//--Game_Run 0Ϊ�����״γ��Ʋ��������ƣ�1Ϊ�����״γ��Ʋ������ƣ�2Ϊ�Լ��״γ��ƣ�3Ϊ��ͨ����			
	WORD		m_BankUser;
};

//--��ҳ���
class CCoutCard:public CCInteger
{
public:
	CCoutCard(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCoutCard);
	BYTE		m_outkCard[MAX_COUNT];				//�����˿�
	WORD  m_numCard;
	WORD  m_outUser;
	WORD  m_bankUser;
};

//--�������
class CCpassCard:public CCInteger
{
public:
	CCpassCard(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCpassCard);
	WORD m_passUser;
};

//--��Ϸ����
class CCgameOver:public CCInteger
{
public:
	CCgameOver(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCgameOver);
	//CMD_S_GameConclude m_gameEndData;
	CMD_S_GameEnd m_gameEndData;
	WORD					m_UserID;
	bool						m_isPochang;
};

//--���Ʊ�����Ϣ
class CCviewOpenCardNum:public CCInteger
{
public:
	CCviewOpenCardNum(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCviewOpenCardNum);
	WORD  m_num;
};

//--�ӱ�����
class CCaddView:public CCInteger
{
public:
	CCaddView(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCaddView);
	WORD			m_addID;
	WORD			m_AddType;		//--�ӱ����ͣ�1 ���֣� 2Ӱ�أ�3.����
};

//--���Ʊ仯
class CCbackData:public CCInteger
{
public:
	CCbackData(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCbackData);
	BYTE   m_data[GAME_PLAYER];
	WORD	m_taskKey;
	bool    m_isNew;
};

//--���ʱ仯
class CCbeilv:public CCInteger
{
public:
	CCbeilv(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCbeilv);
	WORD		m_beilv;
	WORD		m_base;
};

//--��������
class CConline: public CCInteger
{
public:
	CConline(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CConline);
	WORD    m_userID;
	bool        m_isOnline;
};

//--����
class CCfaceAndVioce: public CCInteger
{
public:
	CCfaceAndVioce(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCfaceAndVioce);
	int m_Type;//��1���� 2������
	int m_KeyID;
	int m_UserID;
	char voice[512];
};

//--��������
class CClandView:public CCInteger
{
public:
	CClandView(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CClandView);
	int m_landUserID;
};

//���������Ϣ
class CCSettmentUserMessage:public CCInteger
{
public:
	CCSettmentUserMessage(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCSettmentUserMessage);
	int m_userId;//�û�id
	int m_diZhuId;//����id
	int m_updScore;//�仯�ķ���
	int m_isJiabei;//�Ƿ�ӱ�
	char m_nikeName[32];//�ǳ�
};

//--���ѵ�仯
class CChuafeidian:public CCInteger
{
public:
	CChuafeidian(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CChuafeidian);
	int  m_huafeidian;
};

//--��������
class CCRoomLimit:public CCInteger
{
public:
	CCRoomLimit(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCRoomLimit);
	int  m_RoomLimitKey;			//--1��̫���ˣ�2̫����
};
#endif



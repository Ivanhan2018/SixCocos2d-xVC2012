#ifndef CMD_PAOHUZI_HEAD_FILE
#define CMD_PAOHUZI_HEAD_FILE
#include "common/Define.h"
///////////////////////////////////////////////////////////////////////////////////////
//�����궨��

//#define KIND_ID						ID_LAND						        //��Ϸ I D
#define GAME_PLAYER					3									//��Ϸ����
//#define GAME_NAME					TEXT("��������Ϸ")					//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_GOLD)	//��Ϸ����
#define MAX_COUNT					20
#define GAME_WIDTH				1024
#define GAME_HEIGHT				738

//���������λ��
#define CHAT_DLG_X					740                     
#define CHAT_DLG_Y					650
////////////////////////////////////////////////////////////////////////////////////////

//����������ṹ
#define REC_SUB_S_SEND_CARD				100									//��������
#define REC_SUB_S_LAND_SCORE			101									//�з�����
#define REC_SUB_S_GAME_START			102									//��Ϸ��ʼ
#define REC_SUB_S_OUT_CARD				103									//�û�����
#define REC_SUB_S_PASS_CARD				104									//��������
#define REC_SUB_S_GAME_END				105									//��Ϸ����
#define REC_SUB_S_SPRING                106                                 //������Ϣ
#define REC_SUB_S_OUTCARD_TIMES         108                                 //���ƴ���    
#define REC_SUB_S_LOOK_TRUSTEE          109                                 //�йܲ�ѯ
#define REC_SUB_S_WARN_INFO             111                                 //������Ϣ
#define REC_SUB_S_OFFLINE_CARD          125                                 //���߳���
#define REC_SUB_S_USER_OFFLINE          150                                 //��Ҷ���
#define REC_SUB_S_DAOFAN                151                                 //�û�����
#define REC_SUB_S_OPENCARD			152									//�û�����
#define REC_SUB_S_TIMETOCLOSE			154								//��ɢ�û�
#define GS_WK_SCORE                    50                                   //�з�״̬        

//�������Ϣ
#define SUB_S_GAME_READY             5001                //֪ͨ�ͻ��˷���׼������
#define SUB_C_GAME_READY             5002                //֪ͨ�ͻ��˷���׼������
#define SUB_S_ALL_READY              5003                //֪ͨ�ͻ����Ѿ�׼���õ���
#define SUB_C_ALL_READY              5004                //֪ͨ������Ѿ�׼���õ���
#define SUB_C_ANDROCHAIR             5005                //���������Ӻ�
//#define SUB_C_MATCH_TYPE             5006                //��������
#define SUB_SC_READYTIMEOUT					72				//׼����ʱ
#define SUB_S_GAMESTART					5008				//��Ϸ��ʼ
/////////////////////////////////////////////////////////////////////////////////////////

//�ͻ�����Ϣ
#define SUB_C_CLIENT_READY           4001                //�ͻ���׼������
//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define REC_SUB_C_LAND_SCORE			1									//�û��з�
#define REC_SUB_C_OUT_CART				2									//�û�����
#define REC_SUB_C_PASS_CARD				3									//��������
#define REC_SUB_C_TRUSTEE				4									//�й���Ϣ
#define REC_SUB_C_GAME_END              5                                   //��Ϸ����
#define REC_SUB_C_LOOKTRUSTEE           6                                   //��ѯ�й�
#define REC_SUB_C_WARN_INFO             12									//������Ϣ
#define REC_SUB_C_TURN_COUNT            13									//��������
#define REC_SUB_C_CONTINUE              14                                  //��������
#define REC_SUB_C_DAOFAN                15                                  //�û�����
#define	REC_SUB_S_GOLDEGG               16                                  //�ͽ�
#define REC_SUB_S_RESED_CARD            17                                   //���·��ƣ����ھ���
#define REC_SUB_C_OPNE_CARD				18								//--�������
#define REC_SUB_S_BEILV						20								//--���ʱ仯
#define REC_SUB_S_ONLINE					22								//--������߱�־
#define REC_SUB_C_OVER						24								//--�ͻ����������������ڲ���
//----------------------------

//--��Ҷ���������־
struct CMD_S_UserOffLine
{
	WORD    m_userID;
	bool        m_isOnline;
};

//�����˿�
struct CMD_S_SendAllCard
{
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE								bCardData[GAME_PLAYER][MAX_COUNT];			//�˿���
	BYTE                            bMingPai[MAX_COUNT];                           //����
	BYTE								bBackCardData[GAME_PLAYER];					//�����˿�
	LONG							lBaseScore;							//��������
	bool								bDog;								//gou
};


//��Ϸ�з�
struct CMD_S_StatusScore
{
	BYTE							bLandScore;							//��������
	LONG							lBaseScore;							//��������
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE							bScoreInfo[GAME_PLAYER];			//�з���Ϣ
	BYTE							bCardData[GAME_PLAYER][20];			//�����˿�
	bool							bUserTrustee[GAME_PLAYER];			//����й�
	BYTE							bBackCardData[GAME_PLAYER];			//�����˿�
	WORD						wOpenCard[GAME_PLAYER];				//����  �������
	//��ʷ����
	long long						lTurnScore[GAME_PLAYER];			//������Ϣ
	long long						lCollectScore[GAME_PLAYER];			//������Ϣ
};
//�ͽ�
struct CMD_S_GoldEgg
{
	WORD                            bCurrentUser;                       //��ǰ���
	BYTE                            bGoldEgg;                           //����Ŀ
};

//�û�����
struct CMD_S_OPENCARD
{
	WORD	bOpenUser;
};

//�û�����
struct CMD_C_OPENCARD
{
	WORD	bOpenUser;
	WORD		bNum;
};

//�û��з�(�ͻ���)
struct CMD_C_LandScore  
{
	bool								  bLandScore;							//��������
    WORD                            bLandUser;                          //�з��û�
};
//�û�����
struct CMD_C_DAOFAN
{
	WORD                            m_bUserDaofanID;
};
//�û�׼������
struct CMD_C_START
{
	WORD							bCurrentUser;                     //��ʼ�û� 
	bool								bOpenCard;							//���ƿ�ʼ
};
struct CMD_S_READY
{
	WORD							bCurrentUser;                     //��ʼ�û� 
	bool								bOpenCard;							//���ƿ�ʼ
};
struct CMD_S_DAOFAN
{
	WORD                            m_bUserDaofanID;								//��ǰ�û�
};
//�û��з֣�����ˣ�
struct CMD_S_LandScore
{
	bool								bCanLand;							//���޽з�
	WORD							bLandUser;							//�з����
	WORD							wLanddata;							//�з���ұ�ʶ--���ڱ���������ͽе���
	WORD				 			wCurrentUser;						//��ǰ���
	WORD							wCurrentData;						//��ǰ��ұ�ʶ
	//BYTE							bLandScore;							//�ϴνз�
	//BYTE							bCurrentScore;						//��ǰ�з�
	//bool                            bGameStart;                         //��Ϸ��ʼ��־
};



//���ʱ仯
struct CMD_S_BEILV
{
	WORD beillu[GAME_PLAYER];							//����
};

//�û����ƣ�����ˣ�
//struct CMD_S_OutCard
//{
//	BYTE							bCardCount;							//������Ŀ
//	WORD				 			wCurrentUser;						//��ǰ���
//	WORD							wOutCardUser;						//�������
//	BYTE							bCardData[MAX_COUNT];						//�˿��б�
//	bool                            bIsNoGameEnd;                       //�Ƿ����
//};

//���ƣ��ͻ��ˣ�
//struct CMD_C_OutCard
//{
//	BYTE							bCardCount;							//������Ŀ
//	BYTE							bCardData[MAX_COUNT];						//�˿��б�
//	WORD                            wOutCardUser;                       //�������
//};


//��������
//struct CMD_S_PassCard
//{
//	bool							bNewTurn;							//һ�ֿ�ʼ
//	WORD				 			wPassUser;							//�������
//	WORD				 			wCurrentUser;						//��ǰ���
//};
//���·��ƣ����ھ���
struct CMD_S_ReSedCrad
{
	WORD                            bTurnUser;                          //��һ�ֳ����û�
	BYTE							bTurnCount;							//��һ�ֳ�������Ŀ
	BYTE							bTurnData[MAX_COUNT];						//�˿��б�
	BYTE							bCardCount;							//����Ŀ
	BYTE							bCardData[MAX_COUNT];						//�˿��б�
};

//��������
struct CMD_S_TurnCount
{
	WORD                            wTurnChairID;                       //���ID
	WORD                            wTurnCount;                         //����
};


//�û�����
struct CMD_S_WarnInfo
{
	WORD                           wWarnUser;                           //�������
	bool                           bWarn;                               //������Ϣ
	WORD                           wWarnNum;                            //����ʱ����Ŀ
};
//�йܽṹ
struct CMD_C_UserTrustee {
	WORD							wUserChairID;						//�������
	bool							bTrustee;							//�йܱ�ʶ
};



//������ʾ
struct CMD_S_OutCardNotify
{
	BYTE							bOutCard;							//���Ʊ�־
	WORD							wCurrentUser;						//��ǰ�û�
};


////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#ifndef STRUCT_HEAD_FILE
#define STRUCT_HEAD_FILE
#pragma once
#include "common/Define.h"
#pragma pack(1)  // #pragma pack(1)�ñ��������ṹ������ǿ���������У������Ļ���sizeof��struct s������Ľ������5�ˡ�

/////////////////////////////////////////////////////////////////////
// ��Ϸ�б�

// ��Ϸ����	tagGameType

typedef struct
{
	WORD				wJoinID;						//�ҽ�����							
	WORD				wSortID;						//��������
	WORD				wTypeID;						//��������
	TCHART				szTypeName[LEN_TYPE];			//��������

}tagGameType;
// ��Ϸ���� tagGameKind
typedef struct
{
	WORD				wTypeID;						//��������
	WORD				wJoinID;						//�ҽ�����
	WORD				wSortID;						//��������
	WORD				wKindID;						//��������
	WORD				wGameID;						//ģ������
	DWORD				dwOnLineCount;					//��������
	TCHART				szKindName[LEN_KIND];			//��Ϸ����
	TCHART				szProcessName;					//��������
}tagGameKind;

// ��Ϸ�ڵ�	tagGameNode
typedef struct  
{
	WORD				wKindID;						//��������
	WORD				wJoinID;						//�ҽ�����
	WORD				wSortID;						//��������
	WORD				wNodeID;						//�ڵ�����
	TCHART				szNodeName;						//�ڵ�����
} tagGameNode;

//�������� tagGamePage
typedef struct  
{
	WORD				wPageID;						//ҳ������
	WORD				wKindID;						//��������
	WORD				wNodeID;						//�ڵ�����
	WORD				wSortID;						//��������
	WORD				wOperateType;					//��������
	TCHART				szDisPlayeName[LEN_PAGE];		//��ʾ����
} tagGamePage;

// tagGameServer ������Ϣ��Ӧ��������������
typedef struct
{
	WORD				wKindID;						//��������
	WORD				wNodeID;						//�ڵ�����
	WORD				wSortID;						//��������
	WORD				wServerID;						//��������
	WORD				wServerPort;					//����˿�
	DWORD				dwOnLineCount;					//��������
	DWORD				dwFullCount;					//��Ա����
	TCHART				szServerAddr[LEN_SERVER];		//�����ַ
	TCHART				szServerName[LEN_SERVER-8];		//��������

	// ������Ϣ
	SCORE				lServerScore;					//��Ԫ���� 8BYTES
	SCORE				lMinServerScore;				//��Ҫ���� 8BYTES
} tagGameServer;

// ������Ϣ tagOnLineInfoKind
typedef struct
{
	WORD				wKindID;						//���ͱ�ʶ
	DWORD				dwOnLineCount;					//��������
} tagOnLineInfoKind;

// ������Ϣ tagOnLineInfoServer
typedef struct
{
	WORD				wServerID;						//�����ʶ
	DWORD				dwOnLineCount;					//��������
} tagOnLineInfoServer;

/////////////////////////////////////////////////////////////////////////////
//#pragma mark -
//#pragma mark �û���Ϣ

// ����״̬ tagTableStatus
typedef struct
{
	BYTE				cbTableLock;					//������־
	BYTE				cbPlayStatus;					//��Ϸ��־
} tagTableStatus;

// �û�״̬ tagUserStatus
typedef struct 
{
	WORD				wTableID;						//��������
	WORD				wChairID;						//����λ��
	BYTE				cbUserStatus;					//�û�״̬
} tagUserStatus;

// �û����� tagUserScore
typedef struct
{
	// ������Ϣ
	LONGLONG			lScore;							//�û�����
	LONGLONG			lBanker;						//���չ����

	// ��Ӯ��Ϣ
	DWORD				dwWinCount;						//ʤ������
	DWORD				dwLostCount;					//ʧ������
	DWORD				dwDrawCount;					//�;�����
	DWORD				dwFleeCount;					//��������

	// ȫ����Ϣ
	DWORD				dwUserMedal;					//�û�����
	DWORD				dwExperience;					//�û�����
	DWORD				dwLoveLiness;					//�û�����
} tagUserScore;

//#pragma mark -
//#pragma mark �ֻ��û�����
typedef struct
{
	// ������Ϣ
	SCORE				lScore;							// �û�����

	// ��Ӯ��Ϣ
	DWORD				dwWinCount;						//ʤ������
	DWORD				dwLostCount;					//ʧ������
	DWORD				dwDrawCount;					//�;�����
	DWORD				dwFleeCount;					//��������

	//ȫ����Ϣ
	DWORD				dwExperience;					//�û�����
} tagMobileUserScore;


// �û���Ϣ tagUserInfoHead �����Ϣ
typedef struct  
{
	// �û�����
	DWORD				dwGameID;						// ��ϷID
	DWORD				dwUserID;						// �û�ID

	//ͷ����Ϣ
	WORD				wFaceID;						// ͷ������
	DWORD				dwCustomID;						// �Զ���ʶ

	// �û�����
	BYTE				cbGender;						// �û��Ա�
	BYTE				cbMemberOrder;					// ��Ա�ȼ� 1,2,3,4,5

	// �û�״̬
	WORD				wTableID;						// ��������
	WORD				wChairID;						// ��������
	BYTE				cbUserStatus;					// �û�״̬

	// ������Ϣ
	SCORE                           lScore;                                         // �û�����

	// ��Ϸ��Ϣ
	DWORD				dwWinCount;						// ʤ������
	DWORD				dwLostCount;					// ʧ������
	DWORD				dwDrawCount;					// �;�����
	DWORD				dwFleeCount;					// ��������
	DWORD				dwExperience;					// �û�����
} tagGameInUserInfo;	// ��Ϸ���Լ�����Ϣ

// ��չ�ǳ�
typedef struct
{
	WORD				wDataSize;						// ���ݴ�С
	WORD				wDataDecribe;					// ��������
} tagDataDescribe;

// ͷ����Ϣ tagCustomFaceInfo
typedef struct
{
	DWORD				dwDataSize;						// ���ݴ�С
	DWORD				dwCutstomFace[FACE_CX*FACE_CY];	// ͼƬ��Ϣ
} tagCustomFaceInfo;

// �㳡���� tagGamePlaza
typedef struct
{
	WORD				wPlazaID;						// �㳡��ʶ
	TCHART				szServerAddr[32];				// �����ַ
	TCHART				szServerName[32];				// ��������
} tagGamePlaza;

// �������� tagLevelItem
typedef struct
{
	long				lLevelScore;					// �������
	TCHART				szLevelName[16];				// ��������
} tagLevelItem;

//// ��Ա����	tagMemberItem
//typedef struct
//{
//	BYTE				cbMemberOrder;					// �ȼ���ʶ
//	TCHART				szMemberName[16];				// �ȼ�����
//} tagMemberItem;

// ��������	tagMasterItem
typedef struct
{
	BYTE				cbMasterOrder;					// �ȼ���ʶ
	TCHART				szMasterName[16];				// �ȼ�����
} tagMasterItem;

// �б����� tagColumnItem
typedef struct
{
	BYTE				cbColumnWidth;					// �б���
	BYTE				cbDataDescribe;					// �ֶ�����
	TCHART				szColumnName[16];				// �б�����
} tagColumnItem;

// ��ַ��Ϣ tagAddressInfo
typedef struct
{
	TCHART				szAddress[32];					// ��������ַ
} tagAddressInfo;

// ���ݿ���Ϣ tagDataBaseParameter
typedef struct
{
	WORD				wDataBasePort;					// ���ݿ�˿�
	TCHART				szDataBaseAddr[32];				// ���ݿ��ַ
	TCHART				szDataBaseUser[32];				// ���ݿ��û�
	TCHART				szDataBasePass[32];				// ���ݿ�����
	TCHART				szDataBaseName[32];				// ���ݿ�����
} tagDataBaseParameter;














#pragma pack()

#endif
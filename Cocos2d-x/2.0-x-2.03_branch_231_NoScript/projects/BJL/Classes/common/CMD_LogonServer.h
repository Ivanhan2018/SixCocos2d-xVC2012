/*
*  CMD_LogonServer.h
*  test
*
*  Created by Aden on 14-11-20.
*  Copyright 2014 __MyCompanyName__. All rights reserved.
*
*/
#pragma once
#include "packet.h"

#pragma pack(1)

// ��½����
#define MDM_MB_LOGON							100							//�㳡��½

//��½ģʽ
#define SUB_MB_LOGON_GAMEID						1							//ID��½
#define SUB_MB_LOGON_ACCOUNTS					2							//�˺ŵ�½
#define SUB_MB_REGISITER_ACCOUNTS				3							//ע���˺�
#define SUB_MB_LOGON_OTHERPLATFORM				4							//������½

//��½���
#define SUB_MB_LOGON_SUCCESS					100							//��½�ɹ�
#define SUB_MB_LOGON_FAILURE					101							//��½ʧ��

//������ʾ
#define SUB_MB_UPDATE_NOTIFY					200							//������ʾ

//�˺ŵ�½
typedef struct 
{
	//ϵͳ��Ϣ
	WORD			wModuleID;												//ģ���ʶ
	DWORD			dwPlazaVersion;											//�㳡�汾
	BYTE			cbDeviceType;											//�豸����

	//��½��Ϣ
	TCHART			szPassword[LEN_MD5];									//��½����
	TCHART			szAccounts[LEN_ACCOUNTS];								//��½�˺�

	//������Ϣ
	TCHART			szMachineID[LEN_MACHINE_ID];							//������ʶ
	TCHART			szMobilePhone[LEN_MOBILE_PHONE];						//�绰����
} CMD_MB_LogonAccounts;

//ע���˺�
typedef struct 
{
	// ϵͳ��Ϣ
	WORD			wModuleID;												//ģ���ʶ
	DWORD			dwPlazaVersion;											//�㳡�汾
	BYTE			cbDeviceType;											//�豸����

	// �������
	TCHART			szLogonPass[LEN_MD5];									//��½����
	TCHART			szInsurePass[LEN_MD5];									//���չ�����

	// ע����Ϣ
	WORD			wFaceID;												//ͷ���ʶ
	BYTE			cbGender;												//�û��Ա�
	TCHART			szAccounts[LEN_ACCOUNTS];								//��¼�˺�
	TCHART			szNickName[LEN_NICKNAME];								//�û��ǳ�

	// ������Ϣ
	TCHART			szMachineID[LEN_MACHINE_ID];							//������ʶ
	TCHART			szMobilePhone[LEN_MOBILE_PHONE];						//�绰����
	DWORD			dwSpreadID;												//�Ƽ���ID
} CMD_MB_RegisterAccounts;

//������½
typedef struct 
{
	// ϵͳ��Ϣ
	WORD			wModuleID;												// ģ���ʶ
	DWORD			dwPlazaVersion;											// �㳡�汾
	BYTE			cbDeviceType;											// �豸����

	// ע����Ϣ
	BYTE			cbGender;												// �û��Ա�
	DWORD			dwUserUin;												// ��½�˺�
	TCHART			szNickName[LEN_NICKNAME];								// �û��ǳ�
	TCHART			zsCompellation[LEN_COMPELLATION];						//��ʵ����

	// ������Ϣ
	TCHART			szMachineID[LEN_MACHINE_ID];							// ������ʶ
	TCHART			szMobilePhone[LEN_MOBILE_PHONE];						// �绰����
	//DWORD       dwSpreadID;                         // �Ƽ���ID

} CMD_MB_LogonOtherPlatform;


// ��½�ɹ�
typedef struct 
{
	WORD			wFaceID;												//�û���ʶ
	BYTE			cbGender;												//�û��Ա�
	DWORD			dwUserID;												//�û�ID
	DWORD			dwGameID;												//��ϷID
	DWORD			dwExperience;											//������ֵ
	DWORD			dwGoldScore;											//�û�����
	TCHART			szNickName[LEN_ACCOUNTS];								//�û��ǳ�
} CMD_MB_LogonSuccess;

// ��½ʧ��
typedef struct
{
	long			lErrorCode;												//�������
	TCHART			szDescribeString[128];									//������Ϣ
} CMD_MB_LogonFailure;

// ������ʾ
typedef struct
{
	BYTE			cbMustUpdate;											//ǿ������
	BYTE			cbAdviceUpdate;											//����汾
	DWORD			dwCurrentVersion;										//��ǰ�汾
} CMD_MB_UpdateNotify;


/////////////////////////////////////////////////////////////////////
// �б�����
#define MDM_MB_SERVER_LIST						101							//�б���Ϣ

#define SUB_MB_LIST_KIND						100							//�����б�
#define SUB_MB_LIST_SERVER						101							//�����б�
#define	SUB_MB_LIST_FINISH						200							//�б����

//////////////////////////////////////////////////////////////
//��������
#define MDM_MB_USER_SERVICE						102							//�û�����

////////////////////////////////////////////////////////////////////////////////
// �ʺŷ���
#define SUB_MB_MODIFY_ACCOUNTS					1							//�޸��˺�
#define SUB_MB_MODIFY_LOGON_PASS				2							//�޸�����
#define SUB_MB_MODIFY_INSURE_PASS				3							//�޸�����
#define SUB_MB_MODIFY_INDIVIDUAL				4							//�޸�����

// ��ѯ����
#define SUB_MB_QUERY_INDIVIDUAL					10							//��ѯ��Ϣ
///////////////////////////////////////////////////////////////////////////////////

// �������
#define SUB_MB_OPERATE_SUCCESS					100							//�����ɹ�
#define SUB_MB_OPERATE_FAILURE					101							//����ʧ��

// ��ѯ���
#define SUB_MB_USER_INDIVIDUAL					200							//��������







//////////////////////////////////////////////////////////////////////////////////
// �������չ��������   (��¼������) add by mojunxin

#define MDM_GP_USER_SERVICE						3							// �û����� �������չ��������


// �˺ŷ���
#define SUB_GP_MODIFY_MACHINE					100							//�޸Ļ���
#define SUB_GP_MODIFY_LOGON_PASS				101							//�޸�����
#define SUB_GP_MODIFY_INSURE_PASS				102							//�޸�����
#define SUB_GP_MODIFY_UNDER_WRITE				103							//�޸�ǩ��

// �޸�ͷ��
#define SUB_GP_USER_FACE_INFO					200							//ͷ����Ϣ
#define SUB_GP_SYSTEM_FACE_INFO					201							//ϵͳͷ��
#define SUB_GP_CUSTOM_FACE_INFO					202							//�Զ�ͷ��

// ��������
#define SUB_GP_USER_INDIVIDUAL					301							//��������
#define SUB_GP_QUERY_INDIVIDUAL					302							//��ѯ��Ϣ
#define SUB_GP_MODIFY_INDIVIDUAL				303							//�޸�����

// ���չ����
#define SUB_GP_USER_SAVE_SCORE					400							//�������
#define SUB_GP_USER_TAKE_SCORE					401							//ȡ������
#define SUB_GP_USER_TRANSFER_SCORE					402							//ת�˲���
#define SUB_GP_USER_INSURE_INFO					403							//���չ�����
#define SUB_GP_QUERY_INSURE_INFO				404							//��ѯ���չ�
#define SUB_GP_USER_INSURE_SUCCESS				405							//���չ�ɹ�
#define SUB_GP_USER_INSURE_FAILURE				406							//���չ�ʧ��
#define SUB_GP_QUERY_USER_INFO_REQUEST			407							//��ѯ�û�
#define SUB_GP_QUERY_USER_INFO_RESULT			408							//�û���Ϣ
#define SUB_GP_QUERY_TRANSFER_LOG	409								//��ѯת����־
#define SUB_GP_QUERY_TRANSFER_LOG_RET	410								//��ѯת����־����
#define SUB_GP_SEARCH_GOODS_INFO	411								//������Ʒ
#define SUB_GP_SEARCH_GOODS_INFO_RET 412								//������Ʒ
#define SUB_GP_SALE_GOODS_INFO		413								//������Ʒ��Ϣ
#define SUB_GR_SALE_GOODS_INFO_RET	414								//������Ʒ����
#define SUB_GP_BUY_GOODS_INFO		415								//������Ʒ��Ϣ
#define SUB_GR_BUY_GOODS_INFO_RET	416								//������Ʒ����
#define SUB_GR_GET_USER_PACKET		417								//��ȡ�ҵı���
#define SUB_GR_GET_USER_PACKET_RET	418								//��ȡ�ҵı�������
#define SUB_GP_USER_INSURE_SUCCESS2	419									//���гɹ�

// �������
#define SUB_GP_OPERATE_SUCCESS					900							//�����ɹ�
#define SUB_GP_OPERATE_FAILURE					901							//����ʧ��

//////////////////////////////////////////////////////////////////////////////////
//�޸�����
struct CMD_GP_ModifyLogonPass
{
	DWORD							dwUserID;							//�û� I D
	TCHART							szDesPassword[LEN_PASSWORD];		//�û�����
	TCHART							szScrPassword[LEN_PASSWORD];		//�û�����
};

//////////////////////////////////////////////////////////////////////////////////
//������Ʒ����
struct CMD_GP_SearchGoodsInfo
{
	TCHART							szSearchCondition[216];
};
//������Ʒ����
struct CMD_GP_GetMyPocket
{
	DWORD							dwUserID;
};

//��Ʒ���Ϸ���
struct CMD_GR_GoodsInfoRet
{
	DWORD							dwGoodID;							//��Ʒ I D
	DWORD							dwGoodsImageID;						//��ƷͼƬ		
	DWORD							dwSaleCount;						//����
	LONGLONG						lGoodsPrice;						//����
	TCHART							szGoodsName[LEN_NICKNAME];			//��Ʒ����
	TCHART							szSaleUserName[LEN_NICKNAME];		//������
	SYSTEMTIME						nTime;								//ʣ��ʱ��
};	
//������Ʒ��Ϣ
struct CMD_GP_SaleGoods
{
	TCHART							szSaleGoodsName[LEN_NICKNAME];
	LONGLONG						lSalePrice;
	DWORD							dwSaleCount;
	//TCHART							szSaleUserName[LEN_NICKNAME];
	DWORD							dwUserID;
	DWORD							dwCustomGoodsID;		//ͼƬ��Ϣ
};
//������Ʒ����
struct CMD_GP_UserBuyGoodsInfo
{
	DWORD							dwUserID;
	DWORD							dwBuyGoodsGNO;
	DWORD							dwBuyCount;
};

// ��ѯ���չ�
typedef struct
{
	DWORD										dwUserID;					//�û�ID
	TCHART										szPassword[LEN_MD5];		//���չ�����
} CMD_GP_QueryInsureInfo;

// ���չ�����
typedef struct 
{
	WORD										wRevenueTake;				//˰��
	WORD										wRevenueTransfer;			//˰��
	WORD										wServerID;					//�����ʶ
	SCORE										lUserScore;					//�û�����
	SCORE										lUserInsure;				//���չ񶹶�
	SCORE										lTransferPrerequisite;		//ת������
} CMD_GP_UserInsureInfo;

// ���붹��
typedef struct
{
	DWORD										dwUserID;					//�û�ID
	SCORE										lSaveScore;					//���붹��
	TCHART										szMachineID[LEN_MACHINE_ID];	//��������
} CMD_GP_UserSaveScore;

// ��ȡ����
typedef struct 
{
	DWORD										dwUserID;					//�û�ID
	SCORE										lTakeScore;					//��ȡ����
	TCHART										szPassword[LEN_MD5];		//���չ�����
	TCHART										szMachineID[LEN_MACHINE_ID];	//��������
} CMD_GP_UserTakeScore;

// ת�˶���
//typedef struct
//{
//	DWORD										dwUserID;					//�û�ID
//	BYTE											cbByNickName;				//�ǳ�����
//	SCORE										lTransferScore;				//���Ͷ���
//	TCHART										szPassword[LEN_MD5];		//���չ�����
//
//} CMD_GP_UserTransferScore;
typedef struct
{
	DWORD										dwUserID;					//�û�ID
	BYTE											cbByNickName;				//�ǳ�����
	SCORE										lTransferScore;				//���Ͷ���
	TCHART										szPassword[LEN_MD5];		//���չ�����
	TCHART										szNickName[LEN_NICENAME];	//�û��ǳƻ���ϷID
	TCHART										szMachineID[LEN_MACHINE_ID];//��������
} CMD_GP_UserTransferScore;


// ���չ�ɹ�
typedef struct
{
	DWORD							dwUserID;							// �û� I D
	SCORE							lUserScore;							// �û�����
	SCORE							lUserInsure;						// ���չ񶹶�
	TCHART							szDescribeString[128];				// ������Ϣ
} CMD_GP_UserInsureSuccess;

// ���չ�ʧ��
typedef struct
{
	LONG							lResultCode;						// �������
	TCHART							szDescribeString[128];				// ������Ϣ
} CMD_GP_UserInsureFailure;

// ��ȡ���
typedef struct
{
	DWORD							dwUserID;							// �û� I D
	SCORE							lUserScore;							// �û�����
	SCORE							lUserInsure;						// ���չ񶹶�
} CMD_GP_UserTakeResult;



//��ѯ�û�
typedef struct
{
	BYTE                            cbByNickName;                       // �ǳ�����
	TCHART							szNickName[LEN_NICKNAME];			// Ŀ���û�
} CMD_GP_QueryUserInfoRequest;

//�û���Ϣ
typedef struct
{
	DWORD							dwTargetGameID;						//Ŀ���û�
	TCHART							szNickName[LEN_NICKNAME];			//Ŀ���û�
} CMD_GP_UserTransferUserInfo;
//////////////////////////////////////////////////////////////////////////////////

//����ʧ��
typedef struct
{
	LONG							lResultCode;						//�������
	TCHART							szDescribeString[128];				//������Ϣ
} CMD_GP_OperateFailure;

//�����ɹ�
typedef struct
{
	LONG							lResultCode;						//��������
	TCHART							szDescribeString[128];				//�ɹ���Ϣ
} CMD_GP_OperateSuccess;




#pragma pack()


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

// 登陆命令
#define MDM_MB_LOGON							100							//广场登陆

//登陆模式
#define SUB_MB_LOGON_GAMEID						1							//ID登陆
#define SUB_MB_LOGON_ACCOUNTS					2							//账号登陆
#define SUB_MB_REGISITER_ACCOUNTS				3							//注册账号
#define SUB_MB_LOGON_OTHERPLATFORM				4							//其他登陆

//登陆结果
#define SUB_MB_LOGON_SUCCESS					100							//登陆成功
#define SUB_MB_LOGON_FAILURE					101							//登陆失败

//升级提示
#define SUB_MB_UPDATE_NOTIFY					200							//升级提示

//账号登陆
typedef struct 
{
	//系统信息
	WORD			wModuleID;												//模块标识
	DWORD			dwPlazaVersion;											//广场版本
	BYTE			cbDeviceType;											//设备类型

	//登陆信息
	TCHART			szPassword[LEN_MD5];									//登陆密码
	TCHART			szAccounts[LEN_ACCOUNTS];								//登陆账号

	//连接信息
	TCHART			szMachineID[LEN_MACHINE_ID];							//机器标识
	TCHART			szMobilePhone[LEN_MOBILE_PHONE];						//电话号码
} CMD_MB_LogonAccounts;

//注册账号
typedef struct 
{
	// 系统消息
	WORD			wModuleID;												//模块标识
	DWORD			dwPlazaVersion;											//广场版本
	BYTE			cbDeviceType;											//设备类型

	// 密码变量
	TCHART			szLogonPass[LEN_MD5];									//登陆密码
	TCHART			szInsurePass[LEN_MD5];									//保险柜密码

	// 注册信息
	WORD			wFaceID;												//头像标识
	BYTE			cbGender;												//用户性别
	TCHART			szAccounts[LEN_ACCOUNTS];								//登录账号
	TCHART			szNickName[LEN_NICKNAME];								//用户昵称

	// 连接信息
	TCHART			szMachineID[LEN_MACHINE_ID];							//机器标识
	TCHART			szMobilePhone[LEN_MOBILE_PHONE];						//电话号码
	DWORD			dwSpreadID;												//推荐人ID
} CMD_MB_RegisterAccounts;

//其他登陆
typedef struct 
{
	// 系统信息
	WORD			wModuleID;												// 模块标识
	DWORD			dwPlazaVersion;											// 广场版本
	BYTE			cbDeviceType;											// 设备类型

	// 注册信息
	BYTE			cbGender;												// 用户性别
	DWORD			dwUserUin;												// 登陆账号
	TCHART			szNickName[LEN_NICKNAME];								// 用户昵称
	TCHART			zsCompellation[LEN_COMPELLATION];						//真实姓名

	// 连接信息
	TCHART			szMachineID[LEN_MACHINE_ID];							// 机器标识
	TCHART			szMobilePhone[LEN_MOBILE_PHONE];						// 电话号码
	//DWORD       dwSpreadID;                         // 推荐人ID

} CMD_MB_LogonOtherPlatform;


// 登陆成功
typedef struct 
{
	WORD			wFaceID;												//用户标识
	BYTE			cbGender;												//用户性别
	DWORD			dwUserID;												//用户ID
	DWORD			dwGameID;												//游戏ID
	DWORD			dwExperience;											//经验数值
	DWORD			dwGoldScore;											//用户豆豆
	TCHART			szNickName[LEN_ACCOUNTS];								//用户昵称
} CMD_MB_LogonSuccess;

// 登陆失败
typedef struct
{
	long			lErrorCode;												//错误代码
	TCHART			szDescribeString[128];									//错误消息
} CMD_MB_LogonFailure;

// 升级提示
typedef struct
{
	BYTE			cbMustUpdate;											//强行升级
	BYTE			cbAdviceUpdate;											//建议版本
	DWORD			dwCurrentVersion;										//当前版本
} CMD_MB_UpdateNotify;


/////////////////////////////////////////////////////////////////////
// 列表命令
#define MDM_MB_SERVER_LIST						101							//列表信息

#define SUB_MB_LIST_KIND						100							//种类列表
#define SUB_MB_LIST_SERVER						101							//房间列表
#define	SUB_MB_LIST_FINISH						200							//列表完成

//////////////////////////////////////////////////////////////
//服务命令
#define MDM_MB_USER_SERVICE						102							//用户服务

////////////////////////////////////////////////////////////////////////////////
// 帐号服务
#define SUB_MB_MODIFY_ACCOUNTS					1							//修改账号
#define SUB_MB_MODIFY_LOGON_PASS				2							//修改密码
#define SUB_MB_MODIFY_INSURE_PASS				3							//修改密码
#define SUB_MB_MODIFY_INDIVIDUAL				4							//修改资料

// 查询命令
#define SUB_MB_QUERY_INDIVIDUAL					10							//查询信息
///////////////////////////////////////////////////////////////////////////////////

// 操作结果
#define SUB_MB_OPERATE_SUCCESS					100							//操作成功
#define SUB_MB_OPERATE_FAILURE					101							//操作失败

// 查询结果
#define SUB_MB_USER_INDIVIDUAL					200							//个人资料







//////////////////////////////////////////////////////////////////////////////////
// 大厅保险柜服务命令   (登录服务器) add by mojunxin

#define MDM_GP_USER_SERVICE						3							// 用户服务 大厅保险柜的主命令


// 账号服务
#define SUB_GP_MODIFY_MACHINE					100							//修改机器
#define SUB_GP_MODIFY_LOGON_PASS				101							//修改密码
#define SUB_GP_MODIFY_INSURE_PASS				102							//修改密码
#define SUB_GP_MODIFY_UNDER_WRITE				103							//修改签名

// 修改头像
#define SUB_GP_USER_FACE_INFO					200							//头像信息
#define SUB_GP_SYSTEM_FACE_INFO					201							//系统头像
#define SUB_GP_CUSTOM_FACE_INFO					202							//自定头像

// 个人资料
#define SUB_GP_USER_INDIVIDUAL					301							//个人资料
#define SUB_GP_QUERY_INDIVIDUAL					302							//查询信息
#define SUB_GP_MODIFY_INDIVIDUAL				303							//修改资料

// 保险柜服务
#define SUB_GP_USER_SAVE_SCORE					400							//存入操作
#define SUB_GP_USER_TAKE_SCORE					401							//取出操作
#define SUB_GP_USER_TRANSFER_SCORE					402							//转账操作
#define SUB_GP_USER_INSURE_INFO					403							//保险柜资料
#define SUB_GP_QUERY_INSURE_INFO				404							//查询保险柜
#define SUB_GP_USER_INSURE_SUCCESS				405							//保险柜成功
#define SUB_GP_USER_INSURE_FAILURE				406							//保险柜失败
#define SUB_GP_QUERY_USER_INFO_REQUEST			407							//查询用户
#define SUB_GP_QUERY_USER_INFO_RESULT			408							//用户信息
#define SUB_GP_QUERY_TRANSFER_LOG	409								//查询转账日志
#define SUB_GP_QUERY_TRANSFER_LOG_RET	410								//查询转账日志返回
#define SUB_GP_SEARCH_GOODS_INFO	411								//搜索物品
#define SUB_GP_SEARCH_GOODS_INFO_RET 412								//搜索物品
#define SUB_GP_SALE_GOODS_INFO		413								//寄售物品信息
#define SUB_GR_SALE_GOODS_INFO_RET	414								//寄售物品返回
#define SUB_GP_BUY_GOODS_INFO		415								//购买物品信息
#define SUB_GR_BUY_GOODS_INFO_RET	416								//购买物品返回
#define SUB_GR_GET_USER_PACKET		417								//获取我的背包
#define SUB_GR_GET_USER_PACKET_RET	418								//获取我的背包返回
#define SUB_GP_USER_INSURE_SUCCESS2	419									//银行成功

// 操作结果
#define SUB_GP_OPERATE_SUCCESS					900							//操作成功
#define SUB_GP_OPERATE_FAILURE					901							//操作失败

//////////////////////////////////////////////////////////////////////////////////
//修改密码
struct CMD_GP_ModifyLogonPass
{
	DWORD							dwUserID;							//用户 I D
	TCHART							szDesPassword[LEN_PASSWORD];		//用户密码
	TCHART							szScrPassword[LEN_PASSWORD];		//用户密码
};

//////////////////////////////////////////////////////////////////////////////////
//购买物品条件
struct CMD_GP_SearchGoodsInfo
{
	TCHART							szSearchCondition[216];
};
//搜索物品条件
struct CMD_GP_GetMyPocket
{
	DWORD							dwUserID;
};

//物品资料返回
struct CMD_GR_GoodsInfoRet
{
	DWORD							dwGoodID;							//物品 I D
	DWORD							dwGoodsImageID;						//物品图片		
	DWORD							dwSaleCount;						//数量
	LONGLONG						lGoodsPrice;						//单价
	TCHART							szGoodsName[LEN_NICKNAME];			//物品名称
	TCHART							szSaleUserName[LEN_NICKNAME];		//出售人
	SYSTEMTIME						nTime;								//剩余时间
};	
//寄售物品信息
struct CMD_GP_SaleGoods
{
	TCHART							szSaleGoodsName[LEN_NICKNAME];
	LONGLONG						lSalePrice;
	DWORD							dwSaleCount;
	//TCHART							szSaleUserName[LEN_NICKNAME];
	DWORD							dwUserID;
	DWORD							dwCustomGoodsID;		//图片信息
};
//购买物品条件
struct CMD_GP_UserBuyGoodsInfo
{
	DWORD							dwUserID;
	DWORD							dwBuyGoodsGNO;
	DWORD							dwBuyCount;
};

// 查询保险柜
typedef struct
{
	DWORD										dwUserID;					//用户ID
	TCHART										szPassword[LEN_MD5];		//保险柜密码
} CMD_GP_QueryInsureInfo;

// 保险柜资料
typedef struct 
{
	WORD										wRevenueTake;				//税收
	WORD										wRevenueTransfer;			//税收
	WORD										wServerID;					//房间标识
	SCORE										lUserScore;					//用户豆豆
	SCORE										lUserInsure;				//保险柜豆豆
	SCORE										lTransferPrerequisite;		//转账条件
} CMD_GP_UserInsureInfo;

// 存入豆豆
typedef struct
{
	DWORD										dwUserID;					//用户ID
	SCORE										lSaveScore;					//存入豆豆
	TCHART										szMachineID[LEN_MACHINE_ID];	//机器序列
} CMD_GP_UserSaveScore;

// 提取豆豆
typedef struct 
{
	DWORD										dwUserID;					//用户ID
	SCORE										lTakeScore;					//提取豆豆
	TCHART										szPassword[LEN_MD5];		//保险柜密码
	TCHART										szMachineID[LEN_MACHINE_ID];	//机器序列
} CMD_GP_UserTakeScore;

// 转账豆豆
//typedef struct
//{
//	DWORD										dwUserID;					//用户ID
//	BYTE											cbByNickName;				//昵称赠送
//	SCORE										lTransferScore;				//赠送豆豆
//	TCHART										szPassword[LEN_MD5];		//保险柜密码
//
//} CMD_GP_UserTransferScore;
typedef struct
{
	DWORD										dwUserID;					//用户ID
	BYTE											cbByNickName;				//昵称赠送
	SCORE										lTransferScore;				//赠送豆豆
	TCHART										szPassword[LEN_MD5];		//保险柜密码
	TCHART										szNickName[LEN_NICENAME];	//用户昵称或游戏ID
	TCHART										szMachineID[LEN_MACHINE_ID];//机器序列
} CMD_GP_UserTransferScore;


// 保险柜成功
typedef struct
{
	DWORD							dwUserID;							// 用户 I D
	SCORE							lUserScore;							// 用户豆豆
	SCORE							lUserInsure;						// 保险柜豆豆
	TCHART							szDescribeString[128];				// 描述消息
} CMD_GP_UserInsureSuccess;

// 保险柜失败
typedef struct
{
	LONG							lResultCode;						// 错误代码
	TCHART							szDescribeString[128];				// 描述消息
} CMD_GP_UserInsureFailure;

// 提取结果
typedef struct
{
	DWORD							dwUserID;							// 用户 I D
	SCORE							lUserScore;							// 用户豆豆
	SCORE							lUserInsure;						// 保险柜豆豆
} CMD_GP_UserTakeResult;



//查询用户
typedef struct
{
	BYTE                            cbByNickName;                       // 昵称赠送
	TCHART							szNickName[LEN_NICKNAME];			// 目标用户
} CMD_GP_QueryUserInfoRequest;

//用户信息
typedef struct
{
	DWORD							dwTargetGameID;						//目标用户
	TCHART							szNickName[LEN_NICKNAME];			//目标用户
} CMD_GP_UserTransferUserInfo;
//////////////////////////////////////////////////////////////////////////////////

//操作失败
typedef struct
{
	LONG							lResultCode;						//错误代码
	TCHART							szDescribeString[128];				//描述消息
} CMD_GP_OperateFailure;

//操作成功
typedef struct
{
	LONG							lResultCode;						//操作代码
	TCHART							szDescribeString[128];				//成功消息
} CMD_GP_OperateSuccess;




#pragma pack()


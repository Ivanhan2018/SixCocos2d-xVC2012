// 公共的宏，为了兼容 Unicode 与 Ansi 而设置，安全第一

//#ifndef PUBLIC_MACRO_H
//#define PUBLIC_MACRO_H  // 加了这个就编译不过啦

#pragma once

// 客户端结构体大小和服务器结构体大小是否一致，不一致则视为错误消息，则返回自动归池			// add by cxf
#define DATA_SIZE_CONTRAST(size1,size2){ assert(size1==size2); if(size1!=size2){return TMR_AUTO_RECYCLE; }}

#define INVALID_CHANNEL_NO -1	// 无效的通道号
#define INVALID_USER_ID -1		// 无效用户Id
#define INVAL_TABLE_NO -1		// 无效桌子
#define INVAL_SEAT_NO -1		// 无效座号

#define IP_ADDRES_LEN 20		// IP地址的长度

#define USER_NAME_LEN 32		// 是 CHAR 
#define USER_PASSWORD_LEN  33	// 是 BYTE 
#define USER_REAL_NAME_LEN 16	// 直实姓名的长度，是 CHAR 
#define USER_IDENTITY_CARD_LEN 20	// 身份证号码的长度
#define USER_MOBILE_LEN 16			// 手机号长度

#define	DB_NAME_LEN			20		// 房间相连的只读数据库名称，通常是 six_devisions
#define	DB_USER_NAME_LEN	20		// 房间相连的只读数据库用户名称，通常是 root
#define	DB_PASS_LEN			20		// 房间相连的只读数据库密码

#define ROOM_NAME_LEN			30	// 房间名称的长度，是 char 
#define FIGHT_TABLE_NAME_LEN	30	// 战斗表名的长度，是 char 
#define ROOM_MESSAGE_LEN	   100	// 玩家进入房间时会收到的消息的长度
#define GAME_MESSAGE_LEN       100  // 玩家进入游戏时会收到的消息的长度

#define PARAMETER_KEY_VALUE1_LEN 30		// parameter表中的key_value的长度
#define GAME_NAME_LEN			32		// 游戏名字长度
#define PROGRESS_NAME_LEN		32		// 游戏进程名字长度
#define REWARD_NAME_LEN			32		// 奖励名称长度
#define ACCOUNTS_LEN			16		// 管理员帐号长度
#define CHAT_CONTENT_LEN		256		// 聊天内容长度

#ifndef WIN32
typedef unsigned int		UINT;
typedef unsigned int		WPARAM;
typedef long				LPARAM;
typedef unsigned long long  ULONGLONG; 
typedef long long			LONGLONG;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#define INVALID_SOCKET		-1
#define SOCKET_ERROR		-1
#define SOCKET				long
#define CloseSocket(a)		close(a)
#define _snprintf			snprintf

#ifdef UNICODE
#define _T L##  
#define _tprintf wprintf
#else
#define _T
#define _tprintf printf
#endif  //UNICODE
#endif

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)
template<class T>
class DATA_BASE
{
public:
	unsigned int GetLen()
	{
		return sizeof(*((T*)this));
	}
};
#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif

//#endif
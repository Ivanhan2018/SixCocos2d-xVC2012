// �����ĺ꣬Ϊ�˼��� Unicode �� Ansi �����ã���ȫ��һ

//#ifndef PUBLIC_MACRO_H
//#define PUBLIC_MACRO_H  // ��������ͱ��벻����

#pragma once

// �ͻ��˽ṹ���С�ͷ������ṹ���С�Ƿ�һ�£���һ������Ϊ������Ϣ���򷵻��Զ����			// add by cxf
#define DATA_SIZE_CONTRAST(size1,size2){ assert(size1==size2); if(size1!=size2){return TMR_AUTO_RECYCLE; }}

#define INVALID_CHANNEL_NO -1	// ��Ч��ͨ����
#define INVALID_USER_ID -1		// ��Ч�û�Id
#define INVAL_TABLE_NO -1		// ��Ч����
#define INVAL_SEAT_NO -1		// ��Ч����

#define IP_ADDRES_LEN 20		// IP��ַ�ĳ���

#define USER_NAME_LEN 32		// �� CHAR 
#define USER_PASSWORD_LEN  33	// �� BYTE 
#define USER_REAL_NAME_LEN 16	// ֱʵ�����ĳ��ȣ��� CHAR 
#define USER_IDENTITY_CARD_LEN 20	// ���֤����ĳ���
#define USER_MOBILE_LEN 16			// �ֻ��ų���

#define	DB_NAME_LEN			20		// ����������ֻ�����ݿ����ƣ�ͨ���� six_devisions
#define	DB_USER_NAME_LEN	20		// ����������ֻ�����ݿ��û����ƣ�ͨ���� root
#define	DB_PASS_LEN			20		// ����������ֻ�����ݿ�����

#define ROOM_NAME_LEN			30	// �������Ƶĳ��ȣ��� char 
#define FIGHT_TABLE_NAME_LEN	30	// ս�������ĳ��ȣ��� char 
#define ROOM_MESSAGE_LEN	   100	// ��ҽ��뷿��ʱ���յ�����Ϣ�ĳ���
#define GAME_MESSAGE_LEN       100  // ��ҽ�����Ϸʱ���յ�����Ϣ�ĳ���

#define PARAMETER_KEY_VALUE1_LEN 30		// parameter���е�key_value�ĳ���
#define GAME_NAME_LEN			32		// ��Ϸ���ֳ���
#define PROGRESS_NAME_LEN		32		// ��Ϸ�������ֳ���
#define REWARD_NAME_LEN			32		// �������Ƴ���
#define ACCOUNTS_LEN			16		// ����Ա�ʺų���
#define CHAT_CONTENT_LEN		256		// �������ݳ���

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
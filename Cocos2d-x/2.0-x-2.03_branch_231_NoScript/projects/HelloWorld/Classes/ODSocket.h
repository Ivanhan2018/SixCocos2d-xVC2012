/*
 * define file about portable socket class.
 * description:this sock is suit both windows and linux
 * design:odison
 * e-mail:odison@126.com>
 *
 */

#ifndef _ODSOCKET_H_
#define _ODSOCKET_H_

#include "Packet.h"
//#include "Define.h"

#ifdef WIN32
#include <winsock.h>
typedef int				socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <cstdlib>
#include <fcntl.h>
#include "errno.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <ctime>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/platform.h"
#else
#include "platform.h"
#endif


#include <iostream>
//#include "CMD_Correspond.h"

//#include "GlobalUserInfo.h"
#include "CMD_LOGONSERVER.h"
#include "cocos2d.h"


typedef int				SOCKET;

//#pragma region define win32 const variable in linux
#define INVALID_SOCKET	-1
#define SOCKET_ERROR	-1
//#pragma endregion
#endif
//接口版本

using namespace cocos2d;



#define BULID_VER					0									//授权版本
#define PRODUCT_VER					6									//产品版本


//接口版本
#define INTERFACE_VERSION(cbMainVer,cbSubVer)							\
(DWORD)(														\
(((BYTE)(PRODUCT_VER))<<24)+									\
(((BYTE)(cbMainVer))<<16)+										\
((BYTE)(cbSubVer)<<8))+											\
((BYTE)(BULID_VER))

//模块版本
#define PROCESS_VERSION(cbMainVer,cbSubVer,cbBuildVer)					\
(DWORD)(														\
(((BYTE)(PRODUCT_VER))<<24)+									\
(((BYTE)(cbMainVer))<<16)+										\
((BYTE)(cbSubVer)<<8)+											\
(BYTE)(cbBuildVer))
//程序版本
#define VERSION_FRAME				PROCESS_VERSION(3,6,4)				//框架版本
#define VERSION_PLAZA				PROCESS_VERSION(3,6,4)				//大厅版本
#define VERSION_MOBILE_ANDROID		PROCESS_VERSION(24,6,8)				//手机版本
#define VERSION_MOBILE_IOS			PROCESS_VERSION(25,7,8)				//手机版本

//版本定义
#define VERSION_EFFICACY			0									//效验版本
#define VERSION_FRAME_SDK			INTERFACE_VERSION(6,3)				//框架版本

//////////////////////////////////////////////////////////////////////////////////
//发布版本

//登录命令

#define MDM_GP_LOGON				1									//广场登录

//登录模式
#define SUB_GP_LOGON_GAMEID			1									//I D 登录
#define SUB_GP_LOGON_ACCOUNTS		2									//帐号登录
#define SUB_GP_REGISTER_ACCOUNTS	3									//注册帐号

//////////////////////////////////////////////////////////////////////////////////


#define SOCKET_VER						0x66   //定义网络版本


class ODSocket
{
public:
	//获取标识
	virtual _WORD_   GetSocketID() { return m_wSocketID;}
	//设置标识
	virtual void   SetSocketID(_WORD_ wSocketID) { m_wSocketID=wSocketID; }
public:
    //ODSocket();
	ODSocket(ITCPSocketSink *gameEngine);
	//ODSocket(SOCKET sock = INVALID_SOCKET);
	~ODSocket();
    //static bool GetMachineIDEx(_TCHAR_ szMachineID[LEN_MACHINE_ID]);
	// Create socket object for snd/recv data
	bool Create(int af, int type, int protocol = 0);
    
    // 域名解析
    char  *jiexiyuming(const char *yuming);
	// Connect socket
	bool Connect(const char* ip, unsigned short port);
	//#region server
	// Bind socket
	bool Bind(unsigned short port);
    
	// Listen socket
	bool Listen(int backlog = 5);
    
	// Accept socket
	bool Accept(ODSocket& s, char* fromip = NULL);
	//#endregion
	
	// Send socket
	int Send(void* buf, int len, int flags = 0);
    
	// Recv socket
	int Recv(char* buf, int len, int flags = 0);
	
	// Close socket
	int Close();
    
	// Get errno
	int GetError();
	
	//#pragma region just for win32
	// Init winsock DLL
	static int Init();
	// Clean winsock DLL
	static int Clean();
	//#pragma endregion
    
	// Domain parse
	static bool DnsParse(const char* domain, char* ip);
    
	ODSocket& operator = (SOCKET s);
    
	operator SOCKET ();
    
    
    _WORD_ SeedRandMap(_WORD_ wSeed);
    
    _BYTE_ MapSend_BYTE_(_BYTE_ const cbData);
    
    _BYTE_ MapRecv_BYTE_(_BYTE_ const cbData);
    
    //数据解密
    _WORD_ CrevasseBuffer(_BYTE_ pcbDataBuffer[], _WORD_ wDataSize);
    
    //数据加密
    _WORD_ EncryptBuffer(_BYTE_ pcbDataBuffer[], _WORD_ wDataSize, _WORD_ wBufferSize);
    //获得系统时间
    _D_WORD_ getticketime();
    
    //发送函数
    _D_WORD_ senddata(_WORD_ wMainCmdID, _WORD_ wSubCmdID);
    
    _LRESULT_ OnSocketNotifyRead(int wParam, int lParam);
    
    _D_WORD_ SendData(_WORD_ wMainCmdID, _WORD_ wSubCmdID, void * pData, _WORD_ wDataSize);
    
    bool OnEventMissionRead(TCP_Command Command, void * pData, _WORD_ wDataSize);
    
    bool OnSocketSubLogonSuccess(void * pData, _WORD_ wDataSize);
    
    _LRESULT_ OnSocketNotifyClose(int wParam, int lParam);
    
	int	m_RandTimeValue,m_RandTimeFirst;
protected:
	_WORD_							m_wRecvSize;						//接收长度
	_BYTE_							m_cbRecvBuf[SOCKET_TCP_BUFFER*10];		//接收缓冲
    
protected:
	SOCKET m_sock;
	struct sockaddr_in svraddr;
    //加密
protected:
	_BYTE_							m_cbSendRound;						//字节映射
	_BYTE_							m_cbRecvRound;						//字节映射
	_D_WORD_							m_dwSendXorKey;						//发送密钥
	_D_WORD_							m_dwRecvXorKey;						//接收密钥
    
	//计数变量
protected:
	_D_WORD_							m_dwSendTickCount;					//发送时间
	_D_WORD_							m_dwRecvTickCount;					//接收时间
	_D_WORD_							m_dwSendPacketCount;				//发送计数
	_D_WORD_							m_dwRecvPacketCount;				//接受计数
    
protected:
	_WORD_							m_wSocketID;						//网络标识
	_BYTE_							m_cbSocketStatus;					//网络状态
    
protected:
	SOCKET							m_hSocket;							//连接句柄
	ITCPSocketSink *				m_pITCPSocketSink;					//回调接口
    
protected:
	_BYTE_				m_ProxyServerType;					//代理类型
	tagProxyServer				m_ProxyServerInfo;					//代理信息
    
	//接收变量
};

#endif

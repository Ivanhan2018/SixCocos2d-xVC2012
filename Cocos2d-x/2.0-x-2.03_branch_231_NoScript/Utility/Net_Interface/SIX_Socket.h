/***********************************************
Name£ºSIX_Socket
Desc£ºWinsocket/BSD Socket
Auth£ºCool.Cat@2013-04-16
***********************************************/
#pragma once

#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib,"ws2_32")
#define CloseSocket(a)		closesocket(a)
#else
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
#endif
#include <SIX_Typedef.h>

enum PROTOCOL {
	TCP	=	SOCK_STREAM,
	UDP =	SOCK_DGRAM,
	RAW	=	SOCK_RAW,
	DAM	=	SOCK_RDM,
	SEQ	=	SOCK_SEQPACKET
};

#define BUFFSIZE	1024*8

class SIX_Socket{
public:
	SIX_Socket(int protocol=TCP);
	~SIX_Socket();
public:
	virtual void OnRecv(const char *pData,int pLen){};
	virtual void OnClose(){};
public:
	void Init();
	bool SetOPT(int level,int optname,void *optval);
	bool SetAsynMode(bool isAsyn);
	bool Connect(const char* addr,unsigned short port,int waitTime=5,bool Asyn=true);
	void Recv(int flag=0);
	int Send(const char* buf,int len,int flags=0);
	int Close();
	int GetError();

	bool IsConnected();
	void SetConnected(bool connected);

	bool IsInvalid();
private:
	SOCKET m_sock;
	bool m_IsConnected;
	int m_protocol;
};
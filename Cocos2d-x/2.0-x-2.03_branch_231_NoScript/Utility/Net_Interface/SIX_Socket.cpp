#include "SIX_Socket.h"

SIX_Socket::SIX_Socket(int protocol)
{
#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	if (WSAStartup(version, &wsaData))
	{
		SIXLog("SIX_Socket.WSAStartup.Error[%d]",GetError());
		return;
	}
#endif
	m_sock = INVALID_SOCKET;
	m_protocol = protocol;
	SetConnected(false);
	Init();
}

void SIX_Socket::Init()
{
	if (IsInvalid())
	{
		m_sock = socket(AF_INET,m_protocol,0);
		if (m_sock==INVALID_SOCKET)
			SIXLog("SIX_Socket.socket.Error[%d]",GetError());
	}
}

SIX_Socket::~SIX_Socket()
{
	Close();
#ifdef WIN32
	WSACleanup();
#endif
}

bool SIX_Socket::SetOPT(int level,int optname,void *optval)
{
	if (IsInvalid())
		return false;
	int retv = ::setsockopt (m_sock,level,optname,(char *)&optval, sizeof(optval));
	if(retv==SOCKET_ERROR)
	{
		SIXLog("SIX_Socket.SetOPT.level[%d].optname[%d].optval[%d].Error[%d]",level,optname,optval,GetError());
		return false;
	}
	return true;
}

// isAsyn = true	设置异步套接字
// isAsyn = false	设置同步套接字
bool SIX_Socket::SetAsynMode(bool isAsyn)
{
	if (IsInvalid())
		return false;
	unsigned long ul = isAsyn?1:0;
	int retv = 0;
#ifdef WIN32
	retv = ::ioctlsocket(m_sock,FIONBIO,(unsigned long*)&ul);
#else
	retv = fcntl(m_sock,FIONBIO,(unsigned long*)&ul);
#endif
	if(retv==SOCKET_ERROR)
	{
		SIXLog("SetAsynMode.Error[%d]",GetError());
		return false;
	}
	return true;
}

bool SIX_Socket::Connect(const char* addr,unsigned short port,int waitTime,bool Asyn)
{
	if (IsConnected())
		return false;

	Init();
	
	// 设置发送超时
	if (!SetOPT(SOL_SOCKET,SO_SNDTIMEO,&waitTime))
		return false;

	// 设置接收超时
	if (!SetOPT(SOL_SOCKET,SO_RCVTIMEO,&waitTime))
		return false;

	// 设置套接字被关闭后立即中断，避免出现time_out状态
#ifdef WIN32
	LINGER lingerStruct;
#else
	linger lingerStruct;
#endif
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;

	bool retv = false;

#ifdef WIN32
	retv = SetOPT(SOL_SOCKET,SO_DONTLINGER,&lingerStruct);
#else
	retv = SetOPT(SOL_SOCKET,SO_LINGER,&lingerStruct);
#endif

	if (retv==false)
		return false;

	struct sockaddr_in remote_addr;
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr(addr);
	remote_addr.sin_port = htons(port);

	if (!Asyn)
	{
		int ret = connect(m_sock,(struct sockaddr*)&remote_addr,sizeof(remote_addr));
		if (ret==SOCKET_ERROR)
		{
			SIXLog("Connect.Asyn[%d].Error[%d]",Asyn,GetError());
			return false;
		}
	}
	else
	{
		// 设置异步套接字
		SetAsynMode(Asyn);

		::connect(m_sock,(sockaddr*)&remote_addr,sizeof(remote_addr));

		// select监视写操作
		fd_set w;
		FD_ZERO(&w);
		FD_SET(m_sock,&w);

		// 设置连接超时
		struct timeval timeout;
		timeout.tv_sec = waitTime;
		timeout.tv_usec =0;

		// 等待connect完成
		int ret = select(0,0,&w,0,&timeout);
		// SOCKET_ERROR or timeout=0
		if (ret<=0)
		{
			SIXLog("Connect.Asyn[%d].Error[%d]",Asyn,GetError());
			return false;
		}

		// 重新设置回阻塞方式
		SetAsynMode(false);
	}

	SetConnected(true);
	return true;
}

void SIX_Socket::Recv(int flag)
{
	if (!IsConnected() || IsInvalid())
		return;

	char *msg = new char[BUFFSIZE];
	int retv = recv(m_sock,msg,BUFFSIZE,flag);
	// 接收数据成功
	if (retv>0)
	{
		OnRecv(msg,retv);
		CC_SAFE_DELETE(msg);
	}
	// 接收数据错误
	else if (retv<0)
	{
		// 套接字上出现错误
		if (retv==SOCKET_ERROR)
		{
			// WSAECONNABORTED(10053)
			// WSAECONNRESET(10054)
			if (GetError()==10053 ||
				GetError()==10054
				)
			{
				SIXLog("SIX_Socket.Recv.retv[%d].Error[%d].A",retv,GetError());
				CC_SAFE_DELETE(msg);

				// 通知上层套接字已经断开
				goto close;
			}
		}
		// 其他错误(-2)
		else
		{
			SIXLog("SIX_Socket.Recv.retv[%d].Error[%d].B",retv,GetError());
			CC_SAFE_DELETE(msg);
		}
	}
	// 套接字已经关闭
	else if (retv==0)
	{
		SIXLog("SIX_Socket.Recv.retv[%d].Error[%d].C",retv,GetError());
		CC_SAFE_DELETE(msg);

		// 通知上层套接字已经断开
		goto close;
	}
	return;
close:
	OnClose();
	Close();
	return;
}

int SIX_Socket::Send(const char* buf,int len,int flags)
{
	if (!IsConnected() || IsInvalid())
		return -2;

	int bytes;
	int count = 0;

	while (count<len) 
	{
		bytes = send(m_sock,buf+count,len-count,flags);
		if (bytes<=0)
			return bytes;
		count += bytes;
	}
	return count;
}

int SIX_Socket::Close()
{
	if (!IsConnected() || IsInvalid())
		return -2;
	int retv = CloseSocket(m_sock);
	m_sock = INVALID_SOCKET;
	SetConnected(false);
	return retv;
}

int SIX_Socket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool SIX_Socket::IsConnected()
{
	return m_IsConnected;
}

void SIX_Socket::SetConnected(bool connected)
{
	m_IsConnected = connected;
}

bool SIX_Socket::IsInvalid()
{
	return (m_sock==INVALID_SOCKET)?true:false;
}
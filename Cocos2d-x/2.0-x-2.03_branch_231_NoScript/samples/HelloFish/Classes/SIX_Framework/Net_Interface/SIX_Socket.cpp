#include "SIX_Socket.h"

SIX_Socket::SIX_Socket(int protocol)
{
#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	if (WSAStartup(version, &wsaData))
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("SIX_Socket.WSAStartup.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return;
	}
#endif
	m_sock = INVALID_SOCKET;
	m_protocol = protocol;
	setCloseType(CLOSE_TYPE_NO);
	setConnected(false);
	InitSocket();
}

void SIX_Socket::InitSocket()
{
	if (IsInvalid())
	{
		m_sock = socket(AF_INET,SOCK_STREAM,m_protocol);
		if (m_sock==INVALID_SOCKET)
		{
			const char *errMsg = GetErrorMsg(GetErrorNumber());
			SIXLog("SIX_Socket.socket.Error[%s]",errMsg);
			CC_SAFE_DELETE(errMsg);
			return;
		}
		this->setInited(true);
	}
}

SIX_Socket::~SIX_Socket()
{
	close();
#ifdef WIN32
	WSACleanup();
#endif
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
	retv = ::ioctlsocket(m_sock,FIONBIO,&ul);
#else
	int flag = fcntl(m_sock,F_GETFL,0);
	if (isAsyn)
		flag |= O_NONBLOCK;
	else
		flag &= ~O_NONBLOCK;
	retv = fcntl(m_sock,F_SETFL,O_NONBLOCK);
#endif
	if(retv==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("SetAsynMode.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return false;
	}
	return true;
}

bool SIX_Socket::Connect(const char* addr,unsigned int port,int waitTime,bool Asyn)
{
	if (getConnected())
		return false;

	InitSocket();
	
	// 设置发送超时(SO_SNDTIMEO/SO_RCVTIMEO单位为ms)
	struct timeval timeout;
	timeout.tv_sec = waitTime;
	timeout.tv_usec = 0;
	if (::setsockopt(m_sock,SOL_SOCKET,SO_SNDTIMEO,(const char*)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_SNDTIMEO.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return false;
	}

	// 设置接收超时
	if (::setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_RCVTIMEO.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return false;
	}

	// 设置套接字被关闭后立即中断，避免出现time_out状态
#ifdef WIN32
	LINGER lingerStruct;
#else
	linger lingerStruct;
#endif
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;

#ifdef WIN32
	if (::setsockopt(m_sock,SOL_SOCKET,SO_DONTLINGER,(const char*)&lingerStruct,sizeof(lingerStruct))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_DONTLINGER.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return false;
	}
#else
	if (::setsockopt(m_sock,SOL_SOCKET,SO_LINGER,(const char*)&lingerStruct,sizeof(lingerStruct))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_LINGER.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return false;
	}
#endif

	struct sockaddr_in remote_addr;
	memset(&remote_addr,0,sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr(addr);
	remote_addr.sin_port = htons(port);

	if (!Asyn)
	{
		int ret = ::connect(m_sock,(struct sockaddr*)&remote_addr,sizeof(remote_addr));
		if (ret==SOCKET_ERROR)
		{
			const char *errMsg = GetErrorMsg(GetErrorNumber());
			SIXLog("Connect.Asyn[%d].Error[%s]",Asyn,errMsg);
			CC_SAFE_DELETE(errMsg);
			this->OnConnectFail(false,ret,remote_addr);
			return false;
		}
	}
	else
	{
		// 设置异步套接字
#ifdef WIN32
		SetAsynMode(true);
#endif

		int ret = ::connect(m_sock,(sockaddr*)&remote_addr,sizeof(remote_addr));

#ifndef WIN32
		SetAsynMode(true);
#endif

		// select监视写操作
		fd_set w;
		FD_ZERO(&w);
		FD_SET(m_sock,&w);

		// 设置连接超时(单位s)
		struct timeval selectTimeout;
		selectTimeout.tv_sec = waitTime;
		selectTimeout.tv_usec = 0;

		// 等待connect完成
#ifdef WIN32
		ret = select(0,0,&w,0,&selectTimeout);
#else
		ret = select(m_sock+1,0,&w,0,&selectTimeout);
#endif
		// SOCKET_ERROR or timeout=0
		if (ret<=0)
		{
			const char *errMsg = GetErrorMsg(GetErrorNumber());
			SIXLog("Connect.Asyn[%d].Error[%s]",Asyn,errMsg);
			CC_SAFE_DELETE(errMsg);
			this->OnConnectFail(false,ret,remote_addr);
			return false;
		}

		// 重新设置回阻塞方式
		SetAsynMode(false);
	}

	setConnected(true);
	this->OnConnect(false,remote_addr);
	setCloseType(CLOSE_TYPE_NO);
	return true;
}

int SIX_Socket::Recv(int flag)
{
	if (!getConnected() || IsInvalid())
		return -2;

	char *msg = new char[BUFFSIZE];
	memset(msg,0,BUFFSIZE);
	int retv = recv(m_sock,msg,BUFFSIZE,flag);
	int LastError = GetErrorNumber();
	// 接收数据成功
	if (retv>0)
	{
		OnRecv(msg,retv);
		CC_SAFE_DELETE(msg);
		return 0;
	}

	CC_SAFE_DELETE(msg);

	// 套接字已经超时 或 关闭
	if (retv==0)
	{
		// 非阻塞模式下是正常的
		//const char *errMsg = GetErrorMsg(LastError);
		//SIXLog("SIX_Socket.Recv.retv[%d].Error.A[%s]",retv,errMsg);
		//CC_SAFE_DELETE(errMsg);
		//goto close;
	}
	// 接收数据错误
	else if (retv<0)
	{
		// 套接字上出现错误
		if (retv==SOCKET_ERROR)
		{
			switch (LastError)
			{
#ifdef WIN32
				// WSAETIMEDOUT
			case 10060:
				// WSAEWOULDBLOCK
			case 10035:
				{
					// 非阻塞模式下是正常的
					break;
				}
				// WSAENOTSOCK(e.g:socket已经无效了，可能已被释放掉)
			case 10038:
				// WSAECONNABORTED(e.g:直接调用底层close)
			case 10053:
				// WSAECONNRESET(e.g:禁用网卡 或 被 服务端主动关闭)
			case 10054:
				{
					const char *errMsg = GetErrorMsg(LastError);
					SIXLog("SIX_Socket.Recv.retv[%d].Error.B[%s]",retv,errMsg);
					CC_SAFE_DELETE(errMsg);
					goto close;
				}
			default:
				{
					const char *errMsg = GetErrorMsg(LastError);
					SIXLog("SIX_Socket.Recv.retv[%d].Error.C[%s]",retv,errMsg);
					CC_SAFE_DELETE(errMsg);
					break;
				}
#else
				// EAGAIN
			case 11:
				{
					// 非阻塞模式下是正常的
					break;
				}
				// Connection reset by peer
			case 104:
				{
					const char *errMsg = GetErrorMsg(LastError);
					SIXLog("SIX_Socket.Recv.retv[%d].Error.B[%s]",retv,errMsg);
					CC_SAFE_DELETE(errMsg);
					goto close;
				}
			default:
				{
					const char *errMsg = GetErrorMsg(LastError);
					SIXLog("SIX_Socket.Recv.retv[%d].Error.C[%s]",retv,errMsg);
					CC_SAFE_DELETE(errMsg);
					break;
				}
#endif
			}
		}
		// 其他错误(-2)
		// 不做处理
		else
		{
			const char *errMsg = GetErrorMsg(LastError);
			SIXLog("SIX_Socket.Recv.retv[%d].Error.D[%s]",retv,errMsg);
			CC_SAFE_DELETE(errMsg);
		}
	}
	return 0;
close:
	// 默认以闪断方式断开,在内部进行处理
	close(CLOSE_TYPE_FLASH_CLOSE);
	return -1;
}

int SIX_Socket::Send(const char* buf,int len,int flags)
{
	if (!getConnected() || IsInvalid())
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

int SIX_Socket::close(CLOSE_TYPE iCloseType)
{
	this->setInited(false);

	if (!getConnected() || IsInvalid())
	{
		m_sock = INVALID_SOCKET;
		return -2;
	}

	// 如果并未设置过标志位，否则以之前标志位为准
	if (getCloseType()==CLOSE_TYPE_NO)
	{
		// 设置标志位先~
		setCloseType(iCloseType);
	}
	setConnected(false);

	// 再通知上层套接字已经断开
	OnClose(getCloseType());

	// 最后真正断开
	int retv = CloseSocket(m_sock);
	m_sock = INVALID_SOCKET;
	return retv;
}

int SIX_Socket::GetErrorNumber()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

const char *SIX_Socket::GetErrorMsg(int number)
{
#ifdef WIN32
	LPTSTR pBuffer;
	DWORD retv = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,0,number,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPTSTR)&pBuffer,0,0);
	if (retv)
	{
		char *fmt = new char[MAX_PATH];
		sprintf_s(fmt,MAX_PATH-1,"(%d)%s",
			number,
			SIX_Utility::GetInstance()->G2U(SIX_Utility::GetInstance()->UnicodeToAnsi(pBuffer).c_str()).c_str());
		LocalFree(pBuffer);
		return fmt;
	}
	return 0;
#else
	char *fmt = new char[260];
	snprintf(fmt,259,"(%d)%s",number,strerror(number));
	return fmt;
#endif
}

bool SIX_Socket::getConnected()
{
	return m_bConnected;
}

void SIX_Socket::setConnected(bool connected)
{
	m_bConnected = connected;
}

CLOSE_TYPE SIX_Socket::getCloseType()
{
	return m_iCloseType;
}

void SIX_Socket::setCloseType(CLOSE_TYPE iCloseType)
{
	m_iCloseType = iCloseType;
}

bool SIX_Socket::IsInvalid()
{
	return (m_sock==INVALID_SOCKET)?true:false;
}

void SIX_Socket::setInited(bool bInited)
{
	m_bInited = bInited;
}

bool SIX_Socket::getInited()
{
	return m_bInited;
}
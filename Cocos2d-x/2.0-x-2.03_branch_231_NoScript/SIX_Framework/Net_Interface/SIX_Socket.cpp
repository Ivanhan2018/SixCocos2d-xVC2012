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
	setConnecting(false);
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
	if (getConnected() || getConnecting())
		return false;

	this->setConnecting(true);
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
		this->setConnecting(false);
		return false;
	}

	// 设置接收超时
	if (::setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_RCVTIMEO.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		this->setConnecting(false);
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
		this->setConnecting(false);
		return false;
	}
#else
	if (::setsockopt(m_sock,SOL_SOCKET,SO_LINGER,(const char*)&lingerStruct,sizeof(lingerStruct))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_LINGER.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		this->setConnecting(false);
		return false;
	}
#endif

    // 设置SOCKET为KEEPALIVE
    if(true)
    {
        int optval=1;
        if(setsockopt(m_sock, SOL_SOCKET, SO_KEEPALIVE, (char *) &optval, sizeof(optval)))
        {
            this->setConnecting(false);
            return false;
        }
    }

	struct sockaddr_in remote_addr;
	memset(&remote_addr,0,sizeof(remote_addr));
	//remote_addr.sin_family = AF_INET;
	//remote_addr.sin_addr.s_addr = inet_addr(addr);
	//remote_addr.sin_port = htons(port);

    struct hostent* hp;
     
    hp = gethostbyname(addr);
    if(!hp){
        return false;
    }
    memcpy((char*)&remote_addr.sin_addr, hp->h_addr, hp->h_length);
    remote_addr.sin_family = hp->h_addrtype;
    remote_addr.sin_port = htons(port);


	if (!Asyn)
	{
		SetAsynMode(false);
		int ret = connect(m_sock,(struct sockaddr*)&remote_addr,sizeof(remote_addr));
		if (ret==SOCKET_ERROR)
		{
			const char *errMsg = GetErrorMsg(GetErrorNumber());
			SIXLog("MT:Connect.Asyn[%d].Error[%s]",Asyn,errMsg);
			CC_SAFE_DELETE(errMsg);
			this->OnConnectFail(false,ret,remote_addr);
			this->setConnecting(false);
			return false;
		}
	}
	else
	{
		// 设置异步套接字
		SetAsynMode(true);

		int ret = connect(m_sock,(sockaddr*)&remote_addr,sizeof(remote_addr));
		SIXLog("Connect.ret[%d].waitTime[%d]",ret,waitTime);

		// 本机连接，可能会直接连接上，则ret==0
		// 非本机连接或者ret==-1，要进行select超时处理来判断是否真正连接成功
		// Cool.Cat
		if (ret==-1)
		{
#ifdef WIN32

			// 设置连接超时(单位s)
			struct timeval selectTimeout;
			selectTimeout.tv_sec = waitTime;
			selectTimeout.tv_usec = 0;

			// select监视写操作
			fd_set w;
			FD_ZERO(&w);
			FD_SET(m_sock,&w);

			ret = select(0,0,&w,0,&selectTimeout);

			// SOCKET_ERROR or timeout=0
			if (ret<=0)
			{
				const char *errMsg = GetErrorMsg(GetErrorNumber());
				SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].A",Asyn,errMsg,ret);
				CC_SAFE_DELETE(errMsg);
				this->OnConnectFail(false,ret,remote_addr);
				this->setConnecting(false);
				return false;
			}
#else
			// 连接错误，有可能网卡被禁用或者wifi未开启？
			// ENETUNREACH(101)
			if (GetErrorNumber()!=EINPROGRESS)
			{
				const char *errMsg = GetErrorMsg(GetErrorNumber());
				SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].B",Asyn,errMsg,ret);
				CC_SAFE_DELETE(errMsg);
				this->OnConnectFail(false,ret,remote_addr);
				this->setConnecting(false);
				return false;
			}
			else
			{
				fd_set r;
				fd_set w;
				struct timeval selectTimeout;
				bool jump = false;
				while (!jump)
				{
					// 设置连接超时(单位s)
					selectTimeout.tv_sec = waitTime;
					selectTimeout.tv_usec = 0;

					// 重置读操作
					FD_ZERO(&r);
					FD_SET(m_sock,&r);

					// 重置写操作
					FD_ZERO(&w);
					FD_SET(m_sock,&w);

					ret = select(m_sock+1,&r,&w,0,&selectTimeout);

					switch (ret)
					{
						// got a error
					case -1:
						{
							const char *errMsg = GetErrorMsg(GetErrorNumber());
							SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].C",Asyn,errMsg,ret);
							CC_SAFE_DELETE(errMsg);
							this->OnConnectFail(false,ret,remote_addr);
							this->setConnecting(false);
							return false;
						}
						// timeout
					case 0:
						{
							const char *errMsg = GetErrorMsg(GetErrorNumber());
							SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].D",Asyn,errMsg,ret);
							CC_SAFE_DELETE(errMsg);
							this->OnConnectFail(false,ret,remote_addr);
							this->setConnecting(false);
							return false;
						}
					default:
						{
							// r可读 或 w可写
							if (FD_ISSET(m_sock,&r) || FD_ISSET(m_sock,&w))
							{
								// 检查套接字上是否有错误产生
								int error = 0;
								int len = 0;
								int ret2 = getsockopt(m_sock,SOL_SOCKET,SO_ERROR,&error,&len);
								if (ret2<0)
								{
									const char *errMsg = GetErrorMsg(GetErrorNumber());
									SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].ret2[%d].error[%d].E",Asyn,errMsg,ret,ret2,error);
									CC_SAFE_DELETE(errMsg);
									this->OnConnectFail(false,ret,remote_addr);
									this->setConnecting(false);
									return false;
								}
								// 上面的判断似乎无效，不论是否连接出错，都会进入下面处理。。。
								else
								{
									// 连接出错？
									if (GetErrorNumber()!=EINPROGRESS)
									{
										const char *errMsg = GetErrorMsg(GetErrorNumber());
										SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].ret2[%d].error[%d].F",Asyn,errMsg,ret,ret2,error);
										CC_SAFE_DELETE(errMsg);
										this->OnConnectFail(false,ret,remote_addr);
										this->setConnecting(false);
										return false;
									}
									// 连接正常
									else
									{
										const char *errMsg = GetErrorMsg(GetErrorNumber());
										SIXLog("Connect.Asyn[%d].Error[%s].ret[%d].ret2[%d].error[%d].G",Asyn,errMsg,ret,ret2,error);
										CC_SAFE_DELETE(errMsg);
									}
								}
								jump = true;
							}
							break;
						}
					}
				}
			}
#endif
		}
		SIXLog("Connect.Asyn[%d].ret[%d]",Asyn,ret);

		// 重新设置回阻塞方式
		SetAsynMode(false);
	}

	setConnected(true);
	this->OnConnect(false,remote_addr);
	setCloseType(CLOSE_TYPE_NO);
	this->setConnecting(false);
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

bool SIX_Socket::getConnecting()
{
	return m_bConnecting;
}

void SIX_Socket::setConnecting(bool connecting)
{
	m_bConnecting = connecting;
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
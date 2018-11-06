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

// isAsyn = true	�����첽�׽���
// isAsyn = false	����ͬ���׽���
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
	
	// ���÷��ͳ�ʱ(SO_SNDTIMEO/SO_RCVTIMEO��λΪms)
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

	// ���ý��ճ�ʱ
	if (::setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		const char *errMsg = GetErrorMsg(GetErrorNumber());
		SIXLog("Connect.SO_RCVTIMEO.Error[%s]",errMsg);
		CC_SAFE_DELETE(errMsg);
		return false;
	}

	// �����׽��ֱ��رպ������жϣ��������time_out״̬
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
		// �����첽�׽���
#ifdef WIN32
		SetAsynMode(true);
#endif

		int ret = ::connect(m_sock,(sockaddr*)&remote_addr,sizeof(remote_addr));

#ifndef WIN32
		SetAsynMode(true);
#endif

		// select����д����
		fd_set w;
		FD_ZERO(&w);
		FD_SET(m_sock,&w);

		// �������ӳ�ʱ(��λs)
		struct timeval selectTimeout;
		selectTimeout.tv_sec = waitTime;
		selectTimeout.tv_usec = 0;

		// �ȴ�connect���
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

		// �������û�������ʽ
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
	// �������ݳɹ�
	if (retv>0)
	{
		OnRecv(msg,retv);
		CC_SAFE_DELETE(msg);
		return 0;
	}

	CC_SAFE_DELETE(msg);

	// �׽����Ѿ���ʱ �� �ر�
	if (retv==0)
	{
		// ������ģʽ����������
		//const char *errMsg = GetErrorMsg(LastError);
		//SIXLog("SIX_Socket.Recv.retv[%d].Error.A[%s]",retv,errMsg);
		//CC_SAFE_DELETE(errMsg);
		//goto close;
	}
	// �������ݴ���
	else if (retv<0)
	{
		// �׽����ϳ��ִ���
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
					// ������ģʽ����������
					break;
				}
				// WSAENOTSOCK(e.g:socket�Ѿ���Ч�ˣ������ѱ��ͷŵ�)
			case 10038:
				// WSAECONNABORTED(e.g:ֱ�ӵ��õײ�close)
			case 10053:
				// WSAECONNRESET(e.g:�������� �� �� ����������ر�)
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
					// ������ģʽ����������
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
		// ��������(-2)
		// ��������
		else
		{
			const char *errMsg = GetErrorMsg(LastError);
			SIXLog("SIX_Socket.Recv.retv[%d].Error.D[%s]",retv,errMsg);
			CC_SAFE_DELETE(errMsg);
		}
	}
	return 0;
close:
	// Ĭ�������Ϸ�ʽ�Ͽ�,���ڲ����д���
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

	// �����δ���ù���־λ��������֮ǰ��־λΪ׼
	if (getCloseType()==CLOSE_TYPE_NO)
	{
		// ���ñ�־λ��~
		setCloseType(iCloseType);
	}
	setConnected(false);

	// ��֪ͨ�ϲ��׽����Ѿ��Ͽ�
	OnClose(getCloseType());

	// ��������Ͽ�
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
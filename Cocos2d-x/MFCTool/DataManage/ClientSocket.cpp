#include "stdafx.h"
#include "ClientSocket.h"
#include <winsock2.h>
#include <crtdbg.h>
#include <stdio.h>

//#include "Distributed_Header.h"
#include "CoreHead.h"
//#include "Global_Macro.h"
//#include "zlib.h"
#pragma comment( lib, "ws2_32.lib")
ClientSocket::ClientSocket() : fd_(INVALID_SOCKET)
{
}

ClientSocket::~ClientSocket()
{
	_ASSERT(this->fd_ == INVALID_SOCKET);
}

bool ClientSocket::Connect(const char * addr, unsigned short port, DATA_RECEIVER handler, LOGIC_EXCEPTION exception)
{
	_ASSERT(addr && port > 0 && handler && exception);

	if (this->fd_ != INVALID_SOCKET)
		return false;

	struct in_addr ip;
	hostent * st = gethostbyname(addr);
	if(!st) return false;

	memcpy(&ip, st->h_addr_list[0], 4);

	sockaddr_in sa;
	sa.sin_addr = ip;
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;

	this->fd_ = (int)::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->fd_ == INVALID_SOCKET)
		return false;

	if (::connect(this->fd_, (sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	//int tot = 30000;
	//if (setsockopt(this->fd_, SOL_SOCKET, SO_SNDTIMEO, (const char *)&tot,sizeof(tot)) == -1)
	//{
	//	::closesocket(this->fd_);
	//	this->fd_ = INVALID_SOCKET;
	//	return false;
	//}

	int rsize = 65535;
	if (setsockopt(this->fd_, SOL_SOCKET, SO_RCVBUF, (const char *)&rsize, sizeof(rsize)) == -1)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	int wsize = 8192;
	if (setsockopt(this->fd_, SOL_SOCKET, SO_SNDBUF, (const char *)&wsize, sizeof(wsize)) == -1)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	this->handler_ = handler;
	this->exception_ = exception;

	if (!this->Start())
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	return true;
}

static void base64encrypt(unsigned char * out, const unsigned char * in, int inlen)
{
	const char base64digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	for (; inlen >= 3; inlen -= 3)
	{
		*out++ = base64digits[in[0] >> 2];
		*out++ = base64digits[((in[0] << 4) & 0x30) | (in[1] >> 4)];
		*out++ = base64digits[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
		*out++ = base64digits[in[2] & 0x3f];
		in += 3;
	}

	if (inlen > 0)
	{
		unsigned char fragment;

		*out++ = base64digits[in[0] >> 2];
		fragment = (in[0] << 4) & 0x30;
		if (inlen > 1)
			fragment |= in[1] >> 4;
		*out++ = base64digits[fragment];
		*out++ = (inlen < 2) ? '=' : base64digits[(in[1] << 2) & 0x3c];
		*out++ = '=';
	}
	*out = '\0';
};

bool ClientSocket::ProxyConnect(const char * proxy_addr, unsigned short proxy_port, const char * username, const char * password,
								const char * addr, short port, DATA_RECEIVER handler, LOGIC_EXCEPTION exception)
{
	_ASSERT(proxy_addr && proxy_port && addr && port > 0 && handler && exception);

	if (this->fd_ != INVALID_SOCKET)
		return false;

	struct in_addr proxyip;
	hostent * st = gethostbyname(proxy_addr);
	if(!st) return false;

	memcpy(&proxyip, st->h_addr_list[0], 4);

	sockaddr_in sa;
	sa.sin_addr = proxyip;
	sa.sin_port = htons(proxy_port);
	sa.sin_family = AF_INET;

	this->fd_ = (int)::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->fd_ == INVALID_SOCKET)
		return false;

	if (::connect(this->fd_, (sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	//int tot = 30000;
	//if (setsockopt(this->fd_, SOL_SOCKET, SO_SNDTIMEO, (const char *)&tot,sizeof(tot)) == -1)
	//{
	//	::closesocket(this->fd_);
	//	this->fd_ = INVALID_SOCKET;
	//	return false;
	//}

	int rsize = 65535;
	if (setsockopt(this->fd_, SOL_SOCKET, SO_RCVBUF, (const char *)&rsize, sizeof(rsize)) == -1)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	int wsize = 8192;
	if (setsockopt(this->fd_, SOL_SOCKET, SO_SNDBUF, (const char *)&wsize, sizeof(wsize)) == -1)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	char buf[1024];

	if (!username || !username[0])
	{
		::sprintf(buf, "CONNECT %s:%d HTTP/1.0\r\nUser-Agent: Mozilla/4.0\r\n"
			"Connection: Keep-Alive\r\n\r\n", addr, port);
	}
	else if (!password || !password[0])
	{
		::closesocket(this->fd_);
		return false;
	}
	else
	{
		char auth[1024], autht[1024];
		::sprintf(autht, "%s:%s", username, password);
		int len = (int)strlen(autht);
		base64encrypt((unsigned char *)auth, (unsigned char *)autht, len);

		::sprintf(buf, "CONNECT %s:%d HTTP/1.0\r\nProxy-Authorization: Basic %s\r\n\r\nUser-Agent: \
					   Mozilla/4.0\r\nConnection: Keep-Alive\r\n\r\n", addr, port, auth);
	}

	int slen = (int)strlen(buf);

	if (this->InSend(buf, (int)strlen(buf)) == SOCKET_ERROR)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	if (::recv(this->fd_, buf, 1024, 0) < 1)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	int mj, mi, c;
	::sscanf(buf, "HTTP/%d.%d %d", &mj, &mi, &c);//执行从字符串中的格式化输入
	if (c != 200)
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}

	this->handler_ = handler;
	this->exception_ = exception;

	if (!this->Start())
	{
		::closesocket(this->fd_);
		this->fd_ = INVALID_SOCKET;
		return false;
	}
	
	return true;
}

void ClientSocket::Disconnect()
{
	if (this->fd_ == INVALID_SOCKET)
		return ;

	::shutdown(this->fd_, SD_BOTH);
	::closesocket(this->fd_);
	this->fd_ = INVALID_SOCKET;

	this->Stop();
}

int ClientSocket::Send(const char * buf, int len)
{
	_ASSERT(buf && len > 0);

	//DISTRIBUTED_HEADER * dd = (DISTRIBUTED_HEADER *)buf;
	//_ASSERT(dd->to > 0);
	
	//CORE_MSG_HEAD * dd = (CORE_MSG_HEAD *)buf;

	//if (len >= 300/*LARGE_BOUND*/)
	//{
	//	char tmp[32768];
	//	int tmp_len = 32768;

	//	bool f = ZLIB_Compress(tmp, tmp_len, (char *)buf, len);
	//	_ASSERT(f);

	//	//DISTRIBUTED_HEADER * header = (DISTRIBUTED_HEADER *)tmp;
	//	//return InSend(tmp, header->length); 
	//	CORE_MSG_HEAD * header = (CORE_MSG_HEAD *)tmp;
	//	return InSend(tmp, header->iTotalSize); 
	//}
	
	return InSend(buf, len); 
}

int ClientSocket::InSend(const char * buf, int len)
{
	_ASSERT(buf && len > 0);

	if (this->fd_ == INVALID_SOCKET) 
		return SOCKET_ERROR;

	for ( int sent = 0, tmp = 0 ; ; )
	{
		tmp = ::send(this->fd_, buf + sent, len - sent, 0);
		if (tmp < 1) return SOCKET_ERROR;

		sent += tmp;
		if (len == sent) return sent;
	}

	return SOCKET_ERROR;
}

bool ClientSocket::Connected() const
{
	return this->fd_ != INVALID_SOCKET;
}

int ClientSocket::Recv(char * buf, int len)
{
	_ASSERT(buf && len > 0);

	if (this->fd_ == INVALID_SOCKET) 
		return SOCKET_ERROR;

	for ( int recvl = 0, tmp = 0 ; ; )
	{
		tmp = ::recv(this->fd_, buf + recvl, len - recvl, 0);
		if (tmp < 1) return SOCKET_ERROR;

		recvl += tmp;
		if (len == recvl) return recvl;
	}

	return SOCKET_ERROR;
}

bool ClientSocket::ZLIB_Compress(char * desc, int & desc_len, char * src, int src_len)
{
	//static int header_len = sizeof(DISTRIBUTED_HEADER);

	//DISTRIBUTED_HEADER * header = (DISTRIBUTED_HEADER *)src;
	//char * ptr = src + header_len;
	//uLong ptr_len = src_len - header_len;

	//::memcpy(desc, src, header_len);

	//if (compress((Bytef *)(desc + header_len),
	//	(uLong*)&desc_len, (Bytef *)ptr, ptr_len) != Z_OK)
	//{
	//	return false;
	//}

	//header = (DISTRIBUTED_HEADER *)desc;
	//header->length = desc_len + header_len;
	//header->src_len = ptr_len + header_len;
	//header->compress = 1;
	return true;
}

bool ClientSocket::ZLIB_Uncompress(char * desc, int & desc_len, char * src, int src_len)
{
	//static int header_len = sizeof(DISTRIBUTED_HEADER);

	//DISTRIBUTED_HEADER * header = (DISTRIBUTED_HEADER *)src;
	//char * ptr = src + header_len;
	//uLong ptr_len = src_len - header_len;

	//::memcpy(desc, src, header_len);

	//if (uncompress((Bytef *)(desc + header_len),
	//	(uLong*)&desc_len, (Bytef *)ptr, ptr_len) != Z_OK)
	//{
	//	return false;
	//}

	//header = (DISTRIBUTED_HEADER *)desc;
	//header->length = desc_len + header_len;
	//header->src_len = 0;
	//header->compress = 0;
	return true;
}

void ClientSocket::Execute()
{
	char buffer[TCP_MAX_LEN + 1];
	char buffer_1[TCP_MAX_LEN + 1];
	char * ptr;
	int len_1;

	while (this->IsRun())
	{
		if (this->Recv(buffer, TCP_HEADER_LEN) == SOCKET_ERROR)
			break;

		int length = *(int *)(buffer + 12);
		if (length > TCP_MAX_LEN)
		{
			_ASSERT(false);
			break;
		}

		if (this->Recv(buffer + TCP_HEADER_LEN, length - TCP_HEADER_LEN) == SOCKET_ERROR)
		{
			break;
		}

		buffer[length] = '\0';

		CORE_MSG_HEAD * h = (CORE_MSG_HEAD *)buffer;
		if (this->handler_)
		{
			this->handler_(buffer, h->iTotalSize, false);
		}
		else
		{
			_ASSERT(false);
			break;
		}
	//	if (h->compress == 1)
	//	{
	//		len_1 = TCP_MAX_LEN;
	//		bool f = ZLIB_Uncompress(buffer_1, len_1, buffer, length);
	//		_ASSERT(f);
	//		ptr = buffer_1;
	//	}
	//	else
	//		ptr = buffer;

	//	h = (DISTRIBUTED_HEADER *)ptr;
	//	if ((h->command == CMD_AGENT_CLIENT_RESPONSE) && this->exception_)
	//	{
	//		int code = *(int *)(ptr + sizeof(*h));
	//		this->exception_(code, h->agent, h->from, h->to);
	//	}
	//	else if (this->handler_)
	//		this->handler_(ptr, h->length, false);
	//	else
	//	{
	//		_ASSERT(false);
	//		break;
	//	}
	}

	::shutdown(this->fd_, SD_BOTH);
	::closesocket(this->fd_);
	this->fd_ = INVALID_SOCKET;

	if (this->handler_)
		this->handler_(0, 0, true);
}
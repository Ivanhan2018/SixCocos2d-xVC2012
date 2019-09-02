#ifndef __INCLUDE_SOCKET_H__
#define __INCLUDE_SOCKET_H__

#include "SingleThread.h"

typedef int (__stdcall * DATA_RECEIVER)(const char * buffer, unsigned int length, bool error);
typedef void (__stdcall * LOGIC_EXCEPTION)(int code, int agent_id, int from_id, int to_id);

class ClientSocket : protected SingleThread  
{
	enum { TCP_HEADER_LEN =16 /*11*/ };
	enum { TCP_MAX_LEN = 65535 };

public:
	ClientSocket();
	virtual ~ClientSocket();	

	bool Connect(const char *, unsigned short ,
		DATA_RECEIVER, LOGIC_EXCEPTION);

	bool ProxyConnect(const char *, unsigned short, const char *, const char *, 
		const char *, short, DATA_RECEIVER, LOGIC_EXCEPTION);

	void Disconnect();

	bool Connected() const;

	int Send(const char *, int);

protected:
	bool ZLIB_Compress(char * desc, int & desc_len, char * src, int src_len);
	bool ZLIB_Uncompress(char * desc, int & desc_len, char * src, int src_len);

	int InSend(const char *, int);
	int Recv(char *, int);
	void Execute();

private:
	int  fd_;
	DATA_RECEIVER handler_;
	LOGIC_EXCEPTION exception_;
};

#endif // __INCLUDE_SOCKET_H__

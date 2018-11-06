
#ifndef CORE_CLIENT_H
#define CORE_CLIENT_H

#include <WinSock2.h>

#include "./CloseType.h"
#include "./MemBlockPool.h"
#include "./Log.h"

class __declspec(dllexport)  CCommTcpClient;

#include <hash_map>
using std::hash_map;
using std::pair;

// 子类不能用单键模式，是因为一个工程中可能有多个客户端。
class __declspec(dllexport) CCoreClient
{
public:
	CCoreClient(void);
	~CCoreClient(void);

	

public:
	
	// 设置消息块的长度
	void set_msg_block_size(int iMsgBlockSize=2048);

	// 设置消息池的最初元素数量
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	// 设置发送结果池的最初元素数量
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// 设置断线重连的间隔时间，单位ms
	void set_reconnect_interval_time(int iAutoReConnectTime);

	// 获得断线重连
	bool get_reconnect();

	// 设置断线重连
	void set_reconnect(bool bAutoReConnect);

	// 获得关闭方式
	CLOSE_TYPE get_close_type();

	// 设置关闭方式
	void set_close_type(CLOSE_TYPE iCloseType);

	// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
	void set_shrink_pools_time(LONGLONG iShrinkPoolsTime);

	// 设置发送心跳包的时间
	void set_send_heartbeat_time(LONGLONG iSendHeartbeatTime);

	// 设置日志的路径
	int set_log_path(TCHAR* pszPathName);

	/* --------------------------------------------------------------------------
	函数说明：初始化
	返回值：
		成功则返回 0，失败返回错误码如下：
		10  执行 WSAStartup 失败
		20  建立消息池失败
		40  建立发送结果池失败
		50  m_hConnection 执行 WSASocket 失败
		60  CreateIoCompletionPort 失败
		70  建立 IOCP 的工作线程失败
		90  建立定时检查的线程失败
	--------------------------------------------------------------------------*/
	int init();

	// 启动
	int start();

	// 停止
	int stop();

	/* --------------------------------------------------------------------------
	函数说明：发送数据
	传入参数：
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	int send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	/* --------------------------------------------------------------------------
	函数说明：发送错误数据，用于测试
	传入参数：
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	int send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// 设置连接地址
	void set_connect_addr(const char* szListenAddr);

	// 设置连接端口
	void set_connect_port(unsigned int nPort);

	// 接收小包已完成
	int OnRecvComplete(int iResult, const CMemBlock* pRecv);

	// 主动关闭服务端，目的是让服务端能区别出客户端主动关闭与闪断
	int power_close();

	/* --------------------------------------------------------------------------
	函数说明：列印未归池（在池外）的元素
	传出参数：
		vecOutPool	未归池（在池外）的元素数组
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	void display_out_pool(bool bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool);
		
	// 显示所有的池信息
	void display_all_pool();

	// 发送心跳包
	int send_heartbeat_packeg();

	/* --------------------------------------------------------------------------
	函数说明：写入日志语句
	传入参数：
		iType	类型，参考 LOG_ERR_TYPE 枚举，
					LOG_TYPE_PROMPT = 0,	// 提示
					LOG_TYPE_WARING = 1,	// 警告
					LOG_TYPE_ERR = 2,		// 错误与异常

		pszSentence		日志语句
		iSentenceLen	日志语句的长度
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int write_log(int iType, TCHAR* pszSentence, int iSentenceLen);

	/* --------------------------------------------------------------------------
	函数说明：写入日志语句，仅在 Debug 中生效，Release 中不写的，目的是方便在脚本中调试
	传入参数：
		iType	类型，参考 LOG_ERR_TYPE 枚举，
					LOG_TYPE_PROMPT = 0,	// 提示
					LOG_TYPE_WARING = 1,	// 警告
					LOG_TYPE_ERR = 2,		// 错误与异常

		pszSentence		日志语句
		iSentenceLen	日志语句的长度
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int write_log_debug(int iType, TCHAR* pszSentence, int iSentenceLen);

public:		
	//--- 回调函数 ------------------------

	/* --------------------------------------------------------------------------
	函数说明：响应连接成功
	传入参数：
		bIsReconnect	是否重连
		addrConnect		SOCKET 地址
	--------------------------------------------------------------------------*/
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect) = 0;

	// 响应连接失败
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect) = 0;

	/* --------------------------------------------------------------------------
	函数说明：响应发送成功
	传入参数：
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	/* --------------------------------------------------------------------------
	函数说明：响应发送失败
	传入参数：
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;
	
	/* --------------------------------------------------------------------------
	函数说明：响应关闭服务端
	传入参数：
		bClientClose	是否客户端关闭
	--------------------------------------------------------------------------*/
	virtual void OnClose(CLOSE_TYPE iCloseType) = 0;

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息
	传入参数：
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	virtual void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	// 响应通讯错误的消息
	virtual void OnCommError(char* pszError) = 0;

private:
	CCommTcpClient* m_pTcpClient;	// TCP 通讯层，无法被 CCoreServer 的子类直接使用，总是说“未定义的变量”
									// 只能通过 CCoreServer 的函数来封装 CCommTcpServer 中的功能

	wstring		m_strPath;		// 日志的路径
	CLog*		m_pLogPrompt;	// 提示日志，
	CLog*		m_pLogWaring;	// 警告日志，
	CLog*		m_pLogErr;		// 错误与异常日志


};

#endif
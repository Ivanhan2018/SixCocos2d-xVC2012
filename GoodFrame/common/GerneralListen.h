
#ifndef GERNERAL_LISTEN_H
#define GERNERAL_LISTEN_H

// 通用接收器
class CGerneralListen
{
public:
	CGerneralListen(void);
	~CGerneralListen(void);

	// 接收器响应从发射器传来的消息，是同步的，非异步，发射器是要等待本函数执行完毕的。
	virtual int OnResponse(int iMainCode, int iSubCode, void* pData, int iDataLen) = 0;


};

// 通用发射器
class CGerneralSink
{
public:
	CGerneralSink(void);
	~CGerneralSink(void);

	// 设置通用接收器指针
	void set_gerneral_listen(CGerneralListen* pGerneralListen);

	// 发向接收器，是同步的，非异步，是要等待接收器执行完毕的。
	virtual int send_to_listen(int iMainCode, int iSubCode, void* pData, int iDataLen);

private:
	CGerneralListen* m_pGerneralListen;  // 通用接收器指针
};

#endif
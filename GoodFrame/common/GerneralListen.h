
#ifndef GERNERAL_LISTEN_H
#define GERNERAL_LISTEN_H

// ͨ�ý�����
class CGerneralListen
{
public:
	CGerneralListen(void);
	~CGerneralListen(void);

	// ��������Ӧ�ӷ�������������Ϣ����ͬ���ģ����첽����������Ҫ�ȴ�������ִ����ϵġ�
	virtual int OnResponse(int iMainCode, int iSubCode, void* pData, int iDataLen) = 0;


};

// ͨ�÷�����
class CGerneralSink
{
public:
	CGerneralSink(void);
	~CGerneralSink(void);

	// ����ͨ�ý�����ָ��
	void set_gerneral_listen(CGerneralListen* pGerneralListen);

	// �������������ͬ���ģ����첽����Ҫ�ȴ�������ִ����ϵġ�
	virtual int send_to_listen(int iMainCode, int iSubCode, void* pData, int iDataLen);

private:
	CGerneralListen* m_pGerneralListen;  // ͨ�ý�����ָ��
};

#endif
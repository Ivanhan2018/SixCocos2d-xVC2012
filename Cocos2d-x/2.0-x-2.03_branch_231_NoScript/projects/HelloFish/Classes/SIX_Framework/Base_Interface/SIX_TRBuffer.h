/***********************************************
Name��SIX_TRBuffer
Desc��FIFO+Ring Buffer
Auth��Cool.Cat@2013-08-14
***********************************************/
#pragma once
#include <SIX_Lock.h>
#include <map>
#include <algorithm>
using namespace std;

template<typename T>
class SIX_TRBuffer
{
public:
	SIX_TRBuffer(unsigned int size)
	{
#ifdef WIN32
		mutex = new SIX_SpinLock();
#else
		mutex = new SIX_Mutex();
#endif
		m_uData = new T[size];
		m_iSize = size;
		Clean();
		m_bInited = true;
	}

	~SIX_TRBuffer()
	{
		Destory();
		m_bInited = false;
		CC_SAFE_DELETE(mutex);
	}
public:
	void Clean()
	{
		SIX_Lock lock(mutex);
		memset(m_uData,0,m_iSize);
		m_iOffsetRead = m_iOffsetWrite = 0;
		m_iSizeCanWrite = m_iSize;
	}

	int ReadBuffer(T *pData,unsigned int readLen,bool needErase=true)
	{
		if (!m_bInited)
			return 0;

		SIX_Lock lock(mutex);

		if (!pData || !readLen || m_iSizeCanWrite == m_iSize)
			return 0;

		// �ɶ�����=������-��д����
		unsigned int sizeCanRead = m_iSize-m_iSizeCanWrite;

		// ���Ҫ��ȡ�Ĵ�С�����ɶ�ȡ�Ļ�������С
		if (readLen>sizeCanRead)
			readLen = sizeCanRead;

		// ��ǰ�ɶ�ȡ�Ļ�������С
		unsigned int leftReadSize = m_iSize-m_iOffsetRead;

		// ���Ҫ��ȡ�Ĵ�С������ǰ�ɶ�ȡ�Ļ�������С�Ļ�
		if(readLen>leftReadSize)
		{
			// �ȿ���ƨ�ɺ���ʣ��Ķ�����
			memcpy(pData,m_uData+m_iOffsetRead,leftReadSize);
			// �ٴ�ͷ����ʣ��Ĳ���
			memcpy(pData+leftReadSize,m_uData,readLen-leftReadSize);
		}
		else
		{
			// ����ֱ�ӴӶ�ƫ�ƿ�ʼ��������
			memcpy(pData,m_uData+m_iOffsetRead,readLen);
		}

		if (needErase)
		{
			// ���㵱ǰ��ƫ��
			m_iOffsetRead = (m_iOffsetRead+readLen)%m_iSize;
			m_iSizeCanWrite += readLen;
		}

		return readLen;
	}

	int WriteBuffer(T *pData,unsigned int writeLen)
	{
		if (!m_bInited)
			return 0;

		SIX_Lock lock(mutex);

		if (!pData || !writeLen || !m_iSizeCanWrite)
			return 0;

		// ���Ҫд��Ĵ�С������д��Ļ�������С
		if (writeLen>m_iSizeCanWrite)
			writeLen = m_iSizeCanWrite;

		// ��ǰ��д��Ļ�������С
		unsigned int leftWriteSize = m_iSize-m_iOffsetWrite;

		// ���Ҫд��Ĵ�С������ǰ��д��Ļ�������С�Ļ�
		if(writeLen>leftWriteSize)
		{
			// ��дƨ��
			memcpy(m_uData+m_iOffsetWrite,pData,leftWriteSize);
			// ʣ�µ���дͷ
			memcpy(m_uData,pData+leftWriteSize,writeLen-leftWriteSize);
		}
		else
		{
			// ����ֱ�Ӵ�дƫ�ƿ�ʼ��������
			memcpy(m_uData+m_iOffsetWrite,pData,writeLen);
		}

		// ���㵱ǰдƫ��
		m_iOffsetWrite = (m_iOffsetWrite+writeLen)%m_iSize;
		m_iSizeCanWrite -= writeLen;

		return writeLen;
	}

	unsigned int GetBufferSize()
	{
		if (!m_bInited)
			return 0;
		SIX_Lock lock(mutex);
		return m_iSize;
	}

	unsigned int GetCanWriteSize()
	{
		if (!m_bInited)
			return 0;
		SIX_Lock lock(mutex);
		return m_iSizeCanWrite;
	}

	unsigned int GetCanReadSize()
	{
		if (!m_bInited)
			return 0;
		SIX_Lock lock(mutex);
		return m_iSize-m_iSizeCanWrite;
	}

	void Destory()
	{
		if (!m_bInited)
			return;
		SIX_Lock lock(mutex);
		delete[] m_uData;	
	}
private:
#ifdef WIN32
	SIX_SpinLock *mutex;
#else
	SIX_Mutex *mutex;
#endif
	// ������
	T *m_uData;
	// ������
	unsigned int m_iSize;
	// ��д����
	unsigned int m_iSizeCanWrite;
	// ��ƫ��
	unsigned int m_iOffsetRead;
	// дƫ��
	unsigned int m_iOffsetWrite;

	bool m_bInited;
};
/***********************************************
Name：SIX_TRBuffer
Desc：FIFO+Ring Buffer
Auth：Cool.Cat@2013-08-14
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

		// 可读容量=总容量-可写容量
		unsigned int sizeCanRead = m_iSize-m_iSizeCanWrite;

		// 如果要读取的大小超过可读取的缓冲区大小
		if (readLen>sizeCanRead)
			readLen = sizeCanRead;

		// 当前可读取的缓冲区大小
		unsigned int leftReadSize = m_iSize-m_iOffsetRead;

		// 如果要读取的大小超过当前可读取的缓冲区大小的话
		if(readLen>leftReadSize)
		{
			// 先拷贝屁股后面剩余的读缓冲
			memcpy(pData,m_uData+m_iOffsetRead,leftReadSize);
			// 再从头拷贝剩余的部分
			memcpy(pData+leftReadSize,m_uData,readLen-leftReadSize);
		}
		else
		{
			// 否则直接从读偏移开始拷贝即可
			memcpy(pData,m_uData+m_iOffsetRead,readLen);
		}

		if (needErase)
		{
			// 计算当前读偏移
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

		// 如果要写入的大小超过可写入的缓冲区大小
		if (writeLen>m_iSizeCanWrite)
			writeLen = m_iSizeCanWrite;

		// 当前可写入的缓冲区大小
		unsigned int leftWriteSize = m_iSize-m_iOffsetWrite;

		// 如果要写入的大小超过当前可写入的缓冲区大小的话
		if(writeLen>leftWriteSize)
		{
			// 先写屁股
			memcpy(m_uData+m_iOffsetWrite,pData,leftWriteSize);
			// 剩下的再写头
			memcpy(m_uData,pData+leftWriteSize,writeLen-leftWriteSize);
		}
		else
		{
			// 否则直接从写偏移开始拷贝即可
			memcpy(m_uData+m_iOffsetWrite,pData,writeLen);
		}

		// 计算当前写偏移
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
	// 缓冲区
	T *m_uData;
	// 总容量
	unsigned int m_iSize;
	// 可写容量
	unsigned int m_iSizeCanWrite;
	// 读偏移
	unsigned int m_iOffsetRead;
	// 写偏移
	unsigned int m_iOffsetWrite;

	bool m_bInited;
};
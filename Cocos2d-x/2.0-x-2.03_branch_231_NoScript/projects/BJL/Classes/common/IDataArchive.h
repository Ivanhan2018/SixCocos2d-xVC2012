#ifndef __IDATAARCHIVE_H__
#define __IDATAARCHIVE_H__
#pragma once
#include "Define.h"

// 
struct IArchive
{
	// ����д�뻺�塣nLen < 4K
	// �����и��ٶ���������밴˳��д����������ݣ���ΪCMapContainer�������ʱ
	virtual bool Write(const void* buf,int nLen);
	
	// �������ָ������������
	virtual bool Read(void* buf,int nLen);
	
	// ��ȡ��ǰ����ָ����ָ�����ݵ�ַ���ʺ�ֱ�Ӳ���������
	virtual void* GetBuffer();
	
	// �ѵ�ǰָ������ƶ�nOffset�ֽڣ����ص�ǰָ��
	// �������ʧ�ܣ�Seek����
	virtual int Seek(int nOffset = 0);
	
	// ��ָ���ƶ�ָ��λ��
	virtual int SeekTo(int nPtr = 0);
	
	// ��õ�ǰ����ָ��ƫ��
	virtual int GetBufferOffset();
	
	// ��ȡ����ʱ����ȡʣ�����ݳ��ȣ�д����ʱ��������Ч����������
	virtual int GetLeftBufferLen();
};

// ʹ�ã�CArchive��Ҫ�ⲿ�ṩ������������һ���ֲ�buffer��������:
// char buf[1024];
// CDataArchive archive(buf,1024);
// archive.Write("hello",5);
//class CDataArchive : public IArchive
class CDataArchive
{
protected:
    CDataArchive(void)
	{
		m_nOffset = 0;
		m_pBindBuffer = NULL;
		m_nMaxSize = 0;
	}

	// ��ʼ������
	void Init(void* szBindBuffer, int nMaxSize)
	{
		if (NULL == szBindBuffer || nMaxSize <= 0)
		{
			return;
		}

		m_nOffset = 0;
		m_pBindBuffer = szBindBuffer;
		m_nMaxSize = nMaxSize;
	}
	
public:
	// ���캯��
	CDataArchive(void* szBindBuffer, int nMaxSize)
	{
		m_nOffset = 0;
		m_pBindBuffer = NULL;
		m_nMaxSize = 0;

		Init(szBindBuffer, nMaxSize);
	}

	// ��������
	virtual ~CDataArchive(void)
	{
	};

	// ����д������
	virtual bool Write(const void *buf, int nLen)
	{
		if (buf == NULL || nLen <= 0 || m_nOffset + nLen > m_nMaxSize)
		{
			return false;
		}

		memcpy((char*)m_pBindBuffer + m_nOffset, buf, nLen);
		m_nOffset += nLen;
		return true;
	}

	// ���������������������
	virtual bool Read(void *buf, int nLen)
	{
		if (buf == NULL || nLen <= 0 || m_nOffset + nLen > m_nMaxSize)
		{
			return false;
		}

		memcpy(buf, (char*)m_pBindBuffer + m_nOffset, nLen);
		m_nOffset += nLen;
		return true;
	}
	
	// ��ȡ��ǰ����ָ����ָ�����ݵ�ַ���ʺ�ֱ�Ӳ���������
	virtual void* GetBuffer()
	{
		return (char*)m_pBindBuffer + m_nOffset;
	}
	
	// �ѵ�ǰָ������ƶ�nOffset�ֽڣ������ƶ�ǰ��ָ��
	// ����nOffSet���ɻ�õ�ǰ����ָ��ƫ��
	// �������ʧ�ܣ�Seek����-1
	virtual int Seek(int nOffset)
	{
		if (m_nOffset + nOffset > m_nMaxSize || m_nOffset + nOffset < 0)
		{
			return -1;
		}

		int nOld = m_nOffset;
		m_nOffset += nOffset;
		return nOld;
	}
	
	// ͬ�ϣ��ѻ���ָ���ƶ���ָ��λ�ã������ƶ�ǰ��ָ��
	virtual int SeekTo(int nPtr = 0)
	{
		if (nPtr > m_nMaxSize || nPtr < 0)
		{
			return -1;
		}

		int nOld = m_nOffset;
		m_nOffset = nPtr;
		return nOld;
	}

	// ��õ�ǰ����ָ��ƫ��
	virtual int GetBufferOffset(void)
	{
		return m_nOffset;
	}

	// ��ȡ����ʱ����ȡʣ�����ݳ��ȣ�д����ʱ��������Ч����������
	virtual int GetLeftBufferLen(void)
	{
		return m_nMaxSize - m_nOffset;
	}
	
private:
	int		m_nOffset;
	void* 	m_pBindBuffer;
	int		m_nMaxSize;
};

#endif
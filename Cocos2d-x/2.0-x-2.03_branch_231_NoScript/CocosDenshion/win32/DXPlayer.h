/***********************************************
Name��SoundBuffer
Desc����Ƶ���ݻ���
Auth��Cool.Cat@2013-07-09
***********************************************/
#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <istream>
#include <dsound.h>
#include <tchar.h>
#include "Export.h"
#include <string>
#include <vector>
using namespace std;

namespace CocosDenshion {

struct WaveHeader
{
	BYTE        RIFF[4];          // "RIFF"
	DWORD       dwSize;           // Size of data to follow
	BYTE        WAVE[4];          // "WAVE"
	BYTE        fmt_[4];          // "fmt "
	DWORD       dw16;             // 16
	WORD        wOne_0;           // 1
	WORD        wChnls;           // Number of Channels
	DWORD       dwSRate;          // Sample Rate
	DWORD       BytesPerSec;      // Sample Rate
	WORD        wBlkAlign;        // 1
	WORD        BitsPerSample;    // Sample size
	BYTE        DATA[4];          // "DATA"
	DWORD       dwDSize;          // Number of Samples
};

class DXPlayer
{
public:
	DXPlayer();
	~DXPlayer();
public:
	LPDIRECTSOUNDBUFFER GetBuffer() {return m_pDSBuffer;}

public:
	void Close();

    /**
    @brief ���������ļ�
    @param pFileName ���ŵ������ļ����ƣ���Ҫ�����ļ���·��
    @param nTimes    ���������ļ���ѭ��������Ĭ��ֵΪ 1��������һ��
    */
    void Open(const char* pFileName, UINT uId);

	void Play(UINT uTimes = 1);

    /**
    @brief ��ͣ��������
    */
    void Pause();

    /**
    @brief ������������
    */
    void Resume();

    /**
    @brief ֹͣ��������
    */
    void Stop();

    /**
    @brief ���²���
    */
    void Rewind();

    /**
    @brief ��ȡ��������ǰ�Ƿ����ڲ�����
    */
    bool IsPlaying();

    /**
    @brief ��ȡ��ǰ���ŵ���Ч ID
    @return ��ǰ���ŵ���ЧID
    */
    UINT GetSoundID();

	/**
	@brief �����ٷֱ�(0.0��1.0)
	@return ���ò��ŵ�����
	*/
	void SetVolume(float volRatio);

	/**
	@return ��ȡ���ŵ������ٷֱ�
	*/
	float GetVolume();

	/**
	@return ��ȡ����ʱ��
	*/
	float GetDuration();

private:
	bool CreateSoundBuffer(LPDIRECTSOUND lpDS, DWORD dwFlags, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, bool bStereo);
	bool ReadData(FILE* pFile, DWORD dwSize, DWORD dwPos);
private:
	bool m_bInited;
	HWND m_hWnd;
    UINT m_nSoundID;
    UINT m_uTimes;
    bool m_bPlaying;
	bool m_bIsPaused;
	DWORD m_dwSize;
	float m_fDuration;
protected:
	LPDIRECTSOUNDBUFFER m_pDSBuffer;
};
}
/***********************************************
Name：SoundBuffer
Desc：音频数据缓冲
Auth：Cool.Cat@2013-07-09
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
    @brief 播放声音文件
    @param pFileName 播放的声音文件名称，需要包含文件的路径
    @param nTimes    播放声音文件的循环次数，默认值为 1，即播放一次
    */
    void Open(const char* pFileName, UINT uId);

	void Play(UINT uTimes = 1);

    /**
    @brief 暂停播放声音
    */
    void Pause();

    /**
    @brief 继续播放声音
    */
    void Resume();

    /**
    @brief 停止播放声音
    */
    void Stop();

    /**
    @brief 重新播放
    */
    void Rewind();

    /**
    @brief 获取播放器当前是否正在播放中
    */
    bool IsPlaying();

    /**
    @brief 获取当前播放的音效 ID
    @return 当前播放的音效ID
    */
    UINT GetSoundID();

	/**
	@brief 音量百分比(0.0～1.0)
	@return 设置播放的音量
	*/
	void SetVolume(float volRatio);

	/**
	@return 获取播放的音量百分比
	*/
	float GetVolume();

	/**
	@return 获取持续时间
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
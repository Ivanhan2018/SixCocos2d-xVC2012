#ifndef _MCI_PLAYER_WIN32_H_
#define _MCI_PLAYER_WIN32_H_

#include <windows.h>
#include <mmsystem.h>
#include <Vfw.h>
#include <Digitalv.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
using namespace std;

namespace CocosDenshion {

class MciPlayer
{
public:
    MciPlayer();
    ~MciPlayer();

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
	@brief 获取当前播放设备的ID
	@return 是否存在有效的音频输出
	*/
	bool EnumValidDeviceID(UINT *iWaveDeviceID);

	/**
	@brief 音量百分比(0.0～1.0)
	@return 设置播放的音量
	*/
	void SetVolume(float volRatio);

	/**
	@return 获取播放的音量百分比
	*/
	float GetVolume();

private:
    friend LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    void _SendGenericCommand(int nCommand);

    HWND        m_hWnd;
    MCIDEVICEID m_hDev;
    UINT        m_nSoundID;
    UINT        m_uTimes;
    bool        m_bPlaying;
};

} // end of namespace CocosDenshion

#endif

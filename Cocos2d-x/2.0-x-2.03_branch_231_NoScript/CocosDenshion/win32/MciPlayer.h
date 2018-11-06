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
	@brief ��ȡ��ǰ�����豸��ID
	@return �Ƿ������Ч����Ƶ���
	*/
	bool EnumValidDeviceID(UINT *iWaveDeviceID);

	/**
	@brief �����ٷֱ�(0.0��1.0)
	@return ���ò��ŵ�����
	*/
	void SetVolume(float volRatio);

	/**
	@return ��ȡ���ŵ������ٷֱ�
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

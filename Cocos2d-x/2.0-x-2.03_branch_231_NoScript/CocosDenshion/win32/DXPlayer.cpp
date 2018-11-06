#include "DXPlayer.h"

#define WIN_CLASS_NAME        L"CocosDenshionCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

static HINSTANCE s_hInstance;
static LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#ifdef USING_DSOUND
LPDIRECTSOUND m_pDS = 0;
#endif

wstring Utf8ToUnicode(const char* buf)
{
	int len = ::MultiByteToWideChar(CP_UTF8, 0, buf, -1, 0, 0);
	if (len == 0) return L"";

	std::vector<wchar_t> unicode(len);
	::MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);

	return &unicode[0];
}

DXPlayer::DXPlayer()
{
	m_bIsPaused		= false;
	m_bPlaying		= false;
	m_bInited		= false;
	m_pDSBuffer		= 0;
	m_hWnd			= 0;
	m_nSoundID		= 0;
	m_dwSize		= 0;
	m_fDuration		= 0.0f;

    if (! s_hInstance)
    {
        s_hInstance = GetModuleHandle( NULL );            // Grab An Instance For Our Window

        WNDCLASS  wc;        // Windows Class Structure

        // Redraw On Size, And Own DC For Window.
        wc.style          = 0;  
        wc.lpfnWndProc    = _SoundPlayProc;                    // WndProc Handles Messages
        wc.cbClsExtra     = 0;                              // No Extra Window Data
        wc.cbWndExtra     = 0;                                // No Extra Window Data
        wc.hInstance      = s_hInstance;                    // Set The Instance
        wc.hIcon          = 0;                                // Load The Default Icon
        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );    // Load The Arrow Pointer
        wc.hbrBackground  = NULL;                           // No Background Required For GL
        wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
        wc.lpszClassName  = WIN_CLASS_NAME;                 // Set The Class Name

        if (! RegisterClass(&wc)
            && 1410 != GetLastError())
        {
            return;
        }
    }

    m_hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,                                    // Extended Style For The Window
        WIN_CLASS_NAME,                                        // Class Name
        NULL,                                        // Window Title
        WS_POPUPWINDOW,/*WS_OVERLAPPEDWINDOW*/               // Defined Window Style
        0, 0,                                                // Window Position
        0,                                                    // Window Width
        0,                                                    // Window Height
        NULL,                                                // No Parent Window
        NULL,                                                // No Menu
        s_hInstance,                                        // Instance
        NULL );
    if (m_hWnd)
    {
        SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
    }
}

DXPlayer::~DXPlayer()
{
	Close();
	DestroyWindow(m_hWnd);
	if(m_pDSBuffer)
		m_pDSBuffer->Release();
}

void DXPlayer::Close()
{
    if (m_bPlaying)
    {
        Stop();
    }
    m_bPlaying = false;
}

void DXPlayer::Open(const char* pFileName, UINT uId)
{
    do 
    {
		BREAK_IF(! pFileName || ! m_hWnd || m_bPlaying);

        int nLen = (int)strlen(pFileName);
        BREAK_IF(! nLen);

		if (!m_pDS)
		{
			//// 是否需要指定可用声卡？
			//// Cool.Cat
			// DirectSoundEnumerate

			// 默认为系统当前声卡
			if (DirectSoundCreate(0,&m_pDS,0)!=DS_OK)
			{
				::MessageBox(0,L"创建DirectSound对象失败\n找不到可用的声音设备",0,MB_OK);
				return;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			// 设置协作级别
			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			// 标准级(DSSCL_NORMAL)				该级别只能使用22KHZ、立体声（STEREO）、8位的音乐，并且不能直接的写主缓冲，也不能使用压缩过的声音。
			// 优先级(DSSCL_PAIORITY)			可以实现硬件混合（hardware mixing），可以设置主缓冲的声音格式（可以根据需要来使用不同质量的音乐）和压缩过的音乐。
			// 独占级(DSSCL_EXCLUSIVE)			当应用程序在前台工作时，其它程序是不可使用声音的。
			// 写主缓冲级(DSSCL_WRITEPRIMARY)	最高的合作级，程序可以直接的操纵主缓冲，而且程序必须直接的写主缓冲区（最基层的操作）。
			//									在这种级别，次缓冲将不可用。除了该级别外，所有试图LOCK主缓冲的操作都将失败，也就是说只有该级别可以对主缓冲进行写操作！
			//									当使用写主缓冲级的程序处于前台时，后台所有程序的第二缓冲都将停止且丢失，而如果这时使用写主缓冲级的程序转到后台工作，
			//									它的主缓冲也将丢失并且在又一次转到前台工作时应该还原（restore）。
			//									更多的信息将在缓冲区管理里阐述（现在还没有翻译：P不过用过了DDraw以后这些东西应该很熟悉了才是）。
			//									如果要设置写主缓冲级，先应该确定现在是否可以使用该级别——使用IDirectSound::GetCaps函数，检查DSCAPS结构里是否有DSCAPS_EMULDRIVER标志。
			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			// 1、一般情况下使用标准级即可，如要用到混音或压缩媒体，使用优先级实现；
			// 2、独占级/写主缓冲级在游戏开发中用的比较少，主要用于专业领域，如写声卡驱动、VOIP业务或工控测试等。
			// Cool.Cat
			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (DS_OK != m_pDS->SetCooperativeLevel(m_hWnd,DSSCL_NORMAL))
			{
				::MessageBox(0,L"设置协作级别失败",0,MB_OK);
				return;
			}
		}

        Close();

		TCHAR uIdAlias[MAX_PATH] = {0};
		wsprintf(uIdAlias,L"%u",uId);

		TCHAR fileName[1024] = {0};
		wsprintf(fileName,L"%s",Utf8ToUnicode(pFileName).c_str());

		FILE* pFile = fopen(pFileName,"rb");
		BREAK_IF(!pFile);

		// read wav header~
		WaveHeader wavHdr;
		if (fread(&wavHdr,sizeof(wavHdr),1,pFile)!=1)
		{
			fclose(pFile);
			return;
		}

		m_dwSize = wavHdr.dwDSize;

		// false=单声道
		// true=立体声
		bool bStereo = wavHdr.wChnls>1?true:false;

		DWORD dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_LOCSOFTWARE | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;

		if(CreateSoundBuffer(m_pDS,dwFlags,m_dwSize,wavHdr.dwSRate,wavHdr.BitsPerSample,wavHdr.wBlkAlign,bStereo))
		{
			if (!ReadData(pFile, m_dwSize, sizeof(wavHdr)))
			{
				fclose(pFile);
				MessageBox(0,L"读入声音数据出错",0,MB_OK);
				return;
			}
		}

		fclose(pFile);

        m_nSoundID = uId;
        m_bPlaying = false;
    } while (0);
}

bool DXPlayer::CreateSoundBuffer(LPDIRECTSOUND lpDS, DWORD dwFlags, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, bool bStereo)
{
	if (m_bPlaying)
		return false;

	PCMWAVEFORMAT pcmwf;
	DSBUFFERDESC dsbdesc;

	// 设置wave format结构.
	memset( &pcmwf, 0, sizeof(PCMWAVEFORMAT) );
	pcmwf.wf.wFormatTag         = WAVE_FORMAT_PCM;
	pcmwf.wf.nChannels          = bStereo ? 2 : 1;
	pcmwf.wf.nSamplesPerSec     = dwFreq;
	pcmwf.wf.nBlockAlign        = (WORD)dwBlkAlign;
	pcmwf.wf.nAvgBytesPerSec    = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
	pcmwf.wBitsPerSample        = (WORD)dwBitsPerSample;

	// 设置DSBUFFERDESC结构
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags             = dwFlags;
	dsbdesc.dwBufferBytes       = dwBufSize; 
	dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)(&pcmwf);

	// 如果buffer先前已经创建过，这里应该先释放掉先前的缓冲数据，否则导致memleak!
	// Cool.Cat
	if (m_pDSBuffer)
	{
		m_pDSBuffer->Release();
	}

	if (DS_OK != lpDS->CreateSoundBuffer(&dsbdesc,&m_pDSBuffer,0))
	{
		MessageBox(0,L"创建声音缓冲区失败",0,MB_OK);
		return false;
	}

	m_fDuration = (float)(m_dwSize) / pcmwf.wf.nAvgBytesPerSec;

	return true;
}

bool DXPlayer::ReadData(FILE* pFile, DWORD dwSize, DWORD dwPos)
{
	if (m_bPlaying)
		return false;

	// 定位到文件中的正确位置
	if (dwPos != 0xffffffff && fseek(pFile, dwPos, SEEK_SET) != 0)
		return false;

	LPVOID pData1 = 0;
	DWORD  dwData1Size = 0;
	LPVOID pData2 = 0;
	DWORD  dwData2Size = 0;
	HRESULT rval;

	rval = m_pDSBuffer->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
	if (rval != DS_OK)
		return false;

	// 读取数据
	if (dwData1Size>0 && fread(pData1, dwData1Size, 1, pFile) != 1)
		return false;

	if (dwData2Size>0 && fread(pData2, dwData2Size, 1, pFile) != 1) 
		return false;

	rval = m_pDSBuffer->Unlock(pData1, dwData1Size, pData2, dwData2Size);
	if (rval!=DS_OK)
		return false;
	m_bInited = true;
	return true;
}

void DXPlayer::Play(UINT uTimes /* = 1 */)
{
	if (!m_bInited)
		return;

	if(!m_pDSBuffer)
		return;

	DWORD dwStatus=0;
	if (DS_OK!=m_pDSBuffer->GetStatus(&dwStatus))
	{
		MessageBox(0,L"获取DirectSound缓冲区状态失败！",0,MB_OK);
		return;
	}

	if((dwStatus & DSBSTATUS_PLAYING)==DSBSTATUS_PLAYING)
		return;

	HRESULT hr = 0;
	// 非暂停后的播放，应该重头开始
	// Cool.Cat
	if (!m_bIsPaused)
	{
		hr = m_pDSBuffer->SetCurrentPosition(0);
		if (hr!=DS_OK)
		{
			TCHAR msg[MAX_PATH] = {0};
			wsprintf(msg,L"SetCurrentPosition.error[0x%08X]\n",hr);
			::OutputDebugString(msg);
			return;
		}
	}

	hr = m_pDSBuffer->Play(0,0,(uTimes==-1)?DSBPLAY_LOOPING:0);
	if (hr!=DS_OK)
	{
		TCHAR msg[MAX_PATH] = {0};
		wsprintf(msg,L"Play.error[0x%08X]\n",hr);
		::OutputDebugString(msg);
		return;
	}

	m_bIsPaused = false;
	m_bPlaying = true;
	m_uTimes = uTimes;
	if (m_uTimes!=-1 && m_uTimes>=1)
		m_uTimes -= 1;
}

void DXPlayer::Pause()
{
	if (!m_bInited)
		return;

	m_bIsPaused = true;
	Stop();
}

void DXPlayer::Resume()
{
	if (!m_bInited)
		return;

	Play(m_uTimes);
}

void DXPlayer::Stop()
{
	if (!m_bInited)
		return;

	if (!m_pDSBuffer)
		return;
	
	DWORD dwStatus = 0;
	if (m_pDSBuffer->GetStatus(&dwStatus)!=DS_OK)
		return;

	// 当前不是播放状态
	if ((dwStatus & DSBSTATUS_PLAYING)!=DSBSTATUS_PLAYING)
		return;

	if (m_pDSBuffer->Stop()!=DS_OK)
		return;

	m_bPlaying = false;
}

void DXPlayer::Rewind()
{
	if (!m_bInited)
		return;

	m_pDSBuffer->SetCurrentPosition(0);
	Play(m_uTimes);
}

bool DXPlayer::IsPlaying()
{
	return m_bPlaying;
}

UINT DXPlayer::GetSoundID()
{
	return m_nSoundID;
}

void DXPlayer::SetVolume(float percent)
{
	if (!m_bInited)
		return;

	double decibels = 0.0;
	long nVolume = 0;
	if (percent<=0.0)
		nVolume=DSBVOLUME_MIN;
	else if (percent>=1.0)
		nVolume=DSBVOLUME_MAX;
	else
	{
		decibels = 20.0 * log10(percent);
		nVolume = (long)(decibels * 100.0);
		//nVolume=DSBVOLUME_MIN+(DSBVOLUME_MAX-DSBVOLUME_MIN)*percent;
	}
    HRESULT hr = GetBuffer()->SetVolume(nVolume);
	if (hr!=DS_OK)
	{
		TCHAR msg[MAX_PATH] = {0};
		wsprintf(msg,L"SetVolume.error[0x%08X]\n",hr);
		::OutputDebugString(msg);
	}
}

float DXPlayer::GetVolume()
{
	if (!m_bInited)
		return 0.0;

	long nVolume = 0;
	HRESULT hr = GetBuffer()->GetVolume(&nVolume);
	if (hr!=DS_OK)
	{
		TCHAR msg[MAX_PATH] = {0};
		wsprintf(msg,L"GetVolume.error[0x%08X]\n",hr);
		::OutputDebugString(msg);
		return 0.0;
	}

	float percent = 0.0;
	double decibels = 0.0;
	if (nVolume==DSBVOLUME_MIN)
		percent = 0.0;
	else if (nVolume==DSBVOLUME_MAX)
		percent = 1.0;
	else
	{
		//decibels = 20.0 * log10(percent);
		//nVolume = (long)(decibels * 100.0);
		//nVolume = 2000 * log10(percent);
		//log10(percent) = nVolume/2000;
		//log10(1000) = 3
		decibels = nVolume / 2000.0;
		percent = pow(10,decibels);
	}
	return percent;
}

float DXPlayer::GetDuration()
{
	if (!m_bInited)
		return 0.0;
	return m_fDuration;
}

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
}
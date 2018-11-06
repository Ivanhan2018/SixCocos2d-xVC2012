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
			//// �Ƿ���Ҫָ������������
			//// Cool.Cat
			// DirectSoundEnumerate

			// Ĭ��Ϊϵͳ��ǰ����
			if (DirectSoundCreate(0,&m_pDS,0)!=DS_OK)
			{
				::MessageBox(0,L"����DirectSound����ʧ��\n�Ҳ������õ������豸",0,MB_OK);
				return;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			// ����Э������
			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			// ��׼��(DSSCL_NORMAL)				�ü���ֻ��ʹ��22KHZ����������STEREO����8λ�����֣����Ҳ���ֱ�ӵ�д�����壬Ҳ����ʹ��ѹ������������
			// ���ȼ�(DSSCL_PAIORITY)			����ʵ��Ӳ����ϣ�hardware mixing�������������������������ʽ�����Ը�����Ҫ��ʹ�ò�ͬ���������֣���ѹ���������֡�
			// ��ռ��(DSSCL_EXCLUSIVE)			��Ӧ�ó�����ǰ̨����ʱ�����������ǲ���ʹ�������ġ�
			// д�����弶(DSSCL_WRITEPRIMARY)	��ߵĺ��������������ֱ�ӵĲ��������壬���ҳ������ֱ�ӵ�д���������������Ĳ�������
			//									�����ּ��𣬴λ��彫�����á����˸ü����⣬������ͼLOCK������Ĳ�������ʧ�ܣ�Ҳ����˵ֻ�иü�����Զ����������д������
			//									��ʹ��д�����弶�ĳ�����ǰ̨ʱ����̨���г���ĵڶ����嶼��ֹͣ�Ҷ�ʧ���������ʱʹ��д�����弶�ĳ���ת����̨������
			//									����������Ҳ����ʧ��������һ��ת��ǰ̨����ʱӦ�û�ԭ��restore����
			//									�������Ϣ���ڻ�������������������ڻ�û�з��룺P�����ù���DDraw�Ժ���Щ����Ӧ�ú���Ϥ�˲��ǣ���
			//									���Ҫ����д�����弶����Ӧ��ȷ�������Ƿ����ʹ�øü��𡪡�ʹ��IDirectSound::GetCaps���������DSCAPS�ṹ���Ƿ���DSCAPS_EMULDRIVER��־��
			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			// 1��һ�������ʹ�ñ�׼�����ɣ���Ҫ�õ�������ѹ��ý�壬ʹ�����ȼ�ʵ�֣�
			// 2����ռ��/д�����弶����Ϸ�������õıȽ��٣���Ҫ����רҵ������д����������VOIPҵ��򹤿ز��Եȡ�
			// Cool.Cat
			// ------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (DS_OK != m_pDS->SetCooperativeLevel(m_hWnd,DSSCL_NORMAL))
			{
				::MessageBox(0,L"����Э������ʧ��",0,MB_OK);
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

		// false=������
		// true=������
		bool bStereo = wavHdr.wChnls>1?true:false;

		DWORD dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_LOCSOFTWARE | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;

		if(CreateSoundBuffer(m_pDS,dwFlags,m_dwSize,wavHdr.dwSRate,wavHdr.BitsPerSample,wavHdr.wBlkAlign,bStereo))
		{
			if (!ReadData(pFile, m_dwSize, sizeof(wavHdr)))
			{
				fclose(pFile);
				MessageBox(0,L"�����������ݳ���",0,MB_OK);
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

	// ����wave format�ṹ.
	memset( &pcmwf, 0, sizeof(PCMWAVEFORMAT) );
	pcmwf.wf.wFormatTag         = WAVE_FORMAT_PCM;
	pcmwf.wf.nChannels          = bStereo ? 2 : 1;
	pcmwf.wf.nSamplesPerSec     = dwFreq;
	pcmwf.wf.nBlockAlign        = (WORD)dwBlkAlign;
	pcmwf.wf.nAvgBytesPerSec    = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
	pcmwf.wBitsPerSample        = (WORD)dwBitsPerSample;

	// ����DSBUFFERDESC�ṹ
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags             = dwFlags;
	dsbdesc.dwBufferBytes       = dwBufSize; 
	dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)(&pcmwf);

	// ���buffer��ǰ�Ѿ�������������Ӧ�����ͷŵ���ǰ�Ļ������ݣ�������memleak!
	// Cool.Cat
	if (m_pDSBuffer)
	{
		m_pDSBuffer->Release();
	}

	if (DS_OK != lpDS->CreateSoundBuffer(&dsbdesc,&m_pDSBuffer,0))
	{
		MessageBox(0,L"��������������ʧ��",0,MB_OK);
		return false;
	}

	m_fDuration = (float)(m_dwSize) / pcmwf.wf.nAvgBytesPerSec;

	return true;
}

bool DXPlayer::ReadData(FILE* pFile, DWORD dwSize, DWORD dwPos)
{
	if (m_bPlaying)
		return false;

	// ��λ���ļ��е���ȷλ��
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

	// ��ȡ����
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
		MessageBox(0,L"��ȡDirectSound������״̬ʧ�ܣ�",0,MB_OK);
		return;
	}

	if((dwStatus & DSBSTATUS_PLAYING)==DSBSTATUS_PLAYING)
		return;

	HRESULT hr = 0;
	// ����ͣ��Ĳ��ţ�Ӧ����ͷ��ʼ
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

	// ��ǰ���ǲ���״̬
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
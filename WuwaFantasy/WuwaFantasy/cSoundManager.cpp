#include "stdafx.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	HRESULT hr;

	CoInitialize(NULL);

	DirectSoundCreate8(NULL, &m_pSound, NULL);
	m_pSound->SetCooperativeLevel(g_hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);

	//NEW DSBUFFERDESC Struct
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;

	hr = m_pSound->CreateSoundBuffer(&dsdesc, &m_pPrimeryBuffer, NULL);

	//Create Primary Buffer
	WAVEFORMATEX wformat;
	wformat.cbSize = sizeof(WAVEFORMATEX);
	wformat.wFormatTag = WAVE_FORMAT_PCM;
	wformat.nChannels = 2;
	wformat.nSamplesPerSec = 44100;
	wformat.wBitsPerSample = 16;
	wformat.nBlockAlign = wformat.nChannels * (wformat.wBitsPerSample / 8);
	wformat.nAvgBytesPerSec = wformat.nSamplesPerSec * wformat.nBlockAlign;

	hr = m_pPrimeryBuffer->SetFormat(&wformat);

}

cSoundManager::~cSoundManager()
{

}

typedef std::map<std::string, LPDIRECTSOUNDBUFFER> mapSoundBuffer;
typedef std::map<std::string, LPDIRECTSOUNDBUFFER>::iterator miSoundBuffer;

typedef std::map<std::string, LPDIRECTSOUND3DBUFFER8> mapSound3DBuffer;
typedef std::map<std::string, LPDIRECTSOUND3DBUFFER8>::iterator miSound3DBuffer;

static mapSoundBuffer m_mapSoundBuffer;
static mapSound3DBuffer m_mapSound3DBuffer;

BOOL cSoundManager::CreateDxSoundBuffer(
	LPDIRECTSOUNDBUFFER* secondSoundBuffer,
	DWORD dxSoundFlags,
	GUID guidAlgorithm,
	const char * szFileName)
{
	HRESULT hr;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;

	//WAV file load
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)szFileName, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc)
	{
		return FALSE;
	}

	//WAV chank check;
	ZeroMemory(&mSrcWaveFile, sizeof(MMCKINFO));
	hr = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		mmioClose(hSrc, 0);
		return FALSE;
	}

	//FMT chank check
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	hr = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		return FALSE;
	}

	//Calc Header Size
	int nSrcHeaderSize = mSrcWaveFmt.cksize;
	if (nSrcHeaderSize<sizeof(WAVEFORMATEX))
		nSrcHeaderSize = sizeof(WAVEFORMATEX);

	//Set Header Memory
	LPWAVEFORMATEX hFormat = new WAVEFORMATEX[nSrcHeaderSize];
	ZeroMemory(hFormat, nSrcHeaderSize * sizeof(WAVEFORMATEX));

	//Load of WAVE Files
	hr = mmioRead(hSrc, (char*)hFormat, mSrcWaveFmt.cksize);
	if (FAILED(hr)) {
		SAFE_DELETE(hFormat);
		mmioClose(hSrc, 0);
		return FALSE;
	}
	m_nChannelCount = hFormat->nChannels;
	m_nSamplingRate = hFormat->nSamplesPerSec;
	m_nBitRate = hFormat->wBitsPerSample;

	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	//Find Data chank
	while (1) {
		//Selecting
		hr = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
		if (FAILED(hr)) {
			SAFE_DELETE(hFormat);
			mmioClose(hSrc, 0);
			return FALSE;
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// goto back
		hr = mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	m_nDataSize = mSrcWaveData.cksize;

	//Create Second Sound Buffer
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = dxSoundFlags;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = hFormat;
	dsdesc.guid3DAlgorithm = guidAlgorithm;
	
	hr = m_pSound->CreateSoundBuffer(&dsdesc, secondSoundBuffer, NULL);
	if (FAILED(hr)) {	
		SAFE_DELETE(hFormat);
		mmioClose(hSrc, 0);
		return FALSE;
	}

	//Buffer Lock
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	hr = (*secondSoundBuffer)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(hr)) {
		SAFE_DELETE(hFormat);
		mmioClose(hSrc, 0);
		return FALSE;
	}

	// Writing Data
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// Release Buffer
	(*secondSoundBuffer)->Unlock(pMem1, dwSize1, pMem2, dwSize2);
	// Delete Format
	SAFE_DELETE(hFormat);

	// Close WAV File
	mmioClose(hSrc, 0);

	return TRUE;
}

BOOL cSoundManager::CreateDxSound3DBuffer(LPDIRECTSOUND3DBUFFER * secondSoundBuffer, const char * szFileName)
{
	HRESULT hr;
	LPDIRECTSOUNDBUFFER secondBuffer;

	CreateDxSoundBuffer(&secondBuffer,
		DSBCAPS_CTRL3D,
		DS3DALG_HRTF_FULL,
		szFileName);

	hr = secondBuffer->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)secondSoundBuffer);
	if (FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}

void cSoundManager::AddSound(const char* szName, const char * szFileName)
{
	std::string szFilePath(szFileName);
	std::string szFullPath = SOUND_PATH + szFilePath.substr();

	LPDIRECTSOUNDBUFFER secondBuffer;
	CreateDxSoundBuffer(
		&secondBuffer, 
		DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | 
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN, 
		DS3DALG_DEFAULT, 
		szFullPath.c_str()
	);

	m_mapSoundBuffer.insert(std::make_pair(szName, secondBuffer));
}

void cSoundManager::Add3DSound(const char * szName, const char * szFileName)
{
	LPDIRECTSOUND3DBUFFER second3DBuffer;
	if (!CreateDxSound3DBuffer(&second3DBuffer, szFileName)) return;
	
	m_mapSound3DBuffer.insert(std::make_pair(szName, second3DBuffer));
}

void cSoundManager::Release()
{
	miSoundBuffer iter;
	for (iter = m_mapSoundBuffer.begin(); iter != m_mapSoundBuffer.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_RELEASE(iter->second);
			iter = m_mapSoundBuffer.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	miSound3DBuffer iter3D;
	for (iter3D = m_mapSound3DBuffer.begin(); iter3D != m_mapSound3DBuffer.end();)
	{
		if (iter3D->second != NULL)
		{
			SAFE_RELEASE(iter3D->second);
			iter3D = m_mapSound3DBuffer.erase(iter3D);
		}
		else
		{
			++iter;
		}
	}
	CoUninitialize();
}

void cSoundManager::Start(const char * szName)
{
	miSoundBuffer iter = m_mapSoundBuffer.find(szName);

	if(iter->second) iter->second->Play(0, 0, 0);
}

void cSoundManager::Stop(const char * szName)
{
	miSoundBuffer iter = m_mapSoundBuffer.find(szName);
	if (iter != m_mapSoundBuffer.end())
	{
		iter->second->Stop();
		return;
	}
}

void cSoundManager::SetVolume(const char* szName, int vol)
{
	//volume is -10000 MIN, 0 MAX
	miSoundBuffer iter = m_mapSoundBuffer.find(szName);
	if (vol > DSBVOLUME_MAX) vol = DSBVOLUME_MAX;
	else if (vol < DSBVOLUME_MIN) vol = DSBVOLUME_MIN;

	iter->second->SetVolume(vol);
}

void cSoundManager::SetVolumeTenCount(const char * szName, int vol)
{
	//volume is 0 MIN, 10 MAX
	miSoundBuffer iter = m_mapSoundBuffer.find(szName);
	if (vol < 0) vol = 0;
	else if (vol > 10) vol = 10;

	vol = (10 - vol) * (DSBVOLUME_MIN / 10);

	iter->second->SetVolume(vol);
}

void cSoundManager::SetPens(const char * szName, int pan)
{
	miSoundBuffer iter = m_mapSoundBuffer.find(szName);
	iter->second->SetVolume(pan);
}

void cSoundManager::SetPrimeryVolume(int vol)
{
	//volume is -10000 MIN, 0 MAX
	if (vol > DSBVOLUME_MAX) vol = DSBVOLUME_MAX;
	else if (vol < DSBVOLUME_MIN) vol = DSBVOLUME_MIN;

	m_pPrimeryBuffer->SetVolume(vol);
}

void cSoundManager::SetPrimeryVolumeTenCount(int vol)
{
	//volume is 0 MIN, 10 MAX
	if (vol < 0) vol = 0;
	else if (vol > 10) vol = 10;

	vol = (10 - vol) * (DSBVOLUME_MIN / 10);

	m_pPrimeryBuffer->SetVolume(vol);
}

void cSoundManager::SetPrimeryPens(int pan)
{
	m_pPrimeryBuffer->SetPan(pan);
}

BOOL cSoundManager::Get3DSoundListener(LPDIRECTSOUND3DLISTENER * pp3DSoundListener)
{
	return 0;
}

void cSoundManager::Set3DOptions(const char * szName, LPDS3DBUFFER pDs3DBuffer)
{
}

LPDS3DBUFFER cSoundManager::Get3DOptions(const char * szName)
{
	return LPDS3DBUFFER();
}

void cSoundManager::Set3DMaxDistance(const char * szName, const float & nMaxDistance)
{
}

float cSoundManager::Get3DMaxDistance(const char * szName) const
{
	return 0.0f;
}

void cSoundManager::Set3DMinDistance(const char * szName, const float & nMinDistance)
{
}

float cSoundManager::Get3DMinDistance(const char * szName) const
{
	return 0.0f;
}

void cSoundManager::Set3DPosition(const char * szName, const D3DXVECTOR3 & pos)
{
}

D3DXVECTOR3 cSoundManager::Get3DPosition(const char * szName) const
{
	return D3DXVECTOR3();
}

void cSoundManager::Set3DConsAngle(const char * szName, const DWORD & insideAngle, const DWORD & outsideAngle)
{
}

void cSoundManager::Get3DConsAngle(const char * szName, LPDWORD insideAngle, LPDWORD outsideAngle) const
{
}

void cSoundManager::Set3DConsOrientation(const char * szName, const D3DXVECTOR3 & ori)
{
}

D3DXVECTOR3 cSoundManager::Get3DConsOrientaiton(const char * szName) const
{
	return D3DXVECTOR3();
}

void cSoundManager::Set3DConsOutsideVolume(const char * szName, const LONG & outsideVolume)
{
}

LONG cSoundManager::Get3DConsOutsideVolume(const char * szName) const
{
	return 0;
}

void cSoundManager::Set3DVelocity(const char * szName, const D3DXVECTOR3 & vel)
{
}

void cSoundManager::Get3DVelocity(const char * szName, float * x, float * y, float * z)
{
}

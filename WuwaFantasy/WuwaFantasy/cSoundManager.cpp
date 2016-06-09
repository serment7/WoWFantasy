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
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
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

static mapSoundBuffer m_mapSoundBuffer;


BOOL cSoundManager::CreateSoundBuffer(LPDIRECTSOUNDBUFFER* secondSoundBuffer, const char * szFileName)
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
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = hFormat;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	hr = m_pSound->CreateSoundBuffer(&dsdesc, secondSoundBuffer, NULL);
	if (FAILED(hr)) {
#ifdef DEBUG
		assert(FAILED(hr) && "Create Buffer FAILED");
#endif		
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

void cSoundManager::AddSound(const char* szName, const char * szFileName)
{
	std::string szFilePath(szFileName);
	std::string szFullPath = SOUND_PATH + szFilePath.substr();

	LPDIRECTSOUNDBUFFER secondBuffer;
	CreateSoundBuffer(&secondBuffer, szFullPath.c_str());

	m_mapSoundBuffer.insert(std::make_pair(szName, secondBuffer));
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
	if(iter->second) iter->second->Stop();
}

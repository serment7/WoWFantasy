#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	: m_pSound(nullptr)
	, m_pSoundBuffer(nullptr)
	, m_nChannelCount(0)
	, m_nSamplingRate(0)
	, m_nBitRate(0)
	, m_nDataSize(0)
{
	HRESULT hr;
	//Create Primary Buffer
	WAVEFORMATEX wformat;

	//NEW DSBUFFERDESC Struct
	DSBUFFERDESC dsdesc;
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;

	hr = m_pSound->CreateSoundBuffer(&dsdesc, &m_pSoundBuffer, NULL);
#ifdef DEBUG
	assert(hr == D3D_OK && "Error DSBUFFERDESC Create Struct");
#endif // DEBUG
	wformat.cbSize = sizeof(WAVEFORMATEX);
	wformat.wFormatTag = WAVE_FORMAT_PCM;
	wformat.nChannels = 2;
	wformat.nSamplesPerSec = 44100;
	wformat.wBitsPerSample = 16;
	wformat.nBlockAlign = wformat.nChannels * (wformat.wBitsPerSample / 8);
	wformat.nAvgBytesPerSec = wformat.nSamplesPerSec * wformat.nBlockAlign;
		
	hr = m_pSoundBuffer->SetFormat(&wformat);
#ifdef DEBUG
	assert(hr == S_OK && "Error WAVEFORMATEX Create Struct");
#endif // DEBUG
}

cSoundManager::~cSoundManager()
{

}

typedef std::map<std::string, LPDIRECTSOUNDBUFFER> mapSoundBuffer;
typedef std::map<std::string, LPDIRECTSOUNDBUFFER>::iterator miSoundBuffer;

static mapSoundBuffer m_mapSoundBuffer;


BOOL cSoundManager::CreateSoundBuffer(LPDIRECTSOUNDBUFFER * secondSoundBuffer, const char * szFileName)
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
#ifdef DEBUG
		assert(hSrc && "WAV load FAILED");
#endif // DEBUG
		return FALSE;
	}

	//WAV chank check;
	ZeroMemory(&mSrcWaveFile, sizeof(MMCKINFO));
	hr = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
#ifdef DEBUG
		assert(mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E') && "THIS FILE is NOT WAV");
#endif
		mmioClose(hSrc, 0);
		return FALSE;
	}

	//FMT chank check
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	hr = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
#ifdef DEBUG
		assert((mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ') && "THIS FILE is NOT FMT");
#endif
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
#ifdef DEBUG
		assert(FAILED(hr) && "WAV LODE FAILED");
#endif
		SAFE_DELETE(hFormat);
		mmioClose(hSrc, 0);
		return FALSE;
	}
	//m_nChannelCount = hFormat->nChannels;
	//m_nSamplingRate = hFormat->nSamplesPerSec;
	//m_nBitRate = hFormat->wBitsPerSample;

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

	//m_nDataSize = mSrcWaveData.cksize;

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
#ifdef DEBUG
		assert(FAILED(hr) && "LOCK FAILED");
#endif	
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

void cSoundManager::AddSound(const char * szFileName)
{
	LPDIRECTSOUNDBUFFER pSoundBuffer = NULL;
	CreateSoundBuffer(&pSoundBuffer, szFileName);

	m_mapSoundBuffer.insert(std::make_pair(szFileName, pSoundBuffer));
}

void cSoundManager::Release()
{
	miSoundBuffer iter;
	for (iter = m_mapSoundBuffer.begin(); iter != m_mapSoundBuffer.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = m_mapSoundBuffer.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	SAFE_DELETE(m_pSound);
	SAFE_DELETE(m_pSoundBuffer);

}

void cSoundManager::Start(const char * szFileName)
{
	miSoundBuffer iter = m_mapSoundBuffer.find(szFileName);

	if(iter->second) iter->second->Play(0, 0, 0);
}

void cSoundManager::Stop(const char * szFileName)
{
	miSoundBuffer iter = m_mapSoundBuffer.find(szFileName);
	if(iter->second) iter->second->Stop();
}

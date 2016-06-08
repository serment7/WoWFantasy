#pragma once

#define g_pSoundManager cSoundManager::GetInstance() 

class cSoundManager
{
private:
	LPDIRECTSOUND8			m_pSound;
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;

	int						m_nChannelCount;
	int						m_nSamplingRate;
	int						m_nBitRate;
	int						m_nDataSize;

private:
	BOOL CreateSoundBuffer(LPDIRECTSOUNDBUFFER* secondSoundBuffer, const char* szFileName);

public:

	static cSoundManager* GetInstance()
	{
		static cSoundManager* inst;
		return inst;
	}

	cSoundManager();
	~cSoundManager();
	
	void AddSound(const char* szFileName);
	void Release();
	void Start(const char* szFileName);
	void Stop(const char* szFileName);
};


#pragma once

#define g_pSoundManager cSoundManager::GetInstance() 

const std::string SOUND_PATH = "./Resource/Sound/";

class cSoundManager
{
private:
	LPDIRECTSOUND8			m_pSound;
	LPDIRECTSOUNDBUFFER		m_pPrimeryBuffer;

	int						m_nChannelCount;
	int						m_nSamplingRate;
	int						m_nBitRate;
	int						m_nDataSize;

private:
	BOOL CreateSoundBuffer(LPDIRECTSOUNDBUFFER* secondSoundBuffer, const char* szFileName);

public:

	static cSoundManager* GetInstance()
	{
		static cSoundManager inst;
		return &inst;
	}

	cSoundManager();
	~cSoundManager();
	
	void AddSound(const char* szName, const char* szFileName);
	void Release();
	void Start(const char* szName);
	void Stop(const char* szName);
	//void SetVolume(int vol);

};


#pragma once

#define g_pSoundManager cSoundManager::GetInstance() 

const std::string SOUND_PATH = "./Resource/Sound/";

class cSoundManager
{
private:
	LPDIRECTSOUND8			m_pSound;
	LPDIRECTSOUNDBUFFER	m_pPrimeryBuffer;

	int						m_nChannelCount;
	int						m_nSamplingRate;
	int						m_nBitRate;
	int						m_nDataSize;

private:
	BOOL CreateDxSoundBuffer(LPDIRECTSOUNDBUFFER* secondSoundBuffer, DWORD dxSoundFlags, GUID guidAlgorithm, const char* szFileName);
	BOOL CreateDxSound3DBuffer(LPDIRECTSOUND3DBUFFER* secondSoundBuffer, const char* szFileName);

public:

	static cSoundManager* GetInstance()
	{
		static cSoundManager inst;
		return &inst;
	}

	cSoundManager();
	~cSoundManager();
	
	void AddSound(const char* szName, const char* szFileName);
	void Add3DSound(const char* szName, const char* szFileName);
	void Release();
	void Start(const char* szName);
	void Stop(const char* szName);

//===========================2D SOUNDS=============================
	//individual
	void SetVolume(const char* szName, int vol);
	void SetVolumeTenCount(const char* szName, int vol);
	void SetPens(const char* szName, int pan);

	//several
	void SetPrimeryVolume(int vol);
	void SetPrimeryVolumeTenCount(int vol);
	void SetPrimeryPens(int pan);

	//=======================3D SOUNDS=============================
	//3D Sound
	BOOL Get3DSoundListener(LPDIRECTSOUND3DLISTENER* pp3DSoundListener);
	
	//3D Buffer Option
	void Set3DOptions(const char* szName, LPDS3DBUFFER pDs3DBuffer);
	LPDS3DBUFFER Get3DOptions(const char* szName);

	//Distance
	void Set3DMaxDistance(const char* szName, const float &nMaxDistance);
	float Get3DMaxDistance(const char* szName) const;	
	void Set3DMinDistance(const char* szName, const float &nMinDistance);
	float Get3DMinDistance(const char* szName) const;
	
	//Position
	void Set3DPosition(const char* szName, const D3DXVECTOR3 &pos);
	D3DXVECTOR3 Get3DPosition(const char* szName) const;

	//Cons
	void Set3DConsAngle(const char* szName, const DWORD &insideAngle, const DWORD &outsideAngle);
	void Get3DConsAngle(const char* szName, LPDWORD insideAngle, LPDWORD outsideAngle) const;
	void Set3DConsOrientation(const char* szName, const D3DXVECTOR3 &ori);
	D3DXVECTOR3 Get3DConsOrientaiton(const char* szName) const;
	void Set3DConsOutsideVolume(const char* szName, const LONG &outsideVolume);
	LONG Get3DConsOutsideVolume(const char* szName) const;

	//Velocity
	void Set3DVelocity(const char* szName, const D3DXVECTOR3 &vel);
	void Get3DVelocity(const char* szName, float* x, float* y, float* z);

};


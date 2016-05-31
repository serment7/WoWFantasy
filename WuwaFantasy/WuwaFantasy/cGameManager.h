#pragma once
#include"cCamera.h"

#define g_pGameManager	cGameManager::GetInstance()
#define g_pCamera		cGameManager::GetInstance()->GetCamera();

class cGameManager
{
private:
	RECT				m_rcClientSize;
	POINT				m_ptCursor;
	int					m_nFPS;
	int					m_nFPSCount;
	float				m_fCalFPSTime;

	cCamera				m_camera;

public:
	cGameManager();
	~cGameManager();

	static cGameManager* GetInstance()
	{
		static cGameManager instance;
		return &instance;
	}

	void Update();
	void UpdateClientSize();
	void UpdateCursorPoint();

	const int& GetFPS();
	cCamera* GetCamera();
};
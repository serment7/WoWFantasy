#pragma once
#include"cCamera.h"

#define g_pGameManager	cGameManager::GetInstance()
#define g_pCamera		cGameManager::GetInstance()->GetCamera();

class cIScript;

class cGameManager
{
private:
	RECT				m_rcClientSize;
	POINT				m_ptCursor;
	int					m_nFPS;
	int					m_nFPSCount;
	float				m_fCalFPSTime;

	cCamera				m_camera;
	cCamera				m_dramaCamera;

	bool				m_bRunScript;
	cIScript*			m_pScript;

	int					m_nPlayerID;

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
	void UpdateCursorPointInGlobal();
	void UpdateCursorPointByWindow(const HWND& _targetWindow);

	const int& GetFPS();

	cCamera* GetCamera();
	cCamera* GetDramaCamera();
	void SetScrpit(cIScript* _script);

	const int& GetPlayerID();
	void SetPlayerID(int _nPlayerID);
};
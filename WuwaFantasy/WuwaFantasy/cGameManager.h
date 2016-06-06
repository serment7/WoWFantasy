#pragma once
#include"cCamera.h"

#define g_pGameManager	cGameManager::GetInstance()
#define g_pCamera		cGameManager::GetInstance()->GetCamera();

class cIScript;
class cGameObject;
typedef cGameObject	ENTITY_TYPE;
class cJob;
class cSkill;

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
	cIScript*			m_pDramaScript;

	int					m_nPlayerID;

	std::map<std::string, size_t>		m_mapObjectType;
	std::map<std::string, cSkill*>		m_mapSkill;
	std::map<std::string, cJob*>		m_mapJob;

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

	const int&		GetFPS();
	const POINT&	GetCursorPoint();

	cCamera*		GetCamera();
	cCamera*		GetDramaCamera();
	void			SetScrpit(cIScript* _script);

	const int&		GetPlayerID();
	void			SetPlayerID(int _nPlayerID);

	void RegisterObjectType(const std::string& _typename, const size_t& _tagID);
	void RegisterSkill(cSkill* _skill);
	void RegisterJob(cJob* job);
};
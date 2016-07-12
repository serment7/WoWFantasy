#pragma once
#include"cCamera.h"

#define g_pGameManager	cGameManager::GetInstance()
#define g_pCamera		cGameManager::GetInstance()->GetCamera();

class cIScript;
class cGameObject;
class cJob;
class cSkill;
class cMap;
class cUIClass;
class cHmap;
struct ST_STATUS;

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
	cCamera*			m_pWorldCamera;

	bool				m_bRunScript;
	cIScript*			m_pDramaScript;

	int					m_nPlayerID;

	D3DXVECTOR3			m_vRespawnPos=D3DXVECTOR3(0,0,0);

	std::map<std::string, size_t>		m_mapObjectType;
	std::map<std::string, ST_STATUS>	m_mapStatus;

	std::vector<cHmap*>			m_vecMap;

	bool				m_bUseWorldCamera=false;

	D3DXMATRIXA16				m_matView;
	D3DXMATRIXA16				m_matProj;
	D3DXMATRIXA16				m_matPort;
	D3DVIEWPORT9				m_viewport;

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

	void			Destroy();

	const int&		GetFPS();
	const POINT&	GetCursorPoint();

	cCamera*		GetCamera();
	cCamera*		GetDramaCamera();
	void			SetScript(cIScript* _script);

	const int&		GetPlayerID();
	void			SetPlayerID(int _nPlayerID);

	void RegisterObjectType(const std::string& _typename, const size_t& _tagID);
	void RegisterStatus(const std::string& _typename, const ST_STATUS& _status);

	const size_t FindObjectType(const std::string& _typename);
	const ST_STATUS FindStatus(const std::string& _statusname);

	void					AddMap(cHmap* _map);
	std::vector<cHmap*>&	GetMap();
	const RECT&				GetClientSize();

	const D3DXMATRIXA16& GetViewMat();
	const D3DXMATRIXA16& GetProjMat();
	const D3DXMATRIXA16& GetPortMat();

	void					SetRespawnPos(const D3DXVECTOR3& _pos);
	const D3DXVECTOR3&		GetRespawnPos();

	void MessageHandle(const HWND& hWnd, const UINT& iMessage,const WPARAM& wParam,const LPARAM& lParam);
};
#pragma once

#define g_pUserHUD cUserHUD::GetInstance()

class cUIClass;
class cProgressBar;
class cMiniMap;

class cUserHUD
{
private:
	cUIClass*		m_pUIClass=nullptr;
	cGameObject*	m_pUser = nullptr;
	
	cProgressBar*	m_pUserHPBar=nullptr;
	cProgressBar*	m_pUserMPBar = nullptr;

	cGameObject*	m_pTarget = nullptr;
	cProgressBar*	m_pTargetHPBar = nullptr;
	cMiniMap*		m_pMinimap = nullptr;

	std::map<size_t ,cProgressBar*> m_mapPartyHPBar;
	std::map<size_t, cProgressBar*> m_mapPartyMPBar;

	std::vector<cGameObject*> m_vecObjects;

	LPD3DXFONT		m_font = nullptr;

	cUserHUD();
	~cUserHUD();

public:
	
	static cUserHUD*	GetInstance()
	{
		static cUserHUD instance;
		return &instance;
	}

	void	EnterScene();
	void	ExitScene();
	void	Update();
	void	Render();
	void	AddParty(cGameObject* _pParty);
	void	SetSkill(const char& _key,cSkill* _pSkill);
	void	SetTarget(cGameObject* _pTarget);
	void    LostTarget();
	void    RegisterObjectOnMinimap(cGameObject* _pObject);
};


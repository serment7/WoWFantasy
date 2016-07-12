#pragma once
#include "cIScene.h"
#include "cPlayer.h"
#include "cCamera.h"

class cGameObject;
class cUIObject;
class cSkyBox;

class cInGameScene : 
	public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;
	cCamera*		m_pCamera;
	cPlayer*		m_pPlayer;

	int				m_nSoundVolume;

	std::vector<cGameObject*> m_vecObject;

	D3DLIGHT9		m_light;

	cUIObject*		m_pUIRoot;
	LPD3DXFONT		m_pFont;
	LPD3DXSPRITE	m_pSprite;

	cSkyBox*		m_pSkyBox=nullptr;

public:
	cInGameScene();
	virtual ~cInGameScene();

	virtual void	Update();
	virtual void	Render();
	virtual void	EnterScene();
	virtual void	ExitScene();
	virtual void	ChangeScene(cIScene* _pNextScene);
	virtual void	MessageHandling(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
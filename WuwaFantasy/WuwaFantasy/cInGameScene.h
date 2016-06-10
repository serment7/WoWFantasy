#pragma once
#include "cIScene.h"
#include "cGrid.h"
#include "cPlayer.h"
#include "cCamera.h"

class cGameObject;

class cInGameScene : 
	public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;
	cGrid*			m_pGrid;
	cCamera*		m_pCamera;
	cPlayer*		m_pPlayer;

	std::vector<cGameObject*> m_vecObject;

	D3DLIGHT9		m_light;

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
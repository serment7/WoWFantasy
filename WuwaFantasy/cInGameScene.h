#pragma once
#include "cIScene.h"
#include "cGrid.h"
#include "cPlayer.h"
#include "cCamera.h"

class cObject;

class cInGameScene : 
	public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;
	cGrid*			m_pGrid;
	cCamera*		m_pCamera;
	cPlayer*		m_pPlayer;

	std::map < DWORD, std::vector<cObject*> > m_mapObject;

public:
	cInGameScene();
	virtual ~cInGameScene();

	virtual void Update();
	virtual void Render();
	virtual void EnterScene();
	virtual void ExitScene();
	virtual void ChangeScene(cIScene* _pNextScene);
};
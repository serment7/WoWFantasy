#pragma once
#include "cIScene.h"

class cGameObject;

class cInGameScene : public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;

	//std::map < DWORD, std::vector<cObject*> > m_mapObject;
	std::vector<cGameObject*>  m_vecObject;

	D3DLIGHT9		m_light;

public:
	cInGameScene();
	virtual ~cInGameScene();

	virtual void Update();
	virtual void Render();
	virtual void ExitScene();
};
#pragma once
#include "cIScene.h"

class cObject;
class cIScript;

class cInGameScene :
	public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;

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
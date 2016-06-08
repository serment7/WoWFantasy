
#pragma once
#include "cIScene.h"

class cLoadingGameScene  : public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;

public:
	cLoadingGameScene();
	virtual ~cLoadingGameScene();

	virtual void Update();
	virtual void Render();
	virtual void EnterScene();
	virtual void ExitScene();
	virtual void ChangeScene(cIScene* _pNextScene);
	virtual void MessageHandling(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

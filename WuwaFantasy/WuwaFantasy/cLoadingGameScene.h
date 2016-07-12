
#pragma once
#include "cIScene.h"

class cLoadingGameScene  : public cIScene
{
private:
	bool			m_bPaused;
	float			m_fPlayTime;
	LPDIRECT3DTEXTURE9 m_pLoadingImage = nullptr;
	RECT rect;
	D3DXIMAGE_INFO m_image_info;

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

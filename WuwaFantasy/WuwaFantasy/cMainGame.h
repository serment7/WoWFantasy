
#pragma once
#include "cInGameScene.h"
#include "cLoadingGameScene.h"

class cMainGame 
{
private:
	cInGameScene*	mainScene;
	cLoadingGameScene*	loadingScene;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
	void Release();

	void CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

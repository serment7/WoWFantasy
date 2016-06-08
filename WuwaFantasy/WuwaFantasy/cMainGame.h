
#pragma once
#include "cInGameScene.h"
#include "cLoadingGameScene.h"
#include "cSceneManager.h"

class cGrid;
class cCamera;

class cMainGame 
{
private:
	cGrid*									grid;
	cCamera*								camera;

	cSceneManager*	SceneManager;
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

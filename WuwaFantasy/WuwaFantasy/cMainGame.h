
#pragma once
#include "cInGameScene.h"
#include "cSceneManager.h"

class cGrid;
class cCamera;

class cMainGame 
{
private:
	cGrid*									grid;
	cCamera*								camera;

	cSceneManager*	SceneManager;
	cInGameScene* mainScene;
	cInGameScene* mainScene2;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

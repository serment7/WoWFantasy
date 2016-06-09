#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include"cObjectTypeScript.h"


cMainGame::cMainGame()
:	camera(NULL),
	grid(NULL)
{
}

cMainGame::~cMainGame(void)
{

}

void cMainGame::Setup()
{
	float f = D3DXToRadian(180);
	//g_pSoundManager->AddSound("1.wav");

	mainScene = new cInGameScene;
	g_pSceneManager->AddScene("1", mainScene);

	loadingScene = new cLoadingGameScene;
	g_pSceneManager->AddScene("loading", loadingScene);

	g_pSceneManager->ChangeScene("1", "loading");
	g_pSpriteManager;
	cIScript* script = new cObjectTypeScript;
	script->RunScript();
	script->Update();
	script->StopScript();
	SAFE_DELETE(script);

}

void cMainGame::Update()
{
	SceneManager->Update();

}

void cMainGame::Render()
{
	SceneManager->Render();
}

void cMainGame::Release()
{
	g_pSceneManager->Release();
	g_pTextureManager->Destroy();
	g_pSpriteManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void CALLBACK cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SceneManager->GetGameScene()->MessageHandling(hWnd, message, wParam, lParam);
}
#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include"cObjectTypeScript.h"


cMainGame::cMainGame()
{
}

cMainGame::~cMainGame(void)
{

}

void cMainGame::Setup()
{
	float f = D3DXToRadian(180);

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
	g_pSceneManager->Update();

}

void cMainGame::Render()
{
	g_pSceneManager->Render();
}

void cMainGame::Release()
{
	g_pSceneManager->Release();
	g_pTextureManager->Destroy();
	g_pSpriteManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pSoundManager->Release();
}

void CALLBACK cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pSceneManager->GetGameScene()->MessageHandling(hWnd, message, wParam, lParam);
}
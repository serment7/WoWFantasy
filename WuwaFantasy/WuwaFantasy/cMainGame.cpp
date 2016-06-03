#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"


cMainGame::cMainGame()
:	camera(NULL),
	grid(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(camera);
	SAFE_DELETE(grid);

	g_pDeviceManager->Destroy();
	if(SceneManager)
		SceneManager->Release();
	SceneManager = NULL;
}

void cMainGame::Setup()
{
	float f = D3DXToRadian(180);
	SceneManager = new cSceneManager;

	mainScene = new cInGameScene;
	SceneManager->AddScene("1¹ø¾À", mainScene);
	SceneManager->ChangeScene("1¹ø¾À");

	mainScene2 = new cInGameScene;
	SceneManager->AddScene("2¹ø¾À", mainScene2);
	SceneManager->ChangeScene("2¹ø¾À");
	
	/*
	grid = new cGrid;
	grid->Setup();

	camera = new cCamera;
	camera->Setup();
	*/

}

void cMainGame::Update()
{
	SceneManager->Update();
	/*
	g_pTimeManager->Update();

	if(camera) camera->Update(NULL);
	*/
}

void cMainGame::Render()
{
	SceneManager->Render();
	/*
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(56, 121, 110),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	D3DLIGHT9 dir;
	ZeroMemory(&dir, sizeof(D3DLIGHT9));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	dir.Specular = D3DXCOLOR(1, 1, 1, 1) * 0.3f;
	dir.Ambient = D3DXCOLOR(1, 1, 1, 1) * 0.6f;
	dir.Direction = D3DXVECTOR3(0.0f, 10.0f, -5.0f);
	
	g_pD3DDevice->SetLight(0, &dir);
	g_pD3DDevice->LightEnable(0, true);

	if(grid) grid->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	*/
}

void CALLBACK cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if(camera) camera->WndProc(hWnd, message, wParam, lParam);
}
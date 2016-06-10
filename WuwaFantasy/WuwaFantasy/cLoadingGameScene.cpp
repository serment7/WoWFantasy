
#include "stdafx.h"
#include "cLoadingGameScene.h"


cLoadingGameScene::cLoadingGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
{

}

cLoadingGameScene::~cLoadingGameScene()
{
	ExitScene();
}

void cLoadingGameScene::Update()
{
	g_pTimeManager->Update();
	m_fPlayTime += g_pTimeManager->GetDeltaTime();
	if (m_fPlayTime > 2.0f)
	{
		g_pSceneManager->GetGameScene()->ExitScene();
		g_pSceneManager->GetReadyScene()->EnterScene();
		g_pSceneManager->SetGameScene(g_pSceneManager->GetReadyScene());
	}
	
}

void cLoadingGameScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 150, 42),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cLoadingGameScene::EnterScene()
{
}

void cLoadingGameScene::ExitScene()
{
}

void cLoadingGameScene::ChangeScene(cIScene * _pNextScene)
{
}

void cLoadingGameScene::MessageHandling(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	DefWindowProc(hWnd, iMessage, wParam, lParam);
}

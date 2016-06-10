#include "stdafx.h"
#include "cInGameScene.h"
#include "cObject.h"
#include "cHydra.h"
#include "cMap.h"

cInGameScene::cInGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
	, m_pGrid(nullptr)
	, m_pCamera(nullptr)
{
	//g_pSoundManager->Start("1.wav");
}

cInGameScene::~cInGameScene()
{
	//g_pSoundManager->Release();
	g_pObjectManager->Destroy();
}

void cInGameScene::Update()
{
	g_pTimeManager->Update();
	g_pMessageDispatcher->Update();
	g_pGameManager->Update();

	m_pCamera->Update();

	if (m_pPlayer) m_pPlayer->Update();

	if (m_bPaused)
		return;
	
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Update();
	}

}

void cInGameScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);
	g_pD3DDevice->BeginScene();
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->LightEnable(1, true);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Render();
	}

	std::vector<cMap*>& maps = g_pGameManager->GetMap();
	for (int i = 0; i < maps.size(); ++i)
	{
		maps[i]->Render();
	}

	if (m_pGrid) m_pGrid->Render();
	if (m_pPlayer) m_pPlayer->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::EnterScene()
{
	g_pKeyManager->Setup();
	m_pCamera = g_pGameManager->GetCamera();

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pCamera->SetAspect(rc.right / (float)rc.bottom);

	m_pPlayer = new cPlayer;
	m_pPlayer->SetTag(g_pGameManager->FindObjectType("player"));
	g_pObjectManager->AddObject(m_pPlayer);
	g_pGameManager->SetPlayerID(m_pPlayer->GetID());
	m_pPlayer->Setup();
	m_pPlayer->SetVPos(D3DXVECTOR3(256, 0, 256));

	m_pGrid = new cGrid;
	m_pGrid->SetTag(g_pGameManager->FindObjectType("map"));
	g_pObjectManager->AddObject(m_pGrid);
	m_pGrid->Setup();

	cGameObject* monster = new cHydra;
	monster->SetTag(g_pGameManager->FindObjectType("monster"));
	monster->SetVPos(D3DXVECTOR3(256, 0, 256));
	g_pObjectManager->AddObject(monster);
	m_vecObject.push_back(monster);
	

	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Setup();
	}

	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Direction = D3DXVECTOR3(0, 0, 1);
	D3DCOLORVALUE color;
	color.a = color.b = color.g = color.r = 255.0;
	m_light.Ambient = m_light.Diffuse = m_light.Specular = color;
	g_pD3DDevice->SetLight(0, &m_light);
	m_light.Direction = D3DXVECTOR3(0, 0, -1);
	g_pD3DDevice->SetLight(1, &m_light);

	//g_pGameManager->AddMap(new cMap("HeightMap.raw","terrain"));
}

void cInGameScene::ExitScene()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		SAFE_RELEASE(m_vecObject[i]);
	}
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_pGrid);
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pGameManager->Destroy();
	g_pKeyManager->release();
}	

void cInGameScene::ChangeScene(cIScene * _pNextScene)
{
}

void cInGameScene::MessageHandling(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_MOUSEMOVE:
		g_pGameManager->GetCamera()->MessageHandle(hWnd, iMessage, wParam, lParam);
		break;
	}
}
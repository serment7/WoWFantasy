#include "stdafx.h"
#include "cInGameScene.h"
#include "cObject.h"

cInGameScene::cInGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
	, m_pGrid(nullptr)
	, m_pCamera(nullptr)
{
}

cInGameScene::~cInGameScene()
{
	ExitScene();
	g_pObjectManager->Destroy();
}

void cInGameScene::Update()
{
	m_pCamera->Update();
	if (m_pPlayer) m_pPlayer->Update();

	if (m_bPaused)
		return;
	g_pTimeManager->Update();
	for (auto iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		std::vector<cObject*>& vecObject = iter->second;
		for (size_t i = 0; i < vecObject.size(); ++i)
		{
			vecObject[i]->Update();
		}
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
	for (auto iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		if (iter->first == 0)
			return;
		g_pD3DDevice->SetFVF(iter->first);
		std::vector<cObject*>& vecObject = iter->second;
		for (size_t i = 0; i < vecObject.size(); ++i)
		{
			vecObject[i]->Render();
		}
	}
	if (m_pGrid) m_pGrid->Render();
	if (m_pPlayer) m_pPlayer->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::EnterScene()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();
	m_pGrid->SetTag(200);

	//m_pCamera = new cCamera;
	m_pCamera = g_pGameManager->GetCamera();

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pCamera->SetAspect(rc.right / (float)rc.bottom);
	m_pCamera->SetMinFov(1.0f);
	m_pCamera->SetMaxFov(1000.0f);

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup();
	m_pPlayer->SetTag(33);
	g_pGameManager->SetPlayerID(m_pPlayer->GetID());

	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Direction = D3DXVECTOR3(1, 0, 0);
	D3DCOLORVALUE color;
	color.a = color.b = color.g = color.r = 1.0f;
	m_light.Ambient = m_light.Diffuse = m_light.Specular = color;
	g_pD3DDevice->SetLight(0, &m_light);
	
}

void cInGameScene::ExitScene()
{
	for (auto iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		std::vector<cObject*>& vecObject = iter->second;
		for (size_t i = 0; i < vecObject.size(); ++i)
		{
			SAFE_RELEASE(vecObject[i]);
		}
	}
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_pGrid);
	//SAFE_DELETE(m_pCamera);
}	

void cInGameScene::ChangeScene(cIScene * _pNextScene)
{
}

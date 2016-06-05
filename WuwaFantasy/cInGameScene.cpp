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
	if (m_pPlayer) m_pPlayer->Render();
	if (m_pGrid) m_pGrid->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::EnterScene()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCamera = new cCamera;
	m_pCamera->SetAspect(1.0f);
	m_pCamera->SetMinFov(0.0f);
	m_pCamera->SetMaxFov(1.0f);

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup();

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
	SAFE_DELETE(m_pCamera);
}	

void cInGameScene::ChangeScene(cIScene * _pNextScene)
{
}

#include "stdafx.h"
#include "cInGameScene.h"
#include "cObject.h"

cInGameScene::cInGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
{
}

cInGameScene::~cInGameScene()
{
	ExitScene();
	//g_pObjectManager->Destroy();
}

void cInGameScene::Update()
{
	if (m_bPaused)
		return;
	g_pTimeManager->Update();

	std::map< DWORD, std::vector<cObject*> >::iterator iter;
	for (iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
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
	std::map< DWORD, std::vector<cObject*> >::iterator iter;
	for ( iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
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
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::ExitScene()
{
	std::map< DWORD, std::vector<cObject*> >::iterator iter;
	for (iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		std::vector<cObject*>& vecObject = iter->second;
		for (size_t i = 0; i < vecObject.size(); ++i)
		{
			SAFE_RELEASE(vecObject[i]);
		}
	}
}
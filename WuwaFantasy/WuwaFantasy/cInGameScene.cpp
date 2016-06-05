#include "stdafx.h"
#include "cInGameScene.h"
#include "cObject.h"
#include "cMonster.h"

cInGameScene::cInGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
{
	cGameObject* object = new cMonster;
	object->Setup();
	g_pObjectManager->GetInstance();
	//m_mapObject[ST_PNT_VERTEX::FVF].push_back(object);
	m_vecObject.push_back(object);
	D3DCOLORVALUE color;
	color.a = color.b = color.g = color.r = 1.0f;
	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Ambient = m_light.Diffuse = m_light.Specular = color;
	g_pD3DDevice->SetLight(0, &m_light);
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

	/*std::map< DWORD, std::vector<cObject*> >::iterator iter;
	for (iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		std::vector<cObject*>& vecObject = iter->second;
		for (size_t i = 0; i < vecObject.size(); ++i)
		{
			vecObject[i]->Update();
		}
	}*/
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
	/*std::map< DWORD, std::vector<cObject*> >::iterator iter;
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
	}*/
	g_pD3DDevice->LightEnable(0, true);
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::ExitScene()
{
	/*std::map< DWORD, std::vector<cObject*> >::iterator iter;
	for (iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		std::vector<cObject*>& vecObject = iter->second;
		for (size_t i = 0; i < vecObject.size(); ++i)
		{
			SAFE_RELEASE(vecObject[i]);
		}
	}*/
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		SAFE_RELEASE(m_vecObject[i]);
	}
}
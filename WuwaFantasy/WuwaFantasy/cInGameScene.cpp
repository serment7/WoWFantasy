#include "stdafx.h"
#include "cInGameScene.h"
#include "cObject.h"
#include "cMap.h"
#include "cRandom.h"
#include "cCombatNPC.h"
#include "cSkyBox.h"
#include "cHmap.h"
#include "cMapModScript.h"
#include "cInitGameDataScript.h"

cInGameScene::cInGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
	, m_pCamera(nullptr)
	, m_nSoundVolume(0)
{

}

cInGameScene::~cInGameScene()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	g_pObjectManager->Destroy();
	g_pFontManager->Destroy();
}

void cInGameScene::Update()
{
	if (m_bPaused)
		return;

	g_pTimeManager->Update();
	g_pMessageDispatcher->Update();
	g_pGameManager->Update();

	if (m_pSkyBox) m_pSkyBox->Update();
	
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Update();
	}

	g_pUserHUD->Update();

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
		if (g_pGameManager->GetCamera()->IsItCulling(&m_vecObject[i]->GetBoundSphere()))
			m_vecObject[i]->Render();
	}

	std::vector<cHmap*>& maps = g_pGameManager->GetMap();
	for (size_t i = 0; i < maps.size(); ++i)
	{
		maps[i]->Render();
	}

	if (m_pSkyBox) m_pSkyBox->Render();

	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		g_pMessageDispatcher->Dispatch(m_vecObject[i]->GetID(), m_vecObject[i]->GetID(), 0.0f, Msg_Render, NULL);
	}

	g_pUserHUD->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::EnterScene()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);


	g_pGameManager->AddMap(new cHmap);
	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Initialize();

	g_pKeyManager->Setup();
	m_pCamera = g_pGameManager->GetCamera();

	g_pSoundManager->AddSound("Bless","Bless.wav");
	g_pSoundManager->AddSound("hit", "hit1.wav"); 
	g_pSoundManager->AddSound("Blizzard", "Blizzard.wav");
	g_pSoundManager->AddSound("firepad", "firepad.wav");
	g_pSoundManager->AddSound("BattleRoar", "BattleRoar.wav");
	g_pSoundManager->AddSound("Berserk", "Berserk.wav");
	g_pSoundManager->AddSound("Explosion", "Explosion.wav");
	g_pSoundManager->AddSound("Throw", "Throw.wav");
	g_pSoundManager->AddSound("knife", "knife_slash1.wav");
	g_pSoundManager->AddSound("poison", "poison.wav");
	g_pSoundManager->AddSound("bossbattle", "bossbattle.wav");
	g_pSoundManager->AddSound("mapbgm", "mapbgm.wav");
	//g_pSoundManager->Start("mapbgm");

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pCamera->SetAspect(rc.right / (float)rc.bottom);

	cIScript* m_pInitGameData = new cInitGameDataScript(m_vecObject);
	m_pInitGameData->RunScript();
	m_pInitGameData->Update();
	m_pInitGameData->StopScript();
	SAFE_DELETE(m_pInitGameData);

	cIScript* m_pMapMode = new cMapModScript(m_vecObject);
	m_pMapMode->RunScript();
	m_pMapMode->Update();
	m_pMapMode->StopScript();
	SAFE_DELETE(m_pMapMode);

	g_pUserHUD->EnterScene();

	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Setup();
	}
	
	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Direction=D3DXVECTOR3(0, 0, 1);
	D3DCOLORVALUE color;
	color.a = color.b = color.g = color.r = 255.0;
	m_light.Ambient = m_light.Diffuse = m_light.Specular = color;
	g_pD3DDevice->SetLight(0, &m_light);
	m_light.Direction = D3DXVECTOR3(0, 0, -1);
	g_pD3DDevice->SetLight(1, &m_light);

	g_pGameManager->Update();

}

void cInGameScene::ExitScene()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		SAFE_RELEASE(m_vecObject[i]);
	}
	SAFE_DELETE(m_pSkyBox);
	
	g_pUserHUD->ExitScene();
	g_pGameManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pFontManager->Destroy();
	g_pKeyManager->release();
}	

void cInGameScene::ChangeScene(cIScene * _pNextScene)
{
}

void cInGameScene::MessageHandling(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//static D3DXVECTOR3
	static POINT curPos;
	static bool	bRButtonDown=false;
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		if (bRButtonDown)
		{
			
		}
	case WM_MOUSEWHEEL:
		g_pGameManager->MessageHandle(hWnd, iMessage, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		bRButtonDown = false;
	}
}
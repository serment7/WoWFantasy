#include "stdafx.h"
#include "cInGameScene.h"
#include "cObject.h"
#include "cHydra.h"

cInGameScene::cInGameScene()
	: m_bPaused(FALSE)
	, m_fPlayTime(0.0f)
	, m_pGrid(nullptr)
	, m_pCamera(nullptr)
	, m_nSoundVolume(0)
{

}

cInGameScene::~cInGameScene()
{
	g_pObjectManager->Destroy();
}

void cInGameScene::Update()
{
	g_pTimeManager->Update();
	g_pMessageDispatcher->Update();
	g_pGameManager->Update();

	m_pCamera->Update();

	KeyInput();

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
	if (m_pGrid) m_pGrid->Render();
	if (m_pPlayer) m_pPlayer->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cInGameScene::EnterScene()
{
	g_pKeyManager->Setup();
	m_pCamera = g_pGameManager->GetCamera();

	g_pSoundManager->AddSound("1", "1.wav");
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pCamera->SetAspect(rc.right / (float)rc.bottom);

	m_pPlayer = new cPlayer;
	m_pPlayer->SetTag(g_pGameManager->FindObjectType("player"));
	g_pObjectManager->AddObject(m_pPlayer);
	g_pGameManager->SetPlayerID(m_pPlayer->GetID());
	m_pPlayer->Setup();

	m_pGrid = new cGrid;
	
	m_pGrid->SetTag(g_pGameManager->FindObjectType("collider"));
	g_pObjectManager->AddObject(m_pGrid);
	m_pGrid->Setup();
	
	cGameObject* monster = new cHydra;
	monster->SetTag(g_pGameManager->FindObjectType("monster"));
	g_pObjectManager->AddObject(monster);
	m_vecObject.push_back(monster);

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

	g_pSoundManager->Start("1");
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
		g_pGameManager->GetCamera()->MessageHandle(hWnd, iMessage, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		/*bRButtonDown = true;
		g_pGameManager->UpdateCursorPointInGlobal();
		curPos = g_pGameManager->GetCursorPoint();
		if (g_pPickManager->IsPickedTry(m_pGrid->GetTriVertex(), curPos.x, curPos.y))
		{
			Packet_Move* packet = new Packet_Move(g_pPickManager->GetRayPos());
			packet->vDes.y = 0.0f;
			g_pMessageDispatcher->Dispatch(0, g_pGameManager->GetPlayerID(), 0.0f, Msg_Move, packet);
		}*/
		break;
	case WM_RBUTTONUP:
		bRButtonDown = false;
	}
}

enum KeyEnum
{
	SKILL0 = '0'
	, SKILL1
	, SKILL2
	, SKILL3
	, SKILL4
	, SKILL5
	, SKILL6
	, SKILL7
	, SKILL8
	, END
};

void cInGameScene::KeyInput()
{
	const int& playerID = g_pGameManager->GetPlayerID();
	Packet_Skill* packet_skill=nullptr;
	if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
	{
		g_pGameManager->UpdateCursorPointInGlobal();
		const POINT& curPos = g_pGameManager->GetCursorPoint();
		if (g_pPickManager->IsPickedTry(m_pGrid->GetTriVertex(), curPos.x, curPos.y))
		{
			Packet_Move* packet = new Packet_Move(g_pPickManager->GetRayPos());
			packet->vDes.y = 0.0f;
			g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_Move, packet);
		}
	}

	for (int i = SKILL0; i < KeyEnum::END; ++i)
	{
		if (g_pKeyManager->isOnceKeyDown(i))
			g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_MoveAni, NULL);
	}
}


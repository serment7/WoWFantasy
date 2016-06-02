#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cSkinnedMesh.h"
#include "cWeaponSkinnedMesh.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pWeapon(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pWeapon);
	
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Load("hFemale", "hfemale.x");

	m_pWeapon = new cWeaponSkinnedMesh;
	m_pWeapon->Load("Knife_IceCrownRaid", "Knife_IceCrownRaid.X", RIGHT_HAND_WEAPON, m_pSkinnedMesh);

	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);

	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Direction = vDir;

	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if(m_pSkinnedMesh)
	{
		m_pSkinnedMesh->Update();
	}

	if(m_pWeapon)
	{
		m_pWeapon->Update();
	}

	if (m_pCamera)
	{
		//m_pCamera->Update(&(m_pPlayer->GetPosition()));
		m_pCamera->Update(NULL);
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	
	if (m_pGrid)
	{
		//m_pGrid->Render();
	}

	m_pSkinnedMesh->Render(NULL);
	m_pWeapon->Render(NULL);

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	switch (message)
	{
	case WM_KEYDOWN:
		{
			switch (LOWORD(wParam))
			{
			case VK_SPACE:
				{	
					static int n = 0;
					m_pSkinnedMesh->SetAnimationIndexBlend(++n);
					if(n >= 4) n = -1;
				}
				break;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{	
		}
		break;
	case WM_RBUTTONDOWN:
		{
		}
		break;
	}
}

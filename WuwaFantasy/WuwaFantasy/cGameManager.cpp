#include "stdafx.h"
#include "cGameManager.h"
#include "cIScript.h"
#include "cGameObject.h"
#include"cJob.h"
#include"cSkill.h"
#include "cHmap.h"
#include "cWorldCamera.h"
#include "cUIClass.h"

cGameManager::cGameManager()
	: m_nFPS(0)
	, m_nFPSCount(0)
	, m_fCalFPSTime(0.0f)
	, m_pDramaScript(nullptr)
{
	GetClientRect(g_hWnd, &m_rcClientSize);
	m_pWorldCamera = new cWorldCamera;
	D3DXMatrixIdentity(&m_matPort);
}

cGameManager::~cGameManager()
{
	
}

const int & cGameManager::GetFPS()
{
	return m_nFPS;
}

const POINT & cGameManager::GetCursorPoint()
{
	return m_ptCursor;
}

cCamera * cGameManager::GetCamera()
{
	return &m_camera;
}

cCamera * cGameManager::GetDramaCamera()
{
	return &m_dramaCamera;
}

void cGameManager::SetScript(cIScript * _script)
{
#ifdef _DEBUG
	assert(_script && "error : SetScript() received null pointer");
#endif
	SAFE_DELETE(m_pDramaScript);
	m_pDramaScript = _script;
}

const int & cGameManager::GetPlayerID()
{
	return m_nPlayerID;
}

void cGameManager::SetPlayerID(int _nPlayerID)
{
	m_nPlayerID = _nPlayerID;
}

void cGameManager::RegisterObjectType(const std::string & _typename, const size_t & _tagID)
{
	m_mapObjectType[_typename] = _tagID;
}

void cGameManager::RegisterStatus(const std::string & _typename, const ST_STATUS & _status)
{
	m_mapStatus[_typename] = _status;
}

const size_t cGameManager::FindObjectType(const std::string & _typename)
{
	auto iter = m_mapObjectType.find(_typename);
	if (iter != m_mapObjectType.end())
	{
		return iter->second;
	}
	else
	{
		return -1;
	}
}

const ST_STATUS cGameManager::FindStatus(const std::string & _statusname)
{
	if (m_mapStatus.find(_statusname) == m_mapStatus.end())
	{
		ST_STATUS status;
		ZeroMemory(&status, sizeof(status));
		return status;
	}
	return m_mapStatus[_statusname];
}

void cGameManager::AddMap(cHmap * _map)
{
	_map->Setup(512);
	m_vecMap.push_back(_map);
}

std::vector<cHmap*>& cGameManager::GetMap()
{
	return m_vecMap;
}

const RECT & cGameManager::GetClientSize()
{
	return m_rcClientSize;
}

const D3DXMATRIXA16 & cGameManager::GetViewMat()
{
	return m_matView;
}

const D3DXMATRIXA16 & cGameManager::GetProjMat()
{
	return m_matProj;
}

const D3DXMATRIXA16 & cGameManager::GetPortMat()
{
	return m_matPort;
}

void cGameManager::SetRespawnPos(const D3DXVECTOR3 & _pos)
{
	m_vRespawnPos = _pos;
}

const D3DXVECTOR3 & cGameManager::GetRespawnPos()
{
	return m_vRespawnPos;
}

void cGameManager::MessageHandle(const HWND & hWnd, const UINT & iMessage, const WPARAM & wParam, const LPARAM & lParam)
{
	if (m_bUseWorldCamera)
	{
		m_pWorldCamera->MessageHandle(hWnd, iMessage, wParam, lParam);
	}
	else
	{
		m_camera.MessageHandle(hWnd, iMessage, wParam, lParam);
	}
}


void cGameManager::Update()
{
	m_fCalFPSTime += g_pTimeManager->GetDeltaTime();
	++m_nFPSCount;
	
	if (m_fCalFPSTime > 1.0f)
	{
		m_nFPS = m_nFPSCount / (int)m_fCalFPSTime;
		m_nFPSCount = 0;
		m_fCalFPSTime = 0.0f;
	}
	
	g_pGameManager->UpdateClientSize();

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &m_matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);
	g_pD3DDevice->GetViewport(&m_viewport);
	m_matPort._11 = m_viewport.Width*0.5f;
	m_matPort._22 = m_viewport.Height*-0.5f;
	m_matPort._33 = m_viewport.MaxZ - m_viewport.MinZ;
	m_matPort._41 = m_viewport.X + m_matPort._11;
	m_matPort._42 = m_viewport.Y + -m_matPort._22;
	m_matPort._43 = m_viewport.MinZ;
	
	GetClientRect(g_hWnd, &m_rcClientSize);
	
	if (g_pKeyManager->isOnceKeyDown('P'))
	{
		if (m_bUseWorldCamera)
		{
			m_bUseWorldCamera = false;
		}
		else
		{
			m_bUseWorldCamera = true;
			RECT rc;
			GetClientRect(g_hWnd, &rc);
			m_pWorldCamera->SetAspect(rc.right / (float)rc.bottom);
			m_pWorldCamera->SetEye(m_camera.GetEye());
			m_pWorldCamera->SetLookAt(m_camera.GetLookAt());
			m_pWorldCamera->SetDistance(m_camera.GetDistance());
			m_pWorldCamera->SetAngleX(m_camera.GetAngleX());
			m_pWorldCamera->SetAngleY(m_camera.GetAngleY());
		}
	}

	if (m_pDramaScript && m_pDramaScript->IsRun())
	{
		m_dramaCamera.SetAspect(m_rcClientSize.right / (float)m_rcClientSize.bottom);
		m_dramaCamera.Update();
	}
	else
	{
		if (m_bUseWorldCamera)
		{
			m_camera.SetAspect(m_rcClientSize.right / (float)m_rcClientSize.bottom);
			m_pWorldCamera->Update();
		}
		else
		{
			m_camera.SetAspect(m_rcClientSize.right / (float)m_rcClientSize.bottom);
			D3DXVECTOR3 playerPos = g_pObjectManager->FindObjectByID(g_pGameManager->GetPlayerID())->GetVPos();
			m_camera.SetEye(playerPos);
			m_camera.SetLookAt(playerPos);
			m_camera.Update();
		}
	}

	for (size_t i = 0; i < m_vecMap.size(); ++i)
	{
		m_vecMap[i]->FrustumCallingUpdate();
	}
	
}

void cGameManager::UpdateClientSize()
{
	GetClientRect(g_hWnd, &m_rcClientSize);
}

void cGameManager::UpdateCursorPointInGlobal()
{
	GetCursorPos(&m_ptCursor);
	ScreenToClient(g_hWnd, &m_ptCursor);
}

void cGameManager::UpdateCursorPointByWindow(const HWND & _targetWindow)
{
	GetCursorPos(&m_ptCursor);
	ScreenToClient(_targetWindow, &m_ptCursor);
}

void cGameManager::Destroy()
{
	for (size_t i = 0; i < m_vecMap.size(); ++i)
	{
		SAFE_RELEASE(m_vecMap[i]);
	}
	m_vecMap.clear();
}

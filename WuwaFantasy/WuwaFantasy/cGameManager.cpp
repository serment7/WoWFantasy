#include "stdafx.h"
#include "cGameManager.h"
#include "cIScript.h"

cGameManager::cGameManager()
	: m_nFPS(0)
	, m_nFPSCount(0)
	, m_fCalFPSTime(0.0f)
	, m_pScript(nullptr)
{
	GetClientRect(g_hWnd, &m_rcClientSize);
}

cGameManager::~cGameManager()
{
}

const int & cGameManager::GetFPS()
{
	return m_nFPS;
}

cCamera * cGameManager::GetCamera()
{
	return &m_camera;
}

cCamera * cGameManager::GetDramaCamera()
{
	return &m_dramaCamera;
}

void cGameManager::SetScrpit(cIScript * _script)
{
#ifdef _DEBUG
	assert(_script && "error : SetScript() received null pointer");
#endif
	m_pScript = _script;
}

const int & cGameManager::GetPlayerID()
{
	return m_nPlayerID;
}

void cGameManager::SetPlayerID(int _nPlayerID)
{
	m_nPlayerID = _nPlayerID;
}

void cGameManager::Update()
{
	m_fCalFPSTime += g_pTimeManager->GetDeltaTime();
	++m_nFPSCount;

	if (m_pScript && m_pScript->IsRun())
		m_dramaCamera.Update();
	else
		m_camera.Update();
}

void cGameManager::UpdateClientSize()
{
	GetClientRect(g_hWnd, &m_rcClientSize);
}

void cGameManager::UpdateCursorPointInGlobal()
{
	GetCursorPos(&m_ptCursor);
	ClientToScreen(g_hWnd, &m_ptCursor);
}

void cGameManager::UpdateCursorPointByWindow(const HWND & _targetWindow)
{
	GetCursorPos(&m_ptCursor);
	ClientToScreen(_targetWindow, &m_ptCursor);
}

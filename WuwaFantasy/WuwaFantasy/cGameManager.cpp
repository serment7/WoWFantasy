#include "stdafx.h"
#include "cGameManager.h"


cGameManager::cGameManager()
	: m_nFPS(0)
	, m_nFPSCount(0)
	, m_fCalFPSTime(0.0f)
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

void cGameManager::Update()
{
	m_fCalFPSTime += g_pTimeManager->GetDeltaTime();
	++m_nFPSCount;
	m_camera.Update();
}

void cGameManager::UpdateClientSize()
{
	GetClientRect(g_hWnd, &m_rcClientSize);
}

void cGameManager::UpdateCursorPoint()
{
}

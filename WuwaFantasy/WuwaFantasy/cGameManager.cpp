#include "stdafx.h"
#include "cGameManager.h"
#include "cIScript.h"
#include "cGameObject.h"
#include"cJob.h"
#include"cSkill.h"

cGameManager::cGameManager()
	: m_nFPS(0)
	, m_nFPSCount(0)
	, m_fCalFPSTime(0.0f)
	, m_pDramaScript(nullptr)
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
	m_mapObjectType.insert(std::pair<std::string, size_t>(_typename, _tagID));
}

void cGameManager::RegisterSkill(cSkill* _skill)
{
	m_mapSkill.insert(std::pair<std::string, cSkill*>(_skill->GetSkillName(), _skill));
}

void cGameManager::RegisterJob(cJob* _job)
{
	m_mapJob.insert(std::pair<std::string, cJob*>(std::string(_job->GetName()), _job));
}

void cGameManager::Update()
{
	m_fCalFPSTime += g_pTimeManager->GetDeltaTime();
	++m_nFPSCount;

	if (m_pDramaScript && m_pDramaScript->IsRun())
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

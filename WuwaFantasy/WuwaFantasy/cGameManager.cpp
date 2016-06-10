#include "stdafx.h"
#include "cGameManager.h"
#include "cIScript.h"
#include "cGameObject.h"
#include"cJob.h"
#include"cSkill.h"
#include "cMap.h"

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
	//m_mapSkill.insert(_skill.GetSkillName(), _skill);
}

void cGameManager::RegisterJob(cJob* _job)
{
	m_mapJob.insert(std::pair<std::string, cJob*>(_job->GetName(), _job));
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

const cSkill* cGameManager::FindSkill(const std::string & _typename)
{
	auto iter = m_mapSkill.find(_typename);
	if (iter != m_mapSkill.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

const cJob* cGameManager::FindJob(const std::string & _typename)
{
	auto iter = m_mapJob.find(_typename);
	if (iter != m_mapJob.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

void cGameManager::AddMap(cMap * _map)
{
	m_vecMap.push_back(_map);
}

std::vector<cMap*>& cGameManager::GetMap()
{
	return m_vecMap;
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
	
	//UpdateClientSize();
	GetClientRect(g_hWnd, &m_rcClientSize);
	m_camera.SetAspect(m_rcClientSize.right / (float)m_rcClientSize.bottom);

	if (m_pDramaScript && m_pDramaScript->IsRun())
		m_dramaCamera.Update();
	else
	{
		D3DXVECTOR3 playerPos = g_pObjectManager->FindObjectByID(g_pGameManager->GetPlayerID())->GetVPos();
		m_camera.SetEye(playerPos);
		m_camera.SetLookAt(playerPos);
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
	for (int i = 0; i < m_vecMap.size(); ++i)
	{
		SAFE_DELETE(m_vecMap[i]);
	}
}

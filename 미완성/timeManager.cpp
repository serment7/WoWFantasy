
#include "stdafx.h"
#include "timeManager.h"

cTimeManager::cTimeManager(void)
{
	m_dwLastUpdateTime = m_dwStartTime = GetTickCount();
}

cTimeManager::~cTimeManager(void)
{
}

void cTimeManager::Update()
{
	DWORD dwCurrUpdateTime = GetTickCount();
	m_dwDeltaTime = dwCurrUpdateTime - m_dwLastUpdateTime;
	m_dwLastUpdateTime = dwCurrUpdateTime;
	m_dwCountTime += m_dwDeltaTime;
}

float cTimeManager::GetDeltaTime()
{
	return (float)m_dwDeltaTime / 1000.f;
}

float cTimeManager::GetCountTime()
{
	return (float)m_dwCountTime / 1000.f;
}
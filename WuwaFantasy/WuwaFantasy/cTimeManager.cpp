#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager::cTimeManager()
	: fDeltaTime(0.0f)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeStart);
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Update()
{
	QueryPerformanceCounter(&timeEnd);
	fDeltaTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;
	timeStart = timeEnd;
	dwCurrentTime = GetTickCount();
}

const float& cTimeManager::GetDeltaTime()
{
	return fDeltaTime;
}

const DWORD & cTimeManager::GetCurTime()
{
	return dwCurrentTime;
}

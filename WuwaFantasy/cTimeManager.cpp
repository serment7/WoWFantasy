#include "stdafx.h"
#include "cTimeManager.h"

#pragma comment(lib,"Winmm.lib")

//#include <Mmsystem.h>

const float FRAME_RATE = 60.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations

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
}

const float& cTimeManager::GetDeltaTime()
{
	return fDeltaTime;
}
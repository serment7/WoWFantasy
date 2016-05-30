#include "stdafx.h"
#include "cRandom.h"
#include <ctime>

cRandom::cRandom()
{
}

cRandom::~cRandom()
{
}

void cRandom::SRand()
{
	srand((unsigned int)time(nullptr));
}

const int cRandom::GetInteger(int max, int min)
{
	return min + (rand() % (max - min + 1));
}

const float cRandom::GetFloat(float max, float min)
{
	return min + (rand() / (float)RAND_MAX) * (max - min);
}

void cRandom::GetVector(OUT D3DXVECTOR3 & out, const D3DXVECTOR3 & max, const D3DXVECTOR3 & min)
{
	out.x = GetFloat(max.x, min.x);
	out.y = GetFloat(max.y, min.y);
	out.z = GetFloat(max.z, min.z);
}

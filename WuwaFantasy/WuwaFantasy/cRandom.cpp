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

const int cRandom::GetInteger(const int& max, const int& min)
{
	return min + (rand() % (max - min + 1));
}

const float cRandom::GetFloat(const float& max, const float& min)
{
	return min + (rand() / (float)RAND_MAX) * (max - min);
}

void cRandom::GetVector(OUT D3DXVECTOR3 & out, const D3DXVECTOR3 & max, const D3DXVECTOR3 & min)
{
	out.x = GetFloat(max.x, min.x);
	out.y = GetFloat(max.y, min.y);
	out.z = GetFloat(max.z, min.z);
}

void cRandom::GetVectorInCircle(OUT D3DXVECTOR3 & out, const float & _radius)
{
	out.x = cosf(cRandom::GetFloat(D3DX_PI * 2, 0.0f))*cRandom::GetFloat(_radius, 0.0f);
	out.z = cosf(cRandom::GetFloat(D3DX_PI * 2, 0.0f))*cRandom::GetFloat(_radius, 0.0f);
}

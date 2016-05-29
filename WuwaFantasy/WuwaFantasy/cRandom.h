#pragma once
class cRandom
{
public:
	cRandom();
	~cRandom();

	static void SRand();

	static const int& GetInteger(int max, int min);

	static const float& GetFloat(float max, float min);

	static void GetVector(OUT D3DXVECTOR3& out,const D3DXVECTOR3& max,const D3DXVECTOR3& min);
};


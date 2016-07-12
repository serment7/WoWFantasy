#pragma once
class cRandom
{
public:
	cRandom();
	~cRandom();

	static void SRand();

	static const int GetInteger(const int& max, const int& min);

	static const float GetFloat(const float& max, const float& min);

	static void GetVector(OUT D3DXVECTOR3& out,const D3DXVECTOR3& max,const D3DXVECTOR3& min);

	static void GetVectorInCircle(OUT D3DXVECTOR3& out, const float& _radius);
};


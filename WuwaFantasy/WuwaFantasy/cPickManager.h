#pragma once
#include "cRay.h"

class cPickManager
{
private:
	cRay m_nRay;
	D3DXVECTOR3 m_vPos;
	int m_nCurrentMousePointX;
	int m_nCurrentMousePointY;

public:
	cPickManager();
	~cPickManager();
	//Once
	bool IsPickedTry(ST_PNT_VERTEX vec1, ST_PNT_VERTEX vec2, ST_PNT_VERTEX vec3, const int& x, const int& y);
	bool IsPickedSphere(BoundingSphere sphere, const int& x, const int& y);

	//Several
	bool IsPickedTry(std::vector<ST_PNT_VERTEX> vec, const int& x, const int& y);
	bool IsPickedSphere(std::vector<BoundingSphere> vec, const int& x, const int& y);

	//getter, setter
	POINT GetCurrentMousePoint()
	{
		POINT pt;
		pt.x = m_nCurrentMousePointX;
		pt.y = m_nCurrentMousePointY;

		return pt;
	}

	int GetCurrentMousePointX() { return m_nCurrentMousePointX; }
	int GetCurrentMousePointY() { return m_nCurrentMousePointY; }
	cRay GetRay() { return m_nRay; }
	D3DXVECTOR3 GetRayPos() { return m_vPos; }



};


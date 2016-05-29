#pragma once
class cRay
{
private:
	D3DXVECTOR3			m_vOrg;
	D3DXVECTOR3			m_vDir;

public:
	cRay(void);
	~cRay(void);

	bool IsPicked(const BoundingSphere& _sphere);
	void RayAtViewSpace(const int& nScreenX, const int& nScreenY);
	void RayAtWorldSpace(const int& nScreenX, const int&nScreenY);
};
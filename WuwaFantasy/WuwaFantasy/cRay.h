#pragma once
class cRay
{
private:
	D3DXVECTOR3			m_vOrg;
	D3DXVECTOR3			m_vDir;

public:
	cRay(void);
	~cRay(void);

	void SetOrigin(const D3DXVECTOR3& _vec);
	void SetOrigin(const float& _x, const float& _y, const float& _z);
	void SetDirection(const D3DXVECTOR3& _vec);
	void SetDirection(const float& _x, const float& _y, const float& _z);
	const D3DXVECTOR3& GetOrigin();
	const D3DXVECTOR3& GetDirection();

	bool IsPicked(const BoundingSphere& pSphere);
	static cRay RayAtViewSpace(const int& nScreenX, const int& nScreenY);
	static cRay RayAtWorldSpace(const int& nScreenX, const int& nScreenY);
};
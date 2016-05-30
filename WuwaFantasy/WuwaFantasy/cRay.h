#pragma once
class cRay
{
protected:
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vOrg, Origin);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDir, Direction);

public:
	cRay(void);
	~cRay(void);

	bool IsPicked(BoundingSphere* pSphere);
	static cRay RayAtViewSpace(int nScreenX, int nScreenY);
	static cRay RayAtWorldSpace(int nScreenX, int nScreenY);
};
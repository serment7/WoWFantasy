#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	: m_vOrg(0, 0, 0)
	, m_vDir(0, 0, 1)
{
}

cRay::~cRay()
{
}

bool cRay::IsPicked(const BoundingSphere& pSphere)
{
	D3DXVECTOR3 vLocalOrg = m_vOrg - pSphere.vCenter;
	float qq = D3DXVec3Dot(&vLocalOrg, &vLocalOrg);
	float vv = D3DXVec3Dot(&m_vDir, &m_vDir);
	float qv = D3DXVec3Dot(&vLocalOrg, &m_vDir);
	float rr = pSphere.fRadius * pSphere.fRadius;

	return qv * qv - vv * (qq - rr) >= 0;
}

void cRay::RayAtViewSpace(const int & nScreenX, const int & nScreenY)
{
	D3DVIEWPORT9 vp;
	D3DXMATRIXA16 matProj;

	g_pD3DDevice->GetViewport(&vp);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	m_vOrg = D3DXVECTOR3(0, 0, 0);
	m_vDir.x = (((2.f * nScreenX) / vp.Width) - 1.0f) / matProj._11;
	m_vDir.y = (((-2.f * nScreenY) / vp.Height) + 1.0f) / matProj._22;
	m_vDir.z = 1.0f;
}

void cRay::RayAtWorldSpace(const int & nScreenX, const int & nScreenY)
{
	RayAtWorldSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);
	D3DXVec3TransformCoord(&m_vOrg, &m_vOrg, &matInvView);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matInvView);
}

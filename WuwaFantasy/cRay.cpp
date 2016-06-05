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

void cRay::SetOrigin(const D3DXVECTOR3 & _vOrg)
{
	m_vOrg = _vOrg;
}

void cRay::SetOrigin(const float & _x, const float & _y, const float & _z)
{
	SetOrigin(D3DXVECTOR3(_x, _y, _z));
}

void cRay::SetDirection(const D3DXVECTOR3 & _vDir)
{
	m_vDir = _vDir;
}

void cRay::SetDirection(const float & _x, const float & _y, const float & _z)
{
	SetDirection(D3DXVECTOR3(_x, _y, _z));
}

const D3DXVECTOR3 & cRay::GetOrigin()
{
	return m_vOrg;
}

const D3DXVECTOR3 & cRay::GetDirection()
{
	return m_vDir;
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

cRay cRay::RayAtViewSpace(const int & nScreenX, const int & nScreenY)
{
	D3DVIEWPORT9 vp;
	D3DXMATRIXA16 matProj;

	g_pD3DDevice->GetViewport(&vp);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;
	r.m_vDir.x = (((2.f * nScreenX) / vp.Width) - 1.0f) / matProj._11;
	r.m_vDir.y = (((-2.f * nScreenY) / vp.Height) + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	return r;
}

cRay cRay::RayAtWorldSpace(const int & nScreenX, const int & nScreenY)
{
	cRay r = cRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);
	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvView);

	return r;
}

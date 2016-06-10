#include "stdafx.h"
#include "cFrustumCalling.h"


cFrustumCalling::cFrustumCalling()
{
}


cFrustumCalling::~cFrustumCalling()
{
}

void cFrustumCalling::Setup()
{
	m_vecFrustum.clear();
	m_vecFrustum.resize(8);

	m_vecFrustum.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecFrustum.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecFrustum.push_back(D3DXVECTOR3( 1, -1, 1));
	m_vecFrustum.push_back(D3DXVECTOR3( 1, -1, 0));
	m_vecFrustum.push_back(D3DXVECTOR3(-1,  1, 0));
	m_vecFrustum.push_back(D3DXVECTOR3(-1,  1, 1));
	m_vecFrustum.push_back(D3DXVECTOR3( 1,  1, 1));
	m_vecFrustum.push_back(D3DXVECTOR3( 1,  1, 0));

	m_vecIndex.clear();
	m_vecIndex.resize(6);
}

void cFrustumCalling::Update()
{
	D3DXMATRIXA16 projection, view;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &projection);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);

	std::vector<D3DXVECTOR3> frustum(8);
	for (size_t i = 0; i < 8; i++)
	{
		D3DXVec3Unproject(
			&frustum[i],
			&m_vecFrustum[i],
			nullptr,
			&projection,
			&view,
			nullptr
		);
	}

	D3DXPlaneFromPoints(&m_vecIndex[0],
		&frustum[0], &frustum[3], &frustum[2]);
	D3DXPlaneFromPoints(&m_vecIndex[1],
		&frustum[7], &frustum[6], &frustum[2]);
	D3DXPlaneFromPoints(&m_vecIndex[2],
		&frustum[6], &frustum[5], &frustum[1]);
	D3DXPlaneFromPoints(&m_vecIndex[3],
		&frustum[5], &frustum[4], &frustum[0]);
	D3DXPlaneFromPoints(&m_vecIndex[4],
		&frustum[4], &frustum[7], &frustum[3]);
	D3DXPlaneFromPoints(&m_vecIndex[5],
		&frustum[5], &frustum[6], &frustum[7]);
	/*
	for (int i = 0; i < m_vecIndex.size(); ++i)
	{
		D3DXPlaneScale(&m_vecIndex[i], &m_vecIndex[i], 0.5f);
	}*/
}

void cFrustumCalling::Render()
{
}

BOOL cFrustumCalling::IsitCulling(BoundingSphere* bs)
{
	for (size_t i = 0; i < m_vecIndex.size(); ++i)
	{
		if (D3DXPlaneDotCoord(&m_vecIndex[i], &bs->vCenter) > bs->fRadius)
		{
			return false;
		}
	}

	return true;
}

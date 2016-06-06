#include "stdafx.h"
#include "cPickManager.h"


cPickManager::cPickManager()
{
}


cPickManager::~cPickManager()
{
}

bool cPickManager::IsPickedTry(ST_PNT_VERTEX vec1, 
								ST_PNT_VERTEX vec2, 
								ST_PNT_VERTEX vec3, 
								const int & x, 
								const int & y)
{
	m_nRay = cRay::RayAtWorldSpace(x, y);
	float u, v, f;
		
	if (D3DXIntersectTri(
		&vec1.p,
		&vec2.p,
		&vec3.p,
		&m_nRay.GetOrigin(),
		&m_nRay.GetDirection(),
		&u, &v, &f))
	{
		m_vPos = m_nRay.GetOrigin() + m_nRay.GetDirection() * f;
		return true;
	}
	return false;
}

bool cPickManager::IsPickedSphere(BoundingSphere sphere, const int & x, const int & y)
{
	m_nRay = cRay::RayAtWorldSpace(x, y);
	if (m_nRay.IsPicked(sphere))
	{
		return true;
	}
	return false;
}

bool cPickManager::IsPickedTry(std::vector<ST_PNT_VERTEX> vec, const int & x, const int & y)
{
	m_nRay = cRay::RayAtWorldSpace(x, y);
	float u, v, f;

	for (size_t i = 0; i < vec.size(); i+=3)
	{
		if(D3DXIntersectTri(
			&vec[i].p,
			&vec[i + 1].p,
			&vec[i + 2].p,
			&m_nRay.GetOrigin(),
			&m_nRay.GetDirection(),
			&u, &v, &f))
		{
			m_vPos = m_nRay.GetOrigin() + m_nRay.GetDirection() * f;
			return true;
		}
	}

	return false;
}

bool cPickManager::IsPickedSphere(std::vector<BoundingSphere> vec, const int & x, const int & y)
{
	m_nRay = cRay::RayAtWorldSpace(x, y);
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (m_nRay.IsPicked(vec[i]))
		{
			return true;
		}
	}
	return false;
}

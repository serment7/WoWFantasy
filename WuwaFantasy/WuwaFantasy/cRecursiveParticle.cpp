#include "stdafx.h"
#include "cRecursiveParticle.h"


cRecursiveParticle::cRecursiveParticle(const D3DXVECTOR3& _vCenter,
	const float& _fRadius,
	const float _fOnceRecursiveTime,
	const float _fStartAngle,
	const float _fLifeTime,
	const DWORD& _color)
{
	m_vCenter = _vCenter;
	m_fRadius = _fRadius;
	m_fOnceRecursiveTime = _fOnceRecursiveTime;
	m_fStartAngle = _fStartAngle;
	SetLifeTime(_fLifeTime);
	SetColor(_color);
	SetRecycle(true);
	SetLive(true);
	m_vOffset = m_vCenter + D3DXVECTOR3(0, 0, _fRadius);
}


cRecursiveParticle::~cRecursiveParticle()
{
}

void cRecursiveParticle::Update(const float & _delta)
{
	cParticle::Update(_delta);
	m_fRecursivePassedTime += _delta;
	if (IsLive())
	{
		if (GetAge() > GetLifeTime())
			SetLive(false);

		float t = m_fRecursivePassedTime / m_fOnceRecursiveTime;
		float angle = t * 360+ m_fStartAngle;
		if (angle < 0.0f)
			angle += 360.0f;
		else if (angle > 360.0f)
			angle -= 360.0f;

		D3DXMATRIXA16 angleMat;
		D3DXMatrixRotationY(&angleMat,D3DXToRadian(angle));
		
		D3DXVECTOR3 newPos;
		D3DXVec3TransformCoord(&newPos,&m_vOffset,&angleMat);
		SetPos(newPos);
	}
}

void cRecursiveParticle::Reset()
{
	cParticle::Reset();
	SetLive(true);
	m_fRecursivePassedTime = 0.0f;
}

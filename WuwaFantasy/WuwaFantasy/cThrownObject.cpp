#include "stdafx.h"
#include "cThrownObject.h"
#include "cGameObject.h"
#include "cRandom.h"

cThrownObject::cThrownObject(cGameObject * _pOwner, cGameObject * _pTarget, const float & _speed, cParticleDelgate * _delegate)
{
	m_pOwner = _pOwner;
	m_pTarget = _pTarget;
	m_vFrom=_pOwner->GetVPos();
	m_vTo = _pTarget->GetVPos();
	SetPos(m_vFrom);
	
	SetDir(m_vTo - m_vFrom);
	SetSpeed(_speed);
	m_pDelegate = _delegate;
	SetLifeTime((D3DXVec3Length(&(m_vTo - m_vFrom)) + 0.001f) / _speed);
	SetLive(true);
	SetRecycle(false);
	SetSize(5.0f);
	SetColor(D3DCOLOR_XRGB(255, 255, 255));
}

cThrownObject::cThrownObject(const float& _radius , const float& _startHeight, const float& _height, const float& _lifetime, bool _bRand, const DWORD& _color)
{
	m_fRadius = _radius;
	m_fHeight = _height;
	cRandom::GetVectorInCircle(m_vFrom, m_fRadius);
	m_vFrom.y = _startHeight;
	m_vTo = m_vFrom + D3DXVECTOR3(0, m_fHeight, 0);
	SetLifeTime(_lifetime);
	SetRecycle(true);
	SetColor(_color);
	SetShow(false);
	if (_bRand)
	{
		SetAge(cRandom::GetFloat(_lifetime,0.0f));
	}
}

cThrownObject::~cThrownObject()
{
}

void cThrownObject::Update(const float & _delta)
{
	cParticle::Update(_delta);
	if (!IsLive())
	{
		return;
	}
	
	if (GetAge() > GetLifeTime())
	{
		SetPos(m_vTo);
		if(m_pDelegate)
			m_pDelegate->OnParticleDelegate(this);
		SetLive(false);
	}
	else
	{
		float t = GetAge() / GetLifeTime();
		D3DXVECTOR3 velocity = (1.0f - t) * m_vFrom + t * m_vTo;
		SetPos(velocity);
	}
}

void cThrownObject::Reset()
{
	cParticle::Reset();
	cRandom::GetVectorInCircle(m_vFrom, m_fRadius);
	m_vTo = m_vFrom+D3DXVECTOR3(0,m_fHeight,0);
	SetShow(true);
}

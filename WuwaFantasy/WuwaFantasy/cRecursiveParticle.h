#pragma once
#include "cParticle.h"
class cRecursiveParticle :
	public cParticle
{
private:
	D3DXVECTOR3				m_vCenter;
	float					m_fRadius=0.0f;
	float					m_fStartAngle = 0.0f;
	float					m_fOnceRecursiveTime = 0.0f;
	float					m_fRecursivePassedTime = 0.0f;
	D3DXVECTOR3				m_vOffset;

public:
	cRecursiveParticle(const D3DXVECTOR3& _vCenter,
		const float& _fRadius, 
		const float _fOnceRecursiveTime,
		const float _fStartAngle,
		const float _fLifeTime,
		const DWORD& _color);
	~cRecursiveParticle();

	virtual void		Update(const float& _delta);
	virtual void		Reset();
};


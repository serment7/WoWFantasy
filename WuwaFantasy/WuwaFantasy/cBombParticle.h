#pragma once
#include "cParticle.h"

class cParticleEffect;

class cBombParticle :
	public cParticle
{
private:
	float				m_fStartSize=0.0f;
	float				m_fEndSize = 0.0f;
	float				m_fPassedTime = 0.0f;
	float				m_fTime = 0.0f;
	cParticleEffect*	m_pParticleEffect = nullptr;

public:
	cBombParticle(const D3DXVECTOR3& _vPos, cParticleEffect* _pParticleEffect,const float& _startSize,const float& _endSize, const float& _Time, const DWORD& _color);
	virtual ~cBombParticle();

	virtual void		Update(const float& _delta);
};


#include "stdafx.h"
#include "cBombParticle.h"
#include "cParticleEffect.h"

cBombParticle::cBombParticle(const D3DXVECTOR3 & _vPos, cParticleEffect* _pParticleEffect,const float & _startSize, const float & _endSize, const float & _Time, const DWORD& _color)
	:m_pParticleEffect(_pParticleEffect),m_fStartSize(_startSize),m_fEndSize(_endSize),m_fTime(_Time)
{
	SetPos(_vPos);
	SetRecycle(false);
	SetLifeTime(_Time);
	m_fTime = _Time;
	SetColor(_color);
	SetLive(true);
}

cBombParticle::~cBombParticle()
{
}

void cBombParticle::Update(const float & _delta)
{
	cParticle::Update(_delta);
	m_fPassedTime+= _delta;
	if (IsLive())
	{
		if (GetAge() > GetLifeTime())
		{
			SetLive(false);
			g_pSoundManager->Start("Explosion");
		}
			

		float t = m_fPassedTime / m_fTime;
		float curSize = (1.0f - t) * m_fStartSize + t * m_fEndSize;
		m_pParticleEffect->SetSize(curSize);
	}
}
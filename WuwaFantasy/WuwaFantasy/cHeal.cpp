#include "stdafx.h"
#include "cHeal.h"
#include "cParticleEffect.h"
#include "cStatus.h"
#include "cRandom.h"
#include "cThrownObject.h"
#include "cGameObject.h"

cHeal::cHeal(cGameObject * _pTarget,  const int& _nHealAmount,const float & _fPerHealTime, const float & _HealNum)
{
	SetOwner(_pTarget);
	m_pTargetStatus = &_pTarget->GetStatus();
	m_fPerHealTime = _fPerHealTime;
	m_nHealAmount = _nHealAmount;
	m_pParticleEffect = new cParticleEffect;
	m_pParticleEffect->SetSize(0.2f);
	m_nNumHeal = _HealNum;
	cRandom::SRand();
	float fRadius = GetOwner()->GetBoundSphere().fRadius;
	for (int i = 0; i < 20; ++i)
	{
		m_pParticleEffect->AddParticle(
			new cThrownObject(fRadius*0.5f, 0.0f, fRadius, 1.5f, true, D3DCOLOR_XRGB(125, 255, 125)));
	}
	D3DXMatrixIdentity(&m_matWorld);
}

cHeal::~cHeal()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cHeal::Update(const float & _delta, bool & _lifeTime)
{
	m_fPassedTime += _delta;

	if (m_pParticleEffect)
	{
		m_vecOwner = GetOwner()->GetVPos();
		D3DXMatrixTranslation(&m_matWorld,m_vecOwner.x,m_vecOwner.y,m_vecOwner.z);
		m_pParticleEffect->SetMatrix(m_matWorld);
		m_pParticleEffect->Update(_delta);
	}
		

	if (0 < m_nNumHeal)
	{
		if (m_fPassedTime > m_fHealTime)
		{
			m_pTargetStatus->IncCurrentHP(m_nHealAmount);
			m_fHealTime += m_fPerHealTime;
			--m_nNumHeal;
		}
		_lifeTime = false;
	}
	else if (m_fPassedTime > m_fHealTime)
	{
		_lifeTime = true;
	}
}

void cHeal::PostRender()
{
	if (m_pParticleEffect)
		m_pParticleEffect->Render();
}

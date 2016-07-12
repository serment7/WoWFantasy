#include "stdafx.h"
#include "cPoison.h"
#include "cGameObject.h"
#include "cParticleEffect.h"
#include "cThrownObject.h"

cPoison::cPoison(cGameObject* _pOwner,const int & _nPerDamage, const float & _fPerHitTime, const float & _fConditionTime)
{
	SetOwner(_pOwner);
	m_nPerDamage = _nPerDamage;
	m_fHitTime = 0;
	m_fPerHitTime = _fPerHitTime;
	m_fConditionTime = _fConditionTime;

	m_skillRange.vCenter = D3DXVECTOR3(0, 0, 0);
	m_skillRange.fRadius = 0.3f;

	m_pParticleEffect = new cParticleEffect;
	m_pParticleEffect->SetSize(0.1f);

	for (int i = 0; i < 50; ++i)
	{
		m_pParticleEffect->AddParticle(
			new cThrownObject(m_skillRange.fRadius, 3.0f, -3.0f, 1.5f, true, D3DCOLOR_XRGB(75, 255, 75)));
	}
}

cPoison::~cPoison()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cPoison::Update(const float & _delta, bool & _lifeTime)
{
	
	m_fPassedTime += _delta;

	if (GetOwner()->GetStatus().GetCurrentHP() < 1)
	{
		_lifeTime = true;
		return;
	}
	if (m_fPassedTime > m_fHitTime)
	{
		m_vPos = GetOwner()->GetVPos();
		D3DXMatrixTranslation(&m_matWorld, m_vPos.x, m_vPos.y, m_vPos.z);
		m_pParticleEffect->SetMatrix(m_matWorld);
		m_pParticleEffect->Update(_delta);

		m_fHitTime += m_fPerHitTime;
		if (GetOwner())
		{
			packet_hit = new Packet_Hit(m_nPerDamage);
			g_pSoundManager->Start("poison");
			g_pMessageDispatcher->Dispatch(0, GetOwner()->GetID(), 0.0f, Msg_Hit, packet_hit);
			packet_hit = nullptr;
		}
		_lifeTime = false;
	}

	if (m_fPassedTime > m_fConditionTime)
	{
		_lifeTime = true;
	}
}

void cPoison::Render()
{
	m_pParticleEffect->Render();
}


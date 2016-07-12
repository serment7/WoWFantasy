#include "stdafx.h"
#include "cFireHand.h"
#include "cGameObject.h"
#include "cParticleEffect.h"
#include "cBombParticle.h"

cFireHand::cFireHand(cGameObject* _pOwner, 
	const float& _distance, 
	const float& _fTiming, 
	const float& _fCastTime)
{
	SetOwner(_pOwner);
	m_ownerID = _pOwner->GetID();
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetDistance(_distance);
	m_fCastTime = _fCastTime;
	m_fEffectTiming = _fTiming;
	SetPath("./Resource/UI/ºÒÁÖ¸Ô");
	SetCoolDownTime(2.0f);
	m_nNecessaryMP = 00;

	m_pParticleEffect = new cParticleEffect;
}

cFireHand::~cFireHand()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cFireHand::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;
	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);
	SetCast(true);
	SetCoolDown(false);
	m_bEffect = false;

	m_pParticleEffect->SetSize(0);
	m_fPassedCastTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	

	g_pMessageDispatcher->Dispatch(m_ownerID,m_ownerID,0.0f,Msg_AttackAni,NULL);

	m_nNecessaryMP = 10;
}

void cFireHand::Update(const float & _delta)
{
	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedCastTime = 0.0f;
	}
	m_pParticleEffect->Update(_delta);


	if (IsCast()&&GetTarget())
	{
		if (GetTarget())
		{
			m_fPassedCastTime += _delta;
			if (m_fPassedCastTime > m_fCastTime)
			{
				SetCast(false);

				g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
			}
			if (!m_bEffect)
			{
				if (m_fPassedCastTime > m_fEffectTiming)
				{
					m_bEffect = true;
					SetCoolDown(true);

					m_pParticleEffect->AddParticle(new cBombParticle(GetTarget()->GetVPos(), m_pParticleEffect, 0.0f, 5.0f, 0.5f, D3DCOLOR_XRGB(255, 255, 125)));
				}
			}
		}
		else
		{
			SetCast(false);
			SetCoolDown(true);
		}
		
	}

	if (IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
			SetCoolDown(false);
	}

}

void cFireHand::Render()
{
	m_pParticleEffect->Render();
}

void cFireHand::Stop()
{
}

bool cFireHand::CanUse()
{
	return cSkill::CanUse() && GetTarget();
}

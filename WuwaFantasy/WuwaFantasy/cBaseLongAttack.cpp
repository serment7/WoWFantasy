#include "stdafx.h"
#include "cBaseLongAttack.h"
#include "cGameObject.h"
#include "cThrownObject.h"
#include "cParticleEffect.h"

cBaseLongAttack::cBaseLongAttack(const float& _distance, const float& _attackTiming,const float& _attackPeriod, const std::string& _throwntexture)
{
	SetDistance(_distance);
	m_pParticleEffect = new cParticleEffect;
	m_pParticleEffect->SetSize(1.0f);
	m_pParticleEffect->SetTexture(PARTICLE_PATH + _throwntexture);
	m_fAttackTiming = _attackTiming;
	m_fAttackPeriod = _attackPeriod;
	m_fCoolDownTime = 1.5f;
}


cBaseLongAttack::~cBaseLongAttack()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cBaseLongAttack::Start()
{
	if (!(GetTarget() && (0 < GetTarget()->GetStatus().GetCurrentHP())))
		return;

	SetCast(true);

	GetOwner()->SetVDir(GetTarget()->GetVPos() - GetOwner()->GetVPos());

	SetEffectValue(GetOwner()->GetStatus().GetAttackDamage());
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_AttackAni, NULL);
}

void cBaseLongAttack::Update(const float & _delta)
{
	if (m_nThrownObject)
	{
		m_pParticleEffect->Update(_delta);
	}

	if (IsCast())
	{
		if (m_fPassedTime > m_fAttackPeriod)
		{
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_AttackEnd, NULL);
			SetCast(false);
			m_bShoot = false;
			SetCoolDown(true);
		}
		else if (!m_bShoot && m_fPassedTime > m_fAttackTiming)
		{
			m_bShoot = true;
			
			++m_nThrownObject;
			packet_hit = new Packet_Hit(GetEffectValue());
			m_pParticleEffect->AddParticle(new cThrownObject(GetOwner(), GetTarget(), 7.0f, this));
		}
		else
		{
			m_fPassedTime += _delta;
		}
	}
	if(IsCoolDown())
	{
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
		{
			SetCoolDown(false);
		}
		else
		{
			m_fCoolDownPassedTime += _delta;
		}
	}
}

void cBaseLongAttack::Render()
{
	if (m_nThrownObject)
	{
		m_pParticleEffect->Render();
	}
}

void cBaseLongAttack::Stop()
{
	SetCast(false);
}

void cBaseLongAttack::OnParticleDelegate(cParticle * _pSender)
{
	--m_nThrownObject;
	packet_hit = new Packet_Hit(GetEffectValue());
	g_pMessageDispatcher->Dispatch(m_entityID, m_targetID, 0.0f, Msg_Hit, packet_hit);
}

bool cBaseLongAttack::CanUse()
{
	return cSkill::CanUse() && GetOwner();
}

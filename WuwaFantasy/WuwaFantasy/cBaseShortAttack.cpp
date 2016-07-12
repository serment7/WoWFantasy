#include "stdafx.h"
#include "cBaseShortAttack.h"
#include "cGameObject.h"

cBaseShortAttack::cBaseShortAttack(cGameObject* _pOwner , const float& _skilldistance, const float& _attackTiming, const float& _attackPeriod)
{
	SetOwner(_pOwner);
	m_pOwnerStatus = &GetOwner()->GetStatus();
	m_ownerID = GetOwner()->GetID();

	SetDistance(_skilldistance);
	m_fAttackTiming = _attackTiming;
	m_fAttackPeriod = _attackPeriod;
	SetCoolDownTime(_attackPeriod);	
}


cBaseShortAttack::~cBaseShortAttack()
{
}

void cBaseShortAttack::Start()
{
	if (!(GetTarget() && (0<GetTarget()->GetStatus().GetCurrentHP())))
		return;

	m_fCoolDownPassedTime = 0.0f;
	m_fPassedTime = 0.0f;
	SetCast(true);
	m_bAttack = false;
	SetEffectValue(GetOwner()->GetStatus().GetAttackDamage());
	
	SetCoolDown(true);
	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackAni, NULL);
}

void cBaseShortAttack::Update(const float & _delta)
{
	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedTime = 0.0f;
	}

	if (IsCast())
	{
		m_fPassedTime += _delta;
		if (m_fPassedTime > m_fAttackPeriod)
		{
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
			SetCast(false);
			m_bAttack = false;
		}
		else if (!m_bAttack && m_fPassedTime > m_fAttackTiming)
		{
			m_bAttack = true;
			packet_hit = new Packet_Hit(GetEffectValue());
			g_pMessageDispatcher->Dispatch(m_ownerID,GetTarget()->GetID(),0.0f,Msg_Hit,packet_hit);
			g_pSoundManager->Start("knife");
		}
	}
	if (IsCoolDown())
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

void cBaseShortAttack::Render()
{
}

void cBaseShortAttack::Stop()
{
	SetCast(false);
}

bool cBaseShortAttack::CanUse()
{
	return cSkill::CanUse() && GetTarget();
}

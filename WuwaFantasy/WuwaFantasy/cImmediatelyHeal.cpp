#include "stdafx.h"
#include "cImmediatelyHeal.h"
#include "cHeal.h"
#include "cGameObject.h"

cImmediatelyHeal::cImmediatelyHeal(cGameObject* _pOwner)
{
	SetSkillType(skilltype::Support);
	SetOwner(_pOwner);
	m_pOwnerStatus = &_pOwner->GetStatus();
	m_ownerID = _pOwner->GetID();
	SetPath("./Resource/UI/Èú");
	SetEffectValue(10);
	SetDistance(5.0f);
	SetCoolDownTime(10.0f);
	m_nNecessaryMP = 10;
}

cImmediatelyHeal::~cImmediatelyHeal()
{
	SAFE_DELETE(packet_condition);
}

void cImmediatelyHeal::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_CastingAni, NULL);
	SetCast(true);
	SetCoolDown(true);
	m_fCoolDownPassedTime = 0.0f;
	m_fPassedCastTime = 0.0f;
}

void cImmediatelyHeal::Update(const float & _delta) 
{
	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedCastTime = 0.0f;
	}

	if (IsCast())
	{
		m_fPassedCastTime += _delta;
		if (m_fPassedCastTime > m_fCastTime)
		{
			SetCast(false);
			packet_condition = new Packet_AddCondition(new cHeal(GetTarget(), GetEffectValue(), 1.0f, 5));
			g_pMessageDispatcher->Dispatch(GetOwner()->GetID(), GetTarget()->GetID(), 0.0f, Msg_AddCondition, packet_condition);
			packet_condition = nullptr;
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_SupportEnd, NULL);
		}
	}

	if (IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
			SetCoolDown(false);
	}
}

void cImmediatelyHeal::Render()
{
}

void cImmediatelyHeal::Stop()
{
	SetCast(false);
	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_SupportEnd, NULL);
}

bool cImmediatelyHeal::CanUse()
{
	return cSkill::CanUse() && GetTarget();
}

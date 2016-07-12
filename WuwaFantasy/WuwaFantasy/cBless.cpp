#include "stdafx.h"
#include "cBless.h"
#include "cGameObject.h"
#include "cIncDef.h"

cBless::cBless(cGameObject* _pOwner, const float& _AniTime)
	:m_fAniTime(_AniTime)
{
	m_ownerID = _pOwner->GetID();
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetDistance(FLT_MAX);
	SetCoolDownTime(20.0f);
	SetPath("./Resource/UI/ÆøÁÖ");
	SetSkillType(skilltype::Support);
	SetEffectValue(5);
	m_nNecessaryMP = 10;
}


cBless::~cBless()
{
}

void cBless::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	m_fPassedTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	SetCast(true);
	SetCoolDown(true);
	g_pMessageDispatcher->Dispatch(0, GetOwner()->GetID(), 0.0f, Msg_BattleRoarAni, NULL);
}

void cBless::Update(const float & _delta)
{
	if (IsCast())
	{
		m_fPassedTime += _delta;
		if (m_fPassedTime > m_fAniTime)
		{
			packet_condition = new Packet_AddCondition(new cIncDef(GetTarget(), GetEffectValue(), 10.0f));
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AddCondition, packet_condition);
			packet_condition = nullptr;

			g_pSoundManager->Start("Bless");

			SetCast(false);
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

void cBless::Render()
{
}

void cBless::Stop()
{
}

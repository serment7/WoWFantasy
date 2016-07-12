#include "stdafx.h"
#include "cBerserk.h"
#include "cIncATK.h"
#include "cGameObject.h"

cBerserk::cBerserk(cGameObject* _pOwner, const float& _AniTime)
	:m_fAniTime(_AniTime)
{
	m_ownerID = _pOwner->GetID();
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetDistance(10.0f);
	SetCoolDownTime(20.0f);
	SetPath("./Resource/UI/ÆøÁÖ");
	SetEffectValue(5);
	m_nNecessaryMP = 15;
}

cBerserk::~cBerserk()
{
}

void cBerserk::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	m_fPassedTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	SetCast(true);
	SetCoolDown(true);
	g_pMessageDispatcher->Dispatch(0,GetOwner()->GetID(),0.0f,Msg_BattleRoarAni,NULL);
	g_pSoundManager->Start("Berserk");
}

void cBerserk::Update(const float & _delta)
{
	if (IsCast())
	{
		m_fPassedTime += _delta;
		if (m_fPassedTime > m_fAniTime)
		{
			packet_condition = new Packet_AddCondition(new cIncATK(GetOwner(), GetEffectValue(), 10.0f));
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AddCondition, packet_condition);
			packet_condition = nullptr;

			SetCast(false);
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
		}
	}

	if (IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
			SetCoolDown(false);
	}
}

void cBerserk::Render()
{
}

void cBerserk::Stop()
{
}

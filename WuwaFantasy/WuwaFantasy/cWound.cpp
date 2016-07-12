#include "stdafx.h"
#include "cWound.h"
#include "cGameObject.h"

cWound::cWound(cGameObject * _pOwner, const float & _distance)
{
	SetOwner(_pOwner);
	m_ownerID = _pOwner->GetID();
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetDistance(_distance);
	SetPath("./Resource/UI/¾ÆÆ÷");
	SetCoolDownTime(15.0f);
	m_nNecessaryMP = 00;

	size_t tagID = _pOwner->GetTag();
	if (tagID == g_pGameManager->FindObjectType("player") || tagID == g_pGameManager->FindObjectType("combatnpc"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("monster"));
	}
	else if (tagID == g_pGameManager->FindObjectType("monster"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("player"));
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
	}

}

cWound::~cWound()
{
}

void cWound::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	SetCast(true);
	SetCoolDown(true);

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	m_fPassedTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;

	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_WoundAni, NULL);

	SetEffectValue(m_pOwnerStatus->GetAttackDamage()*0.8f);
}

void cWound::Update(const float & _delta)
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
		if (m_fPassedTime > m_fSkillTime)
		{
			SetCast(false);
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
		}
		if (m_fPassedTime > m_fAttackTiming)
		{
			float fDistance = 0.0f;
			m_vPos = GetOwner()->GetVPos();
			if (!m_listTargets.empty())
			{
				for (auto iter = m_listTargets.begin(); iter != m_listTargets.end(); ++iter)
				{
					fDistance = D3DXVec3LengthSq(&(m_vPos - (*iter)->GetVPos()));
					if (fDistance < m_fSkillEffectDistance*m_fSkillEffectDistance)
					{
						packet_hit = new Packet_Hit(GetEffectValue());
						g_pMessageDispatcher->Dispatch(GetOwner()->GetID(), (*iter)->GetID(), 0.0f, Msg_AddCondition, packet_hit);
						packet_hit = nullptr;
					}
				}
				m_listTargets.clear();
			}

		}
	}

	if (IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
			SetCoolDown(false);
	}
}

void cWound::Render()
{
}

void cWound::Stop()
{
	SetCast(false);
}

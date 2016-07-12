#include "stdafx.h"
#include "cBattleRoar.h"
#include "cGameObject.h"
#include "cStun.h"

cBattleRoar::cBattleRoar(cGameObject* _pOwner, const float& _fDistance, const float& _fEffectTiming, const float& _fCastPeriod)
{
	SetOwner(_pOwner);
	m_ownerID = _pOwner->GetID();
	SetDistance(_fDistance);
	SetCoolDownTime(10.0f);
	m_pOwnerStatus = &_pOwner->GetStatus();

	m_fEffectTiming = _fEffectTiming;
	m_fCastTime = _fCastPeriod;

	size_t tagID = _pOwner->GetTag();
	if (tagID == g_pGameManager->FindObjectType("player")||tagID==g_pGameManager->FindObjectType("combatnpc"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("monster"));
	}
	else if (tagID == g_pGameManager->FindObjectType("monster"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("player"));
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
	}
}


cBattleRoar::~cBattleRoar()
{
	SAFE_DELETE(packet_condition);
}

void cBattleRoar::Start()
{
	SetCast(true);
	SetCoolDown(true);
	m_fPassedCastTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	m_bEffect = false;

	for (size_t index = 0; index < m_vecTargetTag.size(); ++index)
	{
		std::vector<cGameObject*>& vecTargetByTag = g_pObjectManager->FindObjectByTag(m_vecTargetTag[index]);
		for (size_t targetIndex = 0; targetIndex < vecTargetByTag.size(); ++targetIndex)
		{
			m_listTargets.push_back(vecTargetByTag[targetIndex]);
		}
	}

	g_pMessageDispatcher->Dispatch(m_ownerID,m_ownerID,0.0f,Msg_BattleRoarAni,NULL);
}

void cBattleRoar::Update(const float & _delta)
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
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
		}
		if (!m_bEffect)
		{
			if (m_fPassedCastTime > m_fEffectTiming)
			{
				m_bEffect = true;

				g_pSoundManager->Start("BattleRoar");

				float fDistance = 0.0f;
				m_vPos = GetOwner()->GetVPos();
				if (!m_listTargets.empty())
				{
					for (auto iter = m_listTargets.begin(); iter != m_listTargets.end(); ++iter)
					{
						fDistance = D3DXVec3LengthSq(&(m_vPos - (*iter)->GetVPos()));
						if (fDistance < m_fSkillEffectDistance*m_fSkillEffectDistance)
						{
							packet_condition = new Packet_AddCondition(new cStun(*iter, 4.0f));
							g_pMessageDispatcher->Dispatch(GetOwner()->GetID(), (*iter)->GetID(), 0.0f, Msg_AddCondition, packet_condition);
							packet_condition = nullptr;
						}
					}
					m_listTargets.clear();
				}
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

void cBattleRoar::Render()
{
}

void cBattleRoar::Stop()
{
	SetCast(false);
}

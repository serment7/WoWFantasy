#include "stdafx.h"
#include "cBossMonsterState.h"
#include "cGameObject.h"
#include "cUIObject.h"
#include "cUITextView.h"
#include "cRandom.h"
#include "cSkill.h"

cBossMonsterState::cBossMonsterState(cIState* _pState)
{
	m_pState = _pState;
	ZeroMemory(&m_packet, sizeof(m_packet));
}

cBossMonsterState::~cBossMonsterState()
{
	SAFE_DELETE(m_pState);
	for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapSkill.clear();
}

void cBossMonsterState::EnterState(cGameObject * _entity)
{
	m_entityID = _entity->GetID();

	m_pStatus = &_entity->GetStatus();

	m_vRespawnPos = _entity->GetVPos();

	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("player"));
	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
	m_pState->EnterState(_entity);
	cEntityState::EnterState(_entity);
	m_pNameText->SetTextColor(D3DCOLOR_XRGB(255, 0, 0));
}

void cBossMonsterState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
}

void cBossMonsterState::Execute(cGameObject * _entity)
{
	cEntityState::Execute(_entity);

	m_pState->Execute(_entity);
	m_vPos = _entity->GetVPos();

	float delta = g_pTimeManager->GetDeltaTime();

	if (m_fPassedSkillTime<m_fPerSkill)
		m_fPassedSkillTime += delta;

	for (auto i = m_mapSkill.begin(); i != m_mapSkill.end(); ++i)
	{
		i->second->Update(delta);
	}

	if (!m_bLive)
	{
		m_fRespawnPassedTime += delta;

		if (m_fRespawnPassedTime > m_fRespawnTime)
		{
			m_bLive = true;
			_entity->SetVPos(m_vRespawnPos);
			m_pStatus->SetCurrentHP(m_pStatus->GetMaxHP());
			m_pStatus->SetCurrentMP(m_pStatus->GetMaxMP());
			m_packet.msg_type = Msg_IdleAni;
			m_pState->OnMessage(_entity, m_packet);
			_entity->SetShow(true);
		}
		else if (m_fRespawnPassedTime > m_fDeathMotionTime)
		{
			_entity->SetShow(false);
			g_pSoundManager->Stop("bossbattle");
		}
		return;
	}


	for (size_t i = 0; i < m_vecTargetTag.size(); ++i)
	{
		std::vector<cGameObject*>& target = g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
		for (size_t i = 0; i < target.size(); ++i)
		{
			if (!(0 < target[i]->GetStatus().GetCurrentHP()))
				continue;
			m_pTarget = target[i];
			m_vTargetPos = m_pTarget->GetVPos();
			m_fTargetRange = D3DXVec3LengthSq(&(m_vTargetPos - m_vPos));
			if (m_fTargetRange < m_pStatus->GetSenseRange()*m_pStatus->GetSenseRange())
			{
				m_mapTargetList[m_pTarget->GetID()] = m_pTarget;
			}
		}
	}


	m_fSearchTarget = FLT_MAX;
	m_pTarget = nullptr;

	for (auto iter = m_mapTargetList.begin(); iter != m_mapTargetList.end(); )
	{
		if (0 < iter->second->GetStatus().GetCurrentHP())
		{
			m_fTargetRange = D3DXVec3LengthSq(&(iter->second->GetVPos() - m_vPos));

			if (m_fTargetRange > m_pStatus->GetChaseRange()*m_pStatus->GetChaseRange())
			{
				m_mapTargetList.erase(iter++);
				if (m_mapTargetList.empty())
				{
					packet_move = new Packet_Pos(m_vRespawnPos);
					g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Patrol, packet_move);
				}
				continue;
			}
			else if (m_fTargetRange < m_fSearchTarget)
			{
				m_fSearchTarget = m_fTargetRange;
				m_pTarget = iter->second;
			}
			++iter;
		}
		else
		{
			m_mapTargetList.erase(iter++);
			if (m_mapTargetList.empty())
			{
				packet_move = new Packet_Pos(m_vRespawnPos);
				g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Patrol, packet_move);
			}
		}
	}

	if (m_pTarget)
	{
		m_bCombat = true;
		g_pSoundManager->Start("bossbattle");
	}
	else
	{
		m_bCombat = false;
		g_pSoundManager->Stop("bossbattle");
	}

	if (m_bCombat && m_pTarget)
	{

		if (!m_pCurSkill)
		{
			if (m_fPassedSkillTime > m_fPerSkill)
			{
				for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
				{
					iter->second->SetTarget(m_pTarget);
					if (iter->first != BASE_ATTACK
						&& iter->second->GetSKillType() != skilltype::Support
						&& iter->second->CanUse())
					{
						m_pCurSkill = iter->second;
						m_fPassedSkillTime = 0.0f;
						break;
					}
				}
			}

			m_mapSkill[BASE_ATTACK]->SetTarget(m_pTarget);
			if (!m_pCurSkill && m_mapSkill[BASE_ATTACK]->CanUse())
			{
				m_pCurSkill = m_mapSkill[BASE_ATTACK];
			}
		}
	}

	if (m_bCombat)
	{
		if (m_pCurSkill && m_pCurSkill->CanUse())
		{
			packet_attack = new Packet_Attack(m_pTarget, m_pCurSkill);
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Attack, packet_attack);
		}
	}

}

bool cBossMonsterState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Render:
		if (_entity->IsShow())
			m_pUIRoot->Render(g_pSpriteManager->GetSprite());
		if (m_bLive)
		{
			for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
			{
				iter->second->Render();
			}
		}
		return true;
	case Msg_SetSkill:
		packet_setskill = (Packet_SetSkill*)_packet.info;
		packet_setskill->skill->SetOwner(_entity);
		m_mapSkill.insert(std::pair<char, cSkill*>(packet_setskill->key, packet_setskill->skill));
		SAFE_DELETE(packet_setskill);
		return true;
	case Msg_AddCondition:
		packet_condition = (Packet_AddCondition*)_packet.info;
		_entity->AddCondition(packet_condition->pCondition);
		SAFE_DELETE(packet_condition);
		return true;
	case Msg_Hit:
		if (!m_bLive)
			return true;
		g_pSoundManager->Start("hit");
		packet_hit = (Packet_Hit*)_packet.info;
		m_pStatus->DecCurrentHP(packet_hit->damage - m_pStatus->GetDef());
		if (0 < m_pStatus->GetCurrentHP())
		{
			if (_packet.sender != 0)
			{
				cGameObject* newTarget = g_pObjectManager->FindObjectByID(_packet.sender);
				m_mapTargetList[newTarget->GetID()] = newTarget;
			}
		}
		else
		{
			m_bCombat = false;
			m_mapTargetList.clear();
			m_pTarget = nullptr;
			m_packet.msg_type = Msg_Death;
			m_pState->OnMessage(_entity, m_packet);
			m_bLive = false;
			m_fRespawnPassedTime = 0.0f;
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Standby, NULL);
		}
		return true;
	case Msg_AttackEnd:
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
		m_pCurSkill = nullptr;
		return true;
	default:
		return m_pState->OnMessage(_entity, _packet);
	}
	return false;
}
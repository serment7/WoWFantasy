#include "stdafx.h"
#include "cCombatNPCState.h"
#include "cGameObject.h"
#include "cUITextView.h"
#include "cSkill.h"

cCombatNPCState::cCombatNPCState(cIState* _pState)
{
	m_pState = _pState;
	ZeroMemory(&m_packet, sizeof(m_packet));
	m_packet.msg_type = Msg_IdleAni;
}


cCombatNPCState::~cCombatNPCState()
{
	SAFE_DELETE(m_pState);
	for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapSkill.clear();
}

void cCombatNPCState::EnterState(cGameObject * _entity)
{
	ZeroMemory(&m_packet, sizeof(m_packet));
	m_pStatus = &_entity->GetStatus();
	m_entityID = _entity->GetID();

	m_pState->EnterState(_entity);
	cEntityState::EnterState(_entity);
	m_pNameText->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	m_boundsphere = _entity->GetBoundSphere();
}

void cCombatNPCState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
}

void cCombatNPCState::Execute(cGameObject * _entity)
{
	cEntityState::Execute(_entity);

	m_pState->Execute(_entity);

	m_vCurPos = _entity->GetVPos();
	m_nWeightNum = -1;
	m_nVelocityNum = 0;
	m_vVelocity = D3DXVECTOR3(0, 0, 0);

	const float delta = g_pTimeManager->GetDeltaTime();
	m_fPassedSkillTime += delta;

	if (!m_bLive)
		return;

	if (!m_pCurSkill&&!m_mapNeedHelp.empty())
	{
		for (auto iter = m_mapNeedHelp.begin(); iter != m_mapNeedHelp.end(); ++iter)
		{
			if (m_pParty)
			{
				cStatus* curStatus = &m_pParty->GetStatus();
				cStatus* targetStatus = &iter->second->GetStatus();
				if ((curStatus->GetMaxHP()-curStatus->GetCurrentHP())
					<targetStatus->GetMaxHP()-targetStatus->GetCurrentHP())
				{
					m_pParty = iter->second;
				}
			}
			else
				m_pParty = iter->second;
		}

		for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
		{
			if (iter->second->GetSKillType() != skilltype::Support)
				continue;

			iter->second->SetTarget(m_pParty);
			if (iter->first != BASE_ATTACK
				&& iter->second->CanUse())
			{
				m_pCurSkill = iter->second;
				m_fPassedSkillTime = 0.0f;
				break;
			}
		}

		if (!m_pCurSkill || m_pCurSkill->GetSKillType() != skilltype::Support)
			m_pParty = nullptr;
	}

	if (!m_pParty && m_bCombat && m_pTarget)
	{
		if (0 < m_pTarget->GetStatus().GetCurrentHP())
		{
			if (!m_pCurSkill)
			{
				if (m_fPassedSkillTime > m_fPerSkill)
				{	
					for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
					{
						if (iter->second->GetSKillType() == skilltype::Support)
							continue;
						iter->second->SetTarget(m_pTarget);
						if (iter->first != BASE_ATTACK 
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
		else
		{
			m_bCombat = false;
			m_pTarget = nullptr;
		}
	}
	else if (m_pLeader)
	{
		m_vLeaderPos = m_pLeader->GetVPos();
		m_vLeaderDir = m_pLeader->GetVDir();
		float distance = D3DXVec3LengthSq(&(m_vCurPos - m_vLeaderPos));
		if (distance > KEEP_MAX_DISTANCE*KEEP_MAX_DISTANCE)
		{
			_entity->SetVPos(m_vLeaderPos);
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
		}
		else if (distance > REACTION_DISTANCE*REACTION_DISTANCE)
		{
			m_vLeaderDir = m_pLeader->GetVDir();
			D3DXVECTOR3 vPosDir = m_vCurPos-m_vLeaderPos;
			D3DXVec3Normalize(&m_vLeaderDir, &m_vLeaderDir);
			D3DXVec3Normalize(&vPosDir, &vPosDir);

			if (0.0f>D3DXVec3Dot(&m_vLeaderDir,&vPosDir))
			{
				m_vVelocity += m_vLeaderDir;
				++m_nVelocityNum;
			}
		}
		else if (!m_pCurSkill&&distance < KEEP_MIN_DISTANCE*KEEP_MIN_DISTANCE)
		{
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
		}
	}

	if (m_pCurSkill&&m_pCurSkill->GetSKillType() == skilltype::Support)
		int n = 0;

	if (m_pParty)
	{
		if (m_pCurSkill && m_pCurSkill->CanUse())
		{
			m_mapNeedHelp.erase(m_pParty->GetID());
			packet_attack = new Packet_Attack(m_pParty, m_pCurSkill);
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Attack, packet_attack);
		}
	}
	else if (m_bCombat)
	{
		if (m_pCurSkill && m_pCurSkill->CanUse())
		{
			packet_attack = new Packet_Attack(m_pTarget,m_pCurSkill);
			g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f,Msg_Attack,packet_attack);
		}
	}
	else
	{
		float fDistance=0.0f;
		for (size_t i = 0; i < m_vecParty.size(); ++i)
		{
			if (m_vecParty[i]->GetID() == m_leaderID || m_vecParty[i]->GetID() == m_entityID)
				continue;
			fDistance = D3DXVec3LengthSq(&(m_vecParty[i]->GetVPos() - m_vCurPos));
			if (fDistance < m_boundsphere.fRadius*m_boundsphere.fRadius)
			{
				D3DXVECTOR3 velocity = (m_vCurPos - m_vecParty[i]->GetVPos());
				D3DXVec3Normalize(&velocity,&velocity);
				m_vVelocity += velocity;
				++m_nVelocityNum;
			}
		}
	}

	if (m_nVelocityNum)
	{
		m_vVelocity /= m_nVelocityNum;
		packet_move = new Packet_Pos(m_vCurPos + m_vVelocity);
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Move, packet_move);
	}

	
	for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
	{
		iter->second->Update(delta);
	}
}

bool cCombatNPCState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Respawn:
		packet_move = (Packet_Pos*)_packet.info;
		m_bLive = true;
		m_bCombat = false;
		m_pTarget = nullptr;
		m_pStatus->SetCurrentHP(m_pStatus->GetMaxHP());
		m_pStatus->SetCurrentMP(m_pStatus->GetMaxMP());
		m_packet.msg_type = Msg_Respawn;
		m_pState->OnMessage(_entity, m_packet);
		g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f,Msg_Idle,NULL);
		_entity->SetVPos(packet_move->vPos);
		SAFE_DELETE(packet_move);
		return true;
	case Msg_SupportEnd:
		m_pParty = nullptr;
		m_pCurSkill = nullptr;
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
		return true;
	case Msg_AddCondition:
		packet_condition = (Packet_AddCondition*)_packet.info;
		_entity->AddCondition(packet_condition->pCondition);
		SAFE_DELETE(packet_condition);
		return true;
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
	case Msg_LostTarget:
		m_pTarget = nullptr;
		m_bCombat = false;
		return true;
	case Msg_SetSkill:
		packet_setskill = (Packet_SetSkill*)_packet.info;
		packet_setskill->skill->SetOwner(_entity);
		m_mapSkill.insert(std::pair<char, cSkill*>(packet_setskill->key, packet_setskill->skill));
		SAFE_DELETE(packet_setskill);
		return true;
	case Msg_NeedHeal:
		if (m_bLive)
		{
			cGameObject* _pTarget = g_pObjectManager->FindObjectByID(_packet.sender);
			m_mapNeedHelp[_pTarget->GetID()]=_pTarget;
		}
		return true;
	case Msg_JoinParty:
		m_vecParty.push_back(g_pObjectManager->FindObjectByID(_packet.sender));
		if (!m_pLeader) {
			m_pLeader = m_vecParty.front();
			m_leaderID = m_pLeader->GetID();
		}
		return true;
	case Msg_Target:
		packet_target = (Packet_Target*)_packet.info;
		if (m_bLive)
		{
			m_pTarget = packet_target->pTarget;
			if (!m_pTarget)
				m_bCombat = false;
			else if (0 < m_pTarget->GetStatus().GetCurrentHP())
			{
				m_bCombat = true;
			}
			else
				m_pTarget = nullptr;
		}
		SAFE_DELETE(packet_target);
		return true;
	case Msg_AttackEnd:
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
		m_pCurSkill = nullptr;
		return true;
	case Msg_Hit:
		packet_hit = (Packet_Hit*)_packet.info;
		m_pStatus->DecCurrentHP(packet_hit->damage-m_pStatus->GetDef());
		if (0 < m_pStatus->GetCurrentHP())
		{
			for (size_t index = 0; index < m_vecParty.size(); ++index)
			{
				g_pMessageDispatcher->Dispatch(m_entityID,m_vecParty[index]->GetID(),0.0f,Msg_NeedHeal,NULL);
			}
		}
		else
		{
			m_bLive = false;
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Standby, NULL);
			m_packet.msg_type = Msg_Death;
			m_pState->OnMessage(_entity, m_packet);
		}
		SAFE_DELETE(packet_hit);
		g_pSoundManager->Start("hit");
		return true;
	default:
		return m_pState->OnMessage(_entity, _packet);
	}
	return false;
}


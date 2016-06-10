#include "stdafx.h"
#include "cMonsterState.h"
#include "cGameObject.h"
#include "cRandom.h"

cMonsterState::cMonsterState(cIState* _pState)
{
	m_pState = _pState;
	ZeroMemory(&m_packet, sizeof(m_packet));
}

cMonsterState::~cMonsterState()
{
}

void cMonsterState::EnterState(cGameObject * _entity)
{
	m_pState->EnterState(_entity);
	m_pStatus = &_entity->GetStatus();

	m_vRespawnPos = _entity->GetVPos();

	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("player"));
	//m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
	
}

void cMonsterState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
}

void cMonsterState::Execute(cGameObject * _entity)
{
	int HP = m_pStatus->GetMaxHP();

	if (m_bLive)
	{
		if (0 < HP)
		{
		}
		else
		{
			m_packet.msg_type = Msg_Death;
			m_pState->OnMessage(_entity, m_packet);
			m_bLive = false;
			m_fRespawnPassedTime = 0.0f;
			m_fRespawnTime = cRandom::GetFloat(4.0,2.0);
		}
	}
	else
	{
		m_fRespawnPassedTime += g_pTimeManager->GetDeltaTime();
		if (m_fRespawnPassedTime > m_fRespawnTime)
		{
			m_bLive = true;
			_entity->SetVPos(m_vRespawnPos);

		}
	}
	
	m_pState->Execute(_entity);
	m_vPos = _entity->GetVPos();

	if (!m_bAttack)
	{
		for (size_t i = 0; i < m_vecTargetTag.size(); ++i)
		{
			std::vector<cGameObject*>& target = g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
			for (size_t i = 0; i < target.size(); ++i)
			{
				m_pTarget = target[i];
				m_vTargetPos = m_pTarget->GetVPos();
				m_fTargetRange = D3DXVec3LengthSq(&(m_vTargetPos - m_vPos));
				if (m_fTargetRange < m_pStatus->GetSenseRange()*m_pStatus->GetSenseRange())
				{
					packet_target = new Packet_Target(m_pTarget);
					g_pMessageDispatcher->Dispatch(_entity->GetID(), _entity->GetID(),
						0.0f, Msg_Approach, packet_target);
					m_bAttack = true;
				}
			}
		}
	}
	else {
		if (!m_vTargetPos)
			return;
		m_vTargetPos = m_pTarget->GetVPos();
		m_fTargetRange = D3DXVec3LengthSq(&(m_vTargetPos - m_vPos));
		if (m_fTargetRange > m_pStatus->GetChaseRange()*m_pStatus->GetChaseRange())
		{
			/*packet_target = new Packet_Target(m_pTarget);
			g_pMessageDispatcher->Dispatch(_entity->GetID(), _entity->GetID(),
				0.0f, Msg_Attack, packet_target);*/
			m_bAttack = false;
			m_pTarget = nullptr;
			packet_move = new Packet_Move(m_vRespawnPos);
			g_pMessageDispatcher->Dispatch(_entity->GetID(), _entity->GetID(),
				0.0f, Msg_Move, packet_move);
		}
	}
}

bool cMonsterState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type) 
	{
		
	default:
		return m_pState->OnMessage(_entity,_packet);
	}
	return false;
}

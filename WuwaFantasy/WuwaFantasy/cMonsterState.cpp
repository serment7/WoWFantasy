#include "stdafx.h"
#include "cMonsterState.h"
#include "cGameObject.h"

cMonsterState::cMonsterState(cIState* _pState)
{
	m_pState = _pState;
}


cMonsterState::~cMonsterState()
{
}

void cMonsterState::EnterState(cGameObject * _entity)
{
	m_pState->EnterState(_entity);
	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("player"));
	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
}

void cMonsterState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
}

void cMonsterState::Execute(cGameObject * _entity)
{
	m_pState->Execute(_entity);
	m_vPos = _entity->GetVPos();
	if (!m_bAttack)
	{
		for (int i = 0; i < m_vecTargetTag.size(); ++i)
		{
			std::vector<cGameObject*>& target = g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
			for (int i = 0; i < target.size(); ++i)
			{
				m_pTarget = target[i];
				m_vTarget = m_pTarget->GetVPos();
				m_fRange = D3DXVec3LengthSq(&(m_vTarget - m_vPos));
				if (m_fRange < m_fRecognitionRange)
				{
					packet_target = new Packet_Target(m_pTarget);
					g_pMessageDispatcher->Dispatch(_entity->GetID(), _entity->GetID(),
						0.0f, Msg_Attack, packet_target);
					m_bAttack = true;
				}
			}
		}
	}
	else {
		if (!m_vTarget)
			return;
		m_vTarget = m_pTarget->GetVPos();
		m_fRange = D3DXVec3LengthSq(&(m_vTarget - m_vPos));
		if (m_fRange > m_fRecognitionRange)
		{
			packet_target = new Packet_Target(m_pTarget);
			g_pMessageDispatcher->Dispatch(_entity->GetID(), _entity->GetID(),
				0.0f, Msg_Attack, packet_target);
			m_bAttack = false;
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

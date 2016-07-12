#include "stdafx.h"
#include "cIState.h"
#include "cGameObject.h"
#include"cIdleState.h"
#include"cMoveState.h"
#include "cStandbyState.h"
#include "cPatrolState.h"
#include "cAttackState.h"
#include "cStunState.h"

cIState::cIState()
{
}

bool cIState::MessageCatch(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Stun:
		m_pStunState = cStunState::GetInstance();
		_entity->GetStateMachine()->ChangeState(m_pStunState);
		m_pStunState->OnMessage(_entity, _packet);
		m_pStunState = nullptr;
		return true;
	case Msg_Attack:
		m_pAttackState = cAttackState::GetInstance();
		_entity->GetStateMachine()->ChangeState(m_pAttackState);
		m_pAttackState->OnMessage(_entity, _packet);
		m_pAttackState = nullptr;
		return true;
	case Msg_Patrol:
		m_pPatrolState = cPatrolState::GetInstance();
		_entity->GetStateMachine()->ChangeState(m_pPatrolState);
		m_pPatrolState->OnMessage(_entity,_packet);
		m_pPatrolState = nullptr;
		return true;
	case Msg_Idle:
		m_pIdleState = cIdleState::GetInstance();
		_entity->GetStateMachine()->ChangeState(m_pIdleState);
		m_pIdleState->OnMessage(_entity, _packet);
		m_pIdleState = nullptr;
		return true;
	case Msg_Move:
		m_pMoveState = cMoveState::GetInstance();
		_entity->GetStateMachine()->ChangeState(m_pMoveState);
		m_pMoveState->OnMessage(_entity, _packet);
		m_pMoveState = nullptr;
		return true;
	case Msg_Standby:
		m_pStatdbyState = cStandbyState::GetInstance();
		_entity->GetStateMachine()->ChangeState(m_pStatdbyState);
		m_pStatdbyState->OnMessage(_entity, _packet);
		m_pStatdbyState = nullptr;
		return true;
	}
	return false;
}

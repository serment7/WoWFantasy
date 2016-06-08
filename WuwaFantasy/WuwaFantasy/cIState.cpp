#include "stdafx.h"
#include "cIState.h"
#include "cGameObject.h"
#include"cIdleState.h"
#include"cMoveState.h"
#include"cAttackState.h"
#include"cApproachState.h"

bool cIState::MessageCatch(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Idle:
		m_pIdleState = cIdleState::GetInstance();
		m_pIdleState->OnMessage(_entity, _packet);
		_entity->GetStateMachine()->ChangeState(m_pIdleState);
		m_pIdleState = nullptr;
		return true;
	case Msg_Move:
		m_pMoveState = cMoveState::GetInstance();
		m_pMoveState->OnMessage(_entity, _packet);
		_entity->GetStateMachine()->ChangeState(m_pMoveState);
		m_pMoveState = nullptr;
		return true;
	case Msg_Attack:
		m_pAttackState = cAttackState::GetInstance();
		m_pAttackState->OnMessage(_entity, _packet);
		_entity->GetStateMachine()->ChangeState(m_pAttackState);
		m_pAttackState = nullptr;
		return true;
	case Msg_Approach:
		m_pApproachState = cApproachState::GetInstance();
		m_pApproachState->OnMessage(_entity, _packet);
		_entity->GetStateMachine()->ChangeState(m_pApproachState);
		m_pApproachState = nullptr;
		return true;
	}
	return false;
}

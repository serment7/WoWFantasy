#include "stdafx.h"
#include "cPatrolState.h"
#include "cGameObject.h"
#include "cMoveState.h"

cPatrolState::cPatrolState()
{
}


cPatrolState::~cPatrolState()
{
}

void cPatrolState::EnterState(cGameObject * _player)
{
}

void cPatrolState::ExitState(cGameObject * _player)
{
}

void cPatrolState::Execute(cGameObject * _player)
{
}

bool cPatrolState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Move:
		m_pMoveState = cMoveState::GetInstance();
		m_pMoveState->OnMessage(_player, _packet);
		_player->GetStateMachine()->ChangeState(m_pMoveState);
		m_pMoveState = nullptr;
		return true;
	case Msg_Attack:
		return true;
	}

	return false;
}

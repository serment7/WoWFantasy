#include "stdafx.h"
#include "cAttackState.h"
#include "cAction.h"
#include "cGameObject.h"
#include "cMoveState.h"

cAttackState::cAttackState()
{
}

cAttackState::~cAttackState()
{
}

void cAttackState::EnterState(cGameObject * _player)
{
}

void cAttackState::ExitState(cGameObject * _player)
{
}

void cAttackState::Execute(cGameObject * _player)
{
}

bool cAttackState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Attack:
		
		return true;
	case Msg_Move:
		m_pMoveState = cMoveState::GetInstance();
		m_pMoveState->OnMessage(_player, _packet);
		_player->GetStateMachine()->ChangeState(m_pMoveState);
		m_pMoveState = nullptr;
		return true;
	}

	return false;
}

void cAttackState::OnActionDelegate(cAction * _pSender)
{
}

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
	const size_t& id = _player->GetID();
	g_pMessageDispatcher->Dispatch(id, id, 0.0f, Msg_MoveAni, NULL);
}

void cAttackState::ExitState(cGameObject * _player)
{
	
}

void cAttackState::Execute(cGameObject * _player)
{
	_player->GetAction()->Attack();
}

bool cAttackState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Attack:
		packet_target = (Packet_Attack*)_packet.info;
		m_pAction = _player->GetAction();
		m_pAction->SetDelegate(this);
		m_pAction->ReadyAttack(packet_target->pTarget,packet_target->range);
		m_pAction->Start();
		m_pAction = nullptr;
		return true;
	case Msg_Move:
		return MessageCatch(_player,_packet);
	}

	return false;
}

void cAttackState::OnActionDelegate(cAction * _pSender)
{
	_pSender->Stop();
}

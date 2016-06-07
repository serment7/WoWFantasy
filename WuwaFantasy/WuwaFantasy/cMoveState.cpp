#include "stdafx.h"
#include "cMoveState.h"
#include "cAction.h"
#include "cPlayer.h"
#include "cIdleState.h"

cMoveState::cMoveState()
{
	
}

cMoveState::~cMoveState()
{
}

void cMoveState::EnterState(cGameObject * _player)
{
	pAction = _player->GetAction();
	pAction->SetDelegate(this);
}

void cMoveState::ChangeState(cGameObject * _player)
{
}

void cMoveState::ExitState(cGameObject * _player)
{
}

void cMoveState::Execute(cGameObject * _player)
{
	_player->GetAction()->MoveTo();
}

bool cMoveState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Move:
		packet_move = (Packet_Move*)_packet.info;
		cAction* action = _player->GetAction();
		action->ReadyMoveTo(_player->GetVPos(), packet_move->vDes);
		action->Start();
		SAFE_DELETE(packet_move);
		return true;
	}

	return false;
}

void cMoveState::OnActionDelegate(cAction * _pSender)
{
	_pSender->Stop();
	g_pMessageDispatcher->Dispatch(0, _pSender->GetOwner()->GetID(), 0.0f, Msg_Idle, NULL);
}

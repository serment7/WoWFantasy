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
	const size_t& id = _player->GetID();
	g_pMessageDispatcher->Dispatch(id, id, 0.0f, Msg_MoveAni, NULL);
}

void cMoveState::ExitState(cGameObject * _player)
{
	const size_t& id = _player->GetID();
	g_pMessageDispatcher->Dispatch(id, id, 0.0f, Msg_IdleAni, NULL);
	cAction * pAction = _player->GetAction();
	pAction->SetDelegate(nullptr);
	pAction->Stop();
	pAction = nullptr;
}

void cMoveState::Execute(cGameObject * _player)
{
	_player->GetAction()->MoveTo();
}

bool cMoveState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{

	switch (_packet.msg_type)
	{
	case Msg_Move:
		packet_move = (Packet_Pos*)_packet.info;
		pAction = _player->GetAction();
		pAction->SetDelegate(this);
		pAction->Start();
		pAction = _player->GetAction();
		pAction->ReadyMoveTo(packet_move->vPos);
		pAction = nullptr;
		SAFE_DELETE(packet_move);
		return true;
	default:
		return MessageCatch(_player, _packet);
	}

	return false;
}

void cMoveState::OnActionDelegate(cAction * _pSender)
{
	_pSender->Stop();
	_pSender->GetOwner()->GetStateMachine()->ChangeState(cIdleState::GetInstance());
}

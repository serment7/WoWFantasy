#include "stdafx.h"
#include "cMoveState.h"
#include "cAction.h"
#include "cPlayer.h"
#include "cIdleState.h"
#include "cAttackState.h"
#include "cApproachState.h"

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
	cAction * pAction = _player->GetAction();
	pAction->SetDelegate(this);
	pAction = nullptr;
}

void cMoveState::ExitState(cGameObject * _player)
{
	cAction * pAction = _player->GetAction();
	pAction->SetDelegate(nullptr);
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
		packet_move = (Packet_Move*)_packet.info;
		pAction = _player->GetAction();
		pAction->ReadyMoveTo(packet_move->vDes);
		pAction->Start();
		pAction = nullptr;
		SAFE_DELETE(packet_move);
		return true;
	case Msg_Approach:
	case Msg_Attack:
	case Msg_Idle:
		return MessageCatch(_player, _packet);
	}

	return false;
}

void cMoveState::OnActionDelegate(cAction * _pSender)
{
	_pSender->Stop();
	_pSender->GetOwner()->GetStateMachine()->ChangeState(cIdleState::GetInstance());
}

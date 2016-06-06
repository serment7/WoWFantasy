#include "stdafx.h"
#include "cMoveState.h"
#include "cActionMove.h"
#include "cPlayer.h"

cMoveState::cMoveState()
{
	
}

cMoveState::~cMoveState()
{
}

void cMoveState::EnterState(cGameObject * _player)
{
}

void cMoveState::ChangeState(cGameObject * _player)
{
}

void cMoveState::ExitState(cGameObject * _player)
{
}

void cMoveState::Execute(cGameObject * _player)
{
	
}

bool cMoveState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Attack:
		packet_attack= (Packet_Attack*)_packet.info;
		SAFE_DELETE(packet_attack);
		return true;
	case Msg_Move:
		packet_move = (Packet_Move*)_packet.info;
		cActionMove* action= dynamic_cast<cActionMove*>(_player->GetAction());
		if (!action)
		{
			cIAction* pPrevAction = _player->GetAction();
			SAFE_DELETE(action);
			action = new cActionMove;
		}
		action->SetLifeTime(true);
		action->SetOwner(_player);
		action->SetFrom(_player->GetVPos());
		action->SetTo(packet_move->vDes);
		action->SetDelegate(this);
		action->Start();
		_player->SetAction(action);
		_player->GetSkinnedMesh()->SetAnimationIndex(2);
		SAFE_DELETE(packet_move);
		return true;
	}

	return false;
}

void cMoveState::OnActionDelegate(cIAction * _pSender)
{
	_pSender->Stop();
	_pSender->GetOwner()->GetSkinnedMesh()->SetAnimationIndex(4);
	_pSender->SetLifeTime(false);
}

#include "stdafx.h"
#include "cAttackState.h"
#include "cGameObject.h"
#include "cAction.h"

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
	_player->GetAction()->Stop();
	_player->GetAction()->SetDelegate(nullptr);
}

void cAttackState::Execute(cGameObject * _player)
{
	_player->GetAction()->Attack();
}

bool cAttackState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Attack:
		packet_attack = (Packet_Attack*)_packet.info;
		pAction= _player->GetAction();
		pAction->SetDelegate(nullptr);
		pAction->SetTarget(packet_attack->pTarget);
		pAction->ReadyAttack(packet_attack->pSKill);
		pAction->Start();
		pAction = nullptr;
		SAFE_DELETE(packet_attack);
		return true;
	default:
		MessageCatch(_player,_packet);
	}
	return false;
}

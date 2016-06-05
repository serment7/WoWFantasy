#include "stdafx.h"
#include "cPlayerControlState.h"
#include"cActionMove.h"
#include"cPlayer.h"

cPlayerControlState::cPlayerControlState()
{
}


cPlayerControlState::~cPlayerControlState()
{
}

void cPlayerControlState::EnterState(cPlayer * _player)
{

}

void cPlayerControlState::ChangeState(cPlayer * _player)
{
}

void cPlayerControlState::ExitState(cPlayer * _player)
{
}

void cPlayerControlState::Execute(cPlayer * _player)
{
}

bool cPlayerControlState::OnMessage(cPlayer * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver == _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Attack:
		return true;
	case Msg_Move:
		return true;
	}

	return false;
}

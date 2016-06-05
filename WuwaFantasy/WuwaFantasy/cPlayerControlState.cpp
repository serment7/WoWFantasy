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

void cPlayerControlState::EnterState(cPlayer * _entity)
{

}

void cPlayerControlState::ChangeState(cPlayer * _entity)
{
}

void cPlayerControlState::ExitState(cPlayer * _entity)
{
}

void cPlayerControlState::Execute(cPlayer * _entity)
{
}

bool cPlayerControlState::OnMessage(cPlayer * _entity, const ST_PACKET & _packet)
{
	if (_packet.msg_type == Msg_Attack)
	{
		return true;
	}
	return false;
}
